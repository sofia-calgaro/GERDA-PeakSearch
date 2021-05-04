## gerda-BATanalysis
* "peak_search.sh": starting program for the analysis. It requires as input parameters the central energy (_E0_) of the fit window and the polynomial degree (_pol_degree_) for fitting the background. Execute it by using:
```
$ chmod +x peak_search.sh 
$ ./peak_search.sh 
```
* "runDataAnalysis.cxx": main program for the analysis. It takes six input values (_E0, pol_degree, xL, xR, k, output(k)_) directly from the analysis performed in "peak_search.sh":
  * _xL_ (_xR_) is the left (right) energy limit for the fit window centered in _E0_;
  * _k_ is used as an index to get the energy of the corresponding peak from the array that contains all the gamma transitions;
  * _output(k)_ is important to see if there is 1(2) gamma peak(s) and where is(are).
* "Operations.cxx": file that stores different functions that are called in the main source file and in the model source files.
* "DrawPlots.cxx": file that draws the experimental data together with the fit result.
* "GausPol0.cxx": model for fitting with f(x)=pol0(x)+gaus(x) (+gaus1(x)+gaus2(x)).
* "GausPol1.cxx": model for fitting with f(x)=pol1(x)+gaus(x) (+gaus1(x)+gaus2(x)).
* "GausPol2.cxx": model for fitting with f(x)=pol2(x)+gaus(x) (+gaus1(x)+gaus2(x)).
