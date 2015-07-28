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



  std::cout << "-------------------------------------" << endl;
  std::cout << "Execution ended!" << endl;
  std::cout << "-------------------------------------" << endl;
  std::cout << " " << endl;

}
