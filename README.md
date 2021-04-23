## gerda-BATanalysis
* "peak_search.sh": starting program for the analysis. It requires the central energy of the fit window as an input parameter after having executed it:
```
$ chmod +x peak_search.sh 
$ ./peak_search.sh 
```
* "runDataAnalysis.cxx": main program for the analysis. It takes six input values (_E0, pol_degree, xL, xR, k, output(k)_) directly from the analysis performed in "peak_search.sh":
  * _xL_ (_xR_) is the left (right) energy limit for the fit window centered in _E0_;
  * _k_ is used as an index to get the energy of the corresponding peak(s) from the array that contains all the gamma transitions;
  * _output(k)_ is important to see if there is 1(2) gamma peak(s) and where is(are).
* "Operations.cxx": file that stores different functions that are called in the main source file and in the model source files.
* "GausPol0.cxx": model for fitting with f(x)=gaus(x)+pol0(x).
* "GausPol1.cxx": model for fitting with f(x)=gaus(x)+pol1(x).
* "GausPol2.cxx": model for fitting with f(x)=gaus(x)+pol2(x).
