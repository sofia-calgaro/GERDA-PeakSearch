#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace::std;

int FWHM() {

	TGraphErrors *g1 = new TGraphErrors("BEGe.txt", "%lg %lg %*lg");
	TGraphErrors *g2 = new TGraphErrors("coax.txt", "%lg %lg %*lg");
	TGraphErrors *g3 = new TGraphErrors("IC.txt", "%lg %lg %*lg");
	
	g1->GetXaxis()->SetTitle("Energy [keV]");
	g1->GetYaxis()->SetTitle("FWHM [keV]");
	g1->GetYaxis()->SetRangeUser(1.2, 2.6);
	g1->GetXaxis()->CenterTitle();
	g1->GetYaxis()->CenterTitle();
	g1->GetXaxis()->SetTitleSize(0.045);
	g1->GetXaxis()->SetLabelSize(0.045);
	g1->GetYaxis()->SetTitleSize(0.045);
	g1->GetYaxis()->SetLabelSize(0.045);
	
	g1->SetLineWidth(2);
	g2->SetLineWidth(2);
	g3->SetLineWidth(2);
	
	g1->SetLineColor(kBlue+1);
	g2->SetLineColor(kRed+1);
	g3->SetLineColor(kGreen+2);
	
	g1->Draw("AL");
	g2->Draw("same");
	g3->Draw("same");

	auto *legend1 = new TLegend(.15, .75, .38, .88);
	legend1->AddEntry(g1, "EnrBEGe detectors", "l");
	legend1->AddEntry(g2, "EnrCoax detectors", "l");
	legend1->AddEntry(g3, "IC detectors", "l");
	legend1->SetBorderSize(0);
	legend1->Draw();

	return 0;
}
