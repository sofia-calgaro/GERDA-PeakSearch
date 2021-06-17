## gerda-BATanalysis
* **"peak_search.sh"**: starting program for the analysis. It requires as input parameters the central energy (_E0_) of the fit window.
* **"runDataAnalysis.cxx"**: main program for the analysis. It takes six input values (_E0, pol_degree, xL, xR, k, output(k)_) directly from the analysis performed in "peak_search.sh":
  * _pol_degree_ for the BKG is 0, 1, or 2;
  * _xL_ (_xR_) is the left (right) energy limit for the fit window centered in _E0_;
  * _k_ is used as an index to get the energy of the corresponding peak from the array that contains all the gamma transitions;
  * _output(k)_ is important to see if there is 1(2) gamma peak(s) and where is(are); see "peakPosition.txt" for more information.
* **"Operations.cxx"**: file that stores different functions that are called in the main source file and in the model source files.
* **"GausPol0.cxx"**: model for fitting with f(x)=pol0(x)+gaus(x) (+gaus1(x)+gaus2(x)).
* **"GausPol1.cxx"**: model for fitting with f(x)=pol1(x)+gaus(x) (+gaus1(x)+gaus2(x)).
* **"GausPol2.cxx"**: model for fitting with f(x)=pol2(x)+gaus(x) (+gaus1(x)+gaus2(x)).
* **"Output.cxx"**: file that:
  * creates a JSON file containing the "peak_search.sh" results together with the BAT results; it requires the class _json.hpp_ (see [nlohmann/json](https://github.com/nlohmann/json));
  * draws the experimental data together with the fit result.
* **"read_JSON.cpp"**: file that read JSON files and create .txt files containing BAT fit results.
* **"PosteriorCheck.C"**: to analyze marginalized posteriors and see if they are cut or not.
* **"par_VS_E0.C"**: to plot fit results as a function of the energy.
