#include <BAT/BCModel.h>
#include <BAT/BCMath.h>
#include <BAT/BCMTF.h>
#include <BAT/BCDataSet.h>
#include <BAT/BCDataPoint.h>

#include <TFile.h>
#include <TMath.h>
#include <TF1.h>
#include <TH1D.h>

#include <string>
#include <vector>


#pragma once


    // Returns 'true' only if b > a
    bool FindMax(int a, int b); 
    
    // Calculates the energetic resolution for a given energy value 
    double FindSigma(int energy); 
    
    // Calculates the FWHM for a given energy value
    double FindFWHM(int energy); 
    
    // Calculates the maximum of the signal height parameter
    int *FindMaximumSignalHeight(int energy, std::vector<int> bin_signal); 
    
    // Find the range in which the BKG-Pol0 parameters of the models vary
    double *FindRangeOfBKGParameters_Pol0(int energy, std::vector<int> bin_content, int *output);
    
    // Find the range in which the BKG-Pol1 parameters of the models vary
    double *FindRangeOfBKGParameters_Pol1(int energy, std::vector<int> bin_content, int *output);
    
    // Find the range in which the BKG-Pol2 parameters of the models vary
    double *FindRangeOfBKGParameters_Pol2(int energy, std::vector<int> bin_content, int *output);
