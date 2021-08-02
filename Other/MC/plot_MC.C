using namespace std;

Int_t NumberOfRows(char *filename) {
  
        Int_t NumOfRows = 0;
        std::string line;
        std::ifstream file(filename);

        while (std::getline(file,line)) {
                ++NumOfRows;
        }

        //NumOfRows = NumOfRows -1 ; // if 1st line are comments

        return NumOfRows;
}

int plot_MC(int y_max, int delta) {

	int det;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> det;

	int E0;
	cout << " Choose energy: ";
	cin >> E0;

	char namefile[200];
	if ( det==0 ) sprintf(namefile, "MC_output/coax/MC%i_U90.txt", E0);
	if ( det==1 ) sprintf(namefile, "MC_output/BEGe/MC%i_U90.txt", E0);
	if ( det==2 ) sprintf(namefile, "MC_output/IC/MC%i_U90.txt", E0);
	ifstream file(namefile);

	Int_t rows = NumberOfRows(namefile);
	double data[rows][11];
	for ( int i=0; i<rows; i++) {
		for ( int j=0; j<11; j++ ) {
			file >> data[i][j];
		}
	}
	file.close();
		
	int min = data[0][1];
	for ( int i=1; i<rows; i++) {
		if ( data[i][1] < min ) { min = data[i][1]; }
	} 
	int max = data[0][1];
	for ( int i=1; i<rows; i++) {
		if ( data[i][1] > max ) { max = data[i][1]; }
	}
	
	int bins = (max - min)*delta;
	TH1D *histo = new TH1D("histo", "", bins, min, max);
	for ( int i=0; i<rows; i++ ) { histo->Fill(data[i][1]); }
	
	double p[8] = {0, 0.015, 0.0225, 0.1585, 0.5, 0.8415, 0.9775, 0.9985};
	double q[8] = {0};
	histo->GetQuantiles(8, q, p);
	double L99 = q[1];
	double L95 = q[2];
	double L68 = q[3];
	double median = q[4];
	double U68 = q[5];
	double U95 = q[6];
	double U99 = q[7];
	
	/*cout << " L99 = " << L99 << endl;
	cout << " L95 = " << L95 << endl;
	cout << " L68 = " << L68 << endl;
	cout << " median = " << median << endl;
	cout << " U68 = " << U68 << endl;
	cout << " U95 = " << U95 << endl;
	cout << " U99 = " << U99 << endl;*/

	TH1D *h_1sigma = new TH1D("h_1sigma", "", bins, min, max);
	TH1D *h_2sigma = new TH1D("h_2sigma", "", bins, min, max);
	TH1D *h_3sigma = new TH1D("h_3sigma", "", bins, min, max);
	TH1D *h_4sigma = new TH1D("h_4sigma", "", bins, min, max);
	for ( int i=0; i<rows; i++ ) {
		if ( data[i][1]<=L99 || data[i][1]>=U99 ) { h_4sigma->Fill(data[i][1]); }
		if ( (data[i][1]>L99 && data[i][1]<=L95) || (data[i][1]>=U95 && data[i][1]<U99) ) { h_3sigma->Fill(data[i][1]); }
		if ( (data[i][1]>L95 && data[i][1]<=L68) || (data[i][1]>=U68 && data[i][1]<U95) ) { h_2sigma->Fill(data[i][1]); }
		if ( data[i][1]>L68 && data[i][1]<U68 ) { h_1sigma->Fill(data[i][1]); }
	}
	
	if ( det==0 ) {
		h_1sigma->SetFillColor(kRed-10);
		h_2sigma->SetFillColor(kRed-9);
		h_3sigma->SetFillColor(kRed-7);
		h_4sigma->SetFillColor(kRed-4);
	}
	if ( det==1 ) {
		h_1sigma->SetFillColor(kBlue-10);
		h_2sigma->SetFillColor(kBlue-9);
		h_3sigma->SetFillColor(kBlue-7);
		h_4sigma->SetFillColor(kBlue-4);
	}
	if ( det==2 ) {
		h_1sigma->SetFillColor(kGreen-10);
		h_2sigma->SetFillColor(kGreen-9);
		h_3sigma->SetFillColor(kGreen-7);
		h_4sigma->SetFillColor(kGreen-4);
	}
	
	TCanvas *c = new TCanvas();
	h_1sigma->GetXaxis()->SetRange(min-5, max+5);
	h_1sigma->GetXaxis()->SetTitle("Upper 90\% limits for rate [cts]");
	h_1sigma->GetYaxis()->SetTitle("M.C. simulations");
	h_1sigma->GetXaxis()->SetTitleSize(0.045);
	h_1sigma->GetXaxis()->SetLabelSize(0.045);
	h_1sigma->GetYaxis()->SetTitleSize(0.045);
	h_1sigma->GetYaxis()->SetLabelSize(0.045);
	char title1[200];
	if ( det==0 ) sprintf(title1, "EnrCoax M.C. study (%i keV)", E0); 
	if ( det==1 ) sprintf(title1, "EnrBEGe M.C. study (%i keV)", E0); 
	if ( det==2 ) sprintf(title1, "IC M.C. study, (%i keV)", E0); 
	h_1sigma->SetTitle(title1);
	h_1sigma->SetStats(kFALSE);
	h_2sigma->SetStats(kFALSE);
	h_3sigma->SetStats(kFALSE);
	h_4sigma->SetStats(kFALSE);
	h_1sigma->SetLineWidth(0);
	h_2sigma->SetLineWidth(0);
	h_3sigma->SetLineWidth(0);
	h_4sigma->SetLineWidth(0);
	h_1sigma->Draw("B,bar2");
	h_2sigma->Draw("B,bar2,same");
	h_3sigma->Draw("B,bar2,same");
	//h_4sigma->Draw("B,bar2,same");
	
	TLine *line1 = new TLine(median, 0, median, y_max);
	line1->SetLineColor(kRed);
	line1->SetLineStyle(2);
	line1->SetLineWidth(4);
	line1->Draw();
	
	auto *legend1 = new TLegend(.75, .65, .88, .88);
	char title2[200];
	legend1->AddEntry(h_1sigma, "1 \\sigma", "f");
	legend1->AddEntry(h_2sigma, "2 \\sigma", "f");
	legend1->AddEntry(h_3sigma, "3 \\sigma", "f");
	//legend1->AddEntry(h_4sigma, "4 \\sigma", "f");
	legend1->AddEntry(line1, "Median", "l");
	legend1->SetBorderSize(0);
	legend1->Draw();
	c->RedrawAxis(); // to draw tick markers over histograms
	
	char nameoutput[200];
	if ( det==0 ) sprintf(nameoutput, "Draw/MC_coax.txt");
	if ( det==1 ) sprintf(nameoutput, "Draw/MC_BEGe.txt");
	if ( det==2 ) sprintf(nameoutput, "Draw/MC_IC.txt");
	
	fstream output;
	if ( !output ) {
		output.open(nameoutput, ios::out);
		output << E0 << "\t\t" << L99 << "\t\t" << L95 << "\t\t" << L68 << "\t\t" << median << "\t\t" << U68 << "\t\t" << U95 << "\t\t" << U99 << endl;
	}
	else {
		output.open(nameoutput, ios_base::app);
		output << E0 << "\t\t" << L99 << "\t\t" << L95 << "\t\t" << L68 << "\t\t" << median << "\t\t" << U68 << "\t\t" << U95 << "\t\t" << U99 << endl;
	}
	
	output.close();
	
	return 0;
}

