// Pedro Cipriano, Jul 2015
// FESB - Split, CMS
// Last Update: 27 Jul 2015
//
// Plots histograms from root files

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>
#include <TGraph.h>

//#include "plot_histograms.h"

#include <iostream>
using namespace std;

void plot_validation()
{
  gROOT -> Reset();
  gROOT->SetStyle("Plain");

  std::cout << "Plot Electron Isolation - Validation" << endl;
  std::cout << "FESB - Split, CMS" << endl;
  std::cout << "-------------------------------------" << endl;
  std::cout << "Setup" << endl;

//verbose level
  bool detail = false;
  bool show_steps = true;
  bool test = false; //if set will get some entries from histograms and save outputs with extension _test

  if (detail) { std::cout << "Detail mode in enabled!" << endl; }
  if (show_steps) { std::cout << "All steps will be showed!" << endl; }
  if (test) { std::cout << "Test mode in enabled!" << endl; }

  cout << "-------------------------------------" << endl;

  // input files
  string datafile1 = "output/SingleElectron.root";
  string datafile2 = "output/DoubleEG.root";
  string mcfile1 = "output/ggH.root";
  string mcfile2 = "output/DY.root";

  // sets labels for the plots
  TString datalabel1 = "SingleElectron";
  TString datalabel2 = "DoubleEG";
  TString mclabel1 = "ggH";
  TString mclabel2 = "Drell-Yan";

  // sets output directory
  string path = "output/";

  // opens the files
  TFile *d1 = TFile::Open( datafile1.c_str() );
  TFile *d2 = TFile::Open( datafile2.c_str() );
  TFile *m1 = TFile::Open( mcfile1.c_str() );
  TFile *m2 = TFile::Open( mcfile2.c_str() );

  //Vertex Multiplicity Signal
  TH1D *vertex_multiplicity_signal1 = 0;
  TH1D *vertex_multiplicity_signal2 = 0;
  TH1D *vertex_multiplicity_signal3 = 0;

  d1->GetObject("vertex_multiplicity_signal",vertex_multiplicity_signal1);
  if (vertex_multiplicity_signal1 == 0) { cout << "vertex_multiplicity_signal not found!" << endl; return; }
  d2->GetObject("vertex_multiplicity_signal",vertex_multiplicity_signal2);
  if (vertex_multiplicity_signal2 == 0) { cout << "vertex_multiplicity_signal not found!" << endl; return; }
  m1->GetObject("vertex_multiplicity",vertex_multiplicity_signal3);
  if (vertex_multiplicity_signal3 == 0) { cout << "vertex_multiplicity_signal not found!" << endl; return; }

plot_3histograms(vertex_multiplicity_signal1, datalabel1, vertex_multiplicity_signal2, datalabel2, vertex_multiplicity_signal3, mclabel1, path, "val_vertex_multiplicity_signal", "bottom_left", true, false);


  //Vertex Multiplicity Background
  TH1D *vertex_multiplicity_bkg1 = 0;
  TH1D *vertex_multiplicity_bkg2 = 0;
  TH1D *vertex_multiplicity_bkg3 = 0;

  d1->GetObject("vertex_multiplicity_bkg",vertex_multiplicity_bkg1);
  if (vertex_multiplicity_bkg1 == 0) { cout << "vertex_multiplicity_bkg not found!" << endl; return; }
  d2->GetObject("vertex_multiplicity_bkg",vertex_multiplicity_bkg2);
  if (vertex_multiplicity_bkg2 == 0) { cout << "vertex_multiplicity_bkg not found!" << endl; return; }
  m2->GetObject("vertex_multiplicity",vertex_multiplicity_bkg3);
  if (vertex_multiplicity_bkg3 == 0) { cout << "vertex_multiplicity_bkg not found!" << endl; return; }

plot_3histograms(vertex_multiplicity_bkg1, datalabel1, vertex_multiplicity_bkg2, datalabel2, vertex_multiplicity_bkg3, mclabel2, path, "val_vertex_multiplicity_bkg", "bottom_left", true, false);


  //Rho Signal
  TH1D *evt_rho_signal1 = 0;
  TH1D *evt_rho_signal2 = 0;
  TH1D *evt_rho_signal3 = 0;

  d1->GetObject("evt_rho_signal",evt_rho_signal1);
  if (evt_rho_signal1 == 0) { cout << "evt_rho_signal not found!" << endl; return; }
  d2->GetObject("evt_rho_signal",evt_rho_signal2);
  if (evt_rho_signal2 == 0) { cout << "evt_rho_signal not found!" << endl; return; }
  m1->GetObject("evt_rho",evt_rho_signal3);
  if (evt_rho_signal3 == 0) { cout << "evt_rho_signal not found!" << endl; return; }

plot_3histograms(evt_rho_signal1, datalabel1, evt_rho_signal2, datalabel2, evt_rho_signal3, mclabel1, path, "val_evt_rho_signal", "bottom_left", true, false);


  //Rho Background
  TH1D *evt_rho_bkg1 = 0;
  TH1D *evt_rho_bkg2 = 0;
  TH1D *evt_rho_bkg3 = 0;

  d1->GetObject("evt_rho_bkg",evt_rho_bkg1);
  if (evt_rho_bkg1 == 0) { cout << "evt_rho_bkg not found!" << endl; return; }
  d2->GetObject("evt_rho_bkg",evt_rho_bkg2);
  if (evt_rho_bkg2 == 0) { cout << "evt_rho_bkg not found!" << endl; return; }
  m2->GetObject("evt_rho",evt_rho_bkg3);
  if (evt_rho_bkg3 == 0) { cout << "evt_rho_bkg not found!" << endl; return; }

plot_3histograms(evt_rho_bkg1, datalabel1, evt_rho_bkg2, datalabel2, evt_rho_bkg3, mclabel1, path, "val_evt_rho_bkg", "bottom_left", true, false);


  //Electron Multiplicity Signal
  TH1D *ele_multiplicity_signal1 = 0;
  TH1D *ele_multiplicity_signal2 = 0;
  TH1D *ele_multiplicity_signal3 = 0;

  d1->GetObject("reco_ele_multiplicity_signal",ele_multiplicity_signal1);
  if (ele_multiplicity_signal1 == 0) { cout << "ele_multiplicity_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_multiplicity_signal",ele_multiplicity_signal2);
  if (ele_multiplicity_signal2 == 0) { cout << "ele_multiplicity_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_multiplicity",ele_multiplicity_signal3);
  if (ele_multiplicity_signal3 == 0) { cout << "ele_multiplicity_signal not found!" << endl; return; }

plot_3histograms(ele_multiplicity_signal1, datalabel1, ele_multiplicity_signal2, datalabel2, ele_multiplicity_signal3, mclabel1, path, "val_ele_multiplicity_signal", "bottom_left", true, false);


  //Electron Multiplicity Background
  TH1D *ele_multiplicity_bkg1 = 0;
  TH1D *ele_multiplicity_bkg2 = 0;
  TH1D *ele_multiplicity_bkg3 = 0;

  d1->GetObject("reco_ele_multiplicity_bkg",ele_multiplicity_bkg1);
  if (ele_multiplicity_bkg1 == 0) { cout << "ele_multiplicity_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_multiplicity_bkg",ele_multiplicity_bkg2);
  if (ele_multiplicity_bkg2 == 0) { cout << "ele_multiplicity_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_multiplicity",ele_multiplicity_bkg3);
  if (ele_multiplicity_bkg3 == 0) { cout << "ele_multiplicity_bkg not found!" << endl; return; }

plot_3histograms(ele_multiplicity_bkg1, datalabel1, ele_multiplicity_bkg2, datalabel2, ele_multiplicity_bkg3, mclabel1, path, "val_ele_multiplicity_bkg", "bottom_left", true, false);


  //Electron pT Signal
  TH1D *ele_pt_signal1 = 0;
  TH1D *ele_pt_signal2 = 0;
  TH1D *ele_pt_signal3 = 0;

  d1->GetObject("reco_ele_pt_signal",ele_pt_signal1);
  if (ele_pt_signal1 == 0) { cout << "ele_pt_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pt_signal",ele_pt_signal2);
  if (ele_pt_signal2 == 0) { cout << "ele_pt_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pt",ele_pt_signal3);
  if (ele_pt_signal3 == 0) { cout << "ele_pt_signal not found!" << endl; return; }

plot_3histograms(ele_pt_signal1, datalabel1, ele_pt_signal2, datalabel2, ele_pt_signal3, mclabel1, path, "val_ele_pt_signal", "bottom_left", true, false);


  //Electron pT Background
  TH1D *ele_pt_bkg1 = 0;
  TH1D *ele_pt_bkg2 = 0;
  TH1D *ele_pt_bkg3 = 0;

  d1->GetObject("reco_ele_pt_bkg",ele_pt_bkg1);
  if (ele_pt_bkg1 == 0) { cout << "ele_pt_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pt_bkg",ele_pt_bkg2);
  if (ele_pt_bkg2 == 0) { cout << "reco_ele_pt_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pt",ele_pt_bkg3);
  if (ele_pt_bkg3 == 0) { cout << "reco_ele_pt_bkg not found!" << endl; return; }

plot_3histograms(ele_pt_bkg1, datalabel1, ele_pt_bkg2, datalabel2, ele_pt_bkg3, mclabel1, path, "val_ele_pt_bkg", "bottom_left", true, false);

  //Electron Eta Signal
  TH1D *ele_eta_signal1 = 0;
  TH1D *ele_eta_signal2 = 0;
  TH1D *ele_eta_signal3 = 0;

  d1->GetObject("reco_ele_eta_signal",ele_eta_signal1);
  if (ele_eta_signal1 == 0) { cout << "ele_eta_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_eta_signal",ele_eta_signal2);
  if (ele_eta_signal2 == 0) { cout << "ele_eta_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_eta",ele_eta_signal3);
  if (ele_eta_signal3 == 0) { cout << "ele_eta_signal not found!" << endl; return; }

plot_3histograms(ele_eta_signal1, datalabel1, ele_eta_signal2, datalabel2, ele_eta_signal3, mclabel1, path, "val_ele_eta_signal", "bottom_left", true, false);


  //Electron Eta Background
  TH1D *ele_eta_bkg1 = 0;
  TH1D *ele_eta_bkg2 = 0;
  TH1D *ele_eta_bkg3 = 0;

  d1->GetObject("reco_ele_eta_bkg",ele_eta_bkg1);
  if (ele_eta_bkg1 == 0) { cout << "ele_eta_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_eta_bkg",ele_eta_bkg2);
  if (ele_eta_bkg2 == 0) { cout << "reco_ele_eta_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_eta",ele_eta_bkg3);
  if (ele_eta_bkg3 == 0) { cout << "reco_ele_eta_bkg not found!" << endl; return; }

plot_3histograms(ele_eta_bkg1, datalabel1, ele_eta_bkg2, datalabel2, ele_eta_bkg3, mclabel1, path, "val_ele_eta_bkg", "bottom_left", true, false);


  //Electron Phi Signal
  TH1D *ele_phi_signal1 = 0;
  TH1D *ele_phi_signal2 = 0;
  TH1D *ele_phi_signal3 = 0;

  d1->GetObject("reco_ele_phi_signal",ele_phi_signal1);
  if (ele_phi_signal1 == 0) { cout << "ele_phi_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_phi_signal",ele_phi_signal2);
  if (ele_phi_signal2 == 0) { cout << "ele_phi_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_phi",ele_phi_signal3);
  if (ele_phi_signal3 == 0) { cout << "ele_phi_signal not found!" << endl; return; }

plot_3histograms(ele_phi_signal1, datalabel1, ele_phi_signal2, datalabel2, ele_phi_signal3, mclabel1, path, "val_ele_phi_signal", "bottom_left", true, false);


  //Electron Phi Background
  TH1D *ele_phi_bkg1 = 0;
  TH1D *ele_phi_bkg2 = 0;
  TH1D *ele_phi_bkg3 = 0;

  d1->GetObject("reco_ele_phi_bkg",ele_phi_bkg1);
  if (ele_phi_bkg1 == 0) { cout << "ele_phi_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_phi_bkg",ele_phi_bkg2);
  if (ele_phi_bkg2 == 0) { cout << "reco_ele_phi_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_phi",ele_phi_bkg3);
  if (ele_phi_bkg3 == 0) { cout << "reco_ele_phi_bkg not found!" << endl; return; }

plot_3histograms(ele_phi_bkg1, datalabel1, ele_phi_bkg2, datalabel2, ele_phi_bkg3, mclabel1, path, "val_ele_phi_bkg", "bottom_left", true, false);


  //Electron Charge Signal
  TH1D *ele_charge_signal1 = 0;
  TH1D *ele_charge_signal2 = 0;
  TH1D *ele_charge_signal3 = 0;

  d1->GetObject("reco_ele_charge_signal",ele_charge_signal1);
  if (ele_charge_signal1 == 0) { cout << "ele_charge_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_charge_signal",ele_charge_signal2);
  if (ele_charge_signal2 == 0) { cout << "ele_charge_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_charge",ele_charge_signal3);
  if (ele_charge_signal3 == 0) { cout << "ele_charge_signal not found!" << endl; return; }

plot_3histograms(ele_charge_signal1, datalabel1, ele_charge_signal2, datalabel2, ele_charge_signal3, mclabel1, path, "val_ele_charge_signal", "bottom_left", true, false);


  //Electron Charge Background
  TH1D *ele_charge_bkg1 = 0;
  TH1D *ele_charge_bkg2 = 0;
  TH1D *ele_charge_bkg3 = 0;

  d1->GetObject("reco_ele_charge_bkg",ele_charge_bkg1);
  if (ele_charge_bkg1 == 0) { cout << "ele_charge_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_charge_bkg",ele_charge_bkg2);
  if (ele_charge_bkg2 == 0) { cout << "reco_ele_charge_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_charge",ele_charge_bkg3);
  if (ele_charge_bkg3 == 0) { cout << "reco_ele_charge_bkg not found!" << endl; return; }

plot_3histograms(ele_charge_bkg1, datalabel1, ele_charge_bkg2, datalabel2, ele_charge_bkg3, mclabel1, path, "val_ele_charge_bkg", "bottom_left", true, false);

}
