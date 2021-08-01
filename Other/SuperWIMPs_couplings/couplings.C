#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace::std;

int single() {

	int ans0;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> ans0;

	// open file for coupling strength results
	fstream fileDP;
	fileDP.open("vector.txt", ios::out);
	fstream fileALP;
	fileALP.open("pseudoscalar.txt", ios::out);
	
	// import Ge cross sections (reported in [barns/atoms])
	fstream file2;
	file2.open("Ge_CrossSection.txt", ios::in);
	const int rows = 941;
	const int columns = 2;
	double Ge_CS[rows][columns];
	for ( int i=0; i<rows; i++ ) {
		for ( int j=0; j<columns; j++ ) {
			file2 >> Ge_CS[i][j];
		}
	}
	file2.close();
	
	// Ge cross section in [barns]; Ge-detector masses are expressed in [g]
	const double mass_EnrCoax = 19.362*1000;
	const double mass_BEGe = 15.576*1000;
	const double mass_IC = 7.8016*1000;
	const double molar_mass_GE = 72.64;
	
	const double moles_EnrCoax = mass_EnrCoax/molar_mass_GE;
	const double moles_BEGe = mass_BEGe/molar_mass_GE;
	const double moles_IC = mass_IC/molar_mass_GE;
	
	const double AvogadroNumber = 6.0221409*pow(10,23);
	double atoms_EnrCoax=0, atoms_BEGe=0, atoms_IC=0;
	/*
	for ( int i=0; i<rows; i++ ) {
	if (i<5) cout << "after [b/at] = " << Ge_CS[i][1]; 
		if ( ans0==0 ) {
			atoms_EnrCoax = moles_EnrCoax * AvogadroNumber;
			Ge_CS[i][1] = Ge_CS[i][1]*atoms_EnrCoax;
		}
		if ( ans0==1 ) {
			atoms_BEGe = moles_BEGe * AvogadroNumber;
			Ge_CS[i][1] = Ge_CS[i][1]*atoms_BEGe;
			if (i<5) cout << "\tatoms_BEGe = " << atoms_BEGe;
		}
		if ( ans0==2 ) {
			atoms_IC = moles_IC * AvogadroNumber;
			Ge_CS[i][1] = Ge_CS[i][1]*atoms_IC;
		}
	if (i<5) cout << "\tbefore [b] = " << Ge_CS[i][1] << endl; 	
	}*/
	
	
	// import upper limits at 90%
	char filename3[200];
	if ( ans0==0 ) { sprintf(filename3, "UpperLimit_EnrCoax.txt"); }
	if ( ans0==1 ) { sprintf(filename3, "UpperLimit_BEGe.txt"); }
	if ( ans0==2 ) { sprintf(filename3, "UpperLimit_IC.txt"); }
	
	fstream file3;
	file3.open(filename3, ios::in);
	double R90[rows][columns];
	for ( int i=0; i<rows; i++ ) {
		for ( int j=0; j<columns; j++ ) {
			file3 >> R90[i][j];
		}
	}
	file3.close();
	
	// import total efficiencies
	ifstream file4("/home/sofia/Analysis/SuperWIMPs_couplings/efficiency_Rizalina/TotEnCorrectionLAr.json");
	json j_read;
	file4 >> j_read;
	file4.close();	
	
	// Calculation of Super-WIMP coupling strengths
	for ( int E0=60; E0<=1000; E0++ ) {
	
		double tot_eff = 0.0;
		if ( ans0==0 ) { tot_eff = j_read["enrCoax"][E0-40].get<double>(); }
		if ( ans0==1 ) { tot_eff = j_read["enrBEGe"][E0-40].get<double>(); }
		if ( ans0==2 ) { tot_eff = 1; }
	
		int line = E0-60;
		double exposure = 0.0;
		if ( ans0==0 ) {
			if ( E0<195 ) { exposure = 20.6817*365; }
			if ( E0>=195 ) { exposure = 41.8461*365; }
		}
		if ( ans0==1 ) {
			if ( E0<165 ) { exposure = 30.7507*365; }
			if ( E0>=165 ) { exposure = 55.8458*365; }
		}
		if ( ans0==2 ) { exposure = 8.702; }
		
		const int A = 76;
		
		double vector_num = R90[line][1]*A*tot_eff*E0;
		double vector = vector_num / ( exposure*4*pow(10,23)*Ge_CS[line][1] ); // alpha'/alpha
			
		double pseudoscalar_num = R90[line][1]*A*tot_eff;
		double pseudoscalar = sqrt( pseudoscalar_num / ( exposure*1.29*pow(10,19)*Ge_CS[line][1]*E0 ) ); // g_ae
		
		fileDP << E0 << "\t" << vector << endl;
		fileALP << E0 << "\t" << pseudoscalar << endl;
	}
	fileDP.close();
	fileALP.close();
	
	//===============================================================================
	// PLot: vector super-WIMPs
	TCanvas *c1 = new TCanvas("c1","c1",1700,1000);
	c1->SetLogy();
	c1->SetLogx();
	TGraphErrors *gDP = new TGraphErrors("vector.txt");
	gDP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gDP->GetYaxis()->SetTitle("Kinetic mixing strength, #alpha'/#alpha");
	gDP->GetYaxis()->SetTitleOffset(1.1);
	gDP->GetXaxis()->CenterTitle();
	gDP->GetYaxis()->CenterTitle();
	gDP->GetXaxis()->SetTitleSize(0.045);
	gDP->GetXaxis()->SetLabelSize(0.045);
	gDP->GetYaxis()->SetTitleSize(0.045);
	gDP->GetYaxis()->SetLabelSize(0.045);
	gDP->SetTitle("");
	gDP->Draw();
	
	auto *legend1 = new TLegend(.15, .75, .38, .88);
	char title1[200];
	if ( ans0==0 ) { sprintf(title1, "EnrCoax upper limit"); gDP->SetLineColor(kRed+1); }
	if ( ans0==1 ) { sprintf(title1, "EnrBEGe upper limit"); gDP->SetLineColor(kBlue+1); }
	if ( ans0==2 ) { sprintf(title1, "IC upper limit"); gDP->SetLineColor(kGreen+2); }
	legend1->AddEntry(gDP, title1, "l");
	legend1->SetBorderSize(0);
	legend1->Draw();

	//===============================================================================	
	// PLot: pseudoscalar super-WIMPs
	TCanvas *c2 = new TCanvas("c2","c2",1700,1000);
	c2->SetLogy();
	c2->SetLogx();
	TGraphErrors *gALP = new TGraphErrors("pseudoscalar.txt");
	gALP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gALP->GetYaxis()->SetTitle("Axion-electron coupling, g_{ae}");
	gALP->GetYaxis()->SetTitleOffset(1.1);
	gALP->GetXaxis()->CenterTitle();
	gALP->GetYaxis()->CenterTitle();
	gALP->GetXaxis()->SetTitleSize(0.045);
	gALP->GetXaxis()->SetLabelSize(0.045);
	gALP->GetYaxis()->SetTitleSize(0.045);
	gALP->GetYaxis()->SetLabelSize(0.045);
	gALP->SetTitle("");
	gALP->Draw();

	auto *legend2 = new TLegend(.15, .75, .38, .88);
	char title2[200];
	if ( ans0==0 ) { sprintf(title2, "EnrCoax upper limit"); gALP->SetLineColor(kRed+1); }
	if ( ans0==1 ) { sprintf(title2, "EnrBEGe upper limit"); gALP->SetLineColor(kBlue+1); }
	if ( ans0==2 ) { sprintf(title2, "IC upper limit"); gALP->SetLineColor(kGreen+2); }
	legend2->AddEntry(gALP, title2, "l");
	legend2->SetBorderSize(0);
	legend2->Draw();
	
	
	return 0;
}




int all() {

	// import Ge cross sections (reported in [barns/atoms])
	fstream file2;
	file2.open("Ge_CrossSection.txt", ios::in);
	const int rows = 941;
	const int columns = 2;
	double Ge_CS[rows][columns];
	for ( int i=0; i<rows; i++ ) {
		for ( int j=0; j<columns; j++ ) {
			file2 >> Ge_CS[i][j];
		}
	}
	file2.close();
	
	// import total efficiencies
	ifstream file4("/home/sofia/Analysis/SuperWIMPs_couplings/efficiency_Rizalina/TotEnCorrectionLAr.json");
	json j_read;
	file4 >> j_read;
	file4.close();	
	
	// Ge cross section in [barns]; Ge-detector masses are expressed in [g]
	const double mass_EnrCoax = 19.362*1000;
	const double mass_BEGe = 15.576*1000;
	const double mass_IC = 7.8016*1000;
	const double molar_mass_GE = 72.64;
	
	const double moles_EnrCoax = mass_EnrCoax/molar_mass_GE;
	const double moles_BEGe = mass_BEGe/molar_mass_GE;
	const double moles_IC = mass_IC/molar_mass_GE;

	double couplings[rows][7];


	for ( int ans0=0; ans0<=2; ans0++ ) {
		
		const double AvogadroNumber = 6.0221409*pow(10,23);
		double atoms_EnrCoax=0, atoms_BEGe=0, atoms_IC=0;
		
		/*for ( int i=0; i<rows; i++ ) {
			if ( ans0==0 ) {
				atoms_EnrCoax = moles_EnrCoax * AvogadroNumber;
				Ge_CS[i][1] = Ge_CS[i][1]*atoms_EnrCoax;
			}
			if ( ans0==1 ) {
				atoms_BEGe = moles_BEGe * AvogadroNumber;
				Ge_CS[i][1] = Ge_CS[i][1]*atoms_BEGe;
			}
			if ( ans0==2 ) {
				atoms_IC = moles_IC * AvogadroNumber;
				Ge_CS[i][1] = Ge_CS[i][1]*atoms_IC;
			}
		}*/
		
		
		// import upper limits at 90%
		char filename3[200];
		if ( ans0==0 ) { sprintf(filename3, "UpperLimit_EnrCoax.txt"); }
		if ( ans0==1 ) { sprintf(filename3, "UpperLimit_BEGe.txt"); }
		if ( ans0==2 ) { sprintf(filename3, "UpperLimit_IC.txt"); }
		
		fstream file3;
		file3.open(filename3, ios::in);
		double R90[rows][columns];
		for ( int i=0; i<rows; i++ ) {
			for ( int j=0; j<columns; j++ ) {
				file3 >> R90[i][j];
			}
		}
		file3.close();
		
		// Calculation of Super-WIMP coupling strengths
		for ( int E0=60; E0<=1000; E0++ ) {
		
			double tot_eff = 0.0;
			if ( ans0==0 ) { tot_eff = j_read["enrCoax"][E0-40].get<double>(); }
			if ( ans0==1 ) { tot_eff = j_read["enrBEGe"][E0-40].get<double>(); }
			if ( ans0==2 ) { tot_eff = 1; }
		
			int line = E0-60;
			double exposure = 0.0;
			if ( ans0==0 ) {
				if ( E0<195 ) { exposure = 20.6817*365; }
				if ( E0>=195 ) { exposure = 41.8461*365; }
			}
			if ( ans0==1 ) {
				if ( E0<165 ) { exposure = 30.7507*365; }
				if ( E0>=165 ) { exposure = 55.8458*365; }
			}
			if ( ans0==2 ) { exposure = 8.702; }
			
			const int A = 76;
			
			double vector_num = R90[line][1]*A*tot_eff*E0;
			double vector = vector_num / ( exposure*4*pow(10,23)*Ge_CS[line][1] ); // alpha'/alpha
			
			double pseudoscalar_num = R90[line][1]*A*tot_eff;
			double pseudoscalar = sqrt( pseudoscalar_num / ( exposure*1.29*pow(10,19)*Ge_CS[line][1]*E0 ) ); // g_ae
			
			if ( ans0==0 ) {
				couplings[line][1] = vector ;
				couplings[line][2] = pseudoscalar ;
			}
			if ( ans0==1 ) {
				couplings[line][3] = vector ;
				couplings[line][4] = pseudoscalar ;
			}
			if ( ans0==2 ) {
				couplings[line][5] = vector ;
				couplings[line][6] = pseudoscalar ;
			}
			couplings[line][0] = E0;
		} // for EO
	} // for ans0
	
	fstream output;
	output.open("output.txt", ios::out);
	for ( int i=0; i<941; i++ ) {
		output << couplings[i][0] << "\t" << couplings[i][1] << "\t" << couplings[i][2] << "\t" << couplings[i][3] << "\t" << couplings[i][4] << "\t" << couplings[i][5] << "\t" << couplings[i][6] << endl;
	}
	output.close();
	
	//=============================================================================== VECTOR
	// PLot: EnrCoax
	TCanvas *c1 = new TCanvas("c1","c1",1700,1000);
	c1->SetLogy();
	c1->SetLogx();
	TGraphErrors *g0 = new TGraphErrors("output.txt", "%lg %lg %*lg %*lg %*lg %*lg %*lg");
	g0->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	g0->GetYaxis()->SetTitle("Kinetic mixing strength, #alpha'/#alpha");
	g0->GetYaxis()->SetTitleOffset(1.1);
	g0->GetXaxis()->CenterTitle();
	g0->GetYaxis()->CenterTitle();
	g0->GetXaxis()->SetTitleSize(0.045);
	g0->GetXaxis()->SetLabelSize(0.045);
	g0->GetYaxis()->SetTitleSize(0.045);
	g0->GetYaxis()->SetLabelSize(0.045);
	g0->SetTitle("");
	g0->SetLineColor(kRed+1);
	g0->Draw();
	
	// PLot: EnrBEGe
	TGraphErrors *g1 = new TGraphErrors("output.txt", "%lg %*lg %*lg %lg %*lg %*lg %*lg");
	g1->SetLineColor(kBlue+1);
	g1->Draw("same");
	
	// PLot: IC
	//TGraphErrors *g2 = new TGraphErrors("output.txt", "%lg %*lg %*lg %*lg %*lg %lg %*lg");
	//g2->SetLineColor(kGreen+2);
	//g2->Draw("same");
	
	auto *legend1 = new TLegend(.15, .75, .38, .88);
	legend1->AddEntry(g0, "EnrCoax upper limit", "l");
	legend1->AddEntry(g1, "EnrBEGe upper limit", "l");
	//legend1->AddEntry(g2, "IC upper limit", "l");
	legend1->SetBorderSize(0);
	legend1->Draw();
	
	c1->Update();
	c1->SaveAs("vector.png");

	//=============================================================================== PSEUDOSCALAR
	// PLot: EnrCoax
	TCanvas *c2 = new TCanvas("c2","c2",1700,1000);
	c2->SetLogy();
	c2->SetLogx();
	TGraphErrors *g3 = new TGraphErrors("output.txt", "%lg %*lg %lg %*lg %*lg %*lg %*lg");
	g3->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	g3->GetYaxis()->SetTitle("Axion-electron coupling, g_{ae}");
	g3->GetYaxis()->SetTitleOffset(1.1);
	g3->GetXaxis()->CenterTitle();
	g3->GetYaxis()->CenterTitle();
	g3->GetXaxis()->SetTitleSize(0.045);
	g3->GetXaxis()->SetLabelSize(0.045);
	g3->GetYaxis()->SetTitleSize(0.045);
	g3->GetYaxis()->SetLabelSize(0.045);
	g3->SetTitle("");
	g3->SetLineColor(kRed+1);
	g3->Draw();
	
	// PLot: EnrBEGe
	TGraphErrors *g4 = new TGraphErrors("output.txt", "%lg %*lg %*lg %*lg %lg %*lg %*lg");
	g4->SetLineColor(kBlue+1);
	g4->Draw("same");
	
	// PLot: IC
	//TGraphErrors *g5 = new TGraphErrors("output.txt", "%lg %*lg %*lg %*lg %*lg %*lg %lg");
	//g5->SetLineColor(kGreen+2);
	//g5->Draw("same");
	
	auto *legend2 = new TLegend(.15, .75, .38, .88);
	legend2->AddEntry(g3, "EnrCoax upper limit", "l");
	legend2->AddEntry(g4, "EnrBEGe upper limit", "l");
	//legend2->AddEntry(g5, "IC upper limit", "l");
	legend2->SetBorderSize(0);
	legend2->Draw();
	
	c2->Update();
	c2->SaveAs("psuedoscalar.png");
	
	return 0;
}
