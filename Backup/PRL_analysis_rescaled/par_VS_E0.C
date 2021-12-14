// Available functions:
//	- all(): plot, as a function of the energy, U90/p0/p1/p2 values
//	. comparison(): plot together U90 values of two different analysis
//	. difference(): plot the difference of U90 values of two different analysis

Int_t NumberOfRows(char *filename) {

	Int_t NumOfRows = 0;
	std::string line;
	std::ifstream file(filename);
	
	while (std::getline(file,line)) {
		++NumOfRows;
	}
	
	return NumOfRows;
}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
int *all() {

	int det;
	std::cout << "Coax (0), BEGe (1) or IC (2)? ";
	std::cin >> det;
	
	int run;
	std::cout << "\n * Run: 53-93 (0) or 53-114 (1)? ";
	std::cin >> run;
	int norm;
	std::cout << " * Normalized (0) or not (1)? ";
	std::cin >> norm;
	int PSD;
	std::cout << " * Only PSD (0) or everything (1)? ";
	std::cin >> PSD;
	int prior;
	std::cout << " * Prior: coax (0), BEGe (1), IC (2) or constant (3)? ";
	std::cin >> prior;
	
	char file_g1[100], file_g2[100], file_g3[100], file_g4[100];
	
	//========================================================================================================== U90 VS E0
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
						if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_coaxP/90UpperLimit.txt"); }
						if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior==1 ) {
						if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_BEGeP/90UpperLimit.txt"); }
						if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
						if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_ConstantP/90UpperLimit.txt"); std::cout << "HERE" << std::endl; }
						if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_coaxP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_BEGeP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_ConstantP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_ICP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_ICP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_coaxP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_BEGeP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_ICP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_ICP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_ConstantP/90UpperLimit.txt"); }
					if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	std::cout << file_g1 << std::endl;
	int thr=0;
	double y_max=0;
	if ( det==0 ) { thr = 195; y_max=37;}	
	if ( det==1 ) { thr = 195; y_max = 770; y_max=37; }
	if ( det==2 ) { thr = 0; y_max = 240; y_max=35;}
	
	TGraphErrors *g1 = new TGraphErrors(file_g1, "%lg %lg %*lg %*lg %*lg");
	
	TCanvas *c1 = new TCanvas("c1","c1",1700,1000);
	g1->SetLineWidth(2);
	g1->SetMarkerStyle(20);
	if ( det==0 ) {
		g1->SetLineColor(kRed+1);
		g1->SetMarkerColor(kRed+1);
	}
	if ( det==1 ) {
		g1->SetLineColor(kBlue+1);
		g1->SetMarkerColor(kBlue+1);
	}
	if ( det==2 ) {
		g1->SetLineColor(kGreen+2);
		g1->SetMarkerColor(kGreen+2);
	}
	g1->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	g1->GetXaxis()->SetTitleSize(0.045);
	g1->GetXaxis()->SetLabelSize(0.045);
	g1->GetYaxis()->SetTitleOffset(0.9);
	g1->GetXaxis()->CenterTitle();
	g1->GetYaxis()->SetTitle("S [cts/kg*yr]");
	g1->GetYaxis()->SetRangeUser(0,y_max);
	g1->GetXaxis()->SetRangeUser(30,1030);
	g1->GetYaxis()->SetTitleSize(0.045);
	g1->GetYaxis()->SetLabelSize(0.045);
	g1->GetXaxis()->SetRangeUser(0,1050);
	g1->GetYaxis()->CenterTitle();
	gStyle->SetOptTitle(0);
	
	g1->Draw("AL");
	
	TLine *line1 = new TLine(238.6, 0, 238.6, y_max);
	line1->SetLineColor(kGray+2);
	line1->SetLineStyle(9);
	line1->Draw();
	TLine *line2 = new TLine(242, 0, 242, y_max);
	line2->SetLineColor(kGray+2);
	line2->SetLineStyle(9);
	line2->Draw();
	TLine *line3 = new TLine(295.2, 0, 295.2, y_max);
	line3->SetLineColor(kGray+2);
	line3->SetLineStyle(9);
	line3->Draw();
	TLine *line4 = new TLine(352, 0, 352, y_max);
	line4->SetLineColor(kGray+2);
	line4->SetLineStyle(9);
	line4->Draw();
	TLine *line12 = new TLine(478.3, 0, 478.3, y_max);
	line12->SetLineColor(kGray+2);
	line12->SetLineStyle(9);
	line12->Draw();
	TLine *line5 = new TLine(511, 0, 511, y_max);
	line5->SetLineColor(kGray+2);
	line5->SetLineStyle(9);
	line5->Draw();
	TLine *line6 = new TLine(514, 0, 514, y_max);
	line6->SetLineColor(kGray+2);
	line6->SetLineStyle(9);
	line6->Draw();
	TLine *line7 = new TLine(583.2, 0, 583.2, y_max);
	line7->SetLineColor(kGray+2);
	line7->SetLineStyle(9);
	line7->Draw();
	TLine *line8 = new TLine(609.3, 0, 609.3, y_max);
	line8->SetLineColor(kGray+2);
	line8->SetLineStyle(9);
	line8->Draw();
	TLine *line9 = new TLine(911.2, 0, 911.2, y_max);
	line9->SetLineColor(kGray+2);
	line9->SetLineStyle(9);
	line9->Draw();
	TLine *line10 = new TLine(969, 0, 969, y_max);
	line10->SetLineColor(kGray+2);
	line10->SetLineStyle(9);
	line10->Draw();
	
	if ( det!=2 ) {
		auto *legend = new TLegend(.65, .75, .88, .88);
		legend->AddEntry(g1, "90% C.I. upper limits", "l");
		legend->AddEntry(line1, "Background #gamma", "l");
		TLine *line11 = new TLine(thr, 0, thr, y_max);
		line11->SetLineColor(kBlack);
		line11->SetLineWidth(3);
		line11->SetLineStyle(7);
		line11->Draw();
		char thr_label[100];
		sprintf(thr_label, "Energy threshold (%i keV)", thr);	
		legend->AddEntry(line11, thr_label, "l");
		legend->Draw();
	}
	if ( det==2 ) {
		auto *legend = new TLegend(.75, .75, .88, .88);
		legend->AddEntry(g1, "90% C.I. upper limit", "l");
		legend->AddEntry(line1, "Background #gamma", "l");
		legend->Draw();
	}
	
	
	c1->Update();
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_coaxP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_coaxP/counts_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_BEGeP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_BEGeP/counts_VS_E0.png"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_ConstantP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_ConstantP/counts_VS_E0.png"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_coax_coaxP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_BEGe_coaxP/counts_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_coax_BEGeP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_BEGe_BEGeP/counts_VS_E0.png"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_coax_ConstantP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_BEGe_ConstantP/counts_VS_E0.png"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_coax_PSD_coaxP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_BEGe_PSD_coaxP/counts_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_coax_PSD_BEGeP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_BEGe_PSD_BEGeP/counts_VS_E0.png"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_coax_PSD_ConstantP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_BEGe_PSD_ConstantP/counts_VS_E0.png"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_coax_coaxP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_BEGe_coaxP/counts_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_coax_BEGeP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_BEGe_BEGeP/counts_VS_E0.png"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_coax_ConstantP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_BEGe_ConstantP/counts_VS_E0.png"); }
				}
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_coaxP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_coaxP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_coaxP/counts_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_BEGeP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_BEGeP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_BEGeP/counts_VS_E0.png"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_ICP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_ICP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_ICP/counts_VS_E0.png"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_ConstantP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_ConstantP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_ConstantP/counts_VS_E0.png"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_coaxP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_coaxP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_coaxP/counts_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_BEGeP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_BEGeP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_BEGeP/counts_VS_E0.png"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_ICP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_ICP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_ICP/counts_VS_E0.png"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_ConstantP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_ConstantP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_ConstantP/counts_VS_E0.png"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_PSD_coaxP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_PSD_coaxP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_PSD_coaxP/counts_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_PSD_BEGeP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_PSD_BEGeP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_PSD_BEGeP/counts_VS_E0.png"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_PSD_ICP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_PSD_ICP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_PSD_ICP/counts_VS_E0.png"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_PSD_ConstantP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_PSD_ConstantP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_PSD_ConstantP/counts_VS_E0.png"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_coaxP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_coaxP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_coaxP/counts_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_BEGeP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_BEGeP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_BEGeP/counts_VS_E0.png"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_ICP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_ICP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_ICP/counts_VS_E0.png"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_ConstantP/counts_VS_E0.png"); }
					if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_ConstantP/counts_VS_E0.png"); }
					if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_ConstantP/counts_VS_E0.png"); }
				}
			}
		}
	}

	//========================================================================================================== p0 VS E0
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_coaxP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_coaxP/p0_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_BEGeP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_BEGeP/p0_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_ConstantP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_ConstantP/p0_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_coaxP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_coaxP/p0_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_BEGeP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_BEGeP/p0_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_ConstantP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_ConstantP/p0_VS_E0.txt"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
						if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_coaxP/p0_VS_E0.txt"); }
						if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_coaxP/p0_VS_E0.txt"); }
				}
				if ( prior==1 ) {
						if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_BEGeP/p0_VS_E0.txt"); }
						if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_BEGeP/p0_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
						if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_ConstantP/p0_VS_E0.txt"); }
						if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_ConstantP/p0_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_coaxP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_coaxP/p0_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_BEGeP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_BEGeP/p0_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_ConstantP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_ConstantP/p0_VS_E0.txt"); }
				}
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_coaxP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_coaxP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_coaxP/p0_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_BEGeP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_BEGeP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_BEGeP/p0_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_ICP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_ICP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_ICP/p0_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_ConstantP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_ConstantP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_ConstantP/p0_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_coaxP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_coaxP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_coaxP/p0_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_BEGeP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_BEGeP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_BEGeP/p0_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_ICP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_ICP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_ICP/p0_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_ConstantP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_ConstantP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_ConstantP/p0_VS_E0.txt"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_coaxP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_coaxP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_coaxP/p0_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_BEGeP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_BEGeP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_BEGeP/p0_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_ICP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_ICP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_ICP/p0_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_ConstantP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_ConstantP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_ConstantP/p0_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_coaxP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_coaxP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_coaxP/p0_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_BEGeP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_BEGeP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_BEGeP/p0_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_ICP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_ICP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_ICP/p0_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_ConstantP/p0_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_ConstantP/p0_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_ConstantP/p0_VS_E0.txt"); }
				}
			}
		}
	}
	
	Int_t rows = NumberOfRows(file_g2);
	const Int_t columns = 4;
	double data2[rows][columns];
	std::ifstream file2(file_g2);
	for (int i=0; i<rows; i++) {
		for (int j=0; j<columns; j++) {
			file2 >> data2[i][j];
		}
	}
	file2.close();
	
	Double_t x0[rows], y0[rows], exD0[rows], exU0[rows], eyD0[rows], eyU0[rows];
	for (int i=0; i<rows; i++) {
		x0[i] = data2[i][0];
		y0[i] = data2[i][1];
		exD0[i] = 0;
		exU0[i] = 0;
		eyD0[i] = data2[i][2];
		eyU0[i] = data2[i][3];
	}
	
	auto g2 = new TGraphAsymmErrors(rows, x0, y0, exD0, exU0, eyD0, eyU0);
	
	TCanvas *c2 = new TCanvas("c2","c2",1700,700);
	c2->SetLogy();
	g2->SetLineWidth(2);	
	g2->SetMarkerStyle(20);
	g2->SetLineColor(kMagenta+2);
	g2->SetMarkerColor(kMagenta+2);
	g2->SetMarkerSize(1.3);
	g2->GetXaxis()->SetTitle("Energy [keV]");
	g2->GetYaxis()->SetTitle("Offset [cts]");
	g2->GetXaxis()->SetTitleSize(0.045);
	g2->GetXaxis()->SetLabelSize(0.045);
	g2->GetYaxis()->SetTitleSize(0.045);
	g2->GetYaxis()->SetLabelSize(0.045);
	g2->SetTitle("");
	g2->GetXaxis()->SetRangeUser(30,1030);
	g2->Draw("AP");
	g2->GetXaxis()->CenterTitle();
	g2->GetYaxis()->CenterTitle();
	c2->Update();
	
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_coaxP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_coaxP/p0_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_BEGeP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_BEGeP/p0_VS_E0.png"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_ConstantP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_ConstantP/p0_VS_E0.png"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_coax_coaxP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_BEGe_coaxP/p0_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_coax_BEGeP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_BEGe_BEGeP/p0_VS_E0.png"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_coax_ConstantP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_BEGe_ConstantP/p0_VS_E0.png"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_coax_PSD_coaxP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_BEGe_PSD_coaxP/p0_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_coax_PSD_BEGeP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_BEGe_PSD_BEGeP/p0_VS_E0.png"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_coax_PSD_ConstantP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_BEGe_PSD_ConstantP/p0_VS_E0.png"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_coax_coaxP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_BEGe_coaxP/p0_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_coax_BEGeP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_BEGe_BEGeP/p0_VS_E0.png"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_coax_ConstantP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_BEGe_ConstantP/p0_VS_E0.png"); }
				}
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_coaxP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_coaxP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_coaxP/p0_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_BEGeP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_BEGeP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_BEGeP/p0_VS_E0.png"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_ICP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_ICP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_ICP/p0_VS_E0.png"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_ConstantP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_ConstantP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_ConstantP/p0_VS_E0.png"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_coaxP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_coaxP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_coaxP/p0_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_BEGeP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_BEGeP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_BEGeP/p0_VS_E0.png"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_ICP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_ICP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_ICP/p0_VS_E0.png"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_ConstantP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_ConstantP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_ConstantP/p0_VS_E0.png"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_PSD_coaxP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_PSD_coaxP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_PSD_coaxP/p0_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_PSD_BEGeP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_PSD_BEGeP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_PSD_BEGeP/p0_VS_E0.png"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_PSD_ICP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_PSD_ICP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_PSD_ICP/p0_VS_E0.png"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_PSD_ConstantP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_PSD_ConstantP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_PSD_ConstantP/p0_VS_E0.png"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_coaxP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_coaxP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_coaxP/p0_VS_E0.png"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_BEGeP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_BEGeP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_BEGeP/p0_VS_E0.png"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_ICP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_ICP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_ICP/p0_VS_E0.png"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_ConstantP/p0_VS_E0.png"); }
					if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_ConstantP/p0_VS_E0.png"); }
					if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_ConstantP/p0_VS_E0.png"); }
				}
			}
		}
	}
	
	//================================================================================================== p1 VS E0
	ifstream file3;
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
						if ( det==0 ) { file3.open("ReadJSON/53_93_NORM_coax_PSD_coaxP/p1_VS_E0.txt"); }
						if ( det==1 ) { file3.open("ReadJSON/53_93_NORM_BEGe_PSD_coaxP/p1_VS_E0.txt"); }
				}
				if ( prior==1 ) {
						if ( det==0 ) { file3.open("ReadJSON/53_93_NORM_coax_PSD_BEGeP/p1_VS_E0.txt"); }
						if ( det==1 ) { file3.open("ReadJSON/53_93_NORM_BEGe_PSD_BEGeP/p1_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
						if ( det==0 ) { file3.open("ReadJSON/53_93_NORM_coax_PSD_ConstantP/p1_VS_E0.txt"); }
						if ( det==1 ) { file3.open("ReadJSON/53_93_NORM_BEGe_PSD_ConstantP/p1_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_NORM_coax_coaxP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_NORM_BEGe_coaxP/p1_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_NORM_coax_BEGeP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_NORM_BEGe_BEGeP/p1_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_NORM_coax_ConstantP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_NORM_BEGe_ConstantP/p1_VS_E0.txt"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_coax_PSD_coaxP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_BEGe_PSD_coaxP/p1_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_coax_PSD_BEGeP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_BEGe_PSD_BEGeP/p1_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_coax_PSD_ConstantP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_BEGe_PSD_ConstantP/p1_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_coax_coaxP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_BEGe_coaxP/p1_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_coax_BEGeP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_BEGe_BEGeP/p1_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_93_coax_ConstantP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_93_BEGe_ConstantP/p1_VS_E0.txt"); }
				}
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_PSD_coaxP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_PSD_coaxP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_PSD_coaxP/p1_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_PSD_BEGeP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_PSD_BEGeP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_PSD_BEGeP/p1_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_PSD_ICP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_PSD_ICP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_PSD_ICP/p1_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_PSD_ConstantP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_PSD_ConstantP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_PSD_ConstantP/p1_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_coaxP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_coaxP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_coaxP/p1_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_BEGeP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_BEGeP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_BEGeP/p1_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_ICP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_ICP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_ICP/p1_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_ConstantP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_ConstantP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_ConstantP/p1_VS_E0.txt"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_coax_PSD_coaxP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_PSD_coaxP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_IC_PSD_coaxP/p1_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_coax_PSD_BEGeP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_PSD_BEGeP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_IC_PSD_BEGeP/p1_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_coax_PSD_ICPp1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_PSD_ICP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_IC_PSD_ICP/p1_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_coax_PSD_ConstantP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_PSD_ConstantP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_IC_PSD_ConstantP/p1_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_coax_coaxP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_coaxP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_IC_coaxP/p1_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_coax_BEGeP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_BEGeP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_IC_BEGeP/p1_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_coax_ICP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_ICP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_IC_ICP/p1_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { file3.open("ReadJSON/53_114_coax_ConstantP/p1_VS_E0.txt"); }
					if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_ConstantP/p1_VS_E0.txt"); }
					if ( det==2 ) { file3.open("ReadJSON/53_114_IC_ConstantP/p1_VS_E0.txt"); }
				}
			}
		}
	}
	
	if ( !file3 ) { cout << "\"p1_VS_E0.txt\" does not exist"; }
	else {
		double data3[rows][columns];
		for (int i=0; i<rows; i++) {
			for (int j=0; j<columns; j++) {
				file3 >> data3[i][j];
			}
		}
		file3.close();

		Double_t x1[rows], y1[rows], exD1[rows], exU1[rows], eyD1[rows], eyU1[rows];
		for (int i=0; i<rows; i++) {
			x1[i] = data3[i][0];
			y1[i] = data3[i][1];
			exD1[i] = 0;
			exU1[i] = 0;
			eyD1[i] = data3[i][2];
			eyU1[i] = data3[i][3];
		}
		
		auto g3 = new TGraphAsymmErrors(rows, x1, y1, exD1, exU1, eyD1, eyU1);
		
		TCanvas *c3 = new TCanvas("c3","c3",1700,700);
		g3->SetLineColor(kGreen+2);
		g3->SetLineWidth(2);	
		g3->SetMarkerStyle(20);
		g3->SetMarkerColor(kGreen+2);
		g3->SetMarkerSize(1.3);
		g3->GetXaxis()->CenterTitle();
		g3->GetYaxis()->CenterTitle();
		g3->GetXaxis()->SetTitle("Energy [keV]");
		g3->GetYaxis()->SetTitle("Slope [cts/keV]");
		g3->GetXaxis()->SetTitleSize(0.045);
		g3->GetXaxis()->SetLabelSize(0.045);
		g3->GetYaxis()->SetTitleSize(0.045);
		g3->GetYaxis()->SetLabelSize(0.045);
		g3->GetXaxis()->SetRangeUser(30,1030);
		g3->SetTitle("");
		g3->Draw("AP");
		c3->Update();
		
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_coaxP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_coaxP/p1_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_BEGeP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_BEGeP/p1_VS_E0.png"); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_ConstantP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_ConstantP/p1_VS_E0.png"); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_coax_coaxP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_BEGe_coaxP/p1_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_coax_BEGeP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_BEGe_BEGeP/p1_VS_E0.png"); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_coax_ConstantP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_BEGe_ConstantP/p1_VS_E0.png"); }
					}
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_coax_PSD_coaxP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_BEGe_PSD_coaxP/p1_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_coax_PSD_BEGeP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_BEGe_PSD_BEGeP/p1_VS_E0.png"); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_coax_PSD_ConstantP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_BEGe_PSD_ConstantP/p1_VS_E0.png"); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_coax_coaxP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_BEGe_coaxP/p1_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_coax_BEGeP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_BEGe_BEGeP/p1_VS_E0.png"); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_coax_ConstantP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_BEGe_ConstantP/p1_VS_E0.png"); }
					}
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_coaxP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_coaxP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_coaxP/p1_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_BEGeP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_BEGeP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_BEGeP/p1_VS_E0.png"); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_ICP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_ICP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_ICP/p1_VS_E0.png"); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_ConstantP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_ConstantP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_ConstantP/p1_VS_E0.png"); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_coaxP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_coaxP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_coaxP/p1_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_BEGeP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_BEGeP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_BEGeP/p1_VS_E0.png"); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_ICP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_ICP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_ICP/p1_VS_E0.png"); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_ConstantP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_ConstantP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_ConstantP/p1_VS_E0.png"); }
					}
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_PSD_coaxP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_PSD_coaxP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_PSD_coaxP/p1_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_PSD_BEGeP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_PSD_BEGeP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_PSD_BEGeP/p1_VS_E0.png"); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_PSD_ICP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_PSD_ICP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_PSD_ICP/p1_VS_E0.png"); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_PSD_ConstantP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_PSD_ConstantP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_PSD_ConstantP/p1_VS_E0.png"); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_coaxP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_coaxP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_coaxP/p1_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_BEGeP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_BEGeP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_BEGeP/p1_VS_E0.png"); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_ICP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_ICP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_ICP/p1_VS_E0.png"); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_ConstantP/p1_VS_E0.png"); }
						if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_ConstantP/p1_VS_E0.png"); }
						if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_ConstantP/p1_VS_E0.png"); }
					}
				}
			}
		}
		
	}
	
	//================================================================================================== p2 VS E0
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_coax_PSD_coaxP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_BEGe_PSD_coaxP/p2_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_coax_PSD_BEGeP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_BEGe_PSD_BEGeP/p2_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_coax_PSD_ConstantP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_BEGe_PSD_ConstantP/p2_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_coax_coaxP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_BEGe_coaxP/p2_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_coax_BEGeP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_BEGe_BEGeP/p2_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_coax_ConstantP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_BEGe_ConstantP/p2_VS_E0.txt"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
						if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_coax_PSD_coaxP/p2_VS_E0.txt"); }
						if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_BEGe_PSD_coaxP/p2_VS_E0.txt"); }
				}
				if ( prior==1 ) {
						if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_coax_PSD_BEGeP/p2_VS_E0.txt"); }
						if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_BEGe_PSD_BEGeP/p2_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
						if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_coax_PSD_ConstantP/p2_VS_E0.txt"); }
						if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_BEGe_PSD_ConstantP/p2_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_coax_coaxP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_BEGe_coaxP/p2_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_coax_BEGeP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_BEGe_BEGeP/p2_VS_E0.txt"); }
				}
				if ( prior==2 ) {}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_coax_ConstantP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_BEGe_ConstantP/p2_VS_E0.txt"); }
				}
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_PSD_coaxP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_PSD_coaxP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_PSD_coaxP/p2_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_PSD_BEGeP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_PSD_BEGeP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_PSD_BEGeP/p2_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_PSD_ICP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_PSD_ICP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_PSD_ICP/p2_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_PSD_ConstantP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_PSD_ConstantP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_PSD_ConstantP/p2_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_coaxP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_coaxP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_coaxP/p2_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_BEGeP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_BEGeP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_BEGeP/p2_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_ICP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_ICP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_ICP/p2_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_ConstantP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_ConstantP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_ConstantP/p2_VS_E0.txt"); }
				}
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_PSD_coaxP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_PSD_coaxP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_PSD_coaxP/p2_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_PSD_BEGeP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_PSD_BEGeP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_PSD_BEGeP/p2_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_PSD_ICP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_PSD_ICP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_PSD_ICP/p2_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_PSD_ConstantP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_PSD_ConstantP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_PSD_ConstantP/p2_VS_E0.txt"); }
				}
			}
			if ( PSD==1 ) {
				if ( prior==0 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_coaxP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_coaxP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_coaxP/p2_VS_E0.txt"); }
				}
				if ( prior==1 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_BEGeP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_BEGeP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_BEGeP/p2_VS_E0.txt"); }
				}
				if ( prior==2 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_ICP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_ICP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_ICP/p2_VS_E0.txt"); }
				}
				if ( prior==3 ) {
					if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_ConstantP/p2_VS_E0.txt"); }
					if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_ConstantP/p2_VS_E0.txt"); }
					if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_ConstantP/p2_VS_E0.txt"); }
				}
			}
		}
	}
	ifstream file4(file_g4);
	if ( !file4 ) { cout << "\"p2_VS_E0.txt\" does not exist"; }
	else {
		Int_t rows4 = NumberOfRows(file_g4);
		double data4[rows4][columns];
		for (int i=0; i<rows4; i++) {
			for (int j=0; j<columns; j++) {
				file4 >> data4[i][j];
			}
		}
		file4.close();
		
		Double_t x2[rows4], y2[rows4], exD2[rows4], exU2[rows4], eyD2[rows4], eyU2[rows4];
		
		for (int i=0; i<rows4; i++) {
			x2[i] = data4[i][0];
			y2[i] = data4[i][1];
			exD2[i] = 0;
			exU2[i] = 0;
			eyD2[i] = data4[i][2];
			eyU2[i] = data4[i][3];
		}
		
		auto g4 = new TGraphAsymmErrors(rows4, x2, y2, exD2, exU2, eyD2, eyU2);
		
		TCanvas *c4 = new TCanvas("c4","c4",1700,700);
		g4->SetLineColor(kBlue-3);
		g4->SetLineWidth(2);	
		g4->SetMarkerStyle(20);
		g4->SetMarkerColor(kBlue-3);
		g4->SetMarkerSize(1.3);
		g4->GetXaxis()->CenterTitle();
		g4->GetYaxis()->CenterTitle();
		g4->GetXaxis()->SetTitle("Energy [keV]");
		g4->GetYaxis()->SetTitle("Curvature [cts/keV^{2}]");
		g4->GetXaxis()->SetTitleSize(0.045);
		g4->GetXaxis()->SetLabelSize(0.045);
		g4->GetYaxis()->SetTitleSize(0.045);
		g4->GetYaxis()->SetLabelSize(0.045);
		g4->SetTitle("");
		g4->GetXaxis()->SetRangeUser(30,1030);
		g4->Draw("AP");
		c4->Update();
		
		if ( run==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_coaxP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_coaxP/p2_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_BEGeP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_BEGeP/p2_VS_E0.png"); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD_ConstantP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD_ConstantP/p2_VS_E0.png"); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_coax_coaxP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_BEGe_coaxP/p2_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_coax_BEGeP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_BEGe_BEGeP/p2_VS_E0.png"); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_coax_ConstantP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_BEGe_ConstantP/p2_VS_E0.png"); }
					}
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_coax_PSD_coaxP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_BEGe_PSD_coaxP/p2_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_coax_PSD_BEGeP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_BEGe_PSD_BEGeP/p2_VS_E0.png"); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_coax_PSD_ConstantP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_BEGe_PSD_ConstantP/p2_VS_E0.png"); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_coax_coaxP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_BEGe_coaxP/p2_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_coax_BEGeP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_BEGe_BEGeP/p2_VS_E0.png"); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_coax_ConstantP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_BEGe_ConstantP/p2_VS_E0.png"); }
					}
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_coaxP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_coaxP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_coaxP/p2_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_BEGeP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_BEGeP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_BEGeP/p2_VS_E0.png"); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_ICP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_ICP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_ICP/p2_VS_E0.png"); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD_ConstantP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD_ConstantP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD_ConstantP/p2_VS_E0.png"); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_coaxP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_coaxP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_coaxP/p2_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_BEGeP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_BEGeP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_BEGeP/p2_VS_E0.png"); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_ICP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_ICP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_ICP/p2_VS_E0.png"); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_ConstantP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_ConstantP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_ConstantP/p2_VS_E0.png"); }
					}
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_PSD_coaxP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_PSD_coaxP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_PSD_coaxP/p2_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_PSD_BEGeP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_PSD_BEGeP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_PSD_BEGeP/p2_VS_E0.png"); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_PSD_ICP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_PSD_ICP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_PSD_ICP/p2_VS_E0.png"); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_PSD_ConstantP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_PSD_ConstantP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_PSD_ConstantP/p2_VS_E0.png"); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_coaxP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_coaxP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_coaxP/p2_VS_E0.png"); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_BEGeP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_BEGeP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_BEGeP/p2_VS_E0.png"); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_ICP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_ICP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_ICP/p2_VS_E0.png"); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_ConstantP/p2_VS_E0.png"); }
						if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_ConstantP/p2_VS_E0.png"); }
						if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_ConstantP/p2_VS_E0.png"); }
					}
				}
			}
		}
	}

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
int comparison() {

	std::cout << "\n******** FIRST ANALYSIS ********" << std::endl;
	int det1;
	std::cout << "Coax (0), BEGe (1) or IC (2)? ";
	std::cin >> det1;
	int run1;
	std::cout << "\n * Run: 53-93 (0) or 53-114 (1)? ";
	std::cin >> run1;
	int norm1;
	std::cout << " * Normalized (0) or not (1)? ";
	std::cin >> norm1;
	int PSD1;
	std::cout << " * Only PSD (0) or everything (1)? ";
	std::cin >> PSD1;
	int prior1;
	std::cout << " * Prior: coax (0), BEGe (1), IC (2) or constant (3)? ";
	std::cin >> prior1;
	
	std::cout << "\n\n******** SECOND ANALYSIS ********" << std::endl;
	int det2;
	std::cout << "Coax (0), BEGe (1) or IC (2)? ";
	std::cin >> det2;
	int run2;
	std::cout << "\n * Run: 53-93 (0) or 53-114 (1)? ";
	std::cin >> run2;
	int norm2;
	std::cout << " * Normalized (0) or not (1)? ";
	std::cin >> norm2;
	int PSD2;
	std::cout << " * Only PSD (0) or everything (1)? ";
	std::cin >> PSD2;
	int prior2;
	std::cout << " * Prior: coax (0), BEGe (1), IC (2) or constant (3)? ";
	std::cin >> prior2;
	
	TCanvas *c = new TCanvas("c","c",1700,1000);
	c->SetLogy();
	TMultiGraph *mg = new TMultiGraph();	
	int thr = 195;
	double y_max = 40;
	
	char file_g1[100], file_g2[100];
	//========================================================================================================== FIRST ANALYSIS
	if ( run1==0 ) {
		if ( norm1==0 ) {
			if ( PSD1==0 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD1==1 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm1==1 ) {
			if ( PSD1==0 ) {
				if ( prior1==0 ) {
						if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_coaxP/90UpperLimit.txt"); }
						if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
						if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_BEGeP/90UpperLimit.txt"); }
						if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {}
				if ( prior1==3 ) {
						if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_ConstantP/90UpperLimit.txt"); }
						if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD1==1 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	if ( run1==1 ) {
		if ( norm1==0 ) {
			if ( PSD1==0 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD1==1 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_ICP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_ICP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm1==1 ) {
			if ( PSD1==0 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD1==1 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_ICP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_ICP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	//========================================================================================================== SECOND ANALYSIS
	if ( run2==0 ) {
		if ( norm2==0 ) {
			if ( PSD2==0 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD2==1 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm2==1 ) {
			if ( PSD2==0 ) {
				if ( prior2==0 ) {
						if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_coaxP/90UpperLimit.txt"); }
						if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
						if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_BEGeP/90UpperLimit.txt"); }
						if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {}
				if ( prior2==3 ) {
						if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_ConstantP/90UpperLimit.txt"); }
						if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD2==1 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	if ( run2==1 ) {
		if ( norm2==0 ) {
			if ( PSD2==0 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD2==1 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_ICP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_ICP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm2==1 ) {
			if ( PSD2==0 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_ICPs/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD2==1 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_ICP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_ICP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	
	// FIRST ANALYSIS
	TGraphErrors *g1 = new TGraphErrors(file_g1, "%lg %lg %*lg %*lg %*lg");
	g1->SetLineWidth(2);
	g1->SetMarkerStyle(20);
	if ( det1==0 ) { g1->SetLineColor(kRed+1); g1->SetMarkerColor(kRed+1); }
	if ( det1==1 ) { g1->SetLineColor(kBlue+1); g1->SetMarkerColor(kBlue+1); }
	if ( det1==2 ) { g1->SetLineColor(kGreen+2); g1->SetMarkerColor(kGreen+2); }
	
	// SECOND ANALYSIS
	TGraphErrors *g2 = new TGraphErrors(file_g2, "%lg %lg %*lg %*lg %*lg");
	g2->SetLineWidth(2);
	g2->SetMarkerStyle(20);
	if ( det2==0 ) { g2->SetLineColor(kRed+1); g2->SetMarkerColor(kRed+1); }
	if ( det2==1 ) { g2->SetLineColor(kBlue+1); g2->SetMarkerColor(kBlue+1); }
	if ( det2==2 ) { g2->SetLineColor(kGreen+2); g2->SetMarkerColor(kGreen+2); }
	
	// DRAW
	mg->Add(g1);
	mg->Add(g2);
	mg->GetXaxis()->SetTitle("Mass [keV/c^{2}]");
	mg->GetYaxis()->SetTitle("S [cts/kg*yr]");
	mg->Draw("AL");
	
	// GAMMA LINES
	TLine *line1 = new TLine(238.6, 0, 238.6, y_max);
	line1->SetLineColor(kGray+2);
	line1->SetLineStyle(9);
	line1->Draw();
	TLine *line2 = new TLine(242, 0, 242, y_max);
	line2->SetLineColor(kGray+2);
	line2->SetLineStyle(9);
	line2->Draw();
	TLine *line3 = new TLine(295.2, 0, 295.2, y_max);
	line3->SetLineColor(kGray+2);
	line3->SetLineStyle(9);
	line3->Draw();
	TLine *line4 = new TLine(352, 0, 352, y_max);
	line4->SetLineColor(kGray+2);
	line4->SetLineStyle(9);
	line4->Draw();
	TLine *line12 = new TLine(478.3, 0, 478.3, y_max);
	line12->SetLineColor(kGray+2);
	line12->SetLineStyle(9);
	line12->Draw();
	TLine *line5 = new TLine(511, 0, 511, y_max);
	line5->SetLineColor(kGray+2);
	line5->SetLineStyle(9);
	line5->Draw();
	TLine *line6 = new TLine(514, 0, 514, y_max);
	line6->SetLineColor(kGray+2);
	line6->SetLineStyle(9);
	line6->Draw();
	TLine *line7 = new TLine(583.2, 0, 583.2, y_max);
	line7->SetLineColor(kGray+2);
	line7->SetLineStyle(9);
	line7->Draw();
	TLine *line8 = new TLine(609.3, 0, 609.3, y_max);
	line8->SetLineColor(kGray+2);
	line8->SetLineStyle(9);
	line8->Draw();
	TLine *line9 = new TLine(911.2, 0, 911.2, y_max);
	line9->SetLineColor(kGray+2);
	line9->SetLineStyle(9);
	line9->Draw();
	TLine *line10 = new TLine(969, 0, 969, y_max);
	line10->SetLineColor(kGray+2);
	line10->SetLineStyle(9);
	line10->Draw();
	TLine *line11 = new TLine(thr, 0, thr, y_max);
	line11->SetLineColor(kBlack);
	line11->SetLineWidth(3);
	line11->SetLineStyle(7);
	line11->Draw();
	
	// LEGEND
	auto *legend = new TLegend(.75, .75, .88, .88);
	legend->AddEntry(g1, "First analysis", "l");
	legend->AddEntry(g2, "Second analysis", "l");
	legend->AddEntry(line1, "Background #gamma", "l");
	legend->AddEntry(line11, "Energy threshold (195 keV)", "l");
	legend->Draw();

	return 0;
}
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------
int difference() {

	std::cout << "\n******** FIRST ANALYSIS ********" << std::endl;
	int det1;
	std::cout << "Coax (0), BEGe (1) or IC (2)? ";
	std::cin >> det1;
	int run1;
	std::cout << "\n * Run: 53-93 (0) or 53-114 (1)? ";
	std::cin >> run1;
	int norm1;
	std::cout << " * Normalized (0) or not (1)? ";
	std::cin >> norm1;
	int PSD1;
	std::cout << " * Only PSD (0) or everything (1)? ";
	std::cin >> PSD1;
	int prior1;
	std::cout << " * Prior: coax (0), BEGe (1), IC (2) or constant (3)? ";
	std::cin >> prior1;
	
	std::cout << "\n\n******** SECOND ANALYSIS ********" << std::endl;
	int det2;
	std::cout << "Coax (0), BEGe (1) or IC (2)? ";
	std::cin >> det2;
	int run2;
	std::cout << "\n * Run: 53-93 (0) or 53-114 (1)? ";
	std::cin >> run2;
	int norm2;
	std::cout << " * Normalized (0) or not (1)? ";
	std::cin >> norm2;
	int PSD2;
	std::cout << " * Only PSD (0) or everything (1)? ";
	std::cin >> PSD2;
	int prior2;
	std::cout << " * Prior: coax (0), BEGe (1), IC (2) or constant (3)? ";
	std::cin >> prior2;
	
	TCanvas *c = new TCanvas("c","c",1700,1000);
	int thr = 195;
	double y_max = 40;
	
	char file_g1[100], file_g2[100];
	//========================================================================================================== FIRST ANALYSIS
	if ( run1==0 ) {
		if ( norm1==0 ) {
			if ( PSD1==0 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD1==1 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm1==1 ) {
			if ( PSD1==0 ) {
				if ( prior1==0 ) {
						if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_coaxP/90UpperLimit.txt"); }
						if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
						if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_BEGeP/90UpperLimit.txt"); }
						if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {}
				if ( prior1==3 ) {
						if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD_ConstantP/90UpperLimit.txt"); }
						if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD1==1 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	if ( run1==1 ) {
		if ( norm1==0 ) {
			if ( PSD1==0 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD1==1 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_ICP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_ICP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm1==1 ) {
			if ( PSD1==0 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD1==1 ) {
				if ( prior1==0 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_coaxP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior1==1 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_BEGeP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior1==2 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_ICP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_ICP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior1==3 ) {
					if ( det1==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_ConstantP/90UpperLimit.txt"); }
					if ( det1==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det1==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	//========================================================================================================== SECOND ANALYSIS
	if ( run2==0 ) {
		if ( norm2==0 ) {
			if ( PSD2==0 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD2==1 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm2==1 ) {
			if ( PSD2==0 ) {
				if ( prior2==0 ) {
						if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_coaxP/90UpperLimit.txt"); }
						if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
						if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_BEGeP/90UpperLimit.txt"); }
						if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {}
				if ( prior2==3 ) {
						if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD_ConstantP/90UpperLimit.txt"); }
						if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD2==1 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	if ( run2==1 ) {
		if ( norm2==0 ) {
			if ( PSD2==0 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD2==1 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_ICP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_ICP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
		if ( norm2==1 ) {
			if ( PSD2==0 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_coaxP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_BEGeP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_ICP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_ICP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_ICP/90UpperLimit.txt"); }
				}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD_ConstantP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD_ConstantP/90UpperLimit.txt"); }
				}
			}
			if ( PSD2==1 ) {
				if ( prior2==0 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_coaxP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_coaxP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_coaxP/90UpperLimit.txt"); }
				}
				if ( prior2==1 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_BEGeP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_BEGeP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_BEGeP/90UpperLimit.txt"); }
				}
				if ( prior2==2 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_ICP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_ICP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_ICP/90UpperLimit.txt"); }
				}
				if ( prior2==3 ) {
					if ( det2==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_ConstantP/90UpperLimit.txt"); }
					if ( det2==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_ConstantP/90UpperLimit.txt"); }
					if ( det2==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_ConstantP/90UpperLimit.txt"); }
				}
			}
		}
	}
	
	ifstream file1(file_g1);
	ifstream file2(file_g2);
	
	// DATA OF FIRST ANALYSIS
	Int_t row1 = NumberOfRows(file_g1);
	double data1[row1][5];
	for ( int i=0; i<row1; i++ ) {
		for ( int j=0; j<5; j++ ) {
			file1 >> data1[i][j];
		}
	}
	
	// DATA OF SECOND ANALYSIS
	Int_t row2 = NumberOfRows(file_g2);
	double data2[row2][5];
	for ( int i=0; i<row2; i++ ) {
		for ( int j=0; j<5; j++ ) {
			file2 >> data2[i][j];
		}
	}
	file1.close();
	file2.close();
	
	ofstream file_diff("difference.txt");
	
	// DIFFRENCE OF VALUES (1st - 2nd)
	if ( row1 == row2 ) {
		for ( int i=0; i<row1; i++ ) {
			file_diff << data1[i][0] << "\t" << data1[i][1]-data2[i][1] << std::endl;
		}
	}
	else { std::cout << "Files have different number of rows!" << std::endl; }
	file_diff.close();
	
	// FIRST ANALYSIS
	TGraphErrors *diff = new TGraphErrors("difference.txt");
	diff->SetMarkerStyle(20);
	diff->Draw("AP");
	
	// GAMMA LINES
	TLine *line1 = new TLine(238.6, 0, 238.6, y_max);
	line1->SetLineColor(kGray+2);
	line1->SetLineStyle(9);
	line1->Draw();
	TLine *line2 = new TLine(242, 0, 242, y_max);
	line2->SetLineColor(kGray+2);
	line2->SetLineStyle(9);
	line2->Draw();
	TLine *line3 = new TLine(295.2, 0, 295.2, y_max);
	line3->SetLineColor(kGray+2);
	line3->SetLineStyle(9);
	line3->Draw();
	TLine *line4 = new TLine(352, 0, 352, y_max);
	line4->SetLineColor(kGray+2);
	line4->SetLineStyle(9);
	line4->Draw();
	TLine *line12 = new TLine(478.3, 0, 478.3, y_max);
	line12->SetLineColor(kGray+2);
	line12->SetLineStyle(9);
	line12->Draw();
	TLine *line5 = new TLine(511, 0, 511, y_max);
	line5->SetLineColor(kGray+2);
	line5->SetLineStyle(9);
	line5->Draw();
	TLine *line6 = new TLine(514, 0, 514, y_max);
	line6->SetLineColor(kGray+2);
	line6->SetLineStyle(9);
	line6->Draw();
	TLine *line7 = new TLine(583.2, 0, 583.2, y_max);
	line7->SetLineColor(kGray+2);
	line7->SetLineStyle(9);
	line7->Draw();
	TLine *line8 = new TLine(609.3, 0, 609.3, y_max);
	line8->SetLineColor(kGray+2);
	line8->SetLineStyle(9);
	line8->Draw();
	TLine *line9 = new TLine(911.2, 0, 911.2, y_max);
	line9->SetLineColor(kGray+2);
	line9->SetLineStyle(9);
	line9->Draw();
	TLine *line10 = new TLine(969, 0, 969, y_max);
	line10->SetLineColor(kGray+2);
	line10->SetLineStyle(9);
	line10->Draw();
	TLine *line11 = new TLine(thr, 0, thr, y_max);
	line11->SetLineColor(kBlack);
	line11->SetLineWidth(3);
	line11->SetLineStyle(7);
	line11->Draw();
	
	// LEGEND
	auto *legend = new TLegend(.75, .75, .88, .88);
	legend->AddEntry(diff, "1st - 2nd", "l");
	legend->AddEntry(line1, "Background #gamma", "l");
	legend->AddEntry(line11, "Energy threshold (195 keV)", "l");
	legend->Draw();

	return 0;
}
