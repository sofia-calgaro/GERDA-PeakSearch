#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace::std;

int sigma_definition() {

	int ans0, ans;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> ans0;
	/*int E0_min, E0_max;
	cout << "\n * Select the interval [E0_min;E0_max]:\n\t - choose E0_min: ";
	cin >> E0_min;
	cout << "\t - choose E0_max: ";
	cin >> E0_max;*/
	const int E0_min = 60;
	const int E0_max = 1000;
	
	TCanvas *c = new TCanvas("c","c",1700,700);
	TH1F *h_sigma = new TH1F("h", "", 28, -0.25, 6.6195652);
	const int y_max = 590;
	
	char filename2[200];
	if ( ans0==0 ) { sprintf(filename2, "/home/sofia/Analysis/Data2/ReadJSON/coax_PSD/GlobalMode.txt"); }
	if ( ans0==1 ) { sprintf(filename2, "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/GlobalMode.txt"); }
	if ( ans0==2 ) { sprintf(filename2, "/home/sofia/Analysis/DataAnalysis/ReadJSON/IC/GlobalMode.txt"); }
	fstream file2;
	file2.open(filename2, ios::in);
	const int rows = 941;
	const int columns = 9;
	double data[rows][columns];
	for ( int i=0; i<rows; i++ ) {
		for ( int j=0; j<columns; j++ ) {
			file2 >> data[i][j];
		}
	}
	file2.close();

	char filename3[200];
	if ( ans0==0 ) { sprintf(filename3, "5sigma_coax.txt"); }
	if ( ans0==1 ) { sprintf(filename3, "5sigma_BEGe.txt"); }
	if ( ans0==2 ) { sprintf(filename3, "5sigma_IC.txt"); }
	fstream file3;
	file3.open(filename3, ios::out);
	file3 << "# E0" << std::setw(15) << "sigma" << std::setw(15) << "5*sigma" << std::setw(15) << "GM" << std::setw(15) << "GM-5*sigma" << endl;
	
	for ( int E0=E0_min; E0<=E0_max; E0++) {
	
		char filename[200];
		if ( ans0==0 ) { sprintf(filename, "/home/sofia/Analysis/Data2/MarginalizedROOT/coax_PSD/%i.root", E0); }
		if ( ans0==1 ) { sprintf(filename, "/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/BEGe/%i.root", E0); }
		if ( ans0==2 ) { sprintf(filename, "/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/IC/%i.root", E0); }
				
		const int line = E0-60;
		double GlobalMode = data[line][1];
		double qt_34 = 0.0;
		
		TFile *f = new TFile(filename);
		
		char filename3[300];
		
		// no gamma peaks
		if (E0<=193) { sprintf(filename3, "h1_%iGausPol2_parameter_E0_height", E0); }
		if (E0>=194 && E0<=229) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=251 && E0<=283) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=308 && E0<=340) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=364 && E0<=466) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=491 && E0<=501) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=524 && E0<=571) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=596 && E0<=597) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=622 && E0<=899) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=924 && E0<=957) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=981 && E0<=1000) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		// 1 gamma peak
		if (E0>=284 && E0<=307) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=341 && E0<=363) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=467 && E0<=490) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=572 && E0<=595) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=598 && E0<=621) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=900 && E0<=923) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=958 && E0<=980) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		// 2 gamma peaks
		if ( (E0>=230 && E0<=250) || (E0>=502 && E0<=523) ) { sprintf(filename3, "h1_%iGausPol1_2Gamma_parameter_E0_height", E0); }
		
		TH1D *h = (TH1D*)f->Get(filename3);
		int binmax = h->GetMaximumBin();
		for ( int k=1; k<=h->GetNbinsX(); k++ ) { h->SetBinContent(k, h->GetBinContent(k+h->FindBin(GlobalMode)-1)); } // shift to left
		TH1 *h_clone = (TH1D*)h->Clone();
		h_clone->SetLineWidth(2);
		h_clone->SetName("h_clone");
		
		double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
		double q[7] = {0};
		h_clone->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
		qt_34 = q[1] - q[0];
		
		delete h;
		delete h_clone;
		
		// Fill histogram with GM/sigma
		if ( GlobalMode/qt_34 < 1 ) {
			cout << " The peak for E0=" << E0 << " is near to 0! " << endl;
			h_sigma->Fill(GlobalMode/qt_34); 
		}
		
		if ( GlobalMode/qt_34 > 1 ) {
		
			char filename4[200];
			if ( ans0==0 ) { sprintf(filename4, "/home/sofia/Analysis/Data2/ReadJSON/coax_PSD/68Quantile.txt"); }
			if ( ans0==1 ) { sprintf(filename4, "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/68Quantile.txt"); }
			if ( ans0==2 ) { sprintf(filename4, "/home/sofia/Analysis/DataAnalysis/ReadJSON/IC/68Quantile.txt"); }
					
			fstream file4;
			file4.open(filename4, ios::in);
			const int rows = 941;
			const int columns = 9;
			double data[rows][columns];
			for ( int i=0; i<rows; i++ ) {
				for ( int j=0; j<columns; j++ ) {
					file4 >> data[i][j];
				}
			}
			file4.close();
			
			double E0_counts_L68 = data[line][1];
			double E0_counts_U68 = data[line][2];
			double sigma_68 = ( E0_counts_U68 - E0_counts_L68 )*0.5;
			
			if ( GlobalMode/sigma_68<5 ) {
				h_sigma->Fill(GlobalMode/sigma_68);
			}
			if ( GlobalMode/sigma_68>=5 ) {
				file3 << E0 << std::setw(15) << sigma_68 << std::setw(15) << 5*sigma_68 << std::setw(15) << GlobalMode << std::setw(15) << GlobalMode-5*sigma_68 << std::endl;
				h_sigma->Fill(GlobalMode/sigma_68);
			}
		}
		
		f->Close();
	
	} // STOP ciclo for
	
	file3.close();
	
	cout << ifstream(filename3).rdbuf();
	
	// Plot
	h_sigma->SetStats(kFALSE);
	h_sigma->GetXaxis()->SetTitle("Mode/Error");
	h_sigma->GetYaxis()->SetRangeUser(0, y_max);
	h_sigma->GetYaxis()->SetTitle("Frequency");
	if ( ans0==0 ) { h_sigma->SetFillColor(kRed+2); h_sigma->SetLineColor(kRed+2); }
	if ( ans0==1 ) { h_sigma->SetFillColor(kBlue+1); h_sigma->SetLineColor(kBlue+1); }
	if ( ans0==2 ) { h_sigma->SetFillColor(kGreen+2); h_sigma->SetLineColor(kGreen+2); }
	h_sigma->SetFillStyle(0);
	h_sigma->GetXaxis()->SetTitleSize(0.06);
	h_sigma->GetXaxis()->SetLabelSize(0.06);
	h_sigma->GetYaxis()->SetTitleSize(0.06);
	h_sigma->GetYaxis()->SetLabelSize(0.06);
	h_sigma->GetYaxis()->SetTitleOffset(0.7);
	h_sigma->GetXaxis()->SetTitleOffset(0.9);
	h_sigma->GetXaxis()->CenterTitle();
	h_sigma->GetYaxis()->CenterTitle();
	h_sigma->Draw("B,bar2");
	
	TH1F *h_2 = (TH1F*)h_sigma->Clone("h_2");
	h_2->SetBarWidth(0.1);
	h_2->SetBarOffset(0.0);
	if ( ans0==0 ) { h_2->SetFillColor(kRed-7); }
	if ( ans0==1 ) { h_2->SetFillColor(kAzure-4); }
	if ( ans0==2 ) { h_2->SetFillColor(kSpring-4); }
	h_2->Draw("B,bar2,same");
	
	TH1F *h_3 = (TH1F*)h_sigma->Clone("h_3");
	h_3->SetBarWidth(0.1);
	h_3->SetBarOffset(0.9);
	if ( ans0==0 ) { h_3->SetFillColor(kRed+3); }
	if ( ans0==1 ) { h_3->SetFillColor(kBlue+3); }
	if ( ans0==2 ) { h_3->SetFillColor(kGreen+3); }
	h_3->Draw("B,bar2,same");
	
	c->RedrawAxis();
	
	TLine *line1 = new TLine(5, 0, 5, y_max);
	line1->SetLineColor(kBlack);
	line1->SetLineStyle(9);
	line1->SetLineWidth(2);
	line1->Draw();
	
	auto *legend = new TLegend(.55, .72, .78, .85);
	if ( ans0==0 ) { legend->AddEntry(h_sigma, "EnrCoax (II, II+)", "f"); }
	if ( ans0==1 ) { legend->AddEntry(h_sigma, "EnrBEGe (II, II+)", "f"); }
	if ( ans0==2 ) { legend->AddEntry(h_sigma, "IC (II+)", "f"); }
	legend->AddEntry(line1, "Excess threshold", "l");
	legend->SetBorderSize(0);
	legend->Draw();
	
	if ( ans0==0 ) { c->SaveAs("ModeSigma_coax.png"); }
	if ( ans0==1 ) { c->SaveAs("ModeSigma_BEGe.png"); }
	if ( ans0==2 ) { c->SaveAs("ModeSigma_IC.png"); }	
	
	return 0;
}
//====================================================================================================
int for_sigma() {

	const int E0_min = 60;
	const int E0_max = 1000;
	
	TCanvas *c = new TCanvas("c","c",1700,700);
	TH1F *h_sigma_0 = new TH1F("h_sigma_0", "", 23, -0.25, 5.5);
	TH1F *h_sigma_1 = new TH1F("h_sigma_1", "", 23, -0.25, 5.5);
	TH1F *h_sigma_2 = new TH1F("h_sigma_2", "", 23, -0.25, 5.5);
	const int y_max = 590;
	
	// for over detectors
	for ( int ans0=0; ans0<=2; ans0++ ) {
		
		char filename2[200];
		if ( ans0==0 ) { sprintf(filename2, "/home/sofia/Analysis/Data2/ReadJSON/coax_PSD/GlobalMode.txt"); }
		if ( ans0==1 ) { sprintf(filename2, "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/GlobalMode.txt"); }
		if ( ans0==2 ) { sprintf(filename2, "/home/sofia/Analysis/DataAnalysis/ReadJSON/IC_PSD/GlobalMode.txt"); }
		fstream file2;
		file2.open(filename2, ios::in);
		const int rows = 941;
		const int columns = 9;
		double data[rows][columns];
		for ( int i=0; i<rows; i++ ) {
			for ( int j=0; j<columns; j++ ) {
				file2 >> data[i][j];
			}
		}
		file2.close();

		char filename3[200];
		if ( ans0==0 ) { sprintf(filename3, "5sigma_coax.txt"); }
		if ( ans0==1 ) { sprintf(filename3, "5sigma_BEGe.txt"); }
		if ( ans0==2 ) { sprintf(filename3, "5sigma_IC.txt"); }
		fstream file3;
		file3.open(filename3, ios::out);
		file3 << "# E0" << std::setw(15) << "sigma" << std::setw(15) << "5*sigma" << std::setw(15) << "GM" << std::setw(15) << "GM-5*sigma" << endl;
		
		for ( int E0=E0_min; E0<=E0_max; E0++) {
		
			char filename[200];
			if ( ans0==0 ) { sprintf(filename, "/home/sofia/Analysis/Data2/MarginalizedROOT/coax_PSD/%i.root", E0); }
			if ( ans0==1 ) { sprintf(filename, "/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/BEGe/%i.root", E0); }
			if ( ans0==2 ) { sprintf(filename, "/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/IC_PSD/%i.root", E0); }
					
			const int line = E0-60;
			double GlobalMode = data[line][1];
			double qt_34 = 0.0;
			
			TFile *f = new TFile(filename);
			
			char filename3[300];
			
			// no gamma peaks
			if (E0<=193) { sprintf(filename3, "h1_%iGausPol2_parameter_E0_height", E0); }
			if (E0>=194 && E0<=229) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=251 && E0<=283) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=308 && E0<=340) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=364 && E0<=466) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=491 && E0<=501) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=524 && E0<=571) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=596 && E0<=597) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=622 && E0<=899) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=924 && E0<=957) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			if (E0>=981 && E0<=1000) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
			// 1 gamma peak
			if (E0>=284 && E0<=307) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
			if (E0>=341 && E0<=363) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
			if (E0>=467 && E0<=490) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
			if (E0>=572 && E0<=595) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
			if (E0>=598 && E0<=621) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
			if (E0>=900 && E0<=923) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
			if (E0>=958 && E0<=980) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
			// 2 gamma peaks
			if ( (E0>=230 && E0<=250) || (E0>=502 && E0<=523) ) { sprintf(filename3, "h1_%iGausPol1_2Gamma_parameter_E0_height", E0); }
			
			TH1D *h = (TH1D*)f->Get(filename3);
			int binmax = h->GetMaximumBin();
			for ( int k=1; k<=h->GetNbinsX(); k++ ) { h->SetBinContent(k, h->GetBinContent(k+h->FindBin(GlobalMode)-1)); } // shift to left
			TH1 *h_clone = (TH1D*)h->Clone();
			h_clone->SetLineWidth(2);
			h_clone->SetName("h_clone");
			
			double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
			double q[7] = {0};
			h_clone->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
			qt_34 = q[1] - q[0];
			
			delete h;
			delete h_clone;
			
			// Fill histogram with GM/sigma
			if ( GlobalMode/qt_34 < 1 ) {
				//cout << " The peak for E0=" << E0 << " is near to 0! " << endl;
				if ( ans0==0 ) h_sigma_0->Fill(GlobalMode/qt_34); 
				if ( ans0==1 ) h_sigma_1->Fill(GlobalMode/qt_34); 
				if ( ans0==2 ) h_sigma_2->Fill(GlobalMode/qt_34); 
			}
			
			if ( GlobalMode/qt_34 > 1 ) {
			
				char filename4[200];
				if ( ans0==0 ) { sprintf(filename4, "/home/sofia/Analysis/Data2/ReadJSON/coax_PSD/68Quantile.txt"); }
				if ( ans0==1 ) { sprintf(filename4, "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/68Quantile.txt"); }
				if ( ans0==2 ) { sprintf(filename4, "/home/sofia/Analysis/DataAnalysis/ReadJSON/IC_PSD/68Quantile.txt"); }
						
				fstream file4;
				file4.open(filename4, ios::in);
				const int rows = 941;
				const int columns = 9;
				double data[rows][columns];
				for ( int i=0; i<rows; i++ ) {
					for ( int j=0; j<columns; j++ ) {
						file4 >> data[i][j];
					}
				}
				file4.close();
				
				double E0_counts_L68 = data[line][1];
				double E0_counts_U68 = data[line][2];
				double sigma_68 = ( E0_counts_U68 - E0_counts_L68 )*0.5;
				
				if ( GlobalMode/sigma_68<5 ) {
					if ( ans0==0 ) h_sigma_0->Fill(GlobalMode/sigma_68); 
					if ( ans0==1 ) h_sigma_1->Fill(GlobalMode/sigma_68); 
					if ( ans0==2 ) h_sigma_2->Fill(GlobalMode/sigma_68); 
				}
				if ( GlobalMode/sigma_68>=5 ) {
					file3 << E0 << std::setw(15) << sigma_68 << std::setw(15) << 5*sigma_68 << std::setw(15) << GlobalMode << std::setw(15) << GlobalMode-5*sigma_68 << std::endl;
				}
			}
			
			f->Close();
		
		} // STOP ciclo for
		
		file3.close();
		
		cout << " Detector: " << ans0 << endl;
		cout << ifstream(filename3).rdbuf();
	}
	
	// Plot
		h_sigma_0->SetStats(kFALSE);
		h_sigma_1->SetStats(kFALSE);
		h_sigma_2->SetStats(kFALSE);
	h_sigma_0->GetXaxis()->SetTitle("Mode/Error");
	h_sigma_0->GetYaxis()->SetRangeUser(0, y_max);
	h_sigma_0->GetYaxis()->SetTitle("Frequency");
		//h_sigma_0->SetFillColor(kRed+2); 
		h_sigma_0->SetLineColor(kRed+2); 
		//h_sigma_1->SetFillColor(kBlue+1);
		h_sigma_1->SetLineColor(kBlue+1); 
		//h_sigma_2->SetFillColor(kGreen+2); 
		h_sigma_2->SetLineColor(kGreen+2); 
	h_sigma_0->SetFillStyle(0);
	h_sigma_0->GetXaxis()->SetTitleSize(0.06);
	h_sigma_0->GetXaxis()->SetLabelSize(0.06);
	h_sigma_0->GetYaxis()->SetTitleSize(0.06);
	h_sigma_0->GetYaxis()->SetLabelSize(0.06);
	h_sigma_0->GetYaxis()->SetTitleOffset(0.98);
	h_sigma_0->GetXaxis()->CenterTitle();
	h_sigma_0->GetYaxis()->CenterTitle();
		/*h_sigma_0->Draw("B,bar2");
		h_sigma_1->Draw("B,bar2,same");
		h_sigma_2->Draw("B,bar2,same");*/
		h_sigma_0->Draw();
		h_sigma_1->Draw("SAME");
		h_sigma_2->Draw("SAME");
	
	c->RedrawAxis();
	
	TLine *line1 = new TLine(5, 0, 5, y_max);
	line1->SetLineColor(kBlack);
	line1->SetLineStyle(9);
	line1->SetLineWidth(2);
	line1->Draw();
	
	auto *legend = new TLegend(.65, .75, .88, .88);
	legend->AddEntry(h_sigma_0, "EnrCoax (II, II+)", "l"); 
	legend->AddEntry(h_sigma_1, "EnrBEGe (II, II+)", "l"); 
	legend->AddEntry(h_sigma_2, "IC (II+)", "l"); 
	legend->AddEntry(line1, "Excess threshold", "l");
	legend->Draw();	
	
	return 0;
}
//====================================================================================================
//====================================================================================================
//====================================================================================================
int PSD() {

	int ans0, ans;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> ans0;
	/*int E0_min, E0_max;
	cout << "\n * Select the interval [E0_min;E0_max]:\n\t - choose E0_min: ";
	cin >> E0_min;
	cout << "\t - choose E0_max: ";
	cin >> E0_max;*/
	const int E0_min = 60;
	const int E0_max = 1000;
	
	TCanvas *c = new TCanvas();
	TH1F *h_sigma = new TH1F("h", "", 23, -0.25, 5.5);
	const int y_max = 600;
	
	char filename2[200];
	if ( ans0==0 ) { sprintf(filename2, "/home/sofia/Analysis/Data2/ReadJSON/coax_PSD/GlobalMode.txt"); }
	if ( ans0==1 ) { sprintf(filename2, "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe_PSD/GlobalMode.txt"); }
	if ( ans0==2 ) { sprintf(filename2, "/home/sofia/Analysis/DataAnalysis/ReadJSON/IC_PSD/GlobalMode.txt"); }
	fstream file2;
	file2.open(filename2, ios::in);
	const int rows = 941;
	const int columns = 9;
	double data[rows][columns];
	for ( int i=0; i<rows; i++ ) {
		for ( int j=0; j<columns; j++ ) {
			file2 >> data[i][j];
		}
	}
	file2.close();

	char filename3[200];
	if ( ans0==0 ) { sprintf(filename3, "5sigma_coax_PSD.txt"); }
	if ( ans0==1 ) { sprintf(filename3, "5sigma_BEGe_PSD.txt"); }
	if ( ans0==2 ) { sprintf(filename3, "5sigma_IC_PSD.txt"); }
	fstream file3;
	file3.open(filename3, ios::out);
	file3 << "# E0" << std::setw(15) << "sigma" << std::setw(15) << "5*sigma" << std::setw(15) << "GM" << std::setw(15) << "GM-5*sigma" << endl;
	
	for ( int E0=E0_min; E0<=E0_max; E0++) {
	
		char filename[200];
		if ( ans0==0 ) { sprintf(filename, "/home/sofia/Analysis/Data2/MarginalizedROOT/coax_PSD/%i.root", E0); }
		if ( ans0==1 ) { sprintf(filename, "/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/BEGe_PSD/%i.root", E0); }
		if ( ans0==2 ) { sprintf(filename, "/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/IC_PSD/%i.root", E0); }
				
		const int line = E0-60;
		double GlobalMode = data[line][1];
		double qt_34 = 0.0;
		
		TFile *f = new TFile(filename);
		
		char filename3[300];
		
		// no gamma peaks
		if (E0<=194) { sprintf(filename3, "h1_%iGausPol2_parameter_E0_height", E0); }
		if (E0>=195 && E0<=229) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=251 && E0<=283) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=308 && E0<=340) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=364 && E0<=466) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=491 && E0<=501) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=524 && E0<=571) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=596 && E0<=597) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=622 && E0<=899) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=924 && E0<=957) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		if (E0>=981 && E0<=1000) { sprintf(filename3, "h1_%iGausPol1_parameter_E0_height", E0); }
		// 1 gamma peak
		if (E0>=284 && E0<=307) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=341 && E0<=363) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=467 && E0<=490) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=572 && E0<=595) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=598 && E0<=621) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=900 && E0<=923) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		if (E0>=958 && E0<=980) { sprintf(filename3, "h1_%iGausPol1_1Gamma_parameter_E0_height", E0); }
		// 2 gamma peaks
		if ( (E0>=230 && E0<=250) || (E0>=502 && E0<=523) ) { sprintf(filename3, "h1_%iGausPol1_2Gamma_parameter_E0_height", E0); }
		
		TH1D *h = (TH1D*)f->Get(filename3);
		int binmax = h->GetMaximumBin();
		for ( int k=1; k<=h->GetNbinsX(); k++ ) { h->SetBinContent(k, h->GetBinContent(k+h->FindBin(GlobalMode)-1)); } // shift to left
		TH1 *h_clone = (TH1D*)h->Clone();
		h_clone->SetLineWidth(2);
		h_clone->SetName("h_clone");
		
		double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
		double q[7] = {0};
		h_clone->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
		qt_34 = q[1] - q[0];
		
		delete h;
		delete h_clone;
		
		
		
		// Fill histogram with GM/sigma
		if ( GlobalMode/qt_34 < 1 ) {
			cout << " The peak for E0=" << E0 << " is near to 0! " << endl;
			h_sigma->Fill(GlobalMode/qt_34); 
		}
		
		if ( GlobalMode/qt_34 > 1 ) {
		
			char filename4[200];
			if ( ans0==0 ) { sprintf(filename4, "/home/sofia/Analysis/Data2/ReadJSON/coax_PSD/68Quantile.txt"); }
			if ( ans0==1 ) { sprintf(filename4, "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe_PSD/68Quantile.txt"); }
			if ( ans0==2 ) { sprintf(filename4, "/home/sofia/Analysis/DataAnalysis/ReadJSON/IC_PSD/68Quantile.txt"); }
					
			fstream file4;
			file4.open(filename4, ios::in);
			const int rows = 941;
			const int columns = 9;
			double data[rows][columns];
			for ( int i=0; i<rows; i++ ) {
				for ( int j=0; j<columns; j++ ) {
					file4 >> data[i][j];
				}
			}
			file4.close();
			
			double E0_counts_L68 = data[line][1];
			double E0_counts_U68 = data[line][2];
			double sigma_68 = ( E0_counts_U68 - E0_counts_L68 )*0.5;
			
			if ( GlobalMode/sigma_68<5 ) {
				h_sigma->Fill(GlobalMode/sigma_68); if ( E0==338 ) cout << "GM=" << GlobalMode << "\t 5*sigma_68=" << 5*sigma_68 << endl;
			}
			if ( GlobalMode>=5*sigma_68 ) {
				file3 << E0 << std::setw(15) << sigma_68 << std::setw(15) << 5*sigma_68 << std::setw(15) << GlobalMode << std::setw(15) << GlobalMode-5*sigma_68 << std::endl; 
			}
		}
		
		f->Close();
	
	} // STOP ciclo for
	
	file3.close();
	
	cout << ifstream(filename3).rdbuf();
	
	// Plot
	h_sigma->SetStats(kFALSE);
	h_sigma->GetXaxis()->SetTitle("Mode/#sigma");
	h_sigma->GetYaxis()->SetRangeUser(0, y_max);
	h_sigma->GetYaxis()->SetTitle("Frequency");
	h_sigma->SetFillColor(kGray+2);
	h_sigma->SetLineColor(kGray+2);
	h_sigma->SetFillStyle(0);
	h_sigma->GetXaxis()->SetTitleSize(0.045);
	h_sigma->GetXaxis()->SetLabelSize(0.045);
	h_sigma->GetYaxis()->SetTitleSize(0.045);
	h_sigma->GetYaxis()->SetLabelSize(0.045);
	h_sigma->GetYaxis()->SetTitleOffset(0.98);
	h_sigma->Draw("B,bar2");
	
	TH1F *h_2 = (TH1F*)h_sigma->Clone("h_2");
	h_2->SetBarWidth(0.1);
	h_2->SetBarOffset(0.0);
	h_2->SetFillColor(kGray);
	h_2->Draw("B,bar2,same");
	
	TH1F *h_3 = (TH1F*)h_sigma->Clone("h_3");
	h_3->SetBarWidth(0.1);
	h_3->SetBarOffset(0.9);
	h_3->SetFillColor(kBlack);
	h_3->Draw("B,bar2,same");
	
	TLine *line1 = new TLine(5, 0, 5, y_max);
	line1->SetLineColor(kRed);
	line1->SetLineStyle(10);
	line1->SetLineWidth(2);
	line1->Draw();
	
	auto *legend = new TLegend(.65, .75, .88, .88);
	if ( ans0==0 ) { legend->AddEntry(h_sigma, "EnrCoax (II, II+) - PSD", "l"); }
	if ( ans0==1 ) { legend->AddEntry(h_sigma, "EnrBEGe (II, II+) - PSD", "l"); }
	if ( ans0==2 ) { legend->AddEntry(h_sigma, "IC (II+) - PSD", "l"); }
	legend->AddEntry(line1, "Excess threshold", "l");
	legend->Draw();
	
	if ( ans0==0 ) { c->SaveAs("ModeSigma_coax_PSD.png"); }
	if ( ans0==1 ) { c->SaveAs("ModeSigma_BEGe_PSD.png"); }
	if ( ans0==2 ) { c->SaveAs("ModeSigma_IC_PSD.png"); }	
	
	return 0;
}
