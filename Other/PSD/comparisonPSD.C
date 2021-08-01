#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace::std;
using json = nlohmann::json;

// Macro presenti:
//   - comparisonPSD: plot insieme dei due limiti, con e senza PSD, in [counts]
//   - normalized: plot insieme dei due limiti, con e senza PSD, in [counts/(kg*yr)]
//   - rapporto: plot di PSD/noPSD
//   - perc_diff: plot di (1-PSD/noPSD)*100


int comparisonPSD() {

	const int E0_min = 60;
	const int E0_max = 1000;
	
	int ans0;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> ans0;

	fstream file1;
	file1.open("PSD.txt",ios::out);
	fstream file2;
	file2.open("NOTPSD.txt",ios::out);
	
	for ( int i=E0_min; i<=E0_max; i++) {
	
		string filename1, filename2;
		if ( ans0==0 ) { filename1 = "/home/sofia/Analysis/Data2/JsonFiles/coax/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==1 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==2 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC/JsonFile" + to_string(i) + ".json"; }
		
		if ( ans0==0 ) { filename2 = "/home/sofia/Analysis/Data2/JsonFiles/coax_PSD/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==1 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe_PSD/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==2 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC_PSD/JsonFile" + to_string(i) + ".json"; }
		ifstream file3(filename1);
		ifstream file4(filename2);
		if ( !file3 ) { /*file does not exist*/ }
		if ( !file4 ) { /*file does not exist*/ }
		
		else {
			json j_read1, j_read2;
			file3 >> j_read1;
			file4 >> j_read2;
			
			double E0_counts_U90 = j_read1["90UpperLimit"]["E0_counts_U90"].get<double>();
			double E0_counts_U90_PSD = j_read2["90UpperLimit"]["E0_counts_U90"].get<double>();
			
			file1 << i << "\t" << E0_counts_U90_PSD << endl;
			file2 << i << "\t" << E0_counts_U90 << endl;
		}
		file3.close();
		file4.close();
	} 
	
	file1.close();
	file2.close();
	
	TCanvas *c1 = new TCanvas();
	c1->SetLogy();
	TGraphErrors *g1 = new TGraphErrors("NOTPSD.txt");
	g1->GetXaxis()->SetTitle("Energy [keV]");
	g1->GetYaxis()->SetTitle("Signal strength [cts/keV*yr]");
	if ( ans0==0 ) g1->SetLineColor(kRed+1);
	if ( ans0==1 ) g1->SetLineColor(kBlue+1);
	if ( ans0==2 ) g1->SetLineColor(kGreen+2);
	g1->GetXaxis()->SetRangeUser(10,1050);
	g1->SetLineStyle(2);
	g1->SetLineWidth(2);
	g1->Draw();
	
	TGraphErrors *g2 = new TGraphErrors("PSD.txt");
	g2->SetLineColor(kRed);
	if ( ans0==0 ) g2->SetLineColor(kBlack);
	g2->SetLineWidth(2);
	g2->Draw("same");
	
	double y_max = 0;
	if ( ans0==0 ) { y_max = 500; }
	if ( ans0==1 ) { y_max = 538; }
	if ( ans0==2 ) { y_max = 142; }
	
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
	
	auto *legend1 = new TLegend(.65, .75, .88, .88);
	char title1[200], title2[200];
	if ( ans0==0 ) { sprintf(title1, "EnrCoax"); sprintf(title2, "EnrCoax - PSD only"); }
	if ( ans0==1 ) { sprintf(title1, "EnrBEGe"); sprintf(title2, "EnrBEGe - PSD only"); }
	if ( ans0==2 ) { sprintf(title1, "IC"); sprintf(title2, "IC - PSD only"); }
	legend1->AddEntry(g1, title1, "l");
	legend1->AddEntry(g2, title2, "l");
	legend1->AddEntry(line1, "Background #gamma", "l");
	legend1->Draw();
	
	return 0;
}

//============================================================================================================================================================
int normalized() {

	const int E0_min = 60;
	const int E0_max = 1000;
	
	int ans0;
	cout << " BEGe (1) or IC (2)? ";
	cin >> ans0;

	fstream file1;
	file1.open("PSD.txt",ios::out);
	fstream file2;
	file2.open("NOTPSD.txt",ios::out);
	
	for ( int i=E0_min; i<=E0_max; i++) {
	
		string filename1, filename2;
		if ( ans0==1 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==2 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC/JsonFile" + to_string(i) + ".json"; }
		
		if ( ans0==1 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe_PSD/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==2 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC_PSD/JsonFile" + to_string(i) + ".json"; }
		ifstream file3(filename1);
		ifstream file4(filename2);
		if ( !file3 ) { /*file does not exist*/ }
		if ( !file4 ) { /*file does not exist*/ }
		
		else {
			json j_read1, j_read2;
			file3 >> j_read1;
			file4 >> j_read2;
			
			double E0_counts_U90 = j_read1["90UpperLimit"]["E0_counts_U90"].get<double>();
			double E0_counts_U90_PSD = j_read2["90UpperLimit"]["E0_counts_U90"].get<double>();
			
			double expBEL=0, expAB=0, expBEL_PSD=0, expAB_PSD=0;
			
			if ( ans0==1 ) { expBEL = 30.5489; expAB = 54.9284; expBEL_PSD = 30.1516; expAB_PSD = 53.3248; } // BEGe
			if ( ans0==2 ) { expBEL = 8.77469; expAB = expBEL; expBEL_PSD = 8.58872; expAB_PSD = expBEL_PSD; } // IC
			
			if ( i<120 ) { file1 << i << "\t" << E0_counts_U90_PSD/expBEL_PSD << endl; }
			else { file1 << i << "\t" << E0_counts_U90_PSD/expAB_PSD << endl; }
			if ( i<120 ) { file2 << i << "\t" << E0_counts_U90/expBEL << endl; }
			else { file2 << i << "\t" << E0_counts_U90/expAB << endl; }
		}
		file3.close();
		file4.close();
	} 
	
	file1.close();
	file2.close();
	
	TCanvas *c1 = new TCanvas();
	c1->SetLogy();
	TGraphErrors *g1 = new TGraphErrors("NOTPSD.txt");
	g1->GetXaxis()->SetTitle("Energy [keV]");
	g1->GetYaxis()->SetTitle("Signal strength [counts/(kg*yr)]");
	if ( ans0==1 ) g1->SetLineColor(kBlue+1);
	if ( ans0==2 ) g1->SetLineColor(kGreen+2);
	g1->GetXaxis()->SetRangeUser(10,1050);
	g1->GetYaxis()->SetRangeUser(0,15);
	g1->SetLineStyle(2);
	g1->Draw();
	
	TGraphErrors *g2 = new TGraphErrors("PSD.txt");
	g2->SetLineColor(kRed);
	if ( ans0==0 ) g2->SetLineColor(kBlack);
	g2->SetLineWidth(2);
	g2->Draw("same");
	
	double y_max = 15;
	
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
	
	auto *legend1 = new TLegend(.65, .75, .88, .88);
	char title1[200], title2[200];
	if ( ans0==1 ) { sprintf(title1, "EnrBEGe"); sprintf(title2, "EnrBEGe - PSD only"); }
	if ( ans0==2 ) { sprintf(title1, "IC"); sprintf(title2, "IC - PSD only"); }
	legend1->AddEntry(g1, title1, "l");
	legend1->AddEntry(g2, title2, "l");
	legend1->AddEntry(line1, "Background #gamma", "l");
	legend1->Draw();
	
	return 0;
}

//============================================================================================================================================================
int rapporto() {

	const int E0_min = 60;
	const int E0_max = 1000;
	
	int ans0;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> ans0;

	fstream file1;
	file1.open("PSD_over_noPSD.txt",ios::out);
	
	int cts_PSDover = 0;
	int cts_PSDbelow = 0;
	
	for ( int i=E0_min; i<=E0_max; i++) {
	
		string filename1, filename2;
		if ( ans0==0 ) { filename1 = "/home/sofia/Analysis/Data2/JsonFiles/coax/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==1 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==2 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC/JsonFile" + to_string(i) + ".json"; }
		
		if ( ans0==0 ) { filename2 = "/home/sofia/Analysis/Data2/JsonFiles/coax_PSD/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==1 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe_PSD/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==2 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC_PSD/JsonFile" + to_string(i) + ".json"; }
		ifstream file3(filename1);
		ifstream file4(filename2);
		if ( !file3 ) { /*file does not exist*/ }
		if ( !file4 ) { /*file does not exist*/ }
		
		else {
			json j_read1, j_read2;
			file3 >> j_read1;
			file4 >> j_read2;
			
			double E0_counts_U90 = j_read1["90UpperLimit"]["E0_counts_U90"].get<double>();
			double E0_counts_U90_PSD = j_read2["90UpperLimit"]["E0_counts_U90"].get<double>();
			
			double expBEL=0, expAB=0, expBEL_PSD=0, expAB_PSD=0;
			
			if ( ans0==1 ) { expBEL = 30.5489; expAB = 54.9284; expBEL_PSD = 30.1516; expAB_PSD = 53.3248; } // BEGe
			if ( ans0==2 ) { expBEL = 8.77469; expAB = expBEL; expBEL_PSD = 8.58872; expAB_PSD = expBEL_PSD; } // IC
			
			if ( i<120 ) { file1 << i << "\t" << (E0_counts_U90_PSD/E0_counts_U90)*(expBEL/expBEL_PSD) << endl; }
			else { file1 << i << "\t" << (E0_counts_U90_PSD/E0_counts_U90)*(expAB/expAB_PSD) << endl; }
			
			if ( i<120 ) {
				if ( (E0_counts_U90_PSD/E0_counts_U90)*(expBEL/expBEL_PSD) > 1 ) { cts_PSDover++; }
				else { cts_PSDbelow++; }
			}
			else {
				if ( (E0_counts_U90_PSD/E0_counts_U90)*(expAB/expAB_PSD) > 1 ) { cts_PSDover++; }
				else { cts_PSDbelow++; }
			}
		}
		file3.close();
		file4.close();
	} 
	
	cout << " cts_PSDover = " << cts_PSDover << endl;
	cout << " cts_PSDbelow = " << cts_PSDbelow << endl;
	
	file1.close();
	
	TCanvas *c1 = new TCanvas();
	TGraphErrors *g1 = new TGraphErrors("PSD_over_noPSD.txt");
	g1->GetXaxis()->SetRangeUser(20,1040);
	g1->GetXaxis()->SetTitle("Energy [keV]");
	g1->GetYaxis()->SetTitle("PSD / no PSD");
	if ( ans0==0 ) g1->SetMarkerColor(kRed+1);
	if ( ans0==1 ) g1->SetMarkerColor(kBlue+1);
	if ( ans0==2 ) g1->SetMarkerColor(kGreen+2);
	g1->SetMarkerStyle(20);
	g1->SetMarkerSize(0.7);
	g1->Draw("AP");
	
	TLine *line1 = new TLine(20, 1, 1040, 1);
	line1->SetLineWidth(3);
	line1->SetLineColor(kGray+2);
	line1->SetLineStyle(9);
	line1->Draw();
	
	return 0;
}

//============================================================================================================================================================
int perc_diff() {

	const int E0_min = 60;
	const int E0_max = 1000;
	
	int ans0;
	cout << " Coax (0), BEGe (1) or IC (2)? ";
	cin >> ans0;

	fstream file1;
	file1.open("PSD_over_noPSD.txt",ios::out);
	fstream file2;
	file2.open("PSD_over_noPSD.txt",ios::out);
	
	int cts_PSDover = 0;
	int cts_PSDbelow = 0;
	
	for ( int i=E0_min; i<=E0_max; i++) {
	
		string filename1, filename2;
		if ( ans0==0 ) { filename1 = "/home/sofia/Analysis/Data2/JsonFiles/coax/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==1 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==2 ) { filename1 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC/JsonFile" + to_string(i) + ".json"; }
		
		if ( ans0==0 ) { filename2 = "/home/sofia/Analysis/Data2/JsonFiles/coax_PSD/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==1 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/BEGe_PSD/JsonFile" + to_string(i) + ".json"; }
		if ( ans0==2 ) { filename2 = "/home/sofia/Analysis/DataAnalysis/JsonFiles/IC_PSD/JsonFile" + to_string(i) + ".json"; }
		ifstream file3(filename1);
		ifstream file4(filename2);
		if ( !file3 ) { /*file does not exist*/ }
		if ( !file4 ) { /*file does not exist*/ }
		
		else {
			json j_read1, j_read2;
			file3 >> j_read1;
			file4 >> j_read2;
			
			double E0_counts_U90 = j_read1["90UpperLimit"]["E0_counts_U90"].get<double>();
			double E0_counts_U90_PSD = j_read2["90UpperLimit"]["E0_counts_U90"].get<double>();
			
			double expBEL=0, expAB=0, expBEL_PSD=0, expAB_PSD=0;
			
			if ( ans0==1 ) { expBEL = 30.5489; expAB = 54.9284; expBEL_PSD = 30.1516; expAB_PSD = 53.3248; } // BEGe
			if ( ans0==2 ) { expBEL = 8.77469; expAB = expBEL; expBEL_PSD = 8.58872; expAB_PSD = expBEL_PSD; } // IC
			
			if ( i<120 ) { file1 << i << "\t" << (1-(E0_counts_U90_PSD/E0_counts_U90)*(expBEL/expBEL_PSD))*100 << endl; }
			else { file1 << i << "\t" << (1-(E0_counts_U90_PSD/E0_counts_U90)*(expAB/expAB_PSD))*100 << endl; }
			
			if ( i<120 ) {
				if ( (1-(E0_counts_U90_PSD/E0_counts_U90)*(expBEL/expBEL_PSD))*100 < 0 ) { cts_PSDover++; }
				else { cts_PSDbelow++; }
			}
			else {
				if ( (1-(E0_counts_U90_PSD/E0_counts_U90)*(expAB/expAB_PSD))*100 < 0 ) { cts_PSDover++; }
				else { cts_PSDbelow++; }
			}
		}
		file3.close();
		file4.close();
	} 
	
	cout << " cts_PSDover = " << cts_PSDover << endl;
	cout << " cts_PSDbelow = " << cts_PSDbelow << endl;
	
	file1.close();
	
	TCanvas *c1 = new TCanvas();
	TGraphErrors *g1 = new TGraphErrors("PSD_over_noPSD.txt");
	g1->GetXaxis()->SetRangeUser(20,1040);
	g1->GetXaxis()->SetTitle("Energy [keV]");
	g1->GetYaxis()->SetTitle("1 - (PSD / no PSD) [\%]");
	if ( ans0==0 ) g1->SetMarkerColor(kRed+1);
	if ( ans0==1 ) g1->SetMarkerColor(kBlue+1);
	if ( ans0==2 ) g1->SetMarkerColor(kGreen+2);
	g1->SetMarkerStyle(20);
	g1->SetMarkerSize(0.7);
	g1->Draw("AP");
	
	TLine *line1 = new TLine(20, 0, 1040, 0);
	line1->SetLineWidth(3);
	line1->SetLineColor(kGray+2);
	line1->SetLineStyle(9);
	line1->Draw();
	
	return 0;
}
