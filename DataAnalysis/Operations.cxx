// **********************************************************************************************************************
// This file contains different functions that are called in the main source file of the analysis
// ("runDataAnalysis.cxx").
// To use these functions you must include this file with ' #include "Operaions.h" '.
// **********************************************************************************************************************
#include "Operations.h"



//-----------------------------------------------------------------------------------------------------------------------
// Returns 'true' only if b > a
bool FindMax(int a, int b) {
   return (a < b);
}



//-----------------------------------------------------------------------------------------------------------------------
// Calculates the energetic resolution for a given energy value 
double FindSigma(int energy) {

   const double a = 0.280;   // a=0.280(2) keV^2 (electronic noise)
   const double b = 5.83e-4; // b=5.83e-004(2) keV (fluctuation of the # of charge carriers)

   double sigma =  sqrt( a + b*energy );

   return sigma;
}



//-----------------------------------------------------------------------------------------------------------------------
// Calculates the FWHM for a given energy value
double FindFWHM(int energy) {

   const double a = 0.280;   
   const double b = 5.83e-4; 

   double FWHM = sqrt( 8*log(2) ) * sqrt( a + b*energy );

   return FWHM;
}



//-----------------------------------------------------------------------------------------------------------------------
// Calculates the maximum of the signal height paramter
int *FindMaximumSignalHeight(int energy, std::vector<int> bin_signal) {

   int x1 = energy - 12;
   int x2 = energy + 12;
   
   double FWHM = FindFWHM(energy);
   
   // Let's define the range [x1_signal;x2_signal] in which the signal contribution (S) is calculated
   int x1_signal = std::round( energy - 1.5*FWHM );
   int x2_signal = std::round( energy + 1.5*FWHM );
            
   // Calculate the average BKG outside [x1_signal;x2_signal]   
   int B_i = 0;
                    
   for ( int i=x1; i<x1_signal; i++ ) { B_i += bin_signal.at(i); }
           
   for ( int i=x2_signal; i<x2; i++ ) { B_i += bin_signal.at(i); }
                    
   int N_bkg = ( x1_signal - x1 ) + ( x2 - x2_signal );
   int B_avg = std::round( B_i / N_bkg );
                    
   // Calculate the overall bin content in [x1_signal;x2_signal]        
   int S_i = 0;
   for ( int i=x1_signal; i<x2_signal; i++ ) { S_i += bin_signal.at(i); }
                    
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
   
   int *output = new int[4];
   output[0] = B_avg;
   output[1] = B_sig;
   output[2] = S;
   output[3] = max;
   
   return output;
}



//-----------------------------------------------------------------------------------------------------------------------
// Find the range in which the BKG-Pol0 parameters of the models vary
double *FindRangeOfBKGParameters_Pol0(int energy, std::vector<int> bin_content, int *output) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=energy-12; i<energy+12; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }

   // ROOT fit: f0 = pol0 
   if ( output[2] < 3*sqrt(output[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0]", energy-20, energy+20);
	   
	   int S_avg;
	   for (int i=energy-10; i<energy+10; i++) { S_avg += bin_content.at(i); }
	   S_avg = std::round(S_avg/20);
	   f0->SetParameter(0, S_avg);
	   
	   h_energy->Fit("f0","RQNO");
	   
	   double *output_fit_pol0 = new double[2];
	   output_fit_pol0[0] = f0->GetParameter(0); // constant
	   output_fit_pol0[1] = f0->GetParError(0);
	   
	   return output_fit_pol0; 
   }
   
   // ROOT fit: f0 = pol0 + gaus
   else {
   	   
   	   TF1 *f0 = new TF1("f0","[0] + TMath::Gaus(x, [2], [3], false)", energy-20, energy+20);
   	   
	   int S_avg;
	   for (int i=energy-10; i<energy+10; i++) { S_avg += bin_content.at(i); }
	   S_avg = std::round(S_avg/20);
	   f0->SetParameter(0, S_avg);
	   
	   f0->SetParameter(1, output[3]);
	   f0->FixParameter(2, energy);
	   
	   double sigma_E0 = FindSigma(energy);
	   f0->FixParameter(3, sigma_E0);   
	   
   	   h_energy->Fit("f0","RQNO");
   
   	   double *output_fit_pol0 = new double[8];
	   output_fit_pol0[0] = f0->GetParameter(0); // constant
	   output_fit_pol0[1] = f0->GetParError(0);
	   output_fit_pol0[2] = f0->GetParameter(1); // height
	   output_fit_pol0[3] = f0->GetParError(1);
	   output_fit_pol0[4] = f0->GetParameter(2); // E0
	   output_fit_pol0[5] = f0->GetParError(2);
	   output_fit_pol0[6] = f0->GetParameter(3); // sigma
	   output_fit_pol0[7] = f0->GetParError(3);
	   
	   return output_fit_pol0;
   }

}



//-----------------------------------------------------------------------------------------------------------------------
// Find the range in which the BKG-Pol1 parameters of the models vary
double *FindRangeOfBKGParameters_Pol1(int energy, std::vector<int> bin_content, int *output) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=energy-12; i<energy+12; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }

   // ROOT fit: f1 = pol1
   if ( output[2] < 3*sqrt(output[1]) ) { 
	
   	   TF1 *f1 = new TF1("f1","[0]+[1]*x", energy-20, energy+20);
   	   
   	   int S_avg;
	   for (int i=energy-10; i<energy+10; i++) { S_avg += bin_content.at(i); }
	   S_avg = std::round(S_avg/20);
	   f1->SetParameter(0, S_avg);
	   
	   h_energy->Fit("f1","RQNO");
	   
	   double *output_fit_pol1 = new double[4];
	   output_fit_pol1[0] = f1->GetParameter(0); // constant
	   output_fit_pol1[1] = f1->GetParError(0);
	   output_fit_pol1[2] = f1->GetParameter(1); // slope
	   output_fit_pol1[3] = f1->GetParError(2);
	   
	   return output_fit_pol1; 
   }
   
   // ROOT fit: f1 = pol1 + gaus
   else {
   	   
   	   char function[50];
   	   sprintf(function,"[0]+[1]*(x-%i)+TMath::Gaus(x, [2], [3], false)",energy);
   	   TF1 *f1 = new TF1("f1",function, energy-20, energy+20);
   	   
   	   int S_avg;
	   for (int i=energy-10; i<energy+10; i++) { S_avg += bin_content.at(i); }
	   S_avg = std::round(S_avg/20);
	   f1->SetParameter(0, S_avg);
	   
   	   f1->SetParLimits(2, 0, output[3]);
	   f1->FixParameter(3, energy);
	   
	   double sigma_E0 = FindSigma(energy);
	   f1->FixParameter(4, sigma_E0);   
	   
	   h_energy->Fit("f1","RQNO");
	   
	   double *output_fit_pol1 = new double[10];
	   output_fit_pol1[0] = f1->GetParameter(0); // constant
	   output_fit_pol1[1] = f1->GetParError(0);
	   output_fit_pol1[2] = f1->GetParameter(1); // slope
	   output_fit_pol1[3] = f1->GetParError(1);
	   output_fit_pol1[4] = f1->GetParameter(2); // height
	   output_fit_pol1[5] = f1->GetParError(2);
	   output_fit_pol1[6] = f1->GetParameter(3); // E0
	   output_fit_pol1[7] = f1->GetParError(3);
	   output_fit_pol1[8] = f1->GetParameter(4); // sigma
	   output_fit_pol1[9] = f1->GetParError(4);
	   
	   return output_fit_pol1;    
   }

}



//-----------------------------------------------------------------------------------------------------------------------
// Find the new edges x1_new, x2_new in case a gamma peak is present in proximity of the fit window  (E' ANCORA DA IMPLEMENTARE)
/*int FindNewEdges(int i_min, int i_max, int *x1_new, int *x2_new) {

 ... dopo aver controllato che gli if funzionino correttamente,
 inserire qui quanto fatto in HistoFitter.C ...
 
}*/
