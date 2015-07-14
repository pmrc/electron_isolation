// Pedro Cipriano, July 2015
// FESB - Split, CMS
// Last Update: 14 July 2015
//
// Computes the differential distributions for the electron isolation

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>

//#include "plot_histograms.h"

#include <iostream>
using namespace std;

void differential_studies_eta()
{
  gROOT -> Reset();
  gROOT->SetStyle("Plain");

  std::cout << "Differential Studies for Electron Isolation" << endl;
  std::cout << "FESB - Split, CMS" << endl;
  std::cout << "-------------------------------------------" << endl;
  std::cout << "Setup" << endl;

//verbose level
  bool detail = false;
  bool show_steps = true;
  bool test = false; //if set will get some entries from histograms and save outputs with extension _test

  if (detail) { std::cout << "Detail mode in enabled!" << endl; }
  if (show_steps) { std::cout << "All steps will be showed!" << endl; }
  if (test) { std::cout << "Test mode in enabled!" << endl; }

  cout << "-----------------------------------------------" << endl;

  // input files
  string outfile1 = "output/DY.root";
  string outfile2 = "output/GluGluToH.root";

  // sets output directory
  string path = "output/";

  // opens the files
  TFile *f1 = TFile::Open( outfile1.c_str() );
  TFile *f2 = TFile::Open( outfile2.c_str() );

  //setting the prefixes
  string prefix[2];
  prefix[0] = "DY";
  prefix[1] = "GluGluToH";

  //setting the samples number
  int samples = 2;

  //setting the working point
  int working_point = 49;

TH1D *ele_pfiso_simple_eta_eff = new TH1D("ele_pfiso_simple_eta_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_eff = new TH1D("ele_pfiso_effarea_eta_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_eff = new TH1D("ele_pfiso_deltabeta_eta_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_eff = new TH1D("ele_pfiso_puppi_eta_eff","PFIso PUPPI Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_eff = new TH1D("ele_pfiso_puppinl_eta_eff","PFIso PUPPI No Leptond Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_eff = new TH1D("ele_pfiso_citk_eta_eff","PFIso CITK Eta;#eta;Signal Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_eff_99 = new TH1D("ele_pfiso_simple_eta_eff_99","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_eff_99 = new TH1D("ele_pfiso_effarea_eta_eff_99","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_eff_99 = new TH1D("ele_pfiso_deltabeta_eta_eff_99","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_eff_99 = new TH1D("ele_pfiso_puppi_eta_eff_99","PFIso PUPPI Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_eff_99 = new TH1D("ele_pfiso_puppinl_eta_eff_99","PFIso PUPPI No Leptond Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_eff_99 = new TH1D("ele_pfiso_citk_eta_eff_99","PFIso CITK Eta;#eta;Signal Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_eff_99_bkg = new TH1D("ele_pfiso_simple_eta_eff_99_bkg","PFIso Simple Eta;#eta;Bakcground Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_eff_99_bkg = new TH1D("ele_pfiso_effarea_eta_eff_99_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_eff_99_bkg = new TH1D("ele_pfiso_deltabeta_eta_eff_99_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_eff_99_bkg = new TH1D("ele_pfiso_puppi_eta_eff_99_bkg","PFIso PUPPI Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_eff_99_bkg = new TH1D("ele_pfiso_puppinl_eta_eff_99_bkg","PFIso PUPPI No Leptond Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_eff_99_bkg = new TH1D("ele_pfiso_citk_eta_eff_99_bkg","PFIso CITK Eta;#eta;Background Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_eff_95 = new TH1D("ele_pfiso_simple_eta_eff_95","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_eff_95 = new TH1D("ele_pfiso_effarea_eta_eff_95","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_eff_95 = new TH1D("ele_pfiso_deltabeta_eta_eff_95","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_eff_95 = new TH1D("ele_pfiso_puppi_eta_eff_95","PFIso PUPPI Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_eff_95 = new TH1D("ele_pfiso_puppinl_eta_eff_95","PFIso PUPPI No Leptond Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_eff_95 = new TH1D("ele_pfiso_citk_eta_eff_95","PFIso CITK Eta;#eta;Signal Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_eff_95_bkg = new TH1D("ele_pfiso_simple_eta_eff_95_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_eff_95_bkg = new TH1D("ele_pfiso_effarea_eta_eff_95_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_eff_95_bkg = new TH1D("ele_pfiso_deltabeta_eta_eff_95_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_eff_95_bkg = new TH1D("ele_pfiso_puppi_eta_eff_95_bkg","PFIso PUPPI Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_eff_95_bkg = new TH1D("ele_pfiso_puppinl_eta_eff_95_bkg","PFIso PUPPI No Leptond Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_eff_95_bkg = new TH1D("ele_pfiso_citk_eta_eff_95_bkg","PFIso CITK Eta;#eta;Background Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_eff_90 = new TH1D("ele_pfiso_simple_eta_eff_90","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_eff_90 = new TH1D("ele_pfiso_effarea_eta_eff_90","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_eff_90 = new TH1D("ele_pfiso_deltabeta_eta_eff_90","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_eff_90 = new TH1D("ele_pfiso_puppi_eta_eff_90","PFIso PUPPI Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_eff_90 = new TH1D("ele_pfiso_puppinl_eta_eff_90","PFIso PUPPI No Leptond Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_eff_90 = new TH1D("ele_pfiso_citk_eta_eff_90","PFIso CITK Eta;#eta;Signal Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_eff_90_bkg = new TH1D("ele_pfiso_simple_eta_eff_90_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_eff_90_bkg = new TH1D("ele_pfiso_effarea_eta_eff_90_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_eff_90_bkg = new TH1D("ele_pfiso_deltabeta_eta_eff_90_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_eff_90_bkg = new TH1D("ele_pfiso_puppi_eta_eff_90_bkg","PFIso PUPPI Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_eff_90_bkg = new TH1D("ele_pfiso_puppinl_eta_eff_90_bkg","PFIso PUPPI No Leptond Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_eff_90_bkg = new TH1D("ele_pfiso_citk_eta_eff_90_bkg","PFIso CITK Eta;#eta;Background Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_bkg = new TH1D("ele_pfiso_simple_eta_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_bkg = new TH1D("ele_pfiso_effarea_eta_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_bkg = new TH1D("ele_pfiso_deltabeta_eta_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_bkg = new TH1D("ele_pfiso_puppi_eta_bkg","PFIso PUPPI Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_bkg = new TH1D("ele_pfiso_puppinl_eta_bkg","PFIso PUPPI No Leptons Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_bkg = new TH1D("ele_pfiso_citk_eta_bkg","PFIso CITK Eta;#eta;Background Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_bkg_05 = new TH1D("ele_pfiso_simple_eta_bkg_05","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_bkg_05 = new TH1D("ele_pfiso_effarea_eta_bkg_05","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_bkg_05 = new TH1D("ele_pfiso_deltabeta_eta_bkg_05","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_bkg_05 = new TH1D("ele_pfiso_puppi_eta_bkg_05","PFIso PUPPI Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_bkg_05 = new TH1D("ele_pfiso_puppinl_eta_bkg_05","PFIso PUPPI No Leptons Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_bkg_05 = new TH1D("ele_pfiso_citk_eta_bkg_05","PFIso CITK Eta;#eta;Background Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_bkg_05_eff = new TH1D("ele_pfiso_simple_eta_bkg_05_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_bkg_05_eff = new TH1D("ele_pfiso_effarea_eta_bkg_05_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_bkg_05_eff = new TH1D("ele_pfiso_deltabeta_eta_bkg_05_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_bkg_05_eff = new TH1D("ele_pfiso_puppi_eta_bkg_05_eff","PFIso PUPPI Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_bkg_05_eff = new TH1D("ele_pfiso_puppinl_eta_bkg_05_eff","PFIso PUPPI No Leptons Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_bkg_05_eff = new TH1D("ele_pfiso_citk_eta_bkg_05_eff","PFIso CITK Eta;#eta;Signal Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_bkg_10 = new TH1D("ele_pfiso_simple_eta_bkg_10","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_bkg_10 = new TH1D("ele_pfiso_effarea_eta_bkg_10","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_bkg_10 = new TH1D("ele_pfiso_deltabeta_eta_bkg_10","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_bkg_10 = new TH1D("ele_pfiso_puppi_eta_bkg_10","PFIso PUPPI Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_bkg_10 = new TH1D("ele_pfiso_puppinl_eta_bkg_10","PFIso PUPPI No Leptons Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_bkg_10 = new TH1D("ele_pfiso_citk_eta_bkg_10","PFIso CITK Eta;#eta;Background Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_bkg_10_eff = new TH1D("ele_pfiso_simple_eta_bkg_10_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_bkg_10_eff = new TH1D("ele_pfiso_effarea_eta_bkg_10_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_bkg_10_eff = new TH1D("ele_pfiso_deltabeta_eta_bkg_10_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_bkg_10_eff = new TH1D("ele_pfiso_puppi_eta_bkg_10_eff","PFIso PUPPI Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_bkg_10_eff = new TH1D("ele_pfiso_puppinl_eta_bkg_10_eff","PFIso PUPPI No Leptons Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_bkg_10_eff = new TH1D("ele_pfiso_citk_eta_bkg_10_eff","PFIso CITK Eta;#eta;Signal Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_bkg_15 = new TH1D("ele_pfiso_simple_eta_bkg_15","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_bkg_15 = new TH1D("ele_pfiso_effarea_eta_bkg_15","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_bkg_15 = new TH1D("ele_pfiso_deltabeta_eta_bkg_15","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_bkg_15 = new TH1D("ele_pfiso_puppi_eta_bkg_15","PFIso PUPPI Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_bkg_15 = new TH1D("ele_pfiso_puppinl_eta_bkg_15","PFIso PUPPI No Leptons Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_bkg_15 = new TH1D("ele_pfiso_citk_eta_bkg_15","PFIso CITK Eta;#eta;Background Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_bkg_15_eff = new TH1D("ele_pfiso_simple_eta_bkg_15_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_bkg_15_eff = new TH1D("ele_pfiso_effarea_eta_bkg_15_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_bkg_15_eff = new TH1D("ele_pfiso_deltabeta_eta_bkg_15_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_bkg_15_eff = new TH1D("ele_pfiso_puppi_eta_bkg_15_eff","PFIso PUPPI Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_bkg_15_eff = new TH1D("ele_pfiso_puppinl_eta_bkg_15_eff","PFIso PUPPI No Leptons Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_bkg_15_eff = new TH1D("ele_pfiso_citk_eta_bkg_15_eff","PFIso CITK Eta;#eta;Signal Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_ratio = new TH1D("ele_pfiso_simple_eta_ratio","PFIso Simple Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_ratio = new TH1D("ele_pfiso_effarea_eta_ratio","PFIso Simple Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_ratio = new TH1D("ele_pfiso_deltabeta_eta_ratio","PFIso Simple Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_ratio = new TH1D("ele_pfiso_puppi_eta_ratio","PFIso PUPPI Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_ratio = new TH1D("ele_pfiso_puppinl_eta_ratio","PFIso PUPPI No Leptons Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_ratio = new TH1D("ele_pfiso_citk_eta_ratio","PFIso CITK Eta;#eta;Signal/Background", 25,-2.5,2.5);

  //declaring matrices and arrays
   double isolation_simple_eta[samples][25];
   double isolation_simple_eta_eff_90[25], isolation_simple_eta_eff_90_bkg[25];
   double isolation_simple_eta_eff_95[25], isolation_simple_eta_eff_95_bkg[25];
   double isolation_simple_eta_eff_99[25], isolation_simple_eta_eff_99_bkg[25];
   double isolation_simple_eta_bkg_05[25], isolation_simple_eta_bkg_05_eff[25];
   double isolation_simple_eta_bkg_10[25], isolation_simple_eta_bkg_10_eff[25];
   double isolation_simple_eta_bkg_15[25], isolation_simple_eta_bkg_15_eff[25];

   double isolation_effarea_eta[samples][25];
   double isolation_effarea_eta_eff_90[25], isolation_effarea_eta_eff_90_bkg[25];
   double isolation_effarea_eta_eff_95[25], isolation_effarea_eta_eff_95_bkg[25];
   double isolation_effarea_eta_eff_99[25], isolation_effarea_eta_eff_99_bkg[25];
   double isolation_effarea_eta_bkg_05[25], isolation_effarea_eta_bkg_05_eff[25];
   double isolation_effarea_eta_bkg_10[25], isolation_effarea_eta_bkg_10_eff[25];
   double isolation_effarea_eta_bkg_15[25], isolation_effarea_eta_bkg_15_eff[25];

   double isolation_deltabeta_eta[samples][25];
   double isolation_deltabeta_eta_eff_90[25], isolation_deltabeta_eta_eff_90_bkg[25];
   double isolation_deltabeta_eta_eff_95[25], isolation_deltabeta_eta_eff_95_bkg[25];
   double isolation_deltabeta_eta_eff_99[25], isolation_deltabeta_eta_eff_99_bkg[25];
   double isolation_deltabeta_eta_bkg_05[25], isolation_deltabeta_eta_bkg_05_eff[25];
   double isolation_deltabeta_eta_bkg_10[25], isolation_deltabeta_eta_bkg_10_eff[25];
   double isolation_deltabeta_eta_bkg_15[25], isolation_deltabeta_eta_bkg_15_eff[25];

   double isolation_puppi_eta[samples][25];
   double isolation_puppi_eta_eff_90[25], isolation_puppi_eta_eff_90_bkg[25];
   double isolation_puppi_eta_eff_95[25], isolation_puppi_eta_eff_95_bkg[25];
   double isolation_puppi_eta_eff_99[25], isolation_puppi_eta_eff_99_bkg[25];
   double isolation_puppi_eta_bkg_05[25], isolation_puppi_eta_bkg_05_eff[25];
   double isolation_puppi_eta_bkg_10[25], isolation_puppi_eta_bkg_10_eff[25];
   double isolation_puppi_eta_bkg_15[25], isolation_puppi_eta_bkg_15_eff[25];

   double isolation_puppinl_eta[samples][25];
   double isolation_puppinl_eta_eff_90[25], isolation_puppinl_eta_eff_90_bkg[25];
   double isolation_puppinl_eta_eff_95[25], isolation_puppinl_eta_eff_95_bkg[25];
   double isolation_puppinl_eta_eff_99[25], isolation_puppinl_eta_eff_99_bkg[25];
   double isolation_puppinl_eta_bkg_05[25], isolation_puppinl_eta_bkg_05_eff[25];
   double isolation_puppinl_eta_bkg_10[25], isolation_puppinl_eta_bkg_10_eff[25];
   double isolation_puppinl_eta_bkg_15[25], isolation_puppinl_eta_bkg_15_eff[25];


   double isolation_citk_eta[samples][25];
   double isolation_citk_eta_eff_90[25], isolation_citk_eta_eff_90_bkg[25];
   double isolation_citk_eta_eff_95[25], isolation_citk_eta_eff_95_bkg[25];
   double isolation_citk_eta_eff_99[25], isolation_citk_eta_eff_99_bkg[25];
   double isolation_citk_eta_bkg_05[25], isolation_citk_eta_bkg_05_eff[25];
   double isolation_citk_eta_bkg_10[25], isolation_citk_eta_bkg_10_eff[25];
   double isolation_citk_eta_bkg_15[25], isolation_citk_eta_bkg_15_eff[25];

for (int s = 0; s <= 1; ++s)
{	
   for (int y=0; y<25; ++y)
	{
	isolation_simple_eta[s][y] = 0;
	isolation_effarea_eta[s][y] = 0;
	isolation_deltabeta_eta[s][y] = 0;
	isolation_puppi_eta[s][y] = 0;
	isolation_puppinl_eta[s][y] = 0;
	isolation_citk_eta[s][y] = 0;
	}
}

   for (int y=0; y<25; ++y)
	{
	isolation_simple_eta_eff_99[y] = 0;
	isolation_effarea_eta_eff_99[y] = 0;
	isolation_deltabeta_eta_eff_99[y] = 0;
	isolation_puppi_eta_eff_99[y] = 0;
	isolation_puppinl_eta_eff_99[y] = 0;
	isolation_citk_eta_eff_99[y] = 0;

	isolation_simple_eta_eff_99_bkg[y] = 0;
	isolation_effarea_eta_eff_99_bkg[y] = 0;
	isolation_deltabeta_eta_eff_99_bkg[y] = 0;
	isolation_puppi_eta_eff_99_bkg[y] = 0;
	isolation_puppinl_eta_eff_99_bkg[y] = 0;
	isolation_citk_eta_eff_99_bkg[y] = 0;

	isolation_simple_eta_eff_95[y] = 0;
	isolation_effarea_eta_eff_95[y] = 0;
	isolation_deltabeta_eta_eff_95[y] = 0;
	isolation_puppi_eta_eff_95[y] = 0;
	isolation_puppinl_eta_eff_95[y] = 0;
	isolation_citk_eta_eff_95[y] = 0;

	isolation_simple_eta_eff_95_bkg[y] = 0;
	isolation_effarea_eta_eff_95_bkg[y] = 0;
	isolation_deltabeta_eta_eff_95_bkg[y] = 0;
	isolation_puppi_eta_eff_95_bkg[y] = 0;
	isolation_puppinl_eta_eff_95_bkg[y] = 0;
	isolation_citk_eta_eff_95_bkg[y] = 0;

	isolation_simple_eta_eff_90[y] = 0;
	isolation_effarea_eta_eff_90[y] = 0;
	isolation_deltabeta_eta_eff_90[y] = 0;
	isolation_puppi_eta_eff_90[y] = 0;
	isolation_puppinl_eta_eff_90[y] = 0;
	isolation_citk_eta_eff_90[y] = 0;

	isolation_simple_eta_eff_90_bkg[y] = 0;
	isolation_effarea_eta_eff_90_bkg[y] = 0;
	isolation_deltabeta_eta_eff_90_bkg[y] = 0;
	isolation_puppi_eta_eff_90_bkg[y] = 0;
	isolation_puppinl_eta_eff_90_bkg[y] = 0;
	isolation_citk_eta_eff_90_bkg[y] = 0;

	isolation_simple_eta_bkg_05[y] = 0;
	isolation_effarea_eta_bkg_05[y] = 0;
	isolation_deltabeta_eta_bkg_05[y] = 0;
	isolation_puppi_eta_bkg_05[y] = 0;
	isolation_puppinl_eta_bkg_05[y] = 0;
	isolation_citk_eta_bkg_05[y] = 0;

	isolation_simple_eta_bkg_05_eff[y] = 0;
	isolation_effarea_eta_bkg_05_eff[y] = 0;
	isolation_deltabeta_eta_bkg_05_eff[y] = 0;
	isolation_puppi_eta_bkg_05_eff[y] = 0;
	isolation_puppinl_eta_bkg_05_eff[y] = 0;
	isolation_citk_eta_bkg_05_eff[y] = 0;

	isolation_simple_eta_bkg_10[y] = 0;
	isolation_effarea_eta_bkg_10[y] = 0;
	isolation_deltabeta_eta_bkg_10[y] = 0;
	isolation_puppi_eta_bkg_10[y] = 0;
	isolation_puppinl_eta_bkg_10[y] = 0;
	isolation_citk_eta_bkg_10[y] = 0;

	isolation_simple_eta_bkg_10_eff[y] = 0;
	isolation_effarea_eta_bkg_10_eff[y] = 0;
	isolation_deltabeta_eta_bkg_10_eff[y] = 0;
	isolation_puppi_eta_bkg_10_eff[y] = 0;
	isolation_puppinl_eta_bkg_10_eff[y] = 0;
	isolation_citk_eta_bkg_10_eff[y] = 0;

	isolation_simple_eta_bkg_15[y] = 0;
	isolation_effarea_eta_bkg_15[y] = 0;
	isolation_deltabeta_eta_bkg_15[y] = 0;
	isolation_puppi_eta_bkg_15[y] = 0;
	isolation_puppinl_eta_bkg_15[y] = 0;
	isolation_citk_eta_bkg_15[y] = 0;

	isolation_simple_eta_bkg_15_eff[y] = 0;
	isolation_effarea_eta_bkg_15_eff[y] = 0;
	isolation_deltabeta_eta_bkg_15_eff[y] = 0;
	isolation_puppi_eta_bkg_15_eff[y] = 0;
	isolation_puppinl_eta_bkg_15_eff[y] = 0;
	isolation_citk_eta_bkg_15_eff[y] = 0;
	}

  //Iso Simple VS Eta
  TH2D *iso_simple_vs_eta1 = 0;
  TH2D *iso_simple_vs_eta2 = 0;

  f1->GetObject("iso_simple_vs_eta",iso_simple_vs_eta1);
  if (iso_simple_vs_eta1 == 0) { cout << "iso_simple_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_simple_vs_eta",iso_simple_vs_eta2);
  if (iso_simple_vs_eta2 == 0) { cout << "iso_simple_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_simple_vs_eta1, "output/", prefix[0] + "_iso_simple_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_simple_vs_eta2, "output/", prefix[1] + "_iso_simple_vs_eta", prefix[1], "top_right", true);

  //Iso Effective Area VS Eta
  TH2D *iso_effarea_vs_eta1 = 0;
  TH2D *iso_effarea_vs_eta2 = 0;

  f1->GetObject("iso_effarea_vs_eta",iso_effarea_vs_eta1);
  if (iso_effarea_vs_eta1 == 0) { cout << "iso_effarea_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_effarea_vs_eta",iso_effarea_vs_eta2);
  if (iso_effarea_vs_eta2 == 0) { cout << "iso_effarea_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_effarea_vs_eta1, "output/", prefix[0] + "_iso_effarea_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_effarea_vs_eta2, "output/", prefix[1] + "_iso_effarea_vs_eta", prefix[1], "top_right", true);

  //Iso Delta Beta VS Eta
  TH2D *iso_deltabeta_vs_eta1 = 0;
  TH2D *iso_deltabeta_vs_eta2 = 0;

  f1->GetObject("iso_deltabeta_vs_eta",iso_deltabeta_vs_eta1);
  if (iso_deltabeta_vs_eta1 == 0) { cout << "iso_deltabeta_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_deltabeta_vs_eta",iso_deltabeta_vs_eta2);
  if (iso_deltabeta_vs_eta2 == 0) { cout << "iso_deltabeta_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_deltabeta_vs_eta1, "output/", prefix[0] + "_iso_deltabeta_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_deltabeta_vs_eta2, "output/", prefix[1] + "_iso_deltabeta_vs_eta", prefix[1], "top_right", true);

  //Iso PUPPI VS Eta
  TH2D *iso_puppi_vs_eta1 = 0;
  TH2D *iso_puppi_vs_eta2 = 0;

  f1->GetObject("iso_puppi_vs_eta",iso_puppi_vs_eta1);
  if (iso_puppi_vs_eta1 == 0) { cout << "iso_puppi_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_puppi_vs_eta",iso_puppi_vs_eta2);
  if (iso_puppi_vs_eta2 == 0) { cout << "iso_puppi_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_puppi_vs_eta1, "output/", prefix[0] + "_iso_puppi_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppi_vs_eta2, "output/", prefix[1] + "_iso_puppi_vs_eta", prefix[1], "top_right", true);

  //Iso PUPPI No Leptons VS Eta
  TH2D *iso_puppinl_vs_eta1 = 0;
  TH2D *iso_puppinl_vs_eta2 = 0;

  f1->GetObject("iso_puppinl_vs_eta",iso_puppinl_vs_eta1);
  if (iso_puppinl_vs_eta1 == 0) { cout << "iso_puppinl_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_puppinl_vs_eta",iso_puppinl_vs_eta2);
  if (iso_puppinl_vs_eta2 == 0) { cout << "iso_puppinl_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_puppinl_vs_eta1, "output/", prefix[0] + "_iso_puppinl_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppinl_vs_eta2, "output/", prefix[1] + "_iso_puppinl_vs_eta", prefix[1], "top_right", true);



  //Iso citk VS eta
  TH2D *iso_citk_vs_eta1 = 0;
  TH2D *iso_citk_vs_eta2 = 0;

  f1->GetObject("iso_citk_vs_eta",iso_citk_vs_eta1);
  if (iso_citk_vs_eta1 == 0) { cout << "iso_citk_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_citk_vs_eta",iso_citk_vs_eta2);
  if (iso_citk_vs_eta2 == 0) { cout << "iso_citk_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_citk_vs_eta1, "output/", prefix[0] + "_iso_citk_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_citk_vs_eta2, "output/", prefix[1] + "_iso_citk_vs_eta", prefix[1], "top_right", true);


   int nbins = iso_simple_vs_eta1->GetNbinsY();

for (int x=1; x<=nbins; x++)
	{
        if (test) { cout << "begin of loop " << x << "!" << endl; }
	isolation_simple_eta[0][x-1] = iso_simple_vs_eta1->Integral(0,working_point,x,x)/iso_simple_vs_eta1->Integral(0,2000,x,x);
        if (test) { cout << "bin " << x << " = " << isolation_simple_eta[0][x-1] << endl; }
	isolation_effarea_eta[0][x-1] = iso_effarea_vs_eta1->Integral(0,working_point,x,x)/iso_effarea_vs_eta1->Integral(0,2000,x,x);
	isolation_deltabeta_eta[0][x-1] = iso_deltabeta_vs_eta1->Integral(0,working_point,x,x)/iso_deltabeta_vs_eta1->Integral(0,2000,x,x);
	isolation_puppi_eta[0][x-1] = iso_puppi_vs_eta1->Integral(0,working_point,x,x)/iso_puppi_vs_eta1->Integral(0,2000,x,x);
	isolation_puppinl_eta[0][x-1] = iso_puppinl_vs_eta1->Integral(0,working_point,x,x)/iso_puppinl_vs_eta1->Integral(0,2000,x,x);
	isolation_citk_eta[0][x-1] = iso_citk_vs_eta1->Integral(0,working_point,x,x)/iso_citk_vs_eta1->Integral(0,2000,x,x);
        if (test) { cout << x << " - " << isolation_simple_eta[0][x-1] << " | " << isolation_effarea_eta[0][x-1] << " | " << isolation_deltabeta_eta[0][x-1] << endl; }

        if (test) { cout << "middle of loop!" << endl; }
	isolation_simple_eta[1][x-1] = iso_simple_vs_eta2->Integral(0,working_point,x,x)/iso_simple_vs_eta2->Integral(0,2000,x,x);
	isolation_effarea_eta[1][x-1] = iso_effarea_vs_eta2->Integral(0,working_point,x,x)/iso_effarea_vs_eta2->Integral(0,2000,x,x);
	isolation_deltabeta_eta[1][x-1] = iso_deltabeta_vs_eta2->Integral(0,working_point,x,x)/iso_deltabeta_vs_eta2->Integral(0,2000,x,x);
	isolation_puppi_eta[1][x-1] = iso_puppi_vs_eta2->Integral(0,working_point,x,x)/iso_puppi_vs_eta2->Integral(0,2000,x,x);
	isolation_puppinl_eta[1][x-1] = iso_puppinl_vs_eta2->Integral(0,working_point,x,x)/iso_puppinl_vs_eta2->Integral(0,2000,x,x);
	isolation_citk_eta[1][x-1] = iso_citk_vs_eta2->Integral(0,working_point,x,x)/iso_citk_vs_eta2->Integral(0,2000,x,x);
        if (test) { cout << "end of loop!" << endl; }
	}


   for (int x=0; x<=24; x++)
	{
	ele_pfiso_simple_eta_eff->SetBinContent(x+1,isolation_simple_eta[1][x]);
	ele_pfiso_effarea_eta_eff->SetBinContent(x+1,isolation_effarea_eta[1][x]);
	ele_pfiso_deltabeta_eta_eff->SetBinContent(x+1,isolation_deltabeta_eta[1][x]);
	ele_pfiso_puppi_eta_eff->SetBinContent(x+1,isolation_puppi_eta[1][x]);
	ele_pfiso_puppinl_eta_eff->SetBinContent(x+1,isolation_puppinl_eta[1][x]);
	ele_pfiso_citk_eta_eff->SetBinContent(x+1,isolation_citk_eta[1][x]);
	ele_pfiso_simple_eta_eff->SetBinError(x+1,0);
	ele_pfiso_effarea_eta_eff->SetBinError(x+1,0);
	ele_pfiso_deltabeta_eta_eff->SetBinError(x+1,0);
	ele_pfiso_puppi_eta_eff->SetBinError(x+1,0);
	ele_pfiso_puppinl_eta_eff->SetBinError(x+1,0);
	ele_pfiso_citk_eta_eff->SetBinError(x+1,0);

	ele_pfiso_simple_eta_bkg->SetBinContent(x+1,isolation_simple_eta[0][x]);
	ele_pfiso_effarea_eta_bkg->SetBinContent(x+1,isolation_effarea_eta[0][x]);
	ele_pfiso_deltabeta_eta_bkg->SetBinContent(x+1,isolation_deltabeta_eta[0][x]);
	ele_pfiso_puppi_eta_bkg->SetBinContent(x+1,isolation_puppi_eta[0][x]);
	ele_pfiso_puppinl_eta_bkg->SetBinContent(x+1,isolation_puppinl_eta[0][x]);
	ele_pfiso_citk_eta_bkg->SetBinContent(x+1,isolation_citk_eta[0][x]);
	ele_pfiso_simple_eta_bkg->SetBinError(x+1,0);
	ele_pfiso_effarea_eta_bkg->SetBinError(x+1,0);
	ele_pfiso_deltabeta_eta_bkg->SetBinError(x+1,0);
	ele_pfiso_puppi_eta_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_eta_bkg->SetBinError(x+1,0);
	ele_pfiso_citk_eta_bkg->SetBinError(x+1,0);

	ele_pfiso_simple_eta_ratio->SetBinContent(x+1,isolation_simple_eta[1][x]/isolation_simple_eta[0][x]);
	ele_pfiso_effarea_eta_ratio->SetBinContent(x+1,isolation_effarea_eta[1][x]/isolation_effarea_eta[0][x]);
	ele_pfiso_deltabeta_eta_ratio->SetBinContent(x+1,isolation_deltabeta_eta[1][x]/isolation_deltabeta_eta[0][x]);
	ele_pfiso_puppi_eta_ratio->SetBinContent(x+1,isolation_puppi_eta[1][x]/isolation_puppi_eta[0][x]);
	ele_pfiso_puppinl_eta_ratio->SetBinContent(x+1,isolation_puppinl_eta[1][x]/isolation_puppinl_eta[0][x]);
	ele_pfiso_citk_eta_ratio->SetBinContent(x+1,isolation_citk_eta[1][x]/isolation_citk_eta[0][x]);
	ele_pfiso_simple_eta_ratio->SetBinError(x+1,0);
	ele_pfiso_effarea_eta_ratio->SetBinError(x+1,0);
	ele_pfiso_deltabeta_eta_ratio->SetBinError(x+1,0);
	ele_pfiso_puppi_eta_ratio->SetBinError(x+1,0);
	ele_pfiso_puppinl_eta_ratio->SetBinError(x+1,0);
	ele_pfiso_citk_eta_ratio->SetBinError(x+1,0);
	}

   for (int x=0; x<=24; x++)
	{
	if (test) { cout << x << " - " << isolation_simple_eta[0][x] << " | " << isolation_effarea_eta[0][x] << endl; }
	}

   plot_histogram(ele_pfiso_simple_eta_eff, "output/","ele_pfiso_simple_eta_eff", "Electron PF Isolation Simple Eta", "bottom_middle", false);
   plot_histogram(ele_pfiso_effarea_eta_eff, "output/","ele_pfiso_effarea_eta_eff", "Electron PF Isolation Effective Area Eta", "bottom_middle", false);
   plot_histogram(ele_pfiso_deltabeta_eta_eff, "output/","ele_pfiso_deltabeta_eta_eff", "Electron PF Isolation Delta Beta Eta", "bottom_middle", false);
   plot_histogram(ele_pfiso_puppi_eta_eff, "output/","ele_pfiso_puppi_eta_eff", "Electron PF Isolation PUPPI Eta", "bottom_middle", false);
   plot_histogram(ele_pfiso_puppinl_eta_eff, "output/","ele_pfiso_puppinl_eta_eff", "Electron PF Isolation PUPPI No Leptons Eta", "bottom_middle", false);
   plot_histogram(ele_pfiso_citk_eta_eff, "output/","ele_pfiso_citk_eta_eff", "Electron PF Isolation CITK Eta", "bottom_middle", false);

   plot_six_dist(ele_pfiso_simple_eta_eff, "PF without PU subtraction", ele_pfiso_effarea_eta_eff, "Effective Area", ele_pfiso_deltabeta_eta_eff, "Delta Beta", ele_pfiso_puppi_eta_eff, "PUPPI", ele_pfiso_puppinl_eta_eff, "PUPPI No Leptons", ele_pfiso_citk_eta_eff, "CITK", "output/", "", "ele_pfiso_eta_eff", "bottom_middle", false, false);


   plot_histogram(ele_pfiso_simple_eta_bkg, "output/","ele_pfiso_simple_eta_bkg", "Electron PF Isolation Simple Eta", "top_right", false);
   plot_histogram(ele_pfiso_effarea_eta_bkg, "output/","ele_pfiso_effarea_eta_bkg", "Electron PF Isolation Effective Area Eta", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_eta_bkg, "output/","ele_pfiso_deltabeta_eta_bkg", "Electron PF Isolation Delta Beta Eta", "top_right", false);
   plot_histogram(ele_pfiso_puppi_eta_bkg, "output/","ele_pfiso_puppi_eta_bkg", "Electron PF Isolation PUPPI Eta", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_eta_bkg, "output/","ele_pfiso_puppinl_eta_bkg", "Electron PF Isolation PUPPI No Leptons Eta", "top_right", false);
   plot_histogram(ele_pfiso_citk_eta_bkg, "output/","ele_pfiso_citk_eta_bkg", "Electron PF Isolation CITK Eta", "top_right", false);

   plot_six_dist(ele_pfiso_simple_eta_bkg, "PF without PU subtraction", ele_pfiso_effarea_eta_bkg, "Effective Area", ele_pfiso_deltabeta_eta_bkg, "Delta Beta", ele_pfiso_puppi_eta_bkg, "PUPPI", ele_pfiso_puppinl_eta_bkg, "PUPPI No Leptons", ele_pfiso_citk_eta_bkg, "CITK", "output/", "", "ele_pfiso_eta_bkg", "bottom_middle", false, false);

   plot_histogram(ele_pfiso_simple_eta_ratio, "output/","ele_pfiso_simple_eta_ratio", "Electron PF Isolation Simple Eta", "top_right", false);
   plot_histogram(ele_pfiso_effarea_eta_ratio, "output/","ele_pfiso_effarea_eta_ratio", "Electron PF Isolation Effective Area Eta", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_eta_ratio, "output/","ele_pfiso_deltabeta_eta_ratio", "Electron PF Isolation Delta Beta Eta", "top_right", false);
   plot_histogram(ele_pfiso_puppi_eta_ratio, "output/","ele_pfiso_puppi_eta_ratio", "Electron PF Isolation PUPPI Eta", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_eta_ratio, "output/","ele_pfiso_puppinl_eta_ratio", "Electron PF Isolation PUPPI No Leptons Eta", "top_right", false);
   plot_histogram(ele_pfiso_citk_eta_ratio, "output/","ele_pfiso_citk_eta_ratio", "Electron PF Isolation CITK Eta", "top_right", false);

   plot_six_dist(ele_pfiso_simple_eta_ratio, "PF without PU subtraction", ele_pfiso_effarea_eta_ratio, "Effective Area", ele_pfiso_deltabeta_eta_ratio, "Delta Beta", ele_pfiso_puppi_eta_ratio, "PUPPI", ele_pfiso_puppinl_eta_ratio, "PUPPI No Leptons", ele_pfiso_citk_eta_ratio, "CITK", "output/", "", "ele_pfiso_eta_ratio", "bottom_left", false, 0.0, 21.0, false);
}

