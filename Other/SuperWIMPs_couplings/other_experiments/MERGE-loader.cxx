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

using namespace std;


int main() {

	const int thr_BEGe = 195; // BEGe
	const int thr_coax = 195; // coax
	
	double exp_det_II[40]={0};
	double exp_det_IIP[41]={0};
	
	std::fstream write1;
	write1.open("exp_single_detector_II.txt", std::ios::out);	
	std::fstream write2;
	write2.open("exp_single_detector_IIP.txt", std::ios::out);	
	std::fstream write5;
	write5.open("onlyPSD_IIP.txt", std::ios::out);	
	
	std::fstream write3;
	write3.open("dsID_PSD_all.txt", std::ios::out);	
	std::fstream write4;
	write4.open("dsID_all.txt", std::ios::out);	
	
	TH1D *LAr = new TH1D( "LAr", "Energy (LAr veto)", 5200, 0, 5200 );
	LAr->GetXaxis()->SetTitle( "Energy [keV]" );
	LAr->GetYaxis()->SetTitle( "Events / 1 keV" );
	LAr->SetLineWidth(2);
	
	TH1D *LAr_PSD = new TH1D( "LAr_PSD", "Energy (LAr veto + PSD only)", 5200, 0, 5200 );
	LAr_PSD->GetXaxis()->SetTitle( "Energy [keV]" );
	LAr_PSD->GetYaxis()->SetTitle( "Events / 1 keV" );
	LAr->SetLineWidth(2);
	LAr->SetLineColor(2);

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
        double expAB_coax_PSD_II=0, expBEL_coax_PSD_II=0;
        double expAB_coax_PSD_IIP=0, expBEL_coax_PSD_IIP=0;
        double exp_IC_IIP=0;
    	double exp_IC_PSD_IIP=0;
    	
    	double B0=0, B1=0, B2=0, B3=0, B4=0, B5=0, B6=0, B7=0;
    	double C8=0, C9=0, C10=0;
    	double B11=0, B12=0, B13=0, B14=0, B15=0, B16=0, B17=0, B18=0;
    	double B19=0, B20=0, B21=0, B22=0, B23=0, B24=0, B25=0, B26=0;
    	double C27=0, C28=0, C29=0;
    	double B30=0, B31=0, B32=0, B33=0, B34=0, B35=0;
    	double C36=0, I36=0, I37=0, I38=0, I39=0, I40=0;
        
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
							
							// COAX
							if ( detector->GetDetectorType()==kIsCOAX ) { 
								if ( id<95 ) { // Phase II
									if ( id<87 ) { 
										// only PSD
										if ( idsID==1 || idsID==5 ) { 
											expAB_coax_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expAB_coax_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_II[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==8) C8 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==9) C9 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==10) C10 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==27) C27 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==28) C28 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==29) C29 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==36) C36 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
										
									}
									else { 
										// only PSD
										if ( idsID==1 || idsID==5 ) { 
											expAB_coax_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_coax_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expAB_coax_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_coax_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_II[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==8) C8 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==9) C9 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==10) C10 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==27) C27 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==28) C28 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==29) C29 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==36) C36 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
								}
								else { // Phase II+
									if ( id<87 ) { 
										// only PSD
										if ( idsID==1 || idsID==5 ) { 
											expAB_coax_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==8) C8 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==9) C9 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==10) C10 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==27) C27 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==28) C28 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==29) C29 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==36) C36 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
									else { 
										// only PSD
										if ( idsID==1 || idsID==5 ) { 
											expAB_coax_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_coax_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==8) C8 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==9) C9 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==10) C10 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==27) C27 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==28) C28 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==29) C29 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==36) C36 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
								}
							}
							
							// BEGe
							if ( detector->GetDetectorType()==kIsBEGe ) { 
								if ( id<95 ) { // Phase II
									if ( id<87 ) { 
										// only PSD
										if ( idsID==0 || idsID==8 ) { 
											expAB_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_II[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==0) B0 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==1) B1 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==2) B2 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==3) B3 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==4) B4 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==5) B5 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==6) B6 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==7) B7 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==11) B11 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==12) B12 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==13) B13 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==14) B14 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==15) B15 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==16) B16 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==17) B17 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==18) B18 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==19) B19 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==20) B20 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==21) B21 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==22) B22 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==23) B23 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==24) B24 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==25) B25 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==26) B26 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==30) B30 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==31) B31 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==32) B32 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==33) B33 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==34) B34 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==35) B35 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
										// no PSD
										if ( idsID==4 || idsID==9 ) { 
											exp_det_II[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==8) C8 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==9) C9 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==10) C10 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==27) C27 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==28) C28 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==29) C29 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if (j==36) C36 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
									else { 
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
											exp_det_II[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==0) B0 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==1) B1 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==2) B2 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==3) B3 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==4) B4 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==5) B5 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==6) B6 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==7) B7 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==11) B11 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==12) B12 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==13) B13 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==14) B14 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==15) B15 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==16) B16 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==17) B17 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==18) B18 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==19) B19 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==20) B20 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==21) B21 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==22) B22 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==23) B23 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==24) B24 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==25) B25 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==26) B26 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==30) B30 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==31) B31 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==32) B32 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==33) B33 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==34) B34 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==35) B35 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
										// no PSD
										if ( idsID==4 || idsID==9 ) { 
											expAB_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expBEL_BEGe_II += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expBEL_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_II[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==0) B0 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==1) B1 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==2) B2 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==3) B3 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==4) B4 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==5) B5 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==6) B6 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==7) B7 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==11) B11 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==12) B12 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==13) B13 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==14) B14 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==15) B15 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==16) B16 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==17) B17 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==18) B18 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==19) B19 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==20) B20 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==21) B21 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==22) B22 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==23) B23 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==24) B24 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==25) B25 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==26) B26 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==30) B30 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==31) B31 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==32) B32 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==33) B33 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==34) B34 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==35) B35 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
								}
								else { // Phase II+
									if ( id<87 ) { 
										// only PSD
										if ( idsID==0 || idsID==8 ) { 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==0) B0 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==1) B1 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==2) B2 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==3) B3 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==4) B4 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==5) B5 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==6) B6 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==7) B7 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==11) B11 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==12) B12 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==13) B13 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==14) B14 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==15) B15 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==16) B16 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==17) B17 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==18) B18 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==19) B19 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==20) B20 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==21) B21 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==22) B22 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==23) B23 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==24) B24 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==25) B25 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==26) B26 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==30) B30 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==31) B31 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==32) B32 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==33) B33 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==34) B34 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==35) B35 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
										if ( idsID==4 || idsID==9 ) { 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==0) B0 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==1) B1 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==2) B2 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==3) B3 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==4) B4 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==5) B5 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==6) B6 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==7) B7 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==11) B11 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==12) B12 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==13) B13 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==14) B14 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==15) B15 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==16) B16 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==17) B17 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==18) B18 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==19) B19 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==20) B20 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==21) B21 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==22) B22 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==23) B23 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==24) B24 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==25) B25 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==26) B26 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==30) B30 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==31) B31 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==32) B32 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==33) B33 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==34) B34 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==35) B35 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
									else { 
										// only PSD
										if ( idsID==0 || idsID==8 ) { 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expAB_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											expBEL_BEGe_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==0) B0 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==1) B1 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==2) B2 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==3) B3 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==4) B4 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==5) B5 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==6) B6 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==7) B7 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==11) B11 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==12) B12 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==13) B13 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==14) B14 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==15) B15 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==16) B16 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==17) B17 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==18) B18 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==19) B19 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==20) B20 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==21) B21 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==22) B22 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==23) B23 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==24) B24 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==25) B25 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==26) B26 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==30) B30 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==31) B31 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==32) B32 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==33) B33 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==34) B34 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==35) B35 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
										if ( idsID==4 || idsID==9 ) { 
											expAB_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg; 
											expBEL_BEGe_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==0) B0 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==1) B1 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==2) B2 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==3) B3 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==4) B4 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==5) B5 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==6) B6 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==7) B7 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==11) B11 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==12) B12 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==13) B13 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==14) B14 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==15) B15 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==16) B16 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==17) B17 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==18) B18 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==19) B19 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==20) B20 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==21) B21 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==22) B22 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==23) B23 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==24) B24 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==25) B25 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==26) B26 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==30) B30 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==31) B31 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==32) B32 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==33) B33 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==34) B34 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
											if(j==35) B35 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
										}
									}
								}
							}
							// IC
							if ( detector->GetDetectorType()==kIsInvCoax ) { 
								// only PSD
								if ( idsID==6 ) { 
									exp_IC_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									exp_IC_PSD_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==36) I36 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==37) I37 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==38) I38 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==39) I39 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==40) I40 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
								}
								if ( idsID==7 ) { 
									exp_IC_IIP += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									exp_det_IIP[j] += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==36) I36 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==37) I37 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==38) I38 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==39) I39 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
									if(j==40) I40 += TPperiod_y * (theRunConf->GetDetector(j)->GetMass())/CLHEP::kg;
								}
							}
						}
					}		
				}
				
			}   
		}
		
	} // STOP for

	for (int i=0; i<40; i++) {
		write1 << i << "\t" << exp_det_II[i] << std::endl;
	}
	
	for (int i=0; i<41; i++) {
		write2 << i << "\t" << exp_det_IIP[i] << std::endl;
	}
	
	
	write5 << " B0 \t "<< B0 << endl;
	write5 << " B1 \t "<< B1 << endl;
	write5 << " B2 \t "<< B2 << endl;
	write5 << " B3 \t "<< B3 << endl;
	write5 << " B4 \t "<< B4 << endl;
	write5 << " B5 \t "<< B5 << endl;
	write5 << " B6 \t "<< B6 << endl;
	write5 << " B7 \t "<< B7 << endl;
	write5 << " B11 \t "<< B11 << endl;
	write5 << " B12 \t "<< B12 << endl;
	write5 << " B13 \t "<< B13 << endl;
	write5 << " B14 \t "<< B14 << endl;
	write5 << " B15 \t "<< B15 << endl;
	write5 << " B16 \t "<< B16 << endl;
	write5 << " B17 \t "<< B17 << endl;
	write5 << " B18 \t "<< B18 << endl;
	write5 << " B19 \t "<< B19 << endl;
	write5 << " B20 \t "<< B20 << endl;
	write5 << " B21 \t "<< B21 << endl;
	write5 << " B22 \t "<< B22 << endl;
	write5 << " B23 \t "<< B23 << endl;
	write5 << " B24 \t "<< B24 << endl;
	write5 << " B25 \t "<< B25 << endl;
	write5 << " B26 \t "<< B26 << endl;
	write5 << " B30 \t "<< B30 << endl;
	write5 << " B31 \t "<< B31 << endl;
	write5 << " B32 \t "<< B32 << endl;
	write5 << " B33 \t "<< B33 << endl;
	write5 << " B34 \t "<< B34 << endl;
	write5 << " B35 \t "<< B35 << endl;


	write1.close();		
	write2.close();		
	write3.close();
	write4.close();
	write5.close();
	
	// PHASE II, II+
	std::cout << "\n Phase (II) \n TOTAL exposure EnrCoax (>thr; 53-93; yes PSD) = " << expAB_coax_PSD_II << " kg*yr" << std::endl;
	std::cout << " TOTAL exposure EnrCoax (<thr; 87-93; yes PSD) = " << expBEL_coax_PSD_II << " kg*yr" << std::endl;
	std::cout << "\n -----------------------------------------------------------------------" << std::endl;
	std::cout << "\n Phase (II, II+) \n TOTAL exposure EnrCoax (>thr; 53-114; yes PSD) = " << expAB_coax_PSD_IIP << " kg*yr" << std::endl;
	std::cout << " TOTAL exposure EnrCoax (<thr; 87-114; yes PSD) = " << expBEL_coax_PSD_IIP << " kg*yr\n" << std::endl;
	
	std::cout << "\n ***********************************************************************" << std::endl;
	
	std::cout << "\n Phase (II) \n TOTAL exposure BEGe (>thr; 53-93) = " << expAB_BEGe_II << " kg*yr" << std::endl;
	std::cout << " TOTAL exposure BEGe (<thr; 87-93) = " << expBEL_BEGe_II << " kg*yr" << std::endl;
	std::cout << "\n -\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-" << std::endl;   
	std::cout << "\n Phase (II) \n TOTAL exposure BEGe (>thr; 53-93; yes PSD) = " << expAB_BEGe_PSD_II << " kg*yr" << std::endl;
	std::cout << " TOTAL exposure BEGe (<thr; 87-93; yes PSD) = " << expBEL_BEGe_PSD_II << " kg*yr" << std::endl;
	std::cout << "\n -----------------------------------------------------------------------" << std::endl;
	std::cout << "\n Phase (II, II+) \n TOTAL exposure BEGe (>thr; 53-114) = " << expAB_BEGe_IIP << " kg*yr" << std::endl;
	std::cout << " TOTAL exposure BEGe (<thr; 87-114) = " << expBEL_BEGe_IIP << " kg*yr" << std::endl;
	std::cout << "\n -\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-\t-" << std::endl;   
	std::cout << "\n Phase (II, II+) \n TOTAL exposure BEGe (>thr; 53-114; yes PSD) = " << expAB_BEGe_PSD_IIP << " kg*yr" << std::endl;
	std::cout << " TOTAL exposure BEGe (<thr; 87-114; yes PSD) = " << expBEL_BEGe_PSD_IIP << " kg*yr\n" << std::endl;
	
	std::cout << "\n ***********************************************************************" << std::endl;
	
	std::cout << "\n Phase (II, II+) \n TOTAL exposure IC (53-114) = " << exp_IC_IIP << " kg*yr" << std::endl;
	std::cout << "\n -----------------------------------------------------------------------" << std::endl;
	std::cout << "\n Phase (II, II+) \n TOTAL exposure IC (53-114; yes PSD) = " << exp_IC_PSD_IIP << " kg*yr\n" << std::endl;
	
	
	cout << " B0 = " << B0 << endl;
	cout << " B1 = " << B1 << endl;
	cout << " B2 = " << B2 << endl;	
	cout << " B3 = " << B3 << endl;
	cout << " B4 = " << B4 << endl;
	cout << " B5 = " << B5 << endl;
	cout << " B6 = " << B6 << endl;
	cout << " B7 = " << B7 << endl;
	cout << " B11 = " << B11 << endl;
	cout << " B12 = " << B12 << endl;
	cout << " B13 = " << B13 << endl;
	cout << " B14 = " << B14 << endl;
	cout << " B15 = " << B15 << endl;
	cout << " B16 = " << B16 << endl;
	cout << " B17 = " << B17 << endl;
	cout << " B18 = " << B18 << endl;
	cout << " B19 = " << B19 << endl;
	cout << " B20 = " << B20 << endl;
	cout << " B21 = " << B21 << endl;
	cout << " B22 = " << B22 << endl;
	cout << " B23 = " << B23 << endl;
	cout << " B24 = " << B24 << endl;
	cout << " B25 = " << B25 << endl;
	cout << " B26 = " << B26 << endl;
	cout << " B30 = " << B30 << endl;
	cout << " B31 = " << B31 << endl;
	cout << " B32 = " << B32 << endl;	
	cout << " B33 = " << B33 << endl;
	cout << " B34 = " << B34 << endl;
	cout << " B35 = " << B35 << endl;
	
	return 0;
}
