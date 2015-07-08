// Pedro Cipriano, July 2015
// FESB - Split, CMS
// Last Update: 02 July 2015
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

void differential_studies_pt()
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

  //setting the binning
  int pt_nbins = 10;
  double pt_bins[11] = {7.0,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,60.0,100.0};

  //Declare Histograms
TH1D *ele_pfiso_simple_pt_eff = new TH1D("ele_pfiso_simple_pt_eff","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_eff = new TH1D("ele_pfiso_effarea_pt_eff","PFIso Effective Area pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_eff = new TH1D("ele_pfiso_deltabeta_pt_eff","PFIso Delta Beta pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_eff = new TH1D("ele_pfiso_puppi_pt_eff","PFIso PUPPI pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_eff = new TH1D("ele_pfiso_puppinl_pt_eff","PFIso PUPPI No Leptons pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_eff = new TH1D("ele_pfiso_citk_pt_eff","PFIso CITK pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_eff_99 = new TH1D("ele_pfiso_simple_pt_eff_99","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_eff_99 = new TH1D("ele_pfiso_effarea_pt_eff_99","PFIso Effective Area pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_eff_99 = new TH1D("ele_pfiso_deltabeta_pt_eff_99","PFIso Delta Beta pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_eff_99 = new TH1D("ele_pfiso_puppi_pt_eff_99","PFIso PUPPI pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_eff_99 = new TH1D("ele_pfiso_puppinl_pt_eff_99","PFIso PUPPI No Leptons pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_eff_99 = new TH1D("ele_pfiso_citk_pt_eff_99","PFIso CITK pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_eff_99_bkg = new TH1D("ele_pfiso_simple_pt_eff_99_bkg","PFIso Simple pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_eff_99_bkg = new TH1D("ele_pfiso_effarea_pt_eff_99_bkg","PFIso Effective Area pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_eff_99_bkg = new TH1D("ele_pfiso_deltabeta_pt_eff_99_bkg","PFIso Delta Beta pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_eff_99_bkg = new TH1D("ele_pfiso_puppi_pt_eff_99_bkg","PFIso PUPPI pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_eff_99_bkg = new TH1D("ele_pfiso_puppinl_pt_eff_99_bkg","PFIso PUPPI No Leptons pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_eff_99_bkg = new TH1D("ele_pfiso_citk_pt_eff_99_bkg","PFIso CITK pT;p_{T};Background Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_eff_95 = new TH1D("ele_pfiso_simple_pt_eff_95","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_eff_95 = new TH1D("ele_pfiso_effarea_pt_eff_95","PFIso Effective Area pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_eff_95 = new TH1D("ele_pfiso_deltabeta_pt_eff_95","PFIso Delta Beta pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_eff_95 = new TH1D("ele_pfiso_puppi_pt_eff_95","PFIso PUPPI pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_eff_95 = new TH1D("ele_pfiso_puppinl_pt_eff_95","PFIso PUPPI No Leptons pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_eff_95 = new TH1D("ele_pfiso_citk_pt_eff_95","PFIso CITK pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_eff_95_bkg = new TH1D("ele_pfiso_simple_pt_eff_95_bkg","PFIso Simple pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_eff_95_bkg = new TH1D("ele_pfiso_effarea_pt_eff_95_bkg","PFIso Effective Area pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_eff_95_bkg = new TH1D("ele_pfiso_deltabeta_pt_eff_95_bkg","PFIso Delta Beta pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_eff_95_bkg = new TH1D("ele_pfiso_puppi_pt_eff_95_bkg","PFIso PUPPI pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_eff_95_bkg = new TH1D("ele_pfiso_puppinl_pt_eff_95_bkg","PFIso PUPPI No Leptons pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_eff_95_bkg = new TH1D("ele_pfiso_citk_pt_eff_95_bkg","PFIso CITK pT;p_{T};Background Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_eff_90 = new TH1D("ele_pfiso_simple_pt_eff_90","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_eff_90 = new TH1D("ele_pfiso_effarea_pt_eff_90","PFIso Effective Area pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_eff_90 = new TH1D("ele_pfiso_deltabeta_pt_eff_90","PFIso Delta Beta pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_eff_90 = new TH1D("ele_pfiso_puppi_pt_eff_90","PFIso PUPPI pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_eff_90 = new TH1D("ele_pfiso_puppinl_pt_eff_90","PFIso PUPPI No Leptons pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_eff_90 = new TH1D("ele_pfiso_citk_pt_eff_90","PFIso CITK pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_eff_90_bkg = new TH1D("ele_pfiso_simple_pt_eff_90_bkg","PFIso Simple pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_eff_90_bkg = new TH1D("ele_pfiso_effarea_pt_eff_90_bkg","PFIso Effective Area pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_eff_90_bkg = new TH1D("ele_pfiso_deltabeta_pt_eff_90_bkg","PFIso Delta Beta pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_eff_90_bkg = new TH1D("ele_pfiso_puppi_pt_eff_90_bkg","PFIso PUPPI pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_eff_90_bkg = new TH1D("ele_pfiso_puppinl_pt_eff_90_bkg","PFIso PUPPI No Leptons pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_eff_90_bkg = new TH1D("ele_pfiso_citk_pt_eff_90_bkg","PFIso CITK pT;p_{T};Background Efficiency",pt_nbins,pt_bins);


TH1D *ele_pfiso_simple_pt_bkg = new TH1D("ele_pfiso_simple_pt_bkg","PFIso Simple pT;p_{T};Backgroung Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_bkg = new TH1D("ele_pfiso_effarea_pt_bkg","PFIso Effective Area pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_bkg = new TH1D("ele_pfiso_deltabeta_pt_bkg","PFIso Delta Beta pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_bkg = new TH1D("ele_pfiso_puppi_pt_bkg","PFIso PUPPI pT;p_{T};Backgroung Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_bkg = new TH1D("ele_pfiso_puppinl_pt_bkg","PFIso PUPPI No Leptons pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_bkg = new TH1D("ele_pfiso_citk_pt_bkg","PFIso CITK pT;p_{T};Background Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_bkg_05 = new TH1D("ele_pfiso_simple_pt_bkg_05","PFIso Simple pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_bkg_05 = new TH1D("ele_pfiso_effarea_pt_bkg_05","PFIso Effective Area pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_bkg_05 = new TH1D("ele_pfiso_deltabeta_pt_bkg_05","PFIso Delta Beta pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_bkg_05 = new TH1D("ele_pfiso_puppi_pt_bkg_05","PFIso PUPPI pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_bkg_05 = new TH1D("ele_pfiso_puppinl_pt_bkg_05","PFIso PUPPI No Leptons pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_bkg_05 = new TH1D("ele_pfiso_citk_pt_bkg_05","PFIso CITK pT;p_{T};Background Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_bkg_05_eff = new TH1D("ele_pfiso_simple_pt_bkg_05_eff","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_bkg_05_eff = new TH1D("ele_pfiso_effarea_pt_bkg_05_eff","PFIso Effective Area pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_bkg_05_eff = new TH1D("ele_pfiso_deltabeta_pt_bkg_05_eff","PFIso Delta Beta pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_bkg_05_eff = new TH1D("ele_pfiso_puppi_pt_bkg_05_eff","PFIso PUPPI pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_bkg_05_eff = new TH1D("ele_pfiso_puppinl_pt_bkg_05_eff","PFIso PUPPI No Leptons pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_bkg_05_eff = new TH1D("ele_pfiso_citk_pt_bkg_05_eff","PFIso CITK pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_bkg_10 = new TH1D("ele_pfiso_simple_pt_bkg_10","PFIso Simple pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_bkg_10 = new TH1D("ele_pfiso_effarea_pt_bkg_10","PFIso Effective Area pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_bkg_10 = new TH1D("ele_pfiso_deltabeta_pt_bkg_10","PFIso Delta Beta pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_bkg_10 = new TH1D("ele_pfiso_puppi_pt_bkg_10","PFIso PUPPI pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_bkg_10 = new TH1D("ele_pfiso_puppinl_pt_bkg_10","PFIso PUPPI No Leptons pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_bkg_10 = new TH1D("ele_pfiso_citk_pt_bkg_10","PFIso CITK pT;p_{T};Background Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_bkg_10_eff = new TH1D("ele_pfiso_simple_pt_bkg_10_eff","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_bkg_10_eff = new TH1D("ele_pfiso_effarea_pt_bkg_10_eff","PFIso Effective Area pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_bkg_10_eff = new TH1D("ele_pfiso_deltabeta_pt_bkg_10_eff","PFIso Delta Beta pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_bkg_10_eff = new TH1D("ele_pfiso_puppi_pt_bkg_10_eff","PFIso PUPPI pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_bkg_10_eff = new TH1D("ele_pfiso_puppinl_pt_bkg_10_eff","PFIso PUPPI No Leptons pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_bkg_10_eff = new TH1D("ele_pfiso_citk_pt_bkg_10_eff","PFIso CITK pT;p_{T};Signals Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_bkg_15 = new TH1D("ele_pfiso_simple_pt_bkg_15","PFIso Simple pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_bkg_15 = new TH1D("ele_pfiso_effarea_pt_bkg_15","PFIso Effective Area pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_bkg_15 = new TH1D("ele_pfiso_deltabeta_pt_bkg_15","PFIso Delta Beta pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_bkg_15 = new TH1D("ele_pfiso_puppi_pt_bkg_15","PFIso PUPPI pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_bkg_15 = new TH1D("ele_pfiso_puppinl_pt_bkg_15","PFIso PUPPI No Leptons pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_bkg_15 = new TH1D("ele_pfiso_citk_pt_bkg_15","PFIso CITK pT;p_{T};Background Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_bkg_15_eff = new TH1D("ele_pfiso_simple_pt_bkg_15_eff","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_bkg_15_eff = new TH1D("ele_pfiso_effarea_pt_bkg_15_eff","PFIso Effective Area pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_bkg_15_eff = new TH1D("ele_pfiso_deltabeta_pt_bkg_15_eff","PFIso Delta Beta pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_bkg_15_eff = new TH1D("ele_pfiso_puppi_pt_bkg_15_eff","PFIso PUPPI pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_bkg_15_eff = new TH1D("ele_pfiso_puppinl_pt_bkg_15_eff","PFIso PUPPI No Leptons pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_bkg_15_eff = new TH1D("ele_pfiso_citk_pt_bkg_15_eff","PFIso CITK pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_ratio = new TH1D("ele_pfiso_simple_pt_ratio","PFIso Simple pT;p_{T};Signal/Backgroung",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_ratio = new TH1D("ele_pfiso_effarea_pt_ratio","PFIso Simple pT;p_{T};Signal/Background",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_ratio = new TH1D("ele_pfiso_deltabeta_pt_ratio","PFIso Simple pT;p_{T};Signal/Background",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_ratio = new TH1D("ele_pfiso_puppi_pt_ratio","PFIso PUPPI pT;p_{T};Signal/Backgroung",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_ratio = new TH1D("ele_pfiso_puppinl_pt_ratio","PFIso PUPPI No Leptons pT;p_{T};Signal/Background",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_ratio = new TH1D("ele_pfiso_citk_pt_ratio","PFIso CITK pT;p_{T};Signal/Background",pt_nbins,pt_bins);

  //declaring matrices and arrays
   double isolation_simple_pt[samples][10];
   double isolation_simple_pt_eff_99[10], isolation_simple_pt_eff_95[10], isolation_simple_pt_eff_90[10];
   double isolation_simple_pt_eff_99_bkg[10], isolation_simple_pt_eff_95_bkg[10], isolation_simple_pt_eff_90_bkg[10];
   double isolation_simple_pt_bkg_05[10], isolation_simple_pt_bkg_10[10], isolation_simple_pt_bkg_15[10];
   double isolation_simple_pt_bkg_05_eff[10], isolation_simple_pt_bkg_10_eff[10], isolation_simple_pt_bkg_15_eff[10];
   
   double isolation_effarea_pt[samples][10];
   double isolation_effarea_pt_eff_99[10], isolation_effarea_pt_eff_95[10], isolation_effarea_pt_eff_90[10];
   double isolation_effarea_pt_bkg_05[10], isolation_effarea_pt_bkg_10[10], isolation_effarea_pt_bkg_15[10];
   double isolation_effarea_pt_eff_99_bkg[10], isolation_effarea_pt_eff_95_bkg[10], isolation_effarea_pt_eff_90_bkg[10];
   double isolation_effarea_pt_bkg_05_eff[10], isolation_effarea_pt_bkg_10_eff[10], isolation_effarea_pt_bkg_15_eff[10];
   
   double isolation_deltabeta_pt[samples][10];
   double isolation_deltabeta_pt_eff_99[10], isolation_deltabeta_pt_eff_95[10], isolation_deltabeta_pt_eff_90[10];
   double isolation_deltabeta_pt_bkg_05[10], isolation_deltabeta_pt_bkg_10[10], isolation_deltabeta_pt_bkg_15[10];
   double isolation_deltabeta_pt_eff_99_bkg[10], isolation_deltabeta_pt_eff_95_bkg[10], isolation_deltabeta_pt_eff_90_bkg[10];
   double isolation_deltabeta_pt_bkg_05_eff[10], isolation_deltabeta_pt_bkg_10_eff[10], isolation_deltabeta_pt_bkg_15_eff[10];
   
   double isolation_puppi_pt[samples][10];
   double isolation_puppi_pt_eff_99[10], isolation_puppi_pt_eff_95[10], isolation_puppi_pt_eff_90[10];
   double isolation_puppi_pt_bkg_05[10], isolation_puppi_pt_bkg_10[10], isolation_puppi_pt_bkg_15[10];
   double isolation_puppi_pt_eff_99_bkg[10], isolation_puppi_pt_eff_95_bkg[10], isolation_puppi_pt_eff_90_bkg[10];
   double isolation_puppi_pt_bkg_05_eff[10], isolation_puppi_pt_bkg_10_eff[10], isolation_puppi_pt_bkg_15_eff[10];
   
   double isolation_puppinl_pt[samples][10];
   double isolation_puppinl_pt_eff_99[10], isolation_puppinl_pt_eff_95[10], isolation_puppinl_pt_eff_90[10];
   double isolation_puppinl_pt_bkg_05[10], isolation_puppinl_pt_bkg_10[10], isolation_puppinl_pt_bkg_15[10];
   double isolation_puppinl_pt_eff_99_bkg[10], isolation_puppinl_pt_eff_95_bkg[10], isolation_puppinl_pt_eff_90_bkg[10];
   double isolation_puppinl_pt_bkg_05_eff[10], isolation_puppinl_pt_bkg_10_eff[10], isolation_puppinl_pt_bkg_15_eff[10];

   double isolation_citk_pt[samples][10];
   double isolation_citk_pt_eff_99[10], isolation_citk_pt_eff_95[10], isolation_citk_pt_eff_90[10];
   double isolation_citk_pt_bkg_05[10], isolation_citk_pt_bkg_10[10], isolation_citk_pt_bkg_15[10];
   double isolation_citk_pt_eff_99_bkg[10], isolation_citk_pt_eff_95_bkg[10], isolation_citk_pt_eff_90_bkg[10];
   double isolation_citk_pt_bkg_05_eff[10], isolation_citk_pt_bkg_10_eff[10], isolation_citk_pt_bkg_15_eff[10];

for (int s = 0; s <= 1; ++s)
{
   for (int y=0; y<10; ++y)
	{
	isolation_simple_pt[s][y] = 0;
	isolation_effarea_pt[s][y] = 0;
	isolation_deltabeta_pt[s][y] = 0;
	isolation_puppi_pt[s][y] = 0;
	isolation_puppinl_pt[s][y] = 0;
	isolation_citk_pt[s][y] = 0;
	}
}


   for (int y=0; y<10; ++y)
	{
	isolation_simple_pt_eff_90[y] = 0;
	isolation_simple_pt_eff_95[y] = 0;
	isolation_simple_pt_eff_99[y] = 0;
	isolation_simple_pt_bkg_05[y] = 0;
	isolation_simple_pt_bkg_10[y] = 0;
	isolation_simple_pt_bkg_15[y] = 0;
	isolation_effarea_pt_eff_90[y] = 0;
	isolation_effarea_pt_eff_95[y] = 0;
	isolation_effarea_pt_eff_99[y] = 0;
	isolation_effarea_pt_bkg_05[y] = 0;
	isolation_effarea_pt_bkg_10[y] = 0;
	isolation_effarea_pt_bkg_15[y] = 0;
	isolation_deltabeta_pt_eff_90[y] = 0;
	isolation_deltabeta_pt_eff_95[y] = 0;
	isolation_deltabeta_pt_eff_99[y] = 0;
	isolation_deltabeta_pt_bkg_05[y] = 0;
	isolation_deltabeta_pt_bkg_10[y] = 0;
	isolation_deltabeta_pt_bkg_15[y] = 0;
	isolation_puppi_pt_eff_90[y] = 0;
	isolation_puppi_pt_eff_95[y] = 0;
	isolation_puppi_pt_eff_99[y] = 0;
	isolation_puppi_pt_bkg_05[y] = 0;
	isolation_puppi_pt_bkg_10[y] = 0;
	isolation_puppi_pt_bkg_15[y] = 0;
	isolation_puppinl_pt_eff_90[y] = 0;
	isolation_puppinl_pt_eff_95[y] = 0;
	isolation_puppinl_pt_eff_99[y] = 0;
	isolation_puppinl_pt_bkg_05[y] = 0;
	isolation_puppinl_pt_bkg_10[y] = 0;
	isolation_puppinl_pt_bkg_15[y] = 0;
	isolation_citk_pt_eff_90[y] = 0;
	isolation_citk_pt_eff_95[y] = 0;
	isolation_citk_pt_eff_99[y] = 0;
	isolation_citk_pt_bkg_05[y] = 0;
	isolation_citk_pt_bkg_10[y] = 0;
	isolation_citk_pt_bkg_15[y] = 0;

	isolation_simple_pt_eff_90_bkg[y] = 0;
	isolation_simple_pt_eff_95_bkg[y] = 0;
	isolation_simple_pt_eff_99_bkg[y] = 0;
	isolation_simple_pt_bkg_05_eff[y] = 0;
	isolation_simple_pt_bkg_10_eff[y] = 0;
	isolation_simple_pt_bkg_15_eff[y] = 0;
	isolation_effarea_pt_eff_90_bkg[y] = 0;
	isolation_effarea_pt_eff_95_bkg[y] = 0;
	isolation_effarea_pt_eff_99_bkg[y] = 0;
	isolation_effarea_pt_bkg_05_eff[y] = 0;
	isolation_effarea_pt_bkg_10_eff[y] = 0;
	isolation_effarea_pt_bkg_15_eff[y] = 0;
	isolation_deltabeta_pt_eff_90_bkg[y] = 0;
	isolation_deltabeta_pt_eff_95_bkg[y] = 0;
	isolation_deltabeta_pt_eff_99_bkg[y] = 0;
	isolation_deltabeta_pt_bkg_05_eff[y] = 0;
	isolation_deltabeta_pt_bkg_10_eff[y] = 0;
	isolation_deltabeta_pt_bkg_15_eff[y] = 0;
	isolation_puppi_pt_eff_90_bkg[y] = 0;
	isolation_puppi_pt_eff_95_bkg[y] = 0;
	isolation_puppi_pt_eff_99_bkg[y] = 0;
	isolation_puppi_pt_bkg_05_eff[y] = 0;
	isolation_puppi_pt_bkg_10_eff[y] = 0;
	isolation_puppi_pt_bkg_15_eff[y] = 0;
	isolation_puppinl_pt_eff_90_bkg[y] = 0;
	isolation_puppinl_pt_eff_95_bkg[y] = 0;
	isolation_puppinl_pt_eff_99_bkg[y] = 0;
	isolation_puppinl_pt_bkg_05_eff[y] = 0;
	isolation_puppinl_pt_bkg_10_eff[y] = 0;
	isolation_puppinl_pt_bkg_15_eff[y] = 0;
	isolation_citk_pt_eff_90_bkg[y] = 0;
	isolation_citk_pt_eff_95_bkg[y] = 0;
	isolation_citk_pt_eff_99_bkg[y] = 0;
	isolation_citk_pt_bkg_05_eff[y] = 0;
	isolation_citk_pt_bkg_10_eff[y] = 0;
	isolation_citk_pt_bkg_15_eff[y] = 0;
	}

  //Iso Simple VS pt
  TH2D *iso_simple_vs_pt1 = 0;
  TH2D *iso_simple_vs_pt2 = 0;

  f1->GetObject("iso_simple_vs_pt",iso_simple_vs_pt1);
  if (iso_simple_vs_pt1 == 0) { cout << "iso_simple_vs_pt not found!" << endl; return; }
  f2->GetObject("iso_simple_vs_pt",iso_simple_vs_pt2);
  if (iso_simple_vs_pt2 == 0) { cout << "iso_simple_vs_pt not found!" << endl; return; }


plot_2dhistogram(iso_simple_vs_pt1, "output/", prefix[0] + "_iso_simple_vs_pt", prefix[0], "top_right", true);
plot_2dhistogram(iso_simple_vs_pt2, "output/", prefix[1] + "_iso_simple_vs_pt", prefix[1], "top_right", true);

  //Iso Effective Area VS pt
  TH2D *iso_effarea_vs_pt1 = 0;
  TH2D *iso_effarea_vs_pt2 = 0;

  f1->GetObject("iso_effarea_vs_pt",iso_effarea_vs_pt1);
  if (iso_effarea_vs_pt1 == 0) { cout << "iso_effarea_vs_pt not found!" << endl; return; }
  f2->GetObject("iso_effarea_vs_pt",iso_effarea_vs_pt2);
  if (iso_effarea_vs_pt2 == 0) { cout << "iso_effarea_vs_pt not found!" << endl; return; }


plot_2dhistogram(iso_effarea_vs_pt1, "output/", prefix[0] + "_iso_effarea_vs_pt", prefix[0], "top_right", true);
plot_2dhistogram(iso_effarea_vs_pt2, "output/", prefix[1] + "_iso_effarea_vs_pt", prefix[1], "top_right", true);

  //Iso Delta Beta VS pt
  TH2D *iso_deltabeta_vs_pt1 = 0;
  TH2D *iso_deltabeta_vs_pt2 = 0;

  f1->GetObject("iso_deltabeta_vs_pt",iso_deltabeta_vs_pt1);
  if (iso_deltabeta_vs_pt1 == 0) { cout << "iso_deltabeta_vs_pt not found!" << endl; return; }
  f2->GetObject("iso_deltabeta_vs_pt",iso_deltabeta_vs_pt2);
  if (iso_deltabeta_vs_pt2 == 0) { cout << "iso_deltabeta_vs_pt not found!" << endl; return; }


plot_2dhistogram(iso_deltabeta_vs_pt1, "output/", prefix[0] + "_iso_deltabeta_vs_pt", prefix[0], "top_right", true);
plot_2dhistogram(iso_deltabeta_vs_pt2, "output/", prefix[1] + "_iso_deltabeta_vs_pt", prefix[1], "top_right", true);

  //Iso PUPPI VS pt
  TH2D *iso_puppi_vs_pt1 = 0;
  TH2D *iso_puppi_vs_pt2 = 0;

  f1->GetObject("iso_puppi_vs_pt",iso_puppi_vs_pt1);
  if (iso_puppi_vs_pt1 == 0) { cout << "iso_puppi_vs_pt not found!" << endl; return; }
  f2->GetObject("iso_puppi_vs_pt",iso_puppi_vs_pt2);
  if (iso_puppi_vs_pt2 == 0) { cout << "iso_puppi_vs_pt not found!" << endl; return; }


plot_2dhistogram(iso_puppi_vs_pt1, "output/", prefix[0] + "_iso_puppi_vs_pt", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppi_vs_pt2, "output/", prefix[1] + "_iso_puppi_vs_pt", prefix[1], "top_right", true);

  //Iso PUPPI No Leptons VS pt
  TH2D *iso_puppinl_vs_pt1 = 0;
  TH2D *iso_puppinl_vs_pt2 = 0;

  f1->GetObject("iso_puppinl_vs_pt",iso_puppinl_vs_pt1);
  if (iso_puppinl_vs_pt1 == 0) { cout << "iso_puppinl_vs_pt not found!" << endl; return; }
  f2->GetObject("iso_puppinl_vs_pt",iso_puppinl_vs_pt2);
  if (iso_puppinl_vs_pt2 == 0) { cout << "iso_puppinl_vs_pt not found!" << endl; return; }


plot_2dhistogram(iso_puppinl_vs_pt1, "output/", prefix[0] + "_iso_puppinl_vs_pt", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppinl_vs_pt2, "output/", prefix[1] + "_iso_puppinl_vs_pt", prefix[1], "top_right", true);

  //Iso citk VS pt
  TH2D *iso_citk_vs_pt1 = 0;
  TH2D *iso_citk_vs_pt2 = 0;

  f1->GetObject("iso_citk_vs_pt",iso_citk_vs_pt1);
  if (iso_citk_vs_pt1 == 0) { cout << "iso_citk_vs_pt not found!" << endl; return; }
  f2->GetObject("iso_citk_vs_pt",iso_citk_vs_pt2);
  if (iso_citk_vs_pt2 == 0) { cout << "iso_citk_vs_pt not found!" << endl; return; }


plot_2dhistogram(iso_citk_vs_pt1, "output/", prefix[0] + "_iso_citk_vs_pt", prefix[0], "top_right", true);
plot_2dhistogram(iso_citk_vs_pt2, "output/", prefix[1] + "_iso_citk_vs_pt", prefix[1], "top_right", true);


  //compute the differential distributions
  int nbins = iso_simple_vs_pt1->GetNbinsY();

for (int x = 1; x <= nbins; x++)
	{
	isolation_simple_pt[0][x-1] = iso_simple_vs_pt1->Integral(0,working_point,x,x)/iso_simple_vs_pt1->Integral(0,2000,x,x);
	isolation_effarea_pt[0][x-1] = iso_effarea_vs_pt1->Integral(0,working_point,x,x)/iso_effarea_vs_pt1->Integral(0,2000,x,x);
	isolation_deltabeta_pt[0][x-1] = iso_deltabeta_vs_pt1->Integral(0,working_point,x,x)/iso_deltabeta_vs_pt1->Integral(0,2000,x,x);
	isolation_puppi_pt[0][x-1] = iso_puppi_vs_pt1->Integral(0,working_point,x,x)/iso_puppi_vs_pt1->Integral(0,2000,x,x);
	isolation_puppinl_pt[0][x-1] = iso_puppinl_vs_pt1->Integral(0,working_point,x,x)/iso_puppinl_vs_pt1->Integral(0,2000,x,x);
	isolation_citk_pt[0][x-1] = iso_citk_vs_pt1->Integral(0,working_point,x,x)/iso_citk_vs_pt1->Integral(0,2000,x,x);

	isolation_simple_pt[1][x-1] = iso_simple_vs_pt2->Integral(0,working_point,x,x)/iso_simple_vs_pt2->Integral(0,2000,x,x);
	isolation_effarea_pt[1][x-1] = iso_effarea_vs_pt2->Integral(0,working_point,x,x)/iso_effarea_vs_pt2->Integral(0,2000,x,x);
	isolation_deltabeta_pt[1][x-1] = iso_deltabeta_vs_pt2->Integral(0,working_point,x,x)/iso_deltabeta_vs_pt2->Integral(0,2000,x,x);
	isolation_puppi_pt[1][x-1] = iso_puppi_vs_pt2->Integral(0,working_point,x,x)/iso_puppi_vs_pt2->Integral(0,2000,x,x);
	isolation_puppinl_pt[1][x-1] = iso_puppinl_vs_pt2->Integral(0,working_point,x,x)/iso_puppinl_vs_pt2->Integral(0,2000,x,x);
	isolation_citk_pt[1][x-1] = iso_citk_vs_pt2->Integral(0,working_point,x,x)/iso_citk_vs_pt2->Integral(0,2000,x,x);
	}



for (int x = 1; x <= 2000; x++)
	{
	if (iso_simple_vs_pt2->Integral(0,x,1,nbins)/iso_simple_vs_pt2->Integral(0,2000,1,nbins) > .99 and isolation_simple_pt_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found 99% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_pt_eff_99[y-1] = iso_simple_vs_pt2->Integral(0,x,y,y)/iso_simple_vs_pt2->Integral(0,2000,y,y);
			isolation_simple_pt_eff_99_bkg[y-1] = iso_simple_vs_pt1->Integral(0,x,y,y)/iso_simple_vs_pt1->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_simple_pt_eff_99[y-1] << endl; }
			}
		}
	if (iso_simple_vs_pt2->Integral(0,x,1,nbins)/iso_simple_vs_pt2->Integral(0,2000,1,nbins) > .95 and isolation_simple_pt_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found 95% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_pt_eff_95[y-1] = iso_simple_vs_pt2->Integral(0,x,y,y)/iso_simple_vs_pt2->Integral(0,2000,y,y);
			isolation_simple_pt_eff_95_bkg[y-1] = iso_simple_vs_pt1->Integral(0,x,y,y)/iso_simple_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_simple_vs_pt2->Integral(0,x,1,nbins)/iso_simple_vs_pt2->Integral(0,2000,1,nbins) > .90 and isolation_simple_pt_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found 90% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_pt_eff_90[y-1] = iso_simple_vs_pt2->Integral(0,x,y,y)/iso_simple_vs_pt2->Integral(0,2000,y,y);
			isolation_simple_pt_eff_90_bkg[y-1] = iso_simple_vs_pt1->Integral(0,x,y,y)/iso_simple_vs_pt1->Integral(0,2000,y,y);
			}
		}

	if (iso_effarea_vs_pt2->Integral(0,x,1,nbins)/iso_effarea_vs_pt2->Integral(0,2000,1,nbins) > .99 and isolation_effarea_pt_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found 99% effeciency point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_pt_eff_99[y-1] = iso_effarea_vs_pt2->Integral(0,x,y,y)/iso_effarea_vs_pt2->Integral(0,2000,y,y);
			isolation_effarea_pt_eff_99_bkg[y-1] = iso_effarea_vs_pt1->Integral(0,x,y,y)/iso_effarea_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_effarea_vs_pt2->Integral(0,x,1,nbins)/iso_effarea_vs_pt2->Integral(0,2000,1,nbins) > .95 and isolation_effarea_pt_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found 95% effeciency point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_pt_eff_95[y-1] = iso_effarea_vs_pt2->Integral(0,x,y,y)/iso_effarea_vs_pt2->Integral(0,2000,y,y);
			isolation_effarea_pt_eff_95_bkg[y-1] = iso_effarea_vs_pt1->Integral(0,x,y,y)/iso_effarea_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_effarea_vs_pt2->Integral(0,x,1,nbins)/iso_effarea_vs_pt2->Integral(0,2000,1,nbins) > .90 and isolation_effarea_pt_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found 90% effeciency point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_pt_eff_90[y-1] = iso_effarea_vs_pt2->Integral(0,x,y,y)/iso_effarea_vs_pt2->Integral(0,2000,y,y);
			isolation_effarea_pt_eff_90_bkg[y-1] = iso_effarea_vs_pt1->Integral(0,x,y,y)/iso_effarea_vs_pt1->Integral(0,2000,y,y);
			}
		}


	if (iso_deltabeta_vs_pt2->Integral(0,x,1,nbins)/iso_deltabeta_vs_pt2->Integral(0,2000,1,nbins) > .99 and isolation_deltabeta_pt_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found 99% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_pt_eff_99[y-1] = iso_deltabeta_vs_pt2->Integral(0,x,y,y)/iso_deltabeta_vs_pt2->Integral(0,2000,y,y);
			isolation_deltabeta_pt_eff_99_bkg[y-1] = iso_deltabeta_vs_pt1->Integral(0,x,y,y)/iso_deltabeta_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_deltabeta_vs_pt2->Integral(0,x,1,nbins)/iso_deltabeta_vs_pt2->Integral(0,2000,1,nbins) > .95 and isolation_deltabeta_pt_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found 95% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_pt_eff_95[y-1] = iso_deltabeta_vs_pt2->Integral(0,x,y,y)/iso_deltabeta_vs_pt2->Integral(0,2000,y,y);
			isolation_deltabeta_pt_eff_95_bkg[y-1] = iso_deltabeta_vs_pt1->Integral(0,x,y,y)/iso_deltabeta_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_deltabeta_vs_pt2->Integral(0,x,1,nbins)/iso_deltabeta_vs_pt2->Integral(0,2000,1,nbins) > .90 and isolation_deltabeta_pt_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found 90% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_pt_eff_90[y-1] = iso_deltabeta_vs_pt2->Integral(0,x,y,y)/iso_deltabeta_vs_pt2->Integral(0,2000,y,y);
			isolation_deltabeta_pt_eff_90_bkg[y-1] = iso_deltabeta_vs_pt1->Integral(0,x,y,y)/iso_deltabeta_vs_pt1->Integral(0,2000,y,y);
			}
		}

	if (iso_puppi_vs_pt2->Integral(0,x,1,nbins)/iso_puppi_vs_pt2->Integral(0,2000,1,nbins) > .99 and isolation_puppi_pt_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found 99% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_pt_eff_99[y-1] = iso_puppi_vs_pt2->Integral(0,x,y,y)/iso_puppi_vs_pt2->Integral(0,2000,y,y);
			isolation_puppi_pt_eff_99_bkg[y-1] = iso_puppi_vs_pt1->Integral(0,x,y,y)/iso_puppi_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_puppi_vs_pt2->Integral(0,x,1,nbins)/iso_puppi_vs_pt2->Integral(0,2000,1,nbins) > .95 and isolation_puppi_pt_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found 95% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_pt_eff_95[y-1] = iso_puppi_vs_pt2->Integral(0,x,y,y)/iso_puppi_vs_pt2->Integral(0,2000,y,y);
			isolation_puppi_pt_eff_95_bkg[y-1] = iso_puppi_vs_pt1->Integral(0,x,y,y)/iso_puppi_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_puppi_vs_pt2->Integral(0,x,1,nbins)/iso_puppi_vs_pt2->Integral(0,2000,1,nbins) > .90 and isolation_puppi_pt_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found 90% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_pt_eff_90[y-1] = iso_puppi_vs_pt2->Integral(0,x,y,y)/iso_puppi_vs_pt2->Integral(0,2000,y,y);
			isolation_puppi_pt_eff_90_bkg[y-1] = iso_puppi_vs_pt1->Integral(0,x,y,y)/iso_puppi_vs_pt1->Integral(0,2000,y,y);
			}
		}

	if (iso_puppinl_vs_pt2->Integral(0,x,1,nbins)/iso_puppinl_vs_pt2->Integral(0,2000,1,nbins) > .99 and isolation_puppinl_pt_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found 99% effeciency point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_pt_eff_99[y-1] = iso_puppinl_vs_pt2->Integral(0,x,y,y)/iso_puppinl_vs_pt2->Integral(0,2000,y,y);
			isolation_puppinl_pt_eff_99_bkg[y-1] = iso_puppinl_vs_pt1->Integral(0,x,y,y)/iso_puppinl_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_puppinl_vs_pt2->Integral(0,x,1,nbins)/iso_puppinl_vs_pt2->Integral(0,2000,1,nbins) > .95 and isolation_puppinl_pt_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found 95% effeciency point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_pt_eff_95[y-1] = iso_puppinl_vs_pt2->Integral(0,x,y,y)/iso_puppinl_vs_pt2->Integral(0,2000,y,y);
			isolation_puppinl_pt_eff_95_bkg[y-1] = iso_puppinl_vs_pt1->Integral(0,x,y,y)/iso_puppinl_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_puppinl_vs_pt2->Integral(0,x,1,nbins)/iso_puppinl_vs_pt2->Integral(0,2000,1,nbins) > .90 and isolation_puppinl_pt_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found 90% effeciency point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_pt_eff_90[y-1] = iso_puppinl_vs_pt2->Integral(0,x,y,y)/iso_puppinl_vs_pt2->Integral(0,2000,y,y);
			isolation_puppinl_pt_eff_90_bkg[y-1] = iso_puppinl_vs_pt1->Integral(0,x,y,y)/iso_puppinl_vs_pt1->Integral(0,2000,y,y);
			}
		}


	if (iso_citk_vs_pt2->Integral(0,x,1,nbins)/iso_citk_vs_pt2->Integral(0,2000,1,nbins) > .99 and isolation_citk_pt_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found 99% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_pt_eff_99[y-1] = iso_citk_vs_pt2->Integral(0,x,y,y)/iso_citk_vs_pt2->Integral(0,2000,y,y);
			isolation_citk_pt_eff_99_bkg[y-1] = iso_citk_vs_pt1->Integral(0,x,y,y)/iso_citk_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_citk_vs_pt2->Integral(0,x,1,nbins)/iso_citk_vs_pt2->Integral(0,2000,1,nbins) > .95 and isolation_citk_pt_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found 95% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_pt_eff_95[y-1] = iso_citk_vs_pt2->Integral(0,x,y,y)/iso_citk_vs_pt2->Integral(0,2000,y,y);
			isolation_citk_pt_eff_95_bkg[y-1] = iso_citk_vs_pt1->Integral(0,x,y,y)/iso_citk_vs_pt1->Integral(0,2000,y,y);
			}
		}
	if (iso_citk_vs_pt2->Integral(0,x,1,nbins)/iso_citk_vs_pt2->Integral(0,2000,1,nbins) > .90 and isolation_citk_pt_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found 90% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_pt_eff_90[y-1] = iso_citk_vs_pt2->Integral(0,x,y,y)/iso_citk_vs_pt2->Integral(0,2000,y,y);
			isolation_citk_pt_eff_90_bkg[y-1] = iso_citk_vs_pt1->Integral(0,x,y,y)/iso_citk_vs_pt1->Integral(0,2000,y,y);
			}
		}


	if (iso_simple_vs_pt1->Integral(0,x,1,nbins)/iso_simple_vs_pt1->Integral(0,2000,1,nbins) > .05 and isolation_simple_pt_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found 5% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_pt_bkg_05[y-1] = iso_simple_vs_pt1->Integral(0,x,y,y)/iso_simple_vs_pt1->Integral(0,2000,y,y);
			isolation_simple_pt_bkg_05_eff[y-1] = iso_simple_vs_pt2->Integral(0,x,y,y)/iso_simple_vs_pt2->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_simple_pt_bkg_05[y-1] << endl; }
			}
		}
	if (iso_simple_vs_pt1->Integral(0,x,1,nbins)/iso_simple_vs_pt1->Integral(0,2000,1,nbins) > .10 and isolation_simple_pt_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found 10% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_pt_bkg_10[y-1] = iso_simple_vs_pt1->Integral(0,x,y,y)/iso_simple_vs_pt1->Integral(0,2000,y,y);
			isolation_simple_pt_bkg_10_eff[y-1] = iso_simple_vs_pt2->Integral(0,x,y,y)/iso_simple_vs_pt2->Integral(0,2000,y,y);
			}
		}
	if (iso_simple_vs_pt1->Integral(0,x,1,nbins)/iso_simple_vs_pt1->Integral(0,2000,1,nbins) > .15 and isolation_simple_pt_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found 15% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_pt_bkg_15[y-1] = iso_simple_vs_pt1->Integral(0,x,y,y)/iso_simple_vs_pt1->Integral(0,2000,y,y);
			isolation_simple_pt_bkg_15_eff[y-1] = iso_simple_vs_pt2->Integral(0,x,y,y)/iso_simple_vs_pt2->Integral(0,2000,y,y);
			}
		}

	if (iso_effarea_vs_pt1->Integral(0,x,1,nbins)/iso_effarea_vs_pt1->Integral(0,2000,1,nbins) > .05 and isolation_effarea_pt_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found 5% background point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_pt_bkg_05[y-1] = iso_effarea_vs_pt1->Integral(0,x,y,y)/iso_effarea_vs_pt1->Integral(0,2000,y,y);
			isolation_effarea_pt_bkg_05_eff[y-1] = iso_effarea_vs_pt2->Integral(0,x,y,y)/iso_effarea_vs_pt2->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_effarea_pt_bkg_05[y-1] << endl; }
			}
		}
	if (iso_effarea_vs_pt1->Integral(0,x,1,nbins)/iso_effarea_vs_pt1->Integral(0,2000,1,nbins) > .10 and isolation_effarea_pt_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found 10% background point for the effarea method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_pt_bkg_10[y-1] = iso_effarea_vs_pt1->Integral(0,x,y,y)/iso_effarea_vs_pt1->Integral(0,2000,y,y);
			isolation_effarea_pt_bkg_10_eff[y-1] = iso_effarea_vs_pt2->Integral(0,x,y,y)/iso_effarea_vs_pt2->Integral(0,2000,y,y);
			}
		}
	if (iso_effarea_vs_pt1->Integral(0,x,1,nbins)/iso_effarea_vs_pt1->Integral(0,2000,1,nbins) > .15 and isolation_effarea_pt_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found 15% background point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_pt_bkg_15[y-1] = iso_effarea_vs_pt1->Integral(0,x,y,y)/iso_effarea_vs_pt1->Integral(0,2000,y,y);
			isolation_effarea_pt_bkg_15_eff[y-1] = iso_effarea_vs_pt2->Integral(0,x,y,y)/iso_effarea_vs_pt2->Integral(0,2000,y,y);
			}
		}


	if (iso_deltabeta_vs_pt1->Integral(0,x,1,nbins)/iso_deltabeta_vs_pt1->Integral(0,2000,1,nbins) > .05 and isolation_deltabeta_pt_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found 5% background point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_pt_bkg_05[y-1] = iso_deltabeta_vs_pt1->Integral(0,x,y,y)/iso_deltabeta_vs_pt1->Integral(0,2000,y,y);
			isolation_deltabeta_pt_bkg_05_eff[y-1] = iso_deltabeta_vs_pt2->Integral(0,x,y,y)/iso_deltabeta_vs_pt2->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_deltabeta_pt_bkg_05[y-1] << endl; }
			}
		}
	if (iso_deltabeta_vs_pt1->Integral(0,x,1,nbins)/iso_deltabeta_vs_pt1->Integral(0,2000,1,nbins) > .10 and isolation_deltabeta_pt_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found 10% background point for the deltabeta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_pt_bkg_10[y-1] = iso_deltabeta_vs_pt1->Integral(0,x,y,y)/iso_deltabeta_vs_pt1->Integral(0,2000,y,y);
			isolation_deltabeta_pt_bkg_10_eff[y-1] = iso_deltabeta_vs_pt2->Integral(0,x,y,y)/iso_deltabeta_vs_pt2->Integral(0,2000,y,y);
			}
		}
	if (iso_deltabeta_vs_pt1->Integral(0,x,1,nbins)/iso_deltabeta_vs_pt1->Integral(0,2000,1,nbins) > .15 and isolation_deltabeta_pt_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found 15% background point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_pt_bkg_15[y-1] = iso_deltabeta_vs_pt1->Integral(0,x,y,y)/iso_deltabeta_vs_pt1->Integral(0,2000,y,y);
			isolation_deltabeta_pt_bkg_15_eff[y-1] = iso_deltabeta_vs_pt2->Integral(0,x,y,y)/iso_deltabeta_vs_pt2->Integral(0,2000,y,y);
			}
		}

if (iso_puppi_vs_pt1->Integral(0,x,1,nbins)/iso_puppi_vs_pt1->Integral(0,2000,1,nbins) > .05 and isolation_puppi_pt_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found 5% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_pt_bkg_05[y-1] = iso_puppi_vs_pt1->Integral(0,x,y,y)/iso_puppi_vs_pt1->Integral(0,2000,y,y);
			isolation_puppi_pt_bkg_05_eff[y-1] = iso_puppi_vs_pt2->Integral(0,x,y,y)/iso_puppi_vs_pt2->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_puppi_pt_bkg_05[y-1] << endl; }
			}
		}
	if (iso_puppi_vs_pt1->Integral(0,x,1,nbins)/iso_puppi_vs_pt1->Integral(0,2000,1,nbins) > .10 and isolation_puppi_pt_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found 10% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_pt_bkg_10[y-1] = iso_puppi_vs_pt1->Integral(0,x,y,y)/iso_puppi_vs_pt1->Integral(0,2000,y,y);
			isolation_puppi_pt_bkg_10_eff[y-1] = iso_puppi_vs_pt2->Integral(0,x,y,y)/iso_puppi_vs_pt2->Integral(0,2000,y,y);
			}
		}
	if (iso_puppi_vs_pt1->Integral(0,x,1,nbins)/iso_puppi_vs_pt1->Integral(0,2000,1,nbins) > .15 and isolation_puppi_pt_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found 15% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_pt_bkg_15[y-1] = iso_puppi_vs_pt1->Integral(0,x,y,y)/iso_puppi_vs_pt1->Integral(0,2000,y,y);
			isolation_puppi_pt_bkg_15_eff[y-1] = iso_puppi_vs_pt2->Integral(0,x,y,y)/iso_puppi_vs_pt2->Integral(0,2000,y,y);
			}
		}


if (iso_puppinl_vs_pt1->Integral(0,x,1,nbins)/iso_puppinl_vs_pt1->Integral(0,2000,1,nbins) > .05 and isolation_puppinl_pt_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found 5% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_pt_bkg_05[y-1] = iso_puppinl_vs_pt1->Integral(0,x,y,y)/iso_puppinl_vs_pt1->Integral(0,2000,y,y);
			isolation_puppinl_pt_bkg_05_eff[y-1] = iso_puppinl_vs_pt2->Integral(0,x,y,y)/iso_puppinl_vs_pt2->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_puppinl_pt_bkg_05[y-1] << endl; }
			}
		}
if (iso_puppinl_vs_pt1->Integral(0,x,1,nbins)/iso_puppinl_vs_pt1->Integral(0,2000,1,nbins) > .10 and isolation_puppinl_pt_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found 10% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_pt_bkg_10[y-1] = iso_puppinl_vs_pt1->Integral(0,x,y,y)/iso_puppinl_vs_pt1->Integral(0,2000,y,y);
			isolation_puppinl_pt_bkg_10_eff[y-1] = iso_puppinl_vs_pt2->Integral(0,x,y,y)/iso_puppinl_vs_pt2->Integral(0,2000,y,y);
			}
		}
if (iso_puppinl_vs_pt1->Integral(0,x,1,nbins)/iso_puppinl_vs_pt1->Integral(0,2000,1,nbins) > .15 and isolation_puppinl_pt_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found 15% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_pt_bkg_15[y-1] = iso_puppinl_vs_pt1->Integral(0,x,y,y)/iso_puppinl_vs_pt1->Integral(0,2000,y,y);
			isolation_puppinl_pt_bkg_15_eff[y-1] = iso_puppinl_vs_pt2->Integral(0,x,y,y)/iso_puppinl_vs_pt2->Integral(0,2000,y,y);
			}
		}

if (iso_citk_vs_pt1->Integral(0,x,1,nbins)/iso_citk_vs_pt1->Integral(0,2000,1,nbins) > .05 and isolation_citk_pt_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found 5% background point for the CITK method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_pt_bkg_05[y-1] = iso_citk_vs_pt1->Integral(0,x,y,y)/iso_citk_vs_pt1->Integral(0,2000,y,y);
			isolation_citk_pt_bkg_05_eff[y-1] = iso_citk_vs_pt2->Integral(0,x,y,y)/iso_citk_vs_pt2->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_citk_pt_bkg_05[y-1] << endl; }
			}
		}
	if (iso_citk_vs_pt1->Integral(0,x,1,nbins)/iso_citk_vs_pt1->Integral(0,2000,1,nbins) > .10 and isolation_citk_pt_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found 10% background point for the CITK method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_pt_bkg_10[y-1] = iso_citk_vs_pt1->Integral(0,x,y,y)/iso_citk_vs_pt1->Integral(0,2000,y,y);
			isolation_citk_pt_bkg_10_eff[y-1] = iso_citk_vs_pt2->Integral(0,x,y,y)/iso_citk_vs_pt2->Integral(0,2000,y,y);
			}
		}
	if (iso_citk_vs_pt1->Integral(0,x,1,nbins)/iso_citk_vs_pt1->Integral(0,2000,1,nbins) > .15 and isolation_citk_pt_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found 15% background point for the CITK method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_pt_bkg_15[y-1] = iso_citk_vs_pt1->Integral(0,x,y,y)/iso_citk_vs_pt1->Integral(0,2000,y,y);
			isolation_citk_pt_bkg_15_eff[y-1] = iso_citk_vs_pt2->Integral(0,x,y,y)/iso_citk_vs_pt2->Integral(0,2000,y,y);
			}
		}

	}


   for (int x=0; x<=9; x++)
	{
	ele_pfiso_simple_pt_eff->SetBinContent(x+1,isolation_simple_pt[1][x]);
	ele_pfiso_effarea_pt_eff->SetBinContent(x+1,isolation_effarea_pt[1][x]);
	ele_pfiso_deltabeta_pt_eff->SetBinContent(x+1,isolation_deltabeta_pt[1][x]);
	ele_pfiso_puppi_pt_eff->SetBinContent(x+1,isolation_puppi_pt[1][x]);
	ele_pfiso_puppinl_pt_eff->SetBinContent(x+1,isolation_puppinl_pt[1][x]);
	ele_pfiso_citk_pt_eff->SetBinContent(x+1,isolation_citk_pt[1][x]);
	ele_pfiso_simple_pt_eff->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_eff->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_eff->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_eff->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_eff->SetBinError(x+1,0);
	ele_pfiso_citk_pt_eff->SetBinError(x+1,0);

	ele_pfiso_simple_pt_bkg->SetBinContent(x+1,isolation_simple_pt[0][x]);
	ele_pfiso_effarea_pt_bkg->SetBinContent(x+1,isolation_effarea_pt[0][x]);
	ele_pfiso_deltabeta_pt_bkg->SetBinContent(x+1,isolation_deltabeta_pt[0][x]);
	ele_pfiso_puppi_pt_bkg->SetBinContent(x+1,isolation_puppi_pt[0][x]);
	ele_pfiso_puppinl_pt_bkg->SetBinContent(x+1,isolation_puppinl_pt[0][x]);
	ele_pfiso_citk_pt_bkg->SetBinContent(x+1,isolation_citk_pt[0][x]);
	ele_pfiso_simple_pt_bkg->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_bkg->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_bkg->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_bkg->SetBinError(x+1,0);
	ele_pfiso_citk_pt_bkg->SetBinError(x+1,0);

	ele_pfiso_simple_pt_ratio->SetBinContent(x+1,isolation_simple_pt[1][x]/isolation_simple_pt[0][x]);
	ele_pfiso_effarea_pt_ratio->SetBinContent(x+1,isolation_effarea_pt[1][x]/isolation_effarea_pt[0][x]);
	ele_pfiso_deltabeta_pt_ratio->SetBinContent(x+1,isolation_deltabeta_pt[1][x]/isolation_deltabeta_pt[0][x]);
	ele_pfiso_puppi_pt_ratio->SetBinContent(x+1,isolation_puppi_pt[1][x]/isolation_puppi_pt[0][x]);
	ele_pfiso_puppinl_pt_ratio->SetBinContent(x+1,isolation_puppinl_pt[1][x]/isolation_puppinl_pt[0][x]);
	ele_pfiso_citk_pt_ratio->SetBinContent(x+1,isolation_citk_pt[1][x]/isolation_citk_pt[0][x]);
	ele_pfiso_simple_pt_ratio->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_ratio->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_ratio->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_ratio->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_ratio->SetBinError(x+1,0);
	ele_pfiso_citk_pt_ratio->SetBinError(x+1,0);

	ele_pfiso_simple_pt_eff_99->SetBinContent(x+1,isolation_simple_pt_eff_99[x]);
	ele_pfiso_simple_pt_eff_99->SetBinError(x+1,0);
	ele_pfiso_simple_pt_eff_95->SetBinContent(x+1,isolation_simple_pt_eff_95[x]);
	ele_pfiso_simple_pt_eff_95->SetBinError(x+1,0);
	ele_pfiso_simple_pt_eff_90->SetBinContent(x+1,isolation_simple_pt_eff_90[x]);
	ele_pfiso_simple_pt_eff_90->SetBinError(x+1,0);

	ele_pfiso_simple_pt_eff_99_bkg->SetBinContent(x+1,isolation_simple_pt_eff_99_bkg[x]);
	ele_pfiso_simple_pt_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_simple_pt_eff_95_bkg->SetBinContent(x+1,isolation_simple_pt_eff_95_bkg[x]);
	ele_pfiso_simple_pt_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_simple_pt_eff_90_bkg->SetBinContent(x+1,isolation_simple_pt_eff_90_bkg[x]);
	ele_pfiso_simple_pt_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_simple_pt_bkg_05->SetBinContent(x+1,isolation_simple_pt_bkg_05[x]);
	ele_pfiso_simple_pt_bkg_05->SetBinError(x+1,0);
	ele_pfiso_simple_pt_bkg_10->SetBinContent(x+1,isolation_simple_pt_bkg_10[x]);
	ele_pfiso_simple_pt_bkg_10->SetBinError(x+1,0);
	ele_pfiso_simple_pt_bkg_15->SetBinContent(x+1,isolation_simple_pt_bkg_15[x]);
	ele_pfiso_simple_pt_bkg_15->SetBinError(x+1,0);

	ele_pfiso_simple_pt_bkg_05_eff->SetBinContent(x+1,isolation_simple_pt_bkg_05_eff[x]);
	ele_pfiso_simple_pt_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_simple_pt_bkg_10_eff->SetBinContent(x+1,isolation_simple_pt_bkg_10_eff[x]);
	ele_pfiso_simple_pt_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_simple_pt_bkg_15_eff->SetBinContent(x+1,isolation_simple_pt_bkg_15_eff[x]);
	ele_pfiso_simple_pt_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_effarea_pt_eff_99->SetBinContent(x+1,isolation_effarea_pt_eff_99[x]);
	ele_pfiso_effarea_pt_eff_99->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_eff_95->SetBinContent(x+1,isolation_effarea_pt_eff_95[x]);
	ele_pfiso_effarea_pt_eff_95->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_eff_90->SetBinContent(x+1,isolation_effarea_pt_eff_90[x]);
	ele_pfiso_effarea_pt_eff_90->SetBinError(x+1,0);

	ele_pfiso_effarea_pt_eff_99_bkg->SetBinContent(x+1,isolation_effarea_pt_eff_99_bkg[x]);
	ele_pfiso_effarea_pt_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_eff_95_bkg->SetBinContent(x+1,isolation_effarea_pt_eff_95_bkg[x]);
	ele_pfiso_effarea_pt_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_eff_90_bkg->SetBinContent(x+1,isolation_effarea_pt_eff_90_bkg[x]);
	ele_pfiso_effarea_pt_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_effarea_pt_bkg_05->SetBinContent(x+1,isolation_effarea_pt_bkg_05[x]);
	ele_pfiso_effarea_pt_bkg_05->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_bkg_10->SetBinContent(x+1,isolation_effarea_pt_bkg_10[x]);
	ele_pfiso_effarea_pt_bkg_10->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_bkg_15->SetBinContent(x+1,isolation_effarea_pt_bkg_15[x]);
	ele_pfiso_effarea_pt_bkg_15->SetBinError(x+1,0);

	ele_pfiso_effarea_pt_bkg_05_eff->SetBinContent(x+1,isolation_effarea_pt_bkg_05_eff[x]);
	ele_pfiso_effarea_pt_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_bkg_10_eff->SetBinContent(x+1,isolation_effarea_pt_bkg_10_eff[x]);
	ele_pfiso_effarea_pt_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_effarea_pt_bkg_15_eff->SetBinContent(x+1,isolation_effarea_pt_bkg_15_eff[x]);
	ele_pfiso_effarea_pt_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_deltabeta_pt_eff_99->SetBinContent(x+1,isolation_deltabeta_pt_eff_99[x]);
	ele_pfiso_deltabeta_pt_eff_99->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_eff_95->SetBinContent(x+1,isolation_deltabeta_pt_eff_95[x]);
	ele_pfiso_deltabeta_pt_eff_95->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_eff_90->SetBinContent(x+1,isolation_deltabeta_pt_eff_90[x]);
	ele_pfiso_deltabeta_pt_eff_90->SetBinError(x+1,0);

	ele_pfiso_deltabeta_pt_eff_99_bkg->SetBinContent(x+1,isolation_deltabeta_pt_eff_99_bkg[x]);
	ele_pfiso_deltabeta_pt_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_eff_95_bkg->SetBinContent(x+1,isolation_deltabeta_pt_eff_95_bkg[x]);
	ele_pfiso_deltabeta_pt_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_eff_90_bkg->SetBinContent(x+1,isolation_deltabeta_pt_eff_90_bkg[x]);
	ele_pfiso_deltabeta_pt_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_deltabeta_pt_bkg_05->SetBinContent(x+1,isolation_deltabeta_pt_bkg_05[x]);
	ele_pfiso_deltabeta_pt_bkg_05->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_bkg_10->SetBinContent(x+1,isolation_deltabeta_pt_bkg_10[x]);
	ele_pfiso_deltabeta_pt_bkg_10->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_bkg_15->SetBinContent(x+1,isolation_deltabeta_pt_bkg_15[x]);
	ele_pfiso_deltabeta_pt_bkg_15->SetBinError(x+1,0);

	ele_pfiso_deltabeta_pt_bkg_05_eff->SetBinContent(x+1,isolation_deltabeta_pt_bkg_05_eff[x]);
	ele_pfiso_deltabeta_pt_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_bkg_10_eff->SetBinContent(x+1,isolation_deltabeta_pt_bkg_10_eff[x]);
	ele_pfiso_deltabeta_pt_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_deltabeta_pt_bkg_15_eff->SetBinContent(x+1,isolation_deltabeta_pt_bkg_15_eff[x]);
	ele_pfiso_deltabeta_pt_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_puppi_pt_eff_99->SetBinContent(x+1,isolation_puppi_pt_eff_99[x]);
	ele_pfiso_puppi_pt_eff_99->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_eff_95->SetBinContent(x+1,isolation_puppi_pt_eff_95[x]);
	ele_pfiso_puppi_pt_eff_95->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_eff_90->SetBinContent(x+1,isolation_puppi_pt_eff_90[x]);
	ele_pfiso_puppi_pt_eff_90->SetBinError(x+1,0);

	ele_pfiso_puppi_pt_eff_99_bkg->SetBinContent(x+1,isolation_puppi_pt_eff_99_bkg[x]);
	ele_pfiso_puppi_pt_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_eff_95_bkg->SetBinContent(x+1,isolation_puppi_pt_eff_95_bkg[x]);
	ele_pfiso_puppi_pt_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_eff_90_bkg->SetBinContent(x+1,isolation_puppi_pt_eff_90_bkg[x]);
	ele_pfiso_puppi_pt_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_puppi_pt_bkg_05->SetBinContent(x+1,isolation_puppi_pt_bkg_05[x]);
	ele_pfiso_puppi_pt_bkg_05->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_bkg_10->SetBinContent(x+1,isolation_puppi_pt_bkg_10[x]);
	ele_pfiso_puppi_pt_bkg_10->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_bkg_15->SetBinContent(x+1,isolation_puppi_pt_bkg_15[x]);
	ele_pfiso_puppi_pt_bkg_15->SetBinError(x+1,0);

	ele_pfiso_puppi_pt_bkg_05_eff->SetBinContent(x+1,isolation_puppi_pt_bkg_05_eff[x]);
	ele_pfiso_puppi_pt_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_bkg_10_eff->SetBinContent(x+1,isolation_puppi_pt_bkg_10_eff[x]);
	ele_pfiso_puppi_pt_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_puppi_pt_bkg_15_eff->SetBinContent(x+1,isolation_puppi_pt_bkg_15_eff[x]);
	ele_pfiso_puppi_pt_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_puppinl_pt_eff_99->SetBinContent(x+1,isolation_puppinl_pt_eff_99[x]);
	ele_pfiso_puppinl_pt_eff_99->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_eff_95->SetBinContent(x+1,isolation_puppinl_pt_eff_95[x]);
	ele_pfiso_puppinl_pt_eff_95->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_eff_90->SetBinContent(x+1,isolation_puppinl_pt_eff_90[x]);
	ele_pfiso_puppinl_pt_eff_90->SetBinError(x+1,0);

	ele_pfiso_puppinl_pt_eff_99_bkg->SetBinContent(x+1,isolation_puppinl_pt_eff_99_bkg[x]);
	ele_pfiso_puppinl_pt_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_eff_95_bkg->SetBinContent(x+1,isolation_puppinl_pt_eff_95_bkg[x]);
	ele_pfiso_puppinl_pt_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_eff_90_bkg->SetBinContent(x+1,isolation_puppinl_pt_eff_90_bkg[x]);
	ele_pfiso_puppinl_pt_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_puppinl_pt_bkg_05->SetBinContent(x+1,isolation_puppinl_pt_bkg_05[x]);
	ele_pfiso_puppinl_pt_bkg_05->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_bkg_10->SetBinContent(x+1,isolation_puppinl_pt_bkg_10[x]);
	ele_pfiso_puppinl_pt_bkg_10->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_bkg_15->SetBinContent(x+1,isolation_puppinl_pt_bkg_15[x]);
	ele_pfiso_puppinl_pt_bkg_15->SetBinError(x+1,0);

	ele_pfiso_puppinl_pt_bkg_05_eff->SetBinContent(x+1,isolation_puppinl_pt_bkg_05_eff[x]);
	ele_pfiso_puppinl_pt_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_bkg_10_eff->SetBinContent(x+1,isolation_puppinl_pt_bkg_10_eff[x]);
	ele_pfiso_puppinl_pt_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_puppinl_pt_bkg_15_eff->SetBinContent(x+1,isolation_puppinl_pt_bkg_15_eff[x]);
	ele_pfiso_puppinl_pt_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_citk_pt_eff_99->SetBinContent(x+1,isolation_citk_pt_eff_99[x]);
	ele_pfiso_citk_pt_eff_99->SetBinError(x+1,0);
	ele_pfiso_citk_pt_eff_95->SetBinContent(x+1,isolation_citk_pt_eff_95[x]);
	ele_pfiso_citk_pt_eff_95->SetBinError(x+1,0);
	ele_pfiso_citk_pt_eff_90->SetBinContent(x+1,isolation_citk_pt_eff_90[x]);
	ele_pfiso_citk_pt_eff_90->SetBinError(x+1,0);

	ele_pfiso_citk_pt_eff_99_bkg->SetBinContent(x+1,isolation_citk_pt_eff_99_bkg[x]);
	ele_pfiso_citk_pt_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_citk_pt_eff_95_bkg->SetBinContent(x+1,isolation_citk_pt_eff_95_bkg[x]);
	ele_pfiso_citk_pt_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_citk_pt_eff_90_bkg->SetBinContent(x+1,isolation_citk_pt_eff_90_bkg[x]);
	ele_pfiso_citk_pt_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_citk_pt_bkg_05->SetBinContent(x+1,isolation_citk_pt_bkg_05[x]);
	ele_pfiso_citk_pt_bkg_05->SetBinError(x+1,0);
	ele_pfiso_citk_pt_bkg_10->SetBinContent(x+1,isolation_citk_pt_bkg_10[x]);
	ele_pfiso_citk_pt_bkg_10->SetBinError(x+1,0);
	ele_pfiso_citk_pt_bkg_15->SetBinContent(x+1,isolation_citk_pt_bkg_15[x]);
	ele_pfiso_citk_pt_bkg_15->SetBinError(x+1,0);

	ele_pfiso_citk_pt_bkg_05_eff->SetBinContent(x+1,isolation_citk_pt_bkg_05_eff[x]);
	ele_pfiso_citk_pt_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_citk_pt_bkg_10_eff->SetBinContent(x+1,isolation_citk_pt_bkg_10_eff[x]);
	ele_pfiso_citk_pt_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_citk_pt_bkg_15_eff->SetBinContent(x+1,isolation_citk_pt_bkg_15_eff[x]);
	ele_pfiso_citk_pt_bkg_15_eff->SetBinError(x+1,0);
	}

   for (int x=0; x<=9; x++)
	{
	if (test) { cout << x << " - " << isolation_deltabeta_pt[1][x] << " | " << isolation_deltabeta_pt[0][x] << endl; }
	}

  plot_histogram(ele_pfiso_simple_pt_eff, "output/","ele_pfiso_simple_pt_eff", "Electron PF Isolation Simple pT", "bottom_right", false);
   plot_histogram(ele_pfiso_effarea_pt_eff, "output/","ele_pfiso_effarea_pt_eff", "Electron PF Isolation Effective Area pT", "bottom_right", false);
   plot_histogram(ele_pfiso_deltabeta_pt_eff, "output/","ele_pfiso_deltabeta_pt_eff", "Electron PF Isolation Delta Beta pT", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_eff, "output/","ele_pfiso_puppi_pt_eff", "Electron PF Isolation PUPPI pT", "bottom_right", false);
   plot_histogram(ele_pfiso_puppinl_pt_eff, "output/","ele_pfiso_puppinl_pt_eff", "Electron PF Isolation PUPPI No Leptons pT", "bottom_right", false);
   plot_histogram(ele_pfiso_citk_pt_eff, "output/","ele_pfiso_citk_pt_eff", "Electron PF Isolation CITK pT", "bottom_right", false);

   plot_six_dist(ele_pfiso_simple_pt_eff, "PF without PU subtraction", ele_pfiso_effarea_pt_eff, "Effective Area", ele_pfiso_deltabeta_pt_eff, "Delta Beta", ele_pfiso_puppi_pt_eff, "PUPPI", ele_pfiso_puppinl_pt_eff, "PUPPI No Leptons", ele_pfiso_citk_pt_eff, "CITK", "output/", "", "ele_pfiso_pt_eff", "bottom_right", false, 0.45, 1.0, false);

   plot_histogram(ele_pfiso_simple_pt_bkg, "output/","ele_pfiso_simple_pt_bkg", "Electron PF Isolation Simple pT", "bottom_right", false);
   plot_histogram(ele_pfiso_effarea_pt_bkg, "output/","ele_pfiso_effarea_pt_bkg", "Electron PF Isolation Effective Area pT", "bottom_right", false);
   plot_histogram(ele_pfiso_deltabeta_pt_bkg, "output/","ele_pfiso_deltabeta_pt_bkg", "Electron PF Isolation Delta Beta pT", "bottom_right", false);
   plot_histogram(ele_pfiso_puppi_pt_bkg, "output/","ele_pfiso_puppi_pt_bkg", "Electron PF Isolation PUPPI pT", "bottom_right", false);
   plot_histogram(ele_pfiso_puppinl_pt_bkg, "output/","ele_pfiso_puppinl_pt_bkg", "Electron PF Isolation PUPPI No Lepton pT", "bottom_right", false);
   plot_histogram(ele_pfiso_citk_pt_bkg, "output/","ele_pfiso_citk_pt_bkg", "Electron PF Isolation CITK pT", "bottom_right", false);

   plot_six_dist(ele_pfiso_simple_pt_bkg, "PF without PU subtraction", ele_pfiso_effarea_pt_bkg, "Effective Area", ele_pfiso_deltabeta_pt_bkg, "Delta Beta", ele_pfiso_puppi_pt_bkg, "PUPPI", ele_pfiso_puppinl_pt_bkg, "PUPPI No Leptons", ele_pfiso_citk_pt_bkg, "CITK", "output/", "", "ele_pfiso_pt_bkg", "bottom_right", false, 0.04, 0.36, false);

   plot_histogram(ele_pfiso_simple_pt_ratio, "output/","ele_pfiso_simple_pt_ratio", "Electron PF Isolation Simple pT", "top_right", false);
   plot_histogram(ele_pfiso_effarea_pt_ratio, "output/","ele_pfiso_effarea_pt_ratio", "Electron PF Isolation Effective Area pT", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_pt_ratio, "output/","ele_pfiso_deltabeta_pt_ratio", "Electron PF Isolation Delta Beta pT", "top_right", false);
   plot_histogram(ele_pfiso_puppi_pt_ratio, "output/","ele_pfiso_puppi_pt_ratio", "Electron PF Isolation PUPPI pT", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_pt_ratio, "output/","ele_pfiso_puppinl_pt_ratio", "Electron PF Isolation PUPPI No Lepton pT", "top_right", false);
   plot_histogram(ele_pfiso_citk_pt_ratio, "output/","ele_pfiso_citk_pt_ratio", "Electron PF Isolation CITK pT", "top_right", false);

   plot_six_dist(ele_pfiso_simple_pt_ratio, "PF without PU subtraction", ele_pfiso_effarea_pt_ratio, "Effective Area", ele_pfiso_deltabeta_pt_ratio, "Delta Beta", ele_pfiso_puppi_pt_ratio, "PUPPI", ele_pfiso_puppinl_pt_ratio, "PUPPI No Leptons", ele_pfiso_citk_pt_ratio, "CITK", "output/", "", "ele_pfiso_pt_ratio", "top_right", false, 2.0, 12.0, false);

  plot_histogram(ele_pfiso_simple_pt_eff_99, "output/","ele_pfiso_simple_pt_eff_99", "Electron PF Isolation Simple pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_pt_eff_95, "output/","ele_pfiso_simple_pt_eff_95", "Electron PF Isolation Simple pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_pt_eff_90, "output/","ele_pfiso_simple_pt_eff_90", "Electron PF Isolation Simple pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_simple_pt_eff_90, "90% effeciency", ele_pfiso_simple_pt_eff_95, "95% efficiency", ele_pfiso_simple_pt_eff_99, "99% efficiency", "output/", "ele_pfiso_simple_pt_eff_all", "bottom_right", false, 0.59, 1.0, false);

  plot_histogram(ele_pfiso_simple_pt_eff_99_bkg, "output/","ele_pfiso_simple_pt_eff_99_bkg", "Electron PF Isolation Simple pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_pt_eff_95_bkg, "output/","ele_pfiso_simple_pt_eff_95_bkg", "Electron PF Isolation Simple pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_pt_eff_90_bkg, "output/","ele_pfiso_simple_pt_eff_90_bkg", "Electron PF Isolation Simple pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_simple_pt_eff_90_bkg, "90% effeciency", ele_pfiso_simple_pt_eff_95_bkg, "95% efficiency", ele_pfiso_simple_pt_eff_99_bkg, "99% efficiency", "output/", "ele_pfiso_simple_pt_eff_all_bkg", "bottom_right", false, 0.05, 0.78, false);

  plot_histogram(ele_pfiso_effarea_pt_eff_99, "output/","ele_pfiso_effarea_pt_eff_99", "Electron PF Isolation Effective Area pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_pt_eff_95, "output/","ele_pfiso_effarea_pt_eff_95", "Electron PF Isolation Effective Area pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_pt_eff_90, "output/","ele_pfiso_effarea_pt_eff_90", "Electron PF Isolation Effective Area pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_effarea_pt_eff_90, "90% effeciency", ele_pfiso_effarea_pt_eff_95, "95% efficiency", ele_pfiso_effarea_pt_eff_99, "99% efficiency", "output/", "ele_pfiso_effarea_pt_eff_all", "bottom_right", false, 0.7, 1.0, false);

  plot_histogram(ele_pfiso_effarea_pt_eff_99_bkg, "output/","ele_pfiso_effarea_pt_eff_99_bkg", "Electron PF Isolation Effective Area pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_pt_eff_95_bkg, "output/","ele_pfiso_effarea_pt_eff_95_bkg", "Electron PF Isolation Effective Area pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_pt_eff_90_bkg, "output/","ele_pfiso_effarea_pt_eff_90_bkg", "Electron PF Isolation Effective Area pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_effarea_pt_eff_90_bkg, "90% effeciency", ele_pfiso_effarea_pt_eff_95_bkg, "95% efficiency", ele_pfiso_effarea_pt_eff_99_bkg, "99% efficiency", "output/", "ele_pfiso_effarea_pt_eff_all_bkg", "bottom_right", false, 0.04, 0.6, false);


  plot_histogram(ele_pfiso_deltabeta_pt_eff_99, "output/","ele_pfiso_deltabeta_pt_eff_99", "Electron PF Isolation Delta Beta pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_pt_eff_95, "output/","ele_pfiso_deltabeta_pt_eff_95", "Electron PF Isolation Delta Beta pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_pt_eff_90, "output/","ele_pfiso_deltabeta_pt_eff_90", "Electron PF Isolation Delta Beta pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_deltabeta_pt_eff_90, "90% effeciency", ele_pfiso_deltabeta_pt_eff_95, "95% efficiency", ele_pfiso_deltabeta_pt_eff_99, "99% efficiency", "output/", "ele_pfiso_deltabeta_pt_eff_all", "bottom_right", false, 0.7, 1.0, false);

  plot_histogram(ele_pfiso_deltabeta_pt_eff_99_bkg, "output/","ele_pfiso_deltabeta_pt_eff_99_bkg", "Electron PF Isolation Delta Beta pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_pt_eff_95_bkg, "output/","ele_pfiso_deltabeta_pt_eff_95_bkg", "Electron PF Isolation Delta Beta pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_pt_eff_90_bkg, "output/","ele_pfiso_deltabeta_pt_eff_90_bkg", "Electron PF Isolation Delta Beta pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_deltabeta_pt_eff_90_bkg, "90% effeciency", ele_pfiso_deltabeta_pt_eff_95_bkg, "95% efficiency", ele_pfiso_deltabeta_pt_eff_99_bkg, "99% efficiency", "output/", "ele_pfiso_deltabeta_pt_eff_all_bkg", "top_left", false, 0.05, 0.6, false);


  plot_histogram(ele_pfiso_puppi_pt_eff_99, "output/","ele_pfiso_puppi_pt_eff_99", "Electron PF Isolation PUPPI pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_eff_95, "output/","ele_pfiso_puppi_pt_eff_95", "Electron PF Isolation PUPPI pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_eff_90, "output/","ele_pfiso_puppi_pt_eff_90", "Electron PF Isolation PUPPI pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_puppi_pt_eff_90, "90% effeciency", ele_pfiso_puppi_pt_eff_95, "95% efficiency", ele_pfiso_puppi_pt_eff_99, "99% efficiency", "output/", "ele_pfiso_puppi_pt_eff_all", "bottom_right", false, 0.57, 1.0, false);

  plot_histogram(ele_pfiso_puppi_pt_eff_99_bkg, "output/","ele_pfiso_puppi_pt_eff_99_bkg", "Electron PF Isolation PUPPI pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_eff_95_bkg, "output/","ele_pfiso_puppi_pt_eff_95_bkg", "Electron PF Isolation PUPPI pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_eff_90_bkg, "output/","ele_pfiso_puppi_pt_eff_90_bkg", "Electron PF Isolation PUPPI pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_puppi_pt_eff_90_bkg, "90% effeciency", ele_pfiso_puppi_pt_eff_95_bkg, "95% efficiency", ele_pfiso_puppi_pt_eff_99_bkg, "99% efficiency", "output/", "ele_pfiso_puppi_pt_eff_all_bkg", "bottom_right", false, 0.0, 0.85, false);

  plot_histogram(ele_pfiso_puppinl_pt_eff_99, "output/","ele_pfiso_puppinl_pt_eff_99", "Electron PF Isolation PUPPI No Leptons pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_puppinl_pt_eff_95, "output/","ele_pfiso_puppinl_pt_eff_95", "Electron PF Isolation PUPPI No Leptons pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_puppinl_pt_eff_90, "output/","ele_pfiso_puppinl_pt_eff_90", "Electron PF Isolation PUPPI No Leptons pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_puppinl_pt_eff_90, "90% effeciency", ele_pfiso_puppinl_pt_eff_95, "95% efficiency", ele_pfiso_puppinl_pt_eff_99, "99% efficiency", "output/", "ele_pfiso_puppinl_pt_eff_all", "bottom_right", false, 0.6, 1.0, false);

  plot_histogram(ele_pfiso_puppinl_pt_eff_99_bkg, "output/","ele_pfiso_puppinl_pt_eff_99_bkg", "Electron PF Isolation PUPPI No Leptons pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_puppinl_pt_eff_95_bkg, "output/","ele_pfiso_puppinl_pt_eff_95_bkg", "Electron PF Isolation PUPPI No Leptons pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_puppinl_pt_eff_90_bkg, "output/","ele_pfiso_puppinl_pt_eff_90_bkg", "Electron PF Isolation PUPPI No Leptons pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_puppinl_pt_eff_90_bkg, "90% effeciency", ele_pfiso_puppinl_pt_eff_95_bkg, "95% efficiency", ele_pfiso_puppinl_pt_eff_99_bkg, "99% efficiency", "output/", "ele_pfiso_puppinl_pt_eff_all_bkg", "bottom_right", false, 0.0, 0.75, false);

  plot_histogram(ele_pfiso_citk_pt_eff_99, "output/","ele_pfiso_citk_pt_eff_99", "Electron PF Isolation CITK pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_citk_pt_eff_95, "output/","ele_pfiso_citk_pt_eff_95", "Electron PF Isolation CITK pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_citk_pt_eff_90, "output/","ele_pfiso_citk_pt_eff_90", "Electron PF Isolation CITK pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_citk_pt_eff_90, "90% effeciency", ele_pfiso_citk_pt_eff_95, "95% efficiency", ele_pfiso_citk_pt_eff_99, "99% efficiency", "output/", "ele_pfiso_citk_pt_eff_all", "bottom_right", false, 0.58, 1.0, false);

  plot_histogram(ele_pfiso_citk_pt_eff_99_bkg, "output/","ele_pfiso_citk_pt_eff_99_bkg", "Electron PF Isolation CITK pT with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_citk_pt_eff_95_bkg, "output/","ele_pfiso_citk_pt_eff_95_bkg", "Electron PF Isolation CITK pT with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_citk_pt_eff_90_bkg, "output/","ele_pfiso_citk_pt_eff_90_bkg", "Electron PF Isolation CITK pT with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_citk_pt_eff_90_bkg, "90% effeciency", ele_pfiso_citk_pt_eff_95_bkg, "95% efficiency", ele_pfiso_citk_pt_eff_99_bkg, "99% efficiency", "output/", "ele_pfiso_citk_pt_eff_all_bkg", "bottom_right", false, 0.0, 0.8, false);

   plot_six_dist(ele_pfiso_simple_pt_eff_90, "PF without PU subtraction", ele_pfiso_effarea_pt_eff_90, "Effective Area", ele_pfiso_deltabeta_pt_eff_90, "Delta Beta", ele_pfiso_puppi_pt_eff_90, "PUPPI", ele_pfiso_puppinl_pt_eff_90, "PUPPI No Leptons", ele_pfiso_citk_pt_eff_90, "CITK", "output/", "", "ele_pfiso_pt_eff_90", "bottom_right", false, 0.57, 1.0, false);

   plot_six_dist(ele_pfiso_simple_pt_eff_95, "PF without PU subtraction", ele_pfiso_effarea_pt_eff_95, "Effective Area", ele_pfiso_deltabeta_pt_eff_95, "Delta Beta", ele_pfiso_puppi_pt_eff_95, "PUPPI", ele_pfiso_puppinl_pt_eff_95, "PUPPI No Leptons", ele_pfiso_citk_pt_eff_95, "CITK", "output/", "", "ele_pfiso_pt_eff_95", "bottom_right", false, 0.74, 1.0, false);

   plot_six_dist(ele_pfiso_simple_pt_eff_99, "PF without PU subtraction", ele_pfiso_effarea_pt_eff_99, "Effective Area", ele_pfiso_deltabeta_pt_eff_99, "Delta Beta", ele_pfiso_puppi_pt_eff_99, "PUPPI", ele_pfiso_puppinl_pt_eff_99, "PUPPI No Leptons", ele_pfiso_citk_pt_eff_99, "CITK", "output/", "", "ele_pfiso_pt_eff_99", "bottom_right", false, 0.94, 1.0, false);

   plot_six_dist(ele_pfiso_simple_pt_eff_90_bkg, "PF without PU subtraction", ele_pfiso_effarea_pt_eff_90_bkg, "Effective Area", ele_pfiso_deltabeta_pt_eff_90_bkg, "Delta Beta", ele_pfiso_puppi_pt_eff_90_bkg, "PUPPI", ele_pfiso_puppinl_pt_eff_90_bkg, "PUPPI No Leptons", ele_pfiso_citk_pt_eff_90_bkg, "CITK", "output/", "", "ele_pfiso_pt_eff_90_bkg", "top_left", false, 0.04, 0.4, false);

   plot_six_dist(ele_pfiso_simple_pt_eff_95_bkg, "PF without PU subtraction", ele_pfiso_effarea_pt_eff_95_bkg, "Effective Area", ele_pfiso_deltabeta_pt_eff_95_bkg, "Delta Beta", ele_pfiso_puppi_pt_eff_95_bkg, "PUPPI", ele_pfiso_puppinl_pt_eff_95_bkg, "PUPPI No Leptons", ele_pfiso_citk_pt_eff_95_bkg, "CITK", "output/", "", "ele_pfiso_pt_eff_95_bkg", "top_left", false, 0.06, 0.5, false);

   plot_six_dist(ele_pfiso_simple_pt_eff_99_bkg, "PF without PU subtraction", ele_pfiso_effarea_pt_eff_99_bkg, "Effective Area", ele_pfiso_deltabeta_pt_eff_99_bkg, "Delta Beta", ele_pfiso_puppi_pt_eff_99_bkg, "PUPPI", ele_pfiso_puppinl_pt_eff_99_bkg, "PUPPI No Leptons", ele_pfiso_citk_pt_eff_99_bkg, "CITK", "output/", "", "ele_pfiso_pt_eff_99_bkg", "bottom_right", false, 0.2, 0.9, false);

  plot_histogram(ele_pfiso_simple_pt_bkg_05, "output/","ele_pfiso_simple_pt_bkg_05", "Electron PF Isolation Simple pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_pt_bkg_10, "output/","ele_pfiso_simple_pt_bkg_10", "Electron PF Isolation Simple pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_pt_bkg_15, "output/","ele_pfiso_simple_pt_bkg_15", "Electron PF Isolation Simple pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_simple_pt_bkg_05, "5% background", ele_pfiso_simple_pt_bkg_10, "10% background", ele_pfiso_simple_pt_bkg_15, "15% background", "output/", "ele_pfiso_simple_pt_bkg_all", "top_left", false, 0.02, 0.44, false);

  plot_histogram(ele_pfiso_simple_pt_bkg_05_eff, "output/","ele_pfiso_simple_pt_bkg_05_eff", "Electron PF Isolation Simple pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_pt_bkg_10_eff, "output/","ele_pfiso_simple_pt_bkg_10_eff", "Electron PF Isolation Simple pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_pt_bkg_15_eff, "output/","ele_pfiso_simple_pt_bkg_15_eff", "Electron PF Isolation Simple pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_simple_pt_bkg_05_eff, "5% background", ele_pfiso_simple_pt_bkg_10_eff, "10% background", ele_pfiso_simple_pt_bkg_15_eff, "15% background", "output/", "ele_pfiso_simple_pt_bkg_all_eff", "bottom_right", false, 0.37, 1.0,false);

  plot_histogram(ele_pfiso_effarea_pt_bkg_05, "output/","ele_pfiso_effarea_pt_bkg_05", "Electron PF Isolation Effective Area pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_pt_bkg_10, "output/","ele_pfiso_effarea_pt_bkg_10", "Electron PF Isolation Effective Area pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_pt_bkg_15, "output/","ele_pfiso_effarea_pt_bkg_15", "Electron PF Isolation Effective Area pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_effarea_pt_bkg_05, "5% background", ele_pfiso_effarea_pt_bkg_10, "10% background", ele_pfiso_effarea_pt_bkg_15, "15% background", "output/", "ele_pfiso_effarea_pt_bkg_all", "top_left", false,0.03, 0.41, false);

  plot_histogram(ele_pfiso_effarea_pt_bkg_05_eff, "output/","ele_pfiso_effarea_pt_bkg_05_eff", "Electron PF Isolation Effective Area pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_pt_bkg_10_eff, "output/","ele_pfiso_effarea_pt_bkg_10_eff", "Electron PF Isolation Effective Area pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_pt_bkg_15_eff, "output/","ele_pfiso_effarea_pt_bkg_15_eff", "Electron PF Isolation Effective Area pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_effarea_pt_bkg_05_eff, "5% background", ele_pfiso_effarea_pt_bkg_10_eff, "10% background", ele_pfiso_effarea_pt_bkg_15_eff, "15% background", "output/", "ele_pfiso_effarea_pt_bkg_all_eff", "bottom_right", false, 0.63, 1.0, false);

  plot_histogram(ele_pfiso_deltabeta_pt_bkg_05, "output/","ele_pfiso_deltabeta_pt_bkg_05", "Electron PF Isolation Delta Beta pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_pt_bkg_10, "output/","ele_pfiso_deltabeta_pt_bkg_10", "Electron PF Isolation Delta Beta pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_pt_bkg_15, "output/","ele_pfiso_deltabeta_pt_bkg_15", "Electron PF Isolation Delta Beta pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_deltabeta_pt_bkg_05, "5% background", ele_pfiso_deltabeta_pt_bkg_10, "10% background", ele_pfiso_deltabeta_pt_bkg_15, "15% background", "output/", "ele_pfiso_deltabeta_pt_bkg_all", "top_left", false, 0.03, 0.4, false);

  plot_histogram(ele_pfiso_deltabeta_pt_bkg_05_eff, "output/","ele_pfiso_deltabeta_pt_bkg_05_eff", "Electron PF Isolation Delta Beta pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_pt_bkg_10_eff, "output/","ele_pfiso_deltabeta_pt_bkg_10_eff", "Electron PF Isolation Delta Beta pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_pt_bkg_15_eff, "output/","ele_pfiso_deltabeta_pt_bkg_15_eff", "Electron PF Isolation Delta Beta pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_deltabeta_pt_bkg_05_eff, "5% background", ele_pfiso_deltabeta_pt_bkg_10_eff, "10% background", ele_pfiso_deltabeta_pt_bkg_15_eff, "15% background", "output/", "ele_pfiso_deltabeta_pt_bkg_all_eff", "bottom_right", false, 0.59, 1.0, false);

  plot_histogram(ele_pfiso_puppi_pt_bkg_05, "output/","ele_pfiso_puppi_pt_bkg_05", "Electron PF Isolation PUPPI pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_bkg_10, "output/","ele_pfiso_puppi_pt_bkg_10", "Electron PF Isolation PUPPI pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_bkg_15, "output/","ele_pfiso_puppi_pt_bkg_15", "Electron PF Isolation PUPPI pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_puppi_pt_bkg_05, "5% background", ele_pfiso_puppi_pt_bkg_10, "10% background", ele_pfiso_puppi_pt_bkg_15, "15% background", "output/", "ele_pfiso_puppi_pt_bkg_all", "top_left", false, 0.02, 0.44, false);

  plot_histogram(ele_pfiso_puppi_pt_bkg_05_eff, "output/","ele_pfiso_puppi_pt_bkg_05_eff", "Electron PF Isolation PUPPI pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_bkg_10_eff, "output/","ele_pfiso_puppi_pt_bkg_10_eff", "Electron PF Isolation PUPPI pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_puppi_pt_bkg_15_eff, "output/","ele_pfiso_puppi_pt_bkg_15_eff", "Electron PF Isolation PUPPI pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_puppi_pt_bkg_05_eff, "5% background", ele_pfiso_puppi_pt_bkg_10_eff, "10% background", ele_pfiso_puppi_pt_bkg_15_eff, "15% background", "output/", "ele_pfiso_puppi_pt_bkg_all_eff", "bottom_right", false, 0.27, 1.0, false);

  plot_histogram(ele_pfiso_puppinl_pt_bkg_05, "output/","ele_pfiso_puppinl_pt_bkg_05", "Electron PF Isolation PUPPI No Leptons pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_puppinl_pt_bkg_10, "output/","ele_pfiso_puppinl_pt_bkg_10", "Electron PF Isolation PUPPI No Leptons pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_puppinl_pt_bkg_15, "output/","ele_pfiso_puppinl_pt_bkg_15", "Electron PF Isolation PUPPI No Leptons pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_puppinl_pt_bkg_05, "5% background", ele_pfiso_puppinl_pt_bkg_10, "10% background", ele_pfiso_puppinl_pt_bkg_15, "15% background", "output/", "ele_pfiso_puppinl_pt_bkg_all", "top_left", false, 0.02, 0.42, false);

  plot_histogram(ele_pfiso_puppinl_pt_bkg_05_eff, "output/","ele_pfiso_puppinl_pt_bkg_05_eff", "Electron PF Isolation PUPPI No Leptons pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_puppinl_pt_bkg_10_eff, "output/","ele_pfiso_puppinl_pt_bkg_10_eff", "Electron PF Isolation PUPPI No Leptons pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_puppinl_pt_bkg_15_eff, "output/","ele_pfiso_puppinl_pt_bkg_15_eff", "Electron PF Isolation PUPPI No Leptons pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_puppinl_pt_bkg_05_eff, "5% background", ele_pfiso_puppinl_pt_bkg_10_eff, "10% background", ele_pfiso_puppinl_pt_bkg_15_eff, "15% background", "output/", "ele_pfiso_puppinl_pt_bkg_all_eff", "bottom_right", false, 0.3, 1.0, false);

  plot_histogram(ele_pfiso_citk_pt_bkg_05, "output/","ele_pfiso_citk_pt_bkg_05", "Electron PF Isolation CITK pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_citk_pt_bkg_10, "output/","ele_pfiso_citk_pt_bkg_10", "Electron PF Isolation CITK pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_citk_pt_bkg_15, "output/","ele_pfiso_citk_pt_bkg_15", "Electron PF Isolation CITK pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_citk_pt_bkg_05, "5% background", ele_pfiso_citk_pt_bkg_10, "10% background", ele_pfiso_citk_pt_bkg_15, "15% background", "output/", "ele_pfiso_citk_pt_bkg_all", "top_left", false, 0.0, 0.45, false);

  plot_histogram(ele_pfiso_citk_pt_bkg_05_eff, "output/","ele_pfiso_citk_pt_bkg_05_eff", "Electron PF Isolation CITK pT with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_citk_pt_bkg_10_eff, "output/","ele_pfiso_citk_pt_bkg_10_eff", "Electron PF Isolation CITK pT with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_citk_pt_bkg_15_eff, "output/","ele_pfiso_citk_pt_bkg_15_eff", "Electron PF Isolation CITK pT with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_citk_pt_bkg_05_eff, "5% background", ele_pfiso_citk_pt_bkg_10_eff, "10% background", ele_pfiso_citk_pt_bkg_15_eff, "15% background", "output/", "ele_pfiso_citk_pt_bkg_all_eff", "bottom_right", false, 0.37, 1.0, false);


   plot_six_dist(ele_pfiso_simple_pt_bkg_05, "PF without PU subtraction", ele_pfiso_effarea_pt_bkg_05, "Effective Area", ele_pfiso_deltabeta_pt_bkg_05, "Delta Beta", ele_pfiso_puppi_pt_bkg_05, "PUPPI", ele_pfiso_puppinl_pt_bkg_05, "PUPPI No Leptons", ele_pfiso_citk_pt_bkg_05, "CITK", "output/", "", "ele_pfiso_pt_bkg_05", "top_left", false, 0.02, 0.18, false);

   plot_six_dist(ele_pfiso_simple_pt_bkg_10, "PF without PU subtraction", ele_pfiso_effarea_pt_bkg_10, "Effective Area", ele_pfiso_deltabeta_pt_bkg_10, "Delta Beta", ele_pfiso_puppi_pt_bkg_10, "PUPPI", ele_pfiso_puppinl_pt_bkg_10, "PUPPI No Leptons", ele_pfiso_citk_pt_bkg_10, "CITK", "output/", "", "ele_pfiso_pt_bkg_10", "top_left", false, 0.05, 0.35, false);

   plot_six_dist(ele_pfiso_simple_pt_bkg_15, "PF without PU subtraction", ele_pfiso_effarea_pt_bkg_15, "Effective Area", ele_pfiso_deltabeta_pt_bkg_15, "Delta Beta", ele_pfiso_puppi_pt_bkg_15, "PUPPI", ele_pfiso_puppinl_pt_bkg_15, "PUPPI No Leptons", ele_pfiso_citk_pt_bkg_15, "CITK", "output/", "", "ele_pfiso_pt_bkg_15", "bottom_right", false, 0.08, 0.44, false);

   plot_six_dist(ele_pfiso_simple_pt_bkg_05_eff, "PF without PU subtraction", ele_pfiso_effarea_pt_bkg_05_eff, "Effective Area", ele_pfiso_deltabeta_pt_bkg_05_eff, "Delta Beta", ele_pfiso_puppi_pt_bkg_05_eff, "PUPPI", ele_pfiso_puppinl_pt_bkg_05_eff, "PUPPI No Leptons", ele_pfiso_citk_pt_bkg_05_eff, "CITK", "output/", "", "ele_pfiso_pt_bkg_05_eff", "bottom_right", false, 0.26, 1.0, false);

   plot_six_dist(ele_pfiso_simple_pt_bkg_10_eff, "PF without PU subtraction", ele_pfiso_effarea_pt_bkg_10_eff, "Effective Area", ele_pfiso_deltabeta_pt_bkg_10_eff, "Delta Beta", ele_pfiso_puppi_pt_bkg_10_eff, "PUPPI", ele_pfiso_puppinl_pt_bkg_10_eff, "PUPPI No Leptons", ele_pfiso_citk_pt_bkg_10_eff, "CITK", "output/", "", "ele_pfiso_pt_bkg_10_eff", "bottom_right", false, 0.51, 1.0, false);

   plot_six_dist(ele_pfiso_simple_pt_bkg_15_eff, "PF without PU subtraction", ele_pfiso_effarea_pt_bkg_15_eff, "Effective Area", ele_pfiso_deltabeta_pt_bkg_15_eff, "Delta Beta", ele_pfiso_puppi_pt_bkg_15_eff, "PUPPI", ele_pfiso_puppinl_pt_bkg_15_eff, "PUPPI No Leptons", ele_pfiso_citk_pt_bkg_15_eff, "CITK", "output/", "", "ele_pfiso_pt_bkg_15_eff", "bottom_right", false, 0.68, 1.0, false);

}
