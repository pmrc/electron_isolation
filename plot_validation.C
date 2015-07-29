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
  string mcfile1 = "output/GluGluToH.root";
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

plot_3histograms(evt_rho_bkg1, datalabel1, evt_rho_bkg2, datalabel2, evt_rho_bkg3, mclabel2, path, "val_evt_rho_bkg", "bottom_left", true, false);


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

plot_3histograms(ele_multiplicity_bkg1, datalabel1, ele_multiplicity_bkg2, datalabel2, ele_multiplicity_bkg3, mclabel2, path, "val_ele_multiplicity_bkg", "bottom_left", true, false);


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

plot_3histograms(ele_pt_bkg1, datalabel1, ele_pt_bkg2, datalabel2, ele_pt_bkg3, mclabel2, path, "val_ele_pt_bkg", "bottom_left", true, false);

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

plot_3histograms(ele_eta_bkg1, datalabel1, ele_eta_bkg2, datalabel2, ele_eta_bkg3, mclabel2, path, "val_ele_eta_bkg", "bottom_left", true, false);


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

plot_3histograms(ele_phi_bkg1, datalabel1, ele_phi_bkg2, datalabel2, ele_phi_bkg3, mclabel2, path, "val_ele_phi_bkg", "bottom_left", true, false);


  //Electron Charge Signal
  TH1D *ele_charge_signal1 = 0;
  TH1D *ele_charge_signal2 = 0;
  TH1D *ele_charge_signal3 = 0;

  d1->GetObject("reco_ele_charge_signal",ele_charge_signal1);
  if (ele_charge_signal1 == 0) { cout << "ele_charge_signal1 not found!" << endl; return; }
  d2->GetObject("reco_ele_charge_signal",ele_charge_signal2);
  if (ele_charge_signal2 == 0) { cout << "ele_charge_signal2 not found!" << endl; return; }
  //m1->GetObject("reco_ele_charge",ele_charge_signal3);
  //if (ele_charge_signal3 == 0) { cout << "ele_charge_signal3 not found!" << endl; return; }

//plot_3histograms(ele_charge_signal1, datalabel1, ele_charge_signal2, datalabel2, ele_charge_signal3, mclabel1, path, "val_ele_charge_signal", "bottom_left", true, false);
plot_2histograms(ele_charge_signal1, datalabel1, ele_charge_signal2, datalabel2, path, "val_ele_charge_signal", "bottom_left", true, false);


  //Electron Charge Background
  TH1D *ele_charge_bkg1 = 0;
  TH1D *ele_charge_bkg2 = 0;
  TH1D *ele_charge_bkg3 = 0;

  d1->GetObject("reco_ele_charge_bkg",ele_charge_bkg1);
  if (ele_charge_bkg1 == 0) { cout << "reco_ele_charge_bkg1 not found!" << endl; return; }
  d2->GetObject("reco_ele_charge_bkg",ele_charge_bkg2);
  if (ele_charge_bkg2 == 0) { cout << "reco_ele_charge_bkg2 not found!" << endl; return; }
  //m2->GetObject("reco_ele_charge",ele_charge_bkg3);
  //if (ele_charge_bkg3 == 0) { cout << "reco_ele_charge_bkg3 not found!" << endl; return; }

//plot_3histograms(ele_charge_bkg1, datalabel1, ele_charge_bkg2, datalabel2, ele_charge_bkg3, mclabel2, path, "val_ele_charge_bkg", "bottom_left", true, false);
plot_2histograms(ele_charge_bkg1, datalabel1, ele_charge_bkg2, datalabel2, path, "val_ele_charge_bkg", "bottom_left", true, false);


  //Electron Effective Area Signal
  TH1D *ele_effarea_signal1 = 0;
  TH1D *ele_effarea_signal2 = 0;
  TH1D *ele_effarea_signal3 = 0;

  d1->GetObject("reco_ele_effarea_signal",ele_effarea_signal1);
  if (ele_effarea_signal1 == 0) { cout << "ele_effarea_signal1 not found!" << endl; return; }
  d2->GetObject("reco_ele_effarea_signal",ele_effarea_signal2);
  if (ele_effarea_signal2 == 0) { cout << "ele_effarea_signal2 not found!" << endl; return; }
  m1->GetObject("reco_ele_effarea",ele_effarea_signal3);
  if (ele_effarea_signal3 == 0) { cout << "ele_effarea_signal3 not found!" << endl; return; }

plot_3histograms(ele_effarea_signal1, datalabel1, ele_effarea_signal2, datalabel2, ele_effarea_signal3, mclabel1, path, "val_ele_effarea_signal", "top_right", true, false);

  //Electron Effective Area Background
  TH1D *ele_effarea_bkg1 = 0;
  TH1D *ele_effarea_bkg2 = 0;
  TH1D *ele_effarea_bkg3 = 0;

  d1->GetObject("reco_ele_effarea_bkg",ele_effarea_bkg1);
  if (ele_effarea_bkg1 == 0) { cout << "ele_effarea_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_effarea_bkg",ele_effarea_bkg2);
  if (ele_effarea_bkg2 == 0) { cout << "ele_effarea_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_effarea",ele_effarea_bkg3);
  if (ele_effarea_bkg3 == 0) { cout << "ele_effarea_bkg not found!" << endl; return; }

plot_3histograms(ele_effarea_bkg1, datalabel1, ele_effarea_bkg2, datalabel2, ele_effarea_bkg3, mclabel2, path, "val_ele_effarea_bkg", "top_right", true, false);



  //Electron dxy Signal
  TH1D *ele_dxy_signal1 = 0;
  TH1D *ele_dxy_signal2 = 0;
  TH1D *ele_dxy_signal3 = 0;

  d1->GetObject("reco_ele_dxy_signal", ele_dxy_signal1);
  if (ele_dxy_signal1 == 0) { cout << "ele_dxy_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_dxy_signal", ele_dxy_signal2);
  if (ele_dxy_signal2 == 0) { cout << "ele_dxy_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_dxy", ele_dxy_signal3);
  if (ele_dxy_signal3 == 0) { cout << "ele_dxy_signal not found!" << endl; return; }

plot_3histograms(ele_dxy_signal1, datalabel1, ele_dxy_signal2, datalabel2, ele_dxy_signal3, mclabel1, path, "val_ele_dxy_signal", "bottom_left", true, false);


  //Electron dxy Background
  TH1D *ele_dxy_bkg1 = 0;
  TH1D *ele_dxy_bkg2 = 0;
  TH1D *ele_dxy_bkg3 = 0;

  d1->GetObject("reco_ele_dxy_bkg", ele_dxy_bkg1);
  if (ele_dxy_bkg1 == 0) { cout << "ele_dxy_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_dxy_bkg", ele_dxy_bkg2);
  if (ele_dxy_bkg2 == 0) { cout << "ele_dxy_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_dxy", ele_dxy_bkg3);
  if (ele_dxy_bkg3 == 0) { cout << "ele_dxy_bkg not found!" << endl; return; }

plot_3histograms(ele_dxy_bkg1, datalabel1, ele_dxy_bkg2, datalabel2, ele_dxy_bkg3, mclabel2, path, "val_ele_dxy_bkg", "bottom_left", true, false);


  //Electron dz Signal
  TH1D *ele_dz_signal1 = 0;
  TH1D *ele_dz_signal2 = 0;
  TH1D *ele_dz_signal3 = 0;

  d1->GetObject("reco_ele_dz_signal", ele_dz_signal1);
  if (ele_dz_signal1 == 0) { cout << "ele_dz_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_dz_signal", ele_dz_signal2);
  if (ele_dz_signal2 == 0) { cout << "ele_dz_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_dz", ele_dz_signal3);
  if (ele_dz_signal3 == 0) { cout << "ele_dz_signal not found!" << endl; return; }

plot_3histograms(ele_dz_signal1, datalabel1, ele_dz_signal2, datalabel2, ele_dz_signal3, mclabel1, path, "val_ele_dz_signal", "bottom_left", true, false);


  //Electron dz Background
  TH1D *ele_dz_bkg1 = 0;
  TH1D *ele_dz_bkg2 = 0;
  TH1D *ele_dz_bkg3 = 0;

  d1->GetObject("reco_ele_dz_bkg", ele_dz_bkg1);
  if (ele_dz_bkg1 == 0) { cout << "ele_dz_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_dz_bkg", ele_dz_bkg2);
  if (ele_dz_bkg2 == 0) { cout << "ele_dz_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_dz", ele_dz_bkg3);
  if (ele_dz_bkg3 == 0) { cout << "ele_dz_bkg not found!" << endl; return; }

plot_3histograms(ele_dz_bkg1, datalabel1, ele_dz_bkg2, datalabel2, ele_dz_bkg3, mclabel2, path, "val_ele_dz_bkg", "bottom_left", true, false);


  //Electron Missing Hits Signal
  TH1D *ele_missinghit_signal1 = 0;
  TH1D *ele_missinghit_signal2 = 0;
  TH1D *ele_missinghit_signal3 = 0;

  d1->GetObject("reco_ele_missinghit_signal", ele_missinghit_signal1);
  if (ele_missinghit_signal1 == 0) { cout << "ele_missinghit_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_missinghit_signal", ele_missinghit_signal2);
  if (ele_missinghit_signal2 == 0) { cout << "ele_missinghit_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_missinghit", ele_missinghit_signal3);
  if (ele_missinghit_signal3 == 0) { cout << "ele_missinghit_signal not found!" << endl; return; }

plot_3histograms(ele_missinghit_signal1, datalabel1, ele_missinghit_signal2, datalabel2, ele_missinghit_signal3, mclabel1, path, "val_ele_missinghit_signal", "bottom_left", true, false);


  //Electron Missing Hits Background
  TH1D *ele_missinghit_bkg1 = 0;
  TH1D *ele_missinghit_bkg2 = 0;
  TH1D *ele_missinghit_bkg3 = 0;

  d1->GetObject("reco_ele_missinghit_bkg", ele_missinghit_bkg1);
  if (ele_missinghit_bkg1 == 0) { cout << "ele_missinghit_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_missinghit_bkg", ele_missinghit_bkg2);
  if (ele_missinghit_bkg2 == 0) { cout << "ele_missinghit_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_missinghit", ele_missinghit_bkg3);
  if (ele_missinghit_bkg3 == 0) { cout << "ele_missinghit_bkg not found!" << endl; return; }

plot_3histograms(ele_missinghit_bkg1, datalabel1, ele_missinghit_bkg2, datalabel2, ele_missinghit_bkg3, mclabel2, path, "val_ele_missinghit_bkg", "bottom_left", true, false);

  //Electron PF Charged Hadron Isolation Signal
  TH1D *ele_pfchhadiso_signal1 = 0;
  TH1D *ele_pfchhadiso_signal2 = 0;
  TH1D *ele_pfchhadiso_signal3 = 0;

  d1->GetObject("reco_ele_pfchhadiso_signal", ele_pfchhadiso_signal1);
  if (ele_pfchhadiso_signal1 == 0) { cout << "ele_pfchhadiso_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchhadiso_signal", ele_pfchhadiso_signal2);
  if (ele_pfchhadiso_signal2 == 0) { cout << "ele_pfchhadiso_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfchhadiso", ele_pfchhadiso_signal3);
  if (ele_pfchhadiso_signal3 == 0) { cout << "ele_pfchhadiso_signal not found!" << endl; return; }

plot_3histograms(ele_pfchhadiso_signal1, datalabel1, ele_pfchhadiso_signal2, datalabel2, ele_pfchhadiso_signal3, mclabel1, path, "val_ele_pfchhadiso_signal", "bottom_left", true, false);

  //Electron PF Charged Hadron Isolation Background
  TH1D *ele_pfchhadiso_bkg1 = 0;
  TH1D *ele_pfchhadiso_bkg2 = 0;
  TH1D *ele_pfchhadiso_bkg3 = 0;

  d1->GetObject("reco_ele_pfchhadiso_bkg", ele_pfchhadiso_bkg1);
  if (ele_pfchhadiso_bkg1 == 0) { cout << "ele_pfchhadiso_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchhadiso_bkg", ele_pfchhadiso_bkg2);
  if (ele_pfchhadiso_bkg2 == 0) { cout << "ele_pfchhadiso_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfchhadiso", ele_pfchhadiso_bkg3);
  if (ele_pfchhadiso_bkg3 == 0) { cout << "ele_pfchhadiso_bkg not found!" << endl; return; }

plot_3histograms(ele_pfchhadiso_bkg1, datalabel1, ele_pfchhadiso_bkg2, datalabel2, ele_pfchhadiso_bkg3, mclabel2, path, "val_ele_pfchhadiso_bkg", "bottom_left", true, false);


  //Electron PF Charged Hadron Isolation Relative Signal
  TH1D *ele_pfchhadisorel_signal1 = 0;
  TH1D *ele_pfchhadisorel_signal2 = 0;
  TH1D *ele_pfchhadisorel_signal3 = 0;

  d1->GetObject("reco_ele_pfchhadisorel_signal", ele_pfchhadisorel_signal1);
  if (ele_pfchhadisorel_signal1 == 0) { cout << "ele_pfchhadisorel_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchhadisorel_signal", ele_pfchhadisorel_signal2);
  if (ele_pfchhadisorel_signal2 == 0) { cout << "ele_pfchhadisorel_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfchhadisorel", ele_pfchhadisorel_signal3);
  if (ele_pfchhadisorel_signal3 == 0) { cout << "ele_pfchhadisorel_signal not found!" << endl; return; }

plot_3histograms(ele_pfchhadisorel_signal1, datalabel1, ele_pfchhadisorel_signal2, datalabel2, ele_pfchhadisorel_signal3, mclabel1, path, "val_ele_pfchhadisorel_signal", "top_right", true, false);

  //Electron PF Charged Hadron Isolation Relative Background
  TH1D *ele_pfchhadisorel_bkg1 = 0;
  TH1D *ele_pfchhadisorel_bkg2 = 0;
  TH1D *ele_pfchhadisorel_bkg3 = 0;

  d1->GetObject("reco_ele_pfchhadisorel_bkg", ele_pfchhadisorel_bkg1);
  if (ele_pfchhadisorel_bkg1 == 0) { cout << "ele_pfchhadisorel_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchhadisorel_bkg", ele_pfchhadisorel_bkg2);
  if (ele_pfchhadisorel_bkg2 == 0) { cout << "ele_pfchhadisorel_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfchhadisorel", ele_pfchhadisorel_bkg3);
  if (ele_pfchhadisorel_bkg3 == 0) { cout << "ele_pfchhadisorel_bkg not found!" << endl; return; }

plot_3histograms(ele_pfchhadisorel_bkg1, datalabel1, ele_pfchhadisorel_bkg2, datalabel2, ele_pfchhadisorel_bkg3, mclabel2, path, "val_ele_pfchhadisorel_bkg", "top_right", true, false);


  //Electron PF Charged Hadron Isolation Barrel Signal
  TH1D *ele_pfchhadiso_barrel_signal1 = 0;
  TH1D *ele_pfchhadiso_barrel_signal2 = 0;
  TH1D *ele_pfchhadiso_barrel_signal3 = 0;

  d1->GetObject("reco_ele_pfchhadiso_barrel_signal", ele_pfchhadiso_barrel_signal1);
  if (ele_pfchhadiso_barrel_signal1 == 0) { cout << "ele_pfchhadiso_barrel_signal1 not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchhadiso_barrel_signal", ele_pfchhadiso_barrel_signal2);
  if (ele_pfchhadiso_barrel_signal2 == 0) { cout << "ele_pfchhadiso_barrel_signal2 not found!" << endl; return; }
  m1->GetObject("reco_ele_pfchhadiso_barrel", ele_pfchhadiso_barrel_signal3);
  if (ele_pfchhadiso_barrel_signal3 == 0) { cout << "ele_pfchhadiso_barrel_signal3 not found!" << endl; return; }

plot_3histograms(ele_pfchhadiso_barrel_signal1, datalabel1, ele_pfchhadiso_barrel_signal2, datalabel2, ele_pfchhadiso_barrel_signal3, mclabel1, path, "val_ele_pfchhadiso_barrel_signal", "top_right", true, false);

  //Electron PF Charged Hadron Isolation Barrel Background
  TH1D *ele_pfchhadiso_barrel_bkg1 = 0;
  TH1D *ele_pfchhadiso_barrel_bkg2 = 0;
  TH1D *ele_pfchhadiso_barrel_bkg3 = 0;

  d1->GetObject("reco_ele_pfchhadiso_barrel_bkg", ele_pfchhadiso_barrel_bkg1);
  if (ele_pfchhadiso_barrel_bkg1 == 0) { cout << "ele_pfchhadiso_barrel_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchhadiso_barrel_bkg", ele_pfchhadiso_barrel_bkg2);
  if (ele_pfchhadiso_barrel_bkg2 == 0) { cout << "ele_pfchhadiso_barrel_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfchhadiso_barrel", ele_pfchhadiso_barrel_bkg3);
  if (ele_pfchhadiso_barrel_bkg3 == 0) { cout << "ele_pfchhadiso_barrel_bkg not found!" << endl; return; }

plot_3histograms(ele_pfchhadiso_barrel_bkg1, datalabel1, ele_pfchhadiso_barrel_bkg2, datalabel2, ele_pfchhadiso_barrel_bkg3, mclabel2, path, "val_ele_pfchhadiso_barrel_bkg", "top_right", true, false);


  //Electron PF Charged Hadron Isolation EndCap Signal
  TH1D *ele_pfchhadiso_endcap_signal1 = 0;
  TH1D *ele_pfchhadiso_endcap_signal2 = 0;
  TH1D *ele_pfchhadiso_endcap_signal3 = 0;

  d1->GetObject("reco_ele_pfchhadiso_endcap_signal", ele_pfchhadiso_endcap_signal1);
  if (ele_pfchhadiso_endcap_signal1 == 0) { cout << "ele_pfchhadiso_endcap_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchhadiso_endcap_signal", ele_pfchhadiso_endcap_signal2);
  if (ele_pfchhadiso_endcap_signal2 == 0) { cout << "ele_pfchhadiso_endcap_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfchhadiso_endcap", ele_pfchhadiso_endcap_signal3);
  if (ele_pfchhadiso_endcap_signal3 == 0) { cout << "ele_pfchhadiso_endcap_signal not found!" << endl; return; }

plot_3histograms(ele_pfchhadiso_endcap_signal1, datalabel1, ele_pfchhadiso_endcap_signal2, datalabel2, ele_pfchhadiso_endcap_signal3, mclabel1, path, "val_ele_pfchhadiso_endcap_signal", "top_right", true, false);

  //Electron PF Charged Hadron Isolation EndCap Background
  TH1D *ele_pfchhadiso_endcap_bkg1 = 0;
  TH1D *ele_pfchhadiso_endcap_bkg2 = 0;
  TH1D *ele_pfchhadiso_endcap_bkg3 = 0;

  d1->GetObject("reco_ele_pfchhadiso_endcap_bkg", ele_pfchhadiso_endcap_bkg1);
  if (ele_pfchhadiso_endcap_bkg1 == 0) { cout << "ele_pfchhadiso_endcap_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchhadiso_endcap_bkg", ele_pfchhadiso_endcap_bkg2);
  if (ele_pfchhadiso_endcap_bkg2 == 0) { cout << "ele_pfchhadiso_endcap_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfchhadiso_endcap", ele_pfchhadiso_endcap_bkg3);
  if (ele_pfchhadiso_endcap_bkg3 == 0) { cout << "ele_pfchhadiso_endcap_bkg not found!" << endl; return; }

plot_3histograms(ele_pfchhadiso_endcap_bkg1, datalabel1, ele_pfchhadiso_endcap_bkg2, datalabel2, ele_pfchhadiso_endcap_bkg3, mclabel2, path, "val_ele_pfchhadiso_endcap_bkg", "top_right", true, false);

  //Electron PF Neutral Hadron Isolation Signal
  TH1D *ele_pfnehadiso_signal1 = 0;
  TH1D *ele_pfnehadiso_signal2 = 0;
  TH1D *ele_pfnehadiso_signal3 = 0;

  d1->GetObject("reco_ele_pfnehadiso_signal", ele_pfnehadiso_signal1);
  if (ele_pfnehadiso_signal1 == 0) { cout << "ele_pfnehadiso_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfnehadiso_signal", ele_pfnehadiso_signal2);
  if (ele_pfnehadiso_signal2 == 0) { cout << "ele_pfnehadiso_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfnehadiso", ele_pfnehadiso_signal3);
  if (ele_pfnehadiso_signal3 == 0) { cout << "ele_pfnehadiso_signal not found!" << endl; return; }

plot_3histograms(ele_pfnehadiso_signal1, datalabel1, ele_pfnehadiso_signal2, datalabel2, ele_pfnehadiso_signal3, mclabel1, path, "val_ele_pfnehadiso_signal", "top_right", true, false);


  //Electron PF Neutral Hadron Isolation Background
  TH1D *ele_pfnehadiso_bkg1 = 0;
  TH1D *ele_pfnehadiso_bkg2 = 0;
  TH1D *ele_pfnehadiso_bkg3 = 0;

  d1->GetObject("reco_ele_pfnehadiso_bkg", ele_pfnehadiso_bkg1);
  if (ele_pfnehadiso_bkg1 == 0) { cout << "ele_pfnehadiso_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfnehadiso_bkg", ele_pfnehadiso_bkg2);
  if (ele_pfnehadiso_bkg2 == 0) { cout << "ele_pfnehadiso_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfnehadiso", ele_pfnehadiso_bkg3);
  if (ele_pfnehadiso_bkg3 == 0) { cout << "ele_pfnehadiso_bkg not found!" << endl; return; }

plot_3histograms(ele_pfnehadiso_bkg1, datalabel1, ele_pfnehadiso_bkg2, datalabel2, ele_pfnehadiso_bkg3, mclabel2, path, "val_ele_pfnehadiso_bkg", "top_right", true, false);


  //Electron PF Neutral Hadron Relative Isolation Signal
  TH1D *ele_pfnehadisorel_signal1 = 0;
  TH1D *ele_pfnehadisorel_signal2 = 0;
  TH1D *ele_pfnehadisorel_signal3 = 0;

  d1->GetObject("reco_ele_pfnehadisorel_signal", ele_pfnehadisorel_signal1);
  if (ele_pfnehadisorel_signal1 == 0) { cout << "ele_pfnehadisorel_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfnehadisorel_signal", ele_pfnehadisorel_signal2);
  if (ele_pfnehadisorel_signal2 == 0) { cout << "ele_pfnehadisorel_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfnehadisorel", ele_pfnehadisorel_signal3);
  if (ele_pfnehadisorel_signal3 == 0) { cout << "ele_pfnehadisorel_signal not found!" << endl; return; }

plot_3histograms(ele_pfnehadisorel_signal1, datalabel1, ele_pfnehadisorel_signal2, datalabel2, ele_pfnehadisorel_signal3, mclabel1, path, "val_ele_pfnehadisorel_signal", "top_right", true, false);


  //Electron PF Neutral Hadron Relative Isolation Background
  TH1D *ele_pfnehadisorel_bkg1 = 0;
  TH1D *ele_pfnehadisorel_bkg2 = 0;
  TH1D *ele_pfnehadisorel_bkg3 = 0;

  d1->GetObject("reco_ele_pfnehadisorel_bkg", ele_pfnehadisorel_bkg1);
  if (ele_pfnehadisorel_bkg1 == 0) { cout << "ele_pfnehadisorel_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfnehadisorel_bkg", ele_pfnehadisorel_bkg2);
  if (ele_pfnehadisorel_bkg2 == 0) { cout << "ele_pfnehadisorel_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfnehadisorel", ele_pfnehadisorel_bkg3);
  if (ele_pfnehadisorel_bkg3 == 0) { cout << "ele_pfnehadisorel_bkg not found!" << endl; return; }

plot_3histograms(ele_pfnehadisorel_bkg1, datalabel1, ele_pfnehadisorel_bkg2, datalabel2, ele_pfnehadisorel_bkg3, mclabel2, path, "val_ele_pfnehadisorel_bkg", "top_right", true, false);


  //Electron PF Neutral Hadron Isolation Barrel Signal
  TH1D *ele_pfnehadiso_barrel_signal1 = 0;
  TH1D *ele_pfnehadiso_barrel_signal2 = 0;
  TH1D *ele_pfnehadiso_barrel_signal3 = 0;

  d1->GetObject("reco_ele_pfnehadiso_barrel_signal", ele_pfnehadiso_barrel_signal1);
  if (ele_pfnehadiso_barrel_signal1 == 0) { cout << "ele_pfnehadiso_barrel_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfnehadiso_barrel_signal", ele_pfnehadiso_barrel_signal2);
  if (ele_pfnehadiso_barrel_signal2 == 0) { cout << "ele_pfnehadiso_barrel_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfnehadiso_barrel", ele_pfnehadiso_barrel_signal3);
  if (ele_pfnehadiso_barrel_signal3 == 0) { cout << "ele_pfnehadiso_barrel_signal not found!" << endl; return; }

plot_3histograms(ele_pfnehadiso_barrel_signal1, datalabel1, ele_pfnehadiso_barrel_signal2, datalabel2, ele_pfnehadiso_barrel_signal3, mclabel1, path, "val_ele_pfnehadiso_barrel_signal", "top_right", true, false);

  //Electron PF Neutral Hadron Isolation Barrel Background
  TH1D *ele_pfnehadiso_barrel_bkg1 = 0;
  TH1D *ele_pfnehadiso_barrel_bkg2 = 0;
  TH1D *ele_pfnehadiso_barrel_bkg3 = 0;

  d1->GetObject("reco_ele_pfnehadiso_barrel_bkg", ele_pfnehadiso_barrel_bkg1);
  if (ele_pfnehadiso_barrel_bkg1 == 0) { cout << "ele_pfnehadiso_barrel_bkg1 not found!" << endl; return; }
  d2->GetObject("reco_ele_pfnehadiso_barrel_bkg", ele_pfnehadiso_barrel_bkg2);
  if (ele_pfnehadiso_barrel_bkg2 == 0) { cout << "ele_pfnehadiso_barrel_bkg2 not found!" << endl; return; }
  m2->GetObject("reco_ele_pfnehadiso_barrel", ele_pfnehadiso_barrel_bkg3);
  if (ele_pfnehadiso_barrel_bkg3 == 0) { cout << "ele_pfnehadiso_barrel_bkg3 not found!" << endl; return; }

plot_3histograms(ele_pfnehadiso_barrel_bkg1, datalabel1, ele_pfnehadiso_barrel_bkg2, datalabel2, ele_pfnehadiso_barrel_bkg3, mclabel2, path, "val_ele_pfnehadiso_barrel_bkg", "top_right", true, false);


  //Electron PF Neutral Hadron Isolation EndCap Signal
  TH1D *ele_pfnehadiso_endcap_signal1 = 0;
  TH1D *ele_pfnehadiso_endcap_signal2 = 0;
  TH1D *ele_pfnehadiso_endcap_signal3 = 0;

  d1->GetObject("reco_ele_pfnehadiso_endcap_signal", ele_pfnehadiso_endcap_signal1);
  if (ele_pfnehadiso_endcap_signal1 == 0) { cout << "ele_pfnehadiso_endcap_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfnehadiso_endcap_signal", ele_pfnehadiso_endcap_signal2);
  if (ele_pfnehadiso_endcap_signal2 == 0) { cout << "ele_pfnehadiso_endcap_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfnehadiso_endcap", ele_pfnehadiso_endcap_signal3);
  if (ele_pfnehadiso_endcap_signal3 == 0) { cout << "ele_pfnehadiso_endcap_signal not found!" << endl; return; }

plot_3histograms(ele_pfnehadiso_endcap_signal1, datalabel1, ele_pfnehadiso_endcap_signal2, datalabel2, ele_pfnehadiso_endcap_signal3, mclabel1, path, "val_ele_pfnehadiso_endcap_signal", "top_right", true, false);

  //Electron PF Neutral Hadron Isolation EndCap Background
  TH1D *ele_pfnehadiso_endcap_bkg1 = 0;
  TH1D *ele_pfnehadiso_endcap_bkg2 = 0;
  TH1D *ele_pfnehadiso_endcap_bkg3 = 0;

  d1->GetObject("reco_ele_pfnehadiso_endcap_bkg", ele_pfnehadiso_endcap_bkg1);
  if (ele_pfnehadiso_endcap_bkg1 == 0) { cout << "ele_pfnehadiso_endcap_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfnehadiso_endcap_bkg", ele_pfnehadiso_endcap_bkg2);
  if (ele_pfnehadiso_endcap_bkg2 == 0) { cout << "ele_pfnehadiso_endcap_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfnehadiso_endcap", ele_pfnehadiso_endcap_bkg3);
  if (ele_pfnehadiso_endcap_bkg3 == 0) { cout << "ele_pfnehadiso_endcap_bkg not found!" << endl; return; }

plot_3histograms(ele_pfnehadiso_endcap_bkg1, datalabel1, ele_pfnehadiso_endcap_bkg2, datalabel2, ele_pfnehadiso_endcap_bkg3, mclabel2, path, "val_ele_pfnehadiso_endcap_bkg", "top_right", true, false);


  //Electron PF Photon Isolation Signal
  TH1D *ele_pfphotoniso_signal1 = 0;
  TH1D *ele_pfphotoniso_signal2 = 0;
  TH1D *ele_pfphotoniso_signal3 = 0;

  d1->GetObject("reco_ele_pfphotoniso_signal", ele_pfphotoniso_signal1);
  if (ele_pfphotoniso_signal1 == 0) { cout << "ele_pfphotoniso_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfphotoniso_signal", ele_pfphotoniso_signal2);
  if (ele_pfphotoniso_signal2 == 0) { cout << "ele_pfphotoniso_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfphotoniso", ele_pfphotoniso_signal3);
  if (ele_pfphotoniso_signal3 == 0) { cout << "ele_pfphotoniso_signal not found!" << endl; return; }

plot_3histograms(ele_pfphotoniso_signal1, datalabel1, ele_pfphotoniso_signal2, datalabel2, ele_pfphotoniso_signal3, mclabel1, path, "val_ele_pfphotoniso_signal", "top_right", true, false);

  //Electron PF Photon Isolation Background
  TH1D *ele_pfphotoniso_bkg1 = 0;
  TH1D *ele_pfphotoniso_bkg2 = 0;
  TH1D *ele_pfphotoniso_bkg3 = 0;

  d1->GetObject("reco_ele_pfphotoniso_bkg", ele_pfphotoniso_bkg1);
  if (ele_pfphotoniso_bkg1 == 0) { cout << "ele_pfphotoniso_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfphotoniso_bkg", ele_pfphotoniso_bkg2);
  if (ele_pfphotoniso_bkg2 == 0) { cout << "ele_pfphotoniso_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfphotoniso", ele_pfphotoniso_bkg3);
  if (ele_pfphotoniso_bkg3 == 0) { cout << "ele_pfphotoniso_bkg not found!" << endl; return; }

plot_3histograms(ele_pfphotoniso_bkg1, datalabel1, ele_pfphotoniso_bkg2, datalabel2, ele_pfphotoniso_bkg3, mclabel2, path, "val_ele_pfphotoniso_bkg", "top_right", true, false);


  //Electron PF Photon Relative Isolation Signal
  TH1D *ele_pfphotonisorel_signal1 = 0;
  TH1D *ele_pfphotonisorel_signal2 = 0;
  TH1D *ele_pfphotonisorel_signal3 = 0;

  d1->GetObject("reco_ele_pfphotonisorel_signal", ele_pfphotonisorel_signal1);
  if (ele_pfphotonisorel_signal1 == 0) { cout << "ele_pfphotonisorel_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfphotonisorel_signal", ele_pfphotonisorel_signal2);
  if (ele_pfphotonisorel_signal2 == 0) { cout << "ele_pfphotonisorel_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfphotonisorel", ele_pfphotonisorel_signal3);
  if (ele_pfphotonisorel_signal3 == 0) { cout << "ele_pfphotonisorel_signal not found!" << endl; return; }

plot_3histograms(ele_pfphotonisorel_signal1, datalabel1, ele_pfphotonisorel_signal2, datalabel2, ele_pfphotonisorel_signal3, mclabel1, path, "val_ele_pfphotonisorel_signal", "top_right", true, false);

  //Electron PF Photon Relative Isolation Background
  TH1D *ele_pfphotonisorel_bkg1 = 0;
  TH1D *ele_pfphotonisorel_bkg2 = 0;
  TH1D *ele_pfphotonisorel_bkg3 = 0;

  d1->GetObject("reco_ele_pfphotonisorel_bkg", ele_pfphotonisorel_bkg1);
  if (ele_pfphotonisorel_bkg1 == 0) { cout << "ele_pfphotonisorel_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfphotonisorel_bkg", ele_pfphotonisorel_bkg2);
  if (ele_pfphotonisorel_bkg2 == 0) { cout << "ele_pfphotonisorel_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfphotonisorel", ele_pfphotonisorel_bkg3);
  if (ele_pfphotonisorel_bkg3 == 0) { cout << "ele_pfphotonisorel_bkg not found!" << endl; return; }

plot_3histograms(ele_pfphotonisorel_bkg1, datalabel1, ele_pfphotonisorel_bkg2, datalabel2, ele_pfphotonisorel_bkg3, mclabel2, path, "val_ele_pfphotonisorel_bkg", "top_right", true, false);


  //Electron PF Photon Isolation Barrel Signal
  TH1D *ele_pfphotoniso_barrel_signal1 = 0;
  TH1D *ele_pfphotoniso_barrel_signal2 = 0;
  TH1D *ele_pfphotoniso_barrel_signal3 = 0;

  d1->GetObject("reco_ele_pfphotoniso_barrel_signal", ele_pfphotoniso_barrel_signal1);
  if (ele_pfphotoniso_barrel_signal1 == 0) { cout << "ele_pfphotoniso_barrel_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfphotoniso_barrel_signal", ele_pfphotoniso_barrel_signal2);
  if (ele_pfphotoniso_barrel_signal2 == 0) { cout << "ele_pfphotoniso_barrel_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfphotoniso_barrel", ele_pfphotoniso_barrel_signal3);
  if (ele_pfphotoniso_barrel_signal3 == 0) { cout << "ele_pfphotoniso_barrel_signal not found!" << endl; return; }

plot_3histograms(ele_pfphotoniso_barrel_signal1, datalabel1, ele_pfphotoniso_barrel_signal2, datalabel2, ele_pfphotoniso_barrel_signal3, mclabel1, path, "val_ele_pfphotoniso_barrel_signal", "top_right", true, false);

  //Electron PF Photon Isolation Barrel Background
  TH1D *ele_pfphotoniso_barrel_bkg1 = 0;
  TH1D *ele_pfphotoniso_barrel_bkg2 = 0;
  TH1D *ele_pfphotoniso_barrel_bkg3 = 0;

  d1->GetObject("reco_ele_pfphotoniso_barrel_bkg", ele_pfphotoniso_barrel_bkg1);
  if (ele_pfphotoniso_barrel_bkg1 == 0) { cout << "ele_pfphotoniso_barrel_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfphotoniso_barrel_bkg", ele_pfphotoniso_barrel_bkg2);
  if (ele_pfphotoniso_barrel_bkg2 == 0) { cout << "ele_pfphotoniso_barrel_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfphotoniso_barrel", ele_pfphotoniso_barrel_bkg3);
  if (ele_pfphotoniso_barrel_bkg3 == 0) { cout << "ele_pfphotoniso_barrel_bkg not found!" << endl; return; }

plot_3histograms(ele_pfphotoniso_barrel_bkg1, datalabel1, ele_pfphotoniso_barrel_bkg2, datalabel2, ele_pfphotoniso_barrel_bkg3, mclabel2, path, "val_ele_pfphotoniso_barrel_bkg", "top_right", true, false);


  //Electron PF Photon Isolation Endcap Signal
  TH1D *ele_pfphotoniso_endcap_signal1 = 0;
  TH1D *ele_pfphotoniso_endcap_signal2 = 0;
  TH1D *ele_pfphotoniso_endcap_signal3 = 0;

  d1->GetObject("reco_ele_pfphotoniso_endcap_signal", ele_pfphotoniso_endcap_signal1);
  if (ele_pfphotoniso_endcap_signal1 == 0) { cout << "ele_pfphotoniso_endcap_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfphotoniso_endcap_signal", ele_pfphotoniso_endcap_signal2);
  if (ele_pfphotoniso_endcap_signal2 == 0) { cout << "ele_pfphotoniso_endcap_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfphotoniso_endcap", ele_pfphotoniso_endcap_signal3);
  if (ele_pfphotoniso_endcap_signal3 == 0) { cout << "ele_pfphotoniso_endcap_signal not found!" << endl; return; }

plot_3histograms(ele_pfphotoniso_endcap_signal1, datalabel1, ele_pfphotoniso_endcap_signal2, datalabel2, ele_pfphotoniso_endcap_signal3, mclabel1, path, "val_ele_pfphotoniso_endcap_signal", "top_right", true, false);

  //Electron PF Photon Isolation EndCap Background
  TH1D *ele_pfphotoniso_endcap_bkg1 = 0;
  TH1D *ele_pfphotoniso_endcap_bkg2 = 0;
  TH1D *ele_pfphotoniso_endcap_bkg3 = 0;

  d1->GetObject("reco_ele_pfphotoniso_endcap_bkg", ele_pfphotoniso_endcap_bkg1);
  if (ele_pfphotoniso_endcap_bkg1 == 0) { cout << "ele_pfphotoniso_endcap_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfphotoniso_endcap_bkg", ele_pfphotoniso_endcap_bkg2);
  if (ele_pfphotoniso_endcap_bkg2 == 0) { cout << "ele_pfphotoniso_endcap_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfphotoniso_endcap", ele_pfphotoniso_endcap_bkg3);
  if (ele_pfphotoniso_endcap_bkg3 == 0) { cout << "ele_pfphotoniso_endcap_bkg not found!" << endl; return; }

plot_3histograms(ele_pfphotoniso_endcap_bkg1, datalabel1, ele_pfphotoniso_endcap_bkg2, datalabel2, ele_pfphotoniso_endcap_bkg3, mclabel2, path, "val_ele_pfphotoniso_endcap_bkg", "top_right", true, false);


  //Electron PF Charged Hadrons form Pile-Up Isolation Signal
  TH1D *ele_pfchargedfrompu_signal1 = 0;
  TH1D *ele_pfchargedfrompu_signal2 = 0;
  TH1D *ele_pfchargedfrompu_signal3 = 0;

  d1->GetObject("reco_ele_pfchargedfrompu_signal", ele_pfchargedfrompu_signal1);
  if (ele_pfchargedfrompu_signal1 == 0) { cout << "ele_pfchargedfrompu_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchargedfrompu_signal", ele_pfchargedfrompu_signal2);
  if (ele_pfchargedfrompu_signal2 == 0) { cout << "ele_pfchargedfrompu_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfchargedfrompu", ele_pfchargedfrompu_signal3);
  if (ele_pfchargedfrompu_signal3 == 0) { cout << "ele_pfchargedfrompu_signal not found!" << endl; return; }

plot_3histograms(ele_pfchargedfrompu_signal1, datalabel1, ele_pfchargedfrompu_signal2, datalabel2, ele_pfchargedfrompu_signal3, mclabel1, path, "val_ele_pfchargedfrompu_signal", "bottom_left", true, false);

  //Electron PF Charged Hadrons from Pile-Up Isolation Background
  TH1D *ele_pfchargedfrompu_bkg1 = 0;
  TH1D *ele_pfchargedfrompu_bkg2 = 0;
  TH1D *ele_pfchargedfrompu_bkg3 = 0;

  d1->GetObject("reco_ele_pfchargedfrompu_bkg", ele_pfchargedfrompu_bkg1);
  if (ele_pfchargedfrompu_bkg1 == 0) { cout << "ele_pfchargedfrompu_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchargedfrompu_bkg", ele_pfchargedfrompu_bkg2);
  if (ele_pfchargedfrompu_bkg2 == 0) { cout << "ele_pfchargedfrompu_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfchargedfrompu", ele_pfchargedfrompu_bkg3);
  if (ele_pfchargedfrompu_bkg3 == 0) { cout << "ele_pfchargedfrompu_bkg not found!" << endl; return; }

plot_3histograms(ele_pfchargedfrompu_bkg1, datalabel1, ele_pfchargedfrompu_bkg2, datalabel2, ele_pfchargedfrompu_bkg3, mclabel2, path, "val_ele_pfchargedfrompu_bkg", "bottom_left", true, false);


  //Electron PF Charged Hadrons form Pile-Up Relative Isolation Signal
  TH1D *ele_pfchargedfrompurel_signal1 = 0;
  TH1D *ele_pfchargedfrompurel_signal2 = 0;
  TH1D *ele_pfchargedfrompurel_signal3 = 0;

  d1->GetObject("reco_ele_pfchargedfrompurel_signal", ele_pfchargedfrompurel_signal1);
  if (ele_pfchargedfrompurel_signal1 == 0) { cout << "ele_pfchargedfrompurel_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchargedfrompurel_signal", ele_pfchargedfrompurel_signal2);
  if (ele_pfchargedfrompurel_signal2 == 0) { cout << "ele_pfchargedfrompurel_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfchargedfrompurel", ele_pfchargedfrompurel_signal3);
  if (ele_pfchargedfrompurel_signal3 == 0) { cout << "ele_pfchargedfrompurel_signal not found!" << endl; return; }

plot_3histograms(ele_pfchargedfrompurel_signal1, datalabel1, ele_pfchargedfrompurel_signal2, datalabel2, ele_pfchargedfrompurel_signal3, mclabel1, path, "val_ele_pfchhadiso_signal", "bottom_left", true, false);

  //Electron PF Charged Hadrons from Pile-Up Relative Isolation Background
  TH1D *ele_pfchargedfrompurel_bkg1 = 0;
  TH1D *ele_pfchargedfrompurel_bkg2 = 0;
  TH1D *ele_pfchargedfrompurel_bkg3 = 0;

  d1->GetObject("reco_ele_pfchargedfrompurel_bkg", ele_pfchargedfrompurel_bkg1);
  if (ele_pfchargedfrompurel_bkg1 == 0) { cout << "ele_pfchargedfrompurel_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchargedfrompurel_bkg", ele_pfchargedfrompurel_bkg2);
  if (ele_pfchargedfrompurel_bkg2 == 0) { cout << "ele_pfchargedfrompurel_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfchargedfrompurel", ele_pfchargedfrompurel_bkg3);
  if (ele_pfchargedfrompurel_bkg3 == 0) { cout << "ele_pfchargedfrompurel_bkg not found!" << endl; return; }

plot_3histograms(ele_pfchargedfrompurel_bkg1, datalabel1, ele_pfchargedfrompurel_bkg2, datalabel2, ele_pfchargedfrompurel_bkg3, mclabel2, path, "val_ele_pfchargedfrompurel_bkg", "bottom_left", true, false);


  //Electron PF Charged Hadrons form Pile-Up Isolation Barrel Signal
  TH1D *ele_pfchargedfrompu_barrel_signal1 = 0;
  TH1D *ele_pfchargedfrompu_barrel_signal2 = 0;
  TH1D *ele_pfchargedfrompu_barrel_signal3 = 0;

  d1->GetObject("reco_ele_pfchargedfrompu_barrel_signal", ele_pfchargedfrompu_barrel_signal1);
  if (ele_pfchargedfrompu_barrel_signal1 == 0) { cout << "ele_pfchargedfrompu_barrel_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchargedfrompu_barrel_signal", ele_pfchargedfrompu_barrel_signal2);
  if (ele_pfchargedfrompu_barrel_signal2 == 0) { cout << "ele_pfchargedfrompu_barrel_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfchargedfrompu_barrel", ele_pfchargedfrompu_barrel_signal3);
  if (ele_pfchargedfrompu_barrel_signal3 == 0) { cout << "ele_pfchargedfrompu_barrel_signal not found!" << endl; return; }

plot_3histograms(ele_pfchargedfrompu_barrel_signal1, datalabel1, ele_pfchargedfrompu_barrel_signal2, datalabel2, ele_pfchargedfrompu_barrel_signal3, mclabel1, path, "val_ele_pfchhadiso_barrel_signal", "bottom_left", true, false);

  //Electron PF Charged Hadrons from Pile-Up Isolation Barrel Background
  TH1D *ele_pfchargedfrompu_barrel_bkg1 = 0;
  TH1D *ele_pfchargedfrompu_barrel_bkg2 = 0;
  TH1D *ele_pfchargedfrompu_barrel_bkg3 = 0;

  d1->GetObject("reco_ele_pfchargedfrompu_barrel_bkg", ele_pfchargedfrompu_barrel_bkg1);
  if (ele_pfchargedfrompu_barrel_bkg1 == 0) { cout << "ele_pfchargedfrompu_barrel_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchargedfrompu_barrel_bkg", ele_pfchargedfrompu_barrel_bkg2);
  if (ele_pfchargedfrompu_barrel_bkg2 == 0) { cout << "ele_pfchargedfrompu_barrel_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfchargedfrompu_barrel", ele_pfchargedfrompu_barrel_bkg3);
  if (ele_pfchargedfrompu_barrel_bkg3 == 0) { cout << "ele_pfchargedfrompu_barrel_bkg not found!" << endl; return; }

plot_3histograms(ele_pfchargedfrompu_barrel_bkg1, datalabel1, ele_pfchargedfrompu_barrel_bkg2, datalabel2, ele_pfchargedfrompu_barrel_bkg3, mclabel2, path, "val_ele_pfchargedfrompu_barrel_bkg", "bottom_left", true, false);


  //Electron PF Charged Hadrons form Pile-Up Isolation EndCap Signal
  TH1D *ele_pfchargedfrompu_endcap_signal1 = 0;
  TH1D *ele_pfchargedfrompu_endcap_signal2 = 0;
  TH1D *ele_pfchargedfrompu_endcap_signal3 = 0;

  d1->GetObject("reco_ele_pfchargedfrompu_endcap_signal", ele_pfchargedfrompu_endcap_signal1);
  if (ele_pfchargedfrompu_endcap_signal1 == 0) { cout << "ele_pfchargedfrompu_endcap_signal not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchargedfrompu_endcap_signal", ele_pfchargedfrompu_endcap_signal2);
  if (ele_pfchargedfrompu_endcap_signal2 == 0) { cout << "ele_pfchargedfrompu_endcap_signal not found!" << endl; return; }
  m1->GetObject("reco_ele_pfchargedfrompu_endcap", ele_pfchargedfrompu_endcap_signal3);
  if (ele_pfchargedfrompu_endcap_signal3 == 0) { cout << "ele_pfchargedfrompu_endcap_signal not found!" << endl; return; }

plot_3histograms(ele_pfchargedfrompu_endcap_signal1, datalabel1, ele_pfchargedfrompu_endcap_signal2, datalabel2, ele_pfchargedfrompu_endcap_signal3, mclabel1, path, "val_ele_pfchhadiso_endcap_signal", "bottom_left", true, false);

  //Electron PF Charged Hadrons from Pile-Up Isolation EndCap Background
  TH1D *ele_pfchargedfrompu_endcap_bkg1 = 0;
  TH1D *ele_pfchargedfrompu_endcap_bkg2 = 0;
  TH1D *ele_pfchargedfrompu_endcap_bkg3 = 0;

  d1->GetObject("reco_ele_pfchargedfrompu_endcap_bkg", ele_pfchargedfrompu_endcap_bkg1);
  if (ele_pfchargedfrompu_endcap_bkg1 == 0) { cout << "ele_pfchargedfrompu_endcap_bkg not found!" << endl; return; }
  d2->GetObject("reco_ele_pfchargedfrompu_endcap_bkg", ele_pfchargedfrompu_endcap_bkg2);
  if (ele_pfchargedfrompu_endcap_bkg2 == 0) { cout << "ele_pfchargedfrompu_endcap_bkg not found!" << endl; return; }
  m2->GetObject("reco_ele_pfchargedfrompu_endcap", ele_pfchargedfrompu_endcap_bkg3);
  if (ele_pfchargedfrompu_endcap_bkg3 == 0) { cout << "ele_pfchargedfrompu_endcap_bkg not found!" << endl; return; }

plot_3histograms(ele_pfchargedfrompu_endcap_bkg1, datalabel1, ele_pfchargedfrompu_endcap_bkg2, datalabel2, ele_pfchargedfrompu_endcap_bkg3, mclabel2, path, "val_ele_pfchargedfrompu_endcap_bkg", "bottom_left", true, false);



  std::cout << "-------------------------------------" << endl;
  std::cout << "Execution ended!" << endl;
  std::cout << "-------------------------------------" << endl;
  std::cout << " " << endl;
}
