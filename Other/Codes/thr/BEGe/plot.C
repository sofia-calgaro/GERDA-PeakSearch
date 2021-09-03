void all_strings() {

	TFile *file  = new TFile("20210724_BEGeTHR.root");
	
	TH1D *LAr_str1 = (TH1D*)file->Get("LAr_str1");
	TH1D *LAr_str3 = (TH1D*)file->Get("LAr_str3");
	TH1D *LAr_str4 = (TH1D*)file->Get("LAr_str4");
	TH1D *LAr_str6 = (TH1D*)file->Get("LAr_str6");
	
	TCanvas *c = new TCanvas();
	LAr_str1->GetXaxis()->SetRangeUser(120, 300);
	LAr_str1->GetYaxis()->SetRangeUser(0, 320);
	LAr_str1->GetXaxis()->SetTitle("Energy [keV]");
	LAr_str1->GetYaxis()->SetTitle("cts / 1 keV");
	
	LAr_str1->SetStats(kFALSE);
	LAr_str3->SetStats(kFALSE);
	LAr_str4->SetStats(kFALSE);
	LAr_str6->SetStats(kFALSE);
	
	LAr_str1->SetLineWidth(2);
	LAr_str3->SetLineWidth(2);
	LAr_str4->SetLineWidth(2);
	LAr_str6->SetLineWidth(2);
	LAr_str6->SetLineColor(kGreen+1);
	
	LAr_str1->Draw();
	LAr_str3->Draw("same");
	LAr_str4->Draw("same");
	LAr_str6->Draw("same");
	
	TLine *line1 = new TLine(165, 0, 165, 320);
	line1->SetLineColor(kGray+3);
	line1->SetLineStyle(2);
	line1->SetLineWidth(3);
	line1->Draw();
	
	auto *legend = new TLegend(.65, .7, .85, .88);
	legend->AddEntry(LAr_str1, "String #1", "l");
	legend->AddEntry(LAr_str3, "String #3", "l");
	legend->AddEntry(LAr_str4, "String #4", "l");
	legend->AddEntry(LAr_str6, "String #6", "l");
	legend->AddEntry(line1, "Thr = 165 keV", "l");
	legend->Draw();
}

void single_strings() {

	TFile *file  = new TFile("20210724_BEGeTHR.root");
	
	TH1D *LAr_str1 = (TH1D*)file->Get("LAr_str1");
	TH1D *LAr_str3 = (TH1D*)file->Get("LAr_str3");
	TH1D *LAr_str4 = (TH1D*)file->Get("LAr_str4");
	TH1D *LAr_str6 = (TH1D*)file->Get("LAr_str6");
	
	LAr_str1->GetXaxis()->SetRangeUser(120, 300);
	LAr_str1->GetYaxis()->SetRangeUser(0, 270);
	LAr_str1->GetXaxis()->SetTitle("Energy [keV]");
	LAr_str1->GetYaxis()->SetTitle("cts / 1 keV");
	LAr_str3->GetXaxis()->SetRangeUser(120, 300);
	LAr_str3->GetYaxis()->SetRangeUser(0, 320);
	LAr_str3->GetXaxis()->SetTitle("Energy [keV]");
	LAr_str3->GetYaxis()->SetTitle("cts / 1 keV");
	LAr_str4->GetXaxis()->SetRangeUser(120, 300);
	LAr_str4->GetYaxis()->SetRangeUser(0, 250);
	LAr_str4->GetXaxis()->SetTitle("Energy [keV]");
	LAr_str4->GetYaxis()->SetTitle("cts / 1 keV");
	LAr_str6->GetXaxis()->SetRangeUser(120, 300);
	LAr_str6->GetYaxis()->SetRangeUser(0, 200);
	LAr_str6->GetXaxis()->SetTitle("Energy [keV]");
	LAr_str6->GetYaxis()->SetTitle("cts / 1 keV");
	
	LAr_str1->SetStats(kFALSE);
	LAr_str3->SetStats(kFALSE);
	LAr_str4->SetStats(kFALSE);
	LAr_str6->SetStats(kFALSE);
	
	LAr_str1->SetTitle("String #1");
	LAr_str3->SetTitle("String #3");
	LAr_str4->SetTitle("String #4");
	LAr_str6->SetTitle("String #6");
	
	LAr_str1->SetLineWidth(2);
	LAr_str3->SetLineWidth(2);
	LAr_str4->SetLineWidth(2);
	LAr_str6->SetLineWidth(2);
	LAr_str6->SetLineColor(kGreen+1);
	
	TLine *line1 = new TLine(195, 0, 195, 270);
	line1->SetLineColor(kGray+3);
	line1->SetLineStyle(2);
	line1->SetLineWidth(3);
	
	TLine *line3 = new TLine(195, 0, 195, 320);
	line3->SetLineColor(kGray+3);
	line3->SetLineStyle(2);
	line3->SetLineWidth(3);
	
	TLine *line4 = new TLine(195, 0, 195, 250);
	line4->SetLineColor(kGray+3);
	line4->SetLineStyle(2);
	line4->SetLineWidth(3);
	
	TLine *line6 = new TLine(195, 0, 195, 200);
	line6->SetLineColor(kGray+3);
	line6->SetLineStyle(2);
	line6->SetLineWidth(3);
	
	TCanvas *c1 = new TCanvas();
	LAr_str1->Draw();
	line1->Draw();
	
	TCanvas *c3 = new TCanvas();
	LAr_str3->Draw();
	line3->Draw();
	
	TCanvas *c4 = new TCanvas();
	LAr_str4->Draw();
	line4->Draw();
	
	TCanvas *c6 = new TCanvas();
	LAr_str6->Draw();
	line6->Draw();
	
}

void all_channels() {

}
