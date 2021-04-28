#include "GausPol1.h"
#include "Operations.h"
#include <TMath.h>



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol1::GausPol1(const std::string& name, std::vector<int> bin_content, int E0, int xL, int xR, double EG, int outputK)
    : BCModel(name)
{
	    int *max_height = FindMaximumSignalHeight( E0, bin_content);
	    
	    if ( outputK==50 || outputK==1 || outputK==4 || outputK==7 || outputK==15 || outputK==18 || outputK==20 || outputK==21 || outputK==22 ) {
		    double *output_pol1 = FindRange_Pol1( E0, bin_content, max_height);
		    
		    // 1) Signal yield (index 0)
		    AddParameter("height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    AddParameter("p0", output_pol1[0]-10*output_pol1[1], output_pol1[0]+10*output_pol1[1], "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    AddParameter("p1", output_pol1[2]-10*output_pol1[3], output_pol1[2]+10*output_pol1[3], "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
            }
            
            else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) {
		    int *max_gammaYield = FindMaximumSignalHeight( EG, bin_content);
		    double *output_G_pol1 = FindRange_Gamma_Pol1( E0, bin_content, max_height, EG, max_gammaYield);
		    
		    // 1) Signal yield (index 0)
		    AddParameter("height", 0, max_height[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    AddParameter("p0", output_G_pol1[0]-10*output_G_pol1[1], output_G_pol1[0]+10*output_G_pol1[1], "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();  
		    
		    // 3) Slope (index 2)
		    AddParameter("p1", output_G_pol1[2]-10*output_G_pol1[3], output_G_pol1[2]+10*output_G_pol1[3], "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Gamma yield (index 3)  
		    AddParameter("gamma_height", 0, max_gammaYield[3], "", "[events]");
		    GetParameters().Back().SetPriorConstant();        
            } 
            
            else {
            	   // studio dei picchi che distano meno di 24 keV					//!!!!!!!!!!!!!!!!!!
            }

}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
GausPol1::~GausPol1() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double GausPol1::LogLikelihood(const std::vector<double>& pars)
{

            double LP = 0.;
            
            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int xL = GetDataSet()->GetDataPoint(5202).GetValue(0);
            int xR = GetDataSet()->GetDataPoint(5203).GetValue(0);
            double EG = GetDataSet()->GetDataPoint(5204).GetValue(0);
            int outputK = GetDataSet()->GetDataPoint(5205).GetValue(0);

            // Loop over 24 elements
            for ( int i=xL; i<xR; i++ ) {
		    
                    int y_obs =  GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )
                    double y_exp = 0;
                    
                    // expected value
                    if ( outputK==50 || outputK==1 || outputK==4 || outputK==7 || outputK==15 || outputK==18 || outputK==20 || outputK==21 || outputK==22 ) { y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*(i-E0); }
                    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 ) { y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*(i-E0) + pars[3]*TMath::Gaus(i, EG, FindSigma(EG), true); }
                    else {}

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
 }	    
