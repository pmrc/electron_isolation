// Pedro Cipriano, May 2015
// FESB - Split, CMS
// Last Update: 28 May 2015
//
// 

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>
#include <TGraph.h>

#include "plot_histograms.h"

using namespace std;

void plot_electron_isolation()
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
  string label1 = "DY";
  string label2 = "ggH";

  TFile *f1 = TFile::Open( outfile1.c_str() );
  TFile *f2 = TFile::Open( outfile2.c_str() );

  //Vertex Multiplicity
  TH1D *vertex_multiplicity1 = 0;
  TH1D *vertex_multiplicity2 = 0;

  f1->GetObject("vertex_multiplicity",vertex_multiplicity1);
  if (vertex_multiplicity1 == 0) { cout << "vertex_multiplicity not found!" << endl; return; }
  f2->GetObject("vertex_multiplicity",vertex_multiplicity2);
  if (vertex_multiplicity2 == 0) { cout << "vertex_multiplicity not found!" << endl; return; }

}
