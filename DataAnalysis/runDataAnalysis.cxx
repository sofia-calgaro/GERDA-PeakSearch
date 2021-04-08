#include <BAT/BCLog.h>
#include <TFile.h>
#include <TMath.h>

#include "DataAnalysis.h"



// Functions to use in model source files (definitions are below the main() function)

bool find_max(int a, int b); // returns 'true' only if b > a
double find_sigma(int energy); // calculates the energetic resolution for a given energy value
double find_FWHM(int energy); // calculates the FWHM for a given energy value



int main()
{
    // Creazione di un vettore a partire da un TObject del file ROOT (per ora non mi serve)
    TFile *file = new TFile("/home/sofia/gerda_data/IC_20210406.root","READ");
    const std::vector<unsigned int> *bin_content;
    file->GetObject("energy_LAr", bin_content);
    
    BCLog::OpenLog("log.txt", BCLog::detail, BCLog::detail);
    		
    // create a new dataset to pass then to the model
    BCDataSet data_set;
    data_set.ReadDataFromFileTxt("/home/sofia/gerda_data/bin_content.txt", 1); // 1 column
    
    // NB: un modo rapido per passare valori da usare nelle funzioni di DataAnalysis.cxx/GausPol1.cxx è quello
    // di aggiungere i valori in questione alla fine dei 5200 valori del contenuto dei bin dello spettro energetico
    // (la cosa è facilmente realizzabile considerato che al momento si tratta di aggiungere solo 1 valore).
    // In questo modo i valori associati al contenuto dei bin andranno da 1 a 5200, mentre E0 <-> #5201.
    
    // create a new data point: E0
    int E0 = 352;
    BCDataPoint* CentralEnergy = new BCDataPoint(1);
    CentralEnergy->SetValue(0,E0); // E0 sarà da incrementare in futuro
    data_set.AddDataPoint(*CentralEnergy);	
    
    int x1 = E0-12;
    int x2 = E0+12;		
    	
    	
    //================================================================================================== FUTURE IDEA
    
    // 1) Fare qui la selezione sul modello da usare ( => for+if per vedere se ci sono picchi così da
    //    cambiare eventualmente x1 e x2)
    				
    // 2) Definire i vari modelli da considerare e selezionarne solo uno in seguito tramite statement if
    		
    //==================================================================================================
    
    
    DataAnalysis m("GausPol0", bin_content, E0);
    //GausPol1 m("GausPol1"); // uncomment this if you want to use it (and comment the other one)
     
    m.SetDataSet(&data_set); // associate the data set with the model
    
    
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
    
    
    double chi2=0;
    const std::vector<double> params = m.GetBestFitParameters();
    
    for ( int i=x1; i<x2-1; i++ ) {
		    
	    int y_obs =  m.GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )
	    
	    double sigma_E0 = find_sigma(E0);
	    double y_exp =  params.at(0) * TMath::Gaus(i, E0, sigma_E0, false) + params.at(1); // expected value
	    
	    chi2 += pow( y_obs-y_exp, 2) / y_exp; // Pearson chi2
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





//----------------------------------------------------------------------------------------------------- FUNCTIONS
bool find_max(int a, int b) {
   return (a < b);
}
//-----------------------------------------------------------------------------------------------------
double find_sigma(int energy) {

   const double a = 0.280;   // a=0.280(2) keV^2 (electronic noise)
   const double b = 5.83e-4; // b=5.83e-004(2) keV (fluctuation of the # of charge carriers)

   double sigma =  sqrt( a + b*energy );

   return sigma;
}
//-----------------------------------------------------------------------------------------------------
double find_FWHM(int energy) {

   const double a = 0.280;   
   const double b = 5.83e-4; 

   double FWHM = sqrt( 8*log(2) ) * sqrt( a + b*energy );

   return FWHM;
}
