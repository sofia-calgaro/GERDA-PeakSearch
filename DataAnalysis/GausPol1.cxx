#include "GausPol1.h"
#include "Operations.h"
#include <TMath.h>



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol1::GausPol1(const std::string& name, const std::vector<unsigned int> *bin_content, int E0)
    : BCModel(name)
{

	    int max = FindMaximumSignalHeight( E0, bin_content);        

            // 1) Signal yield (index 0)
            AddParameter("height", 0, 10e4, "", "[events]");
            GetParameters().Back().SetPriorConstant();

            // 2) Constant (index 1)
            AddParameter("p0", 0, 10e4, "p0", "[events]");
            GetParameters().Back().SetPriorConstant();
            
            // 3) Slope (index 2)
            AddParameter("p1", -1, 0, "p1", "[events/keV]");
            GetParameters().Back().SetPriorConstant();
}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
GausPol1::~GausPol1() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double GausPol1::LogLikelihood(const std::vector<double>& pars)
{

            double LP = 0.;
            
            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int x1 = E0-12;
            int x2 = E0+12;

            double sigma_E0 = FindSigma(E0);

            // Loop over 24 elements
            for ( int i=x1; i<x2-1; i++ ) {
		    
                    int y_obs =  GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )

                    double y_exp =  pars[0] * TMath::Gaus(i, E0, sigma_E0, false) + pars[1] + pars[2]*(i-E0); // expected value

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }

            return LP;
 }	    
