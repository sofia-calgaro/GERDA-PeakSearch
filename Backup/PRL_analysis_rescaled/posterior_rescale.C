// Macro to rescale the x-axis of a posterior distribution
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <../json.hpp>
using namespace std;
using json = nlohmann::json;

int posterior_rescale() {

	int thr = 194;
	int det = 1;
	int phase = 0; // 0 = II; 1 = II+

	// import efficiencies (fill arrray with json object values)
	long double eff_coax_II_riz[5260][2]={0}, eff_BEGe_II_riz[5260][2]={0};
	ifstream file_riz("/home/sofia/Analysis/SuperWIMPs_couplings/efficiency_Rizalina/TotEnCorrectionLAr.json");
	json jread_riz;
	file_riz >> jread_riz;
	file_riz.close();
	
	json energy = jread_riz["energy"];
	json enrBEGe = jread_riz["enrBEGe"];
	json enrCoax = jread_riz["enrCoax"];
	int j = 0;
	for ( auto i=energy.begin(); i!=energy.end(); ++i ) { // energy column
		eff_coax_II_riz[j][0] = i.value();
		eff_BEGe_II_riz[j][0] = i.value();
		j++;
	}
	j = 0;
	for ( auto i=enrBEGe.begin(); i!=enrBEGe.end(); ++i ) { // enrBEGe eff. column
		eff_BEGe_II_riz[j][1] = i.value();
		j++;
	}
	j = 0;
	for ( auto i=enrCoax.begin(); i!=enrCoax.end(); ++i ) { // enrCoax eff. column
		eff_coax_II_riz[j][1] = i.value();
		j++;
	}

	    for ( int i=0; i<941; i++ ) {
	    	    int E0_start = 60;
		    int row_eff = i+E0_start-40;		
		    int E0 = i+E0_start;
		    if ( E0 < E0_start+10 ) cout << " E0 = " << E0 << "\t E0_eff = " << eff_BEGe_II_riz[row_eff][0] << "\t|\t" << eff_coax_II_riz[row_eff][0] << endl;
	    
	    	    string dir_analysis = "53_93_BEGe_PSD_ConstantP/";
	    	    string dir_to_rescale = "MarginalizedRESCALED/" + dir_analysis;
	    	    DIR *dir = opendir(dir_to_rescale.c_str());
		    if ( !dir ) system(("mkdir -p " + dir_to_rescale).c_str());
		    else closedir(dir);
		    string f_output_name = dir_to_rescale + to_string(E0) + ".root"; 
	    	    TFile *f_output = new TFile(f_output_name.c_str(), "RECREATE");

		    int pol_degree = 0;
		    if ( E0<thr ) 	      { pol_degree = 2; }
		    if ( E0>=thr && E0<1700 ) { pol_degree = 1; }
		    if ( E0>=1700 ) 	      { pol_degree = 0; }
		    
		    // open file
		    string namefile = "../PRL_analysis/MarginalizedROOT/" + dir_analysis + to_string(E0) + ".root";
		    TFile *file = new TFile(namefile.c_str());

		    // get posterior
		    string inputname = "../PRL_analysis/JsonFiles/" + dir_analysis + "JsonFile" + to_string(E0) + ".json";
		    ifstream input(inputname.c_str());
		    json j_read; input >> j_read; input.close();
		    int outputK = j_read["PeakSearch"]["outputk_GammaPosition"].get<int>();
		    
		    char hName_E0[300];
		    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {
			    sprintf(hName_E0, "h1_%iGausPol%i_parameter_E0_height", E0, pol_degree);
		    }
		    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
			   sprintf(hName_E0, "h1_%iGausPol%i_1Gamma_parameter_E0_height", E0, pol_degree);
		    }
		    else {
			    sprintf(hName_E0, "h1_%iGausPol%i_2Gamma_parameter_E0_height", E0, pol_degree);
		    }
		    TH1D *h_E0 = (TH1D*)file->Get(hName_E0); h_E0->SetStats(kFALSE);

		    double x_min = h_E0->GetXaxis()->GetXmin();
		    double x_max = h_E0->GetXaxis()->GetXmax();
		    int Nbins    = h_E0->GetNbinsX();
		    double step  = (x_max-x_min) / Nbins;
		    double data[Nbins][2];	    
		    for ( int i=1; i<=Nbins; i++ ) {
		    	data[i][0] = x_min+i*step;		// x-value
		    	data[i][1] = h_E0->GetBinContent(i);	// y-value
		    }
		    
		    // load efficiencies/exposures + rescale x-values
		    double eff = 0.0;
		    if ( det==0 ) { eff = eff_coax_II_riz[row_eff][1]; }
		    if ( det==1 ) { eff = eff_BEGe_II_riz[row_eff][1]; }
		    
		    double exposure = 0.0;
		    if ( det==0 ) {
		    	    /*if ( E0<thr ) exposure = 6.9; 	// Rizalina
			    if ( E0>=thr ) exposure = 28.1;*/
			    if ( E0<thr ) exposure = 7.4881;	// only PSD
			    if ( E0>=thr ) exposure = 28.6383;
			    /*if ( E0<thr ) exposure = 20.6676; // only PSD + no PSD
			    if ( E0>=thr ) exposure = 41.8177;*/
		    }
		    if ( det==1 ) {
			    /*if ( E0<thr ) exposure = 7.7; 	// Rizalina
			    if ( E0>=thr ) exposure = 30.8;*/
			    if ( E0<thr ) exposure = 8.28657;	// only PSD
			    if ( E0>=thr ) exposure = 31.4597;
			    /*if ( E0<thr ) exposure = 30.5489; // only PSD + no PSD
			    if ( E0>=thr ) exposure = 54.9284;*/
		    }
		    if ( det==2 ) {
			    exposure = 8.58872;	  // only PSD
			    //exposure = 8.77469; // only PSD + no PSD
		    }
		    for ( int i=1; i<=Nbins; i++ ) { data[i][0] = (data[i][0] * eff) / exposure; }
		    
		    // fill new histogram
		    int end = Nbins-1;
		    double x_min_new = data[0][0];
		    double x_max_new = data[end][0];
		    TH1D *h_E0_new = new TH1D("h_E0_new", "h_E0_new", Nbins, x_min_new, x_max_new);
		    h_E0_new->GetYaxis()->SetTitle("P(E0_height | Data)"); h_E0_new->GetXaxis()->SetTitle("E0_height [(events*#epsilon) / (kg*yr)]");
		    for ( int i=1; i<Nbins; i++ ) { h_E0_new->SetBinContent(i, data[i][1]); }

		    f_output->WriteTObject(h_E0_new);
		    f_output->Close();
		    file->Close();
	    }
	    
	    return 0;
}
