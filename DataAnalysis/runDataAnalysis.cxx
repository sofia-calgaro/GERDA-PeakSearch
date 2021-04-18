// BAT
#include <BAT/BCLog.h>
#include <BAT/BCH1D.h>
#include <BAT/BCAux.h>

// ROOT
#include <TFile.h>
#include <TMath.h>
#include <TCanvas.h>

// MODELS
#include "GausPol0.h"
#include "GausPol1.h"
#include "GausPol2.h"

// OTHER
#include "Operations.h"
#include "args_reader.hpp"



int main(int argc, char *argv[])
{  

    std::vector<std::string> args(argc);
    std::copy(argv, argv+argc, args.begin());
  
    std::vector<int> inpval(3,0); // input values: {E0, pol_degree}
    bool found = fetch_arg(args, "--nums", inpval);
    
    if (found) {
    std::cout << "\n *************************" << std::endl;
    std::cout << "  # values = " << inpval[0] << "\n  E0 = " << inpval[1] << "\n  Polynomial degree = " << inpval[2] << std::endl;
    std::cout << " *************************\n" << std::endl;
    }
    
    //---------------------------------------------------------------------------------------------------------------------- DATA LOADING   


    TFile *file = new TFile("/home/sofia/gerda_data/IC_20210406.root","READ");
    TH1D *h = (TH1D*) file->Get("histo_energy_LArVetoed");
    std::vector< int> bin_content;
    for ( int i=1; i<=5200; i++ ) { bin_content.push_back( h->GetBinContent(i) ); }
        		
    // create a new dataset to pass then to the model
    BCDataSet data_set;
    data_set.ReadDataFromFileTxt("/home/sofia/gerda_data/bin_content.txt", 1);
    
    // create a new data point: E0
    int E0 = inpval[1];
    BCDataPoint* CentralEnergy = new BCDataPoint(1);
    CentralEnergy->SetValue(0,E0);
    data_set.AddDataPoint(*CentralEnergy);	
    
    int x1 = E0 - 12;
    int x2 = E0 + 12;	
    
    // open log file
    int pol_degree = inpval[2];
    char name_log[100];
    sprintf(name_log,"/home/sofia/Analysis/DataAnalysis/Log_files/log_%i_GausPol%i.txt", E0, pol_degree);
    BCLog::OpenLog(name_log, BCLog::detail, BCLog::detail);	
    
    
    //---------------------------------------------------------------------------------------------------------------------- ANALYSIS    
    
    
    // Gaus + Pol0
    if ( pol_degree==0 ) {
    	
    	    char name_model[100];
    	    sprintf(name_model,"%i_GausPol0", E0);
	    GausPol0 m(name_model, bin_content, E0);
	    
	    // Associate the data set with the model
   	    m.SetDataSet(&data_set);
	    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kMedium);

	    // run MCMC, marginalizing posterior
	    m.MarginalizeAll(BCIntegrate::kMargMetropolis);

	    // run mode finding; by default using Minuit
	    m.FindMode(m.GetBestFitParameters());
	    
	    // fix the bands for each posterior at 68.3%, 95.4%, 99.7%
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
	 
	    // draw all marginalized distributions into a PDF file
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf");
	  
	    m.PrintSummary();
	  
	    BCLog::OutSummary("Exiting");
	    BCLog::CloseLog();
	    
	    // data + fit
	    TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	    h->Draw();
	    h->GetXaxis()->SetRangeUser(x1, x2);
	    
	    const std::vector<double> params = m.GetBestFitParameters();

	    char function[100];
	    sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1]", E0, FindSigma(E0));
	    TF1 *f0 = new TF1("f0", function, x1, x2);
	    f0->FixParameter(0, params.at(0));
	    f0->FixParameter(1, params.at(1));
		    
	    f0->SetLineWidth(2);
	    f0->SetLineColor(2);
	    f0->Draw("same");
		    
	    h->SetTitle("Fit with gaus(x)+pol0(x)");
	    c->Update();
	    char name_image[100];
	    sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%i_GausPol0.png", E0);
	    c->Print(name_image);
	    char name_rootfile[100];
	    sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%i_GausPol0.root", E0);
	    c->Print(name_rootfile);
    }
    
    
    
    // Gaus + Pol1
    if ( pol_degree==1 ) {
    
   	    char name_model[100];
    	    sprintf(name_model,"%i_GausPol1", E0);
	    GausPol1 m(name_model, bin_content, E0);
   	    
   	    // Associate the data set with the model
   	    m.SetDataSet(&data_set);
    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kMedium);

	    // run MCMC, marginalizing posterior
	    m.MarginalizeAll(BCIntegrate::kMargMetropolis);

	    // run mode finding; by default using Minuit
	    m.FindMode(m.GetBestFitParameters());
	    
	    // fix the bands for each posterior at 68.3%, 95.4%, 99.7%
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
	 
	    // draw all marginalized distributions into a PDF file
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf", 2, 2);
	  
	    m.PrintSummary();
	  
	    BCLog::OutSummary("Exiting");
	    BCLog::CloseLog();
	    
	    // data + fit
	    TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	    h->Draw();
	    h->GetXaxis()->SetRangeUser(x1, x2);
	    
	    const std::vector<double> params = m.GetBestFitParameters();
	    
	    char function[100];
	    sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i)", E0, FindSigma(E0), E0);
	    TF1 *f1 = new TF1("f1", function, x1, x2);
	    f1->FixParameter(0, params.at(0));
	    f1->FixParameter(1, params.at(1));
	    f1->FixParameter(2, params.at(2));
	    
	    f1->SetLineWidth(2);
	    f1->SetLineColor(2);
	    f1->Draw("same");  
	    
	    h->SetTitle("Fit with gaus(x)+pol1(x)");
	    c->Update();
	    char name_image[100];
	    sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%i_GausPol1.png", E0);
	    c->Print(name_image);
	    char name_rootfile[100];
	    sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%i_GausPol1.root", E0);
	    c->Print(name_rootfile);     
    }
    
    
    
    // Gaus + Pol2
    if ( pol_degree==2 ) {
    
  	    char name_model[100];
    	    sprintf(name_model,"%i_GausPol2", E0);
	    GausPol2 m(name_model, bin_content, E0);
  	    
  	    // Associate the data set with the model
   	    m.SetDataSet(&data_set);
    
	    BCLog::OutSummary("Test model created");

	    m.SetPrecision(BCEngineMCMC::kMedium);

	    // run MCMC, marginalizing posterior
	    m.MarginalizeAll(BCIntegrate::kMargMetropolis);

	    // run mode finding; by default using Minuit
	    m.FindMode(m.GetBestFitParameters());
	    
	    // fix the bands for each posterior at 68.3%, 95.4%, 99.7%
	    m.GetBCH1DdrawingOptions().SetBandType(BCH1D::kCentralInterval);  
	 
	    // draw all marginalized distributions into a PDF file
	    m.PrintAllMarginalized("/home/sofia/Analysis/DataAnalysis/MarginalizedPDF/" + m.GetSafeName() + "_plots.pdf", 2, 2);
	  
	    m.PrintSummary();
	  
	    BCLog::OutSummary("Exiting");
	    BCLog::CloseLog();
	    
	    // data + fit
	    TCanvas *c = new TCanvas("c", "c", 1700, 1000);
	    h->Draw();
	    h->GetXaxis()->SetRangeUser(x1, x2);
	    
	    const std::vector<double> params = m.GetBestFitParameters();
	    
	    char function[100];
	    sprintf(function, "[0]*TMath::Gaus(x, %i, %f, true) + [1] + [2]*(x-%i) + [3]*(x-%i)*(x-%i)", E0, FindSigma(E0), E0, E0, E0);
	    TF1 *f2 = new TF1("f2", function, x1, x2);
	    f2->FixParameter(0, params.at(0));
	    f2->FixParameter(1, params.at(1));
	    f2->FixParameter(2, params.at(2));
	    f2->FixParameter(3, params.at(3));
	    
	    f2->SetLineWidth(2);
	    f2->SetLineColor(2);
	    f2->Draw("same");  
	    
	    h->SetTitle("Fit with gaus(x)+pol2(x)");
	    c->Update();
	    char name_image[100];
	    sprintf(name_image, "/home/sofia/Analysis/DataAnalysis/Plot/fit_%i_GausPol2.png", E0);
	    c->Print(name_image);
	    char name_rootfile[100];
	    sprintf(name_rootfile, "/home/sofia/Analysis/DataAnalysis/Root_files/fit_%i_GausPol2.root", E0);
	    c->Print(name_rootfile);
    }

    return 0;
}

