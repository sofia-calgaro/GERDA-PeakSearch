#include "GausPol2.h"
#include "Operations.h"



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol2::GausPol2(const std::string& name, std::vector<int> bin_content, int E0, int xL, int xR, double E1, double E2, int outputK, int *rng)
    : BCModel(name)
{
	    int *max_height = FindMaximumSignalHeight( E0, E1, E2, bin_content, xL, xR, outputK);
	    double min_p0=0, max_p0=0, min_p1=0, max_p1=0, min_p2=0, max_p2=0;
	    
	    if ( outputK<=1 || outputK==4 || outputK==7 || (outputK>=13 && outputK<=15) || outputK==18 || outputK>=20 ) {
	 	    double *output_pol2 = FindRange_Pol2( E0, bin_content, max_height);
		
		    // 1) Signal yield (index 0)
		    AddParameter("E0_height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    if ( rng[0]==0 ) {
		    	min_p0 = output_pol2[0]-10*output_pol2[1];
		    	max_p0 = output_pol2[0]+10*output_pol2[1];
		    }
		    if ( rng[0]==1 ) {
		    	min_p0 = output_pol2[0]-15*output_pol2[1];
		    	max_p0 = output_pol2[0]+15*output_pol2[1];
		    }
		    if ( rng[0]==2 ) {
		    	min_p0 = output_pol2[0]-20*output_pol2[1];
		    	max_p0 = output_pol2[0]+20*output_pol2[1];
		    }
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    if ( rng[1]==0 ) {
		    	min_p1 = output_pol2[2]-10*output_pol2[3];
		    	max_p1 = output_pol2[2]+10*output_pol2[3];
		    }
		    if ( rng[1]==1 ) {
		    	min_p1 = output_pol2[2]-15*output_pol2[3];
		    	max_p1 = output_pol2[2]+15*output_pol2[3];
		    }
		    if ( rng[1]==2 ) {
		    	min_p1 = output_pol2[2]-20*output_pol2[3];
		    	max_p1 = output_pol2[2]+20*output_pol2[3];
		    }
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Quadratic term (index 3)
		    if ( rng[2]==0 ) {
		    	min_p2 = output_pol2[4]-10*output_pol2[5];
		    	max_p2 = output_pol2[4]+10*output_pol2[5];
		    }
		    if ( rng[2]==1 ) {
		    	min_p2 = output_pol2[4]-15*output_pol2[5];
		    	max_p2 = output_pol2[4]+15*output_pol2[5];
		    }
		    if ( rng[2]==2 ) {
		    	min_p2 = output_pol2[4]-20*output_pol2[5];
		    	max_p2 = output_pol2[4]+20*output_pol2[5];
		    }
		    if ( rng[2]==3 ) {
		    	min_p2 = output_pol2[4]-25*output_pol2[5];
		    	max_p2 = output_pol2[4]+25*output_pol2[5];
		    }
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
		    if ( rng[0]==0 ) {
		    	min_p0 = output_G_pol2[0]-10*output_G_pol2[1];
		    	max_p0 = output_G_pol2[0]+10*output_G_pol2[1];
		    }
		    if ( rng[0]==1 ) {
		    	min_p0 = output_G_pol2[0]-15*output_G_pol2[1];
		    	max_p0 = output_G_pol2[0]+15*output_G_pol2[1];
		    }
		    if ( rng[0]==2 ) {
		    	min_p0 = output_G_pol2[0]-20*output_G_pol2[1];
		    	max_p0 = output_G_pol2[0]+20*output_G_pol2[1];
		    }
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    if ( rng[1]==0 ) {
		    	min_p1 = output_G_pol2[2]-10*output_G_pol2[3];
		    	max_p1 = output_G_pol2[2]+10*output_G_pol2[3];
		    }
		    if ( rng[1]==1 ) {
		    	min_p1 = output_G_pol2[2]-15*output_G_pol2[3];
		    	max_p1 = output_G_pol2[2]+15*output_G_pol2[3];
		    }
		    if ( rng[1]==2 ) {
		    	min_p1 = output_G_pol2[2]-20*output_G_pol2[3];
		    	max_p1 = output_G_pol2[2]+20*output_G_pol2[3];
		    }
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Quadratic term (index 3)
		    if ( rng[2]==0 ) {
		    	min_p2 = output_G_pol2[4]-10*output_G_pol2[5];
		    	max_p2 = output_G_pol2[4]+10*output_G_pol2[5];
		    }
		    if ( rng[2]==1 ) {
		    	min_p2 = output_G_pol2[4]-15*output_G_pol2[5];
		    	max_p2 = output_G_pol2[4]+15*output_G_pol2[5];
		    }
		    if ( rng[2]==2 ) {
		    	min_p2 = output_G_pol2[4]-20*output_G_pol2[5];
		    	max_p2 = output_G_pol2[4]+20*output_G_pol2[5];
		    }
		    if ( rng[2]==3 ) {
		    	min_p2 = output_G_pol2[4]-25*output_G_pol2[5];
		    	max_p2 = output_G_pol2[4]+25*output_G_pol2[5];
		    }
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
		    if ( rng[0]==0 ) {
		    	min_p0 = output_2G_pol2[0]-10*output_2G_pol2[1];
		    	max_p0 = output_2G_pol2[0]+10*output_2G_pol2[1];
		    }
		    if ( rng[0]==1 ) {
		    	min_p0 = output_2G_pol2[0]-15*output_2G_pol2[1];
		    	max_p0 = output_2G_pol2[0]+15*output_2G_pol2[1];
		    }
		    if ( rng[0]==2 ) {
		    	min_p0 = output_2G_pol2[0]-20*output_2G_pol2[1];
		    	max_p0 = output_2G_pol2[0]+20*output_2G_pol2[1];
		    }
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    if ( rng[1]==0 ) {
		    	min_p1 = output_2G_pol2[2]-10*output_2G_pol2[3];
		    	max_p1 = output_2G_pol2[2]+10*output_2G_pol2[3];
		    }
		    if ( rng[1]==1 ) {
		    	min_p1 = output_2G_pol2[2]-15*output_2G_pol2[3];
		    	max_p1 = output_2G_pol2[2]+15*output_2G_pol2[3];
		    }
		    if ( rng[1]==2 ) {
		    	min_p1 = output_2G_pol2[2]-20*output_2G_pol2[3];
		    	max_p1 = output_2G_pol2[2]+20*output_2G_pol2[3];
		    }
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Quadratic term (index 3)
		    if ( rng[2]==0 ) {
		    	min_p2 = output_2G_pol2[4]-10*output_2G_pol2[5];
		    	max_p2 = output_2G_pol2[4]+10*output_2G_pol2[5];
		    }
		    if ( rng[2]==1 ) {
		    	min_p2 = output_2G_pol2[4]-15*output_2G_pol2[5];
		    	max_p2 = output_2G_pol2[4]+15*output_2G_pol2[5];
		    }
		    if ( rng[2]==2 ) {
		    	min_p2 = output_2G_pol2[4]-20*output_2G_pol2[5];
		    	max_p2 = output_2G_pol2[4]+20*output_2G_pol2[5];
		    }
		    if ( rng[2]==3 ) {
		    	min_p2 = output_2G_pol2[4]-25*output_2G_pol2[5];
		    	max_p2 = output_2G_pol2[4]+25*output_2G_pol2[5];
		    }
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
