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

void plot_control_plots_data()
{
  gROOT -> Reset();
  gROOT->SetStyle("Plain");

  std::cout << "Plot Electron Isolation - Data Version" << endl;
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
  string outfile1 = "output/SingleElectron.root";
  string outfile2 = "output/DoubleEG.root";

  // sets labels for the plots
  TString label1 = "SingleElectron";
  TString label2 = "DoubleEG";

  // sets output directory
  string path = "output/";

  // opens the files
  TFile *f1 = TFile::Open( outfile1.c_str() );
  TFile *f2 = TFile::Open( outfile2.c_str() );

  //Vertex Multiplicity
  TH1D *vertex_multiplicity1 = 0;
  TH1D *vertex_multiplicity2 = 0;

  f1->GetObject("vertex_multiplicity",vertex_multiplicity1);
  if (vertex_multiplicity1 == 0) { cout << "vertex_multiplicity not found!" << endl; return; }
  f2->GetObject("vertex_multiplicity",vertex_multiplicity2);
  if (vertex_multiplicity2 == 0) { cout << "vertex_multiplicity not found!" << endl; return; }

plot_2histograms(vertex_multiplicity1, label1, vertex_multiplicity2, label2, path, "data_vertex_multiplicity", "bottom_left", true, false);


  //Vertex Multiplicity Signal
  TH1D *vertex_multiplicity_signal1 = 0;
  TH1D *vertex_multiplicity_signal2 = 0;

  f1->GetObject("vertex_multiplicity_signal",vertex_multiplicity_signal1);
  if (vertex_multiplicity_signal1 == 0) { cout << "vertex_multiplicity_signal not found!" << endl; return; }
  f2->GetObject("vertex_multiplicity_signal",vertex_multiplicity_signal2);
  if (vertex_multiplicity_signal2 == 0) { cout << "vertex_multiplicity_signal not found!" << endl; return; }

plot_2histograms(vertex_multiplicity_signal1, label1, vertex_multiplicity_signal2, label2, path, "data_vertex_multiplicity_signal", "top_right", true, false);

  //Vertex Multiplicity Background
  TH1D *vertex_multiplicity_bkg1 = 0;
  TH1D *vertex_multiplicity_bkg2 = 0;

  f1->GetObject("vertex_multiplicity_bkg",vertex_multiplicity_bkg1);
  if (vertex_multiplicity_bkg1 == 0) { cout << "vertex_multiplicity_bkg not found!" << endl; return; }
  f2->GetObject("vertex_multiplicity_bkg",vertex_multiplicity_bkg2);
  if (vertex_multiplicity_bkg2 == 0) { cout << "vertex_multiplicity_bkg not found!" << endl; return; }

plot_2histograms(vertex_multiplicity_bkg1, label1, vertex_multiplicity_bkg2, label2, path, "data_vertex_multiplicity_bkg", "top_right", true, false);


  //Rho
  TH1D *evt_rho1 = 0;
  TH1D *evt_rho2 = 0;

  f1->GetObject("evt_rho",evt_rho1);
  if (evt_rho1 == 0) { cout << "evt_rho not found!" << endl; return; }
  f2->GetObject("evt_rho",evt_rho2);
  if (evt_rho2 == 0) { cout << "evt_rho not found!" << endl; return; }

plot_2histograms(evt_rho1, label1, evt_rho2, label2, path, "data_evt_rho", "bottom_left", true, false);

  //Rho Signal
  TH1D *evt_rho_signal1 = 0;
  TH1D *evt_rho_signal2 = 0;

  f1->GetObject("evt_rho_signal",evt_rho_signal1);
  if (evt_rho_signal1 == 0) { cout << "evt_rho_signal not found!" << endl; return; }
  f2->GetObject("evt_rho_signal",evt_rho_signal2);
  if (evt_rho_signal2 == 0) { cout << "evt_rho_signal not found!" << endl; return; }

plot_2histograms(evt_rho_signal1, label1, evt_rho_signal2, label2, path, "data_evt_rho_signal", "top_right", true, false);

  //Rho Background
  TH1D *evt_rho_bkg1 = 0;
  TH1D *evt_rho_bkg2 = 0;

  f1->GetObject("evt_rho_bkg",evt_rho_bkg1);
  if (evt_rho_bkg1 == 0) { cout << "evt_rho_bkg not found!" << endl; return; }
  f2->GetObject("evt_rho_bkg",evt_rho_bkg2);
  if (evt_rho_bkg2 == 0) { cout << "evt_rho_bkg not found!" << endl; return; }

plot_2histograms(evt_rho_bkg1, label1, evt_rho_bkg2, label2, path, "data_evt_rho_bkg", "top_right", true, false);


  //Ele Multiplicity
  TH1D *reco_ele_multiplicity1 = 0;
  TH1D *reco_ele_multiplicity2 = 0;

  f1->GetObject("reco_ele_multiplicity",reco_ele_multiplicity1);
  if (reco_ele_multiplicity1 == 0) { cout << "reco_ele_multiplicity not found!" << endl; return; }
  f2->GetObject("reco_ele_multiplicity",reco_ele_multiplicity2);
  if (reco_ele_multiplicity2 == 0) { cout << "reco_ele_multiplicity not found!" << endl; return; }

plot_2histograms(reco_ele_multiplicity1, label1, reco_ele_multiplicity2, label2, path, "data_reco_ele_multiplicity", "bottom_left", true, false);

  //Ele Multiplicity Signal
  TH1D *reco_ele_multiplicity_signal1 = 0;
  TH1D *reco_ele_multiplicity_signal2 = 0;

  f1->GetObject("reco_ele_multiplicity_signal",reco_ele_multiplicity_signal1);
  if (reco_ele_multiplicity_signal1 == 0) { cout << "reco_ele_multiplicity_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_multiplicity_signal",reco_ele_multiplicity_signal2);
  if (reco_ele_multiplicity_signal2 == 0) { cout << "reco_ele_multiplicity_signal not found!" << endl; return; }

plot_2histograms(reco_ele_multiplicity_signal1, label1, reco_ele_multiplicity_signal2, label2, path, "data_reco_ele_multiplicity_signal", "bottom_left", true, false);

  //Ele Multiplicity Background
  TH1D *reco_ele_multiplicity_bkg1 = 0;
  TH1D *reco_ele_multiplicity_bkg2 = 0;

  f1->GetObject("reco_ele_multiplicity_bkg",reco_ele_multiplicity_bkg1);
  if (reco_ele_multiplicity_bkg1 == 0) { cout << "reco_ele_multiplicity_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_multiplicity_bkg",reco_ele_multiplicity_bkg2);
  if (reco_ele_multiplicity_bkg2 == 0) { cout << "reco_ele_multiplicity_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_multiplicity_bkg1, label1, reco_ele_multiplicity_bkg2, label2, path, "data_reco_ele_multiplicity_bkg", "bottom_left", true, false);


  //Ele pT
  TH1D *reco_ele_pt1 = 0;
  TH1D *reco_ele_pt2 = 0;

  f1->GetObject("reco_ele_pt",reco_ele_pt1);
  if (reco_ele_pt1 == 0) { cout << "reco_ele_pt not found!" << endl; return; }
  f2->GetObject("reco_ele_pt",reco_ele_pt2);
  if (reco_ele_pt2 == 0) { cout << "reco_ele_pt not found!" << endl; return; }

plot_2histograms(reco_ele_pt1, label1, reco_ele_pt2, label2, path, "data_reco_ele_pt", "bottom_left", true, false);


  //Ele pT Signal
  TH1D *reco_ele_pt_signal1 = 0;
  TH1D *reco_ele_pt_signal2 = 0;

  f1->GetObject("reco_ele_pt_signal",reco_ele_pt_signal1);
  if (reco_ele_pt_signal1 == 0) { cout << "reco_ele_pt_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pt_signal",reco_ele_pt_signal2);
  if (reco_ele_pt_signal2 == 0) { cout << "reco_ele_pt_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pt_signal1, label1, reco_ele_pt_signal2, label2, path, "data_reco_ele_pt_signal", "top_right", true, false);


  //Ele pT Background
  TH1D *reco_ele_pt_bkg1 = 0;
  TH1D *reco_ele_pt_bkg2 = 0;

  f1->GetObject("reco_ele_pt_bkg",reco_ele_pt_bkg1);
  if (reco_ele_pt_bkg1 == 0) { cout << "reco_ele_pt_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pt_bkg",reco_ele_pt_bkg2);
  if (reco_ele_pt_bkg2 == 0) { cout << "reco_ele_pt_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pt_bkg1, label1, reco_ele_pt_bkg2, label2, path, "data_reco_ele_pt_bkg", "top_right", true, false);


  //Ele Eta
  TH1D *reco_ele_eta1 = 0;
  TH1D *reco_ele_eta2 = 0;

  f1->GetObject("reco_ele_eta",reco_ele_eta1);
  if (reco_ele_eta1 == 0) { cout << "reco_ele_eta not found!" << endl; return; }
  f2->GetObject("reco_ele_eta",reco_ele_eta2);
  if (reco_ele_eta2 == 0) { cout << "reco_ele_eta not found!" << endl; return; }

plot_2histograms(reco_ele_eta1, label1, reco_ele_eta2, label2, path, "data_reco_ele_eta", "top_middle", true, false);

  //Ele Eta Signal
  TH1D *reco_ele_eta_signal1 = 0;
  TH1D *reco_ele_eta_signal2 = 0;

  f1->GetObject("reco_ele_eta_signal",reco_ele_eta_signal1);
  if (reco_ele_eta_signal1 == 0) { cout << "reco_ele_eta_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_eta_signal",reco_ele_eta_signal2);
  if (reco_ele_eta_signal2 == 0) { cout << "reco_ele_eta_signal not found!" << endl; return; }

plot_2histograms(reco_ele_eta_signal1, label1, reco_ele_eta_signal2, label2, path, "data_reco_ele_eta_signal", "bottom_middle", true, false);


  //Ele Eta Background
  TH1D *reco_ele_eta_bkg1 = 0;
  TH1D *reco_ele_eta_bkg2 = 0;

  f1->GetObject("reco_ele_eta_bkg",reco_ele_eta_bkg1);
  if (reco_ele_eta_bkg1 == 0) { cout << "reco_ele_eta_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_eta_bkg",reco_ele_eta_bkg2);
  if (reco_ele_eta_bkg2 == 0) { cout << "reco_ele_eta_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_eta_bkg1, label1, reco_ele_eta_bkg2, label2, path, "data_reco_ele_eta_bkg", "bottom_left", true, false);


  //Ele Phi
  TH1D *reco_ele_phi1 = 0;
  TH1D *reco_ele_phi2 = 0;

  f1->GetObject("reco_ele_phi",reco_ele_phi1);
  if (reco_ele_phi1 == 0) { cout << "reco_ele_phi not found!" << endl; return; }
  f2->GetObject("reco_ele_phi",reco_ele_phi2);
  if (reco_ele_phi2 == 0) { cout << "reco_ele_phi not found!" << endl; return; }

plot_2histograms(reco_ele_phi1, label1, reco_ele_phi2, label2, path, "data_reco_ele_phi", "bottom_middle", true, false);


 //Ele Phi Signal
  TH1D *reco_ele_phi_signal1 = 0;
  TH1D *reco_ele_phi_signal2 = 0;

  f1->GetObject("reco_ele_phi_signal",reco_ele_phi_signal1);
  if (reco_ele_phi_signal1 == 0) { cout << "reco_ele_phi_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_phi_signal",reco_ele_phi_signal2);
  if (reco_ele_phi_signal2 == 0) { cout << "reco_ele_phi_signal not found!" << endl; return; }

plot_2histograms(reco_ele_phi_signal1, label1, reco_ele_phi_signal2, label2, path, "data_reco_ele_phi_signal", "bottom_middle", true, false);


  //Ele Phi Background
  TH1D *reco_ele_phi_bkg1 = 0;
  TH1D *reco_ele_phi_bkg2 = 0;

  f1->GetObject("reco_ele_phi_bkg",reco_ele_phi_bkg1);
  if (reco_ele_phi_bkg1 == 0) { cout << "reco_ele_phi_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_phi_bkg",reco_ele_phi_bkg2);
  if (reco_ele_phi_bkg2 == 0) { cout << "reco_ele_phi_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_phi_bkg1, label1, reco_ele_phi_bkg2, label2, path, "data_reco_ele_phi_bkg", "bottom_left", true, false);

  //Ele Charge
  TH1D *reco_ele_charge1 = 0;
  TH1D *reco_ele_charge2 = 0;

  f1->GetObject("reco_ele_charge",reco_ele_charge1);
  if (reco_ele_charge1 == 0) { cout << "reco_ele_charge not found!" << endl; return; }
  f2->GetObject("reco_ele_charge",reco_ele_charge2);
  if (reco_ele_charge2 == 0) { cout << "reco_ele_charge not found!" << endl; return; }

plot_2histograms(reco_ele_charge1, label1, reco_ele_charge2, label2, path, "data_reco_ele_charge", "bottom_left", true, false);


 //Ele Charge Signal
  TH1D *reco_ele_charge_signal1 = 0;
  TH1D *reco_ele_charge_signal2 = 0;

  f1->GetObject("reco_ele_charge_signal",reco_ele_charge_signal1);
  if (reco_ele_charge_signal1 == 0) { cout << "reco_ele_charge_signal1 not found!" << endl; return; }
  f2->GetObject("reco_ele_charge_signal",reco_ele_charge_signal2);
  if (reco_ele_charge_signal2 == 0) { cout << "reco_ele_charge_signal2 not found!" << endl; return; }

plot_2histograms(reco_ele_charge_signal1, label1, reco_ele_charge_signal2, label2, path, "data_reco_ele_charge_signal", "bottom_left", true, false);


  //Ele Charge Background
  TH1D *reco_ele_charge_bkg1 = 0;
  TH1D *reco_ele_charge_bkg2 = 0;

  f1->GetObject("reco_ele_charge_bkg",reco_ele_charge_bkg1);
  if (reco_ele_charge_bkg1 == 0) { cout << "reco_ele_charge_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_charge_bkg",reco_ele_charge_bkg2);
  if (reco_ele_charge_bkg2 == 0) { cout << "reco_ele_charge_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_charge_bkg1, label1, reco_ele_charge_bkg2, label2, path, "data_reco_ele_charge_bkg", "bottom_left", true, false);


  //Ele Effective Area
  TH1D *reco_ele_effarea1 = 0;
  TH1D *reco_ele_effarea2 = 0;

  f1->GetObject("reco_ele_effarea",reco_ele_effarea1);
  if (reco_ele_effarea1 == 0) { cout << "reco_ele_effarea not found!" << endl; return; }
  f2->GetObject("reco_ele_effarea",reco_ele_effarea2);
  if (reco_ele_effarea2 == 0) { cout << "reco_ele_effarea not found!" << endl; return; }

plot_2histograms(reco_ele_effarea1, label1, reco_ele_effarea2, label2, path, "data_reco_ele_effarea", "top_right", true, false);


  //Ele Effective Area Signal
  TH1D *reco_ele_effarea_signal1 = 0;
  TH1D *reco_ele_effarea_signal2 = 0;

  f1->GetObject("reco_ele_effarea_signal",reco_ele_effarea_signal1);
  if (reco_ele_effarea_signal1 == 0) { cout << "reco_ele_effarea_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_effarea_signal",reco_ele_effarea_signal2);
  if (reco_ele_effarea_signal2 == 0) { cout << "reco_ele_effarea_signal not found!" << endl; return; }

plot_2histograms(reco_ele_effarea_signal1, label1, reco_ele_effarea_signal2, label2, path, "data_reco_ele_effarea_signal", "top_right", true, false);

  //Ele Effective Area Background
  TH1D *reco_ele_effarea_bkg1 = 0;
  TH1D *reco_ele_effarea_bkg2 = 0;

  f1->GetObject("reco_ele_effarea_bkg",reco_ele_effarea_bkg1);
  if (reco_ele_effarea_bkg1 == 0) { cout << "reco_ele_effarea_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_effarea_bkg",reco_ele_effarea_bkg2);
  if (reco_ele_effarea_bkg2 == 0) { cout << "reco_ele_effarea_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_effarea_bkg1, label1, reco_ele_effarea_bkg2, label2, path, "data_reco_ele_effarea_bkg", "top_right", true, false);


  //Ele dxy
  TH1D *reco_ele_dxy1 = 0;
  TH1D *reco_ele_dxy2 = 0;

  f1->GetObject("reco_ele_dxy",reco_ele_dxy1);
  if (reco_ele_dxy1 == 0) { cout << "reco_ele_dxy not found!" << endl; return; }
  f2->GetObject("reco_ele_dxy",reco_ele_dxy2);
  if (reco_ele_dxy2 == 0) { cout << "reco_ele_dxy not found!" << endl; return; }

plot_2histograms(reco_ele_dxy1, label1, reco_ele_dxy2, label2, path, "data_reco_ele_dxy", "top_right", true, false);

  //Ele dxy Signal
  TH1D *reco_ele_dxy_signal1 = 0;
  TH1D *reco_ele_dxy_signal2 = 0;

  f1->GetObject("reco_ele_dxy_signal",reco_ele_dxy_signal1);
  if (reco_ele_dxy_signal1 == 0) { cout << "reco_ele_dxy_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_dxy_signal",reco_ele_dxy_signal2);
  if (reco_ele_dxy_signal2 == 0) { cout << "reco_ele_dxy_signal not found!" << endl; return; }

plot_2histograms(reco_ele_dxy_signal1, label1, reco_ele_dxy_signal2, label2, path, "data_reco_ele_dxy_signal", "top_right", true, false);


  //Ele dxy Background
  TH1D *reco_ele_dxy_bkg1 = 0;
  TH1D *reco_ele_dxy_bkg2 = 0;

  f1->GetObject("reco_ele_dxy_bkg",reco_ele_dxy_bkg1);
  if (reco_ele_dxy_bkg1 == 0) { cout << "reco_ele_dxy_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_dxy_bkg",reco_ele_dxy_bkg2);
  if (reco_ele_dxy_bkg2 == 0) { cout << "reco_ele_dxy_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_dxy_bkg1, label1, reco_ele_dxy_bkg2, label2, path, "data_reco_ele_dxy_bkg", "top_right", true, false);


  //Ele dz
  TH1D *reco_ele_dz1 = 0;
  TH1D *reco_ele_dz2 = 0;

  f1->GetObject("reco_ele_dz",reco_ele_dz1);
  if (reco_ele_dz1 == 0) { cout << "reco_ele_dz not found!" << endl; return; }
  f2->GetObject("reco_ele_dz",reco_ele_dz2);
  if (reco_ele_dz2 == 0) { cout << "reco_ele_dz not found!" << endl; return; }

plot_2histograms(reco_ele_dz1, label1, reco_ele_dz2, label2, path, "data_reco_ele_dz", "top_right", true, false);

  //Ele dz Signal
  TH1D *reco_ele_dz_signal1 = 0;
  TH1D *reco_ele_dz_signal2 = 0;

  f1->GetObject("reco_ele_dz_signal",reco_ele_dz_signal1);
  if (reco_ele_dz_signal1 == 0) { cout << "reco_ele_dz_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_dz_signal",reco_ele_dz_signal2);
  if (reco_ele_dz_signal2 == 0) { cout << "reco_ele_dz_signa not found!" << endl; return; }

plot_2histograms(reco_ele_dz_signal1, label1, reco_ele_dz_signal2, label2, path, "data_reco_ele_dz_signal", "top_right", true, false);

  //Ele dz Background
  TH1D *reco_ele_dz_bkg1 = 0;
  TH1D *reco_ele_dz_bkg2 = 0;

  f1->GetObject("reco_ele_dz_bkg",reco_ele_dz_bkg1);
  if (reco_ele_dz_bkg1 == 0) { cout << "reco_ele_dz_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_dz_bkg",reco_ele_dz_bkg2);
  if (reco_ele_dz_bkg2 == 0) { cout << "reco_ele_dz_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_dz_bkg1, label1, reco_ele_dz_bkg2, label2, path, "data_reco_ele_dz_bkg", "top_right", true, false);


  //Ele Missing Hits
  TH1D *reco_ele_missinghit1 = 0;
  TH1D *reco_ele_missinghit2 = 0;

  f1->GetObject("reco_ele_missinghit",reco_ele_missinghit1);
  if (reco_ele_missinghit1 == 0) { cout << "reco_ele_missinghit not found!" << endl; return; }
  f2->GetObject("reco_ele_missinghit",reco_ele_missinghit2);
  if (reco_ele_missinghit2 == 0) { cout << "reco_ele_missinghit not found!" << endl; return; }

plot_2histograms(reco_ele_missinghit1, label1, reco_ele_missinghit2, label2, path, "data_reco_ele_missinghit", "top_right", true, false);

  //Ele Missing Hits Signal
  TH1D *reco_ele_missinghit_signal1 = 0;
  TH1D *reco_ele_missinghit_signal2 = 0;

  f1->GetObject("reco_ele_missinghit_signal",reco_ele_missinghit_signal1);
  if (reco_ele_missinghit_signal1 == 0) { cout << "reco_ele_missinghit_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_missinghit_signal",reco_ele_missinghit_signal2);
  if (reco_ele_missinghit_signal2 == 0) { cout << "reco_ele_missinghit_signal not found!" << endl; return; }

plot_2histograms(reco_ele_missinghit_signal1, label1, reco_ele_missinghit_signal2, label2, path, "data_reco_ele_missinghit_signal", "top_right", true, false);

  //Ele Missing Hits Background
  TH1D *reco_ele_missinghit_bkg1 = 0;
  TH1D *reco_ele_missinghit_bkg2 = 0;

  f1->GetObject("reco_ele_missinghit_bkg",reco_ele_missinghit_bkg1);
  if (reco_ele_missinghit_bkg1 == 0) { cout << "reco_ele_missinghit_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_missinghit_bkg",reco_ele_missinghit_bkg2);
  if (reco_ele_missinghit_bkg2 == 0) { cout << "reco_ele_missinghit_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_missinghit_bkg1, label1, reco_ele_missinghit_bkg2, label2, path, "data_reco_ele_missinghit_bkg", "top_right", true, false);


  //Ele PF Charged Hadron Isolation
  TH1D *reco_ele_pfchhadiso1 = 0;
  TH1D *reco_ele_pfchhadiso2 = 0;

  f1->GetObject("reco_ele_pfchhadiso",reco_ele_pfchhadiso1);
  if (reco_ele_pfchhadiso1 == 0) { cout << "reco_ele_pfchhadiso not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso",reco_ele_pfchhadiso2);
  if (reco_ele_pfchhadiso2 == 0) { cout << "reco_ele_pfchhadiso not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso1, label1, reco_ele_pfchhadiso2, label2, path, "data_reco_ele_pfchhadiso", "top_right", true, false);

  //Ele PF Charged Hadron Isolation Signal
  TH1D *reco_ele_pfchhadiso_signal1 = 0;
  TH1D *reco_ele_pfchhadiso_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_signal",reco_ele_pfchhadiso_signal1);
  if (reco_ele_pfchhadiso_signal1 == 0) { cout << "reco_ele_pfchhadiso_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_signal",reco_ele_pfchhadiso_signal2);
  if (reco_ele_pfchhadiso_signal2 == 0) { cout << "reco_ele_pfchhadiso_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_signal1, label1, reco_ele_pfchhadiso_signal2, label2, path, "data_reco_ele_pfchhadiso_signal", "top_right", true, false);

  //Ele PF Charged Hadron Isolation Background
  TH1D *reco_ele_pfchhadiso_bkg1 = 0;
  TH1D *reco_ele_pfchhadiso_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_bkg",reco_ele_pfchhadiso_bkg1);
  if (reco_ele_pfchhadiso_bkg1 == 0) { cout << "reco_ele_pfchhadiso_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_bkg",reco_ele_pfchhadiso_bkg2);
  if (reco_ele_pfchhadiso_bkg2 == 0) { cout << "reco_ele_pfchhadiso_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_bkg1, label1, reco_ele_pfchhadiso_bkg2, label2, path, "data_reco_ele_pfchhadiso_bkg", "top_right", true, false);


  //Ele PF Charged Hadron Isolation Relative
  TH1D *reco_ele_pfchhadisorel1 = 0;
  TH1D *reco_ele_pfchhadisorel2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel",reco_ele_pfchhadisorel1);
  if (reco_ele_pfchhadisorel1 == 0) { cout << "reco_ele_pfchhadisorel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel",reco_ele_pfchhadisorel2);
  if (reco_ele_pfchhadisorel2 == 0) { cout << "reco_ele_pfchhadisorel not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel1, label1, reco_ele_pfchhadisorel2, label2, path, "data_reco_ele_pfchhadisorel", "top_right", true, false);

  //Ele PF Charged Hadron Isolation Relative Signal
  TH1D *reco_ele_pfchhadisorel_signal1 = 0;
  TH1D *reco_ele_pfchhadisorel_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_signal",reco_ele_pfchhadisorel_signal1);
  if (reco_ele_pfchhadisorel_signal1 == 0) { cout << "reco_ele_pfchhadisorel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_signal",reco_ele_pfchhadisorel_signal2);
  if (reco_ele_pfchhadisorel_signal2 == 0) { cout << "reco_ele_pfchhadisorel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_signal1, label1, reco_ele_pfchhadisorel_signal2, label2, path, "data_reco_ele_pfchhadisorel_signal", "top_right", true, false);

  //Ele PF Charged Hadron Isolation Relative Background
  TH1D *reco_ele_pfchhadisorel_bkg1 = 0;
  TH1D *reco_ele_pfchhadisorel_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_bkg",reco_ele_pfchhadisorel_bkg1);
  if (reco_ele_pfchhadisorel_bkg1 == 0) { cout << "reco_ele_pfchhadisorel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_bkg",reco_ele_pfchhadisorel_bkg2);
  if (reco_ele_pfchhadisorel_bkg2 == 0) { cout << "reco_ele_pfchhadisorel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_bkg1, label1, reco_ele_pfchhadisorel_bkg2, label2, path, "data_reco_ele_pfchhadisorel_bkg", "top_right", true, false);


  //Ele PF Charged Hadron Isolation Barrel
  TH1D *reco_ele_pfchhadiso_barrel1 = 0;
  TH1D *reco_ele_pfchhadiso_barrel2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_barrel",reco_ele_pfchhadiso_barrel1);
  if (reco_ele_pfchhadiso_barrel1 == 0) { cout << "reco_ele_pfchhadiso_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_barrel",reco_ele_pfchhadiso_barrel2);
  if (reco_ele_pfchhadiso_barrel2 == 0) { cout << "reco_ele_pfchhadiso_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_barrel1, label1, reco_ele_pfchhadiso_barrel2, label2, path, "data_reco_ele_pfchhadiso_barrel", "top_right", true, false);

  //Ele PF Charged Hadron Isolation Signal Barrel
  TH1D *reco_ele_pfchhadiso_barrel_signal1 = 0;
  TH1D *reco_ele_pfchhadiso_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_barrel_signal",reco_ele_pfchhadiso_barrel_signal1);
  if (reco_ele_pfchhadiso_barrel_signal1 == 0) { cout << "reco_ele_pfchhadiso_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_barrel_signal",reco_ele_pfchhadiso_barrel_signal2);
  if (reco_ele_pfchhadiso_barrel_signal2 == 0) { cout << "reco_ele_pfchhadiso_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_barrel_signal1, label1, reco_ele_pfchhadiso_barrel_signal2, label2, path, "data_reco_ele_pfchhadiso_barrel_signal", "top_right", true, false);

  //Ele PF Charged Hadron Isolation Background Barrel
  TH1D *reco_ele_pfchhadiso_barrel_bkg1 = 0;
  TH1D *reco_ele_pfchhadiso_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_barrel_bkg",reco_ele_pfchhadiso_barrel_bkg1);
  if (reco_ele_pfchhadiso_barrel_bkg1 == 0) { cout << "reco_ele_pfchhadiso_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_barrel_bkg",reco_ele_pfchhadiso_barrel_bkg2);
  if (reco_ele_pfchhadiso_barrel_bkg2 == 0) { cout << "reco_ele_pfchhadiso_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_barrel_bkg1, label1, reco_ele_pfchhadiso_barrel_bkg2, label2, path, "data_reco_ele_pfchhadiso_barrel_bkg", "top_right", true, false);


  //Ele PF Charged Hadron Relative Isolation Barrel
  TH1D *reco_ele_pfchhadisorel_barrel1 = 0;
  TH1D *reco_ele_pfchhadisorel_barrel2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_barrel",reco_ele_pfchhadisorel_barrel1);
  if (reco_ele_pfchhadisorel_barrel1 == 0) { cout << "reco_ele_pfchhadisorel_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_barrel",reco_ele_pfchhadisorel_barrel2);
  if (reco_ele_pfchhadisorel_barrel2 == 0) { cout << "reco_ele_pfchhadisorel_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_barrel1, label1, reco_ele_pfchhadisorel_barrel2, label2, path, "data_reco_ele_pfchhadisorel_barrel", "top_right", true, false);


  //Ele PF Charged Hadron Relative Isolation Barrel Signal
  TH1D *reco_ele_pfchhadisorel_barrel_signal1 = 0;
  TH1D *reco_ele_pfchhadisorel_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_barrel_signal",reco_ele_pfchhadisorel_barrel_signal1);
  if (reco_ele_pfchhadisorel_barrel_signal1 == 0) { cout << "reco_ele_pfchhadisorel_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_barrel_signal",reco_ele_pfchhadisorel_barrel_signal2);
  if (reco_ele_pfchhadisorel_barrel_signal2 == 0) { cout << "reco_ele_pfchhadisorel_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_barrel_signal1, label1, reco_ele_pfchhadisorel_barrel_signal2, label2, path, "data_reco_ele_pfchhadisorel_barrel_signal", "top_right", true, false);


  //Ele PF Charged Hadron Relative Isolation Barrel Background
  TH1D *reco_ele_pfchhadisorel_barrel_bkg1 = 0;
  TH1D *reco_ele_pfchhadisorel_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_barrel_bkg",reco_ele_pfchhadisorel_barrel_bkg1);
  if (reco_ele_pfchhadisorel_barrel_bkg1 == 0) { cout << "reco_ele_pfchhadisorel_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_barrel_bkg",reco_ele_pfchhadisorel_barrel_bkg2);
  if (reco_ele_pfchhadisorel_barrel_bkg2 == 0) { cout << "reco_ele_pfchhadisorel_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_barrel_bkg1, label1, reco_ele_pfchhadisorel_barrel_bkg2, label2, path, "data_reco_ele_pfchhadisorel_barrel_bkg", "top_right", true, false);

  //Ele PF Charged Hadron Isolation EndCap
  TH1D *reco_ele_pfchhadiso_endcap1 = 0;
  TH1D *reco_ele_pfchhadiso_endcap2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_endcap",reco_ele_pfchhadiso_endcap1);
  if (reco_ele_pfchhadiso_endcap1 == 0) { cout << "reco_ele_pfchhadiso_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_endcap",reco_ele_pfchhadiso_endcap2);
  if (reco_ele_pfchhadiso_endcap2 == 0) { cout << "reco_ele_pfchhadiso_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_endcap1, label1, reco_ele_pfchhadiso_endcap2, label2, path, "data_reco_ele_pfchhadiso_endcap", "top_right", true, false);

  //Ele PF Charged Hadron Isolation Signal EndCap
  TH1D *reco_ele_pfchhadiso_endcap_signal1 = 0;
  TH1D *reco_ele_pfchhadiso_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_endcap_signal",reco_ele_pfchhadiso_endcap_signal1);
  if (reco_ele_pfchhadiso_endcap_signal1 == 0) { cout << "reco_ele_pfchhadiso_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_endcap_signal",reco_ele_pfchhadiso_endcap_signal2);
  if (reco_ele_pfchhadiso_endcap_signal2 == 0) { cout << "reco_ele_pfchhadiso_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_endcap_signal1, label1, reco_ele_pfchhadiso_endcap_signal2, label2, path, "data_reco_ele_pfchhadiso_endcap_signal", "top_right", true, false);

  //Ele PF Charged Hadron Isolation Background Endcap
  TH1D *reco_ele_pfchhadiso_endcap_bkg1 = 0;
  TH1D *reco_ele_pfchhadiso_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_endcap_bkg",reco_ele_pfchhadiso_endcap_bkg1);
  if (reco_ele_pfchhadiso_endcap_bkg1 == 0) { cout << "reco_ele_pfchhadiso_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_endcap_bkg",reco_ele_pfchhadiso_endcap_bkg2);
  if (reco_ele_pfchhadiso_endcap_bkg2 == 0) { cout << "reco_ele_pfchhadiso_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_endcap_bkg1, label1, reco_ele_pfchhadiso_endcap_bkg2, label2, path, "data_reco_ele_pfchhadiso_endcap_bkg", "top_right", true, false);


  //Ele PF Charged Hadron Relative Isolation EndCap
  TH1D *reco_ele_pfchhadisorel_endcap1 = 0;
  TH1D *reco_ele_pfchhadisorel_endcap2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_endcap",reco_ele_pfchhadisorel_endcap1);
  if (reco_ele_pfchhadisorel_endcap1 == 0) { cout << "reco_ele_pfchhadisorel_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_endcap",reco_ele_pfchhadisorel_endcap2);
  if (reco_ele_pfchhadisorel_endcap2 == 0) { cout << "reco_ele_pfchhadisorel_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_endcap1, label1, reco_ele_pfchhadisorel_endcap2, label2, path, "data_reco_ele_pfchhadisorel_endcap", "top_right", true, false);

  //Ele PF Charged Hadron Relative Isolation Signal EndCap
  TH1D *reco_ele_pfchhadisorel_endcap_signal1 = 0;
  TH1D *reco_ele_pfchhadisorel_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_endcap_signal",reco_ele_pfchhadisorel_endcap_signal1);
  if (reco_ele_pfchhadisorel_endcap_signal1 == 0) { cout << "reco_ele_pfchhadisorel_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_endcap_signal",reco_ele_pfchhadisorel_endcap_signal2);
  if (reco_ele_pfchhadisorel_endcap_signal2 == 0) { cout << "reco_ele_pfchhadisorel_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_endcap_signal1, label1, reco_ele_pfchhadisorel_endcap_signal2, label2, path, "data_reco_ele_pfchhadisorel_endcap_signal", "top_right", true, false);


  //Ele PF Charged Hadron Relative Isolation Background Endcap
  TH1D *reco_ele_pfchhadisorel_endcap_bkg1 = 0;
  TH1D *reco_ele_pfchhadisorel_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_endcap_bkg",reco_ele_pfchhadisorel_endcap_bkg1);
  if (reco_ele_pfchhadisorel_endcap_bkg1 == 0) { cout << "reco_ele_pfchhadisorel_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_endcap_bkg",reco_ele_pfchhadisorel_endcap_bkg2);
  if (reco_ele_pfchhadisorel_endcap_bkg2 == 0) { cout << "reco_ele_pfchhadisorel_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_endcap_bkg1, label1, reco_ele_pfchhadisorel_endcap_bkg2, label2, path, "data_reco_ele_pfchhadisorel_endcap_bkg", "top_right", true, false);


  //Ele PF Neutral Hadron Isolation
  TH1D *reco_ele_pfnehadiso1 = 0;
  TH1D *reco_ele_pfnehadiso2 = 0;

  f1->GetObject("reco_ele_pfnehadiso",reco_ele_pfnehadiso1);
  if (reco_ele_pfnehadiso1 == 0) { cout << "reco_ele_pfnehadiso not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso",reco_ele_pfnehadiso2);
  if (reco_ele_pfnehadiso2 == 0) { cout << "reco_ele_pfnehadiso not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso1, label1, reco_ele_pfnehadiso2, label2, path, "data_reco_ele_pfnehadiso", "top_right", true, false);


  //Ele PF Neutral Hadron Isolation Signal
  TH1D *reco_ele_pfnehadiso_signal1 = 0;
  TH1D *reco_ele_pfnehadiso_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_signal",reco_ele_pfnehadiso_signal1);
  if (reco_ele_pfnehadiso_signal1 == 0) { cout << "reco_ele_pfnehadiso_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_signal",reco_ele_pfnehadiso_signal2);
  if (reco_ele_pfnehadiso_signal2 == 0) { cout << "reco_ele_pfnehadiso_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_signal1, label1, reco_ele_pfnehadiso_signal2, label2, path, "data_reco_ele_pfnehadiso_signal", "top_right", true, false);

  //Ele PF Neutral Hadron Isolation Background
  TH1D *reco_ele_pfnehadiso_bkg1 = 0;
  TH1D *reco_ele_pfnehadiso_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_bkg",reco_ele_pfnehadiso_bkg1);
  if (reco_ele_pfnehadiso_bkg1 == 0) { cout << "reco_ele_pfnehadiso_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_bkg",reco_ele_pfnehadiso_bkg2);
  if (reco_ele_pfnehadiso_bkg2 == 0) { cout << "reco_ele_pfnehadiso_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_bkg1, label1, reco_ele_pfnehadiso_bkg2, label2, path, "data_reco_ele_pfnehadiso_bkg", "top_right", true, false);


  //Ele PF Neutral Hadron Isolation Relative
  TH1D *reco_ele_pfnehadisorel1 = 0;
  TH1D *reco_ele_pfnehadisorel2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel",reco_ele_pfnehadisorel1);
  if (reco_ele_pfnehadisorel1 == 0) { cout << "reco_ele_pfnehadisorel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel",reco_ele_pfnehadisorel2);
  if (reco_ele_pfnehadisorel2 == 0) { cout << "reco_ele_pfnehadisorel not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel1, label1, reco_ele_pfnehadisorel2, label2, path, "data_reco_ele_pfnehadisorel", "top_right", true, false);

  //Ele PF Neutral Hadron Isolation Relative Signal
  TH1D *reco_ele_pfnehadisorel_signal1 = 0;
  TH1D *reco_ele_pfnehadisorel_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_signal",reco_ele_pfnehadisorel_signal1);
  if (reco_ele_pfnehadisorel_signal1 == 0) { cout << "reco_ele_pfnehadisorel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_signal",reco_ele_pfnehadisorel_signal2);
  if (reco_ele_pfnehadisorel_signal2 == 0) { cout << "reco_ele_pfnehadisorel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_signal1, label1, reco_ele_pfnehadisorel_signal2, label2, path, "data_reco_ele_pfnehadisorel_signal", "top_right", true, false);

  //Ele PF Neutral Hadron Isolation Relative Background
  TH1D *reco_ele_pfnehadisorel_bkg1 = 0;
  TH1D *reco_ele_pfnehadisorel_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_bkg",reco_ele_pfnehadisorel_bkg1);
  if (reco_ele_pfnehadisorel_bkg1 == 0) { cout << "reco_ele_pfnehadisorel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_bkg",reco_ele_pfnehadisorel_bkg2);
  if (reco_ele_pfnehadisorel_bkg2 == 0) { cout << "reco_ele_pfnehadisorel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_bkg1, label1, reco_ele_pfnehadisorel_bkg2, label2, path, "data_reco_ele_pfnehadisorel_bkg", "top_right", true, false);


  //Ele PF Neutral Hadron Isolation Barrel
  TH1D *reco_ele_pfnehadiso_barrel1 = 0;
  TH1D *reco_ele_pfnehadiso_barrel2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_barrel",reco_ele_pfnehadiso_barrel1);
  if (reco_ele_pfnehadiso_barrel1 == 0) { cout << "reco_ele_pfnehadiso_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_barrel",reco_ele_pfnehadiso_barrel2);
  if (reco_ele_pfnehadiso_barrel2 == 0) { cout << "reco_ele_pfnehadiso_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_barrel1, label1, reco_ele_pfnehadiso_barrel2, label2, path, "data_reco_ele_pfnehadiso_barrel", "top_right", true, false);

  //Ele PF Neutral Hadron Isolation Barrel Signal
  TH1D *reco_ele_pfnehadiso_barrel_signal1 = 0;
  TH1D *reco_ele_pfnehadiso_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_barrel_signal",reco_ele_pfnehadiso_barrel_signal1);
  if (reco_ele_pfnehadiso_barrel_signal1 == 0) { cout << "reco_ele_pfnehadiso_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_barrel_signal",reco_ele_pfnehadiso_barrel_signal2);
  if (reco_ele_pfnehadiso_barrel_signal2 == 0) { cout << "reco_ele_pfnehadiso_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_barrel_signal1, label1, reco_ele_pfnehadiso_barrel_signal2, label2, path, "data_reco_ele_pfnehadiso_barrel_signal", "top_right", true, false);

  //Ele PF Neutral Hadron Isolation Barrel Background
  TH1D *reco_ele_pfnehadiso_barrel_bkg1 = 0;
  TH1D *reco_ele_pfnehadiso_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_barrel_bkg",reco_ele_pfnehadiso_barrel_bkg1);
  if (reco_ele_pfnehadiso_barrel_bkg1 == 0) { cout << "reco_ele_pfnehadiso_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_barrel_bkg",reco_ele_pfnehadiso_barrel_bkg2);
  if (reco_ele_pfnehadiso_barrel_bkg2 == 0) { cout << "reco_ele_pfnehadiso_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_barrel_bkg1, label1, reco_ele_pfnehadiso_barrel_bkg2, label2, path, "data_reco_ele_pfnehadiso_barrel_bkg", "top_right", true, false);


  //Ele PF Neutral Hadron Relative Isolation Barrel
  TH1D *reco_ele_pfnehadisorel_barrel1 = 0;
  TH1D *reco_ele_pfnehadisorel_barrel2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_barrel",reco_ele_pfnehadisorel_barrel1);
  if (reco_ele_pfnehadisorel_barrel1 == 0) { cout << "reco_ele_pfnehadisorel_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_barrel",reco_ele_pfnehadisorel_barrel2);
  if (reco_ele_pfnehadisorel_barrel2 == 0) { cout << "reco_ele_pfnehadisorel_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_barrel1, label1, reco_ele_pfnehadisorel_barrel2, label2, path, "data_reco_ele_pfnehadisorel_barrel", "top_right", true, false);


  //Ele PF Neutral Hadron Relative Isolation Barrel Signal
  TH1D *reco_ele_pfnehadisorel_barrel_signal1 = 0;
  TH1D *reco_ele_pfnehadisorel_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_barrel_signal",reco_ele_pfnehadisorel_barrel_signal1);
  if (reco_ele_pfnehadisorel_barrel_signal1 == 0) { cout << "reco_ele_pfnehadisorel_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_barrel_signal",reco_ele_pfnehadisorel_barrel_signal2);
  if (reco_ele_pfnehadisorel_barrel_signal2 == 0) { cout << "reco_ele_pfnehadisorel_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_barrel_signal1, label1, reco_ele_pfnehadisorel_barrel_signal2, label2, path, "data_reco_ele_pfnehadisorel_barrel_signal", "top_right", true, false);


  //Ele PF Neutral Hadron Relative Isolation Barrel Background
  TH1D *reco_ele_pfnehadisorel_barrel_bkg1 = 0;
  TH1D *reco_ele_pfnehadisorel_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_barrel_bkg",reco_ele_pfnehadisorel_barrel_bkg1);
  if (reco_ele_pfnehadisorel_barrel_bkg1 == 0) { cout << "reco_ele_pfnehadisorel_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_barrel_bkg",reco_ele_pfnehadisorel_barrel_bkg2);
  if (reco_ele_pfnehadisorel_barrel_bkg2 == 0) { cout << "reco_ele_pfnehadisorel_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_barrel_bkg1, label1, reco_ele_pfnehadisorel_barrel_bkg2, label2, path, "data_reco_ele_pfnehadisorel_barrel_bkg", "top_right", true, false);

  //Ele PF Neutral Hadron Isolation EndCap
  TH1D *reco_ele_pfnehadiso_endcap1 = 0;
  TH1D *reco_ele_pfnehadiso_endcap2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_endcap",reco_ele_pfnehadiso_endcap1);
  if (reco_ele_pfnehadiso_endcap1 == 0) { cout << "reco_ele_pfnehadiso_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_endcap",reco_ele_pfnehadiso_endcap2);
  if (reco_ele_pfnehadiso_endcap2 == 0) { cout << "reco_ele_pfnehadiso_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_endcap1, label1, reco_ele_pfnehadiso_endcap2, label2, path, "data_reco_ele_pfnehadiso_endcap", "top_right", true, false);


  //Ele PF Neutral Hadron Isolation EndCap Signal
  TH1D *reco_ele_pfnehadiso_endcap_signal1 = 0;
  TH1D *reco_ele_pfnehadiso_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_endcap_signal",reco_ele_pfnehadiso_endcap_signal1);
  if (reco_ele_pfnehadiso_endcap_signal1 == 0) { cout << "reco_ele_pfnehadiso_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_endcap_signal",reco_ele_pfnehadiso_endcap_signal2);
  if (reco_ele_pfnehadiso_endcap_signal2 == 0) { cout << "reco_ele_pfnehadiso_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_endcap_signal1, label1, reco_ele_pfnehadiso_endcap_signal2, label2, path, "data_reco_ele_pfnehadiso_endcap_signal", "top_right", true, false);

  //Ele PF Neutral Hadron Isolation EndCap Background
  TH1D *reco_ele_pfnehadiso_endcap_bkg1 = 0;
  TH1D *reco_ele_pfnehadiso_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_endcap_bkg",reco_ele_pfnehadiso_endcap_bkg1);
  if (reco_ele_pfnehadiso_endcap_bkg1 == 0) { cout << "reco_ele_pfnehadiso_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_endcap_bkg",reco_ele_pfnehadiso_endcap_bkg2);
  if (reco_ele_pfnehadiso_endcap_bkg2 == 0) { cout << "reco_ele_pfnehadiso_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_endcap_bkg1, label1, reco_ele_pfnehadiso_endcap_bkg2, label2, path, "data_reco_ele_pfnehadiso_endcap_bkg", "top_right", true, false);

  //Ele PF Neutral Hadron Relative Isolation EndCap
  TH1D *reco_ele_pfnehadisorel_endcap1 = 0;
  TH1D *reco_ele_pfnehadisorel_endcap2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_endcap",reco_ele_pfnehadisorel_endcap1);
  if (reco_ele_pfnehadisorel_endcap1 == 0) { cout << "reco_ele_pfnehadisorel_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_endcap",reco_ele_pfnehadisorel_endcap2);
  if (reco_ele_pfnehadisorel_endcap2 == 0) { cout << "reco_ele_pfnehadisorel_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_endcap1, label1, reco_ele_pfnehadisorel_endcap2, label2, path, "data_reco_ele_pfnehadisorel_endcap", "top_right", true, false);

  //Ele PF Neutral Hadron Relative Isolation EndCap Signal
  TH1D *reco_ele_pfnehadisorel_endcap_signal1 = 0;
  TH1D *reco_ele_pfnehadisorel_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_endcap_signal",reco_ele_pfnehadisorel_endcap_signal1);
  if (reco_ele_pfnehadisorel_endcap_signal1 == 0) { cout << "reco_ele_pfnehadisorel_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_endcap_signal",reco_ele_pfnehadisorel_endcap_signal2);
  if (reco_ele_pfnehadisorel_endcap_signal2 == 0) { cout << "reco_ele_pfnehadisorel_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_endcap_signal1, label1, reco_ele_pfnehadisorel_endcap_signal2, label2, path, "data_reco_ele_pfnehadisorel_endcap_signal", "top_right", true, false);


  //Ele PF Neutral Hadron Relative Isolation EndCap Background
  TH1D *reco_ele_pfnehadisorel_endcap_bkg1 = 0;
  TH1D *reco_ele_pfnehadisorel_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_endcap_bkg",reco_ele_pfnehadisorel_endcap_bkg1);
  if (reco_ele_pfnehadisorel_endcap_bkg1 == 0) { cout << "reco_ele_pfnehadisorel_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_endcap_bkg",reco_ele_pfnehadisorel_endcap_bkg2);
  if (reco_ele_pfnehadisorel_endcap_bkg2 == 0) { cout << "reco_ele_pfnehadisorel_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_endcap_bkg1, label1, reco_ele_pfnehadisorel_endcap_bkg2, label2, path, "data_reco_ele_pfnehadisorel_endcap_bkg", "top_right", true, false);

  //Ele PF Photon Isolation
  TH1D *reco_ele_pfphotoniso1 = 0;
  TH1D *reco_ele_pfphotoniso2 = 0;

  f1->GetObject("reco_ele_pfphotoniso",reco_ele_pfphotoniso1);
  if (reco_ele_pfphotoniso1 == 0) { cout << "reco_ele_pfphotoniso not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso",reco_ele_pfphotoniso2);
  if (reco_ele_pfphotoniso2 == 0) { cout << "reco_ele_pfphotoniso not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso1, label1, reco_ele_pfphotoniso2, label2, path, "data_reco_ele_pfphotoniso", "top_right", true, false);


  //Ele PF Photon Isolation Signal
  TH1D *reco_ele_pfphotoniso_signal1 = 0;
  TH1D *reco_ele_pfphotoniso_signal2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_signal",reco_ele_pfphotoniso_signal1);
  if (reco_ele_pfphotoniso_signal1 == 0) { cout << "reco_ele_pfphotoniso_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_signal",reco_ele_pfphotoniso_signal2);
  if (reco_ele_pfphotoniso_signal2 == 0) { cout << "reco_ele_pfphotoniso_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_signal1, label1, reco_ele_pfphotoniso_signal2, label2, path, "data_reco_ele_pfphotoniso_signal", "top_right", true, false);

  //Ele PF Photon Isolation Background
  TH1D *reco_ele_pfphotoniso_bkg1 = 0;
  TH1D *reco_ele_pfphotoniso_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_bkg",reco_ele_pfphotoniso_bkg1);
  if (reco_ele_pfphotoniso_bkg1 == 0) { cout << "reco_ele_pfphotoniso_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_bkg",reco_ele_pfphotoniso_bkg2);
  if (reco_ele_pfphotoniso_bkg2 == 0) { cout << "reco_ele_pfphotoniso_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_bkg1, label1, reco_ele_pfphotoniso_bkg2, label2, path, "data_reco_ele_pfphotoniso_bkg", "top_right", true, false);


  //Ele PF Photon Relative Isolation
  TH1D *reco_ele_pfphotonisorel1 = 0;
  TH1D *reco_ele_pfphotonisorel2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel",reco_ele_pfphotonisorel1);
  if (reco_ele_pfphotonisorel1 == 0) { cout << "reco_ele_pfphotonisorel1 not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel",reco_ele_pfphotonisorel2);
  if (reco_ele_pfphotonisorel2 == 0) { cout << "reco_ele_pfphotonisorel2 not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel1, label1, reco_ele_pfphotonisorel2, label2, path, "data_reco_ele_pfphotonisorel", "top_right", true, false);

  //Ele PF Photon Relative Isolation Signal
  TH1D *reco_ele_pfphotonisorel_signal1 = 0;
  TH1D *reco_ele_pfphotonisorel_signal2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_signal",reco_ele_pfphotonisorel_signal1);
  if (reco_ele_pfphotonisorel_signal1 == 0) { cout << "reco_ele_pfphotonisorel_signal1 not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_signal",reco_ele_pfphotonisorel_signal2);
  if (reco_ele_pfphotonisorel_signal2 == 0) { cout << "reco_ele_pfphotonisorel_signal2 not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_signal1, label1, reco_ele_pfphotonisorel_signal2, label2, path, "data_reco_ele_pfphotonisorel_signal", "top_right", true, false);

  //Ele PF Photon Relative Isolation Background
  TH1D *reco_ele_pfphotonisorel_bkg1 = 0;
  TH1D *reco_ele_pfphotonisorel_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_bkg",reco_ele_pfphotonisorel_bkg1);
  if (reco_ele_pfphotonisorel_bkg1 == 0) { cout << "reco_ele_pfphotonisorel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_bkg",reco_ele_pfphotonisorel_bkg2);
  if (reco_ele_pfphotonisorel_bkg2 == 0) { cout << "reco_ele_pfphotonisorel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_bkg1, label1, reco_ele_pfphotonisorel_bkg2, label2, path, "data_reco_ele_pfphotonisorel_bkg", "top_right", true, false);


  //Ele PF Photon Isolation Barrel
  TH1D *reco_ele_pfphotoniso_barrel1 = 0;
  TH1D *reco_ele_pfphotoniso_barrel2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_barrel",reco_ele_pfphotoniso_barrel1);
  if (reco_ele_pfphotoniso_barrel1 == 0) { cout << "reco_ele_pfphotoniso_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_barrel",reco_ele_pfphotoniso_barrel2);
  if (reco_ele_pfphotoniso_barrel2 == 0) { cout << "reco_ele_pfphotoniso_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_barrel1, label1, reco_ele_pfphotoniso_barrel2, label2, path, "data_reco_ele_pfphotoniso_barrel", "top_right", true, false);


  //Ele PF Photon Isolation Barrel Signal
  TH1D *reco_ele_pfphotoniso_barrel_signal1 = 0;
  TH1D *reco_ele_pfphotoniso_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_barrel_signal",reco_ele_pfphotoniso_barrel_signal1);
  if (reco_ele_pfphotoniso_barrel_signal1 == 0) { cout << "reco_ele_pfphotoniso_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_barrel_signal",reco_ele_pfphotoniso_barrel_signal2);
  if (reco_ele_pfphotoniso_barrel_signal2 == 0) { cout << "reco_ele_pfphotoniso_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_barrel_signal1, label1, reco_ele_pfphotoniso_barrel_signal2, label2, path, "data_reco_ele_pfphotoniso_barrel_signal", "top_right", true, false);

  //Ele PF Photon Isolation Barrel Background
  TH1D *reco_ele_pfphotoniso_barrel_bkg1 = 0;
  TH1D *reco_ele_pfphotoniso_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_barrel_bkg",reco_ele_pfphotoniso_barrel_bkg1);
  if (reco_ele_pfphotoniso_barrel_bkg1 == 0) { cout << "reco_ele_pfphotoniso_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_barrel_bkg",reco_ele_pfphotoniso_barrel_bkg2);
  if (reco_ele_pfphotoniso_barrel_bkg2 == 0) { cout << "reco_ele_pfphotoniso_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_barrel_bkg1, label1, reco_ele_pfphotoniso_barrel_bkg2, label2, path, "data_reco_ele_pfphotoniso_barrel_bkg", "top_right", true, false);


  //Ele PF Photon Relative Isolation Barrel
  TH1D *reco_ele_pfphotonisorel_barrel1 = 0;
  TH1D *reco_ele_pfphotonisorel_barrel2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_barrel",reco_ele_pfphotonisorel_barrel1);
  if (reco_ele_pfphotonisorel_barrel1 == 0) { cout << "reco_ele_pfphotoniso_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_barrel",reco_ele_pfphotonisorel_barrel2);
  if (reco_ele_pfphotonisorel_barrel2 == 0) { cout << "reco_ele_pfphotonisorel_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_barrel1, label1, reco_ele_pfphotonisorel_barrel2, label2, path, "data_reco_ele_pfphotonisorel_barrel", "top_right", true, false);

  //Ele PF Photon Relative Isolation Barrel Signal
  TH1D *reco_ele_pfphotonisorel_barrel_signal1 = 0;
  TH1D *reco_ele_pfphotonisorel_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_barrel_signal",reco_ele_pfphotonisorel_barrel_signal1);
  if (reco_ele_pfphotonisorel_barrel_signal1 == 0) { cout << "reco_ele_pfphotonisorel_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_barrel_signal",reco_ele_pfphotonisorel_barrel_signal2);
  if (reco_ele_pfphotonisorel_barrel_signal2 == 0) { cout << "reco_ele_pfphotonisorel_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_barrel_signal1, label1, reco_ele_pfphotonisorel_barrel_signal2, label2, path, "data_reco_ele_pfphotonisorel_barrel_signal", "top_right", true, false);


  //Ele PF Photon Relative Isolation Barrel Background
  TH1D *reco_ele_pfphotonisorel_barrel_bkg1 = 0;
  TH1D *reco_ele_pfphotonisorel_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_barrel_bkg",reco_ele_pfphotonisorel_barrel_bkg1);
  if (reco_ele_pfphotonisorel_barrel_bkg1 == 0) { cout << "reco_ele_pfphotonisorel_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_barrel_bkg",reco_ele_pfphotonisorel_barrel_bkg2);
  if (reco_ele_pfphotonisorel_barrel_bkg2 == 0) { cout << "reco_ele_pfphotonisorel_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_barrel_bkg1, label1, reco_ele_pfphotonisorel_barrel_bkg2, label2, path, "data_reco_ele_pfphotonisorel_barrel_bkg", "top_right", true, false);


  //Ele PF Photon Isolation EndCap
  TH1D *reco_ele_pfphotoniso_endcap1 = 0;
  TH1D *reco_ele_pfphotoniso_endcap2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_endcap",reco_ele_pfphotoniso_endcap1);
  if (reco_ele_pfphotoniso_endcap1 == 0) { cout << "reco_ele_pfphotoniso_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_endcap",reco_ele_pfphotoniso_endcap2);
  if (reco_ele_pfphotoniso_endcap2 == 0) { cout << "reco_ele_pfphotoniso_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_endcap1, label1, reco_ele_pfphotoniso_endcap2, label2, path, "data_reco_ele_pfphotoniso_endcap", "top_right", true, false);

  //Ele PF Photon Isolation EndCap Signal
  TH1D *reco_ele_pfphotoniso_endcap_signal1 = 0;
  TH1D *reco_ele_pfphotoniso_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_endcap_signal",reco_ele_pfphotoniso_endcap_signal1);
  if (reco_ele_pfphotoniso_endcap_signal1 == 0) { cout << "reco_ele_pfphotoniso_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_endcap_signal",reco_ele_pfphotoniso_endcap_signal2);
  if (reco_ele_pfphotoniso_endcap_signal2 == 0) { cout << "reco_ele_pfphotoniso_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_endcap_signal1, label1, reco_ele_pfphotoniso_endcap_signal2, label2, path, "data_reco_ele_pfphotoniso_endcap_signal", "top_right", true, false);

  //Ele PF Photon Isolation EndCap Background
  TH1D *reco_ele_pfphotoniso_endcap_bkg1 = 0;
  TH1D *reco_ele_pfphotoniso_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_endcap_bkg",reco_ele_pfphotoniso_endcap_bkg1);
  if (reco_ele_pfphotoniso_endcap_bkg1 == 0) { cout << "reco_ele_pfphotoniso_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_endcap_bkg",reco_ele_pfphotoniso_endcap_bkg2);
  if (reco_ele_pfphotoniso_endcap_bkg2 == 0) { cout << "reco_ele_pfphotoniso_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_endcap_bkg1, label1, reco_ele_pfphotoniso_endcap_bkg2, label2, path, "data_reco_ele_pfphotoniso_endcap_bkg", "top_right", true, false);


  //Ele PF Photon Relative Isolation EndCap
  TH1D *reco_ele_pfphotonisorel_endcap1 = 0;
  TH1D *reco_ele_pfphotonisorel_endcap2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_endcap",reco_ele_pfphotonisorel_endcap1);
  if (reco_ele_pfphotonisorel_endcap1 == 0) { cout << "reco_ele_pfphotonisorel_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_endcap",reco_ele_pfphotonisorel_endcap2);
  if (reco_ele_pfphotonisorel_endcap2 == 0) { cout << "reco_ele_pfphotonisorel_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_endcap1, label1, reco_ele_pfphotonisorel_endcap2, label2, path, "data_reco_ele_pfphotonisorel_endcap", "top_right", true, false);

  //Ele PF Photon Relative Isolation EndCap Signal
  TH1D *reco_ele_pfphotonisorel_endcap_signal1 = 0;
  TH1D *reco_ele_pfphotonisorel_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_endcap_signal",reco_ele_pfphotonisorel_endcap_signal1);
  if (reco_ele_pfphotonisorel_endcap_signal1 == 0) { cout << "reco_ele_pfphotonisorel_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_endcap_signal",reco_ele_pfphotonisorel_endcap_signal2);
  if (reco_ele_pfphotonisorel_endcap_signal2 == 0) { cout << "reco_ele_pfphotonisorel_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_endcap_signal1, label1, reco_ele_pfphotonisorel_endcap_signal2, label2, path, "data_reco_ele_pfphotonisorel_endcap_signal", "top_right", true, false);


  //Ele PF Photon Relative Isolation EndCap Background
  TH1D *reco_ele_pfphotonisorel_endcap_bkg1 = 0;
  TH1D *reco_ele_pfphotonisorel_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_endcap_bkg",reco_ele_pfphotonisorel_endcap_bkg1);
  if (reco_ele_pfphotonisorel_endcap_bkg1 == 0) { cout << "reco_ele_pfphotonisorel_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_endcap_bkg",reco_ele_pfphotonisorel_endcap_bkg2);
  if (reco_ele_pfphotonisorel_endcap_bkg2 == 0) { cout << "reco_ele_pfphotonisorel_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_endcap_bkg1, label1, reco_ele_pfphotonisorel_endcap_bkg2, label2, path, "data_reco_ele_pfphotonisorel_endcap_bkg", "top_right", true, false);


  //Ele PF Charged Hadrons for Pile-Up Isolation
  TH1D *reco_ele_pfchargedfrompu1 = 0;
  TH1D *reco_ele_pfchargedfrompu2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu",reco_ele_pfchargedfrompu1);
  if (reco_ele_pfchargedfrompu1 == 0) { cout << "reco_ele_pfchargedfrompu not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu",reco_ele_pfchargedfrompu2);
  if (reco_ele_pfchargedfrompu2 == 0) { cout << "reco_ele_pfchargedfrompu not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu1, label1, reco_ele_pfchargedfrompu2, label2, path, "data_reco_ele_pfchargedfrompu", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Isolation Signal
  TH1D *reco_ele_pfchargedfrompu_signal1 = 0;
  TH1D *reco_ele_pfchargedfrompu_signal2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu_signal",reco_ele_pfchargedfrompu_signal1);
  if (reco_ele_pfchargedfrompu_signal1 == 0) { cout << "reco_ele_pfchargedfrompu_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu_signal",reco_ele_pfchargedfrompu_signal2);
  if (reco_ele_pfchargedfrompu_signal2 == 0) { cout << "reco_ele_pfchargedfrompu_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu_signal1, label1, reco_ele_pfchargedfrompu_signal2, label2, path, "data_reco_ele_pfchargedfrompu_signal", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Isolation Background
  TH1D *reco_ele_pfchargedfrompu_bkg1 = 0;
  TH1D *reco_ele_pfchargedfrompu_bkg2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu_bkg",reco_ele_pfchargedfrompu_bkg1);
  if (reco_ele_pfchargedfrompu_bkg1 == 0) { cout << "reco_ele_pfchargedfrompu_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu_bkg",reco_ele_pfchargedfrompu_bkg2);
  if (reco_ele_pfchargedfrompu_bkg2 == 0) { cout << "reco_ele_pfchargedfrompu_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu_bkg1, label1, reco_ele_pfchargedfrompu_bkg2, label2, path, "data_reco_ele_pfchargedfrompu_bkg", "top_right", true, false);


  //Ele PF Charged Hadrons for Pile-Up Relative Isolation
  TH1D *reco_ele_pfchargedfrompurel1 = 0;
  TH1D *reco_ele_pfchargedfrompurel2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel",reco_ele_pfchargedfrompurel1);
  if (reco_ele_pfchargedfrompurel1 == 0) { cout << "reco_ele_pfchargedfrompurel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel",reco_ele_pfchargedfrompurel2);
  if (reco_ele_pfchargedfrompurel2 == 0) { cout << "reco_ele_pfchargedfrompurel not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel1, label1, reco_ele_pfchargedfrompurel2, label2, path, "data_reco_ele_pfchargedfrompurel", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Relative Isolation Signal
  TH1D *reco_ele_pfchargedfrompurel_signal1 = 0;
  TH1D *reco_ele_pfchargedfrompurel_signal2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel_signal",reco_ele_pfchargedfrompurel_signal1);
  if (reco_ele_pfchargedfrompurel_signal1 == 0) { cout << "reco_ele_pfchargedfrompurel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel_signal",reco_ele_pfchargedfrompurel_signal2);
  if (reco_ele_pfchargedfrompurel_signal2 == 0) { cout << "reco_ele_pfchargedfrompurel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel_signal1, label1, reco_ele_pfchargedfrompurel_signal2, label2, path, "data_reco_ele_pfchargedfrompurel_signal", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Relative Isolation Background
  TH1D *reco_ele_pfchargedfrompurel_bkg1 = 0;
  TH1D *reco_ele_pfchargedfrompurel_bkg2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel_bkg",reco_ele_pfchargedfrompurel_bkg1);
  if (reco_ele_pfchargedfrompurel_bkg1 == 0) { cout << "reco_ele_pfchargedfrompurel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel_bkg",reco_ele_pfchargedfrompurel_bkg2);
  if (reco_ele_pfchargedfrompurel_bkg2 == 0) { cout << "reco_ele_pfchargedfrompurel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel_bkg1, label1, reco_ele_pfchargedfrompurel_bkg2, label2, path, "data_reco_ele_pfchargedfrompurel_bkg", "top_right", true, false);


  //Ele PF Charged Hadrons for Pile-Up Isolation Barrel
  TH1D *reco_ele_pfchargedfrompu_barrel1 = 0;
  TH1D *reco_ele_pfchargedfrompu_barrel2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu_barrel",reco_ele_pfchargedfrompu_barrel1);
  if (reco_ele_pfchargedfrompu_barrel1 == 0) { cout << "reco_ele_pfchargedfrompu_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu_barrel",reco_ele_pfchargedfrompu_barrel2);
  if (reco_ele_pfchargedfrompu_barrel2 == 0) { cout << "reco_ele_pfchargedfrompu_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu_barrel1, label1, reco_ele_pfchargedfrompu_barrel2, label2, path, "data_reco_ele_pfchargedfrompu_barrel", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Isolation Barrel Signal
  TH1D *reco_ele_pfchargedfrompu_barrel_signal1 = 0;
  TH1D *reco_ele_pfchargedfrompu_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu_barrel_signal",reco_ele_pfchargedfrompu_barrel_signal1);
  if (reco_ele_pfchargedfrompu_barrel_signal1 == 0) { cout << "reco_ele_pfchargedfrompu_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu_barrel_signal",reco_ele_pfchargedfrompu_barrel_signal2);
  if (reco_ele_pfchargedfrompu_barrel_signal2 == 0) { cout << "reco_ele_pfchargedfrompu_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu_barrel_signal1, label1, reco_ele_pfchargedfrompu_barrel_signal2, label2, path, "data_reco_ele_pfchargedfrompu_barrel_signal", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Isolation Barrel Background
  TH1D *reco_ele_pfchargedfrompu_barrel_bkg1 = 0;
  TH1D *reco_ele_pfchargedfrompu_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu_barrel_bkg",reco_ele_pfchargedfrompu_barrel_bkg1);
  if (reco_ele_pfchargedfrompu_barrel_bkg1 == 0) { cout << "reco_ele_pfchargedfrompu_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu_barrel_bkg",reco_ele_pfchargedfrompu_barrel_bkg2);
  if (reco_ele_pfchargedfrompu_barrel_bkg2 == 0) { cout << "reco_ele_pfchargedfrompu_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu_barrel_bkg1, label1, reco_ele_pfchargedfrompu_barrel_bkg2, label2, path, "data_reco_ele_pfchargedfrompu_barrel_bkg", "top_right", true, false);


  //Ele PF Charged Hadrons for Pile-Up Relative Isolation Barrel
  TH1D *reco_ele_pfchargedfrompurel_barrel1 = 0;
  TH1D *reco_ele_pfchargedfrompurel_barrel2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel_barrel",reco_ele_pfchargedfrompurel_barrel1);
  if (reco_ele_pfchargedfrompurel_barrel1 == 0) { cout << "reco_ele_pfchargedfrompurel_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel_barrel",reco_ele_pfchargedfrompurel_barrel2);
  if (reco_ele_pfchargedfrompurel_barrel2 == 0) { cout << "reco_ele_pfchargedfrompurel_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel_barrel1, label1, reco_ele_pfchargedfrompurel_barrel2, label2, path, "data_reco_ele_pfchargedfrompurel_barrel", "top_right", true, false);


  //Ele PF Charged Hadrons for Pile-Up Relative Isolation Barrel Signal
  TH1D *reco_ele_pfchargedfrompurel_barrel_signal1 = 0;
  TH1D *reco_ele_pfchargedfrompurel_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel_barrel_signal",reco_ele_pfchargedfrompurel_barrel_signal1);
  if (reco_ele_pfchargedfrompurel_barrel_signal1 == 0) { cout << "reco_ele_pfchargedfrompurel_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel_barrel_signal",reco_ele_pfchargedfrompurel_barrel_signal2);
  if (reco_ele_pfchargedfrompurel_barrel_signal2 == 0) { cout << "reco_ele_pfchargedfrompurel_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel_barrel_signal1, label1, reco_ele_pfchargedfrompurel_barrel_signal2, label2, path, "data_reco_ele_pfchargedfrompurel_barrel_signal", "top_right", true, false);


  //Ele PF Charged Hadrons for Pile-Up Relative Isolation Barrel Background
  TH1D *reco_ele_pfchargedfrompurel_barrel_bkg1 = 0;
  TH1D *reco_ele_pfchargedfrompurel_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel_barrel_bkg",reco_ele_pfchargedfrompurel_barrel_bkg1);
  if (reco_ele_pfchargedfrompurel_barrel_bkg1 == 0) { cout << "reco_ele_pfchargedfrompurel_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel_barrel_bkg",reco_ele_pfchargedfrompurel_barrel_bkg2);
  if (reco_ele_pfchargedfrompurel_barrel_bkg2 == 0) { cout << "reco_ele_pfchargedfrompurel_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel_barrel_bkg1, label1, reco_ele_pfchargedfrompurel_barrel_bkg2, label2, path, "data_reco_ele_pfchargedfrompurel_barrel_bkg", "top_right", true, false);


  //Ele PF Charged Hadrons for Pile-Up Isolation EndCap
  TH1D *reco_ele_pfchargedfrompu_endcap1 = 0;
  TH1D *reco_ele_pfchargedfrompu_endcap2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu_endcap",reco_ele_pfchargedfrompu_endcap1);
  if (reco_ele_pfchargedfrompu_endcap1 == 0) { cout << "reco_ele_pfchargedfrompu_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu_endcap",reco_ele_pfchargedfrompu_endcap2);
  if (reco_ele_pfchargedfrompu_endcap2 == 0) { cout << "reco_ele_pfchargedfrompu_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu_endcap1, label1, reco_ele_pfchargedfrompu_endcap2, label2, path, "data_reco_ele_pfchargedfrompu_endcap", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Isolation EndCap Signal
  TH1D *reco_ele_pfchargedfrompu_endcap_signal1 = 0;
  TH1D *reco_ele_pfchargedfrompu_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu_endcap_signal",reco_ele_pfchargedfrompu_endcap_signal1);
  if (reco_ele_pfchargedfrompu_endcap_signal1 == 0) { cout << "reco_ele_pfchargedfrompu_endcap_signal1 not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu_endcap_signal",reco_ele_pfchargedfrompu_endcap_signal2);
  if (reco_ele_pfchargedfrompu_endcap_signal2 == 0) { cout << "reco_ele_pfchargedfrompu_endcap_signal2 not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu_endcap_signal1, label1, reco_ele_pfchargedfrompu_endcap_signal2, label2, path, "data_reco_ele_pfchargedfrompu_endcap_signal", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Isolation EndCap Background
  TH1D *reco_ele_pfchargedfrompu_endcap_bkg1 = 0;
  TH1D *reco_ele_pfchargedfrompu_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompu_endcap_bkg",reco_ele_pfchargedfrompu_endcap_bkg1);
  if (reco_ele_pfchargedfrompu_endcap_bkg1 == 0) { cout << "reco_ele_pfchargedfrompu_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompu_endcap_bkg",reco_ele_pfchargedfrompu_endcap_bkg2);
  if (reco_ele_pfchargedfrompu_endcap_bkg2 == 0) { cout << "reco_ele_pfchargedfrompu_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompu_endcap_bkg1, label1, reco_ele_pfchargedfrompu_endcap_bkg2, label2, path, "data_reco_ele_pfchargedfrompu_endcap_bkg", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Relative Isolation EndCap
  TH1D *reco_ele_pfchargedfrompurel_endcap1 = 0;
  TH1D *reco_ele_pfchargedfrompurel_endcap2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel_endcap",reco_ele_pfchargedfrompurel_endcap1);
  if (reco_ele_pfchargedfrompurel_endcap1 == 0) { cout << "reco_ele_pfchargedfrompurel_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel_endcap",reco_ele_pfchargedfrompurel_endcap2);
  if (reco_ele_pfchargedfrompurel_endcap2 == 0) { cout << "reco_ele_pfchargedfrompurel_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel_endcap1, label1, reco_ele_pfchargedfrompurel_endcap2, label2, path, "data_reco_ele_pfchargedfrompurel_endcap", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Relative Isolation EndCap Signal
  TH1D *reco_ele_pfchargedfrompurel_endcap_signal1 = 0;
  TH1D *reco_ele_pfchargedfrompurel_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel_endcap_signal",reco_ele_pfchargedfrompurel_endcap_signal1);
  if (reco_ele_pfchargedfrompurel_endcap_signal1 == 0) { cout << "reco_ele_pfchargedfrompurel_endcap_signal1 not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel_endcap_signal",reco_ele_pfchargedfrompurel_endcap_signal2);
  if (reco_ele_pfchargedfrompurel_endcap_signal2 == 0) { cout << "reco_ele_pfchargedfrompurel_endcap_signal2 not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel_endcap_signal1, label1, reco_ele_pfchargedfrompurel_endcap_signal2, label2, path, "data_reco_ele_pfchargedfrompurel_endcap_signal", "top_right", true, false);

  //Ele PF Charged Hadrons for Pile-Up Relative Isolation EndCap Background
  TH1D *reco_ele_pfchargedfrompurel_endcap_bkg1 = 0;
  TH1D *reco_ele_pfchargedfrompurel_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfchargedfrompurel_endcap_bkg",reco_ele_pfchargedfrompurel_endcap_bkg1);
  if (reco_ele_pfchargedfrompurel_endcap_bkg1 == 0) { cout << "reco_ele_pfchargedfrompurel_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchargedfrompurel_endcap_bkg",reco_ele_pfchargedfrompurel_endcap_bkg2);
  if (reco_ele_pfchargedfrompurel_endcap_bkg2 == 0) { cout << "reco_ele_pfchargedfrompurel_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchargedfrompurel_endcap_bkg1, label1, reco_ele_pfchargedfrompurel_endcap_bkg2, label2, path, "data_reco_ele_pfchargedfrompurel_endcap_bkg", "top_right", true, false);


  //Ele PF Charged Hadron PUPPI Isolation
  TH1D *reco_ele_pfchhadiso_puppi1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi",reco_ele_pfchhadiso_puppi1);
  if (reco_ele_pfchhadiso_puppi1 == 0) { cout << "reco_ele_pfchhadiso_puppi not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi",reco_ele_pfchhadiso_puppi2);
  if (reco_ele_pfchhadiso_puppi2 == 0) { cout << "reco_ele_pfchhadiso_puppi not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi1, label1, reco_ele_pfchhadiso_puppi2, label2, path, "data_reco_ele_pfchhadiso_puppi", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Isolation Signal
  TH1D *reco_ele_pfchhadiso_puppi_signal1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi_signal",reco_ele_pfchhadiso_puppi_signal1);
  if (reco_ele_pfchhadiso_puppi_signal1 == 0) { cout << "reco_ele_pfchhadiso_puppi_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi_signal",reco_ele_pfchhadiso_puppi_signal2);
  if (reco_ele_pfchhadiso_puppi_signal2 == 0) { cout << "reco_ele_pfchhadiso_puppi_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi_signal1, label1, reco_ele_pfchhadiso_puppi_signal2, label2, path, "data_reco_ele_pfchhadiso_puppi_signal", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Isolation Background
  TH1D *reco_ele_pfchhadiso_puppi_bkg1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi_bkg",reco_ele_pfchhadiso_puppi_bkg1);
  if (reco_ele_pfchhadiso_puppi_bkg1 == 0) { cout << "reco_ele_pfchhadiso_puppi_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi_bkg",reco_ele_pfchhadiso_puppi_bkg2);
  if (reco_ele_pfchhadiso_puppi_bkg2 == 0) { cout << "reco_ele_pfchhadiso_puppi_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi_bkg1, label1, reco_ele_pfchhadiso_puppi_bkg2, label2, path, "data_reco_ele_pfchhadiso_puppi_bkg", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Relative Isolation
  TH1D *reco_ele_pfchhadisorel_puppi1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi",reco_ele_pfchhadisorel_puppi1);
  if (reco_ele_pfchhadisorel_puppi1 == 0) { cout << "reco_ele_pfchhadisorel_puppi not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi",reco_ele_pfchhadisorel_puppi2);
  if (reco_ele_pfchhadisorel_puppi2 == 0) { cout << "reco_ele_pfchhadisorel_puppi not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi1, label1, reco_ele_pfchhadisorel_puppi2, label2, path, "data_reco_ele_pfchhadisorel_puppi", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Relative Isolation Signal
  TH1D *reco_ele_pfchhadisorel_puppi_signal1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi_signal",reco_ele_pfchhadisorel_puppi_signal1);
  if (reco_ele_pfchhadisorel_puppi_signal1 == 0) { cout << "reco_ele_pfchhadisorel_puppi_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi_signal",reco_ele_pfchhadisorel_puppi_signal2);
  if (reco_ele_pfchhadisorel_puppi_signal2 == 0) { cout << "reco_ele_pfchhadisorel_puppi_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi_signal1, label1, reco_ele_pfchhadisorel_puppi_signal2, label2, path, "data_reco_ele_pfchhadisorel_puppi_signal", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Relative Isolation Background
  TH1D *reco_ele_pfchhadisorel_puppi_bkg1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi_bkg",reco_ele_pfchhadisorel_puppi_bkg1);
  if (reco_ele_pfchhadisorel_puppi_bkg1 == 0) { cout << "reco_ele_pfchhadisorel_puppi_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi_bkg",reco_ele_pfchhadisorel_puppi_bkg2);
  if (reco_ele_pfchhadisorel_puppi_bkg2 == 0) { cout << "reco_ele_pfchhadisorel_puppi_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi_bkg1, label1, reco_ele_pfchhadisorel_puppi_bkg2, label2, path, "data_reco_ele_pfchhadisorel_puppi_bkg", "top_right", true, false);


  //Ele PF Charged Hadron PUPPI Isolation Barrel
  TH1D *reco_ele_pfchhadiso_puppi_barrel1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi_barrel2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi_barrel",reco_ele_pfchhadiso_puppi_barrel1);
  if (reco_ele_pfchhadiso_puppi_barrel1 == 0) { cout << "reco_ele_pfchhadiso_puppi_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi_barrel",reco_ele_pfchhadiso_puppi_barrel2);
  if (reco_ele_pfchhadiso_puppi_barrel2 == 0) { cout << "reco_ele_pfchhadiso_puppi_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi_barrel1, label1, reco_ele_pfchhadiso_puppi_barrel2, label2, path, "data_reco_ele_pfchhadiso_puppi_barrel", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Isolation Barrel Signal
  TH1D *reco_ele_pfchhadiso_puppi_barrel_signal1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi_barrel_signal",reco_ele_pfchhadiso_puppi_barrel_signal1);
  if (reco_ele_pfchhadiso_puppi_barrel_signal1 == 0) { cout << "reco_ele_pfchhadiso_puppi_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi_barrel_signal",reco_ele_pfchhadiso_puppi_barrel_signal2);
  if (reco_ele_pfchhadiso_puppi_barrel_signal2 == 0) { cout << "reco_ele_pfchhadiso_puppi_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi_barrel_signal1, label1, reco_ele_pfchhadiso_puppi_barrel_signal2, label2, path, "data_reco_ele_pfchhadiso_puppi_barrel_signal", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Isolation Barrel Background
  TH1D *reco_ele_pfchhadiso_puppi_barrel_bkg1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi_barrel_bkg",reco_ele_pfchhadiso_puppi_barrel_bkg1);
  if (reco_ele_pfchhadiso_puppi_barrel_bkg1 == 0) { cout << "reco_ele_pfchhadiso_puppi_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi_barrel_bkg",reco_ele_pfchhadiso_puppi_barrel_bkg2);
  if (reco_ele_pfchhadiso_puppi_barrel_bkg2 == 0) { cout << "reco_ele_pfchhadiso_puppi_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi_barrel_bkg1, label1, reco_ele_pfchhadiso_puppi_barrel_bkg2, label2, path, "data_reco_ele_pfchhadiso_puppi_barrel_bkg", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Relative Isolation Barrel
  TH1D *reco_ele_pfchhadisorel_puppi_barrel1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi_barrel2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi_barrel",reco_ele_pfchhadisorel_puppi_barrel1);
  if (reco_ele_pfchhadisorel_puppi_barrel1 == 0) { cout << "reco_ele_pfchhadisorel_puppi_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi_barrel",reco_ele_pfchhadisorel_puppi_barrel2);
  if (reco_ele_pfchhadisorel_puppi_barrel2 == 0) { cout << "reco_ele_pfchhadisorel_puppi_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi_barrel1, label1, reco_ele_pfchhadisorel_puppi_barrel2, label2, path, "data_reco_ele_pfchhadisorel_puppi_barrel", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Relative Isolation Barrel Signal
  TH1D *reco_ele_pfchhadisorel_puppi_barrel_signal1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi_barrel_signal",reco_ele_pfchhadisorel_puppi_barrel_signal1);
  if (reco_ele_pfchhadisorel_puppi_barrel_signal1 == 0) { cout << "reco_ele_pfchhadisorel_puppi_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi_barrel_signal",reco_ele_pfchhadisorel_puppi_barrel_signal2);
  if (reco_ele_pfchhadisorel_puppi_barrel_signal2 == 0) { cout << "reco_ele_pfchhadisorel_puppi_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi_barrel_signal1, label1, reco_ele_pfchhadisorel_puppi_barrel_signal2, label2, path, "data_reco_ele_pfchhadisorel_puppi_barrel_signal", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Relative Isolation Barrel Background
  TH1D *reco_ele_pfchhadisorel_puppi_barrel_bkg1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi_barrel_bkg",reco_ele_pfchhadisorel_puppi_barrel_bkg1);
  if (reco_ele_pfchhadisorel_puppi_barrel_bkg1 == 0) { cout << "reco_ele_pfchhadisorel_puppi_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi_barrel_bkg",reco_ele_pfchhadisorel_puppi_barrel_bkg2);
  if (reco_ele_pfchhadisorel_puppi_barrel_bkg2 == 0) { cout << "reco_ele_pfchhadisorel_puppi_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi_barrel_bkg1, label1, reco_ele_pfchhadisorel_puppi_barrel_bkg2, label2, path, "data_reco_ele_pfchhadisorel_puppi_barrel_bkg", "top_right", true, false);


  //Ele PF Charged Hadron PUPPI Isolation EndCap
  TH1D *reco_ele_pfchhadiso_puppi_endcap1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi_endcap2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi_endcap",reco_ele_pfchhadiso_puppi_endcap1);
  if (reco_ele_pfchhadiso_puppi_endcap1 == 0) { cout << "reco_ele_pfchhadiso_puppi_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi_endcap",reco_ele_pfchhadiso_puppi_endcap2);
  if (reco_ele_pfchhadiso_puppi_endcap2 == 0) { cout << "reco_ele_pfchhadiso_puppi_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi_endcap1, label1, reco_ele_pfchhadiso_puppi_endcap2, label2, path, "data_reco_ele_pfchhadiso_puppi_endcap", "top_right", true, false);


  //Ele PF Charged Hadron PUPPI Isolation EndCap Signal
  TH1D *reco_ele_pfchhadiso_puppi_endcap_signal1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi_endcap_signal",reco_ele_pfchhadiso_puppi_endcap_signal1);
  if (reco_ele_pfchhadiso_puppi_endcap_signal1 == 0) { cout << "reco_ele_pfchhadiso_puppi_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi_endcap_signal",reco_ele_pfchhadiso_puppi_endcap_signal2);
  if (reco_ele_pfchhadiso_puppi_endcap_signal2 == 0) { cout << "reco_ele_pfchhadiso_puppi_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi_endcap_signal1, label1, reco_ele_pfchhadiso_puppi_endcap_signal2, label2, path, "data_reco_ele_pfchhadiso_puppi_endcap_signal", "top_right", true, false);


  //Ele PF Charged Hadron PUPPI Isolation EndCap Background
  TH1D *reco_ele_pfchhadiso_puppi_endcap_bkg1 = 0;
  TH1D *reco_ele_pfchhadiso_puppi_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppi_endcap_bkg",reco_ele_pfchhadiso_puppi_endcap_bkg1);
  if (reco_ele_pfchhadiso_puppi_endcap_bkg1 == 0) { cout << "reco_ele_pfchhadiso_puppi_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppi_endcap_bkg",reco_ele_pfchhadiso_puppi_endcap_bkg2);
  if (reco_ele_pfchhadiso_puppi_endcap_bkg2 == 0) { cout << "reco_ele_pfchhadiso_puppi_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppi_endcap_bkg1, label1, reco_ele_pfchhadiso_puppi_endcap_bkg2, label2, path, "data_reco_ele_pfchhadiso_puppi_endcap_bkg", "top_right", true, false);


  //Ele PF Charged Hadron PUPPI Relative Isolation EndCap
  TH1D *reco_ele_pfchhadisorel_puppi_endcap1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi_endcap2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi_endcap",reco_ele_pfchhadisorel_puppi_endcap1);
  if (reco_ele_pfchhadisorel_puppi_endcap1 == 0) { cout << "reco_ele_pfchhadisorel_puppi_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi_endcap",reco_ele_pfchhadisorel_puppi_endcap2);
  if (reco_ele_pfchhadisorel_puppi_endcap2 == 0) { cout << "reco_ele_pfchhadisorel_puppi_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi_endcap1, label1, reco_ele_pfchhadisorel_puppi_endcap2, label2, path, "data_reco_ele_pfchhadisorel_puppi_endcap", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Relative Isolation EndCap Signal
  TH1D *reco_ele_pfchhadisorel_puppi_endcap_signal1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi_endcap_signal",reco_ele_pfchhadisorel_puppi_endcap_signal1);
  if (reco_ele_pfchhadisorel_puppi_endcap_signal1 == 0) { cout << "reco_ele_pfchhadisorel_puppi_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi_endcap_signal",reco_ele_pfchhadisorel_puppi_endcap_signal2);
  if (reco_ele_pfchhadisorel_puppi_endcap_signal2 == 0) { cout << "reco_ele_pfchhadisorel_puppi_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi_endcap_signal1, label1, reco_ele_pfchhadisorel_puppi_endcap_signal2, label2, path, "data_reco_ele_pfchhadisorel_puppi_endcap_signal", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI Relative Isolation EndCap Background
  TH1D *reco_ele_pfchhadisorel_puppi_endcap_bkg1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppi_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppi_endcap_bkg",reco_ele_pfchhadisorel_puppi_endcap_bkg1);
  if (reco_ele_pfchhadisorel_puppi_endcap_bkg1 == 0) { cout << "reco_ele_pfchhadisorel_puppi_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppi_endcap_bkg",reco_ele_pfchhadisorel_puppi_endcap_bkg2);
  if (reco_ele_pfchhadisorel_puppi_endcap_bkg2 == 0) { cout << "reco_ele_pfchhadisorel_puppi_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppi_endcap_bkg1, label1, reco_ele_pfchhadisorel_puppi_endcap_bkg2, label2, path, "data_reco_ele_pfchhadisorel_puppi_endcap_bkg", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Isolation
  TH1D *reco_ele_pfnehadiso_puppi1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi",reco_ele_pfnehadiso_puppi1);
  if (reco_ele_pfnehadiso_puppi1 == 0) { cout << "reco_ele_pfnehadiso_puppi not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi",reco_ele_pfnehadiso_puppi2);
  if (reco_ele_pfnehadiso_puppi2 == 0) { cout << "reco_ele_pfnehadiso_puppi not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi1, label1, reco_ele_pfnehadiso_puppi2, label2, path, "data_reco_ele_pfnehadiso_puppi", "top_right", true, false);


  //Ele PF Neutral Hadron PUPPI Isolation Signal
  TH1D *reco_ele_pfnehadiso_puppi_signal1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi_signal",reco_ele_pfnehadiso_puppi_signal1);
  if (reco_ele_pfnehadiso_puppi_signal1 == 0) { cout << "reco_ele_pfnehadiso_puppi_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi_signal",reco_ele_pfnehadiso_puppi_signal2);
  if (reco_ele_pfnehadiso_puppi_signal2 == 0) { cout << "reco_ele_pfnehadiso_puppi_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi_signal1, label1, reco_ele_pfnehadiso_puppi_signal2, label2, path, "data_reco_ele_pfnehadiso_puppi_signal", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Isolation Background
  TH1D *reco_ele_pfnehadiso_puppi_bkg1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi_bkg",reco_ele_pfnehadiso_puppi_bkg1);
  if (reco_ele_pfnehadiso_puppi_bkg1 == 0) { cout << "reco_ele_pfnehadiso_puppi_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi_bkg",reco_ele_pfnehadiso_puppi_bkg2);
  if (reco_ele_pfnehadiso_puppi_bkg2 == 0) { cout << "reco_ele_pfnehadiso_puppi_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi_bkg1, label1, reco_ele_pfnehadiso_puppi_bkg2, label2, path, "data_reco_ele_pfnehadiso_puppi_bkg", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Relative Isolation
  TH1D *reco_ele_pfnehadisorel_puppi1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi",reco_ele_pfnehadisorel_puppi1);
  if (reco_ele_pfnehadisorel_puppi1 == 0) { cout << "reco_ele_pfnehadisorel_puppi not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi",reco_ele_pfnehadisorel_puppi2);
  if (reco_ele_pfnehadisorel_puppi2 == 0) { cout << "reco_ele_pfnehadisorel_puppi not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi1, label1, reco_ele_pfnehadisorel_puppi2, label2, path, "data_reco_ele_pfnehadisorel_puppi", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Relative Isolation Signal
  TH1D *reco_ele_pfnehadisorel_puppi_signal1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi_signal",reco_ele_pfnehadisorel_puppi_signal1);
  if (reco_ele_pfnehadisorel_puppi_signal1 == 0) { cout << "reco_ele_pfnehadisorel_puppi_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi_signal",reco_ele_pfnehadisorel_puppi_signal2);
  if (reco_ele_pfnehadisorel_puppi_signal2 == 0) { cout << "reco_ele_pfnehadisorel_puppi_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi_signal1, label1, reco_ele_pfnehadisorel_puppi_signal2, label2, path, "data_reco_ele_pfnehadisorel_puppi_signal", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Relative Isolation Background
  TH1D *reco_ele_pfnehadisorel_puppi_bkg1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi_bkg",reco_ele_pfnehadisorel_puppi_bkg1);
  if (reco_ele_pfnehadisorel_puppi_bkg1 == 0) { cout << "reco_ele_pfnehadisorel_puppi_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi_bkg",reco_ele_pfnehadisorel_puppi_bkg2);
  if (reco_ele_pfnehadisorel_puppi_bkg2 == 0) { cout << "reco_ele_pfnehadisorel_puppi_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi_bkg1, label1, reco_ele_pfnehadisorel_puppi_bkg2, label2, path, "data_reco_ele_pfnehadisorel_puppi_bkg", "top_right", true, false);


  //Ele PF Neutral Hadron PUPPI Isolation Barrel
  TH1D *reco_ele_pfnehadiso_puppi_barrel1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi_barrel2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi_barrel",reco_ele_pfnehadiso_puppi_barrel1);
  if (reco_ele_pfnehadiso_puppi_barrel1 == 0) { cout << "reco_ele_pfnehadiso_puppi_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi_barrel",reco_ele_pfnehadiso_puppi_barrel2);
  if (reco_ele_pfnehadiso_puppi_barrel2 == 0) { cout << "reco_ele_pfnehadiso_puppi_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi_barrel1, label1, reco_ele_pfnehadiso_puppi_barrel2, label2, path, "data_reco_ele_pfnehadiso_puppi_barrel", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Isolation Barrel Signal
  TH1D *reco_ele_pfnehadiso_puppi_barrel_signal1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi_barrel_signal",reco_ele_pfnehadiso_puppi_barrel_signal1);
  if (reco_ele_pfnehadiso_puppi_barrel_signal1 == 0) { cout << "reco_ele_pfnehadiso_puppi_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi_barrel_signal",reco_ele_pfnehadiso_puppi_barrel_signal2);
  if (reco_ele_pfnehadiso_puppi_barrel_signal2 == 0) { cout << "reco_ele_pfnehadiso_puppi_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi_barrel_signal1, label1, reco_ele_pfnehadiso_puppi_barrel_signal2, label2, path, "data_reco_ele_pfnehadiso_puppi_barrel_signal", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Isolation Barrel Background
  TH1D *reco_ele_pfnehadiso_puppi_barrel_bkg1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi_barrel_bkg",reco_ele_pfnehadiso_puppi_barrel_bkg1);
  if (reco_ele_pfnehadiso_puppi_barrel_bkg1 == 0) { cout << "reco_ele_pfnehadiso_puppi_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi_barrel_bkg",reco_ele_pfnehadiso_puppi_barrel_bkg2);
  if (reco_ele_pfnehadiso_puppi_barrel_bkg2 == 0) { cout << "reco_ele_pfnehadiso_puppi_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi_barrel_bkg1, label1, reco_ele_pfnehadiso_puppi_barrel_bkg2, label2, path, "data_reco_ele_pfnehadiso_puppi_barrel_bkg", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Relative Isolation Barrel
  TH1D *reco_ele_pfnehadisorel_puppi_barrel1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi_barrel2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi_barrel",reco_ele_pfnehadisorel_puppi_barrel1);
  if (reco_ele_pfnehadisorel_puppi_barrel1 == 0) { cout << "reco_ele_pfnehadisorel_puppi_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi_barrel",reco_ele_pfnehadisorel_puppi_barrel2);
  if (reco_ele_pfnehadisorel_puppi_barrel2 == 0) { cout << "reco_ele_pfnehadisorel_puppi_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi_barrel1, label1, reco_ele_pfnehadisorel_puppi_barrel2, label2, path, "data_reco_ele_pfnehadisorel_puppi_barrel", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Relative Isolation Barrel Signal
  TH1D *reco_ele_pfnehadisorel_puppi_barrel_signal1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi_barrel_signal",reco_ele_pfnehadisorel_puppi_barrel_signal1);
  if (reco_ele_pfnehadisorel_puppi_barrel_signal1 == 0) { cout << "reco_ele_pfnehadisorel_puppi_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi_barrel_signal",reco_ele_pfnehadisorel_puppi_barrel_signal2);
  if (reco_ele_pfnehadisorel_puppi_barrel_signal2 == 0) { cout << "reco_ele_pfnehadisorel_puppi_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi_barrel_signal1, label1, reco_ele_pfnehadisorel_puppi_barrel_signal2, label2, path, "data_reco_ele_pfnehadisorel_puppi_barrel_signal", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Relative Isolation Barrel Background
  TH1D *reco_ele_pfnehadisorel_puppi_barrel_bkg1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi_barrel_bkg",reco_ele_pfnehadisorel_puppi_barrel_bkg1);
  if (reco_ele_pfnehadisorel_puppi_barrel_bkg1 == 0) { cout << "reco_ele_pfnehadisorel_puppi_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi_barrel_bkg",reco_ele_pfnehadisorel_puppi_barrel_bkg2);
  if (reco_ele_pfnehadisorel_puppi_barrel_bkg2 == 0) { cout << "reco_ele_pfnehadisorel_puppi_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi_barrel_bkg1, label1, reco_ele_pfnehadisorel_puppi_barrel_bkg2, label2, path, "data_reco_ele_pfnehadisorel_puppi_barrel_bkg", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Isolation EndCap
  TH1D *reco_ele_pfnehadiso_puppi_endcap1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi_endcap2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi_endcap",reco_ele_pfnehadiso_puppi_endcap1);
  if (reco_ele_pfnehadiso_puppi_endcap1 == 0) { cout << "reco_ele_pfnehadiso_puppi_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi_endcap",reco_ele_pfnehadiso_puppi_endcap2);
  if (reco_ele_pfnehadiso_puppi_endcap2 == 0) { cout << "reco_ele_pfnehadiso_puppi_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi_endcap1, label1, reco_ele_pfnehadiso_puppi_endcap2, label2, path, "data_reco_ele_pfnehadiso_puppi_endcap", "top_right", true, false);


  //Ele PF Neutral Hadron PUPPI Isolation EndCap Signal
  TH1D *reco_ele_pfnehadiso_puppi_endcap_signal1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi_endcap_signal",reco_ele_pfnehadiso_puppi_endcap_signal1);
  if (reco_ele_pfnehadiso_puppi_endcap_signal1 == 0) { cout << "reco_ele_pfnehadiso_puppi_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi_endcap_signal",reco_ele_pfnehadiso_puppi_endcap_signal2);
  if (reco_ele_pfnehadiso_puppi_endcap_signal2 == 0) { cout << "reco_ele_pfnehadiso_puppi_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi_endcap_signal1, label1, reco_ele_pfnehadiso_puppi_endcap_signal2, label2, path, "data_reco_ele_pfnehadiso_puppi_endcap_signal", "top_right", true, false);

  //Ele PF Neutral Hadron PUPPI Isolation EndCap Background
  TH1D *reco_ele_pfnehadiso_puppi_endcap_bkg1 = 0;
  TH1D *reco_ele_pfnehadiso_puppi_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadiso_puppi_endcap_bkg",reco_ele_pfnehadiso_puppi_endcap_bkg1);
  if (reco_ele_pfnehadiso_puppi_endcap_bkg1 == 0) { cout << "reco_ele_pfnehadiso_puppi_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadiso_puppi_endcap_bkg",reco_ele_pfnehadiso_puppi_endcap_bkg2);
  if (reco_ele_pfnehadiso_puppi_endcap_bkg2 == 0) { cout << "reco_ele_pfnehadiso_puppi_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadiso_puppi_endcap_bkg1, label1, reco_ele_pfnehadiso_puppi_endcap_bkg2, label2, path, "data_reco_ele_pfnehadiso_puppi_endcap_bkg", "top_right", true, false);


  //Ele PF Neutral Hadron PUPPI Relative Isolation EndCap
  TH1D *reco_ele_pfnehadisorel_puppi_endcap1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi_endcap2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi_endcap",reco_ele_pfnehadisorel_puppi_endcap1);
  if (reco_ele_pfnehadisorel_puppi_endcap1 == 0) { cout << "reco_ele_pfnehadisorel_puppi_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi_endcap",reco_ele_pfnehadisorel_puppi_endcap2);
  if (reco_ele_pfnehadisorel_puppi_endcap2 == 0) { cout << "reco_ele_pfnehadisorel_puppi_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi_endcap1, label1, reco_ele_pfnehadisorel_puppi_endcap2, label2, path, "data_reco_ele_pfnehadisorel_puppi_endcap", "top_right", true, false);


  //Ele PF Neutral Hadron PUPPI Relative Isolation EndCap Signal
  TH1D *reco_ele_pfnehadisorel_puppi_endcap_signal1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi_endcap_signal",reco_ele_pfnehadisorel_puppi_endcap_signal1);
  if (reco_ele_pfnehadisorel_puppi_endcap_signal1 == 0) { cout << "reco_ele_pfnehadisorel_puppi_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi_endcap_signal",reco_ele_pfnehadisorel_puppi_endcap_signal2);
  if (reco_ele_pfnehadisorel_puppi_endcap_signal2 == 0) { cout << "reco_ele_pfnehadisorel_puppi_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi_endcap_signal1, label1, reco_ele_pfnehadisorel_puppi_endcap_signal2, label2, path, "data_reco_ele_pfnehadisorel_puppi_endcap_signal", "top_right", true, false);


  //Ele PF Neutral Hadron PUPPI Relative Isolation EndCap Background
  TH1D *reco_ele_pfnehadisorel_puppi_endcap_bkg1 = 0;
  TH1D *reco_ele_pfnehadisorel_puppi_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfnehadisorel_puppi_endcap_bkg",reco_ele_pfnehadisorel_puppi_endcap_bkg1);
  if (reco_ele_pfnehadisorel_puppi_endcap_bkg1 == 0) { cout << "reco_ele_pfnehadisorel_puppi_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfnehadisorel_puppi_endcap_bkg",reco_ele_pfnehadisorel_puppi_endcap_bkg2);
  if (reco_ele_pfnehadisorel_puppi_endcap_bkg2 == 0) { cout << "reco_ele_pfnehadisorel_puppi_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfnehadisorel_puppi_endcap_bkg1, label1, reco_ele_pfnehadisorel_puppi_endcap_bkg2, label2, path, "data_reco_ele_pfnehadisorel_puppi_endcap_bkg", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation
  TH1D *reco_ele_pfphotoniso_puppi1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi",reco_ele_pfphotoniso_puppi1);
  if (reco_ele_pfphotoniso_puppi1 == 0) { cout << "reco_ele_pfphotoniso_puppi not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi",reco_ele_pfphotoniso_puppi2);
  if (reco_ele_pfphotoniso_puppi2 == 0) { cout << "reco_ele_pfphotoniso_puppi not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi1, label1, reco_ele_pfphotoniso_puppi2, label2, path, "data_reco_ele_pfphotoniso_puppi", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation Signal
  TH1D *reco_ele_pfphotoniso_puppi_signal1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi_signal2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi_signal",reco_ele_pfphotoniso_puppi_signal1);
  if (reco_ele_pfphotoniso_puppi_signal1 == 0) { cout << "reco_ele_pfphotoniso_puppi_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi_signal",reco_ele_pfphotoniso_puppi_signal2);
  if (reco_ele_pfphotoniso_puppi_signal2 == 0) { cout << "reco_ele_pfphotoniso_puppi_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi_signal1, label1, reco_ele_pfphotoniso_puppi_signal2, label2, path, "data_reco_ele_pfphotoniso_puppi_signal", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation Background
  TH1D *reco_ele_pfphotoniso_puppi_bkg1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi_bkg",reco_ele_pfphotoniso_puppi_bkg1);
  if (reco_ele_pfphotoniso_puppi_bkg1 == 0) { cout << "reco_ele_pfphotoniso_puppi_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi_bkg",reco_ele_pfphotoniso_puppi_bkg2);
  if (reco_ele_pfphotoniso_puppi_bkg2 == 0) { cout << "reco_ele_pfphotoniso_puppi_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi_bkg1, label1, reco_ele_pfphotoniso_puppi_bkg2, label2, path, "data_reco_ele_pfphotoniso_puppi_bkg", "top_right", true, false);

  //Ele PF Photon PUPPI Relative Isolation
  TH1D *reco_ele_pfphotonisorel_puppi1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi",reco_ele_pfphotonisorel_puppi1);
  if (reco_ele_pfphotonisorel_puppi1 == 0) { cout << "reco_ele_pfphotonisorel_puppi not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi",reco_ele_pfphotonisorel_puppi2);
  if (reco_ele_pfphotonisorel_puppi2 == 0) { cout << "reco_ele_pfphotonisorel_puppi not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi1, label1, reco_ele_pfphotonisorel_puppi2, label2, path, "data_reco_ele_pfphotonisorel_puppi", "top_right", true, false);

  //Ele PF Photon PUPPI Relative Isolation Signal
  TH1D *reco_ele_pfphotonisorel_puppi_signal1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi_signal2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi_signal",reco_ele_pfphotonisorel_puppi_signal1);
  if (reco_ele_pfphotonisorel_puppi_signal1 == 0) { cout << "reco_ele_pfphotonisorel_puppi_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi_signal",reco_ele_pfphotonisorel_puppi_signal2);
  if (reco_ele_pfphotonisorel_puppi_signal2 == 0) { cout << "reco_ele_pfphotonisorel_puppi_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi_signal1, label1, reco_ele_pfphotonisorel_puppi_signal2, label2, path, "data_reco_ele_pfphotonisorel_puppi_signal", "top_right", true, false);

  //Ele PF Photon PUPPI Relative Isolation Background
  TH1D *reco_ele_pfphotonisorel_puppi_bkg1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi_bkg",reco_ele_pfphotonisorel_puppi_bkg1);
  if (reco_ele_pfphotonisorel_puppi_bkg1 == 0) { cout << "reco_ele_pfphotonisorel_puppi_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi_bkg",reco_ele_pfphotonisorel_puppi_bkg2);
  if (reco_ele_pfphotonisorel_puppi_bkg2 == 0) { cout << "reco_ele_pfphotonisorel_puppi_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi_bkg1, label1, reco_ele_pfphotonisorel_puppi_bkg2, label2, path, "data_reco_ele_pfphotonisorel_puppi_bkg", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation Barrel
  TH1D *reco_ele_pfphotoniso_puppi_barrel1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi_barrel2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi_barrel",reco_ele_pfphotoniso_puppi_barrel1);
  if (reco_ele_pfphotoniso_puppi_barrel1 == 0) { cout << "reco_ele_pfphotoniso_puppi_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi_barrel",reco_ele_pfphotoniso_puppi_barrel2);
  if (reco_ele_pfphotoniso_puppi_barrel2 == 0) { cout << "reco_ele_pfphotoniso_puppi_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi_barrel1, label1, reco_ele_pfphotoniso_puppi_barrel2, label2, path, "data_reco_ele_pfphotoniso_puppi_barrel", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation Barrel Signal
  TH1D *reco_ele_pfphotoniso_puppi_barrel_signal1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi_barrel_signal",reco_ele_pfphotoniso_puppi_barrel_signal1);
  if (reco_ele_pfphotoniso_puppi_barrel_signal1 == 0) { cout << "reco_ele_pfphotoniso_puppi_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi_barrel_signal",reco_ele_pfphotoniso_puppi_barrel_signal2);
  if (reco_ele_pfphotoniso_puppi_barrel_signal2 == 0) { cout << "reco_ele_pfphotoniso_puppi_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi_barrel_signal1, label1, reco_ele_pfphotoniso_puppi_barrel_signal2, label2, path, "data_reco_ele_pfphotoniso_puppi_barrel_signal", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation Barrel Background
  TH1D *reco_ele_pfphotoniso_puppi_barrel_bkg1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi_barrel_bkg",reco_ele_pfphotoniso_puppi_barrel_bkg1);
  if (reco_ele_pfphotoniso_puppi_barrel_bkg1 == 0) { cout << "reco_ele_pfphotoniso_puppi_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi_barrel_bkg",reco_ele_pfphotoniso_puppi_barrel_bkg2);
  if (reco_ele_pfphotoniso_puppi_barrel_bkg2 == 0) { cout << "reco_ele_pfphotoniso_puppi_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi_barrel_bkg1, label1, reco_ele_pfphotoniso_puppi_barrel_bkg2, label2, path, "data_reco_ele_pfphotoniso_puppi_barrel_bkg", "top_right", true, false);

  //Ele PF Photon PUPPI Relative Isolation Barrel
  TH1D *reco_ele_pfphotonisorel_puppi_barrel1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi_barrel2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi_barrel",reco_ele_pfphotonisorel_puppi_barrel1);
  if (reco_ele_pfphotonisorel_puppi_barrel1 == 0) { cout << "reco_ele_pfphotonisorel_puppi_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi_barrel",reco_ele_pfphotonisorel_puppi_barrel2);
  if (reco_ele_pfphotonisorel_puppi_barrel2 == 0) { cout << "reco_ele_pfphotonisorel_puppi_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi_barrel1, label1, reco_ele_pfphotonisorel_puppi_barrel2, label2, path, "data_reco_ele_pfphotonisorel_puppi_barrel", "top_right", true, false);

  //Ele PF Photon PUPPI Relative Isolation Barrel Signal
  TH1D *reco_ele_pfphotonisorel_puppi_barrel_signal1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi_barrel_signal2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi_barrel_signal",reco_ele_pfphotonisorel_puppi_barrel_signal1);
  if (reco_ele_pfphotonisorel_puppi_barrel_signal1 == 0) { cout << "reco_ele_pfphotonisorel_puppi_barrel_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi_barrel_signal",reco_ele_pfphotonisorel_puppi_barrel_signal2);
  if (reco_ele_pfphotonisorel_puppi_barrel_signal2 == 0) { cout << "reco_ele_pfphotonisorel_puppi_barrel_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi_barrel_signal1, label1, reco_ele_pfphotonisorel_puppi_barrel_signal2, label2, path, "data_reco_ele_pfphotonisorel_puppi_barrel_signal", "top_right", true, false);

  //Ele PF Photon PUPPI Relative Isolation Barrel Background
  TH1D *reco_ele_pfphotonisorel_puppi_barrel_bkg1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi_barrel_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi_barrel_bkg",reco_ele_pfphotonisorel_puppi_barrel_bkg1);
  if (reco_ele_pfphotonisorel_puppi_barrel_bkg1 == 0) { cout << "reco_ele_pfphotonisorel_puppi_barrel_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi_barrel_bkg",reco_ele_pfphotonisorel_puppi_barrel_bkg2);
  if (reco_ele_pfphotonisorel_puppi_barrel_bkg2 == 0) { cout << "reco_ele_pfphotonisorel_puppi_barrel_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi_barrel_bkg1, label1, reco_ele_pfphotonisorel_puppi_barrel_bkg2, label2, path, "data_reco_ele_pfphotonisorel_puppi_barrel_bkg", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation EndCap
  TH1D *reco_ele_pfphotoniso_puppi_endcap1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi_endcap2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi_endcap",reco_ele_pfphotoniso_puppi_endcap1);
  if (reco_ele_pfphotoniso_puppi_endcap1 == 0) { cout << "reco_ele_pfphotoniso_puppi_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi_endcap",reco_ele_pfphotoniso_puppi_endcap2);
  if (reco_ele_pfphotoniso_puppi_endcap2 == 0) { cout << "reco_ele_pfphotoniso_puppi_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi_endcap1, label1, reco_ele_pfphotoniso_puppi_endcap2, label2, path, "data_reco_ele_pfphotoniso_puppi_endcap", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation EndCap Signal
  TH1D *reco_ele_pfphotoniso_puppi_endcap_signal1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi_endcap_signal",reco_ele_pfphotoniso_puppi_endcap_signal1);
  if (reco_ele_pfphotoniso_puppi_endcap_signal1 == 0) { cout << "reco_ele_pfphotoniso_puppi_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi_endcap_signal",reco_ele_pfphotoniso_puppi_endcap_signal2);
  if (reco_ele_pfphotoniso_puppi_endcap_signal2 == 0) { cout << "reco_ele_pfphotoniso_puppi_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi_endcap_signal1, label1, reco_ele_pfphotoniso_puppi_endcap_signal2, label2, path, "data_reco_ele_pfphotoniso_puppi_endcap_signal", "top_right", true, false);

  //Ele PF Photon PUPPI Isolation EndCap Background
  TH1D *reco_ele_pfphotoniso_puppi_endcap_bkg1 = 0;
  TH1D *reco_ele_pfphotoniso_puppi_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotoniso_puppi_endcap_bkg",reco_ele_pfphotoniso_puppi_endcap_bkg1);
  if (reco_ele_pfphotoniso_puppi_endcap_bkg1 == 0) { cout << "reco_ele_pfphotoniso_puppi_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotoniso_puppi_endcap_bkg",reco_ele_pfphotoniso_puppi_endcap_bkg2);
  if (reco_ele_pfphotoniso_puppi_endcap_bkg2 == 0) { cout << "reco_ele_pfphotoniso_puppi_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotoniso_puppi_endcap_bkg1, label1, reco_ele_pfphotoniso_puppi_endcap_bkg2, label2, path, "data_reco_ele_pfphotoniso_puppi_endcap_bkg", "top_right", true, false);

  //Ele PF Photon PUPPI Relative Isolation EndCap
  TH1D *reco_ele_pfphotonisorel_puppi_endcap1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi_endcap2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi_endcap",reco_ele_pfphotonisorel_puppi_endcap1);
  if (reco_ele_pfphotonisorel_puppi_endcap1 == 0) { cout << "reco_ele_pfphotonisorel_puppi_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi_endcap",reco_ele_pfphotonisorel_puppi_endcap2);
  if (reco_ele_pfphotonisorel_puppi_endcap2 == 0) { cout << "reco_ele_pfphotonisorel_puppi_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi_endcap1, label1, reco_ele_pfphotonisorel_puppi_endcap2, label2, path, "data_reco_ele_pfphotonisorel_puppi_endcap", "top_right", true, false);

  //Ele PF Photon PUPPI Relative Isolation EndCap Signal
  TH1D *reco_ele_pfphotonisorel_puppi_endcap_signal1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi_endcap_signal2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi_endcap_signal",reco_ele_pfphotonisorel_puppi_endcap_signal1);
  if (reco_ele_pfphotonisorel_puppi_endcap_signal1 == 0) { cout << "reco_ele_pfphotonisorel_puppi_endcap_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi_endcap_signal",reco_ele_pfphotonisorel_puppi_endcap_signal2);
  if (reco_ele_pfphotonisorel_puppi_endcap_signal2 == 0) { cout << "reco_ele_pfphotonisorel_puppi_endcap_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi_endcap_signal1, label1, reco_ele_pfphotonisorel_puppi_endcap_signal2, label2, path, "data_reco_ele_pfphotonisorel_puppi_endcap_signal", "top_right", true, false);


  //Ele PF Photon PUPPI Relative Isolation EndCap Background
  TH1D *reco_ele_pfphotonisorel_puppi_endcap_bkg1 = 0;
  TH1D *reco_ele_pfphotonisorel_puppi_endcap_bkg2 = 0;

  f1->GetObject("reco_ele_pfphotonisorel_puppi_endcap_bkg",reco_ele_pfphotonisorel_puppi_endcap_bkg1);
  if (reco_ele_pfphotonisorel_puppi_endcap_bkg1 == 0) { cout << "reco_ele_pfphotonisorel_puppi_endcap_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfphotonisorel_puppi_endcap_bkg",reco_ele_pfphotonisorel_puppi_endcap_bkg2);
  if (reco_ele_pfphotonisorel_puppi_endcap_bkg2 == 0) { cout << "reco_ele_pfphotonisorel_puppi_endcap_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfphotonisorel_puppi_endcap_bkg1, label1, reco_ele_pfphotonisorel_puppi_endcap_bkg2, label2, path, "data_reco_ele_pfphotonisorel_puppi_endcap_bkg", "top_right", true, false);


  //Ele PF Charged Hadron PUPPI No Leptons Isolation
  TH1D *reco_ele_pfchhadiso_puppinl1 = 0;
  TH1D *reco_ele_pfchhadiso_puppinl2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppinl",reco_ele_pfchhadiso_puppinl1);
  if (reco_ele_pfchhadiso_puppinl1 == 0) { cout << "reco_ele_pfchhadiso_puppinl not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppinl",reco_ele_pfchhadiso_puppinl2);
  if (reco_ele_pfchhadiso_puppinl2 == 0) { cout << "reco_ele_pfchhadiso_puppinl not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppinl1, label1, reco_ele_pfchhadiso_puppinl2, label2, path, "data_reco_ele_pfchhadiso_puppinl", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI No Leptons Isolation Signal
  TH1D *reco_ele_pfchhadiso_puppinl_signal1 = 0;
  TH1D *reco_ele_pfchhadiso_puppinl_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppinl_signal",reco_ele_pfchhadiso_puppinl_signal1);
  if (reco_ele_pfchhadiso_puppinl_signal1 == 0) { cout << "reco_ele_pfchhadiso_puppinl_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppinl_signal",reco_ele_pfchhadiso_puppinl_signal2);
  if (reco_ele_pfchhadiso_puppinl_signal2 == 0) { cout << "reco_ele_pfchhadiso_puppinl_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppinl_signal1, label1, reco_ele_pfchhadiso_puppinl_signal2, label2, path, "data_reco_ele_pfchhadiso_puppinl_signal", "top_right", true, false);


  //Ele PF Charged Hadron PUPPI No Leptons Isolation Background
  TH1D *reco_ele_pfchhadiso_puppinl_bkg1 = 0;
  TH1D *reco_ele_pfchhadiso_puppinl_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadiso_puppinl_bkg",reco_ele_pfchhadiso_puppinl_bkg1);
  if (reco_ele_pfchhadiso_puppinl_bkg1 == 0) { cout << "reco_ele_pfchhadiso_puppinl_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadiso_puppinl_bkg",reco_ele_pfchhadiso_puppinl_bkg2);
  if (reco_ele_pfchhadiso_puppinl_bkg2 == 0) { cout << "reco_ele_pfchhadiso_puppinl_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppinl_bkg1, label1, reco_ele_pfchhadiso_puppinl_bkg2, label2, path, "data_reco_ele_pfchhadiso_puppinl_bkg", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI No Leptons Relative Isolation
  TH1D *reco_ele_pfchhadisorel_puppinl1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppinl2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppinl",reco_ele_pfchhadisorel_puppinl1);
  if (reco_ele_pfchhadisorel_puppinl1 == 0) { cout << "reco_ele_pfchhadisorel_puppinl not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppinl",reco_ele_pfchhadisorel_puppinl2);
  if (reco_ele_pfchhadisorel_puppinl2 == 0) { cout << "reco_ele_pfchhadisorel_puppinl not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppinl1, label1, reco_ele_pfchhadisorel_puppinl2, label2, path, "data_reco_ele_pfchhadisorel_puppinl", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI No Leptons Relative Isolation Signal
  TH1D *reco_ele_pfchhadisorel_puppinl_signal1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppinl_signal2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppinl_signal",reco_ele_pfchhadisorel_puppinl_signal1);
  if (reco_ele_pfchhadisorel_puppinl_signal1 == 0) { cout << "reco_ele_pfchhadisorel_puppinl_signal not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppinl_signal",reco_ele_pfchhadisorel_puppinl_signal2);
  if (reco_ele_pfchhadisorel_puppinl_signal2 == 0) { cout << "reco_ele_pfchhadisorel_puppinl_signal not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadiso_puppinl_signal1, label1, reco_ele_pfchhadiso_puppinl_signal2, label2, path, "data_reco_ele_pfchhadiso_puppinl_signal", "top_right", true, false);

  //Ele PF Charged Hadron PUPPI No Leptons Relative Isolation Background
  TH1D *reco_ele_pfchhadisorel_puppinl_bkg1 = 0;
  TH1D *reco_ele_pfchhadisorel_puppinl_bkg2 = 0;

  f1->GetObject("reco_ele_pfchhadisorel_puppinl_bkg",reco_ele_pfchhadisorel_puppinl_bkg1);
  if (reco_ele_pfchhadisorel_puppinl_bkg1 == 0) { cout << "reco_ele_pfchhadisorel_puppinl_bkg not found!" << endl; return; }
  f2->GetObject("reco_ele_pfchhadisorel_puppinl_bkg",reco_ele_pfchhadisorel_puppinl_bkg2);
  if (reco_ele_pfchhadisorel_puppinl_bkg2 == 0) { cout << "reco_ele_pfchhadisorel_puppinl_bkg not found!" << endl; return; }

plot_2histograms(reco_ele_pfchhadisorel_puppinl_bkg1, label1, reco_ele_pfchhadisorel_puppinl_bkg2, label2, path, "data_reco_ele_pfchhadisorel_puppinl_bkg", "top_right", true, false);

  std::cout << "-------------------------------------" << endl;
  std::cout << "Execution ended!" << endl;
  std::cout << "-------------------------------------" << endl;
  std::cout << " " << endl;
  std::cout << " " << endl;

}
