// Available functions:
//	- sample_BATpdf(): for a fixed value of energy, it fits BAT fit-bkg-results pdfs with a Gaussian and then samples from it

#include <fstream>
#include <vector>
#include <string>


double FindSigma(int energy, int det) {

   double a=0, b=0;
   
   if ( det==0 ) { // coax
   	a = 0.985;
   	b = 10.73e-4; 
   }
   if ( det==1 ) { // BEGe
   	a = 0.551;
   	b = 4.294e-4; 
   }
   if ( det==2 ) { // IC
   	a = 0.28;
   	b = 5.83e-4; 
   }

   double sigma =  sqrt( a + b*energy );

   return sigma;
}

void sample_BATpdf(int E0, int pol_degree, int k, int outputK, const char *root_file, int det) {

	char name[200];
	if ( det==0 ) sprintf(name,"/home/sofia/Analysis/Data2/MarginalizedROOT/coax/%i.root", E0);
	if ( det==1 ) sprintf(name,"/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/53_114/BEGe/%i.root", E0);
	if ( det==2 ) sprintf(name,"/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/IC/%i.root", E0);
	TFile *file = new TFile(name);
	
	double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
	int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
	
	// 1 gamma peak
	double E1 = 0;
	if ( k>=0 && k<numGamma ) { E1 = E_gamma[k]; } // when k=numGamma, we do not have gamma peaks ( we leave E1=0 )
	// 2 gamma peak
	double E2 = 0;
	if ( outputK==8 || outputK==9 || outputK==10 || outputK==11 || outputK==16 || outputK==17 || outputK==19 ) {
		E2 = E_gamma[k+1];
	}
	
	// sample from pdf
	char hName_p0[300], hName_p1[300], hName_p2[300], hName_E1[300], hName_E2[300];
	double p0=0, p1=0, p2=0, hE1=-1, hE2=-1;
	const int xL = E0 - 20;
	const int xR = E0 + 20;
	const int bins = xR - xL;
	TH1D *LAr_MC = new TH1D("LAr_MC", "LAr_MC", 5200, 0, 5200);
	LAr_MC->SetStats(kFALSE);
	
	std::ofstream output("bin_content_MC.txt");
	
	// E0>195
	if ( pol_degree==1 ) {
		if ( E1!=0 ) {
			// 2 gamma peaks 
			if ( E2!=0 ) {
				sprintf(hName_p0, "h1_%iGausPol1_2Gamma_parameter_p0", E0);
				sprintf(hName_p1, "h1_%iGausPol1_2Gamma_parameter_p1", E0);
				sprintf(hName_E1, "h1_%iGausPol1_2Gamma_parameter_E1_height", E0);
				sprintf(hName_E2, "h1_%iGausPol1_2Gamma_parameter_E2_height", E0);
				
				TH1D *h_p0 = (TH1D*)file->Get(hName_p0);
				TH1D *h_p1 = (TH1D*)file->Get(hName_p1);
				TH1D *h_E1 = (TH1D*)file->Get(hName_E1);
				TH1D *h_E2 = (TH1D*)file->Get(hName_E2);
				
				// p0
				int bin_min_p0 = h_p0->GetBinContent(1);
				int bin_max_p0 = h_p0->GetBinContent(h_p0->GetNbinsX());
				TF1 *f_p0 = new TF1("f_p0", "gaus(0)", bin_min_p0, bin_max_p0);
				f_p0->SetParameter(0, h_p0->GetBinContent(h_p0->GetMaximumBin()));
				f_p0->SetParameter(1, h_p0->GetXaxis()->GetBinCenter(h_p0->GetMaximumBin()));
				h_p0->Fit("f_p0", "RQNO");
				// p1
				int bin_min_p1 = h_p1->GetBinContent(1);
				int bin_max_p1 = h_p1->GetBinContent(h_p1->GetNbinsX());
				TF1 *f_p1 = new TF1("f_p1", "gaus(0)", bin_min_p1, bin_max_p1);
				f_p1->SetParameter(0, h_p1->GetBinContent(h_p1->GetMaximumBin()));
				f_p1->SetParameter(1, h_p1->GetXaxis()->GetBinCenter(h_p1->GetMaximumBin()));
				h_p1->Fit("f_p1", "RQNO");
				// E1
				int bin_min_E1 = h_E1->GetBinContent(1);
				int bin_max_E1 = h_E1->GetBinContent(h_E1->GetNbinsX());
				double GM_E1=0, sigma_E1=0;
				TF1 *f_E1 = new TF1("f_E1", "gaus(0)", bin_min_E1, bin_max_E1);
				f_E1->SetParameter(0, h_E1->GetBinContent(h_E1->GetMaximumBin()));
				f_E1->SetParameter(1, h_E1->GetXaxis()->GetBinCenter(h_E1->GetMaximumBin()));
				if ( (h_E1->GetBinContent(h_E1->GetMaximumBin()))/(bin_min_E1+0.0) > 1.05 ) { h_E1->Fit("f_E1", "RQNO"); }
				else {
					GM_E1 = h_E1->GetXaxis()->GetBinCenter(h_E1->GetMaximumBin());
					for ( int k=1; k<=h_E1->GetNbinsX(); k++ ) { h_E1->SetBinContent(k, h_E1->GetBinContent(k+h_E1->FindBin(GM_E1)-1)); } // shift to left
					double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
					double q[7] = {0};
					h_E1->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
					sigma_E1 = q[1] - q[0]; // qt_34%
				}
				// E2
				int bin_min_E2 = h_E2->GetBinContent(1);
				int bin_max_E2 = h_E2->GetBinContent(h_E2->GetNbinsX());
				double GM_E2=0, sigma_E2=0;
				TF1 *f_E2 = new TF1("f_E2", "gaus(0)", bin_min_E2, bin_max_E2);
				f_E2->SetParameter(0, h_E2->GetBinContent(h_E2->GetMaximumBin()));
				f_E2->SetParameter(1, h_E2->GetXaxis()->GetBinCenter(h_E2->GetMaximumBin()));
				if ( (h_E2->GetBinContent(h_E2->GetMaximumBin()))/(bin_min_E2+0.0) > 1.05 ) { h_E2->Fit("f_E2", "RQNO"); }
				else {
					GM_E2 = h_E2->GetXaxis()->GetBinCenter(h_E2->GetMaximumBin());
					for ( int k=1; k<=h_E2->GetNbinsX(); k++ ) { h_E2->SetBinContent(k, h_E2->GetBinContent(k+h_E2->FindBin(GM_E2)-1)); } // shift to left
					double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
					double q[7] = {0};
					h_E2->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
					sigma_E2 = q[1] - q[0]; // qt_34%
				}
				
				TRandom3 *r_p0 = new TRandom3(0);
				p0 = r_p0->Gaus(f_p0->GetParameter(1), f_p0->GetParameter(2));
				TRandom3 *r_p1 = new TRandom3(0);
				p1 = r_p1->Gaus(f_p1->GetParameter(1), f_p1->GetParameter(2));
				while ( hE1<0 ) {
					TRandom3 *r_E1 = new TRandom3(0);
					if ( (h_E1->GetBinContent(h_E1->GetMaximumBin()))/(bin_min_E1+0.0) > 1.05 ) { hE1 = r_E1->Gaus(f_E1->GetParameter(1), f_E1->GetParameter(2)); }
					else { hE1 = r_E1->Gaus(GM_E1, sigma_E1); }
				}
				while ( hE2<0 ) {
					TRandom3 *r_E2 = new TRandom3(0);
					if ( (h_E2->GetBinContent(h_E2->GetMaximumBin()))/(bin_min_E2+0.0) > 1.05 ) { hE2 = r_E2->Gaus(f_E2->GetParameter(1), f_E2->GetParameter(2)); }
					else { hE2 = r_E2->Gaus(GM_E2, sigma_E2); }
				}
				std::cout << " p0 = " << p0 << std::endl;
				std::cout << " p1 = " << p1 << std::endl;
				std::cout << " E1 = " << hE1 << std::endl;
				std::cout << " E2 = " << hE2 << std::endl;
				
				for ( int i=1; i<=xL; i++) {
					LAr_MC->SetBinContent(i, 0);
					output << 0 << std::endl;
				}
				for ( int i=xL+1; i<=xR; i++ ) {
					double y_sim_pol = p0 + p1*(i-E0);
					double y_sim_gaus = hE1*TMath::Gaus(i, E1, FindSigma(E1, det), true) + hE2*TMath::Gaus(i, E2, FindSigma(E2, det), true);
					
					LAr_MC->SetBinContent(i, y_sim_pol+y_sim_gaus);
					output << y_sim_pol+y_sim_gaus << std::endl;
				}
				for ( int i=xR+1; i<=5200; i++) {
					LAr_MC->SetBinContent(i, 0);
					output << 0 << std::endl;
				}
			}
			// 1 gamma peak
			else {
				sprintf(hName_p0, "h1_%iGausPol1_1Gamma_parameter_p0", E0);
				sprintf(hName_p1, "h1_%iGausPol1_1Gamma_parameter_p1", E0);
				sprintf(hName_E1, "h1_%iGausPol1_1Gamma_parameter_E1_height", E0);
				
				TH1D *h_p0 = (TH1D*)file->Get(hName_p0);
				TH1D *h_p1 = (TH1D*)file->Get(hName_p1);
				TH1D *h_E1 = (TH1D*)file->Get(hName_E1);
				
				// p0
				int bin_min_p0 = h_p0->GetBinContent(1);
				int bin_max_p0 = h_p0->GetBinContent(h_p0->GetNbinsX());
				TF1 *f_p0 = new TF1("f_p0", "gaus(0)", bin_min_p0, bin_max_p0);
				f_p0->SetParameter(0, h_p0->GetMaximumBin());
				f_p0->SetParameter(1, h_p0->GetXaxis()->GetBinCenter(h_p0->GetMaximumBin()));
				h_p0->Fit("f_p0", "RQNO");
				// p1
				int bin_min_p1 = h_p1->GetBinContent(1);
				int bin_max_p1 = h_p1->GetBinContent(h_p1->GetNbinsX());
				TF1 *f_p1 = new TF1("f_p1", "gaus(0)", bin_min_p1, bin_max_p1);
				f_p1->SetParameter(0, h_p1->GetMaximumBin());
				f_p1->SetParameter(1, h_p1->GetXaxis()->GetBinCenter(h_p1->GetMaximumBin()));
				h_p1->Fit("f_p1", "RQNO");
				// E1
				int bin_min_E1 = h_E1->GetBinContent(1);
				int bin_max_E1 = h_E1->GetBinContent(h_E1->GetNbinsX());
				double GM_E1=0, sigma_E1=0;
				TF1 *f_E1 = new TF1("f_E1", "gaus(0)", bin_min_E1, bin_max_E1);
				f_E1->SetParameter(0, h_E1->GetBinContent(h_E1->GetMaximumBin()));
				f_E1->SetParameter(1, h_E1->GetXaxis()->GetBinCenter(h_E1->GetMaximumBin()));
				if ( (h_E1->GetBinContent(h_E1->GetMaximumBin()))/(bin_min_E1+0.0) > 1.05 ) { h_E1->Fit("f_E1", "RQNO"); }
				else {
					GM_E1 = h_E1->GetXaxis()->GetBinCenter(h_E1->GetMaximumBin());
					for ( int k=1; k<=h_E1->GetNbinsX(); k++ ) { h_E1->SetBinContent(k, h_E1->GetBinContent(k+h_E1->FindBin(GM_E1)-1)); } // shift to left
					double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
					double q[7] = {0};
					h_E1->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
					sigma_E1 = q[1] - q[0]; // qt_34%
				}
				
				TRandom3 *r_p0 = new TRandom3(0);
				p0 = r_p0->Gaus(f_p0->GetParameter(1), f_p0->GetParameter(2));
				TRandom3 *r_p1 = new TRandom3(0);
				p1 = r_p1->Gaus(f_p1->GetParameter(1), f_p1->GetParameter(2));
				while ( hE1<0 ) {
					TRandom3 *r_E1 = new TRandom3(0);
					if ( (h_E1->GetBinContent(h_E1->GetMaximumBin()))/(bin_min_E1+0.0) > 1.05 ) { hE1 = r_E1->Gaus(f_E1->GetParameter(1), f_E1->GetParameter(2)); }
					else { hE1 = r_E1->Gaus(GM_E1, sigma_E1); }
				}
				std::cout << " p0 = " << p0 << std::endl;
				std::cout << " p1 = " << p1 << std::endl;
				std::cout << " E1 = " << hE1 << std::endl;
				
				for ( int i=1; i<=xL; i++) {
					LAr_MC->SetBinContent(i, 0);
					output << 0 << std::endl;
				}
				for ( int i=xL+1; i<=xR; i++ ) {
					double y_sim_pol = p0 + p1*(i-E0);
					double y_sim_gaus = hE1*TMath::Gaus(i, E1, FindSigma(E1, det), true);
					
					LAr_MC->SetBinContent(i, y_sim_pol+y_sim_gaus);
					output << y_sim_pol+y_sim_gaus << std::endl;
				}
				for ( int i=xR+1; i<=5200; i++) {
					LAr_MC->SetBinContent(i, 0);
					output << 0 << std::endl;
				}
			}
		}
		// 0 gamma peaks
		else {
			sprintf(hName_p0, "h1_%iGausPol1_parameter_p0", E0);
			sprintf(hName_p1, "h1_%iGausPol1_parameter_p1", E0);
			
			TH1D *h_p0 = (TH1D*)file->Get(hName_p0);
			TH1D *h_p1 = (TH1D*)file->Get(hName_p1);
				
			// p0
			int bin_min_p0 = h_p0->GetBinContent(1);
			int bin_max_p0 = h_p0->GetBinContent(h_p0->GetNbinsX());
			TF1 *f_p0 = new TF1("f_p0", "gaus(0)", bin_min_p0, bin_max_p0);
			f_p0->SetParameter(0, h_p0->GetMaximumBin());
			f_p0->SetParameter(1, h_p0->GetXaxis()->GetBinCenter(h_p0->GetMaximumBin()));
			h_p0->Fit("f_p0", "RQNO");
			// p1
			int bin_min_p1 = h_p1->GetBinContent(1);
			int bin_max_p1 = h_p1->GetBinContent(h_p1->GetNbinsX());
			TF1 *f_p1 = new TF1("f_p1", "gaus(0)", bin_min_p1, bin_max_p1);
			f_p1->SetParameter(0, h_p1->GetMaximumBin());
			f_p1->SetParameter(1, h_p1->GetXaxis()->GetBinCenter(h_p1->GetMaximumBin()));
			h_p1->Fit("f_p1", "RQNO");
				
			TRandom3 *r_p0 = new TRandom3(0);
			p0 = r_p0->Gaus(f_p0->GetParameter(1), f_p0->GetParameter(2));
			TRandom3 *r_p1 = new TRandom3(0);
			p1 = r_p1->Gaus(f_p1->GetParameter(1), f_p1->GetParameter(2));
			std::cout << " p0 = " << p0 << std::endl;
			std::cout << " p1 = " << p1 << std::endl;
			
			for ( int i=1; i<=xL; i++) {
				LAr_MC->SetBinContent(i, 0);
				output << 0 << std::endl;
			}
			for ( int i=xL+1; i<=xR; i++ ) {
				double y_sim_pol = p0 + p1*(i-E0);
				
				LAr_MC->SetBinContent(i, y_sim_pol);
				output << y_sim_pol << std::endl;
			}
			for ( int i=xR+1; i<=5200; i++) {
				LAr_MC->SetBinContent(i, 0);
				output << 0 << std::endl;
			}
		}
	}
	// E0<195
	if ( pol_degree==2 ) {
		if ( E1!=0 ) {
			// 2 gamma peaks
			if ( E2!=0 ) {
				sprintf(hName_p0, "h1_%iGausPol2_2Gamma_parameter_p0", E0);
				sprintf(hName_p1, "h1_%iGausPol2_2Gamma_parameter_p1", E0);
				sprintf(hName_p2, "h1_%iGausPol2_2Gamma_parameter_p2", E0);
				sprintf(hName_E1, "h1_%iGausPol2_2Gamma_parameter_E1_height", E0);
				sprintf(hName_E2, "h1_%iGausPol2_2Gamma_parameter_E2_height", E0);
				
				TH1D *h_p0 = (TH1D*)file->Get(hName_p0);
				TH1D *h_p1 = (TH1D*)file->Get(hName_p1);
				TH1D *h_p2 = (TH1D*)file->Get(hName_p2);
				TH1D *h_E1 = (TH1D*)file->Get(hName_E1);
				TH1D *h_E2 = (TH1D*)file->Get(hName_E2);
				
				// p0
				int bin_min_p0 = h_p0->GetBinContent(1);
				int bin_max_p0 = h_p0->GetBinContent(h_p0->GetNbinsX());
				TF1 *f_p0 = new TF1("f_p0", "gaus(0)", bin_min_p0, bin_max_p0);
				f_p0->SetParameter(0, h_p0->GetMaximumBin());
				f_p0->SetParameter(1, h_p0->GetXaxis()->GetBinCenter(h_p0->GetMaximumBin()));
				h_p0->Fit("f_p0", "RQNO");
				// p1
				int bin_min_p1 = h_p1->GetBinContent(1);
				int bin_max_p1 = h_p1->GetBinContent(h_p1->GetNbinsX());
				TF1 *f_p1 = new TF1("f_p1", "gaus(0)", bin_min_p1, bin_max_p1);
				f_p1->SetParameter(0, h_p1->GetMaximumBin());
				f_p1->SetParameter(1, h_p1->GetXaxis()->GetBinCenter(h_p1->GetMaximumBin()));
				h_p1->Fit("f_p1", "RQNO");
				// p2
				int bin_min_p2 = h_p2->GetBinContent(1);
				int bin_max_p2 = h_p2->GetBinContent(h_p2->GetNbinsX());
				TF1 *f_p2 = new TF1("f_p2", "gaus(0)", bin_min_p2, bin_max_p2);
				f_p2->SetParameter(0, h_p2->GetMaximumBin());
				f_p2->SetParameter(1, h_p2->GetXaxis()->GetBinCenter(h_p2->GetMaximumBin()));
				h_p2->Fit("f_p2", "RQNO");
				// E1
				int bin_min_E1 = h_E1->GetBinContent(1);
				int bin_max_E1 = h_E1->GetBinContent(h_E1->GetNbinsX());
				double GM_E1=0, sigma_E1=0;
				TF1 *f_E1 = new TF1("f_E1", "gaus(0)", bin_min_E1, bin_max_E1);
				f_E1->SetParameter(0, h_E1->GetBinContent(h_E1->GetMaximumBin()));
				f_E1->SetParameter(1, h_E1->GetXaxis()->GetBinCenter(h_E1->GetMaximumBin()));
				if ( (h_E1->GetBinContent(h_E1->GetMaximumBin()))/(bin_min_E1+0.0) > 1.05 ) { h_E1->Fit("f_E1", "RQNO"); }
				else {
					GM_E1 = h_E1->GetXaxis()->GetBinCenter(h_E1->GetMaximumBin());
					for ( int k=1; k<=h_E1->GetNbinsX(); k++ ) { h_E1->SetBinContent(k, h_E1->GetBinContent(k+h_E1->FindBin(GM_E1)-1)); } // shift to left
					double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
					double q[7] = {0};
					h_E1->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
					sigma_E1 = q[1] - q[0]; // qt_34%
				}
				// E2
				int bin_min_E2 = h_E2->GetBinContent(1);
				int bin_max_E2 = h_E2->GetBinContent(h_E2->GetNbinsX());
				double GM_E2=0, sigma_E2=0;
				TF1 *f_E2 = new TF1("f_E2", "gaus(0)", bin_min_E2, bin_max_E2);
				f_E2->SetParameter(0, h_E2->GetBinContent(h_E2->GetMaximumBin()));
				f_E2->SetParameter(1, h_E2->GetXaxis()->GetBinCenter(h_E2->GetMaximumBin()));
				if ( (h_E2->GetBinContent(h_E2->GetMaximumBin()))/(bin_min_E2+0.0) > 1.05 ) { h_E2->Fit("f_E2", "RQNO"); }
				else {
					GM_E2 = h_E2->GetXaxis()->GetBinCenter(h_E2->GetMaximumBin());
					for ( int k=1; k<=h_E2->GetNbinsX(); k++ ) { h_E2->SetBinContent(k, h_E2->GetBinContent(k+h_E2->FindBin(GM_E2)-1)); } // shift to left
					double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
					double q[7] = {0};
					h_E2->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
					sigma_E2 = q[1] - q[0]; // qt_34%
				}
				
				TRandom3 *r_p0 = new TRandom3(0);
				p0 = r_p0->Gaus(f_p0->GetParameter(1), f_p0->GetParameter(2));
				TRandom3 *r_p1 = new TRandom3(0);
				p1 = r_p1->Gaus(f_p1->GetParameter(1), f_p1->GetParameter(2));
				TRandom3 *r_p2 = new TRandom3(0);
				p2 = r_p2->Gaus(f_p2->GetParameter(1), f_p2->GetParameter(2));
				while ( hE1<0 ) {
					TRandom3 *r_E1 = new TRandom3(0);
					if ( (h_E1->GetBinContent(h_E1->GetMaximumBin()))/(bin_min_E1+0.0) > 1.05 ) { hE1 = r_E1->Gaus(f_E1->GetParameter(1), f_E1->GetParameter(2)); }
					else { hE1 = r_E1->Gaus(GM_E1, sigma_E1); }
				}
				while ( hE2<0 ) {
					TRandom3 *r_E2 = new TRandom3(0);
					if ( (h_E2->GetBinContent(h_E2->GetMaximumBin()))/(bin_min_E2+0.0) > 1.05 ) { hE2 = r_E2->Gaus(f_E2->GetParameter(1), f_E2->GetParameter(2)); }
					else { hE2 = r_E2->Gaus(GM_E2, sigma_E2); }
				}
				std::cout << " p0 = " << p0 << std::endl;
				std::cout << " p1 = " << p1 << std::endl;
				std::cout << " p2 = " << p2 << std::endl;
				std::cout << " E1 = " << hE1 << std::endl;
				std::cout << " E2 = " << hE2 << std::endl;
				
				for ( int i=1; i<=xL; i++) {
					LAr_MC->SetBinContent(i, 0);
					output << 0 << std::endl;
				}
				for ( int i=xL+1; i<=xR; i++ ) {
					double y_sim_pol = p0 + p1*(i-E0) + p2*(i-E0)*(i-E0);
					double y_sim_gaus = hE1*TMath::Gaus(i, E1, FindSigma(E1, det), true) + hE2*TMath::Gaus(i, E2, FindSigma(E2, det), true);
					
					LAr_MC->SetBinContent(i, y_sim_pol+y_sim_gaus);
					output << y_sim_pol+y_sim_gaus << std::endl;
				}
				for ( int i=xR+1; i<=5200; i++) {
					LAr_MC->SetBinContent(i, 0);
					output << 0 << std::endl;
				}
			}
			// 1 gamma peak
			else {
				sprintf(hName_p0, "h1_%iGausPol2_1Gamma_parameter_p0", E0);
				sprintf(hName_p1, "h1_%iGausPol2_1Gamma_parameter_p1", E0);
				sprintf(hName_p2, "h1_%iGausPol2_1Gamma_parameter_p2", E0);
				sprintf(hName_E1, "h1_%iGausPol2_1Gamma_parameter_E1_height", E0);
				
				TH1D *h_p0 = (TH1D*)file->Get(hName_p0);
				TH1D *h_p1 = (TH1D*)file->Get(hName_p1);
				TH1D *h_p2 = (TH1D*)file->Get(hName_p2);
				TH1D *h_E1 = (TH1D*)file->Get(hName_E1);
				
				// p0
				int bin_min_p0 = h_p0->GetBinContent(1);
				int bin_max_p0 = h_p0->GetBinContent(h_p0->GetNbinsX());
				TF1 *f_p0 = new TF1("f_p0", "gaus(0)", bin_min_p0, bin_max_p0);
				f_p0->SetParameter(0, h_p0->GetMaximumBin());
				f_p0->SetParameter(1, h_p0->GetXaxis()->GetBinCenter(h_p0->GetMaximumBin()));
				h_p0->Fit("f_p0", "RQNO");
				// p1
				int bin_min_p1 = h_p1->GetBinContent(1);
				int bin_max_p1 = h_p1->GetBinContent(h_p1->GetNbinsX());
				TF1 *f_p1 = new TF1("f_p1", "gaus(0)", bin_min_p1, bin_max_p1);
				f_p1->SetParameter(0, h_p1->GetMaximumBin());
				f_p1->SetParameter(1, h_p1->GetXaxis()->GetBinCenter(h_p1->GetMaximumBin()));
				h_p1->Fit("f_p1", "RQNO");
				// p2
				int bin_min_p2 = h_p2->GetBinContent(1);
				int bin_max_p2 = h_p2->GetBinContent(h_p2->GetNbinsX());
				TF1 *f_p2 = new TF1("f_p2", "gaus(0)", bin_min_p2, bin_max_p2);
				f_p2->SetParameter(0, h_p2->GetMaximumBin());
				f_p2->SetParameter(1, h_p2->GetXaxis()->GetBinCenter(h_p2->GetMaximumBin()));
				h_p2->Fit("f_p2", "RQNO");
				// E1
				int bin_min_E1 = h_E1->GetBinContent(1);
				int bin_max_E1 = h_E1->GetBinContent(h_E1->GetNbinsX());
				double GM_E1=0, sigma_E1=0;
				TF1 *f_E1 = new TF1("f_E1", "gaus(0)", bin_min_E1, bin_max_E1);
				f_E1->SetParameter(0, h_E1->GetBinContent(h_E1->GetMaximumBin()));
				f_E1->SetParameter(1, h_E1->GetXaxis()->GetBinCenter(h_E1->GetMaximumBin()));
				if ( (h_E1->GetBinContent(h_E1->GetMaximumBin()))/(bin_min_E1+0.0) > 1.05 ) { h_E1->Fit("f_E1", "RQNO"); }
				else {
					GM_E1 = h_E1->GetXaxis()->GetBinCenter(h_E1->GetMaximumBin());
					for ( int k=1; k<=h_E1->GetNbinsX(); k++ ) { h_E1->SetBinContent(k, h_E1->GetBinContent(k+h_E1->FindBin(GM_E1)-1)); } // shift to left
					double p[7] = {0, 0.3415, 0.46, 0.50, 0.84, 0.90, 0.95};
					double q[7] = {0};
					h_E1->GetQuantiles(7, q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
					sigma_E1 = q[1] - q[0]; // qt_34%
				}
				
				TRandom3 *r_p0 = new TRandom3(0);
				p0 = r_p0->Gaus(f_p0->GetParameter(1), f_p0->GetParameter(2));
				TRandom3 *r_p1 = new TRandom3(0);
				p1 = r_p1->Gaus(f_p1->GetParameter(1), f_p1->GetParameter(2));
				TRandom3 *r_p2 = new TRandom3(0);
				p2 = r_p2->Gaus(f_p2->GetParameter(1), f_p2->GetParameter(2));
				while ( hE1<0 ) {
					TRandom3 *r_E1 = new TRandom3(0);
					if ( (h_E1->GetBinContent(h_E1->GetMaximumBin()))/(bin_min_E1+0.0) > 1.05 ) { hE1 = r_E1->Gaus(f_E1->GetParameter(1), f_E1->GetParameter(2)); }
					else { hE1 = r_E1->Gaus(GM_E1, sigma_E1); }
				}
				std::cout << " p0 = " << p0 << std::endl;
				std::cout << " p1 = " << p1 << std::endl;
				std::cout << " p2 = " << p2 << std::endl;
				std::cout << " E1 = " << hE1 << std::endl;
				
				for ( int i=1; i<=xL; i++) {
					LAr_MC->SetBinContent(i, 0);
					output << 0 << std::endl;
				}
				for ( int i=xL+1; i<=xR; i++ ) {
					double y_sim_pol = p0 + p1*(i-E0) + p2*(i-E0)*(i-E0);
					double y_sim_gaus = hE1*TMath::Gaus(i, E1, FindSigma(E1, det), true);
					
					LAr_MC->SetBinContent(i, y_sim_pol+y_sim_gaus);
					output << y_sim_pol+y_sim_gaus << std::endl;
				}
				for ( int i=xR+1; i<=5200; i++) {
					LAr_MC->SetBinContent(i, 0);
					output << 0 << std::endl;
				}
			}
		}
		// 0 gamma peaks
		else {
			sprintf(hName_p0, "h1_%iGausPol2_parameter_p0", E0);
			sprintf(hName_p1, "h1_%iGausPol2_parameter_p1", E0);
			sprintf(hName_p2, "h1_%iGausPol2_parameter_p2", E0);
			
			TH1D *h_p0 = (TH1D*)file->Get(hName_p0);
			TH1D *h_p1 = (TH1D*)file->Get(hName_p1);
			TH1D *h_p2 = (TH1D*)file->Get(hName_p2);
			
			// p0
			int bin_min_p0 = h_p0->GetBinContent(1);
			int bin_max_p0 = h_p0->GetBinContent(h_p0->GetNbinsX());
			TF1 *f_p0 = new TF1("f_p0", "gaus(0)", bin_min_p0, bin_max_p0);
			f_p0->SetParameter(0, h_p0->GetMaximumBin());
			f_p0->SetParameter(1, h_p0->GetXaxis()->GetBinCenter(h_p0->GetMaximumBin()));
			h_p0->Fit("f_p0", "RQNO");
			// p1
			int bin_min_p1 = h_p1->GetBinContent(1);
			int bin_max_p1 = h_p1->GetBinContent(h_p1->GetNbinsX());
			TF1 *f_p1 = new TF1("f_p1", "gaus(0)", bin_min_p1, bin_max_p1);
			f_p1->SetParameter(0, h_p1->GetMaximumBin());
			f_p1->SetParameter(1, h_p1->GetXaxis()->GetBinCenter(h_p1->GetMaximumBin()));
			h_p1->Fit("f_p1", "RQNO");
			// p2
			int bin_min_p2 = h_p2->GetBinContent(1);
			int bin_max_p2 = h_p2->GetBinContent(h_p2->GetNbinsX());
			TF1 *f_p2 = new TF1("f_p2", "gaus(0)", bin_min_p2, bin_max_p2);
			f_p2->SetParameter(0, h_p2->GetMaximumBin());
			f_p2->SetParameter(1, h_p2->GetXaxis()->GetBinCenter(h_p2->GetMaximumBin()));
			h_p2->Fit("f_p2", "RQNO");
			
			TRandom3 *r_p0 = new TRandom3(0);
			p0 = r_p0->Gaus(f_p0->GetParameter(1), f_p0->GetParameter(2));
			TRandom3 *r_p1 = new TRandom3(0);
			p1 = r_p1->Gaus(f_p1->GetParameter(1), f_p1->GetParameter(2));
			TRandom3 *r_p2 = new TRandom3(0);
			p2 = r_p2->Gaus(f_p2->GetParameter(1), f_p2->GetParameter(2));
			std::cout << " p0 = " << p0 << std::endl;
			std::cout << " p1 = " << p1 << std::endl;
			std::cout << " p2 = " << p2 << std::endl;
			
			for ( int i=1; i<=xL; i++) {
				LAr_MC->SetBinContent(i, 0);
				output << 0 << std::endl;
			}
			for ( int i=xL+1; i<=xR; i++ ) {
				double y_sim_pol = p0 + p1*(i-E0) + p2*(i-E0)*(i-E0);
				
				LAr_MC->SetBinContent(i, y_sim_pol);
				output << y_sim_pol << std::endl;
			}
			for ( int i=xR+1; i<=5200; i++) {
				LAr_MC->SetBinContent(i, 0);
				output << 0 << std::endl;
			}
		}
	}
	
	
	
	// attenzione perchè lo spettro va creato in +-20 keV per poter fare il pre-fit con ROOT (andare a rivedere come 
	// allargavo e ristringevo quest'intervallo in Operations.h)
	char namefile[200];
	if ( det==0 ) sprintf(namefile, "MC_spectra/coax/MCspectrum_%i.root", E0);
	if ( det==1 ) sprintf(namefile, "MC_spectra/BEGe/MCspectrum_%i.root", E0);
	if ( det==2 ) sprintf(namefile, "MC_spectra/IC/MCspectrum_%i.root", E0);
	TFile *MCspectrum = new TFile(namefile, "recreate");
	MCspectrum->WriteTObject(LAr_MC);
	MCspectrum->Close();
	output.close();
}
