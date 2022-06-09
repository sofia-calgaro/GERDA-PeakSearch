// BAT
#include <BAT/BCLog.h>
#include <BAT/BCH1D.h>
#include <BAT/BCAux.h>
#include <BAT/BCHistogramFitter.h>

// ROOT
#include <TFile.h>
#include <TMath.h>
#include <TGraph.h>
#include <TLegend.h>

// MODELS
#include "VectorModel.h"

// OTHER
#include "Operations.h"
#include "args_reader.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{  
    vector<string> args(argc);
    copy(argv, argv+argc, args.begin());
  
    vector<int> inpval(14,0);
    bool found = fetch_arg(args, "--nums", inpval);
    
    if (found) {
    cout << "\n *************************" << endl;
    cout << "  E0 = " << inpval[1] << "\n  Polynomial degree = " << inpval[2];
    cout << "\n  xL = " << inpval[3] << "\n  xR = " << inpval[4] << "\n  k = " << inpval[5];
    cout << "\n  output[k] = " << inpval[6] << endl;
    cout << "\n  rng0 = " << inpval[7] << "\n  rng1 = " << inpval[8] << "\n  rng2 = " << inpval[9] << endl;
    cout << "\n  rngE0 = " << inpval[10] << "\n  rngE1 = " << inpval[11] << "\n  rngE2 = " << inpval[12] << endl;
    cout << " *************************\n" << endl;
    }
    int E0 = inpval[1];
    int thr = inpval[13];
    int k = inpval[5];
    int outputK = inpval[6];
    int pol_degree = inpval[2];
    double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
    int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
    
    //---------------------------------------------------------------------------------------------------------------------- e- EFFICIENCY LOADING   
    // phII
    char el_coax_II[300], el_bege_II[300];
    sprintf(el_coax_II, "/home/sofia/Analysis/combined_fit/efficiencies/electron/eff_enrCoax_phII.txt");
    sprintf(el_bege_II, "/home/sofia/Analysis/combined_fit/efficiencies/electron/eff_enrBEGe_phII.txt");
    std::ifstream input_el_coax_II(el_coax_II);
    std::ifstream input_el_bege_II(el_bege_II);
    double eff_coax_el_II[1400][2];
    for ( int i=0; i<1400; i++ ) {
        for ( int j=0; j<2; j++ ) {
                input_el_coax_II >> eff_coax_el_II[i][j];
        }
    }
    input_el_coax_II.close();
    double eff_bege_el_II[1400][2];
    for ( int i=0; i<1400; i++ ) {
        for ( int j=0; j<2; j++ ) {
                input_el_bege_II >> eff_bege_el_II[i][j];
        }
    }
    input_el_bege_II.close();
    // ph(II,II+)
    char el_coax_II_IIp[300], el_bege_II_IIp[300], el_ic_II_IIp[300];
    sprintf(el_coax_II_IIp, "/home/sofia/Analysis/combined_fit/efficiencies/electron/eff_enrCoax_phIIp.txt");
    sprintf(el_bege_II_IIp, "/home/sofia/Analysis/combined_fit/efficiencies/electron/eff_enrBEGe_phIIp.txt");
    sprintf(el_ic_II_IIp, "/home/sofia/Analysis/combined_fit/efficiencies/electron/eff_invCoax_phIIp.txt");
    std::ifstream input_el_coax_II_IIp(el_coax_II_IIp);
    std::ifstream input_el_bege_II_IIp(el_bege_II_IIp);
    std::ifstream input_el_ic_II_IIp(el_ic_II_IIp);
    double eff_coax_el_II_IIp[1400][2];
    for ( int i=0; i<1400; i++ ) {
        for ( int j=0; j<2; j++ ) {
                input_el_coax_II_IIp >> eff_coax_el_II_IIp[i][j];
        }
    }
    input_el_coax_II_IIp.close();
    double eff_bege_el_II_IIp[1400][2];
    for ( int i=0; i<1400; i++ ) {
        for ( int j=0; j<2; j++ ) {
                input_el_bege_II_IIp >> eff_bege_el_II_IIp[i][j];
        }
    }
    input_el_bege_II_IIp.close();
    double eff_ic_el_II_IIp[1400][2];
    for ( int i=0; i<1400; i++ ) {
        for ( int j=0; j<2; j++ ) {
                input_el_ic_II_IIp >> eff_ic_el_II_IIp[i][j];
        }
    }
    input_el_ic_II_IIp.close();
    
    //---------------------------------------------------------------------------------------------------------------------- Ge x-sec LOADING   
    std::ifstream input("/home/sofia/Analysis/super-wimps/SuperWIMPs_couplings/Ge_photo-xsec_1keV-1600keV.txt");
    double Ge_xsec[1600][2];
    for ( int i=0; i<1600; i++ ) {
    	for ( int j=0; j<2; j++ ) {
    		input >> Ge_xsec[i][j];
    	}
    }
    input.close();
    
    //---------------------------------------------------------------------------------------------------------------------- DATA LOADING   
    TFile *file_0 = new TFile("/home/sofia/gerda_data/53_93_PSD/coax/20210827_coax.root","READ");
    TFile *file_1 = new TFile("/home/sofia/gerda_data/53_93_PSD/BEGe/20210827_BEGe.root","READ");
    TFile *file_2 = new TFile("/home/sofia/gerda_data/95_114/coax/20220215_coax.root","READ"); 
    TFile *file_3 = new TFile("/home/sofia/gerda_data/95_114/BEGe/20220215_BEGe.root","READ");
    TFile *file_4 = new TFile("/home/sofia/gerda_data/95_114/IC/20220215_IC.root","READ");
    TH1D *h_0 = (TH1D*) file_0->Get("LAr");
    TH1D *h_1 = (TH1D*) file_1->Get("LAr");
    TH1D *h_2 = (TH1D*) file_2->Get("LAr");
    TH1D *h_3 = (TH1D*) file_3->Get("LAr");
    TH1D *h_4 = (TH1D*) file_4->Get("LAr");
    vector<double> bin_content_0;
    for ( int i=1; i<=5200; i++ ) { bin_content_0.push_back( h_0->GetBinContent(i) ); }
    
    //---------------------------------------------------------------------------------------------------------------------- DATASET CREATION	
    // create a new dataset
    // enrCoax - phII (0-5200)
    BCDataSet data_set;
    data_set.ReadDataFromFileTxt("/home/sofia/gerda_data/53_93_PSD/coax/bin_content_coax.txt", 1); 
    
    // create new data points
    // enrBEGe - phII (5201-10400)
    for ( int i=1; i<=5200; i++ ) {
    	BCDataPoint* h1 = new BCDataPoint(1);
	h1->SetValue(0, h_1->GetBinContent(i));
	data_set.AddDataPoint(*h1);
    }
    // enrCoax - phII+ (10401-15600)
    for ( int i=1; i<=5200; i++ ) {
    	BCDataPoint* h2 = new BCDataPoint(1);
	h2->SetValue(0, h_2->GetBinContent(i));
	data_set.AddDataPoint(*h2);
    }
    // enrBEGe - phII+ (15601-20800)
    for ( int i=1; i<=5200; i++ ) {
    	BCDataPoint* h3 = new BCDataPoint(1);
	h3->SetValue(0, h_3->GetBinContent(i));
	data_set.AddDataPoint(*h3);
    }
    // invCoax - phII+ (20801-26000)
    for ( int i=1; i<=5200; i++ ) { 
    	BCDataPoint* h4 = new BCDataPoint(1);
	h4->SetValue(0, h_4->GetBinContent(i));
	data_set.AddDataPoint(*h4);
    }
    // E0 (26001)
    BCDataPoint* CentralEnergy = new BCDataPoint(1);
    CentralEnergy->SetValue(0, E0);
    data_set.AddDataPoint(*CentralEnergy);	
    // xL (26002)
    int xL = inpval[3];
    BCDataPoint* xLeft = new BCDataPoint(1);
    xLeft->SetValue(0, xL);
    data_set.AddDataPoint(*xLeft);
    // xR (26003)
    int xR = inpval[4];
    BCDataPoint* xRight = new BCDataPoint(1);
    xRight->SetValue(0, xR);
    data_set.AddDataPoint(*xRight);
    // E1 (26004)
    double E1 = 0;
    if ( k>=0 && k<numGamma ) { E1 = E_gamma[k]; } // when k=numGamma, we do not have gamma peaks ( we leave E1=0 )
    if ( outputK==3 ) { E1 = E_gamma[k+1]; }
    BCDataPoint* gammaEnergy = new BCDataPoint(1);
    gammaEnergy->SetValue(0, E1); 
    data_set.AddDataPoint(*gammaEnergy);
    // output[k] (26005)
    BCDataPoint* outInK = new BCDataPoint(1);
    outInK->SetValue(0, outputK);
    data_set.AddDataPoint(*outInK);
    // pol_degree (26006)
    BCDataPoint* pol = new BCDataPoint(1);
    pol->SetValue(0, pol_degree);
    data_set.AddDataPoint(*pol);
    // E2 (26007)
    double E2 = 0;
    if ( (outputK>7 && outputK<20 ) && (outputK!=15 && outputK!=18) ) {
    	if ( k>=0 && k<10 ) {  E2 = E_gamma[k+1]; }
    } 
    BCDataPoint* gammaEnergy_2 = new BCDataPoint(1);
    gammaEnergy_2->SetValue(0, E2);
    data_set.AddDataPoint(*gammaEnergy_2);
    // thr (26008)
    BCDataPoint* en_thr = new BCDataPoint(1);
    en_thr->SetValue(0, thr);
    data_set.AddDataPoint(*en_thr);
    // energy (26009-27408)
    for ( int i=0; i<1400; i++ ) {
    	BCDataPoint* energy = new BCDataPoint(1);
	energy->SetValue(0, eff_bege_el_II[i][0]);
	data_set.AddDataPoint(*energy);
    }
    // eff_coax_el_II (27409-28808)
    for ( int i=0; i<1400; i++ ) {
    	BCDataPoint* energy = new BCDataPoint(1);
	energy->SetValue(0, eff_coax_el_II[i][1]);
	data_set.AddDataPoint(*energy);
    }
    // eff_bege_el_II (28809-30208)
    for ( int i=0; i<1400; i++ ) {
    	BCDataPoint* energy = new BCDataPoint(1);
	energy->SetValue(0, eff_bege_el_II[i][1]);
	data_set.AddDataPoint(*energy);
    }
    // eff_coax_el_II_IIp (30209-31608)
    for ( int i=0; i<1400; i++ ) {
    	BCDataPoint* energy = new BCDataPoint(1);
	energy->SetValue(0, eff_coax_el_II_IIp[i][1]);
	data_set.AddDataPoint(*energy);
    }
    // eff_bege_el_II_IIp (31609-33008)
    for ( int i=0; i<1400; i++ ) {
    	BCDataPoint* energy = new BCDataPoint(1);
	energy->SetValue(0, eff_bege_el_II_IIp[i][1]);
	data_set.AddDataPoint(*energy);
    }
    // eff_ic_el_II_IIp (33009-34408)
    for ( int i=0; i<1400; i++ ) {
    	BCDataPoint* energy = new BCDataPoint(1);
	energy->SetValue(0, eff_ic_el_II_IIp[i][1]);
	data_set.AddDataPoint(*energy);
    }
    // Ge_xsec - energies (34409-36008)
    for ( int i=0; i<1600; i++ ) {
    	BCDataPoint* energy = new BCDataPoint(1);
	energy->SetValue(0, Ge_xsec[i][0]);
	data_set.AddDataPoint(*energy);
    }
    // Ge_xsec (36009-38208)
    for ( int i=0; i<1600; i++ ) {
    	BCDataPoint* xsec = new BCDataPoint(1);
	xsec->SetValue(0, Ge_xsec[i][1]);
	data_set.AddDataPoint(*xsec);
    }
    
    // set of the model name
    bool peak_0 = (outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20);
    bool peak_1 = (outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12);
    bool peak_2 = (peak_0==false && peak_1==false);
    char name_model[100];
    if      ( peak_0==true ) { sprintf(name_model,"%iGausPol%i", E0, pol_degree); }
    else if ( peak_1==true ) { sprintf(name_model,"%iGausPol%i_1Gamma", E0, pol_degree); }
    else                     { sprintf(name_model,"%iGausPol%i_2Gamma", E0, pol_degree); }
    
    
    // collection of some variables necessary for fit
    bool    peak[3] = { peak_0, peak_1, peak_2 };
    double  FitVariables[15] = { E0, E1, E2, xL, xR, k, 
    			          outputK, pol_degree, thr, 
                                 inpval[7], inpval[8], inpval[9], 	   // bkg ranges
                                 inpval[10], inpval[11], inpval[12]};   // gaussian height ranges
    
    //---------------------------------------------------------------------------------------------------------------------- ANALYSIS 
    VectorModel m(name_model, bin_content_0, FitVariables, peak);
    //PseudoscalarModel m(name_model, bin_content_0, FitVariables, peak);
    m.SetDataSet(&data_set);
    m.SetPrecision(BCEngineMCMC::kHigh); // kHigh   kVeryHigh
    
    m.MarginalizeAll(BCIntegrate::kMargMetropolis);
    m.FindMode(m.GetBestFitParameters());
    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
    m.PrintAllMarginalized("MarginalizedPDF/" + m.GetSafeName() + ".pdf", 2, 2);
    m.PrintKnowledgeUpdatePlots("Priors&Posteriors/" + m.GetSafeName() + ".pdf", 2, 2);
    m.WriteMarginalizedDistributions("MarginalizedROOT/" + to_string(E0) + ".root", "RECREATE");
    m.PrintSummary();
    
    // Global mode
    const std::vector<double> params = m.GetBestFitParameters(); 
    const std::vector<double> params_err = m.GetBestFitParameterErrors();
    
    // Posterior distributions
    BCH1D h_E0, h_p0, h_p1, h_p2, h_E1, h_E2;
    h_E0 = m.GetMarginalizedHistogram(0);
    h_p0 = m.GetMarginalizedHistogram(1);
    h_p1 = m.GetMarginalizedHistogram(2);
    if ( pol_degree==1 ) {
	    if ( peak_1==true ) {
	    	h_E1 = m.GetMarginalizedHistogram(3);
	    }
	    if ( peak_2==true ) {
		h_E1 = m.GetMarginalizedHistogram(3);
		h_E2 = m.GetMarginalizedHistogram(4);
	    }
    }
    if ( pol_degree==2 ) {
	    h_p2 = m.GetMarginalizedHistogram(3);
	    if ( peak_1==true ) {
	    	h_E1 = m.GetMarginalizedHistogram(4);
	    }
	    if ( peak_2==true ) {
		h_E1 = m.GetMarginalizedHistogram(4);
		h_E2 = m.GetMarginalizedHistogram(5);
	    }
    }
    std::vector<double> DblResults = BATResults(outputK, pol_degree, h_E0, h_p0, h_p1, h_p2, h_E1, h_E2);
    
    DblResults.push_back(E1); // # 54 (vector index)
    DblResults.push_back(E2); // # 55
	    
    // Parameter range
    double cpl_LPR=0, p0_LPR=0, p1_LPR=0, p2_LPR=0, E1_LPR=0, E2_LPR=0;
    double cpl_UPR=0, p0_UPR=0, p1_UPR=0, p2_UPR=0, E1_UPR=0, E2_UPR=0;
    cpl_LPR = m.GetParameter(0).GetLowerLimit();
    cpl_UPR = m.GetParameter(0).GetUpperLimit();
    p0_LPR = m.GetParameter(1).GetLowerLimit();
    p0_UPR = m.GetParameter(1).GetUpperLimit();
    p1_LPR = m.GetParameter(2).GetLowerLimit();
    p1_UPR = m.GetParameter(2).GetUpperLimit();
    if ( pol_degree==1 ) {
	    if ( peak_1==true ) {
	    	E1_LPR = m.GetParameter(3).GetLowerLimit();
    		E1_UPR = m.GetParameter(3).GetUpperLimit();
	    }
	    if ( peak_2==true ) {
		E1_LPR = m.GetParameter(3).GetLowerLimit();
	    	E1_UPR = m.GetParameter(3).GetUpperLimit();
	    	E2_LPR = m.GetParameter(4).GetLowerLimit();
	    	E2_UPR = m.GetParameter(4).GetUpperLimit();
	    }
    }
    if ( pol_degree==2 ) {
	    p2_LPR = m.GetParameter(3).GetLowerLimit();
	    p2_UPR = m.GetParameter(3).GetUpperLimit();
	    if ( peak_1==true ) {
	    	E1_LPR = m.GetParameter(4).GetLowerLimit();
    		E1_UPR = m.GetParameter(4).GetUpperLimit();
	    }
	    if ( peak_2==true ) {
		E1_LPR = m.GetParameter(4).GetLowerLimit();
	    	E1_UPR = m.GetParameter(4).GetUpperLimit();
	    	E2_LPR = m.GetParameter(5).GetLowerLimit();
	    	E2_UPR = m.GetParameter(5).GetUpperLimit();
	    }
    }

    DblResults.push_back(cpl_LPR); // # 56 (vector index)
    DblResults.push_back(cpl_UPR); // # 57
    DblResults.push_back(p0_LPR);  // # 58
    DblResults.push_back(p0_UPR);  // # 59
    DblResults.push_back(p1_LPR);  // # 60
    DblResults.push_back(p1_UPR);  // # 61
    DblResults.push_back(p2_LPR);  // # 62
    DblResults.push_back(p2_UPR);  // # 63
    DblResults.push_back(E1_LPR);  // # 64
    DblResults.push_back(E1_UPR);  // # 65
    DblResults.push_back(E2_LPR);  // # 66
    DblResults.push_back(E2_UPR);  // # 67
    	    
    JsonFile(params, params_err, FitVariables, DblResults);
    
    return 0;
}
