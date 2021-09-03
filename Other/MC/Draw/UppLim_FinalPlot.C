using namespace std;

Int_t NumberOfRows(char *filename) {
  
        Int_t NumOfRows = 0;
        std::string line;
        std::ifstream file(filename);

        while (std::getline(file,line)) {
                ++NumOfRows;
        }

        return NumOfRows;
}


int UppLim_FinalPlot() {

	int det = 1;
	
	int ans0;
	cout << " Normalized (0) or not (1)? ";
	cin >> ans0;
	
	int peaks;
	cout << " How many peaks? ";
	cin >> peaks;
	
	int real = 0;
	
	ifstream input;
	char nameinput[200];
	if ( peaks==0 ) {
		if ( det==0 ) sprintf(nameinput, "MC_coax_0peaks.txt");
		if ( det==1 ) sprintf(nameinput, "MC_BEGe_0peaks.txt");
		if ( det==2 ) sprintf(nameinput, "MC_IC_0peaks.txt");
	}
	if ( peaks==1 ) {
		if ( det==0 ) sprintf(nameinput, "MC_coax_1peak.txt");
		if ( det==1 ) sprintf(nameinput, "MC_BEGe_1peak.txt");
		if ( det==2 ) sprintf(nameinput, "MC_IC_1peak.txt");
	}
	if ( peaks==2 ) {
		if ( det==0 ) sprintf(nameinput, "MC_coax_2peaks.txt");
		if ( det==1 ) sprintf(nameinput, "MC_BEGe_2peaks.txt");
		if ( det==2 ) sprintf(nameinput, "MC_IC_2peaks.txt");
	}
	input.open(nameinput);
	
	Int_t rows = NumberOfRows(nameinput);
	double data[23][8] = {0};
	for ( int i=0; i<rows; i++ ) {
		for ( int j=0; j<8; j++ ) {
			input >> data[i][j];
		}
	}
	input.close();

	TCanvas *c1 = new TCanvas("c1", "c1", 1700, 1000);
	
	// normalization
	double exp_BEL_PSD=0, exp_AB_PSD=0;
	if ( ans0==0 ) {
		if ( det==0 ) {
			exp_BEL_PSD = 20.6676;
			exp_AB_PSD = 41.8177;
		}
		if ( det==1 ) {
			exp_BEL_PSD = 30.5489;
			exp_AB_PSD = 54.9284;
		}
		if ( det==2 ) {
			exp_BEL_PSD = 8.77469;
			exp_AB_PSD = 8.77469;
		}
	
	}
	else {}
	
	char nameinput2[200];
	if ( peaks==0 ) {
		if ( det==0 ) sprintf(nameinput2, "MC_coax_0peaks.txt");
		if ( det==1 ) sprintf(nameinput2, "MC_BEGe_0peaks.txt");
		if ( det==2 ) sprintf(nameinput2, "MC_IC_0peaks.txt");
	}
	if ( peaks==1 ) {
		if ( det==0 ) sprintf(nameinput2, "MC_coax_1peak.txt");
		if ( det==1 ) sprintf(nameinput2, "MC_BEGe_1peak.txt");
		if ( det==2 ) sprintf(nameinput2, "MC_IC_1peak.txt");
	}
	if ( peaks==2 ) {
		if ( det==0 ) sprintf(nameinput2, "MC_coax_2peaks.txt");
		if ( det==1 ) sprintf(nameinput2, "MC_BEGe_2peaks.txt");
		if ( det==2 ) sprintf(nameinput2, "MC_IC_2peaks.txt");
	}
	// 1 sigma graph
	Int_t n = NumberOfRows(nameinput2);
	Double_t x[n], y[n], ymin_1[n], ymax_1[n], ymin_2[n], ymax_2[n], ymin_3[n], ymax_3[n];
	int i;
	for ( i=0; i<n; i++ ) {
		x[i] = data[i][0];
		// normalization
		if ( ans0==0 ) {
			// only PSD
			if ( data[i][0]<195 ) {
				ymax_1[i] = data[i][5]/exp_BEL_PSD;
				ymin_1[i] = data[i][3]/exp_BEL_PSD;
				ymax_2[i] = data[i][6]/exp_BEL_PSD;
				ymin_2[i] = data[i][2]/exp_BEL_PSD;
				ymax_3[i] = data[i][7]/exp_BEL_PSD;
				ymin_3[i] = data[i][1]/exp_BEL_PSD;
				y[i] = data[i][4]/exp_BEL_PSD;
			}
			else {
				ymax_1[i] = data[i][5]/exp_AB_PSD;
				ymin_1[i] = data[i][3]/exp_AB_PSD;
				ymax_2[i] = data[i][6]/exp_AB_PSD;
				ymin_2[i] = data[i][2]/exp_AB_PSD;
				ymax_3[i] = data[i][7]/exp_AB_PSD;
				ymin_3[i] = data[i][1]/exp_AB_PSD;
				y[i] = data[i][4]/exp_AB_PSD;
			}
		}
		// not normalized
		if ( ans0==1 ) {
			ymax_1[i] = data[i][5];
			ymin_1[i] = data[i][3];
			ymax_2[i] = data[i][6];
			ymin_2[i] = data[i][2];
			ymax_3[i] = data[i][7];
			ymin_3[i] = data[i][1];
			y[i] = data[i][4];
		}
	}
	c1->DrawFrame(x[0]-1, 0, x[n-1]+1, 200);
	
	TMultiGraph *mg = new TMultiGraph();
	mg->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	mg->GetXaxis()->CenterTitle();
	mg->GetYaxis()->CenterTitle();
	if ( ans0==0 ) mg->GetYaxis()->SetTitle("S [cts/kg*yr]");
	if ( ans0==1 ) mg->GetYaxis()->SetTitle("S [cts]");
	mg->GetXaxis()->SetTitleSize(0.04);
	mg->GetXaxis()->SetLabelSize(0.04);
	mg->GetYaxis()->SetTitleSize(0.04);
	mg->GetYaxis()->SetLabelSize(0.04);
	mg->GetXaxis()->SetTitleFont(132);
	mg->GetYaxis()->SetTitleFont(132);
	mg->GetXaxis()->SetLabelFont(132);
	mg->GetYaxis()->SetLabelFont(132);
	
	TGraph *grmin_1 = new TGraph(n, x, ymin_1);
	TGraph *grmax_1 = new TGraph(n, x, ymax_1);
	TGraph *grshade_1 = new TGraph(2*n);
	TGraph *grmin_2 = new TGraph(n, x, ymin_2);
	TGraph *grmax_2 = new TGraph(n, x, ymax_2);
	TGraph *grshade_2 = new TGraph(2*n);
	TGraph *grmin_3 = new TGraph(n, x, ymin_3);
	TGraph *grmax_3 = new TGraph(n, x, ymax_3);
	TGraph *grshade_3 = new TGraph(2*n);
	TGraph *gr = new TGraph(n, x, y);
	
	Double_t y_real[23];
	// 0 peaks
	if ( peaks==0 ) {
		// normalized
		if ( ans0==0 ) {
			y_real[0] = 36.0149145988176/exp_AB_PSD; // 770
			y_real[1] = 48.1825845392363/exp_AB_PSD;
			y_real[2] = 58.9539780676457/exp_AB_PSD; // 772
			y_real[3] = 47.6522460550341/exp_AB_PSD;
			y_real[4] = 30.1075524626117/exp_AB_PSD; // 774
			y_real[5] = 28.5539321324609/exp_AB_PSD;
			y_real[6] = 26.25667045982/exp_AB_PSD; // 776
			y_real[7] = 21.0250975265604/exp_AB_PSD;
			y_real[8] = 24.5926743688489/exp_AB_PSD; // 778
			y_real[9] = 47.4198642171371/exp_AB_PSD;
			y_real[10] = 72.6127167630058/exp_AB_PSD; // 780
			y_real[11] = 65.7371803101253/exp_AB_PSD; 
			y_real[12] = 53.2752497439133/exp_AB_PSD; // 782
			y_real[13] = 43.2419310559764/exp_AB_PSD; 
			y_real[14] = 35.4717338577516/exp_AB_PSD; // 784
			y_real[15] = 37.5247483425741/exp_AB_PSD; 
			y_real[16] = 63.4333681267747/exp_AB_PSD; // 786
			y_real[17] = 65.9176795175785/exp_AB_PSD; 
			y_real[18] = 49.062540740851/exp_AB_PSD; // 788
			y_real[19] = 45.192272411588/exp_AB_PSD; 
			y_real[20] = 34.0979255522528/exp_AB_PSD; // 790
			y_real[21] = 19.4081165998934/exp_AB_PSD; 
			y_real[22] = 19.0515675302526/exp_AB_PSD; // 792
		}
		// not normalized
		if ( ans0==1 ) {
			y_real[0] = 36.0149145988176; // 770
			y_real[1] = 48.1825845392363;
			y_real[2] = 58.9539780676457; // 772
			y_real[3] = 47.6522460550341;
			y_real[4] = 30.1075524626117; // 774
			y_real[5] = 28.5539321324609;
			y_real[6] = 26.25667045982; // 776
			y_real[7] = 21.0250975265604;
			y_real[8] = 24.5926743688489; // 778
			y_real[9] = 47.4198642171371;
			y_real[10] = 72.6127167630058; // 780
			y_real[11] = 65.7371803101253; 
			y_real[12] = 53.2752497439133; // 782
			y_real[13] = 43.2419310559764; 
			y_real[14] = 35.4717338577516; // 784
			y_real[15] = 37.5247483425741; 
			y_real[16] = 63.4333681267747; // 786
			y_real[17] = 65.9176795175785; 
			y_real[18] = 49.062540740851; // 788
			y_real[19] = 45.192272411588; 
			y_real[20] = 34.0979255522528; // 790
			y_real[21] = 19.4081165998934; 
			y_real[22] = 19.0515675302526; // 792
		}
	}
	// 1 peaks
	if ( peaks==1 ) {
		// normalized
		if ( ans0==0 ) {
			y_real[0] = 62.8133281912841/exp_AB_PSD; 
			y_real[1] = 63.7283671536559/exp_AB_PSD; // 290
			y_real[2] = 51.9078332975552/exp_AB_PSD;
			y_real[3] = 46.4885163465253/exp_AB_PSD; // 292
			y_real[4] = 97.3621392973636/exp_AB_PSD;
			y_real[5] = 179.227879416644/exp_AB_PSD; // 294
			y_real[6] = 261.842037652561/exp_AB_PSD;
			y_real[7] = 65.9893150003617/exp_AB_PSD; // 296
			y_real[8] = 46.8812528842142/exp_AB_PSD;
			y_real[9] = 41.4838163777306/exp_AB_PSD; // 298
			y_real[10] = 41.6853906163804/exp_AB_PSD;
			y_real[11] = 51.8203673966889/exp_AB_PSD; // 300
			y_real[12] = 72.251840597062/exp_AB_PSD;
			y_real[13] = 65.4102289182631/exp_AB_PSD; // 302
		}
		// not normalized
		if ( ans0==1 ) {
			y_real[0] = 62.8133281912841; 
			y_real[1] = 63.7283671536559; // 290
			y_real[2] = 51.9078332975552;
			y_real[3] = 46.4885163465253; // 292
			y_real[4] = 97.3621392973636;
			y_real[5] = 179.227879416644; // 294
			y_real[6] = 261.842037652561;
			y_real[7] = 65.9893150003617; // 296
			y_real[8] = 46.8812528842142;
			y_real[9] = 41.4838163777306; // 298
			y_real[10] = 41.6853906163804;
			y_real[11] = 51.8203673966889; // 300
			y_real[12] = 72.251840597062;
			y_real[13] = 65.4102289182631; // 302
		}
	}
	// 2 peaks
	if ( peaks==2 ) {
		// normalized
		if ( ans0==0 ) {
			y_real[0] = 31.898874115778/exp_AB_PSD;
			y_real[1] = 43.4690289505428/exp_AB_PSD;
			y_real[2] = 48.8649468622157/exp_AB_PSD;
			y_real[3] = 53.021828160988/exp_AB_PSD;
			y_real[4] = 45.0812800737054/exp_AB_PSD;
			y_real[5] = 43.5353520885379/exp_AB_PSD;
			y_real[6] = 27.4650662428925/exp_AB_PSD;
			y_real[7] = 24.2695828253115/exp_AB_PSD;
			y_real[8] = 22.7497368042645/exp_AB_PSD;
			y_real[9] = 26.7995840364203/exp_AB_PSD;
			y_real[10] = 55.9028971333847/exp_AB_PSD;
			y_real[11] = 126.18445510101/exp_AB_PSD;
			y_real[12] = 145.543230313436/exp_AB_PSD;
			y_real[13] = 24.0918941633133/exp_AB_PSD;
			y_real[14] = 22.3274940733625/exp_AB_PSD;
			y_real[15] = 36.7413358750907/exp_AB_PSD;
			y_real[16] = 46.4439710628826/exp_AB_PSD;
			y_real[17] = 57.6369882614673/exp_AB_PSD;
			y_real[18] = 70.0458780984173/exp_AB_PSD;
			y_real[19] = 54.2011763425728/exp_AB_PSD;
			y_real[20] = 33.9600108787396/exp_AB_PSD;
			y_real[21] = 28.9237377890242/exp_AB_PSD;
		}
		// not normalized
		if ( ans0==1 ) {
			y_real[0] = 31.898874115778;
			y_real[1] = 43.4690289505428;
			y_real[2] = 48.8649468622157;
			y_real[3] = 53.021828160988;
			y_real[4] = 45.0812800737054;
			y_real[5] = 43.5353520885379;
			y_real[6] = 27.4650662428925;
			y_real[7] = 24.2695828253115;
			y_real[8] = 22.7497368042645;
			y_real[9] = 26.7995840364203;
			y_real[10] = 55.9028971333847;
			y_real[11] = 126.18445510101;
			y_real[12] = 145.543230313436;
			y_real[13] = 24.0918941633133;
			y_real[14] = 22.3274940733625;
			y_real[15] = 36.7413358750907;
			y_real[16] = 46.4439710628826;
			y_real[17] = 57.6369882614673;
			y_real[18] = 70.0458780984173;
			y_real[19] = 54.2011763425728;
			y_real[20] = 33.9600108787396;
			y_real[21] = 28.9237377890242;
		}
	}
	TGraph *gr_real = new TGraph(n, x, y_real);
	
	grmin_1->SetLineWidth(0);
	grmax_1->SetLineWidth(0);
	grmin_2->SetLineWidth(0);
	grmax_2->SetLineWidth(0);
	grmin_3->SetLineWidth(0);
	grmax_3->SetLineWidth(0);
	grshade_1->SetLineWidth(0);
	grshade_2->SetLineWidth(0);
	grshade_3->SetLineWidth(0);
	
	for ( i=0; i<n; i++ ) {
		grshade_1->SetPoint(i, x[i], ymax_1[i]);
		grshade_1->SetPoint(n+i, x[n-i-1], ymin_1[n-i-1]);
		grshade_2->SetPoint(i, x[i], ymax_2[i]);
		grshade_2->SetPoint(n+i, x[n-i-1], ymin_2[n-i-1]);
		grshade_3->SetPoint(i, x[i], ymax_3[i]);
		grshade_3->SetPoint(n+i, x[n-i-1], ymin_3[n-i-1]);
	}
	
	//grshade_1->SetFillStyle(3013);
	if ( det==0 ) {
		grshade_1->SetFillColor(kRed-10);
		grmin_1->SetLineColor(kRed-10);
		grmax_1->SetLineColor(kRed-10);
		grshade_2->SetFillColor(kRed-9);
		grmin_2->SetLineColor(kRed-9);
		grmax_2->SetLineColor(kRed-9);
		grshade_3->SetFillColor(kRed-7);
		grmin_3->SetLineColor(kRed-7);
		grmax_3->SetLineColor(kRed-7);
	}
	if ( det==1 ) {
		grshade_1->SetFillColor(kBlue-10);
		grmin_1->SetLineColor(kBlue-10);
		grmax_1->SetLineColor(kBlue-10);
		grshade_2->SetFillColor(kBlue-9);
		grmin_2->SetLineColor(kBlue-9);
		grmax_2->SetLineColor(kBlue-9);
		grshade_3->SetFillColor(kBlue-7);
		grmin_3->SetLineColor(kBlue-7);
		grmax_3->SetLineColor(kBlue-7);
	}
	if ( det==2 ) {
		grshade_1->SetFillColor(kGreen-10);
		grmin_1->SetLineColor(kGreen-10);
		grmax_1->SetLineColor(kGreen-10);
		grshade_2->SetFillColor(kGreen-9);
		grmin_2->SetLineColor(kGreen-9);
		grmax_2->SetLineColor(kGreen-9);
		grshade_3->SetFillColor(kGreen-7);
		grmin_3->SetLineColor(kGreen-7);
		grmax_3->SetLineColor(kGreen-7);
	}
	
	
	// median graph
	gr->SetLineColor(kBlack);
	gr->SetLineWidth(2);
	gr->SetLineStyle(7);
	if ( real==0 ) {
		gr_real->SetLineColor(kRed);
		gr_real->SetLineWidth(2);
		gr_real->SetLineStyle(7);
	}
	
	// draw
	mg->Add(grmin_1, "l");
	mg->Add(grmin_1, "l");
	mg->Add(grmin_2, "l");
	mg->Add(grmin_2, "l");
	mg->Add(grmin_3, "l");
	mg->Add(grmin_3, "l");
	mg->Add(grshade_3, "f");
	mg->Add(grshade_2, "f");
	mg->Add(grshade_1, "f");
	mg->Add(gr, "l");
	if ( real==0 ) mg->Add(gr_real, "l");
	mg->Draw();
	
	// legend
	auto *legend1 = new TLegend(.65, .65, .88, .88);
	char title2[200];
	legend1->AddEntry(grshade_1, "1 \\sigma", "f");
	legend1->AddEntry(grshade_2, "2 \\sigma", "f");
	legend1->AddEntry(grshade_3, "3 \\sigma", "f");
	legend1->AddEntry(gr, "Median sensitivity", "l");
	if ( real==0 ) legend1->AddEntry(gr_real, "Count Rate Limit", "l");
	legend1->SetBorderSize(0);
	//legend1->Draw();

	return 0;
}

