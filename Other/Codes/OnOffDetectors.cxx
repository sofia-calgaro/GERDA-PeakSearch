// Use this code if you want to see if each detector is ON(0), OFF(1) or AC(2) during each run

//STL
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <map>
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
 #include "GEChannel.hh"
 #include "GERunConfigurationManager.hh"
 


int main() {

	//paths of meta-data and data
	std::string metadataPath = "/nfs/gerda5/gerda-data/blind/v07.01/meta";
	std::string dataPath = "/nfs/gerda5/gerda-data/blind/v07.01/gen";
	
	auto c_str = [](std::string s){ return s.c_str(); };
	bool verbose = true;
	
	// get runconfig list from runconfiguration.db
  	std::vector<std::pair<std::string,unsigned long long>> confList;
	std::ifstream dbfile(metadataPath + "/config/_aux/geruncfg/runconfiguration.db");
	std::stringstream datastream;
	std::string datastring, name;
	int tstamp;
	
	getline(dbfile, datastring);
	getline(dbfile, datastring);

	// A safe way to read data using stringstream
	// and to avoid duplication of the last line
	while (getline(dbfile, datastring)) {

	// Skip empty lines
	if (datastring.empty()) continue;

	// Read the line and stream the name and the time stamp
	datastream.clear();
	datastream.str(datastring);
	datastream >> name;
	datastream >> tstamp;

	confList.push_back(std::make_pair(name, tstamp));
	}
    
	// lambda function to retrieve GETRunConfiguration and filename for timestamp
   	auto FindRunConfiguration = [&](unsigned long long timestamp) {
		std::cout << "Getting RunConfiguration" << std::endl;
		// find filename
		std::string rcfilename;
		for (int k = (int)confList.size()-1; k >= 0; k--) {
		    if (timestamp >= confList[k].second) {
		        rcfilename = confList[k].first;
		        break;
		    }
		}
		// open and read it
		TFile gtrFile(c_str(metadataPath + "/config/_aux/geruncfg/" + rcfilename));
		std::unique_ptr<GETRunConfiguration> runconfig(dynamic_cast<GETRunConfiguration*>(gtrFile.Get("RunConfiguration")));

		return std::make_pair(std::move(runconfig), rcfilename);
    	};
    	
    	TTreeReader reader;
   	TTreeReaderValue<int>       isTP(reader, "isTP");
    	TTreeReaderValue<ULong64_t> timestamp(reader, "timestamp");
        
        for ( int run=53; run<=114; run++ ) {
        
       			if ( run!=66 && run!=68 && run!=80 && run!=81 && run!=82 && run!=94 && run!=102 ) { // <- these runs are excluded!
			gada::FileMap myMap;
			myMap.SetRootDir(dataPath);
			
			if ( run<100 ) { myMap.BuildFromListOfKeys(metadataPath+"/data-sets/phy/run00"+std::to_string(run)+"-phy-analysis.txt"); }
			else { myMap.BuildFromListOfKeys(metadataPath+"/data-sets/phy/run0"+std::to_string(run)+"-phy-analysis.txt"); }
						
			gada::DataLoader loader;
			loader.AddFileMap(&myMap);
			loader.BuildTier3();
			auto tree = loader.GetSharedMasterChain();
			reader.SetTree(tree);
			
			reader.Next();
			long start_time = *timestamp;
			std::cout << " Run : " << run << "\t->\t";
			auto gtr = FindRunConfiguration(*timestamp);
			
			// number of active detectors
			int num = gtr.first->GetNActiveDetectors();
			
			int DetTOT = 0;
			if ( run<95 ) { DetTOT = 40; }
			else { DetTOT = 41; }
		
			for ( int i=0; i<DetTOT; i++ ) {
				int state = 0; // ON
				if ( !gtr.first->IsOn(i) && gtr.first->IsTrash(i) ) { state=1; } // OFF
				if ( !gtr.first->IsOn(i) && !gtr.first->IsTrash(i) ) { state=2; } // AC
			
				// make your analysis here ...
			}
		}
	}
	
	return 0;
}
