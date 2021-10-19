#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

int main() {

	const int E0 = 780;
	
	string filenameC_01;
	filenameC_01 = "JsonFiles/53_93_NORM_BEGe_PSD/JsonFile" + std::to_string(E0) + "_casoC_01.json";
	ifstream fileC_01(filenameC_01);
	json jC_01;
	fileC_01 >> jC_01;
	fileC_01.close();
		
	string filenameD_01;
	filenameD_01 = "JsonFiles/53_93_NORM_BEGe_PSD/JsonFile" + std::to_string(E0) + "_casoD_01.json";
	ifstream fileD_01(filenameD_01);
	json jD_01;
	fileD_01 >> jD_01;
	fileD_01.close();
	
	string filenameB_01;
	filenameB_01 = "JsonFiles/53_93_NORM_BEGe_PSD/JsonFile" + std::to_string(E0) + "_casoB_01.json";
	ifstream fileB_01(filenameB_01);
	json jB_01;
	fileB_01 >> jB_01;
	fileB_01.close();
	
	string filenameA;
	filenameA = "JsonFiles/53_93_NORM_BEGe_PSD/JsonFile" + std::to_string(E0) + "_casoA.json";
	ifstream fileA(filenameA);
	json jA;
	fileA >> jA;
	fileA.close();
	
	double p0_U90_A = jA["90UpperLimit"]["p0_U90"].get<double>();
	double p0_L68_A = jA["68CentralRange"]["p0_L68"].get<double>();
	double p0_U68_A = jA["68CentralRange"]["p0_U68"].get<double>();
	double p1_U90_A = jA["90UpperLimit"]["p1_U90"].get<double>();
	double p1_L68_A = jA["68CentralRange"]["p1_L68"].get<double>();
	double p1_U68_A = jA["68CentralRange"]["p1_U68"].get<double>();
	double p0_GM_A = jA["GlobalMode"]["p0"].get<double>();
	double p1_GM_A = jA["GlobalMode"]["p1"].get<double>();
	
	double p0_U90_B_01 = jB_01["90UpperLimit"]["p0_U90"].get<double>();
	double p0_L68_B_01 = jB_01["68CentralRange"]["p0_L68"].get<double>();
	double p0_U68_B_01 = jB_01["68CentralRange"]["p0_U68"].get<double>();
	double p1_U90_B_01 = jB_01["90UpperLimit"]["p1_U90"].get<double>();
	double p1_L68_B_01 = jB_01["68CentralRange"]["p1_L68"].get<double>();
	double p1_U68_B_01 = jB_01["68CentralRange"]["p1_U68"].get<double>();
	double p0_GM_B_01 = jB_01["GlobalMode"]["p0"].get<double>();
	double p1_GM_B_01 = jB_01["GlobalMode"]["p1"].get<double>();
	
	double p0_U90_C_01 = jC_01["90UpperLimit"]["p0_U90"].get<double>();
	double p0_L68_C_01 = jC_01["68CentralRange"]["p0_L68"].get<double>();
	double p0_U68_C_01 = jC_01["68CentralRange"]["p0_U68"].get<double>();
	double p1_U90_C_01 = jC_01["90UpperLimit"]["p1_U90"].get<double>();
	double p1_L68_C_01 = jC_01["68CentralRange"]["p1_L68"].get<double>();
	double p1_U68_C_01 = jC_01["68CentralRange"]["p1_U68"].get<double>();
	double p0_GM_C_01 = jC_01["GlobalMode"]["p0"].get<double>();
	double p1_GM_C_01 = jC_01["GlobalMode"]["p1"].get<double>();
	
	double p0_U90_D_01 = jD_01["90UpperLimit"]["p0_U90"].get<double>();
	double p0_L68_D_01 = jD_01["68CentralRange"]["p0_L68"].get<double>();
	double p0_U68_D_01 = jD_01["68CentralRange"]["p0_U68"].get<double>();
	double p1_U90_D_01 = jD_01["90UpperLimit"]["p1_U90"].get<double>();
	double p1_L68_D_01 = jD_01["68CentralRange"]["p1_L68"].get<double>();
	double p1_U68_D_01 = jD_01["68CentralRange"]["p1_U68"].get<double>();
	double p0_GM_D_01 = jD_01["GlobalMode"]["p0"].get<double>();
	double p1_GM_D_01 = jD_01["GlobalMode"]["p1"].get<double>();
	
	cout << "\n DIFFERENZA % TRA:\tA - B (0.1)" << endl;
	cout << " 90qt. p0 diff. = " << ((p0_U90_B_01-p0_U90_A)/p0_U90_A)*100 << endl;
	cout << " 90qt. p1 diff. = " << ((p1_U90_B_01-p1_U90_A)/p1_U90_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " 68qt.(L) p0 diff. = " << ((p0_L68_B_01-p0_L68_A)/p0_L68_A)*100 << endl;
	cout << " 68qt.(L) p1 diff. = " << ((p1_L68_B_01-p1_L68_A)/p1_L68_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " 68qt.(U) p0 diff. = " << ((p0_U68_B_01-p0_U68_A)/p0_U68_A)*100 << endl;
	cout << " 68qt.(U) p1 diff. = " << ((p1_U68_B_01-p1_U68_A)/p1_U68_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " GM p0 diff. = " << ((p0_GM_B_01-p0_GM_A)/p0_GM_A)*100 << endl;
	cout << " GM p1 diff. = " << ((p1_GM_B_01-p1_GM_A)/p1_GM_A)*100 << endl;
	cout << "*************************************" << endl;
	cout << "\n DIFFERENZA % TRA:\tA - C (0.1)" << endl;
	cout << " 90qt. p0 diff. = " << ((p0_U90_C_01-p0_U90_A)/p0_U90_A)*100 << endl;
	cout << " 90qt. p1 diff. = " << ((p1_U90_C_01-p1_U90_A)/p1_U90_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " 68qt.(L) p0 diff. = " << ((p0_L68_C_01-p0_L68_A)/p0_L68_A)*100 << endl;
	cout << " 68qt.(L) p1 diff. = " << ((p1_L68_C_01-p1_L68_A)/p1_L68_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " 68qt.(U) p0 diff. = " << ((p0_U68_C_01-p0_U68_A)/p0_U68_A)*100 << endl;
	cout << " 68qt.(U) p1 diff. = " << ((p1_U68_C_01-p1_U68_A)/p1_U68_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " GM p0 diff. = " << ((p0_GM_C_01-p0_GM_A)/p0_GM_A)*100 << endl;
	cout << " GM p1 diff. = " << ((p1_GM_C_01-p1_GM_A)/p1_GM_A)*100 << endl;
	cout << "*************************************" << endl;
	cout << "\n DIFFERENZA % TRA:\tA - D (0.1)" << endl;
	cout << " 90qt. p0 diff. = " << ((p0_U90_D_01-p0_U90_A)/p0_U90_A)*100 << endl;
	cout << " 90qt. p1 diff. = " << ((p1_U90_D_01-p1_U90_A)/p1_U90_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " 68qt.(L) p0 diff. = " << ((p0_L68_D_01-p0_L68_A)/p0_L68_A)*100 << endl;
	cout << " 68qt.(L) p1 diff. = " << ((p1_L68_D_01-p1_L68_A)/p1_L68_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " 68qt.(U) p0 diff. = " << ((p0_U68_D_01-p0_U68_A)/p0_U68_A)*100 << endl;
	cout << " 68qt.(U) p1 diff. = " << ((p1_U68_D_01-p1_U68_A)/p1_U68_A)*100 << endl;
	cout << "-------------------------------------" << endl;
	cout << " GM p0 diff. = " << ((p0_GM_D_01-p0_GM_A)/p0_GM_A)*100 << endl;
	cout << " GM p1 diff. = " << ((p1_GM_D_01-p1_GM_A)/p1_GM_A)*100 << endl;
	cout << "*************************************" << endl;
	
	
	return 0;
}
