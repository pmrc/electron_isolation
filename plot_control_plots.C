// Pedro Cipriano, May 2015
// FESB - Split, CMS
// Last Update: 08 June 2015
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

void plot_control_plots()
{
  gROOT -> Reset();
  gROOT->SetStyle("Plain");

  std::cout << "Plot Electron Isolation" << endl;
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
  string outfile1 = "output/GluGluToH_Background.root";
  string outfile2 = "output/GluGluToH.root";

  // sets labels for the plots
  TString label1 = "Background";
  TString label2 = "GluGluToH";

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

plot_2histograms(vertex_multiplicity1, label1, vertex_multiplicity2, label2, path, "vertex_multiplicity", "top_right", true, false);

  //Reconstructed Pile-Up
  TH1D *reco_pu1 = 0;
  TH1D *reco_pu2 = 0;

  f1->GetObject("reco_pu",reco_pu1);
  if (reco_pu1 == 0) { cout << "reco_pu not found!" << endl; return; }
  f2->GetObject("reco_pu",reco_pu2);
  if (reco_pu2 == 0) { cout << "reco_pu not found!" << endl; return; }

plot_2histograms(reco_pu1, label1, reco_pu2, label2, path, "reco_pu", "top_right", true, false);

  //Generated Pile-Up
  TH1D *gen_pu1 = 0;
  TH1D *gen_pu2 = 0;

  f1->GetObject("gen_pu", gen_pu1);
  if (gen_pu1 == 0) { cout << "gen_pu not found!" << endl; return; }
  f2->GetObject("gen_pu", gen_pu2);
  if (gen_pu2 == 0) { cout << "gen_pu not found!" << endl; return; }

plot_2histograms(gen_pu1, label1, gen_pu2, label2, path, "gen_pu", "top_right", true, false);


  //Reco Electron rho
  TH1D *evt_rho1 = 0;
  TH1D *evt_rho2 = 0;

  f1->GetObject("evt_rho", evt_rho1);
  if (evt_rho1 == 0) { cout << "evt_rho not found!" << endl; return; }
  f2->GetObject("evt_rho", evt_rho2);
  if (evt_rho2 == 0) { cout << "evt_rho not found!" << endl; return; }

plot_2histograms(evt_rho1, label1, evt_rho2, label2, path, "evt_rho", "top_right", true, false);

  //Gen Electron Multiplicity
  TH1D *gen_ele_multiplicity1 = 0;
  TH1D *gen_ele_multiplicity2 = 0;

  f1->GetObject("gen_ele_multiplicity",gen_ele_multiplicity1);
  if (gen_ele_multiplicity1 == 0) { cout << "gen_ele_multiplicity not found!" << endl; return; }
  f2->GetObject("gen_ele_multiplicity",gen_ele_multiplicity2);
  if (gen_ele_multiplicity2 == 0) { cout << "gen_ele_multiplicity not found!" << endl; return; }

plot_2histograms(gen_ele_multiplicity1, label1, gen_ele_multiplicity2, label2, path, "gen_ele_multiplicity", "top_right", false, false);

  //Gen Electron Multiplicity After Matching
  TH1D *gen_ele_multiplicity_am1 = 0;
  TH1D *gen_ele_multiplicity_am2 = 0;

  f1->GetObject("gen_ele_multiplicity_am",gen_ele_multiplicity_am1);
  if (gen_ele_multiplicity_am1 == 0) { cout << "gen_ele_multiplicity_am on " << outfile1 << " not found!" << endl; return; }
  f2->GetObject("gen_ele_multiplicity_am",gen_ele_multiplicity_am2);
  if (gen_ele_multiplicity_am2 == 0) { cout << "gen_ele_multiplicity_am not found!" << endl; return; }

plot_2histograms(gen_ele_multiplicity_am1, label1, gen_ele_multiplicity_am2, label2, path, "gen_ele_multiplicity_am", "top_right", false, false);

  //Gen Electron Multiplicity Matched
  TH1D *gen_ele_multiplicity_matched1 = 0;
  TH1D *gen_ele_multiplicity_matched2 = 0;

  f1->GetObject("gen_ele_multiplicity_matched",gen_ele_multiplicity_matched1);
  if (gen_ele_multiplicity_matched1 == 0) { cout << "gen_ele_multiplicity_matched on " << outfile1 << " not found!" << endl; return; }
  f2->GetObject("gen_ele_multiplicity_matched",gen_ele_multiplicity_matched2);
  if (gen_ele_multiplicity_matched2 == 0) { cout << "gen_ele_multiplicity_matched not found!" << endl; return; }

plot_2histograms(gen_ele_multiplicity_matched1, label1, gen_ele_multiplicity_matched2, label2, path, "gen_ele_multiplicity_matched", "top_right", false, false);

  //Gen Electron Multiplicity Separated
  TH1D *gen_ele_multiplicity_separated1 = 0;
  TH1D *gen_ele_multiplicity_separated2 = 0;

  f1->GetObject("gen_ele_multiplicity_separated",gen_ele_multiplicity_separated1);
  if (gen_ele_multiplicity_separated1 == 0) { cout << "gen_ele_multiplicity_separated on " << outfile1 << " not found!" << endl; return; }
  f2->GetObject("gen_ele_multiplicity_separated",gen_ele_multiplicity_separated2);
  if (gen_ele_multiplicity_separated2 == 0) { cout << "gen_ele_multiplicity_separated not found!" << endl; return; }

plot_2histograms(gen_ele_multiplicity_separated1, label1, gen_ele_multiplicity_separated2, label2, path, "gen_ele_multiplicity_separated", "top_right", false, false);

  //Gen Electron pT
  TH1D *gen_ele_pt1 = 0;
  TH1D *gen_ele_pt2 = 0;

  f1->GetObject("gen_ele_pt",gen_ele_pt1);
  if (gen_ele_pt1 == 0) { cout << "gen_ele_pt not found!" << endl; return; }
  f2->GetObject("gen_ele_pt",gen_ele_pt2);
  if (gen_ele_pt2 == 0) { cout << "gen_ele_pt not found!" << endl; return; }

plot_2histograms(gen_ele_pt1, label1, gen_ele_pt2, label2, path, "gen_ele_pt", "top_right", true, false);

  //Gen Electron Eta
  TH1D *gen_ele_eta1 = 0;
  TH1D *gen_ele_eta2 = 0;

  f1->GetObject("gen_ele_eta",gen_ele_eta1);
  if (gen_ele_eta1 == 0) { cout << "gen_ele_eta not found!" << endl; return; }
  f2->GetObject("gen_ele_eta",gen_ele_eta2);
  if (gen_ele_eta2 == 0) { cout << "gen_ele_eta not found!" << endl; return; }

plot_2histograms(gen_ele_eta1, label1, gen_ele_eta2, label2, path, "gen_ele_eta", "bottom_middle", true, false);

  //Gen Electron Phi
  TH1D *gen_ele_phi1 = 0;
  TH1D *gen_ele_phi2 = 0;

  f1->GetObject("gen_ele_phi",gen_ele_phi1);
  if (gen_ele_phi1 == 0) { cout << "gen_ele_phi not found!" << endl; return; }
  f2->GetObject("gen_ele_phi",gen_ele_phi2);
  if (gen_ele_phi2 == 0) { cout << "gen_ele_phi not found!" << endl; return; }

plot_2histograms(gen_ele_phi1, label1, gen_ele_phi2, label2, path, "gen_ele_phi", "bottom_right", true, false);

  //Leading Gen Electron pT
  TH1D *leading_gen_ele_pt1 = 0;
  TH1D *leading_gen_ele_pt2 = 0;

  f1->GetObject("leading_gen_ele_pt",leading_gen_ele_pt1);
  if (leading_gen_ele_pt1 == 0) { cout << "leading_gen_ele_pt not found!" << endl; return; }
  f2->GetObject("leading_gen_ele_pt",leading_gen_ele_pt2);
  if (gen_ele_pt2 == 0) { cout << "gen_ele_pt not found!" << endl; return; }

plot_2histograms(leading_gen_ele_pt1, label1, leading_gen_ele_pt2, label2, path, "leading_gen_ele_pt", "top_right", true, false);

  //Leading Gen Electron Eta
  TH1D *leading_gen_ele_eta1 = 0;
  TH1D *leading_gen_ele_eta2 = 0;

  f1->GetObject("leading_gen_ele_eta",leading_gen_ele_eta1);
  if (leading_gen_ele_eta1 == 0) { cout << "leading_gen_ele_eta not found!" << endl; return; }
  f2->GetObject("leading_gen_ele_eta",leading_gen_ele_eta2);
  if (leading_gen_ele_eta2 == 0) { cout << "leading_gen_ele_eta not found!" << endl; return; }

plot_2histograms(leading_gen_ele_eta1, label1, leading_gen_ele_eta2, label2, path, "leading_gen_ele_eta", "bottom_middle", true, false);

  //Leading Gen Electron Phi
  TH1D *leading_gen_ele_phi1 = 0;
  TH1D *leading_gen_ele_phi2 = 0;

  f1->GetObject("leading_gen_ele_phi",leading_gen_ele_phi1);
  if (leading_gen_ele_phi1 == 0) { cout << "leading_gen_ele_phi not found!" << endl; return; }
  f2->GetObject("leading_gen_ele_phi",leading_gen_ele_phi2);
  if (leading_gen_ele_phi2 == 0) { cout << "leading_gen_ele_phi not found!" << endl; return; }

plot_2histograms(leading_gen_ele_phi1, label1, leading_gen_ele_phi2, label2, path, "leading_gen_ele_phi", "bottom_right", true, false);

  //Reco Electron Multiplicity
  TH1D *reco_ele_multiplicity1 = 0;
  TH1D *reco_ele_multiplicity2 = 0;

  f1->GetObject("reco_ele_multiplicity",reco_ele_multiplicity1);
  if (reco_ele_multiplicity1 == 0) { cout << "reco_ele_multiplicity not found!" << endl; return; }
  f2->GetObject("reco_ele_multiplicity",reco_ele_multiplicity2);
  if (reco_ele_multiplicity2 == 0) { cout << "reco_ele_multiplicity not found!" << endl; return; }

plot_2histograms(reco_ele_multiplicity1, label1, reco_ele_multiplicity2, label2, path, "reco_ele_multiplicity", "top_right", false, false);

  //Reco Electron Multiplicity After Matching
  TH1D *reco_ele_multiplicity_am1 = 0;
  TH1D *reco_ele_multiplicity_am2 = 0;

  f1->GetObject("reco_ele_multiplicity_am",reco_ele_multiplicity_am1);
  if (reco_ele_multiplicity_am1 == 0) { cout << "reco_ele_multiplicity_am on " << outfile1 << " not found!" << endl; return; }
  f2->GetObject("reco_ele_multiplicity_am",reco_ele_multiplicity_am2);
  if (reco_ele_multiplicity_am2 == 0) { cout << "reco_ele_multiplicity_am not found!" << endl; return; }

plot_2histograms(reco_ele_multiplicity_am1, label1, reco_ele_multiplicity_am2, label2, path, "reco_ele_multiplicity_am", "top_right", false, false);


  //Reco Electron Multiplicity Matched
  TH1D *reco_ele_multiplicity_matched1 = 0;
  TH1D *reco_ele_multiplicity_matched2 = 0;

  f1->GetObject("reco_ele_multiplicity_matched",reco_ele_multiplicity_matched1);
  if (reco_ele_multiplicity_matched1 == 0) { cout << "reco_ele_multiplicity_matched on " << outfile1 << " not found!" << endl; return; }
  f2->GetObject("reco_ele_multiplicity_matched",reco_ele_multiplicity_matched2);
  if (reco_ele_multiplicity_matched2 == 0) { cout << "reco_ele_multiplicity_matched not found!" << endl; return; }

plot_2histograms(reco_ele_multiplicity_matched1, label1, reco_ele_multiplicity_matched2, label2, path, "reco_ele_multiplicity_matched", "top_right", false, false);

  //Reco Electron Multiplicity Separated
  TH1D *reco_ele_multiplicity_separated1 = 0;
  TH1D *reco_ele_multiplicity_separated2 = 0;

  f1->GetObject("reco_ele_multiplicity_separated",reco_ele_multiplicity_separated1);
  if (reco_ele_multiplicity_separated1 == 0) { cout << "reco_ele_multiplicity_separated on " << outfile1 << " not found!" << endl; return; }
  f2->GetObject("reco_ele_multiplicity_separated",reco_ele_multiplicity_separated2);
  if (reco_ele_multiplicity_separated2 == 0) { cout << "reco_ele_multiplicity_separated not found!" << endl; return; }

plot_2histograms(reco_ele_multiplicity_separated1, label1, reco_ele_multiplicity_separated2, label2, path, "reco_ele_multiplicity_separated", "top_right", false, false);

  //Reco Electron pT
  TH1D *reco_ele_pt1 = 0;
  TH1D *reco_ele_pt2 = 0;

  f1->GetObject("reco_ele_pt",reco_ele_pt1);
  if (reco_ele_pt1 == 0) { cout << "reco_ele_pt not found!" << endl; return; }
  f2->GetObject("reco_ele_pt",reco_ele_pt2);
  if (reco_ele_pt2 == 0) { cout << "reco_ele_pt not found!" << endl; return; }

plot_2histograms(reco_ele_pt1, label1, reco_ele_pt2, label2, path, "reco_ele_pt", "top_right", true, false);

  //Reco Electron Eta
  TH1D *reco_ele_eta1 = 0;
  TH1D *reco_ele_eta2 = 0;

  f1->GetObject("reco_ele_eta",reco_ele_eta1);
  if (reco_ele_eta1 == 0) { cout << "reco_ele_eta not found!" << endl; return; }
  f2->GetObject("reco_ele_eta",reco_ele_eta2);
  if (reco_ele_eta2 == 0) { cout << "reco_ele_eta not found!" << endl; return; }

plot_2histograms(reco_ele_eta1, label1, reco_ele_eta2, label2, path, "reco_ele_eta", "bottom_middle", true, false);

  //Reco Electron Phi
  TH1D *reco_ele_phi1 = 0;
  TH1D *reco_ele_phi2 = 0;

  f1->GetObject("reco_ele_phi",reco_ele_phi1);
  if (reco_ele_phi1 == 0) { cout << "reco_ele_phi not found!" << endl; return; }
  f2->GetObject("reco_ele_phi",reco_ele_phi2);
  if (reco_ele_phi2 == 0) { cout << "reco_ele_phi not found!" << endl; return; }

plot_2histograms(reco_ele_phi1, label1, reco_ele_phi2, label2, path, "reco_ele_phi", "bottom_right", true, false);

  //Reco Electron Effective Area
  TH1D *reco_ele_effarea1 = 0;
  TH1D *reco_ele_effarea2 = 0;

  f1->GetObject("reco_ele_effarea",reco_ele_effarea1);
  if (reco_ele_effarea1 == 0) { cout << "reco_ele_effarea not found!" << endl; return; }
  f2->GetObject("reco_ele_effarea",reco_ele_effarea2);
  if (reco_ele_effarea2 == 0) { cout << "reco_ele_effarea not found!" << endl; return; }

plot_2histograms(reco_ele_effarea1, label1, reco_ele_effarea2, label2, path, "reco_ele_effarea", "top_right", false, false);


  //Reco Electron dxz
  TH1D *reco_ele_dxy1 = 0;
  TH1D *reco_ele_dxy2 = 0;

  f1->GetObject("reco_ele_dxy",reco_ele_dxy1);
  if (reco_ele_dxy1 == 0) { cout << "reco_ele_dxy not found!" << endl; return; }
  f2->GetObject("reco_ele_dxy",reco_ele_dxy2);
  if (reco_ele_dxy2 == 0) { cout << "reco_ele_dxy not found!" << endl; return; }

plot_2histograms(reco_ele_dxy1, label1, reco_ele_dxy2, label2, path, "reco_ele_dxy", "top_right", true, false);

  //Reco Electron dz
  TH1D *reco_ele_dz1 = 0;
  TH1D *reco_ele_dz2 = 0;

  f1->GetObject("reco_ele_dz",reco_ele_dz1);
  if (reco_ele_dz1 == 0) { cout << "reco_ele_dz not found!" << endl; return; }
  f2->GetObject("reco_ele_dz",reco_ele_dz2);
  if (reco_ele_dz2 == 0) { cout << "reco_ele_dz not found!" << endl; return; }

plot_2histograms(reco_ele_dz1, label1, reco_ele_dz2, label2, path, "reco_ele_dz", "top_right", true, false);

  //Reco Electron missing hit
  TH1D *reco_ele_missinghit1 = 0;
  TH1D *reco_ele_missinghit2 = 0;

  f1->GetObject("reco_ele_missinghit",reco_ele_missinghit1);
  if (reco_ele_missinghit1 == 0) { cout << "reco_ele_missinghit not found!" << endl; return; }
  f2->GetObject("reco_ele_missinghit",reco_ele_missinghit2);
  if (reco_ele_missinghit2 == 0) { cout << "reco_ele_missinghit not found!" << endl; return; }

plot_2histograms(reco_ele_missinghit1, label1, reco_ele_missinghit2, label2, path, "reco_ele_missinghit", "top_right", false, false);

  //Reco Electron BDT
  TH1D *reco_ele_bdt1 = 0;
  TH1D *reco_ele_bdt2 = 0;

  f1->GetObject("reco_ele_bdt",reco_ele_bdt1);
  if (reco_ele_bdt1 == 0) { cout << "reco_ele_bdt not found!" << endl; return; }
  f2->GetObject("reco_ele_bdt",reco_ele_bdt2);
  if (reco_ele_bdt2 == 0) { cout << "reco_ele_bdt not found!" << endl; return; }

plot_2histograms(reco_ele_bdt1, label1, reco_ele_bdt2, label2, path, "reco_ele_bdt", "top_left", false, false);

  //Reco Electron BDT Barrel
  TH1D *reco_ele_bdt_barrel1 = 0;
  TH1D *reco_ele_bdt_barrel2 = 0;

  f1->GetObject("reco_ele_bdt_barrel",reco_ele_bdt_barrel1);
  if (reco_ele_bdt_barrel1 == 0) { cout << "reco_ele_bdt_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_bdt_barrel",reco_ele_bdt_barrel2);
  if (reco_ele_bdt_barrel2 == 0) { cout << "reco_ele_bdt_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_bdt_barrel1, label1, reco_ele_bdt_barrel2, label2, path, "reco_ele_bdt_barrel", "top_left", false, false);

  //Reco Electron BDT EndCap
  TH1D *reco_ele_bdt_endcap1 = 0;
  TH1D *reco_ele_bdt_endcap2 = 0;

  f1->GetObject("reco_ele_bdt_endcap",reco_ele_bdt_endcap1);
  if (reco_ele_bdt_endcap1 == 0) { cout << "reco_ele_bdt_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_bdt_endcap",reco_ele_bdt_endcap2);
  if (reco_ele_bdt_endcap2 == 0) { cout << "reco_ele_bdt_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_bdt_endcap1, label1, reco_ele_bdt_endcap2, label2, path, "reco_ele_bdt_endcap", "top_left", false, false);

  //Reco Electron SIP
  TH1D *reco_ele_sip1 = 0;
  TH1D *reco_ele_sip2 = 0;

  f1->GetObject("reco_ele_sip",reco_ele_sip1);
  if (reco_ele_sip1 == 0) { cout << "reco_ele_sip not found!" << endl; return; }
  f2->GetObject("reco_ele_sip",reco_ele_sip2);
  if (reco_ele_sip2 == 0) { cout << "reco_ele_sip not found!" << endl; return; }

plot_2histograms(reco_ele_sip1, label1, reco_ele_sip2, label2, path, "reco_ele_sip", "top_right", true, false);

  //Reco Electron SIP Barrel
  TH1D *reco_ele_sip_barrel1 = 0;
  TH1D *reco_ele_sip_barrel2 = 0;

  f1->GetObject("reco_ele_sip_barrel",reco_ele_sip_barrel1);
  if (reco_ele_sip_barrel1 == 0) { cout << "reco_ele_sip_barrel not found!" << endl; return; }
  f2->GetObject("reco_ele_sip_barrel",reco_ele_sip_barrel2);
  if (reco_ele_sip_barrel2 == 0) { cout << "reco_ele_sip_barrel not found!" << endl; return; }

plot_2histograms(reco_ele_sip_barrel1, label1, reco_ele_sip_barrel2, label2, path, "reco_ele_sip_barrel", "top_right", true, false);

  //Reco Electron SIP EndCap
  TH1D *reco_ele_sip_endcap1 = 0;
  TH1D *reco_ele_sip_endcap2 = 0;

  f1->GetObject("reco_ele_sip_endcap",reco_ele_sip_endcap1);
  if (reco_ele_sip_endcap1 == 0) { cout << "reco_ele_sip_endcap not found!" << endl; return; }
  f2->GetObject("reco_ele_sip_endcap",reco_ele_sip_endcap2);
  if (reco_ele_sip_endcap2 == 0) { cout << "reco_ele_sip_endcap not found!" << endl; return; }

plot_2histograms(reco_ele_sip_endcap1, label1, reco_ele_sip_endcap2, label2, path, "reco_ele_sip_endcap", "top_right", true, false);

  //Reco Electron ID
  TH1D *reco_ele_id1 = 0;
  TH1D *reco_ele_id2 = 0;

  f1->GetObject("reco_ele_id",reco_ele_id1);
  if (reco_ele_id1 == 0) { cout << "reco_ele_id not found!" << endl; return; }
  f2->GetObject("reco_ele_id",reco_ele_id2);
  if (reco_ele_id2 == 0) { cout << "reco_ele_id not found!" << endl; return; }

plot_2histograms(reco_ele_id1, label1, reco_ele_id2, label2, path, "reco_ele_id", "bottom_left", false, false);

  //Reco Electron isGood
  TH1D *reco_ele_isgood1 = 0;
  TH1D *reco_ele_isgood2 = 0;

  f1->GetObject("reco_ele_isgood",reco_ele_isgood1);
  if (reco_ele_isgood1 == 0) { cout << "reco_ele_isggod not found!" << endl; return; }
  f2->GetObject("reco_ele_isgood",reco_ele_isgood2);
  if (reco_ele_isgood2 == 0) { cout << "reco_ele_isgood not found!" << endl; return; }

plot_2histograms(reco_ele_isgood1, label1, reco_ele_isgood2, label2, path, "reco_ele_isgood", "bottom_left", false, false);

  //Leading Reco Electron pT
  TH1D *leading_reco_ele_pt1 = 0;
  TH1D *leading_reco_ele_pt2 = 0;

  f1->GetObject("leading_reco_ele_pt",leading_reco_ele_pt1);
  if (leading_reco_ele_pt1 == 0) { cout << "leading_reco_ele_pt not found!" << endl; return; }
  f2->GetObject("leading_reco_ele_pt",leading_reco_ele_pt2);
  if (leading_reco_ele_pt2 == 0) { cout << "leading_reco_ele_pt not found!" << endl; return; }

plot_2histograms(leading_reco_ele_pt1, label1, leading_reco_ele_pt2, label2, path, "leading_reco_ele_pt", "top_right", true, false);

  //Leading Reco Electron Eta
  TH1D *leading_reco_ele_eta1 = 0;
  TH1D *leading_reco_ele_eta2 = 0;

  f1->GetObject("leading_reco_ele_eta",leading_reco_ele_eta1);
  if (leading_reco_ele_eta1 == 0) { cout << "leading_reco_ele_eta not found!" << endl; return; }
  f2->GetObject("leading_reco_ele_eta",leading_reco_ele_eta2);
  if (leading_reco_ele_eta2 == 0) { cout << "leading_reco_ele_eta not found!" << endl; return; }

plot_2histograms(leading_reco_ele_eta1, label1, leading_reco_ele_eta2, label2, path, "leading_reco_ele_eta", "bottom_middle", true, false);

  //Leading Reco Electron Phi
  TH1D *leading_reco_ele_phi1 = 0;
  TH1D *leading_reco_ele_phi2 = 0;

  f1->GetObject("leading_reco_ele_phi",leading_reco_ele_phi1);
  if (leading_reco_ele_phi1 == 0) { cout << "leading_reco_ele_phi not found!" << endl; return; }
  f2->GetObject("leading_reco_ele_phi",leading_reco_ele_phi2);
  if (leading_reco_ele_phi2 == 0) { cout << "leading_reco_ele_phi not found!" << endl; return; }

plot_2histograms(leading_reco_ele_phi1, label1, leading_reco_ele_phi2, label2, path, "leading_reco_ele_phi", "bottom_right", true, false);
}
