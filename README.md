## gerda-BATanalysis

* "_runDataAnalysis.cxx_": main program for the analysis; it takes two input values through "args_readeer.hpp", i.e. the central energy of the fit windown and the polynomial degree
```
$ git clone https://example.com
$ cd ../path/to/the/file
$ npm install
$ npm start
```
* "_Operations.cxx_" ("_Operations.h_"): file that stores different functions that are called in the main source file and in the model source files
* "_GausPol0.cxx_" ("_GausPol0.h_"): fit-model given by f(x)=gaus(x)+pol0(x)
* "_GausPol1.cxx_" ("_GausPol1.h_"): fit-model given by f(x)=gaus(x)+pol1(x)
* "_GausPol2.cxx_" ("_GausPol2.h_"): fit-model given by f(x)=gaus(x)+pol2(x)
