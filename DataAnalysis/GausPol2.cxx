#include "GausPol2.h"
#include "Operations.h"



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol2::GausPol2(const std::string& name, std::vector<int> bin_content, int E0, int xL, int xR, double E1, double E2, int outputK, int *rng)
    : BCModel(name)
{
	    int *max_height = FindMaximumSignalHeight( E0, E1, E2, bin_content, xL, xR, outputK);
	    double min_p0=0, max_p0=0, min_p1=0, max_p1=0, min_p2=0, max_p2=0;
	    
	    int i=0; // constant
	    if ( rng[0]==0 ) { i=10; }
	    if ( rng[0]==1 ) { i=15; }
	    if ( rng[0]==2 ) { i=20; }
	    if ( rng[0]==3 ) { i=25; }
	    if ( rng[0]==4 ) { i=30; }
	    if ( rng[0]==5 ) { i=40; }
	    if ( rng[0]==6 ) { i=50; }
	    if ( rng[0]==7 ) { i=60; }
	    if ( rng[0]==8 ) { i=70; }
	    if ( rng[0]==9 ) { i=80; }
	    if ( rng[0]==10 ) { i=90; }
	    if ( rng[0]==11 ) { i=100; }
	    int j=0; // slope
	    if ( rng[1]==0 ) { j=10; }
	    if ( rng[1]==1 ) { j=15; }
	    if ( rng[1]==2 ) { j=20; }
	    if ( rng[1]==3 ) { j=25; }
	    if ( rng[1]==4 ) { j=30; }
	    if ( rng[1]==5 ) { j=40; }
	    if ( rng[1]==6 ) { j=50; }
	    if ( rng[1]==7 ) { j=60; }
	    if ( rng[1]==8 ) { j=70; }
	    if ( rng[1]==9 ) { j=80; }
	    if ( rng[1]==10 ) { j=90; }
	    if ( rng[1]==11 ) { j=100; }
	    int l=0; // curvature
	    if ( rng[2]==0 ) { l=10; }
	    if ( rng[2]==1 ) { l=15; }
	    if ( rng[2]==2 ) { l=20; }
	    if ( rng[2]==3 ) { l=25; }
	    if ( rng[2]==4 ) { l=30; }
	    if ( rng[2]==5 ) { l=40; }
	    if ( rng[2]==6 ) { l=50; }
	    if ( rng[2]==7 ) { l=60; }
	    if ( rng[2]==8 ) { l=70; }
	    if ( rng[2]==9 ) { l=80; }
	    if ( rng[2]==10 ) { l=90; }
	    if ( rng[2]==11 ) { l=100; }
	    
	    if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
	 	    double *output_pol2 = FindRange_Pol2( E0, bin_content, max_height);
		
		    // 1) Signal yield (index 0)
		    AddParameter("E0_height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    min_p0 = output_pol2[0]-i*output_pol2[1];
		    max_p0 = output_pol2[0]+i*output_pol2[1];
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    min_p1 = output_pol2[2]-j*output_pol2[3];
		    max_p1 = output_pol2[2]+j*output_pol2[3];
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Quadratic term (index 3)
		    min_p2 = output_pol2[4]-l*output_pol2[5];
		    max_p2 = output_pol2[4]+l*output_pol2[5];
		    AddParameter("p2", min_p2, max_p2, "p2", "[events/keV^2]");
		    GetParameters().Back().SetPriorConstant();
            }
            
            else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
		    int *max_gammaYield = FindMaximumGammaHeight1( E0, E1, E2, bin_content, xL, xR, outputK);
		    double *output_G_pol2 = FindRange_Gamma_Pol2( E0, bin_content, max_height, E1, max_gammaYield, xL, xR);
		    
		    // 1) Signal yield (index 0)
		    AddParameter("E0_height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    min_p0 = output_G_pol2[0]-i*output_G_pol2[1];
		    max_p0 = output_G_pol2[0]+i*output_G_pol2[1];
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    min_p1 = output_G_pol2[2]-j*output_G_pol2[3];
		    max_p1 = output_G_pol2[2]+j*output_G_pol2[3];
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Quadratic term (index 3)
		    min_p2 = output_G_pol2[4]-l*output_G_pol2[5];
		    max_p2 = output_G_pol2[4]+l*output_G_pol2[5];
		    AddParameter("p2", min_p2, max_p2, "p2", "[events/keV^2]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 5) Gamma yield (index 4)  
		    AddParameter("E1_height", 0, max_gammaYield[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();        
            } 
            
            else {
            	    int *max_gammaYield1 = FindMaximumGammaHeight1( E0, E1, E2, bin_content, xL, xR, outputK);
            	    int *max_gammaYield2 = FindMaximumGammaHeight2( E0, E1, E2, bin_content, xL, xR, outputK);
		    double *output_2G_pol2 = FindRange_TwoGamma_Pol2( E0, bin_content, max_height, E1, max_gammaYield1, E2, max_gammaYield2, xL, xR);
            	   
            	    // 1) Signal yield (index 0)
		    AddParameter("E0_height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    min_p0 = output_2G_pol2[0]-i*output_2G_pol2[1];
		    max_p0 = output_2G_pol2[0]+i*output_2G_pol2[1];
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    min_p1 = output_2G_pol2[2]-j*output_2G_pol2[3];
		    max_p1 = output_2G_pol2[2]+j*output_2G_pol2[3];
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Quadratic term (index 3)
		    min_p2 = output_2G_pol2[4]-l*output_2G_pol2[5];
		    max_p2 = output_2G_pol2[4]+l*output_2G_pol2[5];
		    AddParameter("p2", min_p2, max_p2, "p2", "[events/keV^2]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 5) Gamma yield (1) (index 4)  
		    AddParameter("E1_height", 0, max_gammaYield1[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 6) Gamma yield (2) (index 5)  
		    AddParameter("E2_height", 0, max_gammaYield2[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();
            }
       
}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
GausPol2::~GausPol2() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double GausPol2::LogLikelihood(const std::vector<double>& pars)
{

            double LP = 0.;
            
            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int xL = GetDataSet()->GetDataPoint(5202).GetValue(0);
            int xR = GetDataSet()->GetDataPoint(5203).GetValue(0);
            int outputK = GetDataSet()->GetDataPoint(5205).GetValue(0);

            // Loop over 24 elements
            for ( int i=xL; i<xR; i++ ) {
		    
                    int y_obs =  GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )
                    double y_exp = 0;
                    
                    // expected value
                    if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
                    	y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*(i-E0) + pars[3]*(i-E0)*(i-E0);
                    }
                    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { 
                    	double E1 = GetDataSet()->GetDataPoint(5204).GetValue(0);
                        y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*(i-E0) + pars[3]*(i-E0)*(i-E0) + pars[4]*TMath::Gaus(i, E1, FindSigma(E1), true);
                    }
                    else { 
                    	double E1 = GetDataSet()->GetDataPoint(5204).GetValue(0);
                   	double E2 = GetDataSet()->GetDataPoint(5206).GetValue(0);
                    	y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*(i-E0) + pars[3]*(i-E0)*(i-E0) + pars[4]*TMath::Gaus(i, E1, FindSigma(E1), true) + pars[5]*TMath::Gaus(i, E2, FindSigma(E2), true);
                    }

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
}
