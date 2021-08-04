### MonteCarlo Study
* **"peakSearch_run.sh"**: starting program for the analysis (iterates over the number of MC simulations).
* **"runDataAnalysis.cxx"**: main program for the analysis. It takes input values after the analysis performed in "peak_search.sh". In particular,
  * _pol_degree_ for the BKG is 0, 1, or 2;
  * _xL_ (_xR_) is the left (right) energy limit for the fit window centered in _E0_;
  * _k_ is used as an index to get the energy of the corresponding peak from the array that contains all the gamma transitions;
  * _output(k)_ is important to see if there is 1(2) gamma peak(s) and where is(are).
* **"Operations.cxx"**: file that stores different functions that are called in the main source file and in the model source files.
* **"GausPol0.cxx"**: model for fitting with f(x)=pol0(x)+gaus(x) (+gaus1(x)+gaus2(x)).
* **"GausPol1.cxx"**: model for fitting with f(x)=pol1(x)+gaus(x) (+gaus1(x)+gaus2(x)).
* **"GausPol2.cxx"**: model for fitting with f(x)=pol2(x)+gaus(x) (+gaus1(x)+gaus2(x)).
* **"Output.cxx"**: file that:
  * creates a JSON file containing the "peak_search.sh" results together with the BAT results;
  * draws the experimental data together with the fit result.
* **"PosteriorCheck.C"**: to analyze marginalized posteriors and see if they are cut or not.
* **"sample_BATpdf.C"**: given the energy _E0_ and the detectory type, it takes the posterior distributions from the BAT fit, it fits the posterior with a gaussian (or it takes the global mode and the 34% quantile in case of gamma height parameters that are compatible with 0 counts), it samples the parameters from the Gaussian function that models the pdfs, it generates a spectrum in E0+-20keV, it stores the spectrum in a ROOT file, which is then analyzed with "RunDataAnalysis.cxx". 
* **"MC_output.C"**: to store the toy-MC fit output in files, then analyzed/plotted with **"plot_MC.C"**.
