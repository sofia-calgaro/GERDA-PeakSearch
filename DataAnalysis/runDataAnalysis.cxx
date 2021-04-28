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
#include "DrawPlots.h"
#include "args_reader.hpp"



int main(int argc, char *argv[])
{  

    std::vector<std::string> args(argc);
    std::copy(argv, argv+argc, args.begin());
  
    std::vector<int> inpval(7,0); // input values: {E0, pol_degree}
    bool found = fetch_arg(args, "--nums", inpval);
    
    if (found) {
    std::cout << "\n *************************" << std::endl;
    std::cout << "  # values = " << inpval[0] << "\n  E0 = " << inpval[1] << "\n  Polynomial degree = " << inpval[2];
    std::cout << "\n  xL = " << inpval[3] << "\n  xR = " << inpval[4] << "\n  k = " << inpval[5];
    std::cout << "\n  output[k] = " << inpval[6] << std::endl;
    std::cout << " *************************\n" << std::endl;
    }
    
    double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
    
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
    
    // create a new data point: E_gamma[k]
    int k = inpval[5];
    double EG = E_gamma[k];
    BCDataPoint* gammaEnergy = new BCDataPoint(1);
    if ( k>=0 && k<11 ) { gammaEnergy->SetValue(0, EG); }
    else { gammaEnergy->SetValue(0, 0); }
    data_set.AddDataPoint(*gammaEnergy);
    
    // create a new data point: output[k]
    int outputK = inpval[6];
    BCDataPoint* outInK = new BCDataPoint(1);
    outInK->SetValue(0, outputK);
    data_set.AddDataPoint(*outInK);
    
    // open log file
    int pol_degree = inpval[2];
    char name_log[100];
    sprintf(name_log,"/home/sofia/Analysis/DataAnalysis/Log_files/log_%i_GausPol%i.txt", E0, pol_degree);
    BCLog::OpenLog(name_log, BCLog::detail, BCLog::detail);	
    
    //---------------------------------------------------------------------------------------------------------------------- ANALYSIS     
    
    // Gaus + Pol0
    if ( pol_degree==0 ) {
    	
    	    char name_model[100];
    	    if ( outputK==50 || outputK==1 || outputK==4 || outputK==7 || outputK==15 || outputK==18 || outputK==20 || outputK==21 || outputK==22 ) { sprintf(name_model,"%iGausPol0", E0); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) { sprintf(name_model,"%iGausPol0_%gGamma", E0, EG); }
	    else { /*studio dei picchi che distano meno di 24 keV*/ }
	    
	    GausPol0 m(name_model, bin_content, E0, xL, xR, EG, outputK);
	    
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
	    
	    const std::vector<double> params = m.GetBestFitParameters();

	    // data + fit
	    if ( outputK==50 || outputK==1 || outputK==4 || outputK==7 || outputK==15 || outputK==18 || outputK==20 || outputK==21 || outputK==22 ) { Draw_Pol0(E0, xL, xR, params, h); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) { Draw_Gamma_Pol0(E0, EG, xL, xR, params, h); }
	    else { /*studio dei picchi che distano meno di 24 keV*/ }
	
	    
    }
    
    
    
    // Gaus + Pol1
    if ( pol_degree==1 ) {
    
   	    char name_model[100];
    	    if ( outputK==50 || outputK==1 || outputK==4 || outputK==7 || outputK==15 || outputK==18 || outputK==20 || outputK==21 || outputK==22 ) { sprintf(name_model,"%iGausPol1", E0); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) { sprintf(name_model,"%iGausPol1_%gGamma", E0, EG); }
	    else { /*studio dei picchi che distano meno di 24 keV*/ }
	    
	    GausPol1 m(name_model, bin_content, E0, xL, xR, EG, outputK);
   	    
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
	    
	    const std::vector<double> params = m.GetBestFitParameters();
	    
	    // data + fit
	    if ( outputK==50 || outputK==1 || outputK==4 || outputK==7 || outputK==15 || outputK==18 || outputK==20 || outputK==21 || outputK==22 ) { Draw_Pol1(E0, xL, xR, params, h); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) { Draw_Gamma_Pol1(E0, EG, xL, xR, params, h); }
	    else { /*studio dei picchi che distano meno di 24 keV*/ }
    }
    
    
    
    // Gaus + Pol2
    if ( pol_degree==2 ) {
    
  	    char name_model[100];
    	    if ( outputK==50 || outputK==1 || outputK==4 || outputK==7 || outputK==15 || outputK==18 || outputK==20 || outputK==21 || outputK==22 ) { sprintf(name_model,"%iGausPol2", E0); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) { sprintf(name_model,"%iGausPol2_%gGamma", E0, EG); }
	    else { /*studio dei picchi che distano meno di 24 keV*/ }
	    
	    GausPol2 m(name_model, bin_content, E0, xL, xR, EG, outputK);
  	    
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
	    
	    const std::vector<double> params = m.GetBestFitParameters();
	    
	    // data + fit
	    if ( outputK==50 || outputK==1 || outputK==4 || outputK==7 || outputK==15 || outputK==18 || outputK==20 || outputK==21 || outputK==22 ) { Draw_Pol2(E0, xL, xR, params, h); }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) { Draw_Gamma_Pol2(E0, EG, xL, xR, params, h); }
	    else { /*studio dei picchi che distano meno di 24 keV*/ }	    
    }

    return 0;
}

