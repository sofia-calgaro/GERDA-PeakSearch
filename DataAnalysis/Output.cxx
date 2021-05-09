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

	char name_file[100];
	sprintf(name_file, "JsonPol%i.json", IntResults[5]);
	
	std::fstream file;
	file.open(name_file, std::ios_base::app); // add lines without overwriting the file
	
	// If file does not exist...
	if ( !file ) {
		std::cout << "\"" << name_file << "\" does not exist. The file is created!" << std::endl;
		file.open(name_file, std::ios::out);
	}

	//----------------------------------------------------------------------------------
	int E0 = IntResults[0];
	int xL = IntResults[1];
	int xR = IntResults[2];
	int bin_width = std::round(xR-xL);
	int k = IntResults[3];
	int outputK = IntResults[4];
	int pol_degree = IntResults[5];	
	
	double E1 = DblResults.at(30);
	double E2 = DblResults.at(31);
		
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
	std::string str;
	str = "E0-" + std::to_string(E0);
	
	json j1, j2, j3, j4, j5;
	
	
	// Results of "peak_search.sh"
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j1 = {
			{ "PeakSearch", {
				{"E0", E0},
				{ "polDegree_BKG", pol_degree},
				{ "windowLeftEdge_xL", xL},
				{ "windowRightEdge_xR", xR},
				{ "windowWidth", bin_width},
				{ "k_GammaArrayIndex", k},
				{ "outputk_GammaPosition", outputK}
			}}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {	
		j1 = {
			{ "PeakSearch", {
				{"E0", E0},
				{"E1", E1},
				{ "polDegree_BKG", pol_degree},
				{ "windowLeftEdge_xL", xL},
				{ "windowRightEdge_xR", xR},
				{ "windowWidth", bin_width},
				{ "k_GammaArrayIndex", k},
				{ "outputk_GammaPosition", outputK}
			}}
		};
	}
	// 2 gamma peaks
	else {
		j1 = {
			{ "PeakSearch", {
				{"E0", E0},
				{"E1", E1},
				{"E2", E2},
				{ "polDegree_BKG", pol_degree},
				{ "windowLeftEdge_xL", xL},
				{ "windowRightEdge_xR", xR},
				{ "windowWidth", bin_width},
				{ "k_GammaArrayIndex", k},
				{ "outputk_GammaPosition", outputK}
			}}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: parameters' ranges
	char str1_PR[100], str2_PR[100];
	sprintf(str1_PR, "[%g, %g]", DblResults.at(32), DblResults.at(33)); // E0_height
	sprintf(str2_PR, "[%g, %g]", DblResults.at(34), DblResults.at(35)); // p0
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {	
		j2 = {
			{ "ParameterRange", {
					{ "E0_height", str1_PR},
					{ "p0", str2_PR},
			}}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {	
		char str3_PR[100];
		sprintf(str3_PR, "[%g, %g]", DblResults.at(40), DblResults.at(41)); // E1_height
		j2 = {
			{ "ParameterRange", {
					{ "E0_height", str1_PR},
					{ "p0", str2_PR},
					{ "E1_height", str3_PR}
			}}
		};
	}
	// 2 gamma peaks
	else {	
		char str3_PR[100], str4_PR[100];
		sprintf(str3_PR, "[%g, %g]", DblResults.at(40), DblResults.at(41)); // E1_height
		sprintf(str4_PR, "[%g, %g]", DblResults.at(42), DblResults.at(43)); // E2_height
		j2 = {
			{ "ParameterRange", {
					{ "E0_height", str1_PR},
					{ "p0", str2_PR},
					{ "E1_height", str3_PR},
					{ "E2_height", str4_PR}
			}}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: global mode
	char str1_GM[100], str2_GM[100];
	sprintf(str1_GM, "%g +- %g", E0_height_GM, E0_height_err_GM); // E0_height
	sprintf(str2_GM, "%g +- %g", p0_GM, p0_err_GM); // p0
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j3 = {
			{ "GlobalMode", {
					{ "E0_height", str1_GM},
					{ "p0", str2_GM}
			}}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		char str3_GM[100];
		sprintf(str3_GM, "%g +- %g", E1_height_GM, E1_height_err_GM); // E1_height
		j3 = {
			{ "GlobalMode", {
					{ "E0_height", str1_GM},
					{ "p0", str2_GM},
					{ "E1_height", str3_GM}
			}}
		};
	}
	// 2 gamma peaks
	else {
		char str3_GM[100], str4_GM[100];
		sprintf(str3_GM, "%g +- %g", E1_height_GM, E1_height_err_GM); // E1_height
		sprintf(str4_GM, "%g +- %g", E2_height_GM, E2_height_err_GM); // E2_height
		j3 = {
			{ "GlobalMode", {
					{ "E0_height", str1_GM},
					{ "p0", str2_GM},
					{ "E1_height", str3_GM},
					{ "E2_height", str4_GM}
			}}
		};
	}
		
	
	//----------------------------------------------------------------------------------
	// Results of BAT: mean +- sqrt(variance)
	char str1_M[100], str2_M[100];
	sprintf(str1_M, "%g +- %g", DblResults.at(6), DblResults.at(12)); // E0_height
	sprintf(str2_M, "%g +- %g", DblResults.at(7), DblResults.at(13)); // p0
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j4 = {
			{ "Mean+-sqrt(variance)", {
					{ "E0_height", str1_M},
					{ "p0", str2_M}
			}}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		char str3_M[100];
		sprintf(str3_M, "%g +- %g", DblResults.at(10), DblResults.at(16)); // E1_height
		j4 = {
			{ "Mean+-sqrt(variance)", {
					{ "E0_height", str1_M},
					{ "p0", str2_M},
					{ "E1_height", str3_M}
			}}
		};
	}
	// 2 gamma peaks
	else {
		char str3_M[100], str4_M[100];
		sprintf(str3_M, "%g +- %g", DblResults.at(10), DblResults.at(16)); // E1_height
		sprintf(str4_M, "%g +- %g", DblResults.at(11), DblResults.at(17)); // E2_height
		j4 = {
			{ "Mean+-sqrt(variance)", {
					{ "E0_height", str1_M},
					{ "p0", str2_M},
					{ "E1_height", str3_M},
					{ "E2_height", str4_M}
			}}
		};
	}
	
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: 68% quantile ( L=lower; U=upper )
	char str1_68[100], str2_68[100];
	sprintf(str1_68, "[L_68, U_68] = [%g, %g]", DblResults.at(18), DblResults.at(19)); // E0_height
	sprintf(str2_68, "[L_68, U_68] = [%g, %g]", DblResults.at(20), DblResults.at(21)); // p0
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j5 = {
			{ "68-Quantile", {
					{ "E0_height", str1_68},
					{ "p0", str2_68}
			}}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		char str3_68[100];
		sprintf(str3_68, "[L_68, U_68] = [%g, %g]", DblResults.at(26), DblResults.at(27)); // E1_height
		j5 = {
			{ "68-Quantile", {
					{ "E0_height", str1_68},
					{ "p0", str2_68},
					{ "E1_height", str3_68}
			}}
		};
	}
	// 2 gamma peaks
	else {
		char str3_68[100], str4_68[100];
		sprintf(str3_68, "[L_68, U_68] = [%g, %g]", DblResults.at(26), DblResults.at(27)); // E1_height
		sprintf(str4_68, "[L_68, U_68] = [%g, %g]", DblResults.at(28), DblResults.at(29)); // E2_height
		j5 = {
			{ "68-Quantile", {
					{ "E0_height", str1_68},
					{ "p0", str2_68},
					{ "E1_height", str3_68},
					{ "E2_height", str4_68}
			}}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	if ( pol_degree == 1 ) {
		// p1 data
		char str5_PR[100], str5_GM[100], str5_M[100], str5_68[100];
		sprintf(str5_PR, "[%g, %g]", DblResults.at(36), DblResults.at(37));
		sprintf(str5_GM, "%g +- %g", p1_GM, p1_err_GM); 
		sprintf(str5_M, "%g +- %g", DblResults.at(8), DblResults.at(14)); 
		sprintf(str5_68, "[L_68, U_68] = [%g, %g]", DblResults.at(22), DblResults.at(23)); 

		j2["ParameterRange"]["p1"] = str5_PR;
		j3["GlobalMode"]["p1"] = str5_GM;
		j4["Mean+-sqrt(variance)"]["p1"] = str5_M;
		j5["68-Quantile"]["p1"] = str5_68;
	}
	if ( pol_degree == 2 ) {
		// p1 data
		char str5_PR[100], str5_GM[100], str5_M[100], str5_68[100];
		sprintf(str5_PR, "[%g, %g]", DblResults.at(36), DblResults.at(37));
		sprintf(str5_GM, "%g +- %g", p1_GM, p1_err_GM); 
		sprintf(str5_M, "%g +- %g", DblResults.at(8), DblResults.at(14)); 
		sprintf(str5_68, "[L_68, U_68] = [%g, %g]", DblResults.at(22), DblResults.at(23));
	
		j2["ParameterRange"]["p1"] = str5_PR;
		j3["GlobalMode"]["p1"] = str5_GM;
		j4["Mean+-sqrt(variance)"]["p1"] = str5_M;
		j5["68-Quantile"]["p1"] = str5_68;
		
		// p2 data
		char str6_PR[100], str6_GM[100], str6_M[100], str6_68[100];
		sprintf(str6_PR, "[%g, %g]", DblResults.at(38), DblResults.at(39));
		sprintf(str6_GM, "%g +- %g", p2_GM, p2_err_GM); 
		sprintf(str6_M, "%g +- %g", DblResults.at(9), DblResults.at(15));
		sprintf(str6_68, "[L_68, U_68] = [%g, %g]", DblResults.at(24), DblResults.at(25));
	
		j2["ParameterRange"]["p2"] = str6_PR;
		j3["GlobalMode"]["p2"] = str6_GM;
		j4["Mean+-sqrt(variance)"]["p2"] = str6_M;
		j5["68-Quantile"]["p2"] = str6_68;
	}
	
	
	//----------------------------------------------------------------------------------	
	// Array of the type: [ j1{...}, j2{...}, j3{...}, j4{...}, j5{...} ]	
	json j_arr = json::array({ j1 , j2, j3, j4, j5 });
	
	// Final JSON object
	json j_tot = {
		{ str, j_arr}
	};
	
	// Print data inside the JSON file
	file << j_tot;
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
