// ****************************************************************************************************
// This file contains different functions that are called in the main source file of the analysis
// ("runDataAnalysis.cxx").
// To use these functions you must include this file with ' #include "Operaions.h" '.
// ****************************************************************************************************
#include "Operations.h"
#include <TMath.h>



// Returns 'true' only if b > a
bool FindMax(int a, int b) {
   return (a < b);
}



// Calculates the energetic resolution for a given energy value 
double FindSigma(int energy) {

   const double a = 0.280;   // a=0.280(2) keV^2 (electronic noise)
   const double b = 5.83e-4; // b=5.83e-004(2) keV (fluctuation of the # of charge carriers)

   double sigma =  sqrt( a + b*energy );

   return sigma;
}



// Calculates the FWHM for a given energy value
double FindFWHM(int energy) {

   const double a = 0.280;   
   const double b = 5.83e-4; 

   double FWHM = sqrt( 8*log(2) ) * sqrt( a + b*energy );

   return FWHM;
}



// Calculates the maximum of the signal height paramter
int FindMaximumSignalHeight(int energy, const std::vector<unsigned int> *bin_signal) {

   int x1 = energy - 12;
   int x2 = energy + 12;
   
   double FWHM = FindFWHM(energy);
   
   // Let's define the range [x1_signal;x2_signal] in which the signal contribution (S) is calculated
   int x1_signal = std::round( energy - 1.5*FWHM );
   int x2_signal = std::round( energy + 1.5*FWHM );
            
   // Calculate the average BKG outside [x1_signal;x2_signal]   
   int B_i = 0;
                    
   for ( int i=x1+1; i<=x1_signal; i++ ) { B_i += bin_signal->at(i); }
           
   for ( int i=x2_signal+1; i<=x2; i++ ) { B_i += bin_signal->at(i); }
                    
   int N_bkg = ( x1_signal - x1 ) + ( x2 - x2_signal );
   int B_avg = std::round( B_i / N_bkg );
                    
   // Calculate the overall bin content in [x1_signal;x2_signal]        
   int S_i = 0;
   for ( int i=x1_signal+1; i<=x2_signal; i++ ) { S_i += bin_signal->at(i); }
                    
   int N_sig = x2_signal-x1_signal;
            
   // Calculate the amount of BKG in [x1_signal;x2_signal]        
   int B_sig = N_sig*B_avg;
            
   // Calculate the signal in [x1_signal;x2_signal]      
   int S = std::round ( S_i-B_sig );                
                    
   // Find the maximum value that the signal height can assume        
   int max1 = std::round( S + 5*sqrt(B_sig) + 5*sqrt(S) );
   int max2 = std::round( 8*sqrt(B_sig) );
   int max3 = 10;
   int max = std::max({max1, max2, max3},FindMax);
   
   return max;
}



// Find the new edges x1_new, x2_new in case a gamma peak is present in proximity of the fit window
/*int FindNewEdges(int i_min, int i_max, int *x1_new, int *x2_new) {

 ... dopo aver controllato che gli if funzionino correttamente,
 inserire qui quanto fatto in HistoFitter.C ...
 
}*/
