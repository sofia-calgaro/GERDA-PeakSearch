#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void MC_output(int E0, int det, int i) {

	
	std::string filename;
	// read from JSON files
	if ( det==0 ) { filename = "/home/sofia/Analysis/MC/JsonFiles/coax/JsonFile" + std::to_string(E0) + ".json"; }
	if ( det==1 ) { filename = "/home/sofia/Analysis/MC/JsonFiles/BEGe/JsonFile" + std::to_string(E0) + ".json"; }
	if ( det==2 ) { filename = "/home/sofia/Analysis/MC/JsonFiles/IC/JsonFile" + std::to_string(E0) + ".json"; }
	std::ifstream file(filename);
	json j_read;
	file >> j_read;
	file.close();
	
	double E0_counts_U90 = j_read["90UpperLimit"]["E0_counts_U90"].get<double>(); // 90% upper limit
	double E0_counts_L68 = j_read["68CentralRange"]["E0_counts_L68"].get<double>(); // 68% central interval
	double E0_counts_U68 = j_read["68CentralRange"]["E0_counts_U68"].get<double>();
	double E0_counts_M = j_read["Mean"]["E0_counts"].get<double>(); // mean
	double E0_counts_sigma_M = j_read["Mean"]["E0_counts_sigma"].get<double>();
	double E0_counts_GM = j_read["GlobalMode"]["E0_counts"].get<double>(); // global  mode
	double E0_counts_sigma_GM = j_read["GlobalMode"]["E0_counts_sigma"].get<double>();
	double E0_counts_median = j_read["Median"]["E0_counts_median"].get<double>(); // median
	double E0_counts_L68_sigma = j_read["Median"]["E0_counts_L68_sigma"].get<double>();
	double E0_counts_U68_sigma = j_read["Median"]["E0_counts_U68_sigma"].get<double>();
	
	char name[200];
	if ( det==0 ) sprintf(name, "MC_output/coax/MC%i_U90.txt", E0);
	if ( det==1 ) sprintf(name, "MC_output/BEGe/MC%i_U90.txt", E0);
	if ( det==2 ) sprintf(name, "MC_output/IC/MC%i_U90.txt", E0);
	std::fstream write;
	if ( !write ) {
		write.open(name, std::ios::out);
		
		write << i << "\t\t" << E0_counts_U90 << "\t\t" << E0_counts_L68 << "\t\t" << E0_counts_U68 << "\t\t" 
		      << E0_counts_M << "\t\t" << E0_counts_sigma_M << "\t\t" << E0_counts_GM << "\t\t" << E0_counts_sigma_GM << "\t\t" 
		      << E0_counts_median << "\t\t" << E0_counts_L68_sigma << "\t\t" << E0_counts_U68_sigma << std::endl;
	}
	else {
		write.open(name, std::ios_base::app);
		
		write << i << "\t\t" << E0_counts_U90 << "\t\t" << E0_counts_L68 << "\t\t" << E0_counts_U68 << "\t\t" 
		      << E0_counts_M << "\t\t" << E0_counts_sigma_M << "\t\t" << E0_counts_GM << "\t\t" << E0_counts_sigma_GM << "\t\t" 
		      << E0_counts_median << "\t\t" << E0_counts_L68_sigma << "\t\t" << E0_counts_U68_sigma << std::endl;
	}	
	
	write.close();
	
	std::cout << "\t\t i = " << i << std::endl;
}
