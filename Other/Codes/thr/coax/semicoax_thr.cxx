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


int main() {

	char name_rootfile[100];
	sprintf(name_rootfile, "20210%i%i_coaxTHR.root", 7, 24);
	TFile *f = new TFile(name_rootfile, "recreate") ;
	
	std::fstream write1;
	write1.open("dsID_coaxTHR.txt", std::ios::out);	
	
	auto runList_lowTHR = { 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
                     63, 64, 65, /*66,*/ 67, /*68,*/ 69, 70, 71, 72,
                     73, 74, 75, 76, 77, 78, 79, /*80, 81, 82,*/
                     83, 84, 85, 86 }; 
        
        // detector histograms
	TH1D *LAr_ch8 = new TH1D("LAr_ch8", "", 180, 120, 300);
	LAr_ch8->SetLineColor(2);
	TH1D *LAr_ch9 = new TH1D("LAr_ch9", "", 180, 120, 300);
	LAr_ch9->SetLineColor(4);
	TH1D *LAr_ch10 = new TH1D("LAr_ch10", "", 180, 120, 300);
	LAr_ch10->SetLineColor(6);
	TH1D *LAr_ch27 = new TH1D("LAr_ch27", "", 180, 120, 300);
	LAr_ch27->SetLineColor(8);
	TH1D *LAr_ch28 = new TH1D("LAr_ch28", "", 180, 120, 300);
	LAr_ch28->SetLineColor(54);
	TH1D *LAr_ch29 = new TH1D("LAr_ch29", "", 180, 120, 300);
	LAr_ch29->SetLineColor(64);
	TH1D *LAr_ch36 = new TH1D("LAr_ch36", "", 180, 120, 300);
	LAr_ch36->SetLineColor(74);
	
	TH1D *LAr_str2 = new TH1D("LAr_str2", "", 180, 120, 300);
	LAr_str2->SetLineColor(2);
	TH1D *LAr_str5 = new TH1D("LAr_str5", "", 180, 120, 300);
	LAr_str5->SetLineColor(4);
        
        for (auto& id : runList_lowTHR) {
        
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
				if(entry%100000==0) { std::cout << "entry " << entry << " of " << etot << std::endl; }
				masterTree->GetEntry(entry++);
			
				//masterTree->GetEntry();
				theRunConf = theRunConfManager->GetRunConfiguration(*timestamp);
				Double_t TPperiod_y = (1/theRunConf->GetPulserRate())/(60*60*24*365.25);
				int DetTOT = theRunConf->GetNDetectors();
				
				for ( int j = 0; j < DetTOT ; j++ ) {
				
					if ( !*isTP and !*isMuVetoed and *multiplicity == 1 and !*isLArVetoed ) { 
						int idsID = DManager.FindDataset(*timestamp, j, PSDeval ? psdIsEval->at(j) : false);
						const GETDetector *detector = theRunConf->GetDetector(j);
					
						if ( detector->GetDetectorType()==kIsCOAX ) { // COAX
							if ( energy[j] > 0 and ( idsID == 1 || idsID == 5 ) ) { 
								if ( j==8 ) LAr_ch8->Fill(energy[j]); 
								if ( j==9 ) LAr_ch9->Fill(energy[j]); 
								if ( j==10 ) LAr_ch10->Fill(energy[j]); 
								if ( j==27 ) LAr_ch27->Fill(energy[j]); 
								if ( j==28 ) LAr_ch28->Fill(energy[j]); 
								if ( j==29 ) LAr_ch29->Fill(energy[j]); 
								if ( id<95 ) { if ( j==36 ) LAr_ch36->Fill(energy[j]); }
								
								if ( j>=8 && j<=10 ) LAr_str2->Fill(energy[j]); 
								if ( j>=27 && j<=29 ) LAr_str5->Fill(energy[j]); 
								
								write1 << idsID << std::endl; 
							}
						}	
					}	
				}
			}
		}
		
	} // STOP for
	//====================================================================================================================
	f->WriteTObject(LAr_ch8);
	f->WriteTObject(LAr_ch9);
	f->WriteTObject(LAr_ch10);
	f->WriteTObject(LAr_ch27);
	f->WriteTObject(LAr_ch28);
	f->WriteTObject(LAr_ch29);
	f->WriteTObject(LAr_ch36);
	
	f->WriteTObject(LAr_str2);
	f->WriteTObject(LAr_str5);
	
	f->Close();
	write1.close();		
	
	return 0;
}
