// BAT
#include <BAT/BCLog.h>
#include <BAT/BCH1D.h>
#include <BAT/BCAux.h>

// ROOT
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>

// MODELS
#include "GausPol0.h"
#include "GausPol1.h"
#include "GausPol2.h"

// FUNCTIONS
#include "Operations.h"



int main()
{
    TFile *file = new TFile("IC_20210406.root","READ");
    TH1D *h = (TH1D*) file->Get("histo_energy_LArVetoed");
    std::vector< int> bin_content;
    for ( int i=1; i<=5200; i++ ) { bin_content.push_back( h->GetBinContent(i) ); }
    
    BCLog::OpenLog("log.txt", BCLog::detail, BCLog::detail);
    		
    // create a new dataset to pass then to the model
    BCDataSet data_set;
    data_set.ReadDataFromFileTxt("bin_content.txt", 1);
    
    // create a new data point: E0
    int E0 = 351;
    BCDataPoint* CentralEnergy = new BCDataPoint(1);
    CentralEnergy->SetValue(0,E0);
    data_set.AddDataPoint(*CentralEnergy);	
    
    int x1 = E0 - 12;
    int x2 = E0 + 12;		
    
    GausPol0 m("GausPol0", bin_content, E0);
    //GausPol1 m("GausPol1", bin_content, E0);
    //GausPol2 m("GausPol2", bin_content, E0);
     
    // Associate the data set with the model
    m.SetDataSet(&data_set);
    
    //------------------------------------------------------------------------------------------------- ANALYSIS
    
    BCLog::OutSummary("Test model created");

    m.SetPrecision(BCEngineMCMC::kMedium);

    // Normalize the posterior by integrating it over the full parameter space
    // m.Normalize();

    // Write Markov Chain to a ROOT file as a TTree
    // m.WriteMarkovChain(m.GetSafeName() + "_mcmc.root", "RECREATE");

    // run MCMC, marginalizing posterior
    m.MarginalizeAll(BCIntegrate::kMargMetropolis);

    // run mode finding; by default using Minuit
    m.FindMode(m.GetBestFitParameters());
    
    // fix the bands for each posterior at 68.3%, 95.4%, 99.7%
    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
    
    // Background analysis: to find the percentage of area subtended
    // in [par0-10*sigma;par0+10*sigma], for example, when m=GausPol0
    BCH1D h_trial = m.GetMarginalized(1);
    int *output = FindMaximumSignalHeight( E0, bin_content);
    double perc = PosteriorInspection( E0, bin_content, output, h_trial);
    std::cout << "\n\t Underlying area in [par0-10*err;par0+10*err] = " << perc << " %\n" << std::endl;
 
    // draw all marginalized distributions into a PDF file
    m.PrintAllMarginalized(m.GetSafeName() + "_plots.pdf");
    
    // print summary plots
    //m.PrintParameterPlot(m.GetSafeName() + "_parameters.pdf");
    //m.PrintCorrelationPlot(m.GetSafeName() + "_correlation.pdf");
    //m.PrintCorrelationMatrix(m.GetSafeName() + "_correlationMatrix.pdf");
    //m.PrintKnowledgeUpdatePlots(m.GetSafeName() + "_update.pdf");
  
    m.PrintSummary();
  
    BCLog::OutSummary("Exiting");
    BCLog::CloseLog();

    return 0;
}

