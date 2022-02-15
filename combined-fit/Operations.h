#include <BAT/BCModel.h>
#include <BAT/BCMath.h>
#include <BAT/BCMTF.h>
#include <BAT/BCDataSet.h>
#include <BAT/BCDataPoint.h>

#include <TFile.h>
#include <TMath.h>
#include <TF1.h>
#include <TH1D.h>
#include <TCanvas.h>

#include <string>
#include <vector>

#include </home/sofia/Software/json/single_include/nlohmann/json.hpp>
using json = nlohmann::json;


#pragma once

    // Calculates the number of rows in a file
    Int_t NumberOfRows(char *filename);
    
    // Returns 'true' only if b > a
    bool FindMax(int a, int b); 
    
    // Calculates the energetic resolution for a given energy value 
    double FindSigma(int energy, int k); 
    
    // Calculates the FWHM for a given energy value
    double FindFWHM(int energy, int k); 
    
    // Calculates the maximum of the signal height parameter
    double *FindMaximumSignalHeight(int E0); 
    
    // Calculates the maximum of the 1st gamma height parameter
    int *FindMaximumGammaHeight1(int E0, double E1, double E2, std::vector<double> bin_content, int xL, int xR, int outputK, int k);
    
    // Calculates the maximum of the 2nd gamma height parameter
    int *FindMaximumGammaHeight2(int E0, double E1, double E2, std::vector<double> bin_content, int xL, int xR, int outputK, int k);
    
    // Find the range in which the BKG-Pol0 parameters of the models vary
    double *FindRange_Pol0(int E0, std::vector<double> bin_content, double *max_height, int xL, int xR, int k);
    
    // Find the range in which the BKG-Pol1 parameters of the models vary
    double *FindRange_Pol1(int E0, std::vector<double> bin_content, double *max_height, int k);
    
    // Find the range in which the BKG-Pol2 parameters of the models vary
    double *FindRange_Pol2(int E0, std::vector<double> bin_content, double *max_height, int k);
    
    // Find the range in which the BKG-Pol0 parameters of the models vary (1 gamma peak)
    double *FindRange_Gamma_Pol0(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield, int xL, int xR, int k);
    
    // Find the range in which the BKG-Pol1 parameters of the models vary (1 gamma peak)
    double *FindRange_Gamma_Pol1(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield, int xL, int xR, int k);
    
    // Find the range in which the BKG-Pol2 parameters of the models vary (1 gamma peak)
    double *FindRange_Gamma_Pol2(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield, int xL, int xR, int k);
    
    // Find the range in which the BKG-Pol0 parameters of the models vary (2 gamma peaks)
    double *FindRange_TwoGamma_Pol0(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR, int k);
    
    // Find the range in which the BKG-Pol1 parameters of the models vary (2 gamma peaks)
    double *FindRange_TwoGamma_Pol1(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR, int k);
    
    // Find the range in which the BKG-Pol2 parameters of the models vary (2 gamma peaks)
    double *FindRange_TwoGamma_Pol2(int E0, std::vector<double> bin_content, double *max_height, double E1, int *max_gammaYield1, double E2, int *max_gammaYield2, int xL, int xR, int k);
    
    // Create a JSON file
    void JsonFile (const std::vector<double> params, const std::vector<double> params_err, double *FitVariables, std::vector<double> DblResults);
    
    // Create an array with fit (BAT) results for given marginalized distributions
    std::vector<double> BATResults (int outputK, int pol_degree, BCH1D h_E0, BCH1D h_p0, BCH1D h_p1, BCH1D h_p2, BCH1D h_E1, BCH1D h_E2);
    
     
