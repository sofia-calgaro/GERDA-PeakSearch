#include "GausPol0.h"
#include "Operations.h"



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol0::GausPol0(const std::string& name, std::vector<int> bin_content, int E0)
    : BCModel(name)
{
 	    int *output = FindMaximumSignalHeight( E0, bin_content);
 	    double *output_pol0 = FindRangeOfBKGParameters_Pol0( E0, bin_content, output);
	
            // 1) Signal yield (index 0)
            AddParameter("height", 0, output[3], "", "[events]");
            GetParameters().Back().SetPriorConstant();

            // 2) Constant (index 1)
            AddParameter("p0", output_pol0[0]-10*output_pol0[1], output_pol0[0]+10*output_pol0[1], "p0", "[events]");
            GetParameters().Back().SetPriorConstant();
}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
GausPol0::~GausPol0() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double GausPol0::LogLikelihood(const std::vector<double>& pars)
{

            double LP = 0.;
            
            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int x1 = E0-12;
            int x2 = E0+12;

            double sigma_E0 = FindSigma(E0);

            // Loop over 24 elements
            for ( int i=x1; i<x2-1; i++ ) {
		    
                    int y_obs =  GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )

                    double y_exp =  pars[0] * TMath::Gaus(i, E0, sigma_E0, false) + pars[1]; // expected value

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
}
