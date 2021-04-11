#include <BAT/BCModel.h>
#include <BAT/BCMath.h>
#include <BAT/BCMTF.h>
#include <BAT/BCDataSet.h>
#include <BAT/BCDataPoint.h>

#include <TFile.h>
#include <TMath.h>

#include <string>
#include <vector>


#pragma once


    // Returns 'true' only if b > a
    bool FindMax(int a, int b); 
    
    // Calculates the energetic resolution for a given energy value 
    double FindSigma(int energy); 
    
    // Calculates the FWHM for a given energy value
    double FindFWHM(int energy); 
    
    // Calculates the maximum of the signal height paramter
    int FindMaximumSignalHeight(int energy, const std::vector<unsigned int> *bin_signal); 
    
    // Find the new edges x1_new, x2_new in case a gamma peak is present in proximity of the fit window
    //int FindNewEdges(int i_min, int i_max, int *x1_new, int *x2_new);
    
