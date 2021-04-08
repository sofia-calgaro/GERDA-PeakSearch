#ifndef __BAT__DATAANALYSIS__H
#define __BAT__DATAANALYSIS__H

#include <BAT/BCModel.h>
#include <BAT/BCMath.h>
#include <BAT/BCMTF.h>
#include <BAT/BCDataSet.h>
#include <BAT/BCDataPoint.h>

#include <TFile.h>
#include <TMath.h>

#include <string>
#include <vector>

// ---------------------------------------------------------------------- Gaus + pol0
class DataAnalysis : public BCModel
{

public:

    // Constructor
    DataAnalysis(const std::string& name, const std::vector<unsigned int> *bin_content, int E0);

    // Destructor
    ~DataAnalysis();

    // Overload LogLikelihood to implement model
    double LogLikelihood(const std::vector<double>& pars);

    // Overload LogAprioriProbability if not using built-in 1D priors
    // double LogAPrioriProbability(const std::vector<double> & pars);

    // Overload CalculateObservables if using observables
    // void CalculateObservables(const std::vector<double> & pars);

};

// ---------------------------------------------------------------------- Gaus + pol1
class GausPol1 : public BCModel
{

public:

    // Constructor
    GausPol1(const std::string& name);

    // Destructor
    ~GausPol1();

    // Overload LogLikelihood to implement model
    double LogLikelihood(const std::vector<double>& pars);

};

// ----------------------------------------------------------------------
#endif
