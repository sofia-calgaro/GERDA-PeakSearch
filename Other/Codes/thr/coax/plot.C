using namespace std;

void all_strings() {

	TFile *file  = new TFile("20210724_coaxTHR.root");
	
	TH1D *LAr_str2 = (TH1D*)file->Get("LAr_str2");
	TH1D *LAr_str5 = (TH1D*)file->Get("LAr_str5");
	
	TCanvas *c = new TCanvas();
	LAr_str2->GetXaxis()->SetRangeUser(120, 300);
	LAr_str2->GetYaxis()->SetRangeUser(0, 420);
	LAr_str2->GetXaxis()->SetTitle("Energy [keV]");
	LAr_str2->GetYaxis()->SetTitle("cts / 1 keV");
	
	LAr_str2->SetStats(kFALSE);
	LAr_str5->SetStats(kFALSE);
	
	LAr_str2->SetLineWidth(2);
	LAr_str5->SetLineWidth(2);
	
	LAr_str2->Draw();
	LAr_str5->Draw("same");
	
	TLine *line1 = new TLine(195, 0, 195, 420);
	line1->SetLineColor(kGray+3);
	line1->SetLineStyle(2);
	line1->SetLineWidth(3);
	line1->Draw();
	
	auto *legend = new TLegend(.65, .7, .85, .88);
	legend->AddEntry(LAr_str2, "String #2", "l");
	legend->AddEntry(LAr_str5, "String #5", "l");
	legend->AddEntry(line1, "Thr = 195 keV", "l");
	legend->Draw();
}

void single_strings() {

	TFile *file  = new TFile("20210724_coaxTHR.root");
	
	TH1D *LAr_str2 = (TH1D*)file->Get("LAr_str2");
	TH1D *LAr_str5 = (TH1D*)file->Get("LAr_str5");
	
	LAr_str2->GetXaxis()->SetRangeUser(120, 300);
	LAr_str2->GetYaxis()->SetRangeUser(0, 420);
	LAr_str2->GetXaxis()->SetTitle("Energy [keV]");
	LAr_str2->GetYaxis()->SetTitle("cts / 1 keV");
	LAr_str5->GetXaxis()->SetRangeUser(120, 300);
	LAr_str5->GetYaxis()->SetRangeUser(0, 420);
	LAr_str5->GetXaxis()->SetTitle("Energy [keV]");
	LAr_str5->GetYaxis()->SetTitle("cts / 1 keV");
	
	LAr_str2->SetStats(kFALSE);
	LAr_str5->SetStats(kFALSE);
	
	LAr_str2->SetLineWidth(2);
	LAr_str5->SetLineWidth(2);
	
	LAr_str2->SetTitle("String #2");
	LAr_str5->SetTitle("String #5");
	
	TLine *line2 = new TLine(195, 0, 195, 420);
	line2->SetLineColor(kGray+3);
	line2->SetLineStyle(2);
	line2->SetLineWidth(3);
	
	TLine *line5 = new TLine(195, 0, 195, 420);
	line5->SetLineColor(kGray+3);
	line5->SetLineStyle(2);
	line5->SetLineWidth(3);
	
	TCanvas *c2 = new TCanvas();
	LAr_str2->Draw();
	line2->Draw();
	
	TCanvas *c5 = new TCanvas();
	LAr_str5->Draw();
	line5->Draw();
	
}

void single_channels() {

	TFile *file  = new TFile("20210724_coaxTHR.root");
	
	int ch;
	cout << " What channel (8-10, 27-29, 36)? ";
	cin >> ch;
	
	char histo_name[200];
	sprintf(histo_name, "LAr_ch%i", ch);
	TH1D *LAr_ch = (TH1D*)file->Get(histo_name);
	
	TCanvas *c = new TCanvas();
	LAr_ch->GetXaxis()->SetRangeUser(120, 300);
	LAr_ch->GetYaxis()->SetRangeUser(0, 70);
	LAr_ch->GetXaxis()->SetTitle("Energy [keV]");
	LAr_ch->GetYaxis()->SetTitle("cts / 1 keV");
	LAr_ch->Draw();
	
	TLine *line1 = new TLine(195, 0, 195, 70);
	line1->SetLineColor(kGray+3);
	line1->SetLineStyle(2);
	line1->SetLineWidth(3);
	line1->Draw();
}
