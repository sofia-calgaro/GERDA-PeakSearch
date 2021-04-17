## gerda-BATanalysis

* "_runDataAnalysis.cxx_": main program for the analysis; it takes two input values through "args_reader.hpp" equal to the central energy of the fit window and to the polynomial degree (0, 1, 2) for the background fit. For example:
```
$ make
$ ./runDataAnalysis --nums 2 {311, 1}
```
* "_Operations.cxx_" ("_Operations.h_"): file that stores different functions that are called in the main source file and in the model source files.
* "_GausPol0.cxx_" ("_GausPol0.h_"): model for fitting with f(x)=gaus(x)+pol0(x).
* "_GausPol1.cxx_" ("_GausPol1.h_"): model for fitting with f(x)=gaus(x)+pol1(x).
* "_GausPol2.cxx_" ("_GausPol2.h_"): model for fitting with f(x)=gaus(x)+pol2(x).
