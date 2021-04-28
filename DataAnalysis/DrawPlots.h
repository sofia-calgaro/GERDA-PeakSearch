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


#pragma once


    // Draw f(x) = pol0(x)+gaus(x)
    void Draw_Pol0(int energy, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol0(x)+gaus(x)+gaus_gamma(x)
    void Draw_Gamma_Pol0(int energy, double EG, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol1(x)+gaus(x)
    void Draw_Pol1(int energy, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol1(x)+gaus(x)+gaus_gamma(x)
    void Draw_Gamma_Pol1(int energy, double EG, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol2(x)+gaus(x)
    void Draw_Pol2(int energy, int xL, int xR, const std::vector<double> params, TH1D *h); 
    
    // Draw f(x) = pol2(x)+gaus(x)+gaus_gamma(x)
    void Draw_Gamma_Pol2(int energy, double EG, int xL, int xR, const std::vector<double> params, TH1D *h); 
