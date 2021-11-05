#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

//==============================================================================================================================================================
Int_t NumberOfRows(char *filename) {
  
        Int_t NumOfRows = 0;
        std::string line;
        std::ifstream file(filename);

        while (std::getline(file,line)) {
                ++NumOfRows;
        }

        //NumOfRows = NumOfRows -1 ; // if 1st line are comments

        return NumOfRows;
}//==============================================================================================================================================================
//==============================================================================================================================================================
//==============================================================================================================================================================
int DataToModel(int E_min, int E_max) {

	int n = E_max - E_min + 1;
	Double_t x[n], y[n], ymin_1[n], ymax_1[n], ymin_2[n], ymax_2[n], ymin_3[n], ymax_3[n];

	int det;
	cout << " * Det: coax (0), BEGe (1) or IC (2)? ";
	cin >> det;
	int phase;
	cout << " * Phase: 53-93 (0) or 53-114 (1)? ";
	cin >> phase;
	int norm;
	cout << " * Normalized (0) or not (1)? ";
	cin >> norm;
	int PSD;
	cout << " * Only PSD (0) or everything (1)? ";
	cin >> PSD;
	int prior;
	cout << " * Prior: coax (0), BEGe (1), IC (2) or constant (3)? ";
	cin >> prior;
	
	ofstream output("data_to_model.txt");
	
	for ( int E0=E_min; E0<=E_max; E0++ ) {
		// open files
		char input_L[300], input_M_B[300];
		if ( phase==0 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_coax_PSD_coaxP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_BEGe_PSD_coaxP/JsonFile%i.json", E0); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_coax_PSD_BEGeP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_BEGe_PSD_BEGeP/JsonFile%i.json", E0); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_coax_PSD_ConstantP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_BEGe_PSD_ConstantP/JsonFile%i.json", E0); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_coax_coaxP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_BEGe_coaxP/JsonFile%i.json", E0); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_coax_BEGeP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_BEGe_BEGeP/JsonFile%i.json", E0); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_coax_ConstantP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_NORM_BEGe_ConstantP/JsonFile%i.json", E0); }
					}
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
							if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_coax_PSD_coaxP/JsonFile%i.json", E0); }
							if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_BEGe_PSD_coaxP/JsonFile%i.json", E0); }
					}
					if ( prior==1 ) {
							if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_coax_PSD_BEGeP/JsonFile%i.json", E0); }
							if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_BEGe_PSD_BEGeP/JsonFile%i.json", E0); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
							if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_coax_PSD_ConstantP/JsonFile%i.json", E0); }
							if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_BEGe_PSD_ConstantP/JsonFile%i.json", E0); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_coax_coaxP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_BEGe_coaxP/JsonFile%i.json", E0); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_coax_BEGeP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_BEGe_BEGeP/JsonFile%i.json", E0); }
					}
					if ( prior==2 ) {}
					if ( prior==3 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_coax_ConstantP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_93_BEGe_ConstantP/JsonFile%i.json", E0); }
					}
				}
			}
		}
		if ( phase==1 ) {
			if ( norm==0 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_coax_PSD_coaxP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_BEGe_PSD_coaxP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_IC_PSD_coaxP/JsonFile%i.json", E0); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_coax_PSD_BEGeP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_BEGe_PSD_BEGeP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_IC_PSD_BEGeP/JsonFile%i.json", E0); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_coax_PSD_ICP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_BEGe_PSD_ICP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_IC_PSD_ICP/JsonFile%i.json", E0); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_coax_PSD_ConstantP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_BEGe_PSD_ConstantP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_IC_PSD_ConstantP/JsonFile%i.json", E0); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_coax_coaxP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_BEGe_coaxP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_IC_coaxP/JsonFile%i.json", E0); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_coax_BEGeP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_BEGe_BEGeP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_IC_BEGeP/JsonFile%i.json", E0); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_coax_ICP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_BEGe_ICP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_IC_ICP/JsonFile%i.json", E0); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_coax_ConstantP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_BEGe_ConstantP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_NORM_IC_ConstantP/JsonFile%i.json", E0); }
					}
				}
			}
			if ( norm==1 ) {
				if ( PSD==0 ) {
					if ( prior==0 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_coax_PSD_coaxP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_BEGe_PSD_coaxP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_IC_PSD_coaxP/JsonFile%i.json", E0); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_coax_PSD_BEGeP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_BEGe_PSD_BEGeP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_IC_PSD_BEGeP/JsonFile%i.json", E0); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_coax_PSD_ICP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_BEGe_PSD_ICP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_IC_PSD_ICP/JsonFile%i.json", E0); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_coax_PSD_ConstantP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_BEGe_PSD_ConstantP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_IC_PSD_ConstantP/JsonFile%i.json", E0); }
					}
				}
				if ( PSD==1 ) {
					if ( prior==0 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_coax_coaxP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_BEGe_coaxP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_IC_coaxP/JsonFile%i.json", E0); }
					}
					if ( prior==1 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_coax_BEGeP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_BEGe_BEGeP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_IC_BEGeP/JsonFile%i.json", E0); }
					}
					if ( prior==2 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_coax_ICP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_BEGe_ICP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_IC_ICP/JsonFile%i.json", E0); }
					}
					if ( prior==3 ) {
						if ( det==0 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_coax_ConstantP/JsonFile%i.json", E0); }
						if ( det==1 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_BEGe_ConstantP/JsonFile%i.json", E0); }
						if ( det==2 ) { sprintf(input_L, "/home/sofia/Analysis/PRL_analysis/JsonFiles/53_114_IC_ConstantP/JsonFile%i.json", E0); }
					}
				}
			}
		}
		if ( det==0 ) sprintf(input_M_B, "Draw/MC_EnrCoax.txt");
		if ( det==1 ) sprintf(input_M_B, "Draw/MC_EnrBEGe.txt");
		if ( det==2 ) sprintf(input_M_B, "Draw/MC_InvCoax.txt");
		ifstream file_L(input_L);
		ifstream file_M_B(input_M_B);
		
		json jread_L;
		file_L >> jread_L;
		file_L.close();
		
		Int_t rows_M_B = NumberOfRows(input_M_B);
		double data_M_B[rows_M_B][8];
		for ( int i=0; i<rows_M_B; i++ ) {
			for ( int j=0; j<8; j++ ) {
				file_M_B >> data_M_B[i][j];
			}
		}
		file_M_B.close();
		
		int k = 0;
		while ( data_M_B[k][0]!=E0 ) { k++; }
		
		double L = jread_L["90UpperLimit"]["E0_counts_U90"].get<double>(); // U90 limit
		double M = data_M_B[k][4]; // median
		double B1 = data_M_B[k][5]; // upper limit of 1/2/3 sigma bands
		double B2 = data_M_B[k][6];
		double B3 = data_M_B[k][7]; 
		double B = 0;
		int X = 0; // 1 (L in 1sigma), 2 (L in 2sigma), 3 (L in 3sigma)
		if ( L<B1 ) X = 1; B = B1;
		if ( L>=B1 && L<B2 ) X = 2; B = B2;
		if ( L>=B2 && L<B3 ) X = 3; B = B3;
		if ( L>B3 ) X = 4; // ?
		
		double delta_L = 0; ( (L-M) / (B-M) ) * X;
		
		/*cout << " L = " << L << endl;
		cout << " M = " << M << endl;
		cout << " X = " << X << endl;*/
		
		if ( L>=M ) {
			int line = E0-E_min;
			x[line] = E0;
			ymax_1[line] = 1;
			ymin_1[line] = 0;
			ymax_2[line] = 2;
			ymin_2[line] = 1;
			ymax_3[line] = 3;
			ymin_3[line] = 2;
			output << E0 << "\t" << delta_L << endl;
		}
	}
	output.close();
	
	TCanvas *c = new TCanvas();
	c->DrawFrame(x[0]-1, 0, x[n-1]+1, 5);
	TMultiGraph *mg = new TMultiGraph();
	mg->SetTitle("; Energy [keV]; Data/Model");
	mg->GetYaxis()->SetRangeUser(0, 5);
	
	// band-graph deinition
	TGraph *grmin_1 = new TGraph(n, x, ymin_1);
	TGraph *grmax_1 = new TGraph(n, x, ymax_1);
	TGraph *grshade_1 = new TGraph(2*n);
	TGraph *grmin_2 = new TGraph(n, x, ymin_2);
	TGraph *grmax_2 = new TGraph(n, x, ymax_2);
	TGraph *grshade_2 = new TGraph(2*n);
	TGraph *grmin_3 = new TGraph(n, x, ymin_3);
	TGraph *grmax_3 = new TGraph(n, x, ymax_3);
	TGraph *grshade_3 = new TGraph(2*n);
	// liine style
	grmin_1->SetLineWidth(0);
	grmax_1->SetLineWidth(0);
	grmin_2->SetLineWidth(0);
	grmax_2->SetLineWidth(0);
	grmin_3->SetLineWidth(0);
	grmax_3->SetLineWidth(0);
	grshade_1->SetLineWidth(0);
	grshade_2->SetLineWidth(0);
	grshade_3->SetLineWidth(0);
	// set point
	for ( int i=0; i<n; i++ ) {
		grshade_1->SetPoint(i, x[i], ymax_1[i]);
		grshade_1->SetPoint(n+i, x[n-i-1], ymin_1[n-i-1]);
		grshade_2->SetPoint(i, x[i], ymax_2[i]);
		grshade_2->SetPoint(n+i, x[n-i-1], ymin_2[n-i-1]);
		grshade_3->SetPoint(i, x[i], ymax_3[i]);
		grshade_3->SetPoint(n+i, x[n-i-1], ymin_3[n-i-1]);
	}
	// fill color
	grshade_1->SetFillColor(kGreen);
	grmin_1->SetLineColor(kGreen);
	grmax_1->SetLineColor(kGreen);
	grshade_2->SetFillColor(5);
	grmin_2->SetLineColor(5);
	grmax_2->SetLineColor(5);
	grshade_3->SetFillColor(2);
	grmin_3->SetLineColor(2);
	grmax_3->SetLineColor(2);
	
	TGraphErrors *g_deltaL = new TGraphErrors("data_to_model.txt");
	g_deltaL->SetMarkerStyle(20);
	
	mg->Add(grmin_1, "l");
	mg->Add(grmin_1, "l");
	mg->Add(grmin_2, "l");
	mg->Add(grmin_2, "l");
	mg->Add(grmin_3, "l");
	mg->Add(grmin_3, "l");
	mg->Add(grshade_3, "f");
	mg->Add(grshade_2, "f");
	mg->Add(grshade_1, "f");
	mg->Add(g_deltaL, "p");
	mg->Draw("AP");
	
	// legend
	auto *legend = new TLegend(.65, .65, .88, .88);
	char title2[200];
	if ( det==0 ) legend->SetHeader("EnrCoax dataset", "C"); // C = centred
	if ( det==1 ) legend->SetHeader("EnrBEGe dataset", "C"); 
	if ( det==2 ) legend->SetHeader("InvCoax dataset", "C");
	legend->AddEntry(grshade_1, "68.3% prob.", "f");
	legend->AddEntry(grshade_2, "95.5% prob.", "f");
	legend->AddEntry(grshade_3, "99.7% prob.", "f");
	legend->AddEntry(g_deltaL, "Data/Model", "p");
	legend->SetBorderSize(0);
	legend->Draw();

	return 0;
}
