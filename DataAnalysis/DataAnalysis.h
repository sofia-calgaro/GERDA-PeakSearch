// ***************************************************************
// This file was created using the bat-project script.
// bat-project is part of Bayesian Analysis Toolkit (BAT).
// BAT can be downloaded from http://mpp.mpg.de/bat
// ***************************************************************

#ifndef __BAT__DATAANALYSIS__H
#define __BAT__DATAANALYSIS__H

#include <BAT/BCModel.h>
#include <BAT/BCMath.h>

#include <string>
#include <vector>

// This is a DataAnalysis header file.
// Model source code is located in file DataAnalysis/DataAnalysis.cxx

// ---------------------------------------------------------
class DataAnalysis : public BCModel
{

public:

    // Constructor
    DataAnalysis(const std::string& name);

    // Destructor
    ~DataAnalysis();

    // Overload LogLikelihood to implement model
    double LogLikelihood(const std::vector<double>& pars);

    // Overload LogAprioriProbability if not using built-in 1D priors
    // double LogAPrioriProbability(const std::vector<double> & pars);

    // Overload CalculateObservables if using observables
    // void CalculateObservables(const std::vector<double> & pars);

};

#endif
