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
#ifndef __BAT__VectorModel__H
#define __BAT__VectorModel__H

class VectorModel : public BCModel
{

public:

    // Constructor
    VectorModel(const std::string& name, std::vector<double> bin_content, double *FitVariables, bool *peak);

    // Destructor
    ~VectorModel();

    // Overload LogLikelihood to implement model
    double LogLikelihood(const std::vector<double>& pars);

};
#endif
