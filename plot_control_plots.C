// Pedro Cipriano, May 2015
// FESB - Split, CMS
// Last Update: 29 May 2015
//
// 

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>
#include <TGraph.h>

#include "plot_histograms.h"

using namespace std;

void plot_control_plots()
{
  gROOT -> Reset();
  gROOT->SetStyle("Plain");

  cout << "Plot Electron Isolation" << endl;
  cout << "FESB - Split, CMS" << endl;
  cout << "-------------------------------------" << endl;
  cout << "Setup" << endl;

//verbose level
  bool detail = false;
  bool show_steps = true;
  bool test = false; //if set will get some entries from histograms and save outputs with extension _test

  if (detail) { cout << "Detail mode in enabled!" << endl; }
  if (show_steps) { cout << "All steps will be showed!" << endl; }
  if (test) { cout << "Test mode in enabled!" << endl; }

  cout << "-------------------------------------" << endl;

  string outfile1 = "output/DY.root";
  string outfile2 = "output/ggH.root";
  TString label1 = "DY";
  TString label2 = "ggH";

  string path = "output/";

  TFile *f1 = TFile::Open( outfile1.c_str() );
  TFile *f2 = TFile::Open( outfile2.c_str() );

  //Vertex Multiplicity
  TH1D *vertex_multiplicity1 = 0;
  TH1D *vertex_multiplicity2 = 0;

  f1->GetObject("vertex_multiplicity",vertex_multiplicity1);
  if (vertex_multiplicity1 == 0) { cout << "vertex_multiplicity not found!" << endl; return; }
  f2->GetObject("vertex_multiplicity",vertex_multiplicity2);
  if (vertex_multiplicity2 == 0) { cout << "vertex_multiplicity not found!" << endl; return; }

plot_2histograms(vertex_multiplicity1, label1, vertex_multiplicity2, label2, path, "vertex_multiplicity", "top_right", false, false);

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

}
