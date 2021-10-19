#include <fstream>
#include <iostream>

using namespace std;

int OnDetectors() {

	TCanvas *c_II = new TCanvas();
	c_II->SetGridy();
	TMultiGraph *mg_II = new TMultiGraph();
	TGraphErrors *g_53_93_BEGe = new TGraphErrors("53_93_ONdetectors_BEGe.txt");	
	TGraphErrors *g_53_93_coax = new TGraphErrors("53_93_ONdetectors_coax.txt");	
	TGraphErrors *g_53_93_coax_nat = new TGraphErrors("53_93_ONdetectors_coax_nat.txt");	
	g_53_93_BEGe->SetMarkerColor(kBlue);
	g_53_93_BEGe->SetMarkerStyle(20);
	g_53_93_BEGe->SetMarkerSize(1.25);
	g_53_93_BEGe->GetYaxis()->SetTitle("Detector ID");
	g_53_93_BEGe->GetXaxis()->SetTitle("# run");
	g_53_93_coax->SetMarkerColor(kRed);
	g_53_93_coax->SetMarkerStyle(21);
	g_53_93_coax->SetMarkerSize(1.25);
	g_53_93_coax->GetYaxis()->SetTitle("Detector ID");
	g_53_93_coax->GetXaxis()->SetTitle("# run");
	g_53_93_coax_nat->SetMarkerColor(kRed);
	g_53_93_coax_nat->SetMarkerStyle(25);
	g_53_93_coax_nat->SetMarkerSize(1.25);
	g_53_93_coax_nat->GetYaxis()->SetTitle("Detector ID");
	g_53_93_coax_nat->GetXaxis()->SetTitle("# run");
	mg_II->Add(g_53_93_BEGe);
	mg_II->Add(g_53_93_coax);
	mg_II->Add(g_53_93_coax_nat);
	mg_II->SetTitle("Phase II - ON detectors");
	mg_II->GetYaxis()->SetTitle("Detector ID");
	mg_II->GetXaxis()->SetTitle("# run");
	mg_II->GetYaxis()->SetRangeUser(-1, 40);
	mg_II->GetXaxis()->SetRangeUser(52, 94);
	mg_II->Draw("AP");
	
	TCanvas *c_IIp = new TCanvas();
	c_IIp->SetGridy();
	TMultiGraph *mg_IIp = new TMultiGraph();
	TGraphErrors *g_94_114_BEGe = new TGraphErrors("94_114_ONdetectors_BEGe.txt");	
	TGraphErrors *g_94_114_coax = new TGraphErrors("94_114_ONdetectors_coax.txt");	
	TGraphErrors *g_94_114_IC = new TGraphErrors("94_114_ONdetectors_IC.txt");	
	g_94_114_BEGe->SetMarkerColor(kBlue);
	g_94_114_BEGe->SetMarkerStyle(20);
	g_94_114_BEGe->SetMarkerSize(1.25);
	g_94_114_BEGe->GetYaxis()->SetTitle("Detector ID");
	g_94_114_BEGe->GetXaxis()->SetTitle("# run");
	g_94_114_coax->SetMarkerColor(kRed);
	g_94_114_coax->SetMarkerStyle(21);
	g_94_114_coax->SetMarkerSize(1.25);
	g_94_114_coax->GetYaxis()->SetTitle("Detector ID");
	g_94_114_coax->GetXaxis()->SetTitle("# run");
	g_94_114_IC->SetMarkerColor(kGreen+1);
	g_94_114_IC->SetMarkerStyle(34);
	g_94_114_IC->SetMarkerSize(1.25);
	g_94_114_IC->GetYaxis()->SetTitle("Detector ID");
	g_94_114_IC->GetXaxis()->SetTitle("# run");
	mg_IIp->Add(g_94_114_BEGe);
	mg_IIp->Add(g_94_114_coax);
	mg_IIp->Add(g_94_114_IC);
	mg_IIp->SetTitle("Phase II+ - ON detectors");
	mg_IIp->GetYaxis()->SetTitle("Detector ID");
	mg_IIp->GetXaxis()->SetTitle("# run");
	mg_IIp->GetYaxis()->SetRangeUser(-1, 41);
	mg_IIp->GetXaxis()->SetRangeUser(93, 115);
	mg_IIp->Draw("AP");
	
	return 0;
}
