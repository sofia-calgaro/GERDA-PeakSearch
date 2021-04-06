// ***************************************************************
// This file was created using the bat-project script
// for project DataAnalysis.
// bat-project is part of Bayesian Analysis Toolkit (BAT).
// BAT can be downloaded from http://mpp.mpg.de/bat
// ***************************************************************


//#include "GausPol1.h"
#include "DataAnalysis.h"
#include <TMath.h>

bool find_max(int a, int b); // returns 'true' only if b > a
int find_sigma_FWHM(int energy, double *sigma_E0, double *FWHM); // calculates the energetic resolution and FWHM for a given energy value

// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol1::GausPol1(const std::string& name)
    : BCModel(name)
{

/*
            // Get the vector containing the experimental data
            std::vector<int> vettore;
            int output2 = vector_from_data(&vettore);
            if ( output2 == 1 ) { std::cout << "There is a problem" << std::endl; } 

            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int x1 = GetDataSet()->GetDataPoint(5202).GetValue(0);
            int x2 = GetDataSet()->GetDataPoint(5203).GetValue(0);
                            
            double sigma_E0, FWHM;
            int output = find_sigma_FWHM(*E0, &sigma_E0, &FWHM);
            if ( output == 1 ) { std::cout << "There is a problem" << std::endl; }
                         
            int x1_stop = std::round( *E0 - 1.5*FWHM );
            int x2_start = std::round( *E0 + 1.5*FWHM );
                    
            int B_i = 0;
                    
            for ( int i=x1+1; i<=x1_stop; i++ ) { B_i += vettore.at(i); }
            
            for ( int i=x2_start+1; i<=x2; i++ ) { B_i += vettore.at(i); }
                    
            int N_bkg = ( x1_stop - x1 ) + ( x2 - x2_start );
            int B_avg = std::round( B_i / N_bkg );
                    
            int S_i = 0;
            for ( int i=x1_stop+1; i<=x2_start; i++ ) { S_i += vettore.at(i); }
                    
            int N_sig = x2_start-x1_stop;
                    
            int B_sig = N_sig*B_avg;
                    
            int S = std::round ( S_i-B_sig );                
                    
            int max1 = std::round( S + 5*sqrt(B_sig) + 5*sqrt(S) );
            int max2 = std::round( 8*sqrt(B_sig) );
            int max3 = 10;
            int max = std::max({max1, max2, max3},find_max);
        */

            // Let's add parameters/priors for a Gaussian+pol0 function:
            // 1) Signal yield (index 0)
            AddParameter("height", 0, 10e4, "", "[events]");
            GetParameters().Back().SetPriorConstant();

            // 2) Constant (index 1)
            AddParameter("p0", 0, 10e4, "p0", "[events]");
            GetParameters().Back().SetPriorConstant();
            
            // 3) Slope (index 2)
            AddParameter("p1", -1, 0, "p1", "[events/keV]");
            GetParameters().Back().SetPriorConstant();
}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
GausPol1::~GausPol1() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double GausPol1::LogLikelihood(const std::vector<double>& pars)
{

            double LP = 0.;
            
            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int x1 = GetDataSet()->GetDataPoint(5202).GetValue(0);
            int x2 = GetDataSet()->GetDataPoint(5203).GetValue(0);

            double sigma_E0, FWHM;
            int output = find_sigma_FWHM(E0, &sigma_E0, &FWHM);
            if ( output == 1 ) { std::cout << "There is a problem" << std::endl; }

            // Loop over 24 elements
            for ( int i=x1; i<x2-1; i++ ) {
		    
                    int y_obs =  GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )

                    double y_exp =  pars[0] * TMath::Gaus(i, E0, sigma_E0, false) + pars[1] + pars[2]*(i-E0); // expected value

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
}
