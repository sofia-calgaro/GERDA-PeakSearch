## gerda-BATanalysis
* ```css **"peak_search.sh"** ```: starting program for the analysis. It requires as input parameters the central energy (_E0_) of the fit window and the number of fit you want to perform. Detector resultions must be changed by hand. Pay attention to the re-definition of _xL_ and _xR_ when you use spectrum normalized by exposure.
* **"runDataAnalysis.cxx"**: main program for the analysis. It takes input values (_E0, pol_degree, xL, xR, k, output(k)_) from "peak_search.sh":
  * _pol_degree_ for the BKG is 0 (>1700 keV), 1, or 2 (<195 keV);
  * _xL_ (_xR_) is the left (right) energy limit for the fit window centered in _E0_;
  * _k_ is used as an index to get the energy of the corresponding peak from the array that contains all the gamma transitions;
  * _output(k)_ is important to see if there is 1(2) gamma peak(s) and where is; see "peakPosition.txt" for more information.
* **"Operations.cxx"**: file that stores different functions that are called in the main source file and in the model source files. Detector resultions must be changed by hand. Pay attention to the re-definition of _xL_ and _xR_ when you use spectrum normalized by exposure.
* **"GausPol0.cxx"**: model for fitting with f(x)=pol0(x)+gaus(x) (+gaus1(x)+gaus2(x)). Priors (constant or not) must be changed by hand (pay attention to directories).
* **"GausPol1.cxx"**: model for fitting with f(x)=pol1(x)+gaus(x) (+gaus1(x)+gaus2(x)). Priors (constant or not) must be changed by hand (pay attention to directories).
* **"GausPol2.cxx"**: model for fitting with f(x)=pol2(x)+gaus(x) (+gaus1(x)+gaus2(x)). Priors (constant or not) must be changed by hand (pay attention to directories).
* **"Output.cxx"**: file that:
  * creates a JSON file containing the "peak_search.sh" results together with the fit results; it requires the class _json.hpp_ (see [nlohmann/json](https://github.com/nlohmann/json));
  * draws the experimental data together with the fit result.
* **"read_JSON.cpp"**: file that print JSON files and create .txt files containing fit results.
* **"PosteriorCheck.C"**: to analyze marginalized posteriors and see if they are well contained in the previusly well-defined range.
* **"par_VS_E0.C"**: to plot fit results as a function of the energy.
* **"DistributionCheck.C"**: to study the shape of marginalized posteriors. Posteriors are fit with a pol0 function; if chi2 is too high, posteriors are unlikely constant (-> gaussian). Problems arise if constant posteriors are detected.
* **"content_eff_correction.C"**: to calculate .txt and .root files for normalized spectra corrected by the efficiencies.
