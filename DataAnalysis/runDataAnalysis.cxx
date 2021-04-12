#include <BAT/BCLog.h>
#include <TFile.h>
#include <TMath.h>

// MODELS
#include "GausPol0.h"
#include "GausPol1.h"

// FUNCTIONS
#include "Operations.h"



int main()
{
    TFile *file = new TFile("/home/sofia/gerda_data/IC_20210406.root","READ");
    TH1D *h = (TH1D*) file->Get("histo_energy_LArVetoed");
    std::vector< int> bin_content;
    for ( int i=1; i<=5200; i++ ) { bin_content.push_back( h->GetBinContent(i) ); }
    
    BCLog::OpenLog("log.txt", BCLog::detail, BCLog::detail);
    		
    // create a new dataset to pass then to the model
    BCDataSet data_set;
    data_set.ReadDataFromFileTxt("/home/sofia/gerda_data/bin_content.txt", 1);
    
    // create a new data point: E0
    int E0 = 351;
    BCDataPoint* CentralEnergy = new BCDataPoint(1);
    CentralEnergy->SetValue(0,E0);
    data_set.AddDataPoint(*CentralEnergy);	
    
    int x1 = E0 - 12;
    int x2 = E0 + 12;		

    	
    /*================================================================================================= FUTURE IDEA
    
    1) Fare qui la selezione sul modello da usare ( => for+if per vedere se ci sono picchi così da
          cambiare eventualmente x1 e x2), tipo:
 
	    double *x1_new, *x2_new;
	    int return_0 = FindNewEdges(x1, x2, &x1_new, &x2_new); // dove funzione è la serie di if
    
    2) Definire i vari modelli da considerare e selezionarne solo uno in seguito tramite statement if, tipo:
    
            if (x2<120) { pol2 (no picchi) || pol2+gaus_s (picco segnale) || pol2+gaus_s+gaus_g (picco segnale+gamma) }
            if (x2>120 && x<1000) { pol1 || pol1+gaus_s || pol1+gaus_s+gaus_g } 
    		
    =================================================================================================== */
    
    
    //GausPol0 m("GausPol0", bin_content, E0);
    GausPol1 m("GausPol1", bin_content, E0); // uncomment this if you want to use it (and comment the other one)
     
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
    
    // draw all marginalized distributions into a PDF file
    m.PrintAllMarginalized(m.GetSafeName() + "_plots.pdf");
    
    // print summary plots
    m.PrintParameterPlot(m.GetSafeName() + "_parameters.pdf");
    m.PrintCorrelationPlot(m.GetSafeName() + "_correlation.pdf");
    //m.PrintCorrelationMatrix(m.GetSafeName() + "_correlationMatrix.pdf");
    m.PrintKnowledgeUpdatePlots(m.GetSafeName() + "_update.pdf");
    
   
    double chi2=0;
    const std::vector<double> params = m.GetBestFitParameters();
    
    for ( int i=x1; i<x2-1; i++ ) {
		    
	    int y_obs =  m.GetDataSet()->GetDataPoint(i).GetValue(0);
	    
	    double sigma_E0 = FindSigma(E0);
	    
	    //double y_exp =  params.at(0) * TMath::Gaus(i, E0, sigma_E0, false) + params.at(1);
	    double y_exp =  params.at(0) * TMath::Gaus(i, E0, sigma_E0, false) + params.at(1) + params.at(2)*(i-E0); // uncomment this if you use the GausPol1 model (and comment the other one)
	    
	    chi2 += pow( y_obs-y_exp, 2) / y_exp; // Pearson chi2 for Poisson distributed data
    }
    
    int nu = ( x2 - x1 ) - params.size();
    
    double p_value = TMath::Prob( chi2, nu);


    m.PrintSummary();
    
    std::cout << "\n\t*******************************************************" << std::endl;
    std::cout << "\n\t   CHI2 = " << chi2 << " ( DoF = " << nu << " )\t p-VALUE = " << p_value << std::endl;
    std::cout << "\n\t*******************************************************\n" << std::endl;    

    BCLog::OutSummary("Exiting");
    BCLog::CloseLog();

    return 0;
}

