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
        
        int ctII, ctIIplus;
        int ctIIplus_0=0, ctIIplus_1=0, ctIIplus_2=0, ctIIplus_3=0, ctIIplus_4=0, ctIIplus_5=0, ctIIplus_6=0, ctIIplus_7=0,
            ctIIplus_11=0, ctIIplus_12=0, ctIIplus_13=0, ctIIplus_14=0, ctIIplus_15=0, ctIIplus_16=0, ctIIplus_17=0,
            ctIIplus_18=0, ctIIplus_19=0, ctIIplus_20=0, ctIIplus_21=0, ctIIplus_22=0, ctIIplus_23=0, ctIIplus_24=0,
            ctIIplus_25=0, ctIIplus_26=0, ctIIplus_30=0, ctIIplus_31=0, ctIIplus_32=0, ctIIplus_33=0, ctIIplus_34=0, ctIIplus_35=0;
        int ctII_0=0, ctII_1=0, ctII_2=0, ctII_3=0, ctII_4=0, ctII_5=0, ctII_6=0, ctII_7=0,
            ctII_11=0, ctII_12=0, ctII_13=0, ctII_14=0, ctII_15=0, ctII_16=0, ctII_17=0,
            ctII_18=0, ctII_19=0, ctII_20=0, ctII_21=0, ctII_22=0, ctII_23=0, ctII_24=0,
            ctII_25=0, ctII_26=0, ctII_30=0, ctII_31=0, ctII_32=0, ctII_33=0, ctII_34=0, ctII_35=0;
        int ctII_8=0, ctII_9=0, ctII_10=0, ctII_27=0, ctII_28=0, ctII_29=0, ctII_36=0;
        for ( int run=53; run<=114; run++ ) {
        
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
		
			
		
			for ( int i=0; i<40; i++ ) {
				
				int state = 0; // ON
				if ( !gtr.first->IsOn(i) && gtr.first->IsTrash(i) ) { state=1; } // OFF
				if ( !gtr.first->IsOn(i) && !gtr.first->IsTrash(i) ) { state=2; } // AC
			
				if ( state!=0 ) {
					if ( run<95 ) {
						if ( i==0 ) ctII_0++;
						if ( i==1 ) ctII_1++;
						if ( i==2 ) ctII_2++;
						if ( i==3 ) ctII_3++;
						if ( i==4 ) ctII_4++;
						if ( i==5 ) ctII_5++;
						if ( i==6 ) ctII_6++;
						if ( i==7 ) ctII_7++;
						if ( i==11 ) ctII_11++;
						if ( i==12 ) ctII_12++;
						if ( i==13 ) ctII_13++;
						if ( i==14 ) ctII_14++;
						if ( i==15 ) ctII_15++;
						if ( i==16 ) ctII_16++;
						if ( i==17 ) ctII_17++;
						if ( i==18 ) ctII_18++;
						if ( i==19 ) ctII_19++;
						if ( i==20 ) ctII_20++;
						if ( i==21 ) ctII_21++;
						if ( i==22 ) ctII_22++;
						if ( i==23 ) ctII_23++;
						if ( i==24 ) ctII_24++;
						if ( i==25 ) ctII_25++;
						if ( i==26 ) ctII_26++;
						if ( i==30 ) ctII_30++;
						if ( i==31 ) ctII_31++;
						if ( i==32 ) ctII_32++;
						if ( i==33 ) ctII_33++;
						if ( i==34 ) ctII_34++;
						if ( i==35 ) ctII_35++;
					}
					else {
						if ( i==0 ) ctIIplus_0++;
						if ( i==1 ) ctIIplus_1++;
						if ( i==2 ) ctIIplus_2++;
						if ( i==3 ) ctIIplus_3++;
						if ( i==4 ) ctIIplus_4++;
						if ( i==5 ) ctIIplus_5++;
						if ( i==6 ) ctIIplus_6++;
						if ( i==7 ) ctIIplus_7++;
						if ( i==11 ) ctIIplus_11++;
						if ( i==12 ) ctIIplus_12++;
						if ( i==13 ) ctIIplus_13++;
						if ( i==14 ) ctIIplus_14++;
						if ( i==15 ) ctIIplus_15++;
						if ( i==16 ) ctIIplus_16++;
						if ( i==17 ) ctIIplus_17++;
						if ( i==18 ) ctIIplus_18++;
						if ( i==19 ) ctIIplus_19++;
						if ( i==20 ) ctIIplus_20++;
						if ( i==21 ) ctIIplus_21++;
						if ( i==22 ) ctIIplus_22++;
						if ( i==23 ) ctIIplus_23++;
						if ( i==24 ) ctIIplus_24++;
						if ( i==25 ) ctIIplus_25++;
						if ( i==26 ) ctIIplus_26++;
						if ( i==30 ) ctIIplus_30++;
						if ( i==31 ) ctIIplus_31++;
						if ( i==32 ) ctIIplus_32++;
						if ( i==33 ) ctIIplus_33++;
						if ( i==34 ) ctIIplus_34++;
						if ( i==35 ) ctIIplus_35++;
					}
				}
			}
		}
	}
	
	std::cout << "\n ctII_0 = " << ctII_0 << "\t ctIIplus_0 = " << ctIIplus_0 << std::endl;
	std::cout << " ctII_1 = " << ctII_1 << "\t ctIIplus_1 = " << ctIIplus_1 << std::endl;
	std::cout << " ctII_2 = " << ctII_2 << "\t ctIIplus_2 = " << ctIIplus_2 << std::endl;
	std::cout << " ctII_3 = " << ctII_3 << "\t ctIIplus_3 = " << ctIIplus_3 << std::endl;
	std::cout << " ctII_4 = " << ctII_4 << "\t ctIIplus_4 = " << ctIIplus_4 << std::endl;
	std::cout << " ctII_5 = " << ctII_5 << "\t ctIIplus_5 = " << ctIIplus_5 << std::endl;
	std::cout << " ctII_6 = " << ctII_6 << "\t ctIIplus_6 = " << ctIIplus_6 << std::endl;
	std::cout << " ctII_7 = " << ctII_7 << "\t ctIIplus_7 = " << ctIIplus_7 << std::endl;
	
	std::cout << " ctII_11 = " << ctII_11 << "\t ctIIplus_11 = " << ctIIplus_11 << std::endl;
	std::cout << " ctII_12 = " << ctII_12 << "\t ctIIplus_12 = " << ctIIplus_12 << std::endl;
	std::cout << " ctII_13 = " << ctII_13 << "\t ctIIplus_13 = " << ctIIplus_13 << std::endl;
	std::cout << " ctII_14 = " << ctII_14 << "\t ctIIplus_14 = " << ctIIplus_14 << std::endl;
	std::cout << " ctII_15 = " << ctII_15 << "\t ctIIplus_15 = " << ctIIplus_15 << std::endl;
	std::cout << " ctII_16 = " << ctII_16 << "\t ctIIplus_16 = " << ctIIplus_16 << std::endl;
	std::cout << " ctII_17 = " << ctII_17 << "\t ctIIplus_17 = " << ctIIplus_17 << std::endl;
	std::cout << " ctII_18 = " << ctII_18 << "\t ctIIplus_18 = " << ctIIplus_18 << std::endl;
	std::cout << " ctII_19 = " << ctII_19 << "\t ctIIplus_19 = " << ctIIplus_19 << std::endl;
	
	std::cout << " ctII_20 = " << ctII_20 << "\t ctIIplus_20 = " << ctIIplus_20 << std::endl;
	std::cout << " ctII_21 = " << ctII_21 << "\t ctIIplus_21 = " << ctIIplus_21 << std::endl;
	std::cout << " ctII_22 = " << ctII_22 << "\t ctIIplus_22 = " << ctIIplus_22 << std::endl;
	std::cout << " ctII_23 = " << ctII_23 << "\t ctIIplus_23 = " << ctIIplus_23 << std::endl;
	std::cout << " ctII_24 = " << ctII_24 << "\t ctIIplus_24 = " << ctIIplus_24 << std::endl;
	std::cout << " ctII_25 = " << ctII_25 << "\t ctIIplus_25 = " << ctIIplus_25 << std::endl;
	std::cout << " ctII_26 = " << ctII_26 << "\t ctIIplus_26 = " << ctIIplus_26 << std::endl;
	
	std::cout << " ctII_30 = " << ctII_30 << "\t ctIIplus_30 = " << ctIIplus_30 << std::endl;
	std::cout << " ctII_31 = " << ctII_31 << "\t ctIIplus_31 = " << ctIIplus_31 << std::endl;
	std::cout << " ctII_32 = " << ctII_32 << "\t ctIIplus_32 = " << ctIIplus_32 << std::endl;
	std::cout << " ctII_33 = " << ctII_33 << "\t ctIIplus_33 = " << ctIIplus_33 << std::endl;
	std::cout << " ctII_34 = " << ctII_34 << "\t ctIIplus_34 = " << ctIIplus_34 << std::endl;
	std::cout << " ctII_35 = " << ctII_35 << "\t ctIIplus_35 = " << ctIIplus_35 << std::endl;

	return 0;
}
