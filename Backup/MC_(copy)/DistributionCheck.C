#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int DistributionCheck(int E0, int det, int norm, int phase, int PSD, int prior) {

	std::fstream file_out;
	file_out.open("shape_posterior.txt", std::ios::out);
	
	TFile *file_root = new TFile("chi2_distribution.root", "RECREATE");
	TH1F *chi2_p0 = new TH1F("chi2_p0", "chi2_p0", 1e7, -1, 1e7);
	TH1F *chi2_p1 = new TH1F("chi2_p1", "chi2_p1", 1e7, -1, 1e7);
	TH1F *chi2_p2 = new TH1F("chi2_p2", "chi2_p2", 1e7, -1, 1e7);
	TH1F *chi2_E0 = new TH1F("chi2_E0", "chi2_E0", 1e7, -1, 1e7);
	TH1F *chi2_E1 = new TH1F("chi2_E1", "chi2_E1", 1e7, -1, 1e7);
	TH1F *chi2_E2 = new TH1F("chi2_E2", "chi2_E2", 1e7, -1, 1e7);	

	char name_file[300];
	if ( phase==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_NORM_coax_PSD_coaxP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_NORM_BEGe_PSD_coaxP/JsonFile%i.json", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_NORM_coax_PSD_BEGeP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_NORM_BEGe_PSD_BEGeP/JsonFile%i.json", E0); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_NORM_coax_PSD_ConstantP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_NORM_BEGe_PSD_ConstantP/JsonFile%i.json", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_NORM_coax_coaxP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_NORM_BEGe_coaxP/JsonFile%i.json", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_NORM_coax_BEGeP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_NORM_BEGe_BEGeP/JsonFile%i.json", E0); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_NORM_coax_ConstantP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_NORM_BEGe_ConstantP/JsonFile%i.json", E0); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
						if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_coax_PSD_coaxP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_BEGe_PSD_coaxP/JsonFile%i.json", E0); }
				}
				if ( prior==1 ) {
						if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_coax_PSD_BEGeP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_BEGe_PSD_BEGeP/JsonFile%i.json", E0); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
						if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_coax_PSD_ConstantP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_BEGe_PSD_ConstantP/JsonFile%i.json", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_coax_coaxP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_BEGe_coaxP/JsonFile%i.json", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_coax_BEGeP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_BEGe_BEGeP/JsonFile%i.json", E0); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_93_coax_ConstantP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_93_BEGe_ConstantP/JsonFile%i.json", E0); }
				}
			}
		}
	}
	if ( phase==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_NORM_coax_PSD_coaxP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_NORM_BEGe_PSD_coaxP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_NORM_IC_PSD_coaxP/JsonFile%i.json", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_NORM_coax_PSD_BEGeP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_NORM_BEGe_PSD_BEGeP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_NORM_IC_PSD_BEGeP/JsonFile%i.json", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_NORM_coax_PSD_ICP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_NORM_BEGe_PSD_ICP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_NORM_IC_PSD_ICP/JsonFile%i.json", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_NORM_coax_PSD_ConstantP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_NORM_BEGe_PSD_ConstantP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_NORM_IC_PSD_ConstantP/JsonFile%i.json", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_NORM_coax_coaxP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_NORM_BEGe_coaxP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_NORM_IC_coaxP/JsonFile%i.json", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_NORM_coax_BEGeP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_NORM_BEGe_BEGeP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_NORM_IC_BEGeP/JsonFile%i.json", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_NORM_coax_ICP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_NORM_BEGe_ICP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_NORM_IC_ICP/JsonFile%i.json", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_NORM_coax_ConstantP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_NORM_BEGe_ConstantP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_NORM_IC_ConstantP/JsonFile%i.json", E0); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_coax_PSD_coaxP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_BEGe_PSD_coaxP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_IC_PSD_coaxP/JsonFile%i.json", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_coax_PSD_BEGeP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_BEGe_PSD_BEGeP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_IC_PSD_BEGeP/JsonFile%i.json", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_coax_PSD_ICP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_BEGe_PSD_ICP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_IC_PSD_ICP/JsonFile%i.json", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_coax_PSD_ConstantP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_BEGe_PSD_ConstantP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_IC_PSD_ConstantP/JsonFile%i.json", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_coax_coaxP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_BEGe_coaxP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_IC_coaxP/JsonFile%i.json", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_coax_BEGeP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_BEGe_BEGeP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_IC_BEGeP/JsonFile%i.json", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_coax_ICP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_BEGe_ICP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_IC_ICP/JsonFile%i.json", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name_file, "JsonFiles/53_114_coax_ConstantP/JsonFile%i.json", E0); }
					if ( det==1 ) { sprintf(name_file, "JsonFiles/53_114_BEGe_ConstantP/JsonFile%i.json", E0); }
					if ( det==2 ) { sprintf(name_file, "JsonFiles/53_114_IC_ConstantP/JsonFile%i.json", E0); }
				}
			}
		}
	}
	std::ifstream fileJSON(name_file);
	json j_read;
	fileJSON >> j_read;
	fileJSON.close();	
	
	int pol_degree = j_read["PeakSearch"]["polDegree_BKG"].get<int>();
	int outputK = j_read["PeakSearch"]["outputk_GammaPosition"].get<int>();
	char root_file[300];
	if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) { sprintf(root_file, "GausPol%i", pol_degree); }
	else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { sprintf(root_file, "GausPol%i_1Gamma", pol_degree); }
	else { sprintf(root_file, "GausPol%i_2Gamma", pol_degree); }
	
	char name[300];
	if ( phase==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_coax_PSD_coaxP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_BEGe_PSD_coaxP/%i.root", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_coax_PSD_BEGeP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_BEGe_PSD_BEGeP/%i.root", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_coax_PSD_ICP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_BEGe_PSD_ICP/%i.root", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_coax_PSD_ConstantP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_BEGe_PSD_ConstantP/%i.root", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_coax_coaxP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_BEGe_coaxP/%i.root", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_coax_BEGeP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_BEGe_BEGeP/%i.root", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_coax_ICP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_BEGe_ICP/%i.root", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_coax_ConstantP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_NORM_BEGe_ConstantP/%i.root", E0); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
						if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_coax_PSD_coaxP/%i.root", E0); }
						if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_BEGe_PSD_coaxP/%i.root", E0); }
				}
				if ( prior==1 ) {
						if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_coax_PSD_BEGeP/%i.root", E0); }
						if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_BEGe_PSD_BEGeP/%i.root", E0); }
				}
				if ( prior==2 ) {
						if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_coax_PSD_ICP/%i.root", E0); }
						if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_BEGe_PSD_ICP/%i.root", E0); }
				}
				if ( prior==3 ) {
						if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_coax_PSD_ConstantP/%i.root", E0); }
						if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_BEGe_PSD_ConstantP/%i.root", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_coax_coaxP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_BEGe_coaxP/%i.root", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_coax_BEGeP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_BEGe_BEGeP/%i.root", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_coax_ICP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_BEGe_ICP/%i.root", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_93_coax_ConstantP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_93_BEGe_ConstantP/%i.root", E0); }
				}
			}
		}
	}
	if ( phase==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_coax_PSD_coaxP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_BEGe_PSD_coaxP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_IC_PSD_coaxP/%i.root", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_coax_PSD_BEGeP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_BEGe_PSD_BEGeP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_IC_PSD_BEGeP/%i.root", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_coax_PSD_ICP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_BEGe_PSD_ICP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_IC_PSD_ICP/%i.root", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_coax_PSD_ConstantP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_BEGe_PSD_ConstantP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_IC_PSD_ConstantP/%i.root", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_coax_coaxP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_BEGe_coaxP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_IC_coaxP/%i.root", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_coax_BEGeP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_BEGe_BEGeP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_IC_BEGeP/%i.root", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_coax_ICP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_BEGe_ICP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_IC_ICP/%i.root", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_coax_ConstantP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_BEGe_ConstantP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_NORM_IC_ConstantP/%i.root", E0); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_coax_PSD_coaxP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_BEGe_PSD_coaxP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_IC_PSD_coaxP/%i.root", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_coax_PSD_BEGeP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_BEGe_PSD_BEGeP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_IC_PSD_BEGeP/%i.root", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_coax_PSD_ICP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_BEGe_PSD_ICP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_IC_PSD_ICP/%i.root", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_coax_PSD_ConstantP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_BEGe_PSD_ConstantP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_IC_PSD_ConstantP/%i.root", E0); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_coax_coaxP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_BEGe_coaxP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_IC_coaxP/%i.root", E0); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_coax_BEGeP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_BEGe_BEGeP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_IC_BEGeP/%i.root", E0); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_coax_ICP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_BEGe_ICP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_IC_ICP/%i.root", E0); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(name, "MarginalizedROOT/53_114_coax_ConstantP/%i.root", E0); }
					if ( det==1 ) { sprintf(name, "MarginalizedROOT/53_114_BEGe_ConstantP/%i.root", E0); }
					if ( det==2 ) { sprintf(name, "MarginalizedROOT/53_114_IC_ConstantP/%i.root", E0); }
				}
			}
		}
	}	
	TFile *file = new TFile(name);
		
	// p0 marginalzied posterior histogram
	char histo_p0[200];
	sprintf(histo_p0, "h1_%i%s_parameter_p0", E0, root_file);
	TH1D *hp0 = (TH1D*) file->Get(histo_p0);
		
	// p1 marginalzied posterior histogram
	char histo_p1[200];
	sprintf(histo_p1, "h1_%i%s_parameter_p1", E0, root_file);
	TH1D *hp1 = new TH1D();
	if ( pol_degree==1 ) {
		hp1 = (TH1D*) file->Get(histo_p1);
	}
		
	// p2 marginalzied posterior histogram
	char histo_p2[200];
	sprintf(histo_p2, "h1_%i%s_parameter_p2", E0, root_file);
	TH1D *hp2 = new TH1D();
	if ( pol_degree==2 ) {
		hp1 = (TH1D*) file->Get(histo_p1);
		hp2 = (TH1D*) file->Get(histo_p2);
	}
		
	// E0, E1, E2 marginalized posterior histograms
	char histo_E0[200];
	sprintf(histo_E0, "h1_%i%s_parameter_E0_height", E0, root_file);
	TH1D *hE0 = (TH1D*) file->Get(histo_E0);
	// 1 peak
	char histo_E1[200];
	sprintf(histo_E1, "h1_%i%s_parameter_E1_height", E0, root_file);
	TH1D *hE1 = new TH1D();
	if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
		hE1 = (TH1D*) file->Get(histo_E1);
	}
	// 2 peaks
	char histo_E2[200];
	sprintf(histo_E2, "h1_%i%s_parameter_E2_height", E0, root_file);
	TH1D *hE2 = new TH1D();
	if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		hE1 = (TH1D*) file->Get(histo_E1);
		hE2 = (TH1D*) file->Get(histo_E2);
	}
	
	//==========================================================================================================
	// study of the shape of the distribution
	double E0_BinMin=0, E1_BinMin=0, E2_BinMin=0, p0_BinMin=0, p1_BinMin=0, p2_BinMin=0;
	double E0_BinMax=0, E1_BinMax=0, E2_BinMax=0, p0_BinMax=0, p1_BinMax=0, p2_BinMax=0;
	E0_BinMin = j_read["ParameterRange"]["E0_counts_MIN"].get<double>();
	E0_BinMax = j_read["ParameterRange"]["E0_counts_MAX"].get<double>();
	p0_BinMin = j_read["ParameterRange"]["p0_MIN"].get<double>();
	p0_BinMax = j_read["ParameterRange"]["p0_MAX"].get<double>();
	if ( pol_degree==1 ) { 
		p1_BinMin = j_read["ParameterRange"]["p1_MIN"].get<double>();
		p1_BinMax = j_read["ParameterRange"]["p1_MAX"].get<double>();
	}
	if ( pol_degree==2 ) { 
		p1_BinMin = j_read["ParameterRange"]["p1_MIN"].get<double>();
		p1_BinMax = j_read["ParameterRange"]["p1_MAX"].get<double>();
		p2_BinMin = j_read["ParameterRange"]["p2_MIN"].get<double>();
		p2_BinMax = j_read["ParameterRange"]["p2_MAX"].get<double>();
	}
	if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
		E1_BinMin = j_read["ParameterRange"]["E1_counts_MIN"].get<double>();
		E1_BinMax = j_read["ParameterRange"]["E1_counts_MAX"].get<double>();
	}
	if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		E1_BinMin = j_read["ParameterRange"]["E1_counts_MIN"].get<double>();
		E1_BinMax = j_read["ParameterRange"]["E1_counts_MAX"].get<double>();
		E2_BinMin = j_read["ParameterRange"]["E2_counts_MIN"].get<double>();
		E2_BinMax = j_read["ParameterRange"]["E2_counts_MAX"].get<double>();
	}
	
	double E0_chi2=0, E1_chi2=0, E2_chi2=0, p0_chi2=0, p1_chi2=0, p2_chi2=0; 
	TF1 *f_E0 = new TF1("f_E0", "pol0", E0_BinMin, E0_BinMax);
	TF1 *f_p0 = new TF1("f_p0", "pol0", p0_BinMin, p0_BinMax);
	TF1 *f_p1 = new TF1("f_p1", "pol0", p1_BinMin, p1_BinMax);
	TF1 *f_p2 = new TF1("f_p2", "pol0", p2_BinMin, p2_BinMax);
	TF1 *f_E1 = new TF1("f_E1", "pol0", E1_BinMin, E1_BinMax);
	TF1 *f_E2 = new TF1("f_E2", "pol0", E2_BinMin, E2_BinMax);
	
	hE0->Fit("f_E0", "RQNO");
	E0_chi2 = f_E0->GetChisquare();
	hp0->Fit("f_p0", "RQNO");
	p0_chi2 = f_p0->GetChisquare();
	if ( pol_degree==1 ) { 
		hp1->Fit("f_p1", "RQNO");
		p1_chi2 = f_p1->GetChisquare();
	}
	if ( pol_degree==2 ) { 
		hp1->Fit("f_p1", "RQNO");
		hp2->Fit("f_p2", "RQNO");
		p1_chi2 = f_p1->GetChisquare();
		p2_chi2 = f_p2->GetChisquare();
	}
	if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
		hE1->Fit("f_E1", "RQNO");
		E1_chi2 = f_E1->GetChisquare();
	}
	if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		hE1->Fit("f_E1", "RQNO");
		hE2->Fit("f_E2", "RQNO");
		E1_chi2 = f_E1->GetChisquare();
		E2_chi2 = f_E2->GetChisquare();
	}
	
	int ck0=0, ck1=0, ck2=0, ckE0=0, ckE1=0, ckE2=0;
	if ( p0_chi2<1e4 && p0_chi2!=0 ) ck0=1;
	if ( p1_chi2<1e4 && p1_chi2!=0 ) ck1=1;
	if ( p2_chi2<1e4 && p2_chi2!=0 ) ck2=1;
	if ( E0_chi2<1e4 && E0_chi2!=0 ) ckE0=1;
	if ( E1_chi2<1e4 && E1_chi2!=0 ) ckE1=1; 
	if ( E2_chi2<1e4 && E2_chi2!=0 ) ckE2=1;
	
	chi2_p0->Fill(p0_chi2);
	chi2_p1->Fill(p1_chi2);
	chi2_p2->Fill(p2_chi2);
	chi2_E0->Fill(E0_chi2);
	chi2_E1->Fill(E1_chi2);
	chi2_E2->Fill(E2_chi2);
		
	file_out << ck0 << "\n" << ck1 << "\n" << ck2 << "\n" << ckE0 << "\n" << ckE1 << "\n" << ckE2 << std::endl;
	
	file_out.close();
	file_root->WriteTObject(chi2_p0);
	file_root->WriteTObject(chi2_p1);
	file_root->WriteTObject(chi2_p2);
	file_root->WriteTObject(chi2_E0);
	file_root->WriteTObject(chi2_E1);
	file_root->WriteTObject(chi2_E2);
	file_root->Close();
	
	return 0;
}
