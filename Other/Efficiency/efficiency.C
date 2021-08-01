//   Available functions:
//	- efficiency(): to calculate efficiencies (raw, LAr, PSD, LAr+PSD); N_tot = # primaries; eff -> starting from histogram entries
//	- fit_raw_efficiency() : to display fit for the raw efficiency 
//	- plot(): to plot the spectrum for a given type of detector, energy and cut
//	- neighbour_raw_plot(): to plot two consecutive energies given a detector (only raw cut)
//	- plot_all(): to plot all cuts for a given detector and energy
//	- plot_efficiency(): to plot efficiencies for a given detector (to use only after efficiency())

#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

int plot_efficiency();

double HistoIntegral(TH1D *histo, double min, double max) {

	// min/max -> bins
	int minBin = histo->GetXaxis()->FindBin(min);
	int maxBin = histo->GetXaxis()->FindBin(max);
	
	return histo->Integral(minBin, maxBin);
}

int efficiency() {

	fstream output;
	output.open("efficiency_phIIplus.json", ios::out);
	
	fstream write1;
	write1.open("efficiencies_phaseIIp_enrCoax.txt", ios::out);
	fstream write2;
	write2.open("efficiencies_phaseIIp_enrBEGe.txt", ios::out);
	fstream write3;
	write3.open("efficiencies_phaseIIp_invCoax.txt", ios::out);
	
	int enrCoax_energies[23] = { 60, 90, 120, 150, 180, 195, 200, 250, 300, // 9
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7
	int enrBEGe_energies[22] = { 60, 90, 120, 150, 165, 200, 250, 300, // 8
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7	
	int invCoax_energies[22] = { 60, 90, 120, 150, 165, 200, 250, 300, // 8
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7	
				   
	for ( int det=0; det<=2; det++ ) {
		for ( int j=0; j<=22; j++ ) {
		
			if ( (det==1 || det==2) && j==22 ) { continue; }
		
			double eff_raw=0, eff_LAr=0, eff_PSD=0, eff_LAr_PSD=0;
			double delta = 0;
			
			if ( det==0 ) { delta=3; }
			if ( det==1 ) { delta=3; }
			if ( det==2 ) { delta=3.5; }
			
			if ( det==0 && j==0 ) { delta=4; }
			
			for ( int state=0; state<=3; state++ ) {
			
				int energy = 0;
				if ( det==0 ) { energy = enrCoax_energies[j]; }
				if ( det==1 ) { energy = enrBEGe_energies[j]; }
				if ( det==2 ) { energy = invCoax_energies[j]; }
			
				char file_name[200];
				if ( det==0 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", energy);
				if ( det==1 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", energy);
				if ( det==2 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", energy);
				TFile *file = new TFile(file_name);
				
				char dir_histo[200];
				if ( state==0 ) {
					if ( det==0 ) sprintf(dir_histo, "raw/M1_enrCoax");
					if ( det==1 ) sprintf(dir_histo, "raw/M1_enrBEGe");
					if ( det==2 ) sprintf(dir_histo, "raw/M1_invCoax");
				}
				if ( state==1 ) {
					if ( det==0 ) sprintf(dir_histo, "lar/M1_enrCoax");
					if ( det==1 ) sprintf(dir_histo, "lar/M1_enrBEGe");
					if ( det==2 ) sprintf(dir_histo, "lar/M1_invCoax");
				}
				if ( state==2 ) {
					if ( det==0 ) sprintf(dir_histo, "psd/M1_enrCoax");
					if ( det==1 ) sprintf(dir_histo, "psd/M1_enrBEGe");
					if ( det==2 ) sprintf(dir_histo, "psd/M1_invCoax");
				}
				if ( state==3 ) {
					if ( det==0 ) sprintf(dir_histo, "lar_psd/M1_enrCoax");
					if ( det==1 ) sprintf(dir_histo, "lar_psd/M1_enrBEGe");
					if ( det==2 ) sprintf(dir_histo, "lar_psd/M1_invCoax");
				}
				
				
				TH1D *histo = (TH1D*) file->Get(dir_histo);
				
				double sigma = 0;
				if ( det==0 ) { sigma = sqrt (0.985 + 0.0001073*energy); }
				if ( det==1 ) { sigma = sqrt (0.551 + 0.0004294*energy); }
				if ( det==2 ) { sigma = sqrt (0.28 + 0.000583*energy); }
				int bin_max = histo->GetMaximumBin();
				int peak_mode = histo->GetBinContent(bin_max);
				double FWHM = sqrt (8*log(2))*sigma;
				
				// signal window
				double xmin_sig = energy-delta*FWHM;
				double xmax_sig = energy+delta*FWHM;
				
				// bkg window (L and R of signal)
				double xmin_L_bkg = energy-2*delta*FWHM;
				double xmin_R_bkg = xmin_sig;
				double xmax_L_bkg = xmax_sig;
				double xmax_R_bkg = energy+2*delta*FWHM;
				
				// signal events
				int nPeak = HistoIntegral(histo, xmin_sig, xmax_sig);
				int nBkg = HistoIntegral(histo, xmin_L_bkg, xmin_R_bkg) + HistoIntegral(histo, xmax_L_bkg, xmax_R_bkg);
				
				double ratio = ( nPeak - nBkg ) / ( 1e7 + 0.0 );
				
				if ( state==0 ) { eff_raw = ratio; }
				if ( state==1 ) { eff_LAr = ratio; }
				if ( state==2 ) { eff_PSD = ratio; }
				if ( state==3 ) { eff_LAr_PSD = ratio; }
			}
		
			if ( det==0 ) {
				json jtot = json::object({ {"Energy_keV", enrCoax_energies[j]},
							   {"eff_raw", eff_raw},
							   {"eff_LAr", eff_LAr},
							   {"eff_PSD", eff_PSD},
							   {"eff_LAr_PSD", eff_LAr_PSD} });
			
				char name[200];
				sprintf(name, "enrCoax_%i", enrCoax_energies[j]);
				json jfinal = json::object({ {name, jtot} });
				
				output << std::setw(4) << jfinal << std::endl;
				write1 << enrCoax_energies[j] << "\t\t" << eff_raw << "\t\t" << eff_LAr << "\t\t" << eff_PSD << "\t\t" << eff_LAr_PSD << endl;
			}
			if ( det==1 ) {
				json jtot = json::object({ {"Energy_keV", enrBEGe_energies[j]},
							   {"eff_raw", eff_raw},
							   {"eff_LAr", eff_LAr},
							   {"eff_PSD", eff_PSD},
							   {"eff_LAr_PSD", eff_LAr_PSD} });
			
				char name[200];
				sprintf(name, "enrBEGe_%i", enrBEGe_energies[j]);
				json jfinal = json::object({ {name, jtot} });
				
				output << std::setw(4) << jfinal << std::endl;
				write2 << enrBEGe_energies[j] << "\t\t" << eff_raw << "\t\t" << eff_LAr << "\t\t" << eff_PSD << "\t\t" << eff_LAr_PSD << endl;
			}
			if ( det==2 ) {
				json jtot = json::object({ {"Energy_keV", invCoax_energies[j]},
							   {"eff_raw", eff_raw},
							   {"eff_LAr", eff_LAr},
							   {"eff_PSD", eff_PSD},
							   {"eff_LAr_PSD", eff_LAr_PSD} });
			
				char name[200];
				sprintf(name, "invCoax_%i", invCoax_energies[j]);
				json jfinal = json::object({ {name, jtot} });
				
				output << std::setw(4) << jfinal << std::endl;
				write3 << invCoax_energies[j] << "\t\t" << eff_raw << "\t\t" << eff_LAr << "\t\t" << eff_PSD << "\t\t" << eff_LAr_PSD << endl;
			}	
		}
	}

	output.close();
	write1.close();
	write2.close();
	write2.close();
	
	int a = plot_efficiency();
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int fit_raw_efficiency() {

	int det;
	cout << " What detector: Coax (0), BEGe (1) or IC (2)? ";
	cin >> det;
	
	int En;
	cout << " Choose the energy in [60;1000] keV: ";
	cin >> En;
	
	double delta;
	cout << " Choose delta: ";
	cin >> delta;

	int enrCoax_energies[23] = { 60, 90, 120, 150, 180, 195, 200, 250, 300, // 9
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7
	int enrBEGe_energies[22] = { 60, 90, 120, 150, 165, 200, 250, 300, // 8
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7	
	int invCoax_energies[22] = { 60, 90, 120, 150, 165, 200, 250, 300, // 8
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7	
				   
	int j = 0;
	int diff = 0;
	if ( det==0 ) diff = fabs( En - enrCoax_energies[j] );
	if ( det==1 ) diff = fabs( En - enrBEGe_energies[j] );
	if ( det==2 ) diff = fabs( En - invCoax_energies[j] );
	while ( diff!=0 ) {
		j++;
		if ( det==0 ) diff = fabs( En - enrCoax_energies[j] );
		if ( det==1 ) diff = fabs( En - enrBEGe_energies[j] );
		if ( det==2 ) diff = fabs( En - invCoax_energies[j] );
	}
	
	double eff_raw=0, eff_LAr=0, eff_PSD=0, eff_LAr_PSD=0;
		
	int energy = 0;
	if ( det==0 ) { energy = enrCoax_energies[j]; }
	if ( det==1 ) { energy = enrBEGe_energies[j]; }
	if ( det==2 ) { energy = invCoax_energies[j]; }
		
	char file_name[200];
	if ( det==0 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", energy);
	if ( det==1 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", energy);
	if ( det==2 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", energy);
	TFile *file = new TFile(file_name);
	
	char dir_histo[200];
	if ( det==0 ) sprintf(dir_histo, "raw/M1_enrCoax");
	if ( det==1 ) sprintf(dir_histo, "raw/M1_enrBEGe");
	if ( det==2 ) sprintf(dir_histo, "raw/M1_invCoax");
					
	TH1D *histo = (TH1D*) file->Get(dir_histo);
			
	double sigma = 0;
	if ( det==0 ) { sigma = sqrt (0.985 + 0.0001073*energy); }
	if ( det==1 ) { sigma = sqrt (0.551 + 0.0004294*energy); }
	if ( det==2 ) { sigma = sqrt (0.28 + 0.000583*energy); }
	int bin_max = histo->GetMaximumBin();
	int peak_mode = histo->GetBinContent(bin_max);
	double FWHM = sqrt (8*log(2))*sigma;
			
	int xmin_sig = energy-delta*FWHM;
	int xmax_sig = energy+delta*FWHM;
	int xmin_bkg = energy-2*delta*FWHM;
	int xmax_bkg = energy+2*delta*FWHM;
			
	int q = 0;
	for ( int i=xmin_bkg+1; i<=xmin_sig; i++ ) {
		q += histo->GetBinContent(i);
	}
			
	const int primaries = 1e7;
		
	int tot_int = histo->Integral(xmin_bkg, xmax_bkg);
	int bkg_int = 0;
			
	TF1 *tot_fit =  new TF1("tot_fit", "gaus(0)+pol1(3)", xmin_bkg, xmax_bkg);
	tot_fit->SetParameter(0, peak_mode);
	tot_fit->FixParameter(1, energy);
	tot_fit->FixParameter(2, sigma); 
	tot_fit->SetParameter(3, q);
	tot_fit->SetParameter(4, 0);
			
	TFitResultPtr tot_fit_BL = histo->Fit("tot_fit", "SL", "", xmin_bkg, xmax_bkg);
			
	q = tot_fit->GetParameter(3);
	double m = tot_fit->GetParameter(1);
	double b = xmax_sig - xmin_sig;
	bkg_int += b * (q + 0.5*b*m); // bkg inside the signal region
	cout << " b = " << b << endl;
			
	double ratio = ( tot_int - bkg_int ) / ( primaries + 0.0 );
	cout << " tot_int = " << tot_int << endl;
	cout << " tot_int - bkg_int = " << tot_int - 5.10762e+01*( xmax_sig - xmin_sig ) << endl;
	cout << "\n\033[1;30m Raw efficiency = " << ratio << "\033[0m\n" << endl;
		
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int plot() {

	int det;
	cout << " What detector: Coax (0), BEGe (1) or IC (2)? ";
	cin >> det;
	
	int En;
	cout << " Choose the energy in [60;1000] keV: ";
	cin >> En;
	
	int state;
	cout << " Raw (0), LAr (1), PSD (2) or LAr+PSD (3)? ";
	cin >> state;
	
	char file_name[200];
	if ( det==0 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", En);
	if ( det==1 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En);
	if ( det==2 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", En);
	TFile *file = new TFile(file_name);
	
	char dir_histo[200];
	if ( state==0 ) {
		if ( det==0 ) sprintf(dir_histo, "raw/M1_enrCoax");
		if ( det==1 ) sprintf(dir_histo, "raw/M1_enrBEGe");
		if ( det==2 ) sprintf(dir_histo, "raw/M1_invCoax");
	}
	if ( state==1 ) {
		if ( det==0 ) sprintf(dir_histo, "lar/M1_enrCoax");
		if ( det==1 ) sprintf(dir_histo, "lar/M1_enrBEGe");
		if ( det==2 ) sprintf(dir_histo, "lar/M1_invCoax");
	}
	if ( state==2 ) {
		if ( det==0 ) sprintf(dir_histo, "psd/M1_enrCoax");
		if ( det==1 ) sprintf(dir_histo, "psd/M1_enrBEGe");
		if ( det==2 ) sprintf(dir_histo, "psd/M1_invCoax");
	}
	if ( state==3 ) {
		if ( det==0 ) sprintf(dir_histo, "lar_psd/M1_enrCoax");
		if ( det==1 ) sprintf(dir_histo, "lar_psd/M1_enrBEGe");
		if ( det==2 ) sprintf(dir_histo, "lar_psd/M1_invCoax");
	}
	
	TCanvas *c = new TCanvas();
	c->SetLogy();
	TH1D *histo = (TH1D*) file->Get(dir_histo);
	histo->GetXaxis()->SetRangeUser(0,En+300);
	histo->Draw();

	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int neighbour_raw_plot() {

	int det;
	cout << " What detector: Coax (0), BEGe (1) or IC (2)? ";
	cin >> det;
	
	int En;
	cout << " Choose the energy in [60;1000] keV: ";
	cin >> En;
	
	int dir;
	cout << " Second energy: up (0) or down (1)? ";
	cin >> dir;
	
	int ans;
	cout << " Shifted (0) or not (1)? ";
	cin >> ans;
	
	int enrCoax_energies[23] = { 60, 90, 120, 150, 180, 195, 200, 250, 300, // 9
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7
	int enrBEGe_energies[22] = { 60, 90, 120, 150, 165, 200, 250, 300, // 8
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7	
	int invCoax_energies[22] = { 60, 90, 120, 150, 165, 200, 250, 300, // 8
				   350, 400, 450, 500, 550, 600, 650, // 7
				   700, 750, 800, 850, 900, 950, 1000 }; // 7	
				   
	int j = 0;
	int diff = 0;
	if ( det==0 ) diff = fabs( En - enrCoax_energies[j] );
	if ( det==1 ) diff = fabs( En - enrBEGe_energies[j] );
	if ( det==2 ) diff = fabs( En - invCoax_energies[j] );
	while ( diff!=0 ) {
		j++;
		if ( det==0 ) diff = fabs( En - enrCoax_energies[j] );
		if ( det==1 ) diff = fabs( En - enrBEGe_energies[j] );
		if ( det==2 ) diff = fabs( En - invCoax_energies[j] );
	}
	
	char file_name1[200], file_name2[200];
	if ( det==0 ) sprintf(file_name1, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", enrCoax_energies[j]);
	if ( det==1 ) sprintf(file_name1, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", enrBEGe_energies[j]);
	if ( det==2 ) sprintf(file_name1, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", invCoax_energies[j]);
	TFile *file1 = new TFile(file_name1);
	if ( dir==0 ) {
		if ( det==0 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", enrCoax_energies[j+1]);
		if ( det==1 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", enrBEGe_energies[j+1]);
		if ( det==2 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", invCoax_energies[j+1]);
	}
	if ( dir==1 ) {
		if ( det==0 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", enrCoax_energies[j-1]);
		if ( det==1 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", enrBEGe_energies[j-1]);
		if ( det==2 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", invCoax_energies[j-1]);
	}
	TFile *file2 = new TFile(file_name2);
	
	char dir_histo[200];
	if ( det==0 ) sprintf(dir_histo, "raw/M1_enrCoax");
	if ( det==1 ) sprintf(dir_histo, "raw/M1_enrBEGe");
	if ( det==2 ) sprintf(dir_histo, "raw/M1_invCoax");
	
	TCanvas *c = new TCanvas();
	c->SetLogy();
	TH1D *histo1 = (TH1D*) file1->Get(dir_histo);
	histo1->GetXaxis()->SetRangeUser(0,En+50);
	histo1->GetXaxis()->SetTitle("Energy [keV]");
	histo1->GetYaxis()->SetTitle("cts / 1 keV");
	histo1->SetLineWidth(2);
	histo1->SetStats(kFALSE);
	TH1D *histo2 = (TH1D*) file2->Get(dir_histo);
	histo2->SetLineColor(2);
	histo2->SetLineWidth(2);
	histo2->SetStats(kFALSE);
	if ( ans==0 ) {
		if ( dir==0 ) {
			if ( det==0 ) diff = fabs( En - enrCoax_energies[j+1] );
			if ( det==1 ) diff = fabs( En - enrBEGe_energies[j+1] );
			if ( det==2 ) diff = fabs( En - invCoax_energies[j+1] );
			for ( int i=1; i<(histo2->GetNbinsX())-diff; i++ ) {
				histo2->SetBinContent(i, histo2->GetBinContent(i+diff));
			}
		}
		if ( dir==1 ) {
			if ( det==0 ) diff = fabs( En - enrCoax_energies[j-1] );
			if ( det==1 ) diff = fabs( En - enrBEGe_energies[j-1] );
			if ( det==2 ) diff = fabs( En - invCoax_energies[j-1] );
			for ( int i=1; i<(histo1->GetNbinsX())-diff; i++ ) {
				histo1->SetBinContent(i, histo1->GetBinContent(i+diff));
			}
		}
		histo1->Draw();
		histo2->Draw("same"); 
	}
	if ( ans==1 ) { 
		histo1->Draw();
		histo2->Draw("same");
	}

	auto *legend = new TLegend(.15, .7, .4, .88);
	char histo1_name[200], histo2_name[200];
	sprintf(histo1_name, "Energy = %i keV", En);
	if ( det==0 ) {
		if ( dir==0 ) sprintf(histo2_name, "Energy = %i keV", enrCoax_energies[j+1]);
		if ( dir==1 ) sprintf(histo2_name, "Energy = %i keV", enrCoax_energies[j-1]);
	}
	if ( det==1 ) {
		if ( dir==0 ) sprintf(histo2_name, "Energy = %i keV", enrBEGe_energies[j+1]);
		if ( dir==1 ) sprintf(histo2_name, "Energy = %i keV", enrBEGe_energies[j-1]);
	}
	if ( det==2 ) {
		if ( dir==0 ) sprintf(histo2_name, "Energy = %i keV", invCoax_energies[j+1]);
		if ( dir==1 ) sprintf(histo2_name, "Energy = %i keV", invCoax_energies[j-1]);
	}
	legend->AddEntry(histo1, histo1_name, "l");
	legend->AddEntry(histo2, histo2_name, "l");
	legend->Draw();

	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int plot_all() {

	int det;
	cout << " What detector: Coax (0), BEGe (1) or IC (2)? ";
	cin >> det;
	
	int En;
	cout << " Choose the energy in [60;1000] keV: ";
	cin >> En;
	
	char file_name[200];
	if ( det==0 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", En);
	if ( det==1 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En);
	if ( det==2 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", En);
	TFile *file = new TFile(file_name);
	
	char dir_histo1[200], dir_histo2[200], dir_histo3[200], dir_histo4[200];
	if ( det==0 ) {
		sprintf(dir_histo1, "raw/M1_enrCoax");
		sprintf(dir_histo2, "lar/M1_enrCoax");
		sprintf(dir_histo3, "psd/M1_enrCoax");
		sprintf(dir_histo4, "lar_psd/M1_enrCoax");
	}
	if ( det==1 ) {
		sprintf(dir_histo1, "raw/M1_enrBEGe");
		sprintf(dir_histo2, "lar/M1_enrBEGe");
		sprintf(dir_histo3, "psd/M1_enrBEGe");
		sprintf(dir_histo4, "lar_psd/M1_enrBEGe");
		}
	if ( det==2 ) {
		sprintf(dir_histo1, "raw/M1_invCoax");
		sprintf(dir_histo2, "lar/M1_invCoax");
		sprintf(dir_histo3, "raw/M1_invCoax");
		sprintf(dir_histo4, "lar_psd/M1_invCoax");
	}
	
	TCanvas *c = new TCanvas();
	c->SetLogy();
	TH1D *histo1 = (TH1D*) file->Get(dir_histo1);
	histo1->GetXaxis()->SetRangeUser(0,1150);
	histo1->SetStats(kFALSE);
	histo1->Draw();
	
	TH1D *histo2 = (TH1D*) file->Get(dir_histo2);
	histo2->SetLineColor(2);
	histo2->SetStats(kFALSE);
	histo2->Draw("same");
	
	TH1D *histo3 = (TH1D*) file->Get(dir_histo3);
	histo3->SetLineColor(kGreen+2);
	histo3->SetStats(kFALSE);
	histo3->Draw("same");
	
	TH1D *histo4 = (TH1D*) file->Get(dir_histo4);
	histo4->SetLineColor(kGray+3);
	histo4->SetStats(kFALSE);
	histo4->Draw("same");
	
	auto *legend = new TLegend(.15, .7, .4, .88);
	legend->AddEntry(histo1, "Raw", "l");
	legend->AddEntry(histo2, "LAr", "l");
	legend->AddEntry(histo3, "PSD", "l");
	legend->AddEntry(histo4, "LAr+PSD", "l");
	legend->Draw();
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int plot_efficiency() {

	// COAX -------------------------------------------------------------------------------------
	TCanvas *c_0 = new TCanvas();
	TMultiGraph *mg_0 = new TMultiGraph();
	TGraph *g1_0 = new TGraph("efficiencies_phaseIIp_enrCoax.txt", "%lg %lg %*lg %*lg %*lg");
	g1_0->SetLineColor(kAzure);
	g1_0->SetMarkerColor(kAzure);
	g1_0->SetMarkerStyle(20);
	g1_0->SetMarkerSize(2.3);
	mg_0->Add(g1_0);
	
	TGraph *g2_0 = new TGraph("efficiencies_phaseIIp_enrCoax.txt", "%lg %*lg %lg %*lg %*lg");
	g2_0->SetLineColor(2);
	g2_0->SetMarkerColor(2);
	g2_0->SetMarkerStyle(20);
	mg_0->Add(g2_0);
	
	TGraph *g3_0 = new TGraph("efficiencies_phaseIIp_enrCoax.txt", "%lg %*lg %*lg %lg %*lg");
	g3_0->SetLineColor(kGreen);
	g3_0->SetMarkerColor(kGreen);
	g3_0->SetMarkerStyle(20);
	g3_0->SetMarkerSize(2.3);
	mg_0->Add(g3_0);
	
	TGraph *g4_0 = new TGraph("efficiencies_phaseIIp_enrCoax.txt", "%lg %*lg %*lg %*lg %lg");
	g4_0->SetLineColor(kBlack);
	g4_0->SetMarkerColor(kBlack);
	g4_0->SetMarkerStyle(20);
	mg_0->Add(g4_0);
	
	mg_0->SetTitle("enrCoax efficiency; Energy [keV]; Efficiency");
	mg_0->Draw("AP");
	
	auto *legend_0 = new TLegend(.15, .4, .3, .58);
	legend_0->AddEntry(g1_0, "Raw", "p");
	legend_0->AddEntry(g2_0, "LAr", "p");
	legend_0->AddEntry(g3_0, "PSD", "p");
	legend_0->AddEntry(g4_0, "LAr+PSD", "p");
	legend_0->Draw();
	
	// BEGe -------------------------------------------------------------------------------------
	TCanvas *c_1 = new TCanvas();
	TMultiGraph *mg_1 = new TMultiGraph();
	TGraph *g1_1 = new TGraph("efficiencies_phaseIIp_enrBEGe.txt", "%lg %lg %*lg %*lg %*lg");
	g1_1->SetLineColor(kAzure);
	g1_1->SetMarkerColor(kAzure);
	g1_1->SetMarkerStyle(20);
	g1_1->SetMarkerSize(2.3);
	mg_1->Add(g1_1);
	
	TGraph *g2_1 = new TGraph("efficiencies_phaseIIp_enrBEGe.txt", "%lg %*lg %lg %*lg %*lg");
	g2_1->SetLineColor(2);
	g2_1->SetMarkerColor(2);
	g2_1->SetMarkerStyle(20);
	mg_1->Add(g2_1);
	
	TGraph *g3_1 = new TGraph("efficiencies_phaseIIp_enrBEGe.txt", "%lg %*lg %*lg %lg %*lg");
	g3_1->SetLineColor(kGreen);
	g3_1->SetMarkerColor(kGreen);
	g3_1->SetMarkerStyle(20);
	g3_1->SetMarkerSize(2.3);
	mg_1->Add(g3_1);
	
	TGraph *g4_1 = new TGraph("efficiencies_phaseIIp_enrBEGe.txt", "%lg %*lg %*lg %*lg %lg");
	g4_1->SetLineColor(kBlack);
	g4_1->SetMarkerColor(kBlack);
	g4_1->SetMarkerStyle(20);
	mg_1->Add(g4_1);
	
	mg_1->SetTitle("enrBEGe efficiency; Energy [keV]; Efficiency");
	mg_1->Draw("AP");
	
	auto *legend_1 = new TLegend(.15, .4, .3, .58);
	legend_1->AddEntry(g1_1, "Raw", "p");
	legend_1->AddEntry(g2_1, "LAr", "p");
	legend_1->AddEntry(g3_1, "PSD", "p");
	legend_1->AddEntry(g4_1, "LAr+PSD", "p");
	legend_1->Draw();
	
	// IC ---------------------------------------------------------------------------------------
	TCanvas *c_2 = new TCanvas();
	TMultiGraph *mg_2 = new TMultiGraph();
	TGraph *g1_2 = new TGraph("efficiencies_phaseIIp_invCoax.txt", "%lg %lg %*lg %*lg %*lg");
	g1_2->SetLineColor(kAzure);
	g1_2->SetMarkerColor(kAzure);
	g1_2->SetMarkerStyle(20);
	g1_2->SetMarkerSize(2.3);
	mg_2->Add(g1_2);
	
	TGraph *g2_2 = new TGraph("efficiencies_phaseIIp_invCoax.txt", "%lg %*lg %lg %*lg %*lg");
	g2_2->SetLineColor(2);
	g2_2->SetMarkerColor(2);
	g2_2->SetMarkerStyle(20);
	mg_2->Add(g2_2);
	
	TGraph *g3_2 = new TGraph("efficiencies_phaseIIp_invCoax.txt", "%lg %*lg %*lg %lg %*lg");
	g3_2->SetLineColor(kGreen);
	g3_2->SetMarkerColor(kGreen);
	g3_2->SetMarkerStyle(20);
	g3_2->SetMarkerSize(2.3);
	mg_2->Add(g3_2);
	
	TGraph *g4_2 = new TGraph("efficiencies_phaseIIp_invCoax.txt", "%lg %*lg %*lg %*lg %lg");
	g4_2->SetLineColor(kBlack);
	g4_2->SetMarkerColor(kBlack);
	g4_2->SetMarkerStyle(20);
	mg_2->Add(g4_2);
	
	mg_2->SetTitle("invCoax efficiency; Energy [keV]; Efficiency");
	mg_2->Draw("AP");
	
	auto *legend_2 = new TLegend(.15, .4, .3, .58);
	legend_2->AddEntry(g1_2, "Raw", "p");
	legend_2->AddEntry(g2_2, "LAr", "p");
	legend_2->AddEntry(g3_2, "PSD", "p");
	legend_2->AddEntry(g4_2, "LAr+PSD", "p");
	legend_2->Draw();
	
	return 0;
}
