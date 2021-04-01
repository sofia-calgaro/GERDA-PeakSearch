// ***************************************************************
// This file was created using the bat-project script
// for project DataAnalysis.
// bat-project is part of Bayesian Analysis Toolkit (BAT).
// BAT can be downloaded from http://mpp.mpg.de/bat
// ***************************************************************


#include "DataAnalysis.h"
#include <TMath.h>

int vector_from_data(std::vector<int> *trial_vec); // returns a vector filled with data
bool find_max(int a, int b); // returns 'true' only if b > a
int find_sigma_FWHM(int energy, double *sigma_E0, double *FWHM); // calculates the energetic resolution and FWHM for a given energy value



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
DataAnalysis::DataAnalysis(const std::string& name)
    : BCModel(name)
{

/*
            // Get the vector containing the experimental data
            std::vector<int> vettore;
            int output2 = vector_from_data(&vettore);
            if ( output2 == 1 ) { std::cout << "There is a problem" << std::endl; } 

            int x1 = 340;
            int x2 = x1+24;
            int E0 = x1+12;
                            
            double sigma_E0, FWHM;
            int output = find_sigma_FWHM(E0, &sigma_E0, &FWHM);
            if ( output == 1 ) { std::cout << "There is a problem" << std::endl; }
                         
            int x1_stop = std::round( E0 - 1.5*FWHM );
            int x2_start = std::round( E0 + 1.5*FWHM );
                    
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
            AddParameter("height", 0, 50, "", "[events]");
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

            int x1 = 340;
            int x2 = x1+24;
            int E0 = x1+12;

            double sigma_E0, FWHM;
            int output = find_sigma_FWHM(E0, &sigma_E0, &FWHM);
            if ( output == 1 ) { std::cout << "There is a problem" << std::endl; }


            // Get the vector containing the experimental data
            std::vector<int> vettore;
            int output2 = vector_from_data(&vettore);
            if ( output2 == 1 ) { std::cout << "There is a problem" << std::endl; }

            // Loop over 24 elements
            for ( int i=x1; i<x2-1; i++ ) {

                    int y_obs = vettore.at(i); // observed value
                    //std::cout << "\n\ti = " << i << "\t y = " << y_obs << std::endl;      

                    double y_exp =  pars[0] * TMath::Gaus(i, E0, sigma_E0, false) + pars[1]; // expected value

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////
int vector_from_data(std::vector<int> *trial_vec) {

    if ( trial_vec == NULL ) { return 1; } // ERRROR

    std::fstream read;
    read.open("vector_content.txt", std::ios::in);

    int value;

    while (read >> value) {
    trial_vec->push_back(value);
    }
    
    read.close();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
bool find_max(int a, int b) {
   return (a < b);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
int find_sigma_FWHM(int energy, double *sigma_E0, double *FWHM) {

   if ( sigma_E0 == NULL || FWHM == NULL ) { return 1; } // ERRROR

   const double a = 0.280;   // a=0.280(2) keV^2 (electronic noise)
   const double b = 5.83e-4; // b=5.83e-004(2) keV (fluctuation of the # of charge carriers)

   *sigma_E0 =  sqrt( a + b*energy );
   *FWHM = sqrt( 8*log(2) ) * sqrt( a + b*energy );

   return 0;
}
