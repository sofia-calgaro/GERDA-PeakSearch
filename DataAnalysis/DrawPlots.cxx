// **********************************************************************************************************************
// This file contains different functions that are called in the main source file ("runDataAnalysis.cxx") to draw
// with ROOT the energetic spectrum together with the fit result from BAT.
// **********************************************************************************************************************
#include "DrawPlots.h"
#include "Operations.h"



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
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol0_%gGamma.root", E0, EG);
	c->Print(name_rootfile);
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
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol0_%gGamma_%gGamma.root", E0, EG, EG_2);
	c->Print(name_rootfile);
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
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol1.root", E0);
	c->Print(name_rootfile);     
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
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol1_%gGamma.root", E0, EG);
	c->Print(name_rootfile);
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
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol1_%gGamma_%gGamma.root", E0, EG, EG_2);
	c->Print(name_rootfile);
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
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol2.root", E0);
	c->Print(name_rootfile);
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
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol2_%gGamma.root", E0, EG);
	c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol2(x)+gaus(x)+gaus_gamma(x)+gaus_gamma_2(x)
void Draw_TwoGamma_Pol2(int E0, double EG, double EG_2, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[200];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*(x-%i)*(x-%i) + [4]*TMath::Gaus(x, %f, %f, true)+ + [5]*TMath::Gaus(x, %f, %f, true)", E0, FindSigma(E0), E0, E0, E0, EG, FindSigma(EG), EG_2, FindSigma(EG_2));
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
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol2_%gGamma_%gGamma.root", E0, EG, EG_2);
	c->Print(name_rootfile);
}
