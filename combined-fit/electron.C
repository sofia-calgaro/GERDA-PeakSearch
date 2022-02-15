// Macro to calculate and draw the eff_gamma*eff_electron to have a first estimate of 
// the Compton efficiency

#include <iostream>
#include <fstream>
#include </home/sofia/Software/json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

int electron() {
	
	// electrons
	for ( int det=0; det<=2; det++ ) {
		for ( int run=0; run<=1; run++ ) {
		
			char filename4[200];
			// Phase II+
			if ( run==1 ) { 
				if ( det==0 ) sprintf(filename4, "/home/sofia/Analysis/super-wimps/Efficiency/old/FepEff_phaseIIp_enrCoax.txt"); 
				if ( det==1 ) sprintf(filename4, "/home/sofia/Analysis/super-wimps/Efficiency/old/FepEff_phaseIIp_enrBEGe.txt"); 
				if ( det==2 ) sprintf(filename4, "/home/sofia/Analysis/super-wimps/Efficiency/old/FepEff_phaseIIp_invCoax.txt"); 
			}
			// Phase II
			if ( run==0 ) { 
				if ( det==0 ) sprintf(filename4, "/home/sofia/Analysis/super-wimps/Efficiency/old/FepEff_phaseII_enrCoax.txt"); 
				if ( det==1 ) sprintf(filename4, "/home/sofia/Analysis/super-wimps/Efficiency/old/FepEff_phaseII_enrBEGe.txt"); 
				if ( det==2 ) {}
			}		
		
			ifstream file4(filename4);
			const int rows = 97;
			const int columns4 = 5;
			double eff_sim[rows][columns4];
			for ( int i=0; i<rows; i++ ) {
				for ( int j=0; j<columns4; j++ ) {
					file4 >> eff_sim[i][j];
				}
			}
			file4.close();
			
			char outputname[200];
			if ( run==1 ) {
				if ( det==0 ) sprintf(outputname, "eff_enrCoax_phIIp.txt");
				if ( det==1 ) sprintf(outputname, "eff_enrBEGe_phIIp.txt");
				if ( det==2 ) sprintf(outputname, "eff_invCoax_phIIp.txt");
			}
			if ( run==0 ) {
				if ( det==0 ) sprintf(outputname, "eff_enrCoax_phII.txt");
				if ( det==1 ) sprintf(outputname, "eff_enrBEGe_phII.txt");
				if ( det==2 ) continue;
			}
			ofstream output(outputname);
			
			// extrapolation
			for ( int i=0; i<rows-1; i++ ) {
				int k = i+1;
				
				// extract down to 40 keV using fit parameters of 60-70 keV
				if ( i==0 ) {
					int en_start = 40;
					int j = 0;
					while ( j<20 ) {
						double x = en_start + j;
						double x1 = eff_sim[0][0];
						double x2 = eff_sim[1][0];
						double y1 = eff_sim[0][2];
						double y2 = eff_sim[1][2];
						double y = ( (x-x1)/(x2-x1) ) * (y2-y1) + y1; // extrapolated efficiencies
						j++;
						output << x << "\t\t" << y << endl;
					}	
				}
				
				// extract from 60 keV to 1000 keV
				if ( i==10 && det==0 ) k = i + 2;
				if ( i==11 && det==0 ) continue;
			
				int limit = 10;
				if ( (i==10 || i==11) && det!=0 ) limit = 5;
				if ( i==14 || i==15 ) limit = 5;
				if ( i==rows-2 ) limit = 11;
				
				int j = 0;
				while ( j<limit ) {
					double x = eff_sim[i][0] + j;
					double x1 = eff_sim[i][0];
					double x2 = eff_sim[k][0];
					double y1 = eff_sim[i][2];
					double y2 = eff_sim[k][2];
					double y = 0.0;
					if ( j!=0 ) { y = ( (x-x1)/(x2-x1) ) * (y2-y1) + y1; } 
					else { y = eff_sim[i][2]; } 
					j++;
					output << x << "\t\t" << y << endl;
				}	
				
				// extract up to 1022+20 keV using fit parameters of 990-1000 keV
				if ( i==rows-2 ) {
					int en_start = 1001;
					int j = 0;
					while ( j<40 ) {
						double x = en_start + j;
						double x1 = eff_sim[95][0];
						double x2 = eff_sim[96][0];
						double y1 = eff_sim[95][2];
						double y2 = eff_sim[96][2];
						double y = ( (x-x1)/(x2-x1) ) * (y2-y1) + y1; // extrapolated efficiencies
						j++;
						output << x << "\t\t" << y << endl;
					}	
				}		
			}
			output.close();		
		}
	}
	
	// phase II, II+	
	TCanvas *c1 = new TCanvas("c1", "c1", 1500, 900);
	TMultiGraph *mg1 = new TMultiGraph();
		
	TGraphErrors *g_coax_II_IIp = new TGraphErrors("eff_enrCoax_phIIp.txt"); // COAX
	g_coax_II_IIp->SetLineColor(kRed);
	g_coax_II_IIp->SetMarkerColor(kRed);
	g_coax_II_IIp->SetMarkerStyle(20);
	g_coax_II_IIp->SetMarkerSize(0.8);
	mg1->Add(g_coax_II_IIp);
		
	TGraphErrors *g_bege_II_IIp = new TGraphErrors("eff_enrBEGe_phIIp.txt"); // BEGe 
	g_bege_II_IIp->SetLineColor(kBlue);
	g_bege_II_IIp->SetMarkerColor(kBlue);
	g_bege_II_IIp->SetMarkerStyle(20);
	g_bege_II_IIp->SetMarkerSize(0.8);
	mg1->Add(g_bege_II_IIp);
	
	TGraphErrors *g_ic_II_IIp = new TGraphErrors("eff_invCoax_phIIp.txt"); // IC
	g_ic_II_IIp->SetLineColor(8);
	g_ic_II_IIp->SetMarkerColor(8);
	g_ic_II_IIp->SetMarkerStyle(20);
	g_ic_II_IIp->SetMarkerSize(0.8);
	mg1->Add(g_ic_II_IIp);
	
	mg1->SetTitle("Phase (II, II+)"); 	
	mg1->GetXaxis()->SetTitle("Energy [keV]"); 
	mg1->GetYaxis()->SetTitle("Efficiency");
	mg1->GetXaxis()->SetTitleSize(0.045);
	mg1->GetXaxis()->SetLabelSize(0.045);
	mg1->GetXaxis()->CenterTitle();
	mg1->GetYaxis()->SetTitleSize(0.045);
	mg1->GetYaxis()->SetLabelSize(0.045);
	mg1->GetYaxis()->CenterTitle();
	mg1->GetYaxis()->CenterTitle();
	mg1->GetXaxis()->SetTitleFont(132);
	mg1->GetYaxis()->SetTitleFont(132);
	mg1->GetXaxis()->SetLabelFont(132);
	mg1->GetYaxis()->SetLabelFont(132);
	mg1->GetXaxis()->SetTitleOffset(0.92);
	mg1->GetYaxis()->SetTitleOffset(1.00);
	mg1->GetXaxis()->SetRangeUser(0, 1500);
	mg1->Draw("AP");	
		
	auto *legend1 = new TLegend(.75, .7, .88, .88);
	legend1->SetBorderSize(0);
	legend1->AddEntry(g_coax_II_IIp, "EnrCoax", "p");
	legend1->AddEntry(g_bege_II_IIp, "EnrBEGe", "p");
	legend1->AddEntry(g_ic_II_IIp, "InvCoax", "p");
	legend1->Draw();
	
	
	// phase II
	TCanvas *c2 = new TCanvas("c2", "c2", 1500, 900);
	TMultiGraph *mg2 = new TMultiGraph();
		
	TGraphErrors *g_coax_II = new TGraphErrors("eff_enrCoax_phII.txt"); // COAX
	g_coax_II->SetLineColor(kRed);
	g_coax_II->SetMarkerColor(kRed);
	g_coax_II->SetMarkerStyle(20);
	g_coax_II->SetMarkerSize(0.8);
	mg2->Add(g_coax_II);
		
	TGraphErrors *g_bege_II = new TGraphErrors("eff_enrBEGe_phII.txt"); // BEGe 
	g_bege_II->SetLineColor(kBlue);
	g_bege_II->SetMarkerColor(kBlue);
	g_bege_II->SetMarkerStyle(20);
	g_bege_II->SetMarkerSize(0.8);
	mg2->Add(g_bege_II);
	
	mg2->SetTitle("Phase II"); 	
	mg2->GetXaxis()->SetTitle("Energy [keV]"); 
	mg2->GetYaxis()->SetTitle("Efficiency");
	mg2->GetXaxis()->SetTitleSize(0.045);
	mg2->GetXaxis()->SetLabelSize(0.045);
	mg2->GetXaxis()->CenterTitle();
	mg2->GetYaxis()->SetTitleSize(0.045);
	mg2->GetYaxis()->SetLabelSize(0.045);
	mg2->GetYaxis()->CenterTitle();
	mg2->GetYaxis()->CenterTitle();
	mg2->GetXaxis()->SetTitleFont(132);
	mg2->GetYaxis()->SetTitleFont(132);
	mg2->GetXaxis()->SetLabelFont(132);
	mg2->GetYaxis()->SetLabelFont(132);
	mg2->GetXaxis()->SetTitleOffset(0.92);
	mg2->GetYaxis()->SetTitleOffset(1.00);
	mg2->GetXaxis()->SetRangeUser(0, 1500);
	mg2->Draw("AP");	
		
	auto *legend2 = new TLegend(.75, .7, .88, .88);
	legend2->SetBorderSize(0);
	legend2->AddEntry(g_coax_II, "EnrCoax", "p");
	legend2->AddEntry(g_bege_II, "EnrBEGe", "p");
	legend2->Draw();
		
	
	return 0;
}
