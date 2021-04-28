// **********************************************************************************************************************
// This file contains different functions that are called in the main source file ("runDataAnalysis.cxx") to draw
// with ROOT the energetic spectrum together with the fit result from BAT.
// **********************************************************************************************************************
#include "DrawPlots.h"
#include "Operations.h"



//=======================================================================================================================
// Draw f(x) = pol0(x)+gaus(x)
void Draw_Pol0(int energy, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[100];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1]", energy, FindSigma(energy));
	TF1 *f0 = new TF1("f0", function, xL, xR);
	f0->FixParameter(0, params.at(0));
	f0->FixParameter(1, params.at(1));
			    
	f0->SetLineWidth(2);
	f0->SetLineColor(2);
	f0->Draw("same");
			    
	h->SetTitle("Fit with pol0(x)+gaus(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol0.png", energy);
	c->Print(name_image);
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol0.root", energy);
	c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol0(x)+gaus(x)+gaus_gamma(x)
void Draw_Gamma_Pol0(int energy, double EG, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[100];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*TMath::Gaus(x, %f, %f, true)", energy, FindSigma(energy), EG, FindSigma(EG));
	TF1 *f0 = new TF1("f0", function, xL, xR);
	f0->FixParameter(0, params.at(0));
	f0->FixParameter(1, params.at(1));
	f0->FixParameter(2, params.at(2));
			    
	f0->SetLineWidth(2);
	f0->SetLineColor(2);
	f0->Draw("same");
			    
	h->SetTitle("Fit with pol0(x)+gaus(x)+gaus_gamma(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol0_%gGamma.png", energy, EG);
	c->Print(name_image);
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol0_%gGamma.root", energy, EG);
	c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol1(x)+gaus(x)
void Draw_Pol1(int energy, int xL, int xR, const std::vector<double> params, TH1D *h) {

        TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);
		    
	char function[100];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i)", energy, FindSigma(energy), energy);
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
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol1.png", energy);
	c->Print(name_image);
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol1.root", energy);
	c->Print(name_rootfile);     
}



//=======================================================================================================================
// Draw f(x) = pol1(x)+gaus(x)+gaus_gamma(x)
void Draw_Gamma_Pol1(int energy, double EG, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[200];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*TMath::Gaus(x, %f, %f, true)", energy, FindSigma(energy), energy, EG, FindSigma(EG));
	TF1 *f0 = new TF1("f0", function, xL, xR);
	f0->FixParameter(0, params.at(0));
	f0->FixParameter(1, params.at(1));
	f0->FixParameter(2, params.at(2));
	f0->FixParameter(3, params.at(3));
			    
	f0->SetLineWidth(2);
	f0->SetLineColor(2);
	f0->Draw("same");
			    
	h->SetTitle("Fit with pol1(x)+gaus(x)+gaus_gamma(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol1_%gGamma.png", energy, EG);
	c->Print(name_image);
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol1_%gGamma.root", energy, EG);
	c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol2(x)+gaus(x)
void Draw_Pol2(int energy, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);
	    	    
	char function[100];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*(x-%i)*(x-%i)", energy, FindSigma(energy), energy, energy, energy);
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
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol2.png", energy);
	c->Print(name_image);
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol2.root", energy);
	c->Print(name_rootfile);
}



//=======================================================================================================================
// Draw f(x) = pol2(x)+gaus(x)+gaus_gamma(x)
void Draw_Gamma_Pol2(int energy, double EG, int xL, int xR, const std::vector<double> params, TH1D *h) {

	TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	h->Draw();
	h->GetXaxis()->SetRangeUser(xL, xR);

	char function[200];
	sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*(x-%i)*(x-%i) + [4]*TMath::Gaus(x, %f, %f, true)", energy, FindSigma(energy), energy, energy, energy, EG, FindSigma(EG));
	TF1 *f2 = new TF1("f2", function, xL, xR);
	f2->FixParameter(0, params.at(0));
	f2->FixParameter(1, params.at(1));
	f2->FixParameter(2, params.at(2));
	f2->FixParameter(3, params.at(3));
	f2->FixParameter(4, params.at(4));
			    
	f2->SetLineWidth(2);
	f2->SetLineColor(2);
	f2->Draw("same");
			    
	h->SetTitle("Fit with pol2(x)+gaus(x)+gaus_gamma(x)");
	c->Update();
	char name_image[100];
	sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%iGausPol2_%gGamma.png", energy, EG);
	c->Print(name_image);
	char name_rootfile[100];
	sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%iGausPol2_%gGamma.root", energy, EG);
	c->Print(name_rootfile);
}
