int plot_other_experiments() {

	int sing_comb;
	cout << " Single (0) or Combined (1)? ";
	cin >> sing_comb;
	
	int det;
	if ( sing_comb==0 ) {
		cout << " Coax (0), BEGe (1) or IC (2)? ";
		cin >> det;
	}
	
	char filename_DP[200], filename_ALP[200];
	if ( sing_comb==0 ) {
		if ( det==0 ) { 
			sprintf(filename_DP, "/home/sofia/Analysis/SuperWIMPs_couplings/vector_enrCoax.txt"); 
			sprintf(filename_ALP, "/home/sofia/Analysis/SuperWIMPs_couplings/pseudo_enrCoax.txt"); 
		}
		if ( det==1 ) { 
			sprintf(filename_DP, "/home/sofia/Analysis/SuperWIMPs_couplings/vector_enrBEGe.txt"); 
			sprintf(filename_ALP, "/home/sofia/Analysis/SuperWIMPs_couplings/pseudo_enrBEGe.txt"); 
		}
		if ( det==2 ) { 
			sprintf(filename_DP, "/home/sofia/Analysis/SuperWIMPs_couplings/vector_invCoax.txt"); 
			sprintf(filename_ALP, "/home/sofia/Analysis/SuperWIMPs_couplings/pseudo_invCoax.txt"); 
		}
	}
	if ( sing_comb==1 ) {
		sprintf(filename_DP, "/home/sofia/Analysis/SuperWIMPs_couplings/vector.txt"); 
		sprintf(filename_ALP, "/home/sofia/Analysis/SuperWIMPs_couplings/pseudo.txt");
	}

	//===========================================================================================
	// vector SuperWIMPs (dark photons)
	TCanvas *c_dp = new TCanvas("c_dp", "c_dp", 1300, 900);
	c_dp->SetLogy();
	c_dp->SetLogx();
	TMultiGraph *mg_dp = new TMultiGraph();
		
		// CDEX
		TGraphErrors *gr1 = new TGraphErrors("vector/CDEX_cut.txt", "%lg %lg %*lg");
		gr1->SetLineColor(kAzure+2);
		gr1->SetLineWidth(2);
		
		// Majorana
		TGraphErrors *gr2 = new TGraphErrors("vector/Majorana2_dp.txt");
		gr2->SetLineColor(kRed+1);
		gr2->SetLineWidth(2);
		
		// EDELWEISS3 - incomplete
		TGraphErrors *gr3 = new TGraphErrors("vector/EDELWEISS3_incomplete.txt");
		gr3->SetLineColor(kOrange);
		gr3->SetLineWidth(2);
		
		// RG
		TGraphErrors *gr4 = new TGraphErrors("vector/HB_RG.txt");
		gr4->SetLineColor(kGreen+2);
		gr4->SetLineWidth(2);
		gr4->SetLineStyle(10);
		
		// HB
		TGraphErrors *gr5 = new TGraphErrors("vector/RG_HB.txt");
		gr5->SetLineColor(kViolet-5);
		gr5->SetLineWidth(2);
		gr5->SetLineStyle(10);
		
		// stellar_bounds
		TGraphErrors *gr6 = new TGraphErrors("vector/stellar_bounds.txt");
		gr6->SetLineColor(6);
		gr6->SetLineWidth(2);
		
		// SuperCDMS
		TGraphErrors *gr7 = new TGraphErrors("vector/SuperCDMS_cut.txt", "%lg %lg %*lg");
		gr7->SetLineColor(kRed+2);
		gr7->SetLineWidth(2);
		
		// XENON100
		TGraphErrors *gr8 = new TGraphErrors("vector/XENON100.txt");
		gr8->SetLineColor(kMagenta+1);
		gr8->SetLineWidth(2);
		
		// XMASS
		TGraphErrors *gr9 = new TGraphErrors("vector/XMASS.txt");
		gr9->SetLineColor(kGray+1);
		gr9->SetLineWidth(2);
		
		// GERDA - old
		TGraphErrors *gr19 = new TGraphErrors("results_cplg_strength.txt", "%lg %*lg %lg");
		gr19->SetLineColor(kAzure-8);
		gr19->SetLineWidth(2);
		
		// GERDA - new
		TGraphErrors *gr20 = new TGraphErrors(filename_DP);
		gr20->SetLineColor(kOrange-3);
		gr20->SetLineWidth(2);
	
	mg_dp->Add(gr1);
	mg_dp->Add(gr2);
	//mg_dp->Add(gr3); // valori incompleti
	mg_dp->Add(gr4);
	mg_dp->Add(gr5);
	//mg_dp->Add(gr6); // NO
	mg_dp->Add(gr7); 
	mg_dp->Add(gr8);
	mg_dp->Add(gr9);
	mg_dp->Add(gr19);
	mg_dp->Add(gr20);
	
	mg_dp->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	mg_dp->GetYaxis()->SetTitle("Kinetic mixing strength, #alpha ' / #alpha");
	mg_dp->GetXaxis()->SetTitleSize(0.045);
	mg_dp->GetXaxis()->SetLabelSize(0.045);
	mg_dp->GetYaxis()->SetTitleSize(0.045);
	mg_dp->GetYaxis()->SetLabelSize(0.045);
	mg_dp->GetXaxis()->SetTitleOffset(1.00);
	mg_dp->GetXaxis()->SetLabelOffset(-0.01);
	mg_dp->GetYaxis()->SetTitleOffset(1.15);
	mg_dp->GetYaxis()->SetLabelOffset(-0.001);
	mg_dp->GetXaxis()->SetTitleFont(132);
	mg_dp->GetYaxis()->SetTitleFont(132);
	mg_dp->GetXaxis()->SetLabelFont(132);
	mg_dp->GetYaxis()->SetLabelFont(132);
	mg_dp->GetXaxis()->CenterTitle();
	mg_dp->GetYaxis()->CenterTitle();
	mg_dp->Draw("AL");
	mg_dp->GetXaxis()->SetRange(5, 1500);
	
	auto *leg_dp = new TLegend(.13, .67, .5, .89);
	leg_dp->SetBorderSize(0);
	//leg_dp->AddEntry(gr3, "EDELWEISS3_incomplete", "l");
	leg_dp->AddEntry(gr4, "RG", "l");
	leg_dp->AddEntry(gr5, "HB", "l");
	//leg_dp->AddEntry(gr6, "stellar_bounds", "l");
	leg_dp->AddEntry(gr8, "XENON100", "l");
	leg_dp->AddEntry(gr7, "SuperCDMS", "l");
	leg_dp->AddEntry(gr2, "Majorana", "l");
	leg_dp->AddEntry(gr9, "XMASS", "l");
	leg_dp->AddEntry(gr1, "CDEX", "l");
	leg_dp->AddEntry(gr19, "GERDA - Phase (II)", "l");
	char gr20_label[200];
	if ( sing_comb==0 ) {
		if ( det==0 ) sprintf(gr20_label, "EnrCoax - Phase (II, II+)");
		if ( det==1 ) sprintf(gr20_label, "EnrBEGe - Phase (II, II+)");
		if ( det==2 ) sprintf(gr20_label, "IC - Phase (II, II+)");
	}
	if ( sing_comb==1 ) { sprintf(gr20_label, "GERDA - Phase (II, II+)"); }
	leg_dp->AddEntry(gr20, gr20_label, "l");
	leg_dp->Draw();



	//===========================================================================================
	// pseudoscalar SuperWIMPs (ALPs)
	TCanvas *c_alps = new TCanvas("c_alps", "c_alps", 1300, 900);
	c_alps->SetLogy();
	c_alps->SetLogx();
	TMultiGraph *mg_alps = new TMultiGraph();
		
		// CDEX
		TGraphErrors *gr10 = new TGraphErrors("pseudo/CDEX_cut.txt");
		gr10->SetLineColor(kAzure+2);
		gr10->SetLineWidth(2);
		
		// Majorana
		TGraphErrors *gr11 = new TGraphErrors("pseudo/Majorana2_alps.txt");
		gr11->SetLineColor(kRed+1);
		gr11->SetLineWidth(2);
		
		// EDELWEISS3
		TGraphErrors *gr12 = new TGraphErrors("pseudo/EDELWEISS3.txt");
		gr12->SetLineColor(kOrange);
		gr12->SetLineWidth(2);
		
		// SuperCDMS
		TGraphErrors *gr13 = new TGraphErrors("pseudo/SuperCDMS_PhysRev.txt", "%lg %lg %*lg");
		gr13->SetLineColor(kRed+2);
		gr13->SetLineWidth(2);
		
		// XENON100
		TGraphErrors *gr14 = new TGraphErrors("pseudo/XENON100.txt");
		gr14->SetLineColor(kMagenta+1);
		gr14->SetLineWidth(2);
		
		// XMASS
		TGraphErrors *gr15 = new TGraphErrors("pseudo/XMASS.txt");
		gr15->SetLineColor(kGray+1);
		gr15->SetLineWidth(2);
		
		// LUX
		TGraphErrors *gr16 = new TGraphErrors("pseudo/LUX.txt");
		gr16->SetLineColor(kGreen+2);
		gr16->SetLineWidth(2);
		
		// PandaX_II
		TGraphErrors *gr17 = new TGraphErrors("pseudo/PandaX_II.txt");
		gr17->SetLineColor(kViolet-5);
		gr17->SetLineWidth(2);
		
		// GERDA - old
		TGraphErrors *gr18 = new TGraphErrors("results_cplg_strength.txt", "%lg %lg %*lg");
		gr18->SetLineColor(kAzure-8);
		gr18->SetLineWidth(2);
		
		// GERDA - new
		TGraphErrors *gr21 = new TGraphErrors(filename_ALP);
		gr21->SetLineColor(kOrange-3);
		gr21->SetLineWidth(2);
	
	mg_alps->Add(gr10);
	mg_alps->Add(gr11);
	//mg_alps->Add(gr12);
	mg_alps->Add(gr13);
	mg_alps->Add(gr14);
	mg_alps->Add(gr15);
	mg_alps->Add(gr16);
	mg_alps->Add(gr17);
	mg_alps->Add(gr18);
	mg_alps->Add(gr21);
	
	mg_alps->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	mg_alps->GetYaxis()->SetTitle("Axion-electron coupling, g_{ae}");
	mg_alps->GetXaxis()->SetTitleSize(0.045);
	mg_alps->GetXaxis()->SetLabelSize(0.045);
	mg_alps->GetYaxis()->SetTitleSize(0.045);
	mg_alps->GetYaxis()->SetLabelSize(0.045);
	mg_alps->GetXaxis()->SetTitleOffset(1.00);
	mg_alps->GetXaxis()->SetLabelOffset(-0.01);
	mg_alps->GetYaxis()->SetTitleOffset(1.15);
	mg_alps->GetYaxis()->SetLabelOffset(-0.001);
	mg_alps->GetXaxis()->SetTitleFont(132);
	mg_alps->GetYaxis()->SetTitleFont(132);
	mg_alps->GetXaxis()->SetLabelFont(132);
	mg_alps->GetYaxis()->SetLabelFont(132);
	mg_alps->GetXaxis()->CenterTitle();
	mg_alps->GetYaxis()->CenterTitle();
	mg_alps->Draw("AL");
	mg_alps->GetXaxis()->SetRange(5, 1500);
	
	auto *leg_alps = new TLegend(.13, .67, .5, .89);
	leg_alps->SetBorderSize(0);
	//leg_alps->AddEntry(gr12, "EDELWEISS3", "l");
	leg_alps->AddEntry(gr17, "PandaX-II", "l");
	leg_alps->AddEntry(gr14, "XENON100", "l");
	leg_alps->AddEntry(gr13, "SuperCDMS", "l");
	leg_alps->AddEntry(gr11, "Majorana", "l");
	leg_alps->AddEntry(gr15, "XMASS", "l");
	leg_alps->AddEntry(gr16, "LUX", "l");
	leg_alps->AddEntry(gr10, "CDEX", "l");
	leg_alps->AddEntry(gr18, "GERDA - Phase (II)", "l");
	char gr21_label[200];
	if ( sing_comb==0 ) {
		if ( det==0 ) sprintf(gr21_label, "EnrCoax - Phase (II, II+)");
		if ( det==1 ) sprintf(gr21_label, "EnrBEGe - Phase (II, II+)");
		if ( det==2 ) sprintf(gr21_label, "IC - Phase (II, II+)");
	}
	if ( sing_comb==1 ) { sprintf(gr21_label, "GERDA - Phase (II, II+)"); }
	leg_alps->AddEntry(gr21, gr21_label, "l");
	leg_alps->Draw();

	return 0;
}
