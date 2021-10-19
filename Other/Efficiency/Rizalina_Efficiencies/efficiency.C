#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace::std;

int efficiency() {

	int ans0;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> ans0;
	
	// import total efficiencies
	ifstream file4("/home/sofia/Analysis/SuperWIMPs_couplings/efficiency_Rizalina/TotEnCorrectionLAr.json");
	json j_read;
	file4 >> j_read;
	file4.close();	
	
	fstream file;
	file.open("eff.txt", ios::out);
	
	// Calculation of Super-WIMP coupling strengths
	for ( int E0=60; E0<=1000; E0++ ) {
	
		double tot_eff = 0.0;
		if ( (E0%30==0 && E0<200) || (E0%50==0 && E0>=200)  ) {
			if ( ans0==0 ) { tot_eff = j_read["enrCoax"][E0-40].get<double>(); }
			if ( ans0==1 ) { tot_eff = j_read["enrBEGe"][E0-40].get<double>(); }
			file << E0 << "\t" << tot_eff << endl;
		}
	}
	file.close();
	
	//===============================================================================
	// PLot: vector super-WIMPs
	TCanvas *c1 = new TCanvas("c1","c1",1700,1000);
	TGraphErrors *g = new TGraphErrors("eff.txt");
	g->GetXaxis()->SetTitle("Energy [keV]");
	g->GetYaxis()->SetTitle("Total efficiency");
	g->SetMarkerStyle(20);
	g->Draw("AP");	
	
	return 0;
}

