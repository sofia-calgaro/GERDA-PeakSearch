int plot_warnings() {
	
	TCanvas *c1 = new TCanvas();
	TGraphErrors *g_S_height = new TGraphErrors("y_exp.txt", "%lg %lg %*lg %*lg");
	g_S_height->SetTitle("Signal hieght parameter");
	g_S_height->SetLineColor(1);
	g_S_height->SetMarkerStyle(8);
	g_S_height->Draw("AP");
	
	TCanvas *c2 = new TCanvas();
	TGraphErrors *g_p0 = new TGraphErrors("y_exp.txt", "%lg %*lg %lg %*lg");
	g_p0->SetTitle("p0 parameter");
	g_p0->SetLineColor(2);
	g_p0->SetMarkerStyle(8);
	g_p0->Draw("AP");
	
	TCanvas *c3 = new TCanvas();
	TGraphErrors *g_p1 = new TGraphErrors("y_exp.txt", "%lg %*lg %*lg %lg");
	g_p1->SetLineColor(4);
	g_p1->SetTitle("p1 parameter");
	g_p1->SetMarkerStyle(8);
	g_p1->Draw("AP");
		
 
	return 0;
}
