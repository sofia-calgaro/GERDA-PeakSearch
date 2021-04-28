// **********************************************************************************************************************
// This file contains different functions that are called in the source files in order to calculate different quantities
// and to perform a prefit for the BKG polynomial before the BAT analysis.
// **********************************************************************************************************************
#include "Operations.h"



//=======================================================================================================================
// Returns 'true' only if b > a
bool FindMax(int a, int b) {
   return (a < b);
}



//=======================================================================================================================
// Calculates the energetic resolution for a given energy value 
double FindSigma(int energy) {

   const double a = 0.280;   // a=0.280(2) keV^2 (electronic noise)
   const double b = 5.83e-4; // b=5.83e-004(2) keV (fluctuation of the # of charge carriers)

   double sigma =  sqrt( a + b*energy );

   return sigma;
}



//=======================================================================================================================
// Calculates the FWHM for a given energy value
double FindFWHM(int energy) {

   const double a = 0.280;   
   const double b = 5.83e-4; 

   double FWHM = sqrt( 8*log(2) ) * sqrt( a + b*energy );

   return FWHM;
}



//=======================================================================================================================
// Calculates the maximum of the signal height parameter
int *FindMaximumSignalHeight(int energy, std::vector<int> bin_content) {

   int x1 = energy - 12;
   int x2 = energy + 12;
   
   double FWHM = FindFWHM(energy);
   
   // Let's define the range [x1_signal;x2_signal] in which the signal contribution (S) is calculated
   int x1_signal = std::round( energy - 1.5*FWHM );
   int x2_signal = std::round( energy + 1.5*FWHM ); 
            
   // Calculate the average BKG outside [x1_signal;x2_signal]   
   int B_i = 0;
                    
   for ( int i=x1; i<x1_signal; i++ ) { B_i += bin_content.at(i); }
           
   for ( int i=x2_signal; i<x2; i++ ) { B_i += bin_content.at(i); }
                    
   int N_bkg = ( x1_signal - x1 ) + ( x2 - x2_signal );
   double B_avg = B_i / (N_bkg+0.0);
                    
   // Calculate the overall bin content in [x1_signal;x2_signal]        
   int S_i = 0;
   for ( int i=x1_signal; i<x2_signal; i++ ) { S_i += bin_content.at(i); }
                    
   int N_sig = x2_signal-x1_signal;
            
   // Calculate the amount of BKG in [x1_signal;x2_signal]        
   double B_S = N_sig*B_avg;
            
   // Calculate the signal in [x1_signal;x2_signal]      
   int S = std::round ( S_i-B_S );                
                    
   // Find the maximum value that the signal height can assume        
   int max1 = std::round( S + 5*sqrt(B_S) + 5*sqrt(S) );
   int max2 = std::round( 8*sqrt(B_S) );
   int max3 = 10;
   int max = std::max({max1, max2, max3},FindMax);
   
   //std::cout << "\n\tx1_signal = " << x1_signal << std::endl;
   //std::cout << "\tx2_signal = " << x2_signal << std::endl;  
   //std::cout << "\n\tB_i = " << B_i << "\tN_bkg = " << N_bkg << "\tB_avg = " << B_avg << std::endl;
   //std::cout << "\n\tS_i = " << S_i << "\tN_sig = " << N_sig << "\tB_S = " << B_S << "\tS = " << S << std::endl;
   //std::cout << "\n\tmax1 = " << max1 << "\tmax2 = " << max2 << "\tmax3 = " << max3 << "\t MAX = " << max << "\n" << std::endl;
   
   int *output = new int[4];
   output[0] = std::round(B_avg);
   output[1] = std::round(B_S);
   output[2] = S;
   output[3] = max;
      
   return output;
}



//=======================================================================================================================
// Find the range in which the BKG-Pol0 parameters of the models vary
double *FindRange_Pol0(int energy, std::vector<int> bin_content, int *max_height) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   int p0 = 0;
   for (int i=energy-20; i<energy+20; i++) { p0 += bin_content.at(i); }
   p0 = std::round(p0/40);

   // ROOT fit: f0 = pol0 
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0]", energy-20, energy+20);
	   
	   f0->SetParameter(0, p0);
	   
	   h_energy->Fit("f0","R");
	   
	   double *output_pol0 = new double[2];
	   output_pol0[0] = f0->GetParameter(0); // constant
	   output_pol0[1] = f0->GetParError(0);
	   
	   delete h_energy;
	   delete f0;
	   return output_pol0; 
   }
   
   // ROOT fit: f0 = pol0 + gaus
   else {
   	   
   	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true)", energy-20, energy+20);
   	   
	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_height[3]);
	   f0->FixParameter(2, energy);
	   f0->FixParameter(3, FindSigma(energy));   
	   
   	   h_energy->Fit("f0","R");
   
   	   double *output_pol0 = new double[2];
	   output_pol0[0] = f0->GetParameter(0); // constant
	   output_pol0[1] = f0->GetParError(0);
	   
	   delete h_energy;
	   delete f0;
	   return output_pol0;
   }
}



//=======================================================================================================================
// Find the range in which the BKG-Pol1 parameters of the models vary
double *FindRange_Pol1(int energy, std::vector<int> bin_content, int *max_height) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   double q = - ( 2*(energy-20)*bin_content.at(energy-20) - (energy-20)*bin_content.at(energy+20-1) - (energy+20)*bin_content.at(energy-20) ) / ( (energy-20) - (energy+20) );
   double m = ( bin_content.at(energy-20) - bin_content.at(energy+20-1) ) / ( (energy-20) - (energy+20) + 0.0 );

   // ROOT fit: f1 = pol1
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	 
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i)", energy);
   	   TF1 *f1 = new TF1("f1", function, energy-20, energy+20);
   	   
   	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   h_energy->Fit("f1","R");
	   
	   double *output_pol1 = new double[4];
	   output_pol1[0] = f1->GetParameter(0); // constant
	   output_pol1[1] = f1->GetParError(0);
	   output_pol1[2] = f1->GetParameter(1); // slope
	   output_pol1[3] = f1->GetParError(1);
	   
	   delete h_energy;
	   delete f1;
	   return output_pol1; 
   }
   
   // ROOT fit: f1 = pol1 + gaus
   else {
   	   
   	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true)", energy);
   	   TF1 *f1 = new TF1("f1",function, energy-20, energy+20);
   	   
   	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);	   
	   
   	   f1->SetParLimits(2, 0, max_height[3]);
	   f1->FixParameter(3, energy);
	   f1->FixParameter(4, FindSigma(energy));   
	   
	   h_energy->Fit("f1","R");
	   
	   double *output_pol1 = new double[4];
	   output_pol1[0] = f1->GetParameter(0); // constant
	   output_pol1[1] = f1->GetParError(0);
	   output_pol1[2] = f1->GetParameter(1); // slope
	   output_pol1[3] = f1->GetParError(1);
	   
	   delete h_energy;
	   delete f1;
	   return output_pol1;    
   }
}




//=======================================================================================================================
// Find the range in which the BKG-Pol2 parameters of the models vary
double *FindRange_Pol2(int energy, std::vector<int> bin_content, int *max_height) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   double a_x = energy - 20;
   double a_y = bin_content.at(energy-20);
   double b_x = energy;
   double b_y = bin_content.at(energy);
   double c_x = energy + 20;
   double c_y = bin_content.at(energy+20-1);
   	   
   double k = pow ( b_x/c_x, 2);
   double q = pow ( a_x/c_x, 2);
   double z = ( b_y - k*c_y ) / ( b_x - k*c_x );
   	   
   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-k)/(b_x-k*c_x) - q*(1-c_x*(1-k)/(b_x-k*c_x)) );
   double p_1 = ( b_y - p_0*(1-k) - k*c_y ) / ( b_x - k*c_x );
   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);

   // ROOT fit: f2 = pol2
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i)", energy, energy, energy);
   	   TF1 *f2 = new TF1("f2", function, energy-20, energy+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);
	   
	   h_energy->Fit("f2","R");
	   
	   double *output_pol2 = new double[6];
	   output_pol2[0] = f2->GetParameter(0); // constant
	   output_pol2[1] = f2->GetParError(0);
	   output_pol2[2] = f2->GetParameter(1); // slope
	   output_pol2[3] = f2->GetParError(1);
	   output_pol2[4] = f2->GetParameter(2); // quadratic term
	   output_pol2[5] = f2->GetParError(2);
	   
	   delete h_energy;
	   delete f2;
	   return output_pol2; 
   }
   
   // ROOT fit: f2 = pol2 + gaus
   else {
   	   
   	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true)", energy, energy, energy);
   	   TF1 *f2 = new TF1("f2",function, energy-20, energy+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	   
	   
   	   f2->SetParameter(3, max_height[3]);
	   f2->FixParameter(4, energy);
	   f2->FixParameter(5, FindSigma(energy));   
	   
	   h_energy->Fit("f2","R");
	   
	   double *output_pol2 = new double[6];
	   output_pol2[0] = f2->GetParameter(0); // constant
	   output_pol2[1] = f2->GetParError(0);
	   output_pol2[2] = f2->GetParameter(1); // slope
	   output_pol2[3] = f2->GetParError(1);
	   output_pol2[4] = f2->GetParameter(2); // quadratic term
	   output_pol2[5] = f2->GetParError(2);
	   
	   delete h_energy;
	   delete f2;
	   return output_pol2;    
   }
}



//=======================================================================================================================
// Find the range in which the BKG-Pol0 parameters of the models vary (1 gamma peak)
double *FindRange_Gamma_Pol0(int energy, std::vector<int> bin_content, int *max_height, double EG, int *max_gammaYield) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   int p0 = 0;
   for (int i=energy-20; i<energy+20; i++) { p0 += bin_content.at(i); }
   p0 = std::round(p0/40);

   // ROOT fit: f0 = pol0 + gaus(EG)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true)", energy-20, energy+20);
	   
	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield[3]);
	   f0->FixParameter(2, EG);
	   f0->FixParameter(3, FindSigma(EG));
	   
	   h_energy->Fit("f0","R");
	   
	   double *output_pol0 = new double[4];
	   output_pol0[0] = f0->GetParameter(0); // constant
	   output_pol0[1] = f0->GetParError(0);
	   output_pol0[2] = f0->GetParameter(1); // gamma yield
	   output_pol0[3] = f0->GetParError(1);
	   
	   delete h_energy;
	   delete f0;
	   return output_pol0; 
   }
   
   // ROOT fit: f0 = pol0 + gaus(EG) + gaus
   else {
   	   
   	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true) + [4]*TMath::Gaus(x, [5], [6], true)", energy-20, energy+20);	

	   f0->SetParameter(0, p0);
	   
	   int *max_gammaYield = FindMaximumSignalHeight( EG, bin_content);
	   f0->SetParameter(1, max_gammaYield[3]);
	   f0->FixParameter(2, EG);
	   f0->FixParameter(3, FindSigma(EG));
	   
	   f0->SetParameter(4, max_height[3]);
	   f0->FixParameter(5, energy);
	   f0->FixParameter(6, FindSigma(energy));	   
	   
   	   h_energy->Fit("f0","R");
   
   	   double *output_pol0 = new double[4];
	   output_pol0[0] = f0->GetParameter(0); // constant
	   output_pol0[1] = f0->GetParError(0);
	   output_pol0[2] = f0->GetParameter(1); // gamma yield
	   output_pol0[3] = f0->GetParError(1);
	   
	   delete h_energy;
	   delete f0;
	   return output_pol0;
   }
}
  
  
  
//=======================================================================================================================    
// Find the range in which the BKG-Pol1 parameters of the models vary (1 gamma peak)
double *FindRange_Gamma_Pol1(int energy, std::vector<int> bin_content, int *max_height, double EG, int *max_gammaYield) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   double q = - ( 2*(energy-20)*bin_content.at(energy-20) - (energy-20)*bin_content.at(energy+20-1) - (energy+20)*bin_content.at(energy-20) ) / ( (energy-20) - (energy+20) );
   double m = ( bin_content.at(energy-20) - bin_content.at(energy+20-1) ) / ( (energy-20) - (energy+20) + 0.0 );

   // ROOT fit: f1 = pol1 + gaus(EG)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true)", energy);
   	   TF1 *f1 = new TF1("f1", function, energy-20, energy+20);
	   
	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield[3]);
	   f1->FixParameter(3, EG);
	   f1->FixParameter(4, FindSigma(EG));
	   
	   h_energy->Fit("f1","R");
	   
	   double *output_pol1 = new double[6];
	   output_pol1[0] = f1->GetParameter(0); // constant
	   output_pol1[1] = f1->GetParError(0);
	   output_pol1[2] = f1->GetParameter(1); // gamma yield
	   output_pol1[3] = f1->GetParError(1);
	   output_pol1[4] = f1->GetParameter(2); // gamma yield
	   output_pol1[5] = f1->GetParError(2);
	   
	   delete h_energy;
	   delete f1;
	   return output_pol1; 
   }
   
   // ROOT fit: f1 = pol1 + gaus(EG) + gaus
   else {
   	   
   	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true) + [5]*TMath::Gaus(x, [6], [7], true)", energy);
   	   TF1 *f1 = new TF1("f1", function, energy-20, energy+20);

	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   int *max_gammaYield = FindMaximumSignalHeight( EG, bin_content);
	   f1->SetParameter(2, max_gammaYield[3]);
	   f1->FixParameter(3, EG);
	   f1->FixParameter(4, FindSigma(EG));
	   
	   f1->SetParameter(5, max_height[3]);
	   f1->FixParameter(6, energy);
	   f1->FixParameter(7, FindSigma(energy));	   
	   
   	   h_energy->Fit("f1","R");
   
   	   double *output_pol1 = new double[4];
	   output_pol1[0] = f1->GetParameter(0); // constant
	   output_pol1[1] = f1->GetParError(0);
	   output_pol1[2] = f1->GetParameter(1); // gamma yield
	   output_pol1[3] = f1->GetParError(1);
	   
	   delete h_energy;
	   delete f1;
	   return output_pol1;
   }
}



//======================================================================================================================= 
// Find the range in which the BKG-Pol2 parameters of the models vary (1 gamma peak)
double *FindRange_Gamma_Pol2(int energy, std::vector<int> bin_content, int *max_height, double EG, int *max_gammaYield) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   double a_x = energy - 20;
   double a_y = bin_content.at(energy-20);
   double b_x = energy;
   double b_y = bin_content.at(energy);
   double c_x = energy + 20;
   double c_y = bin_content.at(energy+20-1);
   	   
   double k = pow ( b_x/c_x, 2);
   double q = pow ( a_x/c_x, 2);
   double z = ( b_y - k*c_y ) / ( b_x - k*c_x );
   	   
   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-k)/(b_x-k*c_x) - q*(1-c_x*(1-k)/(b_x-k*c_x)) );
   double p_1 = ( b_y - p_0*(1-k) - k*c_y ) / ( b_x - k*c_x );
   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);

   // ROOT fit: f2 = pol2 + gaus(EG)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true)", energy, energy, energy);
   	   TF1 *f2 = new TF1("f2", function, energy-20, energy+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);
	   
	   f2->SetParameter(3, max_gammaYield[3]);
	   f2->FixParameter(4, EG);
	   f2->FixParameter(5, FindSigma(EG));
	   
	   h_energy->Fit("f2","R");
	   
	   double *output_pol2 = new double[8];
	   output_pol2[0] = f2->GetParameter(0); // constant
	   output_pol2[1] = f2->GetParError(0);
	   output_pol2[2] = f2->GetParameter(1); // slope
	   output_pol2[3] = f2->GetParError(1);
	   output_pol2[4] = f2->GetParameter(2); // quadratic term
	   output_pol2[5] = f2->GetParError(2);
	   output_pol2[6] = f2->GetParameter(3); // gamma yield
	   output_pol2[7] = f2->GetParError(3);
	   
	   delete h_energy;
	   delete f2;
	   return output_pol2; 
   }
   
   // ROOT fit: f2 = pol2 + gaus(EG) +  gaus
   else {
   	   
   	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true) + [6]*TMath::Gaus(x, [7], [8], true)", energy, energy, energy);
   	   TF1 *f2 = new TF1("f2",function, energy-20, energy+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	 
	   
	   f2->SetParameter(3, max_gammaYield[3]);
	   f2->FixParameter(4, EG);
	   f2->FixParameter(5, FindSigma(EG));  
	   
   	   f2->SetParameter(6, max_height[3]);
	   f2->FixParameter(7, energy);
	   f2->FixParameter(8, FindSigma(energy));   
	   
	   h_energy->Fit("f2","R");
	   
	   double *output_pol2 = new double[8];
	   output_pol2[0] = f2->GetParameter(0); // constant
	   output_pol2[1] = f2->GetParError(0);
	   output_pol2[2] = f2->GetParameter(1); // slope
	   output_pol2[3] = f2->GetParError(1);
	   output_pol2[4] = f2->GetParameter(2); // quadratic term
	   output_pol2[5] = f2->GetParError(2);
	   output_pol2[6] = f2->GetParameter(3); // gamma yield
	   output_pol2[7] = f2->GetParError(3);
	   
	   delete h_energy;
	   delete f2;
	   return output_pol2;    
   }
}
