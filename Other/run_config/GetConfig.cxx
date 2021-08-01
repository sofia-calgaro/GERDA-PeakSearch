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
	//if (verbose) for (auto& i : confList) std::cout << i.first << '\t' << i.second << std::endl;
    
	// lambda function to retrieve GETRunConfiguration and filename for timestamp
   	auto FindRunConfiguration = [&](unsigned long long timestamp) {
		//if (verbose) std::cout << "Getting RunConfiguration" << std::endl;
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
	
	// detector names for PhaseII
        const char *detName_II[40] = { "GD91A", "GD35B", "GD02B", "GD00B", "GD61A", "GD89B", "GD02D", "GD91C",
        			"ANG5", "RG1", "ANG3",
        			"GD02A", "GD32B", "GD32A", "GD32C", "GD89C", "GD61C", "GD76B", "GD00C",
        			"GD35C", "GD76C", "GD89D", "GD00D", "GD79C", "GD35A", "GD91B", "GD61B", 
        			"ANG2", "RG2", "ANG4", 
        			"GD00A", "GD02C", "GD79B", "GD91D", "GD32D", "GD89A", "ANG1",
        			"GTF112", "GTF32", "GTF45_2"};	
        // detector names for PhaseII+ 		
        const char *detName_IIPlus[41] = { "GD91A", "GD35B", "GD02B", "GD00B", "GD61A", "GD89B", "GD02D", "GD91C",
        			"ANG5", "RG1", "ANG3",
        			"GD02A", "GD32B", "GD32A", "GD32C", "GD89C", "GD61C", "GD76B", "GD00C",
        			"GD35C", "GD76C", "GD89D", "GD00D", "GD79C", "GD35A", "GD91B", "GD61B", 
        			"ANG2", "RG2", "ANG4", 
        			"GD00A", "GD02C", "GD79B", "GD91D", "GD32D", "GD89A", "IC48B",
        			"IC50B", "IC48A", "IC50A", "IC74A"};			
        
        for ( int run=95; run<=114; run++ ) {
        
       			if ( run!=66 && run!=68 && run!=80 && run!=81 && run!=82 && run!=94 && run!=102 ) {
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
			
			// active detectors
			int num = gtr.first->GetNActiveDetectors();
		
			// file creation
			std::ofstream file("run_config/run"+std::to_string(run)+"_configuration.txt");
			file << "\n *******************************************" << std::endl;
			file << "  Run: " << run << "\t|  Active detectors: " << num << std::endl;
			file << " *******************************************" << std::endl;   
			file << "  Detector\t|  FADC channel\t|  State" << std::endl;
		
			for ( int i=0; i<40; i++ ) {
				if ( i==0 ) {
					file << " *******************************************" << std::endl;
					file << "  String: I" << std::endl;
					file << " *******************************************" << std::endl; 
				}
				if ( i==8 ) {
					file << " *******************************************" << std::endl;
					file << "  String: II" << std::endl;
					file << " *******************************************" << std::endl; 
				}
				if ( i==11 ) {
					file << " *******************************************" << std::endl;
					file << "  String: III" << std::endl;
					file << " *******************************************" << std::endl; 
				}
				if ( i==19 ) {
					file << " *******************************************" << std::endl;
					file << "  String: IV" << std::endl;
					file << " *******************************************" << std::endl; 
				}
				if ( i==27 ) {
					file << " *******************************************" << std::endl;
					file << "  String: V" << std::endl;
					file << " *******************************************" << std::endl; 
				}
				if ( i==30 ) {
					file << " *******************************************" << std::endl;
					file << "  String: VI" << std::endl;
					file << " *******************************************" << std::endl; 
				}
				if ( i==37 ) {
					file << " *******************************************" << std::endl;
					file << "  String: VII" << std::endl;
					file << " *******************************************" << std::endl; 
				}
				int state = 0; // ON
				if ( !gtr.first->IsOn(i) && gtr.first->IsTrash(i) ) { state=1; } // OFF
				if ( !gtr.first->IsOn(i) && !gtr.first->IsTrash(i) ) { state=2; } // AC
				if ( run<=93 ) {
					if ( i==37 || i==39 ) file << "  " << detName_II[i] << "\t|  " << i << "\t\t|  " << state << std::endl;
					else { file << "  " << detName_II[i] << "\t\t|  " << i << "\t\t|  " << state << std::endl; }
				}
				if ( run>=95 ) { file << "  " << detName_IIPlus[i] << "\t\t|  " << i << "\t\t|  " << state << std::endl; }
				if ( i!=7 && i!=10 && i!=18 && i!=26 && i!=29 && i!=36 && i!=39  ) {
					file << " ------------------------------------------" << std::endl;
				}
			}
			file << " *******************************************\n" << std::endl; 
			file.close();
		}
	}
	

	return 0;
}
