// Pedro Cipriano, May 2012
// DESY, CMS
// Last Update: 24 May  2013
//
// run_analysis()
// compiles the analysis routines and runs them to do the analysis

#pragma once

#include <iostream>
#include "TROOT.h"

#include "create_directories.C"
#include "plot_histograms.h"
#include "common_methods.h"
#include "pile_up_reweight.C"
#include "electron_isolation_data.C"
#include "electron_isolation.C"
#include "plot_control_plots.C"
#include "plot_control_plots_data.C"
#include "plot_validation.C"
#include "plot_isolation_variables.C"
#include "differential_studies_vtx.C"
#include "differential_studies_eta.C"
#include "differential_studies_pt.C"

void run_analysis()
{

  gROOT->Reset();
  gROOT->SetStyle("Plain");

  bool vtx_weights = false;
  bool read_data = false;
  bool read_mc = true;
  bool diff_studies = false;

  std::cout << "-------------------------------------" << endl;
  std::cout << "Global Setup" << endl;
  if (vtx_weights) { cout << "Monte Carlo Vertex Weights Will be computed!" << endl; }
  if (read_data) { cout << "Data NTuples will be read!" << endl; }
  if (read_mc) { cout << "Monte Carlo NTuples will be read!" << endl; }
  if (diff_studies) { cout << "Differential Studies will be done!" << endl; }
  std::cout << "-------------------------------------" << endl;
  std::cout << " " << endl;

  //create directories
  create_directories("", "output/", "plots");
  create_directories("", "ntuples/", "root");

  if (vtx_weights) { pile_up_reweight(); }
  if (read_data) { electron_isolation_data(); }
  if (read_mc) { electron_isolation(); }
  if (read_data) { plot_control_plots_data(); }
  if (read_mc) { plot_control_plots(); }
  if (read_mc) { plot_isolation_variables(); }
  if (read_mc or read_data) { plot_validation(); }
  if (diff_studies) { differential_studies_vtx(); }
  if (diff_studies) { differential_studies_eta(); }
  if (diff_studies) { differential_studies_pt(); }

}
