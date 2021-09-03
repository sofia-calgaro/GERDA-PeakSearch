int drawplot_gstr() {

	TFile *f1 = new TFile("20210528/IC_20210528_coax.root");
	TH1D *h1 = (TH1D*)f1->Get("histo_energy_LAr");
	TH1D *h1_new = new TH1D ("h1_new","",5200,0,5200);
	
	TFile *f2 = new TFile("20210528/IC_20210528_BEGe.root");
	TH1D *h2 = (TH1D*)f2->Get("histo_energy_LAr");
	TH1D *h2_new = new TH1D ("h2_new","",5200,0,5200);
	
	TCanvas *c = new TCanvas();
	c->SetLogy();
	h1->SetLineColor(kBlue);
	h1->SetStats(false);
	h1->SetLineWidth(2);
	h1->GetXaxis()->SetTitle("Energy [keV]");
	h1->GetYaxis()->SetTitle("Events / 1 keV");
	h1->GetXaxis()->SetRangeUser(0, 5200);
	h2->SetLineColor(kMagenta);
	h2->GetXaxis()->SetRangeUser(0, 5200);
	h2->SetLineWidth(2);
	h2->SetStats(false);
	h2->GetXaxis()->SetTitle("Energy [keV]");
	h2->GetYaxis()->SetTitle("Events / 1 keV");
	h2->Draw();
	h1->Draw("same");
	/*
	for ( int i=0; i<195; i++) {
		h1_new->SetBinContent(i+1, (h1->GetBinContent(i+1))/6.9); // coax
	}
	
	for ( int i=195; i<5200; i++) {
		h1_new->SetBinContent(i+1, (h1->GetBinContent(i+1))/28.1); // coax
	}
	
	for ( int i=0; i<165; i++) {
		h2_new->SetBinContent(i+1, (h2->GetBinContent(i+1))/7.7); // BEGe
	}
	
	for ( int i=165; i<5200; i++) {	
		h2_new->SetBinContent(i+1, (h2->GetBinContent(i+1))/30.8); // BEGe
	}

	// Normalized histograms
	TCanvas *c1 = new TCanvas();
	c1->SetLogy();
	h1_new->SetLineColor(kBlue-3);
	h1_new->SetStats(false);
	h1_new->SetLineWidth(2);
	h1_new->GetXaxis()->SetTitle("Energy [keV]");
	h1_new->GetYaxis()->SetTitle("Events / (1 keV*kg*yr)");
	h1_new->GetXaxis()->SetRangeUser(0, 5200);
	h2_new->SetLineColor(kPink+4);
	h2_new->GetXaxis()->SetRangeUser(0, 5200);
	h2_new->SetLineWidth(2);
	h2_new->SetStats(false);
	h2_new->GetXaxis()->SetTitle("Energy [keV]");
	h2_new->GetYaxis()->SetTitle("Events / (1 keV*kg*yr)");
	
	h2_new->Draw();
	h1_new->Draw("same");*/
	/*
	fstream write_1, write_2;
        write_1.open("20210524_norm/bin_content_coax_norm.txt", ios::out);
	write_2.open("20210524_norm/bin_content_BEGe_norm.txt", ios::out);
	
	vector<int> energy_LAr_1, energy_LAr_2;
	for (int i=0; i< h1_new->GetNbinsX(); i++) {
		energy_LAr_1.push_back(h1_new->GetBinContent(i+1));
		write_1 << energy_LAr_1.at(i) << endl;
	}
	for (int i=0; i< h2_new->GetNbinsX(); i++) {
		energy_LAr_2.push_back(h2_new->GetBinContent(i+1));
		write_2 << energy_LAr_2.at(i) << endl;
	}

	write_1.close();
	write_2.close();
	
	TFile *f_h1 = new TFile("20210524_norm/h_coax_norm.root","RECREATE");
	TFile *f_h2 = new TFile("20210524_norm/h_BEGe_norm.root","RECREATE");
	f_h1->WriteTObject(h1_new);
	f_h2->WriteTObject(h2_new);
	f_h1->Close();
	f_h2->Close();
*/
	return 0;
}


