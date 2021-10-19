#include "GausPol1.h"
#include "Operations.h"
#include <TMath.h>
#include <BAT/BCTH1Prior.h>



// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
GausPol1::GausPol1(const std::string& name, std::vector<double> bin_content, int E0, int xL, int xR, double E1, double E2, int outputK, int *rng)
    : BCModel(name)
{
	    int *max_height = FindMaximumSignalHeight( E0, E1, E2, bin_content, xL, xR, outputK);
	    double min_p0=0, max_p0=0, min_p1=0, max_p1=0;
	    
	    int i=0; // constant
	    if ( rng[0]==0 ) { i=7; }
	    if ( rng[0]==1 ) { i=8; }
	    if ( rng[0]==2 ) { i=9; }
	    if ( rng[0]==3 ) { i=10; }
	    if ( rng[0]==4 ) { i=20; }
	    if ( rng[0]==5 ) { i=30; }
	    if ( rng[0]==6 ) { i=40; }
	    if ( rng[0]==7 ) { i=50; }
	    if ( rng[0]==8 ) { i=60; }
	    if ( rng[0]==9 ) { i=70; }
	    if ( rng[0]==10 ) { i=80; }
	    if ( rng[0]==11 ) { i=90; }
	    if ( rng[0]==12 ) { i=100; }
	    if ( rng[0]==13 ) { i=110; }
	    if ( rng[0]==14 ) { i=120; }
	    if ( rng[0]==15 ) { i=130; }
	    if ( rng[0]==16 ) { i=140; }
	    int j=0; // slope
	    if ( rng[1]==0 ) { j=7; }
	    if ( rng[1]==1 ) { j=8; }
	    if ( rng[1]==2 ) { j=9; }
	    if ( rng[1]==3 ) { j=10; }
	    if ( rng[1]==4 ) { j=20; }
	    if ( rng[1]==5 ) { j=30; }
	    if ( rng[1]==6 ) { j=40; }
	    if ( rng[1]==7 ) { j=50; }
	    if ( rng[1]==8 ) { j=60; }
	    if ( rng[1]==9 ) { j=70; }
	    if ( rng[1]==10 ) { j=80; }
	    if ( rng[1]==11 ) { j=90; }
	    if ( rng[1]==12 ) { j=100; }
	    if ( rng[1]==13 ) { j=110; }
	    if ( rng[1]==14 ) { j=120; }
	    if ( rng[1]==15 ) { j=130; }
	    if ( rng[1]==16 ) { j=140; }
	    
	    int xE0=0; // E0
	    if ( rng[3]==0 ) { xE0=0; }
	    if ( rng[3]==1 ) { xE0=25; }
	    if ( rng[3]==2 ) { xE0=50; }
	    if ( rng[3]==3 ) { xE0=75; }
	    if ( rng[3]==4 ) { xE0=100; }
	    if ( rng[3]==5 ) { xE0=125; }
	    if ( rng[3]==6 ) { xE0=150; }
	    if ( rng[3]==7 ) { xE0=175; }
	    if ( rng[3]==8 ) { xE0=200; }
	    if ( rng[3]==9 ) { xE0=225; }
	    if ( rng[3]==10 ) { xE0=250; }
	    if ( rng[3]==11 ) { xE0=275; }
	    
	    int xE1; // E1
	    if ( rng[4]==0 ) { xE1=0; }
	    if ( rng[4]==1 ) { xE1=25; }
	    if ( rng[4]==2 ) { xE1=50; }
	    if ( rng[4]==3 ) { xE1=75; }
	    if ( rng[4]==4 ) { xE1=100; }
	    if ( rng[4]==5 ) { xE1=125; }
	    if ( rng[4]==6 ) { xE1=150; }
	    if ( rng[4]==7 ) { xE1=175; }
	    if ( rng[4]==8 ) { xE1=200; }
	    if ( rng[4]==9 ) { xE1=225; }
	    if ( rng[4]==10 ) { xE1=250; }
	    if ( rng[4]==11 ) { xE1=275; }
	    
	    int xE2; // E2
	    if ( rng[5]==0 ) { xE2=0; }
	    if ( rng[5]==1 ) { xE2=25; }
	    if ( rng[5]==2 ) { xE2=50; }
	    if ( rng[5]==3 ) { xE2=75; }
	    if ( rng[5]==4 ) { xE2=100; }
	    if ( rng[5]==5 ) { xE2=125; }
	    if ( rng[5]==6 ) { xE2=150; }
	    if ( rng[5]==7 ) { xE2=175; }
	    if ( rng[5]==8 ) { xE2=200; }
	    if ( rng[5]==9 ) { xE2=225; }
	    if ( rng[5]==10 ) { xE2=250; }
	    if ( rng[5]==11 ) { xE2=275; }
	    
	    /*int pol_degree = 0;
	    if ( E0<195 ) { pol_degree = 2; }
	    if ( E0>=195 && E0<1700 ) { pol_degree = 1; }
	    if ( E0>=1700 ) { pol_degree = 0; }
	    
	    char namefile[300], hName_E0[300];
	    sprintf(namefile,"MarginalizedROOT/53_93_NORM_BEGe_PSD/%i.root", E0);
	    TFile *file = new TFile(namefile);
	    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {
		    sprintf(hName_E0, "h1_%iGausPol%i_parameter_E0_height", E0, pol_degree);
	    }
	    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
		   sprintf(hName_E0, "h1_%iGausPol%i_1Gamma_parameter_E0_height", E0, pol_degree);
	    }
	    else {
		    sprintf(hName_E0, "h1_%iGausPol%i_2Gamma_parameter_E0_height", E0, pol_degree);
	    }
	    TH1D *h_E0 = (TH1D*)file->Get(hName_E0);*/
	    	    
	    
	    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {
		    double *output_pol1 = FindRange_Pol1( E0, bin_content, max_height);
		    
		    // 1) Signal yield (index 0)
		    AddParameter("E0_height", 0, max_height[3]+xE0, "", "[events]");
		    //GetParameters().Back().SetPrior(new BCTH1Prior(h_E0));
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    min_p0 = output_pol1[0]-i*output_pol1[1];
		    max_p0 = output_pol1[0]+i*output_pol1[1];
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    min_p1 = output_pol1[2]-j*output_pol1[3];
		    max_p1 = output_pol1[2]+j*output_pol1[3];
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
            }
            
            else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) {
		    int *max_gammaYield = FindMaximumGammaHeight1( E0, E1, E2, bin_content, xL, xR, outputK);
		    double *output_G_pol1 = FindRange_Gamma_Pol1( E0, bin_content, max_height, E1, max_gammaYield, xL, xR);
		    
		    // 1) Signal yield (index 0)
		    AddParameter("E0_height", 0, max_height[3]+xE0, "", "[events]");
		    //GetParameters().Back().SetPrior(new BCTH1Prior(h_E0));
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    min_p0 = output_G_pol1[0]-i*output_G_pol1[1];
		    max_p0 = output_G_pol1[0]+i*output_G_pol1[1];
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant(); 
		    
		    // 3) Slope (index 2)
		    min_p1 = output_G_pol1[2]-j*output_G_pol1[3];
		    max_p1 = output_G_pol1[2]+j*output_G_pol1[3];
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Gamma yield (index 3)  
		    AddParameter("E1_height", 0, max_gammaYield[3]+xE1, "", "[events]");
		    GetParameters().Back().SetPriorConstant();        
            } 
            
            else {
            	    int *max_gammaYield1 = FindMaximumGammaHeight1( E0, E1, E2, bin_content, xL, xR, outputK);
            	    int *max_gammaYield2 = FindMaximumGammaHeight2( E0, E1, E2, bin_content, xL, xR, outputK);
		    double *output_2G_pol1 = FindRange_TwoGamma_Pol1( E0, bin_content, max_height, E1, max_gammaYield1, E2, max_gammaYield2, xL, xR);
            	   
            	    // 1) Signal yield (index 0)
		    AddParameter("E0_height", 0, max_height[3]+xE0, "", "[events]");
		    //GetParameters().Back().SetPrior(new BCTH1Prior(h_E0));
		    GetParameters().Back().SetPriorConstant();

		    // 2) Constant (index 1)
		    min_p0 = output_2G_pol1[0]-i*output_2G_pol1[1];
		    max_p0 = output_2G_pol1[0]+i*output_2G_pol1[1];
		    AddParameter("p0", min_p0, max_p0, "p0", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 3) Slope (index 2)
		    min_p1 = output_2G_pol1[2]-j*output_2G_pol1[3];
		    max_p1 = output_2G_pol1[2]+j*output_2G_pol1[3];
		    AddParameter("p1", min_p1, max_p1, "p1", "[events/keV]");
		    GetParameters().Back().SetPriorConstant();
		    GetParameters().Back().SetPriorConstant();
		    
		    // 4) Gamma yield (1) (index 3)  
		    AddParameter("E1_height", 0, max_gammaYield1[3]+xE1, "", "[events]");
		    GetParameters().Back().SetPriorConstant();
		    
		    // 5) Gamma yield (2) (index 4)  
		    AddParameter("E2_height", 0, max_gammaYield2[3]+xE2, "", "[events]");
		    GetParameters().Back().SetPriorConstant(); 
            }

}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
GausPol1::~GausPol1() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double GausPol1::LogLikelihood(const std::vector<double>& pars)
{

            double LP = 0.;
            
            int E0 = GetDataSet()->GetDataPoint(5201).GetValue(0);
            int xL = GetDataSet()->GetDataPoint(5202).GetValue(0);
            int xR = GetDataSet()->GetDataPoint(5203).GetValue(0);
            int outputK = GetDataSet()->GetDataPoint(5205).GetValue(0);
	    int counts = 0;
	    
            for ( int i=xL; i<xR; i++ ) {
		    
                    double y_obs = GetDataSet()->GetDataPoint(i).GetValue(0); // observed value ( 0 = 1st column )
                    double y_exp = 0;
                    
                    // expected value
                    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {
                    	y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*(i-E0);
                    }
                    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { 
                    	double E1 = GetDataSet()->GetDataPoint(5204).GetValue(0);
                    	y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*(i-E0) + pars[3]*TMath::Gaus(i, E1, FindSigma(E1), true);
                    }
                    else { 
                    	double E1 = GetDataSet()->GetDataPoint(5204).GetValue(0);
                    	double E2 = GetDataSet()->GetDataPoint(5206).GetValue(0);
                    	y_exp =  pars[0]*TMath::Gaus(i, E0, FindSigma(E0), true) + pars[1] + pars[2]*(i-E0) + pars[3]*TMath::Gaus(i, E1, FindSigma(E1), true) + pars[4]*TMath::Gaus(i, E2, FindSigma(E2), true);
                    }
                    
                    if ( y_exp<0 ) { counts++; }

                    LP += BCMath::LogPoisson(y_obs, y_exp); // log of conditional probability, p(data|pars)         
            }
            	
            if (counts!=0) {
		    std::fstream file2;
		    file2.open("output.txt", std::ios_base::app);
		    file2 << counts << std::endl;
		    file2.close();
            }           
            
            return LP;
 }	    
