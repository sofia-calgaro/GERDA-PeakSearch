// **********************************************************************************************************************
// This file contains different functions that are called in the main source file ("runDataAnalysis.cxx").
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
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }

   // ROOT fit: f0 = pol0 
   if ( output[2] < 3*sqrt(output[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0]", energy-20, energy+20);
	   
	   int S_avg = 0;
	   for (int i=energy-20; i<energy+20; i++) { S_avg += bin_content.at(i); }
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
   	   
	   int S_avg = 0;
	   for (int i=energy-20; i<energy+20; i++) { S_avg += bin_content.at(i); }
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
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }

   // ROOT fit: f1 = pol1
   if ( output[2] < 3*sqrt(output[1]) ) { 
	 
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i)", energy);
   	   TF1 *f1 = new TF1("f1", function, energy-20, energy+20);
   	   
   	   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   	   double q = - ( 2*(energy-20)*bin_content.at(energy-20) - (energy-20)*bin_content.at(energy+20) - (energy+20)*bin_content.at(energy-20) ) / ( (energy-20) - (energy+20) );
   	   double m = ( bin_content.at(energy-20) - bin_content.at(energy+20) ) / ( (energy-20) - (energy+20) + 0.0 ); // 0.0 is needed since we are dividing an int by an int, but we want a double
   	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   h_energy->Fit("f1","R");
	   
	   double *output_fit_pol1 = new double[4];
	   output_fit_pol1[0] = f1->GetParameter(0); // constant
	   output_fit_pol1[1] = f1->GetParError(0);
	   output_fit_pol1[2] = f1->GetParameter(1); // slope
	   output_fit_pol1[3] = f1->GetParError(1);
	   
	   return output_fit_pol1; 
   }
   
   // ROOT fit: f1 = pol1 + gaus
   else {
   	   
   	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], false)", energy);
   	   TF1 *f1 = new TF1("f1",function, energy-20, energy+20);
   	   
   	   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   	   double q = - ( 2*(energy-20)*bin_content.at(energy-20) - (energy-20)*bin_content.at(energy+20) - (energy+20)*bin_content.at(energy-20) ) / ( (energy-20) - (energy+20) );
   	   double m = ( bin_content.at(energy-20) - bin_content.at(energy+20) ) / ( (energy-20) - (energy+20) + 0.0 ); // 0.0 is needed since we are dividing an int by an int, but we want a double
   	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);	   
	   
   	   f1->SetParameter(2, output[3]);
	   f1->FixParameter(3, energy);
	   
	   double sigma_E0 = FindSigma(energy);
	   f1->FixParameter(4, sigma_E0);   
	   
	   h_energy->Fit("f1","R");
	   
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
// Find the range in which the BKG-Pol2 parameters of the models vary
double *FindRangeOfBKGParameters_Pol2(int energy, std::vector<int> bin_content, int *output) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }

   // ROOT fit: f2 = pol2
   if ( output[2] < 3*sqrt(output[1]) ) { 
	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i)", energy, energy, energy);
   	   TF1 *f2 = new TF1("f2", function, energy-20, energy+20);
   	   
   	   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   	   double a_x = energy - 20;
   	   double a_y = bin_content.at(energy-20);
   	   double b_x = energy;
   	   double b_y = bin_content.at(energy);
   	   double c_x = energy + 20;
   	   double c_y = bin_content.at(energy+20);
   	   
   	   double k = pow ( b_x/c_x, 2);
   	   double q = pow ( a_x/c_x, 2);
   	   double z = ( b_y - k*c_y ) / ( b_x - k*c_x );
   	   
   	   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-k)/(b_x-k*c_x) - q*(1-c_x*(1-k)/(b_x-k*c_x)) );
   	   double p_1 = ( b_y - p_0*(1-k) - k*c_y ) / ( b_x - k*c_x );
   	   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);
	   
	   h_energy->Fit("f2","R");
	   
	   double *output_fit_pol2 = new double[6];
	   output_fit_pol2[0] = f2->GetParameter(0); // constant
	   output_fit_pol2[1] = f2->GetParError(0);
	   output_fit_pol2[2] = f2->GetParameter(1); // slope
	   output_fit_pol2[3] = f2->GetParError(1);
	   output_fit_pol2[4] = f2->GetParameter(2); // quadratic term
	   output_fit_pol2[5] = f2->GetParError(3);
	   
	   return output_fit_pol2; 
   }
   
   // ROOT fit: f2 = pol2 + gaus
   else {
   	   
   	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], false)", energy, energy, energy);
   	   TF1 *f2 = new TF1("f2",function, energy-20, energy+20);
   	   
   	   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   	   double a_x = energy - 20;
   	   double a_y = bin_content.at(energy-20);
   	   double b_x = energy;
   	   double b_y = bin_content.at(energy);
   	   double c_x = energy + 20;
   	   double c_y = bin_content.at(energy+20);
   	   
   	   double k = pow ( b_x/c_x, 2);
   	   double q = pow ( a_x/c_x, 2);
   	   double z = ( b_y - k*c_y ) / ( b_x - k*c_x );
   	   
   	   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-k)/(b_x-k*c_x) - q*(1-c_x*(1-k)/(b_x-k*c_x)) );
   	   double p_1 = ( b_y - p_0*(1-k) - k*c_y ) / ( b_x - k*c_x );
   	   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	   
	   
   	   f2->SetParameter(3, output[3]);
	   f2->FixParameter(4, energy);
	   
	   double sigma_E0 = FindSigma(energy);
	   f2->FixParameter(5, sigma_E0);   
	   
	   h_energy->Fit("f2","R");
	   
	   double *output_fit_pol2 = new double[12];
	   output_fit_pol2[0] = f2->GetParameter(0); // constant
	   output_fit_pol2[1] = f2->GetParError(0);
	   output_fit_pol2[2] = f2->GetParameter(1); // slope
	   output_fit_pol2[3] = f2->GetParError(1);
	   output_fit_pol2[4] = f2->GetParameter(2); // quadratic term
	   output_fit_pol2[5] = f2->GetParError(2);
	   output_fit_pol2[6] = f2->GetParameter(3); // height
	   output_fit_pol2[7] = f2->GetParError(3);
	   output_fit_pol2[8] = f2->GetParameter(4); // E0
	   output_fit_pol2[9] = f2->GetParError(4);
	   output_fit_pol2[10] = f2->GetParameter(5); // sigma
	   output_fit_pol2[11] = f2->GetParError(5);
	   
	   return output_fit_pol2;    
   }

}




// See if the ranges obtained by ROOT for the BKG parameters are good or not (Pol0 model) --> cercare su BAT una funzione analoga
//-----------------------------------------------------------------------------------------------------------------------
double PosteriorInspection_Pol0(int energy, std::vector<int> bin_content, int *output, BCH1D marginalized_histo) {

    double *output_pol0 = FindRangeOfBKGParameters_Pol0( energy, bin_content, output);
    
    TH1D *h0 = (TH1D*)marginalized_histo.GetHistogram();
    
    int Nbins = h0->GetNbinsX();
    double int_tot = h0->Integral(0, Nbins);
    
    double int_range = h0->Integral(output_pol0[0]-10*output_pol0[1], output_pol0[0]+10*output_pol0[1]);
    
    double area_perc = ( int_range / int_tot ) * 100;
    std::cout << "\n\t int_tot = " << int_tot << "\tint_range = " << int_range << std::endl;
    
    // Command to visualize the histogram of the par0 of pol0 model
    //TFile *f = new TFile("h0.root","RECREATE");
    //h0->Write();
    //f->Write();
 
    return area_perc;
}




//-----------------------------------------------------------------------------------------------------------------------
// Find the new edges x1_new, x2_new in case a gamma peak is present in proximity of the fit window  (E' ANCORA DA IMPLEMENTARE)
/*int FindNewEdges(int i_min, int i_max, int *x1_new, int *x2_new) {

 ... dopo aver controllato che gli if funzionino correttamente,
 inserire qui quanto fatto in HistoFitter.C ...
 
}*/
