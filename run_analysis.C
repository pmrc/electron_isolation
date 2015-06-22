// Pedro Cipriano, May 2012
// DESY, CMS
// Last Update: 29 May  2013
//
// run_analysis()
// compiles the analysis routines and runs them to do the analysis

void run_analysis()
{

  gROOT -> Reset();
  gROOT -> SetStyle("Plain");

  //compilling code
  gROOT -> ProcessLine(".L create_directories.C++");
  gROOT -> ProcessLine(".L common_methods.h++");
  gROOT -> ProcessLine(".L electron_isolation.C++");
  gROOT -> ProcessLine(".L plot_control_plots.C++");
  gROOT -> ProcessLine(".L plot_isolation_variables.C++");

  //create directories
  create_directories("", "output/", "plots");
  create_directories("", "ntuples/", "root");

  electron_isolation();
  plot_control_plots();
  plot_isolation_variables();

}
