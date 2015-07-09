// Pedro Cipriano, July 2015
// FESB - Split, CMS
// Last Update: 09 July 2015
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

void differential_studies()
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
  int vtx_nbins = 27;
  double vtx_bins[28] = {5.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0,22.0,23.0, 24.0,25.0,26.0,27.0,28.0,29.0,30.0,35.0,42.5,50.0,60.0,70.0,80.0};

  //Declare Histograms
TH1D *ele_pfiso_simple_vtx_eff = new TH1D("ele_pfiso_simple_vtx_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff = new TH1D("ele_pfiso_effarea_vtx_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff = new TH1D("ele_pfiso_deltabeta_vtx_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff = new TH1D("ele_pfiso_puppi_vtx_eff","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff = new TH1D("ele_pfiso_puppinl_vtx_eff","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff = new TH1D("ele_pfiso_citk_vtx_eff","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_99 = new TH1D("ele_pfiso_simple_vtx_eff_99","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_99 = new TH1D("ele_pfiso_effarea_vtx_eff_99","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_99 = new TH1D("ele_pfiso_deltabeta_vtx_eff_99","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_99 = new TH1D("ele_pfiso_puppi_vtx_eff_99","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_99 = new TH1D("ele_pfiso_puppinl_vtx_eff_99","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_99 = new TH1D("ele_pfiso_citk_vtx_eff_99","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_99_bkg = new TH1D("ele_pfiso_simple_vtx_eff_99_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_99_bkg = new TH1D("ele_pfiso_effarea_vtx_eff_99_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_99_bkg = new TH1D("ele_pfiso_deltabeta_vtx_eff_99_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_99_bkg = new TH1D("ele_pfiso_puppi_vtx_eff_99_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_99_bkg = new TH1D("ele_pfiso_puppinl_vtx_eff_99_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_99_bkg = new TH1D("ele_pfiso_citk_vtx_eff_99_bkg","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_95 = new TH1D("ele_pfiso_simple_vtx_eff_95","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_95 = new TH1D("ele_pfiso_effarea_vtx_eff_95","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_95 = new TH1D("ele_pfiso_deltabeta_vtx_eff_95","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_95 = new TH1D("ele_pfiso_puppi_vtx_eff_95","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_95 = new TH1D("ele_pfiso_puppinl_vtx_eff_95","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_95 = new TH1D("ele_pfiso_citk_vtx_eff_95","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_95_bkg = new TH1D("ele_pfiso_simple_vtx_eff_95_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_95_bkg = new TH1D("ele_pfiso_effarea_vtx_eff_95_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_95_bkg = new TH1D("ele_pfiso_deltabeta_vtx_eff_95_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_95_bkg = new TH1D("ele_pfiso_puppi_vtx_eff_95_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_95_bkg = new TH1D("ele_pfiso_puppinl_vtx_eff_95_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_95_bkg = new TH1D("ele_pfiso_citk_vtx_eff_95_bkg","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_90 = new TH1D("ele_pfiso_simple_vtx_eff_90","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_90 = new TH1D("ele_pfiso_effarea_vtx_eff_90","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_90 = new TH1D("ele_pfiso_deltabeta_vtx_eff_90","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_90 = new TH1D("ele_pfiso_puppi_vtx_eff_90","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_90 = new TH1D("ele_pfiso_puppinl_vtx_eff_90","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_90 = new TH1D("ele_pfiso_citk_vtx_eff_90","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_90_bkg = new TH1D("ele_pfiso_simple_vtx_eff_90_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_90_bkg = new TH1D("ele_pfiso_effarea_vtx_eff_90_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_90_bkg = new TH1D("ele_pfiso_deltabeta_vtx_eff_90_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_90_bkg = new TH1D("ele_pfiso_puppi_vtx_eff_90_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_90_bkg = new TH1D("ele_pfiso_puppinl_vtx_eff_90_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_90_bkg = new TH1D("ele_pfiso_citk_vtx_eff_90_bkg","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg = new TH1D("ele_pfiso_simple_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg = new TH1D("ele_pfiso_effarea_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg = new TH1D("ele_pfiso_deltabeta_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg = new TH1D("ele_pfiso_puppi_vtx_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg = new TH1D("ele_pfiso_puppinl_vtx_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg = new TH1D("ele_pfiso_citk_vtx_bkg","PFIso CITK Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_05 = new TH1D("ele_pfiso_simple_vtx_bkg_05","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_05 = new TH1D("ele_pfiso_effarea_vtx_bkg_05","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_05 = new TH1D("ele_pfiso_deltabeta_vtx_bkg_05","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_05 = new TH1D("ele_pfiso_puppi_vtx_bkg_05","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_05 = new TH1D("ele_pfiso_puppinl_vtx_bkg_05","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_05 = new TH1D("ele_pfiso_citk_vtx_bkg_05","PFIso CITK Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_05_eff = new TH1D("ele_pfiso_simple_vtx_bkg_05_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_05_eff = new TH1D("ele_pfiso_effarea_vtx_bkg_05_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_05_eff = new TH1D("ele_pfiso_deltabeta_vtx_bkg_05_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_05_eff = new TH1D("ele_pfiso_puppi_vtx_bkg_05_eff","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_05_eff = new TH1D("ele_pfiso_puppinl_vtx_bkg_05_eff","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_05_eff = new TH1D("ele_pfiso_citk_vtx_bkg_05_eff","PFIso CITK Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_10 = new TH1D("ele_pfiso_simple_vtx_bkg_10","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_10 = new TH1D("ele_pfiso_effarea_vtx_bkg_10","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_10 = new TH1D("ele_pfiso_deltabeta_vtx_bkg_10","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_10 = new TH1D("ele_pfiso_puppi_vtx_bkg_10","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_10 = new TH1D("ele_pfiso_puppinl_vtx_bkg_10","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_10 = new TH1D("ele_pfiso_citk_vtx_bkg_10","PFIso CITK Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_10_eff = new TH1D("ele_pfiso_simple_vtx_bkg_10_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_10_eff = new TH1D("ele_pfiso_effarea_vtx_bkg_10_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_10_eff = new TH1D("ele_pfiso_deltabeta_vtx_bkg_10_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_10_eff = new TH1D("ele_pfiso_puppi_vtx_bkg_10_eff","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_10_eff = new TH1D("ele_pfiso_puppinl_vtx_bkg_10_eff","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_10_eff = new TH1D("ele_pfiso_citk_vtx_bkg_10_eff","PFIso CITK Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_15 = new TH1D("ele_pfiso_simple_vtx_bkg_15","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_15 = new TH1D("ele_pfiso_effarea_vtx_bkg_15","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_15 = new TH1D("ele_pfiso_deltabeta_vtx_bkg_15","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_15 = new TH1D("ele_pfiso_puppi_vtx_bkg_15","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_15 = new TH1D("ele_pfiso_puppinl_vtx_bkg_15","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_15 = new TH1D("ele_pfiso_citk_vtx_bkg_15","PFIso CITK Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_15_eff = new TH1D("ele_pfiso_simple_vtx_bkg_15_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_15_eff = new TH1D("ele_pfiso_effarea_vtx_bkg_15_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_15_eff = new TH1D("ele_pfiso_deltabeta_vtx_bkg_15_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_15_eff = new TH1D("ele_pfiso_puppi_vtx_bkg_15_eff","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_15_eff = new TH1D("ele_pfiso_puppinl_vtx_bkg_15_eff","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_15_eff = new TH1D("ele_pfiso_citk_vtx_bkg_15_eff","PFIso CITK Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_ratio = new TH1D("ele_pfiso_simple_vtx_ratio","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_ratio = new TH1D("ele_pfiso_effarea_vtx_ratio","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_ratio = new TH1D("ele_pfiso_deltabeta_vtx_ratio","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_ratio = new TH1D("ele_pfiso_puppi_vtx_ratio","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_ratio = new TH1D("ele_pfiso_puppinl_vtx_ratio","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_ratio = new TH1D("ele_pfiso_citk_vtx_ratio","PFIso CITK Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_eta_eff = new TH1D("ele_pfiso_simple_eta_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_eff = new TH1D("ele_pfiso_effarea_eta_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_eff = new TH1D("ele_pfiso_deltabeta_eta_eff","PFIso Simple Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_eff = new TH1D("ele_pfiso_puppi_eta_eff","PFIso PUPPI Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_eff = new TH1D("ele_pfiso_puppinl_eta_eff","PFIso PUPPI No Leptond Eta;#eta;Signal Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_eff = new TH1D("ele_pfiso_citk_eta_eff","PFIso CITK Eta;#eta;Signal Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_bkg = new TH1D("ele_pfiso_simple_eta_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_bkg = new TH1D("ele_pfiso_effarea_eta_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_bkg = new TH1D("ele_pfiso_deltabeta_eta_bkg","PFIso Simple Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_bkg = new TH1D("ele_pfiso_puppi_eta_bkg","PFIso PUPPI Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_bkg = new TH1D("ele_pfiso_puppinl_eta_bkg","PFIso PUPPI No Leptons Eta;#eta;Background Efficiency", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_bkg = new TH1D("ele_pfiso_citk_eta_bkg","PFIso CITK Eta;#eta;Background Efficiency", 25,-2.5,2.5);

TH1D *ele_pfiso_simple_eta_ratio = new TH1D("ele_pfiso_simple_eta_ratio","PFIso Simple Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_effarea_eta_ratio = new TH1D("ele_pfiso_effarea_eta_ratio","PFIso Simple Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_deltabeta_eta_ratio = new TH1D("ele_pfiso_deltabeta_eta_ratio","PFIso Simple Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_puppi_eta_ratio = new TH1D("ele_pfiso_puppi_eta_ratio","PFIso PUPPI Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_puppinl_eta_ratio = new TH1D("ele_pfiso_puppinl_eta_ratio","PFIso PUPPI No Leptons Eta;#eta;Signal/Background", 25,-2.5,2.5);
TH1D *ele_pfiso_citk_eta_ratio = new TH1D("ele_pfiso_citk_eta_ratio","PFIso CITK Eta;#eta;Signal/Background", 25,-2.5,2.5);


  //declaring matrices and arrays
   double isolation_simple_vtx[samples][vtx_nbins], isolation_simple_eta[samples][25];
   double isolation_simple_vtx_eff_99[vtx_nbins], isolation_simple_vtx_eff_95[vtx_nbins], isolation_simple_vtx_eff_90[vtx_nbins];
   double isolation_simple_vtx_eff_99_bkg[vtx_nbins], isolation_simple_vtx_eff_95_bkg[vtx_nbins], isolation_simple_vtx_eff_90_bkg[vtx_nbins];
   double isolation_simple_vtx_bkg_05[vtx_nbins], isolation_simple_vtx_bkg_10[vtx_nbins], isolation_simple_vtx_bkg_15[vtx_nbins];
   double isolation_simple_vtx_bkg_05_eff[vtx_nbins], isolation_simple_vtx_bkg_10_eff[vtx_nbins], isolation_simple_vtx_bkg_15_eff[vtx_nbins];


   double isolation_effarea_vtx[samples][vtx_nbins], isolation_effarea_eta[samples][25];
   double isolation_effarea_vtx_eff_99[vtx_nbins], isolation_effarea_vtx_eff_95[vtx_nbins], isolation_effarea_vtx_eff_90[vtx_nbins];
   double isolation_effarea_vtx_eff_99_bkg[vtx_nbins], isolation_effarea_vtx_eff_95_bkg[vtx_nbins], isolation_effarea_vtx_eff_90_bkg[vtx_nbins];
   double isolation_effarea_vtx_bkg_05[vtx_nbins], isolation_effarea_vtx_bkg_10[vtx_nbins], isolation_effarea_vtx_bkg_15[vtx_nbins];
   double isolation_effarea_vtx_bkg_05_eff[vtx_nbins], isolation_effarea_vtx_bkg_10_eff[vtx_nbins], isolation_effarea_vtx_bkg_15_eff[vtx_nbins];

   double isolation_deltabeta_vtx[samples][vtx_nbins], isolation_deltabeta_eta[samples][25];
   double isolation_deltabeta_vtx_eff_99[vtx_nbins], isolation_deltabeta_vtx_eff_95[vtx_nbins], isolation_deltabeta_vtx_eff_90[vtx_nbins];
   double isolation_deltabeta_vtx_eff_99_bkg[vtx_nbins], isolation_deltabeta_vtx_eff_95_bkg[vtx_nbins], isolation_deltabeta_vtx_eff_90_bkg[vtx_nbins];
   double isolation_deltabeta_vtx_bkg_05[vtx_nbins], isolation_deltabeta_vtx_bkg_10[vtx_nbins], isolation_deltabeta_vtx_bkg_15[vtx_nbins];
   double isolation_deltabeta_vtx_bkg_05_eff[vtx_nbins], isolation_deltabeta_vtx_bkg_10_eff[vtx_nbins], isolation_deltabeta_vtx_bkg_15_eff[vtx_nbins];

   double isolation_puppi_vtx[samples][vtx_nbins], isolation_puppi_eta[samples][25];
   double isolation_puppi_vtx_eff_99[vtx_nbins], isolation_puppi_vtx_eff_95[vtx_nbins], isolation_puppi_vtx_eff_90[vtx_nbins];
   double isolation_puppi_vtx_eff_99_bkg[vtx_nbins], isolation_puppi_vtx_eff_95_bkg[vtx_nbins], isolation_puppi_vtx_eff_90_bkg[vtx_nbins];
   double isolation_puppi_vtx_bkg_05[vtx_nbins], isolation_puppi_vtx_bkg_10[vtx_nbins], isolation_puppi_vtx_bkg_15[vtx_nbins];
   double isolation_puppi_vtx_bkg_05_eff[vtx_nbins], isolation_puppi_vtx_bkg_10_eff[vtx_nbins], isolation_puppi_vtx_bkg_15_eff[vtx_nbins];

   double isolation_puppinl_vtx[samples][vtx_nbins], isolation_puppinl_eta[samples][25];
   double isolation_puppinl_vtx_eff_99[vtx_nbins], isolation_puppinl_vtx_eff_95[vtx_nbins], isolation_puppinl_vtx_eff_90[vtx_nbins];
   double isolation_puppinl_vtx_eff_99_bkg[vtx_nbins], isolation_puppinl_vtx_eff_95_bkg[vtx_nbins], isolation_puppinl_vtx_eff_90_bkg[vtx_nbins];
   double isolation_puppinl_vtx_bkg_05[vtx_nbins], isolation_puppinl_vtx_bkg_10[vtx_nbins], isolation_puppinl_vtx_bkg_15[vtx_nbins];
   double isolation_puppinl_vtx_bkg_05_eff[vtx_nbins], isolation_puppinl_vtx_bkg_10_eff[vtx_nbins], isolation_puppinl_vtx_bkg_15_eff[vtx_nbins];

   double isolation_citk_vtx[samples][vtx_nbins], isolation_citk_eta[samples][25];
   double isolation_citk_vtx_eff_99[vtx_nbins], isolation_citk_vtx_eff_95[vtx_nbins], isolation_citk_vtx_eff_90[vtx_nbins];
   double isolation_citk_vtx_eff_99_bkg[vtx_nbins], isolation_citk_vtx_eff_95_bkg[vtx_nbins], isolation_citk_vtx_eff_90_bkg[vtx_nbins];
   double isolation_citk_vtx_bkg_05[vtx_nbins], isolation_citk_vtx_bkg_10[vtx_nbins], isolation_citk_vtx_bkg_15[vtx_nbins];
   double isolation_citk_vtx_bkg_05_eff[vtx_nbins], isolation_citk_vtx_bkg_10_eff[vtx_nbins], isolation_citk_vtx_bkg_15_eff[vtx_nbins];

for (int s = 0; s <= 1; ++s)
{
   for (int y=0; y<22; ++y)
	{
	isolation_simple_vtx[s][y] = 0;
	isolation_effarea_vtx[s][y] = 0;
	isolation_deltabeta_vtx[s][y] = 0;
	isolation_puppi_vtx[s][y] = 0;
	isolation_puppinl_vtx[s][y] = 0;
	isolation_citk_vtx[s][y] = 0;
	}
	
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

   for (int y=0; y<22; ++y)
	{
	isolation_simple_vtx_eff_99[y] = 0;
	isolation_effarea_vtx_eff_99[y] = 0;
	isolation_deltabeta_vtx_eff_99[y] = 0;
	isolation_puppi_vtx_eff_99[y] = 0;
	isolation_puppinl_vtx_eff_99[y] = 0;
	isolation_citk_vtx_eff_99[y] = 0;

	isolation_simple_vtx_eff_99_bkg[y] = 0;
	isolation_effarea_vtx_eff_99_bkg[y] = 0;
	isolation_deltabeta_vtx_eff_99_bkg[y] = 0;
	isolation_puppi_vtx_eff_99_bkg[y] = 0;
	isolation_puppinl_vtx_eff_99_bkg[y] = 0;
	isolation_citk_vtx_eff_99_bkg[y] = 0;

	isolation_simple_vtx_eff_95[y] = 0;
	isolation_effarea_vtx_eff_95[y] = 0;
	isolation_deltabeta_vtx_eff_95[y] = 0;
	isolation_puppi_vtx_eff_95[y] = 0;
	isolation_puppinl_vtx_eff_95[y] = 0;
	isolation_citk_vtx_eff_95[y] = 0;

	isolation_simple_vtx_eff_95_bkg[y] = 0;
	isolation_effarea_vtx_eff_95_bkg[y] = 0;
	isolation_deltabeta_vtx_eff_95_bkg[y] = 0;
	isolation_puppi_vtx_eff_95_bkg[y] = 0;
	isolation_puppinl_vtx_eff_95_bkg[y] = 0;
	isolation_citk_vtx_eff_95_bkg[y] = 0;

	isolation_simple_vtx_eff_90[y] = 0;
	isolation_effarea_vtx_eff_90[y] = 0;
	isolation_deltabeta_vtx_eff_90[y] = 0;
	isolation_puppi_vtx_eff_90[y] = 0;
	isolation_puppinl_vtx_eff_90[y] = 0;
	isolation_citk_vtx_eff_90[y] = 0;

	isolation_simple_vtx_eff_90_bkg[y] = 0;
	isolation_effarea_vtx_eff_90_bkg[y] = 0;
	isolation_deltabeta_vtx_eff_90_bkg[y] = 0;
	isolation_puppi_vtx_eff_90_bkg[y] = 0;
	isolation_puppinl_vtx_eff_90_bkg[y] = 0;
	isolation_citk_vtx_eff_90_bkg[y] = 0;

	isolation_simple_vtx_bkg_05[y] = 0;
	isolation_effarea_vtx_bkg_05[y] = 0;
	isolation_deltabeta_vtx_bkg_05[y] = 0;
	isolation_puppi_vtx_bkg_05[y] = 0;
	isolation_puppinl_vtx_bkg_05[y] = 0;
	isolation_citk_vtx_bkg_05[y] = 0;

	isolation_simple_vtx_bkg_05_eff[y] = 0;
	isolation_effarea_vtx_bkg_05_eff[y] = 0;
	isolation_deltabeta_vtx_bkg_05_eff[y] = 0;
	isolation_puppi_vtx_bkg_05_eff[y] = 0;
	isolation_puppinl_vtx_bkg_05_eff[y] = 0;
	isolation_citk_vtx_bkg_05_eff[y] = 0;

	isolation_simple_vtx_bkg_10[y] = 0;
	isolation_effarea_vtx_bkg_10[y] = 0;
	isolation_deltabeta_vtx_bkg_10[y] = 0;
	isolation_puppi_vtx_bkg_10[y] = 0;
	isolation_puppinl_vtx_bkg_10[y] = 0;
	isolation_citk_vtx_bkg_10[y] = 0;

	isolation_simple_vtx_bkg_10_eff[y] = 0;
	isolation_effarea_vtx_bkg_10_eff[y] = 0;
	isolation_deltabeta_vtx_bkg_10_eff[y] = 0;
	isolation_puppi_vtx_bkg_10_eff[y] = 0;
	isolation_puppinl_vtx_bkg_10_eff[y] = 0;
	isolation_citk_vtx_bkg_10_eff[y] = 0;

	isolation_simple_vtx_bkg_15[y] = 0;
	isolation_effarea_vtx_bkg_15[y] = 0;
	isolation_deltabeta_vtx_bkg_15[y] = 0;
	isolation_puppi_vtx_bkg_15[y] = 0;
	isolation_puppinl_vtx_bkg_15[y] = 0;
	isolation_citk_vtx_bkg_15[y] = 0;

	isolation_simple_vtx_bkg_15_eff[y] = 0;
	isolation_effarea_vtx_bkg_15_eff[y] = 0;
	isolation_deltabeta_vtx_bkg_15_eff[y] = 0;
	isolation_puppi_vtx_bkg_15_eff[y] = 0;
	isolation_puppinl_vtx_bkg_15_eff[y] = 0;
	isolation_citk_vtx_bkg_15_eff[y] = 0;
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

  //Iso Simple VS vtx
  TH2D *iso_simple_vs_vtx1 = 0;
  TH2D *iso_simple_vs_vtx2 = 0;

  f1->GetObject("iso_simple_vs_vtx",iso_simple_vs_vtx1);
  if (iso_simple_vs_vtx1 == 0) { cout << "iso_simple_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_simple_vs_vtx",iso_simple_vs_vtx2);
  if (iso_simple_vs_vtx2 == 0) { cout << "iso_simple_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_simple_vs_vtx1, "output/", prefix[0] + "_iso_simple_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_simple_vs_vtx2, "output/", prefix[1] + "_iso_simple_vs_vtx", prefix[1], "top_right", true);

  //Iso Effective Area VS Eta
  TH2D *iso_effarea_vs_eta1 = 0;
  TH2D *iso_effarea_vs_eta2 = 0;

  f1->GetObject("iso_effarea_vs_eta",iso_effarea_vs_eta1);
  if (iso_effarea_vs_eta1 == 0) { cout << "iso_effarea_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_effarea_vs_eta",iso_effarea_vs_eta2);
  if (iso_effarea_vs_eta2 == 0) { cout << "iso_effarea_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_effarea_vs_eta1, "output/", prefix[0] + "_iso_effarea_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_effarea_vs_eta2, "output/", prefix[1] + "_iso_effarea_vs_eta", prefix[1], "top_right", true);


  //Iso Effective Area VS vtx
  TH2D *iso_effarea_vs_vtx1 = 0;
  TH2D *iso_effarea_vs_vtx2 = 0;

  f1->GetObject("iso_effarea_vs_vtx",iso_effarea_vs_vtx1);
  if (iso_effarea_vs_vtx1 == 0) { cout << "iso_effarea_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_effarea_vs_vtx",iso_effarea_vs_vtx2);
  if (iso_effarea_vs_vtx2 == 0) { cout << "iso_effarea_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_effarea_vs_vtx1, "output/", prefix[0] + "_iso_effarea_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_effarea_vs_vtx2, "output/", prefix[1] + "_iso_effarea_vs_vtx", prefix[1], "top_right", true);

  //Iso Delta Beta VS Eta
  TH2D *iso_deltabeta_vs_eta1 = 0;
  TH2D *iso_deltabeta_vs_eta2 = 0;

  f1->GetObject("iso_deltabeta_vs_eta",iso_deltabeta_vs_eta1);
  if (iso_deltabeta_vs_eta1 == 0) { cout << "iso_deltabeta_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_deltabeta_vs_eta",iso_deltabeta_vs_eta2);
  if (iso_deltabeta_vs_eta2 == 0) { cout << "iso_deltabeta_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_deltabeta_vs_eta1, "output/", prefix[0] + "_iso_deltabeta_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_deltabeta_vs_eta2, "output/", prefix[1] + "_iso_deltabeta_vs_eta", prefix[1], "top_right", true);

  //Iso Delta Beta VS vtx
  TH2D *iso_deltabeta_vs_vtx1 = 0;
  TH2D *iso_deltabeta_vs_vtx2 = 0;

  f1->GetObject("iso_deltabeta_vs_vtx",iso_deltabeta_vs_vtx1);
  if (iso_deltabeta_vs_vtx1 == 0) { cout << "iso_deltabeta_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_deltabeta_vs_vtx",iso_deltabeta_vs_vtx2);
  if (iso_deltabeta_vs_vtx2 == 0) { cout << "iso_deltabeta_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_deltabeta_vs_vtx1, "output/", prefix[0] + "_iso_deltabeta_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_deltabeta_vs_vtx2, "output/", prefix[1] + "_iso_deltabeta_vs_vtx", prefix[1], "top_right", true);

  //Iso PUPPI VS Eta
  TH2D *iso_puppi_vs_eta1 = 0;
  TH2D *iso_puppi_vs_eta2 = 0;

  f1->GetObject("iso_puppi_vs_eta",iso_puppi_vs_eta1);
  if (iso_puppi_vs_eta1 == 0) { cout << "iso_puppi_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_puppi_vs_eta",iso_puppi_vs_eta2);
  if (iso_puppi_vs_eta2 == 0) { cout << "iso_puppi_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_puppi_vs_eta1, "output/", prefix[0] + "_iso_puppi_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppi_vs_eta2, "output/", prefix[1] + "_iso_puppi_vs_eta", prefix[1], "top_right", true);

  //Iso PUPPI VS vtx
  TH2D *iso_puppi_vs_vtx1 = 0;
  TH2D *iso_puppi_vs_vtx2 = 0;

  f1->GetObject("iso_puppi_vs_vtx",iso_puppi_vs_vtx1);
  if (iso_puppi_vs_vtx1 == 0) { cout << "iso_puppi_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_puppi_vs_vtx",iso_puppi_vs_vtx2);
  if (iso_puppi_vs_vtx2 == 0) { cout << "iso_puppi_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_puppi_vs_vtx1, "output/", prefix[0] + "_iso_puppi_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppi_vs_vtx2, "output/", prefix[1] + "_iso_puppi_vs_vtx", prefix[1], "top_right", true);

  //Iso PUPPI No Leptons VS Eta
  TH2D *iso_puppinl_vs_eta1 = 0;
  TH2D *iso_puppinl_vs_eta2 = 0;

  f1->GetObject("iso_puppinl_vs_eta",iso_puppinl_vs_eta1);
  if (iso_puppinl_vs_eta1 == 0) { cout << "iso_puppinl_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_puppinl_vs_eta",iso_puppinl_vs_eta2);
  if (iso_puppinl_vs_eta2 == 0) { cout << "iso_puppinl_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_puppinl_vs_eta1, "output/", prefix[0] + "_iso_puppinl_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppinl_vs_eta2, "output/", prefix[1] + "_iso_puppinl_vs_eta", prefix[1], "top_right", true);

  //Iso PUPPI No Leptons VS vtx
  TH2D *iso_puppinl_vs_vtx1 = 0;
  TH2D *iso_puppinl_vs_vtx2 = 0;

  f1->GetObject("iso_puppinl_vs_vtx",iso_puppinl_vs_vtx1);
  if (iso_puppinl_vs_vtx1 == 0) { cout << "iso_puppinl_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_puppinl_vs_vtx",iso_puppinl_vs_vtx2);
  if (iso_puppinl_vs_vtx2 == 0) { cout << "iso_puppinl_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_puppinl_vs_vtx1, "output/", prefix[0] + "_iso_puppinl_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppinl_vs_vtx2, "output/", prefix[1] + "_iso_puppinl_vs_vtx", prefix[1], "top_right", true);

  //Iso citk VS eta
  TH2D *iso_citk_vs_eta1 = 0;
  TH2D *iso_citk_vs_eta2 = 0;

  f1->GetObject("iso_citk_vs_eta",iso_citk_vs_eta1);
  if (iso_citk_vs_eta1 == 0) { cout << "iso_citk_vs_eta not found!" << endl; return; }
  f2->GetObject("iso_citk_vs_eta",iso_citk_vs_eta2);
  if (iso_citk_vs_eta2 == 0) { cout << "iso_citk_vs_eta not found!" << endl; return; }


plot_2dhistogram(iso_citk_vs_eta1, "output/", prefix[0] + "_iso_citk_vs_eta", prefix[0], "top_right", true);
plot_2dhistogram(iso_citk_vs_eta2, "output/", prefix[1] + "_iso_citk_vs_eta", prefix[1], "top_right", true);


  //Iso citk VS vtx
  TH2D *iso_citk_vs_vtx1 = 0;
  TH2D *iso_citk_vs_vtx2 = 0;

  f1->GetObject("iso_citk_vs_vtx",iso_citk_vs_vtx1);
  if (iso_citk_vs_vtx1 == 0) { cout << "iso_citk_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_citk_vs_vtx",iso_citk_vs_vtx2);
  if (iso_citk_vs_vtx2 == 0) { cout << "iso_citk_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_citk_vs_vtx1, "output/", prefix[0] + "_iso_citk_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_citk_vs_vtx2, "output/", prefix[1] + "_iso_citk_vs_vtx", prefix[1], "top_right", true);


  //compute the differential distributions
  int nbins = 0;

   nbins = iso_simple_vs_vtx1->GetNbinsY();

   if (show_steps) { cout << "N bins = " << nbins << endl; }

for (int x=1; x<=nbins; x++)
	{
	isolation_simple_vtx[0][x-1] = iso_simple_vs_vtx1->Integral(0,working_point,x,x)/iso_simple_vs_vtx1->Integral(0,2000,x,x);
	isolation_effarea_vtx[0][x-1] = iso_effarea_vs_vtx1->Integral(0,working_point,x,x)/iso_effarea_vs_vtx1->Integral(0,2000,x,x);
	isolation_deltabeta_vtx[0][x-1] = iso_deltabeta_vs_vtx1->Integral(0,working_point,x,x)/iso_deltabeta_vs_vtx1->Integral(0,2000,x,x);
	isolation_puppi_vtx[0][x-1] = iso_puppi_vs_vtx1->Integral(0,working_point,x,x)/iso_puppi_vs_vtx1->Integral(0,2000,x,x);
	isolation_puppinl_vtx[0][x-1] = iso_puppinl_vs_vtx1->Integral(0,working_point,x,x)/iso_puppinl_vs_vtx1->Integral(0,2000,x,x);
	isolation_citk_vtx[0][x-1] = iso_citk_vs_vtx1->Integral(0,working_point,x,x)/iso_citk_vs_vtx1->Integral(0,2000,x,x);

	isolation_simple_vtx[1][x-1] = iso_simple_vs_vtx2->Integral(0,working_point,x,x)/iso_simple_vs_vtx2->Integral(0,2000,x,x);
	isolation_effarea_vtx[1][x-1] = iso_effarea_vs_vtx2->Integral(0,working_point,x,x)/iso_effarea_vs_vtx2->Integral(0,2000,x,x);
	isolation_deltabeta_vtx[1][x-1] = iso_deltabeta_vs_vtx2->Integral(0,working_point,x,x)/iso_deltabeta_vs_vtx2->Integral(0,2000,x,x);
	isolation_puppi_vtx[1][x-1] = iso_puppi_vs_vtx2->Integral(0,working_point,x,x)/iso_puppi_vs_vtx2->Integral(0,2000,x,x);
	isolation_puppinl_vtx[1][x-1] = iso_puppinl_vs_vtx2->Integral(0,working_point,x,x)/iso_puppinl_vs_vtx2->Integral(0,2000,x,x);
	isolation_citk_vtx[1][x-1] = iso_citk_vs_vtx2->Integral(0,working_point,x,x)/iso_citk_vs_vtx2->Integral(0,2000,x,x);

	}


for (int x = 1; x <= 2000; x++)
	{
	if (iso_simple_vs_vtx2->Integral(0,x,1,nbins)/iso_simple_vs_vtx2->Integral(0,2000,1,nbins) > .99 and isolation_simple_vtx_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 99% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_vtx_eff_99[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			isolation_simple_vtx_eff_99_bkg[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_simple_vtx_eff_99[y-1] << endl; }
			}
		}

	if (iso_simple_vs_vtx2->Integral(0,x,1,nbins)/iso_simple_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_simple_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 95% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_vtx_eff_95[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			isolation_simple_vtx_eff_95_bkg[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
			}
		}

	if (iso_simple_vs_vtx2->Integral(0,x,1,nbins)/iso_simple_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_simple_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 90% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_vtx_eff_90[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			isolation_simple_vtx_eff_90_bkg[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
			}
		}

        if (test and x < 200) { cout << "bin " << x << " = " << iso_effarea_vs_vtx2->Integral(0,x,1,nbins)/iso_effarea_vs_vtx2->Integral(0,2000,1,nbins) << endl; }

if (iso_effarea_vs_vtx2->Integral(0,x,1,nbins)/iso_effarea_vs_vtx2->Integral(0,2000,1,nbins) > .99 and isolation_effarea_vtx_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 99% effeciency point for the effarea method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_vtx_eff_99[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			isolation_effarea_vtx_eff_99_bkg[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_effarea_vs_vtx2->Integral(0,x,1,nbins)/iso_effarea_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_effarea_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 95% effeciency point for the effarea method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_vtx_eff_95[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			isolation_effarea_vtx_eff_95_bkg[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_effarea_vs_vtx2->Integral(0,x,1,nbins)/iso_effarea_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_effarea_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 90% effeciency point for the effarea method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_vtx_eff_90[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			isolation_effarea_vtx_eff_90_bkg[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_deltabeta_vs_vtx2->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx2->Integral(0,2000,1,nbins) > .99 and isolation_deltabeta_vtx_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 99% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_vtx_eff_99[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			isolation_deltabeta_vtx_eff_99_bkg[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_deltabeta_vs_vtx2->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_deltabeta_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 95% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_vtx_eff_95[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			isolation_deltabeta_vtx_eff_95_bkg[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_deltabeta_vs_vtx2->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_deltabeta_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 90% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_vtx_eff_90[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			isolation_deltabeta_vtx_eff_90_bkg[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_puppi_vs_vtx2->Integral(0,x,1,nbins)/iso_puppi_vs_vtx2->Integral(0,2000,1,nbins) > .99 and isolation_puppi_vtx_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 99% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_vtx_eff_99[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			isolation_puppi_vtx_eff_99_bkg[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_puppi_vs_vtx2->Integral(0,x,1,nbins)/iso_puppi_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_puppi_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 95% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_vtx_eff_95[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			isolation_puppi_vtx_eff_95_bkg[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_puppi_vs_vtx2->Integral(0,x,1,nbins)/iso_puppi_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_puppi_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 90% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_vtx_eff_90[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			isolation_puppi_vtx_eff_90_bkg[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_puppinl_vs_vtx2->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx2->Integral(0,2000,1,nbins) > .99 and isolation_puppinl_vtx_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 99% effeciency point for the puppi no leptons  method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_vtx_eff_99[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			isolation_puppinl_vtx_eff_99_bkg[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_puppinl_vs_vtx2->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_puppinl_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 95% effeciency point for the puppi no leptons  method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_vtx_eff_95[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			isolation_puppinl_vtx_eff_95_bkg[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_puppinl_vs_vtx2->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_puppinl_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 90% effeciency point for the puppi no leptons  method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_vtx_eff_90[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			isolation_puppinl_vtx_eff_90_bkg[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_citk_vs_vtx2->Integral(0,x,1,nbins)/iso_citk_vs_vtx2->Integral(0,2000,1,nbins) > .99 and isolation_citk_vtx_eff_99[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 99% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_vtx_eff_99[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			isolation_citk_vtx_eff_99_bkg[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_citk_vs_vtx2->Integral(0,x,1,nbins)/iso_citk_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_citk_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 95% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_vtx_eff_95[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			isolation_citk_vtx_eff_95_bkg[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
			}
		}

if (iso_citk_vs_vtx2->Integral(0,x,1,nbins)/iso_citk_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_citk_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 90% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_vtx_eff_90[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			isolation_citk_vtx_eff_90_bkg[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
			}
		}

	if (iso_simple_vs_vtx1->Integral(0,x,1,nbins)/iso_simple_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_simple_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 5% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_vtx_bkg_05[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
			isolation_simple_vtx_bkg_05_eff[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_simple_vtx_bkg_05[y-1] << endl; }
			}
		}

	if (iso_simple_vs_vtx1->Integral(0,x,1,nbins)/iso_simple_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_simple_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 10% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_vtx_bkg_10[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
			isolation_simple_vtx_bkg_10_eff[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_simple_vs_vtx1->Integral(0,x,1,nbins)/iso_simple_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_simple_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 15% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_simple_vtx_bkg_15[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
			isolation_simple_vtx_bkg_15_eff[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_effarea_vs_vtx1->Integral(0,x,1,nbins)/iso_effarea_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_effarea_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 05% background point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_vtx_bkg_05[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
			isolation_effarea_vtx_bkg_05_eff[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_effarea_vs_vtx1->Integral(0,x,1,nbins)/iso_effarea_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_effarea_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 10% background point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_vtx_bkg_10[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
			isolation_effarea_vtx_bkg_10_eff[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_effarea_vs_vtx1->Integral(0,x,1,nbins)/iso_effarea_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_effarea_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 15% background point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_vtx_bkg_15[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
			isolation_effarea_vtx_bkg_15_eff[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_deltabeta_vs_vtx1->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_deltabeta_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 05% background point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_vtx_bkg_05[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
			isolation_deltabeta_vtx_bkg_05_eff[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_deltabeta_vs_vtx1->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_deltabeta_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 10% background point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_vtx_bkg_10[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
			isolation_deltabeta_vtx_bkg_10_eff[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_deltabeta_vs_vtx1->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_deltabeta_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 15% background point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_vtx_bkg_15[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
			isolation_deltabeta_vtx_bkg_15_eff[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppi_vs_vtx1->Integral(0,x,1,nbins)/iso_puppi_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_puppi_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 05% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_vtx_bkg_05[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
			isolation_puppi_vtx_bkg_05_eff[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppi_vs_vtx1->Integral(0,x,1,nbins)/iso_puppi_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_puppi_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 10% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_vtx_bkg_10[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
			isolation_puppi_vtx_bkg_10_eff[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppi_vs_vtx1->Integral(0,x,1,nbins)/iso_puppi_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_puppi_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 15% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_vtx_bkg_15[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
			isolation_puppi_vtx_bkg_15_eff[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppinl_vs_vtx1->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_puppinl_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 05% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_vtx_bkg_05[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
			isolation_puppinl_vtx_bkg_05_eff[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppinl_vs_vtx1->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_puppinl_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 10% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_vtx_bkg_10[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
			isolation_puppinl_vtx_bkg_10_eff[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppinl_vs_vtx1->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_puppinl_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 15% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_vtx_bkg_15[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
			isolation_puppinl_vtx_bkg_15_eff[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_citk_vs_vtx1->Integral(0,x,1,nbins)/iso_citk_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_citk_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 10% background point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_vtx_bkg_10[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
			isolation_citk_vtx_bkg_10_eff[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppinl_vs_vtx1->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_puppinl_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "Found vtx 15% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppinl_vtx_bkg_15[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
			isolation_puppinl_vtx_bkg_15_eff[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			}
		}


	}

	
   nbins = iso_simple_vs_eta1->GetNbinsY();

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

   for (int x=0; x<=nbins; x++)
	{
	ele_pfiso_simple_vtx_eff->SetBinContent(x+1,isolation_simple_vtx[1][x]);
	ele_pfiso_effarea_vtx_eff->SetBinContent(x+1,isolation_effarea_vtx[1][x]);
	ele_pfiso_deltabeta_vtx_eff->SetBinContent(x+1,isolation_deltabeta_vtx[1][x]);
	ele_pfiso_puppi_vtx_eff->SetBinContent(x+1,isolation_puppi_vtx[1][x]);
	ele_pfiso_puppinl_vtx_eff->SetBinContent(x+1,isolation_puppinl_vtx[1][x]);
	ele_pfiso_citk_vtx_eff->SetBinContent(x+1,isolation_citk_vtx[1][x]);
	ele_pfiso_simple_vtx_eff->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_eff->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_eff->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_eff->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_eff->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_eff->SetBinError(x+1,0);

	ele_pfiso_simple_vtx_bkg->SetBinContent(x+1,isolation_simple_vtx[0][x]);
	ele_pfiso_effarea_vtx_bkg->SetBinContent(x+1,isolation_effarea_vtx[0][x]);
	ele_pfiso_deltabeta_vtx_bkg->SetBinContent(x+1,isolation_deltabeta_vtx[0][x]);
	ele_pfiso_puppi_vtx_bkg->SetBinContent(x+1,isolation_puppi_vtx[0][x]);
	ele_pfiso_puppinl_vtx_bkg->SetBinContent(x+1,isolation_puppinl_vtx[0][x]);
	ele_pfiso_citk_vtx_bkg->SetBinContent(x+1,isolation_citk_vtx[0][x]);
	ele_pfiso_simple_vtx_bkg->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_bkg->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_bkg->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_bkg->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_bkg->SetBinError(x+1,0);

	ele_pfiso_simple_vtx_ratio->SetBinContent(x+1,isolation_simple_vtx[1][x]/isolation_simple_vtx[0][x]);
	ele_pfiso_effarea_vtx_ratio->SetBinContent(x+1,isolation_effarea_vtx[1][x]/isolation_effarea_vtx[0][x]);
	ele_pfiso_deltabeta_vtx_ratio->SetBinContent(x+1,isolation_deltabeta_vtx[1][x]/isolation_deltabeta_vtx[0][x]);
	ele_pfiso_puppi_vtx_ratio->SetBinContent(x+1,isolation_puppi_vtx[1][x]/isolation_puppi_vtx[0][x]);
	ele_pfiso_puppinl_vtx_ratio->SetBinContent(x+1,isolation_puppinl_vtx[1][x]/isolation_puppinl_vtx[0][x]);
	ele_pfiso_citk_vtx_ratio->SetBinContent(x+1,isolation_citk_vtx[1][x]/isolation_citk_vtx[0][x]);
	ele_pfiso_simple_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_ratio->SetBinError(x+1,0);

	ele_pfiso_simple_vtx_eff_99->SetBinContent(x+1,isolation_simple_vtx_eff_99[x]);
	ele_pfiso_simple_vtx_eff_99->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_eff_95->SetBinContent(x+1,isolation_simple_vtx_eff_95[x]);
	ele_pfiso_simple_vtx_eff_95->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_eff_90->SetBinContent(x+1,isolation_simple_vtx_eff_90[x]);
	ele_pfiso_simple_vtx_eff_90->SetBinError(x+1,0);

	ele_pfiso_simple_vtx_eff_99_bkg->SetBinContent(x+1,isolation_simple_vtx_eff_99_bkg[x]);
	ele_pfiso_simple_vtx_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_eff_95_bkg->SetBinContent(x+1,isolation_simple_vtx_eff_95_bkg[x]);
	ele_pfiso_simple_vtx_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_eff_90_bkg->SetBinContent(x+1,isolation_simple_vtx_eff_90_bkg[x]);
	ele_pfiso_simple_vtx_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_effarea_vtx_eff_99->SetBinContent(x+1,isolation_effarea_vtx_eff_99[x]);
	ele_pfiso_effarea_vtx_eff_99->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_eff_95->SetBinContent(x+1,isolation_effarea_vtx_eff_95[x]);
	ele_pfiso_effarea_vtx_eff_95->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_eff_90->SetBinContent(x+1,isolation_effarea_vtx_eff_90[x]);
	ele_pfiso_effarea_vtx_eff_90->SetBinError(x+1,0);

	ele_pfiso_effarea_vtx_eff_99_bkg->SetBinContent(x+1,isolation_effarea_vtx_eff_99_bkg[x]);
	ele_pfiso_effarea_vtx_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_eff_95_bkg->SetBinContent(x+1,isolation_effarea_vtx_eff_95_bkg[x]);
	ele_pfiso_effarea_vtx_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_eff_90_bkg->SetBinContent(x+1,isolation_effarea_vtx_eff_90_bkg[x]);
	ele_pfiso_effarea_vtx_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_deltabeta_vtx_eff_99->SetBinContent(x+1,isolation_deltabeta_vtx_eff_99[x]);
	ele_pfiso_deltabeta_vtx_eff_99->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_eff_95->SetBinContent(x+1,isolation_deltabeta_vtx_eff_95[x]);
	ele_pfiso_deltabeta_vtx_eff_95->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_eff_90->SetBinContent(x+1,isolation_deltabeta_vtx_eff_90[x]);
	ele_pfiso_deltabeta_vtx_eff_90->SetBinError(x+1,0);

	ele_pfiso_deltabeta_vtx_eff_99_bkg->SetBinContent(x+1,isolation_deltabeta_vtx_eff_99_bkg[x]);
	ele_pfiso_deltabeta_vtx_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_eff_95_bkg->SetBinContent(x+1,isolation_deltabeta_vtx_eff_95_bkg[x]);
	ele_pfiso_deltabeta_vtx_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_eff_90_bkg->SetBinContent(x+1,isolation_deltabeta_vtx_eff_90_bkg[x]);
	ele_pfiso_deltabeta_vtx_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_puppi_vtx_eff_99->SetBinContent(x+1,isolation_puppi_vtx_eff_99[x]);
	ele_pfiso_puppi_vtx_eff_99->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_eff_95->SetBinContent(x+1,isolation_puppi_vtx_eff_95[x]);
	ele_pfiso_puppi_vtx_eff_95->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_eff_90->SetBinContent(x+1,isolation_puppi_vtx_eff_90[x]);
	ele_pfiso_puppi_vtx_eff_90->SetBinError(x+1,0);

	ele_pfiso_puppi_vtx_eff_99_bkg->SetBinContent(x+1,isolation_puppi_vtx_eff_99_bkg[x]);
	ele_pfiso_puppi_vtx_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_eff_95_bkg->SetBinContent(x+1,isolation_puppi_vtx_eff_95_bkg[x]);
	ele_pfiso_puppi_vtx_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_eff_90_bkg->SetBinContent(x+1,isolation_puppi_vtx_eff_90_bkg[x]);
	ele_pfiso_puppi_vtx_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_puppinl_vtx_eff_99->SetBinContent(x+1,isolation_puppinl_vtx_eff_99[x]);
	ele_pfiso_puppinl_vtx_eff_99->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_eff_95->SetBinContent(x+1,isolation_puppinl_vtx_eff_95[x]);
	ele_pfiso_puppinl_vtx_eff_95->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_eff_90->SetBinContent(x+1,isolation_puppinl_vtx_eff_90[x]);
	ele_pfiso_puppinl_vtx_eff_90->SetBinError(x+1,0);

	ele_pfiso_puppinl_vtx_eff_99_bkg->SetBinContent(x+1,isolation_puppinl_vtx_eff_99_bkg[x]);
	ele_pfiso_puppinl_vtx_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_eff_95_bkg->SetBinContent(x+1,isolation_puppinl_vtx_eff_95_bkg[x]);
	ele_pfiso_puppinl_vtx_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_eff_90_bkg->SetBinContent(x+1,isolation_puppinl_vtx_eff_90_bkg[x]);
	ele_pfiso_puppinl_vtx_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_citk_vtx_eff_99->SetBinContent(x+1,isolation_citk_vtx_eff_99[x]);
	ele_pfiso_citk_vtx_eff_99->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_eff_95->SetBinContent(x+1,isolation_citk_vtx_eff_95[x]);
	ele_pfiso_citk_vtx_eff_95->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_eff_90->SetBinContent(x+1,isolation_citk_vtx_eff_90[x]);
	ele_pfiso_citk_vtx_eff_90->SetBinError(x+1,0);

	ele_pfiso_citk_vtx_eff_99_bkg->SetBinContent(x+1,isolation_citk_vtx_eff_99_bkg[x]);
	ele_pfiso_citk_vtx_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_eff_95_bkg->SetBinContent(x+1,isolation_citk_vtx_eff_95_bkg[x]);
	ele_pfiso_citk_vtx_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_eff_90_bkg->SetBinContent(x+1,isolation_citk_vtx_eff_90_bkg[x]);
	ele_pfiso_citk_vtx_eff_90_bkg->SetBinError(x+1,0);

	ele_pfiso_simple_vtx_bkg_05->SetBinContent(x+1,isolation_simple_vtx_bkg_05[x]);
	ele_pfiso_simple_vtx_bkg_05->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_bkg_10->SetBinContent(x+1,isolation_simple_vtx_bkg_10[x]);
	ele_pfiso_simple_vtx_bkg_10->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_bkg_15->SetBinContent(x+1,isolation_simple_vtx_bkg_15[x]);
	ele_pfiso_simple_vtx_bkg_15->SetBinError(x+1,0);

	ele_pfiso_simple_vtx_bkg_05_eff->SetBinContent(x+1,isolation_simple_vtx_bkg_05_eff[x]);
	ele_pfiso_simple_vtx_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_bkg_10_eff->SetBinContent(x+1,isolation_simple_vtx_bkg_10_eff[x]);
	ele_pfiso_simple_vtx_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_bkg_15_eff->SetBinContent(x+1,isolation_simple_vtx_bkg_15_eff[x]);
	ele_pfiso_simple_vtx_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_effarea_vtx_bkg_05->SetBinContent(x+1,isolation_effarea_vtx_bkg_05[x]);
	ele_pfiso_effarea_vtx_bkg_05->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_bkg_10->SetBinContent(x+1,isolation_effarea_vtx_bkg_10[x]);
	ele_pfiso_effarea_vtx_bkg_10->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_bkg_15->SetBinContent(x+1,isolation_effarea_vtx_bkg_15[x]);
	ele_pfiso_effarea_vtx_bkg_15->SetBinError(x+1,0);

	ele_pfiso_effarea_vtx_bkg_05_eff->SetBinContent(x+1,isolation_effarea_vtx_bkg_05_eff[x]);
	ele_pfiso_effarea_vtx_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_bkg_10_eff->SetBinContent(x+1,isolation_effarea_vtx_bkg_10_eff[x]);
	ele_pfiso_effarea_vtx_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_bkg_15_eff->SetBinContent(x+1,isolation_effarea_vtx_bkg_15_eff[x]);
	ele_pfiso_effarea_vtx_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_deltabeta_vtx_bkg_05->SetBinContent(x+1,isolation_deltabeta_vtx_bkg_05[x]);
	ele_pfiso_deltabeta_vtx_bkg_05->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_bkg_10->SetBinContent(x+1,isolation_deltabeta_vtx_bkg_10[x]);
	ele_pfiso_deltabeta_vtx_bkg_10->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_bkg_15->SetBinContent(x+1,isolation_deltabeta_vtx_bkg_15[x]);
	ele_pfiso_deltabeta_vtx_bkg_15->SetBinError(x+1,0);

	ele_pfiso_deltabeta_vtx_bkg_05_eff->SetBinContent(x+1,isolation_deltabeta_vtx_bkg_05_eff[x]);
	ele_pfiso_deltabeta_vtx_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_bkg_10_eff->SetBinContent(x+1,isolation_deltabeta_vtx_bkg_10_eff[x]);
	ele_pfiso_deltabeta_vtx_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_bkg_15_eff->SetBinContent(x+1,isolation_deltabeta_vtx_bkg_15_eff[x]);
	ele_pfiso_deltabeta_vtx_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_puppi_vtx_bkg_05->SetBinContent(x+1,isolation_puppi_vtx_bkg_05[x]);
	ele_pfiso_puppi_vtx_bkg_05->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_bkg_10->SetBinContent(x+1,isolation_puppi_vtx_bkg_10[x]);
	ele_pfiso_puppi_vtx_bkg_10->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_bkg_15->SetBinContent(x+1,isolation_puppi_vtx_bkg_15[x]);
	ele_pfiso_puppi_vtx_bkg_15->SetBinError(x+1,0);

	ele_pfiso_puppi_vtx_bkg_05_eff->SetBinContent(x+1,isolation_puppi_vtx_bkg_05_eff[x]);
	ele_pfiso_puppi_vtx_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_bkg_10_eff->SetBinContent(x+1,isolation_puppi_vtx_bkg_10_eff[x]);
	ele_pfiso_puppi_vtx_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_bkg_15_eff->SetBinContent(x+1,isolation_puppi_vtx_bkg_15_eff[x]);
	ele_pfiso_puppi_vtx_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_puppinl_vtx_bkg_05->SetBinContent(x+1,isolation_puppinl_vtx_bkg_05[x]);
	ele_pfiso_puppinl_vtx_bkg_05->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_bkg_10->SetBinContent(x+1,isolation_puppinl_vtx_bkg_10[x]);
	ele_pfiso_puppinl_vtx_bkg_10->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_bkg_15->SetBinContent(x+1,isolation_puppinl_vtx_bkg_15[x]);
	ele_pfiso_puppinl_vtx_bkg_15->SetBinError(x+1,0);

	ele_pfiso_puppinl_vtx_bkg_05_eff->SetBinContent(x+1,isolation_puppinl_vtx_bkg_05_eff[x]);
	ele_pfiso_puppinl_vtx_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_bkg_10_eff->SetBinContent(x+1,isolation_puppinl_vtx_bkg_10_eff[x]);
	ele_pfiso_puppinl_vtx_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_bkg_15_eff->SetBinContent(x+1,isolation_puppinl_vtx_bkg_15_eff[x]);
	ele_pfiso_puppinl_vtx_bkg_15_eff->SetBinError(x+1,0);

	ele_pfiso_citk_vtx_bkg_05->SetBinContent(x+1,isolation_citk_vtx_bkg_05[x]);
	ele_pfiso_citk_vtx_bkg_05->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_bkg_10->SetBinContent(x+1,isolation_citk_vtx_bkg_10[x]);
	ele_pfiso_citk_vtx_bkg_10->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_bkg_15->SetBinContent(x+1,isolation_citk_vtx_bkg_15[x]);
	ele_pfiso_citk_vtx_bkg_15->SetBinError(x+1,0);

	ele_pfiso_citk_vtx_bkg_05_eff->SetBinContent(x+1,isolation_citk_vtx_bkg_05_eff[x]);
	ele_pfiso_citk_vtx_bkg_05_eff->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_bkg_10_eff->SetBinContent(x+1,isolation_citk_vtx_bkg_10_eff[x]);
	ele_pfiso_citk_vtx_bkg_10_eff->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_bkg_15_eff->SetBinContent(x+1,isolation_citk_vtx_bkg_15_eff[x]);
	ele_pfiso_citk_vtx_bkg_15_eff->SetBinError(x+1,0);
	}

   for (int x=0; x<=21; x++)
	{
	if (test) { cout << x << " - " << isolation_effarea_vtx[1][x] << " | " << isolation_effarea_vtx[0][x] << endl; }
	}

   plot_histogram(ele_pfiso_simple_vtx_eff, "output/","ele_pfiso_simple_vtx_eff", "Electron PF Isolation Simple Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_effarea_vtx_eff, "output/","ele_pfiso_effarea_vtx_eff", "Electron PF Isolation Effective Area Number of Vertices", "bottom_left", false);
   plot_histogram(ele_pfiso_deltabeta_vtx_eff, "output/","ele_pfiso_deltabeta_vtx_eff", "Electron PF Isolation Delta Beta Number of Vertices", "bottom_right", false);
   plot_histogram(ele_pfiso_puppi_vtx_eff, "output/","ele_pfiso_puppi_vtx_eff", "Electron PF Isolation PUPPI Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_vtx_eff, "output/","ele_pfiso_puppinl_vtx_eff", "Electron PF Isolation PUPPI No Leptons Number of Vertices", "bottom_left", false);
   plot_histogram(ele_pfiso_citk_vtx_eff, "output/","ele_pfiso_citk_vtx_eff", "Electron PF Isolation CITK Number of Vertices", "bottom_right", false);

   plot_six_dist(ele_pfiso_simple_vtx_eff, "PF without PU subtraction", ele_pfiso_effarea_vtx_eff, "Effective Area", ele_pfiso_deltabeta_vtx_eff, "Delta Beta", ele_pfiso_puppi_vtx_eff, "PUPPI", ele_pfiso_puppinl_vtx_eff, "PUPPI No Leptons", ele_pfiso_citk_vtx_eff, "CITK", "output/", "", "ele_pfiso_vtx_eff", "bottom_right", false, false);


   plot_histogram(ele_pfiso_simple_vtx_bkg, "output/","ele_pfiso_simple_vtx_bkg", "Electron PF Isolation Simple Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_effarea_vtx_bkg, "output/","ele_pfiso_effarea_vtx_bkg", "Electron PF Isolation Effective Area Number of Vertices", "bottom_right", false);
   plot_histogram(ele_pfiso_deltabeta_vtx_bkg, "output/","ele_pfiso_deltabeta_vtx_bkg", "Electron PF Isolation Delta Beta Number of Vertices", "bottom_right", false);
   plot_histogram(ele_pfiso_puppi_vtx_bkg, "output/","ele_pfiso_puppi_vtx_bkg", "Electron PF Isolation PUPPI Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_vtx_bkg, "output/","ele_pfiso_puppinl_vtx_bkg", "Electron PF Isolation PUPPI No Leptons Number of Vertices", "bottom_right", false);
   plot_histogram(ele_pfiso_citk_vtx_bkg, "output/","ele_pfiso_citk_vtx_bkg", "Electron PF Isolation CITK Number of Vertices", "bottom_right", false);

   plot_six_dist(ele_pfiso_simple_vtx_bkg, "PF without PU subtraction", ele_pfiso_effarea_vtx_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_bkg, "Delta Beta", ele_pfiso_puppi_vtx_bkg, "PUPPI", ele_pfiso_puppinl_vtx_bkg, "PUPPI No Leptons", ele_pfiso_citk_vtx_bkg, "CITK", "output/", "", "ele_pfiso_vtx_bkg", "bottom_right", false, false);

   plot_histogram(ele_pfiso_simple_vtx_ratio, "output/","ele_pfiso_simple_vtx_ratio", "Electron PF Isolation Simple Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_effarea_vtx_ratio, "output/","ele_pfiso_effarea_vtx_ratio", "Electron PF Isolation Effective Area Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_vtx_ratio, "output/","ele_pfiso_deltabeta_vtx_ratio", "Electron PF Isolation Delta Beta Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppi_vtx_ratio, "output/","ele_pfiso_puppi_vtx_ratio", "Electron PF Isolation PUPPI Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_vtx_ratio, "output/","ele_pfiso_puppinl_vtx_ratio", "Electron PF Isolation PUPPI No Leptons Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_citk_vtx_ratio, "output/","ele_pfiso_citk_vtx_ratio", "Electron PF Isolation CITK Number of Vertices", "top_right", false);

   plot_six_dist(ele_pfiso_simple_vtx_ratio, "PF without PU subtraction", ele_pfiso_effarea_vtx_ratio, "Effective Area", ele_pfiso_deltabeta_vtx_ratio, "Delta Beta", ele_pfiso_puppi_vtx_ratio, "PUPPI", ele_pfiso_puppinl_vtx_ratio, "PUPPI No Leptons", ele_pfiso_citk_vtx_ratio, "CITK", "output/", "", "ele_pfiso_vtx_ratio", "bottom_right", false, false);


  plot_histogram(ele_pfiso_simple_vtx_eff_99, "output/","ele_pfiso_simple_vtx_eff_99", "Electron PF Isolation Simple vtx with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_vtx_eff_95, "output/","ele_pfiso_simple_vtx_eff_95", "Electron PF Isolation Simple vtx with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_vtx_eff_90, "output/","ele_pfiso_simple_vtx_eff_90", "Electron PF Isolation Simple vtx with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_simple_vtx_eff_90, "90% effeciency", ele_pfiso_simple_vtx_eff_95, "95% efficiency", ele_pfiso_simple_vtx_eff_99, "99% efficiency", "output/", "ele_pfiso_simple_vtx_eff_all", "bottom_right", false, 0.0, 1.0, false);

  plot_histogram(ele_pfiso_simple_vtx_bkg_05_eff, "output/","ele_pfiso_simple_vtx_bkg_05_eff", "Electron PF Isolation Simple vtx with 05% background", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_vtx_bkg_10_eff, "output/","ele_pfiso_simple_vtx_bkg_10_eff", "Electron PF Isolation Simple vtx with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_simple_vtx_bkg_15_eff, "output/","ele_pfiso_simple_vtx_bkg_15_eff", "Electron PF Isolation Simple vtx with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_simple_vtx_bkg_05_eff, "5% background", ele_pfiso_simple_vtx_bkg_10_eff, "10% background", ele_pfiso_simple_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_simple_vtx_bkg_all_eff", "bottom_right", false, 0.0, 1.0, false);


  plot_histogram(ele_pfiso_effarea_vtx_eff_99, "output/","ele_pfiso_effarea_vtx_eff_99", "Electron PF Isolation Effective Area vtx with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_eff_95, "output/","ele_pfiso_effarea_vtx_eff_95", "Electron PF Isolation Effective Area vtx with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_eff_90, "output/","ele_pfiso_effarea_vtx_eff_90", "Electron PF Isolation Effective Area vtx with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_effarea_vtx_eff_90, "90% effeciency", ele_pfiso_effarea_vtx_eff_95, "95% efficiency", ele_pfiso_effarea_vtx_eff_99, "99% efficiency", "output/", "ele_pfiso_effarea_vtx_eff_all", "bottom_right", false, 0.0, 1.0, false);

  plot_histogram(ele_pfiso_effarea_vtx_bkg_05_eff, "output/","ele_pfiso_effarea_vtx_bkg_05_eff", "Electron PF Isolation Effective Area vtx with 05% background", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_bkg_10_eff, "output/","ele_pfiso_effarea_vtx_bkg_10_eff", "Electron PF Isolation Effective Area vtx with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_bkg_15_eff, "output/","ele_pfiso_effarea_vtx_bkg_15_eff", "Electron PF Isolation Effective Area vtx with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_effarea_vtx_bkg_05_eff, "5% background", ele_pfiso_effarea_vtx_bkg_10_eff, "10% background", ele_pfiso_effarea_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_effarea_vtx_bkg_all_eff", "bottom_right", false, 0.0, 1.0, false);

  plot_histogram(ele_pfiso_deltabeta_vtx_eff_99, "output/","ele_pfiso_deltabeta_vtx_eff_99", "Electron PF Isolation Delta Beta vtx with 99% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_eff_95, "output/","ele_pfiso_deltabeta_vtx_eff_95", "Electron PF Isolation Delta Beta vtx with 95% effeciency", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_eff_90, "output/","ele_pfiso_deltabeta_vtx_eff_90", "Electron PF Isolation Delta Beta vtx with 90% effeciency", "bottom_right", false);

  plot_3histograms(ele_pfiso_deltabeta_vtx_eff_90, "90% effeciency", ele_pfiso_deltabeta_vtx_eff_95, "95% efficiency", ele_pfiso_deltabeta_vtx_eff_99, "99% efficiency", "output/", "ele_pfiso_deltabeta_vtx_eff_all", "bottom_right", false, 0.0, 1.0, false);

  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_05_eff, "output/","ele_pfiso_deltabeta_vtx_bkg_05_eff", "Electron PF Isolation Delta Beta vtx with 5% background", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_10_eff, "output/","ele_pfiso_deltabeta_vtx_bkg_10_eff", "Electron PF Isolation Delta Beta vtx with 10% background", "bottom_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_15_eff, "output/","ele_pfiso_deltabeta_vtx_bkg_15_eff", "Electron PF Isolation Delta Beta vtx with 15% background", "bottom_right", false);

  plot_3histograms(ele_pfiso_deltabeta_vtx_bkg_05_eff, "5% background", ele_pfiso_deltabeta_vtx_bkg_10_eff, "10% background", ele_pfiso_deltabeta_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_deltabeta_vtx_bkg_all_eff", "bottom_right", false, 0.0, 1.0, false);



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
