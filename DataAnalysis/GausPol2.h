#include <BAT/BCModel.h>
#include <BAT/BCMath.h>
#include <BAT/BCMTF.h>
#include <BAT/BCDataSet.h>
#include <BAT/BCDataPoint.h>

#include <TFile.h>
#include <TMath.h>

#include <string>
#include <vector>

#include "Operations.h"



// ---------------------------------------------------------------------------------------------- Gaus + pol2
#ifndef __BAT__GAUSPOL2__H
#define __BAT__GAUSPOL2__H

class GausPol2 : public BCModel
{

public:

    // Constructor
    GausPol2(const std::string& name, std::vector<int> bin_content, int E0, int xL, int xR, double EG, int outputK);

    // Destructor
    ~GausPol2();

    // Overload LogLikelihood to implement model
    double LogLikelihood(const std::vector<double>& pars);

};
#endif
