#include <BAT/BCModel.h>
#include <BAT/BCMath.h>
#include <BAT/BCMTF.h>
#include <BAT/BCDataSet.h>
#include <BAT/BCDataPoint.h>

#include <TFile.h>
#include <TMath.h>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Operations.h"

#include </home/sofia/Software/json/single_include/nlohmann/json.hpp>
using json = nlohmann::json;


// ---------------------------------------------------------------------------------------------- Gaus + pol1
#ifndef __BAT__PseudoscalarModel__H
#define __BAT__PseudoscalarModel__H

class PseudoscalarModel : public BCModel
{

public:

    // Constructor
    PseudoscalarModel(const std::string& name, std::vector<double> bin_content, double *FitVariables, bool *peak);

    // Destructor
    ~PseudoscalarModel();

    // Overload LogLikelihood to implement model
    double LogLikelihood(const std::vector<double>& pars);

};
#endif
