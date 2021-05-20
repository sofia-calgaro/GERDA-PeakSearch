// **********************************************************************************************************************
// This file contains different functions that are called in the source files in order to create:
// 	- a JSON (one for each polynomial degree available for the BKG) file that contains all the necessary BAT
//	  parameters for the analysis;
//	- ROOT plots/files containing data and fit results from BAT.
// **********************************************************************************************************************
#include "Output.h"
#include "Operations.h"



//=======================================================================================================================
// Create a JSON file
void JsonFile (const std::vector<double> params, const std::vector<double> params_err, int IntResults[], std::vector<double> DblResults) {

	int E0 = IntResults[0];
	int xL = IntResults[1];
	int xR = IntResults[2];
	int bin_width = std::round(xR-xL);
	int k = IntResults[3];
	int outputK = IntResults[4];
	int pol_degree = IntResults[5];	
	
	double E1 = DblResults.at(54);
	double E2 = DblResults.at(55);

	char name_file[200];
	sprintf(name_file, "/home/sofia/Analysis/DataAnalysis/JsonFiles/JsonFile%i.json", E0);
	std::fstream file;
	file.open(name_file, std::ios::out);
	
	// signal counts VS E0
	std::fstream file_counts;
	file_counts.open("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/counts_VS_E0.txt", std::ios_base::app);
	if ( !file_counts ) { file_counts.open("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/counts_VS_E0.txt", std::ios::out); }
	file_counts << E0 << "\t" <<  DblResults.at(30) << std::endl; // U-90
	
	// p0 VS E0
	std::fstream file_p0;
	file_p0.open("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/p0_VS_E0.txt", std::ios_base::app);
	if ( !file_p0 ) { file_p0.open("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/p0_VS_E0.txt", std::ios::out); }
	file_p0 << E0 << "\t" <<  params.at(1) << "\t" << DblResults.at(44) << "\t" << DblResults.at(45) << std::endl;
	
	// p1 VS E0
	if ( pol_degree==1 ) {
		std::fstream file_p1;
		file_p1.open("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/p1_VS_E0.txt", std::ios_base::app);
		if ( !file_p1 ) { file_p1.open("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/p1_VS_E0.txt", std::ios::out); }
		file_p1 << E0 << "\t" <<  params.at(2) << "\t" << DblResults.at(46) << "\t" << DblResults.at(47) << std::endl;
	}
	
	// p2 VS E0
	if ( pol_degree==2 ) {
		std::fstream file_p2;
		file_p2.open("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/p2_VS_E0.txt", std::ios_base::app);
		if ( !file_p2 ) { file_p2.open("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/p2_VS_E0.txt", std::ios::out); }
		file_p2 << E0 << "\t" <<  params.at(3) << "\t" << DblResults.at(48) << "\t" << DblResults.at(49) << std::endl;
	}
	
		
	//----------------------------------------------------------------------------------
	// Global mode
	double E0_height_GM=0, E0_height_err_GM=0, E1_height_GM=0, E1_height_err_GM=0, E2_height_GM=0, E2_height_err_GM=0;
	E0_height_GM = params.at(0);
	E0_height_err_GM = params_err.at(0);
	
	double p0_GM=0, p0_err_GM=0, p1_GM=0, p2_GM=0, p1_err_GM=0, p2_err_GM=0;	
	p0_GM = params.at(1);
	p0_err_GM = params_err.at(1);
	if ( pol_degree==1 ) {
		p1_GM = params.at(2);
		p1_err_GM = params_err.at(2);
	}
	if ( pol_degree==2 ) {
		p1_GM = params.at(2);
		p1_err_GM = params_err.at(2);
		p2_GM = params.at(3);
		p2_err_GM = params_err.at(3);
	}
	
	// 1 gamma peak (pay attention to the indexes)
	if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		if ( pol_degree==0 ) {
			E1_height_GM = params.at(2);
			E1_height_err_GM = params_err.at(2);
		}
		if ( pol_degree==1 ) {
			E1_height_GM = params.at(3);
			E1_height_err_GM = params_err.at(3);
			}
		if (pol_degree==2 ) {
			E1_height_GM = params.at(4);
			E1_height_err_GM = params_err.at(4);
			}
	}
	// 2 gamma peaks (pay attention to the indexes)
	if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		if ( pol_degree==0 ) {
			E1_height_GM = params.at(2);
			E1_height_err_GM = params_err.at(2);
			E2_height_GM = params.at(3);
			E2_height_err_GM = params_err.at(3);
		}
		if ( pol_degree==1 ) {
			E1_height_GM = params.at(3);
			E1_height_err_GM = params_err.at(3);
			E2_height_GM = params.at(4);
			E2_height_err_GM = params_err.at(4);
			}
		if ( pol_degree==2 ) {
			E1_height_GM = params.at(4);
			E1_height_err_GM = params_err.at(4);
			E2_height_GM = params.at(5);
			E2_height_err_GM = params_err.at(5);
			}
	}
	
	
	//----------------------------------------------------------------------------------
	json j1, j2, j3, j4, j5, j6, j7;
	
	// Results of "peak_search.sh"
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j1 = {
			{ "polDegree_BKG", pol_degree},
			{ "windowLeftEdge_xL", xL},
			{ "windowRightEdge_xR", xR},
			{ "windowWidth", bin_width},
			{ "k_GammaArrayIndex", k},
			{ "outputk_GammaPosition", outputK}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {	
		j1 = {
			{ "E1", E1},
			{ "polDegree_BKG", pol_degree},
			{ "windowLeftEdge_xL", xL},
			{ "windowRightEdge_xR", xR},
			{ "windowWidth", bin_width},
			{ "k_GammaArrayIndex", k},
			{ "outputk_GammaPosition", outputK}
		};
	}
	// 2 gamma peaks
	else {
		j1 = {
			{ "E1", E1},
			{ "E2", E2},
			{ "polDegree_BKG", pol_degree},
			{ "windowLeftEdge_xL", xL},
			{ "windowRightEdge_xR", xR},
			{ "windowWidth", bin_width},
			{ "k_GammaArrayIndex", k},
			{ "outputk_GammaPosition", outputK}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: parameters' ranges
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {	
		j2 = {
			{ "E0_counts_MIN", DblResults.at(56)},
			{ "E0_counts_MAX", DblResults.at(57)},
			{ "p0_MIN", DblResults.at(58)},
			{ "p0_MAX", DblResults.at(59)}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {	
		j2 = {
			{ "E0_counts_MIN", DblResults.at(56)},
			{ "E0_counts_MAX", DblResults.at(57)},
			{ "p0_MIN", DblResults.at(58)},
			{ "p0_MAX", DblResults.at(59)},
			{ "E1_counts_MIN", DblResults.at(64)},
			{ "E1_counts_MAX", DblResults.at(65)}
		};
	}
	// 2 gamma peaks
	else {	
		j2 = {
			{ "E0_counts_MIN", DblResults.at(56)},
			{ "E0_counts_MAX", DblResults.at(57)},
			{ "p0_MIN", DblResults.at(58)},
			{ "p0_MAX", DblResults.at(59)},
			{ "E1_counts_MIN", DblResults.at(64)},
			{ "E1_counts_MAX", DblResults.at(65)},
			{ "E2_counts_MIN", DblResults.at(66)},
			{ "E2_counts_MAX", DblResults.at(67)}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: global mode
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j3 = {
			{ "E0_counts", E0_height_GM},
			{ "E0_counts_sigma", E0_height_err_GM},
			{ "p0", p0_GM},
			{ "p0_sigma", p0_err_GM}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j3 = {
			{ "E0_counts", E0_height_GM},
			{ "E0_counts_sigma", E0_height_err_GM},
			{ "p0", p0_GM},
			{ "p0_sigma", p0_err_GM},
			{ "E1_counts", E1_height_GM},
			{ "E1_counts_sigma", E1_height_err_GM}
		};
	}
	// 2 gamma peaks
	else {
		j3 = {
			{ "E0_counts", E0_height_GM},
			{ "E0_counts_sigma", E0_height_err_GM},
			{ "p0", p0_GM},
			{ "p0_sigma", p0_err_GM},
			{ "E1_counts", E1_height_GM},
			{ "E1_counts_sigma", E1_height_err_GM},
			{ "E2_counts", E2_height_GM},
			{ "E2_counts_sigma", E2_height_err_GM}
		};
	}
		
	
	//----------------------------------------------------------------------------------
	// Results of BAT: mean +- sqrt(variance)
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j4 = {
			{ "E0_counts", DblResults.at(6)},
			{ "E0_counts_sigma", DblResults.at(12)},
			{ "p0", DblResults.at(7)},
			{ "p0_sigma", DblResults.at(13)}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j4 = {
			{ "E0_counts", DblResults.at(6)},
			{ "E0_counts_sigma", DblResults.at(12)},
			{ "p0", DblResults.at(7)},
			{ "p0_sigma", DblResults.at(13)},
			{ "E1_counts", DblResults.at(10)},
			{ "E1_counts_sigma", DblResults.at(16)}
		};
	}
	// 2 gamma peaks
	else {
		j4 = {
			{ "E0_counts", DblResults.at(6)},
			{ "E0_counts_sigma", DblResults.at(12)},
			{ "p0", DblResults.at(7)},
			{ "p0_sigma", DblResults.at(13)},
			{ "E1_counts", DblResults.at(10)},
			{ "E1_counts_sigma", DblResults.at(16)},
			{ "E2_counts", DblResults.at(11)},
			{ "E2_counts_sigma", DblResults.at(17)}
		};
	}
	
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: 68% central range ( L=lower/U=upper limit )
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j5 = {
			{ "E0_counts_L68", DblResults.at(18)},
			{ "E0_counts_U68", DblResults.at(19)},
			{ "p0_L68", DblResults.at(20)},
			{ "p0_U68", DblResults.at(21)}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j5 = {
			{ "E0_counts_L68", DblResults.at(18)},
			{ "E0_counts_U68", DblResults.at(19)},
			{ "p0_L68", DblResults.at(20)},
			{ "p0_U68", DblResults.at(21)},
			{ "E1_counts_L68", DblResults.at(26)},
			{ "E1_counts_U68", DblResults.at(27)}
		};
	}
	// 2 gamma peaks
	else {
		j5 = {
			{ "E0_counts_L68", DblResults.at(18)},
			{ "E0_counts_U68", DblResults.at(19)},
			{ "p0_L68", DblResults.at(20)},
			{ "p0_U68", DblResults.at(21)},
			{ "E1_counts_L68", DblResults.at(26)},
			{ "E1_counts_U68", DblResults.at(27)},
			{ "E2_counts_L68", DblResults.at(28)},
			{ "E2_counts_U68", DblResults.at(29)}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: 90% upper limit
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j6 = {
			{ "E0_counts_U90", DblResults.at(30)},
			{ "p0_U90", DblResults.at(31)}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j6 = {
			{ "E0_counts_U90", DblResults.at(30)},
			{ "p0_U90", DblResults.at(31)},
			{ "E1_counts_U90", DblResults.at(34)}
		};
	}
	// 2 gamma peaks
	else {
		j6 = {
			{ "E0_counts_U90", DblResults.at(30)},
			{ "p0_U90", DblResults.at(31)},
			{ "E1_counts_U90", DblResults.at(34)},
			{ "E2_counts_U90", DblResults.at(35)}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: median
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j7 = {
			{ "E0_counts_median", DblResults.at(36)},
			{ "E0_counts_L68_sigma", DblResults.at(42)},
			{ "E0_counts_U68_sigma", DblResults.at(43)},
			{ "p0_median", DblResults.at(37)},
			{ "p0_L68_sigma", DblResults.at(44)},
			{ "p0_U68_sigma", DblResults.at(45)},
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j7 = {
			{ "E0_counts_median", DblResults.at(36)},
			{ "E0_counts_L68_sigma", DblResults.at(42)},
			{ "E0_counts_U68_sigma", DblResults.at(43)},
			{ "p0_median", DblResults.at(37)},
			{ "p0_L68_sigma", DblResults.at(44)},
			{ "p0_U68_sigma", DblResults.at(45)},
			{ "E1_counts_median", DblResults.at(40)},
			{ "E1_counts_L68_sigma", DblResults.at(50)},
			{ "E1_counts_U68_sigma", DblResults.at(51)}
		};
	}
	// 2 gamma peaks
	else {
		j7 = {
			{ "E0_counts_median", DblResults.at(36)},
			{ "E0_counts_L68_sigma", DblResults.at(42)},
			{ "E0_counts_U68_sigma", DblResults.at(43)},
			{ "p0_median", DblResults.at(37)},
			{ "p0_L68_sigma", DblResults.at(44)},
			{ "p0_U68_sigma", DblResults.at(45)},
			{ "E1_counts_median", DblResults.at(40)},
			{ "E1_counts_L68_sigma", DblResults.at(50)},
			{ "E1_counts_U68_sigma", DblResults.at(51)},
			{ "E2_counts_median", DblResults.at(41)},
			{ "E2_counts_L68_sigma", DblResults.at(52)},
			{ "E2_counts_U68_sigma", DblResults.at(53)}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	if ( pol_degree == 1 ) {
		// p1 data
		j2["p1_MIN"] = DblResults.at(60);
		j2["p1_MAX"] = DblResults.at(61);
		j3["p1"] = p1_GM;
		j3["p1_sigma"] = p1_err_GM;
		j4["p1"] = DblResults.at(8);
		j4["p1_sigma"] = DblResults.at(14);
		j5["p1_L68"] = DblResults.at(22);
		j5["p1_U68"] = DblResults.at(23);
		j6["p1_U90"] = DblResults.at(32);
		j7["p1_median"] = DblResults.at(38);
		j7["p1_L68_sigma"] = DblResults.at(46);
		j7["p1_U68_sigma"] = DblResults.at(47);
	}
	if ( pol_degree == 2 ) {
		// p1 data
		j2["p1_MIN"] = DblResults.at(60);
		j2["p1_MAX"] = DblResults.at(61);
		j3["p1"] = p1_GM;
		j3["p1_sigma"] = p1_err_GM;
		j4["p1"] = DblResults.at(8);
		j4["p1_sigma"] = DblResults.at(14);
		j5["p1_L68"] = DblResults.at(22);
		j5["p1_U68"] = DblResults.at(23);
		j6["p1_U90"] = DblResults.at(32);
		j7["p1_median"] = DblResults.at(38);
		j7["p1_L68_sigma"] = DblResults.at(46);
		j7["p1_U68_sigma"] = DblResults.at(47);
		
		// p2 data
		j2["p2_MIN"] = DblResults.at(62);
		j2["p2_MAX"] = DblResults.at(63);
		j3["p2"] = p2_GM;
		j3["p2_sigma"] = p2_err_GM;
		j4["p2"] = DblResults.at(9);
		j4["p2_sigma"] = DblResults.at(15);
		j5["p2_L68"] = DblResults.at(24);
		j5["p2_U68"] = DblResults.at(25);
		j6["p2_U90"] = DblResults.at(33);
		j7["p2_median"] = DblResults.at(39);
		j7["p2_L68_sigma"] = DblResults.at(48);
		j7["p2_U68_sigma"] = DblResults.at(49);
	}
	
	
	//----------------------------------------------------------------------------------	
	// Final JSON object
	json jtot = json::object({  {"E0", E0}, {"PeakSearch", j1 }, {"ParameterRange", j2 }, {"GlobalMode", j3 },
				    {"Mean", j4 }, {"68CentralRange", j5 }, {"90UpperLimit", j6 }, {"Median", j7 } });
	
	// Print data inside the JSON file
	file << std::setw(4) << jtot << std::endl;
	file.close();
}



//=======================================================================================================================
// Draw f(x) = pol0(x)+gaus(x)
void Draw_Pol0(int E0, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[100];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1]", E0, FindSigma(E0));
	TF1 *f0 = new TF1("f0", function, xL, xR);
	f0->FixParameter(0, params.at(0));
	f0->FixParameter(1, params.at(1));
			    
	f0->SetLineWidth(2);
	f0->SetLineColor(2);
	f0->Draw("same");
			    
	h->SetTitle("Fit with pol0(x)+gaus(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol0.png", E0);
	c->Print(name_image);
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol0.root", E0);
	c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol0(x)+gaus(x)+gaus_gamma(x)
void Draw_Gamma_Pol0(int E0, double EG, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[100];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*TMath::Gaus(x, %f, %f, true)", E0, FindSigma(E0), EG, FindSigma(EG));
	TF1 *f0 = new TF1("f0", function, xL, xR);
	f0->FixParameter(0, params.at(0));
	f0->FixParameter(1, params.at(1));
	f0->FixParameter(2, params.at(2));
			    
	f0->SetLineWidth(2);
	f0->SetLineColor(2);
	f0->Draw("same");
			    
	h->SetTitle("Fit with pol0(x)+gaus(x)+gaus1(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol0_%gGamma.png", E0, EG);
	c->Print(name_image);
	//char name_rootfile[100];
	//sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol0_%gGamma.root", E0, EG);
	//c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol0(x)+gaus(x)+gaus_gamma(x)+gaus_gamma_2(x)
void Draw_TwoGamma_Pol0(int E0, double EG, double EG_2, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[200];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*TMath::Gaus(x, %f, %f, true) + [3]*TMath::Gaus(x, %f, %f, true)", E0, FindSigma(E0), EG, FindSigma(EG), EG_2, FindSigma(EG_2));
	TF1 *f0 = new TF1("f0", function, xL, xR);
	f0->FixParameter(0, params.at(0));
	f0->FixParameter(1, params.at(1));
	f0->FixParameter(2, params.at(2));
	f0->FixParameter(3, params.at(3));
			    
	f0->SetLineWidth(2);
	f0->SetLineColor(2);
	f0->Draw("same");
			    
	h->SetTitle("Fit with pol0(x)+gaus(x)+gaus1(x)+gaus2(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol0_%gGamma_%gGamma.png", E0, EG, EG_2);
	c->Print(name_image);
	//char name_rootfile[100];
	//sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol0_%gGamma_%gGamma.root", E0, EG, EG_2);
	//c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol1(x)+gaus(x)
void Draw_Pol1(int E0, int xL, int xR, const std::vector<double> params, TH1D *h) {

        TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);
		    
	char function[100];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i)", E0, FindSigma(E0), E0);
	TF1 *f1 = new TF1("f1", function, xL, xR);
	f1->FixParameter(0, params.at(0));
	f1->FixParameter(1, params.at(1));
	f1->FixParameter(2, params.at(2));
	  
	f1->SetLineWidth(2);
	f1->SetLineColor(2);
	f1->Draw("same");  
	   
	h->SetTitle("Fit with pol1(x)+gaus(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol1.png", E0);
	c->Print(name_image);
	//char name_rootfile[100];
	//sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol1.root", E0);
	//c->Print(name_rootfile);     
}



//=======================================================================================================================
// Draw f(x) = pol1(x)+gaus(x)+gaus_gamma(x)
void Draw_Gamma_Pol1(int E0, double EG, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[200];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*TMath::Gaus(x, %f, %f, true)", E0, FindSigma(E0), E0, EG, FindSigma(EG));
	TF1 *f0 = new TF1("f0", function, xL, xR);
	f0->FixParameter(0, params.at(0));
	f0->FixParameter(1, params.at(1));
	f0->FixParameter(2, params.at(2));
	f0->FixParameter(3, params.at(3));
			    
	f0->SetLineWidth(2);
	f0->SetLineColor(2);
	f0->Draw("same");
			    
	h->SetTitle("Fit with pol1(x)+gaus(x)+gaus1(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol1_%gGamma.png", E0, EG);
	c->Print(name_image);
	//char name_rootfile[100];
	//sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol1_%gGamma.root", E0, EG);
	//c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol1(x)+gaus(x)+gaus_gamma(x)+gaus_gamma_2(x)
void Draw_TwoGamma_Pol1(int E0, double EG, double EG_2, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[200];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*TMath::Gaus(x, %f, %f, true) + [4]*TMath::Gaus(x, %f, %f, true)", E0, FindSigma(E0), E0, EG, FindSigma(EG), EG_2, FindSigma(EG_2));
	TF1 *f0 = new TF1("f0", function, xL, xR);
	f0->FixParameter(0, params.at(0));
	f0->FixParameter(1, params.at(1));
	f0->FixParameter(2, params.at(2));
	f0->FixParameter(3, params.at(3));
	f0->FixParameter(4, params.at(4));
			    
	f0->SetLineWidth(2);
	f0->SetLineColor(2);
	f0->Draw("same");
			    
	h->SetTitle("Fit with pol1(x)+gaus(x)+gaus1(x)+gaus2(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol1_%gGamma_%gGamma.png", E0, EG, EG_2);
	c->Print(name_image);
	//char name_rootfile[100];
	//sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol1_%gGamma_%gGamma.root", E0, EG, EG_2);
	//c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol2(x)+gaus(x)
void Draw_Pol2(int E0, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);
	    	    
	char function[100];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*(x-%i)*(x-%i)", E0, FindSigma(E0), E0, E0, E0);
	TF1 *f2 = new TF1("f2", function, xL, xR);
	f2->FixParameter(0, params.at(0));
	f2->FixParameter(1, params.at(1));
	f2->FixParameter(2, params.at(2));
	f2->FixParameter(3, params.at(3));
	    
	f2->SetLineWidth(2);
	f2->SetLineColor(2);
	f2->Draw("same");  
	    
	h->SetTitle("Fit with pol2(x)+gaus(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol2.png", E0);
	c->Print(name_image);
	//char name_rootfile[100];
	//sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol2.root", E0);
	//c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol2(x)+gaus(x)+gaus_gamma(x)
void Draw_Gamma_Pol2(int E0, double EG, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[200];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*(x-%i)*(x-%i) + [4]*TMath::Gaus(x, %f, %f, true)", E0, FindSigma(E0), E0, E0, E0, EG, FindSigma(EG));
	TF1 *f2 = new TF1("f2", function, xL, xR);
	f2->FixParameter(0, params.at(0));
	f2->FixParameter(1, params.at(1));
	f2->FixParameter(2, params.at(2));
	f2->FixParameter(3, params.at(3));
	f2->FixParameter(4, params.at(4));
			    
	f2->SetLineWidth(2);
	f2->SetLineColor(2);
	f2->Draw("same");
			    
	h->SetTitle("Fit with pol2(x)+gaus(x)+gaus1(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol2_%gGamma.png", E0, EG);
	c->Print(name_image);
	//char name_rootfile[100];
	//sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol2_%gGamma.root", E0, EG);
	//c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol2(x)+gaus(x)+gaus_gamma(x)+gaus_gamma_2(x)
void Draw_TwoGamma_Pol2(int E0, double EG, double EG_2, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[200];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*(x-%i)*(x-%i) + [4]*TMath::Gaus(x, %f, %f, true) + [5]*TMath::Gaus(x, %f, %f, true)", E0, FindSigma(E0), E0, E0, E0, EG, FindSigma(EG), EG_2, FindSigma(EG_2));
	TF1 *f2 = new TF1("f2", function, xL, xR);
	f2->FixParameter(0, params.at(0));
	f2->FixParameter(1, params.at(1));
	f2->FixParameter(2, params.at(2));
	f2->FixParameter(3, params.at(3));
	f2->FixParameter(4, params.at(4));
	f2->FixParameter(5, params.at(5));
			    
	f2->SetLineWidth(2);
	f2->SetLineColor(2);
	f2->Draw("same");
			    
	h->SetTitle("Fit with pol2(x)+gaus(x)+gaus1(x)+gaus2(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol2_%gGamma_%gGamma.png", E0, EG, EG_2);
	c->Print(name_image);
	//char name_rootfile[100];
	//sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol2_%gGamma_%gGamma.root", E0, EG, EG_2);
	//c->Print(name_rootfile);
}
