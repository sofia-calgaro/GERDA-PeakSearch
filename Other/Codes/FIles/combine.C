int combine() {

	TFile *f = new TFile("gerda-summary-run0053-run0114-phy-full.root");
	
	// LAr cut
	TH1D *hLAr0 = (TH1D*)f->Get("hLAr0");
	TH1D *hLAr1 = (TH1D*)f->Get("hLAr1");
	TH1D *hLAr4 = (TH1D*)f->Get("hLAr4");
	TH1D *hLAr5 = (TH1D*)f->Get("hLAr5");
	TH1D *hLAr6 = (TH1D*)f->Get("hLAr6");
	TH1D *hLAr7 = (TH1D*)f->Get("hLAr7");
	TH1D *hLAr8 = (TH1D*)f->Get("hLAr8");
	TH1D *hLAr9 = (TH1D*)f->Get("hLAr9");
	
	TH1D *hLAr_BEGe = (TH1D*)hLAr0->Clone();
	hLAr_BEGe->Add(hLAr4);
	hLAr_BEGe->Add(hLAr8);
	hLAr_BEGe->Add(hLAr9);
	TH1D *hLAr_BEGe_withoutNoPSD = (TH1D*)hLAr8->Clone();
	hLAr_BEGe_withoutNoPSD->Add(hLAr0);
	
	TH1D *hLAr_coax = (TH1D*)hLAr1->Clone();
	hLAr_coax->Add(hLAr5);
	
	TH1D *hLAr_IC = (TH1D*)hLAr6->Clone();
	hLAr_IC->Add(hLAr7);
	
	// LAr+PSD cut
	TH1D *hPSDLAr0 = (TH1D*)f->Get("hPSDLAr0");
	TH1D *hPSDLAr1 = (TH1D*)f->Get("hPSDLAr1");
	TH1D *hPSDLAr5 = (TH1D*)f->Get("hPSDLAr5");
	TH1D *hPSDLAr6 = (TH1D*)f->Get("hPSDLAr6");
	TH1D *hPSDLAr8 = (TH1D*)f->Get("hPSDLAr8");
	
	TH1D *hPSDLAr_BEGe = (TH1D*)hPSDLAr0->Clone();
	hPSDLAr_BEGe->Add(hPSDLAr8);
	
	TH1D *hPSDLAr_coax = (TH1D*)hPSDLAr1->Clone();
	hPSDLAr_coax->Add(hPSDLAr5);
	
	TH1D *hPSDLAr_IC = (TH1D*)hPSDLAr6->Clone();
	
	TFile *output = new TFile("LAr_and_PSD_datasets.root", "recreate");
	output->WriteTObject(hLAr_BEGe);
	output->WriteTObject(hLAr_BEGe_withoutNoPSD);
	output->WriteTObject(hLAr_coax);
	output->WriteTObject(hLAr_IC);
	output->WriteTObject(hPSDLAr_BEGe);
	output->WriteTObject(hPSDLAr_coax);
	output->WriteTObject(hPSDLAr_IC);
	output->Close();
	
	return 0;

}
