// Pedro Cipriano, Jul 2015
// FESB - Split, CMS
// Last Update: 28 Jul 2015
//
// 

#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>

using namespace std;

void pile_up_reweight()
{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  std::cout << "Pile Up Reweight" << endl;
  std::cout << "FESB - Split, CMS" << endl;
  std::cout << "-------------------------------------" << endl;
  std::cout << "Setup" << endl;

  //verbose level
  bool detail = false;
  bool show_steps = true;
  bool test = false; //if set will get some entries from histograms and save outputs with extension _test
  bool show_special_events = false;
  int max_special_events = 1000;

  if (detail) { std::cout << "Detail mode in enabled!" << endl; }
  if (show_steps) { std::cout << "All steps will be showed!" << endl; }
  if (test) { std::cout << "Test mode in enabled!" << endl; }

  std::cout << "-------------------------------------" << endl;

  int data_samples = 2;
  int mc_samples = 2;
  string data_sample[2];
  string mc_sample[2];
  string out[2];
  string mc_prefix[2];

  mc_sample[0] = "/data_CMS/cms/cipriano/isolationNtuples_DYJetsToLL_RunIISpring15DR74_29_Jun_2015/DY.root";
  mc_sample[1] = "/data_CMS/cms/cipriano/isolationNtuples_ggH_RunIISpring15DR74_29_Jun_2015/ggH.root";

  data_sample[0] = "/data_CMS/cms/cipriano/isolationNtuples_SingleElectron_Run2015B_27_Jul_2015/SingleElectron.root";
  data_sample[1] = "/data_CMS/cms/cipriano/isolationNtuples_DoubleEg_Run2015B_27_Jul_2015/DoubleEG.root";

  out[0] = "output/Weights-DY.root";
  out[1] = "output/Weights-GluGluToH.root";

  TH1D *data_vertex_sum = new TH1D("data_vertex_sum","Number of Vertices;Number of Vertices;N/N_{total}",55,-0.5,54.5);
  TH1D *data_vertex1 = new TH1D("data_vertex1","Number of Vertices;Number of Vertices;N/N_{total}",55,-0.5,54.5);
  TH1D *data_vertex2 = new TH1D("data_vertex2","Number of Vertices;Number of Vertices;N/N_{total}",55,-0.5,54.5);

  TH1D *mc_vertex1 = new TH1D("mc_vertex1","Number of Vertices;Number of Vertices;N/N_{total}",55,-0.5,54.5);
  TH1D *mc_vertex2 = new TH1D("mc_vertex2","Number of Vertices;Number of Vertices;N/N_{total}",55,-0.5,54.5);

  TH1D *weight = new TH1D("weight","Number of Vertices;Number of Vertices;Weight",55,-0.5,54.5);

  data_vertex_sum->Sumw2();
  data_vertex1->Sumw2();
  data_vertex2->Sumw2();
  mc_vertex1->Sumw2();
  mc_vertex2->Sumw2();

  TChain* chaind[2];
  TChain* chainm[2];

  Int_t nPV;

  int total_events_data = 0;

  for (int s=0; s<data_samples; ++s)
    {

    chaind[s] = new TChain("tree");
    chaind[s]->Add(data_sample[s].c_str());

    cout << "Reading " << data_sample[s] << "..." << endl;

    chaind[s]->SetBranchAddress("nPV", &nPV);

    Int_t entries = chaind[s]->GetEntries();
    cout << "Total Events: " << entries << endl;
    total_events_data = total_events_data + entries;

    for (int z=0; z<entries; ++z)
	{
	chaind[s]->GetEntry(z);
	data_vertex_sum->Fill(nPV);
    	if (s == 0) { data_vertex1->Fill(nPV); }
    	if (s == 1) { data_vertex2->Fill(nPV); }
	}
  }

  normalize_histogram(data_vertex_sum, "data_vertex_sum", true, false);
  normalize_histogram(data_vertex1, "data_vertex1", true, false);
  normalize_histogram(data_vertex2, "data_vertex2", true, false);

  cout << "Total Events in Data = "<< total_events_data << endl;

  for (int s=0; s<mc_samples; ++s)
    {

    weight->Reset();

    chainm[s] = new TChain("tree");
    chainm[s]->Add(mc_sample[s].c_str());

    cout << "Reading " << mc_sample[s] << "..." << endl;

    chainm[s]->SetBranchAddress("nPV", &nPV);

    Int_t entries = chainm[s]->GetEntries();
    cout << "Total Events: " << entries << endl;

    for (int z=0; z<entries; ++z)
	{
	chainm[s]->GetEntry(z);
    	if (s == 0) { mc_vertex1->Fill(nPV); }
    	if (s == 1) { mc_vertex2->Fill(nPV); }
	}
	
	if (s == 0)
		{
		normalize_histogram(mc_vertex1, "mc_vertex1", true, false);
		weight->Divide(data_vertex_sum, mc_vertex1);
		plot_histogram(weight, "output/", "weight_dyjets", "DYJets", "bottom_left", true, false);
		}
	if (s == 1)
		{
		normalize_histogram(mc_vertex1, "mc_vertex1", true, false);
		weight->Divide(data_vertex_sum, mc_vertex2);
		plot_histogram(weight, "output/", "weight_ggh", "ggH", "bottom_left", true, false);
		}

     	//Open the output root file
     	TFile *data_output = TFile::Open( out[s].c_str() , "RECREATE");

     	//save histograms on the file
	data_vertex_sum->Write();
	data_vertex1->Write();
	data_vertex2->Write();
	if (s == 0) { mc_vertex1->Write(); }
	if (s == 1) { mc_vertex2->Write(); }

	weight->Write();

	//close the file
	data_output->Close();

  }

  plot_histogram(data_vertex_sum, "output/", "data_vertex_sum", "All data", "bottom_left", true, false);
  plot_histogram(data_vertex1, "output/", "data_vertex_singleelectron", "SingleElectron", "bottom_left", true, false);
  plot_histogram(data_vertex2, "output/", "data_vertex_doubleeg", "DoubleEG", "bottom_left", true, false);
  plot_histogram(mc_vertex1, "output/", "mc_vertex_dyjets", "DYJets", "bottom_left", true, false);
  plot_histogram(mc_vertex2, "output/", "mc_vertex_ggh", "ggH", "bottom_left", true, false);

  plot_4histograms(data_vertex_sum, "All Data", data_vertex1, "SingleElectron", data_vertex2, "DoubleEG", mc_vertex1, "DYJets", "output/", "data_vertex_dyjets", "top_left", true, 0, 1, false);
  plot_4histograms(data_vertex_sum, "All Data", data_vertex1, "SingleElectron", data_vertex2, "DoubleEG", mc_vertex2, "ggH", "output/", "data_vertex_ggh", "top_left", true, 0, 1, false);

  std::cout << "-------------------------------------" << endl;
  std::cout << "Execution ended!" << endl;
  std::cout << "-------------------------------------" << endl;
  std::cout << " " << endl;

}
