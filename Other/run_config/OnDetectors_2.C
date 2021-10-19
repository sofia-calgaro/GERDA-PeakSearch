int phII() {

	TCanvas *c = new TCanvas();
	c->SetGridx();
	TGraphErrors *g_lim = new TGraphErrors("phII_limits_canvas.txt");
	g_lim->SetMarkerStyle(20);
	g_lim->SetMarkerColor(0);
	g_lim->SetMarkerSize(0);
	g_lim->SetLineWidth(0);
	g_lim->GetXaxis()->SetTitle("# run");
	g_lim->GetYaxis()->SetTitle("# channel");
	g_lim->SetTitle("ON detectors ( phase II )");
	g_lim->Draw("AP");
	
	// ch 0
	TLine *l0_0 = new TLine(53, 0, 66, 0);
	l0_0->SetLineColor(kBlue);
	l0_0->SetLineWidth(4);
	l0_0->Draw();
	TLine *l0_1 = new TLine(69, 0, 80, 0);
	l0_1->SetLineColor(kBlue);
	l0_1->SetLineWidth(4);
	l0_1->Draw();
	TLine *l0_2 = new TLine(83, 0, 94, 0);
	l0_2->SetLineColor(kBlue);
	l0_2->SetLineWidth(4);
	l0_2->Draw();
	TLine *l0_3 = new TLine(67, 0, 68, 0);
	l0_3->SetLineColor(kBlue);
	l0_3->SetLineWidth(4);
	l0_3->Draw();
	
	// ch 1
	TLine *l1_0 = new TLine(53, 1, 66, 1);
	l1_0->SetLineColor(kBlue);
	l1_0->SetLineWidth(4);
	l1_0->Draw();
	TLine *l1_1 = new TLine(69, 1, 80, 1);
	l1_1->SetLineColor(kBlue);
	l1_1->SetLineWidth(4);
	l1_1->Draw();
	TLine *l1_2 = new TLine(83, 1, 94, 1);
	l1_2->SetLineColor(kBlue);
	l1_2->SetLineWidth(4);
	l1_2->Draw();
	TLine *l1_3 = new TLine(67, 1, 68, 1);
	l1_3->SetLineColor(kBlue);
	l1_3->SetLineWidth(4);
	l1_3->Draw();
	
	// ch 2
	TLine *l2_0 = new TLine(53, 2, 66, 2);
	l2_0->SetLineColor(kBlue);
	l2_0->SetLineWidth(4);
	l2_0->Draw();
	TLine *l2_1 = new TLine(69, 2, 80, 2);
	l2_1->SetLineColor(kBlue);
	l2_1->SetLineWidth(4);
	l2_1->Draw();
	TLine *l2_2 = new TLine(83, 2, 94, 2);
	l2_2->SetLineColor(kBlue);
	l2_2->SetLineWidth(4);
	l2_2->Draw();
	TLine *l2_3 = new TLine(67, 2, 68, 2);
	l2_3->SetLineColor(kBlue);
	l2_3->SetLineWidth(4);
	l2_3->Draw();
	
	// ch 3
	TLine *l3_0 = new TLine(54, 3, 66, 3);
	l3_0->SetLineColor(kBlue);
	l3_0->SetLineWidth(4);
	l3_0->Draw();
	TLine *l3_1 = new TLine(69, 3, 80, 3);
	l3_1->SetLineColor(kBlue);
	l3_1->SetLineWidth(4);
	l3_1->Draw();
	TLine *l3_2 = new TLine(83, 3, 94, 3);
	l3_2->SetLineColor(kBlue);
	l3_2->SetLineWidth(4);
	l3_2->Draw();
	TLine *l3_3 = new TLine(67, 3, 68, 3);
	l3_3->SetLineColor(kBlue);
	l3_3->SetLineWidth(4);
	l3_3->Draw();
	
	// ch 4
	TLine *l4_0 = new TLine(53, 4, 54, 4);
	l4_0->SetLineColor(kBlue);
	l4_0->SetLineWidth(4);
	l4_0->Draw();
	TLine *l4_1 = new TLine(69, 4, 80, 4);
	l4_1->SetLineColor(kBlue);
	l4_1->SetLineWidth(4);
	l4_1->Draw();
	TLine *l4_2 = new TLine(83, 4, 94, 4);
	l4_2->SetLineColor(kBlue);
	l4_2->SetLineWidth(4);
	l4_2->Draw();
	TLine *l4_3 = new TLine(53, 4, 54, 4);
	l4_3->SetLineColor(kBlue);
	l4_3->SetLineWidth(4);
	l4_3->Draw();
	TLine *l4_4 = new TLine(67, 4, 68, 4);
	l4_4->SetLineColor(kBlue);
	l4_4->SetLineWidth(4);
	l4_4->Draw();
	TLine *l4_5 = new TLine(55, 4, 66, 4);
	l4_5->SetLineColor(kBlue);
	l4_5->SetLineWidth(4);
	l4_5->Draw();
	
	// ch 5
	TLine *l5_0 = new TLine(55, 5, 66, 5);
	l5_0->SetLineColor(kBlue);
	l5_0->SetLineWidth(4);
	l5_0->Draw();
	TLine *l5_1 = new TLine(69, 5, 80, 5);
	l5_1->SetLineColor(kBlue);
	l5_1->SetLineWidth(4);
	l5_1->Draw();
	TLine *l5_2 = new TLine(53, 5, 54, 5);
	l5_2->SetLineColor(kBlue);
	l5_2->SetLineWidth(4);
	l5_2->Draw();
	TLine *l5_3 = new TLine(67, 5, 68, 5);
	l5_3->SetLineColor(kBlue);
	l5_3->SetLineWidth(4);
	l5_3->Draw();
	
	// ch 6
	TLine *l6_0 = new TLine(55, 6, 66, 6);
	l6_0->SetLineColor(kBlue);
	l6_0->SetLineWidth(4);
	l6_0->Draw();
	TLine *l6_1 = new TLine(69, 6, 80, 6);
	l6_1->SetLineColor(kBlue);
	l6_1->SetLineWidth(4);
	l6_1->Draw();
	TLine *l6_2 = new TLine(53, 6, 54, 6);
	l6_2->SetLineColor(kBlue);
	l6_2->SetLineWidth(4);
	l6_2->Draw();
	TLine *l6_3 = new TLine(67, 6, 68, 6);
	l6_3->SetLineColor(kBlue);
	l6_3->SetLineWidth(4);
	l6_3->Draw();
	
	// ch 7
	TLine *l7_0 = new TLine(55, 7, 66, 7);
	l7_0->SetLineColor(kBlue);
	l7_0->SetLineWidth(4);
	l7_0->Draw();
	TLine *l7_2 = new TLine(53, 7, 54, 7);
	l7_2->SetLineColor(kBlue);
	l7_2->SetLineWidth(4);
	l7_2->Draw();
	TLine *l7_3 = new TLine(67, 7, 68, 7);
	l7_3->SetLineColor(kBlue);
	l7_3->SetLineWidth(4);
	l7_3->Draw();
	
	// ch 8
	TLine *l8_0 = new TLine(55, 8, 66, 8);
	l8_0->SetLineColor(kRed);
	l8_0->SetLineWidth(4);
	l8_0->Draw();
	TLine *l8_1 = new TLine(69, 8, 80, 8);
	l8_1->SetLineColor(kRed);
	l8_1->SetLineWidth(4);
	l8_1->Draw();
	TLine *l8_2 = new TLine(83, 8, 94, 8);
	l8_2->SetLineColor(kRed);
	l8_2->SetLineWidth(4);
	l8_2->Draw();
	TLine *l8_4 = new TLine(67, 8, 68, 8);
	l8_4->SetLineColor(kRed);
	l8_4->SetLineWidth(4);
	l8_4->Draw();
	
	// ch 9
	TLine *l9_0 = new TLine(54, 9, 66, 9);
	l9_0->SetLineColor(kRed);
	l9_0->SetLineWidth(4);
	l9_0->Draw();
	TLine *l9_1 = new TLine(69, 9, 80, 9);
	l9_1->SetLineColor(kRed);
	l9_1->SetLineWidth(4);
	l9_1->Draw();
	TLine *l9_2 = new TLine(83, 9, 94, 9);
	l9_2->SetLineColor(kRed);
	l9_2->SetLineWidth(4);
	l9_2->Draw();
	TLine *l9_4 = new TLine(67, 9, 68, 9);
	l9_4->SetLineColor(kRed);
	l9_4->SetLineWidth(4);
	l9_4->Draw();
	
	// ch 10
	TLine *l10_0 = new TLine(53, 10, 66, 10);
	l10_0->SetLineColor(kRed);
	l10_0->SetLineWidth(4);
	l10_0->Draw();
	TLine *l10_1 = new TLine(69, 10, 80, 10);
	l10_1->SetLineColor(kRed);
	l10_1->SetLineWidth(4);
	l10_1->Draw();
	TLine *l10_2 = new TLine(83, 10, 94, 10);
	l10_2->SetLineColor(kRed);
	l10_2->SetLineWidth(4);
	l10_2->Draw();
	TLine *l10_3 = new TLine(53, 10, 54, 10);
	l10_3->SetLineColor(kRed);
	l10_3->SetLineWidth(4);
	l10_3->Draw();
	TLine *l10_4 = new TLine(67, 10, 68, 10);
	l10_4->SetLineColor(kRed);
	l10_4->SetLineWidth(4);
	l10_4->Draw();
	
	// ch 11
	TLine *l11_0 = new TLine(53, 11, 66, 11);
	l11_0->SetLineColor(kBlue);
	l11_0->SetLineWidth(4);
	l11_0->Draw();
	TLine *l11_1 = new TLine(69, 11, 80, 11);
	l11_1->SetLineColor(kBlue);
	l11_1->SetLineWidth(4);
	l11_1->Draw();
	TLine *l11_2 = new TLine(67, 11, 68, 11);
	l11_2->SetLineColor(kBlue);
	l11_2->SetLineWidth(4);
	l11_2->Draw();
	TLine *l11_3 = new TLine(83, 11, 94, 11);
	l11_3->SetLineColor(kBlue);
	l11_3->SetLineWidth(4);
	l11_3->Draw();
	
	// ch 12
	TLine *l12_0 = new TLine(54, 12, 66, 12);
	l12_0->SetLineColor(kBlue);
	l12_0->SetLineWidth(4);
	l12_0->Draw();
	TLine *l12_1 = new TLine(69, 12, 80, 12);
	l12_1->SetLineColor(kBlue);
	l12_1->SetLineWidth(4);
	l12_1->Draw();
	TLine *l12_2 = new TLine(67, 12, 68, 12);
	l12_2->SetLineColor(kBlue);
	l12_2->SetLineWidth(4);
	l12_2->Draw();
	TLine *l12_3 = new TLine(83, 12, 94, 12);
	l12_3->SetLineColor(kBlue);
	l12_3->SetLineWidth(4);
	l12_3->Draw();
	
	// ch 13
	TLine *l13_0 = new TLine(53, 13, 66, 13);
	l13_0->SetLineColor(kBlue);
	l13_0->SetLineWidth(4);
	l13_0->Draw();
	TLine *l13_1 = new TLine(69, 13, 80, 13);
	l13_1->SetLineColor(kBlue);
	l13_1->SetLineWidth(4);
	l13_1->Draw();
	TLine *l13_2 = new TLine(67, 13, 68, 13);
	l13_2->SetLineColor(kBlue);
	l13_2->SetLineWidth(4);
	l13_2->Draw();
	TLine *l13_3 = new TLine(83, 13, 84, 13);
	l13_3->SetLineColor(kBlue);
	l13_3->SetLineWidth(4);
	l13_3->Draw();
	TLine *l13_4 = new TLine(87, 13, 90, 13);
	l13_4->SetLineColor(kBlue);
	l13_4->SetLineWidth(4);
	l13_4->Draw();
	TLine *l13_5 = new TLine(91, 13, 94, 13);
	l13_5->SetLineColor(kBlue);
	l13_5->SetLineWidth(4);
	l13_5->Draw();
	
	// ch 14
	TLine *l14_0 = new TLine(53, 14, 66, 14);
	l14_0->SetLineColor(kBlue);
	l14_0->SetLineWidth(4);
	l14_0->Draw();
	TLine *l14_1 = new TLine(69, 14, 80, 14);
	l14_1->SetLineColor(kBlue);
	l14_1->SetLineWidth(4);
	l14_1->Draw();
	TLine *l14_2 = new TLine(67, 14, 68, 14);
	l14_2->SetLineColor(kBlue);
	l14_2->SetLineWidth(4);
	l14_2->Draw();
	TLine *l14_3 = new TLine(83, 14, 94, 14);
	l14_3->SetLineColor(kBlue);
	l14_3->SetLineWidth(4);
	l14_3->Draw();
	
	// ch 15
	TLine *l15_0 = new TLine(53, 15, 66, 15);
	l15_0->SetLineColor(kBlue);
	l15_0->SetLineWidth(4);
	l15_0->Draw();
	TLine *l15_1 = new TLine(69, 15, 80, 15);
	l15_1->SetLineColor(kBlue);
	l15_1->SetLineWidth(4);
	l15_1->Draw();
	TLine *l15_2 = new TLine(67, 15, 68, 15);
	l15_2->SetLineColor(kBlue);
	l15_2->SetLineWidth(4);
	l15_2->Draw();
	TLine *l15_3 = new TLine(83, 15, 84, 15);
	l15_3->SetLineColor(kBlue);
	l15_3->SetLineWidth(4);
	l15_3->Draw();
	TLine *l15_4 = new TLine(85, 15, 94, 15);
	l15_4->SetLineColor(kBlue);
	l15_4->SetLineWidth(4);
	l15_4->Draw();
	
	// ch 16
	TLine *l16_0 = new TLine(54, 16, 66, 16);
	l16_0->SetLineColor(kBlue);
	l16_0->SetLineWidth(4);
	l16_0->Draw();
	TLine *l16_1 = new TLine(69, 16, 77, 16);
	l16_1->SetLineColor(kBlue);
	l16_1->SetLineWidth(4);
	l16_1->Draw();
	TLine *l16_2 = new TLine(67, 16, 68, 16);
	l16_2->SetLineColor(kBlue);
	l16_2->SetLineWidth(4);
	l16_2->Draw();
	TLine *l16_3 = new TLine(78, 16, 80, 16);
	l16_3->SetLineColor(kBlue);
	l16_3->SetLineWidth(4);
	l16_3->Draw();
	TLine *l16_4 = new TLine(83, 16, 94, 16);
	l16_4->SetLineColor(kBlue);
	l16_4->SetLineWidth(4);
	l16_4->Draw();
	
	// ch 17
	TLine *l17_0 = new TLine(53, 17, 66, 17);
	l17_0->SetLineColor(kBlue);
	l17_0->SetLineWidth(4);
	l17_0->Draw();
	TLine *l17_1 = new TLine(69, 17, 80, 17);
	l17_1->SetLineColor(kBlue);
	l17_1->SetLineWidth(4);
	l17_1->Draw();
	TLine *l17_2 = new TLine(67, 17, 68, 17);
	l17_2->SetLineColor(kBlue);
	l17_2->SetLineWidth(4);
	l17_2->Draw();
	TLine *l17_3 = new TLine(83, 17, 94, 17);
	l17_3->SetLineColor(kBlue);
	l17_3->SetLineWidth(4);
	l17_3->Draw();
	
	// ch 18
	TLine *l18_0 = new TLine(54, 18, 66, 18);
	l18_0->SetLineColor(kBlue);
	l18_0->SetLineWidth(4);
	l18_0->Draw();
	TLine *l18_1 = new TLine(69, 18, 80, 18);
	l18_1->SetLineColor(kBlue);
	l18_1->SetLineWidth(4);
	l18_1->Draw();
	TLine *l18_2 = new TLine(67, 18, 68, 18);
	l18_2->SetLineColor(kBlue);
	l18_2->SetLineWidth(4);
	l18_2->Draw();
	TLine *l18_3 = new TLine(83, 18, 94, 18);
	l18_3->SetLineColor(kBlue);
	l18_3->SetLineWidth(4);
	l18_3->Draw();
	
	// ch 19
	TLine *l19_0 = new TLine(53, 19, 66, 19);
	l19_0->SetLineColor(kBlue);
	l19_0->SetLineWidth(4);
	l19_0->Draw();
	TLine *l19_1 = new TLine(69, 19, 80, 19);
	l19_1->SetLineColor(kBlue);
	l19_1->SetLineWidth(4);
	l19_1->Draw();
	TLine *l19_2 = new TLine(67, 19, 68, 19);
	l19_2->SetLineColor(kBlue);
	l19_2->SetLineWidth(4);
	l19_2->Draw();
	TLine *l19_4 = new TLine(83, 19, 94, 19);
	l19_4->SetLineColor(kBlue);
	l19_4->SetLineWidth(4);
	l19_4->Draw();
	
	// ch 20
	TLine *l20_0 = new TLine(53, 20, 66, 20);
	l20_0->SetLineColor(kBlue);
	l20_0->SetLineWidth(4);
	l20_0->Draw();
	TLine *l20_1 = new TLine(69, 20, 80, 20);
	l20_1->SetLineColor(kBlue);
	l20_1->SetLineWidth(4);
	l20_1->Draw();
	TLine *l20_2 = new TLine(67, 20, 68, 20);
	l20_2->SetLineColor(kBlue);
	l20_2->SetLineWidth(4);
	l20_2->Draw();
	TLine *l20_4 = new TLine(83, 20, 94, 20);
	l20_4->SetLineColor(kBlue);
	l20_4->SetLineWidth(4);
	l20_4->Draw();
	
	// ch 21
	TLine *l21_0 = new TLine(53, 21, 66, 21);
	l21_0->SetLineColor(kBlue);
	l21_0->SetLineWidth(4);
	l21_0->Draw();
	TLine *l21_1 = new TLine(69, 21, 80, 21);
	l21_1->SetLineColor(kBlue);
	l21_1->SetLineWidth(4);
	l21_1->Draw();
	TLine *l21_2 = new TLine(67, 21, 68, 21);
	l21_2->SetLineColor(kBlue);
	l21_2->SetLineWidth(4);
	l21_2->Draw();
	TLine *l21_4 = new TLine(83, 21, 94, 21);
	l21_4->SetLineColor(kBlue);
	l21_4->SetLineWidth(4);
	l21_4->Draw();
	
	// ch 22
	TLine *l22_0 = new TLine(53, 22, 66, 22);
	l22_0->SetLineColor(kBlue);
	l22_0->SetLineWidth(4);
	l22_0->Draw();
	TLine *l22_1 = new TLine(69, 22, 80, 22);
	l22_1->SetLineColor(kBlue);
	l22_1->SetLineWidth(4);
	l22_1->Draw();
	TLine *l22_2 = new TLine(67, 22, 68, 22);
	l22_2->SetLineColor(kBlue);
	l22_2->SetLineWidth(4);
	l22_2->Draw();
	TLine *l22_4 = new TLine(83, 22, 94, 22);
	l22_4->SetLineColor(kBlue);
	l22_4->SetLineWidth(4);
	l22_4->Draw();
	
	// ch 23
	TLine *l23_0 = new TLine(54, 23, 55, 23);
	l23_0->SetLineColor(kBlue);
	l23_0->SetLineWidth(4);
	l23_0->Draw();
	TLine *l23_1 = new TLine(62, 23, 66, 23);
	l23_1->SetLineColor(kBlue);
	l23_1->SetLineWidth(4);
	l23_1->Draw();
	TLine *l23_2 = new TLine(67, 23, 68, 23);
	l23_2->SetLineColor(kBlue);
	l23_2->SetLineWidth(4);
	l23_2->Draw();
	TLine *l23_4 = new TLine(69, 23, 70, 23);
	l23_4->SetLineColor(kBlue);
	l23_4->SetLineWidth(4);
	l23_4->Draw();
	TLine *l23_5 = new TLine(72, 23, 80, 23);
	l23_5->SetLineColor(kBlue);
	l23_5->SetLineWidth(4);
	l23_5->Draw();
	TLine *l23_6 = new TLine(83, 23, 94, 23);
	l23_6->SetLineColor(kBlue);
	l23_6->SetLineWidth(4);
	l23_6->Draw();
	
	// ch 24
	TLine *l24_0 = new TLine(53, 24, 66, 24);
	l24_0->SetLineColor(kBlue);
	l24_0->SetLineWidth(4);
	l24_0->Draw();
	TLine *l24_1 = new TLine(69, 24, 80, 24);
	l24_1->SetLineColor(kBlue);
	l24_1->SetLineWidth(4);
	l24_1->Draw();
	TLine *l24_2 = new TLine(67, 24, 68, 24);
	l24_2->SetLineColor(kBlue);
	l24_2->SetLineWidth(4);
	l24_2->Draw();
	TLine *l24_4 = new TLine(83, 24, 94, 24);
	l24_4->SetLineColor(kBlue);
	l24_4->SetLineWidth(4);
	l24_4->Draw();
	
	// ch 25
	TLine *l25_0 = new TLine(54, 25, 66, 25);
	l25_0->SetLineColor(kBlue);
	l25_0->SetLineWidth(4);
	l25_0->Draw();
	TLine *l25_2 = new TLine(67, 25, 68, 25);
	l25_2->SetLineColor(kBlue);
	l25_2->SetLineWidth(4);
	l25_2->Draw();
	TLine *l25_4 = new TLine(70, 25, 80, 25);
	l25_4->SetLineColor(kBlue);
	l25_4->SetLineWidth(4);
	l25_4->Draw();
	TLine *l25_6 = new TLine(83, 25, 94, 25);
	l25_6->SetLineColor(kBlue);
	l25_6->SetLineWidth(4);
	l25_6->Draw();
	
	// ch 26
	TLine *l26_0 = new TLine(54, 26, 66, 26);
	l26_0->SetLineColor(kBlue);
	l26_0->SetLineWidth(4);
	l26_0->Draw();
	TLine *l26_3 = new TLine(74, 26, 80, 26);
	l26_3->SetLineColor(kBlue);
	l26_3->SetLineWidth(4);
	l26_3->Draw();
	TLine *l26_4 = new TLine(69, 26, 70, 26);
	l26_4->SetLineColor(kBlue);
	l26_4->SetLineWidth(4);
	l26_4->Draw();
	TLine *l26_5 = new TLine(72, 26, 73, 26);
	l26_5->SetLineColor(kBlue);
	l26_5->SetLineWidth(4);
	l26_5->Draw();
	TLine *l26_6 = new TLine(83, 26, 94, 26);
	l26_6->SetLineColor(kBlue);
	l26_6->SetLineWidth(4);
	l26_6->Draw();
	
	// ch 27
	TLine *l27_0 = new TLine(54, 27, 61, 27);
	l27_0->SetLineColor(kRed);
	l27_0->SetLineWidth(4);
	l27_0->Draw();
	TLine *l27_2 = new TLine(62, 27, 66, 27);
	l27_2->SetLineColor(kRed);
	l27_2->SetLineWidth(4);
	l27_2->Draw();
	TLine *l27_3 = new TLine(69, 27, 70, 27);
	l27_3->SetLineColor(kRed);
	l27_3->SetLineWidth(4);
	l27_3->Draw();
	TLine *l27_4 = new TLine(72, 27, 80, 27);
	l27_4->SetLineColor(kRed);
	l27_4->SetLineWidth(4);
	l27_4->Draw();
	TLine *l27_5 = new TLine(83, 27, 94, 27);
	l27_5->SetLineColor(kRed);
	l27_5->SetLineWidth(4);
	l27_5->Draw();
	
	// ch 28
	TLine *l28_0 = new TLine(54, 28, 66, 28);
	l28_0->SetLineColor(kRed);
	l28_0->SetLineWidth(4);
	l28_0->Draw();
	TLine *l28_2 = new TLine(67, 28, 68, 28);
	l28_2->SetLineColor(kRed);
	l28_2->SetLineWidth(4);
	l28_2->Draw();
	TLine *l28_3 = new TLine(69, 28, 80, 28);
	l28_3->SetLineColor(kRed);
	l28_3->SetLineWidth(4);
	l28_3->Draw();
	TLine *l28_4 = new TLine(83, 28, 94, 28);
	l28_4->SetLineColor(kRed);
	l28_4->SetLineWidth(4);
	l28_4->Draw();
	
	// ch 29
	TLine *l29_0 = new TLine(53, 29, 66, 29);
	l29_0->SetLineColor(kRed);
	l29_0->SetLineWidth(4);
	l29_0->Draw();
	TLine *l29_2 = new TLine(67, 29, 68, 29);
	l29_2->SetLineColor(kRed);
	l29_2->SetLineWidth(4);
	l29_2->Draw();
	TLine *l29_3 = new TLine(69, 29, 80, 29);
	l29_3->SetLineColor(kRed);
	l29_3->SetLineWidth(4);
	l29_3->Draw();
	TLine *l29_4 = new TLine(83, 29, 94, 29);
	l29_4->SetLineColor(kRed);
	l29_4->SetLineWidth(4);
	l29_4->Draw();
	
	// ch 30
	TLine *l30_0 = new TLine(53, 30, 66, 30);
	l30_0->SetLineColor(kBlue);
	l30_0->SetLineWidth(4);
	l30_0->Draw();
	TLine *l30_2 = new TLine(67, 30, 68, 30);
	l30_2->SetLineColor(kBlue);
	l30_2->SetLineWidth(4);
	l30_2->Draw();
	TLine *l30_3 = new TLine(69, 30, 80, 30);
	l30_3->SetLineColor(kBlue);
	l30_3->SetLineWidth(4);
	l30_3->Draw();
	TLine *l30_4 = new TLine(83, 30, 94, 30);
	l30_4->SetLineColor(kBlue);
	l30_4->SetLineWidth(4);
	l30_4->Draw();
	
	// ch 31
	TLine *l31_0 = new TLine(54, 31, 66, 31);
	l31_0->SetLineColor(kBlue);
	l31_0->SetLineWidth(4);
	l31_0->Draw();
	TLine *l31_2 = new TLine(67, 31, 68, 31);
	l31_2->SetLineColor(kBlue);
	l31_2->SetLineWidth(4);
	l31_2->Draw();
	TLine *l31_3 = new TLine(69, 31, 80, 31);
	l31_3->SetLineColor(kBlue);
	l31_3->SetLineWidth(4);
	l31_3->Draw();
	TLine *l31_4 = new TLine(83, 31, 94, 31);
	l31_4->SetLineColor(kBlue);
	l31_4->SetLineWidth(4);
	l31_4->Draw();
	
	// ch 32
	TLine *l32_0 = new TLine(54, 32, 59, 32);
	l32_0->SetLineColor(kBlue);
	l32_0->SetLineWidth(4);
	l32_0->Draw();
	TLine *l32_2 = new TLine(61, 32, 63, 32);
	l32_2->SetLineColor(kBlue);
	l32_2->SetLineWidth(4);
	l32_2->Draw();
	TLine *l32_3 = new TLine(70, 32, 80, 32);
	l32_3->SetLineColor(kBlue);
	l32_3->SetLineWidth(4);
	l32_3->Draw();
	TLine *l32_4 = new TLine(83, 32, 84, 32);
	l32_4->SetLineColor(kBlue);
	l32_4->SetLineWidth(4);
	l32_4->Draw();
	TLine *l32_5 = new TLine(90, 32, 94, 32);
	l32_5->SetLineColor(kBlue);
	l32_5->SetLineWidth(4);
	l32_5->Draw();
	
	// ch 33
	TLine *l33_0 = new TLine(54, 33, 66, 33);
	l33_0->SetLineColor(kBlue);
	l33_0->SetLineWidth(4);
	l33_0->Draw();
	TLine *l33_2 = new TLine(67, 33, 68, 33);
	l33_2->SetLineColor(kBlue);
	l33_2->SetLineWidth(4);
	l33_2->Draw();
	TLine *l33_3 = new TLine(72, 33, 80, 33);
	l33_3->SetLineColor(kBlue);
	l33_3->SetLineWidth(4);
	l33_3->Draw();
	TLine *l33_4 = new TLine(83, 33, 94, 33);
	l33_4->SetLineColor(kBlue);
	l33_4->SetLineWidth(4);
	l33_4->Draw();
	
	// ch 34
	TLine *l34_0 = new TLine(54, 34, 63, 34);
	l34_0->SetLineColor(kBlue);
	l34_0->SetLineWidth(4);
	l34_0->Draw();
	TLine *l34_2 = new TLine(67, 34, 68, 34);
	l34_2->SetLineColor(kBlue);
	l34_2->SetLineWidth(4);
	l34_2->Draw();
	TLine *l34_3 = new TLine(69, 34, 72, 34);
	l34_3->SetLineColor(kBlue);
	l34_3->SetLineWidth(4);
	l34_3->Draw();
	TLine *l34_4 = new TLine(73, 34, 80, 34);
	l34_4->SetLineColor(kBlue);
	l34_4->SetLineWidth(4);
	l34_4->Draw();
	TLine *l34_5 = new TLine(83, 34, 94, 34);
	l34_5->SetLineColor(kBlue);
	l34_5->SetLineWidth(4);
	l34_5->Draw();
	
	// ch 35
	TLine *l35_0 = new TLine(53, 35, 66, 35);
	l35_0->SetLineColor(kBlue);
	l35_0->SetLineWidth(4);
	l35_0->Draw();
	TLine *l35_2 = new TLine(67, 35, 68, 35);
	l35_2->SetLineColor(kBlue);
	l35_2->SetLineWidth(4);
	l35_2->Draw();
	TLine *l35_3 = new TLine(69, 35, 72, 35);
	l35_3->SetLineColor(kBlue);
	l35_3->SetLineWidth(4);
	l35_3->Draw();
	TLine *l35_4 = new TLine(73, 35, 80, 35);
	l35_4->SetLineColor(kBlue);
	l35_4->SetLineWidth(4);
	l35_4->Draw();
	TLine *l35_5 = new TLine(83, 35, 94, 35);
	l35_5->SetLineColor(kBlue);
	l35_5->SetLineWidth(4);
	l35_5->Draw();
	
	// ch 36
	TLine *l36_0 = new TLine(53, 36, 66, 36);
	l36_0->SetLineColor(kRed);
	l36_0->SetLineWidth(4);
	l36_0->Draw();
	TLine *l36_2 = new TLine(67, 36, 68, 36);
	l36_2->SetLineColor(kRed);
	l36_2->SetLineWidth(4);
	l36_2->Draw();
	TLine *l36_3 = new TLine(69, 36, 72, 36);
	l36_3->SetLineColor(kRed);
	l36_3->SetLineWidth(4);
	l36_3->Draw();
	TLine *l36_4 = new TLine(73, 36, 80, 36);
	l36_4->SetLineColor(kRed);
	l36_4->SetLineWidth(4);
	l36_4->Draw();
	TLine *l36_5 = new TLine(83, 36, 94, 36);
	l36_5->SetLineColor(kRed);
	l36_5->SetLineWidth(4);
	l36_5->Draw();
	
	// ch 37
	TLine *l37_0 = new TLine(53, 37, 63, 37);
	l37_0->SetLineColor(kRed+2);
	l37_0->SetLineWidth(4);
	l37_0->Draw();
	TLine *l37_2 = new TLine(65, 37, 66, 37);
	l37_2->SetLineColor(kRed+2);
	l37_2->SetLineWidth(4);
	l37_2->Draw();
	TLine *l37_4 = new TLine(69, 37, 70, 37);
	l37_4->SetLineColor(kRed+2);
	l37_4->SetLineWidth(4);
	l37_4->Draw();
	TLine *l37_5 = new TLine(71, 37, 75, 37);
	l37_5->SetLineColor(kRed+2);
	l37_5->SetLineWidth(4);
	l37_5->Draw();
	TLine *l37_6 = new TLine(85, 37, 92, 37);
	l37_6->SetLineColor(kRed+2);
	l37_6->SetLineWidth(4);
	l37_6->Draw();
	TLine *l37_7 = new TLine(77, 37, 80, 37);
	l37_7->SetLineColor(kRed+2);
	l37_7->SetLineWidth(4);
	l37_7->Draw();
	
	// ch 38
	TLine *l38_0 = new TLine(55, 38, 57, 38);
	l38_0->SetLineColor(kRed+2);
	l38_0->SetLineWidth(4);
	l38_0->Draw();
	TLine *l38_2 = new TLine(60, 38, 61, 38);
	l38_2->SetLineColor(kRed+2);
	l38_2->SetLineWidth(4);
	l38_2->Draw();
	TLine *l38_3 = new TLine(65, 38, 66, 38);
	l38_3->SetLineColor(kRed+2);
	l38_3->SetLineWidth(4);
	l38_3->Draw();
	TLine *l38_4 = new TLine(72, 38, 80, 38);
	l38_4->SetLineColor(kRed+2);
	l38_4->SetLineWidth(4);
	l38_4->Draw();
	TLine *l38_5 = new TLine(83, 38, 84, 38);
	l38_5->SetLineColor(kRed+2);
	l38_5->SetLineWidth(4);
	l38_5->Draw();
	TLine *l38_6 = new TLine(89, 38, 90, 38);
	l38_6->SetLineColor(kRed+2);
	l38_6->SetLineWidth(4);
	l38_6->Draw();
	TLine *l38_7 = new TLine(91, 38, 92, 38);
	l38_7->SetLineColor(kRed+2);
	l38_7->SetLineWidth(4);
	l38_7->Draw();
	
	// ch 39
	TLine *l39_0 = new TLine(53, 39, 66, 39);
	l39_0->SetLineColor(kRed+2);
	l39_0->SetLineWidth(4);
	l39_0->Draw();
	TLine *l39_2 = new TLine(69, 39, 70, 39);
	l39_2->SetLineColor(kRed+2);
	l39_2->SetLineWidth(4);
	l39_2->Draw();
	TLine *l39_3 = new TLine(71, 39, 80, 39);
	l39_3->SetLineColor(kRed+2);
	l39_3->SetLineWidth(4);
	l39_3->Draw();
	TLine *l39_4 = new TLine(83, 39, 84, 39);
	l39_4->SetLineColor(kRed+2);
	l39_4->SetLineWidth(4);
	l39_4->Draw();
	TLine *l39_5 = new TLine(85, 39, 86, 39);
	l39_5->SetLineColor(kRed+2);
	l39_5->SetLineWidth(4);
	l39_5->Draw();
	TLine *l39_6 = new TLine(88, 39, 92, 39);
	l39_6->SetLineColor(kRed+2);
	l39_6->SetLineWidth(4);
	l39_6->Draw();
	
	return 0;
}
//=======================================================================================
//=======================================================================================
//=======================================================================================
int phIIplus() {

	TCanvas *c = new TCanvas();
	c->SetGridx();
	TGraphErrors *g_lim = new TGraphErrors("phIIp_limits_canvas.txt");
	g_lim->SetMarkerStyle(20);
	g_lim->SetMarkerColor(0);
	g_lim->SetMarkerSize(0);
	g_lim->SetLineWidth(0);
	g_lim->GetXaxis()->SetTitle("# run");
	g_lim->GetYaxis()->SetTitle("# channel");
	g_lim->SetTitle("ON detectors ( phase II+ )");
	g_lim->Draw("AP");
	
	// ch 0
	TLine *l0_0 = new TLine(95, 0, 102, 0);
	l0_0->SetLineColor(kBlue);
	l0_0->SetLineWidth(4);
	l0_0->Draw();
	TLine *l0_1 = new TLine(103, 0, 115, 0);
	l0_1->SetLineColor(kBlue);
	l0_1->SetLineWidth(4);
	l0_1->Draw();
	
	// ch 1
	TLine *l1_0 = new TLine(95, 1, 102, 1);
	l1_0->SetLineColor(kBlue);
	l1_0->SetLineWidth(4);
	l1_0->Draw();
	TLine *l1_1 = new TLine(103, 1, 115, 1);
	l1_1->SetLineColor(kBlue);
	l1_1->SetLineWidth(4);
	l1_1->Draw();
	
	// ch 2
	TLine *l2_0 = new TLine(95, 2, 102, 2);
	l2_0->SetLineColor(kBlue);
	l2_0->SetLineWidth(4);
	l2_0->Draw();
	TLine *l2_1 = new TLine(103, 2, 115, 2);
	l2_1->SetLineColor(kBlue);
	l2_1->SetLineWidth(4);
	l2_1->Draw();
	
	// ch 3
	TLine *l3_0 = new TLine(96, 3, 102, 3);
	l3_0->SetLineColor(kBlue);
	l3_0->SetLineWidth(4);
	l3_0->Draw();
	TLine *l3_1 = new TLine(103, 3, 115, 3);
	l3_1->SetLineColor(kBlue);
	l3_1->SetLineWidth(4);
	l3_1->Draw();
	
	// ch 4
	TLine *l4_0 = new TLine(95, 4, 102, 4);
	l4_0->SetLineColor(kBlue);
	l4_0->SetLineWidth(4);
	l4_0->Draw();
	TLine *l4_1 = new TLine(103, 4, 115, 4);
	l4_1->SetLineColor(kBlue);
	l4_1->SetLineWidth(4);
	l4_1->Draw();
	
	// ch 5
	TLine *l5_0 = new TLine(95, 5, 102, 5);
	l5_0->SetLineColor(kBlue);
	l5_0->SetLineWidth(4);
	l5_0->Draw();
	TLine *l5_1 = new TLine(103, 5, 115, 5);
	l5_1->SetLineColor(kBlue);
	l5_1->SetLineWidth(4);
	l5_1->Draw();
	
	// ch 6
	TLine *l6_0 = new TLine(95, 6, 102, 6);
	l6_0->SetLineColor(kBlue);
	l6_0->SetLineWidth(4);
	l6_0->Draw();
	TLine *l6_1 = new TLine(103, 6, 115, 6);
	l6_1->SetLineColor(kBlue);
	l6_1->SetLineWidth(4);
	l6_1->Draw();
	
	// ch 7
	TLine *l7_0 = new TLine(95, 7, 102, 7);
	l7_0->SetLineColor(kBlue);
	l7_0->SetLineWidth(4);
	l7_0->Draw();
	TLine *l7_1 = new TLine(103, 7, 115, 7);
	l7_1->SetLineColor(kBlue);
	l7_1->SetLineWidth(4);
	l7_1->Draw();

	// ch 8
	
	// ch 9
	TLine *l9_0 = new TLine(95, 9, 102, 9);
	l9_0->SetLineColor(kRed);
	l9_0->SetLineWidth(4);
	l9_0->Draw();
	TLine *l9_1 = new TLine(103, 9, 108, 9);
	l9_1->SetLineColor(kRed);
	l9_1->SetLineWidth(4);
	l9_1->Draw();
	TLine *l9_2 = new TLine(109, 9, 115, 9);
	l9_2->SetLineColor(kRed);
	l9_2->SetLineWidth(4);
	l9_2->Draw();
	
	// ch 10
	TLine *l10_0 = new TLine(95, 10, 102, 10);
	l10_0->SetLineColor(kRed);
	l10_0->SetLineWidth(4);
	l10_0->Draw();
	TLine *l10_1 = new TLine(103, 10, 108, 10);
	l10_1->SetLineColor(kRed);
	l10_1->SetLineWidth(4);
	l10_1->Draw();
	TLine *l10_2 = new TLine(109, 10, 115, 10);
	l10_2->SetLineColor(kRed);
	l10_2->SetLineWidth(4);
	l10_2->Draw();
	
	// ch 11
	TLine *l11_0 = new TLine(95, 11, 102, 11);
	l11_0->SetLineColor(kBlue);
	l11_0->SetLineWidth(4);
	l11_0->Draw();
	TLine *l11_1 = new TLine(103, 11, 115, 11);
	l11_1->SetLineColor(kBlue);
	l11_1->SetLineWidth(4);
	l11_1->Draw();
	
	// ch 12
	TLine *l12_0 = new TLine(96, 12, 102, 12);
	l12_0->SetLineColor(kBlue);
	l12_0->SetLineWidth(4);
	l12_0->Draw();
	TLine *l12_1 = new TLine(103, 12, 115, 12);
	l12_1->SetLineColor(kBlue);
	l12_1->SetLineWidth(4);
	l12_1->Draw();
	
	// ch 13 
	TLine *l13_0 = new TLine(95, 13, 102, 13);
	l13_0->SetLineColor(kBlue);
	l13_0->SetLineWidth(4);
	l13_0->Draw();
	TLine *l13_1 = new TLine(103, 13, 115, 13);
	l13_1->SetLineColor(kBlue);
	l13_1->SetLineWidth(4);
	l13_1->Draw();
	
	// ch 14
	TLine *l14_0 = new TLine(95, 14, 102, 14);
	l14_0->SetLineColor(kBlue);
	l14_0->SetLineWidth(4);
	l14_0->Draw();
	TLine *l14_1 = new TLine(103, 14, 115, 14);
	l14_1->SetLineColor(kBlue);
	l14_1->SetLineWidth(4);
	l14_1->Draw();
	
	// ch 15
	TLine *l15_0 = new TLine(95, 15, 102, 15);
	l15_0->SetLineColor(kBlue);
	l15_0->SetLineWidth(4);
	l15_0->Draw();
	TLine *l15_1 = new TLine(103, 15, 115, 15);
	l15_1->SetLineColor(kBlue);
	l15_1->SetLineWidth(4);
	l15_1->Draw();
	
	// ch 16
	TLine *l16_0 = new TLine(95, 16, 102, 16);
	l16_0->SetLineColor(kBlue);
	l16_0->SetLineWidth(4);
	l16_0->Draw();
	TLine *l16_1 = new TLine(103, 16, 115, 16);
	l16_1->SetLineColor(kBlue);
	l16_1->SetLineWidth(4);
	l16_1->Draw();
	
	// ch 17
	TLine *l17_0 = new TLine(95, 17, 102, 17);
	l17_0->SetLineColor(kBlue);
	l17_0->SetLineWidth(4);
	l17_0->Draw();
	TLine *l17_1 = new TLine(103, 17, 115, 17);
	l17_1->SetLineColor(kBlue);
	l17_1->SetLineWidth(4);
	l17_1->Draw();
	
	// ch 18
	TLine *l18_0 = new TLine(95, 18, 102, 18);
	l18_0->SetLineColor(kBlue);
	l18_0->SetLineWidth(4);
	l18_0->Draw();
	TLine *l18_1 = new TLine(103, 18, 115, 18);
	l18_1->SetLineColor(kBlue);
	l18_1->SetLineWidth(4);
	l18_1->Draw();
	
	// ch 19
	TLine *l19_0 = new TLine(95, 19, 102, 19);
	l19_0->SetLineColor(kBlue);
	l19_0->SetLineWidth(4);
	l19_0->Draw();
	TLine *l19_1 = new TLine(103, 19, 115, 19);
	l19_1->SetLineColor(kBlue);
	l19_1->SetLineWidth(4);
	l19_1->Draw();
	
	// ch 20
	TLine *l20_0 = new TLine(95, 20, 102, 20);
	l20_0->SetLineColor(kBlue);
	l20_0->SetLineWidth(4);
	l20_0->Draw();
	TLine *l20_1 = new TLine(103, 20, 115, 20);
	l20_1->SetLineColor(kBlue);
	l20_1->SetLineWidth(4);
	l20_1->Draw();
	
	// ch 21
	TLine *l21_0 = new TLine(95, 21, 102, 21);
	l21_0->SetLineColor(kBlue);
	l21_0->SetLineWidth(4);
	l21_0->Draw();
	TLine *l21_1 = new TLine(103, 21, 115, 21);
	l21_1->SetLineColor(kBlue);
	l21_1->SetLineWidth(4);
	l21_1->Draw();
	
	// ch 22
	TLine *l22_0 = new TLine(95, 22, 102, 22);
	l22_0->SetLineColor(kBlue);
	l22_0->SetLineWidth(4);
	l22_0->Draw();
	TLine *l22_1 = new TLine(103, 22, 115, 22);
	l22_1->SetLineColor(kBlue);
	l22_1->SetLineWidth(4);
	l22_1->Draw();
	
	// ch 23
	TLine *l23_0 = new TLine(95, 23, 102, 23);
	l23_0->SetLineColor(kBlue);
	l23_0->SetLineWidth(4);
	l23_0->Draw();
	TLine *l23_1 = new TLine(103, 23, 115, 23);
	l23_1->SetLineColor(kBlue);
	l23_1->SetLineWidth(4);
	l23_1->Draw();
	
	// ch 24
	TLine *l24_0 = new TLine(95, 24, 102, 24);
	l24_0->SetLineColor(kBlue);
	l24_0->SetLineWidth(4);
	l24_0->Draw();
	TLine *l24_1 = new TLine(103, 24, 115, 24);
	l24_1->SetLineColor(kBlue);
	l24_1->SetLineWidth(4);
	l24_1->Draw();
	
	// ch 25
	TLine *l25_0 = new TLine(96, 25, 102, 25);
	l25_0->SetLineColor(kBlue);
	l25_0->SetLineWidth(4);
	l25_0->Draw();
	TLine *l25_1 = new TLine(103, 25, 115, 25);
	l25_1->SetLineColor(kBlue);
	l25_1->SetLineWidth(4);
	l25_1->Draw();
	
	// ch 26
	TLine *l26_0 = new TLine(95, 26, 101, 26);
	l26_0->SetLineColor(kBlue);
	l26_0->SetLineWidth(4);
	l26_0->Draw();
	TLine *l26_2 = new TLine(103, 26, 108, 26);
	l26_2->SetLineColor(kBlue);
	l26_2->SetLineWidth(4);
	l26_2->Draw();
	TLine *l26_3 = new TLine(109, 26, 115, 26);
	l26_3->SetLineColor(kBlue);
	l26_3->SetLineWidth(4);
	l26_3->Draw();
	
	// ch 27
	TLine *l27_0 = new TLine(98, 27, 102, 27);
	l27_0->SetLineColor(kRed);
	l27_0->SetLineWidth(4);
	l27_0->Draw();
	TLine *l27_2 = new TLine(103, 27, 115, 27);
	l27_2->SetLineColor(kRed);
	l27_2->SetLineWidth(4);
	l27_2->Draw();
	
	// ch 28
	TLine *l28_0 = new TLine(95, 28, 102, 28);
	l28_0->SetLineColor(kRed);
	l28_0->SetLineWidth(4);
	l28_0->Draw();
	TLine *l28_1 = new TLine(103, 28, 115, 28);
	l28_1->SetLineColor(kRed);
	l28_1->SetLineWidth(4);
	l28_1->Draw();
	
	// ch 29
	TLine *l29_0 = new TLine(95, 29, 102, 29);
	l29_0->SetLineColor(kRed);
	l29_0->SetLineWidth(4);
	l29_0->Draw();
	TLine *l29_1 = new TLine(103, 29, 115, 29);
	l29_1->SetLineColor(kRed);
	l29_1->SetLineWidth(4);
	l29_1->Draw();
	
	// ch 30
	TLine *l30_0 = new TLine(95, 30, 102, 30);
	l30_0->SetLineColor(kBlue);
	l30_0->SetLineWidth(4);
	l30_0->Draw();
	TLine *l30_1 = new TLine(103, 30, 115, 30);
	l30_1->SetLineColor(kBlue);
	l30_1->SetLineWidth(4);
	l30_1->Draw();
	
	// ch 31
	TLine *l31_0 = new TLine(95, 31, 102, 31);
	l31_0->SetLineColor(kBlue);
	l31_0->SetLineWidth(4);
	l31_0->Draw();
	TLine *l31_1 = new TLine(103, 31, 115, 31);
	l31_1->SetLineColor(kBlue);
	l31_1->SetLineWidth(4);
	l31_1->Draw();
	
	// ch 32
	TLine *l32_0 = new TLine(104, 32, 113, 32);
	l32_0->SetLineColor(kBlue);
	l32_0->SetLineWidth(4);
	l32_0->Draw();
	TLine *l32_2 = new TLine(114, 32, 115, 32);
	l32_2->SetLineColor(kBlue);
	l32_2->SetLineWidth(4);
	l32_2->Draw();
	
	// ch 33 
	TLine *l33_0 = new TLine(95, 33, 102, 33);
	l33_0->SetLineColor(kBlue);
	l33_0->SetLineWidth(4);
	l33_0->Draw();
	TLine *l33_1 = new TLine(103, 33, 115, 33);
	l33_1->SetLineColor(kBlue);
	l33_1->SetLineWidth(4);
	l33_1->Draw();
	
	// ch 34
	TLine *l34_0 = new TLine(95, 34, 102, 34);
	l34_0->SetLineColor(kBlue);
	l34_0->SetLineWidth(4);
	l34_0->Draw();
	TLine *l34_1 = new TLine(104, 34, 115, 34);
	l34_1->SetLineColor(kBlue);
	l34_1->SetLineWidth(4);
	l34_1->Draw();
	
	// ch 35
	TLine *l35_0 = new TLine(95, 35, 102, 35);
	l35_0->SetLineColor(kBlue);
	l35_0->SetLineWidth(4);
	l35_0->Draw();
	TLine *l35_1 = new TLine(103, 35, 115, 35);
	l35_1->SetLineColor(kBlue);
	l35_1->SetLineWidth(4);
	l35_1->Draw();
	
	// ch 36
	
	// ch 37
	TLine *l37_0 = new TLine(95, 37, 102, 37);
	l37_0->SetLineColor(kGreen+1);
	l37_0->SetLineWidth(4);
	l37_0->Draw();
	TLine *l37_1 = new TLine(103, 37, 115, 37);
	l37_1->SetLineColor(kGreen+1);
	l37_1->SetLineWidth(4);
	l37_1->Draw();
	
	// ch 38
	TLine *l38_0 = new TLine(95, 38, 102, 38);
	l38_0->SetLineColor(kGreen+1);
	l38_0->SetLineWidth(4);
	l38_0->Draw();
	TLine *l38_1 = new TLine(103, 38, 115, 38);
	l38_1->SetLineColor(kGreen+1);
	l38_1->SetLineWidth(4);
	l38_1->Draw();
	
	// ch 39
	TLine *l39_0 = new TLine(98, 39, 102, 39);
	l39_0->SetLineColor(kGreen+1);
	l39_0->SetLineWidth(4);
	l39_0->Draw();
	TLine *l39_1 = new TLine(103, 39, 115, 39);
	l39_1->SetLineColor(kGreen+1);
	l39_1->SetLineWidth(4);
	l39_1->Draw();
	
	// ch 40
	TLine *l40_0 = new TLine(95, 40, 102, 40);
	l40_0->SetLineColor(kGreen+1);
	l40_0->SetLineWidth(4);
	l40_0->Draw();
	TLine *l40_1 = new TLine(103, 40, 115, 40);
	l40_1->SetLineColor(kGreen+1);
	l40_1->SetLineWidth(4);
	l40_1->Draw();
	
	return 0;
}
