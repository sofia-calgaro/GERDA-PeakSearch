//STL
 #include <vector>
 #include <string>
 #include <chrono>
 //#include <inttypes.h>
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

	//paths of meta-data and data
	//std::string metadataPath = "/home/sofia/gerda_data/v07.01/meta"; 
	//std::string dataPath = "/home/sofia/gerda_data/v07.01/gen";
	std::string metadataPath = "/nfs/gerda5/gerda-data/blind/v07.01/meta";
        std::string dataPath = "/nfs/gerda5/gerda-data/blind/v07.01/gen";


	gada::FileMap myMap;
	myMap.SetRootDir(dataPath);
	//take the List of Keys (.txt file)
	
	// Run 53-93 -> 7'060'532 entries
	for (int i=53; i<=93; i++) {
		myMap.BuildFromListOfKeys(metadataPath+"/data-sets/phy/run00"+std::to_string(i)+"-phy-analysis.txt");
	}
	
	// Run 87-114 (no 94)
/*	for (int i=87; i<=99; i++) {
		if ( i != 94 ) { myMap.BuildFromListOfKeys(metadataPath+"/data-sets/phy/run00"+std::to_string(i)+"-phy-analysis.txt"); }
	}
	for (int i=100; i<=114; i++) {
		myMap.BuildFromListOfKeys(metadataPath+"/data-sets/phy/run0"+std::to_string(i)+"-phy-analysis.txt");
	}
*/	

	char name_rootfile[100];
	sprintf(name_rootfile, "IC_20210%i%i.root", 5, 12);

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
	TTreeReaderArray<double> energyGauss (treereader, "rawEnergyGauss");
	TTreeReaderArray<double> energy      (treereader, "energy");
	TTreeReaderArray<double> risetime1090 (treereader,"risetime1090");
	TTreeReaderArray<double> AoE (treereader,"AoE");
	TTreeReaderArray<double> AoEcorrected (treereader,"AoEcorrected");
	TTreeReaderValue<ULong64_t> timestamp (treereader, "timestamp");

	treereader.SetTree(masterTree);

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	// IC -> det = 37, 38 (IC48A), 39, 40
	
	const int det_tot = 41; // number of detectors

	std::vector<bool>   *isAoEevaluated = new std::vector<bool>  (det_tot);
	//vector<double> *AoEcorrected = new vector <double> (det_tot);
	//std::vector<int> *psdIsEval = new std::vector<int> (det_tot);
	//std::vector<double> energy (det_tot);
	//std::vector<bool>    isAoEevaluated (det_tot);
	//std::vector<double> AoEcorrected (det_tot);

	bool AEeval = false;
	
	if( masterTree->GetBranchStatus("isAoEevaluated") ) { // chain==masterTree  
		AEeval = true;
		masterTree -> SetBranchAddress("isAoEevaluated", &isAoEevaluated);
		}

	auto start = std::chrono::system_clock::now(); 

	int nTP = 0;

	TFile *f = new TFile( name_rootfile, "recreate") ;

	TH1D *histo_energy_LArVetoed = new TH1D( "histo_energy_LArVetoed", "Energy (LAr veto)", 5200, 0, 5200 );
        histo_energy_LArVetoed->GetXaxis()->SetTitle( "Energy [keV]" );
        histo_energy_LArVetoed->GetYaxis()->SetTitle( "Events / 1 keV" );
	
	TH1D *histo_energy = new TH1D( "histo_energy", "Energy (no LAr veto)", 5200, 0, 5200 );
	histo_energy->SetLineColor(2);	
	histo_energy->GetXaxis()->SetTitle( "Energy [keV]" );
        histo_energy->GetYaxis()->SetTitle( "Events / 1 keV" );
        	
	/*TH1D *histo_AE= new TH1D ( "histo_AE", "histo_AE (no LAr veto)", 1e4, 0, 0.1 );
	TH2D *histo_AE_E= new TH2D("histo_AE_E","histo_AE_E",1e4,0,1e4,1e4,0,0.14);
	TH2D *histo_AE_E_corrected= new TH2D("histo_AE_E_corrected","histo_AE_E_corrected",3000,0,3000,1e4,0,2.8);
	TH2D *histo_risetime_E= new TH2D("histo_risetime_E","histo_risetime_E",3000,0,3000,1e3,0,1500);*/

	int entry = 0;
	int etot = masterTree->GetEntries();

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Up to when there is a Next in the entries:
	while (treereader.Next()){ 

		if(entry%100000==0) { std::cout << "entry " << entry << " of " << etot << std::endl; }

		masterTree->GetEntry(entry++);

		if (*isTP) nTP++; // count test pulses (every 20s) if I want to calculate the lifetime

		// loop over channels (IC -> 37, 38, 39, 40)
		for ( int det = 36; det < 40 ; det++ ) {

			if ( !*isTP and !*isMuVetoed and *multiplicity == 1 and !*isLArVetoed) { // LAr veto
				auto dsID = DManager.FindDataset(*timestamp, det, true);
				
				if ( energy[det] > 0 and (dsID == -1 or dsID == 2 or energy[det] == 10000 )) { }
				
				else if( energy[det]>1 ) {
					histo_energy_LArVetoed->Fill(energy[det]);
					//histo_AE->Fill(AoE[det]);
					//histo_AE_E->Fill(energy[det],AoE[det]);
					//histo_risetime_E->Fill(energy[det],risetime1090[det]);

					//if(AEeval)
					//if(isAoEevaluated->at(det)){ // poichè AoEevaluated è un puntatore, lo faccio puntare in modo controllato così
					//histo_AE_E_corrected->Fill(energy[det],AoEcorrected[det]);
					
					} // STOP else if
				} // STOP if(isTP, isMuVetoed, multiplicity, isLArVetoed)
				
			if ( !*isTP and !*isMuVetoed and *multiplicity == 1 ) {
				auto dsID = DManager.FindDataset(*timestamp, det, true);
				
				if ( energy[det] > 0 and (dsID == -1 or dsID == 2 or energy[det] == 10000 )) { }
				
				else if( energy[det]>1 ) {
					histo_energy->Fill(energy[det]);
					//histo_AE->Fill(AoE[det]);
					
					} // STOP else if
				} // STOP if(isTP, isMuVetoed, multiplicity)				
			} // STOP for(det)
		} // STOP while
	
	// create a txt file containing the bin contents
	std::fstream write;
        write.open("bin_content.txt", std::ios::out);

        for (int i=1; i<=5200; i++) {
        write << histo_energy_LArVetoed->GetBinContent(i) << std::endl;
        }
    
        write.close();
			
	std::vector<int> energy_LAr(5200);
   	for (int i=1; i <= 5200; i++) {
	   	int x = histo_energy_LArVetoed->GetBinContent(i);
	   	energy_LAr.push_back( x );
   	}
			
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	f->WriteTObject(histo_energy_LArVetoed);
	f->WriteTObject(histo_energy);
	f->WriteObject(&energy_LAr, "energy_LAr");		
	f->Close();
	
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
	std::cout << " [" << elapsed.count()*1./1000 << "s]\n";
	
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------	
	
	return 0;
}

