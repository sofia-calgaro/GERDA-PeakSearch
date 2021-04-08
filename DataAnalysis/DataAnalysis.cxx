#include "DataAnalysis.h"
#include <TMath.h>

bool find_max(int a, int b); // returns 'true' only if b > a
double find_sigma(int energy); // calculates the energetic resolution for a given energy value
double find_FWHM(int energy); // calculates the FWHM for a given energy value

// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
DataAnalysis::DataAnalysis(const std::string& name, const std::vector<unsigned int> *bin_content, int E0)
    : BCModel(name)
{

            int x1 = E0-12;
            int x2 = E0+12;
                            
            double FWHM = find_FWHM(E0);
           
            int x1_stop = std::round( E0 - 1.5*FWHM );
            int x2_start = std::round( E0 + 1.5*FWHM );
                   
            int B_i = 0;
                    
            for ( int i=x1+1; i<=x1_stop; i++ ) { B_i += bin_content->at(i); }
            
            for ( int i=x2_start+1; i<=x2; i++ ) { B_i += bin_content->at(i); }
                    
            int N_bkg = ( x1_stop - x1 ) + ( x2 - x2_start );
            int B_avg = std::round( B_i / N_bkg );
                    
            int S_i = 0;
            for ( int i=x1_stop+1; i<=x2_start; i++ ) { S_i += bin_content->at(i); }
                    
            int N_sig = x2_start-x1_stop;
                    
            int B_sig = N_sig*B_avg;
                    
            int S = std::round ( S_i-B_sig );                
                    
            int max1 = std::round( S + 5*sqrt(B_sig) + 5*sqrt(S) );
            int max2 = std::round( 8*sqrt(B_sig) );
            int max3 = 10;
            int max = std::max({max1, max2, max3},find_max);
        

            // Let's add parameters/priors for a Gaussian+pol0 function:
            // 1) Signal yield (index 0)
            AddParameter("height", 0, max, "", "[events]");
            GetParameters().Back().SetPriorConstant();

            // 2) Constant (index 1)
            AddParameter("p0", 0, 80, "p0", "[events]");
            GetParameters().Back().SetPriorConstant();
}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
DataAnalysis::~DataAnalysis() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double DataAnalysis::LogLikelihood(const std::vector<double>& pars)
{

            double LP = 0.;
            
            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int x1 = E0-12;
            int x2 = E0+12;

            double sigma_E0 = find_sigma(E0);

            // Loop over 24 elements
            for ( int i=x1; i<x2-1; i++ ) {
		    
                    int y_obs =  GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )

                    double y_exp =  pars[0] * TMath::Gaus(i, E0, sigma_E0, false) + pars[1]; // expected value

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
}
