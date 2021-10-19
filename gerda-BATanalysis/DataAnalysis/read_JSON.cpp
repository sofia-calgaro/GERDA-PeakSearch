#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {

	int det, choice;
	std::cout << " Coax (0), BEGe (1) or IC (2)? ";
	std::cin >> det;
	std::cout << "\n * Press:\n\t - 0 if you want to create files,\n\t - 1 if you want to print one E0,\n\t - 2 if you want to print more E0\n -> ";
	std::cin >> choice;
	
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------- CREATE FILES
	if ( choice == 0 ) {
		const int E0_min = 60;
		const int E0_max = 1000;
		/*int E0_min, E0_max;
		std::cout << "\n * Select the interval [E0_min;E0_max]:\n\t - choose E0_min: ";
		std::cin >> E0_min;
		std::cout << "\t - choose E0_max: ";
		std::cin >> E0_max;*/
		
		int run;
		std::cout << "\n * Run: 53-93 (0) or 53-114 (1)? ";
		std::cin >> run;
		int norm;
		std::cout << " * Normalized (0) or not (1)? ";
		std::cin >> norm;
		int PSD;
		std::cout << " * Only PSD (0) or everything (1)? ";
		std::cin >> PSD;
		
		std::string filename1, filename2, filename3, filename4, filename5, filename6, filename7, filename8, filename9, filename10, filename11, filename12;
		
		// ===============================================================================================================
		// Peak Search
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename1 = "ReadJSON/53_93_NORM_coax_PSD/PeakSearch.txt"; }
					if ( det==1 ) { filename1 = "ReadJSON/53_93_NORM_BEGe_PSD/PeakSearch.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename1 = "ReadJSON/53_93_NORM_coax/PeakSearch.txt"; }
					if ( det==1 ) { filename1 = "ReadJSON/53_93_NORM_BEGe/PeakSearch.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename1 = "ReadJSON/53_93_coax_PSD/PeakSearch.txt"; }
					if ( det==1 ) { filename1 = "ReadJSON/53_93_BEGe_PSD/PeakSearch.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename1 = "ReadJSON/53_93_coax/PeakSearch.txt"; }
					if ( det==1 ) { filename1 = "ReadJSON/53_93_BEGe/PeakSearch.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename1 = "ReadJSON/53_114_NORM_coax_PSD/PeakSearch.txt"; }
					if ( det==1 ) { filename1 = "ReadJSON/53_114_NORM_BEGe_PSD/PeakSearch.txt"; }
					if ( det==2 ) { filename1 = "ReadJSON/53_114_NORM_IC_PSD/PeakSearch.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename1 = "ReadJSON/53_114_NORM_coax/PeakSearch.txt"; }
					if ( det==1 ) { filename1 = "ReadJSON/53_114_NORM_BEGe/PeakSearch.txt"; }
					if ( det==2 ) { filename1 = "ReadJSON/53_114_NORM_IC/PeakSearch.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename1 = "ReadJSON/53_114_coax_PSD/PeakSearch.txt"; }
					if ( det==1 ) { filename1 = "ReadJSON/53_114_BEGe_PSD/PeakSearch.txt"; }
					if ( det==2 ) { filename1 = "ReadJSON/53_114_IC_PSD/PeakSearch.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename1 = "ReadJSON/53_114_coax/PeakSearch.txt"; }
					if ( det==1 ) { filename1 = "ReadJSON/53_114_BEGe/PeakSearch.txt"; }
					if ( det==2 ) { filename1 = "ReadJSON/53_114_IC/PeakSearch.txt"; }
				}
			}
		}
		std::ofstream file1(filename1);
		
		// ===============================================================================================================
		// Parameter Ranges
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename2 = "ReadJSON/53_93_NORM_coax_PSD/ParameterRanges.txt"; }
					if ( det==1 ) { filename2 = "ReadJSON/53_93_NORM_BEGe_PSD/ParameterRanges.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename2 = "ReadJSON/53_93_NORM_coax/ParameterRanges.txt"; }
					if ( det==1 ) { filename2 = "ReadJSON/53_93_NORM_BEGe/ParameterRanges.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename2 = "ReadJSON/53_93_coax_PSD/ParameterRanges.txt"; }
					if ( det==1 ) { filename2 = "ReadJSON/53_93_BEGe_PSD/ParameterRanges.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename2 = "ReadJSON/53_93_coax/ParameterRanges.txt"; }
					if ( det==1 ) { filename2 = "ReadJSON/53_93_BEGe/ParameterRanges.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename2 = "ReadJSON/53_114_NORM_coax_PSD/ParameterRanges.txt"; }
					if ( det==1 ) { filename2 = "ReadJSON/53_114_NORM_BEGe_PSD/ParameterRanges.txt"; }
					if ( det==2 ) { filename2 = "ReadJSON/53_114_NORM_IC_PSD/ParameterRanges.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename2 = "ReadJSON/53_114_NORM_coax/ParameterRanges.txt"; }
					if ( det==1 ) { filename2 = "ReadJSON/53_114_NORM_BEGe/ParameterRanges.txt"; }
					if ( det==2 ) { filename2 = "ReadJSON/53_114_NORM_IC/ParameterRanges.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename2 = "ReadJSON/53_114_coax_PSD/ParameterRanges.txt"; }
					if ( det==1 ) { filename2 = "ReadJSON/53_114_BEGe_PSD/ParameterRanges.txt"; }
					if ( det==2 ) { filename2 = "ReadJSON/53_114_IC_PSD/ParameterRanges.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename2 = "ReadJSON/53_114_coax/ParameterRanges.txt"; }
					if ( det==1 ) { filename2 = "ReadJSON/53_114_BEGe/ParameterRanges.txt"; }
					if ( det==2 ) { filename2 = "ReadJSON/53_114_IC/ParameterRanges.txt"; }
				}
			}
		}
		
		std::ofstream file2(filename2);
		
		// ===============================================================================================================
		// Global Mode
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename3 = "ReadJSON/53_93_NORM_coax_PSD/GlobalMode.txt"; }
					if ( det==1 ) { filename3 = "ReadJSON/53_93_NORM_BEGe_PSD/GlobalMode.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename3 = "ReadJSON/53_93_NORM_coax/GlobalMode.txt"; }
					if ( det==1 ) { filename3 = "ReadJSON/53_93_NORM_BEGe/GlobalMode.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename3 = "ReadJSON/53_93_coax_PSD/GlobalMode.txt"; }
					if ( det==1 ) { filename3 = "ReadJSON/53_93_BEGe_PSD/GlobalMode.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename3 = "ReadJSON/53_93_coax/GlobalMode.txt"; }
					if ( det==1 ) { filename3 = "ReadJSON/53_93_BEGe/GlobalMode.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename3 = "ReadJSON/53_114_NORM_coax_PSD/GlobalMode.txt"; }
					if ( det==1 ) { filename3 = "ReadJSON/53_114_NORM_BEGe_PSD/GlobalMode.txt"; }
					if ( det==2 ) { filename3 = "ReadJSON/53_114_NORM_IC_PSD/GlobalMode.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename3 = "ReadJSON/53_114_NORM_coax/GlobalMode.txt"; }
					if ( det==1 ) { filename3 = "ReadJSON/53_114_NORM_BEGe/GlobalMode.txt"; }
					if ( det==2 ) { filename3 = "ReadJSON/53_114_NORM_IC/GlobalMode.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename3 = "ReadJSON/53_114_coax_PSD/GlobalMode.txt"; }
					if ( det==1 ) { filename3 = "ReadJSON/53_114_BEGe_PSD/GlobalMode.txt"; }
					if ( det==2 ) { filename3 = "ReadJSON/53_114_IC_PSD/GlobalMode.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename3 = "ReadJSON/53_114_coax/GlobalMode.txt"; }
					if ( det==1 ) { filename3 = "ReadJSON/53_114_BEGe/GlobalMode.txt"; }
					if ( det==2 ) { filename3 = "ReadJSON/53_114_IC/GlobalMode.txt"; }
				}
			}
		}
		std::ofstream file3(filename3);
		
		// ===============================================================================================================
		// Mean
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename4 = "ReadJSON/53_93_NORM_coax_PSD/Mean.txt"; }
					if ( det==1 ) { filename4 = "ReadJSON/53_93_NORM_BEGe_PSD/Mean.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename4 = "ReadJSON/53_93_NORM_coax/Mean.txt"; }
					if ( det==1 ) { filename4 = "ReadJSON/53_93_NORM_BEGe/Mean.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename4 = "ReadJSON/53_93_coax_PSD/Mean.txt"; }
					if ( det==1 ) { filename4 = "ReadJSON/53_93_BEGe_PSD/Mean.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename4 = "ReadJSON/53_93_coax/Mean.txt"; }
					if ( det==1 ) { filename4 = "ReadJSON/53_93_BEGe/Mean.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename4 = "ReadJSON/53_114_NORM_coax_PSD/Mean.txt"; }
					if ( det==1 ) { filename4 = "ReadJSON/53_114_NORM_BEGe_PSD/Mean.txt"; }
					if ( det==2 ) { filename4 = "ReadJSON/53_114_NORM_IC_PSD/Mean.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename4 = "ReadJSON/53_114_NORM_coax/Mean.txt"; }
					if ( det==1 ) { filename4 = "ReadJSON/53_114_NORM_BEGe/Mean.txt"; }
					if ( det==2 ) { filename4 = "ReadJSON/53_114_NORM_IC/Mean.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename4 = "ReadJSON/53_114_coax_PSD/Mean.txt"; }
					if ( det==1 ) { filename4 = "ReadJSON/53_114_BEGe_PSD/Mean.txt"; }
					if ( det==2 ) { filename4 = "ReadJSON/53_114_IC_PSD/Mean.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename4 = "ReadJSON/53_114_coax/Mean.txt"; }
					if ( det==1 ) { filename4 = "ReadJSON/53_114_BEGe/Mean.txt"; }
					if ( det==2 ) { filename4 = "ReadJSON/53_114_IC/Mean.txt"; }
				}
			}
		}
		std::ofstream file4(filename4);
		
		// ===============================================================================================================
		// 68% Quantile
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename5 = "ReadJSON/53_93_NORM_coax_PSD/68Quantile.txt"; }
					if ( det==1 ) { filename5 = "ReadJSON/53_93_NORM_BEGe_PSD/68Quantile.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename5 = "ReadJSON/53_93_NORM_coax/68Quantile.txt"; }
					if ( det==1 ) { filename5 = "ReadJSON/53_93_NORM_BEGe/68Quantile.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename5 = "ReadJSON/53_93_coax_PSD/68Quantile.txt"; }
					if ( det==1 ) { filename5 = "ReadJSON/53_93_BEGe_PSD/68Quantile.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename5 = "ReadJSON/53_93_coax/68Quantile.txt"; }
					if ( det==1 ) { filename5 = "ReadJSON/53_93_BEGe/68Quantile.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename5 = "ReadJSON/53_114_NORM_coax_PSD/68Quantile.txt"; }
					if ( det==1 ) { filename5 = "ReadJSON/53_114_NORM_BEGe_PSD/68Quantile.txt"; }
					if ( det==2 ) { filename5 = "ReadJSON/53_114_NORM_IC_PSD/68Quantile.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename5 = "ReadJSON/53_114_NORM_coax/68Quantile.txt"; }
					if ( det==1 ) { filename5 = "ReadJSON/53_114_NORM_BEGe/68Quantile.txt"; }
					if ( det==2 ) { filename5 = "ReadJSON/53_114_NORM_IC/68Quantile.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename5 = "ReadJSON/53_114_coax_PSD/68Quantile.txt"; }
					if ( det==1 ) { filename5 = "ReadJSON/53_114_BEGe_PSD/68Quantile.txt"; }
					if ( det==2 ) { filename5 = "ReadJSON/53_114_IC_PSD/68Quantile.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename5 = "ReadJSON/53_114_coax/68Quantile.txt"; }
					if ( det==1 ) { filename5 = "ReadJSON/53_114_BEGe/68Quantile.txt"; }
					if ( det==2 ) { filename5 = "ReadJSON/53_114_IC/68Quantile.txt"; }
				}
			}
		}
		std::ofstream file5(filename5);
		
		// ===============================================================================================================
		// 90% Upper Limit
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename6 = "ReadJSON/53_93_NORM_coax_PSD/90UpperLimit.txt"; }
					if ( det==1 ) { filename6 = "ReadJSON/53_93_NORM_BEGe_PSD/90UpperLimit.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename6 = "ReadJSON/53_93_NORM_coax/90UpperLimit.txt"; }
					if ( det==1 ) { filename6 = "ReadJSON/53_93_NORM_BEGe/90UpperLimit.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename6 = "ReadJSON/53_93_coax_PSD/90UpperLimit.txt"; }
					if ( det==1 ) { filename6 = "ReadJSON/53_93_BEGe_PSD/90UpperLimit.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename6 = "ReadJSON/53_93_coax/90UpperLimit.txt"; }
					if ( det==1 ) { filename6 = "ReadJSON/53_93_BEGe/90UpperLimit.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename6 = "ReadJSON/53_114_NORM_coax_PSD/90UpperLimit.txt"; }
					if ( det==1 ) { filename6 = "ReadJSON/53_114_NORM_BEGe_PSD/90UpperLimit.txt"; }
					if ( det==2 ) { filename6 = "ReadJSON/53_114_NORM_IC_PSD/90UpperLimit.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename6 = "ReadJSON/53_114_NORM_coax/90UpperLimit.txt"; }
					if ( det==1 ) { filename6 = "ReadJSON/53_114_NORM_BEGe/90UpperLimit.txt"; }
					if ( det==2 ) { filename6 = "ReadJSON/53_114_NORM_IC/90UpperLimit.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename6 = "ReadJSON/53_114_coax_PSD/90UpperLimit.txt"; }
					if ( det==1 ) { filename6 = "ReadJSON/53_114_BEGe_PSD/90UpperLimit.txt"; }
					if ( det==2 ) { filename6 = "ReadJSON/53_114_IC_PSD/90UpperLimit.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename6 = "ReadJSON/53_114_coax/90UpperLimit.txt"; }
					if ( det==1 ) { filename6 = "ReadJSON/53_114_BEGe/90UpperLimit.txt"; }
					if ( det==2 ) { filename6 = "ReadJSON/53_114_IC/90UpperLimit.txt"; }
				}
			}
		}
		std::ofstream file6(filename6);
		
		// ===============================================================================================================
		// Median
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename7 = "ReadJSON/53_93_NORM_coax_PSD/Median.txt"; }
					if ( det==1 ) { filename7 = "ReadJSON/53_93_NORM_BEGe_PSD/Median.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename7 = "ReadJSON/53_93_NORM_coax/Median.txt"; }
					if ( det==1 ) { filename7 = "ReadJSON/53_93_NORM_BEGe/Median.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename7 = "ReadJSON/53_93_coax_PSD/Median.txt"; }
					if ( det==1 ) { filename7 = "ReadJSON/53_93_BEGe_PSD/Median.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename7 = "ReadJSON/53_93_coax/Median.txt"; }
					if ( det==1 ) { filename7 = "ReadJSON/53_93_BEGe/Median.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename7 = "ReadJSON/53_114_NORM_coax_PSD/Median.txt"; }
					if ( det==1 ) { filename7 = "ReadJSON/53_114_NORM_BEGe_PSD/Median.txt"; }
					if ( det==2 ) { filename7 = "ReadJSON/53_114_NORM_IC_PSD/Median.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename7 = "ReadJSON/53_114_NORM_coax/Median.txt"; }
					if ( det==1 ) { filename7 = "ReadJSON/53_114_NORM_BEGe/Median.txt"; }
					if ( det==2 ) { filename7 = "ReadJSON/53_114_NORM_IC/Median.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename7 = "ReadJSON/53_114_coax_PSD/Median.txt"; }
					if ( det==1 ) { filename7 = "ReadJSON/53_114_BEGe_PSD/Median.txt"; }
					if ( det==2 ) { filename7 = "ReadJSON/53_114_IC_PSD/Median.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename7 = "ReadJSON/53_114_coax/Median.txt"; }
					if ( det==1 ) { filename7 = "ReadJSON/53_114_BEGe/Median.txt"; }
					if ( det==2 ) { filename7 = "ReadJSON/53_114_IC/Median.txt"; }
				}
			}
		}
		std::ofstream file7(filename7);
		
		// ===============================================================================================================
		// p0 VS E0
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename8 = "ReadJSON/53_93_NORM_coax_PSD/p0_VS_E0.txt"; }
					if ( det==1 ) { filename8 = "ReadJSON/53_93_NORM_BEGe_PSD/p0_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename8 = "ReadJSON/53_93_NORM_coax/p0_VS_E0.txt"; }
					if ( det==1 ) { filename8 = "ReadJSON/53_93_NORM_BEGe/p0_VS_E0.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename8 = "ReadJSON/53_93_coax_PSD/p0_VS_E0.txt"; }
					if ( det==1 ) { filename8 = "ReadJSON/53_93_BEGe_PSD/p0_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename8 = "ReadJSON/53_93_coax/p0_VS_E0.txt"; }
					if ( det==1 ) { filename8 = "ReadJSON/53_93_BEGe/p0_VS_E0.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename8 = "ReadJSON/53_114_NORM_coax_PSD/p0_VS_E0.txt"; }
					if ( det==1 ) { filename8 = "ReadJSON/53_114_NORM_BEGe_PSD/p0_VS_E0.txt"; }
					if ( det==2 ) { filename8 = "ReadJSON/53_114_NORM_IC_PSD/p0_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename8 = "ReadJSON/53_114_NORM_coax/p0_VS_E0.txt"; }
					if ( det==1 ) { filename8 = "ReadJSON/53_114_NORM_BEGe/p0_VS_E0.txt"; }
					if ( det==2 ) { filename8 = "ReadJSON/53_114_NORM_IC/p0_VS_E0.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename8 = "ReadJSON/53_114_coax_PSD/p0_VS_E0.txt"; }
					if ( det==1 ) { filename8 = "ReadJSON/53_114_BEGe_PSD/p0_VS_E0.txt"; }
					if ( det==2 ) { filename8 = "ReadJSON/53_114_IC_PSD/p0_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename8 = "ReadJSON/53_114_coax/p0_VS_E0.txt"; }
					if ( det==1 ) { filename8 = "ReadJSON/53_114_BEGe/p0_VS_E0.txt"; }
					if ( det==2 ) { filename8 = "ReadJSON/53_114_IC/p0_VS_E0.txt"; }
				}
			}
		}
		std::ofstream file8(filename8);
		
		// ===============================================================================================================
		// p1 VS E0
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename9 = "ReadJSON/53_93_NORM_coax_PSD/p1_VS_E0.txt"; }
					if ( det==1 ) { filename9 = "ReadJSON/53_93_NORM_BEGe_PSD/p1_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename9 = "ReadJSON/53_93_NORM_coax/p1_VS_E0.txt"; }
					if ( det==1 ) { filename9 = "ReadJSON/53_93_NORM_BEGe/p1_VS_E0.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename9 = "ReadJSON/53_93_coax_PSD/p1_VS_E0.txt"; }
					if ( det==1 ) { filename9 = "ReadJSON/53_93_BEGe_PSD/p1_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename9 = "ReadJSON/53_93_coax/p1_VS_E0.txt"; }
					if ( det==1 ) { filename9 = "ReadJSON/53_93_BEGe/p1_VS_E0.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename9 = "ReadJSON/53_114_NORM_coax_PSD/p1_VS_E0.txt"; }
					if ( det==1 ) { filename9 = "ReadJSON/53_114_NORM_BEGe_PSD/p1_VS_E0.txt"; }
					if ( det==2 ) { filename9 = "ReadJSON/53_114_NORM_IC_PSD/p1_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename9 = "ReadJSON/53_114_NORM_coax/p1_VS_E0.txt"; }
					if ( det==1 ) { filename9 = "ReadJSON/53_114_NORM_BEGe/p1_VS_E0.txt"; }
					if ( det==2 ) { filename9 = "ReadJSON/53_114_NORM_IC/p1_VS_E0.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename9 = "ReadJSON/53_114_coax_PSD/p1_VS_E0.txt"; }
					if ( det==1 ) { filename9 = "ReadJSON/53_114_BEGe_PSD/p1_VS_E0.txt"; }
					if ( det==2 ) { filename9 = "ReadJSON/53_114_IC_PSD/p1_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename9 = "ReadJSON/53_114_coax/p1_VS_E0.txt"; }
					if ( det==1 ) { filename9 = "ReadJSON/53_114_BEGe/p1_VS_E0.txt"; }
					if ( det==2 ) { filename9 = "ReadJSON/53_114_IC/p1_VS_E0.txt"; }
				}
			}
		}
		std::ofstream file9(filename9);
		
		// ===============================================================================================================
		// p2 VS E0
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename10 = "ReadJSON/53_93_NORM_coax_PSD/p2_VS_E0.txt"; }
					if ( det==1 ) { filename10 = "ReadJSON/53_93_NORM_BEGe_PSD/p2_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename10 = "ReadJSON/53_93_NORM_coax/p2_VS_E0.txt"; }
					if ( det==1 ) { filename10 = "ReadJSON/53_93_NORM_BEGe/p2_VS_E0.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename10 = "ReadJSON/53_93_coax_PSD/p2_VS_E0.txt"; }
					if ( det==1 ) { filename10 = "ReadJSON/53_93_BEGe_PSD/p2_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename10 = "ReadJSON/53_93_coax/p2_VS_E0.txt"; }
					if ( det==1 ) { filename10 = "ReadJSON/53_93_BEGe/p2_VS_E0.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename10 = "ReadJSON/53_114_NORM_coax_PSD/p2_VS_E0.txt"; }
					if ( det==1 ) { filename10 = "ReadJSON/53_114_NORM_BEGe_PSD/p2_VS_E0.txt"; }
					if ( det==2 ) { filename10 = "ReadJSON/53_114_NORM_IC_PSD/p2_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename10 = "ReadJSON/53_114_NORM_coax/p2_VS_E0.txt"; }
					if ( det==1 ) { filename10 = "ReadJSON/53_114_NORM_BEGe/p2_VS_E0.txt"; }
					if ( det==2 ) { filename10 = "ReadJSON/53_114_NORM_IC/p2_VS_E0.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename10 = "ReadJSON/53_114_coax_PSD/p2_VS_E0.txt"; }
					if ( det==1 ) { filename10 = "ReadJSON/53_114_BEGe_PSD/p2_VS_E0.txt"; }
					if ( det==2 ) { filename10 = "ReadJSON/53_114_IC_PSD/p2_VS_E0.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename10 = "ReadJSON/53_114_coax/p2_VS_E0.txt"; }
					if ( det==1 ) { filename10 = "ReadJSON/53_114_BEGe/p2_VS_E0.txt"; }
					if ( det==2 ) { filename10 = "ReadJSON/53_114_IC/p2_VS_E0.txt"; }
				}
			}
		}
		std::ofstream file10(filename10);
		
		// ===============================================================================================================
		// 90% Upper Limit - NORMALIZED
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename11 = "ReadJSON/53_93_NORM_coax_PSD/90UpperLimit_norm.txt"; }
					if ( det==1 ) { filename11 = "ReadJSON/53_93_NORM_BEGe_PSD/90UpperLimit_norm.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename11 = "ReadJSON/53_93_NORM_coax/90UpperLimit_norm.txt"; }
					if ( det==1 ) { filename11 = "ReadJSON/53_93_NORM_BEGe/90UpperLimit_norm.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename11 = "ReadJSON/53_93_coax_PSD/90UpperLimit_norm.txt"; }
					if ( det==1 ) { filename11 = "ReadJSON/53_93_BEGe_PSD/90UpperLimit_norm.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename11 = "ReadJSON/53_93_coax/90UpperLimit_norm.txt"; }
					if ( det==1 ) { filename11 = "ReadJSON/53_93_BEGe/90UpperLimit_norm.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename11 = "ReadJSON/53_114_NORM_coax_PSD/90UpperLimit_norm.txt"; }
					if ( det==1 ) { filename11 = "ReadJSON/53_114_NORM_BEGe_PSD/90UpperLimit_norm.txt"; }
					if ( det==2 ) { filename11 = "ReadJSON/53_114_NORM_IC_PSD/90UpperLimit_norm.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename11 = "ReadJSON/53_114_NORM_coax/90UpperLimit_norm.txt"; }
					if ( det==1 ) { filename11 = "ReadJSON/53_114_NORM_BEGe/90UpperLimit_norm.txt"; }
					if ( det==2 ) { filename11 = "ReadJSON/53_114_NORM_IC/90UpperLimit_norm.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename11 = "ReadJSON/53_114_coax_PSD/90UpperLimit_norm.txt"; }
					if ( det==1 ) { filename11 = "ReadJSON/53_114_BEGe_PSD/90UpperLimit_norm.txt"; }
					if ( det==2 ) { filename11 = "ReadJSON/53_114_IC_PSD/90UpperLimit_norm.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename11 = "ReadJSON/53_114_coax/90UpperLimit_norm.txt"; }
					if ( det==1 ) { filename11 = "ReadJSON/53_114_BEGe/90UpperLimit_norm.txt"; }
					if ( det==2 ) { filename11 = "ReadJSON/53_114_IC/90UpperLimit_norm.txt"; }
				}
			}
		}
		std::ofstream file11(filename11);
		
		// ===============================================================================================================
		// Significance
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename12 = "ReadJSON/53_93_NORM_coax_PSD/Significance.txt"; }
					if ( det==1 ) { filename12 = "ReadJSON/53_93_NORM_BEGe_PSD/Significance.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename12 = "ReadJSON/53_93_NORM_coax/Significance.txt"; }
					if ( det==1 ) { filename12 = "ReadJSON/53_93_NORM_BEGe/Significance.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename12 = "ReadJSON/53_93_coax_PSD/Significance.txt"; }
					if ( det==1 ) { filename12 = "ReadJSON/53_93_BEGe_PSD/Significance.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename12 = "ReadJSON/53_93_coax/Significance.txt"; }
					if ( det==1 ) { filename12 = "ReadJSON/53_93_BEGe/Significance.txt"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename12 = "ReadJSON/53_114_NORM_coax_PSD/Significance.txt"; }
					if ( det==1 ) { filename12 = "ReadJSON/53_114_NORM_BEGe_PSD/Significance.txt"; }
					if ( det==2 ) { filename12 = "ReadJSON/53_114_NORM_IC_PSD/Significance.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename12 = "ReadJSON/53_114_NORM_coax/Significance.txt"; }
					if ( det==1 ) { filename12 = "ReadJSON/53_114_NORM_BEGe/Significance.txt"; }
					if ( det==2 ) { filename12 = "ReadJSON/53_114_NORM_IC/Significance.txt"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename12 = "ReadJSON/53_114_coax_PSD/Significance.txt"; }
					if ( det==1 ) { filename12 = "ReadJSON/53_114_BEGe_PSD/Significance.txt"; }
					if ( det==2 ) { filename12 = "ReadJSON/53_114_IC_PSD/Significance.txt"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename12 = "ReadJSON/53_114_coax/Significance.txt"; }
					if ( det==1 ) { filename12 = "ReadJSON/53_114_BEGe/Significance.txt"; }
					if ( det==2 ) { filename12 = "ReadJSON/53_114_IC/Significance.txt"; }
				}
			}
		}
		std::ofstream file12(filename12);
		
		for ( int i=E0_min; i<=E0_max; i++) {
		
			std::string filename;
			if ( run==0 ) {
				if ( norm==0 ) {
					if ( PSD==0 ) {
						if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_PSD/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_PSD/JsonFile" + std::to_string(i) + ".json"; }
					}
					if ( PSD==1 ) {
						if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe/JsonFile" + std::to_string(i) + ".json"; }
					}
				}
				if ( norm==1 ) {
					if ( PSD==0 ) {
						if ( det==0 ) { filename = "JsonFiles/53_93_coax_PSD/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_PSD/JsonFile" + std::to_string(i) + ".json"; }
					}
					if ( PSD==1 ) {
						if ( det==0 ) { filename = "JsonFiles/53_93_coax/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_93_BEGe/JsonFile" + std::to_string(i) + ".json"; }
					}
				}
			}
			if ( run==1 ) {
				if ( norm==0 ) {
					if ( PSD==0 ) {
						if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_PSD/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_PSD/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_PSD/JsonFile" + std::to_string(i) + ".json"; }
					}
					if ( PSD==1 ) {
						if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC/JsonFile" + std::to_string(i) + ".json"; }
					}
				}
				if ( norm==1 ) {
					if ( PSD==0 ) {
						if ( det==0 ) { filename = "JsonFiles/53_114_coax_PSD/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_PSD/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==2 ) { filename = "JsonFiles/53_114_IC_PSD/JsonFile" + std::to_string(i) + ".json"; }
					}
					if ( PSD==1 ) {
						if ( det==0 ) { filename = "JsonFiles/53_114_coax/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==1 ) { filename = "JsonFiles/53_114_BEGe/JsonFile" + std::to_string(i) + ".json"; }
						if ( det==2 ) { filename = "JsonFiles/53_114_IC/JsonFile" + std::to_string(i) + ".json"; }
					}
				}
			}
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
				
				file5 << i << "\t\t" << E0_counts_L68 << "\t\t" << E0_counts_U68 << "\t\t" << p0_L68 << "\t\t" << p0_U68 
				<< "\t\t" << p1_L68 << "\t\t" << p1_U68 << "\t\t" << p2_L68 << "\t\t" << p2_U68 << std::endl;
				
				file6 << i << "\t\t" << E0_counts_U90 << "\t\t" << p0_U90 << "\t\t" << p1_U90 << "\t\t" << p2_U90 << std::endl;
				
				file7 << i << std::setw(15) << E0_counts_median << std::setw(14) << E0_counts_L68_sigma << std::setw(14) << E0_counts_U68_sigma << std::setw(14)
				<< p0_median << std::setw(15) << p0_L68_sigma << std::setw(15) << p0_U68_sigma << std::setw(15) << p1_median << std::setw(15) << 
				p1_L68_sigma << std::setw(15) << p1_U68_sigma << std::setw(15) << p2_median << std::setw(15) << p2_L68_sigma << std::setw(15) <<
				p2_U68_sigma << std::endl;
							
				file8 << i << "\t" << p0_GM << "\t" << p0_L68_sigma << "\t" << p0_U68_sigma << std::endl;
				file9 << i << "\t" << p1_GM << "\t" << p1_L68_sigma << "\t" << p1_U68_sigma << std::endl;
				if ( p2_GM!=0 ) file10 << i << "\t" << p2_GM << "\t" << p2_L68_sigma << "\t" << p2_U68_sigma << std::endl;
				
				
				file12 << E0_counts_GM/(( E0_counts_U68 - E0_counts_L68 )*0.5) << std::endl;
				
				if ( run==0 ) {
					if ( det==0 )  { // coax
						const int thr_coax = 195;
						if ( i<thr_coax ) {
							E0_counts_U90 = E0_counts_U90/7.4881;
							p0_U90 = p0_U90/7.4881;
							p1_U90 = p0_U90/7.4881;
							p2_U90 = p0_U90/7.4881;
						}
						if ( i>=thr_coax ) {
							E0_counts_U90 = E0_counts_U90/28.6383;
							p0_U90 = p0_U90/28.6383;
							p1_U90 = p0_U90/28.6383;
							p2_U90 = p0_U90/28.6383;
						}
					}
					if ( det==1 )  { // BEGe
						const int thr_BEGe = 195;
						if ( PSD==0 ) {
							if ( i<thr_BEGe ) {
								E0_counts_U90 = E0_counts_U90/8.28657;
								p0_U90 = p0_U90/8.28657;
								p1_U90 = p0_U90/8.28657;
								p2_U90 = p0_U90/8.28657;
							}
							if ( i>=thr_BEGe ) {
								E0_counts_U90 = E0_counts_U90/31.4597;
								p0_U90 = p0_U90/31.4597;
								p1_U90 = p0_U90/31.4597;
								p2_U90 = p0_U90/31.4597;
							}
						}
						if ( PSD==1 ) {
							if ( i<thr_BEGe ) {
								E0_counts_U90 = E0_counts_U90/8.36807;
								p0_U90 = p0_U90/8.36807;
								p1_U90 = p0_U90/8.36807;
								p2_U90 = p0_U90/8.36807;
							}
							if ( i>=thr_BEGe ) {
								E0_counts_U90 = E0_counts_U90/32.7476;
								p0_U90 = p0_U90/32.7476;
								p1_U90 = p0_U90/32.7476;
								p2_U90 = p0_U90/32.7476;
							}
						}
					}
				}
				if ( run==1 ) {
					if ( det==0 )  { // coax
						const int thr_coax = 195;
						if ( i<thr_coax ) {
							E0_counts_U90 = E0_counts_U90/20.6676;
							p0_U90 = p0_U90/20.6676;
							p1_U90 = p0_U90/20.6676;
							p2_U90 = p0_U90/20.6676;
						}
						if ( i>=thr_coax ) {
							E0_counts_U90 = E0_counts_U90/41.8177;
							p0_U90 = p0_U90/41.8177;
							p1_U90 = p0_U90/41.8177;
							p2_U90 = p0_U90/41.8177;
						}
					}
					if ( det==1 )  { // BEGe
						const int thr_BEGe = 195;
						if ( PSD==0 ) {
							if ( i<thr_BEGe ) {
								E0_counts_U90 = E0_counts_U90/30.1516;
								p0_U90 = p0_U90/30.1516;
								p1_U90 = p0_U90/30.1516;
								p2_U90 = p0_U90/30.1516;
							}
							if ( i>=thr_BEGe ) {
								E0_counts_U90 = E0_counts_U90/53.3248;
								p0_U90 = p0_U90/53.3248;
								p1_U90 = p0_U90/53.3248;
								p2_U90 = p0_U90/53.3248;
							}
						}
						if ( PSD==1 ) {
							if ( i<thr_BEGe ) {
								E0_counts_U90 = E0_counts_U90/30.5489;
								p0_U90 = p0_U90/30.5489;
								p1_U90 = p0_U90/30.5489;
								p2_U90 = p0_U90/30.5489;
							}
							if ( i>=thr_BEGe ) {
								E0_counts_U90 = E0_counts_U90/54.9284;
								p0_U90 = p0_U90/54.9284;
								p1_U90 = p0_U90/54.9284;
								p2_U90 = p0_U90/54.9284;
							}
						}
					}
					if ( det==2 )  { // IC
						if ( PSD==0 ) {
							E0_counts_U90 = E0_counts_U90/8.58872;
							p0_U90 = p0_U90/8.58872;
							p1_U90 = p0_U90/8.58872;
							p2_U90 = p0_U90/8.58872;
						}
						if ( PSD==1 ) {
							E0_counts_U90 = E0_counts_U90/8.77469;
							p0_U90 = p0_U90/8.77469;
							p1_U90 = p0_U90/8.77469;
							p2_U90 = p0_U90/8.77469;
						}
					}
				}
				
				file11 << i << std::setw(15) << E0_counts_U90 << std::setw(14) << p0_U90 << std::setw(15) << p1_U90 << std::setw(15) << p2_U90 << std::endl;
			} // stop else
		} // stop for
		
		std::cout << filename1 << std::endl;
		std::cout << filename2 << std::endl;
		std::cout << filename3 << std::endl;
		std::cout << filename4 << std::endl;
		std::cout << filename5 << std::endl;
		std::cout << filename6 << std::endl;
		std::cout << filename7 << std::endl;
		std::cout << filename8 << std::endl;
		std::cout << filename9 << std::endl;
		std::cout << filename10 << std::endl;
		std::cout << filename11 << std::endl;
		std::cout << filename12 << std::endl;
		
		file1.close();
		file2.close();
		file3.close();
		file4.close();
		file5.close();
		file6.close();
		file7.close();
		file8.close();
		file9.close();
		file10.close();
		file11.close();
		
		std::cout << "\033[1;31m -> files have been created\033[0m\n";
	} // stop choice=0


	//---------------------------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------- PRINT ONE E0
	if ( choice == 1 ) {
		int E0;
		std::cout << "\n * Choose E0: ";
		std::cin >> E0;
		
		int run;
		std::cout << "\n * Run: 53-93 (0) or 53-114 (1)? ";
		std::cin >> run;
		int norm;
		std::cout << " * Normalized (0) or not (1)? ";
		std::cin >> norm;
		int PSD;
		std::cout << " * Only PSD (0) or everything (1)? ";
		std::cin >> PSD;
		
		std::string filename;
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_PSD/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_PSD/JsonFile" + std::to_string(E0) + ".json"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe/JsonFile" + std::to_string(E0) + ".json"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_coax_PSD/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_PSD/JsonFile" + std::to_string(E0) + ".json"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_93_coax/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_93_BEGe/JsonFile" + std::to_string(E0) + ".json"; }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_PSD/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_PSD/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_PSD/JsonFile" + std::to_string(E0) + ".json"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC/JsonFile" + std::to_string(E0) + ".json"; }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax_PSD/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_PSD/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC_PSD/JsonFile" + std::to_string(E0) + ".json"; }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { filename = "JsonFiles/53_114_coax/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==1 ) { filename = "JsonFiles/53_114_BEGe/JsonFile" + std::to_string(E0) + ".json"; }
					if ( det==2 ) { filename = "JsonFiles/53_114_IC/JsonFile" + std::to_string(E0) + ".json"; }
				}
			}
		}
		std::cout << filename << std::endl;
		std::ifstream file(filename);
		json j_read;
		file >> j_read;
		file.close();
		
		std::cout << "\n\033[1;36m " << std::setw(4) << j_read << "\033[0m\n";	
	} // stop choice=1
	
	
	//----------------------------------------------------------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------------------------------------------- PRINT MORE E0
	if ( choice == 2 ) {
		int E0_min, E0_max;
		std::cout << "\n * Select the interval [E0_min;E0_max]:\n\t - choose E0_min: ";
		std::cin >> E0_min;
		std::cout << "\t - choose E0_max: ";
		std::cin >> E0_max;
		
		int run;
		std::cout << "\n * Run: 53-93 (0) or 53-114 (1)? ";
		std::cin >> run;
		int norm;
		std::cout << " * Normalized (0) or not (1)? ";
		std::cin >> norm;
		int PSD;
		std::cout << " * Only PSD (0) or everything (1)? ";
		std::cin >> PSD;
		
		int json_what;
		std::cout << "\n * Do you want everything (0) or not (1)? ";
		std::cin >> json_what;
		
		if ( json_what == 0 ) {
				int k = 31;
				for ( int j=E0_min; j<=E0_max; j++) {
					std::string filename;
					if ( run==0 ) {
						if ( norm==0 ) {
							if ( PSD==0 ) {
								if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_PSD/JsonFile" + std::to_string(j) + ".json"; }
							}
							if ( PSD==1 ) {
								if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe/JsonFile" + std::to_string(j) + ".json"; }
							}
						}
						if ( norm==1 ) {
							if ( PSD==0 ) {
								if ( det==0 ) { filename = "JsonFiles/53_93_coax_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_PSD/JsonFile" + std::to_string(j) + ".json"; }
							}
							if ( PSD==1 ) {
								if ( det==0 ) { filename = "JsonFiles/53_93_coax/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_93_BEGe/JsonFile" + std::to_string(j) + ".json"; }
							}
						}
					}
					if ( run==1 ) {
						if ( norm==0 ) {
							if ( PSD==0 ) {
								if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_PSD/JsonFile" + std::to_string(j) + ".json"; }
							}
							if ( PSD==1 ) {
								if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC/JsonFile" + std::to_string(j) + ".json"; }
							}
						}
						if ( norm==1 ) {
							if ( PSD==0 ) {
								if ( det==0 ) { filename = "JsonFiles/53_114_coax_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==2 ) { filename = "JsonFiles/53_114_IC_PSD/JsonFile" + std::to_string(j) + ".json"; }
							}
							if ( PSD==1 ) {
								if ( det==0 ) { filename = "JsonFiles/53_114_coax/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_114_BEGe/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==2 ) { filename = "JsonFiles/53_114_IC/JsonFile" + std::to_string(j) + ".json"; }
							}
						}
					}
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
		} // stop json_what=0
		
		if ( json_what == 1 ) {
				int ans3;
				std::cout << "\n * What result do you want? " << std::endl;
				std::cout << "\t (1) Peak Search\n\t (2) Parameter Range\n\t (3) Global Mode\n";
				std::cout << "\t (4) Mean\n\t (5) 68 Central Range\n\t (6) 90 Upper Limit\n\t (7) Median\n -> ";
				std::cin >> ans3;
				
		
				int k = 31;
				for ( int j=E0_min; j<=E0_max; j++) {
					std::string filename;
					if ( run==0 ) {
						if ( norm==0 ) {
							if ( PSD==0 ) {
								if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe_PSD/JsonFile" + std::to_string(j) + ".json"; }
							}
							if ( PSD==1 ) {
								if ( det==0 ) { filename = "JsonFiles/53_93_NORM_coax/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_93_NORM_BEGe/JsonFile" + std::to_string(j) + ".json"; }
							}
						}
						if ( norm==1 ) {
							if ( PSD==0 ) {
								if ( det==0 ) { filename = "JsonFiles/53_93_coax_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_93_BEGe_PSD/JsonFile" + std::to_string(j) + ".json"; }
							}
							if ( PSD==1 ) {
								if ( det==0 ) { filename = "JsonFiles/53_93_coax/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_93_BEGe/JsonFile" + std::to_string(j) + ".json"; }
							}
						}
					}
					if ( run==1 ) {
						if ( norm==0 ) {
							if ( PSD==0 ) {
								if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC_PSD/JsonFile" + std::to_string(j) + ".json"; }
							}
							if ( PSD==1 ) {
								if ( det==0 ) { filename = "JsonFiles/53_114_NORM_coax/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_114_NORM_BEGe/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==2 ) { filename = "JsonFiles/53_114_NORM_IC/JsonFile" + std::to_string(j) + ".json"; }
							}
						}
						if ( norm==1 ) {
							if ( PSD==0 ) {
								if ( det==0 ) { filename = "JsonFiles/53_114_coax_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_114_BEGe_PSD/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==2 ) { filename = "JsonFiles/53_114_IC_PSD/JsonFile" + std::to_string(j) + ".json"; }
							}
							if ( PSD==1 ) {
								if ( det==0 ) { filename = "JsonFiles/53_114_coax/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==1 ) { filename = "JsonFiles/53_114_BEGe/JsonFile" + std::to_string(j) + ".json"; }
								if ( det==2 ) { filename = "JsonFiles/53_114_IC/JsonFile" + std::to_string(j) + ".json"; }
							}
						}
					}
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
		} // stop json_what=1
	
	} // stop choice=2	

	return 0;
}
