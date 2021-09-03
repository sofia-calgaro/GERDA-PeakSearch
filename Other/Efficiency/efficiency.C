//   Available functions:
//	- efficiency_fep(): to calculate e- absorption efficiencies (raw, LAr, PSD, LAr+PSD); N_tot = # primaries; eff -> starting from histogram entries
//	- efficiency_tot(): to calculate total efficiencies (raw, LAr, PSD, LAr+PSD); N_tot = # primaries; eff -> starting from histogram entries
//	- plot(): to plot the spectrum for a given type of detector, energy and cut
//	- neighbour_raw_plot(): to plot two energies for a given detector (only LAr cut)
//	- common(): to plot the same energy from super-wimps-phIIplus/ and super-wimps-phIIplus-lowthr/
//	- plot_all(): to plot all cuts for a given detector and energy
//	- plot_efficiency(int eff_type, int ans): to plot efficiencies for all detectors; ans = 0 -> plot all 4 cuts
//	- phase_plot(): to plot total and electron (+LAr cut) efficiencies for all detectors for each phase
//	- phase_fep(): to plot electron (+LAr cut) efficiencies for all detectors for each phase

#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace std;

//-----------------------------------------------------------------------------------------------
Int_t NumberOfRows(char *filename) {

	Int_t NumOfRows = 0;
	std::string line;
	std::ifstream file(filename);
	
	while (std::getline(file,line)) {
		++NumOfRows;
	}
	
	return NumOfRows;
}
//-----------------------------------------------------------------------------------------------
int plot_efficiency(int eff_type, int ans);
int phase_fep();
//-----------------------------------------------------------------------------------------------
double HistoIntegral(TH1D *histo, double min, double max) {

	// min/max -> bins
	int minBin = histo->GetXaxis()->FindBin(min);
	int maxBin = histo->GetXaxis()->FindBin(max);
	
	return histo->Integral(minBin, maxBin);
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int efficiency_fep() {
	
	// Phase II+
	fstream write1;
	write1.open("FepEff_phaseIIp_enrCoax.txt", ios::out);
	fstream write2;
	write2.open("FepEff_phaseIIp_enrBEGe.txt", ios::out);
	fstream write3;
	write3.open("FepEff_phaseIIp_invCoax.txt", ios::out);
	// Phase II
	fstream write4;
	write4.open("FepEff_phaseII_enrCoax.txt", ios::out);
	fstream write5;
	write5.open("FepEff_phaseII_enrBEGe.txt", ios::out);
	
	// Phase II+
	fstream write6;
	write6.open("LAr_enrCoax_phIIp.txt", ios::out);
	fstream write7;
	write7.open("LAr_enrBEGe_phIIp.txt", ios::out);
	fstream write8;
	write8.open("LAr_invCoax_phIIp.txt", ios::out);
	// Phase II
	fstream write9;
	write9.open("LAr_enrCoax_phII.txt", ios::out);
	fstream write10;
	write10.open("LAr_enrBEGe_phII.txt", ios::out);
	
	// Phase II
	int enrCoax_energies_II[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12 -> ! Non esiste il file per E=165 keV !
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
	int enrBEGe_energies_II[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
		
	// Phase II+			   
	int enrCoax_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12 -> ! Non esiste il file per E=165 keV !
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
	int enrBEGe_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
	int invCoax_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
				   
				   
				   
	for ( int det=0; det<=2; det++ ) {
		for ( int j=0; j<97; j++ ) {
			for ( int phase=0; phase<=1; phase++ ) {
			
				if ( phase==0 ) { // Phase II+
					if ( det==0 && j==11 ) { continue; }
				}
				if ( phase==1 ) { // Phase II
					if ( det==0 && j==11 ) { continue; }
				}
		
				double eff_raw=0, eff_LAr=0, eff_PSD=0, eff_LAr_PSD=0;
				double delta = 0;
				
				if ( det==0 ) { delta=2; }
				if ( det==1 ) { delta=2.27; }
				if ( det==2 ) { delta=2.63; }
				
				int energy = 0;
				if ( phase==0 ) { // Phase II+
					if ( det==0 ) { energy = enrCoax_energies_IIP[j]; }
					if ( det==1 ) { energy = enrBEGe_energies_IIP[j]; }
					if ( det==2 ) { energy = invCoax_energies_IIP[j]; }
				}
				if ( phase==1 ) { // Phase II
					if ( det==0 ) { energy = enrCoax_energies_II[j]; }
					if ( det==1 ) { energy = enrBEGe_energies_II[j]; }
					if ( det==2 ) { }
				}
				
				if ( det==0 && energy>=200 ) { delta=1.8; }
				
				for ( int state=0; state<=3; state++ ) {
				
					char file_name[200];
					if ( phase==0 ) { // Phase II+
						if ( det==0 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", energy);
						if ( det==1 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", energy);
						if ( det==2 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", energy);
					}
					if ( phase==1 ) { // Phase II
						if ( energy<=195 ) {
							if ( det==0 ) sprintf(file_name, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", energy);
							if ( det==1 ) sprintf(file_name, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_bege-electron_%ikeV.root", energy);
							if ( det==2 ) continue;
						}
						if ( energy>195 ) {
							if ( det==0 ) sprintf(file_name, "super-wimps-phII/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", energy);
							if ( det==1 ) sprintf(file_name, "super-wimps-phII/pdf-gedet-intrinsic_bege-electron_%ikeV.root", energy);
							if ( det==2 ) continue;
						}
					}
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
					/*if ( energy==200 && det==0 && state==1 && phase==1 ) {
						int cont = 0;
						int z = 0;
						while ( cont==0 ) {
							z++;
							cont = histo->GetBinContent(z);
						}
						cout << " x (first bin non null - Phase II) = " << z-1 << endl;
					}*/
					
					
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
					
					file->Close();
				}
			
				if ( phase==0 ) { // Phase II+
					if ( det==0 ) { write1 << energy << "\t\t" << eff_raw << "\t\t" << eff_LAr << "\t\t" << eff_PSD << "\t\t" << eff_LAr_PSD << endl;
							if (j==10) { write1 << 165 << "\t\t" << 0 << "\t\t" << 0 << "\t\t" << 0 << "\t\t" << 0 << endl; }}
					if ( det==1 ) { write2 << energy << "\t\t" << eff_raw << "\t\t" << eff_LAr << "\t\t" << eff_PSD << "\t\t" << eff_LAr_PSD << endl; }
					if ( det==2 ) { write3 << energy << "\t\t" << eff_raw << "\t\t" << eff_LAr << "\t\t" << eff_PSD << "\t\t" << eff_LAr_PSD << endl; }
					if ( det==0 ) { write6 << energy << "\t\t" << eff_raw/eff_LAr << endl; }
					if ( det==1 ) { write7 << energy << "\t\t" << eff_raw/eff_LAr << endl; }
					if ( det==2 ) { write8 << energy << "\t\t" << eff_raw/eff_LAr << endl; }
				}
				if ( phase==1 ) { // Phase II
					if ( det==0 ) { write4 << energy << "\t\t" << eff_raw << "\t\t" << eff_LAr << "\t\t" << eff_PSD << "\t\t" << eff_LAr_PSD << endl; 
							if (j==10) { write4 << 165 << "\t\t" << 0 << "\t\t" << 0 << "\t\t" << 0 << "\t\t" << 0 << endl; }}
					if ( det==1 ) { write5 << energy << "\t\t" << eff_raw << "\t\t" << eff_LAr << "\t\t" << eff_PSD << "\t\t" << eff_LAr_PSD << endl; }
					if ( det==2 ) { }
					if ( det==0 ) { write9 << energy << "\t\t" << eff_raw/eff_LAr << endl; }
					if ( det==1 ) { write10 << energy << "\t\t" << eff_raw/eff_LAr << endl; }
					if ( det==2 ) { }
				}	
			}
		}
	}

	write1.close();
	write2.close();
	write2.close();
	write4.close();
	write5.close();
	write6.close();
	write7.close();
	write8.close();
	write9.close();
	write10.close();
	
	// efficiency plot
	//int a = plot_efficiency(0, 1); // 0 = to plot raw+lar efficiencies
	int a = phase_fep();
	
	// write JSON files
	fstream output1; // Phase II
	output1.open("FepEff_phII.json", ios::out);
	fstream output2; // Phase II+
	output2.open("FepEff_phIIplus.json", ios::out);
	
	char name1[200], name2[200], name3[200], name4[200], name5[200];
	sprintf(name1, "FepEff_phaseII_enrCoax.txt");
	sprintf(name2, "FepEff_phaseII_enrBEGe.txt");
	sprintf(name3, "FepEff_phaseIIp_enrCoax.txt");
	sprintf(name4, "FepEff_phaseIIp_enrBEGe.txt");
	sprintf(name5, "FepEff_phaseIIp_invCoax.txt");
	ifstream input1(name1);
	ifstream input2(name2);
	ifstream input3(name3);
	ifstream input4(name4);
	ifstream input5(name5);
	
	Int_t rows_coax_II = NumberOfRows(name1);
	Int_t rows_BEGe_II = NumberOfRows(name2);
	double data_coax_II[rows_coax_II][5], data_BEGe_II[rows_BEGe_II][5];
	Int_t rows_coax_IIP = NumberOfRows(name3);
	Int_t rows_BEGe_IIP = NumberOfRows(name4);
	Int_t rows_IC_IIP = NumberOfRows(name5);
	double data_coax_IIP[rows_coax_IIP][5], data_BEGe_IIP[rows_BEGe_IIP][5], data_IC_IIP[rows_IC_IIP][5];
	
	for ( int i=0; i<rows_coax_II; i++ ) { for ( int j=0; j<5; j++ ) { input1 >> data_coax_II[i][j]; } }
	for ( int i=0; i<rows_BEGe_II; i++ ) { for ( int j=0; j<5; j++ ) { input2 >> data_BEGe_II[i][j]; } }
	for ( int i=0; i<rows_coax_IIP; i++ ) { for ( int j=0; j<5; j++ ) { input3 >> data_coax_IIP[i][j]; } }
	for ( int i=0; i<rows_BEGe_IIP; i++ ) { for ( int j=0; j<5; j++ ) { input4 >> data_BEGe_IIP[i][j]; } }
	for ( int i=0; i<rows_IC_IIP; i++ ) { for ( int j=0; j<5; j++ ) { input5 >> data_IC_IIP[i][j]; } }
	
	input1.close();
	input2.close();
	input3.close();
	input4.close();
	input5.close();
	
	json jfinal1, jfinal2;
	// Phase II
	for ( int i=0; i<rows_coax_II; i++ ) {
	
		json jtot = json::object({ {"eff_raw", data_coax_II[i][1]},
					   {"eff_LAr", data_coax_II[i][2]},
					   {"eff_PSD", data_coax_II[i][3]},
					   {"eff_LAr_PSD", data_coax_II[i][4]} });
					   
		char energy[200];
		sprintf(energy, "%g", data_coax_II[i][0]);
		json jen = json::object({ {energy, jtot} });
	
		if ( i==0 ) jfinal1["enrCoax"] = {jen};
		else { jfinal1["enrCoax"].push_back({energy, jtot}); }
	}
	for ( int i=0; i<rows_BEGe_II; i++ ) {
	
		json jtot = json::object({ {"eff_raw", data_BEGe_II[i][1]},
					   {"eff_LAr", data_BEGe_II[i][2]},
					   {"eff_PSD", data_BEGe_II[i][3]},
					   {"eff_LAr_PSD", data_BEGe_II[i][4]} });
					   
		char energy[200];
		sprintf(energy, "%g", data_BEGe_II[i][0]);
		json jen = json::object({ {energy, jtot} });
	
		if ( i==0 ) jfinal1["enrBEGe"] = {jen};
		else { jfinal1["enrBEGe"].push_back({energy, jtot}); }
	}
	// Phase II+
	for ( int i=0; i<rows_coax_IIP; i++ ) {
	
		json jtot = json::object({ {"eff_raw", data_coax_IIP[i][1]},
					   {"eff_LAr", data_coax_IIP[i][2]},
					   {"eff_PSD", data_coax_IIP[i][3]},
					   {"eff_LAr_PSD", data_coax_IIP[i][4]} });
					   
		char energy[200];
		sprintf(energy, "%g", data_coax_IIP[i][0]);
		json jen = json::object({ {energy, jtot} });
	
		if ( i==0 ) jfinal2["enrCoax"] = {jen};
		else { jfinal2["enrCoax"].push_back({energy, jtot}); }
	}
	for ( int i=0; i<rows_BEGe_IIP; i++ ) {
	
		json jtot = json::object({ {"eff_raw", data_BEGe_IIP[i][1]},
					   {"eff_LAr", data_BEGe_IIP[i][2]},
					   {"eff_PSD", data_BEGe_IIP[i][3]},
					   {"eff_LAr_PSD", data_BEGe_IIP[i][4]} });
					   
		char energy[200];
		sprintf(energy, "%g", data_BEGe_IIP[i][0]);
		json jen = json::object({ {energy, jtot} });
	
		if ( i==0 ) jfinal2["enrBEGe"] = {jen};
		else { jfinal2["enrBEGe"].push_back({energy, jtot}); }
	}
	for ( int i=0; i<rows_IC_IIP; i++ ) {
	
		json jtot = json::object({ {"eff_raw", data_IC_IIP[i][1]},
					   {"eff_LAr", data_IC_IIP[i][2]},
					   {"eff_PSD", data_IC_IIP[i][3]},
					   {"eff_LAr_PSD", data_IC_IIP[i][4]} });
					   
		char energy[200];
		sprintf(energy, "%g", data_IC_IIP[i][0]);
		json jen = json::object({ {energy, jtot} });
	
		if ( i==0 ) jfinal2["invCoax"] = {jen};
		else { jfinal2["invCoax"].push_back({energy, jtot}); }
	}
	
	output1 << jfinal1.dump(4) << std::endl; // Phase II	
	output2 << jfinal2.dump(4) << std::endl; // Phase II+
	
	output1.close();
	output2.close();
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int efficiency_tot() {
	
	// Phase II+
	fstream write1;
	write1.open("TotEff_phaseIIp_enrCoax.txt", ios::out);
	fstream write2;
	write2.open("TotEff_phaseIIp_enrBEGe.txt", ios::out);
	fstream write3;
	write3.open("TotEff_phaseIIp_invCoax.txt", ios::out);
	// Phase II
	fstream write4;
	write4.open("TotEff_phaseII_enrCoax.txt", ios::out);
	fstream write5;
	write5.open("TotEff_phaseII_enrBEGe.txt", ios::out);
	
	fstream fileDetData;
	fileDetData.open("detector-data/phase2I-detectorData.json", ios::in);
	json j_DetData;
	fileDetData >> j_DetData;
	fileDetData.close();
	
	// Phase II
	int enrCoax_energies_II[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12 -> ! Non esiste il file per E=165 keV !
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
	int enrBEGe_energies_II[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000}; 	// 11
		
	// Phase II+			   
	int enrCoax_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12 -> ! Non esiste il file per E=165 keV !
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};	// 11
	int enrBEGe_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};	// 11
	int invCoax_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
				   
	for ( int det=0; det<=2; det++ ) {
		for ( int j=0; j<97; j++ ) {
			for ( int phase=0; phase<=1; phase++ ) {
		
				if ( phase==0 ) { // Phase II+
					if ( det==0 && j==11 ) { continue; }
				}
				if ( phase==1 ) { // Phase II
					if ( det==0 && j==11 ) { continue; }
				}
			
				double eff_raw=0, eff_LAr=0, eff_PSD=0, eff_LAr_PSD=0;
				double eff_raw_tot=0, eff_LAr_tot=0, eff_PSD_tot=0, eff_LAr_PSD_tot=0;
				double delta = 0;
				
				if ( det==0 ) { delta=2; }
				if ( det==1 ) { delta=2.27; }
				if ( det==2 ) { delta=2.63; }
				
				int energy = 0;
                                if ( phase==0 ) { // Phase II+
                                        if ( det==0 ) { energy = enrCoax_energies_IIP[j]; }
                                        if ( det==1 ) { energy = enrBEGe_energies_IIP[j]; }
                                        if ( det==2 ) { energy = invCoax_energies_IIP[j]; }
                                }
                                if ( phase==1 ) { // Phase II
                                        if ( det==0 ) { energy = enrCoax_energies_II[j]; }
                                        if ( det==1 ) { energy = enrBEGe_energies_II[j]; }
                                        if ( det==2 ) { }
                                }

				
				for ( int state=0; state<=3; state++ ) {
				
					char file_name[200];
					if ( phase==0 ) { // Phase II+
                                                if ( det==0 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", energy);
                                                if ( det==1 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", energy);
                                                if ( det==2 ) sprintf(file_name, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", energy);
                                        }
                                        if ( phase==1 ) { // Phase II
                                                if ( energy<=195 ) {
                                                        if ( det==0 ) sprintf(file_name, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", energy);
                                                        if ( det==1 ) sprintf(file_name, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_bege-electron_%ikeV.root", energy);
                                                        if ( det==2 ) continue;
                                                }
                                                if ( energy>195 ) {
                                                        if ( det==0 ) sprintf(file_name, "super-wimps-phII/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", energy);
                                                        if ( det==1 ) sprintf(file_name, "super-wimps-phII/pdf-gedet-intrinsic_bege-electron_%ikeV.root", energy);
                                                        if ( det==2 ) continue;
                                                }
                                        }

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
					
					double M_av=0, M_tot=0;
					const int detTOT = 41;
					
					// TOTAL EFFICIENCY
					if ( det==0 ) { 
						for ( int i=0; i<detTOT; i++ ) {
							if ( (i>=0 && i<=35) && i!=8 && i!=9 && i!=10 && i!=27 && i!=28 && i!=29 ) {
								char channel[10];
								sprintf(channel, "%i", i);
								M_av += j_DetData["detData"][channel]["activemass"].get<double>();
								M_tot += j_DetData["detData"][channel]["mass"].get<double>();
							}
						}
					}
					if ( det==1 ) { 
						for ( int i=0; i<detTOT; i++ ) {
							if ( (i>=8 && i<=10) || (i>=27 && i<=29) ) { // nella phII c'è anche i==36
								char channel[10];
								sprintf(channel, "%i", i);
								M_av += j_DetData["detData"][channel]["activemass"].get<double>();
								M_tot += j_DetData["detData"][channel]["mass"].get<double>();
							}
						}
					}
					if ( det==2 ) { 
						for ( int i=0; i<detTOT; i++ ) {
							if ( i>=36 ) {
								char channel[10];
								sprintf(channel, "%i", i);
								M_av += j_DetData["detData"][channel]["activemass"].get<double>();
								M_tot += j_DetData["detData"][channel]["mass"].get<double>();
							}
						}
					}
					
					if ( state==0 ) { eff_raw_tot = eff_raw*(M_av/M_tot); }
					if ( state==1 ) { eff_LAr_tot = eff_LAr*(M_av/M_tot); }
					if ( state==2 ) { eff_PSD_tot = eff_PSD*(M_av/M_tot); }
					if ( state==3 ) { eff_LAr_PSD_tot = eff_LAr_PSD*(M_av/M_tot); }
					
					file->Close();
				}
			
				if ( phase==0 ) { // Phase II+
                                        if ( det==0 ) { write1 << energy << "\t\t" << eff_raw_tot << "\t\t" << eff_LAr_tot << "\t\t" << eff_PSD_tot << "\t\t" << eff_LAr_PSD_tot << endl; }
                                        if ( det==1 ) { write2 << energy << "\t\t" << eff_raw_tot << "\t\t" << eff_LAr_tot << "\t\t" << eff_PSD_tot << "\t\t" << eff_LAr_PSD_tot << endl; }
                                        if ( det==2 ) { write3 << energy << "\t\t" << eff_raw_tot << "\t\t" << eff_LAr_tot << "\t\t" << eff_PSD_tot << "\t\t" << eff_LAr_PSD_tot << endl; }
                                }
                                if ( phase==1 ) { // Phase II
                                        if ( det==0 ) { write4 << energy << "\t\t" << eff_raw_tot << "\t\t" << eff_LAr_tot << "\t\t" << eff_PSD_tot << "\t\t" << eff_LAr_PSD_tot << endl; }
                                        if ( det==1 ) { write5 << energy << "\t\t" << eff_raw_tot << "\t\t" << eff_LAr_tot << "\t\t" << eff_PSD_tot << "\t\t" << eff_LAr_PSD_tot << endl; }
                                        if ( det==2 ) { }
                                }	
			}
		}
	}

	write1.close();
	write2.close();
	write3.close();
	write4.close();
	write5.close();
	
	// efficiency plot
	int a = plot_efficiency(1, 1); // 1 = to plot total efficiencies
	
	// write JSON files
	fstream output1; // Phase II
	output1.open("TotEff_phII.json", ios::out);
	fstream output2; // Phase II+
	output2.open("TotEff_phIIplus.json", ios::out);
	
	char name1[200], name2[200], name3[200], name4[200], name5[200];
	sprintf(name1, "TotEff_phaseII_enrCoax.txt");
	sprintf(name2, "TotEff_phaseII_enrBEGe.txt");
	sprintf(name3, "TotEff_phaseIIp_enrCoax.txt");
	sprintf(name4, "TotEff_phaseIIp_enrBEGe.txt");
	sprintf(name5, "TotEff_phaseIIp_invCoax.txt");
	ifstream input1(name1);
	ifstream input2(name2);
	ifstream input3(name3);
	ifstream input4(name4);
	ifstream input5(name5);
	
	Int_t rows_coax_II = NumberOfRows(name1);
        Int_t rows_BEGe_II = NumberOfRows(name2);
        double data_coax_II[rows_coax_II][5], data_BEGe_II[rows_BEGe_II][5];
        Int_t rows_coax_IIP = NumberOfRows(name3);
        Int_t rows_BEGe_IIP = NumberOfRows(name4);
        Int_t rows_IC_IIP = NumberOfRows(name5);
        double data_coax_IIP[rows_coax_IIP][5], data_BEGe_IIP[rows_BEGe_IIP][5], data_IC_IIP[rows_IC_IIP][5];
	
	for ( int i=0; i<rows_coax_II; i++ ) { for ( int j=0; j<5; j++ ) { input1 >> data_coax_II[i][j]; } }
        for ( int i=0; i<rows_BEGe_II; i++ ) { for ( int j=0; j<5; j++ ) { input2 >> data_BEGe_II[i][j]; } }
        for ( int i=0; i<rows_coax_IIP; i++ ) { for ( int j=0; j<5; j++ ) { input3 >> data_coax_IIP[i][j]; } }
        for ( int i=0; i<rows_BEGe_IIP; i++ ) { for ( int j=0; j<5; j++ ) { input4 >> data_BEGe_IIP[i][j]; } }
        for ( int i=0; i<rows_IC_IIP; i++ ) { for ( int j=0; j<5; j++ ) { input5 >> data_IC_IIP[i][j]; } }

        input1.close();
        input2.close();
        input3.close();
        input4.close();
        input5.close();

        json jfinal1, jfinal2;
        // Phase II
        for ( int i=0; i<rows_coax_II; i++ ) {

                json jtot = json::object({ {"eff_raw", data_coax_II[i][1]},
                                           {"eff_LAr", data_coax_II[i][2]},
                                           {"eff_PSD", data_coax_II[i][3]},
                                           {"eff_LAr_PSD", data_coax_II[i][4]} });

                char energy[200];
                sprintf(energy, "%g", data_coax_II[i][0]);
                json jen = json::object({ {energy, jtot} });

                if ( i==0 ) jfinal1["enrCoax"] = {jen};
                else { jfinal1["enrCoax"].push_back({energy, jtot}); }
        }
        for ( int i=0; i<rows_BEGe_II; i++ ) {

                json jtot = json::object({ {"eff_raw", data_BEGe_II[i][1]},
                                           {"eff_LAr", data_BEGe_II[i][2]},
                                           {"eff_PSD", data_BEGe_II[i][3]},
                                           {"eff_LAr_PSD", data_BEGe_II[i][4]} });

                char energy[200];
                sprintf(energy, "%g", data_BEGe_II[i][0]);
                json jen = json::object({ {energy, jtot} });

                if ( i==0 ) jfinal1["enrBEGe"] = {jen};
                else { jfinal1["enrBEGe"].push_back({energy, jtot}); }
        }
        // Phase II+
	for ( int i=0; i<rows_coax_IIP; i++ ) {

                json jtot = json::object({ {"eff_raw", data_coax_IIP[i][1]},
                                           {"eff_LAr", data_coax_IIP[i][2]},
                                           {"eff_PSD", data_coax_IIP[i][3]},
                                           {"eff_LAr_PSD", data_coax_IIP[i][4]} });

                char energy[200];
                sprintf(energy, "%g", data_coax_IIP[i][0]);
                json jen = json::object({ {energy, jtot} });

                if ( i==0 ) jfinal2["enrCoax"] = {jen};
                else { jfinal2["enrCoax"].push_back({energy, jtot}); }
        }
	for ( int i=0; i<rows_BEGe_IIP; i++ ) {

                json jtot = json::object({ {"eff_raw", data_BEGe_IIP[i][1]},
                                           {"eff_LAr", data_BEGe_IIP[i][2]},
                                           {"eff_PSD", data_BEGe_IIP[i][3]},
                                           {"eff_LAr_PSD", data_BEGe_IIP[i][4]} });

                char energy[200];
                sprintf(energy, "%g", data_BEGe_IIP[i][0]);
                json jen = json::object({ {energy, jtot} });

                if ( i==0 ) jfinal2["enrBEGe"] = {jen};
                else { jfinal2["enrBEGe"].push_back({energy, jtot}); }
        }
        for ( int i=0; i<rows_IC_IIP; i++ ) {

                json jtot = json::object({ {"eff_raw", data_IC_IIP[i][1]},
                                           {"eff_LAr", data_IC_IIP[i][2]},
                                           {"eff_PSD", data_IC_IIP[i][3]},
                                           {"eff_LAr_PSD", data_IC_IIP[i][4]} });

                char energy[200];
                sprintf(energy, "%g", data_IC_IIP[i][0]);
                json jen = json::object({ {energy, jtot} });

                if ( i==0 ) jfinal2["invCoax"] = {jen};
                else { jfinal2["invCoax"].push_back({energy, jtot}); }
        }

	output1 << jfinal1.dump(4) << std::endl; // Phase II    
        output2 << jfinal2.dump(4) << std::endl; // Phase II+

        output1.close();
        output2.close();
	
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
	
	TCanvas *c = new TCanvas("c", "c", 1800, 700);
	c->SetLogy();
	TH1D *histo = (TH1D*) file->Get(dir_histo);
	histo->GetXaxis()->SetRangeUser(40, 920);
	histo->GetYaxis()->SetRangeUser(3e2, 1e7);
	histo->SetStats(kFALSE);
	histo->SetLineColor(0);
	histo->SetLineWidth(2);
	histo->GetXaxis()->SetTitle("Energy [keV]");
	histo->GetXaxis()->CenterTitle();
	histo->GetYaxis()->CenterTitle();
	histo->GetYaxis()->SetTitle("Events / 1 keV");
	histo->GetXaxis()->SetTitleSize(0.05);
	histo->GetXaxis()->SetLabelSize(0.05);
	histo->GetYaxis()->SetTitleSize(0.05);
	histo->GetYaxis()->SetLabelSize(0.05);
	histo->SetFillColor(kAzure-9);
	histo->Draw("B,bar2");
	
	int xL = 894;
	int xR = En + 100;
	int bins = xR - xL;
	TH1D *hfep = new TH1D("hfep","", bins, xL, xR);
	hfep->SetStats(kFALSE);
	hfep->SetLineColor(0);
	hfep->SetFillColor(kAzure-3);
	for ( int i=1; i<=bins; i++ ) {
		hfep->SetBinContent(i, histo->GetBinContent(histo->GetXaxis()->FindBin(i+xL-1)));
	}
	hfep->Draw("B,bar2,same");
	c->RedrawAxis();
	
	auto *legend = new TLegend(.15, .7, .42, .88);
	legend->AddEntry(hfep, "Full energy deposition", "f");
	legend->AddEntry(histo, "Partial energy deposition", "f");
	legend->SetBorderSize(0);
	legend->Draw();

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
	cout << " Choose the first energy in [60;1000] keV: ";
	cin >> En;
	
	int En2;
	cout << " Choose the second energy in [60;1000] keV: ";
	cin >> En2;
	
	int ans;
	cout << " Shifted (0) or not (1)? ";
	cin >> ans;
	
	int phase;
	cout << " Phase II+ (0) or II (1)? ";
	cin >> phase;
	
	// Phase II+			   
	int enrCoax_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12 -> ! Non esiste il file per E=165 keV !
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
	int enrBEGe_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
	int invCoax_energies_IIP[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11	
				   
	char file_name1[200], file_name2[200];
	if ( phase==0 ) { // Phase II+
		if ( det==0 ) sprintf(file_name1, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", En);
		if ( det==1 ) sprintf(file_name1, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En);
		if ( det==2 ) sprintf(file_name1, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", En);
		
		if ( det==0 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", En2);
		if ( det==1 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En2);
		if ( det==2 ) sprintf(file_name2, "super-wimps-phIIplus/pdf-gedet-intrinsic_invcoax-electron_%ikeV.root", En2);
	}
	if ( phase==1 ) { // Phase II
		if ( En<=195 ) {
			if ( det==0 ) sprintf(file_name1, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", En);
			if ( det==1 ) sprintf(file_name1, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En);
		}
		if ( En2<=195 ) {
			if ( det==0 ) sprintf(file_name2, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", En2);
			if ( det==1 ) sprintf(file_name2, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En2);
		}
		if ( En>195 ) {
			if ( det==0 ) sprintf(file_name1, "super-wimps-phII/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", En);
			if ( det==1 ) sprintf(file_name1, "super-wimps-phII/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En);
		}
		if ( En2>195 ) {
			if ( det==0 ) sprintf(file_name2, "super-wimps-phII/pdf-gedet-intrinsic_semicoax-electron_%ikeV.root", En2);
			if ( det==1 ) sprintf(file_name2, "super-wimps-phII/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En2);
		}
	}
	TFile *file1 = new TFile(file_name1);
	TFile *file2 = new TFile(file_name2);
	
	char dir_histo[200];
	if ( det==0 ) sprintf(dir_histo, "lar/M1_enrCoax");
	if ( det==1 ) sprintf(dir_histo, "lar/M1_enrBEGe");
	if ( det==2 ) sprintf(dir_histo, "lar/M1_invCoax");
	
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
	
	double delta=0.0, delta2=0.0;
	if ( det==0 ) delta=2; delta2=2;
	if ( det==1 ) delta=2.27;
	if ( det==2 ) delta=2.63;
					
	double sigma1=0.0, sigma2=0.0;
	if ( det==0 ) { sigma1 = sqrt (0.985 + 0.0001073*En); sigma2 = sqrt (0.985 + 0.0001073*En2); }
	if ( det==1 ) { sigma1 = sqrt (0.551 + 0.0004294*En); sigma2 = sqrt (0.551 + 0.0004294*En2); }
	if ( det==2 ) { sigma1 = sqrt (0.28 + 0.000583*En); sigma2 = sqrt (0.28 + 0.000583*En2); }
	int bin_max1 = histo1->GetMaximumBin();
	int bin_max2 = histo2->GetMaximumBin();
	int peak_mode1 = histo1->GetBinContent(bin_max1);
	int peak_mode2 = histo2->GetBinContent(bin_max2);
	double FWHM1 = sqrt (8*log(2))*sigma1;
	double FWHM2 = sqrt (8*log(2))*sigma2;
					
	// signal window
	double xmin_sig1 = En-delta*FWHM1;
	double xmin_sig2 = En2-delta2*FWHM2;
	double xmax_sig1 = En+delta*FWHM1;
	double xmax_sig2 = En2+delta2*FWHM2;
				
	// bkg window (L and R of signal)
	double xmin_L_bkg1 = En-2*delta*FWHM1;
	double xmin_L_bkg2 = En2-2*delta2*FWHM2;
	double xmin_R_bkg1 = xmin_sig1;
	double xmin_R_bkg2 = xmin_sig2;
	double xmax_L_bkg1 = xmax_sig1;
	double xmax_L_bkg2 = xmax_sig2;
	double xmax_R_bkg1 = En+2*delta*FWHM1;
	double xmax_R_bkg2 = En2+2*delta2*FWHM2;
				
	// signal events
	int nPeak1 = HistoIntegral(histo1, xmin_sig1, xmax_sig1);
	int nPeak2 = HistoIntegral(histo2, xmin_sig2, xmax_sig2);
	// bkg events
	int nBkg1 = HistoIntegral(histo1, xmin_L_bkg1, xmin_R_bkg1) + HistoIntegral(histo1, xmax_L_bkg1, xmax_R_bkg1);
	int nBkg2 = HistoIntegral(histo2, xmin_L_bkg2, xmin_R_bkg2) + HistoIntegral(histo2, xmax_L_bkg2, xmax_R_bkg2);
	// efficiencies	
	double ratio1 = ( nPeak1 - nBkg1 ) / ( 1e7 + 0.0 );
	double ratio2 = ( nPeak2 - nBkg2 ) / ( 1e7 + 0.0 );
	
	cout << "\n\n 1)\n xmin_sig1 = " << xmin_sig1 << "\t xmax_sig1 = " << xmax_sig1 << endl;
	cout << " xmin_L_bkg1 = " << xmin_L_bkg1 << "\t xmin_R_bkg1 = " << xmin_R_bkg1 << endl;
	cout << " xmax_L_bkg1 = " << xmax_L_bkg1 << "\t xmax_R_bkg1 = " << xmax_R_bkg1 << endl;
	cout << " 2)\n xmin_sig2 = " << xmin_sig2 << "\t xmax_sig2 = " << xmax_sig2 << endl;
	cout << " xmin_L_bkg2 = " << xmin_L_bkg2 << "\t xmin_R_bkg2 = " << xmin_R_bkg2 << endl;
	cout << " xmax_L_bkg2 = " << xmax_L_bkg2 << "\t xmax_R_bkg2 = " << xmax_R_bkg2 << endl;
	
	cout << "\n 1) nPeak1 = " << nPeak1 << "\t nBkg1 = " << nBkg1 << endl;
	cout << " 2) nPeak2 = " << nPeak2 << "\t nBkg2 = " << nBkg2 << endl;
	
	cout << "\n Eff ( E1 = " << En << " ): " << ratio1 << endl;
	cout << " Eff ( E2 = " << En2 << " ): " << ratio2 << "\n" << endl;
	
	int diff = 0;
	if ( det==0 ) diff = fabs( En - En2 );
	if ( det==1 ) diff = fabs( En - En2 );
	if ( det==2 ) diff = fabs( En - En2 );
	
	if ( ans==0 ) {
		if ( En2 > En ) {
			for ( int i=1; i<(histo2->GetNbinsX())-diff; i++ ) {
				histo2->SetBinContent(i, histo2->GetBinContent(i+diff));
			}
		}
		if ( En2 < En ) {
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
	
	TLine *line1 = new TLine(xmin_sig1, 0, xmin_sig1, 1e8);
	line1->SetLineColor(kAzure+2);
	line1->SetLineStyle(9);
	line1->Draw();
	double x1, x2;
	if ( ans==0 ) { x1 = xmin_sig2-diff; x2 = xmin_sig2-diff; }
	if ( ans==1 ) { x1 = xmin_sig2; x2 = xmin_sig2; }
	TLine *line2 = new TLine(x1, 0, x2, 1e8);
	line2->SetLineColor(kAzure+2);
	line2->SetLineStyle(9);
	line2->Draw();
	TLine *line3 = new TLine(xmax_sig1, 0, xmax_sig1, 1e8);
	line3->SetLineColor(kOrange+2);
	line3->SetLineStyle(9);
	line3->Draw();
	double x3, x4;
	if ( ans==0 ) { x3 = xmax_sig2-diff; x4 = xmax_sig2-diff; }
	if ( ans==1 ) { x3 = xmax_sig2; x4 = xmax_sig2; }
	TLine *line4 = new TLine(x3, 0, x4, 1e8);
	line4->SetLineColor(kOrange+2);
	line4->SetLineStyle(9);
	line4->Draw();
	
	auto *legend = new TLegend(.15, .7, .4, .88);
	char histo1_name[200], histo2_name[200];
	sprintf(histo1_name, "Energy = %i keV", En);
	sprintf(histo2_name, "Energy = %i keV", En2);
	legend->AddEntry(histo1, histo1_name, "l");
	legend->AddEntry(histo2, histo2_name, "l");
	legend->Draw();

	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int common() {

	int det = 1;
	int En;
	cout << " Energy (<200 keV): ";
	cin >> En;
	int En2 = En;
	int ans = 0;
	int phase = 1;
	
	// Phase II			   
	int enrBEGe_energies_II[97] = { 60, 70, 80, 90, 						// 4
					100, 110, 120, 130, 140, 150, 160, 165, 170, 180, 190, 195, 	// 12
					200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 		// 10
					300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 		// 10
					400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 		// 10
					500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 		// 10
					600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 		// 10
					700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 		// 10
					800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 		// 10
					900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 1000};  	// 11
				   
	char file_name1[200], file_name2[200];
	sprintf(file_name1, "super-wimps-phII/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En);
	sprintf(file_name2, "super-wimps-phII-lowthr/pdf-gedet-intrinsic_bege-electron_%ikeV.root", En2);
	TFile *file1 = new TFile(file_name1);
	TFile *file2 = new TFile(file_name2);
	
	char dir_histo[200];
	if ( det==0 ) sprintf(dir_histo, "lar/M1_enrCoax");
	if ( det==1 ) sprintf(dir_histo, "lar/M1_enrBEGe");
	if ( det==2 ) sprintf(dir_histo, "lar/M1_invCoax");
	
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
	
	double delta=0.0, delta2=0.0;
	if ( det==0 ) delta=2; delta2=1.8;
	if ( det==1 ) delta=2.27;
	if ( det==2 ) delta=2.63;
					
	double sigma1=0.0, sigma2=0.0;
	if ( det==0 ) { sigma1 = sqrt (0.985 + 0.0001073*En); sigma2 = sqrt (0.985 + 0.0001073*En2); }
	if ( det==1 ) { sigma1 = sqrt (0.551 + 0.0004294*En); sigma2 = sqrt (0.551 + 0.0004294*En2); }
	if ( det==2 ) { sigma1 = sqrt (0.28 + 0.000583*En); sigma2 = sqrt (0.28 + 0.000583*En2); }
	int bin_max1 = histo1->GetMaximumBin();
	int bin_max2 = histo2->GetMaximumBin();
	int peak_mode1 = histo1->GetBinContent(bin_max1);
	int peak_mode2 = histo2->GetBinContent(bin_max2);
	double FWHM1 = sqrt (8*log(2))*sigma1;
	double FWHM2 = sqrt (8*log(2))*sigma2;
					
	// signal window
	double xmin_sig1 = En-delta*FWHM1;
	double xmin_sig2 = En2-delta2*FWHM2;
	double xmax_sig1 = En+delta*FWHM1;
	double xmax_sig2 = En2+delta2*FWHM2;
				
	// bkg window (L and R of signal)
	double xmin_L_bkg1 = En-2*delta*FWHM1;
	double xmin_L_bkg2 = En2-2*delta2*FWHM2;
	double xmin_R_bkg1 = xmin_sig1;
	double xmin_R_bkg2 = xmin_sig2;
	double xmax_L_bkg1 = xmax_sig1;
	double xmax_L_bkg2 = xmax_sig2;
	double xmax_R_bkg1 = En+2*delta*FWHM1;
	double xmax_R_bkg2 = En2+2*delta2*FWHM2;
				
	// signal events
	int nPeak1 = HistoIntegral(histo1, xmin_sig1, xmax_sig1);
	int nPeak2 = HistoIntegral(histo2, xmin_sig2, xmax_sig2);
	// bkg events
	int nBkg1 = HistoIntegral(histo1, xmin_L_bkg1, xmin_R_bkg1) + HistoIntegral(histo1, xmax_L_bkg1, xmax_R_bkg1);
	int nBkg2 = HistoIntegral(histo2, xmin_L_bkg2, xmin_R_bkg2) + HistoIntegral(histo2, xmax_L_bkg2, xmax_R_bkg2);
	// efficiencies	
	double ratio1 = ( nPeak1 - nBkg1 ) / ( 1e7 + 0.0 );
	double ratio2 = ( nPeak2 - nBkg2 ) / ( 1e7 + 0.0 );
	
	cout << "\n\n 1)\n xmin_sig1 = " << xmin_sig1 << "\t xmax_sig1 = " << xmax_sig1 << endl;
	cout << " xmin_L_bkg1 = " << xmin_L_bkg1 << "\t xmin_R_bkg1 = " << xmin_R_bkg1 << endl;
	cout << " xmax_L_bkg1 = " << xmax_L_bkg1 << "\t xmax_R_bkg1 = " << xmax_R_bkg1 << endl;
	cout << " 2)\n xmin_sig2 = " << xmin_sig2 << "\t xmax_sig2 = " << xmax_sig2 << endl;
	cout << " xmin_L_bkg2 = " << xmin_L_bkg2 << "\t xmin_R_bkg2 = " << xmin_R_bkg2 << endl;
	cout << " xmax_L_bkg2 = " << xmax_L_bkg2 << "\t xmax_R_bkg2 = " << xmax_R_bkg2 << endl;
	
	cout << "\n 1) nPeak1 = " << nPeak1 << "\t nBkg1 = " << nBkg1 << endl;
	cout << " 2) nPeak2 = " << nPeak2 << "\t nBkg2 = " << nBkg2 << endl;
	
	cout << "\n Eff ( E1 = " << En << " ): " << ratio1 << endl;
	cout << " Eff ( E2 = " << En2 << " ): " << ratio2 << "\n" << endl;
	
	if ( ans==0 ) {
		int diff = 0;
		if ( En2 > En ) {
			if ( det==0 ) diff = fabs( En - En2 );
			if ( det==1 ) diff = fabs( En - En2 );
			if ( det==2 ) diff = fabs( En - En2 );
			for ( int i=1; i<(histo2->GetNbinsX())-diff; i++ ) {
				histo2->SetBinContent(i, histo2->GetBinContent(i+diff));
			}
		}
		if ( En2 < En ) {
			if ( det==0 ) diff = fabs( En - En2 );
			if ( det==1 ) diff = fabs( En - En2 );
			if ( det==2 ) diff = fabs( En - En2 );
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
	sprintf(histo1_name, "Energy = %i keV / II", En);
	sprintf(histo2_name, "Energy = %i keV / II-lowthr", En2);
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
int plot_efficiency(int eff_type, int ans) {

	// eff_Type = 0 -> Fep
	// eff_Type = 1 -> TOT
	char name1[200], name2[200], name3[200], name4[200], name5[200];
	if ( eff_type==0 ) {
		sprintf(name1, "FepEff_phaseIIp_enrCoax.txt");
		sprintf(name2, "FepEff_phaseIIp_enrBEGe.txt");
		sprintf(name3, "FepEff_phaseIIp_invCoax.txt");
		sprintf(name4, "FepEff_phaseII_enrCoax.txt");
		sprintf(name5, "FepEff_phaseII_enrBEGe.txt");
	}
	if ( eff_type==1 ) {
		sprintf(name1, "TotEff_phaseIIp_enrCoax.txt");
		sprintf(name2, "TotEff_phaseIIp_enrBEGe.txt");
		sprintf(name3, "TotEff_phaseIIp_invCoax.txt");
		sprintf(name4, "TotEff_phaseII_enrCoax.txt");
		sprintf(name5, "TotEff_phaseII_enrBEGe.txt");
	}

	//=====================================================================================================
	// COAX ------------------------------------------------------------------------------------- Phase II+
	TCanvas *c_0 = new TCanvas();
	TMultiGraph *mg_0 = new TMultiGraph();
	TGraph *g1_0 = new TGraph(name1, "%lg %lg %*lg %*lg %*lg");
	g1_0->SetLineColor(kAzure);
	g1_0->SetMarkerColor(kAzure);
	g1_0->SetMarkerStyle(20);
	g1_0->SetMarkerSize(2.3);
	mg_0->Add(g1_0);
	
	TGraph *g2_0 = new TGraph(name1, "%lg %*lg %lg %*lg %*lg");
	g2_0->SetLineColor(2);
	g2_0->SetMarkerColor(2);
	g2_0->SetMarkerStyle(20);
	mg_0->Add(g2_0);
	
	TGraph *g3_0 = new TGraph(name1, "%lg %*lg %*lg %lg %*lg");
	g3_0->SetLineColor(kGreen);
	g3_0->SetMarkerColor(kGreen);
	g3_0->SetMarkerStyle(20);
	g3_0->SetMarkerSize(2.3);
	if ( ans==0 ) mg_0->Add(g3_0);
	
	TGraph *g4_0 = new TGraph(name1, "%lg %*lg %*lg %*lg %lg");
	g4_0->SetLineColor(kBlack);
	g4_0->SetMarkerColor(kBlack);
	g4_0->SetMarkerStyle(20);
	if ( ans==0 ) mg_0->Add(g4_0);
	
	if ( eff_type==0 ) mg_0->SetTitle("enrCoax - Phase II+; Energy [keV]; Efficiency");
	if ( eff_type==1 ) mg_0->SetTitle("enrCoax - Phase II+; Energy [keV]; Efficiency");
	mg_0->Draw("AP");
	
	auto *legend_0 = new TLegend(.15, .4, .3, .58);
	legend_0->AddEntry(g1_0, "Raw", "p");
	legend_0->AddEntry(g2_0, "LAr", "p");
	if ( ans==0 ) legend_0->AddEntry(g3_0, "PSD", "p");
	if ( ans==0 ) legend_0->AddEntry(g4_0, "LAr+PSD", "p");
	if ( ans==0 ) legend_0->Draw();
	
	// COAX ------------------------------------------------------------------------------------- Phase II
	TCanvas *c_0_II = new TCanvas();
	TMultiGraph *mg_0_II = new TMultiGraph();
	TGraph *g1_0_II = new TGraph(name4, "%lg %lg %*lg %*lg %*lg");
	g1_0_II->SetLineColor(kAzure);
	g1_0_II->SetMarkerColor(kAzure);
	g1_0_II->SetMarkerStyle(20);
	g1_0_II->SetMarkerSize(2.3);
	mg_0_II->Add(g1_0_II);
	
	TGraph *g2_0_II = new TGraph(name4, "%lg %*lg %lg %*lg %*lg");
	g2_0_II->SetLineColor(2);
	g2_0_II->SetMarkerColor(2);
	g2_0_II->SetMarkerStyle(20);
	mg_0_II->Add(g2_0_II);
	
	TGraph *g3_0_II = new TGraph(name4, "%lg %*lg %*lg %lg %*lg");
	g3_0_II->SetLineColor(kGreen);
	g3_0_II->SetMarkerColor(kGreen);
	g3_0_II->SetMarkerStyle(20);
	g3_0_II->SetMarkerSize(2.3);
	if ( ans==0 ) mg_0_II->Add(g3_0_II);
	
	TGraph *g4_0_II = new TGraph(name4, "%lg %*lg %*lg %*lg %lg");
	g4_0_II->SetLineColor(kBlack);
	g4_0_II->SetMarkerColor(kBlack);
	g4_0_II->SetMarkerStyle(20);
	if ( ans==0 ) mg_0_II->Add(g4_0_II);
	
	if ( eff_type==0 ) mg_0_II->SetTitle("enrCoax - Phase II; Energy [keV]; Efficiency");
	if ( eff_type==1 ) mg_0_II->SetTitle("enrCoax - Phase II; Energy [keV]; Efficiency");
	mg_0_II->Draw("AP");
	
	auto *legend_0_II = new TLegend(.15, .4, .3, .58);
	legend_0_II->AddEntry(g1_0_II, "Raw", "p");
	legend_0_II->AddEntry(g2_0_II, "LAr", "p");
	if ( ans==0 ) legend_0_II->AddEntry(g3_0_II, "PSD", "p");
	if ( ans==0 ) legend_0_II->AddEntry(g4_0_II, "LAr+PSD", "p");
	if ( ans==0 ) legend_0_II->Draw();
	
	//=====================================================================================================
	// BEGe ------------------------------------------------------------------------------------- Phase II+
	TCanvas *c_1 = new TCanvas();
	TMultiGraph *mg_1 = new TMultiGraph();
	TGraph *g1_1 = new TGraph(name2, "%lg %lg %*lg %*lg %*lg");
	g1_1->SetLineColor(kAzure);
	g1_1->SetMarkerColor(kAzure);
	g1_1->SetMarkerStyle(20);
	g1_1->SetMarkerSize(2.3);
	mg_1->Add(g1_1);
	
	TGraph *g2_1 = new TGraph(name2, "%lg %*lg %lg %*lg %*lg");
	g2_1->SetLineColor(2);
	g2_1->SetMarkerColor(2);
	g2_1->SetMarkerStyle(20);
	mg_1->Add(g2_1);
	
	TGraph *g3_1 = new TGraph(name2, "%lg %*lg %*lg %lg %*lg");
	g3_1->SetLineColor(kGreen);
	g3_1->SetMarkerColor(kGreen);
	g3_1->SetMarkerStyle(20);
	g3_1->SetMarkerSize(2.3);
	if ( ans==0 ) mg_1->Add(g3_1);
	
	TGraph *g4_1 = new TGraph(name2, "%lg %*lg %*lg %*lg %lg");
	g4_1->SetLineColor(kBlack);
	g4_1->SetMarkerColor(kBlack);
	g4_1->SetMarkerStyle(20);
	if ( ans==0 ) mg_1->Add(g4_1);
	
	if ( eff_type==0 ) mg_1->SetTitle("enrBEGe - Phase II+; Energy [keV]; Efficiency");
	if ( eff_type==1 ) mg_1->SetTitle("enrBEGe - Phase II+; Energy [keV]; Efficiency");
	mg_1->Draw("AP");
	
	auto *legend_1 = new TLegend(.15, .4, .3, .58);
	legend_1->AddEntry(g1_1, "Raw", "p");
	legend_1->AddEntry(g2_1, "LAr", "p");
	if ( ans==0 ) legend_1->AddEntry(g3_1, "PSD", "p");
	if ( ans==0 ) legend_1->AddEntry(g4_1, "LAr+PSD", "p");
	if ( ans==0 ) legend_1->Draw();
	
	// BEGe ------------------------------------------------------------------------------------- Phase II
	TCanvas *c_1_II = new TCanvas();
	TMultiGraph *mg_1_II = new TMultiGraph();
	TGraph *g1_1_II = new TGraph(name5, "%lg %lg %*lg %*lg %*lg");
	g1_1_II->SetLineColor(kAzure);
	g1_1_II->SetMarkerColor(kAzure);
	g1_1_II->SetMarkerStyle(20);
	g1_1_II->SetMarkerSize(2.3);
	mg_1_II->Add(g1_1_II);
	
	TGraph *g2_1_II = new TGraph(name5, "%lg %*lg %lg %*lg %*lg");
	g2_1_II->SetLineColor(2);
	g2_1_II->SetMarkerColor(2);
	g2_1_II->SetMarkerStyle(20);
	mg_1_II->Add(g2_1_II);
	
	TGraph *g3_1_II = new TGraph(name5, "%lg %*lg %*lg %lg %*lg");
	g3_1_II->SetLineColor(kGreen);
	g3_1_II->SetMarkerColor(kGreen);
	g3_1_II->SetMarkerStyle(20);
	g3_1_II->SetMarkerSize(2.3);
	if ( ans==0 ) mg_1_II->Add(g3_1_II);
	
	TGraph *g4_1_II = new TGraph(name5, "%lg %*lg %*lg %*lg %lg");
	g4_1_II->SetLineColor(kBlack);
	g4_1_II->SetMarkerColor(kBlack);
	g4_1_II->SetMarkerStyle(20);
	if ( ans==0 ) mg_1_II->Add(g4_1_II);
	
	if ( eff_type==0 ) mg_1_II->SetTitle("enrBEGe - Phase II; Energy [keV]; Efficiency");
	if ( eff_type==1 ) mg_1_II->SetTitle("enrBEGe - Phase II; Energy [keV]; Efficiency");
	mg_1_II->Draw("AP");
	
	auto *legend_1_II = new TLegend(.15, .4, .3, .58);
	legend_1_II->AddEntry(g1_1_II, "Raw", "p");
	legend_1_II->AddEntry(g2_1_II, "LAr", "p");
	if ( ans==0 ) legend_1_II->AddEntry(g3_1_II, "PSD", "p");
	if ( ans==0 ) legend_1_II->AddEntry(g4_1_II, "LAr+PSD", "p");
	if ( ans==0 ) legend_1_II->Draw();
	
	//=====================================================================================================
	// IC --------------------------------------------------------------------------------------- Phase II+
	TCanvas *c_2 = new TCanvas();
	TMultiGraph *mg_2 = new TMultiGraph();
	TGraph *g1_2 = new TGraph(name3, "%lg %lg %*lg %*lg %*lg");
	g1_2->SetLineColor(kAzure);
	g1_2->SetMarkerColor(kAzure);
	g1_2->SetMarkerStyle(20);
	g1_2->SetMarkerSize(2.3);
	mg_2->Add(g1_2);
	
	TGraph *g2_2 = new TGraph(name3, "%lg %*lg %lg %*lg %*lg");
	g2_2->SetLineColor(2);
	g2_2->SetMarkerColor(2);
	g2_2->SetMarkerStyle(20);
	mg_2->Add(g2_2);
	
	TGraph *g3_2 = new TGraph(name3, "%lg %*lg %*lg %lg %*lg");
	g3_2->SetLineColor(kGreen);
	g3_2->SetMarkerColor(kGreen);
	g3_2->SetMarkerStyle(20);
	g3_2->SetMarkerSize(2.3);
	if ( ans==0 ) mg_2->Add(g3_2);
	
	TGraph *g4_2 = new TGraph(name3, "%lg %*lg %*lg %*lg %lg");
	g4_2->SetLineColor(kBlack);
	g4_2->SetMarkerColor(kBlack);
	g4_2->SetMarkerStyle(20);
	if ( ans==0 ) mg_2->Add(g4_2);
	
	if ( eff_type==0 ) mg_2->SetTitle("invCoax - Phase II+; Energy [keV]; Efficiency");
	if ( eff_type==1 ) mg_2->SetTitle("invCoax - Phase II+; Energy [keV]; Efficiency");
	mg_2->Draw("AP");
	
	auto *legend_2 = new TLegend(.15, .4, .3, .58);
	legend_2->AddEntry(g1_2, "Raw", "p");
	legend_2->AddEntry(g2_2, "LAr", "p");
	if ( ans==0 ) legend_2->AddEntry(g3_2, "PSD", "p");
	if ( ans==0 ) legend_2->AddEntry(g4_2, "LAr+PSD", "p");
	if ( ans==0 ) legend_2->Draw();
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int phase_plot() {

	char name1[200], name2[200], name3[200];
	char name4[200], name5[200], name6[200];
	char name7[200], name8[200], name9[200];
	char name10[200], name11[200], name12[200];
	// coax
	sprintf(name1, "FepEff_phaseII_enrCoax.txt"); // Phase II
	sprintf(name2, "FepEff_phaseIIp_enrCoax.txt"); // Phase II+
	sprintf(name3, "TotEff_phaseII_enrCoax.txt"); // Phase II
	sprintf(name4, "TotEff_phaseIIp_enrCoax.txt"); // Phase II+
	// BEGe
	sprintf(name5, "FepEff_phaseII_enrBEGe.txt"); // Phase II
	sprintf(name6, "FepEff_phaseIIp_enrBEGe.txt"); // Phase II+
	sprintf(name7, "TotEff_phaseII_enrBEGe.txt"); // Phase II
	sprintf(name8, "TotEff_phaseIIp_enrBEGe.txt"); // Phase II+
	// IC
	sprintf(name10, "FepEff_phaseIIp_invCoax.txt"); // Phase II+
	sprintf(name12, "TotEff_phaseIIp_invCoax.txt"); // Phase II+

	//=====================================================================================================
	//=====================================================================================================
	// COAX ------------------------------------------------------------------------------------- Phase II
	TCanvas *c_0_coax = new TCanvas("c_0_coax", "c_0_coax", 1000, 900);
	TMultiGraph *mg_0_coax = new TMultiGraph();
	
	TGraph *g_1_coax = new TGraph(name1, "%lg %lg %*lg %*lg %*lg"); // fep
	g_1_coax->SetLineColor(kRed);
	g_1_coax->SetMarkerColor(kRed);
	g_1_coax->SetMarkerStyle(20);
	g_1_coax->SetMarkerSize(1.3);
	mg_0_coax->Add(g_1_coax);
	
	TGraph *g_3_coax = new TGraph(name3, "%lg %*lg %lg %*lg %*lg"); // tot
	g_3_coax->SetLineColor(kOrange-3);
	g_3_coax->SetMarkerColor(kOrange-3);
	g_3_coax->SetMarkerStyle(20);
	g_3_coax->SetMarkerSize(1.3);
	mg_0_coax->Add(g_3_coax);
	
	mg_0_coax->SetTitle("Phase II; Energy [keV]; Efficiency");
	mg_0_coax->GetXaxis()->SetTitleSize(0.05);
	mg_0_coax->GetXaxis()->SetLabelSize(0.05);
	mg_0_coax->GetXaxis()->CenterTitle();
	mg_0_coax->GetYaxis()->SetTitleSize(0.05);
	mg_0_coax->GetYaxis()->SetLabelSize(0.05);
	mg_0_coax->GetYaxis()->CenterTitle();
	mg_0_coax->GetYaxis()->CenterTitle();
	mg_0_coax->GetXaxis()->SetTitleFont(132);
	mg_0_coax->GetYaxis()->SetTitleFont(132);
	mg_0_coax->GetXaxis()->SetLabelFont(132);
	mg_0_coax->GetYaxis()->SetLabelFont(132);
	mg_0_coax->GetXaxis()->SetTitleOffset(0.92);
	mg_0_coax->GetYaxis()->SetTitleOffset(1.00);
	mg_0_coax->Draw("AP");
	
	auto *leg_0_coax = new TLegend(.15, .1, .3, .28);
	leg_0_coax->SetBorderSize(0);
	leg_0_coax->AddEntry(g_1_coax, "EnrCoax - #epsilon_{e^{-}}", "p");
	leg_0_coax->AddEntry(g_3_coax, "EnrCoax - #epsilon_{e_{tot}}", "p");
	leg_0_coax->Draw();
	
	// COAX ------------------------------------------------------------------------------------- Phase II+
	TCanvas *c_1_coax = new TCanvas("c_1_coax", "c_1_coax", 1000, 900);
	TMultiGraph *mg_1_coax = new TMultiGraph();
	
	TGraph *g_2_coax = new TGraph(name2, "%lg %lg %*lg %*lg %*lg"); // fep
	g_2_coax->SetLineColor(kRed);
	g_2_coax->SetMarkerColor(kRed);
	g_2_coax->SetMarkerStyle(20);
	g_2_coax->SetMarkerSize(1.3);
	mg_1_coax->Add(g_2_coax);
	
	TGraph *g_4_coax = new TGraph(name4, "%lg %*lg %lg %*lg %*lg"); // tot
	g_4_coax->SetLineColor(kOrange-3);
	g_4_coax->SetMarkerColor(kOrange-3);
	g_4_coax->SetMarkerStyle(20);
	g_4_coax->SetMarkerSize(1.3);
	mg_1_coax->Add(g_4_coax);
	
	mg_1_coax->SetTitle("Phase II+; Energy [keV]; Efficiency");
	mg_1_coax->GetXaxis()->SetTitleSize(0.05);
	mg_1_coax->GetXaxis()->SetLabelSize(0.05);
	mg_1_coax->GetXaxis()->CenterTitle();
	mg_1_coax->GetYaxis()->SetTitleSize(0.05);
	mg_1_coax->GetYaxis()->SetLabelSize(0.05);
	mg_1_coax->GetYaxis()->CenterTitle();
	mg_1_coax->GetYaxis()->CenterTitle();
	mg_1_coax->GetXaxis()->SetTitleFont(132);
	mg_1_coax->GetYaxis()->SetTitleFont(132);
	mg_1_coax->GetXaxis()->SetLabelFont(132);
	mg_1_coax->GetYaxis()->SetLabelFont(132);
	mg_1_coax->GetXaxis()->SetTitleOffset(0.92);
	mg_1_coax->GetYaxis()->SetTitleOffset(1.00);
	mg_1_coax->Draw("AP");
	
	auto *leg_1_coax = new TLegend(.15, .1, .3, .28);
	leg_1_coax->SetBorderSize(0);
	leg_1_coax->AddEntry(g_2_coax, "EnrCoax - #epsilon_{e^{-}}", "p");
	leg_1_coax->AddEntry(g_4_coax, "EnrCoax - #epsilon_{e_{tot}}", "p");
	leg_1_coax->Draw();
	
	//=====================================================================================================
	//=====================================================================================================
	// BEGe ------------------------------------------------------------------------------------- Phase II
	TCanvas *c_0_BEGe = new TCanvas("c_0_BEGe", "c_0_BEGe", 1000, 900);
	TMultiGraph *mg_0_BEGe = new TMultiGraph();
	
	TGraph *g_5_BEGe = new TGraph(name5, "%lg %lg %*lg %*lg %*lg"); // fep
	g_5_BEGe->SetLineColor(kBlue);
	g_5_BEGe->SetMarkerColor(kBlue);
	g_5_BEGe->SetMarkerStyle(20);
	g_5_BEGe->SetMarkerSize(1.3);
	mg_0_BEGe->Add(g_5_BEGe);
	
	TGraph *g_7_BEGe = new TGraph(name7, "%lg %*lg %lg %*lg %*lg"); // tot
	g_7_BEGe->SetLineColor(kAzure+10);
	g_7_BEGe->SetMarkerColor(kAzure+10);
	g_7_BEGe->SetMarkerStyle(20);
	g_7_BEGe->SetMarkerSize(1.3);
	mg_0_BEGe->Add(g_7_BEGe);
	
	mg_0_BEGe->SetTitle("Phase II; Energy [keV]; Efficiency");
	mg_0_BEGe->GetXaxis()->SetTitleSize(0.05);
	mg_0_BEGe->GetXaxis()->SetLabelSize(0.05);
	mg_0_BEGe->GetXaxis()->CenterTitle();
	mg_0_BEGe->GetYaxis()->SetTitleSize(0.05);
	mg_0_BEGe->GetYaxis()->SetLabelSize(0.05);
	mg_0_BEGe->GetYaxis()->CenterTitle();
	mg_0_BEGe->GetYaxis()->CenterTitle();
	mg_0_BEGe->GetXaxis()->SetTitleFont(132);
	mg_0_BEGe->GetYaxis()->SetTitleFont(132);
	mg_0_BEGe->GetXaxis()->SetLabelFont(132);
	mg_0_BEGe->GetYaxis()->SetLabelFont(132);
	mg_0_BEGe->GetXaxis()->SetTitleOffset(0.92);
	mg_0_BEGe->GetYaxis()->SetTitleOffset(1.00);
	mg_0_BEGe->Draw("AP");
	
	auto *leg_0_BEGe = new TLegend(.15, .1, .3, .28);
	leg_0_BEGe->SetBorderSize(0);
	leg_0_BEGe->AddEntry(g_5_BEGe, "EnrBEGe - #epsilon_{e^{-}}", "p");
	leg_0_BEGe->AddEntry(g_7_BEGe, "EnrBEGe - #epsilon_{e_{tot}}", "p");
	leg_0_BEGe->Draw();
	
	// BEGe ------------------------------------------------------------------------------------- Phase II+
	TCanvas *c_1_BEGe = new TCanvas("c_1_BEGe", "c_1_BEGe", 1000, 900);
	TMultiGraph *mg_1_BEGe = new TMultiGraph();
	
	TGraph *g_6_BEGe = new TGraph(name6, "%lg %lg %*lg %*lg %*lg"); // fep
	g_6_BEGe->SetLineColor(kBlue);
	g_6_BEGe->SetMarkerColor(kBlue);
	g_6_BEGe->SetMarkerStyle(20);
	g_6_BEGe->SetMarkerSize(1.3);
	mg_1_BEGe->Add(g_6_BEGe);
	
	TGraph *g_8_BEGe = new TGraph(name8, "%lg %*lg %lg %*lg %*lg"); // tot
	g_8_BEGe->SetLineColor(kAzure+10);
	g_8_BEGe->SetMarkerColor(kAzure+10);
	g_8_BEGe->SetMarkerStyle(20);
	g_8_BEGe->SetMarkerSize(1.3);
	mg_1_BEGe->Add(g_8_BEGe);
	
	mg_1_BEGe->SetTitle("Phase II+; Energy [keV]; Efficiency");
	mg_1_BEGe->GetXaxis()->SetTitleSize(0.05);
	mg_1_BEGe->GetXaxis()->SetLabelSize(0.05);
	mg_1_BEGe->GetXaxis()->CenterTitle();
	mg_1_BEGe->GetYaxis()->SetTitleSize(0.05);
	mg_1_BEGe->GetYaxis()->SetLabelSize(0.05);
	mg_1_BEGe->GetYaxis()->CenterTitle();
	mg_1_BEGe->GetYaxis()->CenterTitle();
	mg_1_BEGe->GetXaxis()->SetTitleFont(132);
	mg_1_BEGe->GetYaxis()->SetTitleFont(132);
	mg_1_BEGe->GetXaxis()->SetLabelFont(132);
	mg_1_BEGe->GetYaxis()->SetLabelFont(132);
	mg_1_BEGe->GetXaxis()->SetTitleOffset(0.92);
	mg_1_BEGe->GetYaxis()->SetTitleOffset(1.00);
	mg_1_BEGe->Draw("AP");
	
	auto *leg_1_BEGe = new TLegend(.15, .1, .3, .28);
	leg_1_BEGe->SetBorderSize(0);
	leg_1_BEGe->AddEntry(g_6_BEGe, "EnrBEGe - #epsilon_{e^{-}}", "p");
	leg_1_BEGe->AddEntry(g_8_BEGe, "EnrBEGe - #epsilon_{e_{tot}}", "p");
	leg_1_BEGe->Draw();
	
	//=====================================================================================================
	//=====================================================================================================
	// IC --------------------------------------------------------------------------------------- Phase II+
	TCanvas *c_1_IC = new TCanvas("c_1_IC", "c_1_IC", 1000, 900);
	TMultiGraph *mg_1_IC= new TMultiGraph();
	
	TGraph *g_10_IC = new TGraph(name10, "%lg %lg %*lg %*lg %*lg"); // fep
	g_10_IC->SetLineColor(kGreen+2);
	g_10_IC->SetMarkerColor(kGreen+2);
	g_10_IC->SetMarkerStyle(20);
	g_10_IC->SetMarkerSize(1.3);
	mg_1_IC->Add(g_10_IC);
	
	TGraph *g_12_IC = new TGraph(name12, "%lg %*lg %lg %*lg %*lg"); // tot
	g_12_IC->SetLineColor(kSpring+9);
	g_12_IC->SetMarkerColor(kSpring+9);
	g_12_IC->SetMarkerStyle(20);
	g_12_IC->SetMarkerSize(1.3);
	mg_1_IC->Add(g_12_IC);
	
	mg_1_IC->SetTitle("Phase II+; Energy [keV]; Efficiency");
	mg_1_IC->GetXaxis()->SetTitleSize(0.05);
	mg_1_IC->GetXaxis()->SetLabelSize(0.05);
	mg_1_IC->GetXaxis()->CenterTitle();
	mg_1_IC->GetYaxis()->SetTitleSize(0.05);
	mg_1_IC->GetYaxis()->SetLabelSize(0.05);
	mg_1_IC->GetYaxis()->CenterTitle();
	mg_1_IC->GetXaxis()->SetTitleFont(132);
	mg_1_IC->GetYaxis()->SetTitleFont(132);
	mg_1_IC->GetXaxis()->SetLabelFont(132);
	mg_1_IC->GetYaxis()->SetLabelFont(132);
	mg_1_IC->GetXaxis()->SetTitleOffset(0.92);
	mg_1_IC->GetYaxis()->SetTitleOffset(1.00);
	mg_1_IC->Draw("AP");
	
	auto *leg_1_IC = new TLegend(.15, .1, .3, .28);
	leg_1_IC->SetBorderSize(0);
	leg_1_IC->AddEntry(g_10_IC, "InvCoax - #epsilon_{e^{-}}", "p");
	leg_1_IC->AddEntry(g_12_IC, "InvCoax - #epsilon_{e_{tot}}", "p");
	leg_1_IC->Draw();
	
	
	return 0;
}
//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================
int phase_fep() {

	char name1[200], name2[200];
	char name5[200], name6[200];
	char name10[200];
	// coax
	sprintf(name1, "FepEff_phaseII_enrCoax.txt"); // Phase II
	sprintf(name2, "FepEff_phaseIIp_enrCoax.txt"); // Phase II+
	// BEGe
	sprintf(name5, "FepEff_phaseII_enrBEGe.txt"); // Phase II
	sprintf(name6, "FepEff_phaseIIp_enrBEGe.txt"); // Phase II+
	// IC
	sprintf(name10, "FepEff_phaseIIp_invCoax.txt"); // Phase II+

	//=====================================================================================================
	//=====================================================================================================
	//-------------------------------------------------------------------------------------------- Phase II
	TCanvas *c0 = new TCanvas("c0", "c0", 1500, 900);
	TMultiGraph *mg0 = new TMultiGraph();
	
	// COAX
	TGraph *g_1_coax = new TGraph(name1, "%lg %lg %*lg %*lg %*lg");
	g_1_coax->SetLineColor(kRed);
	g_1_coax->SetMarkerColor(kRed);
	g_1_coax->SetMarkerStyle(20);
	g_1_coax->SetMarkerSize(1.3);
	mg0->Add(g_1_coax);
	// BEGe 
	TGraph *g_5_BEGe = new TGraph(name5, "%lg %lg %*lg %*lg %*lg");
	g_5_BEGe->SetLineColor(kBlue);
	g_5_BEGe->SetMarkerColor(kBlue);
	g_5_BEGe->SetMarkerStyle(20);
	g_5_BEGe->SetMarkerSize(1.3);
	mg0->Add(g_5_BEGe);
	
	mg0->SetTitle("Phase II; Energy [keV]; Efficiency");
	mg0->GetXaxis()->SetTitleSize(0.05);
	mg0->GetXaxis()->SetLabelSize(0.05);
	mg0->GetXaxis()->CenterTitle();
	mg0->GetYaxis()->SetTitleSize(0.05);
	mg0->GetYaxis()->SetLabelSize(0.05);
	mg0->GetYaxis()->CenterTitle();
	mg0->GetYaxis()->CenterTitle();
	mg0->GetXaxis()->SetTitleFont(132);
	mg0->GetYaxis()->SetTitleFont(132);
	mg0->GetXaxis()->SetLabelFont(132);
	mg0->GetYaxis()->SetLabelFont(132);
	mg0->GetXaxis()->SetTitleOffset(0.92);
	mg0->GetYaxis()->SetTitleOffset(1.00);
	mg0->Draw("AP");
	mg0->GetXaxis()->SetRangeUser(0, 1060);
	mg0->GetYaxis()->SetRangeUser(0.7, 0.9);
	
	auto *leg_0_coax = new TLegend(.6, .8, .88, .88);
	leg_0_coax->SetBorderSize(0);
	leg_0_coax->AddEntry(g_1_coax, "EnrCoax - Phase II", "p");
	leg_0_coax->AddEntry(g_5_BEGe, "EnrBEGe - Phase II", "p");
	leg_0_coax->Draw();
	
	
	//=====================================================================================================
	//=====================================================================================================
	// ------------------------------------------------------------------------------------------ Phase II+
	TCanvas *c1 = new TCanvas("c1", "c1", 1500, 900);
	TMultiGraph *mg1 = new TMultiGraph();
	
	// COAX
	TGraph *g_2_coax = new TGraph(name2, "%lg %lg %*lg %*lg %*lg"); 
	g_2_coax->SetLineColor(kRed);
	g_2_coax->SetMarkerColor(kRed);
	g_2_coax->SetMarkerStyle(20);
	g_2_coax->SetMarkerSize(1.3);
	mg1->Add(g_2_coax);
	// BEGe
	TGraph *g_6_BEGe = new TGraph(name6, "%lg %lg %*lg %*lg %*lg");
	g_6_BEGe->SetLineColor(kBlue);
	g_6_BEGe->SetMarkerColor(kBlue);
	g_6_BEGe->SetMarkerStyle(20);
	g_6_BEGe->SetMarkerSize(1.3);
	mg1->Add(g_6_BEGe);
	// IC
	TGraph *g_10_IC = new TGraph(name10, "%lg %lg %*lg %*lg %*lg");
	g_10_IC->SetLineColor(kGreen+2);
	g_10_IC->SetMarkerColor(kGreen+2);
	g_10_IC->SetMarkerStyle(20);
	g_10_IC->SetMarkerSize(1.3);
	mg1->Add(g_10_IC);
	
	mg1->SetTitle("Phase II+; Energy [keV]; Efficiency");
	mg1->GetXaxis()->SetTitleSize(0.05);
	mg1->GetXaxis()->SetLabelSize(0.05);
	mg1->GetXaxis()->CenterTitle();
	mg1->GetYaxis()->SetTitleSize(0.05);
	mg1->GetYaxis()->SetLabelSize(0.05);
	mg1->GetYaxis()->CenterTitle();
	mg1->GetYaxis()->CenterTitle();
	mg1->GetXaxis()->SetTitleFont(132);
	mg1->GetYaxis()->SetTitleFont(132);
	mg1->GetXaxis()->SetLabelFont(132);
	mg1->GetYaxis()->SetLabelFont(132);
	mg1->GetXaxis()->SetTitleOffset(0.92);
	mg1->GetYaxis()->SetTitleOffset(1.00);
	mg1->Draw("AP");
	mg1->GetXaxis()->SetRangeUser(0, 1060);
	mg1->GetYaxis()->SetRangeUser(0.6, 0.9);
	
	auto *leg_1_coax = new TLegend(.6, .76, .88, .88);
	leg_1_coax->SetBorderSize(0);
	leg_1_coax->AddEntry(g_2_coax, "EnrCoax - Phase II+", "p");
	leg_1_coax->AddEntry(g_6_BEGe, "EnrBEGe - Phase II+", "p");
	leg_1_coax->AddEntry(g_10_IC, "IC - Phase II+", "p");
	leg_1_coax->Draw();
	
	return 0;
}
