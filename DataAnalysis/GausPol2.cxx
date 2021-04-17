#include "GausPol2.h"
#include "Operations.h"



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol2::GausPol2(const std::string& name, std::vector<int> bin_content, int E0)
    : BCModel(name)
{
 	    int *output = FindMaximumSignalHeight( E0, bin_content);
 	    double *output_pol2 = FindRangeOfBKGParameters_Pol2( E0, bin_content, output);
	
            // 1) Signal yield (index 0)
            AddParameter("height", 0, output[3], "", "[events]");
            GetParameters().Back().SetPriorConstant();

            // 2) Constant (index 1)
            AddParameter("p0", output_pol2[0]-10*output_pol2[1], output_pol2[0]+10*output_pol2[1], "p0", "[events]");
            //AddParameter("p0", 0, 80, "p0", "[events]");
            GetParameters().Back().SetPriorConstant();
            
            // 3) Slope (index 2)
            AddParameter("p1", output_pol2[2]-10*output_pol2[3], output_pol2[2]+10*output_pol2[3], "p1", "[events/keV]");
            //AddParameter("p1", 0, 80, "p1", "[events/keV]");
            GetParameters().Back().SetPriorConstant();
            
            // 4) Quadratic term (index 3)
            AddParameter("p2", output_pol2[4]-10*output_pol2[5], output_pol2[4]+10*output_pol2[5], "p2", "[events/keV^2]");
            GetParameters().Back().SetPriorConstant();
}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
GausPol2::~GausPol2() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double GausPol2::LogLikelihood(const std::vector<double>& pars)
{

            double LP = 0.;
            
            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int x1 = E0-12;
            int x2 = E0+12;

            double sigma_E0 = FindSigma(E0);

            // Loop over 24 elements
            for ( int i=x1; i<x2-1; i++ ) {
		    
                    int y_obs =  GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )

                    double y_exp =  pars[0] * TMath::Gaus(i, E0, sigma_E0, true) + pars[1] + pars[2]*(i-E0) + pars[3]*(i-E0)*(i-E0); // expected value

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
}
