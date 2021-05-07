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
int *FindMaximumSignalHeight(int E0, double E1, double E2, std::vector<int> bin_content, int xL, int xR, int outputK) {

   double FWHM_0 = FindFWHM(E0);
   double FWHM_1 = FindFWHM(E1);
   double FWHM_2 = FindFWHM(E2);
   int xL_S = std::round( E0 - 1.5*FWHM_0 ); // [xL_S;xR_S] = signal range
   int xR_S = std::round( E0 + 1.5*FWHM_0 ); 
   int B_i = 0;  
   int N_bkg = 0;
   double B_avg = 0.0;
   int S_i = 0;
   int N_sig = 0;
   double B_S = 0.0;
   int S = 0;

   if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
	   
	   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }     
	   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); } // Bin content outside [xL_S;xR_S]     
		            
	   N_bkg = ( xL_S - xL ) + ( xR - xR_S ); // # of BKG bins
		            
	   for ( int i=xL_S; i<xR_S; i++ ) { S_i += bin_content.at(i); } // Bin content in [xL_S;xR_S]         
   }
   
   else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) { 
   
    	   int xL_1 = std::round( E1 - 1.5*FWHM_1 ); 
   	   int xR_1 = std::round( E1 + 1.5*FWHM_1 ); 
   	   
   	   // Gamma peak is on the right of the signal peak
   	   if ( E1 > E0) {
   	   	   if ( (E1 - E0) > 1.5*(FWHM_1 + FWHM_0) ) {
   	   	   	   // Bin content outside [xL_S;xR_S] U [xL_1;xR_1] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_S; i<xL_1; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_1; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_S - xL ) + ( xL_1 - xR_S ) + ( xR - xR_1 );  
   	   	   }
   	   	   else {
   	   	   	   // Bin content outside [xL_S;xR_1] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }    
			   for ( int i=xR_1; i<xR; i++ ) { B_i += bin_content.at(i); }  
			   N_bkg = ( xL_S - xL ) + ( xR - xR_1 );     
   	   	   }
   	   }
   	   // Gamma peak is on the left of the signal peak
   	   else {
   	   	   if ( (E0 - E1) > 1.5*(FWHM_1 + FWHM_0) ) {
   	   	   	   // Bin content outside [xL_1;xR_1] U [xL_S;xR_S]
		   	   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_1; i<xL_S; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); } 
			   N_bkg = ( xL_1 - xL ) + ( xL_S - xR_1 ) + ( xR - xR_S );  
   	   	   }
   	   	   else {
   	   	   	   // Bin content outside [xL_1;xR_S]
		   	   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); } 
			   N_bkg = ( xL_1 - xL ) + ( xR - xR_S ); 
   	   	   }
   	   }
	              
	   for ( int i=xL_S; i<xR_S; i++ ) { S_i += bin_content.at(i); }      
   }
   
   else {
   
   	   int xL_1 = std::round( E1 - 1.5*FWHM_1 ); 
      	   int xR_2 = std::round( E2 + 1.5*FWHM_2 ); 
      	   
      	   // Signal peak is on the right of the gamma peaks
      	   if ( E0 > E2 ) {
      	   	if ( (E0 - E2) > 1.5*(FWHM_0 + FWHM_2) ) {
      	   		   // Bin content outside [xL_1;xR_2] U [xL_S;xR_S] 
			   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_2; i<xL_S; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_1 - xL ) + ( xL_S - xR_2 ) + ( xR - xR_S );  
      	   	}
      	   	else {
      	   		   // Bin content outside [xL_1;xR_S] 
			   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_1 - xL ) + ( xR - xR_S );  
      	   	}
      	   }
      	   // Signal peak is on the left of the gamma peaks
      	   else {
      	   	if ( (E1 - E0) > 1.5*(FWHM_0 + FWHM_1) ) {
      	   		   // Bin content outside [xL_S;xR_S] U [xL_1;xR_2] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_S; i<xL_1; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_2; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_S - xL ) + ( xL_1 - xR_S ) + ( xR - xR_2 );  
      	   	}
      	   	else {
      	   		   // Bin content outside [xL_S;xR_2] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }   
			   for ( int i=xR_2; i<xR; i++ ) { B_i += bin_content.at(i); }   
			   N_bkg = ( xL_S - xL ) + ( xR - xR_2 );  
      	   	}	
      	   }
   }
   
   B_avg = B_i / (N_bkg+0.0);
   N_sig = xR_S-xL_S; // # of signal bins
   B_S = N_sig*B_avg; // BKG in [xL_S;xR_S]     	         
   S = std::round ( S_i-B_S ); // Signal in [xL_S;xR_S] 
                      
   // Maximum value that the signal height can assume        
   int max1 = std::round( S + 5*sqrt(B_S) + 5*sqrt(S) );
   int max2 = std::round( 8*sqrt(B_S) );
   int max3 = 10;
   int max = std::max({max1, max2, max3},FindMax);
   
   std::cout << "\n\t| MAXIMUM SIGNAL HEIGHT:" << std::endl;
   std::cout << "\t| xL_S = " << xL_S << std::endl;
   std::cout << "\t| xR_S = " << xR_S << std::endl;  
   std::cout << "\t|\n\t| B_i = " << B_i << "\tN_bkg = " << N_bkg << "\tB_avg = " << B_avg << std::endl;
   std::cout << "\t| S_i = " << S_i << "\tN_sig = " << N_sig << "\tB_S = " << B_S << "\tS = " << S << std::endl;
   std::cout << "\t| max1 = " << max1 << "\tmax2 = " << max2 << "\tmax3 = " << max3 << "\n\t| => MAX = " << max << "\n" << std::endl;
   
   int *results = new int[6];
   results[0] = std::round(B_avg);
   results[1] = std::round(B_S);
   results[2] = S;
   results[3] = max;
   results[4] = N_bkg;
   results[5] = B_i;
      
   return results;
}



//=======================================================================================================================
// Calculates the maximum of the 1st gamma height parameter
int *FindMaximumGammaHeight1(int E0, double E1, double E2, std::vector<int> bin_content, int xL, int xR, int outputK) {

   double FWHM_0 = FindFWHM(E0);
   double FWHM_1 = FindFWHM(E1);
   double FWHM_2 = FindFWHM(E2);
   int xL_S = std::round( E0 - 1.5*FWHM_0 ); 
   int xR_S = std::round( E0 + 1.5*FWHM_0 ); 
   int xL_1 = std::round( E1 - 1.5*FWHM_1 ); 
   int xR_1 = std::round( E1 + 1.5*FWHM_1 ); 
   int B_i = 0;  
   int N_bkg = 0;
   double B_avg = 0.0;
   int G_i = 0;
   int N_sig = 0;
   double B_G = 0.0;
   int G = 0;


   if ( (outputK>=2 && outputK<=6) && outputK!=4 ) { 
   
   	   if ( E1 > E0 ) {
   	   	   if ( fabs(E0-E1) > 1.5*(FWHM_1 + FWHM_0) ) {
   	   	   	   // Bin content outside [x1_S;x2_S] U [x1_G;x2_G] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_S; i<xL_1; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_1; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_S - xL ) + ( xL_1 - xR_S ) + ( xR - xR_1 );  
   	   	   }
   	   	   else {
   	   	   	   // Bin content outside [x1_S;x2_G] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }    
			   for ( int i=xR_1; i<xR; i++ ) { B_i += bin_content.at(i); }  
			   N_bkg = ( xL_S - xL ) + ( xR - xR_1 );  
   	   	   }
   	   }
   	   else {
   	   	   if ( fabs(E0-E1) > 1.5*(FWHM_1 + FWHM_0) ) {
   	   	   	   // Bin content outside [x1_G;x2_G] U [x1_S;x2_S]
		   	   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_1; i<xL_S; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); } 
			   N_bkg = ( xL_1 - xL ) + ( xL_S - xR_1 ) + ( xR - xR_S );  
   	   	   }
   	   	   else {
   	   	   	   // Bin content outside [x1_G;x2_S]
		   	   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); } 
			   N_bkg = ( xL_1 - xL ) + ( xR - xR_S ); 
   	   	   }
   	   } 
   }
   if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
   
   	   int xR_2 = std::round( E2 + 1.5*FWHM_2 ); 
      	   
      	   // Signal peak is on the right of the gamma peaks
      	   if ( E0 > E2 ) {
      	   	if ( (E0 - E2) > 1.5*(FWHM_0 + FWHM_2) ) {
      	   		   // Bin content outside [xL_1;xR_2] U [xL_S;xR_S] 
			   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_2; i<xL_S; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_1 - xL ) + ( xL_S - xR_2 ) + ( xR - xR_S );  
      	   	}
      	   	else {
      	   		   // Bin content outside [xL_1;xR_S] 
			   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_1 - xL ) + ( xR - xR_S );  
      	   	}
      	   }
      	   // Signal peak is on the left of the gamma peaks
      	   else {
      	   	if ( (E1 - E0) > 1.5*(FWHM_0 + FWHM_1) ) {
      	   		   // Bin content outside [xL_S;xR_S] U [xL_1;xR_2] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_S; i<xL_1; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_2; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_S - xL ) + ( xL_1 - xR_S ) + ( xR - xR_2 );  
      	   	}
      	   	else {
      	   		   // Bin content outside [xL_S;xR_2] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }   
			   for ( int i=xR_2; i<xR; i++ ) { B_i += bin_content.at(i); }   
			   N_bkg = ( xL_S - xL ) + ( xR - xR_2 );  
      	   	}	
      	   }
   }
   
   B_avg = B_i / (N_bkg+0.0);
	            
   for ( int i=xL_1; i<xR_1; i++ ) { G_i += bin_content.at(i); }      
		            
   N_sig = xR_1-xL_1;         
   B_G = N_sig*B_avg;
   G = std::round ( G_i-B_G ); 
   
   // Maximum value that the signal height can assume        
   int max1 = std::round( G + 5*sqrt(B_G) + 5*sqrt(G) );
   int max2 = std::round( 8*sqrt(B_G) );
   int max3 = 10;
   int max = std::max({max1, max2, max3},FindMax);
   
   std::cout << "\n\t| MAXIMUM GAMMA PEAK HEIGHT:" << std::endl;
   std::cout << "\t| xL_1 = " << xL_1 << std::endl;
   std::cout << "\t| xR_1 = " << xR_1 << std::endl;  
   std::cout << "\t|\n\t| B_i = " << B_i << "\tN_bkg = " << N_bkg << "\tB_avg = " << B_avg << std::endl;
   std::cout << "\t| G_i = " << G_i << "\tN_sig = " << N_sig << "\tB_G = " << B_G << "\tG = " << G << std::endl;
   std::cout << "\t| max1 = " << max1 << "\tmax2 = " << max2 << "\tmax3 = " << max3 << "\n\t| => MAX = " << max << "\n" << std::endl;
   
   int *results = new int[6];
   results[0] = std::round(B_avg);
   results[1] = std::round(B_G);
   results[2] = G;
   results[3] = max;
   results[4] = N_bkg;
   results[5] = B_i;
      
   return results;
}



//=======================================================================================================================
// Calculates the maximum of the 2nd gamma height parameter
int *FindMaximumGammaHeight2(int E0, double E1, double E2, std::vector<int> bin_content, int xL, int xR, int outputK) {

   double FWHM_0 = FindFWHM(E0);
   double FWHM_1 = FindFWHM(E1);
   double FWHM_2 = FindFWHM(E2);
   int xL_S = std::round( E0 - 1.5*FWHM_0 ); 
   int xR_S = std::round( E0 + 1.5*FWHM_0 ); 
   int xL_1 = std::round( E1 - 1.5*FWHM_1 ); 
   int xL_2 = std::round( E2 - 1.5*FWHM_2 ); 
   int xR_2 = std::round( E2 + 1.5*FWHM_2 ); 
   int B_i = 0;  
   int N_bkg = 0;
   double B_avg = 0.0;
   int G_i = 0;
   int N_sig = 0;
   double B_G = 0.0;
   int G = 0;


   if ( (outputK>7 && outputK<20 ) && outputK!=13 && outputK!=14 && outputK!=15 && outputK!=18 ) {
   
   	   // Signal peak is on the right of the gamma peaks
      	   if ( E0 > E2 ) {
      	   	if ( (E0 - E2) > 1.5*(FWHM_0 + FWHM_2) ) {
      	   		   // Bin content outside [xL_1;xR_2] U [xL_S;xR_S] 
			   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_2; i<xL_S; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_1 - xL ) + ( xL_S - xR_2 ) + ( xR - xR_S );  
      	   	}
      	   	else {
      	   		   // Bin content outside [xL_1;xR_S] 
			   for ( int i=xL; i<xL_1; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_S; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_1 - xL ) + ( xR - xR_S );  
      	   	}
      	   }
      	   // Signal peak is on the left of the gamma peaks
      	   else {
      	   	if ( (E1 - E0) > 1.5*(FWHM_0 + FWHM_1)  ) {
      	   		   // Bin content outside [xL_S;xR_S] U [xL_1;xR_2] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }     
			   for ( int i=xR_S; i<xL_1; i++ ) { B_i += bin_content.at(i); }  
			   for ( int i=xR_2; i<xR; i++ ) { B_i += bin_content.at(i); }     
			   N_bkg = ( xL_S - xL ) + ( xL_1 - xR_S ) + ( xR - xR_2 );  
      	   	}
      	   	else {
      	   		   // Bin content outside [xL_S;xR_2] 
			   for ( int i=xL; i<xL_S; i++ ) { B_i += bin_content.at(i); }   
			   for ( int i=xR_2; i<xR; i++ ) { B_i += bin_content.at(i); }   
			   N_bkg = ( xL_S - xL ) + ( xR - xR_2 );  
      	   	}	
      	   }
   }
   
   B_avg = B_i / (N_bkg+0.0);
	            
   for ( int i=xL_2; i<xR_2; i++ ) { G_i += bin_content.at(i); }      
		            
   N_sig = xR_2-xL_2;         
   B_G = N_sig*B_avg;
   G = std::round ( G_i-B_G ); 
   
   // Maximum value that the signal height can assume        
   int max1 = std::round( G + 5*sqrt(B_G) + 5*sqrt(G) );
   int max2 = std::round( 8*sqrt(B_G) );
   int max3 = 10;
   int max = std::max({max1, max2, max3},FindMax);
   
   std::cout << "\n\t| MAXIMUM 2nd GAMMA PEAK HEIGHT:" << std::endl;
   std::cout << "\t| xL_2 = " << xL_2 << std::endl;
   std::cout << "\t| xR_2 = " << xR_2 << std::endl;  
   std::cout << "\t|\n\t| B_i = " << B_i << "\tN_bkg = " << N_bkg << "\tB_avg = " << B_avg << std::endl;
   std::cout << "\t| G_i = " << G_i << "\tN_sig = " << N_sig << "\tB_G = " << B_G << "\tG = " << G << std::endl;
   std::cout << "\t| max1 = " << max1 << "\tmax2 = " << max2 << "\tmax3 = " << max3 << "\n\t| => MAX = " << max << "\n" << std::endl;
   
   int *results = new int[6];
   results[0] = std::round(B_avg);
   results[1] = std::round(B_G);
   results[2] = G;
   results[3] = max;
   results[4] = N_bkg;
   results[5] = B_i;
      
   return results;
}



//=======================================================================================================================
// Find the range in which the BKG-Pol0 parameters of the models vary
double *FindRange_Pol0(int E0, std::vector<int> bin_content, int *max_height, int xL, int xR) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
   
   int B_i = 0;
   int N_bkg = 0;
   int check1 = 0;
   int check2 = 0;
   
   // LEFT part
   for (int i=0; i<numGamma; i++) {
   	if ( E_gamma[i]>=x_min && E_gamma[i]<=xL ) {
   		// 2 gamma peaks in [x_min;xL]
   		if ( E_gamma[i+1]>=x_min && E_gamma[i+1]<=xL ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > x_min ) {
	   			for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - x_min );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i]) + FindFWHM(E_gamma[i+1])) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1])) < xL ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])) );
	   		}
	   		break;
   		}
   		// 1 gamma peaks in [x_min;xL]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > x_min ) {
   				for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - x_min );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i])) < xL ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
   			}
   			break;
   		} 		
   	}
   	// no gamma peaks in [x_min;xL]
   	else { check1 += 1; }
   } 
   
   // RIGHT part	
   for (int i=0; i<numGamma; i++) {	
   	if ( E_gamma[i]>=xR && E_gamma[i]<=x_max ) {
   		// 2 gamma peaks in [xR;x_max]
   		if ( E_gamma[i+1]>=xR && E_gamma[i+1]<=x_max ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > xR ) {
	   			for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - xR );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i]) + FindFWHM(E_gamma[i+1])) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1])) < x_max ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])) );
	   		}
	   		break;   		
   		}
   		// 1 gamma peaks in [xR;x_max]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > xR ) {
   				for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - xR );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i])) < x_max ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
   			}
   			break;
   		} 
   		
   	}
   	// no gamma peaks in [xR;x_max]
   	else { check2 += 1; }
   }
   
   // no gamma peaks in [x_min;xL]
   if ( check1 == numGamma ) {
   	for (int j=x_min; j<xL; j++) { B_i += bin_content.at(j); }
	N_bkg += ( xL - x_min);
   }
   // no gamma peaks in [xR;x_max]
   if ( check2 == numGamma ) {
   	for (int j=xR; j<x_max; j++) { B_i += bin_content.at(j); }
	N_bkg += ( x_max - xR);
   }
   
   int p0 = std::round((N_bkg+max_height[5])/(B_i+max_height[4]+0.0));
   
   // ROOT fit: f0 = pol0 
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0]", E0-20, E0+20);
	   
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
   	   
   	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true)", E0-20, E0+20);
   	   
	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_height[3]);
	   f0->FixParameter(2, E0);
	   f0->FixParameter(3, FindSigma(E0));   
	   
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
double *FindRange_Pol1(int E0, std::vector<int> bin_content, int *max_height) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
  
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i])); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i])); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i])); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i])); break; }
   }
   
   double q = - ( 2*x_min*bin_content.at(x_min) - x_min*bin_content.at(x_max-1) - x_max*bin_content.at(x_min) ) / ( x_min - x_max );
   double m = ( bin_content.at(x_min) - bin_content.at(x_max-1) ) / ( x_min - x_max + 0.0 );

   // ROOT fit: f1 = pol1
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	 
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i)", E0);
   	   TF1 *f1 = new TF1("f1", function, E0-20, E0+20);
   	   
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
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true)", E0);
   	   TF1 *f1 = new TF1("f1",function, E0-20, E0+20);
   	   
   	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);	   
	   
   	   f1->SetParLimits(2, 0, max_height[3]);
	   f1->FixParameter(3, E0);
	   f1->FixParameter(4, FindSigma(E0));   
	   
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
double *FindRange_Pol2(int E0, std::vector<int> bin_content, int *max_height) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i])); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i])); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i])); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i])); break; }
   }
   
   double a_x = x_min;
   double a_y = bin_content.at(x_min);
   double b_x = E0+1.5*FindFWHM(E0);
   double b_y = bin_content.at(std::round(b_x));
   double c_x = x_max;
   double c_y = bin_content.at(x_max-1);
   	   
   double k = pow ( b_x/c_x, 2);
   double q = pow ( a_x/c_x, 2);
   double z = ( b_y - k*c_y ) / ( b_x - k*c_x );
   	   
   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-k)/(b_x-k*c_x) - q*(1-c_x*(1-k)/(b_x-k*c_x)) );
   double p_1 = ( b_y - p_0*(1-k) - k*c_y ) / ( b_x - k*c_x );
   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);

   // ROOT fit: f2 = pol2
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2", function, E0-20, E0+20);
   	   
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
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2",function, E0-20, E0+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	   
	   
   	   f2->SetParameter(3, max_height[3]);
	   f2->FixParameter(4, E0);
	   f2->FixParameter(5, FindSigma(E0));   
	   
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
double *FindRange_Gamma_Pol0(int E0, std::vector<int> bin_content, int *max_height, double E1, int *max_gammaYield, int xL, int xR) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
   
   int B_i = 0;
   int N_bkg = 0;
   int check1 = 0;
   int check2 = 0;
      
   // LEFT part
   for (int i=0; i<numGamma; i++) {
   	if ( E_gamma[i]>=x_min && E_gamma[i]<=xL ) {
   		// 2 gamma peaks in [x_min;xL]
   		if ( E_gamma[i+1]>=x_min && E_gamma[i+1]<=xL ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > x_min ) {
	   			for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - x_min );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i]) + FindFWHM(E_gamma[i+1])) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1])) < xL ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])) );
	   		}
	   		break;
   		}
   		// 1 gamma peaks in [x_min;xL]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > x_min ) {
   				for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - x_min );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i])) < xL ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
   			}
   			break;
   		} 		
   	}
   	// no gamma peaks in [x_min;xL]
   	else { check1 += 1; }
   } 
   
   // RIGHT part	
   for (int i=0; i<numGamma; i++) {	
   	if ( E_gamma[i]>=xR && E_gamma[i]<=x_max ) {
   		// 2 gamma peaks in [xR;x_max]
   		if ( E_gamma[i+1]>=xR && E_gamma[i+1]<=x_max ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > xR ) {
	   			for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - xR );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i]) + FindFWHM(E_gamma[i+1])) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1])) < x_max ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])) );
	   		}
	   		break;   		
   		}
   		// 1 gamma peaks in [xR;x_max]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > xR ) {
   				for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - xR );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i])) < x_max ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
   			}
   			break;
   		} 
   		
   	}
   	// no gamma peaks in [xR;x_max]
   	else { check2 += 1; }
   }
   
   // no gamma peaks in [x_min;xL]
   if ( check1 == numGamma ) {
   	for (int j=x_min; j<xL; j++) { B_i += bin_content.at(j); }
	N_bkg += ( xL - x_min);
   }
   // no gamma peaks in [xR;x_max]
   if ( check2 == numGamma ) {
   	for (int j=xR; j<x_max; j++) { B_i += bin_content.at(j); }
	N_bkg += ( x_max - xR);
   }
   
   int p0 = std::round((N_bkg+max_height[5])/(B_i+max_height[4]+0.0));
   
   // ROOT fit: f0 = pol0 + gaus(E1)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true)", E0-20, E0+20);
	   
	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield[3]);
	   f0->FixParameter(2, E1);
	   f0->FixParameter(3, FindSigma(E1));
	   
	   h_energy->Fit("f0","R");
	   
	   double *output_pol0 = new double[2];
	   output_pol0[0] = f0->GetParameter(0); // constant
	   output_pol0[1] = f0->GetParError(0);
	   
	   delete h_energy;
	   delete f0;
	   return output_pol0; 
   }
   
   // ROOT fit: f0 = pol0 + gaus(E1) + gaus
   else {
   	   
   	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true) + [4]*TMath::Gaus(x, [5], [6], true)", E0-20, E0+20);	

	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield[3]);
	   f0->FixParameter(2, E1);
	   f0->FixParameter(3, FindSigma(E1));
	   
	   f0->SetParameter(4, max_height[3]);
	   f0->FixParameter(5, E0);
	   f0->FixParameter(6, FindSigma(E0));	   
	   
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
// Find the range in which the BKG-Pol1 parameters of the models vary (1 gamma peak)
double *FindRange_Gamma_Pol1(int E0, std::vector<int> bin_content, int *max_height, double E1, int *max_gammaYield, int xL, int xR) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i])); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i])); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i])); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i])); break; }
   }
   
   double q = - ( 2*x_min*bin_content.at(x_min) - x_min*bin_content.at(x_max-1) - x_max*bin_content.at(x_min) ) / ( x_min - x_max );
   double m = ( bin_content.at(x_min) - bin_content.at(x_max-1) ) / ( x_min - x_max + 0.0 );

   // ROOT fit: f1 = pol1 + gaus(E1)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true)", E0);
   	   TF1 *f1 = new TF1("f1", function, E0-20, E0+20);
	   
	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield[3]);
	   f1->FixParameter(3, E1);
	   f1->FixParameter(4, FindSigma(E1));
	   
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
   
   // ROOT fit: f1 = pol1 + gaus(E1) + gaus
   else {
   	   
   	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true) + [5]*TMath::Gaus(x, [6], [7], true)", E0);
   	   TF1 *f1 = new TF1("f1", function, E0-20, E0+20);

	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield[3]);
	   f1->FixParameter(3, E1);
	   f1->FixParameter(4, FindSigma(E1));
	   
	   f1->SetParameter(5, max_height[3]);
	   f1->FixParameter(6, E0);
	   f1->FixParameter(7, FindSigma(E0));	   
	   
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
// Find the range in which the BKG-Pol2 parameters of the models vary (1 gamma peak)
double *FindRange_Gamma_Pol2(int E0, std::vector<int> bin_content, int *max_height, double E1, int *max_gammaYield, int xL, int xR) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i])); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i])); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i])); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i])); break; }
   }
   
   double a_x = x_min;
   double a_y = bin_content.at(x_min);
   double b_x = E0;
   double b_y = bin_content.at(E0);
   double c_x = x_max;
   double c_y = bin_content.at(x_max);
   	   
   double k = pow ( b_x/c_x, 2);
   double q = pow ( a_x/c_x, 2);
   double z = ( b_y - k*c_y ) / ( b_x - k*c_x );
   	   
   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-k)/(b_x-k*c_x) - q*(1-c_x*(1-k)/(b_x-k*c_x)) );
   double p_1 = ( b_y - p_0*(1-k) - k*c_y ) / ( b_x - k*c_x );
   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);

   // ROOT fit: f2 = pol2 + gaus(E1)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2", function, E0-20, E0+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);
	   
	   f2->SetParameter(3, max_gammaYield[3]);
	   f2->FixParameter(4, E1);
	   f2->FixParameter(5, FindSigma(E1));
	   
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
   
   // ROOT fit: f2 = pol2 + gaus(E1) +  gaus
   else {
   	   
   	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true) + [6]*TMath::Gaus(x, [7], [8], true)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2",function, E0-20, E0+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	 
	   
	   f2->SetParameter(3, max_gammaYield[3]);
	   f2->FixParameter(4, E1);
	   f2->FixParameter(5, FindSigma(E1));  
	   
   	   f2->SetParameter(6, max_height[3]);
	   f2->FixParameter(7, E0);
	   f2->FixParameter(8, FindSigma(E0));   
	   
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
// Find the range in which the BKG-Pol0 parameters of the models vary (2 gamma peaks)
double *FindRange_TwoGamma_Pol0(int E0, std::vector<int> bin_content, int *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
   
   int B_i = 0;
   int N_bkg = 0;
   int check1 = 0;
   int check2 = 0;
   
   // LEFT part
   for (int i=0; i<numGamma; i++) {
   	if ( E_gamma[i]>=x_min && E_gamma[i]<=xL ) {
   		// 2 gamma peaks in [x_min;xL]
   		if ( E_gamma[i+1]>=x_min && E_gamma[i+1]<=xL ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > x_min ) {
	   			for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - x_min );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i]) + FindFWHM(E_gamma[i+1])) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1])) < xL ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])) );
	   		}
	   		break;
   		}
   		// 1 gamma peaks in [x_min;xL]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > x_min ) {
   				for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - x_min );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i])) < xL ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
   			}
   			break;
   		} 		
   	}
   	// no gamma peaks in [x_min;xL]
   	else { check1 += 1; }
   } 
   
   // RIGHT part	
   for (int i=0; i<numGamma; i++) {	
   	if ( E_gamma[i]>=xR && E_gamma[i]<=x_max ) {
   		// 2 gamma peaks in [xR;x_max]
   		if ( E_gamma[i+1]>=xR && E_gamma[i+1]<=x_max ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > xR ) {
	   			for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - xR );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i]) + FindFWHM(E_gamma[i+1])) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1])) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1])) < x_max ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1])) );
	   		}
	   		break;   		
   		}
   		// 1 gamma peaks in [xR;x_max]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i])) > xR ) {
   				for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i])); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i])) - xR );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i])) < x_max ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i])); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i]+1.5*FindFWHM(E_gamma[i])) );
   			}
   			break;
   		} 
   		
   	}
   	// no gamma peaks in [xR;x_max]
   	else { check2 += 1; }
   }
   
   // no gamma peaks in [x_min;xL]
   if ( check1 == numGamma ) {
   	for (int j=x_min; j<xL; j++) { B_i += bin_content.at(j); }
	N_bkg += ( xL - x_min);
   }
   // no gamma peaks in [xR;x_max]
   if ( check2 == numGamma ) {
   	for (int j=xR; j<x_max; j++) { B_i += bin_content.at(j); }
	N_bkg += ( x_max - xR);
   }
   
   int p0 = std::round((N_bkg+max_height[5])/(B_i+max_height[4]+0.0));
   
   // ROOT fit: f0 = pol0 + gaus(E1) + gaus(E2)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true) + [4]*TMath::Gaus(x, [5], [6], true)", E0-20, E0+20);
	   
	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield1[3]);
	   f0->FixParameter(2, E1);
	   f0->FixParameter(3, FindSigma(E1));
	   
	   f0->SetParameter(4, max_gammaYield2[3]);
	   f0->FixParameter(5, E2);
	   f0->FixParameter(6, FindSigma(E2));
	   
	   h_energy->Fit("f0","R");
	   
	   double *output_pol0 = new double[2];
	   output_pol0[0] = f0->GetParameter(0); // constant
	   output_pol0[1] = f0->GetParError(0);
	   
	   delete h_energy;
	   delete f0;
	   return output_pol0; 
   }
   
   // ROOT fit: f0 = pol0 + gaus(E1) + gaus(E2) + gaus
   else {
   	   
   	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true) + [4]*TMath::Gaus(x, [5], [6], true) + [7]*TMath::Gaus(x, [8], [9], true)", E0-20, E0+20);	

	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield1[3]);
	   f0->FixParameter(2, E1);
	   f0->FixParameter(3, FindSigma(E1));
	   
	   f0->SetParameter(4, max_gammaYield2[3]);
	   f0->FixParameter(5, E2);
	   f0->FixParameter(6, FindSigma(E2));
	   
	   f0->SetParameter(7, max_height[3]);
	   f0->FixParameter(8, E0);
	   f0->FixParameter(9, FindSigma(E0));	   
	   
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
// Find the range in which the BKG-Pol1 parameters of the models vary (2 gamma peaks)
double *FindRange_TwoGamma_Pol1(int E0, std::vector<int> bin_content, int *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i])); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i])); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i])); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i])); break; }
   }
   
   double q = - ( 2*x_min*bin_content.at(x_min) - x_min*bin_content.at(x_max-1) - x_max*bin_content.at(x_min) ) / ( x_min - x_max );
   double m = ( bin_content.at(x_min) - bin_content.at(x_max-1) ) / ( x_min - x_max + 0.0 );

   // ROOT fit: f1 = pol1 + gaus(E1) + gaus(E2)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true) + [5]*TMath::Gaus(x, [6], [7], true)", E0);
   	   TF1 *f1 = new TF1("f1", function, E0-20, E0+20);
	   
	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield1[3]);
	   f1->FixParameter(3, E1);
	   f1->FixParameter(4, FindSigma(E1));
	   
	   f1->SetParameter(5, max_gammaYield2[3]);
	   f1->FixParameter(6, E2);
	   f1->FixParameter(7, FindSigma(E2));
	   
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
   
   // ROOT fit: f1 = pol1 + gaus(E1) + gaus(E2) + gaus
   else {
   	   
   	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true) + [5]*TMath::Gaus(x, [6], [7], true) + [8]*TMath::Gaus(x, [9], [10], true)", E0);
   	   TF1 *f1 = new TF1("f1", function, E0-20, E0+20);

	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield1[3]);
	   f1->FixParameter(3, E1);
	   f1->FixParameter(4, FindSigma(E1));
	   
	   f1->SetParameter(5, max_gammaYield2[3]);
	   f1->FixParameter(6, E2);
	   f1->FixParameter(7, FindSigma(E2));
	   
	   f1->SetParameter(8, max_height[3]);
	   f1->FixParameter(9, E0);
	   f1->FixParameter(10, FindSigma(E0));	   
	   
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
// Find the range in which the BKG-Pol2 parameters of the models vary (2 gamma peaks)
double *FindRange_TwoGamma_Pol2(int E0, std::vector<int> bin_content, int *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   double E_gamma[11]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min = E0 - 20;
   int x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i])); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i])); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i]) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i])); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i])); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i]) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i])); break; }
   }
   
   double a_x = x_min;
   double a_y = bin_content.at(x_min);
   double b_x = E0;
   double b_y = bin_content.at(E0);
   double c_x = x_max;
   double c_y = bin_content.at(x_max);
   	   
   double k = pow ( b_x/c_x, 2);
   double q = pow ( a_x/c_x, 2);
   double z = ( b_y - k*c_y ) / ( b_x - k*c_x );
   	   
   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-k)/(b_x-k*c_x) - q*(1-c_x*(1-k)/(b_x-k*c_x)) );
   double p_1 = ( b_y - p_0*(1-k) - k*c_y ) / ( b_x - k*c_x );
   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);

   // ROOT fit: f2 = pol2 + gaus(E1) + gaus(E2)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	
	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true) + [6]*TMath::Gaus(x, [7], [8], true)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2", function, E0-20, E0+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);
	   
	   f2->SetParameter(3, max_gammaYield1[3]);
	   f2->FixParameter(4, E1);
	   f2->FixParameter(5, FindSigma(E1));
	   
	   f2->SetParameter(6, max_gammaYield2[3]);
	   f2->FixParameter(7, E2);
	   f2->FixParameter(8, FindSigma(E2));
	   
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
   
   // ROOT fit: f2 = pol2 + gaus(E1) + gaus(E1) +  gaus
   else {
   	   
   	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true) + [6]*TMath::Gaus(x, [7], [8], true) + [9]*TMath::Gaus(x, [10], [11], true)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2",function, E0-20, E0+20);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	 
	   
	   f2->SetParameter(3, max_gammaYield1[3]);
	   f2->FixParameter(4, E1);
	   f2->FixParameter(5, FindSigma(E1));  
	   
	   f2->SetParameter(6, max_gammaYield2[3]);
	   f2->FixParameter(7, E2);
	   f2->FixParameter(8, FindSigma(E2));
	   
   	   f2->SetParameter(9, max_height[3]);
	   f2->FixParameter(10, E0);
	   f2->FixParameter(11, FindSigma(E0));   
	   
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
