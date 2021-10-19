// Available functions:
//	- draw_efficiency(int det, int phase): to plot Katharina and extrapolated efficiencies together
//	- int Efficiency_extrapolation(): to extrapolate efficiencies for each detector and Phase
//	- content_eff_correction(): to calculate new .txt files with normalized bin contents corrected by the efficiencies

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
			
			// extrapolation ...
			// ... in [40;60) keV ...
			double x_60 = eff_sim[0][0];
			double x_70 = eff_sim[1][0];
			double y_60 = eff_sim[0][2];
			double y_70 = eff_sim[1][2];
			for ( int x=40; x<60; x++ ) {
				double y = ( (x-x_60)/(x_70-x_60) ) * (y_70-y_60) + y_60;
				output << x << "\t\t" << y << endl;
			}
			
			// ... in [60;1000] keV ...
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
			
			// ... in (1000;1020] keV
			double x_990 = eff_sim[95][0];
			double x_1000 = eff_sim[96][0];
			double y_990 = eff_sim[95][2];
			double y_1000 = eff_sim[96][2];
			
			for ( int x=1000+1; x<=1020; x++ ) {
				double y = ( (x-x_990)/(x_1000-x_990) ) * (y_1000-y_990) + y_990;
				output << x << "\t\t" << y << endl;
			}
			
			output.close();		
		}
	}
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int content_eff_correction() {

	for ( int phase=0; phase<=1; phase++ ) {
		
		if ( phase==0 ) { // Phase II
			ifstream fileCOAX("/home/sofia/gerda_data/53_93_PSD/normalized_phII_PSD_COAX.txt");
			ifstream fileBEGe("/home/sofia/gerda_data/53_93_PSD/normalized_phII_PSD_BEGe.txt");
			
			double dataCOAX[5200], dataBEGe[5200];
			for ( int i=0; i<5200; i++ ) {
				fileCOAX >> dataCOAX[i];
				fileBEGe >> dataBEGe[i];
			}
			
			fileCOAX.close();
			fileBEGe.close();
			
			// !!! Rizalina efficiencies !!!
			// Katharina values are not extracted for PSD only data.
			// To reproduce the PRL SuperWIMP results, here I consider the old efficiency values for Phase II.
			ifstream effRiz("/home/sofia/Analysis/SuperWIMPs_couplings/efficiency_Rizalina/TotEnCorrectionLAr.json");
			json j_eff;
			effRiz >> j_eff;
			effRiz.close();
			
			double effCOAX[981], effBEGe[981];
			for ( int i=0; i<981; i++ ) {
				effCOAX[i] = j_eff["enrCoax"][i].get<double>();
				effBEGe[i] = j_eff["enrBEGe"][i].get<double>();
			}
			
			for ( int i=40; i<=1020; i++ ) {
				dataCOAX[i-2] = dataCOAX[i-2]*(effCOAX[i-40]);
				dataBEGe[i-2] = dataBEGe[i-2]*(effBEGe[i-40]);
			}
			
			ofstream fileCOAX_eff("/home/sofia/gerda_data/53_93_PSD/normalized_eff_phII_PSD_COAX.txt");
			ofstream fileBEGe_eff("/home/sofia/gerda_data/53_93_PSD/normalized_eff_phII_PSD_BEGe.txt");
			
			for ( int i=0; i<5200; i++ ) {
				fileCOAX_eff << dataCOAX[i] << endl;
				fileBEGe_eff << dataBEGe[i] << endl;
			}
			
			fileCOAX_eff.close();
			fileBEGe_eff.close();
			
			TH1D *hCOAX = new TH1D ("hCOAX","COAX - only PSD",5200,0,5200);
			TH1D *hBEGe = new TH1D ("hBEGe","BEGe - only PSD",5200,0,5200);
			
			for ( int i=1; i<=5200; i++ ) {
				hCOAX->SetBinContent(i, dataCOAX[i]);
				hBEGe->SetBinContent(i, dataBEGe[i]);
			}
			
			TFile *fileoutput = new TFile("/home/sofia/gerda_data/53_93_PSD/normalized_eff_phII_PSD.root", "RECREATE");
			fileoutput->WriteTObject(hCOAX);
			fileoutput->WriteTObject(hBEGe);
			fileoutput->Close();	
			delete hCOAX;
			delete hBEGe;		
		}
		
		if ( phase==1 ) { // Phase II, II+
			ifstream fileCOAX("/home/sofia/gerda_data/53_114_PSD/normalized_phIIp_COAX.txt");
			ifstream fileBEGe("/home/sofia/gerda_data/53_114_PSD/normalized_phIIp_BEGe.txt");
			ifstream fileIC("/home/sofia/gerda_data/53_114_PSD/normalized_phIIp_IC.txt");
			
			double dataCOAX[5200], dataBEGe[5200], dataIC[5200];
			for ( int i=0; i<5200; i++ ) {
				fileCOAX >> dataCOAX[i];
				fileBEGe >> dataBEGe[i];
				fileIC >> dataIC[i];
			}
			
			ifstream eff_COAX_IIp("eff_enrCoax_phIIp.txt");
			ifstream eff_BEGe_IIp("eff_enrBEGe_phIIp.txt");
			ifstream eff_IC_IIp("eff_invCoax_phIIp.txt");
			
			double effCOAX[981][2], effBEGe[981][2], effIC[981][2];
			
			for ( int i=0; i<981; i++ ) {
				for ( int j=0; j<2; j++ ) {
					eff_COAX_IIp >> effCOAX[i][j];
					eff_BEGe_IIp >> effBEGe[i][j];
					eff_IC_IIp >> effIC[i][j];
				}
			}
			
			fileCOAX.close();
			fileBEGe.close();
			fileIC.close();
			
			for ( int i=40; i<=1020; i++ ) {
				dataCOAX[i-2] = dataCOAX[i-2]*(effCOAX[i-40][1]);
				dataBEGe[i-2] = dataBEGe[i-2]*(effBEGe[i-40][1]);
				dataIC[i-2] = dataIC[i-2]*(effIC[i-40][1]);
			}
			
			ofstream fileCOAX_eff("/home/sofia/gerda_data/53_114_PSD/normalized_eff_phIIp_COAX.txt");
			ofstream fileBEGe_eff("/home/sofia/gerda_data/53_114_PSD/normalized_eff_phIIp_BEGe.txt");
			ofstream fileIC_eff("/home/sofia/gerda_data/53_114_PSD/normalized_eff_phIIp_IC.txt");
			
			for ( int i=0; i<5200; i++ ) {
				fileCOAX_eff << dataCOAX[i] << endl;
				fileBEGe_eff << dataBEGe[i] << endl;
				fileIC_eff << dataIC[i] << endl;
			}
			
			fileCOAX_eff.close();
			fileBEGe_eff.close();
			fileIC_eff.close();
			
			TH1D *hIC = new TH1D ("hIC","IC - only PSD + no PSD",5200,0,5200);
			TH1D *hBEGe = new TH1D ("hBEGe","BEGe - only PSD + no PSD",5200,0,5200);
			TH1D *hCOAX = new TH1D ("hCOAX","COAX - only PSD + no PSD",5200,0,5200);
			
			for ( int i=1; i<=5200; i++ ) {
				hCOAX->SetBinContent(i, dataCOAX[i-1]);
				hBEGe->SetBinContent(i, dataBEGe[i-1]);
				hIC->SetBinContent(i, dataIC[i-1]);
			}
			
			TFile *fileoutput = new TFile("/home/sofia/gerda_data/53_114_PSD/normalized_eff_phIIp.root", "RECREATE");
			fileoutput->WriteTObject(hCOAX);
			fileoutput->WriteTObject(hBEGe);
			fileoutput->WriteTObject(hIC);
			fileoutput->Close();	
			delete hCOAX;
			delete hBEGe;
			delete hIC;
		}
	
	}

	return 0;
}
