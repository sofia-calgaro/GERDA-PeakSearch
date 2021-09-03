int DrawPlot() {

	TFile *f1 = new TFile("PSD_20210717_IC.root");
	TH1D *h1 = (TH1D*)f1->Get("LAr");
	TH1D *h2 = (TH1D*)f1->Get("LAr_PSD");
	
	TCanvas *c = new TCanvas("c","c",1700,1000);
	c->SetLogy();
	h1->SetLineColor(kGreen+2);
	h1->SetStats(false);
	h1->GetXaxis()->SetTitle("Energy [keV]");
	h1->GetYaxis()->SetTitle("Events / 1 keV");
	h1->GetXaxis()->SetRangeUser(0, 5200);
	h1->GetXaxis()->SetTitleSize(0.045);
	h1->GetXaxis()->SetLabelSize(0.045);
	h1->GetYaxis()->SetTitleSize(0.045);
	h1->GetYaxis()->SetLabelSize(0.045);
	h2->SetLineColor(kBlack);
	h2->GetXaxis()->SetRangeUser(0, 5200);
	h2->SetStats(false);
	h2->GetXaxis()->SetTitle("Energy [keV]");
	h2->GetYaxis()->SetTitle("Events / 1 keV");
	h2->GetXaxis()->SetTitleSize(0.045);
	h2->GetXaxis()->SetLabelSize(0.045);
	h2->GetYaxis()->SetTitleSize(0.045);
	h2->GetYaxis()->SetLabelSize(0.045);
	h2->Draw();
	h1->Draw("same");
	
	auto *legend = new TLegend(.65, .75, .88, .88);
	legend->AddEntry(h1, "EnrBEGe", "l");
	legend->AddEntry(h2, "EnrBEGe - PSD only", "l");
	legend->Draw();

	return 0;
}


