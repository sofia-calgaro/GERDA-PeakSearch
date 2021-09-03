int diff() {

	TFile *f1 = TFile::Open("/home/sofia/gerda_data/53_114_PSD/coax_new/PSD_20210717_coax.root"); // tot
	//TFile *f1 = TFile::Open("/home/sofia/gerda_data/53_114_PSD/IC_new/PSD_20210717_IC.root"); // tot
	TH1D *h1 = (TH1D*) f1->Get("LAr_PSD");
	//TFile *f2 = TFile::Open("/home/sofia/gerda_data/53_114_PSD/IC/PSD_2021078_IC.root"); // PSD
	TFile *f2 = TFile::Open("/home/sofia/gerda_data/53_114_PSD/coax_new2/20210726_coax.root"); // PSD
	TH1D *h2 = (TH1D*) f2->Get("LAr_PSD");
	
	for ( int i=0; i<h1->GetNbinsX(); i++ ) {
		int a = h1->GetBinContent(i);
		int b = h2->GetBinContent(i);
		int diff = a - b;
		if ( diff!=0 ) {
			std::cout << "Diff = " << diff << "\t for bin=" << i+1 << std::endl;
		}
	}

	return 0;
}
