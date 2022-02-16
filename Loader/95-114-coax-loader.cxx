// Macro to build the whole dataset (semicoax + BEGe + IC) for Phase (II, II+) data.
// The exposure is also calculated, above and below the thresholds.

//STL
 #include <vector>
 #include <string>
 #include <chrono>
// ROOT
 #include "TTree.h"
 #include "TTreeReader.h"
 #include "TTreeReaderArray.h"
 #include "TTreeReaderValue.h"
 #include "TFile.h"
 #include "TCanvas.h"
 #include "TH1D.h"
 #include "TH2D.h"
 #include "TStyle.h"
// gerda-ADA
 #include "gerda-ada/FileMap.h"
 #include "gerda-ada/DataLoader.h"
 #include "gerda-ada/GADatasetManager.h"
// GELATIO
 #include "GETRunConfiguration.hh"
 #include "GERunConfigurationManager.hh"
//CLHEP 
#include "CLHEP/Units/SystemOfUnits.h"


int main() {

	const int thr = 195;
	
	char name_rootfile[100];
	sprintf(name_rootfile, "20220%i%i_coax.root", 2, 15); // year / month / day
	TFile *f = new TFile( name_rootfile, "recreate") ;
	
	std::fstream write1;
	write1.open("bin_content_coax.txt", std::ios::out);
	std::fstream write2;
	write2.open("bin_content_PSD_coax.txt", std::ios::out);
	std::fstream write3;
	write3.open("dsID_PSD_coax.txt", std::ios::out);	
	std::fstream write4;
	write4.open("dsID_coax.txt", std::ios::out);	
	
	TH1D *LAr = new TH1D( "LAr", "Energy (LAr veto)", 5200, 0, 5200 );
	LAr->GetXaxis()->SetTitle( "Energy [keV]" );
	LAr->GetYaxis()->SetTitle( "Events / 1 keV" );
	LAr->SetLineWidth(2);
	
	TH1D *LAr_PSD = new TH1D( "LAr_PSD", "Energy (LAr veto + PSD only)", 5200, 0, 5200 );
	LAr_PSD->GetXaxis()->SetTitle( "Energy [keV]" );
	LAr_PSD->GetYaxis()->SetTitle( "Events / 1 keV" );
	LAr->SetLineWidth(2);
	LAr->SetLineColor(2);

	auto runList_IIP = { 95,  96,  97,  98,  99, 100, 101, /*102,*/ 103, 104, 105,
                             106, 107, 108, 109, 110, 111, 112, 113, 114 }; // Phase II+
                     
        double expAB_coax_PSD_II=0, expBEL_coax_PSD_II=0; 
        double expAB_coax_PSD_IIp=0, expBEL_coax_PSD_IIp=0;
        
        for (auto& id : runList_IIP) {
		//paths of meta-data and data
		std::string metadataPath = "/nfs/gerda5/gerda-data/blind/v07.01/meta";
		std::string dataPath = "/nfs/gerda5/gerda-data/blind/v07.01/gen";

		gada::FileMap myMap;
		myMap.SetRootDir(dataPath); //take the List of Keys (.txt file)
		
		if ( id<100 ) { myMap.BuildFromListOfKeys(metadataPath+"/data-sets/phy/run00"+std::to_string(id)+"-phy-analysis.txt"); } 
		else { myMap.BuildFromListOfKeys(metadataPath+"/data-sets/phy/run0"+std::to_string(id)+"-phy-analysis.txt"); }
		
		gada::DataLoader loader;
		loader.AddFileMap(&myMap);
		loader.BuildTier3();
		loader.BuildTier4();

		//shared pointer
		TTree* masterTree = loader.GetSharedMasterChain();

		//chech the datasetID (an environment variables -->setenv)
		gada::GADatasetManager DManager;
		setenv("MU_CAL", (metadataPath + "/config/_aux/geruncfg").c_str(), 1);

		//Set up the tree reader
		TTreeReader treereader;
		TTreeReaderValue<int>    multiplicity(treereader, "multiplicity.firedChannels");
		TTreeReaderValue<int>    isTP        (treereader, "isTP.isTP");
		TTreeReaderValue<int>    isBL        (treereader, "isBL.isBL");
		TTreeReaderValue<int>    isMuVetoed  (treereader, "isVetoedInTime.isvetoedintime");	
		TTreeReaderValue<int>    isLArVetoed  (treereader, "isLArVetoed.isLArVetoed"); // Branch 26 - tier4	
		TTreeReaderArray<int>	 isOverflow (treereader,"isOverflow"); 
		TTreeReaderArray<int>    isPSDVetoed  (treereader, "isPSDVetoed");
		TTreeReaderArray<double> energyGauss (treereader, "rawEnergyGauss");
		TTreeReaderArray<double> energy      (treereader, "energy");
		TTreeReaderArray<double> risetime1090 (treereader,"risetime1090");
		TTreeReaderArray<double> AoE (treereader,"AoE");
		TTreeReaderArray<double> AoEcorrected (treereader,"AoEcorrected");
		TTreeReaderValue<ULong64_t> timestamp (treereader, "timestamp");

		treereader.SetTree(masterTree);

		//====================================================================================================================
		// activated branches
		int DetTOT = 0;
		if ( id < 95 ) { DetTOT = 40; }
		else { DetTOT = 41; }
		std::vector<bool>  	*isAoEevaluated = new std::vector<bool>  (DetTOT);
		std::vector<int>	*psdIsEval = new std::vector<int> (DetTOT);
		std::vector<int>	*qualityCuts = new std::vector<int> (DetTOT);

		bool AEeval = false, PSDeval = false, Qcuts = false;
		if( masterTree->GetBranchStatus("isAoEevaluated") ) { // chain==masterTree  
			AEeval = true;
			masterTree -> SetBranchAddress("isAoEevaluated", &isAoEevaluated);
		}
		if( masterTree->GetBranchStatus("psdIsEval") ) { 
			PSDeval = true;
			masterTree -> SetBranchAddress("psdIsEval", &psdIsEval);
		}
		if( masterTree->GetBranchStatus("failedFlag") ) { 
			Qcuts = true;
			masterTree -> SetBranchAddress("failedFlag", &qualityCuts);
		}

		if ( id>52 ) {
			int entry = 0;
			int etot = masterTree->GetEntries();
			GERunConfigurationManager* theRunConfManager = new GERunConfigurationManager();
			GETRunConfiguration *theRunConf = 0;
			theRunConfManager->AllowRunConfigurationSwitch(true);
			std::cout << " RUN = " << id << std::endl;
			
			//------------------------------------------------------------------------------------------------------------
			while (treereader.Next()) {
				if(entry%100000==0) { /*std::cout << "entry " << entry << " of " << etot << std::endl;*/ }
				masterTree->GetEntry(entry++);
			
				//masterTree->GetEntry();
				theRunConf = theRunConfManager->GetRunConfiguration(*timestamp);
				Double_t TPperiod_y = (1.0/theRunConf->GetPulserRate())/(60.0*60.0*24.0*365.25);
				int DetTOT = theRunConf->GetNDetectors();
				
				// exposure calculation (available only for run 53-93)
				if (*isTP) {
					for (int j=0; j<DetTOT; j++) { // loop over detectors
						if ( theRunConf->IsOn(j) && !theRunConf->IsTrash(j) ) { 
							int idsID = DManager.FindDataset(*timestamp, j, PSDeval ? psdIsEval->at(j) : false);
							const GETDetector *detector = theRunConf->GetDetector(j);
							
							// BEGe
							if ( detector->GetDetectorType()==kIsCOAX ) { 
								if ( id<95 ) { // Phase II
									if ( id<87 ) {
										// only PSD
										if ( idsID==1 || idsID==5 ) { 
											expAB_coax_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
									else { 
										// only PSD
										if ( idsID==1 || idsID==5 ) { 
											expAB_coax_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_coax_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
								}
								else { // Phase II+
									if ( id<87 ) {
										// only PSD
										if ( idsID==1 || idsID==5 ) { 
                                                                                        expAB_coax_PSD_IIp += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
                                                                                }
									}
									else { 
										// only PSD
										if ( idsID==1 || idsID==5 ) {
                                                                                        expAB_coax_PSD_IIp += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
                                                                                        expBEL_coax_PSD_IIp += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
                                                                                }
									}
								}
							}
						}
					}		
				}
				
				for ( int j = 0; j < DetTOT ; j++ ) {
					if ( !*isTP and !*isBL and !*isMuVetoed and *multiplicity == 1 and !*isLArVetoed and qualityCuts->at(j)==0 ) { 
						int idsID = DManager.FindDataset(*timestamp, j, PSDeval ? psdIsEval->at(j) : false);
						const GETDetector *detector = theRunConf->GetDetector(j);
						
						// BEGe
						if ( detector->GetDetectorType()==kIsCOAX ) { 
							if ( id<87 ) {
								// only PSD
								if ( energy[j] > thr and ( idsID == 1 || idsID == 5 ) ) { 
									LAr->Fill(energy[j]);
									write4 << idsID << std::endl;
									LAr_PSD->Fill(energy[j]);
									write3 << idsID << std::endl;
								}
							}
							else {
								// only PSD
								if ( energy[j] > 0 and ( idsID == 1 || idsID == 5 ) ) { 
									LAr->Fill(energy[j]);
									write4 << idsID << std::endl;
									LAr_PSD->Fill(energy[j]);
									write3 << idsID << std::endl;
								}
							}
						}
					}				
				}
			}   
		}
		
	} // STOP for

	//====================================================================================================================
	

	std::vector<int> energy_LAr_PSD;
	for (int i=0; i< LAr_PSD->GetNbinsX(); i++) {
		energy_LAr_PSD.push_back(LAr_PSD->GetBinContent(i+1));
		write2 << energy_LAr_PSD.at(i) << std::endl;
	}
	
	f->WriteTObject(LAr);
	f->WriteTObject(LAr_PSD);
	f->Close();
	write1.close();		
	write2.close();		
	write3.close();
	write4.close();
	
	// PHASE II, II+
        std::cout << "\n Phase (II) \n TOTAL exposure BEGe (>thr; 95-114; yes PSD) = " << expAB_coax_PSD_IIp << " kg*yr" << std::endl;
        std::cout << " TOTAL exposure BEGe (<thr; 95-114; yes PSD) = " << expBEL_coax_PSD_IIp << " kg*yr" << std::endl;

	
	return 0;
}
