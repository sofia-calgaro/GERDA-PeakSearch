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
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


#pragma once

    // Create a JSON file
    void JsonFile (const std::vector<double> params, const std::vector<double> params_err, int IntResults[], std::vector<double> DblResults);
        
    // Draw f(x) = pol0(x)+gaus(x)
    void Draw_Pol0(int E0, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol0(x)+gaus(x)+gaus_gamma(x)
    void Draw_Gamma_Pol0(int E0, double EG, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol0(x)+gaus(x)+gaus_gamma(x)+gaus_gamma_2(x)
    void Draw_TwoGamma_Pol0(int E0, double EG, double EG_2, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol1(x)+gaus(x)
    void Draw_Pol1(int E0, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol1(x)+gaus(x)+gaus_gamma(x)
    void Draw_Gamma_Pol1(int E0, double EG, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol1(x)+gaus(x)+gaus_gamma(x)+gaus_gamma_2(x)
    void Draw_TwoGamma_Pol1(int E0, double EG, double EG_2, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol2(x)+gaus(x)
    void Draw_Pol2(int E0, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol2(x)+gaus(x)+gaus_gamma(x)
    void Draw_Gamma_Pol2(int E0, double EG, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol2(x)+gaus(x)+gaus_gamma(x)+gaus_gamma_2(x)
    void Draw_TwoGamma_Pol2(int E0, double EG, double EG_2, int xL, int xR, const std::vector<double> params, TH1D *h); 
