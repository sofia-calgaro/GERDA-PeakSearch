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
  
    std::vector<int> inpval(7,0);
    bool found = fetch_arg(args, "--nums", inpval);
    
    if (found) {
    std::cout << "\n *************************" << std::endl;
    std::cout << "  E0 = " << inpval[1] << "\n  Polynomial degree = " << inpval[2];
    std::cout << "\n  xL = " << inpval[3] << "\n  xR = " << inpval[4] << "\n  k = " << inpval[5];
    std::cout << "\n  output[k] = " << inpval[6] << std::endl;
    std::cout << " *************************\n" << std::endl;
    }
      
    //---------------------------------------------------------------------------------------------------------------------- DATA LOADING   

    TFile *file = new TFile("/home/sofia/gerda_data/IC_20210406.root","READ");
    TH1D *h = (TH1D*) file->Get("histo_energy_LArVetoed");
    std::vector< int> bin_content;
    for ( int i=1; i<=5200; i++ ) { bin_content.push_back( h->GetBinContent(i) ); }
        		
    // create a new dataset
    BCDataSet data_set;
    data_set.ReadDataFromFileTxt("/home/sofia/gerda_data/bin_content.txt", 1);
    
    // create a new data point: E0
    int E0 = inpval[1];
    BCDataPoint* CentralEnergy = new BCDataPoint(1);
    CentralEnergy->SetValue(0, E0);
    data_set.AddDataPoint(*CentralEnergy);	
    
    // create a new data point: xL
    int xL = inpval[3];
    BCDataPoint* xLeft = new BCDataPoint(1);
    xLeft->SetValue(0, xL);
    data_set.AddDataPoint(*xLeft);
    
    // create a new data point: xR
    int xR = inpval[4];
    BCDataPoint* xRight = new BCDataPoint(1);
    xRight->SetValue(0, xR);
    data_set.AddDataPoint(*xRight);
    
    double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
    int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
    
    // create a new data point: E1=E_gamma[k]
    int k = inpval[5];
    double E1 = 0;
    BCDataPoint* gammaEnergy = new BCDataPoint(1);
    if ( k>=0 && k<numGamma ) { E1 = E_gamma[k]; }
    gammaEnergy->SetValue(0, E1); // when k=numGamma, we do not have any gamma peak
    data_set.AddDataPoint(*gammaEnergy);
       
    // create a new data point: output[k]
    int outputK = inpval[6];
    BCDataPoint* outInK = new BCDataPoint(1);
    outInK->SetValue(0, outputK);
    data_set.AddDataPoint(*outInK);
    
    // create a new data point: E2=E_gamma[k+1]
    double E2 = 0;
    BCDataPoint* gammaEnergy_2 = new BCDataPoint(1);
    if ( (outputK>7 && outputK<20 ) && (outputK!=15 && outputK!=18) ) {
    	if ( k>=0 && k<10 ) {  E2 = E_gamma[k+1]; }
    }       
    gammaEnergy_2->SetValue(0, E2);
    data_set.AddDataPoint(*gammaEnergy_2);
        
    // open log file
    int pol_degree = inpval[2];
    char name_log[100];
    sprintf(name_log,"/home/sofia/Analysis/DataAnalysis/Log_files/log_%i_GausPol%i.txt", E0, pol_degree);
    BCLog::OpenLog(name_log, BCLog::detail, BCLog::detail);	
    
    int IntResults[6] = { E0, xL, xR, k, outputK, pol_degree};
    
    //---------------------------------------------------------------------------------------------------------------------- ANALYSIS     
    
    // BKG = Pol0
    if ( pol_degree==0 ) {
    	
    	    char name_model[100];
    	    if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) { sprintf(name_model,"%iGausPol0", E0); }
	    else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) { sprintf(name_model,"%iGausPol0_%gGamma", E0, E1); }
	    else { sprintf(name_model,"%iGausPol0_%gGamma_%gGamma", E0, E1, E2); }
	    
	    GausPol0 m(name_model, bin_content, E0, xL, xR, E1, E2, outputK);
	    
   	    m.SetDataSet(&data_set); // Associate the data set with the model
	    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kMedium);

	    m.MarginalizeAll(BCIntegrate::kMargMetropolis); // run MCMC, marginalizing posterior

	    m.FindMode(m.GetBestFitParameters()); // run mode finding; by default using Minuit
	    
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval); // fix the bands for each posterior at 68.3%, 95.4%, 99.7%
	 
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf", 2, 2); // draw all marginalized distributions into a PDF file
	  
	    m.PrintSummary();
	  
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
	    
	    if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
	    	    h_E1 = m.GetMarginalizedHistogram(2);
	    }
	    if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		    h_E1 = m.GetMarginalizedHistogram(2);
		    h_E2 = m.GetMarginalizedHistogram(3);
	    }
	    
	    std::vector<double> DblResults = BATResults(outputK, pol_degree, h_E0, h_p0, h_p1, h_p2, h_E1, h_E2);
	    
	    DblResults.push_back(E1); // # 30
	    DblResults.push_back(E2); // # 31
	    
	    // Parameter range
	    double E0_LPR=0, p0_LPR=0, p1_LPR=0, p2_LPR=0, E1_LPR=0, E2_LPR=0;
	    double E0_UPR=0, p0_UPR=0, p1_UPR=0, p2_UPR=0, E1_UPR=0, E2_UPR=0;
	    E0_LPR = m.GetParameter(0).GetLowerLimit();
	    E0_UPR = m.GetParameter(0).GetUpperLimit();
	    p0_LPR = m.GetParameter(1).GetLowerLimit();
	    p0_UPR = m.GetParameter(1).GetUpperLimit();
	    if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
	    	E1_LPR = m.GetParameter(2).GetLowerLimit();
	    	E1_UPR = m.GetParameter(2).GetUpperLimit();
	    }
	    if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
	    	E1_LPR = m.GetParameter(2).GetLowerLimit();
	    	E1_UPR = m.GetParameter(2).GetUpperLimit();
	    	E2_LPR = m.GetParameter(3).GetLowerLimit();
	    	E2_UPR = m.GetParameter(3).GetUpperLimit();
	    }
	    
	    DblResults.push_back(E0_LPR); // # 32
	    DblResults.push_back(E0_UPR); // # 33
	    DblResults.push_back(p0_LPR); // # 34
	    DblResults.push_back(p0_UPR); // # 35
	    DblResults.push_back(p1_LPR); // # 36
	    DblResults.push_back(p1_UPR); // # 37
	    DblResults.push_back(p2_LPR); // # 38
	    DblResults.push_back(p2_UPR); // # 39
	    DblResults.push_back(E1_LPR); // # 40
	    DblResults.push_back(E1_UPR); // # 41
	    DblResults.push_back(E2_LPR); // # 42
	    DblResults.push_back(E2_UPR); // # 43
	    	    
	    JsonFile(params, params_err, IntResults, DblResults);
	    
	    //---------------------------------------------------------------------------------------------
	    // plot: data + fit
	    if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) { Draw_Pol0(E0, xL, xR, params, h); }
	    else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) { Draw_Gamma_Pol0(E0, E1, xL, xR, params, h); }
	    else { Draw_TwoGamma_Pol0(E0, E1, E2, xL, xR, params, h); }
	
	    
    }
    
    
    
    // BKG = Pol1
    if ( pol_degree==1 ) {
    
   	    char name_model[100];
    	    if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) { sprintf(name_model,"%iGausPol1", E0); }
	    else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) { sprintf(name_model,"%iGausPol1_%gGamma", E0, E1); }
	    else { sprintf(name_model,"%iGausPol0_%gGamma_%gGamma", E0, E1, E2); }
	    
	    GausPol1 m(name_model, bin_content, E0, xL, xR, E1, E2, outputK);
   	    
   	    m.SetDataSet(&data_set);
    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kMedium);

	    m.MarginalizeAll(BCIntegrate::kMargMetropolis);

	    m.FindMode(m.GetBestFitParameters());
	    
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
	 
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf", 2, 2);
	  
	    m.PrintSummary();
	  
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
	    
	    if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
	    	    h_E1 = m.GetMarginalizedHistogram(3);
	    }
	    if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		    h_E1 = m.GetMarginalizedHistogram(3);
		    h_E2 = m.GetMarginalizedHistogram(4);
	    }
	    
	    std::vector<double> DblResults = BATResults(outputK, pol_degree, h_E0, h_p0, h_p1, h_p2, h_E1, h_E2);
	    
	    DblResults.push_back(E1); // # 30
	    DblResults.push_back(E2); // # 31
	    
	    // Parameter range
	    double E0_LPR=0, p0_LPR=0, p1_LPR=0, p2_LPR=0, E1_LPR=0, E2_LPR=0;
	    double E0_UPR=0, p0_UPR=0, p1_UPR=0, p2_UPR=0, E1_UPR=0, E2_UPR=0;
	    E0_LPR = m.GetParameter(0).GetLowerLimit();
	    E0_UPR = m.GetParameter(0).GetUpperLimit();
	    p0_LPR = m.GetParameter(1).GetLowerLimit();
	    p0_UPR = m.GetParameter(1).GetUpperLimit();
	    p1_LPR = m.GetParameter(2).GetLowerLimit();
	    p1_UPR = m.GetParameter(2).GetUpperLimit();
	    if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
	    	E1_LPR = m.GetParameter(3).GetLowerLimit();
	    	E1_UPR = m.GetParameter(3).GetUpperLimit();
	    }
	    if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
	    	E1_LPR = m.GetParameter(3).GetLowerLimit();
	    	E1_UPR = m.GetParameter(3).GetUpperLimit();
	    	E2_LPR = m.GetParameter(4).GetLowerLimit();
	    	E2_UPR = m.GetParameter(4).GetUpperLimit();
	    }
	    
	    DblResults.push_back(E0_LPR); // # 32
	    DblResults.push_back(E0_UPR); // # 33
	    DblResults.push_back(p0_LPR); // # 34
	    DblResults.push_back(p0_UPR); // # 35
	    DblResults.push_back(p1_LPR); // # 36
	    DblResults.push_back(p1_UPR); // # 37
	    DblResults.push_back(p2_LPR); // # 38
	    DblResults.push_back(p2_UPR); // # 39
	    DblResults.push_back(E1_LPR); // # 40
	    DblResults.push_back(E1_UPR); // # 41
	    DblResults.push_back(E2_LPR); // # 42
	    DblResults.push_back(E2_UPR); // # 43
	    	    
	    JsonFile(params, params_err, IntResults, DblResults);
	    
	    //--------------------------------------------------------------------------------------------- PLOT: DATA+FIT
	    if ( outputK==0 || outputK==1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) { Draw_Pol1(E0, xL, xR, params, h); }
	    else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) { Draw_Gamma_Pol1(E0, E1, xL, xR, params, h); }
	    else { Draw_TwoGamma_Pol1(E0, E1, E2, xL, xR, params, h); }
    }
    
    
    
    // BKG = Pol2
    if ( pol_degree==2 ) {
    
  	    char name_model[100];
    	    if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) { sprintf(name_model,"%iGausPol2", E0); }
	    else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) { sprintf(name_model,"%iGausPol2_%gGamma", E0, E1); }
	    else { sprintf(name_model,"%iGausPol0_%gGamma_%gGamma", E0, E1, E2); }
	    
	    GausPol2 m(name_model, bin_content, E0, xL, xR, E1, E2, outputK);
  	    
   	    m.SetDataSet(&data_set);
    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kMedium);

	    m.MarginalizeAll(BCIntegrate::kMargMetropolis);

	    m.FindMode(m.GetBestFitParameters());
	    
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
	 
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf", 2, 2);
	  
	    m.PrintSummary();
	  
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
	    
	    if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
	    	    h_E1 = m.GetMarginalizedHistogram(4);
	    }
	    if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
		    h_E1 = m.GetMarginalizedHistogram(4);
		    h_E2 = m.GetMarginalizedHistogram(5);
	    }
	    
	    std::vector<double> DblResults = BATResults(outputK, pol_degree, h_E0, h_p0, h_p1, h_p2, h_E1, h_E2);
	    
	    DblResults.push_back(E1); // # 30
	    DblResults.push_back(E2); // # 31
	    
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
	    if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
	    	E1_LPR = m.GetParameter(4).GetLowerLimit();
	    	E1_UPR = m.GetParameter(4).GetUpperLimit();
	    }
	    if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
	    	E1_LPR = m.GetParameter(4).GetLowerLimit();
	    	E1_UPR = m.GetParameter(4).GetUpperLimit();
	    	E2_LPR = m.GetParameter(5).GetLowerLimit();
	    	E2_UPR = m.GetParameter(5).GetUpperLimit();
	    }
	    
	    DblResults.push_back(E0_LPR); // # 32
	    DblResults.push_back(E0_UPR); // # 33
	    DblResults.push_back(p0_LPR); // # 34
	    DblResults.push_back(p0_UPR); // # 35
	    DblResults.push_back(p1_LPR); // # 36
	    DblResults.push_back(p1_UPR); // # 37
	    DblResults.push_back(p2_LPR); // # 38
	    DblResults.push_back(p2_UPR); // # 39
	    DblResults.push_back(E1_LPR); // # 40
	    DblResults.push_back(E1_UPR); // # 41
	    DblResults.push_back(E2_LPR); // # 42
	    DblResults.push_back(E2_UPR); // # 43
	    	    
	    JsonFile(params, params_err, IntResults, DblResults);
	    
	    //---------------------------------------------------------------------------------------------
	    
	    // plot: data + fit
	    if ( outputK==0 || outputK==1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) { Draw_Pol2(E0, xL, xR, params, h); }
	    else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) { Draw_Gamma_Pol2(E0, E1, xL, xR, params, h); }
	    else { Draw_TwoGamma_Pol2(E0, E1, E2, xL, xR, params, h); }	    
    }

    return 0;
}
