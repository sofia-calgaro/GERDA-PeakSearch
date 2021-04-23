## gerda-BATanalysis
* "_peak_search.sh_": starting program for the analysis. It requires the central energy of the fit window as an input parameter after having executed it:
```
$ chmod +x peak_search.sh 
$ ./peak_search.sh 
```
* "_runDataAnalysis.cxx_": main program for the analysis. It takes six input values (_E0, pol_degree, xL, xR, k, output(k)_) directly from the analysis performed in "peak_search.sh":
  * _xL_ (_xR_) is the left (right) energy limit for the fit window centered in _E0_;
  * _k_ is used as an index to get the energy of the corresponding peak(s) from the array that contains all the gamma transitions;
  * _output(k)_ is important to see if there is 1(2) gamma peak(s) and where is(are).
* "_Operations.cxx_": file that stores different functions that are called in the main source file and in the model source files.
* "_GausPol0.cxx_": model for fitting with f(x)=gaus(x)+pol0(x).
* "_GausPol1.cxx_": model for fitting with f(x)=gaus(x)+pol1(x).
* "_GausPol2.cxx_": model for fitting with f(x)=gaus(x)+pol2(x).
