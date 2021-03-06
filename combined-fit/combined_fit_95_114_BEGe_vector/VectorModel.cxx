#include "VectorModel.h"
#include "Operations.h"
#include <TMath.h>
#include <BAT/BCTH1Prior.h>

// ----------------------------------------------------------------------------------------------------- CONSTRUCTOR
VectorModel::VectorModel(const std::string& name, std::vector<double> bin_content, double *FitVariables, bool *peak)
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
	    
	    char inupt_name[300]; 
	    if ( E0>1000 ) { sprintf(inupt_name, "/home/sofia/Analysis/PRL_analysis_all/JsonFiles/95_114_IC_BEGe_coax_ConstantP/JsonFile1000.json"); }
	    else           { sprintf(inupt_name, "/home/sofia/Analysis/PRL_analysis_all/JsonFiles/95_114_IC_BEGe_coax_ConstantP/JsonFile%i.json", E0); }
	    std::ifstream input_json(inupt_name);
	    json j_read; input_json >> j_read; input_json.close();
	    
	    if ( pol_degree==0 ) { std::cout << "Pol0-fit not implemented yet!" << std::endl; }
	    
	    if ( pol_degree==1 ) {
	    		
	    	    double p0_GM = j_read["GlobalMode"]["p0"].get<double>();
	    	    double p1_GM = j_read["GlobalMode"]["p1"].get<double>();
	    	    double p0_sigma = j_read["GlobalMode"]["p0_sigma"].get<double>();
	    	    double p1_sigma = j_read["GlobalMode"]["p1_sigma"].get<double>();
		    double min_p0 = p0_GM - (rng_p0+1)*25*p0_sigma;
		    double max_p0 = p0_GM + (rng_p0+1)*10*p0_sigma;
		    double min_p1 = p1_GM - (rng_p1+1)*15*p1_sigma;
		    double max_p1 = p1_GM + (rng_p1+1)*15*p1_sigma;
	    	    
		    // Coupling yield 
		    double *max_height = FindMaximumSignalHeight(E0);
		    AddParameter("E0_height", 0, max_height[0] + (rng_E0+1)*5*max_height[0], "#alpha'/#alpha", "");
		    GetParameters().Back().SetPriorConstant();
		    
		    if ( peak[0]==true ) { 

			    // Constant
			    AddParameter("p0", min_p0, max_p0, "p0", "[cts]");
			    GetParameters().Back().SetPriorConstant();
			    
			    // Slope 
			    AddParameter("p1", min_p1, max_p1, "p1", "[cts/keV]");
			    GetParameters().Back().SetPriorConstant();
			    
			    std::cout << " p0 - min : " << min_p0 << "    - max : " << max_p0 << std::endl;
			    std::cout << " p1 - min : " << min_p1 << "    - max : " << max_p1 << std::endl;
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
		    double min_p0 = p0_GM - (rng_p0+1)*25*p0_sigma;
		    double max_p0 = p0_GM + (rng_p0+1)*15*p0_sigma;
		    double min_p1 = p1_GM - (rng_p1+1)*10*p1_sigma;
		    double max_p1 = p1_GM + (rng_p1+1)*10*p1_sigma;
		    double min_p2 = p2_GM - (rng_p2+1)*15*p2_sigma;
		    double max_p2 = p2_GM + (rng_p2+1)*15*p2_sigma;
		    
		    // Coupling yield
	            double *max_height = FindMaximumSignalHeight(E0);
	    	    AddParameter("E0_height", 0, max_height[0] + (rng_E0+1)*5*max_height[0], "#alpha'/#alpha", "");
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
			    
			    std::cout << " p0 - min : " << min_p0 << "    - max : " << max_p0 << std::endl;
			    std::cout << " p1 - min : " << min_p1 << "    - max : " << max_p1 << std::endl;
			    std::cout << " p2 - min : " << min_p2 << "    - max : " << max_p2 << std::endl;
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
VectorModel::~VectorModel() { }

// ----------------------------------------------------------------------------------------------------- MY MODEL
double VectorModel::LogLikelihood(const std::vector<double>& par)
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
            double A = atomic_mass_II_IIp(E0, thr);
            //std::cout << A << std::endl;
            double num = 4.683*1e23;
            
            // start values for other data points
            const int co_II  = 0;
            const int be_II  = 5201;
            const int co_IIp = 10401;
            const int be_IIp = 15601;
            const int ic_IIp = 20801;
            const int start_en      = 26009;
            const int start_co_II   = 27409;
            const int start_be_II   = 28809;
            const int start_co_IIp  = 30209;
            const int start_be_IIp  = 31609;
            const int start_ic_IIp  = 33009;
            const int start_Ge_en   = 34409;
            const int start_Ge_xsec = 36009;
            /*std::cout << GetDataSet()->GetDataPoint(start_en).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_co_II).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_be_II).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_co_IIp).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_be_IIp).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_ic_IIp).GetValue(0) << 
                         std::endl; */
            /*std::cout << GetDataSet()->GetDataPoint(start_Ge_en).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_Ge_xsec).GetValue(0) << "\t" <<
                         GetDataSet()->GetDataPoint(start_Ge_en+1).GetValue(0) << "\t" << 
                         GetDataSet()->GetDataPoint(start_Ge_xsec+1).GetValue(0) << 
                         std::endl; */
                         
            int line = 0;
            while ( (GetDataSet()->GetDataPoint(start_en+line).GetValue(0))!=xL ) { line++; }
            int line2 = 0;
            while ( (GetDataSet()->GetDataPoint(start_Ge_en+line2).GetValue(0))!=xL ) { line2++; }
            
	    // Likelihood calculation
	    double LP = 0.0; // total likelihood (product of LP_k)
	    const int N_partition = 5;
	    for ( int k=0; k<N_partition; k++) {
		    /*	0 -> coax-II
		    *	1 -> bege-II
		    *	2 -> coax-II+
		    *	3 -> bege-II+
		    *	4 -> ic-II+  
		    */
		    if ( k!=3 ) continue; // pick up only IC-II+
		    if ( k!=3 ) { std::cout << k << std::endl; }
		    //std::cout << k << std::endl;
		    
		    double LP_k = 0.0;
		    double exp = 0.0;
		    double eff_LAr = 0.0;
		    if ( E0<thr ) {
		    	if ( k==3 ) exp = 23.49774;
		    }
		    if ( E0>=thr ) {
		    	if ( k==3 ) exp = 23.49774;
		    }
		    //std::cout << k << "\t" << exp << std::endl;
		    
		    if ( k==0 ) eff_LAr = 0;
		    if ( k==1 ) eff_LAr = 0;
		    if ( k==2 ) eff_LAr = 0.982;
		    if ( k==3 ) eff_LAr = 0.982;
		    if ( k==4 ) eff_LAr = 0.982;
    
		    for ( int i=xL; i<xR; i++ ) {
			    
		            double cts = 0.0;
		            if ( k==0 ) cts = 0; 
		            if ( k==1 ) cts = 0; 
		            if ( k==2 ) cts = GetDataSet()->GetDataPoint(co_IIp+i).GetValue(0); 
		            if ( k==3 ) cts = GetDataSet()->GetDataPoint(be_IIp+i).GetValue(0); 
		            if ( k==4 ) cts = GetDataSet()->GetDataPoint(ic_IIp+i).GetValue(0); 
		            //std::cout << "k=" << k << "\t i=" << i << "\t cts=" << cts << std::endl;
		            
		            // eff
		            double line_i = line + (i-xL);
		            double eff = 0.0;
		            if ( k==0 ) eff = 0; 
		            if ( k==1 ) eff = 0;
		            if ( k==2 ) eff = GetDataSet()->GetDataPoint(start_co_IIp+line_i).GetValue(0);
		            if ( k==3 ) eff = GetDataSet()->GetDataPoint(start_be_IIp+line_i).GetValue(0);
		            if ( k==4 ) eff = GetDataSet()->GetDataPoint(start_ic_IIp+line_i).GetValue(0);
		            //std::cout << "k=" << k << "\t i=" << i << "\t eff=" << eff << std::endl;
		            
		            // Ge xsec
		            double line2_i = line2 + (i-xL);
		            double xsec = GetDataSet()->GetDataPoint(start_Ge_xsec+line2_i).GetValue(0);
		            //std::cout << "k=" << k << "\t i=" << i << "\t xsec=" << xsec << std::endl;
		            
		            // signal
		            double mu_S = ( par[0] * exp*365.25 * eff * eff_LAr * xsec * num * TMath::Gaus(i, E0, FindSigma(E0, k), true) ) / ( i*A );
		            // background
		            double mu_B_pol = 0.0;
		            double mu_B_ga1 = 0.0;
		            double mu_B_ga2 = 0.0;
		            
		            if ( pol_degree==1 ) { mu_B_pol = par[1] + par[2]*(i-E0); }	
		            if ( pol_degree==2 ) { mu_B_pol = par[1] + par[2]*(i-E0) + par[3]*(i-E0)*(i-E0); }
		            
		            if ( outputK<=1 || outputK==4 || outputK==7 || outputK==13 || outputK==14 || outputK==15 || outputK==18 || outputK>=20 ) {}
			    else if ( outputK==2 || outputK==3 || outputK==5 || outputK==6 || outputK==12 ) { 
			    	mu_B_ga1 = par[3]*TMath::Gaus(i, E1, FindSigma(E1, k), true);
			    }
			    else { 
			    	mu_B_ga1 = par[3]*TMath::Gaus(i, E1, FindSigma(E1, k), true);
			    	mu_B_ga2 = par[4]*TMath::Gaus(i, E2, FindSigma(E2, k), true);
			    }
		            
		            LP_k += BCMath::LogPoisson(cts, mu_B_pol + mu_B_ga1 + mu_B_ga2 + mu_S); // logPoiss(obs|exp)
		    }
		    
		    LP += LP_k;
	    }
            
            return LP;
 }	    
