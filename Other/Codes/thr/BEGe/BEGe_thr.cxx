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
	sprintf(name_rootfile, "20210%i%i_BEGeTHR.root", 7, 24);
	TFile *f = new TFile(name_rootfile, "recreate") ;
	
	std::fstream write1;
	write1.open("dsID_BEGeTHR.txt", std::ios::out);	
	
	auto runList_lowTHR = { 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
                     63, 64, 65, /*66,*/ 67, /*68,*/ 69, 70, 71, 72,
                     73, 74, 75, 76, 77, 78, 79, /*80, 81, 82,*/
                     83, 84, 85, 86 }; 
        
        // detector histograms
	TH1D *LAr_ch0 = new TH1D("LAr_ch0", "", 180, 120, 300);
	LAr_ch0->SetLineColor(2);
	TH1D *LAr_ch1 = new TH1D("LAr_ch1", "", 180, 120, 300);
	LAr_ch1->SetLineColor(4);
	TH1D *LAr_ch2 = new TH1D("LAr_ch2", "", 180, 120, 300);
	LAr_ch2->SetLineColor(6);
	TH1D *LAr_ch3 = new TH1D("LAr_ch3", "", 180, 120, 300);
	LAr_ch3->SetLineColor(8);
	TH1D *LAr_ch4 = new TH1D("LAr_ch4", "", 180, 120, 300);
	LAr_ch4->SetLineColor(42);
	TH1D *LAr_ch5 = new TH1D("LAr_ch5", "", 180, 120, 300);
	LAr_ch5->SetLineColor(44);
	TH1D *LAr_ch6 = new TH1D("LAr_ch6", "", 180, 120, 300);
	LAr_ch6->SetLineColor(46);
	TH1D *LAr_ch7 = new TH1D("LAr_ch7", "", 180, 120, 300);
	LAr_ch7->SetLineColor(48);
	TH1D *LAr_ch11 = new TH1D("LAr_ch11", "", 180, 120, 300);
	LAr_ch11->SetLineColor(50);
	TH1D *LAr_ch12 = new TH1D("LAr_ch12", "", 180, 120, 300);
	LAr_ch12->SetLineColor(20);
	TH1D *LAr_ch13 = new TH1D("LAr_ch13", "", 180, 120, 300);
	LAr_ch13->SetLineColor(22);
	TH1D *LAr_ch14 = new TH1D("LAr_ch14", "", 180, 120, 300);
	LAr_ch14->SetLineColor(24);
	TH1D *LAr_ch15 = new TH1D("LAr_ch15", "", 180, 120, 300);
	LAr_ch15->SetLineColor(26);
	TH1D *LAr_ch16 = new TH1D("LAr_ch16", "", 180, 120, 300);
	LAr_ch16->SetLineColor(28);
	TH1D *LAr_ch17 = new TH1D("LAr_ch17", "", 180, 120, 300);
	LAr_ch17->SetLineColor(30);
	TH1D *LAr_ch18 = new TH1D("LAr_ch18", "", 180, 120, 300);
	LAr_ch18->SetLineColor(32);
	TH1D *LAr_ch19 = new TH1D("LAr_ch19", "", 180, 120, 300);
	LAr_ch19->SetLineColor(34);
	TH1D *LAr_ch20 = new TH1D("LAr_ch20", "", 180, 120, 300);
	LAr_ch20->SetLineColor(36);
	TH1D *LAr_ch21 = new TH1D("LAr_ch21", "", 180, 120, 300);
	LAr_ch21->SetLineColor(38);
	TH1D *LAr_ch22 = new TH1D("LAr_ch22", "", 180, 120, 300);
	LAr_ch22->SetLineColor(40);
	TH1D *LAr_ch23 = new TH1D("LAr_ch23", "", 180, 120, 300);
	LAr_ch23->SetLineColor(42);
	TH1D *LAr_ch24 = new TH1D("LAr_ch24", "", 180, 120, 300);
	LAr_ch24->SetLineColor(44);
	TH1D *LAr_ch25 = new TH1D("LAr_ch25", "", 180, 120, 300);
	LAr_ch25->SetLineColor(46);
	TH1D *LAr_ch26 = new TH1D("LAr_ch26", "", 180, 120, 300);
	LAr_ch26->SetLineColor(48);
	TH1D *LAr_ch30 = new TH1D("LAr_ch30", "", 180, 120, 300);
	LAr_ch30->SetLineColor(50);
	TH1D *LAr_ch31 = new TH1D("LAr_ch31", "", 180, 120, 300);
	LAr_ch31->SetLineColor(52);
	TH1D *LAr_ch32 = new TH1D("LAr_ch32", "", 180, 120, 300);
	LAr_ch32->SetLineColor(54);
	TH1D *LAr_ch33 = new TH1D("LAr_ch33", "", 180, 120, 300);
	LAr_ch33->SetLineColor(56);
	TH1D *LAr_ch34 = new TH1D("LAr_ch34", "", 180, 120, 300);
	LAr_ch34->SetLineColor(58);
	TH1D *LAr_ch35 = new TH1D("LAr_ch35", "", 180, 120, 300);
	LAr_ch35->SetLineColor(60);
	
	TH1D *LAr_str1 = new TH1D("LAr_str1", "", 5200, 0, 5200);
	LAr_str1->SetLineColor(1);
	TH1D *LAr_str3 = new TH1D("LAr_str3", "", 5200, 0, 5200);
	LAr_str3->SetLineColor(2);
	TH1D *LAr_str4 = new TH1D("LAr_str4", "", 5200, 0, 5200);
	LAr_str4->SetLineColor(4);
	TH1D *LAr_str6 = new TH1D("LAr_str6", "", 5200, 0, 5200);
	LAr_str6->SetLineColor(6);
        
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
					
						if ( detector->GetDetectorType()==kIsBEGe ) { // BEGe
							if ( energy[j] > 0 and ( idsID == 0 || idsID == 4 || idsID == 8 || idsID == 9 ) ) { 
								if ( j==0 ) LAr_ch0->Fill(energy[j]); 
								if ( j==1 ) LAr_ch1->Fill(energy[j]); 
								if ( j==2 ) LAr_ch2->Fill(energy[j]); 
								if ( j==3 ) LAr_ch3->Fill(energy[j]); 
								if ( j==4 ) LAr_ch4->Fill(energy[j]); 
								if ( j==5 ) LAr_ch5->Fill(energy[j]); 
								if ( j==6 ) LAr_ch6->Fill(energy[j]); 
								if ( j==7 ) LAr_ch7->Fill(energy[j]); 
								if ( j==11 ) LAr_ch11->Fill(energy[j]); 
								if ( j==12 ) LAr_ch12->Fill(energy[j]); 
								if ( j==13 ) LAr_ch13->Fill(energy[j]); 
								if ( j==14 ) LAr_ch14->Fill(energy[j]); 
								if ( j==15 ) LAr_ch15->Fill(energy[j]); 
								if ( j==16 ) LAr_ch16->Fill(energy[j]); 
								if ( j==17 ) LAr_ch17->Fill(energy[j]); 
								if ( j==18 ) LAr_ch18->Fill(energy[j]); 
								if ( j==19 ) LAr_ch19->Fill(energy[j]); 
								if ( j==20 ) LAr_ch20->Fill(energy[j]); 
								if ( j==21 ) LAr_ch21->Fill(energy[j]); 
								if ( j==22 ) LAr_ch22->Fill(energy[j]); 
								if ( j==23 ) LAr_ch23->Fill(energy[j]); 
								if ( j==24 ) LAr_ch24->Fill(energy[j]); 
								if ( j==25 ) LAr_ch25->Fill(energy[j]); 
								if ( j==26 ) LAr_ch26->Fill(energy[j]); 
								if ( j==30 ) LAr_ch30->Fill(energy[j]); 
								if ( j==31 ) LAr_ch31->Fill(energy[j]); 
								if ( j==32 ) LAr_ch32->Fill(energy[j]); 
								if ( j==33 ) LAr_ch33->Fill(energy[j]); 
								if ( j==34 ) LAr_ch34->Fill(energy[j]); 
								if ( j==35 ) LAr_ch35->Fill(energy[j]); 
								
								if ( j>=0 && j<=7 ) LAr_str1->Fill(energy[j]); 
								if ( j>=11 && j<=18 ) LAr_str3->Fill(energy[j]); 
								if ( j>=19 && j<=26 ) LAr_str4->Fill(energy[j]); 
								if ( j>=30 && j<=35 ) LAr_str6->Fill(energy[j]); 
								
								write1 << idsID << std::endl; 
							}
						}	
					}	
				}
			}
		}
		
	} // STOP for
	//====================================================================================================================
	f->WriteTObject(LAr_ch0);
	f->WriteTObject(LAr_ch1);
	f->WriteTObject(LAr_ch2);
	f->WriteTObject(LAr_ch3);
	f->WriteTObject(LAr_ch4);
	f->WriteTObject(LAr_ch5);
	f->WriteTObject(LAr_ch6);
	f->WriteTObject(LAr_ch7);
	f->WriteTObject(LAr_ch11);
	f->WriteTObject(LAr_ch12);
	f->WriteTObject(LAr_ch13);
	f->WriteTObject(LAr_ch14);
	f->WriteTObject(LAr_ch15);
	f->WriteTObject(LAr_ch16);
	f->WriteTObject(LAr_ch17);
	f->WriteTObject(LAr_ch18);
	f->WriteTObject(LAr_ch19);
	f->WriteTObject(LAr_ch20);
	f->WriteTObject(LAr_ch21);
	f->WriteTObject(LAr_ch22);
	f->WriteTObject(LAr_ch23);
	f->WriteTObject(LAr_ch24);
	f->WriteTObject(LAr_ch25);
	f->WriteTObject(LAr_ch26);
	f->WriteTObject(LAr_ch30);
	f->WriteTObject(LAr_ch31);
	f->WriteTObject(LAr_ch32);
	f->WriteTObject(LAr_ch33);
	f->WriteTObject(LAr_ch34);
	f->WriteTObject(LAr_ch35);
	
	f->WriteTObject(LAr_str1);
	f->WriteTObject(LAr_str3);
	f->WriteTObject(LAr_str4);
	f->WriteTObject(LAr_str6);
	
	f->Close();
	write1.close();		
	
	return 0;
}
