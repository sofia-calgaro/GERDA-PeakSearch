// BAT
#include <BAT/BCLog.h>
#include <BAT/BCH1D.h>
#include <BAT/BCAux.h>

// ROOT
#include <TFile.h>
#include <TMath.h>

// MODELS
#include "GausPol0.h"
#include "GausPol1.h"
#include "GausPol2.h"

// OTHER
#include "Operations.h"
#include "Output.h"
#include "args_reader.hpp"



int main(int argc, char *argv[])
{  

    std::vector<std::string> args(argc);
    std::copy(argv, argv+argc, args.begin());
  
    std::vector<int> inpval(13,0);
    bool found = fetch_arg(args, "--nums", inpval);
    
    if (found) {
    std::cout << "\n *************************" << std::endl;
    std::cout << "  E0 = " << inpval[1] << "\n  Polynomial degree = " << inpval[2];
    std::cout << "\n  xL = " << inpval[3] << "\n  xR = " << inpval[4] << "\n  k = " << inpval[5];
    std::cout << "\n  output[k] = " << inpval[6] << std::endl;
    std::cout << "\n  rng0 = " << inpval[7] << "\n  rng1 = " << inpval[8] << "\n  rng2 = " << inpval[9] << std::endl;
    std::cout << "\n  rngE0 = " << inpval[10] << "\n  rngE1 = " << inpval[11] << "\n  rngE2 = " << inpval[12] << std::endl;
    std::cout << " *************************\n" << std::endl;
    }
      
    //---------------------------------------------------------------------------------------------------------------------- DATA LOADING   
    TFile *file = new TFile("/home/sofia/gerda_data/53_114_PSD/BEGe_new/20210726_BEGe.root","READ");
    TH1D *h = (TH1D*) file->Get("LAr");
    std::vector< int> bin_content;
    for ( int i=1; i<=5200; i++ ) { bin_content.push_back( h->GetBinContent(i) ); }
        		
    // create a new dataset
    BCDataSet data_set;
    data_set.ReadDataFromFileTxt("/home/sofia/gerda_data/53_114_PSD/BEGe_new/bin_content_BEGe.txt", 1);
    
    // create a new data point: E0 (5201)
    int E0 = inpval[1];
    BCDataPoint* CentralEnergy = new BCDataPoint(1);
    CentralEnergy->SetValue(0, E0);
    data_set.AddDataPoint(*CentralEnergy);	
    
    // create a new data point: xL (5202)
    int xL = inpval[3];
    BCDataPoint* xLeft = new BCDataPoint(1);
    xLeft->SetValue(0, xL);
    data_set.AddDataPoint(*xLeft);
    
    // create a new data point: xR (5203)
    int xR = inpval[4];
    BCDataPoint* xRight = new BCDataPoint(1);
    xRight->SetValue(0, xR);
    data_set.AddDataPoint(*xRight);
    
    double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
    int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
    
    // create a new data point: E1=E_gamma[k] (5204)
    int k = inpval[5];
    double E1 = 0;
    BCDataPoint* gammaEnergy = new BCDataPoint(1);
    if ( k>=0 && k<numGamma ) { E1 = E_gamma[k]; } // when k=numGamma, we do not have gamma peaks ( we leave E1=0 )
    gammaEnergy->SetValue(0, E1); 
    data_set.AddDataPoint(*gammaEnergy);
       
    // create a new data point: output[k] (5205)
    int outputK = inpval[6];
    BCDataPoint* outInK = new BCDataPoint(1);
    outInK->SetValue(0, outputK);
    data_set.AddDataPoint(*outInK);
    
    // create a new data point: E2=E_gamma[k+1] (5206)
    double E2 = 0;
    BCDataPoint* gammaEnergy_2 = new BCDataPoint(1);
    if ( (outputK>7 && outputK<20 ) && (outputK!=15 && outputK!=18) ) {
    	if ( k>=0 && k<10 ) {  E2 = E_gamma[k+1]; }
    }       
    gammaEnergy_2->SetValue(0, E2);
    data_set.AddDataPoint(*gammaEnergy_2);
    
    // array of range-check parameters
    int rng[6] = { inpval[7], inpval[8], inpval[9], inpval[10], inpval[11], inpval[12] };
        
    // open log file
    int pol_degree = inpval[2];
    char name_log[100];
    sprintf(name_log,"/home/sofia/Analysis/DataAnalysis/Log_files/log_%i_GausPol%i.txt", E0, pol_degree);
    BCLog::OpenLog(name_log, BCLog::detail, BCLog::detail);	
    
    // collection of some integer results
    int IntResults[12] = { E0, xL, xR, k, outputK, pol_degree, rng[0], rng[1], rng[2], rng[3], rng[4], rng[5]};
    
    // set of the model name
    char name_model[100];
    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {
	    sprintf(name_model,"%iGausPol%i", E0, pol_degree);
    }
    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
	    sprintf(name_model,"%iGausPol%i_1Gamma", E0, pol_degree);
    }
    else {
    	sprintf(name_model,"%iGausPol%i_2Gamma", E0, pol_degree); 
    }
    
    //---------------------------------------------------------------------------------------------------------------------- ANALYSIS     
    
    // BKG = Pol0
    if ( pol_degree==0 ) {
    	
    	    GausPol0 m(name_model, bin_content, E0, xL, xR, E1, E2, outputK, rng);
	    
   	    m.SetDataSet(&data_set); // Associate the data set with the model
	    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kHigh);
	    
	    // run MCMC, marginalizing posterior
	    m.MarginalizeAll(BCIntegrate::kMargMetropolis); 
	    // run mode finding; by default using Minuit
	    m.FindMode(m.GetBestFitParameters()); 
	    // fix the bands for each posterior at 68.3%, 95.4%, 99.7%
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);
	    // draw all marginalized distributions into a PDF file
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf", 2, 2);
	    m.PrintSummary();
	    m.WriteMarginalizedDistributions("/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/" + m.GetSafeName() + ".root", "RECREATE");
	  
	    BCLog::OutSummary("Exiting");
	    BCLog::CloseLog();
	    	    
	    //---------------------------------------------------------------------------------------------
	    // Posterior distributions
	    BCH1D h_E0, h_p0, h_p1, h_p2, h_E1, h_E2;
	    h_E0 = m.GetMarginalizedHistogram(0);
	    h_p0 = m.GetMarginalizedHistogram(1);
	    
	    // Global mode
	    const std::vector<double> params = m.GetBestFitParameters(); 
	    const std::vector<double> params_err = m.GetBestFitParameterErrors();
	    
	    if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
	    	    h_E1 = m.GetMarginalizedHistogram(2);
	    }
	    if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		    h_E1 = m.GetMarginalizedHistogram(2);
		    h_E2 = m.GetMarginalizedHistogram(3);
	    }
	    
	    std::vector<double> DblResults = BATResults(outputK, pol_degree, h_E0, h_p0, h_p1, h_p2, h_E1, h_E2);
	    
	    DblResults.push_back(E1); // # 54 (vector index)
	    DblResults.push_back(E2); // # 55
	    
	    // Parameter range
	    double E0_LPR=0, p0_LPR=0, p1_LPR=0, p2_LPR=0, E1_LPR=0, E2_LPR=0;
	    double E0_UPR=0, p0_UPR=0, p1_UPR=0, p2_UPR=0, E1_UPR=0, E2_UPR=0;
	    E0_LPR = m.GetParameter(0).GetLowerLimit();
	    E0_UPR = m.GetParameter(0).GetUpperLimit();
	    p0_LPR = m.GetParameter(1).GetLowerLimit();
	    p0_UPR = m.GetParameter(1).GetUpperLimit();
	    if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
	    	E1_LPR = m.GetParameter(2).GetLowerLimit();
	    	E1_UPR = m.GetParameter(2).GetUpperLimit();
	    }
	    if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
	    	E1_LPR = m.GetParameter(2).GetLowerLimit();
	    	E1_UPR = m.GetParameter(2).GetUpperLimit();
	    	E2_LPR = m.GetParameter(3).GetLowerLimit();
	    	E2_UPR = m.GetParameter(3).GetUpperLimit();
	    }
	    
	    DblResults.push_back(E0_LPR); // # 56 (vector index)
	    DblResults.push_back(E0_UPR); // # 57
	    DblResults.push_back(p0_LPR); // # 58
	    DblResults.push_back(p0_UPR); // # 59
	    DblResults.push_back(p1_LPR); // # 60
	    DblResults.push_back(p1_UPR); // # 61
	    DblResults.push_back(p2_LPR); // # 62
	    DblResults.push_back(p2_UPR); // # 63
	    DblResults.push_back(E1_LPR); // # 64
	    DblResults.push_back(E1_UPR); // # 65
	    DblResults.push_back(E2_LPR); // # 66
	    DblResults.push_back(E2_UPR); // # 67
	    	    
	    JsonFile(params, params_err, IntResults, DblResults); // write JSON file
	    
	    //--------------------------------------------------------------------------------------------- plot: data + fit
	    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) { Draw_Pol0(E0, xL, xR, params, h); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { Draw_Gamma_Pol0(E0, E1, xL, xR, params, h); }
	    else { Draw_TwoGamma_Pol0(E0, E1, E2, xL, xR, params, h); }
	
	    
    }
    
    
    
    // BKG = Pol1
    if ( pol_degree==1 ) {
    
   	    GausPol1 m(name_model, bin_content, E0, xL, xR, E1, E2, outputK, rng);
   	    
   	    m.SetDataSet(&data_set);
    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kHigh);
	    
	    m.MarginalizeAll(BCIntegrate::kMargMetropolis);
	    m.FindMode(m.GetBestFitParameters());
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf", 2, 2);
	    m.PrintSummary();
	    m.WriteMarginalizedDistributions("/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/" + m.GetSafeName() + ".root", "RECREATE");
	  
	    BCLog::OutSummary("Exiting");
	    BCLog::CloseLog();
	    
	    //---------------------------------------------------------------------------------------------
	    // Posterior distributions
	    BCH1D h_E0, h_p0, h_p1, h_p2, h_E1, h_E2;
	    h_E0 = m.GetMarginalizedHistogram(0);
	    h_p0 = m.GetMarginalizedHistogram(1);
	    h_p1 = m.GetMarginalizedHistogram(2);
	    
	    // Global mode
	    const std::vector<double> params = m.GetBestFitParameters(); 
	    const std::vector<double> params_err = m.GetBestFitParameterErrors();
	    
	    if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
	    	    h_E1 = m.GetMarginalizedHistogram(3);
	    }
	    if ( outputK==8 || outputK==9 || outputK==10 || outputK==11 || outputK==16 || outputK==17 || outputK==19 ) {
		    h_E1 = m.GetMarginalizedHistogram(3);
		    h_E2 = m.GetMarginalizedHistogram(4);
	    }
	    
	    std::vector<double> DblResults = BATResults(outputK, pol_degree, h_E0, h_p0, h_p1, h_p2, h_E1, h_E2);
	    
	    DblResults.push_back(E1); // # 54 (vector index)
	    DblResults.push_back(E2); // # 55
	    
	    // Parameter range
	    double E0_LPR=0, p0_LPR=0, p1_LPR=0, p2_LPR=0, E1_LPR=0, E2_LPR=0;
	    double E0_UPR=0, p0_UPR=0, p1_UPR=0, p2_UPR=0, E1_UPR=0, E2_UPR=0;
	    E0_LPR = m.GetParameter(0).GetLowerLimit();
	    E0_UPR = m.GetParameter(0).GetUpperLimit();
	    p0_LPR = m.GetParameter(1).GetLowerLimit();
	    p0_UPR = m.GetParameter(1).GetUpperLimit();
	    p1_LPR = m.GetParameter(2).GetLowerLimit();
	    p1_UPR = m.GetParameter(2).GetUpperLimit();
	    if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
	    	E1_LPR = m.GetParameter(3).GetLowerLimit();
	    	E1_UPR = m.GetParameter(3).GetUpperLimit();
	    }
	    if ( outputK==8 || outputK==9 || outputK==10 || outputK==11 || outputK==16 || outputK==17 || outputK==19 ) {
	    	E1_LPR = m.GetParameter(3).GetLowerLimit();
	    	E1_UPR = m.GetParameter(3).GetUpperLimit();
	    	E2_LPR = m.GetParameter(4).GetLowerLimit();
	    	E2_UPR = m.GetParameter(4).GetUpperLimit();
	    }
	    
	    DblResults.push_back(E0_LPR); // # 56 (vector index)
	    DblResults.push_back(E0_UPR); // # 57
	    DblResults.push_back(p0_LPR); // # 58
	    DblResults.push_back(p0_UPR); // # 59
	    DblResults.push_back(p1_LPR); // # 60
	    DblResults.push_back(p1_UPR); // # 61
	    DblResults.push_back(p2_LPR); // # 62
	    DblResults.push_back(p2_UPR); // # 63
	    DblResults.push_back(E1_LPR); // # 64
	    DblResults.push_back(E1_UPR); // # 65
	    DblResults.push_back(E2_LPR); // # 66
	    DblResults.push_back(E2_UPR); // # 67
	    	    
	    JsonFile(params, params_err, IntResults, DblResults);
	    
	    //--------------------------------------------------------------------------------------------- plot: data + fit
	    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) { Draw_Pol1(E0, xL, xR, params, h); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { Draw_Gamma_Pol1(E0, E1, xL, xR, params, h); }
	    else { Draw_TwoGamma_Pol1(E0, E1, E2, xL, xR, params, h); }
    }
    
    
    
    // BKG = Pol2
    if ( pol_degree==2 ) {
    
  	    GausPol2 m(name_model, bin_content, E0, xL, xR, E1, E2, outputK, rng);
  	    
   	    m.SetDataSet(&data_set);
    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kHigh);
	    
	    m.MarginalizeAll(BCIntegrate::kMargMetropolis);
	    m.FindMode(m.GetBestFitParameters());
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf", 2, 2);
	    m.PrintSummary();
	    m.WriteMarginalizedDistributions("/home/sofia/Analysis/DataAnalysis/MarginalizedROOT/" + m.GetSafeName() + ".root", "RECREATE");
	  
	    BCLog::OutSummary("Exiting");
	    BCLog::CloseLog();
	    
	    //---------------------------------------------------------------------------------------------
	    // Posterior distributions
	    BCH1D h_E0, h_p0, h_p1, h_p2, h_E1, h_E2;
	    h_E0 = m.GetMarginalizedHistogram(0);
	    h_p0 = m.GetMarginalizedHistogram(1);
	    h_p1 = m.GetMarginalizedHistogram(2);
	    h_p2 = m.GetMarginalizedHistogram(3);
	    
	    // Global mode
	    const std::vector<double> params = m.GetBestFitParameters(); 
	    const std::vector<double> params_err = m.GetBestFitParameterErrors();
	    
	    if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
	    	    h_E1 = m.GetMarginalizedHistogram(4);
	    }
	    if ( outputK==8 || outputK==9 || outputK==10 || outputK==11 || outputK==16 || outputK==17 || outputK==19 ) {
		    h_E1 = m.GetMarginalizedHistogram(4);
		    h_E2 = m.GetMarginalizedHistogram(5);
	    }
	    
	    std::vector<double> DblResults = BATResults(outputK, pol_degree, h_E0, h_p0, h_p1, h_p2, h_E1, h_E2);
	    
	    DblResults.push_back(E1); // # 54 (vector index)
	    DblResults.push_back(E2); // # 55
	    
	    // Parameter range
	    double E0_LPR=0, p0_LPR=0, p1_LPR=0, p2_LPR=0, E1_LPR=0, E2_LPR=0;
	    double E0_UPR=0, p0_UPR=0, p1_UPR=0, p2_UPR=0, E1_UPR=0, E2_UPR=0;
	    E0_LPR = m.GetParameter(0).GetLowerLimit();
	    E0_UPR = m.GetParameter(0).GetUpperLimit();
	    p0_LPR = m.GetParameter(1).GetLowerLimit();
	    p0_UPR = m.GetParameter(1).GetUpperLimit();
	    p1_LPR = m.GetParameter(2).GetLowerLimit();
	    p1_UPR = m.GetParameter(2).GetUpperLimit();
	    p2_LPR = m.GetParameter(3).GetLowerLimit();
	    p2_UPR = m.GetParameter(3).GetUpperLimit();
	    if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
	    	E1_LPR = m.GetParameter(4).GetLowerLimit();
	    	E1_UPR = m.GetParameter(4).GetUpperLimit();
	    }
	    if ( outputK==8 || outputK==9 || outputK==10 || outputK==11 || outputK==16 || outputK==17 || outputK==19 ) {
	    	E1_LPR = m.GetParameter(4).GetLowerLimit();
	    	E1_UPR = m.GetParameter(4).GetUpperLimit();
	    	E2_LPR = m.GetParameter(5).GetLowerLimit();
	    	E2_UPR = m.GetParameter(5).GetUpperLimit();
	    }
	    
	    DblResults.push_back(E0_LPR); // # 56 (vector index)
	    DblResults.push_back(E0_UPR); // # 57
	    DblResults.push_back(p0_LPR); // # 58
	    DblResults.push_back(p0_UPR); // # 59
	    DblResults.push_back(p1_LPR); // # 60
	    DblResults.push_back(p1_UPR); // # 61
	    DblResults.push_back(p2_LPR); // # 62
	    DblResults.push_back(p2_UPR); // # 63
	    DblResults.push_back(E1_LPR); // # 64
	    DblResults.push_back(E1_UPR); // # 65
	    DblResults.push_back(E2_LPR); // # 66
	    DblResults.push_back(E2_UPR); // # 67
	    	    
	    JsonFile(params, params_err, IntResults, DblResults);
	    
	    //--------------------------------------------------------------------------------------------- plot: data + fit
	    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) { Draw_Pol2(E0, xL, xR, params, h); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { Draw_Gamma_Pol2(E0, E1, xL, xR, params, h); }
	    else { Draw_TwoGamma_Pol2(E0, E1, E2, xL, xR, params, h); }	    
    }

    return 0;
}
