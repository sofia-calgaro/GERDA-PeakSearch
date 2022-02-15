#include "PseudoscalarModel.h"
#include "Operations.h"
#include <TMath.h>
#include <BAT/BCTH1Prior.h>

// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
PseudoscalarModel::PseudoscalarModel(const std::string& name, std::vector<double> bin_content, double *FitVariables, bool *peak)
    : BCModel(name)
{
	    int E0 = FitVariables[0];
	    double E1 = FitVariables[1];
	    double E2 = FitVariables[2];
	    int xL = FitVariables[3];
	    int xR = FitVariables[4];
	    int k_fit  = FitVariables[5];
	    int outputK = FitVariables[6];
	    int pol_degree = FitVariables[7];
	    int rng_p0 = FitVariables[9];
	    int rng_p1 = FitVariables[10];
	    int rng_p2 = FitVariables[11];
	    int rng_E0 = FitVariables[12];
	    int rng_E1 = FitVariables[13];
	    int rng_E2 = FitVariables[14];
	    int k = 0;
	    
	    char inupt_name[300]; sprintf(inupt_name, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_coax_PSD_ConstantP/JsonFile%i.json", E0);
	    std::ifstream input_json(inupt_name);
	    json j_read; input_json >> j_read; input_json.close();
	    
	    if ( pol_degree==0 ) { std::cout << "Pol0-fit not implemented yet!" << std::endl; }
	    
	    if ( pol_degree==1 ) {
	    		
	    	    double p0_GM = j_read["GlobalMode"]["p0"].get<double>();
	    	    double p1_GM = j_read["GlobalMode"]["p1"].get<double>();
	    	    double p0_sigma = j_read["GlobalMode"]["p0_sigma"].get<double>();
	    	    double p1_sigma = j_read["GlobalMode"]["p1_sigma"].get<double>();
		    double min_p0 = p0_GM - (rng_p0+1)*10*p0_sigma;
		    double max_p0 = p0_GM + (rng_p0+1)*10*p0_sigma;
		    double min_p1 = p1_GM - (rng_p1+1)*10*p1_sigma;
		    double max_p1 = p1_GM + (rng_p1+1)*10*p1_sigma;
	    	    
		    // Coupling yield 
		    double *max_height = FindMaximumSignalHeight(E0);
		    AddParameter("E0_height", 0, max_height[1] + (rng_E0+1)*5*max_height[1], "#alpha'/#alpha", "");
		    GetParameters().Back().SetPriorConstant();
		    
		    if ( peak[0]==true ) { 

			    // Constant
			    AddParameter("p0", min_p0, max_p0, "p0", "[cts]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Slope 
			    AddParameter("p1", min_p1, max_p1, "p1", "[cts/keV]");
			    GetParameters().Back().SetPriorConstant();
		    }
		    
		    else if ( peak[1]==true ) {
			    double E1_counts = j_read["GlobalMode"]["E1_counts"].get<double>();
			    double E1_counts_sigma = j_read["GlobalMode"]["E1_counts_sigma"].get<double>();
			    double max_E1 = E1_counts + 10*E1_counts_sigma;

			    // Constant
			    AddParameter("p0", min_p0, max_p0, "p0", "[cts]");
			    GetParameters().Back().SetPriorConstant(); 
			    
			    // Slope
			    AddParameter("p1", min_p1, max_p1, "p1", "[cts/keV]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Gamma yield 
			    AddParameter("E1_height", 0, max_E1 + rng_E1*25, "E1_height", "[cts]");
			    GetParameters().Back().SetPriorConstant();        
		    } 
		    
		    else {
		    	    double E1_counts = j_read["GlobalMode"]["E1_counts"].get<double>();
			    double E2_counts = j_read["GlobalMode"]["E2_counts"].get<double>();
			    double E1_counts_sigma = j_read["GlobalMode"]["E1_counts_sigma"].get<double>();
			    double E2_counts_sigma = j_read["GlobalMode"]["E2_counts_sigma"].get<double>();
			    double max_E1 = E1_counts + 10*E1_counts_sigma;
			    double max_E2 = E2_counts + 10*E2_counts_sigma;
			    
			    // Constant 
			    AddParameter("p0", min_p0, max_p0, "p0", "[cts]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Slope
			    AddParameter("p1", min_p1, max_p1, "p1", "[cts/keV]");
			    GetParameters().Back().SetPriorConstant();
			    GetParameters().Back().SetPriorConstant();
			    
			    // Gamma yield (1)
			    AddParameter("E1_height", 0, max_E1 + rng_E1*25, "E1_height", "[cts]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Gamma yield (2) 
			    AddParameter("E2_height", 0, max_E2 + rng_E2*25, "E2_height", "[cts]");
			    GetParameters().Back().SetPriorConstant(); 
		    }
	    }
	    
	    if ( pol_degree==2 ) {
	    		
	    	    double p0_GM = j_read["GlobalMode"]["p0"].get<double>();
	    	    double p1_GM = j_read["GlobalMode"]["p1"].get<double>();
	    	    double p2_GM = j_read["GlobalMode"]["p2"].get<double>();
	    	    double p0_sigma = j_read["GlobalMode"]["p0_sigma"].get<double>();
	    	    double p1_sigma = j_read["GlobalMode"]["p1_sigma"].get<double>();
	    	    double p2_sigma = j_read["GlobalMode"]["p2_sigma"].get<double>();
		    double min_p0 = p0_GM - (rng_p0+1)*10*p0_sigma;
		    double max_p0 = p0_GM + (rng_p0+1)*10*p0_sigma;
		    double min_p1 = p1_GM - (rng_p1+1)*10*p1_sigma;
		    double max_p1 = p1_GM + (rng_p1+1)*10*p1_sigma;
		    double min_p2 = p2_GM - (rng_p2+1)*15*p2_sigma;
		    double max_p2 = p2_GM + (rng_p2+1)*15*p2_sigma;
		    
		    // Coupling yield
	            double *max_height = FindMaximumSignalHeight(E0);
	    	    AddParameter("E0_height", 0, max_height[1] + (rng_E0+1)*5*max_height[1], "#alpha'/#alpha", "");
		    GetParameters().Back().SetPriorConstant();
	    	
		    if ( peak[0]==true ) {
			    // Constant 
			    AddParameter("p0", min_p0, max_p0, "p0", "[cts]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Slope
			    AddParameter("p1", min_p1, max_p1, "p1", "[cts/keV]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Quadratic term
			    AddParameter("p2", min_p2, max_p2, "p2", "[cts/keV^2]");
			    GetParameters().Back().SetPriorConstant();
		    }
		    
		    else if ( peak[1]==true ) {
		    	    double E1_counts = j_read["GlobalMode"]["E1_counts"].get<double>();
			    double E1_counts_sigma = j_read["GlobalMode"]["E1_counts_sigma"].get<double>();
			    double max_E1 = E1_counts + 10*E1_counts_sigma;
			    
			    // Constant 
			    AddParameter("p0", min_p0, max_p0, "p0", "[cts]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Slope
			    AddParameter("p1", min_p1, max_p1, "p1", "[cts/keV]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Quadratic term
			    AddParameter("p2", min_p2, max_p2, "p2", "[cts/keV^2]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Gamma yield
			    AddParameter("E1_height", 0, max_E1 + rng_E1*25, "", "[cts]");
			    GetParameters().Back().SetPriorConstant();        
		    } 
		    
		    else {
		    	    double E1_counts = j_read["GlobalMode"]["E1_counts"].get<double>();
			    double E2_counts = j_read["GlobalMode"]["E2_counts"].get<double>();
			    double E1_counts_sigma = j_read["GlobalMode"]["E1_counts_sigma"].get<double>();
			    double E2_counts_sigma = j_read["GlobalMode"]["E2_counts_sigma"].get<double>();
			    double max_E1 = E1_counts + 10*E1_counts_sigma;
			    double max_E2 = E2_counts + 10*E2_counts_sigma;
			    
			    // Constant 
			    AddParameter("p0", min_p0, max_p0, "p0", "[cts]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Slope
			    AddParameter("p1", min_p1, max_p1, "p1", "[cts/keV]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Quadratic term 
			    AddParameter("p2", min_p2, max_p2, "p2", "[cts/keV^2]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Gamma yield (1)  
			    AddParameter("E1_height", 0, max_E1 + rng_E1*25, "", "[cts]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Gamma yield (2) 
			    AddParameter("E2_height", 0, max_E2 + rng_E2*25, "", "[cts]");
			    GetParameters().Back().SetPriorConstant();
		    }
	    }

}

// ----------------------------------------------------------------------------------------------------- DESTRUCTOR
PseudoscalarModel::~PseudoscalarModel() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double PseudoscalarModel::LogLikelihood(const std::vector<double>& par)
{

            // fit variables
            int E0 = GetDataSet()->GetDataPoint(26001).GetValue(0);
            int xL = GetDataSet()->GetDataPoint(26002).GetValue(0);
            int xR = GetDataSet()->GetDataPoint(26003).GetValue(0);
            double E1 = GetDataSet()->GetDataPoint(26004).GetValue(0);
            int outputK = GetDataSet()->GetDataPoint(26005).GetValue(0);
            int pol_degree = GetDataSet()->GetDataPoint(26006).GetValue(0);
            double E2 = GetDataSet()->GetDataPoint(26007).GetValue(0);
            int thr = GetDataSet()->GetDataPoint(26008).GetValue(0);
            double A = 75.921402725*0.88;
            double num = 1.467*1e19;
            double exp_87_93[2]     = {7.48810, 8.36807};
            double exp_53_93[2]     = {28.6383, 32.7476};
            double exp_87_93_PSD[2] = {7.48810, 8.28657};
            double exp_53_93_PSD[2] = {28.6383, 31.4597};
            double exp_87_114[3]    = {20.6676, 30.5489, 8.77469};
            double exp_53_114[3]    = {41.8177, 52.9284, 8.77469};
            
            // start values for other data points
            const int co_II  = 0;
            const int be_II  = 5201;
            const int co_IIp = 10401;
            const int be_IIp = 15601;
            const int ic_IIp = 20801;
            const int start_en      = 26009;
            const int start_co_II   = 27010;
            const int start_be_II   = 28011;
            const int start_co_IIp  = 29012;
            const int start_be_IIp  = 30013;
            const int start_ic_IIp  = 31014;
            const int start_Ge_en   = 32015;
            const int start_Ge_xsec = 33615;
            /*std::cout << GetDataSet()->GetDataPoint(start_en).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_co_II).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_be_II).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_co_IIp).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_be_IIp).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_ic_IIp).GetValue(0) << 
                         std::endl; */
            /*std::cout << GetDataSet()->GetDataPoint(start_Ge_en).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_Ge_xsec).GetValue(0) << 
                         std::endl; */
            
            int line = 0;
            while ( (GetDataSet()->GetDataPoint(start_en+line).GetValue(0))!=xL ) { line++; }
            int line2 = 0;
            while ( (GetDataSet()->GetDataPoint(start_Ge_en+line2).GetValue(0))!=xL ) { line2++; }
            
	    // Likelihood calculation
	    double LP = 0.0; // total likelihood (product of LP_k)
	    const int N_partition = 2;
	    for ( int k=0; k<N_partition; k++) {
		    /*	0 -> coax-II
		    *	1 -> bege-II
		    *	2 -> coax-II+
		    *	3 -> bege-II+
		    *	4 -> ic-II+  
		    */
		    double LP_k = 0.0;
		    double exp = 0.0;
		    if ( E0<thr ) {
		    	if ( k==0 ) exp = exp_87_93[0];
		    	if ( k==1 ) exp = exp_87_93[1];
		    	if ( k==2 ) exp = exp_87_114[0] - exp_87_93[0];
		    	if ( k==3 ) exp = exp_87_114[1] - exp_87_93[1];
		    	if ( k==4 ) exp = exp_87_114[2];
		    }
		    if ( E0>=thr ) {
		    	if ( k==0 ) exp = exp_53_93[0];
		    	if ( k==1 ) exp = exp_53_93[1];
		    	if ( k==2 ) exp = exp_53_114[0] - exp_53_93[0];
		    	if ( k==3 ) exp = exp_53_114[1] - exp_53_93[1];
		    	if ( k==4 ) exp = exp_53_114[2];
		    }
    
		    for ( int i=xL; i<xR; i++ ) {
			    
		            double cts = 0.0;
		            if ( k==0 ) cts = GetDataSet()->GetDataPoint(co_II+i).GetValue(0); 
		            if ( k==1 ) cts = GetDataSet()->GetDataPoint(be_II+i).GetValue(0); 
		            if ( k==2 ) cts = GetDataSet()->GetDataPoint(co_IIp+i).GetValue(0); 
		            if ( k==3 ) cts = GetDataSet()->GetDataPoint(be_IIp+i).GetValue(0); 
		            if ( k==4 ) cts = GetDataSet()->GetDataPoint(ic_IIp+i).GetValue(0); 
		            
		            // eff
		            double line_i = line + (i-xL);
		            double eff = 0.0;
		            if ( k==0 ) eff = GetDataSet()->GetDataPoint(start_co_II+line_i).GetValue(0);
		            if ( k==1 ) eff = GetDataSet()->GetDataPoint(start_be_II+line_i).GetValue(0);
		            if ( k==2 ) eff = GetDataSet()->GetDataPoint(start_co_IIp+line_i).GetValue(0);
		            if ( k==3 ) eff = GetDataSet()->GetDataPoint(start_be_IIp+line_i).GetValue(0);
		            if ( k==4 ) eff = GetDataSet()->GetDataPoint(start_ic_IIp+line_i).GetValue(0);
		            // Ge xsec
		            double line2_i = line2 + (i-xL);
		            double xsec = GetDataSet()->GetDataPoint(start_Ge_xsec+line2_i).GetValue(0);
		            // signal
		            double mu_S = ( par[0]*par[0] * exp*365.25 * eff * xsec * num * TMath::Gaus(i, E0, FindSigma(E0, k), true) * i ) / A;
		            // background
		            double mu_B_pol = 0.0;
		            double mu_B_ga1 = 0.0;
		            double mu_B_ga2 = 0.0;
		            
		            if ( pol_degree==1 ) {
		            	    mu_B_pol = par[1] + par[2]*(i-E0);
		            	    
				    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {}
				    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { 
				    	mu_B_ga1 = par[3]*TMath::Gaus(i, E1, FindSigma(E1, k), true);
				    }
				    else { 
				    	mu_B_ga1 = par[3]*TMath::Gaus(i, E1, FindSigma(E1, k), true);
				    	mu_B_ga2 = par[4]*TMath::Gaus(i, E2, FindSigma(E2, k), true);
				    }
		            }
		            if ( pol_degree==2 ) {
		            	    mu_B_pol = par[1] + par[2]*(i-E0) + par[3]*(i-E0)*(i-E0);
		            	    
				    if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {}
				    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { 
				    	mu_B_ga1 = par[4]*TMath::Gaus(i, E1, FindSigma(E1, k), true);
				    }
				    else { 
				    	mu_B_ga1 = par[4]*TMath::Gaus(i, E1, FindSigma(E1, k), true);
				    	mu_B_ga2 = par[5]*TMath::Gaus(i, E2, FindSigma(E2, k), true);
				    }
		            }
		            
		            LP_k += BCMath::LogPoisson(cts, mu_B_pol + mu_B_ga1 + mu_B_ga2 + mu_S); // logPoiss(obs|exp)
		    }
		    
		    LP += LP_k;
	    }
            
            return LP;
 }	    
