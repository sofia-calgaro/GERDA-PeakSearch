#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {

	int ans0, ans;
	std::cout << " Coax (0) or BEGe (1)? ";
	std::cin >> ans0;
	std::cout << "\n * Press:\n\t - 0 if you want to create files,\n\t - 1 if you want to print one E0,\n\t - 2 if you want to print more E0\n -> ";
	std::cin >> ans;

	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	if ( ans == 1 ) {
		int E0;
		std::cout << "\n * Choose E0: ";
		std::cin >> E0;
		
		std::string filename;
		if ( ans0==0 ) { filename = "/home/sofia/Analysis/DataAnalysis/JsonFiles/coax/JsonFile" + std::to_string(E0) + ".json"; }
		else { filename = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe/JsonFile" + std::to_string(E0) + ".json"; }
		std::ifstream file(filename);
		json j_read;
		file >> j_read;
		file.close();
		
		std::cout << "\n\033[1;36m " << std::setw(4) << j_read << "\033[0m\n";	
	} // stop ans=1
	
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	if ( ans == 2 ) {
		int E0_min, E0_max;
		std::cout << "\n * Select the interval [E0_min;E0_max]:\n\t - choose E0_min: ";
		std::cin >> E0_min;
		std::cout << "\t - choose E0_max: ";
		std::cin >> E0_max;
		
		int ans2;
		std::cout << "\n * Do you want everything (0) or not (1)? ";
		std::cin >> ans2;
		
		if ( ans2 == 0 ) {
				int k = 31;
				for ( int j=E0_min; j<=E0_max; j++) {
					std::string filename;
					if ( ans0==0 ) { filename = "/home/sofia/Analysis/DataAnalysis/JsonFiles/coax/JsonFile" + std::to_string(j) + ".json"; }
					else { filename = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe/JsonFile" + std::to_string(j) + ".json"; }
					std::ifstream file(filename);
					if ( !file ) { /*file does not exist*/ }
					else {
						json j_read;
						file >> j_read;
						file.close();
						std::cout << "\033[1;" << k << "m " << std::setw(4) << j_read << "\033[0m\n";
					}
					k++;
					if ( k==37) { k = 31; }	
				}
		} // stop ans2=0
		
		if ( ans2 == 1 ) {
				int ans3;
				std::cout << "\n * What result do you want? " << std::endl;
				std::cout << "\t (1) Peak Search\n\t (2) Parameter Range\n\t (3) Global Mode\n";
				std::cout << "\t (4) Mean\n\t (5) 68 Central Range\n\t (6) 90 Upper Limit\n\t (7) Median\n -> ";
				std::cin >> ans3;
				
		
				int k = 31;
				for ( int j=E0_min; j<=E0_max; j++) {
					std::string filename;
					if ( ans0==0 ) { filename = "/home/sofia/Analysis/DataAnalysis/JsonFiles/coax/JsonFile" + std::to_string(j) + ".json"; }
					else { filename = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe/JsonFile" + std::to_string(j) + ".json"; }
					std::ifstream file(filename);
					if ( !file ) { /*file does not exist*/ }
					else {
						json j_read;
						file >> j_read;
						file.close();
						if ( ans3 == 1 ) { std::cout << "\033[1;" << k << "m " << " E0 = " << j << "\n" << std::setw(4) << j_read["PeakSearch"] << "\033[0m\n"; }
						if ( ans3 == 2 ) { std::cout << "\033[1;" << k << "m " << " E0 = " << j << "\n" << std::setw(4) << j_read["ParameterRange"] << "\033[0m\n"; }
						if ( ans3 == 3 ) { std::cout << "\033[1;" << k << "m " << " E0 = " << j << "\n" << std::setw(4) << j_read["GlobalMode"] << "\033[0m\n"; }
						if ( ans3 == 4 ) { std::cout << "\033[1;" << k << "m " << " E0 = " << j << "\n" << std::setw(4) << j_read["Mean"] << "\033[0m\n"; }
						if ( ans3 == 5 ) { std::cout << "\033[1;" << k << "m " << " E0 = " << j << "\n" << std::setw(4) << j_read["68CentralRange"] << "\033[0m\n"; }
						if ( ans3 == 6 ) { std::cout << "\033[1;" << k << "m " << " E0 = " << j << "\n" << std::setw(4) << j_read["90UpperLimit"] << "\033[0m\n"; }
						if ( ans3 == 7 ) { std::cout << "\033[1;" << k << "m " << " E0 = " << j << "\n" << std::setw(4) << j_read["Median"] << "\033[0m\n"; }
					}
					k++;
					if ( k==37) { k = 31; }	
				}
		} // stop ans2=1
	
	} // stop ans=2
	
	
	//--------------------------------------------------------------------------------------------------------------------------------------------
	if ( ans == 0) {
		int E0_min, E0_max;
		std::cout << "\n * Select the interval [E0_min;E0_max]:\n\t - choose E0_min: ";
		std::cin >> E0_min;
		std::cout << "\t - choose E0_max: ";
		std::cin >> E0_max;
		
		std::string filename1, filename2, filename3, filename4, filename5, filename6, filename7;
		
		// Peak Search
		if ( ans0==0 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/PeakSearch.txt"; }
		else { filename1 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/PeakSearch.txt"; }
		std::ofstream file1(filename1);
		file1 << "# E0" << "\t\t" << "k" << "\t\t" << "outputK" << "\t\t" << "BKGpol" << "\t\t" << "xL" << "\t\t" << "xR" << "\t\t" << "xR-xL" << std::endl;
		
		// Parameter Ranges
		if ( ans0==0 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/ParameterRanges.txt"; }
		else { filename2 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/ParameterRanges.txt"; }
		std::ofstream file2(filename2);
		file2 << "# E0" << std::setw(15) << "E0_min" << std::setw(15) << "E0_max" << std::setw(14) << "p0_min" << std::setw(15) << "p0_max" << std::setw(15) 
		<< "p1_min" << std::setw(15) << "p1_max" << std::setw(15) << "p2_min" << std::setw(15) << "p2_max" << std::endl;
		
		// Global Mode
		if ( ans0==0 ) { filename3 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/GlobalMode.txt"; }
		else { filename3 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/GlobalMode.txt"; }
		std::ofstream file3(filename3);
		file3 << "# E0" << std::setw(14) << "E0_count" << std::setw(15) << "sigma" << std::setw(15) << "p0" << std::setw(15) << "sigma" << std::setw(15) 
		<< "p1" << std::setw(15) << "sigma" << std::setw(15) << "p2" << std::setw(15) << "sigma" << std::endl;
		
		// Mean
		if ( ans0==0 ) { filename4 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/Mean.txt"; }
		else { filename4 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/Mean.txt"; }
		std::ofstream file4(filename4);
		file4 << "# E0" << std::setw(14) << "E0_count" << std::setw(15) << "sigma" << std::setw(15) << "p0" << std::setw(15) << "sigma" <<  std::setw(15) 
		<< "p1" << std::setw(15) << "sigma" << std::setw(15) << "p2" << std::setw(15) << "sigma" << std::endl;
		
		// 68% Quantile
		if ( ans0==0 ) { filename5 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/68Quantile.txt"; }
		else { filename5 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/68Quantile.txt"; }
		std::ofstream file5(filename5);
		file5 << "# E0" << std::setw(15) << "E0_count_L68" << std::setw(15) << "E0_count_U68" << std::setw(14) << "p0_L68" << std::setw(15) << "p0_U68" 
		<< std::setw(15) << "p1_L68" << std::setw(15) << "p1_U68" << std::setw(15) << "p2_L68" << std::setw(15) << "p2_U68" << std::endl;
		
		// 90% Upper Limit
		if ( ans0==0 ) { filename6 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/90UpperLimit.txt"; }
		else { filename6 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/90UpperLimit.txt"; }
		std::ofstream file6(filename6);
		file6 << "# E0" << std::setw(15) << "E0_count_U90" << std::setw(14) << "p0_U90"	<< std::setw(15) << "p1_U90" << std::setw(15) << "p2_U90" << std::endl;
		
		// Median
		if ( ans0==0 ) { filename7 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/Median.txt"; }
		else { filename7 = "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/Median.txt"; }
		std::ofstream file7(filename7);
		file7 << "# E0" << std::setw(15) << "E0_med" << std::setw(14) << "E0_L68sig" << std::setw(14) << "E0_U68sig" << std::setw(14)
		<< "p0_med" << std::setw(15) << "p0_L68sig" << std::setw(15) << "p0_U68sig" << std::setw(15) << "p1_med" << std::setw(15) << 
		"p1_L68sig" << std::setw(15) << "p1_U68sig" << std::setw(15) << "p2_med" << std::setw(15) << "p2_L68sig" << std::setw(15) <<
		"p2_U68sig" << std::endl;
		
		for ( int i=E0_min; i<=E0_max; i++) {
		
			std::string filename;
			if ( ans0==0 ) { filename = "/home/sofia/Analysis/DataAnalysis/JsonFiles/coax/JsonFile" + std::to_string(i) + ".json"; }
			else { filename = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe/JsonFile" + std::to_string(i) + ".json"; }
			std::ifstream file(filename);
			if ( !file ) { /*file does not exist*/ }
			else {
				json j_read;
				file >> j_read;
				file.close();
				
				// Peak Search
				int k_GammaArrayIndex = j_read["PeakSearch"]["k_GammaArrayIndex"].get<int>();
				int outputk_GammaPosition = j_read["PeakSearch"]["outputk_GammaPosition"].get<int>();
				int polDegree_BKG = j_read["PeakSearch"]["polDegree_BKG"].get<double>();
				int windowLeftEdge_xL = j_read["PeakSearch"]["windowLeftEdge_xL"].get<int>();
				int windowRightEdge_xR = j_read["PeakSearch"]["windowRightEdge_xR"].get<int>();
				int windowWidth = j_read["PeakSearch"]["windowWidth"].get<int>();
				
				// Parameter Ranges
				double E0_height_MIN = j_read["ParameterRange"]["E0_counts_MIN"].get<double>();
				double E0_height_MAX = j_read["ParameterRange"]["E0_counts_MAX"].get<double>();
				double p0_MIN = j_read["ParameterRange"]["p0_MIN"].get<double>();
				double p0_MAX = j_read["ParameterRange"]["p0_MAX"].get<double>();
				double p1_MIN=0, p1_MAX=0, p2_MIN=0, p2_MAX=0;
				if ( polDegree_BKG==1 ) {
					p1_MIN = j_read["ParameterRange"]["p1_MIN"].get<double>();
					p1_MAX = j_read["ParameterRange"]["p1_MAX"].get<double>();
				}
				if ( polDegree_BKG==2 ) {
					p2_MIN = j_read["ParameterRange"]["p2_MIN"].get<double>();
					p2_MAX = j_read["ParameterRange"]["p2_MAX"].get<double>();
				}
				
				// Global Mode
				double E0_counts_GM = j_read["GlobalMode"]["E0_counts"].get<double>();
				double E0_counts_sigma_GM = j_read["GlobalMode"]["E0_counts_sigma"].get<double>();
				double p0_GM = j_read["GlobalMode"]["p0"].get<double>();
				double p0_sigma_GM = j_read["GlobalMode"]["p0_sigma"].get<double>();
				double p1_GM=0, p1_sigma_GM=0, p2_GM=0, p2_sigma_GM=0;
				if ( polDegree_BKG==1 ) {
					p1_GM = j_read["GlobalMode"]["p1"].get<double>();
					p1_sigma_GM = j_read["GlobalMode"]["p1_sigma"].get<double>();
				}
				if ( polDegree_BKG==2 ) {
					p1_GM = j_read["GlobalMode"]["p1"].get<double>();
					p1_sigma_GM = j_read["GlobalMode"]["p1_sigma"].get<double>();
					p2_GM = j_read["GlobalMode"]["p2"].get<double>();
					p2_sigma_GM = j_read["GlobalMode"]["p2_sigma"].get<double>();
				}
				
				// Mean
				double E0_counts_M = j_read["Mean"]["E0_counts"].get<double>();
				double E0_counts_sigma_M = j_read["Mean"]["E0_counts_sigma"].get<double>();
				double p0_M = j_read["Mean"]["p0"].get<double>();
				double p0_sigma_M = j_read["Mean"]["p0_sigma"].get<double>();
				double p1_M=0, p1_sigma_M=0, p2_M=0, p2_sigma_M=0;
				if ( polDegree_BKG==1 ) {
					p1_M = j_read["Mean"]["p1"].get<double>();
					p1_sigma_M = j_read["Mean"]["p1_sigma"].get<double>();
				}
				if ( polDegree_BKG==2 ) {
					p1_M = j_read["Mean"]["p1"].get<double>();
					p1_sigma_M = j_read["Mean"]["p1_sigma"].get<double>();
					p2_M = j_read["Mean"]["p2"].get<double>();
					p2_sigma_M = j_read["Mean"]["p2_sigma"].get<double>();
				}
				
				// 68% Quantile
				double E0_counts_L68 = j_read["68CentralRange"]["E0_counts_L68"].get<double>();
				double E0_counts_U68 = j_read["68CentralRange"]["E0_counts_U68"].get<double>();
				double p0_L68 = j_read["68CentralRange"]["p0_L68"].get<double>();
				double p0_U68 = j_read["68CentralRange"]["p0_U68"].get<double>();
				double p1_L68=0, p1_U68=0, p2_L68=0, p2_U68=0;
				if ( polDegree_BKG==1 ) {
					p1_L68 = j_read["68CentralRange"]["p1_L68"].get<double>();
					p1_U68 = j_read["68CentralRange"]["p1_U68"].get<double>();
				}
				if ( polDegree_BKG==2 ) {
					p1_L68 = j_read["68CentralRange"]["p1_L68"].get<double>();
					p1_U68 = j_read["68CentralRange"]["p1_U68"].get<double>();
					p2_L68 = j_read["68CentralRange"]["p2_L68"].get<double>();
					p2_U68 = j_read["68CentralRange"]["p2_U68"].get<double>();
				}
				
				// 90 Upper Limit
				double E0_counts_U90 = j_read["90UpperLimit"]["E0_counts_U90"].get<double>();
				double p0_U90 = j_read["90UpperLimit"]["p0_U90"].get<double>();
				double p1_U90=0, p2_U90=0;
				if ( polDegree_BKG==1 ) {
					p1_U90 = j_read["90UpperLimit"]["p1_U90"].get<double>();
				}
				if ( polDegree_BKG==2 ) {
					p1_U90 = j_read["90UpperLimit"]["p1_U90"].get<double>();
					p2_U90 = j_read["90UpperLimit"]["p2_U90"].get<double>();
				}
				
				// Median
				double E0_counts_median = j_read["Median"]["E0_counts_median"].get<double>();
				double E0_counts_L68_sigma = j_read["Median"]["E0_counts_L68_sigma"].get<double>();
				double E0_counts_U68_sigma = j_read["Median"]["E0_counts_U68_sigma"].get<double>();
				double p0_median = j_read["Median"]["p0_median"].get<double>();
				double p0_L68_sigma = j_read["Median"]["p0_L68_sigma"].get<double>();
				double p0_U68_sigma = j_read["Median"]["p0_U68_sigma"].get<double>();
				double p1_median=0, p2_median=0;
				double p1_L68_sigma=0, p1_U68_sigma=0, p2_L68_sigma=0, p2_U68_sigma=0;
				if ( polDegree_BKG==1 ) {
					p1_median = j_read["Median"]["p1_median"].get<double>();
					p1_L68_sigma = j_read["Median"]["p1_L68_sigma"].get<double>();
					p1_U68_sigma = j_read["Median"]["p1_U68_sigma"].get<double>();
				}
				if ( polDegree_BKG==2 ) {
					p1_median = j_read["Median"]["p1_median"].get<double>();
					p1_L68_sigma = j_read["Median"]["p1_L68_sigma"].get<double>();
					p1_U68_sigma = j_read["Median"]["p1_U68_sigma"].get<double>();
					p2_median = j_read["Median"]["p2_median"].get<double>();
					p2_L68_sigma = j_read["Median"]["p2_L68_sigma"].get<double>();
					p2_U68_sigma = j_read["Median"]["p2_U68_sigma"].get<double>();
				}
				
				file1 << i << "\t\t" << k_GammaArrayIndex << "\t\t" << outputk_GammaPosition << "\t\t" << polDegree_BKG << "\t\t" << windowLeftEdge_xL 
				<< "\t\t" << windowRightEdge_xR << "\t\t" << windowWidth << std::endl;
				
				file2 << i << std::setw(15) << E0_height_MIN << std::setw(15) << E0_height_MAX << std::setw(15) << p0_MIN << std::setw(15) << p0_MAX 
				<< std::setw(15) << p1_MIN << std::setw(15) << p1_MAX << std::setw(15) << p2_MIN << std::setw(15) << p2_MAX << std::endl;
				
				file3 << i << std::setw(15) << E0_counts_GM << std::setw(15) << E0_counts_sigma_GM << std::setw(15) << p0_GM << std::setw(15) << p0_sigma_GM 
				<< std::setw(15) << p1_GM << std::setw(15) << p1_sigma_GM << std::setw(15) << p2_GM << std::setw(15) << p2_sigma_GM << std::endl;
				
				file4 << i << std::setw(15) << E0_counts_M << std::setw(15) << E0_counts_sigma_M << std::setw(15) << p0_M << std::setw(15) << p0_sigma_M 
				<< std::setw(15) << p1_M << std::setw(15) << p1_sigma_M << std::setw(15) << p2_M << std::setw(15) << p2_sigma_M << std::endl;
				
				file5 << i << std::setw(15) << E0_counts_L68 << std::setw(15) << E0_counts_U68 << std::setw(15) << p0_L68 << std::setw(15) << p0_U68 
				<< std::setw(15) << p1_L68 << std::setw(15) << p1_U68 << std::setw(15) << p2_L68 << std::setw(15) << p2_U68 << std::endl;
				
				file6 << i << std::setw(15) << E0_counts_U90 << std::setw(14) << p0_U90 << std::setw(15) << p1_U90 << std::setw(15) << p2_U90 << std::endl;
				
				file7 << i << std::setw(15) << E0_counts_median << std::setw(14) << E0_counts_L68_sigma << std::setw(14) << E0_counts_U68_sigma << std::setw(14)
				<< p0_median << std::setw(15) << p0_L68_sigma << std::setw(15) << p0_U68_sigma << std::setw(15) << p1_median << std::setw(15) << 
				p1_L68_sigma << std::setw(15) << p1_U68_sigma << std::setw(15) << p2_median << std::setw(15) << p2_L68_sigma << std::setw(15) <<
				p2_U68_sigma << std::endl;
			} // stop else
		} // stop for
		
		file1.close();
		file2.close();
		file3.close();
		file4.close();
		file5.close();
		file6.close();
		file7.close();
		
		std::cout << "\033[1;31m -> files have been created\033[0m\n";
		
	} // stop ans=0

	return 0;
}