#include "GausPol0.h"
#include "Operations.h"



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol0::GausPol0(const std::string& name, std::vector<int> bin_content, int E0, int xL, int xR, double E1, double E2, int outputK)
    : BCModel(name)
{
	    int *max_height = FindMaximumSignalHeight( E0, E1, E2, bin_content, xL, xR, outputK);
	    
	    if ( outputK==0 || outputK==1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {
		    double *output_pol0 = FindRange_Pol0( E0, bin_content, max_height, xL, xR);
		    
		    // 1) Signal yield (index 0)
		    AddParameter("S_height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    AddParameter("p0", output_pol0[0]-10*output_pol0[1], output_pol0[0]+10*output_pol0[1], "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
            }
            
            else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) {
		    int *max_gammaYield = FindMaximumGammaHeight1( E0, E1, E2, bin_content, xL, xR, outputK);
		    double *output_G_pol0 = FindRange_Gamma_Pol0( E0, bin_content, max_height, E1, max_gammaYield, xL, xR);
		    
		    // 1) Signal yield (index 0)
		    AddParameter("S_height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    AddParameter("p0", output_G_pol0[0]-10*output_G_pol0[1], output_G_pol0[0]+10*output_G_pol0[1], "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();  
		    
		    // 3) Gamma yield (index 2)  
		    AddParameter("E1_height", 0, max_gammaYield[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();        
            } 
            
            else {
            	    int *max_gammaYield1 = FindMaximumSignalHeight( E0, E1, E2, bin_content, xL, xR, outputK);
            	    int *max_gammaYield2 = FindMaximumSignalHeight( E0, E1, E2, bin_content, xL, xR, outputK);
		    double *output_2G_pol0 = FindRange_TwoGamma_Pol0( E0, bin_content, max_height, E1, max_gammaYield1, E2, max_gammaYield1, xL, xR);
		    
		    // 1) Signal yield (index 0)
		    AddParameter("S_height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    AddParameter("p0", output_2G_pol0[0]-10*output_2G_pol0[1], output_2G_pol0[0]+10*output_2G_pol0[1], "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();  
		    
		    // 3) Gamma yield (1) (index 2)  
		    AddParameter("E1_height", 0, max_gammaYield1[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Gamma yield (2) (index 3)  
		    AddParameter("E2_height", 0, max_gammaYield2[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();     
            }
}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
GausPol0::~GausPol0() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double GausPol0::LogLikelihood(const std::vector<double>& pars)
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
                    if ( outputK==0 || outputK==1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) { y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1]; }
                    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) {
                    	double E1 = GetDataSet()->GetDataPoint(5204).GetValue(0);
                    	y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*TMath::Gaus(i, E1, FindSigma(E1), true);
                    }
                    else { 
                        double E1 = GetDataSet()->GetDataPoint(5204).GetValue(0);
                    	double E2 = GetDataSet()->GetDataPoint(5206).GetValue(0);
                    	y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*TMath::Gaus(i, E1, FindSigma(E1), true) + pars[3]*TMath::Gaus(i, E2, FindSigma(E2), true);
                    }

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
}
