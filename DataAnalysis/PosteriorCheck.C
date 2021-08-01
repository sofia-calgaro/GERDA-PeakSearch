// **********************************************************************************************************************
// This file studies the marginalized posteriors for p0, p1, p2 parameters that enter into the BKG model.
// The output is wrote into a file:
// 	- 0 means everything was OK;
//	- 1 means that the posterior is cut.
//
// Values are written in column:
// 	- the first line refers to p0;
// 	- the second line refers to p1;
// 	- the third line refers to p2.
//
// An example of problems with p1 is:
//
// 				=============== check_posterior.txt ===============
//				   >  0
//				   >  1
//				   >  0
// 				===================================================
//
// **********************************************************************************************************************
#include <iostream>
#include <fstream>
#include <string>

void PosteriorCheck(int E0, int pol_degree, int outputK, const char *root_file) {

	char name[200];
	sprintf(name,"MarginalizedROOT/%i%s.root", E0, root_file);
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
	
	// study of the 1st and last bin content
	int p0FirstBin=0, p0LastBin=0, p1FirstBin=0, p1LastBin=0, p2FirstBin=0, p2LastBin=0;
	p0FirstBin = hp0->GetBinContent(1);
	p0LastBin = hp0->GetBinContent(hp0->GetNbinsX());
	if ( pol_degree==1 ) {
		p1FirstBin = hp1->GetBinContent(1);
		p1LastBin = hp1->GetBinContent(hp1->GetNbinsX());
	}
	if ( pol_degree==2 ) {
		p1FirstBin = hp1->GetBinContent(1);
		p1LastBin = hp1->GetBinContent(hp1->GetNbinsX());
		p2FirstBin = hp2->GetBinContent(1);
		p2LastBin = hp2->GetBinContent(hp2->GetNbinsX());
	}
	
	int E0LastBin=0, E1LastBin=0, E2LastBin=0;
	E0LastBin = hE0->GetBinContent(hE0->GetNbinsX());
	if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
		E1LastBin = hE1->GetBinContent(hE1->GetNbinsX());
	}
	if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		E1LastBin = hE1->GetBinContent(hE1->GetNbinsX());
		E2LastBin = hE2->GetBinContent(hE2->GetNbinsX());
	}
	
	int ck0=0, ck1=0, ck2=0, ckE0=0, ckE1=0, ckE2=0;
	if ( p0FirstBin!=0 || p0LastBin!=0 ) { ck0 = 1; }
	if ( p1FirstBin!=0 || p1LastBin!=0 ) { ck1 = 1; }
	if ( p2FirstBin!=0 || p2LastBin!=0 ) { ck2 = 1; }
	if ( E0LastBin!=0 ) { ckE0 = 1; }
	if ( E1LastBin!=0 ) { ckE1 = 1; }
	if ( E2LastBin!=0 ) { ckE2 = 1; }

	
	std::fstream file_out;
	file_out.open("check_posterior.txt",std::ios::out);
	file_out << ck0 << "\n" << ck1 << "\n" << ck2 << "\n" << ckE0 << "\n" << ckE1 << "\n" << ck2;
	file_out.close();
}


