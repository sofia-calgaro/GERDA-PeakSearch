// Available functions:
//	- draw_efficiency(int det, int phase): to plot Kat and extrapolated efficiencies together
//	- int Efficiency_extrapolation(): to extrapolate efficiencies for each detector and Phase
//	- single(): plot the single dataset
//	- combined(): plot the 2/3 datasets combined
//	- rizalina_inverse(): to get R_tot from old results
//	- ratio_GERDA(): to plot the percentage variation between new and old results

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace::std;
//-------------------------------------------------------------------------------------------------------------------------------------
int draw_efficiency(int det, int phase) {

	char filename[200], filename2[200];
	// Phase II+
	if ( phase==0 ) { 
		if ( det==0 ) sprintf(filename, "eff_enrCoax_phIIp.txt");
		if ( det==1 ) sprintf(filename, "eff_enrBEGe_phIIp.txt");
		if ( det==2 ) sprintf(filename, "eff_invCoax_phIIp.txt");
	}
	if ( phase==0 ) { 
		if ( det==0 ) sprintf(filename2, "/home/sofia/Analysis/Efficiency/FepEff_phaseIIp_enrCoax.txt");
		if ( det==1 ) sprintf(filename2, "/home/sofia/Analysis/Efficiency/FepEff_phaseIIp_enrBEGe.txt");
		if ( det==2 ) sprintf(filename2, "/home/sofia/Analysis/Efficiency/FepEff_phaseIIp_invCoax.txt");
	}
	// Phase II
	if ( phase==1 ) { 
		if ( det==0 ) sprintf(filename, "eff_enrCoax_phII.txt");
		if ( det==1 ) sprintf(filename, "eff_enrBEGe_phII.txt");
		if ( det==2 ) {}
	}
	if ( phase==1 ) { 
		if ( det==0 ) sprintf(filename2, "/home/sofia/Analysis/Efficiency/FepEff_phaseII_enrCoax.txt");
		if ( det==1 ) sprintf(filename2, "/home/sofia/Analysis/Efficiency/FepEff_phaseII_enrBEGe.txt");
		if ( det==2 ) {}
	}	
	
	TCanvas *c = new TCanvas();
	TMultiGraph *mg = new TMultiGraph();
	
	TGraphErrors *g1 = new TGraphErrors(filename); // Extrapolated
	g1->SetMarkerStyle(7);
	mg->Add(g1);
	
	TGraphErrors *g2 = new TGraphErrors(filename2, "%lg %*lg %lg %*lg %*lg"); //Katharina
	g2->SetLineColor(2);
	g2->SetMarkerColor(2);
	g2->SetMarkerStyle(20);
	g2->SetMarkerSize(1);
	mg->Add(g2);
	
	mg->Draw("AP");
	
	auto *legend_0 = new TLegend(.7, .4, .89, .58);
	legend_0->AddEntry(g1, "Extrapolated", "p");
	legend_0->AddEntry(g2, "Katharina", "p");
	legend_0->Draw();

	return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------------
int Efficiency_extrapolation() {
	
	for ( int det=0; det<=2; det++ ) {
		for ( int phase=0; phase<=1; phase++ ) {
		
			char filename4[200];
			// Phase II+
			if ( phase==0 ) { 
				if ( det==0 ) sprintf(filename4, "/home/sofia/Analysis/Efficiency/FepEff_phaseIIp_enrCoax.txt"); 
				if ( det==1 ) sprintf(filename4, "/home/sofia/Analysis/Efficiency/FepEff_phaseIIp_enrBEGe.txt"); 
				if ( det==2 ) sprintf(filename4, "/home/sofia/Analysis/Efficiency/FepEff_phaseIIp_invCoax.txt"); 
			}
			// Phase II
			if ( phase==1 ) { 
				if ( det==0 ) sprintf(filename4, "/home/sofia/Analysis/Efficiency/FepEff_phaseII_enrCoax.txt"); 
				if ( det==1 ) sprintf(filename4, "/home/sofia/Analysis/Efficiency/FepEff_phaseII_enrBEGe.txt"); 
				if ( det==2 ) {}
			}		
		
			ifstream file4(filename4);
			const int rows4 = 97;
			const int columns4 = 5;
			double eff_sim[rows4][columns4];
			for ( int i=0; i<rows4; i++ ) {
				for ( int j=0; j<columns4; j++ ) {
					file4 >> eff_sim[i][j];
				}
			}
			file4.close();
			
			double eff_lar[941][2] = {0};
			
			char outputname[200];
			if ( phase==0 ) {
				if ( det==0 ) sprintf(outputname, "eff_enrCoax_phIIp.txt");
				if ( det==1 ) sprintf(outputname, "eff_enrBEGe_phIIp.txt");
				if ( det==2 ) sprintf(outputname, "eff_invCoax_phIIp.txt");
			}
			if ( phase==1 ) {
				if ( det==0 ) sprintf(outputname, "eff_enrCoax_phII.txt");
				if ( det==1 ) sprintf(outputname, "eff_enrBEGe_phII.txt");
				if ( det==2 ) continue;
			}
			ofstream output(outputname);
			
			// extrapolation
			for ( int i=0; i<rows4-1; i++ ) {
				int k = i+1;
				if ( i==10 && det==0 ) k = i + 2;
				if ( i==11 && det==0 ) continue;
			
				int limit = 10;
				if ( (i==10 || i==11) && det!=0 ) limit = 5;
				if ( i==14 || i==15 ) limit = 5;
				if ( i==rows4-2 ) limit = 11;
				
				int j = 0;
				while ( j<limit ) {
					double x = eff_sim[i][0] + j;
					double x1 = eff_sim[i][0];
					double x2 = eff_sim[k][0];
					double y1 = eff_sim[i][2];
					double y2 = eff_sim[k][2];
					double y = 0.0;
					if ( j!=0 ) { y = ( (x-x1)/(x2-x1) ) * (y2-y1) + y1; } // extrapolated efficiencies
					else { y = eff_sim[i][2]; } // real efficiencies
					j++;
					output << x << "\t\t" << y << endl;
				}			
			}
			output.close();		
		}
	}
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int single() {

	int det;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> det;
	
	int phase;
	cout << " Phase II+ (0) or II (1)? ";
	cin >> phase;
	
	
	int gerda;
	cout << " Old GERDA results: yes (0) or no (1)? ";
	cin >> gerda;

	// open file for coupling strength results
	char filename_DP[200], filename_ALP[200];
	if ( det==0 ) { sprintf(filename_DP, "vector_enrCoax.txt"); sprintf(filename_ALP, "pseudo_enrCoax.txt"); }
	if ( det==1 ) { sprintf(filename_DP, "vector_enrBEGe.txt"); sprintf(filename_ALP, "pseudo_enrBEGe.txt"); }
	if ( det==2 ) { sprintf(filename_DP, "vector_invCoax.txt"); sprintf(filename_ALP, "pseudo_invCoax.txt"); }
	fstream fileDP;
	fileDP.open(filename_DP, ios::out);
	fstream fileALP;
	fileALP.open(filename_ALP, ios::out);
	
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
	/*const double mass_EnrCoax = 19.362*1000;
	const double mass_BEGe = 15.576*1000;
	const double mass_IC = 7.8016*1000;
	const double molar_mass_GE = 72.64;
	
	const double moles_EnrCoax = mass_EnrCoax/molar_mass_GE;
	const double moles_BEGe = mass_BEGe/molar_mass_GE;
	const double moles_IC = mass_IC/molar_mass_GE;
	
	const double AvogadroNumber = 6.0221409*pow(10,23);
	double atoms_EnrCoax=0, atoms_BEGe=0, atoms_IC=0;
	
	for ( int i=0; i<rows; i++ ) {
	if (i<5) cout << "after [b/at] = " << Ge_CS[i][1]; 
		if ( det==0 ) {
			atoms_EnrCoax = moles_EnrCoax * AvogadroNumber;
			Ge_CS[i][1] = Ge_CS[i][1]*atoms_EnrCoax;
		}
		if ( det==1 ) {
			atoms_BEGe = moles_BEGe * AvogadroNumber;
			Ge_CS[i][1] = Ge_CS[i][1]*atoms_BEGe;
			if (i<5) cout << "\tatoms_BEGe = " << atoms_BEGe;
		}
		if ( det==2 ) {
			atoms_IC = moles_IC * AvogadroNumber;
			Ge_CS[i][1] = Ge_CS[i][1]*atoms_IC;
		}
	if (i<5) cout << "\tbefore [b] = " << Ge_CS[i][1] << endl; 	
	}*/
	
	// extrapolate efficiencies
	int files_creation = Efficiency_extrapolation();
	// import efficiencies
	char filename3[200], filename6[200];
	if ( det==0 ) sprintf(filename3, "eff_enrCoax_phIIp.txt"); 
	if ( det==1 ) sprintf(filename3, "eff_enrBEGe_phIIp.txt"); 
	if ( det==2 ) sprintf(filename3, "eff_invCoax_phIIp.txt"); 
	
	if ( det==0 ) sprintf(filename6, "eff_enrCoax_phII.txt"); 
	if ( det==1 ) sprintf(filename6, "eff_enrBEGe_phII.txt"); 
	
	ifstream file3(filename3);
	double eff_fep_IIp[941][2];
	for ( int i=0; i<941; i++ ) {
		for ( int j=0; j<2; j++ ) {
			file3 >> eff_fep_IIp[i][j];
		}
	}
	file3.close();
	ifstream file6(filename6);
	double eff_fep[941][2];
	for ( int i=0; i<941; i++ ) {
		for ( int j=0; j<2; j++ ) {
			file6 >> eff_fep[i][j];
		}
	}
	file6.close();	
	
	
	//--------------------------------------------------------------------------------------------------------------------------------
	// Calculation of Super-WIMP coupling strengths
	for ( int E0=60; E0<=1000; E0++ ) {
	
		char filename5[200];
		// Phase II+
		if ( phase==0 ) { 
			if ( det==0 ) sprintf(filename5, "/home/sofia/Analysis/Data2/JsonFiles/53_114/coax_PSD/JsonFile%i.json", E0); 
			if ( det==1 ) sprintf(filename5, "/home/sofia/Analysis/DataAnalysis/JsonFiles/53_114/BEGe/JsonFile%i.json", E0); 
			if ( det==2 ) sprintf(filename5, "/home/sofia/Analysis/DataAnalysis/JsonFiles/53_114/IC_PSD/JsonFile%i.json", E0); 
		}
		// Phase II
		if ( phase==1 ) { 
			if ( det==0 ) sprintf(filename5, "/home/sofia/Analysis/Data2/JsonFiles/coax_PSD/JsonFile%i.json", E0); 
			if ( det==1 ) sprintf(filename5, "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe_PSD/JsonFile%i.json", E0); 
			if ( det==2 ) {}
		}
		ifstream file5(filename5);
		json j_read5;
		file5 >> j_read5;
		file5.close();
	
		double exposure = 0.0;
		if ( phase==0 ) {
			if ( det==0 ) {
				if ( E0<195 ) { exposure = 20.6676*365.25; }
				if ( E0>=195 ) { exposure = 41.8177*365.25; }
			}
			if ( det==1 ) {
				if ( E0<195 ) { exposure = 30.5489*365.25; }
				if ( E0>=195 ) { exposure = 54.9284*365.25; }
			}
			if ( det==2 ) { exposure = 8.58872*365.25; }
		}
		if ( phase==1 ) {
			if ( det==0 ) {
				if ( E0<195 ) { exposure = 7.4881*365.25; }
				if ( E0>=195 ) { exposure = 28.6383*365.25; }
			}
			if ( det==1 ) {
				if ( E0<195 ) { exposure = 8.28657*365.25; }
				if ( E0>=195 ) { exposure = 31.4597*365.25; }
			}
			if ( det==2 ) { }
		}
		
		const double A = 75.921492725; // atomic mass
		int row = E0 - 60; // arrays start from 0, not from 60 [ since the loop over energies is for( i=60; i<=1000; i++)]
		double cts90 = j_read5["90UpperLimit"]["E0_counts_U90"].get<double>(); // 90% C.I. upper limits (in [counts])
		double R90 = cts90 / exposure; // signal counting rate; exposure is in [kg*days]
		
		// vector superWIMPs
		double vector_num = 0;
		if ( phase==0 && det!=2 ) vector_num = R90 * A * (1-eff_fep[row][1]) * (1-eff_fep_IIp[row][1]) * E0;
		if ( phase==0 && det==2 ) vector_num = R90 * A * (1-eff_fep_IIp[row][1]) * E0;
		if ( phase==1 ) vector_num = R90 * A * (1-eff_fep[row][1]) * E0;
		double vector_den = 4 * 1e23 * Ge_CS[row][1];
		double alpha = vector_num / vector_den; 
		
		// pseudoscalar superWIMPs
		double pseudoscalar_num = 0;
		if ( phase==0 && det!=2 ) pseudoscalar_num = R90 * A * (1-eff_fep[row][1]) * (1-eff_fep_IIp[row][1]);
		if ( phase==0 && det==2 ) pseudoscalar_num = R90 * A * (1-eff_fep_IIp[row][1]);
		if ( phase==1 ) pseudoscalar_num = R90 * A * (1-eff_fep[row][1]);
		double pseudoscalar_den = 1.29 * 1e19 * Ge_CS[row][1] * E0;
		double g_ae = sqrt( pseudoscalar_num / pseudoscalar_den ); 
		
		fileDP << E0 << "\t" << alpha << endl;
		fileALP << E0 << "\t" << g_ae << endl;
		
		if ( E0==200 ) {
			cout << "E0 =" << E0 << endl;
			cout << "cts90 = " << cts90 << endl;
			cout << "A = " << A << endl;
			cout << "exposure = " << exposure << endl;
			cout << "eff_fep[row][1] = " << eff_fep[row][1] << endl;
			cout << "Ge_CS[row][1] = " << Ge_CS[row][1] << endl;
			cout << "alpha = " << alpha << endl;
			cout << "alpha*sigma_ge = " << alpha*Ge_CS[row][1] << endl;
			cout << "g_ae = " << g_ae << endl;
		}
	}
	fileDP.close();
	fileALP.close();
	
	//===============================================================================
	// PLot: vector super-WIMPs
	TCanvas *c1 = new TCanvas("c1", "c1", 1700, 1000);
	c1->SetLogy();
	c1->SetLogx();
	TGraphErrors *gDP = new TGraphErrors(filename_DP);
	gDP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gDP->GetYaxis()->SetTitle("Kinetic mixing strength, #alpha'/#alpha");
	gDP->GetYaxis()->SetTitleOffset(1.1);
	gDP->GetXaxis()->CenterTitle();
	gDP->GetYaxis()->CenterTitle();
	gDP->GetXaxis()->SetTitleSize(0.05);
	gDP->GetXaxis()->SetLabelSize(0.05);
	gDP->GetYaxis()->SetTitleSize(0.05);
	gDP->GetYaxis()->SetLabelSize(0.05);
	gDP->GetXaxis()->SetTitleFont(132);
	gDP->GetYaxis()->SetTitleFont(132);
	gDP->GetXaxis()->SetLabelFont(132);
	gDP->GetYaxis()->SetLabelFont(132);
	gDP->SetTitle("");
	gDP->Draw();
	
	auto *legend1 = new TLegend(.15, .75, .38, .88);
	char title1[200];
	if ( phase==0 ) {
		if ( det==0 ) { sprintf(title1, "EnrCoax - Phase (II, II+)"); gDP->SetLineColor(kRed+1); }
		if ( det==1 ) { sprintf(title1, "EnrBEGe - Phase (II, II+)"); gDP->SetLineColor(kBlue+1); }
		if ( det==2 ) { sprintf(title1, "IC - (II, II+)"); gDP->SetLineColor(kGreen+2); }
	}
	if ( phase==1 ) {
		if ( det==0 ) { sprintf(title1, "EnrCoax - Phase (II)"); gDP->SetLineColor(kRed+1); }
		if ( det==1 ) { sprintf(title1, "EnrBEGe - Phase (II)"); gDP->SetLineColor(kBlue+1); }
		if ( det==2 ) {  }
	}
	legend1->AddEntry(gDP, title1, "l");
	legend1->SetBorderSize(0);
	legend1->Draw();

	//===============================================================================	
	// PLot: pseudoscalar super-WIMPs
	TCanvas *c2 = new TCanvas("c2", "c2", 1700, 1000);
	c2->SetLogy();
	c2->SetLogx();
	TGraphErrors *gALP = new TGraphErrors(filename_ALP);
	gALP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gALP->GetYaxis()->SetTitle("Axion-electron coupling, g_{ae}");
	gALP->GetYaxis()->SetTitleOffset(1.1);
	gALP->GetXaxis()->CenterTitle();
	gALP->GetYaxis()->CenterTitle();
	gALP->GetXaxis()->SetTitleSize(0.05);
	gALP->GetXaxis()->SetLabelSize(0.05);
	gALP->GetYaxis()->SetTitleSize(0.05);
	gALP->GetYaxis()->SetLabelSize(0.05);
	gALP->GetXaxis()->SetTitleFont(132);
	gALP->GetYaxis()->SetTitleFont(132);
	gALP->GetXaxis()->SetLabelFont(132);
	gALP->GetYaxis()->SetLabelFont(132);
	gALP->SetTitle("");
	gALP->Draw();

	auto *legend2 = new TLegend(.15, .75, .38, .88);
	char title2[200];
	if ( phase==0 ) {
		if ( det==0 ) { sprintf(title2, "EnrCoax - Phase (II, II+)"); gALP->SetLineColor(kRed+1); }
		if ( det==1 ) { sprintf(title2, "EnrBEGe - Phase (II, II+)"); gALP->SetLineColor(kBlue+1); }
		if ( det==2 ) { sprintf(title2, "IC - Phase (II, II+)"); gALP->SetLineColor(kGreen+2); }
	}
	if ( phase==1 ) {
		if ( det==0 ) { sprintf(title2, "EnrCoax - Phase (II)"); gALP->SetLineColor(kRed+1); }
		if ( det==1 ) { sprintf(title2, "EnrBEGe - Phase (II)"); gALP->SetLineColor(kBlue+1); }
		if ( det==2 ) { }
	}
	legend2->AddEntry(gALP, title2, "l");
	legend2->SetBorderSize(0);
	legend2->Draw();
	
	if ( gerda==0 ) {
		//TGraphErrors *gDP_gerda = new TGraphErrors("/home/sofia/Analysis/SuperWIMPs_couplings/other_experiments/vector/GERDA_dp.txt");
		TGraphErrors *gDP_gerda = new TGraphErrors("/home/sofia/Analysis/SuperWIMPs_couplings/other_experiments/results_cplg_strength.txt", "%lg %*lg %lg");
		c1->cd();
		gDP_gerda->SetLineColor(1);
		gDP_gerda->Draw("same");
		legend1->AddEntry(gDP_gerda, "GERDA - Phase II (total)", "l");
		legend1->Draw();
		
		//TGraphErrors *gALP_gerda = new TGraphErrors("/home/sofia/Analysis/SuperWIMPs_couplings/other_experiments/pseudo/GERDA_alps.txt");
		TGraphErrors *gALP_gerda = new TGraphErrors("/home/sofia/Analysis/SuperWIMPs_couplings/other_experiments/results_cplg_strength.txt", "%lg %lg %*lg");
		c2->cd();
		gALP_gerda->SetLineColor(1);
		gALP_gerda->Draw("same");
		legend2->AddEntry(gALP_gerda, "GERDA - Phase II (total)", "l");
		legend2->Draw();
	}

	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int combined() {

	int phase;
	cout << " Phase II+ (0) or II (1)? ";
	cin >> phase;
	
	int gerda;
	cout << " Old GERDA results: yes (0) or no (1)? ";
	cin >> gerda;

	// open file for coupling strength results
	fstream fileDP;
	fileDP.open("vector.txt", ios::out);
	fstream fileALP;
	fileALP.open("pseudo.txt", ios::out);
	fstream file_Rtot;
	file_Rtot.open("Rtot_combined.txt", ios::out);
	
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
	
	int files_creation = Efficiency_extrapolation();
	
	char filename3_0[200], filename3_1[200], filename3_2[200];
	char filename3_3[200], filename3_4[200];
	double eff_fep_0[941][2], eff_fep_1[941][2], eff_fep_2[941][2];
	double eff_fep_3[941][2], eff_fep_4[941][2];
	sprintf(filename3_0, "eff_enrCoax_phIIp.txt"); 
	sprintf(filename3_1, "eff_enrBEGe_phIIp.txt"); 
	sprintf(filename3_2, "eff_invCoax_phIIp.txt"); 	
	ifstream file3_0(filename3_0);
	ifstream file3_1(filename3_1);
	ifstream file3_2(filename3_2);
	for ( int i=0; i<941; i++ ) {
		for ( int j=0; j<2; j++ ) {
			file3_0 >> eff_fep_0[i][j];
			file3_1 >> eff_fep_1[i][j];
			file3_2 >> eff_fep_2[i][j];
		}
	}
	file3_0.close();
	file3_1.close();
	file3_2.close();
	
	sprintf(filename3_3, "eff_enrCoax_phII.txt"); 
	sprintf(filename3_4, "eff_enrBEGe_phII.txt"); 
	ifstream file3_3(filename3_3);
	ifstream file3_4(filename3_4);
	for ( int i=0; i<941; i++ ) {
		for ( int j=0; j<2; j++ ) {
			file3_3 >> eff_fep_3[i][j];
			file3_4 >> eff_fep_4[i][j];
		}
	}
	file3_3.close();
	file3_4.close();
	
	
	//--------------------------------------------------------------------------------------------------------------------------------
	// Calculation of Super-WIMP coupling strengths
	for ( int E0=60; E0<=1000; E0++ ) {
	
		char filename5_0[200], filename5_1[200], filename5_2[200];
		// Phase II+
		if ( phase==0 ) { 
			sprintf(filename5_0, "/home/sofia/Analysis/Data2/JsonFiles/53_114/coax_PSD/JsonFile%i.json", E0); 
			sprintf(filename5_1, "/home/sofia/Analysis/DataAnalysis/JsonFiles/53_114/BEGe/JsonFile%i.json", E0); 
			sprintf(filename5_2, "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC/JsonFile%i.json", E0); 
			
			ifstream file5_0(filename5_0);
			ifstream file5_1(filename5_1);
			ifstream file5_2(filename5_2);
			json j_read5_0, j_read5_1, j_read5_2;
			file5_0 >> j_read5_0;
			file5_1 >> j_read5_1;
			file5_2 >> j_read5_2;
			file5_0.close();
			file5_1.close();
			file5_2.close();
		
			double exposure_0=0.0, exposure_1=0.0, exposure_2=0.0;
			if ( E0<195 ) { exposure_0 = 20.6676*365.25; exposure_1 = 30.5489*365.25; }
			if ( E0>=195 ) { exposure_0 = 41.8177*365.25; exposure_1 = 54.9284*365.25; }
			exposure_2 = 8.77469*365.25; 
			
			const double A = 75.921492725;
			int line = E0 - 60;
			
			double R90_0, R90_1, R90_2;
			R90_0 = ( j_read5_0["90UpperLimit"]["E0_counts_U90"].get<double>() ) / exposure_0;
			R90_1 = ( j_read5_0["90UpperLimit"]["E0_counts_U90"].get<double>() ) / exposure_1;
			R90_2 = ( j_read5_0["90UpperLimit"]["E0_counts_U90"].get<double>() ) / exposure_2;
			
			double R_tot = 0.0;
			R_tot = ( R90_0*exposure_0*(1-eff_fep_0[line][1])*(1-eff_fep_3[line][1]) + 
				  R90_1*exposure_1*(1-eff_fep_1[line][1])*(1-eff_fep_4[line][1]) +
				  R90_2*exposure_2*(1-eff_fep_2[line][1]) ) / 
				( exposure_0 + exposure_1 + exposure_2 );
			
			
			double vector_num = R_tot * A * E0;
			double vector_den = 4 * 1e23 * Ge_CS[line][1];
			double alpha = vector_num / vector_den; 
				
			double pseudoscalar_num = R_tot * A;
			double pseudoscalar_den = 1.29 * 1e19 * Ge_CS[line][1] * E0;
			double g_ae = sqrt( pseudoscalar_num / pseudoscalar_den );
			
			fileDP << E0 << "\t" << alpha << endl;
			fileALP << E0 << "\t" << g_ae << endl;
			file_Rtot << E0 << "\t" << R_tot << endl;
		}
		// Phase II
		if ( phase==1 ) { 
			sprintf(filename5_0, "/home/sofia/Analysis/Data2/JsonFiles/coax_PSD/JsonFile%i.json", E0); 
			sprintf(filename5_1, "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe_PSD/JsonFile%i.json", E0); 
			
			ifstream file5_0(filename5_0);
			ifstream file5_1(filename5_1);
			json j_read5_0, j_read5_1;
			file5_0 >> j_read5_0;
			file5_1 >> j_read5_1;
			file5_0.close();
			file5_1.close();
		
			double exposure_0=0.0, exposure_1=0.0;
			if ( E0<195 ) { exposure_0 = 7.4881*365.25; exposure_1 = 8.28657*365.25; }
			if ( E0>=195 ) { exposure_0 = 28.6383*365.25; exposure_1 = 31.4597*365.25; }
			
			const int A = 76;
			int line = E0 - 60;
			
			double R90_0, R90_1;
			R90_0 = ( j_read5_0["90UpperLimit"]["E0_counts_U90"].get<double>() ) / exposure_0;
			R90_1 = ( j_read5_0["90UpperLimit"]["E0_counts_U90"].get<double>() ) / exposure_1;
			
			double R_tot = 0.0;
			R_tot = (R90_0*exposure_0*(1-eff_fep_3[line][1]) + R90_1*exposure_1*(1-eff_fep_4[line][1])) / (exposure_0 + exposure_1);
			
			
			double vector_num = R_tot * A * E0;
			double vector_den = 4 * 1e23 * Ge_CS[line][1];
			double alpha = vector_num / vector_den; 
				
			double pseudoscalar_num = R_tot * A;
			double pseudoscalar_den = 1.29 * 1e19 * Ge_CS[line][1] * E0;
			double g_ae = sqrt( pseudoscalar_num / pseudoscalar_den );
			
			fileDP << E0 << "\t" << alpha << endl;
			fileALP << E0 << "\t" << g_ae << endl;
			file_Rtot << E0 << "\t" << R_tot << endl;
		}
	}
	fileDP.close();
	fileALP.close();
	file_Rtot.close();
	
	//===============================================================================
	// PLot: vector super-WIMPs
	TCanvas *c1 = new TCanvas("c1", "c1", 1700, 1000);
	
	TGraphErrors *gDP = new TGraphErrors("vector.txt");
	gDP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gDP->GetYaxis()->SetTitle("Kinetic mixing strength, #alpha'/#alpha");
	gDP->SetLineWidth(2);
	gDP->GetYaxis()->SetTitleOffset(1.1);
	gDP->GetXaxis()->CenterTitle();
	gDP->GetYaxis()->CenterTitle();
	gDP->GetXaxis()->SetTitleSize(0.05);
	gDP->GetXaxis()->SetLabelSize(0.05);
	gDP->GetYaxis()->SetTitleSize(0.05);
	gDP->GetYaxis()->SetLabelSize(0.05);
	gDP->GetXaxis()->SetTitleFont(132);
	gDP->GetYaxis()->SetTitleFont(132);
	gDP->GetXaxis()->SetLabelFont(132);
	gDP->GetYaxis()->SetLabelFont(132);
	gDP->SetTitle("");
	gDP->Draw();
	
	auto *legend1 = new TLegend(.15, .75, .38, .88);
	char title1[200];
	sprintf(title1, "GERDA - Phase (II, II+)"); 
	gDP->SetLineColor(kOrange-3);
	gDP->SetMarkerColor(kOrange-3);
	legend1->AddEntry(gDP, title1, "l");
	legend1->SetBorderSize(0);
	legend1->Draw();

	//===============================================================================	
	// PLot: pseudoscalar super-WIMPs
	TCanvas *c2 = new TCanvas("c2", "c2", 1700, 1000);

	TGraphErrors *gALP = new TGraphErrors("pseudo.txt");
	gALP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gALP->GetYaxis()->SetTitle("Axion-electron coupling, g_{ae}");
	gALP->SetLineWidth(2);
	gALP->GetYaxis()->SetTitleOffset(1.1);
	gALP->GetXaxis()->CenterTitle();
	gALP->GetYaxis()->CenterTitle();
	gALP->GetXaxis()->SetTitleSize(0.05);
	gALP->GetXaxis()->SetLabelSize(0.05);
	gALP->GetYaxis()->SetTitleSize(0.05);
	gALP->GetYaxis()->SetLabelSize(0.05);
	gALP->GetXaxis()->SetTitleFont(132);
	gALP->GetYaxis()->SetTitleFont(132);
	gALP->GetXaxis()->SetLabelFont(132);
	gALP->GetYaxis()->SetLabelFont(132);
	gALP->SetTitle("");
	gALP->Draw();

	auto *legend2 = new TLegend(.15, .75, .38, .88);
	char title2[200];
	sprintf(title2, "GERDA - Phase (II, II+)");
	gALP->SetLineColor(kOrange-3);
	gALP->SetMarkerColor(kOrange-3);
	legend2->AddEntry(gALP, title2, "l");
	legend2->SetBorderSize(0);
	legend2->Draw();
	
	if ( gerda==0 ) {
		//TGraphErrors *gDP_gerda = new TGraphErrors("/home/sofia/Analysis/SuperWIMPs_couplings/other_experiments/vector/GERDA_dp.txt");
		TGraphErrors *gDP_gerda = new TGraphErrors("/home/sofia/Analysis/SuperWIMPs_couplings/other_experiments/results_cplg_strength.txt", "%lg %*lg %lg");
		c1->cd();
		gDP_gerda->SetLineColor(kAzure-8);
		gDP_gerda->SetMarkerColor(kAzure-8);
		gDP_gerda->SetLineWidth(2);
		gDP_gerda->Draw("same");
		legend1->AddEntry(gDP_gerda, "GERDA - Phase (II)", "l");
		legend1->Draw();
		
		//TGraphErrors *gALP_gerda = new TGraphErrors("/home/sofia/Analysis/SuperWIMPs_couplings/other_experiments/pseudo/GERDA_alps.txt");
		TGraphErrors *gALP_gerda = new TGraphErrors("/home/sofia/Analysis/SuperWIMPs_couplings/other_experiments/results_cplg_strength.txt", "%lg %lg %*lg");
		c2->cd();
		gALP_gerda->SetLineColor(kAzure-8);
		gALP_gerda->SetMarkerColor(kAzure-8);
		gALP_gerda->SetLineWidth(2);
		gALP_gerda->Draw("same");
		legend2->AddEntry(gALP_gerda, "GERDA - Phase (II)", "l");
		legend2->Draw();
	}
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int rizalina_inverse() {

	fstream fileDP;
	fileDP.open("Rtot_Rizalina.txt", ios::out);
	
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
	
	// import RIZALINA alpha'/alpha
	fstream file1;
	file1.open("other_experiments/results_cplg_strength.txt", ios::in);
	const int rows1 = 939;
	const int columns1 = 3;
	double riz[rows1][columns1];
	for ( int i=0; i<rows1; i++ ) {
		for ( int j=0; j<columns1; j++ ) {
			file1 >> riz[i][j];
		}
	}
	file1.close();
	
	
	//--------------------------------------------------------------------------------------------------------------------------------
	// Calculation of Super-WIMP coupling strengths
	for ( int E0=60; E0<=1000; E0++ ) {
	
			if ( E0==97 || E0==98 ) { continue; }
		
			double exposure_0=0.0, exposure_1=0.0;
			if ( E0<200 ) { exposure_0 = 6.9*365.25; exposure_1 = 7.7*365.25; }
			if ( E0>=200 ) { exposure_0 = 28.1*365.25; exposure_1 = 30.8*365.25; }
			
			const int A = 76;
			int line = E0 - 60;
			
			double R90_0, R90_1;
			
			double num = 4 * 1e23 * riz[line][2] * Ge_CS[line][1];
			double den = A * E0;
			//R_tot = (R90_0*exposure_0*eff_fep_0[line][1] + R90_1*exposure_1*eff_fep_1[line][1] ) / (exposure_0 + exposure_1);
			double R_tot = num / den;
			
			fileDP << E0 << "\t" << R_tot << endl;
	}
	fileDP.close();
	
	//===============================================================================
	// PLot: vector super-WIMPs
	TCanvas *c1 = new TCanvas("c1", "c1", 1700, 1000);
	c1->SetLogy();
	TGraphErrors *gDP = new TGraphErrors("Rtot_Rizalina.txt");
	gDP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gDP->GetYaxis()->SetTitle("R_{tot}");
	gDP->GetXaxis()->CenterTitle();
	gDP->GetYaxis()->CenterTitle();
	gDP->SetTitle("");
	gDP->Draw();
	
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int ratio_GERDA() {

	fstream fileDP;
	fileDP.open("vector.txt", ios::in);
	fstream fileALP;
	fileALP.open("pseudo.txt", ios::in);
	fstream fileRiz;
	fileRiz.open("other_experiments/results_cplg_strength.txt", ios::in);
	
	fstream fileDP_ratio;
	fileDP_ratio.open("vector_ratio.txt", ios::out);
	fstream fileALP_ratio;
	fileALP_ratio.open("pseudo_ratio.txt", ios::out);
	
	// import RIZALINA alpha'/alpha
	const int rows1 = 939;
	const int columns1 = 3;
	double riz[rows1][columns1];
	for ( int i=0; i<rows1; i++ ) {
		for ( int j=0; j<columns1; j++ ) {
			fileRiz >> riz[i][j];
		}
	}
	fileRiz.close();
	
	// import pseudo
	const int rows2 = 941;
	const int columns2 = 2;
	double ALP[rows2][columns2];
	for ( int i=0; i<rows2; i++ ) {
		for ( int j=0; j<columns2; j++ ) {
			fileALP >> ALP[i][j];
		}
	}
	fileALP.close();
	
	// import vector
	const int rows3 = 941;
	const int columns3 = 2;
	double DP[rows3][columns3];
	for ( int i=0; i<rows3; i++ ) {
		for ( int j=0; j<columns3; j++ ) {
			fileDP >> DP[i][j];
		}
	}
	fileDP.close();
	
	
	//--------------------------------------------------------------------------------------------------------------------------------
	// Calculation of Super-WIMP coupling strengths
	for ( int E0=60; E0<=95; E0++ ) {
	
			if ( E0==97 || E0==98 ) { continue; }
			int line = E0-60;
			if ( E0==97 || E0==98 ) cout << E0 << endl;
			double DP_ratio = 100*( (DP[line][1]-riz[line][2]) / riz[line][2] );
			double ALP_ratio = 100*( (ALP[line][1]-riz[line][1]) / riz[line][1] );
			
			fileDP_ratio << E0 << "\t" << DP_ratio << endl;
			fileALP_ratio << E0 << "\t" << ALP_ratio << endl;
	}
	fileDP_ratio.close();
	fileALP_ratio.close();
	
	//===============================================================================
	// PLot: vector super-WIMPs
	TCanvas *c1 = new TCanvas("c1", "c1", 1700, 1000);
	TGraphErrors *gDP = new TGraphErrors("vector_ratio.txt");
	gDP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gDP->SetMarkerStyle(20);
	gDP->SetTitle("");
	gDP->Draw("AP");
	
	// PLot: pseudo super-WIMPs
	TCanvas *c2 = new TCanvas("c2", "c2", 1700, 1000);
	TGraphErrors *gALP = new TGraphErrors("pseudo_ratio.txt");
	gALP->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	gALP->SetMarkerStyle(20);
	gALP->SetTitle("");
	gALP->Draw("AP");
	
	
	return 0;
}
