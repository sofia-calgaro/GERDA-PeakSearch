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



// ---------------------------------------------------------------------------------------------- Gaus + pol1
#ifndef __BAT__GAUSPOL1__H
#define __BAT__GAUSPOL1__H

class GausPol1 : public BCModel
{

public:

    // Constructor
    GausPol1(const std::string& name, std::vector<int> bin_content, int E0, int xL, int xR, double E1, double E2, int outputK, int *rng);

    // Destructor
    ~GausPol1();

    // Overload LogLikelihood to implement model
    double LogLikelihood(const std::vector<double>& pars);

};
#endif
