Int_t NumberOfRows(char *filename) {

	Int_t NumOfRows = 0;
	std::string line;
	std::ifstream file(filename);
	
	while (std::getline(file,line)) {
		++NumOfRows;
	}
	
	//NumOfRows = NumOfRows -1 ; // if 1st line are comments
	
	return NumOfRows;
}

//--------------------------------------------------------------------------------------------------------------------------
int *all() {

	int A;
	std::cout << "Coax (0) or BEGe (1)? ";
	std::cin >> A;
	
	char file_g1[100], file_g2[100], file_g3[100], file_g4[100];
	
	//========================================================================================================== U90 VS E0
	if ( A==0 ) { sprintf(file_g1, "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/90UpperLimit_norm.txt"); }	
	else { sprintf(file_g1, "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/90UpperLimit_norm.txt"); }
	TGraphErrors *g1 = new TGraphErrors(file_g1, "%lg %lg %*lg %*lg %*lg");
	
	TCanvas *c1 = new TCanvas("c1","c1",1700,1000);
	c1->SetGrid();
	c1->SetLogy();
	g1->SetLineWidth(2);
	g1->SetMarkerStyle(20);
	if ( A==0 ) {
		g1->SetLineColor(kRed+1);
		g1->SetMarkerColor(kRed+1);
	}
	else {
		g1->SetLineColor(kBlue+1);
		g1->SetMarkerColor(kBlue+1);
	}
	g1->SetMarkerSize(1.3);
	g1->GetXaxis()->SetTitle("E0 [keV]");
	g1->GetYaxis()->SetTitle("[cts/(kg*yr)]");
	g1->GetYaxis()->SetRange(0,200);
	g1->SetTitle("counts VS E0");
	g1->Draw("AL");
	c1->Update();
	if ( A==0 ) { c1->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/counts_VS_E0.png"); }
	else { c1->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/counts_VS_E0.png"); }
	
	//========================================================================================================== p0 VS E0
	if ( A==0 ) { sprintf(file_g2, "/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/p0_VS_E0.txt"); }	
	else { sprintf(file_g2, "/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/p0_VS_E0.txt"); }
	
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
	
	TCanvas *c2 = new TCanvas("c2","c2",1700,1000);
	c2->SetGrid();
	c2->SetLogy();
	g2->SetLineWidth(2);	
	g2->SetMarkerStyle(20);
	g2->SetLineColor(kMagenta+2);
	g2->SetMarkerColor(kMagenta+2);
	g2->SetMarkerSize(1.3);
	g2->GetXaxis()->SetTitle("E0 [keV]");
	g2->GetYaxis()->SetTitle("offset [cts]");
	g2->SetTitle("p0 VS E0");
	g2->Draw("AP");
	c2->Update();
	if ( A==0 ) { c2->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p0_VS_E0.png"); }
	else { c2->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p0_VS_E0.png"); }
	
	ifstream file3;
	if ( A==0 ) { file3.open("/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/p1_VS_E0.txt"); }
	else { file3.open("/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/p1_VS_E0.txt"); }
	if ( !file3 ) { cout << "\"p1_VS_E0.txt\" does not exist"; }
	else {
		//================================================================================================== p1 VS E0
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
		
		TCanvas *c3 = new TCanvas("c3","c3",1700,1000);
		c3->SetGrid();
		g3->SetLineColor(kGreen+2);
		g3->SetLineWidth(2);	
		g3->SetMarkerStyle(20);
		g3->SetMarkerColor(kGreen+2);
		g3->SetMarkerSize(1.3);
		g3->GetXaxis()->SetTitle("E0 [keV]");
		g3->GetYaxis()->SetTitle("slope [cts/keV]");
		g3->GetYaxis()->SetRangeUser(-25,3);
		g3->SetTitle("p1 VS E0");
		g3->Draw("AP");
		c3->Update();
		if ( A==0 ) { c3->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p1_VS_E0.png"); }
		else { c3->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p1_VS_E0.png"); }
	}
	
	ifstream file4;
	if ( A==0 ) { file4.open("/home/sofia/Analysis/DataAnalysis/ReadJSON/coax/p2_VS_E0.txt"); }
	else { file4.open("/home/sofia/Analysis/DataAnalysis/ReadJSON/BEGe/p2_VS_E0.txt"); }
	if ( !file4 ) { cout << "\"p2_VS_E0.txt\" does not exist"; }
	else {
		//================================================================================================== p2 VS E0
		double data4[rows][columns];
		for (int i=0; i<rows; i++) {
			for (int j=0; j<columns; j++) {
				file4 >> data4[i][j];
			}
		}
		file4.close();
		
		Double_t x2[rows], y2[rows], exD2[rows], exU2[rows], eyD2[rows], eyU2[rows];
		
		for (int i=0; i<rows; i++) {
			x2[i] = data4[i][0];
			y2[i] = data4[i][1];
			exD2[i] = 0;
			exU2[i] = 0;
			eyD2[i] = data4[i][2];
			eyU2[i] = data4[i][3];
		}
		
		auto g4 = new TGraphAsymmErrors(rows, x2, y2, exD2, exU2, eyD2, eyU2);
		
		TCanvas *c4 = new TCanvas("c4","c4",1700,1000);
		c4->SetGrid();
		g4->SetLineColor(kGreen+2);
		g4->SetLineWidth(2);	
		g4->SetMarkerStyle(20);
		g4->SetMarkerColor(kGreen+2);
		g4->SetMarkerSize(1.3);
		g4->GetXaxis()->SetTitle("E0 [keV]");
		g4->GetYaxis()->SetTitle("p2 [cts/keV^2]");
		g4->SetTitle("p2 VS E0");
		g4->Draw("AP");
		c4->Update();
		if ( A==0 ) { c4->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p2_VS_E0.png"); }
		else { c4->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p2_VS_E0.png"); }
	}
	
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------- p0
int p0() {

	int A;
	std::cout << " Coax (0) or BEGe (1)? ";
	std::cin >> A;
	
	char file_g2[100];
	if ( A==0 ) { sprintf(file_g2, "/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p0_VS_E0.txt"); }	
	else { sprintf(file_g2, "/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p0_VS_E0.txt"); }
	
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
	
	TCanvas *c2 = new TCanvas("c2","c2",1700,1000);
	c2->SetGrid();
	c2->SetLogy();
	g2->SetLineWidth(2);
	g2->SetMarkerStyle(20);
	g2->SetLineColor(kMagenta+2);
	g2->SetMarkerColor(kMagenta+2);
	g2->SetMarkerSize(1.3);
	g2->GetXaxis()->SetTitle("E0 [keV]");
	g2->GetYaxis()->SetTitle("p0 [cts]");
	g2->SetTitle("p0 VS E0");
	g2->Draw("AP");
	c2->Update();
	if ( A==0 ) { c2->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p0_VS_E0.png"); }
	else { c2->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p0_VS_E0.png"); }

	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------- p1
int p1() {

	int A;
	std::cout << " Coax (0) or BEGe (1)? ";
	std::cin >> A;
	
	char file_g3[100];
	if ( A==0 ) { sprintf(file_g3, "/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p1_VS_E0.txt"); }	
	else { sprintf(file_g3, "/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p1_VS_E0.txt"); }
	
	Int_t rows = NumberOfRows(file_g3);
	const Int_t columns = 4;
	double data3[rows][columns];
	std::ifstream file3(file_g3);
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
	
	TCanvas *c3 = new TCanvas("c3","c3",1700,1000);
	c3->SetGrid();
	g3->SetLineColor(kGreen+2);
	g3->SetLineWidth(2);	
	g3->SetMarkerStyle(20);
	g3->SetMarkerColor(kGreen+2);
	g3->SetMarkerSize(1.3);
	g3->GetXaxis()->SetTitle("E0 [keV]");
	g3->GetYaxis()->SetTitle("slope [cts/keV]");
	g3->GetYaxis()->SetRangeUser(-25,3);
	g3->SetTitle("p1 VS E0");
	g3->Draw("AP");
	c3->Update();
	if ( A==0 ) { c3->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p1_VS_E0.png"); }
	else { c3->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p1_VS_E0.png"); }

	return 0;
}

//-------------------------------------------------------------------------------------------------------------------------- p2
int p2() {

	int A;
	std::cout << " Coax (0) or BEGe (1)? ";
	std::cin >> A;
	
	char file_g4[100];
	if ( A==0 ) { sprintf(file_g4, "/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p2_VS_E0.txt"); }	
	else { sprintf(file_g4, "/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p2_VS_E0.txt"); }
	
	Int_t rows = NumberOfRows(file_g4);
	const Int_t columns = 4;
	double data4[rows][columns];
	std::ifstream file4(file_g4);
	for (int i=0; i<rows; i++) {
		for (int j=0; j<columns; j++) {
			file4 >> data4[i][j];
		}
	}
	file4.close();
	
	Double_t x2[rows], y2[rows], exD2[rows], exU2[rows], eyD2[rows], eyU2[rows];
	
	for (int i=0; i<rows; i++) {
		x2[i] = data4[i][0];
		y2[i] = data4[i][1];
		exD2[i] = 0;
		exU2[i] = 0;
		eyD2[i] = data4[i][2];
		eyU2[i] = data4[i][3];
	}
	
	auto g4 = new TGraphAsymmErrors(rows, x2, y2, exD2, exU2, eyD2, eyU2);
	
	TCanvas *c4 = new TCanvas("c4","c4",1700,1000);
	c4->SetGrid();
	c4->SetGrid();
	g4->SetLineColor(kGreen+2);
	g4->SetLineWidth(2);	
	g4->SetMarkerStyle(20);
	g4->SetMarkerColor(kGreen+2);
	g4->SetMarkerSize(1.3);
	g4->GetXaxis()->SetTitle("E0 [keV]");
	g4->GetYaxis()->SetTitle("p2 [cts/keV^2]");
	g4->SetTitle("p2 VS E0");
	g4->Draw("AP");
	c4->Update();
	if ( A==0 ) { c4->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/coax/p2_VS_E0.png"); }
	else { c4->SaveAs("/home/sofia/Analysis/DataAnalysis/Par_VS_E0/BEGe/p2_VS_E0.png"); }

	return 0;
}
