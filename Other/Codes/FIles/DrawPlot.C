int DrawPlot() {

	TFile *f1 = new TFile("53_114_PSD/IC_new/20210726_IC.root");
	TH1D *h1 = (TH1D*)f1->Get("LAr");
	TFile *f2 = new TFile("53_114_PSD/BEGe_new/20210726_BEGe.root");
	TH1D *h2 = (TH1D*)f2->Get("LAr");
	TFile *f3 = new TFile("53_114_PSD/coax_new/20210726_coax.root");
	TH1D *h3 = (TH1D*)f3->Get("LAr");
	
	const int y_max= 4e4;
	
	TCanvas *c = new TCanvas("c","c",1700,1000);
	c->SetLogy();
	h1->SetLineColor(kGreen+1);
	h1->SetStats(false);
	h1->GetXaxis()->SetTitle("Energy [keV]");
	h1->GetYaxis()->SetTitle("Events / 1 keV");
	h1->GetXaxis()->SetRangeUser(0, 1000);
	h1->GetXaxis()->SetTitleSize(0.045);
	h1->GetXaxis()->SetLabelSize(0.045);
	h1->GetYaxis()->SetTitleSize(0.045);
	h1->GetYaxis()->SetLabelSize(0.045);
	h2->SetLineColor(kBlue);
	h2->GetXaxis()->SetRangeUser(0, 1000);
	h2->SetStats(false);
	h2->GetXaxis()->SetTitle("Energy [keV]");
	h2->GetYaxis()->SetTitle("Events / 1 keV");
	h2->GetXaxis()->SetTitleSize(0.045);
	h2->GetXaxis()->SetLabelSize(0.045);
	h2->GetYaxis()->SetTitleSize(0.045);
	h2->GetYaxis()->SetLabelSize(0.045);
	h3->SetLineColor(kRed+1);
	h3->GetXaxis()->SetRangeUser(0, 1000);
	h3->SetStats(false);
	h3->GetXaxis()->SetTitle("Energy [keV]");
	h3->GetYaxis()->SetTitle("Events / 1 keV");
	h3->GetXaxis()->CenterTitle();
	h3->GetYaxis()->CenterTitle();
	h3->GetXaxis()->SetTitleSize(0.045);
	h3->GetXaxis()->SetLabelSize(0.045);
	h3->GetYaxis()->SetTitleSize(0.045);
	h3->GetYaxis()->SetLabelSize(0.045);
	h3->Draw();
	h2->Draw("same");
	h1->Draw("same");
	
	TLine *line1 = new TLine(238.6, 0, 238.6, y_max);
	line1->SetLineColor(kGray);
	line1->SetLineStyle(9);
	line1->Draw();
	TLine *line2 = new TLine(242, 0, 242, y_max);
	line2->SetLineColor(kGray);
	line2->SetLineStyle(9);
	line2->Draw();
	TLine *line3 = new TLine(295.2, 0, 295.2, y_max);
	line3->SetLineColor(kGray);
	line3->SetLineStyle(9);
	line3->Draw();
	TLine *line4 = new TLine(352, 0, 352, y_max);
	line4->SetLineColor(kGray);
	line4->SetLineStyle(9);
	line4->Draw();
	TLine *line11 = new TLine(478.3, 0, 478.3, y_max);
	line11->SetLineColor(kGray);
	line11->SetLineStyle(9);
	line11->Draw();
	TLine *line5 = new TLine(511, 0, 511, y_max);
	line5->SetLineColor(kGray);
	line5->SetLineStyle(9);
	line5->Draw();
	TLine *line6 = new TLine(514, 0, 514, y_max);
	line6->SetLineColor(kGray);
	line6->SetLineStyle(9);
	line6->Draw();
	TLine *line7 = new TLine(583.2, 0, 583.2, y_max);
	line7->SetLineColor(kGray);
	line7->SetLineStyle(9);
	line7->Draw();
	TLine *line8 = new TLine(609.3, 0, 609.3, y_max);
	line8->SetLineColor(kGray);
	line8->SetLineStyle(9);
	line8->Draw();
	TLine *line9 = new TLine(911.2, 0, 911.2, y_max);
	line9->SetLineColor(kGray);
	line9->SetLineStyle(9);
	line9->Draw();
	TLine *line10 = new TLine(969, 0, 969, y_max);
	line10->SetLineColor(kGray);
	line10->SetLineStyle(9);
	line10->Draw();
	
	auto *legend = new TLegend(.7, .75, .88, .88);
	legend->AddEntry(h3, "EnrCoax (II, II+)", "l");
	legend->AddEntry(h2, "EnrBEGe (II, II+)", "l");
	legend->AddEntry(h1, "IC (II+)", "l");
	legend->AddEntry(line1, "Background #gamma", "l");
	legend->Draw();

	return 0;
}
//=========================================================================
//=========================================================================
//=========================================================================
int normalized() {

	TFile *f1 = new TFile("53_114_PSD/IC_new/20210726_IC.root");
	TH1D *histo1 = (TH1D*)f1->Get("LAr");
	TFile *f2 = new TFile("53_114_PSD/BEGe_new/20210726_BEGe.root");
	TH1D *histo2 = (TH1D*)f2->Get("LAr");
	TFile *f3 = new TFile("53_114_PSD/coax_new/20210726_coax.root");
	TH1D *histo3 = (TH1D*)f3->Get("LAr");
	
	TH1D *h1 = new TH1D ("h1","",5200,0,5200);
	TH1D *h2 = new TH1D ("h2","",5200,0,5200);
	TH1D *h3 = new TH1D ("h3","",5200,0,5200);
	
	for ( int i=0; i<195; i++) {
		h3->SetBinContent(i+1, (histo3->GetBinContent(i+1))/20.6676); // coax
	}
	
	for ( int i=195; i<5200; i++) {
		h3->SetBinContent(i+1, (histo3->GetBinContent(i+1))/41.8177); // coax
	}
	
	for ( int i=0; i<195; i++) {
		h2->SetBinContent(i+1, (histo2->GetBinContent(i+1))/30.1516); // BEGe
	}
	
	for ( int i=195; i<5200; i++) {	
		h2->SetBinContent(i+1, (histo2->GetBinContent(i+1))/53.3248); // BEGe
	}
	
	for ( int i=0; i<5200; i++) {
		h1->SetBinContent(i+1, (histo1->GetBinContent(i+1))/8.58872); // IC
	}
	
	
	
	const int y_max= 4e4;
	
	TCanvas *c = new TCanvas("c","c",1700,1000);
	c->SetLogy();
	h1->SetLineColor(kGreen+1);
	h1->SetStats(false);
	h1->GetXaxis()->SetTitle("Energy [keV]");
	h1->GetYaxis()->SetTitle("Events / (1 keV*kg*yr)");
	h1->GetXaxis()->SetRangeUser(0, 1000);
	h1->GetXaxis()->SetTitleSize(0.045);
	h1->GetXaxis()->SetLabelSize(0.045);
	h1->GetYaxis()->SetTitleSize(0.045);
	h1->GetYaxis()->SetLabelSize(0.045);
	h2->SetLineColor(kBlue);
	h2->GetXaxis()->SetRangeUser(0, 1000);
	h2->SetStats(false);
	h2->GetXaxis()->SetTitle("Energy [keV]");
	h2->GetYaxis()->SetTitle("Events / (1 keV*kg*yr)");
	h2->GetXaxis()->SetTitleSize(0.045);
	h2->GetXaxis()->SetLabelSize(0.045);
	h2->GetYaxis()->SetTitleSize(0.045);
	h2->GetYaxis()->SetLabelSize(0.045);
	h3->SetLineColor(kRed+1);
	h3->GetXaxis()->SetRangeUser(0, 1000);
	h3->SetStats(false);
	h3->GetXaxis()->SetTitle("Energy [keV]");
	h3->GetYaxis()->SetTitle("Events / (1 keV*kg*yr)");
	h3->GetXaxis()->CenterTitle();
	h3->GetYaxis()->CenterTitle();
	h3->GetXaxis()->SetTitleSize(0.045);
	h3->GetXaxis()->SetLabelSize(0.045);
	h3->GetYaxis()->SetTitleSize(0.045);
	h3->GetYaxis()->SetLabelSize(0.045);
	h3->Draw();
	h2->Draw("same");
	h1->Draw("same");
	
	TLine *line1 = new TLine(238.6, 0, 238.6, y_max);
	line1->SetLineColor(kGray);
	line1->SetLineStyle(9);
	line1->Draw();
	TLine *line2 = new TLine(242, 0, 242, y_max);
	line2->SetLineColor(kGray);
	line2->SetLineStyle(9);
	line2->Draw();
	TLine *line3 = new TLine(295.2, 0, 295.2, y_max);
	line3->SetLineColor(kGray);
	line3->SetLineStyle(9);
	line3->Draw();
	TLine *line4 = new TLine(352, 0, 352, y_max);
	line4->SetLineColor(kGray);
	line4->SetLineStyle(9);
	line4->Draw();
	TLine *line11 = new TLine(478.3, 0, 478.3, y_max);
	line11->SetLineColor(kGray);
	line11->SetLineStyle(9);
	line11->Draw();
	TLine *line5 = new TLine(511, 0, 511, y_max);
	line5->SetLineColor(kGray);
	line5->SetLineStyle(9);
	line5->Draw();
	TLine *line6 = new TLine(514, 0, 514, y_max);
	line6->SetLineColor(kGray);
	line6->SetLineStyle(9);
	line6->Draw();
	TLine *line7 = new TLine(583.2, 0, 583.2, y_max);
	line7->SetLineColor(kGray);
	line7->SetLineStyle(9);
	line7->Draw();
	TLine *line8 = new TLine(609.3, 0, 609.3, y_max);
	line8->SetLineColor(kGray);
	line8->SetLineStyle(9);
	line8->Draw();
	TLine *line9 = new TLine(911.2, 0, 911.2, y_max);
	line9->SetLineColor(kGray);
	line9->SetLineStyle(9);
	line9->Draw();
	TLine *line10 = new TLine(969, 0, 969, y_max);
	line10->SetLineColor(kGray);
	line10->SetLineStyle(9);
	line10->Draw();
	
	auto *legend = new TLegend(.7, .75, .88, .88);
	legend->AddEntry(h3, "EnrCoax (II, II+)", "l");
	legend->AddEntry(h2, "EnrBEGe (II, II+)", "l");
	legend->AddEntry(h1, "IC (II+)", "l");
	legend->AddEntry(line1, "Background #gamma", "l");
	legend->Draw();

	return 0;
}


