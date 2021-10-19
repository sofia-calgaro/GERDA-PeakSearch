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
	
	char file_g1[100], file_g2[100], file_g3[100], file_g4[100];
	
	//========================================================================================================== U90 VS E0
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax_PSD/90UpperLimit.txt"); }
				if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe_PSD/90UpperLimit.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_coax/90UpperLimit.txt"); }
				if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_NORM_BEGe/90UpperLimit.txt"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax_PSD/90UpperLimit_norm.txt"); }
				if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe_PSD/90UpperLimit_norm.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_93_coax/90UpperLimit_norm.txt"); }
				if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_93_BEGe/90UpperLimit_norm.txt"); }
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax_PSD/90UpperLimit.txt"); }
				if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe_PSD/90UpperLimit.txt"); }
				if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC_PSD/90UpperLimit.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_coax/90UpperLimit.txt"); }
				if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_BEGe/90UpperLimit.txt"); }
				if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_NORM_IC/90UpperLimit.txt"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax_PSD/90UpperLimit_norm.txt"); }
				if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe_PSD/90UpperLimit_norm.txt"); }
				if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC_PSD/90UpperLimit_norm.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g1, "ReadJSON/53_114_coax/90UpperLimit_norm.txt"); }
				if ( det==1 ) { sprintf(file_g1, "ReadJSON/53_114_BEGe/90UpperLimit_norm.txt"); }
				if ( det==2 ) { sprintf(file_g1, "ReadJSON/53_114_IC/90UpperLimit_norm.txt"); }
			}
		}
	}
	std::cout << file_g1 << std::endl;
	int thr=0;
	double y_max=0;
	if ( det==0 ) { thr = 195; y_max=35;}	
	if ( det==1 ) { thr = 195; y_max = 770; y_max=35; }
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
				if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD/counts_VS_E0.png"); }
				if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD/counts_VS_E0.png"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_coax/counts_VS_E0.png"); }
				if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_NORM_BEGe/counts_VS_E0.png"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_coax_PSD/counts_VS_E0.png"); }
				if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_BEGe_PSD/counts_VS_E0.png"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_93_coax/counts_VS_E0.png"); }
				if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_93_BEGe/counts_VS_E0.png"); }
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD/counts_VS_E0.png"); }
				if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD/counts_VS_E0.png"); }
				if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD/counts_VS_E0.png"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_coax/counts_VS_E0.png"); }
				if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_BEGe/counts_VS_E0.png"); }
				if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_NORM_IC/counts_VS_E0.png"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax_PSD/counts_VS_E0.png"); }
				if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe_PSD/counts_VS_E0.png"); }
				if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC_PSD/counts_VS_E0.png"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { c1->SaveAs("Par_VS_E0/53_114_coax/counts_VS_E0.png"); }
				if ( det==1 ) { c1->SaveAs("Par_VS_E0/53_114_BEGe/counts_VS_E0.png"); }
				if ( det==2 ) { c1->SaveAs("Par_VS_E0/53_114_IC/counts_VS_E0.png"); }
			}
		}
	}

	//========================================================================================================== p0 VS E0
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax_PSD/p0_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe_PSD/p0_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_coax/p0_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_NORM_BEGe/p0_VS_E0.txt"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax_PSD/p0_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe_PSD/p0_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_93_coax/p0_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_93_BEGe/p0_VS_E0.txt"); }
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax_PSD/p0_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe_PSD/p0_VS_E0.txt"); }
				if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC_PSD/p0_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_coax/p0_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_BEGe/p0_VS_E0.txt"); }
				if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_NORM_IC/p0_VS_E0.txt"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax_PSD/p0_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe_PSD/p0_VS_E0.txt"); }
				if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC_PSD/p0_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g2, "ReadJSON/53_114_coax/p0_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g2, "ReadJSON/53_114_BEGe/p0_VS_E0.txt"); }
				if ( det==2 ) { sprintf(file_g2, "ReadJSON/53_114_IC/p0_VS_E0.txt"); }
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
				if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD/p0_VS_E0.png"); }
				if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD/p0_VS_E0.png"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_coax/p0_VS_E0.png"); }
				if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_NORM_BEGe/p0_VS_E0.png"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_coax_PSD/p0_VS_E0.png"); }
				if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_BEGe_PSD/p0_VS_E0.png"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_93_coax/p0_VS_E0.png"); }
				if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_93_BEGe/p0_VS_E0.png"); }
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD/p0_VS_E0.png"); }
				if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD/p0_VS_E0.png"); }
				if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD/p0_VS_E0.png"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_coax/p0_VS_E0.png"); }
				if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_BEGe/p0_VS_E0.png"); }
				if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_NORM_IC/p0_VS_E0.png"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax_PSD/p0_VS_E0.png"); }
				if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe_PSD/p0_VS_E0.png"); }
				if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC_PSD/p0_VS_E0.png"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { c2->SaveAs("Par_VS_E0/53_114_coax/p0_VS_E0.png"); }
				if ( det==1 ) { c2->SaveAs("Par_VS_E0/53_114_BEGe/p0_VS_E0.png"); }
				if ( det==2 ) { c2->SaveAs("Par_VS_E0/53_114_IC/p0_VS_E0.png"); }
			}
		}
	}
	
	//================================================================================================== p1 VS E0
	ifstream file3;
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { file3.open("ReadJSON/53_93_NORM_coax_PSD/p1_VS_E0.txt"); }
				if ( det==1 ) { file3.open("ReadJSON/53_93_NORM_BEGe_PSD/p1_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { file3.open("ReadJSON/53_93_NORM_coax/p1_VS_E0.txt"); }
				if ( det==1 ) { file3.open("ReadJSON/53_93_NORM_BEGe/p1_VS_E0.txt"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { file3.open("ReadJSON/53_93_coax_PSD/p1_VS_E0.txt"); }
				if ( det==1 ) { file3.open("ReadJSON/53_93_BEGe_PSD/p1_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { file3.open("ReadJSON/53_93_coax/p1_VS_E0.txt"); }
				if ( det==1 ) { file3.open("ReadJSON/53_93_BEGe/p1_VS_E0.txt"); }
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax_PSD/p1_VS_E0.txt"); }
				if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe_PSD/p1_VS_E0.txt"); }
				if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC_PSD/p1_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { file3.open("ReadJSON/53_114_NORM_coax/p1_VS_E0.txt"); }
				if ( det==1 ) { file3.open("ReadJSON/53_114_NORM_BEGe/p1_VS_E0.txt"); }
				if ( det==2 ) { file3.open("ReadJSON/53_114_NORM_IC/p1_VS_E0.txt"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { file3.open("ReadJSON/53_114_coax_PSD/p1_VS_E0.txt"); }
				if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe_PSD/p1_VS_E0.txt"); }
				if ( det==2 ) { file3.open("ReadJSON/53_114_IC_PSD/p1_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { file3.open("ReadJSON/53_114_coax/p1_VS_E0.txt"); }
				if ( det==1 ) { file3.open("ReadJSON/53_114_BEGe/p1_VS_E0.txt"); }
				if ( det==2 ) { file3.open("ReadJSON/53_114_IC/p1_VS_E0.txt"); }
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
					if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD/p1_VS_E0.png"); }
					if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD/p1_VS_E0.png"); }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_coax/p1_VS_E0.png"); }
					if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_NORM_BEGe/p1_VS_E0.png"); }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_coax_PSD/p1_VS_E0.png"); }
					if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_BEGe_PSD/p1_VS_E0.png"); }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_93_coax/p1_VS_E0.png"); }
					if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_93_BEGe/p1_VS_E0.png"); }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD/p1_VS_E0.png"); }
					if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD/p1_VS_E0.png"); }
					if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD/p1_VS_E0.png"); }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_coax/p1_VS_E0.png"); }
					if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_BEGe/p1_VS_E0.png"); }
					if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_NORM_IC/p1_VS_E0.png"); }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax_PSD/p1_VS_E0.png"); }
					if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe_PSD/p1_VS_E0.png"); }
					if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC_PSD/p1_VS_E0.png"); }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { c3->SaveAs("Par_VS_E0/53_114_coax/p1_VS_E0.png"); }
					if ( det==1 ) { c3->SaveAs("Par_VS_E0/53_114_BEGe/p1_VS_E0.png"); }
					if ( det==2 ) { c3->SaveAs("Par_VS_E0/53_114_IC/p1_VS_E0.png"); }
				}
			}
		}
	}
	
	//================================================================================================== p2 VS E0
	if ( run==0 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_coax_PSD/p2_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_BEGe_PSD/p2_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_coax/p2_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_NORM_BEGe/p2_VS_E0.txt"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_coax_PSD/p2_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_BEGe_PSD/p2_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_93_coax/p2_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_93_BEGe/p2_VS_E0.txt"); }
			}
		}
	}
	if ( run==1 ) {
		if ( norm==0 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax_PSD/p2_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe_PSD/p2_VS_E0.txt"); }
				if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC_PSD/p2_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_coax/p2_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_BEGe/p2_VS_E0.txt"); }
				if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_NORM_IC/p2_VS_E0.txt"); }
			}
		}
		if ( norm==1 ) {
			if ( PSD==0 ) {
				if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax_PSD/p2_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe_PSD/p2_VS_E0.txt"); }
				if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC_PSD/p2_VS_E0.txt"); }
			}
			if ( PSD==1 ) {
				if ( det==0 ) { sprintf(file_g4, "ReadJSON/53_114_coax/p2_VS_E0.txt"); }
				if ( det==1 ) { sprintf(file_g4, "ReadJSON/53_114_BEGe/p2_VS_E0.txt"); }
				if ( det==2 ) { sprintf(file_g4, "ReadJSON/53_114_IC/p2_VS_E0.txt"); }
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
					if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_coax_PSD/p2_VS_E0.png"); }
					if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_BEGe_PSD/p2_VS_E0.png"); }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_coax/p2_VS_E0.png"); }
					if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_NORM_BEGe/p2_VS_E0.png"); }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_coax_PSD/p2_VS_E0.png"); }
					if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_BEGe_PSD/p2_VS_E0.png"); }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_93_coax/p2_VS_E0.png"); }
					if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_93_BEGe/p2_VS_E0.png"); }
				}
			}
		}
		if ( run==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax_PSD/p2_VS_E0.png"); }
					if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe_PSD/p2_VS_E0.png"); }
					if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC_PSD/p2_VS_E0.png"); }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_coax/p2_VS_E0.png"); }
					if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_BEGe/p2_VS_E0.png"); }
					if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_NORM_IC/p2_VS_E0.png"); }
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax_PSD/p2_VS_E0.png"); }
					if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe_PSD/p2_VS_E0.png"); }
					if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC_PSD/p2_VS_E0.png"); }
				}
				if ( PSD==1 ) {
					if ( det==0 ) { c4->SaveAs("Par_VS_E0/53_114_coax/p2_VS_E0.png"); }
					if ( det==1 ) { c4->SaveAs("Par_VS_E0/53_114_BEGe/p2_VS_E0.png"); }
					if ( det==2 ) { c4->SaveAs("Par_VS_E0/53_114_IC/p2_VS_E0.png"); }
				}
			}
		}
	}

	return 0;
}
