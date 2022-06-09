// **********************************************************************************************************************
// This file contains different functions that are called in the source files in order to calculate different quantities
// and to perform a prefit for the BKG polynomial before the BAT analysis.
// **********************************************************************************************************************
#include "Operations.h"

const int thr = 195;

//=======================================================================================================================
// Calculates the number of rows in a file
Int_t NumberOfRows(char *filename) {

	Int_t NumOfRows = 0;
	std::string line;
	std::ifstream file(filename);
	while (std::getline(file,line)) {
		++NumOfRows;
	}
	return NumOfRows;
}



//=======================================================================================================================
// Returns 'true' only if b > a
bool FindMax(int a, int b) {
   return (a < b);
}



//=======================================================================================================================
// Calculates the atomic mass in ph(II)
double atomic_mass_II(int E0, int thr) {
		
	return 0;	
}



//=======================================================================================================================
// Calculates the atomic mass in ph(II,II+)
double atomic_mass_II_IIp(int E0, int thr) {

	double f76 = 88.0 / 100.0;
	double A_76 = 75.921402725; // g/mol
	double A_Ge = 72.64; // g/mol
	double A = f76*A_76 + (1.0-f76)*A_Ge;
		
	return A;	
}




//=======================================================================================================================
// Calculates the energetic resolution for a given energy value 
double FindSigma(int energy, int k) {

   double a=0.0, b=0.0;
   
   if ( k==0 ) { // enrCoax (pre upgrade)
   	a = 1.025;   
   	b = 6.47e-4; 
   }
   if ( k==1 ) { // enrBEGe (pre upgrade)
   	a = 0.681;   
   	b = 4.27e-4; 
   }
   if ( k==2 ) { // enrCoax (post upgrade)
   	a = 0.898;   
   	b = 20.0e-4; 
   }
   if ( k==3 ) { // enrBEGe (post upgrade)
   	a = 0.363;   
   	b = 4.32e-4; 
   }
   if ( k==4 ) { // invCoax (post upgrade)
   	a = 0.280;   
   	b = 5.83e-4; 
   }

   double sigma =  sqrt( a + b*energy );
   return sigma;
}



//=======================================================================================================================
// Calculates the FWHM for a given energy value
double FindFWHM(int energy, int k) {

   double FWHM = sqrt( 8*log(2) ) * FindSigma(energy, k);
   return FWHM;
}



//=======================================================================================================================
// Calculates the maximum of the signal height parameter
double *FindMaximumSignalHeight(int E0) {

	// Ge xsec loading
	char input_name[300];
	sprintf(input_name, "/home/sofia/Analysis/super-wimps/SuperWIMPs_couplings/Ge_photo-xsec_1keV-1600keV.txt");
	std::ifstream input_Ge(input_name);
	Int_t row_Ge = NumberOfRows(input_name);
	double data_Ge[row_Ge][2];
	for ( int i=0; i<row_Ge; i++ ) {
		for ( int j=0; j<2; j++ ) {
			input_Ge >> data_Ge[i][j];
		}
	}
	input_Ge.close();
	
	int k = 0;
	double diff = data_Ge[k][0]-E0;
	while ( diff!=0 ) { k++; diff=data_Ge[k][0]-E0; }
	double xsec = data_Ge[k][1];
	
	
	// PRL coupling 
	char file_g_Riz[300];
	sprintf(file_g_Riz, "/home/sofia/Analysis/super-wimps/SuperWIMPs_couplings/ssh_lngs_RizAnalysis/PaperPlots/Limits/enrCoax_sens_limits.txt");
	std::ifstream input(file_g_Riz);
	Int_t row = NumberOfRows(file_g_Riz);
	double data[row][2];
	for ( int i=0; i<row; i++ ) {
		for ( int j=0; j<2; j++ ) {
			input >> data[i][j];
		}
	}
	input.close();
	
	// import efficiencies (fill arrray with json object values)
	long double eff_coax_II_riz[5260][2]={0}, eff_BEGe_II_riz[5260][2]={0};
	std::ifstream file_riz("/home/sofia/Analysis/super-wimps/SuperWIMPs_couplings/efficiency_Rizalina/TotEnCorrectionLAr.json");
	json jread_riz;
	file_riz >> jread_riz;
	file_riz.close();
	
	json energy = jread_riz["energy"];
	json enrBEGe = jread_riz["enrBEGe"];
	json enrCoax = jread_riz["enrCoax"];
	int j = 0;
	for ( auto i=energy.begin(); i!=energy.end(); ++i ) { // energy column
		eff_coax_II_riz[j][0] = i.value();
		eff_BEGe_II_riz[j][0] = i.value();
		j++;
	}
	j = 0;
	for ( auto i=enrBEGe.begin(); i!=enrBEGe.end(); ++i ) { // enrBEGe eff. column
		eff_BEGe_II_riz[j][1] = i.value();
		j++;
	}
	j = 0;
	for ( auto i=enrCoax.begin(); i!=enrCoax.end(); ++i ) { // enrCoax eff. column
		eff_coax_II_riz[j][1] = i.value();
		j++;
	}
	
	double *results = new double[2]; // alpha | g_ae
	
	int i = 0;
	int p = 0;
	while (i<980) {
	
		int energy = i+60;
		if ( energy!=E0 ) { i++; continue; }
		if ( energy>1022 ) break;
		
		if ( energy==89 ) p++;
		if ( energy==97 ) p++;
		if ( energy==98 ) p++;
		if ( i>937 ) { i=937; p=0; }
		
		int data_line = i+p;
		int row_eff = i+20;	
		//std::cout << energy << "\t" << i << "\t" << data[data_line][0] << std::endl;
		
		double exposure_0=0.0, exposure_1=0.0;
		if ( energy<195 ) { exposure_0 = 6.7*365.25; exposure_1 = 7.7*365.25; }
		if ( energy>=195 ) { exposure_0 = 28.1*365.25; exposure_1 = 30.8*365.25; }
			
		double eff_bege = eff_BEGe_II_riz[row_eff][1];
		double eff_coax = eff_coax_II_riz[row_eff][1];
	
		double R90 = data[data_line][1] / 365.25; // [counts/kg*days]
		const double A = 75.921402725*0.88;
		
		// vector superWIMPs
		double vector_num = R90 * A  * eff_coax * energy;
		double vector_den = 4.683 * 1e23 * xsec;
		results[0] = vector_num / vector_den;
		
		// pseudoscalar superWIMPs
		double pseudoscalar_num = R90 * A * eff_coax ;
		double pseudoscalar_den = 1.467 * 1e19 * xsec * energy;
		results[1] = sqrt( pseudoscalar_num / pseudoscalar_den ); 
		
		break;
	}
	
	//std::cout << " alpha = " << results[1] << "\t g_ae = " << results[1] << std::endl;
	return results;
}



//=======================================================================================================================
// Calculates the maximum of the 1st gamma height parameter
int *FindMaximumGammaHeight1(int E0, double E1, double E2, std::vector<double> bin_content, int xL, int xR, int outputK, int k) {

   double FWHM_0 = FindFWHM(E0, k);
   double FWHM_1 = FindFWHM(E1, k);
   double FWHM_2 = FindFWHM(E2, k);
   int xL_S = std::round( E0 - 1.5*FWHM_0 ); 
   int xR_S = std::round( E0 + 1.5*FWHM_0 ); 
   int xL_1 = std::round( E1 - 1.5*FWHM_1 ); 
   int xR_1 = std::round( E1 + 1.5*FWHM_1 ); 
   double B_i = 0;  
   double N_bkg = 0;
   double B_avg = 0.0;
   double G_i = 0;
   double N_sig = 0;
   double B_G = 0.0;
   double G = 0;


   if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {}
   else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
   
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
   else {
   
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
   G = G_i-B_G; 
   
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
int *FindMaximumGammaHeight2(int E0, double E1, double E2, std::vector<double> bin_content, int xL, int xR, int outputK, int k) {

   double FWHM_0 = FindFWHM(E0, k);
   double FWHM_1 = FindFWHM(E1, k);
   double FWHM_2 = FindFWHM(E2, k);
   int xL_S = std::round( E0 - 1.5*FWHM_0 ); 
   int xR_S = std::round( E0 + 1.5*FWHM_0 ); 
   int xL_1 = std::round( E1 - 1.5*FWHM_1 ); 
   int xL_2 = std::round( E2 - 1.5*FWHM_2 ); 
   int xR_2 = std::round( E2 + 1.5*FWHM_2 ); 
   double B_i = 0;  
   double N_bkg = 0;
   double B_avg = 0.0;
   double G_i = 0;
   double N_sig = 0;
   double B_G = 0.0;
   double G = 0;


   if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {}
   else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {}
   else {
   
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
   G = G_i-B_G; 
   
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
double *FindRange_Pol0(int E0, std::vector<double> bin_content, double *max_height, int xL, int xR, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;
   
   double B_i = 0;
   double N_bkg = 0;
   int check1 = 0;
   int check2 = 0;
   
   // LEFT part
   for (int i=0; i<numGamma; i++) {
   	if ( E_gamma[i]>=x_min && E_gamma[i]<=xL ) {
   		// 2 gamma peaks in [x_min;xL]
   		if ( E_gamma[i+1]>=x_min && E_gamma[i+1]<=xL ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > x_min ) {
	   			for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - x_min );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i], k) + FindFWHM(E_gamma[i+1], k)) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1], k)) < xL ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)) );
	   		}
	   		break;
   		}
   		// 1 gamma peaks in [x_min;xL]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > x_min ) {
   				for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - x_min );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i], k)) < xL ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
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
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > xR ) {
	   			for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - xR );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i], k) + FindFWHM(E_gamma[i+1], k)) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1], k)) < x_max ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)) );
	   		}
	   		break;   		
   		}
   		// 1 gamma peaks in [xR;x_max]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > xR ) {
   				for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - xR );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i], k)) < x_max ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
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
   
   double p0 = (N_bkg+max_height[5])/(B_i+max_height[4]+0.0);
   
   // ROOT fit: f0 = pol0 
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0]", x_min, x_max);
	   
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
   	   
   	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true)", x_min, x_max);
   	   
	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_height[3]);
	   f0->FixParameter(2, E0);
	   f0->FixParameter(3, FindSigma(E0, k));   
	   
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
double *FindRange_Pol1(int E0, std::vector<double> bin_content, double *max_height, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;

   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i], k)); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i], k)); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i], k)); break; }
   }
   
   double q = - ( 2*x_min*bin_content.at(x_min) - x_min*bin_content.at(x_max-1) - x_max*bin_content.at(x_min) ) / ( x_min - x_max );
   double m = ( bin_content.at(x_min) - bin_content.at(x_max-1) ) / ( x_min - x_max + 0.0 );

   // ROOT fit: f1 = pol1
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	 
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i)", E0);
   	   TF1 *f1 = new TF1("f1", function, x_min, x_max);
   	   
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
   	   TF1 *f1 = new TF1("f1", function, x_min, x_max);
   	   
   	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);	   
	   
   	   f1->SetParLimits(2, 0, max_height[3]);
	   f1->FixParameter(3, E0);
	   f1->FixParameter(4, FindSigma(E0, k));   
	   
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
double *FindRange_Pol2(int E0, std::vector<double> bin_content, double *max_height, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i], k)); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i], k)); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i], k)); break; }
   }
   
   double a_x = x_min;
   double a_y = bin_content.at(x_min);
   double b_x = E0;
   double b_y = bin_content.at(std::round(b_x));
   double c_x = x_max;
   double c_y = bin_content.at(x_max-1);
   	   
   double w = pow ( b_x/c_x, 2);
   double q = pow ( a_x/c_x, 2);
   double z = ( b_y - w*c_y ) / ( b_x - w*c_x );
   	   
   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-w)/(b_x-w*c_x) - q*(1-c_x*(1-w)/(b_x-w*c_x)) );
   double p_1 = ( b_y - p_0*(1-w) - w*c_y ) / ( b_x - w*c_x );
   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);

   // ROOT fit: f2 = pol2
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2", function, x_min, x_max);
   	   
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
   	   TF1 *f2 = new TF1("f2", function, x_min, x_max);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	   
	   
   	   f2->SetParameter(3, max_height[3]);
	   f2->FixParameter(4, E0);
	   f2->FixParameter(5, FindSigma(E0, k));   
	   
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
double *FindRange_Gamma_Pol0(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield, int xL, int xR, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;
   
   double B_i = 0;
   double N_bkg = 0;
   int check1 = 0;
   int check2 = 0;
      
   // LEFT part
   for (int i=0; i<numGamma; i++) {
   	if ( E_gamma[i]>=x_min && E_gamma[i]<=xL ) {
   		// 2 gamma peaks in [x_min;xL]
   		if ( E_gamma[i+1]>=x_min && E_gamma[i+1]<=xL ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > x_min ) {
	   			for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - x_min );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i], k) + FindFWHM(E_gamma[i+1], k)) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1], k)) < xL ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)) );
	   		}
	   		break;
   		}
   		// 1 gamma peaks in [x_min;xL]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > x_min ) {
   				for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - x_min );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i], k)) < xL ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
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
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > xR ) {
	   			for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - xR );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i], k) + FindFWHM(E_gamma[i+1], k)) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1], k)) < x_max ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)) );
	   		}
	   		break;   		
   		}
   		// 1 gamma peaks in [xR;x_max]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > xR ) {
   				for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - xR );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i], k)) < x_max ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
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
   
   double p0 = (N_bkg+max_height[5])/(B_i+max_height[4]+0.0);
   
   // ROOT fit: f0 = pol0 + gaus(E1)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true)", x_min, x_max);
	   
	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield[3]);
	   f0->FixParameter(2, E1);
	   f0->FixParameter(3, FindSigma(E1, k));
	   
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
   	   
   	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true) + [4]*TMath::Gaus(x, [5], [6], true)", x_min, x_max);

	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield[3]);
	   f0->FixParameter(2, E1);
	   f0->FixParameter(3, FindSigma(E1, k));
	   
	   f0->SetParameter(4, max_height[3]);
	   f0->FixParameter(5, E0);
	   f0->FixParameter(6, FindSigma(E0, k));	   
	   
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
double *FindRange_Gamma_Pol1(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield, int xL, int xR, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i], k)); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i], k)); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i], k)); break; }
   }
   
   double q = - ( 2*x_min*bin_content.at(x_min) - x_min*bin_content.at(x_max-1) - x_max*bin_content.at(x_min) ) / ( x_min - x_max );
   double m = ( bin_content.at(x_min) - bin_content.at(x_max-1) ) / ( x_min - x_max + 0.0 );

   // ROOT fit: f1 = pol1 + gaus(E1)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true)", E0);
   	   TF1 *f1 = new TF1("f1", function, x_min, x_max);
	   
	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield[3]);
	   f1->FixParameter(3, E1);
	   f1->FixParameter(4, FindSigma(E1, k));
	   
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
   	   TF1 *f1 = new TF1("f1", function, x_min, x_max);

	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield[3]);
	   f1->FixParameter(3, E1);
	   f1->FixParameter(4, FindSigma(E1, k));
	   
	   f1->SetParameter(5, max_height[3]);
	   f1->FixParameter(6, E0);
	   f1->FixParameter(7, FindSigma(E0, k));	   
	   
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
double *FindRange_Gamma_Pol2(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield, int xL, int xR, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i], k)); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i], k)); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i], k)); break; }
   }
   
   double a_x = x_min;
   double a_y = bin_content.at(x_min);
   double b_x = E0;
   double b_y = bin_content.at(E0);
   double c_x = x_max;
   double c_y = bin_content.at(x_max);
   	   
   double w = pow ( b_x/c_x, 2);
   double q = pow ( a_x/c_x, 2);
   double z = ( b_y - w*c_y ) / ( b_x - w*c_x );
   	   
   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-w)/(b_x-w*c_x) - q*(1-c_x*(1-w)/(b_x-w*c_x)) );
   double p_1 = ( b_y - p_0*(1-w) - w*c_y ) / ( b_x - w*c_x );
   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);

   // ROOT fit: f2 = pol2 + gaus(E1)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	
	   char function[100];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2", function, x_min, x_max);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);
	   
	   f2->SetParameter(3, max_gammaYield[3]);
	   f2->FixParameter(4, E1);
	   f2->FixParameter(5, FindSigma(E1, k));
	   
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
   	   TF1 *f2 = new TF1("f2", function, x_min, x_max);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	 
	   
	   f2->SetParameter(3, max_gammaYield[3]);
	   f2->FixParameter(4, E1);
	   f2->FixParameter(5, FindSigma(E1, k));  
	   
   	   f2->SetParameter(6, max_height[3]);
	   f2->FixParameter(7, E0);
	   f2->FixParameter(8, FindSigma(E0, k));   
	   
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
double *FindRange_TwoGamma_Pol0(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;
   
   double B_i = 0;
   double N_bkg = 0;
   int check1 = 0;
   int check2 = 0;
   
   // LEFT part
   for (int i=0; i<numGamma; i++) {
   	if ( E_gamma[i]>=x_min && E_gamma[i]<=xL ) {
   		// 2 gamma peaks in [x_min;xL]
   		if ( E_gamma[i+1]>=x_min && E_gamma[i+1]<=xL ) {
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > x_min ) {
	   			for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - x_min );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i], k) + FindFWHM(E_gamma[i+1], k)) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1], k)) < xL ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)) );
	   		}
	   		break;
   		}
   		// 1 gamma peaks in [x_min;xL]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > x_min ) {
   				for (int j=x_min; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - x_min );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i], k)) < xL ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<xL; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( xL - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
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
	   		if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > xR ) {
	   			for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - xR );
	   		}
	   		
	   		if ( (E_gamma[i+1] - E_gamma[i]) > 1.5*(FindFWHM(E_gamma[i], k) + FindFWHM(E_gamma[i+1], k)) ) { // far peaks
	   			for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<(E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i+1]-1.5*FindFWHM(E_gamma[i+1], k)) - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
	   		}
	   		
	   		if ( (E_gamma[i+1] + 1.5*FindFWHM(E_gamma[i+1], k)) < x_max ) {
		   		for (int j=(E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i+1]+1.5*FindFWHM(E_gamma[i+1], k)) );
	   		}
	   		break;   		
   		}
   		// 1 gamma peaks in [xR;x_max]
   		else {
   			if ( (E_gamma[i] - 1.5*FindFWHM(E_gamma[i], k)) > xR ) {
   				for (int j=xR; j<(E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)); j++) { B_i += bin_content.at(j); }
	   			N_bkg += ( (E_gamma[i]-1.5*FindFWHM(E_gamma[i], k)) - xR );
   			}
   			
   			if ( (E_gamma[i] + 1.5*FindFWHM(E_gamma[i], k)) < x_max ) {
   				for (int j=(E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)); j<x_max; j++) { B_i += bin_content.at(j); }
		   		N_bkg += ( x_max - (E_gamma[i]+1.5*FindFWHM(E_gamma[i], k)) );
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
   
   double p0 = (N_bkg+max_height[5])/(B_i+max_height[4]+0.0);
   
   // ROOT fit: f0 = pol0 + gaus(E1) + gaus(E2)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true) + [4]*TMath::Gaus(x, [5], [6], true)", x_min, x_max);
	   
	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield1[3]);
	   f0->FixParameter(2, E1);
	   f0->FixParameter(3, FindSigma(E1, k));
	   
	   f0->SetParameter(4, max_gammaYield2[3]);
	   f0->FixParameter(5, E2);
	   f0->FixParameter(6, FindSigma(E2, k));
	   
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
   	   
   	   TF1 *f0 = new TF1("f0","[0] + [1]*TMath::Gaus(x, [2], [3], true) + [4]*TMath::Gaus(x, [5], [6], true) + [7]*TMath::Gaus(x, [8], [9], true)", x_min, x_max);

	   f0->SetParameter(0, p0);
	   
	   f0->SetParameter(1, max_gammaYield1[3]);
	   f0->FixParameter(2, E1);
	   f0->FixParameter(3, FindSigma(E1, k));
	   
	   f0->SetParameter(4, max_gammaYield2[3]);
	   f0->FixParameter(5, E2);
	   f0->FixParameter(6, FindSigma(E2, k));
	   
	   f0->SetParameter(7, max_height[3]);
	   f0->FixParameter(8, E0);
	   f0->FixParameter(9, FindSigma(E0, k));	   
	   
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
double *FindRange_TwoGamma_Pol1(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // slope and constant are evaluated starting from the equation of a straight line crossing two points
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i], k)); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i], k)); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i], k)); break; }
   }
   
   double q = - ( 2*x_min*bin_content.at(x_min) - x_min*bin_content.at(x_max-1) - x_max*bin_content.at(x_min) ) / ( x_min - x_max );
   double m = ( bin_content.at(x_min) - bin_content.at(x_max-1) ) / ( x_min - x_max + 0.0 );

   // ROOT fit: f1 = pol1 + gaus(E1) + gaus(E2)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	   	
	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*TMath::Gaus(x, [3], [4], true) + [5]*TMath::Gaus(x, [6], [7], true)", E0);
   	   TF1 *f1 = new TF1("f1", function, x_min, x_max);
	   
	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield1[3]);
	   f1->FixParameter(3, E1);
	   f1->FixParameter(4, FindSigma(E1, k));
	   
	   f1->SetParameter(5, max_gammaYield2[3]);
	   f1->FixParameter(6, E2);
	   f1->FixParameter(7, FindSigma(E2, k));
	   
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
   	   TF1 *f1 = new TF1("f1", function, x_min, x_max);

	   f1->SetParameter(0, q);
	   f1->SetParameter(1, m);
	   
	   f1->SetParameter(2, max_gammaYield1[3]);
	   f1->FixParameter(3, E1);
	   f1->FixParameter(4, FindSigma(E1, k));
	   
	   f1->SetParameter(5, max_gammaYield2[3]);
	   f1->FixParameter(6, E2);
	   f1->FixParameter(7, FindSigma(E2, k));
	   
	   f1->SetParameter(8, max_height[3]);
	   f1->FixParameter(9, E0);
	   f1->FixParameter(10, FindSigma(E0, k));	   
	   
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
double *FindRange_TwoGamma_Pol2(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR, int k) {

   TH1D *h_energy = new TH1D("h_energy","", 5200, 0, 5200);
   for (int i=0; i<5200; i++) { h_energy->SetBinContent(i+1, bin_content.at(i) ); }
   
   // Second order parameters are evaluated starting from the equation of a parabola crossing three points
   double E_gamma[13]={238.6, 242.0, 295.2, 352.0, 478.3, 511.0, 514.0, 583.2, 609.3, 911.2, 969.0, 1460.8, 1524.6};
   int numGamma = sizeof(E_gamma)/sizeof(*E_gamma);
   
   int x_min=0, x_max=0;
   if ( E0 >= thr+20 ) {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   if ( E0 > thr-20 && E0 < thr ) {
	   x_min = E0 - 20;
	   x_max = thr-1;  
   }
   if ( E0 >= thr && E0 < thr+20 ) {
	   x_min = thr;
	   x_max = E0 + 20;   
   }
   if ( E0 <= thr-20)  {
	   x_min = E0 - 20;
	   x_max = E0 + 20;
   }
   //x_min = E0 - 20;
   //x_max = E0 + 20;
   
   for (int i=0; i<numGamma; i++) {
   	// x_min:
   	// gamma peak on the left
   	if ( x_min - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_min - E_gamma[i] > 0 ) { x_min = std::round(x_min + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_min == E_gamma[i] ) { x_min = std::round(x_min + 1.5*FindFWHM(E_gamma[i], k)); }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_min < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_min > 0 ) { x_min = std::round(x_min - FindFWHM(E_gamma[i], k)); break; }
   	// x_max:
   	// gamma peak on the left
   	if ( x_max - E_gamma[i] < 2*FindFWHM(E_gamma[i], k) && x_max - E_gamma[i] > 0 ) { x_max = std::round(x_max + FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak == x_min
   	else if ( x_max == E_gamma[i] ) { x_max = std::round(x_max + 1.5*FindFWHM(E_gamma[i], k)); break; }	
   	// gamma peak on the right
   	else if ( E_gamma[i] - x_max < 2*FindFWHM(E_gamma[i], k) && E_gamma[i] - x_max > 0 ) { x_max = std::round(x_max - FindFWHM(E_gamma[i], k)); break; }
   }
   
   double a_x = x_min;
   double a_y = bin_content.at(x_min);
   double b_x = E0;
   double b_y = bin_content.at(E0);
   double c_x = x_max;
   double c_y = bin_content.at(x_max);
   	   
   double w = pow ( b_x/c_x, 2);
   double q = pow ( a_x/c_x, 2);
   double z = ( b_y - w*c_y ) / ( b_x - w*c_x );
   	   
   double p_0 = ( a_y - z*(1-q*c_x) - q*c_y ) / ( 1 - (1-w)/(b_x-w*c_x) - q*(1-c_x*(1-w)/(b_x-w*c_x)) );
   double p_1 = ( b_y - p_0*(1-w) - w*c_y ) / ( b_x - w*c_x );
   double p_2 = ( c_y - p_0 - p_1*c_x ) / pow( c_x, 2);

   // ROOT fit: f2 = pol2 + gaus(E1) + gaus(E2)
   if ( max_height[2] < 3*sqrt(max_height[1]) ) { 
	
	   char function[200];
   	   sprintf(function,"[0] + [1]*(x-%i) + [2]*(x-%i)*(x-%i) + [3]*TMath::Gaus(x, [4], [5], true) + [6]*TMath::Gaus(x, [7], [8], true)", E0, E0, E0);
   	   TF1 *f2 = new TF1("f2", function, x_min, x_max);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);
	   
	   f2->SetParameter(3, max_gammaYield1[3]);
	   f2->FixParameter(4, E1);
	   f2->FixParameter(5, FindSigma(E1, k));
	   
	   f2->SetParameter(6, max_gammaYield2[3]);
	   f2->FixParameter(7, E2);
	   f2->FixParameter(8, FindSigma(E2, k));
	   
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
   	   TF1 *f2 = new TF1("f2", function, x_min, x_max);
   	   
   	   f2->SetParameter(0, p_0);
	   f2->SetParameter(1, p_1);
	   f2->SetParameter(2, p_2);	 
	   
	   f2->SetParameter(3, max_gammaYield1[3]);
	   f2->FixParameter(4, E1);
	   f2->FixParameter(5, FindSigma(E1, k));  
	   
	   f2->SetParameter(6, max_gammaYield2[3]);
	   f2->FixParameter(7, E2);
	   f2->FixParameter(8, FindSigma(E2, k));
	   
   	   f2->SetParameter(9, max_height[3]);
	   f2->FixParameter(10, E0);
	   f2->FixParameter(11, FindSigma(E0, k));   
	   
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
// Create a JSON file
void JsonFile (const std::vector<double> params, const std::vector<double> params_err, double *FitVariables, std::vector<double> DblResults) {

	int E0 = FitVariables[0];
	double E1 = FitVariables[1];
	double E2 = FitVariables[2];
	int xL = FitVariables[3];
	int xR = FitVariables[4];
	int bin_width = std::round(xR-xL);
	int k  = FitVariables[5];
	int outputK = FitVariables[6];
	int pol_degree = FitVariables[7];
	int rng0 = FitVariables[9];
	int rng1 = FitVariables[10];
	int rng2 = FitVariables[11];
	int rngE0 = FitVariables[12];
	int rngE1 = FitVariables[13];
	int rngE2 = FitVariables[14];
	
	char name_file[200];
	sprintf(name_file, "JsonFiles/JsonFile%i.json", E0);
	std::fstream file;
	file.open(name_file, std::ios::out);
		
	//----------------------------------------------------------------------------------
	// Global mode
	double E0_height_GM=0, E0_height_err_GM=0, E1_height_GM=0, E1_height_err_GM=0, E2_height_GM=0, E2_height_err_GM=0;
	E0_height_GM = params.at(0);
	E0_height_err_GM = params_err.at(0);
	
	double p0_GM=0, p0_err_GM=0, p1_GM=0, p2_GM=0, p1_err_GM=0, p2_err_GM=0;	
	p0_GM = params.at(1);
	p0_err_GM = params_err.at(1);
	if ( pol_degree==1 ) {
		p1_GM = params.at(2);
		p1_err_GM = params_err.at(2);
	}
	if ( pol_degree==2 ) {
		p1_GM = params.at(2);
		p1_err_GM = params_err.at(2);
		p2_GM = params.at(3);
		p2_err_GM = params_err.at(3);
	}
	
	
	
	
	if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {}
	// 1 gamma peak
	else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
		if ( pol_degree==0 ) {
			E1_height_GM = params.at(2);
			E1_height_err_GM = params_err.at(2);
		}
		if ( pol_degree==1 ) {
			E1_height_GM = params.at(3);
			E1_height_err_GM = params_err.at(3);
		}
		if (pol_degree==2 ) {
			E1_height_GM = params.at(4);
			E1_height_err_GM = params_err.at(4);
		}
	}
	// 2 gamma peaks
	else {
		if ( pol_degree==0 ) {
			E1_height_GM = params.at(2);
			E1_height_err_GM = params_err.at(2);
			E2_height_GM = params.at(3);
			E2_height_err_GM = params_err.at(3);
		}
		if ( pol_degree==1 ) {
			E1_height_GM = params.at(3);
			E1_height_err_GM = params_err.at(3);
			E2_height_GM = params.at(4);
			E2_height_err_GM = params_err.at(4);
		}
		if ( pol_degree==2 ) {
			E1_height_GM = params.at(4);
			E1_height_err_GM = params_err.at(4);
			E2_height_GM = params.at(5);
			E2_height_err_GM = params_err.at(5);
		}
	}
	
	
	//----------------------------------------------------------------------------------
	json j1, j2, j3, j4, j5, j6, j7;
	
	// Results of "peak_search.sh"
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j1 = {
			{ "polDegree_BKG", pol_degree},
			{ "windowLeftEdge_xL", xL},
			{ "windowRightEdge_xR", xR},
			{ "windowWidth", bin_width},
			{ "k_GammaArrayIndex", k},
			{ "outputk_GammaPosition", outputK},
			{ "rng_p0", rng0},
			{ "rng_S", rngE0}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {	
		j1 = {
			{ "E1", E1},
			{ "polDegree_BKG", pol_degree},
			{ "windowLeftEdge_xL", xL},
			{ "windowRightEdge_xR", xR},
			{ "windowWidth", bin_width},
			{ "k_GammaArrayIndex", k},
			{ "outputk_GammaPosition", outputK},
			{ "rng_p0", rng0},
			{ "rng_S", rngE0},
			{ "rng_E1", rngE1}
		};
	}
	// 2 gamma peaks
	else {
		j1 = {
			{ "E1", E1},
			{ "E2", E2},
			{ "polDegree_BKG", pol_degree},
			{ "windowLeftEdge_xL", xL},
			{ "windowRightEdge_xR", xR},
			{ "windowWidth", bin_width},
			{ "k_GammaArrayIndex", k},
			{ "outputk_GammaPosition", outputK},
			{ "rng_p0", rng0},
			{ "rng_S", rngE0},
			{ "rng_E1", rngE1},
			{ "rng_E2", rngE2}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: parameters' ranges
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {	
		j2 = {
			{ "S_counts_MIN", DblResults.at(56)},
			{ "S_counts_MAX", DblResults.at(57)},
			{ "p0_MIN", DblResults.at(58)},
			{ "p0_MAX", DblResults.at(59)}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {	
		j2 = {
			{ "S_counts_MIN", DblResults.at(56)},
			{ "S_counts_MAX", DblResults.at(57)},
			{ "p0_MIN", DblResults.at(58)},
			{ "p0_MAX", DblResults.at(59)},
			{ "E1_counts_MIN", DblResults.at(64)},
			{ "E1_counts_MAX", DblResults.at(65)}
		};
	}
	// 2 gamma peaks
	else {	
		j2 = {
			{ "S_counts_MIN", DblResults.at(56)},
			{ "S_counts_MAX", DblResults.at(57)},
			{ "p0_MIN", DblResults.at(58)},
			{ "p0_MAX", DblResults.at(59)},
			{ "E1_counts_MIN", DblResults.at(64)},
			{ "E1_counts_MAX", DblResults.at(65)},
			{ "E2_counts_MIN", DblResults.at(66)},
			{ "E2_counts_MAX", DblResults.at(67)}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: global mode
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j3 = {
			{ "S_counts", E0_height_GM},
			{ "S_counts_sigma", E0_height_err_GM},
			{ "p0", p0_GM},
			{ "p0_sigma", p0_err_GM}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j3 = {
			{ "S_counts", E0_height_GM},
			{ "S_counts_sigma", E0_height_err_GM},
			{ "p0", p0_GM},
			{ "p0_sigma", p0_err_GM},
			{ "E1_counts", E1_height_GM},
			{ "E1_counts_sigma", E1_height_err_GM}
		};
	}
	// 2 gamma peaks
	else {
		j3 = {
			{ "S_counts", E0_height_GM},
			{ "S_counts_sigma", E0_height_err_GM},
			{ "p0", p0_GM},
			{ "p0_sigma", p0_err_GM},
			{ "E1_counts", E1_height_GM},
			{ "E1_counts_sigma", E1_height_err_GM},
			{ "E2_counts", E2_height_GM},
			{ "E2_counts_sigma", E2_height_err_GM}
		};
	}
		
	
	//----------------------------------------------------------------------------------
	// Results of BAT: mean +- sqrt(variance)
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j4 = {
			{ "S_counts", DblResults.at(6)},
			{ "S_counts_sigma", DblResults.at(12)},
			{ "p0", DblResults.at(7)},
			{ "p0_sigma", DblResults.at(13)}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j4 = {
			{ "S_counts", DblResults.at(6)},
			{ "S_counts_sigma", DblResults.at(12)},
			{ "p0", DblResults.at(7)},
			{ "p0_sigma", DblResults.at(13)},
			{ "E1_counts", DblResults.at(10)},
			{ "E1_counts_sigma", DblResults.at(16)}
		};
	}
	// 2 gamma peaks
	else {
		j4 = {
			{ "S_counts", DblResults.at(6)},
			{ "S_counts_sigma", DblResults.at(12)},
			{ "p0", DblResults.at(7)},
			{ "p0_sigma", DblResults.at(13)},
			{ "E1_counts", DblResults.at(10)},
			{ "E1_counts_sigma", DblResults.at(16)},
			{ "E2_counts", DblResults.at(11)},
			{ "E2_counts_sigma", DblResults.at(17)}
		};
	}
	
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: 68% central range ( L=lower/U=upper limit )
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j5 = {
			{ "S_counts_L68", DblResults.at(18)},
			{ "S_counts_U68", DblResults.at(19)},
			{ "p0_L68", DblResults.at(20)},
			{ "p0_U68", DblResults.at(21)}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j5 = {
			{ "S_counts_L68", DblResults.at(18)},
			{ "S_counts_U68", DblResults.at(19)},
			{ "p0_L68", DblResults.at(20)},
			{ "p0_U68", DblResults.at(21)},
			{ "E1_counts_L68", DblResults.at(26)},
			{ "E1_counts_U68", DblResults.at(27)}
		};
	}
	// 2 gamma peaks
	else {
		j5 = {
			{ "S_counts_L68", DblResults.at(18)},
			{ "S_counts_U68", DblResults.at(19)},
			{ "p0_L68", DblResults.at(20)},
			{ "p0_U68", DblResults.at(21)},
			{ "E1_counts_L68", DblResults.at(26)},
			{ "E1_counts_U68", DblResults.at(27)},
			{ "E2_counts_L68", DblResults.at(28)},
			{ "E2_counts_U68", DblResults.at(29)}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: 90% upper limit
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j6 = {
			{ "S_counts_U90", DblResults.at(30)},
			{ "p0_U90", DblResults.at(31)}
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j6 = {
			{ "S_counts_U90", DblResults.at(30)},
			{ "p0_U90", DblResults.at(31)},
			{ "E1_counts_U90", DblResults.at(34)}
		};
	}
	// 2 gamma peaks
	else {
		j6 = {
			{ "S_counts_U90", DblResults.at(30)},
			{ "p0_U90", DblResults.at(31)},
			{ "E1_counts_U90", DblResults.at(34)},
			{ "E2_counts_U90", DblResults.at(35)}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	// Results of BAT: median
	
	// NO gamma peaks
	if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
		j7 = {
			{ "S_counts_median", DblResults.at(36)},
			{ "S_counts_L68_sigma", DblResults.at(42)},
			{ "S_counts_U68_sigma", DblResults.at(43)},
			{ "p0_median", DblResults.at(37)},
			{ "p0_L68_sigma", DblResults.at(44)},
			{ "p0_U68_sigma", DblResults.at(45)},
		};
	}
	// 1 gamma peak
	else if ( (outputK>=2 && outputK<=6) && outputK!=4 ) {
		j7 = {
			{ "S_counts_median", DblResults.at(36)},
			{ "S_counts_L68_sigma", DblResults.at(42)},
			{ "S_counts_U68_sigma", DblResults.at(43)},
			{ "p0_median", DblResults.at(37)},
			{ "p0_L68_sigma", DblResults.at(44)},
			{ "p0_U68_sigma", DblResults.at(45)},
			{ "E1_counts_median", DblResults.at(40)},
			{ "E1_counts_L68_sigma", DblResults.at(50)},
			{ "E1_counts_U68_sigma", DblResults.at(51)}
		};
	}
	// 2 gamma peaks
	else {
		j7 = {
			{ "S_counts_median", DblResults.at(36)},
			{ "S_counts_L68_sigma", DblResults.at(42)},
			{ "S_counts_U68_sigma", DblResults.at(43)},
			{ "p0_median", DblResults.at(37)},
			{ "p0_L68_sigma", DblResults.at(44)},
			{ "p0_U68_sigma", DblResults.at(45)},
			{ "E1_counts_median", DblResults.at(40)},
			{ "E1_counts_L68_sigma", DblResults.at(50)},
			{ "E1_counts_U68_sigma", DblResults.at(51)},
			{ "E2_counts_median", DblResults.at(41)},
			{ "E2_counts_L68_sigma", DblResults.at(52)},
			{ "E2_counts_U68_sigma", DblResults.at(53)}
		};
	}
	
	
	//----------------------------------------------------------------------------------
	if ( pol_degree == 1 ) {
		// p1 data
		j1["rng_p1"] = rng1;
		j2["p1_MIN"] = DblResults.at(60);
		j2["p1_MAX"] = DblResults.at(61);
		j3["p1"] = p1_GM;
		j3["p1_sigma"] = p1_err_GM;
		j4["p1"] = DblResults.at(8);
		j4["p1_sigma"] = DblResults.at(14);
		j5["p1_L68"] = DblResults.at(22);
		j5["p1_U68"] = DblResults.at(23);
		j6["p1_U90"] = DblResults.at(32);
		j7["p1_median"] = DblResults.at(38);
		j7["p1_L68_sigma"] = DblResults.at(46);
		j7["p1_U68_sigma"] = DblResults.at(47);
	}
	if ( pol_degree == 2 ) {
		// p1 data
		j1["rng_p1"] = rng1;
		j2["p1_MIN"] = DblResults.at(60);
		j2["p1_MAX"] = DblResults.at(61);
		j3["p1"] = p1_GM;
		j3["p1_sigma"] = p1_err_GM;
		j4["p1"] = DblResults.at(8);
		j4["p1_sigma"] = DblResults.at(14);
		j5["p1_L68"] = DblResults.at(22);
		j5["p1_U68"] = DblResults.at(23);
		j6["p1_U90"] = DblResults.at(32);
		j7["p1_median"] = DblResults.at(38);
		j7["p1_L68_sigma"] = DblResults.at(46);
		j7["p1_U68_sigma"] = DblResults.at(47);
		
		// p2 data
		j1["rng_p2"] = rng2;
		j2["p2_MIN"] = DblResults.at(62);
		j2["p2_MAX"] = DblResults.at(63);
		j3["p2"] = p2_GM;
		j3["p2_sigma"] = p2_err_GM;
		j4["p2"] = DblResults.at(9);
		j4["p2_sigma"] = DblResults.at(15);
		j5["p2_L68"] = DblResults.at(24);
		j5["p2_U68"] = DblResults.at(25);
		j6["p2_U90"] = DblResults.at(33);
		j7["p2_median"] = DblResults.at(39);
		j7["p2_L68_sigma"] = DblResults.at(48);
		j7["p2_U68_sigma"] = DblResults.at(49);
	}
	
	
	//----------------------------------------------------------------------------------	
	// Final JSON object
	json jtot = json::object({  {"E0", E0}, {"PeakSearch", j1 }, {"ParameterRange", j2 }, {"GlobalMode", j3 },
				    {"Mean", j4 }, {"68CentralRange", j5 }, {"90UpperLimit", j6 }, {"Median", j7 } });
	
	// Print data inside the JSON file
	file << std::setw(4) << jtot << std::endl;
	file.close();
}



//=======================================================================================================================   
std::vector<double> BATResults (int outputK, int pol_degree, BCH1D h_E0, BCH1D h_p0, BCH1D h_p1, BCH1D h_p2, BCH1D h_E1, BCH1D h_E2) {
	    
	    // Local mode
	    double E0_LM=0, p0_LM=0, p1_LM=0, p2_LM=0, E1_LM=0, E2_LM=0;
	    E0_LM = h_E0.GetLocalMode();
	    p0_LM = h_p0.GetLocalMode();
	    if ( pol_degree==1 ) {
	    	p1_LM = h_p1.GetLocalMode();
	    }
	    if ( pol_degree==2 ) {
	    	p1_LM = h_p1.GetLocalMode();
	    	p2_LM = h_p2.GetLocalMode();
	    }
	    
	    // Mean 
	    double E0_M=0, p0_M=0, p1_M=0, p2_M=0, E1_M=0, E2_M=0;
	    E0_M = h_E0.GetHistogram()->GetMean();
	    p0_M = h_p0.GetHistogram()->GetMean();
	    if ( pol_degree==1 ) {
	    	p1_M = h_p1.GetHistogram()->GetMean();
	    }
	    if ( pol_degree==2 ) {
	    	p1_M = h_p1.GetHistogram()->GetMean();
	    	p2_M = h_p2.GetHistogram()->GetMean();
	    }
	    
	    // Sqrt(variance)
	    double E0_RMS=0, p0_RMS=0, p1_RMS=0, p2_RMS=0, E1_RMS=0, E2_RMS=0;
	    E0_RMS = h_E0.GetHistogram()->GetRMS();
	    p0_RMS = h_p0.GetHistogram()->GetRMS();
	    if ( pol_degree==1 ) {
	    	p1_RMS = h_p1.GetHistogram()->GetRMS();
	    }
	    if ( pol_degree==2 ) {
	    	p1_RMS = h_p1.GetHistogram()->GetRMS();
	    	p2_RMS = h_p2.GetHistogram()->GetRMS();
	    }
	    
	    // 68% Quantile, Median
	    double p[7] = {0.05, 0.10, 0.16, 0.50, 0.84, 0.90, 0.95};
	    double E0_q[7]={0}, p0_q[7]={0}, p1_q[7]={0}, p2_q[7]={0}, E1_q[7]={0}, E2_q[7]={0};
	    double E0_L68=0, E0_U68=0, p0_L68=0, p0_U68=0, p1_L68=0, p1_U68=0, p2_L68=0, p2_U68=0, E1_L68=0, E1_U68=0, E2_L68=0, E2_U68=0;
	    h_E0.GetHistogram()->GetQuantiles(7, E0_q, p); // GetQuantiles(n_division, quantiles, probsum[%]);
	    h_p0.GetHistogram()->GetQuantiles(7, p0_q, p);

	    double E0_med=0, p0_med=0, p1_med=0, p2_med=0, E1_med=0, E2_med=0; 
	    E0_med = h_E0.GetQuantile(0.5); // Median
	    p0_med = h_p0.GetQuantile(0.5);
	    
	    double E0_L68_sigma=0, E0_U68_sigma=0, p0_L68_sigma=0, p0_U68_sigma=0, p1_L68_sigma=0, p1_U68_sigma=0;
	    double p2_L68_sigma=0, p2_U68_sigma=0, E1_L68_sigma=0, E1_U68_sigma=0, E2_L68_sigma=0, E2_U68_sigma=0;
	    E0_L68_sigma = E0_q[3] - E0_q[2];
	    E0_U68_sigma = E0_q[4] - E0_q[3];
	    p0_L68_sigma = p0_q[3] - p0_q[2];
	    p0_U68_sigma = p0_q[4] - p0_q[3];
	    
	    E0_L68 = E0_med - E0_L68_sigma;
	    E0_U68 = E0_med + E0_U68_sigma;
	    p0_L68 = p0_med - p0_L68_sigma;
	    p0_U68 = p0_med + p0_U68_sigma;
	    
	    if ( pol_degree==1 ) {
	    	    h_p1.GetHistogram()->GetQuantiles(7, p1_q, p);
	    	    p1_med = h_p1.GetQuantile(0.5);
	    	    p1_L68_sigma = p1_q[3] - p1_q[2];
		    p1_U68_sigma = p1_q[4] - p1_q[3];
	            p1_L68 = p1_med - p1_L68_sigma;
		    p1_U68 = p1_med + p1_U68_sigma;
	    }
	    if ( pol_degree==2 ) {
	    	    h_p1.GetHistogram()->GetQuantiles(7, p1_q, p);
	    	    p1_med = h_p1.GetQuantile(0.5);
	    	    p1_L68_sigma = p1_q[3] - p1_q[2];
		    p1_U68_sigma = p1_q[4] - p1_q[3];
	            p1_L68 = p1_med - p1_L68_sigma;
		    p1_U68 = p1_med + p1_U68_sigma;
		    
		    h_p2.GetHistogram()->GetQuantiles(7, p2_q, p);
		    p2_med = h_p2.GetQuantile(0.5);
		    p2_L68_sigma = p2_q[3] - p2_q[2];
		    p2_U68_sigma = p2_q[4] - p2_q[3];
		    p2_L68 = p2_med - p2_L68_sigma;
		    p2_U68 = p2_med + p2_U68_sigma;
	    }
	
	    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {}
   	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { // E1
	    	    E1_LM = h_E1.GetLocalMode();
	    	    E1_M = h_E1.GetHistogram()->GetMean();
	    	    E1_RMS = h_E1.GetHistogram()->GetRMS();
	    	    
	    	    h_E1.GetHistogram()->GetQuantiles(7, E1_q, p);
	    	    E1_med = h_E1.GetQuantile(0.5);
	    	    E1_L68_sigma = E1_q[3] - E1_q[2];
		    E1_U68_sigma = E1_q[4] - E1_q[3];
	    	    E1_L68 = E1_med - E1_L68_sigma;
	    	    E1_U68 = E1_med + E1_U68_sigma;
	    }
	    else { // E1, E2
	    	    E1_LM = h_E1.GetLocalMode();
	    	    E2_LM = h_E2.GetLocalMode();
	    	    E1_M = h_E1.GetHistogram()->GetMean();
	    	    E2_M = h_E2.GetHistogram()->GetMean();
	    	    E1_RMS = h_E1.GetHistogram()->GetRMS();
	    	    E2_RMS = h_E2.GetHistogram()->GetRMS();
	    	    
	    	    h_E1.GetHistogram()->GetQuantiles(7, E1_q, p);
	    	    E1_med = h_E1.GetQuantile(0.5);
	    	    E1_L68_sigma = E1_q[3] - E1_q[2];
		    E1_U68_sigma = E1_q[4] - E1_q[3];
	    	    E1_L68 = E1_med - E1_L68_sigma;
	    	    E1_U68 = E1_med + E1_U68_sigma;
	    	    
	    	    h_E2.GetHistogram()->GetQuantiles(7, E2_q, p);
	    	    E2_med = h_E2.GetQuantile(0.5);
	    	    E2_L68_sigma = E2_q[3] - E2_q[2];
		    E2_U68_sigma = E2_q[4] - E2_q[3];
	    	    E2_L68 = E2_med - E2_L68_sigma;
	    	    E2_U68 = E2_med + E2_U68_sigma;
	    }   
	    
	    // 90% Upper Limit
	    double E0_U90=0, p0_U90=0, p1_U90=0, p2_U90=0, E1_U90=0, E2_U90=0;
	    E0_U90 = h_E0.GetQuantile(0.90);
	    p0_U90 = h_p0.GetQuantile(0.90);
	    
	    if ( pol_degree==1 ) {
	    	    p1_U90 = h_p1.GetQuantile(0.90);
	    }
	    if ( pol_degree==2 ) {
	    	    p1_U90 = h_p1.GetQuantile(0.90);
	    	    p2_U90 = h_p2.GetQuantile(0.90);
	    }
	
	    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {}
   	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
	    	    E1_U90 = h_E1.GetQuantile(0.90);
	    }
	    else { 	    	    
	    	    E1_U90 = h_E1.GetQuantile(0.90);
	    	    E2_U90 = h_E2.GetQuantile(0.90);
	    }  
	      	    
	    std::vector<double> DblResults(54);
	    
	    // Local mode
	    DblResults.at(0) = E0_LM;
	    DblResults.at(1) = p0_LM;
	    DblResults.at(2) = p1_LM;
	    DblResults.at(3) = p2_LM;
	    DblResults.at(4) = E1_LM;
	    DblResults.at(5) = E2_LM;
	    
	    // Mean 
	    DblResults.at(6) = E0_M;
	    DblResults.at(7) = p0_M;
	    DblResults.at(8) = p1_M;
	    DblResults.at(9) = p2_M;
	    DblResults.at(10) = E1_M;
	    DblResults.at(11) = E2_M;
	    
	    // Sqrt(variance)
	    DblResults.at(12) = E0_RMS;
	    DblResults.at(13) = p0_RMS;
	    DblResults.at(14) = p1_RMS;
	    DblResults.at(15) = p2_RMS;
	    DblResults.at(16) = E1_RMS;
	    DblResults.at(17) = E2_RMS;
	    
	    // 68% Quantile
	    DblResults.at(18) = E0_L68;
	    DblResults.at(19) = E0_U68;
	    DblResults.at(20) = p0_L68;
	    DblResults.at(21) = p0_U68;
	    DblResults.at(22) = p1_L68;
	    DblResults.at(23) = p1_U68;
	    DblResults.at(24) = p2_L68;
	    DblResults.at(25) = p2_U68;
	    DblResults.at(26) = E1_L68;
	    DblResults.at(27) = E1_U68;
	    DblResults.at(28) = E2_L68;
	    DblResults.at(29) = E2_U68;
	    
	    // 90% Upper Limit
	    DblResults.at(30) = E0_U90;
	    DblResults.at(31) = p0_U90;
	    DblResults.at(32) = p1_U90;
	    DblResults.at(33) = p2_U90;
	    DblResults.at(34) = E1_U90;
	    DblResults.at(35) = E2_U90;
	    
	    // Median
	    DblResults.at(36) = E0_med;
	    DblResults.at(37) = p0_med;
	    DblResults.at(38) = p1_med;
	    DblResults.at(39) = p2_med;
	    DblResults.at(40) = E1_med;
	    DblResults.at(41) = E2_med;
	    DblResults.at(42) = E0_L68_sigma;
	    DblResults.at(43) = E0_U68_sigma;
	    DblResults.at(44) = p0_L68_sigma;
	    DblResults.at(45) = p0_U68_sigma;
	    DblResults.at(46) = p1_L68_sigma;
	    DblResults.at(47) = p1_U68_sigma;
	    DblResults.at(48) = p2_L68_sigma;
	    DblResults.at(49) = p2_U68_sigma;
	    DblResults.at(50) = E1_L68_sigma;
	    DblResults.at(51) = E1_U68_sigma;
	    DblResults.at(52) = E2_L68_sigma;
	    DblResults.at(53) = E2_U68_sigma;
	    
	    
	    return DblResults;
}
