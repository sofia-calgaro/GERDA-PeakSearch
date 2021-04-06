// ***************************************************************
// This file was created using the bat-project script
// for project DataAnalysis.
// bat-project is part of Bayesian Analysis Toolkit (BAT).
// BAT can be downloaded from http://mpp.mpg.de/bat
// ***************************************************************

#include <BAT/BCLog.h>
#include <TFile.h>

#include "DataAnalysis.h"



// Functions to use in model source files (definitions are below the main() function)
bool find_max(int a, int b); // returns 'true' only if b > a
int find_sigma_FWHM(int energy, double *sigma_E0, double *FWHM); // calculates the energetic resolution and FWHM for a given energy value



int main()
{
    // Creazione di un vettore a partire da un TObject del file ROOT (per ora non mi serve)
    //TFile *file = new TFile("/home/sofia/gerda_data/IC_20210406.root","READ");
    //const std::vector<unsigned int> *bin_content;
    //file->GetObject("energy_LAr", bin_content);
    
    BCLog::OpenLog("log.txt", BCLog::detail, BCLog::detail);
    		
    // create a new dataset to pass then to the model
    BCDataSet data_set;
    data_set.ReadDataFromFileTxt("/home/sofia/gerda_data/bin_content.txt", 1); // 1 column
    
    // NB: un modo rapido per passare valori da usare nelle funzioni di DataAnalysis.cxx/GausPol1.cxx è quello
    // di aggiungere i valori in questione alla fine dei 5200 valori del contenuto dei bin dello spettro energetico
    // (la cosa è facilmente realizzabile considerato che al momento si tratta di aggiungere solo 3 valori).
    // In questo modo i valori associati al contenuto dei bin andranno da 1 a 5200, mentre E0 <-> #5201, x1 <-> #5202, x2 <-> #5203.
    // NB: non si possono associare più dataset allo stesso modello! (altrimenti l'avrei fatto per separare un po' le cose)
    
    // create a new data point: E0
    int E0 = 352;
    BCDataPoint* CentralEnergy = new BCDataPoint(1);
    CentralEnergy->SetValue(0,E0); // E0 sarà da incrementare in futuro
    data_set.AddDataPoint(*CentralEnergy);	
    	
    	
    //-------------------------------------------------------------------------------------------------- FUTURE IDEA
    
    // Idea: fare qui la selezione sul modello da usare ( => for+if per vedere se ci sono picchi
    // così da cambiare eventualmente x1 e x2)
    		
    //--------------------------------------------------------------------------------------------------		
    
    
    // create a new data point: x1 	
    int x1 = E0-12;
    BCDataPoint* left_x_limit = new BCDataPoint(1);
    left_x_limit->SetValue(0,x1);
    data_set.AddDataPoint(*left_x_limit);	
    
    // create a new data point: x2
    int x2 = E0+12;	
    BCDataPoint* right_x_limit = new BCDataPoint(1);
    right_x_limit->SetValue(0,x2);
    data_set.AddDataPoint(*right_x_limit);		
    
    
    //-------------------------------------------------------------------------------------------------- FUTURE IDEA
    
    // Idea: definire i vari modelli da considerare e selezionarne uno con statement if
    		
    //--------------------------------------------------------------------------------------------------
    
    
    DataAnalysis m("GausPol0");
    //GausPol1 m("GausPol1"); // uncomment this if you want to use it (and comment the other one)
     
    // associate the data set with the model
    m.SetDataSet(&data_set);
    
    
    //-------------------------------------------------------------------------------------------------- ANALYSIS
    
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
    //m.PrintParameterPlot(m.GetSafeName() + "_parameters.pdf");
    //m.PrintCorrelationPlot(m.GetSafeName() + "_correlation.pdf");
    //m.PrintCorrelationMatrix(m.GetSafeName() + "_correlationMatrix.pdf");
    //m.PrintKnowledgeUpdatePlots(m.GetSafeName() + "_update.pdf");
    
    m.PrintSummary();

    BCLog::OutSummary("Exiting");
    BCLog::CloseLog();

    return 0;
}





//----------------------------------------------------------------------------------------------------- FUNCTIONS
bool find_max(int a, int b) {
   return (a < b);
}
//-----------------------------------------------------------------------------------------------------
int find_sigma_FWHM(int energy, double *sigma_E0, double *FWHM) {

   if ( sigma_E0 == NULL || FWHM == NULL ) { return 1; } // ERRROR

   const double a = 0.280;   // a=0.280(2) keV^2 (electronic noise)
   const double b = 5.83e-4; // b=5.83e-004(2) keV (fluctuation of the # of charge carriers)

   *sigma_E0 =  sqrt( a + b*energy );
   *FWHM = sqrt( 8*log(2) ) * sqrt( a + b*energy );

   return 0;
}
