// Pedro Cipriano, July 2015
// FESB - Split, CMS
// Last Update: 17 July 2015
//
// Computes the differential distributions for the electron isolation

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
//#include <TEfficiency.h>

//#include "plot_histograms.h"

#include <iostream>
using namespace std;

void create_eff_plot(TH1D *pass = 0, TH1D *tot = 0, TGraphAsymmErrors *eff = 0, string path = "/", string name = "test", TString label = "test")
{

  plot_histogram(pass, path, name+"_pass", label, "top_right", false);
  plot_histogram(tot, path, name+"_tot", label, "top_right", false);

  plot_eff(eff, path, name, label, "top_right", false);

}


void differential_studies_vtx()
{
  gROOT -> Reset();
  gROOT->SetStyle("Plain");

  std::cout << "Differential Studies for Electron Isolation" << endl;
  std::cout << "Variable: Number of Primary Vertices" << endl;
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
  int vtx_nbins = 25;
  double vtx_bins[26] = {5.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0,22.0,23.0, 24.0,25.0,26.0,27.0,28.0,29.0,30.0,35.0,42.5,50.0,80.0};

  //Declare Histograms
TH1D *ele_pfiso_simple_vtx_eff_pass = new TH1D("ele_pfiso_simple_vtx_eff_pass","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_simple_vtx_eff_tot = new TH1D("ele_pfiso_simple_vtx_eff_tot","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_effarea_vtx_eff_pass = new TH1D("ele_pfiso_effarea_vtx_eff_pass","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_tot = new TH1D("ele_pfiso_effarea_vtx_eff_tot","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_deltabeta_vtx_eff_pass = new TH1D("ele_pfiso_deltabeta_vtx_eff_pass","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_tot = new TH1D("ele_pfiso_deltabeta_vtx_eff_tot","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_puppi_vtx_eff_pass = new TH1D("ele_pfiso_puppi_vtx_eff_pass","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_tot = new TH1D("ele_pfiso_puppi_vtx_eff_tot","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_puppinl_vtx_eff_pass = new TH1D("ele_pfiso_puppinl_vtx_eff_pass","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_tot = new TH1D("ele_pfiso_puppinl_vtx_eff_tot","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_citk_vtx_eff_pass = new TH1D("ele_pfiso_citk_vtx_eff_pass","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_tot = new TH1D("ele_pfiso_citk_vtx_eff_tot","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);


TH1D *ele_pfiso_simple_vtx_eff_99_pass = new TH1D("ele_pfiso_simple_vtx_eff_99_pass","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_simple_vtx_eff_99_tot = new TH1D("ele_pfiso_simple_vtx_eff_99_tot","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_effarea_vtx_eff_99_pass = new TH1D("ele_pfiso_effarea_vtx_eff_99_pass","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_99_tot = new TH1D("ele_pfiso_effarea_vtx_eff_99_tot","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_deltabeta_vtx_eff_99_pass = new TH1D("ele_pfiso_deltabeta_vtx_eff_99_pass","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_99_tot = new TH1D("ele_pfiso_deltabeta_vtx_eff_99_tot","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_puppi_vtx_eff_99_pass = new TH1D("ele_pfiso_puppi_vtx_eff_99_pass","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_99_tot = new TH1D("ele_pfiso_puppi_vtx_eff_99_tot","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_puppinl_vtx_eff_99_pass = new TH1D("ele_pfiso_puppinl_vtx_eff_99_pass","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_99_tot = new TH1D("ele_pfiso_puppinl_vtx_eff_99_tot","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_citk_vtx_eff_99_pass = new TH1D("ele_pfiso_citk_vtx_eff_99_pass","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_99_tot = new TH1D("ele_pfiso_citk_vtx_eff_99_tot","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);


TH1D *ele_pfiso_simple_vtx_eff_99_bkg = new TH1D("ele_pfiso_simple_vtx_eff_99_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_99_bkg = new TH1D("ele_pfiso_effarea_vtx_eff_99_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_99_bkg = new TH1D("ele_pfiso_deltabeta_vtx_eff_99_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_99_bkg = new TH1D("ele_pfiso_puppi_vtx_eff_99_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_99_bkg = new TH1D("ele_pfiso_puppinl_vtx_eff_99_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_99_bkg = new TH1D("ele_pfiso_citk_vtx_eff_99_bkg","PFIso Simple CITK of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_95_pass = new TH1D("ele_pfiso_simple_vtx_eff_95_pass","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_simple_vtx_eff_95_tot = new TH1D("ele_pfiso_simple_vtx_eff_95_tot","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_effarea_vtx_eff_95 = new TH1D("ele_pfiso_effarea_vtx_eff_95","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_95 = new TH1D("ele_pfiso_deltabeta_vtx_eff_95","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_95 = new TH1D("ele_pfiso_puppi_vtx_eff_95","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_puppinl_vtx_eff_95_pass = new TH1D("ele_pfiso_puppinl_vtx_eff_95_pass","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_95_tot = new TH1D("ele_pfiso_puppinl_vtx_eff_95_tot","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_citk_vtx_eff_95 = new TH1D("ele_pfiso_citk_vtx_eff_95","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_95_bkg = new TH1D("ele_pfiso_simple_vtx_eff_95_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_95_bkg = new TH1D("ele_pfiso_effarea_vtx_eff_95_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_95_bkg = new TH1D("ele_pfiso_deltabeta_vtx_eff_95_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_95_bkg = new TH1D("ele_pfiso_puppi_vtx_eff_95_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_95_bkg = new TH1D("ele_pfiso_puppinl_vtx_eff_95_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Background;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_95_bkg = new TH1D("ele_pfiso_citk_vtx_eff_95_bkg","PFIso Simple CITK of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_90_pass = new TH1D("ele_pfiso_simple_vtx_eff_90_pass","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_simple_vtx_eff_90_tot = new TH1D("ele_pfiso_simple_vtx_eff_90_tot","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_effarea_vtx_eff_90 = new TH1D("ele_pfiso_effarea_vtx_eff_90","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_90 = new TH1D("ele_pfiso_deltabeta_vtx_eff_90","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_90 = new TH1D("ele_pfiso_puppi_vtx_eff_90","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_puppinl_vtx_eff_90_pass = new TH1D("ele_pfiso_puppinl_vtx_eff_90_pass","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_90_tot = new TH1D("ele_pfiso_puppinl_vtx_eff_90_tot","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);


TH1D *ele_pfiso_citk_vtx_eff_90 = new TH1D("ele_pfiso_citk_vtx_eff_90","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_eff_90_bkg = new TH1D("ele_pfiso_simple_vtx_eff_90_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff_90_bkg = new TH1D("ele_pfiso_effarea_vtx_eff_90_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff_90_bkg = new TH1D("ele_pfiso_deltabeta_vtx_eff_90_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff_90_bkg = new TH1D("ele_pfiso_puppi_vtx_eff_90_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff_90_bkg = new TH1D("ele_pfiso_puppinl_vtx_eff_90_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff_90_bkg = new TH1D("ele_pfiso_citk_vtx_eff_90_bkg","PFIso Simple CITK of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg = new TH1D("ele_pfiso_simple_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg = new TH1D("ele_pfiso_effarea_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg = new TH1D("ele_pfiso_deltabeta_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg = new TH1D("ele_pfiso_puppi_vtx_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg = new TH1D("ele_pfiso_puppinl_vtx_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg = new TH1D("ele_pfiso_citk_vtx_bkg","PFIso CITK Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_05 = new TH1D("ele_pfiso_simple_vtx_bkg_05","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_05 = new TH1D("ele_pfiso_effarea_vtx_bkg_05","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_05 = new TH1D("ele_pfiso_deltabeta_vtx_bkg_05","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_05 = new TH1D("ele_pfiso_puppi_vtx_bkg_05","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_05 = new TH1D("ele_pfiso_puppinl_vtx_bkg_05","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_05 = new TH1D("ele_pfiso_citk_vtx_bkg_05","PFIso CITK Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_05_eff = new TH1D("ele_pfiso_simple_vtx_bkg_05_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_05_eff = new TH1D("ele_pfiso_effarea_vtx_bkg_05_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_05_eff = new TH1D("ele_pfiso_deltabeta_vtx_bkg_05_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_05_eff = new TH1D("ele_pfiso_puppi_vtx_bkg_05_eff","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_05_eff = new TH1D("ele_pfiso_puppinl_vtx_bkg_05_eff","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_05_eff = new TH1D("ele_pfiso_citk_vtx_bkg_05_eff","PFIso CITK Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_10 = new TH1D("ele_pfiso_simple_vtx_bkg_10","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_10 = new TH1D("ele_pfiso_effarea_vtx_bkg_10","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_10 = new TH1D("ele_pfiso_deltabeta_vtx_bkg_10","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_10 = new TH1D("ele_pfiso_puppi_vtx_bkg_10","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_10 = new TH1D("ele_pfiso_puppinl_vtx_bkg_10","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_10 = new TH1D("ele_pfiso_citk_vtx_bkg_10","PFIso CITK Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_10_eff = new TH1D("ele_pfiso_simple_vtx_bkg_10_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_10_eff = new TH1D("ele_pfiso_effarea_vtx_bkg_10_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_10_eff = new TH1D("ele_pfiso_deltabeta_vtx_bkg_10_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_10_eff = new TH1D("ele_pfiso_puppi_vtx_bkg_10_eff","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_10_eff = new TH1D("ele_pfiso_puppinl_vtx_bkg_10_eff","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_10_eff = new TH1D("ele_pfiso_citk_vtx_bkg_10_eff","PFIso CITK Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_15 = new TH1D("ele_pfiso_simple_vtx_bkg_15","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_15 = new TH1D("ele_pfiso_effarea_vtx_bkg_15","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_15 = new TH1D("ele_pfiso_deltabeta_vtx_bkg_15","PFIso Simple Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_15 = new TH1D("ele_pfiso_puppi_vtx_bkg_15","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_15 = new TH1D("ele_pfiso_puppinl_vtx_bkg_15","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_15 = new TH1D("ele_pfiso_citk_vtx_bkg_15","PFIso CITK Number of Generated Vertices;Number of Vertices;Background",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg_15_eff = new TH1D("ele_pfiso_simple_vtx_bkg_15_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg_15_eff = new TH1D("ele_pfiso_effarea_vtx_bkg_15_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg_15_eff = new TH1D("ele_pfiso_deltabeta_vtx_bkg_15_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg_15_eff = new TH1D("ele_pfiso_puppi_vtx_bkg_15_eff","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg_15_eff = new TH1D("ele_pfiso_puppinl_vtx_bkg_15_eff","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg_15_eff = new TH1D("ele_pfiso_citk_vtx_bkg_15_eff","PFIso CITK Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_ratio = new TH1D("ele_pfiso_simple_vtx_ratio","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_ratio = new TH1D("ele_pfiso_effarea_vtx_ratio","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_ratio = new TH1D("ele_pfiso_deltabeta_vtx_ratio","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_ratio = new TH1D("ele_pfiso_puppi_vtx_ratio","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_ratio = new TH1D("ele_pfiso_puppinl_vtx_ratio","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_ratio = new TH1D("ele_pfiso_citk_vtx_ratio","PFIso CITK Number of Generated Vertices;Number of Vertices;Signal/Background",vtx_nbins,vtx_bins);



  //declaring matrices and arrays
   double isolation_simple_vtx[samples][vtx_nbins];
   double isolation_simple_vtx_eff_99_bkg[vtx_nbins], isolation_simple_vtx_eff_95_bkg[vtx_nbins], isolation_simple_vtx_eff_90_bkg[vtx_nbins];
   double isolation_simple_vtx_bkg_05[vtx_nbins], isolation_simple_vtx_bkg_10[vtx_nbins], isolation_simple_vtx_bkg_15[vtx_nbins];
   double isolation_simple_vtx_bkg_05_eff[vtx_nbins], isolation_simple_vtx_bkg_10_eff[vtx_nbins], isolation_simple_vtx_bkg_15_eff[vtx_nbins];


   double isolation_effarea_vtx[samples][vtx_nbins];
   double isolation_effarea_vtx_eff_95[vtx_nbins], isolation_effarea_vtx_eff_90[vtx_nbins];
   double isolation_effarea_vtx_eff_99_bkg[vtx_nbins], isolation_effarea_vtx_eff_95_bkg[vtx_nbins], isolation_effarea_vtx_eff_90_bkg[vtx_nbins];
   double isolation_effarea_vtx_bkg_05[vtx_nbins], isolation_effarea_vtx_bkg_10[vtx_nbins], isolation_effarea_vtx_bkg_15[vtx_nbins];
   double isolation_effarea_vtx_bkg_05_eff[vtx_nbins], isolation_effarea_vtx_bkg_10_eff[vtx_nbins], isolation_effarea_vtx_bkg_15_eff[vtx_nbins];

   double isolation_deltabeta_vtx[samples][vtx_nbins];
   double isolation_deltabeta_vtx_eff_95[vtx_nbins], isolation_deltabeta_vtx_eff_90[vtx_nbins];
   double isolation_deltabeta_vtx_eff_99_bkg[vtx_nbins], isolation_deltabeta_vtx_eff_95_bkg[vtx_nbins], isolation_deltabeta_vtx_eff_90_bkg[vtx_nbins];
   double isolation_deltabeta_vtx_bkg_05[vtx_nbins], isolation_deltabeta_vtx_bkg_10[vtx_nbins], isolation_deltabeta_vtx_bkg_15[vtx_nbins];
   double isolation_deltabeta_vtx_bkg_05_eff[vtx_nbins], isolation_deltabeta_vtx_bkg_10_eff[vtx_nbins], isolation_deltabeta_vtx_bkg_15_eff[vtx_nbins];

   double isolation_puppi_vtx[samples][vtx_nbins];
   double isolation_puppi_vtx_eff_95[vtx_nbins], isolation_puppi_vtx_eff_90[vtx_nbins];
   double isolation_puppi_vtx_eff_99_bkg[vtx_nbins], isolation_puppi_vtx_eff_95_bkg[vtx_nbins], isolation_puppi_vtx_eff_90_bkg[vtx_nbins];
   double isolation_puppi_vtx_bkg_05[vtx_nbins], isolation_puppi_vtx_bkg_10[vtx_nbins], isolation_puppi_vtx_bkg_15[vtx_nbins];
   double isolation_puppi_vtx_bkg_05_eff[vtx_nbins], isolation_puppi_vtx_bkg_10_eff[vtx_nbins], isolation_puppi_vtx_bkg_15_eff[vtx_nbins];

   double isolation_puppinl_vtx[samples][vtx_nbins], isolation_puppinl_eta[samples][25];
   double isolation_puppinl_vtx_eff_99_bkg[vtx_nbins], isolation_puppinl_vtx_eff_95_bkg[vtx_nbins], isolation_puppinl_vtx_eff_90_bkg[vtx_nbins];
   double isolation_puppinl_vtx_bkg_05[vtx_nbins], isolation_puppinl_vtx_bkg_10[vtx_nbins], isolation_puppinl_vtx_bkg_15[vtx_nbins];
   double isolation_puppinl_vtx_bkg_05_eff[vtx_nbins], isolation_puppinl_vtx_bkg_10_eff[vtx_nbins], isolation_puppinl_vtx_bkg_15_eff[vtx_nbins];

   double isolation_citk_vtx[samples][vtx_nbins];
   double isolation_citk_vtx_eff_95[vtx_nbins], isolation_citk_vtx_eff_90[vtx_nbins];
   double isolation_citk_vtx_eff_99_bkg[vtx_nbins], isolation_citk_vtx_eff_95_bkg[vtx_nbins], isolation_citk_vtx_eff_90_bkg[vtx_nbins];
   double isolation_citk_vtx_bkg_05[vtx_nbins], isolation_citk_vtx_bkg_10[vtx_nbins], isolation_citk_vtx_bkg_15[vtx_nbins];
   double isolation_citk_vtx_bkg_05_eff[vtx_nbins], isolation_citk_vtx_bkg_10_eff[vtx_nbins], isolation_citk_vtx_bkg_15_eff[vtx_nbins];

for (int s = 0; s <= 1; ++s)
{
   for (int y=0; y<vtx_nbins; ++y)
	{
	isolation_simple_vtx[s][y] = 0;
	isolation_effarea_vtx[s][y] = 0;
	isolation_deltabeta_vtx[s][y] = 0;
	isolation_puppi_vtx[s][y] = 0;
	isolation_puppinl_vtx[s][y] = 0;
	isolation_citk_vtx[s][y] = 0;
	}
}

   for (int y=0; y<vtx_nbins; ++y)
	{
	isolation_simple_vtx_eff_99_bkg[y] = 0;
	isolation_effarea_vtx_eff_99_bkg[y] = 0;
	isolation_deltabeta_vtx_eff_99_bkg[y] = 0;
	isolation_puppi_vtx_eff_99_bkg[y] = 0;
	isolation_puppinl_vtx_eff_99_bkg[y] = 0;
	isolation_citk_vtx_eff_99_bkg[y] = 0;

	isolation_effarea_vtx_eff_95[y] = 0;
	isolation_deltabeta_vtx_eff_95[y] = 0;
	isolation_puppi_vtx_eff_95[y] = 0;
	isolation_citk_vtx_eff_95[y] = 0;

	isolation_simple_vtx_eff_95_bkg[y] = 0;
	isolation_effarea_vtx_eff_95_bkg[y] = 0;
	isolation_deltabeta_vtx_eff_95_bkg[y] = 0;
	isolation_puppi_vtx_eff_95_bkg[y] = 0;
	isolation_puppinl_vtx_eff_95_bkg[y] = 0;
	isolation_citk_vtx_eff_95_bkg[y] = 0;

	isolation_effarea_vtx_eff_90[y] = 0;
	isolation_deltabeta_vtx_eff_90[y] = 0;
	isolation_puppi_vtx_eff_90[y] = 0;
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


  std::cout << "Ploting the 2D histograms..." << endl;

  //Iso Simple VS vtx
  TH2D *iso_simple_vs_vtx1 = 0;
  TH2D *iso_simple_vs_vtx2 = 0;

  f1->GetObject("iso_simple_vs_vtx",iso_simple_vs_vtx1);
  if (iso_simple_vs_vtx1 == 0) { cout << "iso_simple_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_simple_vs_vtx",iso_simple_vs_vtx2);
  if (iso_simple_vs_vtx2 == 0) { cout << "iso_simple_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_simple_vs_vtx1, "output/", prefix[0] + "_iso_simple_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_simple_vs_vtx2, "output/", prefix[1] + "_iso_simple_vs_vtx", prefix[1], "top_right", true);

  //Iso Effective Area VS vtx
  TH2D *iso_effarea_vs_vtx1 = 0;
  TH2D *iso_effarea_vs_vtx2 = 0;

  f1->GetObject("iso_effarea_vs_vtx",iso_effarea_vs_vtx1);
  if (iso_effarea_vs_vtx1 == 0) { cout << "iso_effarea_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_effarea_vs_vtx",iso_effarea_vs_vtx2);
  if (iso_effarea_vs_vtx2 == 0) { cout << "iso_effarea_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_effarea_vs_vtx1, "output/", prefix[0] + "_iso_effarea_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_effarea_vs_vtx2, "output/", prefix[1] + "_iso_effarea_vs_vtx", prefix[1], "top_right", true);

  //Iso Delta Beta VS vtx
  TH2D *iso_deltabeta_vs_vtx1 = 0;
  TH2D *iso_deltabeta_vs_vtx2 = 0;

  f1->GetObject("iso_deltabeta_vs_vtx",iso_deltabeta_vs_vtx1);
  if (iso_deltabeta_vs_vtx1 == 0) { cout << "iso_deltabeta_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_deltabeta_vs_vtx",iso_deltabeta_vs_vtx2);
  if (iso_deltabeta_vs_vtx2 == 0) { cout << "iso_deltabeta_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_deltabeta_vs_vtx1, "output/", prefix[0] + "_iso_deltabeta_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_deltabeta_vs_vtx2, "output/", prefix[1] + "_iso_deltabeta_vs_vtx", prefix[1], "top_right", true);

  //Iso PUPPI VS vtx
  TH2D *iso_puppi_vs_vtx1 = 0;
  TH2D *iso_puppi_vs_vtx2 = 0;

  f1->GetObject("iso_puppi_vs_vtx",iso_puppi_vs_vtx1);
  if (iso_puppi_vs_vtx1 == 0) { cout << "iso_puppi_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_puppi_vs_vtx",iso_puppi_vs_vtx2);
  if (iso_puppi_vs_vtx2 == 0) { cout << "iso_puppi_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_puppi_vs_vtx1, "output/", prefix[0] + "_iso_puppi_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppi_vs_vtx2, "output/", prefix[1] + "_iso_puppi_vs_vtx", prefix[1], "top_right", true);

  //Iso PUPPI No Leptons VS vtx
  TH2D *iso_puppinl_vs_vtx1 = 0;
  TH2D *iso_puppinl_vs_vtx2 = 0;

  f1->GetObject("iso_puppinl_vs_vtx",iso_puppinl_vs_vtx1);
  if (iso_puppinl_vs_vtx1 == 0) { cout << "iso_puppinl_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_puppinl_vs_vtx",iso_puppinl_vs_vtx2);
  if (iso_puppinl_vs_vtx2 == 0) { cout << "iso_puppinl_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_puppinl_vs_vtx1, "output/", prefix[0] + "_iso_puppinl_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_puppinl_vs_vtx2, "output/", prefix[1] + "_iso_puppinl_vs_vtx", prefix[1], "top_right", true);

  //Iso citk VS vtx
  TH2D *iso_citk_vs_vtx1 = 0;
  TH2D *iso_citk_vs_vtx2 = 0;

  f1->GetObject("iso_citk_vs_vtx",iso_citk_vs_vtx1);
  if (iso_citk_vs_vtx1 == 0) { cout << "iso_citk_vs_vtx not found!" << endl; return; }
  f2->GetObject("iso_citk_vs_vtx",iso_citk_vs_vtx2);
  if (iso_citk_vs_vtx2 == 0) { cout << "iso_citk_vs_vtx not found!" << endl; return; }


plot_2dhistogram(iso_citk_vs_vtx1, "output/", prefix[0] + "_iso_citk_vs_vtx", prefix[0], "top_right", true);
plot_2dhistogram(iso_citk_vs_vtx2, "output/", prefix[1] + "_iso_citk_vs_vtx", prefix[1], "top_right", true);


  if (show_steps) { std::cout << "All the 2D histograms were sucessful ploted!" << endl; }

  //temporary variables
  double integral_tot, error_tot, integral_pass, error_pass;

  //compute the differential distributions
  int nbins = 0;

   nbins = iso_simple_vs_vtx1->GetNbinsY();

   if (show_steps) { cout << "N bins = " << nbins << endl; }

for (int x=1; x<=nbins; x++)
	{
	if (iso_simple_vs_vtx1->Integral(0,2000,x,x) > 0.0)
		{
		isolation_simple_vtx[0][x-1] = iso_simple_vs_vtx1->Integral(0,working_point,x,x)/iso_simple_vs_vtx1->Integral(0,2000,x,x);
		}
	else
		{
		isolation_simple_vtx[0][x-1] = 0.0;
		}

	if (iso_effarea_vs_vtx1->Integral(0,2000,x,x) > 0.0)
		{
		isolation_effarea_vtx[0][x-1] = iso_effarea_vs_vtx1->Integral(0,working_point,x,x)/iso_effarea_vs_vtx1->Integral(0,2000,x,x);
		}
	else
		{
		isolation_effarea_vtx[0][x-1] = 0.0;
		}

	if (iso_deltabeta_vs_vtx1->Integral(0,2000,x,x) > 0.0)
		{
		isolation_deltabeta_vtx[0][x-1] = iso_deltabeta_vs_vtx1->Integral(0,working_point,x,x)/iso_deltabeta_vs_vtx1->Integral(0,2000,x,x);
		}
	else
		{
		isolation_deltabeta_vtx[0][x-1] = 0.0;
		}

	if (iso_puppi_vs_vtx1->Integral(0,2000,x,x) > 0.0)
		{
		isolation_puppi_vtx[0][x-1] = iso_puppi_vs_vtx1->Integral(0,working_point,x,x)/iso_puppi_vs_vtx1->Integral(0,2000,x,x);
		}
	else
		{
		isolation_puppi_vtx[0][x-1] = 0.0;
		}

	if (iso_puppinl_vs_vtx1->Integral(0,2000,x,x) > 0.0)
		{
		isolation_puppinl_vtx[0][x-1] = iso_puppinl_vs_vtx1->Integral(0,working_point,x,x)/iso_puppinl_vs_vtx1->Integral(0,2000,x,x);
		}
	else
		{
		isolation_puppinl_vtx[0][x-1] = 0.0;
		}

	if (iso_citk_vs_vtx1->Integral(0,2000,x,x) > 0.0)
		{
		isolation_citk_vtx[0][x-1] = iso_citk_vs_vtx1->Integral(0,working_point,x,x)/iso_citk_vs_vtx1->Integral(0,2000,x,x);
		}
	else
		{
		isolation_citk_vtx[0][x-1] = 0.0;
		}
	
	isolation_simple_vtx[1][x-1] = iso_simple_vs_vtx2->Integral(0,working_point,x,x)/iso_simple_vs_vtx2->Integral(0,2000,x,x);
	isolation_effarea_vtx[1][x-1] = iso_effarea_vs_vtx2->Integral(0,working_point,x,x)/iso_effarea_vs_vtx2->Integral(0,2000,x,x);
	isolation_deltabeta_vtx[1][x-1] = iso_deltabeta_vs_vtx2->Integral(0,working_point,x,x)/iso_deltabeta_vs_vtx2->Integral(0,2000,x,x);
	isolation_puppi_vtx[1][x-1] = iso_puppi_vs_vtx2->Integral(0,working_point,x,x)/iso_puppi_vs_vtx2->Integral(0,2000,x,x);
	isolation_puppinl_vtx[1][x-1] = iso_puppinl_vs_vtx2->Integral(0,working_point,x,x)/iso_puppinl_vs_vtx2->Integral(0,2000,x,x);
	isolation_citk_vtx[1][x-1] = iso_citk_vs_vtx2->Integral(0,working_point,x,x)/iso_citk_vs_vtx2->Integral(0,2000,x,x);

	integral_pass = iso_simple_vs_vtx2->IntegralAndError(0,working_point,x,x,error_tot);
	integral_tot = iso_simple_vs_vtx2->IntegralAndError(0,2000,x,x,error_pass);
	ele_pfiso_simple_vtx_eff_pass->SetBinContent(x,integral_pass);
	ele_pfiso_simple_vtx_eff_pass->SetBinError(x,error_pass);
	ele_pfiso_simple_vtx_eff_tot->SetBinContent(x,integral_tot);
	ele_pfiso_simple_vtx_eff_tot->SetBinError(x,error_tot);

	integral_pass = iso_effarea_vs_vtx2->IntegralAndError(0,working_point,x,x,error_tot);
	integral_tot = iso_effarea_vs_vtx2->IntegralAndError(0,2000,x,x,error_pass);
	ele_pfiso_effarea_vtx_eff_pass->SetBinContent(x,integral_pass);
	ele_pfiso_effarea_vtx_eff_pass->SetBinError(x,error_pass);
	ele_pfiso_effarea_vtx_eff_tot->SetBinContent(x,integral_tot);
	ele_pfiso_effarea_vtx_eff_tot->SetBinError(x,error_tot);

	integral_pass = iso_deltabeta_vs_vtx2->IntegralAndError(0,working_point,x,x,error_tot);
	integral_tot = iso_deltabeta_vs_vtx2->IntegralAndError(0,2000,x,x,error_pass);
	ele_pfiso_deltabeta_vtx_eff_pass->SetBinContent(x,integral_pass);
	ele_pfiso_deltabeta_vtx_eff_pass->SetBinError(x,error_pass);
	ele_pfiso_deltabeta_vtx_eff_tot->SetBinContent(x,integral_tot);
	ele_pfiso_deltabeta_vtx_eff_tot->SetBinError(x,error_tot);

	integral_pass = iso_puppi_vs_vtx2->IntegralAndError(0,working_point,x,x,error_tot);
	integral_tot = iso_puppi_vs_vtx2->IntegralAndError(0,2000,x,x,error_pass);
	ele_pfiso_puppi_vtx_eff_pass->SetBinContent(x,integral_pass);
	ele_pfiso_puppi_vtx_eff_pass->SetBinError(x,error_pass);
	ele_pfiso_puppi_vtx_eff_tot->SetBinContent(x,integral_tot);
	ele_pfiso_puppi_vtx_eff_tot->SetBinError(x,error_tot);

	integral_pass = iso_puppinl_vs_vtx2->IntegralAndError(0,working_point,x,x,error_tot);
	integral_tot = iso_puppinl_vs_vtx2->IntegralAndError(0,2000,x,x,error_pass);
	ele_pfiso_puppinl_vtx_eff_pass->SetBinContent(x,integral_pass);
	ele_pfiso_puppinl_vtx_eff_pass->SetBinError(x,error_pass);
	ele_pfiso_puppinl_vtx_eff_tot->SetBinContent(x,integral_tot);
	ele_pfiso_puppinl_vtx_eff_tot->SetBinError(x,error_tot);

	integral_pass = iso_citk_vs_vtx2->IntegralAndError(0,working_point,x,x,error_tot);
	integral_tot = iso_citk_vs_vtx2->IntegralAndError(0,2000,x,x,error_pass);
	ele_pfiso_citk_vtx_eff_pass->SetBinContent(x,integral_pass);
	ele_pfiso_citk_vtx_eff_pass->SetBinError(x,error_pass);
	ele_pfiso_citk_vtx_eff_tot->SetBinContent(x,integral_tot);
	ele_pfiso_citk_vtx_eff_tot->SetBinError(x,error_tot);

	}

   if (show_steps) { cout << "Choosing the fixed effiency points..." << endl; }


for (int x = 1; x <= 2000; x++)
	{
	if (iso_simple_vs_vtx2->Integral(0,x,1,nbins)/iso_simple_vs_vtx2->Integral(0,2000,1,nbins) > .99 and ele_pfiso_simple_vtx_eff_99_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "00: Found vtx 99% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_simple_vtx_eff_99_pass->SetBinContent(y,iso_simple_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_simple_vtx_eff_99_tot->SetBinContent(y,iso_simple_vs_vtx2->Integral(0,2000,y,y));
			if (iso_simple_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_simple_vtx_eff_99_bkg[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_simple_vtx_eff_99_bkg[y-1] = 0.0;
				}
			if (test) { cout << "Bin " << y << ": " << ele_pfiso_simple_vtx_eff_99_pass->GetBinContent(y) << endl; }
			}
		}

	if (iso_simple_vs_vtx2->Integral(0,x,1,nbins)/iso_simple_vs_vtx2->Integral(0,2000,1,nbins) > .95 and ele_pfiso_simple_vtx_eff_95_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "01: Found vtx 95% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_simple_vtx_eff_95_pass->SetBinContent(y,iso_simple_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_simple_vtx_eff_95_tot->SetBinContent(y,iso_simple_vs_vtx2->Integral(0,2000,y,y));
			if (iso_simple_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_simple_vtx_eff_95_bkg[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_simple_vtx_eff_95_bkg[y-1] = 0.0;
				}
			}
		}

	if (iso_simple_vs_vtx2->Integral(0,x,1,nbins)/iso_simple_vs_vtx2->Integral(0,2000,1,nbins) > .90 and ele_pfiso_simple_vtx_eff_90_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "02: Found vtx 90% effeciency point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_simple_vtx_eff_90_pass->SetBinContent(y,iso_simple_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_simple_vtx_eff_90_tot->SetBinContent(y,iso_simple_vs_vtx2->Integral(0,2000,y,y));
			if (iso_simple_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_simple_vtx_eff_90_bkg[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_simple_vtx_eff_90_bkg[y-1] = 0.0;
				}
			}
		}

        if (test and x < 200) { cout << "bin " << x << " = " << iso_effarea_vs_vtx2->Integral(0,x,1,nbins)/iso_effarea_vs_vtx2->Integral(0,2000,1,nbins) << endl; }

if (iso_effarea_vs_vtx2->Integral(0,x,1,nbins)/iso_effarea_vs_vtx2->Integral(0,2000,1,nbins) > .99 and ele_pfiso_effarea_vtx_eff_99_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "03: Found vtx 99% effeciency point for the effarea method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_effarea_vtx_eff_99_pass->SetBinContent(y,iso_effarea_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_effarea_vtx_eff_99_tot->SetBinContent(y,iso_effarea_vs_vtx2->Integral(0,2000,y,y));
			if (iso_effarea_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_effarea_vtx_eff_99_bkg[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_effarea_vtx_eff_99_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_effarea_vs_vtx2->Integral(0,x,1,nbins)/iso_effarea_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_effarea_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "04: Found vtx 95% effeciency point for the effarea method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_vtx_eff_95[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			if (iso_effarea_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_effarea_vtx_eff_95_bkg[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_effarea_vtx_eff_95_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_effarea_vs_vtx2->Integral(0,x,1,nbins)/iso_effarea_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_effarea_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "05: Found vtx 90% effeciency point for the effarea method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_effarea_vtx_eff_90[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			if (iso_effarea_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_effarea_vtx_eff_90_bkg[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_effarea_vtx_eff_90_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_deltabeta_vs_vtx2->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx2->Integral(0,2000,1,nbins) > .99 and ele_pfiso_deltabeta_vtx_eff_99_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "06: Found vtx 99% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_deltabeta_vtx_eff_99_pass->SetBinContent(y,iso_deltabeta_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_deltabeta_vtx_eff_99_tot->SetBinContent(y,iso_deltabeta_vs_vtx2->Integral(0,2000,y,y));
			if (iso_deltabeta_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_deltabeta_vtx_eff_99_bkg[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_deltabeta_vtx_eff_99_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_deltabeta_vs_vtx2->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_deltabeta_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "07: Found vtx 95% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_vtx_eff_95[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			if (iso_deltabeta_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_deltabeta_vtx_eff_95_bkg[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_deltabeta_vtx_eff_95_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_deltabeta_vs_vtx2->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_deltabeta_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "08: Found vtx 90% effeciency point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_deltabeta_vtx_eff_90[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			if (iso_deltabeta_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_deltabeta_vtx_eff_90_bkg[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_deltabeta_vtx_eff_90_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_puppi_vs_vtx2->Integral(0,x,1,nbins)/iso_puppi_vs_vtx2->Integral(0,2000,1,nbins) > .99 and ele_pfiso_puppi_vtx_eff_99_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "09: Found vtx 99% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_puppi_vtx_eff_99_pass->SetBinContent(y,iso_puppi_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_puppi_vtx_eff_99_tot->SetBinContent(y,iso_puppi_vs_vtx2->Integral(0,2000,y,y));
			if (iso_puppi_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppi_vtx_eff_99_bkg[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppi_vtx_eff_99_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_puppi_vs_vtx2->Integral(0,x,1,nbins)/iso_puppi_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_puppi_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "10: Found vtx 95% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_vtx_eff_95[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			if (iso_puppi_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppi_vtx_eff_95_bkg[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppi_vtx_eff_95_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_puppi_vs_vtx2->Integral(0,x,1,nbins)/iso_puppi_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_puppi_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "11: Found vtx 90% effeciency point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_puppi_vtx_eff_90[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			if (iso_puppi_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppi_vtx_eff_90_bkg[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppi_vtx_eff_90_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_puppinl_vs_vtx2->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx2->Integral(0,2000,1,nbins) > .99 and ele_pfiso_puppinl_vtx_eff_99_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "12: Found vtx 99% effeciency point for the puppi no leptons  method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_puppinl_vtx_eff_99_pass->SetBinContent(y,iso_puppinl_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_puppinl_vtx_eff_99_tot->SetBinContent(y,iso_puppinl_vs_vtx2->Integral(0,2000,y,y));
			if (iso_puppinl_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppinl_vtx_eff_99_bkg[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppinl_vtx_eff_99_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_puppinl_vs_vtx2->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx2->Integral(0,2000,1,nbins) > .95 and ele_pfiso_puppinl_vtx_eff_95_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "13: Found vtx 95% effeciency point for the puppi no leptons  method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_puppinl_vtx_eff_95_pass->SetBinContent(y,iso_puppinl_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_puppinl_vtx_eff_95_tot->SetBinContent(y,iso_puppinl_vs_vtx2->Integral(0,2000,y,y));
			if (iso_puppinl_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppinl_vtx_eff_95_bkg[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppinl_vtx_eff_95_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_puppinl_vs_vtx2->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx2->Integral(0,2000,1,nbins) > .90 and ele_pfiso_puppinl_vtx_eff_90_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "14: Found vtx 90% effeciency point for the puppi no leptons  method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_puppinl_vtx_eff_90_pass->SetBinContent(y,iso_puppinl_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_puppinl_vtx_eff_90_tot->SetBinContent(y,iso_puppinl_vs_vtx2->Integral(0,2000,y,y));
			if (iso_puppinl_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppinl_vtx_eff_90_bkg[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppinl_vtx_eff_90_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_citk_vs_vtx2->Integral(0,x,1,nbins)/iso_citk_vs_vtx2->Integral(0,2000,1,nbins) > .99 and ele_pfiso_citk_vtx_eff_99_pass->GetBinContent(1) == 0)
		{
		if (show_steps) { cout << "15: Found vtx 99% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			ele_pfiso_citk_vtx_eff_99_pass->SetBinContent(y,iso_citk_vs_vtx2->Integral(0,x,y,y));
			ele_pfiso_citk_vtx_eff_99_tot->SetBinContent(y,iso_citk_vs_vtx2->Integral(0,2000,y,y));
			if (iso_citk_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_citk_vtx_eff_99_bkg[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_citk_vtx_eff_99_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_citk_vs_vtx2->Integral(0,x,1,nbins)/iso_citk_vs_vtx2->Integral(0,2000,1,nbins) > .95 and isolation_citk_vtx_eff_95[0] == 0)
		{
		if (show_steps) { cout << "16: Found vtx 95% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_vtx_eff_95[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			if (iso_citk_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_citk_vtx_eff_95_bkg[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_citk_vtx_eff_95_bkg[y-1] = 0.0;
				}
			}
		}

if (iso_citk_vs_vtx2->Integral(0,x,1,nbins)/iso_citk_vs_vtx2->Integral(0,2000,1,nbins) > .90 and isolation_citk_vtx_eff_90[0] == 0)
		{
		if (show_steps) { cout << "17: Found vtx 90% effeciency point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			isolation_citk_vtx_eff_90[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			if (iso_citk_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_citk_vtx_eff_90_bkg[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_citk_vtx_eff_90_bkg[y-1] = 0.0;
				}
			}
		}

//Simple Background

	if (iso_simple_vs_vtx1->Integral(0,x,1,nbins)/iso_simple_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_simple_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "18: Found vtx 5% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_simple_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_simple_vtx_bkg_05[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_simple_vtx_bkg_05[y-1] = 0.0;
				}
			isolation_simple_vtx_bkg_05_eff[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			if (test) { cout << "Bin " << y << ": " << isolation_simple_vtx_bkg_05[y-1] << "(" << iso_simple_vs_vtx1->Integral(0,x,y,y) << "/" << iso_simple_vs_vtx1->Integral(0,2000,y,y) << endl; }
			}
		}

	if (iso_simple_vs_vtx1->Integral(0,x,1,nbins)/iso_simple_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_simple_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "19: Found vtx 10% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_simple_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_simple_vtx_bkg_10[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_simple_vtx_bkg_10[y-1] = 0.0;
				}
			isolation_simple_vtx_bkg_10_eff[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_simple_vs_vtx1->Integral(0,x,1,nbins)/iso_simple_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_simple_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "20: Found vtx 15% background point for the simple method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_simple_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_simple_vtx_bkg_15[y-1] = iso_simple_vs_vtx1->Integral(0,x,y,y)/iso_simple_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_simple_vtx_bkg_15[y-1] = 0.0;
				}
			isolation_simple_vtx_bkg_15_eff[y-1] = iso_simple_vs_vtx2->Integral(0,x,y,y)/iso_simple_vs_vtx2->Integral(0,2000,y,y);
			}
		}

//Effective Area Background

	if (iso_effarea_vs_vtx1->Integral(0,x,1,nbins)/iso_effarea_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_effarea_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "21: Found vtx 05% background point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_effarea_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_effarea_vtx_bkg_05[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_effarea_vtx_bkg_05[y-1] = 0.0;
				}
			isolation_effarea_vtx_bkg_05_eff[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_effarea_vs_vtx1->Integral(0,x,1,nbins)/iso_effarea_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_effarea_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "22: Found vtx 10% background point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_effarea_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_effarea_vtx_bkg_10[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_effarea_vtx_bkg_10[y-1] = 0.0;
				}
			isolation_effarea_vtx_bkg_10_eff[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_effarea_vs_vtx1->Integral(0,x,1,nbins)/iso_effarea_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_effarea_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "23: Found vtx 15% background point for the effective area method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_effarea_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_effarea_vtx_bkg_15[y-1] = iso_effarea_vs_vtx1->Integral(0,x,y,y)/iso_effarea_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_effarea_vtx_bkg_15[y-1] = 0.0;
				}
			isolation_effarea_vtx_bkg_15_eff[y-1] = iso_effarea_vs_vtx2->Integral(0,x,y,y)/iso_effarea_vs_vtx2->Integral(0,2000,y,y);
			}
		}

//Delta Beta Background

	if (iso_deltabeta_vs_vtx1->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_deltabeta_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "24: Found vtx 05% background point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_deltabeta_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_deltabeta_vtx_bkg_05[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_deltabeta_vtx_bkg_05[y-1] = 0.0;
				}
			isolation_deltabeta_vtx_bkg_05_eff[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_deltabeta_vs_vtx1->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_deltabeta_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "25: Found vtx 10% background point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_deltabeta_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_deltabeta_vtx_bkg_10[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_deltabeta_vtx_bkg_10[y-1] = 0.0;
				}
			isolation_deltabeta_vtx_bkg_10_eff[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_deltabeta_vs_vtx1->Integral(0,x,1,nbins)/iso_deltabeta_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_deltabeta_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "26: Found vtx 15% background point for the delta beta method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_deltabeta_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_deltabeta_vtx_bkg_15[y-1] = iso_deltabeta_vs_vtx1->Integral(0,x,y,y)/iso_deltabeta_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_deltabeta_vtx_bkg_15[y-1] = 0.0;
				}
			isolation_deltabeta_vtx_bkg_15_eff[y-1] = iso_deltabeta_vs_vtx2->Integral(0,x,y,y)/iso_deltabeta_vs_vtx2->Integral(0,2000,y,y);
			}
		}

//PUPPI Background

	if (iso_puppi_vs_vtx1->Integral(0,x,1,nbins)/iso_puppi_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_puppi_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "27: Found vtx 05% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_puppi_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppi_vtx_bkg_05[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppi_vtx_bkg_05[y-1] = 0.0;
				}
			isolation_puppi_vtx_bkg_05_eff[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppi_vs_vtx1->Integral(0,x,1,nbins)/iso_puppi_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_puppi_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "28: Found vtx 10% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_puppi_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppi_vtx_bkg_10[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppi_vtx_bkg_10[y-1] = 0.0;
				}
			isolation_puppi_vtx_bkg_10_eff[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppi_vs_vtx1->Integral(0,x,1,nbins)/iso_puppi_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_puppi_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "29: Found vtx 15% background point for the puppi method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_puppi_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppi_vtx_bkg_15[y-1] = iso_puppi_vs_vtx1->Integral(0,x,y,y)/iso_puppi_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppi_vtx_bkg_15[y-1] = 0.0;
				}
			isolation_puppi_vtx_bkg_15_eff[y-1] = iso_puppi_vs_vtx2->Integral(0,x,y,y)/iso_puppi_vs_vtx2->Integral(0,2000,y,y);
			}
		}

//PUPPI No Leptons Background

	if (iso_puppinl_vs_vtx1->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_puppinl_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "30: Found vtx 05% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_puppinl_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppinl_vtx_bkg_05[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppinl_vtx_bkg_05[y-1] = 0.0;
				}
			isolation_puppinl_vtx_bkg_05_eff[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_puppinl_vs_vtx1->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_puppinl_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "31: Found vtx 10% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_puppinl_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppinl_vtx_bkg_10[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppinl_vtx_bkg_10[y-1] = 0.0;
				}
			isolation_puppinl_vtx_bkg_10_eff[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			}
		}


	if (iso_puppinl_vs_vtx1->Integral(0,x,1,nbins)/iso_puppinl_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_puppinl_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "32: Found vtx 15% background point for the puppi no leptons method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_puppinl_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_puppinl_vtx_bkg_15[y-1] = iso_puppinl_vs_vtx1->Integral(0,x,y,y)/iso_puppinl_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_puppinl_vtx_bkg_15[y-1] = 0.0;
				}
			isolation_puppinl_vtx_bkg_15_eff[y-1] = iso_puppinl_vs_vtx2->Integral(0,x,y,y)/iso_puppinl_vs_vtx2->Integral(0,2000,y,y);
			}
		}


//CITK Background

	if (iso_citk_vs_vtx1->Integral(0,x,1,nbins)/iso_citk_vs_vtx1->Integral(0,2000,1,nbins) > .05 and isolation_citk_vtx_bkg_05[0] == 0)
		{
		if (show_steps) { cout << "33: Found vtx 5% background point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_citk_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_citk_vtx_bkg_05[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_citk_vtx_bkg_05[y-1] = 0.0;
				}
			isolation_citk_vtx_bkg_05_eff[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_citk_vs_vtx1->Integral(0,x,1,nbins)/iso_citk_vs_vtx1->Integral(0,2000,1,nbins) > .10 and isolation_citk_vtx_bkg_10[0] == 0)
		{
		if (show_steps) { cout << "34: Found vtx 10% background point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_citk_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_citk_vtx_bkg_10[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_citk_vtx_bkg_10[y-1] = 0.0;
				}
			isolation_citk_vtx_bkg_10_eff[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			}
		}

	if (iso_citk_vs_vtx1->Integral(0,x,1,nbins)/iso_citk_vs_vtx1->Integral(0,2000,1,nbins) > .15 and isolation_citk_vtx_bkg_15[0] == 0)
		{
		if (show_steps) { cout << "35: Found vtx 15% background point for the citk method: " << x << endl; } 
		for (int y = 1; y <= nbins; y++)
			{
			if (iso_citk_vs_vtx1->Integral(0,2000,y,y) > 0.0)
				{
				isolation_citk_vtx_bkg_15[y-1] = iso_citk_vs_vtx1->Integral(0,x,y,y)/iso_citk_vs_vtx1->Integral(0,2000,y,y);
				}
			else
				{
				isolation_citk_vtx_bkg_15[y-1] = 0.0;
				}
			isolation_citk_vtx_bkg_15_eff[y-1] = iso_citk_vs_vtx2->Integral(0,x,y,y)/iso_citk_vs_vtx2->Integral(0,2000,y,y);
			}
		}


	}

	
  if (show_steps) { std::cout << "Efficiency and Background points choosen!" << endl; }

  //Declare  TGraphAsymmErrors
  TGraphAsymmErrors *ele_pfiso_simple_vtx_eff = new TGraphAsymmErrors(ele_pfiso_simple_vtx_eff_pass, ele_pfiso_simple_vtx_eff_tot);
  TGraphAsymmErrors *ele_pfiso_effarea_vtx_eff = new TGraphAsymmErrors(ele_pfiso_effarea_vtx_eff_pass, ele_pfiso_effarea_vtx_eff_tot);
  TGraphAsymmErrors *ele_pfiso_deltabeta_vtx_eff = new TGraphAsymmErrors(ele_pfiso_deltabeta_vtx_eff_pass, ele_pfiso_deltabeta_vtx_eff_tot);
  TGraphAsymmErrors *ele_pfiso_puppi_vtx_eff = new TGraphAsymmErrors(ele_pfiso_puppi_vtx_eff_pass, ele_pfiso_puppi_vtx_eff_tot);
  TGraphAsymmErrors *ele_pfiso_puppinl_vtx_eff = new TGraphAsymmErrors(ele_pfiso_puppinl_vtx_eff_pass, ele_pfiso_puppinl_vtx_eff_tot);
  TGraphAsymmErrors *ele_pfiso_citk_vtx_eff = new TGraphAsymmErrors(ele_pfiso_citk_vtx_eff_pass, ele_pfiso_citk_vtx_eff_tot);


  TGraphAsymmErrors *ele_pfiso_simple_vtx_eff_99 = new TGraphAsymmErrors(ele_pfiso_simple_vtx_eff_99_pass, ele_pfiso_simple_vtx_eff_99_tot);
  TGraphAsymmErrors *ele_pfiso_effarea_vtx_eff_99 = new TGraphAsymmErrors(ele_pfiso_effarea_vtx_eff_99_pass, ele_pfiso_effarea_vtx_eff_99_tot);
  TGraphAsymmErrors *ele_pfiso_deltabeta_vtx_eff_99 = new TGraphAsymmErrors(ele_pfiso_deltabeta_vtx_eff_99_pass, ele_pfiso_deltabeta_vtx_eff_99_tot);
  TGraphAsymmErrors *ele_pfiso_puppi_vtx_eff_99 = new TGraphAsymmErrors(ele_pfiso_puppi_vtx_eff_99_pass, ele_pfiso_puppi_vtx_eff_99_tot);
  TGraphAsymmErrors *ele_pfiso_puppinl_vtx_eff_99 = new TGraphAsymmErrors(ele_pfiso_puppinl_vtx_eff_99_pass, ele_pfiso_puppinl_vtx_eff_99_tot);
  TGraphAsymmErrors *ele_pfiso_citk_vtx_eff_99 = new TGraphAsymmErrors(ele_pfiso_citk_vtx_eff_99_pass, ele_pfiso_citk_vtx_eff_99_tot);

  TGraphAsymmErrors *ele_pfiso_simple_vtx_eff_95 = new TGraphAsymmErrors(ele_pfiso_simple_vtx_eff_95_pass, ele_pfiso_simple_vtx_eff_95_tot);


  TGraphAsymmErrors *ele_pfiso_puppinl_vtx_eff_95 = new TGraphAsymmErrors(ele_pfiso_puppinl_vtx_eff_95_pass, ele_pfiso_puppinl_vtx_eff_95_tot);


  TGraphAsymmErrors *ele_pfiso_simple_vtx_eff_90 = new TGraphAsymmErrors(ele_pfiso_simple_vtx_eff_90_pass, ele_pfiso_simple_vtx_eff_90_tot);

  TGraphAsymmErrors *ele_pfiso_puppinl_vtx_eff_90 = new TGraphAsymmErrors(ele_pfiso_puppinl_vtx_eff_90_pass, ele_pfiso_puppinl_vtx_eff_90_tot);

  std::cout << "Setting the histograms" << endl;

   nbins = iso_simple_vs_vtx1->GetNbinsY();

   for (int x=0; x<=nbins; x++)
	{
	//ele_pfiso_simple_vtx_eff->SetBinContent(x+1,isolation_simple_vtx[1][x]);
	//ele_pfiso_effarea_vtx_eff->SetBinContent(x+1,isolation_effarea_vtx[1][x]);
	//ele_pfiso_deltabeta_vtx_eff->SetBinContent(x+1,isolation_deltabeta_vtx[1][x]);
	//ele_pfiso_puppi_vtx_eff->SetBinContent(x+1,isolation_puppi_vtx[1][x]);
	//ele_pfiso_puppinl_vtx_eff->SetBinContent(x+1,isolation_puppinl_vtx[1][x]);
	//ele_pfiso_citk_vtx_eff->SetBinContent(x+1,isolation_citk_vtx[1][x]);
	//ele_pfiso_simple_vtx_eff->SetBinError(x+1,0);
	//ele_pfiso_effarea_vtx_eff->SetBinError(x+1,0);
	//ele_pfiso_deltabeta_vtx_eff->SetBinError(x+1,0);
	//ele_pfiso_puppi_vtx_eff->SetBinError(x+1,0);
	//ele_pfiso_puppinl_vtx_eff->SetBinError(x+1,0);
	//ele_pfiso_citk_vtx_eff->SetBinError(x+1,0);

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

	if (isolation_simple_vtx[0][x] > 0.0)
		{
		ele_pfiso_simple_vtx_ratio->SetBinContent(x+1,isolation_simple_vtx[1][x]/isolation_simple_vtx[0][x]);
		}
	else
		{
		ele_pfiso_simple_vtx_ratio->SetBinContent(x+1,0.0);
		}

	if (isolation_effarea_vtx[0][x] > 0.0)
		{
		ele_pfiso_effarea_vtx_ratio->SetBinContent(x+1,isolation_effarea_vtx[1][x]/isolation_effarea_vtx[0][x]);
		}
	else
		{
		ele_pfiso_effarea_vtx_ratio->SetBinContent(x+1,0.0);
		}

	if (isolation_deltabeta_vtx[0][x] > 0.0)
		{
		ele_pfiso_deltabeta_vtx_ratio->SetBinContent(x+1,isolation_deltabeta_vtx[1][x]/isolation_deltabeta_vtx[0][x]);
		}
	else
		{
		ele_pfiso_deltabeta_vtx_ratio->SetBinContent(x+1,0.0);
		}

	if (isolation_puppi_vtx[0][x] > 0.0)
		{
		ele_pfiso_puppi_vtx_ratio->SetBinContent(x+1,isolation_puppi_vtx[1][x]/isolation_puppi_vtx[0][x]);
		}
	else
		{
		ele_pfiso_puppi_vtx_ratio->SetBinContent(x+1,0.0);
		}

	if (isolation_puppinl_vtx[0][x] > 0.0)
		{
		ele_pfiso_puppinl_vtx_ratio->SetBinContent(x+1,isolation_puppinl_vtx[1][x]/isolation_puppinl_vtx[0][x]);
		}
	else
		{
		ele_pfiso_puppinl_vtx_ratio->SetBinContent(x+1,0.0);
		}

	if (isolation_citk_vtx[0][x] > 0.0)
		{
		ele_pfiso_citk_vtx_ratio->SetBinContent(x+1,isolation_citk_vtx[1][x]/isolation_citk_vtx[0][x]);
		}
	else
		{
		ele_pfiso_citk_vtx_ratio->SetBinContent(x+1,0.0);
		}

	ele_pfiso_simple_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_effarea_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_deltabeta_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_puppi_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_ratio->SetBinError(x+1,0);
	ele_pfiso_citk_vtx_ratio->SetBinError(x+1,0);

	//ele_pfiso_simple_vtx_eff_99->SetBinContent(x+1,isolation_simple_vtx_eff_99[x]);
	//ele_pfiso_simple_vtx_eff_99->SetBinError(x+1,0);
	//ele_pfiso_simple_vtx_eff_95->SetBinContent(x+1,isolation_simple_vtx_eff_95[x]);
	//ele_pfiso_simple_vtx_eff_95->SetBinError(x+1,0);
	//ele_pfiso_simple_vtx_eff_90->SetBinContent(x+1,isolation_simple_vtx_eff_90[x]);
	//ele_pfiso_simple_vtx_eff_90->SetBinError(x+1,0);

	ele_pfiso_simple_vtx_eff_99_bkg->SetBinContent(x+1,isolation_simple_vtx_eff_99_bkg[x]);
	ele_pfiso_simple_vtx_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_eff_95_bkg->SetBinContent(x+1,isolation_simple_vtx_eff_95_bkg[x]);
	ele_pfiso_simple_vtx_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_simple_vtx_eff_90_bkg->SetBinContent(x+1,isolation_simple_vtx_eff_90_bkg[x]);
	ele_pfiso_simple_vtx_eff_90_bkg->SetBinError(x+1,0);

	//ele_pfiso_effarea_vtx_eff_99->SetBinContent(x+1,isolation_effarea_vtx_eff_99[x]);
	//ele_pfiso_effarea_vtx_eff_99->SetBinError(x+1,0);
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

	//ele_pfiso_deltabeta_vtx_eff_99->SetBinContent(x+1,isolation_deltabeta_vtx_eff_99[x]);
	//ele_pfiso_deltabeta_vtx_eff_99->SetBinError(x+1,0);
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

	//ele_pfiso_puppi_vtx_eff_99->SetBinContent(x+1,isolation_puppi_vtx_eff_99[x]);
	//ele_pfiso_puppi_vtx_eff_99->SetBinError(x+1,0);
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

	//ele_pfiso_puppinl_vtx_eff_99->SetBinContent(x+1,isolation_puppinl_vtx_eff_99[x]);
	//ele_pfiso_puppinl_vtx_eff_99->SetBinError(x+1,0);
	//ele_pfiso_puppinl_vtx_eff_95->SetBinContent(x+1,isolation_puppinl_vtx_eff_95[x]);
	//ele_pfiso_puppinl_vtx_eff_95->SetBinError(x+1,0);
	//ele_pfiso_puppinl_vtx_eff_90->SetBinContent(x+1,isolation_puppinl_vtx_eff_90[x]);
	//ele_pfiso_puppinl_vtx_eff_90->SetBinError(x+1,0);

	ele_pfiso_puppinl_vtx_eff_99_bkg->SetBinContent(x+1,isolation_puppinl_vtx_eff_99_bkg[x]);
	ele_pfiso_puppinl_vtx_eff_99_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_eff_95_bkg->SetBinContent(x+1,isolation_puppinl_vtx_eff_95_bkg[x]);
	ele_pfiso_puppinl_vtx_eff_95_bkg->SetBinError(x+1,0);
	ele_pfiso_puppinl_vtx_eff_90_bkg->SetBinContent(x+1,isolation_puppinl_vtx_eff_90_bkg[x]);
	ele_pfiso_puppinl_vtx_eff_90_bkg->SetBinError(x+1,0);

	//ele_pfiso_citk_vtx_eff_99->SetBinContent(x+1,isolation_citk_vtx_eff_99[x]);
	//ele_pfiso_citk_vtx_eff_99->SetBinError(x+1,0);
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

   for (int x=0; x<=nbins; x++)
	{
	if (test) { cout << x << " - " << isolation_effarea_vtx[1][x] << " | " << isolation_effarea_vtx[0][x] << endl; }
	}


   plot_histogram(ele_pfiso_simple_vtx_eff_pass, "output/","ele_pfiso_simple_vtx_eff_pass", "Electron PF Isolation Simple Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_simple_vtx_eff_tot, "output/","ele_pfiso_simple_vtx_eff_tot", "Electron PF Isolation Simple Number of Vertices", "top_right", false);

   plot_eff(ele_pfiso_simple_vtx_eff, "output/","ele_pfiso_simple_vtx_eff", "Electron PF Isolation Simple Number of Vertices", "top_right", false, true);


   plot_histogram(ele_pfiso_effarea_vtx_eff_pass, "output/","ele_pfiso_effarea_vtx_eff_pass", "Electron PF Isolation Effective Area Number of Vertices", "bottom_left", false);
   plot_histogram(ele_pfiso_effarea_vtx_eff_tot, "output/","ele_pfiso_effarea_vtx_eff_tot", "Electron PF Isolation Effective Area Number of Vertices", "bottom_left", false);

   plot_eff(ele_pfiso_effarea_vtx_eff, "output/","ele_pfiso_effarea_vtx_eff", "Electron PF Isolation Effective Area Number of Vertices", "bottom_left", false);


   plot_histogram(ele_pfiso_deltabeta_vtx_eff_pass, "output/","ele_pfiso_deltabeta_vtx_eff_pass", "Electron PF Isolation Delta Beta Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_vtx_eff_tot, "output/","ele_pfiso_deltabeta_vtx_eff_tot", "Electron PF Isolation Delta Beta Number of Vertices", "top_right", false);

   plot_eff(ele_pfiso_deltabeta_vtx_eff, "output/","ele_pfiso_deltabeta_vtx_eff", "Electron PF Isolation Delta Beta Number of Vertices", "top_right", false);


   plot_histogram(ele_pfiso_puppi_vtx_eff_pass, "output/","ele_pfiso_puppi_vtx_eff_pass", "Electron PF Isolation PUPPI Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppi_vtx_eff_tot, "output/","ele_pfiso_puppi_vtx_eff_tot", "Electron PF Isolation PUPPI Number of Vertices", "top_right", false);

   plot_eff(ele_pfiso_puppi_vtx_eff, "output/","ele_pfiso_puppi_vtx_eff", "Electron PF Isolation PUPPI Number of Vertices", "top_right", false);


   plot_histogram(ele_pfiso_puppinl_vtx_eff_pass, "output/","ele_pfiso_puppinl_vtx_eff_pass", "Electron PF Isolation PUPPI No Leptons Number of Vertices", "bottom_left", false);
   plot_histogram(ele_pfiso_puppinl_vtx_eff_tot, "output/","ele_pfiso_puppinl_vtx_eff_tot", "Electron PF Isolation PUPPI No Leptons Number of Vertices", "bottom_left", false);

   plot_eff(ele_pfiso_puppinl_vtx_eff, "output/","ele_pfiso_puppinl_vtx_eff", "Electron PF Isolation PUPPI No Leptons Number of Vertices", "bottom_left", false);


   plot_histogram(ele_pfiso_citk_vtx_eff_pass, "output/","ele_pfiso_citk_vtx_eff_pass", "Electron PF Isolation CITK Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_citk_vtx_eff_tot, "output/","ele_pfiso_citk_vtx_eff_tot", "Electron PF Isolation CITK Number of Vertices", "top_right", false);

   plot_eff(ele_pfiso_citk_vtx_eff, "output/","ele_pfiso_citk_vtx_eff", "Electron PF Isolation CITK Number of Vertices", "top_right", false);

   // plot_six_dist(ele_pfiso_simple_vtx_eff, "PF without PU subtraction", ele_pfiso_effarea_vtx_eff, "Effective Area", ele_pfiso_deltabeta_vtx_eff, "Delta Beta", ele_pfiso_puppi_vtx_eff, "PUPPI", ele_pfiso_puppinl_vtx_eff, "PUPPI No Leptons", ele_pfiso_citk_vtx_eff, "CITK", "output/", "", "ele_pfiso_vtx_eff", "bottom_left", false, 0.55, 1.0, false);


   //plot_4histograms(ele_pfiso_effarea_vtx_eff, "Effective Area", ele_pfiso_deltabeta_vtx_eff, "Delta Beta", ele_pfiso_puppi_vtx_eff, "PUPPI", ele_pfiso_puppinl_vtx_eff, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_eff_pres", "bottom_left", false, 0.55, 1.0, false);


   plot_histogram(ele_pfiso_simple_vtx_bkg, "output/","ele_pfiso_simple_vtx_bkg", "Electron PF Isolation Simple Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_effarea_vtx_bkg, "output/","ele_pfiso_effarea_vtx_bkg", "Electron PF Isolation Effective Area Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_vtx_bkg, "output/","ele_pfiso_deltabeta_vtx_bkg", "Electron PF Isolation Delta Beta Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppi_vtx_bkg, "output/","ele_pfiso_puppi_vtx_bkg", "Electron PF Isolation PUPPI Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_vtx_bkg, "output/","ele_pfiso_puppinl_vtx_bkg", "Electron PF Isolation PUPPI No Leptons Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_citk_vtx_bkg, "output/","ele_pfiso_citk_vtx_bkg", "Electron PF Isolation CITK Number of Vertices", "top_right", false);

   plot_6histograms(ele_pfiso_simple_vtx_bkg, "PF without PU subtraction", ele_pfiso_effarea_vtx_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_bkg, "Delta Beta", ele_pfiso_puppi_vtx_bkg, "PUPPI", ele_pfiso_puppinl_vtx_bkg, "PUPPI No Leptons", ele_pfiso_citk_vtx_bkg, "CITK", "output/", "", "ele_pfiso_vtx_bkg", "bottom_right", false, 0.0, 0.22, false);

   plot_4histograms(ele_pfiso_effarea_vtx_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_bkg, "Delta Beta", ele_pfiso_puppi_vtx_bkg, "PUPPI", ele_pfiso_puppinl_vtx_bkg, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_bkg_pres", "top_right", false, 0.0, 0.20, false);

   plot_histogram(ele_pfiso_simple_vtx_ratio, "output/","ele_pfiso_simple_vtx_ratio", "Electron PF Isolation Simple Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_effarea_vtx_ratio, "output/","ele_pfiso_effarea_vtx_ratio", "Electron PF Isolation Effective Area Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_vtx_ratio, "output/","ele_pfiso_deltabeta_vtx_ratio", "Electron PF Isolation Delta Beta Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppi_vtx_ratio, "output/","ele_pfiso_puppi_vtx_ratio", "Electron PF Isolation PUPPI Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_vtx_ratio, "output/","ele_pfiso_puppinl_vtx_ratio", "Electron PF Isolation PUPPI No Leptons Number of Vertices", "top_right", false);
   plot_histogram(ele_pfiso_citk_vtx_ratio, "output/","ele_pfiso_citk_vtx_ratio", "Electron PF Isolation CITK Number of Vertices", "top_right", false);

   plot_6histograms(ele_pfiso_simple_vtx_ratio, "PF without PU subtraction", ele_pfiso_effarea_vtx_ratio, "Effective Area", ele_pfiso_deltabeta_vtx_ratio, "Delta Beta", ele_pfiso_puppi_vtx_ratio, "PUPPI", ele_pfiso_puppinl_vtx_ratio, "PUPPI No Leptons", ele_pfiso_citk_vtx_ratio, "CITK", "output/", "", "ele_pfiso_vtx_ratio", "bottom_right", false, 0.0, 15.0, false);

   plot_4histograms(ele_pfiso_effarea_vtx_ratio, "Effective Area", ele_pfiso_deltabeta_vtx_ratio, "Delta Beta", ele_pfiso_puppi_vtx_ratio, "PUPPI", ele_pfiso_puppinl_vtx_ratio, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_ratio_pres", "top_right", false, 4.0, 15.0, false);


  create_eff_plot(ele_pfiso_simple_vtx_eff_99_pass, ele_pfiso_simple_vtx_eff_99_tot, ele_pfiso_simple_vtx_eff_99, "output/", "ele_pfiso_simple_vtx_eff_99", "Electron PF Isolation Simple vtx with 99% effeciency");
  create_eff_plot(ele_pfiso_simple_vtx_eff_95_pass, ele_pfiso_simple_vtx_eff_95_tot, ele_pfiso_puppinl_vtx_eff_95, "output/", "ele_pfiso_simple_vtx_eff_95", "Electron PF Isolation Simple vtx with 95% effeciency");
  create_eff_plot(ele_pfiso_simple_vtx_eff_90_pass, ele_pfiso_simple_vtx_eff_90_tot, ele_pfiso_simple_vtx_eff_90, "output/", "ele_pfiso_simple_vtx_eff_90", "Electron PF Isolation Simple vtx with 90% effeciency");


  // plot_3histograms(ele_pfiso_simple_vtx_eff_90, "90% signal efficiency", ele_pfiso_simple_vtx_eff_95, "95% signal efficiency", ele_pfiso_simple_vtx_eff_99, "99% signal efficiency", "output/", "ele_pfiso_simple_vtx_eff_all", "bottom_left", false, 0.72, 1.0, false);

  plot_histogram(ele_pfiso_simple_vtx_bkg_05_eff, "output/","ele_pfiso_simple_vtx_bkg_05_eff", "Electron PF Isolation Simple vtx with 05% background", "top_right", false);
  plot_histogram(ele_pfiso_simple_vtx_bkg_10_eff, "output/","ele_pfiso_simple_vtx_bkg_10_eff", "Electron PF Isolation Simple vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_simple_vtx_bkg_15_eff, "output/","ele_pfiso_simple_vtx_bkg_15_eff", "Electron PF Isolation Simple vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_simple_vtx_bkg_05_eff, "5% background", ele_pfiso_simple_vtx_bkg_10_eff, "10% background", ele_pfiso_simple_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_simple_vtx_bkg_all_eff", "bottom_left", false, 0.5, 1.0, false);

  create_eff_plot(ele_pfiso_effarea_vtx_eff_99_pass, ele_pfiso_effarea_vtx_eff_99_tot, ele_pfiso_effarea_vtx_eff_99, "output/", "ele_pfiso_effarea_vtx_eff_99", "Electron PF Isolation Effective Area vtx with 99% effeciency");

  plot_histogram(ele_pfiso_effarea_vtx_eff_95, "output/","ele_pfiso_effarea_vtx_eff_95", "Electron PF Isolation Effective Area vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_eff_90, "output/","ele_pfiso_effarea_vtx_eff_90", "Electron PF Isolation Effective Area vtx with 90% effeciency", "top_right", false);

  //plot_3histograms(ele_pfiso_effarea_vtx_eff_90, "90% signal efficiency", ele_pfiso_effarea_vtx_eff_95, "95% signal efficiency", ele_pfiso_effarea_vtx_eff_99, "99% signal efficiency", "output/", "ele_pfiso_effarea_vtx_eff_all", "bottom_right", false, 0.8, 1.0, false);

  plot_histogram(ele_pfiso_effarea_vtx_bkg_05_eff, "output/","ele_pfiso_effarea_vtx_bkg_05_eff", "Electron PF Isolation Effective Area vtx with 05% background", "top_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_bkg_10_eff, "output/","ele_pfiso_effarea_vtx_bkg_10_eff", "Electron PF Isolation Effective Area vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_bkg_15_eff, "output/","ele_pfiso_effarea_vtx_bkg_15_eff", "Electron PF Isolation Effective Area vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_effarea_vtx_bkg_05_eff, "5% background", ele_pfiso_effarea_vtx_bkg_10_eff, "10% background", ele_pfiso_effarea_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_effarea_vtx_bkg_all_eff", "bottom_left", false, 0.78, 1.0, false);

  create_eff_plot(ele_pfiso_deltabeta_vtx_eff_99_pass, ele_pfiso_deltabeta_vtx_eff_99_tot, ele_pfiso_deltabeta_vtx_eff_99, "output/", "ele_pfiso_deltabeta_vtx_eff_99", "Electron PF Isolation Delta Beta vtx with 99% effeciency");

  plot_histogram(ele_pfiso_deltabeta_vtx_eff_95, "output/","ele_pfiso_deltabeta_vtx_eff_95", "Electron PF Isolation Delta Beta vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_eff_90, "output/","ele_pfiso_deltabeta_vtx_eff_90", "Electron PF Isolation Delta Beta vtx with 90% effeciency", "top_right", false);

  //plot_3histograms(ele_pfiso_deltabeta_vtx_eff_90, "90% signal efficiency", ele_pfiso_deltabeta_vtx_eff_95, "95% signal efficiency", ele_pfiso_deltabeta_vtx_eff_99, "99% signal efficiency", "output/", "ele_pfiso_deltabeta_vtx_eff_all", "bottom_left", false, 0.8, 1.0, false);

  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_05_eff, "output/","ele_pfiso_deltabeta_vtx_bkg_05_eff", "Electron PF Isolation Delta Beta vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_10_eff, "output/","ele_pfiso_deltabeta_vtx_bkg_10_eff", "Electron PF Isolation Delta Beta vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_15_eff, "output/","ele_pfiso_deltabeta_vtx_bkg_15_eff", "Electron PF Isolation Delta Beta vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_deltabeta_vtx_bkg_05_eff, "5% background", ele_pfiso_deltabeta_vtx_bkg_10_eff, "10% background", ele_pfiso_deltabeta_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_deltabeta_vtx_bkg_all_eff", "bottom_left", false, 0.75, 1.0, false);

  create_eff_plot(ele_pfiso_puppi_vtx_eff_99_pass, ele_pfiso_puppi_vtx_eff_99_tot, ele_pfiso_puppi_vtx_eff_99, "output/", "ele_pfiso_puppi_vtx_eff_99", "Electron PF Isolation PUPPI vtx with 99% effeciency");


  plot_histogram(ele_pfiso_puppi_vtx_eff_95, "output/","ele_pfiso_puppi_vtx_eff_95", "Electron PF Isolation PUPPI vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_puppi_vtx_eff_90, "output/","ele_pfiso_puppi_vtx_eff_90", "Electron PF Isolation PUPPI vtx with 90% effeciency", "top_right", false);

  //plot_3histograms(ele_pfiso_puppi_vtx_eff_90, "90% signal efficiency", ele_pfiso_puppi_vtx_eff_95, "95% signal efficiency", ele_pfiso_puppi_vtx_eff_99, "99% signal efficiency", "output/", "ele_pfiso_puppi_vtx_eff_all", "bottom_left", false, 0.65, 1.0, false);

  plot_histogram(ele_pfiso_puppi_vtx_bkg_05_eff, "output/","ele_pfiso_puppi_vtx_bkg_05_eff", "Electron PF Isolation PUPPI vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_puppi_vtx_bkg_10_eff, "output/","ele_pfiso_puppi_vtx_bkg_10_eff", "Electron PF Isolation PUPPI vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_puppi_vtx_bkg_15_eff, "output/","ele_pfiso_puppi_vtx_bkg_15_eff", "Electron PF Isolation PUPPI vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_puppi_vtx_bkg_05_eff, "5% background", ele_pfiso_puppi_vtx_bkg_10_eff, "10% background", ele_pfiso_puppi_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_puppi_vtx_bkg_all_eff", "bottom_left", false, 0.3, 1.0, false);

  create_eff_plot(ele_pfiso_puppinl_vtx_eff_99_pass, ele_pfiso_puppinl_vtx_eff_99_tot, ele_pfiso_puppinl_vtx_eff_99, "output/", "ele_pfiso_puppinl_vtx_eff_99", "Electron PF Isolation PUPPI No Leptons vtx with 99% effeciency");
  create_eff_plot(ele_pfiso_puppinl_vtx_eff_95_pass, ele_pfiso_puppinl_vtx_eff_95_tot, ele_pfiso_puppinl_vtx_eff_95, "output/", "ele_pfiso_puppinl_vtx_eff_95", "Electron PF Isolation PUPPI No Leptons vtx with 95% effeciency");
  create_eff_plot(ele_pfiso_puppinl_vtx_eff_90_pass, ele_pfiso_puppinl_vtx_eff_90_tot, ele_pfiso_puppinl_vtx_eff_90, "output/", "ele_pfiso_puppinl_vtx_eff_90", "Electron PF Isolation PUPPI No Leptons vtx with 90% effeciency");

  //plot_3histograms(ele_pfiso_puppinl_vtx_eff_90, "90% signal efficiency", ele_pfiso_puppinl_vtx_eff_95, "95% signal efficiency", ele_pfiso_puppinl_vtx_eff_99, "99% signal efficiency", "output/", "ele_pfiso_puppinl_vtx_eff_all", "bottom_left", false, 0.7, 1.0, false);

  plot_histogram(ele_pfiso_puppinl_vtx_bkg_05_eff, "output/","ele_pfiso_puppinl_vtx_bkg_05_eff", "Electron PF Isolation PUPPI No Leptons vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_puppinl_vtx_bkg_10_eff, "output/","ele_pfiso_puppinl_vtx_bkg_10_eff", "Electron PF Isolation PUPPI No Leptons vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_puppinl_vtx_bkg_15_eff, "output/","ele_pfiso_puppinl_vtx_bkg_15_eff", "Electron PF Isolation PUPPI No Leptons vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_puppinl_vtx_bkg_05_eff, "5% background", ele_pfiso_puppinl_vtx_bkg_10_eff, "10% background", ele_pfiso_puppinl_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_puppinl_vtx_bkg_all_eff", "bottom_left", false, 0.3, 1.0, false);

  create_eff_plot(ele_pfiso_citk_vtx_eff_99_pass, ele_pfiso_citk_vtx_eff_99_tot, ele_pfiso_citk_vtx_eff_99, "output/", "ele_pfiso_citk_vtx_eff_99", "Electron PF Isolation CITK vtx with 99% effeciency");

  plot_histogram(ele_pfiso_citk_vtx_eff_95, "output/","ele_pfiso_citk_vtx_eff_95", "Electron PF Isolation CITK vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_citk_vtx_eff_90, "output/","ele_pfiso_citk_vtx_eff_90", "Electron PF Isolation CITK vtx with 90% effeciency", "top_right", false);

  //plot_3histograms(ele_pfiso_citk_vtx_eff_90, "90% signal efficiency", ele_pfiso_citk_vtx_eff_95, "95% signal efficiency", ele_pfiso_citk_vtx_eff_99, "99% signal efficiency", "output/", "ele_pfiso_citk_vtx_eff_all", "bottom_left", false, 0.7, 1.0, false);

  plot_histogram(ele_pfiso_citk_vtx_bkg_05_eff, "output/","ele_pfiso_citk_vtx_bkg_05_eff", "Electron PF Isolation CITK vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_citk_vtx_bkg_10_eff, "output/","ele_pfiso_citk_vtx_bkg_10_eff", "Electron PF Isolation CITK vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_citk_vtx_bkg_15_eff, "output/","ele_pfiso_citk_vtx_bkg_15_eff", "Electron PF Isolation CITK vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_citk_vtx_bkg_05_eff, "5% background", ele_pfiso_citk_vtx_bkg_10_eff, "10% background", ele_pfiso_citk_vtx_bkg_15_eff, "15% background", "output/", "ele_pfiso_citk_vtx_bkg_all_eff", "bottom_left", false, 0.5, 1.0, false);

  // plot_six_dist(ele_pfiso_simple_vtx_eff_90, "PF without PU subtraction", ele_pfiso_effarea_vtx_eff_90, "Effective Area", ele_pfiso_deltabeta_vtx_eff_90, "Delta Beta", ele_pfiso_puppi_vtx_eff_90, "PUPPI", ele_pfiso_puppinl_vtx_eff_90, "PUPPI No Leptons", ele_pfiso_citk_vtx_eff_90, "CITK", "output/", "", "ele_pfiso_vtx_eff_90", "bottom_left", false, 0.65, 1.0, false);

  // plot_six_dist(ele_pfiso_simple_vtx_eff_95, "PF without PU subtraction", ele_pfiso_effarea_vtx_eff_95, "Effective Area", ele_pfiso_deltabeta_vtx_eff_95, "Delta Beta", ele_pfiso_puppi_vtx_eff_95, "PUPPI", ele_pfiso_puppinl_vtx_eff_95, "PUPPI No Leptons", ele_pfiso_citk_vtx_eff_95, "CITK", "output/", "", "ele_pfiso_vtx_eff_95", "bottom_left", false, 0.8, 1.0, false);

  // plot_six_dist(ele_pfiso_simple_vtx_eff_99, "PF without PU subtraction", ele_pfiso_effarea_vtx_eff_99, "Effective Area", ele_pfiso_deltabeta_vtx_eff_99, "Delta Beta", ele_pfiso_puppi_vtx_eff_99, "PUPPI", ele_pfiso_puppinl_vtx_eff_99, "PUPPI No Leptons", ele_pfiso_citk_vtx_eff_99, "CITK", "output/", "", "ele_pfiso_vtx_eff_99", "bottom_left", false, 0.92, 1.0, false);

 //  plot_4histograms(ele_pfiso_effarea_vtx_eff_90, "Effective Area", ele_pfiso_deltabeta_vtx_eff_90, "Delta Beta", ele_pfiso_puppi_vtx_eff_90, "PUPPI", ele_pfiso_puppinl_vtx_eff_90, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_eff_90_pres", "bottom_left", false, 0.65, 1.0, false);

 //  plot_4histograms(ele_pfiso_effarea_vtx_eff_95, "Effective Area", ele_pfiso_deltabeta_vtx_eff_95, "Delta Beta", ele_pfiso_puppi_vtx_eff_95, "PUPPI", ele_pfiso_puppinl_vtx_eff_95, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_eff_95_pres", "bottom_left", false, 0.8, 1.0, false);

 //  plot_4histograms(ele_pfiso_effarea_vtx_eff_99, "Effective Area", ele_pfiso_deltabeta_vtx_eff_99, "Delta Beta", ele_pfiso_puppi_vtx_eff_99, "PUPPI", ele_pfiso_puppinl_vtx_eff_99, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_eff_99_pres", "bottom_left", false, 0.96, 1.0, false);

   plot_6histograms(ele_pfiso_simple_vtx_bkg_05_eff, "PF without PU subtraction", ele_pfiso_effarea_vtx_bkg_05_eff, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_05_eff, "Delta Beta", ele_pfiso_puppi_vtx_bkg_05_eff, "PUPPI", ele_pfiso_puppinl_vtx_bkg_05_eff, "PUPPI No Leptons", ele_pfiso_citk_vtx_bkg_05_eff, "CITK", "output/", "", "ele_pfiso_vtx_bkg_05_eff", "bottom_left", false, 0.4, 1.0, false);

   plot_6histograms(ele_pfiso_simple_vtx_bkg_10_eff, "PF without PU subtraction", ele_pfiso_effarea_vtx_bkg_10_eff, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_10_eff, "Delta Beta", ele_pfiso_puppi_vtx_bkg_10_eff, "PUPPI", ele_pfiso_puppinl_vtx_bkg_10_eff, "PUPPI No Leptons", ele_pfiso_citk_vtx_bkg_10_eff, "CITK", "output/", "", "ele_pfiso_vtx_bkg_10_eff", "bottom_left", false, 0.6, 1.0, false);

   plot_6histograms(ele_pfiso_simple_vtx_bkg_15_eff, "PF without PU subtraction", ele_pfiso_effarea_vtx_bkg_15_eff, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_15_eff, "Delta Beta", ele_pfiso_puppi_vtx_bkg_15_eff, "PUPPI", ele_pfiso_puppinl_vtx_bkg_15_eff, "PUPPI No Leptons", ele_pfiso_citk_vtx_bkg_15_eff, "CITK", "output/", "", "ele_pfiso_vtx_bkg_15_eff", "bottom_left", false, 0.75, 1.0, false);

   plot_4histograms(ele_pfiso_effarea_vtx_bkg_05_eff, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_05_eff, "Delta Beta", ele_pfiso_puppi_vtx_bkg_05_eff, "PUPPI", ele_pfiso_puppinl_vtx_bkg_05_eff, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_bkg_05_eff_pres", "bottom_left", false, 0.4, 1.0, false);

   plot_4histograms(ele_pfiso_effarea_vtx_bkg_10_eff, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_10_eff, "Delta Beta", ele_pfiso_puppi_vtx_bkg_10_eff, "PUPPI", ele_pfiso_puppinl_vtx_bkg_10_eff, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_bkg_10_eff_pres", "bottom_left", false, 0.6, 1.0, false);

   plot_4histograms(ele_pfiso_effarea_vtx_bkg_15_eff, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_15_eff, "Delta Beta", ele_pfiso_puppi_vtx_bkg_15_eff, "PUPPI", ele_pfiso_puppinl_vtx_bkg_15_eff, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_bkg_15_eff_pres", "bottom_left", false, 0.75, 1.0, false);

  plot_histogram(ele_pfiso_simple_vtx_bkg_05, "output/","ele_pfiso_simple_vtx_bkg_05", "Electron PF Isolation Simple vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_simple_vtx_bkg_10, "output/","ele_pfiso_simple_vtx_bkg_10", "Electron PF Isolation Simple vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_simple_vtx_bkg_15, "output/","ele_pfiso_simple_vtx_bkg_15", "Electron PF Isolation Simple vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_simple_vtx_bkg_05, "5% background", ele_pfiso_simple_vtx_bkg_10, "10% background", ele_pfiso_simple_vtx_bkg_15, "15% background", "output/", "ele_pfiso_simple_vtx_bkg_all", "top_right", false, 0.0, 0.17,false);

  plot_histogram(ele_pfiso_simple_vtx_eff_99_bkg, "output/","ele_pfiso_simple_vtx_eff_99_bkg", "Electron PF Isolation Simple vtx with 99% effeciency", "bottom_left", false);
  plot_histogram(ele_pfiso_simple_vtx_eff_95_bkg, "output/","ele_pfiso_simple_vtx_eff_95_bkg", "Electron PF Isolation Simple vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_simple_vtx_eff_90_bkg, "output/","ele_pfiso_simple_vtx_eff_90_bkg", "Electron PF Isolation Simple vtx with 90% effeciency", "top_right", false);

  plot_3histograms(ele_pfiso_simple_vtx_eff_90_bkg, "90% signal efficiency", ele_pfiso_simple_vtx_eff_95_bkg, "95% signal efficiency", ele_pfiso_simple_vtx_eff_99_bkg, "99% signal efficiency", "output/", "ele_pfiso_simple_vtx_eff_all_bkg", "top_left", false, 0.00, 0.52, false);

  plot_histogram(ele_pfiso_effarea_vtx_bkg_05, "output/","ele_pfiso_effarea_vtx_bkg_05", "Electron PF Isolation Effective Area vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_bkg_10, "output/","ele_pfiso_effarea_vtx_bkg_10", "Electron PF Isolation Effective Area vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_bkg_15, "output/","ele_pfiso_effarea_vtx_bkg_15", "Electron PF Isolation Effective Area vtx with 15% background", "bottom_left", false);

  plot_3histograms(ele_pfiso_effarea_vtx_bkg_05, "5% background", ele_pfiso_effarea_vtx_bkg_10, "10% background", ele_pfiso_effarea_vtx_bkg_15, "15% background", "output/", "ele_pfiso_effarea_vtx_bkg_all", "top_left", false, 0.0, 0.52,false);

  plot_histogram(ele_pfiso_effarea_vtx_eff_99_bkg, "output/","ele_pfiso_effarea_vtx_eff_99_bkg", "Electron PF Isolation Effective Area vtx with 99% effeciency", "bottom_left", false);
  plot_histogram(ele_pfiso_effarea_vtx_eff_95_bkg, "output/","ele_pfiso_effarea_vtx_eff_95_bkg", "Electron PF Isolation Effective Area vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_effarea_vtx_eff_90_bkg, "output/","ele_pfiso_effarea_vtx_eff_90_bkg", "Electron PF Isolation Effective Area vtx with 90% effeciency", "top_right", false);

  plot_3histograms(ele_pfiso_effarea_vtx_eff_90_bkg, "90% signal efficiency", ele_pfiso_effarea_vtx_eff_95_bkg, "95% signal efficiency", ele_pfiso_effarea_vtx_eff_99_bkg, "99% signal efficiency", "output/", "ele_pfiso_effarea_vtx_eff_all_bkg", "top_left", false, 0.00, 0.52, false);

  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_05, "output/","ele_pfiso_deltabeta_vtx_bkg_05", "Electron PF Isolation Delta Beta vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_10, "output/","ele_pfiso_deltabeta_vtx_bkg_10", "Electron PF Isolation Delta Beta vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_bkg_15, "output/","ele_pfiso_deltabeta_vtx_bkg_15", "Electron PF Isolation Delta Beta vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_deltabeta_vtx_bkg_05, "5% background", ele_pfiso_deltabeta_vtx_bkg_10, "10% background", ele_pfiso_deltabeta_vtx_bkg_15, "15% background", "output/", "ele_pfiso_deltabeta_vtx_bkg_all", "top_right", false, 0.0, 0.21,false);

  plot_histogram(ele_pfiso_deltabeta_vtx_eff_99_bkg, "output/","ele_pfiso_deltabeta_vtx_eff_99_bkg", "Electron PF Isolation Delta Beta vtx with 99% effeciency", "bottom_left", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_eff_95_bkg, "output/","ele_pfiso_deltabeta_vtx_eff_95_bkg", "Electron PF Isolation Delta Beta vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_deltabeta_vtx_eff_90_bkg, "output/","ele_pfiso_deltabeta_vtx_eff_90_bkg", "Electron PF Isolation Delta Beta vtx with 90% effeciency", "top_right", false);

  plot_3histograms(ele_pfiso_deltabeta_vtx_eff_90_bkg, "90% signal efficiency", ele_pfiso_deltabeta_vtx_eff_95_bkg, "95% signal efficiency", ele_pfiso_deltabeta_vtx_eff_99_bkg, "99% signal efficiency", "output/", "ele_pfiso_deltabeta_vtx_eff_all_bkg", "top_left", false, 0.00, 0.52, false);

  plot_histogram(ele_pfiso_puppi_vtx_bkg_05, "output/","ele_pfiso_puppi_vtx_bkg_05", "Electron PF Isolation PUPPI vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_puppi_vtx_bkg_10, "output/","ele_pfiso_puppi_vtx_bkg_10", "Electron PF Isolation PUPPI vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_puppi_vtx_bkg_15, "output/","ele_pfiso_puppi_vtx_bkg_15", "Electron PF Isolation PUPPI vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_puppi_vtx_bkg_05, "5% background", ele_pfiso_puppi_vtx_bkg_10, "10% background", ele_pfiso_puppi_vtx_bkg_15, "15% background", "output/", "ele_pfiso_puppi_vtx_bkg_all", "top_right", false, 0.0, 0.17,false);

  plot_histogram(ele_pfiso_puppi_vtx_eff_99_bkg, "output/","ele_pfiso_puppi_vtx_eff_99_bkg", "Electron PF Isolation PUPPI vtx with 99% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_puppi_vtx_eff_95_bkg, "output/","ele_pfiso_puppi_vtx_eff_95_bkg", "Electron PF Isolation PUPPI vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_puppi_vtx_eff_90_bkg, "output/","ele_pfiso_puppi_vtx_eff_90_bkg", "Electron PF Isolation PUPPI vtx with 90% effeciency", "top_right", false);

  plot_3histograms(ele_pfiso_puppi_vtx_eff_90_bkg, "90% signal efficiency", ele_pfiso_puppi_vtx_eff_95_bkg, "95% signal efficiency", ele_pfiso_puppi_vtx_eff_99_bkg, "99% signal efficiency", "output/", "ele_pfiso_puppi_vtx_eff_all_bkg", "top_right", false, 0.00, 0.39, false);

  plot_histogram(ele_pfiso_puppinl_vtx_bkg_05, "output/","ele_pfiso_puppinl_vtx_bkg_05", "Electron PF Isolation PUPPI No Leptons vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_puppinl_vtx_bkg_10, "output/","ele_pfiso_puppinl_vtx_bkg_10", "Electron PF Isolation PUPPI No Leptons vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_puppinl_vtx_bkg_15, "output/","ele_pfiso_puppinl_vtx_bkg_15", "Electron PF Isolation PUPPI No Leptons vtx with 15% background", "bottom_left", false);

  plot_3histograms(ele_pfiso_puppinl_vtx_bkg_05, "5% background", ele_pfiso_puppinl_vtx_bkg_10, "10% background", ele_pfiso_puppinl_vtx_bkg_15, "15% background", "output/", "ele_pfiso_puppinl_vtx_bkg_all", "top_right", false, 0.0, 0.17,false);

  plot_histogram(ele_pfiso_puppinl_vtx_eff_99_bkg, "output/","ele_pfiso_puppinl_vtx_eff_99_bkg", "Electron PF Isolation PUPPI No Leptons vtx with 99% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_puppinl_vtx_eff_95_bkg, "output/","ele_pfiso_puppinl_vtx_eff_95_bkg", "Electron PF Isolation PUPPI No Leptons vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_puppinl_vtx_eff_90_bkg, "output/","ele_pfiso_puppinl_vtx_eff_90_bkg", "Electron PF Isolation PUPPI No Leptons vtx with 90% effeciency", "top_right", false);

  plot_3histograms(ele_pfiso_puppinl_vtx_eff_90_bkg, "90% signal efficiency", ele_pfiso_puppinl_vtx_eff_95_bkg, "95% signal efficiency", ele_pfiso_puppinl_vtx_eff_99_bkg, "99% signal efficiency", "output/", "ele_pfiso_puppinl_vtx_eff_all_bkg", "top_right", false, 0.00, 0.34, false);

  plot_histogram(ele_pfiso_citk_vtx_bkg_05, "output/","ele_pfiso_citk_vtx_bkg_05", "Electron PF Isolation CITK vtx with 5% background", "top_right", false);
  plot_histogram(ele_pfiso_citk_vtx_bkg_10, "output/","ele_pfiso_citk_vtx_bkg_10", "Electron PF Isolation CITK vtx with 10% background", "top_right", false);
  plot_histogram(ele_pfiso_citk_vtx_bkg_15, "output/","ele_pfiso_citk_vtx_bkg_15", "Electron PF Isolation CITK vtx with 15% background", "top_right", false);

  plot_3histograms(ele_pfiso_citk_vtx_bkg_05, "5% background", ele_pfiso_citk_vtx_bkg_10, "10% background", ele_pfiso_citk_vtx_bkg_15, "15% background", "output/", "ele_pfiso_citk_vtx_bkg_all", "top_right", false, 0.0, 0.17, false);

  plot_histogram(ele_pfiso_citk_vtx_eff_99_bkg, "output/","ele_pfiso_citk_vtx_eff_99_bkg", "Electron PF Isolation CITK vtx with 99% effeciency", "bottom_left", false);
  plot_histogram(ele_pfiso_citk_vtx_eff_95_bkg, "output/","ele_pfiso_citk_vtx_eff_95_bkg", "Electron PF Isolation CITK vtx with 95% effeciency", "top_right", false);
  plot_histogram(ele_pfiso_citk_vtx_eff_90_bkg, "output/","ele_pfiso_citk_vtx_eff_90_bkg", "Electron PF Isolation CITK vtx with 90% effeciency", "top_right", false);

  plot_3histograms(ele_pfiso_citk_vtx_eff_90_bkg, "90% signal efficiency", ele_pfiso_citk_vtx_eff_95_bkg, "95% signal efficiency", ele_pfiso_citk_vtx_eff_99_bkg, "99% signal efficiency", "output/", "ele_pfiso_citk_vtx_eff_all_bkg", "top_left", false, 0.00, 0.52, false);

   plot_6histograms(ele_pfiso_simple_vtx_bkg_05, "PF without PU subtraction", ele_pfiso_effarea_vtx_bkg_05, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_05, "Delta Beta", ele_pfiso_puppi_vtx_bkg_05, "PUPPI", ele_pfiso_puppinl_vtx_bkg_05, "PUPPI No Leptons", ele_pfiso_citk_vtx_bkg_05, "CITK", "output/", "", "ele_pfiso_vtx_bkg_05", "top_right", false, 0.0, 0.09, false);

   plot_6histograms(ele_pfiso_simple_vtx_bkg_10, "PF without PU subtraction", ele_pfiso_effarea_vtx_bkg_10, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_10, "Delta Beta", ele_pfiso_puppi_vtx_bkg_10, "PUPPI", ele_pfiso_puppinl_vtx_bkg_10, "PUPPI No Leptons", ele_pfiso_citk_vtx_bkg_10, "CITK", "output/", "", "ele_pfiso_vtx_bkg_10", "top_right", false, 0.0, 0.16, false);

   plot_6histograms(ele_pfiso_simple_vtx_bkg_15, "PF without PU subtraction", ele_pfiso_effarea_vtx_bkg_15, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_15, "Delta Beta", ele_pfiso_puppi_vtx_bkg_15, "PUPPI", ele_pfiso_puppinl_vtx_bkg_15, "PUPPI No Leptons", ele_pfiso_citk_vtx_bkg_15, "CITK", "output/", "", "ele_pfiso_vtx_bkg_15", "top_left", false, 0.0, 0.52, false);


   plot_4histograms(ele_pfiso_effarea_vtx_bkg_05, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_05, "Delta Beta", ele_pfiso_puppi_vtx_bkg_05, "PUPPI", ele_pfiso_puppinl_vtx_bkg_05, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_bkg_05_pres", "top_right", false, 0.0, 0.09, false);

   plot_4histograms(ele_pfiso_effarea_vtx_bkg_10, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_10, "Delta Beta", ele_pfiso_puppi_vtx_bkg_10, "PUPPI", ele_pfiso_puppinl_vtx_bkg_10, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_bkg_10_pres", "top_right", false, 0.0, 0.16, false);

   plot_4histograms(ele_pfiso_effarea_vtx_bkg_15, "Effective Area", ele_pfiso_deltabeta_vtx_bkg_15, "Delta Beta", ele_pfiso_puppi_vtx_bkg_15, "PUPPI", ele_pfiso_puppinl_vtx_bkg_15, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_bkg_15_pres", "top_left", false, 0.0, 0.52, false);


   plot_6histograms(ele_pfiso_simple_vtx_eff_90_bkg, "PF without PU subtraction", ele_pfiso_effarea_vtx_eff_90_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_eff_90_bkg, "Delta Beta", ele_pfiso_puppi_vtx_eff_90_bkg, "PUPPI", ele_pfiso_puppinl_vtx_eff_90_bkg, "PUPPI No Leptons", ele_pfiso_citk_vtx_eff_90_bkg, "CITK", "output/", "", "ele_pfiso_vtx_eff_90_bkg", "top_right", false, 0.0, 0.13, false);

   plot_6histograms(ele_pfiso_simple_vtx_eff_95_bkg, "PF without PU subtraction", ele_pfiso_effarea_vtx_eff_95_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_eff_95_bkg, "Delta Beta", ele_pfiso_puppi_vtx_eff_95_bkg, "PUPPI", ele_pfiso_puppinl_vtx_eff_95_bkg, "PUPPI No Leptons", ele_pfiso_citk_vtx_eff_95_bkg, "CITK", "output/", "", "ele_pfiso_vtx_eff_95_bkg", "top_right", false, 0.0, 0.19, false);

   plot_6histograms(ele_pfiso_simple_vtx_eff_99_bkg, "PF without PU subtraction", ele_pfiso_effarea_vtx_eff_99_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_eff_99_bkg, "Delta Beta", ele_pfiso_puppi_vtx_eff_99_bkg, "PUPPI", ele_pfiso_puppinl_vtx_eff_99_bkg, "PUPPI No Leptons", ele_pfiso_citk_vtx_eff_99_bkg, "CITK", "output/", "", "ele_pfiso_vtx_eff_99_bkg", "bottom_left", false, 0.0, 0.52, false);

   plot_4histograms(ele_pfiso_effarea_vtx_eff_90_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_eff_90_bkg, "Delta Beta", ele_pfiso_puppi_vtx_eff_90_bkg, "PUPPI", ele_pfiso_puppinl_vtx_eff_90_bkg, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_eff_90_bkg_pres", "top_right", false, 0.0, 0.13, false);

   plot_4histograms(ele_pfiso_effarea_vtx_eff_95_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_eff_95_bkg, "Delta Beta", ele_pfiso_puppi_vtx_eff_95_bkg, "PUPPI", ele_pfiso_puppinl_vtx_eff_95_bkg, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_eff_95_bkg_pres", "top_right", false, 0.0, 0.19, false);

   plot_4histograms(ele_pfiso_effarea_vtx_eff_99_bkg, "Effective Area", ele_pfiso_deltabeta_vtx_eff_99_bkg, "Delta Beta", ele_pfiso_puppi_vtx_eff_99_bkg, "PUPPI", ele_pfiso_puppinl_vtx_eff_99_bkg, "PUPPI No Leptons", "output/", "ele_pfiso_vtx_eff_99_bkg_pres", "bottom_left", false, 0.0, 0.52, false);

  cout << "-----------------------------------------------" << endl;
  cout << "End of Execution" << endl;
  cout << "-----------------------------------------------" << endl;
  cout << "" << endl;


}
