#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void MC_output(int E0, int i, int det, int phase, int norm, int PSD, int prior) {
	
	std::string filename;
	// read from JSON files
	if ( phase==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_coaxP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_BEGeP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_ConstantP/JsonFile" + to_string(E0) + ".json"; }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
						if ( det==0 ) { filename = "JsonFiles/53_93_coax_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==1 ) {
						if ( det==0 ) { filename = "JsonFiles/53_93_coax_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
						if ( det==0 ) { filename = "JsonFiles/53_93_coax_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_coax_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_coaxP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_coax_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_BEGeP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_coax_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_ConstantP/JsonFile" + to_string(E0) + ".json"; }
				}
			}
		}
	}
	if ( phase==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==2 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_PSD_ICP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_PSD_ICP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_PSD_ICP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==3 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_coaxP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_BEGeP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==2 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_ICP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_ICP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_ICP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==3 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_ConstantP/JsonFile" + to_string(E0) + ".json"; }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_PSD_coaxP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_PSD_BEGeP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==2 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_PSD_ICP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_PSD_ICP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_PSD_ICP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==3 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_PSD_ConstantP/JsonFile" + to_string(E0) + ".json"; }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_coaxP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_coaxP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_BEGeP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_BEGeP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==2 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_ICP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_ICP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_ICP/JsonFile" + to_string(E0) + ".json"; }
				}
				if ( prior==3 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_ConstantP/JsonFile" + to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_ConstantP/JsonFile" + to_string(E0) + ".json"; }
				}
			}
		}
	}
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
	if ( phase==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_NORM_coax_PSD_coaxP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_NORM_BEGe_PSD_coaxP/MC%i_U90.txt", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_NORM_coax_PSD_BEGeP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_NORM_BEGe_PSD_BEGeP/MC%i_U90.txt", E0); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_NORM_coax_PSD_ConstantP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_NORM_BEGe_PSD_ConstantP/MC%i_U90.txt", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_NORM_coax_coaxP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_NORM_BEGe_coaxP/MC%i_U90.txt", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_NORM_coax_BEGeP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_NORM_BEGe_BEGeP/MC%i_U90.txt", E0); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_NORM_coax_ConstantP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_NORM_BEGe_ConstantP/MC%i_U90.txt", E0); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
						if ( det==0 ) { sprintf(name, "MC_output/53_93_coax_PSD_coaxP/MC%i_U90.txt", E0); }
						if ( det==1 ) { sprintf(name, "MC_output/53_93_BEGe_PSD_coaxP/MC%i_U90.txt", E0); }
				}
				if ( prior==1 ) {
						if ( det==0 ) { sprintf(name, "MC_output/53_93_coax_PSD_BEGeP/MC%i_U90.txt", E0); }
						if ( det==1 ) { sprintf(name, "MC_output/53_93_BEGe_PSD_BEGeP/MC%i_U90.txt", E0); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
						if ( det==0 ) { sprintf(name, "MC_output/53_93_coax_PSD_ConstantP/MC%i_U90.txt", E0); }
						if ( det==1 ) { sprintf(name, "MC_output/53_93_BEGe_PSD_ConstantP/MC%i_U90.txt", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_coax_coaxP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_BEGe_coaxP/MC%i_U90.txt", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_coax_BEGeP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_BEGe_BEGeP/MC%i_U90.txt", E0); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_93_coax_ConstantP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_93_BEGe_ConstantP/MC%i_U90.txt", E0); }
				}
			}
		}
	}
	if ( phase==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_NORM_coax_PSD_coaxP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_NORM_BEGe_PSD_coaxP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_NORM_IC_PSD_coaxP/MC%i_U90.txt", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_NORM_coax_PSD_BEGeP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_NORM_BEGe_PSD_BEGeP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_NORM_IC_PSD_BEGeP/MC%i_U90.txt", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_NORM_coax_PSD_ICP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_NORM_BEGe_PSD_ICP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_NORM_IC_PSD_ICP/MC%i_U90.txt", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_NORM_coax_PSD_ConstantP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_NORM_BEGe_PSD_ConstantP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_NORM_IC_PSD_ConstantP/MC%i_U90.txt", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_NORM_coax_coaxP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_NORM_BEGe_coaxP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_NORM_IC_coaxP/MC%i_U90.txt", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_NORM_coax_BEGeP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_NORM_BEGe_BEGeP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_NORM_IC_BEGeP/MC%i_U90.txt", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_NORM_coax_ICP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_NORM_BEGe_ICP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_NORM_IC_ICP/MC%i_U90.txt", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_NORM_coax_ConstantP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_NORM_BEGe_ConstantP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_NORM_IC_ConstantP/MC%i_U90.txt", E0); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_coax_PSD_coaxP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_BEGe_PSD_coaxP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_IC_PSD_coaxP/MC%i_U90.txt", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_coax_PSD_BEGeP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_BEGe_PSD_BEGeP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_IC_PSD_BEGeP/MC%i_U90.txt", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_coax_PSD_ICP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_BEGe_PSD_ICP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_IC_PSD_ICP/MC%i_U90.txt", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_coax_PSD_ConstantP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_BEGe_PSD_ConstantP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_IC_PSD_ConstantP/MC%i_U90.txt", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_coax_coaxP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_BEGe_coaxP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_IC_coaxP/MC%i_U90.txt", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_coax_BEGeP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_BEGe_BEGeP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_IC_BEGeP/MC%i_U90.txt", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_coax_ICP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_BEGe_ICP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_IC_ICP/MC%i_U90.txt", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MC_output/53_114_coax_ConstantP/MC%i_U90.txt", E0); }
					if ( det==1 ) { sprintf(name, "MC_output/53_114_BEGe_ConstantP/MC%i_U90.txt", E0); }
					if ( det==2 ) { sprintf(name, "MC_output/53_114_IC_ConstantP/MC%i_U90.txt", E0); }
				}
			}
		}
	}
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
	
	std::cout << "\t\t i-th simulation = " << i << std::endl;
}
