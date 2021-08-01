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

	const int thr = 165; // BEGe
	//const int thr = 195; // coax
	//const int thr = 0; // IC
	
	char name_rootfile[100];
	sprintf(name_rootfile, "PSD_20210%i%i_BEGe.root", 7, 17);
	TFile *f = new TFile( name_rootfile, "recreate") ;
	
	std::fstream write1;
	write1.open("bin_content_BEGe.txt", std::ios::out);
	std::fstream write4;
	write4.open("bin_content_PSD_BEGe.txt", std::ios::out);
	
	std::fstream write2;
	write2.open("dsID_BEGe.txt", std::ios::out);	
	std::fstream write3;
	write3.open("dsID_PSD_BEGe.txt", std::ios::out);	
	
	TH1D *LAr = new TH1D( "LAr", "Energy (LAr veto)", 5200, 0, 5200 );
	LAr->GetXaxis()->SetTitle( "Energy [keV]" );
	LAr->GetYaxis()->SetTitle( "Events / 1 keV" );
	LAr->SetLineColor(kGreen+2);
	
	TH1D *LAr_PSD = new TH1D( "LAr_PSD", "Energy (LAr veto + PSD only)", 5200, 0, 5200 );
	LAr_PSD->GetXaxis()->SetTitle( "Energy [keV]" );
	LAr_PSD->GetYaxis()->SetTitle( "Events / 1 keV" );
	
	auto runList_IIP = { 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
                     63, 64, 65, /*66,*/ 67, /*68,*/ 69, 70, 71, 72,
                     73, 74, 75, 76, 77, 78, 79, /*80, 81, 82,*/
                     83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
                     95,  96,  97,  98,  99, 100, 101, /*102,*/ 103, 104, 105,
                     106, 107, 108, 109, 110, 111, 112, 113, 114 }; // Phase II, II+
                    
        double expAB_BEGe_II=0, expBEL_BEGe_II=0;
        double expAB_BEGe_PSD_II=0, expBEL_BEGe_PSD_II=0;
        double expAB_BEGe_IIP=0, expBEL_BEGe_IIP=0;
        double expAB_BEGe_PSD_IIP=0, expBEL_BEGe_PSD_IIP=0;
        
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
		TTreeReaderValue<int>    isMuVetoed  (treereader, "isVetoedInTime.isvetoedintime");	
		TTreeReaderValue<int>    isLArVetoed  (treereader, "isLArVetoed.isLArVetoed"); // Branch 26 - tier4	
		TTreeReaderArray<int>	 isOverflow (treereader,"isOverflow"); 
		TTreeReaderArray<int>    failedFlag  (treereader, "failedFlag");
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

		bool AEeval = false, PSDeval = false;
		if( masterTree->GetBranchStatus("isAoEevaluated") ) { // chain==masterTree  
			AEeval = true;
			masterTree -> SetBranchAddress("isAoEevaluated", &isAoEevaluated);
			}
		if( masterTree->GetBranchStatus("psdIsEval") ) { 
			PSDeval = true;
			masterTree -> SetBranchAddress("psdIsEval", &psdIsEval);
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
				Double_t TPperiod_y = (1/theRunConf->GetPulserRate())/(60*60*24*365.25);
				int DetTOT = theRunConf->GetNDetectors();
				
				// exposure calculation
				if (*isTP) {
					for (int j=0; j<DetTOT; j++) { // loop over detectors
						if ( theRunConf->IsOn(j) && !theRunConf->IsTrash(j) ) { 
							int idsID = DManager.FindDataset(*timestamp, j, PSDeval ? psdIsEval->at(j) : false);
							const GETDetector *detector = theRunConf->GetDetector(j);
							
							if ( detector->GetDetectorType()==kIsBEGe ) { 
								if ( id<95 ) { // Phase II
									if ( id<87 ) { 
										if ( idsID==4 || idsID==9 ) { 
											expAB_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
										}
										// only PSD
										if ( idsID==0 || idsID==8 ) { 
											expAB_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
									else { 
										if ( idsID==4 || idsID==9 ) { 
											expAB_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expBEL_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expBEL_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
										// only PSD
										if ( idsID==0 || idsID==8 ) { 
											expAB_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_BEGe_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
								}
								else { // Phase II+
									if ( id<87 ) { 
										if ( idsID==4 || idsID==9 ) { 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
										}
										// only PSD
										if ( idsID==0 || idsID==8 ) { 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
									else { 
										if ( idsID==4 || idsID==9 ) { 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expBEL_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
										// only PSD
										if ( idsID==0 || idsID==8 ) { 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
								}
							}
						}
					}		
				}
				else {
					for ( int j = 0; j < DetTOT ; j++ ) {
						if ( !*isTP and !*isMuVetoed and *multiplicity == 1 and !*isLArVetoed ) { 
							int idsID = DManager.FindDataset(*timestamp, j, PSDeval ? psdIsEval->at(j) : false);
							const GETDetector *detector = theRunConf->GetDetector(j);
							
							if ( detector->GetDetectorType()==kIsBEGe ) { 
								if ( id<87 ) {
									if ( energy[j] > thr and ( idsID == 4 || idsID == 9 ) ) { 
										LAr->Fill(energy[j]); 
										write2 << idsID << std::endl; 
									}
									// only PSD
									if ( energy[j] > thr and ( idsID == 0 || idsID == 8 ) ) { 
										LAr->Fill(energy[j]);
										write2 << idsID << std::endl;
										LAr_PSD->Fill(energy[j]);
										write3 << idsID << std::endl;
									}
								}
								else {
									if ( energy[j] > 0 and ( idsID == 4 || idsID == 9 ) ) { 
										LAr->Fill(energy[j]); 
										write2 << idsID << std::endl; 
									}
									// only PSD
									if ( energy[j] > 0 and ( idsID == 0 || idsID == 8 ) ) { 
										LAr->Fill(energy[j]);
										write2 << idsID << std::endl;
										LAr_PSD->Fill(energy[j]);
										write3 << idsID << std::endl;
									}
								}
							}
						}				
					}
				}
			}   
		}
		
	} // STOP for

	//====================================================================================================================
	

	std::vector<int> energy_LAr, energy_LAr_PSD;
	for (int i=0; i< LAr->GetNbinsX(); i++) {
		energy_LAr.push_back(LAr->GetBinContent(i+1));
		write1 << energy_LAr.at(i) << std::endl;
	}
	
	for (int i=0; i< LAr_PSD->GetNbinsX(); i++) {
		energy_LAr_PSD.push_back(LAr_PSD->GetBinContent(i+1));
		write4 << energy_LAr_PSD.at(i) << std::endl;
	}
	
	f->WriteTObject(LAr);
	f->WriteTObject(LAr_PSD);
	f->Close();
	write1.close();		
	write2.close();
	write3.close();
	write4.close();
	
	    // PHASE II
	    std::cout << "\n Phase (II) \n TOTAL exposure BEGe (>thr; 53-93) = " << expAB_BEGe_II << " kg*yr" << std::endl;
	    std::cout << " TOTAL exposure BEGe (<thr; 87-93) = " << expBEL_BEGe_II << " kg*yr" << std::endl;
	    std::cout << "\n -----------------------------------------------------------------------" << std::endl;
	    
	    std::cout << "\n Phase (II) \n TOTAL exposure BEGe (>thr; 53-93; yes PSD) = " << expAB_BEGe_PSD_II << " kg*yr" << std::endl;
	    std::cout << " TOTAL exposure BEGe (<thr; 87-93; yes PSD) = " << expBEL_BEGe_PSD_II << " kg*yr" << std::endl;
	    std::cout << "\n ***********************************************************************" << std::endl;
	      
	    // PHASE II, II+
	    std::cout << "\n Phase (II, II+) \n TOTAL exposure BEGe (>thr; 53-114) = " << expAB_BEGe_IIP << " kg*yr" << std::endl;
	    std::cout << " TOTAL exposure BEGe (<thr; 87-114) = " << expBEL_BEGe_IIP << " kg*yr" << std::endl;
	    
	    std::cout << "\n -----------------------------------------------------------------------" << std::endl;
	    std::cout << "\n Phase (II, II+) \n TOTAL exposure BEGe (>thr; 53-114; yes PSD) = " << expAB_BEGe_PSD_IIP << " kg*yr" << std::endl;
	    std::cout << " TOTAL exposure BEGe (<thr; 87-114; yes PSD) = " << expBEL_BEGe_PSD_IIP << " kg*yr\n" << std::endl;
	
	return 0;
}
