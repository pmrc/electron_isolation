// Pedro Cipriano, May 2015
// FESB - Split, CMS
// Last Update: 28 May 2015
//
// 

#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TMath.h>

using namespace std;

void electron_isolation()
{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  std::cout << "Electron Isolation" << endl;
  std::cout << "FESB - Split, CMS" << endl;
  std::cout << "-------------------------------------" << endl;
  std::cout << "Setup" << endl;

  //verbose level
  bool detail = false;
  bool show_steps = true;
  bool test = false; //if set will get some entries from histograms and save outputs with extension _test
  bool show_special_events = false;
  int max_special_events = 1000;

  if (detail) { std::cout << "Detail mode in enabled!" << endl; }
  if (show_steps) { std::cout << "All steps will be showed!" << endl; }
  if (test) { std::cout << "Test mode in enabled!" << endl; }

  std::cout << "-------------------------------------" << endl;

  int samples = 2;
  int working_point = 40;
  string sample[4];
  string out[4];
  string prefix[4];
  bool signal[4];

  sample[0] = "/data_CMS/cms/cipriano/isolationNtuples_Background_RunIISpring15DR74_23_Jun_2015/Background.root";
  sample[1] = "/data_CMS/cms/cipriano/isolationNtuples_ggH_RunIISpring15DR74_23_Jun_2015/ggH.root";
  sample[2] = "/data_CMS/cms/cipriano/isolationNtuples_DYJetsToLL_PHYS14_PU20bx25_18_Jun_2015/DY.root";
  sample[3] = "/data_CMS/cms/cipriano/isolationNtuples_ggH_PHYS14_PU20bx25_18_Jun_2015/ggH.root";

  out[0] = "output/GluGluToH_Background.root";
  out[1] = "output/GluGluToH.root";
  out[2] = "output/DY.root";
  out[3] = "output/ggH.root";

  prefix[0] = "GluGluToH_Background";
  prefix[1] = "GluGluToH";
  prefix[2] = "DY";
  prefix[3] = "GluGluToH";


  signal[0] = false;
  signal[1] = true;
  signal[2] = false;
  signal[3] = true;

  int pt_nbins = 10;
  double pt_bins[11] = {7.0,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,60.0,100.0};
  int vtx_nbins = 22;
  double vtx_bins[23] = {5.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0,22.0,23.0, 24.0,25.0,26.0,27.0,28.0,29.0,30.0,35.0};

  //TFile *dy = TFile::Open( dy_sample.c_str() );

TH1D *vertex_multiplicity = new TH1D("vertex_multiplicity","Generated Vertex Multiplicity;Number of Generated Vertices;N/N_{total}",50,-0.5,49.5);
TH1D *reco_pu = new TH1D("reco_pu","Reconstructed Pile-Up;Reconstructed Pile-Up;N/N_{total}",50,-0.5,49.5);
TH1D *gen_pu = new TH1D("gen_pu","Generated Pile-Up;Generated Pile-Up;N/N_{total}",50,-0.5,49.5);

TH1D *evt_rho = new TH1D("evt_rho","Event Rho",100,0,35.0);

TH1D *gen_ele_multiplicity = new TH1D("gen_ele_multiplicity","Generated Electron Multiplicity;Number of Generated Electrons;N/N_{total}",6,-0.5,5.5);
TH1D *gen_ele_multiplicity_am = new TH1D("gen_ele_multiplicity_am","Generated Electron Multiplicity After Matching;Number of Generated Electrons After Matching;N/N_{total}",6,-0.5,5.5);
TH1D *gen_ele_multiplicity_matched = new TH1D("gen_ele_multiplicity_matched","Generated Electron Multiplicity Matched;Number of Generated Electrons Matched;N/N_{total}",6,-0.5,5.5);
TH1D *gen_ele_multiplicity_separated = new TH1D("gen_ele_multiplicity_separated","Generated Electron Multiplicity Separated;Number of Generated Electrons Separated;N/N_{total}",6,-0.5,5.5);
TH1D *gen_ele_pt = new TH1D("gen_ele_pt","Generated Electron pT;Generated Electron p_{T};N/N_{total}",100,0,200);
TH1D *gen_ele_eta = new TH1D("gen_ele_eta","Generated Electron Eta;Generated Electron #eta;N/N_{total}",50,-6,6);
TH1D *gen_ele_phi = new TH1D("gen_ele_phi","Generated Electron Phi;Generated Electron #phi;N/N_{total}",50,-3.5,3.5);
TH1D *leading_gen_ele_pt = new TH1D("leading_gen_ele_pt","Leading Generated Electron pT;Leading Generated Electron p_{T};N/N_{total}",100,0,200);
TH1D *leading_gen_ele_eta = new TH1D("leading_gen_ele_eta","Leading Generated Electron Eta;Leading Generated Electron #eta;N/N_{total}",50,-6,6);
TH1D *leading_gen_ele_phi = new TH1D("leading_gen_ele_phi","Leading Generated Electron Phi; Leading Generated Electron #phi;N/N_{total}",50,-3.5,3.5);


TH1D *reco_ele_multiplicity = new TH1D("reco_ele_multiplicity","Reconstructed Electron Multiplicity;Number of Reconstructed Electrons;N/N_{total}",6,-0.5,5.5);
TH1D *reco_ele_multiplicity_am = new TH1D("reco_ele_multiplicity_am","Reconstructed Electron Multiplicity After Matching;Number of Reconstructed Electrons After Matching;N/N_{total}",6, -0.5,5.5);
TH1D *reco_ele_multiplicity_matched = new TH1D("reco_ele_multiplicity_matched","Reconstructed Electron Multiplicity Matched;Number of Reconstructed Electrons Matched;N/N_{total}",6,-0.5,5.5);
TH1D *reco_ele_multiplicity_separated = new TH1D("reco_ele_multiplicity_separated","Reconstructed Electron Multiplicity Separated;Number of Reconstructed Electrons Separated;N/N_{total}",6,-0.5,5.5);
TH1D *reco_ele_pt = new TH1D("reco_ele_pt","Reconstructed Electron pT;Reconstructed Electron p_{T};N/N_{total}",100,0,200);
TH1D *reco_ele_eta = new TH1D("reco_ele_eta","Reconstructed Electron Eta;Reconstructed Electron #eta;N/N_{total}",60,-3,3);
TH1D *reco_ele_phi = new TH1D("reco_ele_phi","Reconstructed Electron Phi;Reconstructed Electron #phi;N/N_{total}",50,-3.5,3.5);
TH1D *reco_ele_effarea = new TH1D("reco_ele_effarea","Reconstructed Electron Effective Area;Reconstructed Electron Effective Area;N/N_{total}",50,0.0,0.5);
TH1D *reco_ele_dxy = new TH1D("reco_ele_dxy","Reconstructed Electron dxy;Reconstructed Electron dxy;N/N_{total}",60,0,0.6);
TH1D *reco_ele_dz = new TH1D("reco_ele_dz","Reconstructed Electron dz;Reconstructed Electron dz;N/N_{total}",120,0,1.2);
TH1D *reco_ele_missinghit = new TH1D("reco_ele_missinghit","Reconstructed Electron Missing Hits;Reconstructed Electron Number of Missing Hits;N/N_{total}",3,-0.5,2.5);
TH1D *reco_ele_pfchhadiso = new TH1D("reco_ele_pfchhadiso","PF Charged Hadron Isolated;PF CH Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel = new TH1D("reco_ele_pfchhadisorel","PF Charged Hadron Isolated pT;PF CH Iso/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfchhadiso_barrel = new TH1D("reco_ele_pfchhadiso_barrel","PF Charged Hadron Isolated Barrel;PF CH Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadiso_endcap = new TH1D("reco_ele_pfchhadiso_endcap","PF Charged Hadron Isolated EndCap;PF CH Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadiso = new TH1D("reco_ele_pfnehadiso","PF Neutral Hadron Isolated;PF NH Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel = new TH1D("reco_ele_pfnehadisorel","PF Neutral Hadron Isolated pT;PF NH Iso/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfnehadiso_barrel = new TH1D("reco_ele_pfnehadiso_barrel","PF Neutral Hadron Isolated Barrel;PF NH Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadiso_endcap = new TH1D("reco_ele_pfnehadiso_endcap","PF Neutral Hadron Isolated EndCap;PF NH Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotoniso = new TH1D("reco_ele_pfphotoniso","PF Photon Isolated;PF Photon Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel = new TH1D("reco_ele_pfphotonisorel","PF Photon Isolated pT;PF Photon Iso/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfphotoniso_barrel = new TH1D("reco_ele_pfphotoniso_barrel","PF Photon Isolated Barrel;PF Photon Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotoniso_endcap = new TH1D("reco_ele_pfphotoniso_endcap","PF Photon Isolated EndCap;PF Photon Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompu = new TH1D("reco_ele_pfchargedfrompu","PF Charged Hadrons from PU;PF Charged Hadrons From PU; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel = new TH1D("reco_ele_pfchargedfrompurel","PF Charged Hadrons from PU/p_{T};PF Charged Hadrons From PU/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfchargedfrompu_barrel = new TH1D("reco_ele_pfchargedfrompu_barrel","PF Charged Hadrons from PU Barrel;PF Charged Hadrons From PU Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompu_endcap = new TH1D("reco_ele_pfchargedfrompu_endcap","PF Charged Hadrons from PU EndCap;PF Charged Hadrons From PU EndCap; N/N_{total}",100,0,100.0);

TH1D *reco_ele_pfchhadiso_puppi = new TH1D("reco_ele_pfchhadiso_puppi","PF Charged Hadron Isolated with PUPPI;PF CH Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi = new TH1D("reco_ele_pfchhadisorel_puppi","PF Charged Hadron Isolated Relative with PUPPI;PF CH Iso PUPPI/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfchhadiso_puppi_barrel = new TH1D("reco_ele_pfchhadiso_puppi_barrel","PF Charged Hadron Isolated with PUPPI Barrel;PF CH Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadiso_puppi_endcap = new TH1D("reco_ele_pfchhadiso_puppi_endcap","PF Charged Hadron Isolated with PUPPI EndCap;PF CH Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadiso_puppi = new TH1D("reco_ele_pfnehadiso_puppi","PF Neutral Hadron Isolated with PUPPI;PF NE Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi = new TH1D("reco_ele_pfnehadisorel_puppi","PF Neutral Hadron Isolated Relative with PUPPI;PF NE Iso PUPPI/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfnehadiso_puppi_barrel = new TH1D("reco_ele_pfnehadiso_puppi_barrel","PF Neutral Hadron Isolated with PUPPI Barrel;PF Ne Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadiso_puppi_endcap = new TH1D("reco_ele_pfnehadiso_puppi_endcap","PF Neutral Hadron Isolated with PUPPI EndCap;PF Ne Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotoniso_puppi = new TH1D("reco_ele_pfphotoniso_puppi","PF Photon Isolated with PUPPI;PF Photon Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi = new TH1D("reco_ele_pfphotonisorel_puppi","PF Photon Isolated Relative with PUPPI;PF Photon Iso PUPPI/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfphotoniso_puppi_barrel = new TH1D("reco_ele_pfphotoniso_puppi_barrel","PF Photon Isolated with PUPPI Barrel;PF Photon Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotoniso_puppi_endcap = new TH1D("reco_ele_pfphotoniso_puppi_endcap","PF Photon Isolated with PUPPI EndCap;PF Photon Iso PUPPI EndCap; N/N_{total}",100,0,100.0);

TH1D *reco_ele_pfchhadiso_puppinl = new TH1D("reco_ele_pfchhadiso_puppinl","PF Charged Hadron Isolated with PUPPI No LEptons;PF CH Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl = new TH1D("reco_ele_pfchhadisorel_puppinl","PF Charged Hadron Isolated Relative with PUPPI No Leptons;PF CH Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfchhadiso_puppinl_barrel = new TH1D("reco_ele_pfchhadiso_puppinl_barrel","PF Charged Hadron Isolated with PUPPI No Leptons Barrel;PF CH Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadiso_puppinl_endcap = new TH1D("reco_ele_pfchhadiso_puppinl_endcap","PF Charged Hadron Isolated with PUPPI No Leptons EndCap;PF CH Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadiso_puppinl = new TH1D("reco_ele_pfnehadiso_puppinl","PF Neutral Hadron Isolated with PUPPI No Leptons;PF NE Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl = new TH1D("reco_ele_pfnehadisorel_puppinl","PF Neutral Hadron Isolated Relative with PUPPI No Leptons;PF NE Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfnehadiso_puppinl_barrel = new TH1D("reco_ele_pfnehadiso_puppinl_barrel","PF Neutral Hadron Isolated with PUPPI No Leptons Barrel;PF Ne Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadiso_puppinl_endcap = new TH1D("reco_ele_pfnehadiso_puppinl_endcap","PF Neutral Hadron Isolated with PUPPI No Leptons EndCap;PF Ne Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotoniso_puppinl = new TH1D("reco_ele_pfphotoniso_puppinl","PF Photon Isolated with PUPPI No Leptons;PF Photon Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl = new TH1D("reco_ele_pfphotonisorel_puppinl","PF Photon Isolated Relative with PUPPI No Leptons;PF Photon Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfphotoniso_puppinl_barrel = new TH1D("reco_ele_pfphotoniso_puppinl_barrel","PF Photon Isolated with PUPPI No Leptons Barrel No Leptons;PF Photon Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotoniso_puppinl_endcap = new TH1D("reco_ele_pfphotoniso_puppinl_endcap","PF Photon Isolated with PUPPI No Leptons EndCap;PF Photon Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);

TH1D *reco_ele_pfchhadiso_citk = new TH1D("reco_ele_pfchhadiso_citk","PF Charged Hadron Isolated with CITK;PF CH Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk = new TH1D("reco_ele_pfchhadisorel_citk","PF Charged Hadron Isolated Relative with CITK;PF CH Iso CITK/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfchhadiso_citk_barrel = new TH1D("reco_ele_pfchhadiso_citk_barrel","PF Charged Hadron Isolated with CITK Barrel;PF CH Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadiso_citk_endcap = new TH1D("reco_ele_pfchhadiso_citk_endcap","PF Charged Hadron Isolated with CITK EndCap;PF CH Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadiso_citk = new TH1D("reco_ele_pfnehadiso_citk","PF Neutral Hadron Isolated with CITK;PF NE Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk = new TH1D("reco_ele_pfnehadisorel_citk","PF Neutral Hadron Isolated Relative with CITK;PF NE Iso CITK/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfnehadiso_citk_barrel = new TH1D("reco_ele_pfnehadiso_citk_barrel","PF Neutral Hadron Isolated with CITK Barrel;PF Ne Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadiso_citk_endcap = new TH1D("reco_ele_pfnehadiso_citk_endcap","PF Neutral Hadron Isolated with CITK EndCap;PF Ne Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotoniso_citk = new TH1D("reco_ele_pfphotoniso_citk","PF Photon Isolated with CITK;PF Photon Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk = new TH1D("reco_ele_pfphotonisorel_citk","PF Photon Isolated Relative with CITK;PF Photon Iso CITK/p_{T}; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfphotoniso_citk_barrel = new TH1D("reco_ele_pfphotoniso_citk_barrel","PF Photon Isolated with CITK Barrel;PF Photon Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotoniso_citk_endcap = new TH1D("reco_ele_pfphotoniso_citk_endcap","PF Photon Isolated with CITK EndCap;PF Photon Iso CITK EndCap; N/N_{total}",100,0,100.0);

TH1D *reco_ele_pfiso_simple = new TH1D("reco_ele_pfiso_simple","PF Combined Relation Isolation Simple;PF Iso Simple; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_simple_barrel = new TH1D("reco_ele_pfiso_simple_barrel","PF Combined Relation Isolation Simple Barrel;PF Iso Simple Barrel; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_simple_endcap = new TH1D("reco_ele_pfiso_simple_endcap","PF Combined Relation Isolation Simple EndCap;PF Iso Simple EndCap; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_simple_lowpu = new TH1D("reco_ele_pfiso_simple_lowpu","PF Combined Relation Isolation Simple with Low Pile-Up;;PF Iso Simple Low Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_simple_medpu = new TH1D("reco_ele_pfiso_simple_medpu","PF Combined Relation Isolation Simple with Medium Pile-Up;PF Iso Simple Medium Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_simple_highpu = new TH1D("reco_ele_pfiso_simple_highpu","PF Combined Relation Isolation Simple with High Pile-Up;PF Iso Simple High Pile-Up; N/N_{total}",100,0,2.0);

TH1D *reco_ele_pfiso_effarea = new TH1D("reco_ele_pfiso_effarea","PF Combined Relation Isolation Effective Area;PF Iso Eff Area; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_effarea_barrel = new TH1D("reco_ele_pfiso_effarea_barrel","PF Combined Relation Isolation Effective Area Barrel;PF Iso Eff Area Barrel; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_effarea_endcap = new TH1D("reco_ele_pfiso_effarea_endcap","PF Combined Relation Isolation Effective Area EndCap;PF Iso Eff Area EndCap; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_effarea_lowpu = new TH1D("reco_ele_pfiso_effarea_lowpu","PF Combined Relation Isolation Effective Area with Low Pile-Up;PF Iso Eff Area Low Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_effarea_medpu = new TH1D("reco_ele_pfiso_effarea_medpu","PF Combined Relation Isolation Effective Area with Medium Pile-Up;PF Iso Eff Area Medium Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_effarea_highpu = new TH1D("reco_ele_pfiso_effarea_highpu","PF Combined Relation Isolation Effective Area with High Pile-Up;PF Iso Eff Area High Pile-Up; N/N_{total}",100,0,2.0);

TH1D *reco_ele_pfiso_deltabeta = new TH1D("reco_ele_pfiso_deltabeta","PF Combined Relation Isolation Delta Eta;PF Iso #Delta#beta; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_deltabeta_barrel = new TH1D("reco_ele_pfiso_deltabeta_barrel","PF Combined Relation Isolation Delta Eta Barrel;PF Iso #Delta#beta Barrel; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_deltabeta_endcap = new TH1D("reco_ele_pfiso_deltabeta_endcap","PF Combined Relation Isolation Delta Eta EndCap;PF Iso #Delta#beta EndCap; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_deltabeta_lowpu = new TH1D("reco_ele_pfiso_deltabeta_lowpu","PF Combined Relation Isolation Delta Eta with Low Pile-Up;PF Iso #Delta#beta Low Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_deltabeta_medpu = new TH1D("reco_ele_pfiso_deltabeta_medpu","PF Combined Relation Isolation Delta Eta with Medium Pile-Up;PF Iso #Delta#beta Medium Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_deltabeta_highpu = new TH1D("reco_ele_pfiso_deltabeta_highpu","PF Combined Relation Isolation Delta Eta with High Pile-Up;PF Iso #Delta#beta High Pile-Up; N/N_{total}",100,0,2.0);

TH1D *reco_ele_pfiso_puppi = new TH1D("reco_ele_pfiso_puppi","PF Combined Relation Isolation PUPPI;PF Iso PUPPI; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppi_barrel = new TH1D("reco_ele_pfiso_puppi_barrel","PF Combined Relation Isolation PUPPI Barrel;PF Iso PUPPI Barrel; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppi_endcap = new TH1D("reco_ele_pfiso_puppi_endcap","PF Combined Relation Isolation PUPPI EndCap;PF Iso PUPPI EndCap; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppi_lowpu = new TH1D("reco_ele_pfiso_puppi_lowpu","PF Combined Relation Isolation PUPPI with Low Pile-Up;;PF Iso PUPPI Low Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppi_medpu = new TH1D("reco_ele_pfiso_puppi_medpu","PF Combined Relation Isolation PUPPI with Medium Pile-Up;PF Iso PUPPI Medium Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppi_highpu = new TH1D("reco_ele_pfiso_puppi_highpu","PF Combined Relation Isolation PUPPI with High Pile-Up;PF Iso PUPPI High Pile-Up; N/N_{total}",100,0,2.0);

TH1D *reco_ele_pfiso_puppinl = new TH1D("reco_ele_pfiso_puppinl","PF Combined Relation Isolation PUPPI No Leptons;PF Iso PUPPI No Leptons; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppinl_barrel = new TH1D("reco_ele_pfiso_puppinl_barrel","PF Combined Relation Isolation PUPPI No Leptons Barrel;PF Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppinl_endcap = new TH1D("reco_ele_pfiso_puppinl_endcap","PF Combined Relation Isolation PUPPI No Leptons EndCap;PF Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppinl_lowpu = new TH1D("reco_ele_pfiso_puppinl_lowpu","PF Combined Relation Isolation PUPPI No Leptons with Low Pile-Up;;PF Iso PUPPI No Leptons Low Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppinl_medpu = new TH1D("reco_ele_pfiso_puppinl_medpu","PF Combined Relation Isolation PUPPI No Leptons with Medium Pile-Up;PF Iso PUPPI Medium No Leptons Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_puppinl_highpu = new TH1D("reco_ele_pfiso_puppinl_highpu","PF Combined Relation Isolation PUPPI No Leptons with High Pile-Up;PF Iso PUPPI No Leptons High Pile-Up; N/N_{total}",100,0,2.0);

TH1D *reco_ele_pfiso_citk = new TH1D("reco_ele_pfiso_citk","PF Combined Relation Isolation CITK;PF Iso CITK; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_citk_barrel = new TH1D("reco_ele_pfiso_citk_barrel","PF Combined Relation Isolation CITK Barrel;PF Iso CITK Barrel; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_citk_endcap = new TH1D("reco_ele_pfiso_citk_endcap","PF Combined Relation Isolation CITK EndCap;PF Iso CITK EndCap; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_citk_lowpu = new TH1D("reco_ele_pfiso_citk_lowpu","PF Combined Relation Isolation CITK with Low Pile-Up;;PF Iso CITK Low Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_citk_medpu = new TH1D("reco_ele_pfiso_citk_medpu","PF Combined Relation Isolation CITK with Medium Pile-Up;PF Iso CITK Medium Pile-Up; N/N_{total}",100,0,2.0);
TH1D *reco_ele_pfiso_citk_highpu = new TH1D("reco_ele_pfiso_citk_highpu","PF Combined Relation Isolation CITK with High Pile-Up;PF Iso CITK High Pile-Up; N/N_{total}",100,0,2.0);

TH1D *reco_ele_bdt = new TH1D("reco_ele_bdt","Electron BDT",100,-1.0,1.0);
TH1D *reco_ele_bdt_barrel = new TH1D("reco_ele_bdt_barrel","Electron BDT Barrel",100,-1.0,1.0);
TH1D *reco_ele_bdt_endcap = new TH1D("reco_ele_bdt_endcap","Electron BDT EndCap",100,-1.0,1.0);
TH1D *reco_ele_sip = new TH1D("reco_ele_sip","Electron SIP",100,0,25.0);
TH1D *reco_ele_sip_barrel = new TH1D("reco_ele_sip_barrel","Electron SIP Barrel",100,0,25.0);
TH1D *reco_ele_sip_endcap = new TH1D("reco_ele_sip_endcap","Electron SIP Endcap",100,0,25.0);
TH1D *reco_ele_id = new TH1D("reco_ele_id","Electron ID",2,-0.5,1.5);
TH1D *reco_ele_isgood = new TH1D("reco_ele_isgood","Electron is Good",2,-0.5,1.5);
TH1D *leading_reco_ele_pt = new TH1D("leading_reco_ele_pt","Leading Reconstructed Electron pT",40,0,200);
TH1D *leading_reco_ele_eta = new TH1D("leading_reco_ele_eta","Leading Reconstructed Electron Eta",22,-5.5,5.5);
TH1D *leading_reco_ele_phi = new TH1D("leading_reco_ele_phi","Leading Reconstructed Electron Phi",20,-3.15,3.15);

TH2D *iso_simple_vs_pt = new TH2D("iso_simple_vs_pt","PFIso Simple Versus pT",100,0,1.0,pt_nbins,pt_bins);
TH2D *iso_simple_vs_vtx = new TH2D("iso_simple_vs_vtx","PFIso Simple Versus Number of Vertices",100,0,1.0,vtx_nbins,vtx_bins);
TH2D *iso_simple_vs_eta = new TH2D("iso_simple_vs_eta","PFIso Simple Versus Eta",100,0,1.0,25,-2.5,2.5);

TH2D *iso_effarea_vs_pt = new TH2D("iso_effarea_vs_pt","PFIso Effective Area Versus pT",100,0,1.0,pt_nbins,pt_bins);
TH2D *iso_effarea_vs_vtx = new TH2D("iso_effarea_vs_vtx","PFIso Effective Area Versus Number of Vertices",100,0,1.0,vtx_nbins,vtx_bins);
TH2D *iso_effarea_vs_eta = new TH2D("iso_effarea_vs_eta","PFIso Effective Area Versus Eta",100,0,1.0,25,-2.5,2.5);

TH2D *iso_deltabeta_vs_pt = new TH2D("iso_deltabeta_vs_pt","PFIso Delta Beta Versus pT",100,0,1.0,pt_nbins,pt_bins);
TH2D *iso_deltabeta_vs_vtx = new TH2D("iso_deltabeta_vs_vtx","PFIso Delta Beta Versus Number of Vertices",100,0,1.0,vtx_nbins,vtx_bins);
TH2D *iso_deltabeta_vs_eta = new TH2D("iso_deltabeta_vs_eta","PFIso Delta Beta Versus Eta",100,0,1.0,25,-2.5,2.5);

TH2D *iso_puppi_vs_pt = new TH2D("iso_puppi_vs_pt","PFIso PUPPI Versus pT",100,0,1.0,pt_nbins,pt_bins);
TH2D *iso_puppi_vs_vtx = new TH2D("iso_puppi_vs_vtx","PFIso PUPPI Versus Number of Vertices",100,0,1.0,vtx_nbins,vtx_bins);
TH2D *iso_puppi_vs_eta = new TH2D("iso_puppi_vs_eta","PFIso PUPPI Versus Eta",100,0,1.0,25,-2.5,2.5);

TH2D *iso_puppinl_vs_pt = new TH2D("iso_puppinl_vs_pt","PFIso PUPPI Versus pT",100,0,1.0,pt_nbins,pt_bins);
TH2D *iso_puppinl_vs_vtx = new TH2D("iso_puppinl_vs_vtx","PFIso PUPPI Versus Number of Vertices",100,0,1.0,vtx_nbins,vtx_bins);
TH2D *iso_puppinl_vs_eta = new TH2D("iso_puppinl_vs_eta","PFIso PUPPI Versus Eta",100,0,1.0,25,-2.5,2.5);

TH2D *iso_citk_vs_pt = new TH2D("iso_citk_vs_pt","PFIso CITK Versus pT",100,0,1.0,pt_nbins,pt_bins);
TH2D *iso_citk_vs_vtx = new TH2D("iso_citk_vs_vtx","PFIso CITK Versus Number of Vertices",100,0,1.0,vtx_nbins,vtx_bins);
TH2D *iso_citk_vs_eta = new TH2D("iso_citk_vs_eta","PFIso CITK Versus Eta",100,0,1.0,25,-2.5,2.5);

TH1D *ele_pfiso_simple_pt_eff = new TH1D("ele_pfiso_simple_pt_eff","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_eff = new TH1D("ele_pfiso_effarea_pt_eff","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_eff = new TH1D("ele_pfiso_deltabeta_pt_eff","PFIso Simple pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_eff = new TH1D("ele_pfiso_puppi_pt_eff","PFIso PUPPI pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_eff = new TH1D("ele_pfiso_puppinl_pt_eff","PFIso PUPPI No Leptons pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_eff = new TH1D("ele_pfiso_citk_pt_eff","PFIso CITK pT;p_{T};Signal Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_bkg = new TH1D("ele_pfiso_simple_pt_bkg","PFIso Simple pT;p_{T};Backgroung Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_bkg = new TH1D("ele_pfiso_effarea_pt_bkg","PFIso Simple pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_bkg = new TH1D("ele_pfiso_deltabeta_pt_bkg","PFIso Simple pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_bkg = new TH1D("ele_pfiso_puppi_pt_bkg","PFIso PUPPI pT;p_{T};Backgroung Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_bkg = new TH1D("ele_pfiso_puppinl_pt_bkg","PFIso PUPPI No Leptons pT;p_{T};Background Efficiency",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_bkg = new TH1D("ele_pfiso_citk_pt_bkg","PFIso CITK pT;p_{T};Background Efficiency",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_pt_ratio = new TH1D("ele_pfiso_simple_pt_ratio","PFIso Simple pT;p_{T};Signal/Backgroung",pt_nbins,pt_bins);
TH1D *ele_pfiso_effarea_pt_ratio = new TH1D("ele_pfiso_effarea_pt_ratio","PFIso Simple pT;p_{T};Signal/Background",pt_nbins,pt_bins);
TH1D *ele_pfiso_deltabeta_pt_ratio = new TH1D("ele_pfiso_deltabeta_pt_ratio","PFIso Simple pT;p_{T};Signal/Background",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppi_pt_ratio = new TH1D("ele_pfiso_puppi_pt_ratio","PFIso PUPPI pT;p_{T};Signal/Backgroung",pt_nbins,pt_bins);
TH1D *ele_pfiso_puppinl_pt_ratio = new TH1D("ele_pfiso_puppinl_pt_ratio","PFIso PUPPI No Leptons pT;p_{T};Signal/Background",pt_nbins,pt_bins);
TH1D *ele_pfiso_citk_pt_ratio = new TH1D("ele_pfiso_citk_pt_ratio","PFIso CITK pT;p_{T};Signal/Background",pt_nbins,pt_bins);

TH1D *ele_pfiso_simple_vtx_eff = new TH1D("ele_pfiso_simple_vtx_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_eff = new TH1D("ele_pfiso_effarea_vtx_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_eff = new TH1D("ele_pfiso_deltabeta_vtx_eff","PFIso Simple Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_eff = new TH1D("ele_pfiso_puppi_vtx_eff","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_eff = new TH1D("ele_pfiso_puppinl_vtx_eff","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_eff = new TH1D("ele_pfiso_citk_vtx_eff","PFIso Simple CITK of Generated Vertices;Number of Vertices;Signal Efficiency",vtx_nbins,vtx_bins);

TH1D *ele_pfiso_simple_vtx_bkg = new TH1D("ele_pfiso_simple_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_effarea_vtx_bkg = new TH1D("ele_pfiso_effarea_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_deltabeta_vtx_bkg = new TH1D("ele_pfiso_deltabeta_vtx_bkg","PFIso Simple Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppi_vtx_bkg = new TH1D("ele_pfiso_puppi_vtx_bkg","PFIso PUPPI Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_puppinl_vtx_bkg = new TH1D("ele_pfiso_puppinl_vtx_bkg","PFIso PUPPI No Leptons Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);
TH1D *ele_pfiso_citk_vtx_bkg = new TH1D("ele_pfiso_citk_vtx_bkg","PFIso CITK Number of Generated Vertices;Number of Vertices;Background Efficiency",vtx_nbins,vtx_bins);

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

  Int_t nEvent;
  Int_t nRun;
  Int_t nLumi;

  Int_t nPV;
  Int_t nPU;
  Int_t nPUTrue;
  Float_t rho;

  //generated muons
  Int_t gmn;

  //generated electrons
  Int_t gen;
  Float_t geeta[100];
  Float_t gept [100];
  Float_t gephi[100];

  //reco electrons  
  Int_t nele;
  Float_t ele_pt[100];
  Float_t ele_eta[100];
  Float_t ele_sclEta[100];
  Float_t ele_phi[100];
  Float_t ele_effarea[100];
  Float_t ele_PFChargedHadIso[100];
  Float_t ele_PFNeutralHadIso[100];
  Float_t ele_PFPhotonIso[100];
  Float_t ele_PFChargedFromPU[100];
  Float_t ele_PFChargedHadIsoRel[100];
  Float_t ele_PFNeutralHadIsoRel[100];
  Float_t ele_PFPhotonIsoRel[100];
  Float_t ele_PFChargedFromPURel[100];
  Float_t ele_PFChargedHadIso_PUPPI[100];
  Float_t ele_PFChargedHadIsoRel_PUPPI[100];
  Float_t ele_PFNeutralHadIso_PUPPI[100];
  Float_t ele_PFNeutralHadIsoRel_PUPPI[100];
  Float_t ele_PFPhotonIso_PUPPI[100];
  Float_t ele_PFPhotonIsoRel_PUPPI[100];
  Float_t ele_PFChargedHadIso_PUPPINL[100];
  Float_t ele_PFChargedHadIsoRel_PUPPINL[100];
  Float_t ele_PFNeutralHadIso_PUPPINL[100];
  Float_t ele_PFNeutralHadIsoRel_PUPPINL[100];
  Float_t ele_PFPhotonIso_PUPPINL[100];
  Float_t ele_PFPhotonIsoRel_PUPPINL[100];
  Float_t ele_PFChargedHadIso_CITK[100];
  Float_t ele_PFChargedHadIsoRel_CITK[100];
  Float_t ele_PFNeutralHadIso_CITK[100];
  Float_t ele_PFNeutralHadIsoRel_CITK[100];
  Float_t ele_PFPhotonIso_CITK[100];
  Float_t ele_PFPhotonIsoRel_CITK[100];
  Float_t ele_PFIso_simple[100];
  Float_t ele_PFIso_effarea[100];
  Float_t ele_PFIso_deltabeta[100];
  Float_t ele_PFIso_PUPPI[100];
  Float_t ele_PFIso_PUPPINL[100];
  Float_t ele_PFIso_CITK[100];
  Float_t ele_SIP[100];
  Float_t ele_dxy[100];
  Float_t ele_dz[100];
  Float_t ele_BDT[100];
  Float_t ele_isBDT[100];
  Float_t ele_missingHit[100];
  Float_t ele_ID[100];
  Float_t ele_isGood[100];

    TChain* chain[2];

   double max_gen_pt, max_reco_pt, radius;
   int id_leading_gen, id_leading_reco;
   int ele_matched, ele_separated, ele_matched_event, ele_separated_event;
   bool use_electrons, matched, separated;
   bool disp_ini_info;
   int selected_electrons[samples];

   double isolation_simple[samples][100], isolation_simple_barrel[samples][100];
   double isolation_simple_endcap[samples][100];
   double isolation_simple_lowpu[samples][100], isolation_simple_medpu[samples][100];
   double isolation_simple_highpu[samples][100];

   double isolation_effarea[samples][100], isolation_effarea_barrel[samples][100];
   double isolation_effarea_endcap[samples][100];
   double isolation_effarea_lowpu[samples][100], isolation_effarea_medpu[samples][100];
   double isolation_effarea_highpu[samples][100];

   double isolation_deltabeta[samples][100], isolation_deltabeta_barrel[samples][100];
   double isolation_deltabeta_endcap[samples][100]; 
   double isolation_deltabeta_lowpu[samples][100], isolation_deltabeta_medpu[samples][100];
   double isolation_deltabeta_highpu[samples][100];

   double isolation_puppi[samples][100], isolation_puppi_barrel[samples][100];
   double isolation_puppi_endcap[samples][100];
   double isolation_puppi_lowpu[samples][100], isolation_puppi_medpu[samples][100];
   double isolation_puppi_highpu[samples][100];

   double isolation_puppinl[samples][100], isolation_puppinl_barrel[samples][100];
   double isolation_puppinl_endcap[samples][100];
   double isolation_puppinl_lowpu[samples][100], isolation_puppinl_medpu[samples][100];
   double isolation_puppinl_highpu[samples][100];

   double isolation_citk[samples][100], isolation_citk_barrel[samples][100];
   double isolation_citk_endcap[samples][100]; 
   double isolation_citk_lowpu[samples][100], isolation_citk_medpu[samples][100];
   double isolation_citk_highpu[samples][100];

   double sip[samples][100], sip_barrel[samples][100], sip_endcap[samples][100];
   double bdt[samples][100], bdt_barrel[samples][100], bdt_endcap[samples][100];
   
   //double integral_simple_pt[20], integral_simple_vtx[50], integral_simple_eta[25];
   //double integral_effarea_pt[20], integral_effarea_vtx[50], integral_effarea_eta[25];
   //double integral_deltabeta_pt[20], integral_deltabeta_vtx[50], integral_deltabeta_eta[25];
   
   double isolation_simple_pt[samples][10], isolation_simple_vtx[samples][22], isolation_simple_eta[samples][25];
   double isolation_effarea_pt[samples][10], isolation_effarea_vtx[samples][22], isolation_effarea_eta[samples][25];
   double isolation_deltabeta_pt[samples][10], isolation_deltabeta_vtx[samples][22], isolation_deltabeta_eta[samples][25];
   double isolation_puppi_pt[samples][10], isolation_puppi_vtx[samples][22], isolation_puppi_eta[samples][25];
   double isolation_puppinl_pt[samples][10], isolation_puppinl_vtx[samples][22], isolation_puppinl_eta[samples][25];
   double isolation_citk_pt[samples][10], isolation_citk_vtx[samples][22], isolation_citk_eta[samples][25];

    for (int s=0; s<samples; ++s) {

    chain[s] = new TChain("tree");
    chain[s]->Add(sample[s].c_str());

    cout << "Reading " << sample[s] << "..." << endl;

    chain[s]->SetBranchAddress("nEvent", &nEvent);
    chain[s]->SetBranchAddress("nRun", &nRun);
    chain[s]->SetBranchAddress("nLumi", &nLumi);

    chain[s]->SetBranchAddress("nPV", &nPV);
    chain[s]->SetBranchAddress("nPU", &nPU);
    chain[s]->SetBranchAddress("nPUTrue", &nPUTrue);
    chain[s]->SetBranchAddress("rho", &rho);

    chain[s]->SetBranchAddress("gen", &gen);
    chain[s]->SetBranchAddress("gept", &gept);
    chain[s]->SetBranchAddress("geeta", &geeta);
    chain[s]->SetBranchAddress("gephi", &gephi);
    chain[s]->SetBranchAddress("gmn", &gmn);
    chain[s]->SetBranchAddress("nele", &nele);
    chain[s]->SetBranchAddress("ele_pt", &ele_pt);
    chain[s]->SetBranchAddress("ele_eta", &ele_eta);
    chain[s]->SetBranchAddress("ele_sclEta", &ele_sclEta);
    chain[s]->SetBranchAddress("ele_phi", &ele_phi);
    chain[s]->SetBranchAddress("ele_effective_area", &ele_effarea);
    chain[s]->SetBranchAddress("ele_PFChargedHadIso", &ele_PFChargedHadIso);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIso", &ele_PFNeutralHadIso);
    chain[s]->SetBranchAddress("ele_PFPhotonIso", &ele_PFPhotonIso);
    chain[s]->SetBranchAddress("ele_PFChargedFromPU", &ele_PFChargedFromPU);
    chain[s]->SetBranchAddress("ele_PFChargedHadIsoRel", &ele_PFChargedHadIsoRel);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIsoRel", &ele_PFNeutralHadIsoRel);
    chain[s]->SetBranchAddress("ele_PFPhotonIsoRel", &ele_PFPhotonIsoRel);
    chain[s]->SetBranchAddress("ele_PFChargedFromPURel", &ele_PFChargedFromPURel);
    chain[s]->SetBranchAddress("ele_PFChargedHadIso_PUPPI", &ele_PFChargedHadIso_PUPPI);
    chain[s]->SetBranchAddress("ele_PFChargedHadIsoRel_PUPPI", &ele_PFChargedHadIsoRel_PUPPI);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIso_PUPPI", &ele_PFNeutralHadIso_PUPPI);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIsoRel_PUPPI", &ele_PFNeutralHadIsoRel_PUPPI);
    chain[s]->SetBranchAddress("ele_PFPhotonIso_PUPPI", &ele_PFPhotonIso_PUPPI);
    chain[s]->SetBranchAddress("ele_PFPhotonIsoRel_PUPPI", &ele_PFPhotonIsoRel_PUPPI);
    chain[s]->SetBranchAddress("ele_PFChargedHadIso_PUPPI_NoLeptons", &ele_PFChargedHadIso_PUPPINL);
    chain[s]->SetBranchAddress("ele_PFChargedHadIsoRel_PUPPI_NoLeptons", &ele_PFChargedHadIsoRel_PUPPINL);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIso_PUPPI_NoLeptons", &ele_PFNeutralHadIso_PUPPINL);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIsoRel_PUPPI_NoLeptons", &ele_PFNeutralHadIsoRel_PUPPINL);
    chain[s]->SetBranchAddress("ele_PFPhotonIso_PUPPI_NoLeptons", &ele_PFPhotonIso_PUPPINL);
    chain[s]->SetBranchAddress("ele_PFPhotonIsoRel_PUPPI_NoLeptons", &ele_PFPhotonIsoRel_PUPPINL);
    chain[s]->SetBranchAddress("ele_PFChargedHadIso_CITK", &ele_PFChargedHadIso_CITK);
    chain[s]->SetBranchAddress("ele_PFChargedHadIsoRel_CITK", &ele_PFChargedHadIsoRel_CITK);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIso_CITK", &ele_PFNeutralHadIso_CITK);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIsoRel_CITK", &ele_PFNeutralHadIsoRel_CITK);
    chain[s]->SetBranchAddress("ele_PFPhotonIso_CITK", &ele_PFPhotonIso_CITK);
    chain[s]->SetBranchAddress("ele_PFPhotonIsoRel_CITK", &ele_PFPhotonIsoRel_CITK);

    chain[s]->SetBranchAddress("ele_PFIso_simple", &ele_PFIso_simple);
    chain[s]->SetBranchAddress("ele_PFIso_effarea", &ele_PFIso_effarea);
    chain[s]->SetBranchAddress("ele_PFIso_deltabeta", &ele_PFIso_deltabeta);
    chain[s]->SetBranchAddress("ele_PFIso_PUPPI", &ele_PFIso_PUPPI);
    chain[s]->SetBranchAddress("ele_PFIso_PUPPINoLeptons", &ele_PFIso_PUPPINL);
    chain[s]->SetBranchAddress("ele_PFIso_CITK", &ele_PFIso_CITK);

    chain[s]->SetBranchAddress("ele_SIP", &ele_SIP);
    chain[s]->SetBranchAddress("ele_dxy", &ele_dxy);
    chain[s]->SetBranchAddress("ele_dz", &ele_dz);
    chain[s]->SetBranchAddress("ele_BDT", &ele_BDT);
    chain[s]->SetBranchAddress("ele_isBDT", &ele_isBDT);
    chain[s]->SetBranchAddress("ele_missingHit", &ele_missingHit);
    chain[s]->SetBranchAddress("ele_ID", &ele_ID);
    chain[s]->SetBranchAddress("ele_isGood", &ele_isGood);

   //Reset Histograms
   vertex_multiplicity->Reset();
   reco_pu->Reset();
   gen_pu->Reset();
   evt_rho->Reset();

   gen_ele_multiplicity->Reset();
   gen_ele_pt->Reset();
   gen_ele_eta->Reset();
   gen_ele_phi->Reset();
   leading_gen_ele_pt->Reset();
   leading_gen_ele_eta->Reset();
   leading_gen_ele_phi->Reset();

   reco_ele_multiplicity->Reset();
   reco_ele_pt->Reset();
   reco_ele_eta->Reset();
   reco_ele_phi->Reset();
   reco_ele_effarea->Reset();
   reco_ele_dxy->Reset();
   reco_ele_dz->Reset();
   reco_ele_missinghit->Reset();
   reco_ele_pfchhadiso->Reset();
   reco_ele_pfchhadisorel->Reset();
   reco_ele_pfchhadiso_barrel->Reset();
   reco_ele_pfchhadiso_endcap->Reset();
   reco_ele_pfnehadisorel->Reset();
   reco_ele_pfnehadiso->Reset();
   reco_ele_pfnehadiso_barrel->Reset();
   reco_ele_pfnehadiso_endcap->Reset();
   reco_ele_pfphotoniso->Reset();
   reco_ele_pfphotonisorel->Reset();
   reco_ele_pfphotoniso_barrel->Reset();
   reco_ele_pfphotoniso_endcap->Reset();
   reco_ele_pfchargedfrompu->Reset();
   reco_ele_pfchargedfrompurel->Reset();
   reco_ele_pfchargedfrompu_barrel->Reset();
   reco_ele_pfchargedfrompu_endcap->Reset();

   reco_ele_pfchhadiso_puppi->Reset();
   reco_ele_pfchhadisorel_puppi->Reset();
   reco_ele_pfchhadiso_puppi_barrel->Reset();
   reco_ele_pfchhadiso_puppi_endcap->Reset();
   reco_ele_pfnehadiso_puppi->Reset();
   reco_ele_pfnehadisorel_puppi->Reset();
   reco_ele_pfnehadiso_puppi_barrel->Reset();
   reco_ele_pfnehadiso_puppi_endcap->Reset();
   reco_ele_pfphotoniso_puppi->Reset();
   reco_ele_pfphotonisorel_puppi->Reset();
   reco_ele_pfphotoniso_puppi_barrel->Reset();
   reco_ele_pfphotoniso_puppi_endcap->Reset();

   reco_ele_pfchhadiso_puppinl->Reset();
   reco_ele_pfchhadisorel_puppinl->Reset();
   reco_ele_pfchhadiso_puppinl_barrel->Reset();
   reco_ele_pfchhadiso_puppinl_endcap->Reset();
   reco_ele_pfnehadiso_puppinl->Reset();
   reco_ele_pfnehadisorel_puppinl->Reset();
   reco_ele_pfnehadiso_puppinl_barrel->Reset();
   reco_ele_pfnehadiso_puppinl_endcap->Reset();
   reco_ele_pfphotoniso_puppinl->Reset();
   reco_ele_pfphotonisorel_puppinl->Reset();
   reco_ele_pfphotoniso_puppinl_barrel->Reset();
   reco_ele_pfphotoniso_puppinl_endcap->Reset();

   reco_ele_pfchhadiso_citk->Reset();
   reco_ele_pfchhadisorel_citk->Reset();
   reco_ele_pfchhadiso_citk_barrel->Reset();
   reco_ele_pfchhadiso_citk_endcap->Reset();
   reco_ele_pfnehadiso_citk->Reset();
   reco_ele_pfnehadisorel_citk->Reset();
   reco_ele_pfnehadiso_citk_barrel->Reset();
   reco_ele_pfnehadiso_citk_endcap->Reset();
   reco_ele_pfphotoniso_citk->Reset();
   reco_ele_pfphotonisorel_citk->Reset();
   reco_ele_pfphotoniso_citk_barrel->Reset();
   reco_ele_pfphotoniso_citk_endcap->Reset();

   reco_ele_pfiso_simple->Reset();
   reco_ele_pfiso_simple_barrel->Reset();
   reco_ele_pfiso_simple_endcap->Reset();
   reco_ele_pfiso_simple_lowpu->Reset();
   reco_ele_pfiso_simple_medpu->Reset();
   reco_ele_pfiso_simple_highpu->Reset();

   reco_ele_pfiso_effarea->Reset();
   reco_ele_pfiso_effarea_barrel->Reset();
   reco_ele_pfiso_effarea_endcap->Reset();
   reco_ele_pfiso_effarea_lowpu->Reset();
   reco_ele_pfiso_effarea_medpu->Reset();
   reco_ele_pfiso_effarea_highpu->Reset();

   reco_ele_pfiso_deltabeta->Reset();
   reco_ele_pfiso_deltabeta_barrel->Reset();
   reco_ele_pfiso_deltabeta_endcap->Reset();
   reco_ele_pfiso_deltabeta_lowpu->Reset();
   reco_ele_pfiso_deltabeta_medpu->Reset();
   reco_ele_pfiso_deltabeta_highpu->Reset();

   reco_ele_pfiso_puppi->Reset();
   reco_ele_pfiso_puppi_barrel->Reset();
   reco_ele_pfiso_puppi_endcap->Reset();
   reco_ele_pfiso_puppi_lowpu->Reset();
   reco_ele_pfiso_puppi_medpu->Reset();
   reco_ele_pfiso_puppi_highpu->Reset();

   reco_ele_pfiso_puppinl->Reset();
   reco_ele_pfiso_puppinl_barrel->Reset();
   reco_ele_pfiso_puppinl_endcap->Reset();
   reco_ele_pfiso_puppinl_lowpu->Reset();
   reco_ele_pfiso_puppinl_medpu->Reset();
   reco_ele_pfiso_puppinl_highpu->Reset();

   reco_ele_pfiso_citk->Reset();
   reco_ele_pfiso_citk_barrel->Reset();
   reco_ele_pfiso_citk_endcap->Reset();
   reco_ele_pfiso_citk_lowpu->Reset();
   reco_ele_pfiso_citk_medpu->Reset();
   reco_ele_pfiso_citk_highpu->Reset();

   reco_ele_bdt->Reset();
   reco_ele_bdt_barrel->Reset();
   reco_ele_bdt_endcap->Reset();
   reco_ele_sip->Reset();
   reco_ele_sip_barrel->Reset();
   reco_ele_sip_endcap->Reset();
   reco_ele_id->Reset();
   reco_ele_isgood->Reset();
   leading_reco_ele_pt->Reset();
   leading_reco_ele_eta->Reset();
   leading_reco_ele_phi->Reset();
   
   iso_simple_vs_pt->Reset();
   iso_simple_vs_vtx->Reset();
   iso_simple_vs_eta->Reset();
   
   iso_effarea_vs_pt->Reset();
   iso_effarea_vs_vtx->Reset();
   iso_effarea_vs_eta->Reset();
   
   iso_deltabeta_vs_pt->Reset();
   iso_deltabeta_vs_vtx->Reset();
   iso_deltabeta_vs_eta->Reset();

   iso_puppi_vs_pt->Reset();
   iso_puppi_vs_vtx->Reset();
   iso_puppi_vs_eta->Reset();
   
   iso_puppinl_vs_pt->Reset();
   iso_puppinl_vs_vtx->Reset();
   iso_puppinl_vs_eta->Reset();
   
   iso_citk_vs_pt->Reset();
   iso_citk_vs_vtx->Reset();
   iso_citk_vs_eta->Reset();

   selected_electrons[s] = 0;
   for (int y=0; y<100; ++y)
	{
	isolation_simple[s][y] = 0;
	isolation_simple_barrel[s][y] = 0;
	isolation_simple_endcap[s][y] = 0;
	isolation_simple_lowpu[s][y] = 0;
	isolation_simple_medpu[s][y] = 0;
	isolation_simple_highpu[s][y] = 0;

	isolation_effarea[s][y] = 0;
	isolation_effarea_barrel[s][y] = 0;
	isolation_effarea_endcap[s][y] = 0;
	isolation_effarea_lowpu[s][y] = 0;
	isolation_effarea_medpu[s][y] = 0;
	isolation_effarea_highpu[s][y] = 0;

	isolation_deltabeta[s][y] = 0;
	isolation_deltabeta_barrel[s][y] = 0;
	isolation_deltabeta_endcap[s][y] = 0;
	isolation_deltabeta_lowpu[s][y] = 0;
	isolation_deltabeta_medpu[s][y] = 0;
	isolation_deltabeta_highpu[s][y] = 0;

	isolation_puppi[s][y] = 0;
	isolation_puppi_barrel[s][y] = 0;
	isolation_puppi_endcap[s][y] = 0;
	isolation_puppi_lowpu[s][y] = 0;
	isolation_puppi_medpu[s][y] = 0;
	isolation_puppi_highpu[s][y] = 0;

	isolation_puppinl[s][y] = 0;
	isolation_puppinl_barrel[s][y] = 0;
	isolation_puppinl_endcap[s][y] = 0;
	isolation_puppinl_lowpu[s][y] = 0;
	isolation_puppinl_medpu[s][y] = 0;
	isolation_puppinl_highpu[s][y] = 0;

	isolation_citk[s][y] = 0;
	isolation_citk_barrel[s][y] = 0;
	isolation_citk_endcap[s][y] = 0;
	isolation_citk_lowpu[s][y] = 0;
	isolation_citk_medpu[s][y] = 0;
	isolation_citk_highpu[s][y] = 0;

	sip[s][y] = 0;
	sip_barrel[s][y] = 0;
	sip_endcap[s][y] = 0;
	bdt[s][y] = 0;
	bdt_barrel[s][y] = 0;
	bdt_endcap[s][y] = 0;
	}
	
   for (int y=0; y<10; ++y)
	{
	isolation_simple_pt[s][y] = 0;
	isolation_effarea_pt[s][y] = 0;
	isolation_deltabeta_pt[s][y] = 0;
	isolation_puppi_pt[s][y] = 0;
	isolation_puppinl_pt[s][y] = 0;
	isolation_citk_pt[s][y] = 0;
	}
	
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

    Int_t entries = chain[s]->GetEntries();
    if (test) { entries = 100; }
    cout << "Total Events: " << entries << endl;

    for (int z=0; z<entries; ++z)
	{

	max_gen_pt = 0.0;
	id_leading_gen = -1;
	max_reco_pt = 0.0;
	id_leading_reco = -1;
	ele_matched = 0;
	ele_separated = 0;
	ele_matched_event = 0;
	ele_separated_event = 0;
        radius = 0;
	use_electrons = false;
	matched = false;
	separated = true;
	disp_ini_info = false;

	chain[s]->GetEntry(z);
	if (detail or test) { cout << "z = " << z << " of " << entries << endl; }
	if (detail or test) { cout << "Event Number = " << nEvent << endl; }
	if (detail or test) { cout << "Run Number = " << nRun << endl; }
	if (detail or test) { cout << "Lumi Block = " << nLumi << endl; }
	if (detail) { cout << "Number of Generated Vertexes = " << nPV << endl; }
	if (detail) { cout << "Electron Rho = " << rho << endl; }
	vertex_multiplicity->Fill(nPV);
	reco_pu->Fill(nPU);
	gen_pu->Fill(nPUTrue);
	evt_rho->Fill(rho);
	gen_ele_multiplicity->Fill(gen);
	reco_ele_multiplicity->Fill(nele);
	if (detail) { cout << "Generated Electrons = " << gen << endl; }
	if (detail) { cout << "Generated Muons = " << gmn << endl; }

	if (signal[s]) { if ((gen==4&&gmn==0) || (gen==2&&gmn==2)) {use_electrons = true; }}
	if (!signal[s]) { if (gen==2) { use_electrons = true; }}

	if (use_electrons)
	{
	for(int iGen=0; iGen<gen; iGen++)
		{ if (detail) { cout << "#" << iGen << " pt = " << gept[iGen] << " eta = " << geeta[iGen] << " phi = " << gephi[iGen] << endl; }
		if (gept[iGen] > max_gen_pt) { max_gen_pt = gept[iGen]; id_leading_gen = iGen; }
		gen_ele_pt->Fill(gept[iGen]);
		gen_ele_eta->Fill(geeta[iGen]);
		gen_ele_phi->Fill(gephi[iGen]);
		}

	if (detail) { cout << "Reconstructed Electrons = " << nele << endl; }
	for(int iReco=0; iReco<nele; iReco++)
		{
		matched = false;
		separated = true;
		if (detail) { cout << "#" << iReco << " pt = " << ele_pt[iReco] << " eta = " << ele_sclEta[iReco] << " phi = " << ele_phi[iReco] << endl;
                //cout << " dxy = " << ele_dxy[iReco] << " dz = " << ele_dz[iReco] << " missing hits = " << ele_missingHit[iReco] << endl;
		cout << " Effective Area = " << ele_effarea[iReco] << endl;
		cout << " PF charged hadron isolation = " << ele_PFChargedHadIso[iReco] << endl;
		cout << " PF neutral hadron isolation = " << ele_PFNeutralHadIso[iReco] << endl;
		cout << " PF photon isolation = " << ele_PFPhotonIso[iReco] << endl;
		cout << " PF charged hadron isolation with PUPPI = " << ele_PFChargedHadIso_PUPPI[iReco] << endl;
		cout << " PF neutral hadron isolation with PUPPI = " << ele_PFNeutralHadIso_PUPPI[iReco] << endl;
		cout << " PF photon isolation with PUPPI = " << ele_PFPhotonIso_PUPPI[iReco] << endl;
		cout << " PF charged hadron isolation with PUPPI No Leptons = " << ele_PFChargedHadIso_PUPPINL[iReco] << endl;
		cout << " PF neutral hadron isolation with PUPPI No Leptons = " << ele_PFNeutralHadIso_PUPPINL[iReco] << endl;
		cout << " PF photon isolation with PUPPI No Leptons = " << ele_PFPhotonIso_PUPPINL[iReco] << endl;
		cout << " PF charged hadron isolation with CITK = " << ele_PFChargedHadIso_CITK[iReco] << endl;
		cout << " PF neutral hadron isolation with CITK = " << ele_PFNeutralHadIso_CITK[iReco] << endl;
		cout << " PF photon isolation with CITK = " << ele_PFPhotonIso_CITK[iReco] << endl;
		//cout << " PF isolation simple = " << ele_PFIso_simple[iReco] << endl;
		//cout << " PF isolation Effective Area = " << ele_PFIso_effarea[iReco] << endl;
		//cout << " PF isolation Delta Beta = " << ele_PFIso_deltabeta[iReco] << endl;
                //cout << " Electron BDT = " << ele_BDT[iReco] << " is BDT? " << ele_isBDT[iReco] << endl;
		//cout << " Electron SIP = " << ele_SIP[iReco] << endl;
		//cout << " Id = " << ele_ID[iReco] << " Electron Is Good = " << ele_isGood[iReco] << endl;
		}


		ele_PFPhotonIsoRel_PUPPINL[iReco] = ele_PFPhotonIso_PUPPINL[iReco] / ele_pt[iReco];

		for(int iGen=0; iGen<gen; iGen++)
			{			
			if (delta_r(geeta[iGen],gephi[iGen],ele_eta[iReco],ele_phi[iReco]) < 0.1) {
			if (detail or test) {cout << "Matched to #" << iGen << " (eta = " << geeta[iGen] << " and phi = " << gephi[iGen] << ")" << endl; }
			radius = delta_r(geeta[iGen],gephi[iGen],ele_eta[iReco],ele_phi[iReco]);
			matched = true;
			}
			if (delta_r(geeta[iGen],gephi[iGen],ele_eta[iReco],ele_phi[iReco]) < 0.1) {
			if (detail or test) {cout << "Separated to #" << iGen << " (eta = " << geeta[iGen] << " and phi = " << gephi[iGen] << ")" << endl; }
			radius = delta_r(geeta[iGen],gephi[iGen],ele_eta[iReco],ele_phi[iReco]);
			separated = false;
			}
			}
		if (matched) { ele_matched_event = ele_matched_event + 1; }
		if (separated) { ele_separated_event = ele_separated_event + 1; }

		if ((ele_pt[iReco] > 7.0 and (TMath::Abs(ele_sclEta[iReco]) < 2.5) and ele_dxy[iReco] < 0.5 and ele_dz[iReco] < 1.0 and use_electrons) and ((signal[s] and matched) or (!signal[s] and separated)))
		{
		if (ele_pt[iReco] > max_reco_pt) { max_reco_pt = ele_pt[iReco]; id_leading_reco = iReco; }
		if (detail or test) { cout << "Electron Selected" << endl; }
		if (signal[s]) { ele_matched = ele_matched + 1; }
		if (!signal[s]) { ele_separated = ele_separated + 1; }
		if (!signal[s]  and show_special_events and TMath::Abs(ele_sclEta[iReco]) < 0.5 and ele_BDT[iReco] > 0.9 and max_special_events > 0)
			{
			if (!disp_ini_info)
				{
				cout << "z = " << z << " of " << entries << endl;
				cout << "Event Number = " << nEvent << endl;
				cout << "Run Number = " << nRun << endl;
				cout << "Lumi Block = " << nLumi << endl;
				cout << "Number of Generated Vertexes = " << nPV << endl;
				cout << "Electron Rho = " << rho << endl;
				cout << "Generated Electrons = " << gen << endl;
				cout << "Generated Muons = " << gmn << endl;
				disp_ini_info = true;
				max_special_events = max_special_events - 1;
				}
			cout << "#" << iReco << " pt = " << ele_pt[iReco] << " eta = " << ele_sclEta[iReco] << " phi = " << ele_phi[iReco] << endl;
			cout << " Radius = " << radius << endl;
                	cout << " dxy = " << ele_dxy[iReco] << " dz = " << ele_dz[iReco] << " missing hits = " << ele_missingHit[iReco] << endl;
			cout << " PF charged hadron isolation = " << ele_PFChargedHadIso[iReco] << endl;
			cout << " PF neutral hadron isolation = " << ele_PFNeutralHadIso[iReco] << endl;
			cout << " PF photon isolation = " << ele_PFPhotonIso[iReco] << endl;
			cout << " PF isolation simple = " << ele_PFIso_simple[iReco] << endl;
			cout << " PF isolation Effective Area = " << ele_PFIso_effarea[iReco] << endl;
			cout << " PF isolation Delta Beta = " << ele_PFIso_deltabeta[iReco] << endl;
                	cout << " Electron BDT = " << ele_BDT[iReco] << " is BDT? " << ele_isBDT[iReco] << endl;
			cout << " Electron SIP = " << ele_SIP[iReco] << endl;
			cout << " Id = " << ele_ID[iReco] << " Electron Is Good = " << ele_isGood[iReco] << endl;
			}
		selected_electrons[s] = selected_electrons[s] + 1;	
		reco_ele_pt->Fill(ele_pt[iReco]);
		reco_ele_eta->Fill(ele_sclEta[iReco]);
		reco_ele_phi->Fill(ele_phi[iReco]);
		reco_ele_effarea->Fill(ele_effarea[iReco]);
		reco_ele_dxy->Fill(ele_dxy[iReco]);
		reco_ele_dz->Fill(ele_dz[iReco]);
		reco_ele_missinghit->Fill(ele_missingHit[iReco]);
		reco_ele_pfchhadiso->Fill(ele_PFChargedHadIso[iReco]);
		reco_ele_pfchhadisorel->Fill(ele_PFChargedHadIsoRel[iReco]);
		reco_ele_pfnehadiso->Fill(ele_PFNeutralHadIso[iReco]);
		reco_ele_pfnehadisorel->Fill(ele_PFNeutralHadIsoRel[iReco]);
		reco_ele_pfphotoniso->Fill(ele_PFPhotonIso[iReco]);
		reco_ele_pfphotonisorel->Fill(ele_PFPhotonIsoRel[iReco]);
		reco_ele_pfchargedfrompu->Fill(ele_PFChargedFromPU[iReco]);
		reco_ele_pfchargedfrompurel->Fill(ele_PFChargedFromPURel[iReco]);

		reco_ele_pfchhadiso_puppi->Fill(ele_PFChargedHadIso_PUPPI[iReco]);
		reco_ele_pfchhadisorel_puppi->Fill(ele_PFChargedHadIsoRel_PUPPI[iReco]);
		reco_ele_pfnehadiso_puppi->Fill(ele_PFNeutralHadIso_PUPPI[iReco]);
		reco_ele_pfnehadisorel_puppi->Fill(ele_PFNeutralHadIsoRel_PUPPI[iReco]);
		reco_ele_pfphotoniso_puppi->Fill(ele_PFPhotonIso_PUPPI[iReco]);
		reco_ele_pfphotonisorel_puppi->Fill(ele_PFPhotonIsoRel_PUPPI[iReco]);

		reco_ele_pfchhadiso_puppinl->Fill(ele_PFChargedHadIso_PUPPINL[iReco]);
		reco_ele_pfchhadisorel_puppinl->Fill(ele_PFChargedHadIsoRel_PUPPINL[iReco]);
		reco_ele_pfnehadiso_puppinl->Fill(ele_PFNeutralHadIso_PUPPINL[iReco]);
		reco_ele_pfnehadisorel_puppinl->Fill(ele_PFNeutralHadIsoRel_PUPPINL[iReco]);
		reco_ele_pfphotoniso_puppinl->Fill(ele_PFPhotonIso_PUPPINL[iReco]);
		reco_ele_pfphotonisorel_puppinl->Fill(ele_PFPhotonIsoRel_PUPPINL[iReco]);

		reco_ele_pfchhadiso_citk->Fill(ele_PFChargedHadIso_CITK[iReco]);
		reco_ele_pfchhadisorel_citk->Fill(ele_PFChargedHadIsoRel_CITK[iReco]);
		reco_ele_pfnehadiso_citk->Fill(ele_PFNeutralHadIso_CITK[iReco]);
		reco_ele_pfnehadisorel_citk->Fill(ele_PFNeutralHadIsoRel_CITK[iReco]);
		reco_ele_pfphotoniso_citk->Fill(ele_PFPhotonIso_CITK[iReco]);
		reco_ele_pfphotonisorel_citk->Fill(ele_PFPhotonIsoRel_CITK[iReco]);

		reco_ele_pfiso_simple->Fill(ele_PFIso_simple[iReco]);
		reco_ele_pfiso_effarea->Fill(ele_PFIso_effarea[iReco]);
		reco_ele_pfiso_deltabeta->Fill(ele_PFIso_deltabeta[iReco]);
		reco_ele_pfiso_puppi->Fill(ele_PFIso_PUPPI[iReco]);
		reco_ele_pfiso_puppinl->Fill(ele_PFIso_PUPPINL[iReco]);
		reco_ele_pfiso_citk->Fill(ele_PFIso_CITK[iReco]);

		iso_simple_vs_pt->Fill(ele_PFIso_simple[iReco],ele_pt[iReco]);
		iso_simple_vs_vtx->Fill(ele_PFIso_simple[iReco],nPV);
		iso_simple_vs_eta->Fill(ele_PFIso_simple[iReco],ele_sclEta[iReco]);
		iso_effarea_vs_pt->Fill(ele_PFIso_effarea[iReco],ele_pt[iReco]);
		iso_effarea_vs_vtx->Fill(ele_PFIso_effarea[iReco],nPV);
		iso_effarea_vs_eta->Fill(ele_PFIso_effarea[iReco],ele_sclEta[iReco]);
		iso_deltabeta_vs_pt->Fill(ele_PFIso_deltabeta[iReco],ele_pt[iReco]);
		iso_deltabeta_vs_vtx->Fill(ele_PFIso_deltabeta[iReco],nPV);
		iso_deltabeta_vs_eta->Fill(ele_PFIso_deltabeta[iReco],ele_sclEta[iReco]);
		iso_puppi_vs_pt->Fill(ele_PFIso_PUPPI[iReco],ele_pt[iReco]);
		iso_puppi_vs_vtx->Fill(ele_PFIso_PUPPI[iReco],nPV);
		iso_puppi_vs_eta->Fill(ele_PFIso_PUPPI[iReco],ele_sclEta[iReco]);
		iso_puppinl_vs_pt->Fill(ele_PFIso_PUPPINL[iReco],ele_pt[iReco]);
		iso_puppinl_vs_vtx->Fill(ele_PFIso_PUPPINL[iReco],nPV);
		iso_puppinl_vs_eta->Fill(ele_PFIso_PUPPINL[iReco],ele_sclEta[iReco]);
		iso_citk_vs_pt->Fill(ele_PFIso_CITK[iReco],ele_pt[iReco]);
		iso_citk_vs_vtx->Fill(ele_PFIso_CITK[iReco],nPV);
		iso_citk_vs_eta->Fill(ele_PFIso_CITK[iReco],ele_sclEta[iReco]);
		if (nPV <= 15)
			{
			reco_ele_pfiso_simple_lowpu->Fill(ele_PFIso_simple[iReco]);
			reco_ele_pfiso_effarea_lowpu->Fill(ele_PFIso_effarea[iReco]);
			reco_ele_pfiso_deltabeta_lowpu->Fill(ele_PFIso_deltabeta[iReco]);
			reco_ele_pfiso_puppi_lowpu->Fill(ele_PFIso_PUPPI[iReco]);
			reco_ele_pfiso_puppinl_lowpu->Fill(ele_PFIso_PUPPINL[iReco]);
			reco_ele_pfiso_citk_lowpu->Fill(ele_PFIso_CITK[iReco]);
			}
		if (nPV > 15 and nPV < 25)
			{
			reco_ele_pfiso_simple_medpu->Fill(ele_PFIso_simple[iReco]);
			reco_ele_pfiso_effarea_medpu->Fill(ele_PFIso_effarea[iReco]);
			reco_ele_pfiso_deltabeta_medpu->Fill(ele_PFIso_deltabeta[iReco]);
			reco_ele_pfiso_puppi_medpu->Fill(ele_PFIso_PUPPI[iReco]);
			reco_ele_pfiso_puppinl_medpu->Fill(ele_PFIso_PUPPINL[iReco]);
			reco_ele_pfiso_citk_medpu->Fill(ele_PFIso_CITK[iReco]);
			}
		if (nPV >= 25)
			{
			reco_ele_pfiso_simple_highpu->Fill(ele_PFIso_simple[iReco]);
			reco_ele_pfiso_effarea_highpu->Fill(ele_PFIso_effarea[iReco]);
			reco_ele_pfiso_deltabeta_highpu->Fill(ele_PFIso_deltabeta[iReco]);
			reco_ele_pfiso_puppi_highpu->Fill(ele_PFIso_PUPPI[iReco]);
			reco_ele_pfiso_puppinl_highpu->Fill(ele_PFIso_PUPPINL[iReco]);
			reco_ele_pfiso_citk_highpu->Fill(ele_PFIso_CITK[iReco]);
			}
		reco_ele_bdt->Fill(ele_BDT[iReco]);
		reco_ele_sip->Fill(ele_SIP[iReco]);
		reco_ele_id->Fill(ele_ID[iReco]);
		reco_ele_isgood->Fill(ele_isGood[iReco]);
		if (TMath::Abs(ele_sclEta[iReco]) < 1.479)
			{
			reco_ele_sip_barrel->Fill(ele_SIP[iReco]);
			reco_ele_bdt_barrel->Fill(ele_BDT[iReco]);
			reco_ele_pfchhadiso_barrel->Fill(ele_PFChargedHadIso[iReco]);
			reco_ele_pfnehadiso_barrel->Fill(ele_PFNeutralHadIso[iReco]);
			reco_ele_pfphotoniso_barrel->Fill(ele_PFPhotonIso[iReco]);
			reco_ele_pfchargedfrompu_barrel->Fill(ele_PFChargedFromPU[iReco]);

			reco_ele_pfchhadiso_puppi_barrel->Fill(ele_PFChargedHadIso_PUPPI[iReco]);
			reco_ele_pfnehadiso_puppi_barrel->Fill(ele_PFNeutralHadIso_PUPPI[iReco]);
			reco_ele_pfphotoniso_puppi_barrel->Fill(ele_PFPhotonIso_PUPPI[iReco]);

			reco_ele_pfchhadiso_puppinl_barrel->Fill(ele_PFChargedHadIso_PUPPINL[iReco]);
			reco_ele_pfnehadiso_puppinl_barrel->Fill(ele_PFNeutralHadIso_PUPPINL[iReco]);
			reco_ele_pfphotoniso_puppinl_barrel->Fill(ele_PFPhotonIso_PUPPINL[iReco]);

			reco_ele_pfchhadiso_citk_barrel->Fill(ele_PFChargedHadIso_CITK[iReco]);
			reco_ele_pfnehadiso_citk_barrel->Fill(ele_PFNeutralHadIso_CITK[iReco]);
			reco_ele_pfphotoniso_citk_barrel->Fill(ele_PFPhotonIso_CITK[iReco]);

			reco_ele_pfiso_simple_barrel->Fill(ele_PFIso_simple[iReco]);
			reco_ele_pfiso_effarea_barrel->Fill(ele_PFIso_effarea[iReco]);
			reco_ele_pfiso_deltabeta_barrel->Fill(ele_PFIso_deltabeta[iReco]);
			reco_ele_pfiso_puppi_barrel->Fill(ele_PFIso_PUPPI[iReco]);
			reco_ele_pfiso_puppinl_barrel->Fill(ele_PFIso_PUPPINL[iReco]);
			reco_ele_pfiso_citk_barrel->Fill(ele_PFIso_CITK[iReco]);
			}
		else
			{
			reco_ele_sip_endcap->Fill(ele_SIP[iReco]);
			reco_ele_bdt_endcap->Fill(ele_BDT[iReco]);
			reco_ele_pfchhadiso_endcap->Fill(ele_PFChargedHadIso[iReco]);
			reco_ele_pfnehadiso_endcap->Fill(ele_PFNeutralHadIso[iReco]);
			reco_ele_pfphotoniso_endcap->Fill(ele_PFPhotonIso[iReco]);
			reco_ele_pfchargedfrompu_endcap->Fill(ele_PFChargedFromPU[iReco]);

			reco_ele_pfchhadiso_puppi_endcap->Fill(ele_PFChargedHadIso_PUPPI[iReco]);
			reco_ele_pfnehadiso_puppi_endcap->Fill(ele_PFNeutralHadIso_PUPPI[iReco]);
			reco_ele_pfphotoniso_puppi_endcap->Fill(ele_PFPhotonIso_PUPPI[iReco]);

			reco_ele_pfchhadiso_puppinl_endcap->Fill(ele_PFChargedHadIso_PUPPINL[iReco]);
			reco_ele_pfnehadiso_puppinl_endcap->Fill(ele_PFNeutralHadIso_PUPPINL[iReco]);
			reco_ele_pfphotoniso_puppinl_endcap->Fill(ele_PFPhotonIso_PUPPINL[iReco]);

			reco_ele_pfchhadiso_citk_endcap->Fill(ele_PFChargedHadIso_CITK[iReco]);
			reco_ele_pfnehadiso_citk_endcap->Fill(ele_PFNeutralHadIso_CITK[iReco]);
			reco_ele_pfphotoniso_citk_endcap->Fill(ele_PFPhotonIso_CITK[iReco]);

			reco_ele_pfiso_simple_endcap->Fill(ele_PFIso_simple[iReco]);
			reco_ele_pfiso_effarea_endcap->Fill(ele_PFIso_effarea[iReco]);
			reco_ele_pfiso_deltabeta_endcap->Fill(ele_PFIso_deltabeta[iReco]);
			reco_ele_pfiso_puppi_endcap->Fill(ele_PFIso_PUPPI[iReco]);
			reco_ele_pfiso_puppinl_endcap->Fill(ele_PFIso_PUPPINL[iReco]);
			reco_ele_pfiso_citk_endcap->Fill(ele_PFIso_CITK[iReco]);
			}
		}
		}	

	if (id_leading_gen > -1)
		{
		leading_gen_ele_pt->Fill(gept[id_leading_gen]);
		leading_gen_ele_eta->Fill(geeta[id_leading_gen]);
		leading_gen_ele_phi->Fill(gephi[id_leading_gen]);
		}
	if (id_leading_reco > -1)
		{
		leading_reco_ele_pt->Fill(ele_pt[id_leading_reco]);
		leading_reco_ele_eta->Fill(ele_sclEta[id_leading_reco]);
		leading_reco_ele_phi->Fill(ele_phi[id_leading_reco]);
		}

		gen_ele_multiplicity_am->Fill(gen);
		reco_ele_multiplicity_am->Fill(nele);
		gen_ele_multiplicity_matched->Fill(ele_matched_event);
		reco_ele_multiplicity_matched->Fill(ele_matched_event);
		gen_ele_multiplicity_separated->Fill(ele_separated_event);
		reco_ele_multiplicity_separated->Fill(ele_separated_event);
	}
	else
	{
	if (detail) { cout << "Event rejected!" << endl; }
	}

	}


//normalization of the histograms
normalize_histogram(vertex_multiplicity, "Vertex Multiplicity", true, false);
normalize_histogram(reco_pu, "Reconstructed Pile-Up", true, false);
normalize_histogram(gen_pu, "Generated Pile-Up", true, false);
normalize_histogram(evt_rho, "evt_rho", true, false);

normalize_histogram(gen_ele_multiplicity, "Generated Electron Multiplicity", true, false);
normalize_histogram(gen_ele_multiplicity_am, "Generated Electron Multiplicity After Matching", true, false);
normalize_histogram(gen_ele_multiplicity_matched, "Generated Electron Multiplicity Matched", true, false);
normalize_histogram(gen_ele_multiplicity_separated, "Generated Electron Multiplicity Separated", true, false);
normalize_histogram(gen_ele_pt, "Gen Electron pT", true, false);
normalize_histogram(gen_ele_eta, "Gen Electron Eta", true, false);
normalize_histogram(gen_ele_phi, "Gen Electron Phi", true, false);
normalize_histogram(leading_gen_ele_pt, "Leading Gen Electron pT", true, false);
normalize_histogram(leading_gen_ele_eta, "Leading Gen Electron Eta", true, false);
normalize_histogram(leading_gen_ele_phi, "Leading Gen Electron Phi", true, false);

normalize_histogram(reco_ele_multiplicity, "Reco Electron Multiplicity", true, false);
normalize_histogram(reco_ele_multiplicity_am, "Reco Electron Multiplicity After Matching", true, false);
normalize_histogram(reco_ele_multiplicity_matched, "Reco Electron Multiplicity Matched", true, false);
normalize_histogram(reco_ele_multiplicity_separated, "Reco Electron Multiplicity Separated", true, false);
normalize_histogram(reco_ele_pt, "Reco Electron pT", true, false);
normalize_histogram(reco_ele_eta, "Reco Electron Eta", true, false);
normalize_histogram(reco_ele_phi, "Reco Electron Phi", true, false);
normalize_histogram(reco_ele_effarea, "Reco Electron Effective Area", true, false);
normalize_histogram(reco_ele_dxy, "Reco Electron dxy", true, false);
normalize_histogram(reco_ele_dz, "Reco Electron dz", true, false);
normalize_histogram(reco_ele_missinghit, "Reco Electron Missing Hit", true, false);

normalize_histogram(reco_ele_pfchhadiso, "Reco Electron Charged Hadron Isolation", true, false);
normalize_histogram(reco_ele_pfchhadisorel, "Reco Electron Charged Hadron Isolation Relative", true, false);
normalize_histogram(reco_ele_pfchhadiso_barrel, "Reco Electron Charged Hadron Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_endcap, "Reco Electron Charged Hadron Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfnehadiso, "Reco Electron Neutral Hadron Isolation", true, false);
normalize_histogram(reco_ele_pfnehadisorel, "Reco Electron Neutral Hadron Isolation Relative", true, false);
normalize_histogram(reco_ele_pfnehadiso_barrel, "Reco Electron Neutral Hadron Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_endcap, "Reco Electron Neutral Hadron Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfphotoniso, "Reco Electron Photon Isolation", true, false);
normalize_histogram(reco_ele_pfphotonisorel, "Reco Electron Photon Isolation Relative", true, false);
normalize_histogram(reco_ele_pfphotoniso_barrel, "Reco Electron Photon Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_endcap, "Reco Electron Photon Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfchargedfrompu, "Reco Electron Charged Hadrom From Pile-Up Isolation", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel, "Reco Electron Charged Hadrom From Pile-Up Isolation Relative", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_barrel, "Reco Electron Charged Hadrom From Pile-Up Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_endcap, "Reco Electron Charged Hadrom From Pile-Up Isolation EndCap", true, false);

normalize_histogram(reco_ele_pfchhadiso_puppi, "Reco Electron Charged Hadron Isolation From PUPPI", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi, "Reco Electron Charged Hadron Isolation From PUPPI Relative", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppi_barrel, "Reco Electron Charged Hadron Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppi_endcap, "Reco Electron Charged Hadron Isolation From PUPPI EndCap", true, false);

normalize_histogram(reco_ele_pfnehadiso_puppi, "Reco Electron Neutral Hadron Isolation From PUPPI", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi, "Reco Electron Neutral Hadron Isolation From PUPPI Relative", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppi_barrel, "Reco Electron Neutral Hadron Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppi_endcap, "Reco Electron Neutral Hadron Isolation From PUPPI EndCap", true, false);

normalize_histogram(reco_ele_pfphotoniso_puppi, "Reco Electron Photon Isolation From PUPPI", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi, "Reco Electron Photon Isolation From PUPPI Relative", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppi_barrel, "Reco Electron Photon Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppi_endcap, "Reco Electron Photon Isolation From PUPPI EndCap", true, false);

normalize_histogram(reco_ele_pfchhadiso_puppinl, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Relative", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppinl_barrel, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppinl_endcap, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons EndCap", true, false);

normalize_histogram(reco_ele_pfnehadiso_puppinl, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Relative", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppinl_barrel, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppinl_endcap, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons EndCap", true, false);

normalize_histogram(reco_ele_pfphotoniso_puppinl, "Reco Electron Photon Isolation From PUPPI No Leptons", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl, "Reco Electron Photon Isolation From PUPPI No Leptons Relative", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppinl_barrel, "Reco Electron Photon Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppinl_endcap, "Reco Electron Photon Isolation From PUPPI No Leptons EndCap", true, false);

normalize_histogram(reco_ele_pfchhadiso_citk, "Reco Electron Charged Hadron Isolation From CITK", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk, "Reco Electron Charged Hadron Isolation From CITK Relative", true, false);
normalize_histogram(reco_ele_pfchhadiso_citk_barrel, "Reco Electron Charged Hadron Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_citk_endcap, "Reco Electron Charged Hadron Isolation From CITK EndCap", true, false);

normalize_histogram(reco_ele_pfnehadiso_citk, "Reco Electron Neutral Hadron Isolation From CITK", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk, "Reco Electron Neutral Hadron Isolation From CITK Relative", true, false);
normalize_histogram(reco_ele_pfnehadiso_citk_barrel, "Reco Electron Neutral Hadron Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_citk_endcap, "Reco Electron Neutral Hadron Isolation From CITK EndCap", true, false);

normalize_histogram(reco_ele_pfphotoniso_citk, "Reco Electron Photon Isolation From CITK", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk, "Reco Electron Photon Isolation From CITK Relative", true, false);
normalize_histogram(reco_ele_pfphotoniso_citk_barrel, "Reco Electron Photon Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_citk_endcap, "Reco Electron Photon Isolation From CITK EndCap", true, false);

normalize_histogram(reco_ele_pfiso_simple, "Reco_ele_PFIso_Simple", true, false);
normalize_histogram(reco_ele_pfiso_simple_barrel, "Reco_ele_PFIso_Simple_Barrel", true, false);
normalize_histogram(reco_ele_pfiso_simple_endcap, "Reco_ele_PFIso_Simple_EndCap", true, false);
normalize_histogram(reco_ele_pfiso_simple_lowpu, "Reco_ele_PFIso_Simple Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_simple_medpu, "Reco_ele_PFIso_Simple Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_simple_highpu, "Reco_ele_PFIso_Simple High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_effarea, "Reco_ele_PFIso_EffArea", true, false);
normalize_histogram(reco_ele_pfiso_effarea_barrel, "Reco_ele_PFIso_Simple_EffArea", true, false);
normalize_histogram(reco_ele_pfiso_effarea_endcap, "Reco_ele_PFIso_Simple_EffArea", true, false);
normalize_histogram(reco_ele_pfiso_effarea_lowpu, "Reco_ele_PFIso_EffArea Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_effarea_medpu, "Reco_ele_PFIso_EffArea Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_effarea_highpu, "Reco_ele_PFIso_EffArea High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_deltabeta, "Reco_ele_PFIso_DeltaBeta", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_barrel, "Reco_ele_PFIso_DeltaBeta_Barrel", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_endcap, "Reco_ele_PFIso_DeltaBeta_EndCap", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_lowpu, "Reco_ele_PFIso_DeltaBeta Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_medpu, "Reco_ele_PFIso_DeltaBeta Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_highpu, "Reco_ele_PFIso_DeltaBeta High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_puppi, "Reco_ele_PFIso_PUPPI", true, false);
normalize_histogram(reco_ele_pfiso_puppi_barrel, "Reco_ele_PFIso_PUPPI_Barrel", true, false);
normalize_histogram(reco_ele_pfiso_puppi_endcap, "Reco_ele_PFIso_PUPPI_EndCap", true, false);
normalize_histogram(reco_ele_pfiso_puppi_lowpu, "Reco_ele_PFIso_PUPPI Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_puppi_medpu, "Reco_ele_PFIso_PUPPI Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_puppi_highpu, "Reco_ele_PFIso_PUPPI High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_puppinl, "Reco_ele_PFIso PUPPI No Leptons", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_barrel, "Reco_ele_PFIso PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_endcap, "Reco_ele_PFIso PUPPI No Leptons EndCap", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_lowpu, "Reco_ele_PFIso PUPPI No Leptons Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_medpu, "Reco_ele_PFIso PUPPI No Leptons Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_highpu, "Reco_ele_PFIso PUPPI No Leptons High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_citk, "Reco_ele_PFIso CITK", true, false);
normalize_histogram(reco_ele_pfiso_citk_barrel, "Reco_ele_PFIso CITK Barrel", true, false);
normalize_histogram(reco_ele_pfiso_citk_endcap, "Reco_ele_PFIso CITK EndCap", true, false);
normalize_histogram(reco_ele_pfiso_citk_lowpu, "Reco_ele_PFIso CITK Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_citk_medpu, "Reco_ele_PFIso CITK Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_citk_highpu, "Reco_ele_PFIso CITK High Pile-Up", true, false);

normalize_histogram(reco_ele_sip, "Reco_ele_SIP", true, false);
normalize_histogram(reco_ele_sip_barrel, "Reco_ele_SIP_Barrel", true, false);
normalize_histogram(reco_ele_sip_endcap, "Reco_ele_SIP_EndCap", true, false);
normalize_histogram(reco_ele_bdt, "Reco_ele_BDT", true, false);
normalize_histogram(reco_ele_bdt_barrel, "Reco_ele_BDT_Barrel", true, false);
normalize_histogram(reco_ele_bdt_endcap, "Reco_ele_BDT_EndCap", true, false);
normalize_histogram(reco_ele_id, "Reco_ele_ID", true, false);
normalize_histogram(reco_ele_isgood, "Reco_ele_isGood", true, false);

normalize_histogram(leading_reco_ele_pt, "Leading_Reco_ele_pT", true, false);
normalize_histogram(leading_reco_ele_eta, "Leading_Reco_ele_Eta", true, false);
normalize_histogram(leading_reco_ele_phi, "Leading_Reco_ele_Phi", true, false);

int nbins = reco_ele_pfiso_simple->GetNbinsX();
int x;

for (x=1; x<nbins; x++)
	{
	if (detail) { cout << "Isolation Simple x = " << x << " integral = " << reco_ele_pfiso_simple->Integral(0,x) << endl; }
	if (detail) { cout << "Isolation Simple Barrel x = " << x << " integral = " << reco_ele_pfiso_simple_barrel->Integral(0,x) << endl; }
	if (detail) { cout << "Isolation Simple Endcap x = " << x << " integral = " << reco_ele_pfiso_simple_endcap->Integral(0,x) << endl; }

	if (detail) { cout << "Isolation Effective Area x = " << x << " integral = " << reco_ele_pfiso_effarea->Integral(0,x) << endl; }
	if (detail) { cout << "Isolation Effective Area Barrel x = " << x << " integral = " << reco_ele_pfiso_effarea_barrel->Integral(0,x) << endl; }
	if (detail) { cout << "Isolation Effective Area Endcap x = " << x << " integral = " << reco_ele_pfiso_effarea_endcap->Integral(0,x) << endl; }

	if (detail) { cout << "Isolation Delta Beta x = " << x << " integral = " << reco_ele_pfiso_deltabeta->Integral(0,x) << endl; }
	if (detail) { cout << "Isolation Delta Beta Barrel x = " << x << " integral = " << reco_ele_pfiso_deltabeta_barrel->Integral(0,x) << endl; }
	if (detail) { cout << "Isolation Delta Beta Endcap x = " << x << " integral = " << reco_ele_pfiso_deltabeta_endcap->Integral(0,x) << endl; }

	if (detail) { cout << "SIP x = " << x << " integral = " << reco_ele_sip->Integral(0,x) << endl; }
	if (detail) { cout << "SIP Barrel x = " << x << " integral = " << reco_ele_sip_barrel->Integral(0,x) << endl; }
	if (detail) { cout << "SIP Endcap x = " << x << " integral = " << reco_ele_sip_endcap->Integral(0,x) << endl; }
	if (detail) { cout << "BDT x = " << x << " integral = " << reco_ele_bdt->Integral(nbins-x,nbins) << endl; }
	if (detail) { cout << "BDT Barrel x = " << x << " integral = " << reco_ele_bdt_barrel->Integral(nbins-x,nbins) << endl; }
	if (detail) { cout << "BDT Endcap x = " << x << " integral = " << reco_ele_bdt_endcap->Integral(nbins-x,nbins) << endl; }
	isolation_simple[s][x-1] = reco_ele_pfiso_simple->Integral(0,x);
	isolation_simple_barrel[s][x-1] = reco_ele_pfiso_simple_barrel->Integral(0,x);
	isolation_simple_endcap[s][x-1] = reco_ele_pfiso_simple_endcap->Integral(0,x);
	isolation_simple_lowpu[s][x-1] = reco_ele_pfiso_simple_lowpu->Integral(0,x);
	isolation_simple_medpu[s][x-1] = reco_ele_pfiso_simple_medpu->Integral(0,x);
	isolation_simple_highpu[s][x-1] = reco_ele_pfiso_simple_highpu->Integral(0,x);

	isolation_effarea[s][x-1] = reco_ele_pfiso_effarea->Integral(0,x);
	isolation_effarea_barrel[s][x-1] = reco_ele_pfiso_effarea_barrel->Integral(0,x);
	isolation_effarea_endcap[s][x-1] = reco_ele_pfiso_effarea_endcap->Integral(0,x);
	isolation_effarea_lowpu[s][x-1] = reco_ele_pfiso_effarea_lowpu->Integral(0,x);
	isolation_effarea_medpu[s][x-1] = reco_ele_pfiso_effarea_medpu->Integral(0,x);
	isolation_effarea_highpu[s][x-1] = reco_ele_pfiso_effarea_highpu->Integral(0,x);

	isolation_deltabeta[s][x-1] = reco_ele_pfiso_deltabeta->Integral(0,x);
	isolation_deltabeta_barrel[s][x-1] = reco_ele_pfiso_deltabeta_barrel->Integral(0,x);
	isolation_deltabeta_endcap[s][x-1] = reco_ele_pfiso_deltabeta_endcap->Integral(0,x);
	isolation_deltabeta_lowpu[s][x-1] = reco_ele_pfiso_deltabeta_lowpu->Integral(0,x);
	isolation_deltabeta_medpu[s][x-1] = reco_ele_pfiso_deltabeta_medpu->Integral(0,x);
	isolation_deltabeta_highpu[s][x-1] = reco_ele_pfiso_deltabeta_highpu->Integral(0,x);

	isolation_puppi[s][x-1] = reco_ele_pfiso_puppi->Integral(0,x);
	isolation_puppi_barrel[s][x-1] = reco_ele_pfiso_puppi_barrel->Integral(0,x);
	isolation_puppi_endcap[s][x-1] = reco_ele_pfiso_puppi_endcap->Integral(0,x);
	isolation_puppi_lowpu[s][x-1] = reco_ele_pfiso_puppi_lowpu->Integral(0,x);
	isolation_puppi_medpu[s][x-1] = reco_ele_pfiso_puppi_medpu->Integral(0,x);
	isolation_puppi_highpu[s][x-1] = reco_ele_pfiso_puppi_highpu->Integral(0,x);

	isolation_puppinl[s][x-1] = reco_ele_pfiso_puppinl->Integral(0,x);
	isolation_puppinl_barrel[s][x-1] = reco_ele_pfiso_puppinl_barrel->Integral(0,x);
	isolation_puppinl_endcap[s][x-1] = reco_ele_pfiso_puppinl_endcap->Integral(0,x);
	isolation_puppinl_lowpu[s][x-1] = reco_ele_pfiso_puppinl_lowpu->Integral(0,x);
	isolation_puppinl_medpu[s][x-1] = reco_ele_pfiso_puppinl_medpu->Integral(0,x);
	isolation_puppinl_highpu[s][x-1] = reco_ele_pfiso_puppinl_highpu->Integral(0,x);

	isolation_citk[s][x-1] = reco_ele_pfiso_citk->Integral(0,x);
	isolation_citk_barrel[s][x-1] = reco_ele_pfiso_citk_barrel->Integral(0,x);
	isolation_citk_endcap[s][x-1] = reco_ele_pfiso_citk_endcap->Integral(0,x);
	isolation_citk_lowpu[s][x-1] = reco_ele_pfiso_citk_lowpu->Integral(0,x);
	isolation_citk_medpu[s][x-1] = reco_ele_pfiso_citk_medpu->Integral(0,x);
	isolation_citk_highpu[s][x-1] = reco_ele_pfiso_citk_highpu->Integral(0,x);

	sip[s][x-1] = reco_ele_sip->Integral(0,x);
	sip_barrel[s][x-1] = reco_ele_sip_barrel->Integral(0,x);
	sip_endcap[s][x-1] = reco_ele_sip_endcap->Integral(0,x);
	bdt[s][x-1] = reco_ele_bdt->Integral(nbins-x,nbins);
	bdt_barrel[s][x-1] = reco_ele_bdt_barrel->Integral(nbins-x,nbins);
	bdt_endcap[s][x-1] = reco_ele_bdt_endcap->Integral(nbins-x,nbins);
	}

   nbins = iso_simple_vs_pt->GetNbinsY();

for (x = 1; x <= nbins; x++)
	{
	isolation_simple_pt[s][x-1] = iso_simple_vs_pt->Integral(0,working_point,x,x)/iso_simple_vs_pt->Integral(0,100,x,x);
	isolation_effarea_pt[s][x-1] = iso_effarea_vs_pt->Integral(0,working_point,x,x)/iso_effarea_vs_pt->Integral(0,100,x,x);
	isolation_deltabeta_pt[s][x-1] = iso_deltabeta_vs_pt->Integral(0,working_point,x,x)/iso_deltabeta_vs_pt->Integral(0,100,x,x);
	isolation_puppi_pt[s][x-1] = iso_puppi_vs_pt->Integral(0,working_point,x,x)/iso_puppi_vs_pt->Integral(0,100,x,x);
	isolation_puppinl_pt[s][x-1] = iso_puppinl_vs_pt->Integral(0,working_point,x,x)/iso_puppinl_vs_pt->Integral(0,100,x,x);
	isolation_citk_pt[s][x-1] = iso_citk_vs_pt->Integral(0,working_point,x,x)/iso_citk_vs_pt->Integral(0,100,x,x);
	}
	
   nbins = iso_simple_vs_vtx->GetNbinsY();

for (x=1; x<=nbins; x++)
	{
	isolation_simple_vtx[s][x-1] = iso_simple_vs_vtx->Integral(0,working_point,x,x)/iso_simple_vs_vtx->Integral(0,100,x,x);
	isolation_effarea_vtx[s][x-1] = iso_effarea_vs_vtx->Integral(0,working_point,x,x)/iso_effarea_vs_vtx->Integral(0,100,x,x);
	isolation_deltabeta_vtx[s][x-1] = iso_deltabeta_vs_vtx->Integral(0,working_point,x,x)/iso_deltabeta_vs_vtx->Integral(0,100,x,x);
	isolation_puppi_vtx[s][x-1] = iso_puppi_vs_vtx->Integral(0,working_point,x,x)/iso_puppi_vs_vtx->Integral(0,100,x,x);
	isolation_puppinl_vtx[s][x-1] = iso_puppinl_vs_vtx->Integral(0,working_point,x,x)/iso_puppinl_vs_vtx->Integral(0,100,x,x);
	isolation_citk_vtx[s][x-1] = iso_citk_vs_vtx->Integral(0,working_point,x,x)/iso_citk_vs_vtx->Integral(0,100,x,x);
	}
	
   nbins = iso_simple_vs_eta->GetNbinsY();

for (x=1; x<=nbins; x++)
	{
	isolation_simple_eta[s][x-1] = iso_simple_vs_eta->Integral(0,working_point,x,x)/iso_simple_vs_eta->Integral(0,100,x,x);
	isolation_effarea_eta[s][x-1] = iso_effarea_vs_eta->Integral(0,working_point,x,x)/iso_effarea_vs_eta->Integral(0,100,x,x);
	isolation_deltabeta_eta[s][x-1] = iso_deltabeta_vs_eta->Integral(0,working_point,x,x)/iso_deltabeta_vs_eta->Integral(0,100,x,x);
	isolation_puppi_eta[s][x-1] = iso_puppi_vs_eta->Integral(0,working_point,x,x)/iso_puppi_vs_eta->Integral(0,100,x,x);
	isolation_puppinl_eta[s][x-1] = iso_puppinl_vs_eta->Integral(0,working_point,x,x)/iso_puppinl_vs_eta->Integral(0,100,x,x);
	isolation_citk_eta[s][x-1] = iso_citk_vs_eta->Integral(0,working_point,x,x)/iso_citk_vs_eta->Integral(0,100,x,x);
        if (test) { cout << x << " - " << isolation_simple_eta[s][x-1] << " | " << isolation_effarea_eta[s][x-1] << " | " << isolation_deltabeta_eta[s][x-1] << endl; }
	}


     	//Open the output root file
     	TFile *data_output= TFile::Open( out[s].c_str() , "RECREATE");

     	//save histograms on the file
	vertex_multiplicity->Write();
	reco_pu->Write();
	gen_pu->Write();
	evt_rho->Write();

	gen_ele_multiplicity->Write();
	gen_ele_multiplicity_am->Write();
	gen_ele_multiplicity_matched->Write();
	gen_ele_multiplicity_separated->Write();
	gen_ele_pt->Write();
	gen_ele_eta->Write();
	gen_ele_phi->Write();
	leading_gen_ele_pt->Write();
	leading_gen_ele_eta->Write();
	leading_gen_ele_phi->Write();

	reco_ele_multiplicity->Write();
	reco_ele_multiplicity_am->Write();
	reco_ele_multiplicity_matched->Write();
	reco_ele_multiplicity_separated->Write();
	reco_ele_pt->Write();
	reco_ele_eta->Write();
	reco_ele_phi->Write();
	reco_ele_effarea->Write();
	reco_ele_dxy->Write();
	reco_ele_dz->Write();
	reco_ele_missinghit->Write();

	reco_ele_pfchhadiso->Write();
	reco_ele_pfchhadisorel->Write();
	reco_ele_pfchhadiso_barrel->Write();
	reco_ele_pfchhadiso_endcap->Write();
	reco_ele_pfnehadiso->Write();
	reco_ele_pfnehadisorel->Write();
	reco_ele_pfnehadiso_barrel->Write();
	reco_ele_pfnehadiso_endcap->Write();
	reco_ele_pfphotoniso->Write();
	reco_ele_pfphotonisorel->Write();
	reco_ele_pfphotoniso_barrel->Write();
	reco_ele_pfphotoniso_endcap->Write();
	reco_ele_pfchargedfrompu->Write();
	reco_ele_pfchargedfrompurel->Write();
	reco_ele_pfchargedfrompu_barrel->Write();
	reco_ele_pfchargedfrompu_endcap->Write();

	reco_ele_pfchhadiso_puppi->Write();
	reco_ele_pfchhadisorel_puppi->Write();
	reco_ele_pfchhadiso_puppi_barrel->Write();
	reco_ele_pfchhadiso_puppi_endcap->Write();
	reco_ele_pfnehadiso_puppi->Write();
	reco_ele_pfnehadisorel_puppi->Write();
	reco_ele_pfnehadiso_puppi_barrel->Write();
	reco_ele_pfnehadiso_puppi_endcap->Write();
	reco_ele_pfphotoniso_puppi->Write();
	reco_ele_pfphotonisorel_puppi->Write();
	reco_ele_pfphotoniso_puppi_barrel->Write();
	reco_ele_pfphotoniso_puppi_endcap->Write();

	reco_ele_pfchhadiso_puppinl->Write();
	reco_ele_pfchhadisorel_puppinl->Write();
	reco_ele_pfchhadiso_puppinl_barrel->Write();
	reco_ele_pfchhadiso_puppinl_endcap->Write();
	reco_ele_pfnehadiso_puppinl->Write();
	reco_ele_pfnehadisorel_puppinl->Write();
	reco_ele_pfnehadiso_puppinl_barrel->Write();
	reco_ele_pfnehadiso_puppinl_endcap->Write();
	reco_ele_pfphotoniso_puppinl->Write();
	reco_ele_pfphotonisorel_puppinl->Write();
	reco_ele_pfphotoniso_puppinl_barrel->Write();
	reco_ele_pfphotoniso_puppinl_endcap->Write();

	reco_ele_pfchhadiso_citk->Write();
	reco_ele_pfchhadisorel_citk->Write();
	reco_ele_pfchhadiso_citk_barrel->Write();
	reco_ele_pfchhadiso_citk_endcap->Write();
	reco_ele_pfnehadiso_citk->Write();
	reco_ele_pfnehadisorel_citk->Write();
	reco_ele_pfnehadiso_citk_barrel->Write();
	reco_ele_pfnehadiso_citk_endcap->Write();
	reco_ele_pfphotoniso_citk->Write();
	reco_ele_pfphotonisorel_citk->Write();
	reco_ele_pfphotoniso_citk_barrel->Write();
	reco_ele_pfphotoniso_citk_endcap->Write();

	reco_ele_pfiso_simple->Write();
	reco_ele_pfiso_simple_barrel->Write();
	reco_ele_pfiso_simple_endcap->Write();
	reco_ele_pfiso_simple_lowpu->Write();
	reco_ele_pfiso_simple_medpu->Write();
	reco_ele_pfiso_simple_highpu->Write();

	reco_ele_pfiso_effarea->Write();
	reco_ele_pfiso_effarea_barrel->Write();
	reco_ele_pfiso_effarea_endcap->Write();
	reco_ele_pfiso_effarea_lowpu->Write();
	reco_ele_pfiso_effarea_medpu->Write();
	reco_ele_pfiso_effarea_highpu->Write();

	reco_ele_pfiso_deltabeta->Write();
	reco_ele_pfiso_deltabeta_barrel->Write();
	reco_ele_pfiso_deltabeta_endcap->Write();
	reco_ele_pfiso_deltabeta_lowpu->Write();
	reco_ele_pfiso_deltabeta_medpu->Write();
	reco_ele_pfiso_deltabeta_highpu->Write();

	reco_ele_pfiso_puppi->Write();
	reco_ele_pfiso_puppi_barrel->Write();
	reco_ele_pfiso_puppi_endcap->Write();
	reco_ele_pfiso_puppi_lowpu->Write();
	reco_ele_pfiso_puppi_medpu->Write();
	reco_ele_pfiso_puppi_highpu->Write();

	reco_ele_pfiso_puppinl->Write();
	reco_ele_pfiso_puppinl_barrel->Write();
	reco_ele_pfiso_puppinl_endcap->Write();
	reco_ele_pfiso_puppinl_lowpu->Write();
	reco_ele_pfiso_puppinl_medpu->Write();
	reco_ele_pfiso_puppinl_highpu->Write();

	reco_ele_pfiso_citk->Write();
	reco_ele_pfiso_citk_barrel->Write();
	reco_ele_pfiso_citk_endcap->Write();
	reco_ele_pfiso_citk_lowpu->Write();
	reco_ele_pfiso_citk_medpu->Write();
	reco_ele_pfiso_citk_highpu->Write();

	reco_ele_bdt->Write();
	reco_ele_bdt_barrel->Write();
	reco_ele_bdt_endcap->Write();
	reco_ele_sip->Write();
	reco_ele_sip_barrel->Write();
	reco_ele_sip_endcap->Write();
	reco_ele_id->Write();
	reco_ele_isgood->Write();
	leading_reco_ele_pt->Write();
	leading_reco_ele_eta->Write();
	leading_reco_ele_phi->Write();
	
	iso_simple_vs_pt->Write();
	iso_simple_vs_vtx->Write();
	iso_simple_vs_eta->Write();
	
	iso_effarea_vs_pt->Write();
	iso_effarea_vs_vtx->Write();
	iso_effarea_vs_eta->Write();
	
	iso_deltabeta_vs_pt->Write();
	iso_deltabeta_vs_vtx->Write();
	iso_deltabeta_vs_eta->Write();

	iso_puppi_vs_pt->Write();
	iso_puppi_vs_vtx->Write();
	iso_puppi_vs_eta->Write();
	
	iso_puppinl_vs_pt->Write();
	iso_puppinl_vs_vtx->Write();
	iso_puppinl_vs_eta->Write();
	
	iso_citk_vs_pt->Write();
	iso_citk_vs_vtx->Write();
	iso_citk_vs_eta->Write();
	//close the file
	data_output->Close();
}

cout << "Selected Electrons " << selected_electrons[0] << " " << selected_electrons[1] << endl;

int npoints = 99;
double z0[npoints], y0[npoints], z1[npoints], y1[npoints], z2[npoints], y2[npoints];
double z3[npoints], y3[npoints], z4[npoints], y4[npoints], z5[npoints], y5[npoints];
double z6[npoints], y6[npoints], z7[npoints], y7[npoints], z8[npoints], y8[npoints];
double z9[npoints], y9[npoints], z10[npoints], y10[npoints], z11[npoints], y11[npoints];
double z12[npoints], y12[npoints], z13[npoints], y13[npoints], z14[npoints], y14[npoints];
double z15[npoints], y15[npoints], z16[npoints], y16[npoints], z17[npoints], y17[npoints];
double z18[npoints], y18[npoints], z19[npoints], y19[npoints], z20[npoints], y20[npoints];
double z21[npoints], y21[npoints], z22[npoints], y22[npoints], z23[npoints], y23[npoints];
double z24[npoints], y24[npoints], z25[npoints], y25[npoints], z26[npoints], y26[npoints];
double z27[npoints], y27[npoints], z28[npoints], y28[npoints], z29[npoints], y29[npoints];
double z30[npoints], y30[npoints], z31[npoints], y31[npoints], z32[npoints], y32[npoints];
double z33[npoints], y33[npoints], z34[npoints], y34[npoints], z35[npoints], y35[npoints];
double z36[npoints], y36[npoints], z37[npoints], y37[npoints], z38[npoints], y38[npoints];
double z39[npoints], y39[npoints], z40[npoints], y40[npoints], z41[npoints], y41[npoints];

double z0b[1], y0b[1], z1b[1], y1b[1], z2b[1], y2b[1];
double z3b[1], y3b[1], z4b[1], y4b[1], z5b[1], y5b[1];
double z6b[1], y6b[1], z7b[1], y7b[1], z8b[1], y8b[1];
double z9b[1], y9b[1], z10b[1], y10b[1], z11b[1], y11b[1];
double z12b[1], y12b[1], z13b[1], y13b[1], z14b[1], y14b[1];
double z15b[1], y15b[1], z16b[1], y16b[1], z17b[1], y17b[1];
double z18b[1], y18b[1], z19b[1], y19b[1], z20b[1], y20b[1];
double z21b[1], y21b[1], z22b[1], y22b[1], z23b[1], y23b[1];
double z24b[1], y24b[1], z25b[1], y25b[1], z26b[1], y26b[1];
double z27b[1], y27b[1], z28b[1], y28b[1], z29b[1], y29b[1];
double z30b[1], y30b[1], z31b[1], y31b[1], z32b[1], y32b[1];
double z33b[1], y33b[1], z34b[1], y34b[1], z35b[1], y35b[1];
double z36b[1], y36b[1], z37b[1], y37b[1], z38b[1], y38b[1];
double z39b[1], y39b[1], z40b[1], y40b[1], z41b[1], y41b[1];

	z0b[0] = isolation_simple[0][24];
	y0b[0] = isolation_simple[1][24];
	z1b[0] = isolation_simple_barrel[0][24];
	y1b[0] = isolation_simple_barrel[1][24];
	z2b[0] = isolation_simple_endcap[0][24];
	y2b[0] = isolation_simple_endcap[1][24];

	z3b[0] = isolation_effarea[0][24];
	y3b[0] = isolation_effarea[1][24];
	z4b[0] = isolation_effarea_barrel[0][24];
	y4b[0] = isolation_effarea_barrel[1][24];
	z5b[0] = isolation_effarea_endcap[0][24];
	y5b[0] = isolation_effarea_endcap[1][24];

	z6b[0] = isolation_deltabeta[0][24];
	y6b[0] = isolation_deltabeta[1][24];
	z7b[0] = isolation_deltabeta_barrel[0][24];
	y7b[0] = isolation_deltabeta_barrel[1][24];
	z8b[0] = isolation_deltabeta_endcap[0][24];
	y8b[0] = isolation_deltabeta_endcap[1][24];

	z9b[0] = sip[0][24];
	y9b[0] = sip[1][24];
	z10b[0] = sip_barrel[0][24];
	y10b[0] = sip_barrel[1][24];
	z11b[0] = sip_endcap[0][24];
	y11b[0] = sip_endcap[1][24];
	z12b[0] = bdt[0][24];
	y12b[0] = bdt[1][24];
	z13b[0] = bdt_barrel[0][24];
	y13b[0] = bdt_barrel[1][24];
	z14b[0] = bdt_endcap[0][24];
	y14b[0] = bdt_endcap[1][24];

	z15b[0] = isolation_simple_lowpu[0][24];
	y15b[0] = isolation_simple_lowpu[1][24];
	z16b[0] = isolation_simple_medpu[0][24];
	y16b[0] = isolation_simple_medpu[1][24];
	z17b[0] = isolation_simple_highpu[0][24];
	y17b[0] = isolation_simple_highpu[1][24];

	z18b[0] = isolation_effarea_lowpu[0][24];
	y18b[0] = isolation_effarea_lowpu[1][24];
	z19b[0] = isolation_effarea_medpu[0][24];
	y19b[0] = isolation_effarea_medpu[1][24];
	z20b[0] = isolation_effarea_highpu[0][24];
	y20b[0] = isolation_effarea_highpu[1][24];

	z21b[0] = isolation_deltabeta_lowpu[0][24];
	y21b[0] = isolation_deltabeta_lowpu[1][24];
	z22b[0] = isolation_deltabeta_medpu[0][24];
	y22b[0] = isolation_deltabeta_medpu[1][24];
	z23b[0] = isolation_deltabeta_highpu[0][24];
	y23b[0] = isolation_deltabeta_highpu[1][24];

	z24b[0] = isolation_puppi[0][24];
	y24b[0] = isolation_puppi[1][24];
	z25b[0] = isolation_puppi_barrel[0][24];
	y25b[0] = isolation_puppi_barrel[1][24];
	z26b[0] = isolation_puppi_endcap[0][24];
	y26b[0] = isolation_puppi_endcap[1][24];

	z27b[0] = isolation_puppinl[0][24];
	y27b[0] = isolation_puppinl[1][24];
	z28b[0] = isolation_puppinl_barrel[0][24];
	y28b[0] = isolation_puppinl_barrel[1][24];
	z29b[0] = isolation_puppinl_endcap[0][24];
	y29b[0] = isolation_puppinl_endcap[1][24];

	z30b[0] = isolation_citk[0][24];
	y30b[0] = isolation_citk[1][24];
	z31b[0] = isolation_citk_barrel[0][24];
	y31b[0] = isolation_citk_barrel[1][24];
	z32b[0] = isolation_citk_endcap[0][24];
	y32b[0] = isolation_citk_endcap[1][24];

	z33b[0] = isolation_puppi_lowpu[0][24];
	y33b[0] = isolation_puppi_lowpu[1][24];
	z34b[0] = isolation_puppi_medpu[0][24];
	y34b[0] = isolation_puppi_medpu[1][24];
	z35b[0] = isolation_puppi_highpu[0][24];
	y35b[0] = isolation_puppi_highpu[1][24];

	z36b[0] = isolation_puppinl_lowpu[0][24];
	y36b[0] = isolation_puppinl_lowpu[1][24];
	z37b[0] = isolation_puppinl_medpu[0][24];
	y37b[0] = isolation_puppinl_medpu[1][24];
	z38b[0] = isolation_puppinl_highpu[0][24];
	y38b[0] = isolation_puppinl_highpu[1][24];

	z39b[0] = isolation_citk_lowpu[0][24];
	y39b[0] = isolation_citk_lowpu[1][24];
	z40b[0] = isolation_citk_medpu[0][24];
	y40b[0] = isolation_citk_medpu[1][24];
	z41b[0] = isolation_citk_highpu[0][24];
	y41b[0] = isolation_citk_highpu[1][24];

for (int x=0; x<99; x++)
	{
	z0[x] = isolation_simple[0][x];
	y0[x] = isolation_simple[1][x];
	z1[x] = isolation_simple_barrel[0][x];
	y1[x] = isolation_simple_barrel[1][x];
	z2[x] = isolation_simple_endcap[0][x];
	y2[x] = isolation_simple_endcap[1][x];

	z3[x] = isolation_effarea[0][x];
	y3[x] = isolation_effarea[1][x];
	z4[x] = isolation_effarea_barrel[0][x];
	y4[x] = isolation_effarea_barrel[1][x];
	z5[x] = isolation_effarea_endcap[0][x];
	y5[x] = isolation_effarea_endcap[1][x];

	z6[x] = isolation_deltabeta[0][x];
	y6[x] = isolation_deltabeta[1][x];
	z7[x] = isolation_deltabeta_barrel[0][x];
	y7[x] = isolation_deltabeta_barrel[1][x];
	z8[x] = isolation_deltabeta_endcap[0][x];
	y8[x] = isolation_deltabeta_endcap[1][x];

	z9[x] = sip[0][x];
	y9[x] = sip[1][x];
	z10[x] = sip_barrel[0][x];
	y10[x] = sip_barrel[1][x];
	z11[x] = sip_endcap[0][x];
	y11[x] = sip_endcap[1][x];
	z12[x] = bdt[0][x];
	y12[x] = bdt[1][x];
	z13[x] = bdt_barrel[0][x];
	y13[x] = bdt_barrel[1][x];
	z14[x] = bdt_endcap[0][x];
	y14[x] = bdt_endcap[1][x];

	z15[x] = isolation_simple_lowpu[0][x];
	y15[x] = isolation_simple_lowpu[1][x];
	z16[x] = isolation_simple_medpu[0][x];
	y16[x] = isolation_simple_medpu[1][x];
	z17[x] = isolation_simple_highpu[0][x];
	y17[x] = isolation_simple_highpu[1][x];

	z18[x] = isolation_effarea_lowpu[0][x];
	y18[x] = isolation_effarea_lowpu[1][x];
	z19[x] = isolation_effarea_medpu[0][x];
	y19[x] = isolation_effarea_medpu[1][x];
	z20[x] = isolation_effarea_highpu[0][x];
	y20[x] = isolation_effarea_highpu[1][x];

	z21[x] = isolation_deltabeta_lowpu[0][x];
	y21[x] = isolation_deltabeta_lowpu[1][x];
	z22[x] = isolation_deltabeta_medpu[0][x];
	y22[x] = isolation_deltabeta_medpu[1][x];
	z23[x] = isolation_deltabeta_highpu[0][x];
	y23[x] = isolation_deltabeta_highpu[1][x];

	z24[x] = isolation_puppi[0][x];
	y24[x] = isolation_puppi[1][x];
	z25[x] = isolation_puppi_barrel[0][x];
	y25[x] = isolation_puppi_barrel[1][x];
	z26[x] = isolation_puppi_endcap[0][x];
	y26[x] = isolation_puppi_endcap[1][x];

	z27[x] = isolation_puppinl[0][x];
	y27[x] = isolation_puppinl[1][x];
	z28[x] = isolation_puppinl_barrel[0][x];
	y28[x] = isolation_puppinl_barrel[1][x];
	z29[x] = isolation_puppinl_endcap[0][x];
	y29[x] = isolation_puppinl_endcap[1][x];

	z30[x] = isolation_citk[0][x];
	y30[x] = isolation_citk[1][x];
	z31[x] = isolation_citk_barrel[0][x];
	y31[x] = isolation_citk_barrel[1][x];
	z32[x] = isolation_citk_endcap[0][x];
	y32[x] = isolation_citk_endcap[1][x];

	z33[x] = isolation_puppi_lowpu[0][x];
	y33[x] = isolation_puppi_lowpu[1][x];
	z34[x] = isolation_puppi_medpu[0][x];
	y34[x] = isolation_puppi_medpu[1][x];
	z35[x] = isolation_puppi_highpu[0][x];
	y35[x] = isolation_puppi_highpu[1][x];

	z36[x] = isolation_puppinl_lowpu[0][x];
	y36[x] = isolation_puppinl_lowpu[1][x];
	z37[x] = isolation_puppinl_medpu[0][x];
	y37[x] = isolation_puppinl_medpu[1][x];
	z38[x] = isolation_puppinl_highpu[0][x];
	y38[x] = isolation_puppinl_highpu[1][x];

	z39[x] = isolation_citk_lowpu[0][x];
	y39[x] = isolation_citk_lowpu[1][x];
	z40[x] = isolation_citk_medpu[0][x];
	y40[x] = isolation_citk_medpu[1][x];
	z41[x] = isolation_citk_highpu[0][x];
	y41[x] = isolation_citk_highpu[1][x];
	if (detail) { cout << "x = " << x << " - " << z4[x] << " - " << y4[x] << " - " << z6[x] << endl; }
	}
	
   //double temp;
	
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

   plot_six_dist(ele_pfiso_simple_pt_eff, "PF without PU subtraction", ele_pfiso_effarea_pt_eff, "Effective Area", ele_pfiso_deltabeta_pt_eff, "Delta Beta", ele_pfiso_puppi_pt_eff, "PUPPI", ele_pfiso_puppinl_pt_eff, "PUPPI No Leptons", ele_pfiso_citk_pt_eff, "CITK", "output/", "", "ele_pfiso_pt_eff", "bottom_right", false, false);

   plot_histogram(ele_pfiso_simple_pt_bkg, "output/","ele_pfiso_simple_pt_bkg", "Electron PF Isolation Simple pT", "bottom_right", false);
   plot_histogram(ele_pfiso_effarea_pt_bkg, "output/","ele_pfiso_effarea_pt_bkg", "Electron PF Isolation Effective Area pT", "bottom_right", false);
   plot_histogram(ele_pfiso_deltabeta_pt_bkg, "output/","ele_pfiso_deltabeta_pt_bkg", "Electron PF Isolation Delta Beta pT", "bottom_right", false);
   plot_histogram(ele_pfiso_puppi_pt_bkg, "output/","ele_pfiso_puppi_pt_bkg", "Electron PF Isolation PUPPI pT", "bottom_right", false);
   plot_histogram(ele_pfiso_puppinl_pt_bkg, "output/","ele_pfiso_puppinl_pt_bkg", "Electron PF Isolation PUPPI No Lepton pT", "bottom_right", false);
   plot_histogram(ele_pfiso_citk_pt_bkg, "output/","ele_pfiso_citk_pt_bkg", "Electron PF Isolation CITK pT", "bottom_right", false);

   plot_six_dist(ele_pfiso_simple_pt_bkg, "PF without PU subtraction", ele_pfiso_effarea_pt_bkg, "Effective Area", ele_pfiso_deltabeta_pt_bkg, "Delta Beta", ele_pfiso_puppi_pt_bkg, "PUPPI", ele_pfiso_puppinl_pt_bkg, "PUPPI No Leptons", ele_pfiso_citk_pt_bkg, "CITK", "output/", "", "ele_pfiso_pt_bkg", "bottom_right", false, false);

   plot_histogram(ele_pfiso_simple_pt_ratio, "output/","ele_pfiso_simple_pt_ratio", "Electron PF Isolation Simple pT", "top_right", false);
   plot_histogram(ele_pfiso_effarea_pt_ratio, "output/","ele_pfiso_effarea_pt_ratio", "Electron PF Isolation Effective Area pT", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_pt_ratio, "output/","ele_pfiso_deltabeta_pt_ratio", "Electron PF Isolation Delta Beta pT", "top_right", false);
   plot_histogram(ele_pfiso_puppi_pt_ratio, "output/","ele_pfiso_puppi_pt_ratio", "Electron PF Isolation PUPPI pT", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_pt_ratio, "output/","ele_pfiso_puppinl_pt_ratio", "Electron PF Isolation PUPPI No Lepton pT", "top_right", false);
   plot_histogram(ele_pfiso_citk_pt_ratio, "output/","ele_pfiso_citk_pt_ratio", "Electron PF Isolation CITK pT", "top_right", false);

   plot_six_dist(ele_pfiso_simple_pt_ratio, "PF without PU subtraction", ele_pfiso_effarea_pt_ratio, "Effective Area", ele_pfiso_deltabeta_pt_ratio, "Delta Beta", ele_pfiso_puppi_pt_ratio, "PUPPI", ele_pfiso_puppinl_pt_ratio, "PUPPI No Leptons", ele_pfiso_citk_pt_ratio, "CITK", "output/", "", "ele_pfiso_pt_ratio", "top_right", false, false);

   for (int x=0; x<=21; x++)
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

   plot_six_dist(ele_pfiso_simple_vtx_ratio, "PF without PU subtraction", ele_pfiso_effarea_vtx_ratio, "Effective Area", ele_pfiso_deltabeta_vtx_ratio, "Delta Beta", ele_pfiso_puppi_vtx_ratio, "PUPPI", ele_pfiso_puppinl_vtx_ratio, "PUPPI No Leptons", ele_pfiso_citk_vtx_ratio, "CITK", "output/", "", "ele_pfiso_vtx_ratio", "top_right", false, false);

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

   plot_six_dist(ele_pfiso_simple_eta_bkg, "PF without PU subtraction", ele_pfiso_effarea_eta_bkg, "Effective Area", ele_pfiso_deltabeta_eta_bkg, "Delta Beta", ele_pfiso_puppi_eta_bkg, "PUPPI", ele_pfiso_puppinl_eta_bkg, "PUPPI No Leptons", ele_pfiso_citk_eta_bkg, "CITK", "output/", "", "ele_pfiso_eta_bkg", "top_right", false, false);

   plot_histogram(ele_pfiso_simple_eta_ratio, "output/","ele_pfiso_simple_eta_ratio", "Electron PF Isolation Simple Eta", "top_right", false);
   plot_histogram(ele_pfiso_effarea_eta_ratio, "output/","ele_pfiso_effarea_eta_ratio", "Electron PF Isolation Effective Area Eta", "top_right", false);
   plot_histogram(ele_pfiso_deltabeta_eta_ratio, "output/","ele_pfiso_deltabeta_eta_ratio", "Electron PF Isolation Delta Beta Eta", "top_right", false);
   plot_histogram(ele_pfiso_puppi_eta_ratio, "output/","ele_pfiso_puppi_eta_ratio", "Electron PF Isolation PUPPI Eta", "top_right", false);
   plot_histogram(ele_pfiso_puppinl_eta_ratio, "output/","ele_pfiso_puppinl_eta_ratio", "Electron PF Isolation PUPPI No Leptons Eta", "top_right", false);
   plot_histogram(ele_pfiso_citk_eta_ratio, "output/","ele_pfiso_citk_eta_ratio", "Electron PF Isolation CITK Eta", "top_right", false);

   plot_six_dist(ele_pfiso_simple_eta_ratio, "PF without PU subtraction", ele_pfiso_effarea_eta_ratio, "Effective Area", ele_pfiso_deltabeta_eta_ratio, "Delta Beta", ele_pfiso_puppi_eta_ratio, "PUPPI", ele_pfiso_puppinl_eta_ratio, "PUPPI No Leptons", ele_pfiso_citk_eta_ratio, "CITK", "output/", "", "ele_pfiso_eta_ratio", "top_right", false, false);

   TCanvas *c1 = new TCanvas("c1","Electron Isolation Simple",200,10,700,500);
   TGraph *gr0 = new TGraph(99,z0,y0);
   TGraph *gr0b = new TGraph(1,z0b,y0b);
   gr0->Draw("AL");
   gr0->SetLineWidth(2);
   gr0->GetYaxis()->SetRangeUser(0.8,1.0);
   gr0->GetXaxis()->SetRangeUser(0.0,1.0);
   gr0->GetXaxis()->SetTitle("Background Efficiency");
   gr0->GetYaxis()->SetTitle("Signal Efficiency");
   gr0b->Draw("*");
   gr0b->SetMarkerStyle(21);
   gr0b->SetMarkerSize(2);
   print_plots(c1, "output/", "electron_isolation_simple");

   TCanvas *c2 = new TCanvas("c2","Electron Isolation Simple Barrel",200,10,700,500);
   TGraph *gr1 = new TGraph(99,z1,y1);
   TGraph *gr1b = new TGraph(1,z1b,y1b);
   gr1->Draw("AL");
   gr1->SetLineWidth(2);
   gr1->GetYaxis()->SetRangeUser(0.8,1.0);
   gr1->GetXaxis()->SetRangeUser(0.0,1.0);
   gr1->GetXaxis()->SetTitle("Background Efficiency");
   gr1->GetYaxis()->SetTitle("Signal Efficiency");
   gr1b->Draw("*");
   gr1b->SetMarkerStyle(21);
   gr1b->SetMarkerSize(2);
   print_plots(c2, "output/", "electron_isolation_simple_barrel");

   TCanvas *c3 = new TCanvas("c3","Electron Isolation Simple Endcap",200,10,700,500);
   TGraph *gr2 = new TGraph(99,z2,y2);
   TGraph *gr2b = new TGraph(1,z2b,y2b);
   gr2->Draw("AL");
   gr2->SetLineWidth(2);
   gr2->GetYaxis()->SetRangeUser(0.8,1.0);
   gr2->GetXaxis()->SetRangeUser(0.0,1.0);
   gr2->GetXaxis()->SetTitle("Background Efficiency");
   gr2->GetYaxis()->SetTitle("Signal Efficiency");
   gr2b->Draw("*");
   gr2b->SetMarkerStyle(21);
   gr2b->SetMarkerSize(2);
   print_plots(c3, "output/", "electron_isolation_simple_endcap");

   TCanvas *c4 = new TCanvas("c4","Electron Isolation Simple All",200,10,700,500);
   gr0->Draw("AL");
   gr0b->Draw("*");
   gr0b->SetMarkerStyle(21);
   gr0b->SetMarkerSize(2);
   gr1->Draw("L");
   gr1->SetLineColor(2);
   gr1b->Draw("*");
   gr1b->SetMarkerColor(2);
   gr1b->SetMarkerStyle(21);
   gr1b->SetMarkerSize(2);
   gr2->Draw("L");
   gr2->SetLineColor(4);
   gr2b->Draw("*");
   gr2b->SetMarkerColor(4);
   gr2b->SetMarkerStyle(21);
   gr2b->SetMarkerSize(2);
   print_plots(c4, "output/", "electron_isolation_simple_all");


   TCanvas *c5 = new TCanvas("c5","Electron Isolation Effective Area",200,10,700,500);
   TGraph *gr3 = new TGraph(99,z3,y3);
   TGraph *gr3b = new TGraph(1,z3b,y3b);
   gr3->Draw("AL");
   gr3->SetLineWidth(2);
   gr3->GetYaxis()->SetRangeUser(0.8,1.0);
   gr3->GetXaxis()->SetRangeUser(0.0,1.0);
   gr3->GetXaxis()->SetTitle("Background Efficiency");
   gr3->GetYaxis()->SetTitle("Signal Efficiency");
   gr3b->Draw("*");
   gr3b->SetMarkerStyle(21);
   gr3b->SetMarkerSize(2);
   print_plots(c5, "output/", "electron_isolation_effarea");

   TCanvas *c6 = new TCanvas("c6","Electron Isolation Effective Area Barrel",200,10,700,500);
   TGraph *gr4 = new TGraph(99,z4,y4);
   TGraph *gr4b = new TGraph(1,z4b,y4b);
   gr4->Draw("AL");
   gr4->SetLineWidth(2);
   gr4->GetYaxis()->SetRangeUser(0.8,1.0);
   gr4->GetXaxis()->SetRangeUser(0.0,1.0);
   gr4->GetXaxis()->SetTitle("Background Efficiency");
   gr4->GetYaxis()->SetTitle("Signal Efficiency");
   gr4b->Draw("*");
   gr4b->SetMarkerStyle(21);
   gr4b->SetMarkerSize(2);
   print_plots(c6, "output/", "electron_isolation_effarea_barrel");

   TCanvas *c7 = new TCanvas("c3","Electron Isolation Effective Area Endcap",200,10,700,500);
   TGraph *gr5 = new TGraph(99,z5,y5);
   TGraph *gr5b = new TGraph(1,z5b,y5b);
   gr5->Draw("AL");
   gr5->SetLineWidth(2);
   gr5->GetYaxis()->SetRangeUser(0.8,1.0);
   gr5->GetXaxis()->SetRangeUser(0.0,1.0);
   gr5->GetXaxis()->SetTitle("Background Efficiency");
   gr5->GetYaxis()->SetTitle("Signal Efficiency");
   gr5b->Draw("*");
   gr5b->SetMarkerStyle(21);
   gr5b->SetMarkerSize(2);
   print_plots(c7, "output/", "electron_isolation_effarea_endcap");

   TCanvas *c8 = new TCanvas("c8","Electron Isolation Effective Area All",200,10,700,500);
   gr3->Draw("AL");
   gr3b->Draw("*");
   gr3b->SetMarkerStyle(21);
   gr3b->SetMarkerSize(2);
   gr4->Draw("L");
   gr4->SetLineColor(2);
   gr4b->SetMarkerColor(2);
   gr4b->Draw("*");
   gr4b->SetMarkerStyle(21);
   gr4b->SetMarkerSize(2);   
   gr5->Draw("L");
   gr5->SetLineColor(4);
   gr5b->SetMarkerColor(4);
   gr5b->Draw("*");
   gr5b->SetMarkerStyle(21);
   gr5b->SetMarkerSize(2);
   print_plots(c8, "output/", "electron_isolation_effarea_all");


   TCanvas *c9 = new TCanvas("c9","Electron Isolation Delta Eta",200,10,700,500);
   TGraph *gr6 = new TGraph(99,z6,y6);
   TGraph *gr6b = new TGraph(1,z6b,y6b);
   gr6->Draw("AL");
   gr6->SetLineWidth(2);
   gr6->GetYaxis()->SetRangeUser(0.8,1.0);
   gr6->GetXaxis()->SetRangeUser(0.0,1.0);
   gr6->GetXaxis()->SetTitle("Background Efficiency");
   gr6->GetYaxis()->SetTitle("Signal Efficiency");
   gr6b->Draw("*");
   gr6b->SetMarkerStyle(21);
   gr6b->SetMarkerSize(2);
   print_plots(c9, "output/", "electron_isolation_deltabeta");

   TCanvas *c10 = new TCanvas("c10","Electron Isolation Delta Eta Barrel",200,10,700,500);
   TGraph *gr7 = new TGraph(99,z7,y7);
   TGraph *gr7b = new TGraph(1,z7b,y7b);
   gr7->Draw("AL");
   gr7->SetLineWidth(2);
   gr7->GetYaxis()->SetRangeUser(0.8,1.0);
   gr7->GetXaxis()->SetRangeUser(0.0,1.0);
   gr7->GetXaxis()->SetTitle("Background Efficiency");
   gr7->GetYaxis()->SetTitle("Signal Efficiency");
   gr7b->Draw("*");
   gr7b->SetMarkerStyle(21);
   gr7b->SetMarkerSize(2);
   print_plots(c10, "output/", "electron_isolation_deltabeta_barrel");

   TCanvas *c11 = new TCanvas("c11","Electron Isolation Delta Eta Endcap",200,10,700,500);
   TGraph *gr8 = new TGraph(99,z8,y8);
   TGraph *gr8b = new TGraph(1,z8b,y8b);
   gr8->Draw("AL");
   gr8->SetLineWidth(2);
   gr8->GetYaxis()->SetRangeUser(0.8,1.0);
   gr8->GetXaxis()->SetRangeUser(0.0,1.0);
   gr8->GetXaxis()->SetTitle("Background Efficiency");
   gr8->GetYaxis()->SetTitle("Signal Efficiency");
   gr8b->Draw("*");
   gr8b->SetMarkerStyle(21);
   gr8b->SetMarkerSize(2);
   print_plots(c11, "output/", "electron_isolation_deltabeta_endcap");


   TCanvas *c12 = new TCanvas("c12","Electron Isolation Delta Eta All",200,10,700,500);
   gr6->Draw("AL");
   gr6b->Draw("*");
   gr6b->SetMarkerStyle(21);
   gr6b->SetMarkerSize(2);
   gr7->Draw("L");
   gr7->SetLineColor(2);
   gr7b->Draw("*");
   gr7b->SetMarkerStyle(21);
   gr7b->SetMarkerSize(2);
   gr7b->SetMarkerColor(2);
   gr8->Draw("L");
   gr8->SetLineColor(4);
   gr8b->Draw("*");
   gr8b->SetMarkerStyle(21);
   gr8b->SetMarkerSize(2);
   gr8b->SetMarkerColor(4);
   print_plots(c12, "output/", "electron_isolation_deltabeta_all");


   TCanvas *c13 = new TCanvas("c13","SIP",200,10,700,500);
   TGraph *gr9 = new TGraph(99,z9,y9);
   TGraph *gr9b = new TGraph(1,z9b,y9b);
   gr9->Draw("AL");
   gr9->SetLineWidth(2);
   gr9->GetYaxis()->SetRangeUser(0.8,1.0);
   gr9->GetXaxis()->SetRangeUser(0.6,1.0);
   gr9->GetXaxis()->SetTitle("Background Efficiency");
   gr9->GetYaxis()->SetTitle("Signal Efficiency");
   gr9b->Draw("*");
   gr9b->SetMarkerStyle(21);
   gr9b->SetMarkerSize(2);
   print_plots(c13, "output/", "sip");

   TCanvas *c14 = new TCanvas("c14","SIP Barrel",200,10,700,500);
   TGraph *gr10 = new TGraph(99,z10,y10);
   TGraph *gr10b = new TGraph(1,z10b,y10b);
   gr10->Draw("AL");
   gr10->SetLineWidth(2);
   gr10->GetYaxis()->SetRangeUser(0.8,1.0);
   gr10->GetXaxis()->SetRangeUser(0.6,1.0);
   gr10->GetXaxis()->SetTitle("Background Efficiency");
   gr10->GetYaxis()->SetTitle("Signal Efficiency");
   gr10b->Draw("*");
   gr10b->SetMarkerStyle(21);
   gr10b->SetMarkerSize(2);
   print_plots(c14, "output/", "sip_barrel");

   TCanvas *c15 = new TCanvas("c15","SIP Endcap",200,10,700,500);
   TGraph *gr11 = new TGraph(99,z11,y11);
   TGraph *gr11b = new TGraph(1,z11b,y11b);
   gr11->Draw("AL");
   gr11->SetLineWidth(2);
   gr11->GetYaxis()->SetRangeUser(0.8,1.0);
   gr11->GetXaxis()->SetRangeUser(0.6,1.0);
   gr11->GetXaxis()->SetTitle("Background Efficiency");
   gr11->GetYaxis()->SetTitle("Signal Efficiency");
   gr11b->Draw("*");
   gr11b->SetMarkerStyle(21);
   gr11b->SetMarkerSize(2);
   print_plots(c15, "output/", "sip_endcap");

   TCanvas *c16 = new TCanvas("c16","SIP All",200,10,700,500);
   gr9->Draw("AL");
   gr9->SetLineWidth(2);
   gr9b->Draw("*");
   gr9b->SetMarkerStyle(21);
   gr9b->SetMarkerSize(2);
   gr10->Draw("L");
   gr10->SetLineColor(2);
   gr10->SetLineWidth(2);
   gr10b->Draw("*");
   gr10b->SetMarkerStyle(21);
   gr10b->SetMarkerSize(2);
   gr10b->SetMarkerColor(2);
   gr11->Draw("L");
   gr11->SetLineColor(4);
   gr11->SetLineWidth(2);
   gr11b->Draw("*");
   gr11b->SetMarkerStyle(21);
   gr11b->SetMarkerSize(2);
   gr11b->SetMarkerColor(4);
   print_plots(c16, "output/", "sip_all");

   TCanvas *c17 = new TCanvas("c17","BDT",200,10,700,500);
   TGraph *gr12 = new TGraph(99,z12,y12);
   TGraph *gr12b = new TGraph(1,z12b,y12b);
   gr12->Draw("AL");
   gr12->SetLineWidth(2);
   gr12->GetYaxis()->SetRangeUser(0.8,1.0);
   gr12->GetXaxis()->SetRangeUser(0.0,1.0);
   gr12->GetXaxis()->SetTitle("Background Efficiency");
   gr12->GetYaxis()->SetTitle("Signal Efficiency");
   gr12b->Draw("*");
   gr12b->SetMarkerStyle(21);
   gr12b->SetMarkerSize(2);
   print_plots(c17, "output/", "bdt");

   TCanvas *c18 = new TCanvas("c18","BDT Barrel",200,10,700,500);
   TGraph *gr13 = new TGraph(99,z13,y13);
   TGraph *gr13b = new TGraph(1,z13b,y13b);
   gr13->Draw("AL");
   gr13->SetLineWidth(2);
   gr13->GetYaxis()->SetRangeUser(0.8,1.0);
   gr13->GetXaxis()->SetRangeUser(0.0,1.0);
   gr13->GetXaxis()->SetTitle("Background Efficiency");
   gr13->GetYaxis()->SetTitle("Signal Efficiency");
   gr13b->Draw("*");
   gr13b->SetMarkerStyle(21);
   gr13b->SetMarkerSize(2);
   print_plots(c18, "output/", "bdt_barrel");

   TCanvas *c19 = new TCanvas("c19","BDT Endcap",200,10,700,500);
   TGraph *gr14 = new TGraph(99,z14,y14);
   TGraph *gr14b = new TGraph(1,z14b,y14b);
   gr14->Draw("AL");
   gr14->SetLineWidth(2);
   gr14->GetYaxis()->SetRangeUser(0.8,1.0);
   gr14->GetXaxis()->SetRangeUser(0.0,1.0);
   gr14->GetXaxis()->SetTitle("Background Efficiency");
   gr14->GetYaxis()->SetTitle("Signal Efficiency");
   gr14b->Draw("*");
   gr14b->SetMarkerStyle(21);
   gr14b->SetMarkerSize(2);
   print_plots(c19, "output/", "bdt_endcap");

   TCanvas *c20 = new TCanvas("c20","BDT All",200,10,700,500);
   gr12->Draw("AL");
   gr12->SetLineWidth(2);
   gr12b->Draw("*");
   gr12b->SetMarkerStyle(21);
   gr12b->SetMarkerSize(2);
   gr13->Draw("L");
   gr13->SetLineWidth(2);
   gr13->SetLineColor(2);
   gr13b->Draw("*");
   gr13b->SetMarkerStyle(21);
   gr13b->SetMarkerSize(2);
   gr13b->SetMarkerColor(2);
   gr14->Draw("L");
   gr14->SetLineWidth(2);
   gr14->SetLineColor(4);
   gr14b->Draw("*");
   gr14b->SetMarkerStyle(21);
   gr14b->SetMarkerSize(2);
   gr14b->SetMarkerColor(4);
   print_plots(c20, "output/", "bdt_all");

   TCanvas *c24 = new TCanvas("c24","Electron Isolation Simple Low Pile-Up",200,10,700,500);
   TGraph *gr15 = new TGraph(99,z15,y15);
   TGraph *gr15b = new TGraph(1,z15b,y15b);
   gr15->Draw("AL");
   gr15->SetLineWidth(2);
   gr15->GetYaxis()->SetRangeUser(0.8,1.0);
   gr15->GetXaxis()->SetRangeUser(0.0,1.0);
   gr15->GetXaxis()->SetTitle("Background Efficiency");
   gr15->GetYaxis()->SetTitle("Signal Efficiency");
   gr15b->Draw("*");
   gr15b->SetMarkerStyle(21);
   gr15b->SetMarkerSize(2);
   print_plots(c24, "output/", "electron_isolation_simple_lowpu");

   TCanvas *c25 = new TCanvas("c25","Electron Isolation Simple Medium Pile-Up",200,10,700,500);
   TGraph *gr16 = new TGraph(99,z16,y16);
   TGraph *gr16b = new TGraph(1,z16b,y16b);
   gr16->Draw("AL");
   gr16->SetLineWidth(2);
   gr16->GetYaxis()->SetRangeUser(0.8,1.0);
   gr16->GetXaxis()->SetRangeUser(0.0,1.0);
   gr16->GetXaxis()->SetTitle("Background Efficiency");
   gr16->GetYaxis()->SetTitle("Signal Efficiency");
   gr16b->Draw("*");
   gr16b->SetMarkerStyle(21);
   gr16b->SetMarkerSize(2);
   print_plots(c25, "output/", "electron_isolation_simple_medpu");

   TCanvas *c26 = new TCanvas("c26","Electron Isolation Simple High Pile-Up",200,10,700,500);
   TGraph *gr17 = new TGraph(99,z17,y17);
   TGraph *gr17b = new TGraph(1,z17b,y17b);
   gr17->Draw("AL");
   gr17->SetLineWidth(2);
   gr17->GetYaxis()->SetRangeUser(0.8,1.0);
   gr17->GetXaxis()->SetRangeUser(0.0,1.0);
   gr17->GetXaxis()->SetTitle("Background Efficiency");
   gr17->GetYaxis()->SetTitle("Signal Efficiency");
   gr17b->Draw("*");
   gr17b->SetMarkerStyle(21);
   gr17b->SetMarkerSize(2);
   print_plots(c26, "output/", "electron_isolation_simple_highpu");

   TCanvas *c27 = new TCanvas("c27","Electron Isolation Simple Pile-Up Scenarios",200,10,700,500);
   gr15->Draw("AL");
   gr15->SetLineWidth(2);
   gr15b->Draw("*");
   gr15b->SetMarkerStyle(21);
   gr15b->SetMarkerSize(2);
   gr16->Draw("L");
   gr16->SetLineWidth(2);
   gr16->SetLineColor(2);
   gr16b->Draw("*");
   gr16b->SetMarkerStyle(21);
   gr16b->SetMarkerSize(2);
   gr16b->SetMarkerColor(2);
   gr17->Draw("L");
   gr17->SetLineWidth(2);
   gr17->SetLineColor(4);
   gr17b->Draw("*");
   gr17b->SetMarkerStyle(21);
   gr17b->SetMarkerSize(2);
   gr17b->SetMarkerColor(4);
   print_plots(c27, "output/", "electron_isolation_simple_pu_scenarios");


   TCanvas *c28 = new TCanvas("c28","Electron Isolation Eff Area Low Pile-Up",200,10,700,500);
   TGraph *gr18 = new TGraph(99,z18,y18);
   TGraph *gr18b = new TGraph(1,z18b,y18b);
   gr18->Draw("AL");
   gr18->SetLineWidth(2);
   gr18->GetYaxis()->SetRangeUser(0.8,1.0);
   gr18->GetXaxis()->SetRangeUser(0.0,1.0);
   gr18->GetXaxis()->SetTitle("Background Efficiency");
   gr18->GetYaxis()->SetTitle("Signal Efficiency");
   gr18b->Draw("*");
   gr18b->SetMarkerStyle(21);
   gr18b->SetMarkerSize(2);
   print_plots(c28, "output/", "electron_isolation_effarea_lowpu");

   TCanvas *c29 = new TCanvas("c29","Electron Isolation Eff Area Medium Pile-Up",200,10,700,500);
   TGraph *gr19 = new TGraph(99,z19,y19);
   TGraph *gr19b = new TGraph(1,z19b,y19b);
   gr19->Draw("AL");
   gr19->SetLineWidth(2);
   gr19->GetYaxis()->SetRangeUser(0.8,1.0);
   gr19->GetXaxis()->SetRangeUser(0.0,1.0);
   gr19->GetXaxis()->SetTitle("Background Efficiency");
   gr19->GetYaxis()->SetTitle("Signal Efficiency");
   gr19b->Draw("*");
   gr19b->SetMarkerStyle(21);
   gr19b->SetMarkerSize(2);
   print_plots(c29, "output/", "electron_isolation_effarea_medpu");

   TCanvas *c30 = new TCanvas("c30","Electron Isolation Eff Area High Pile-Up",200,10,700,500);
   TGraph *gr20 = new TGraph(99,z20,y20);
   TGraph *gr20b = new TGraph(1,z20b,y20b);
   gr20->Draw("AL");
   gr20->SetLineWidth(2);
   gr20->GetYaxis()->SetRangeUser(0.8,1.0);
   gr20->GetXaxis()->SetRangeUser(0.0,1.0);
   gr20->GetXaxis()->SetTitle("Background Efficiency");
   gr20->GetYaxis()->SetTitle("Signal Efficiency");
   gr20b->Draw("*");
   gr20b->SetMarkerStyle(21);
   gr20b->SetMarkerSize(2);
   print_plots(c30, "output/", "electron_isolation_effarea_highpu");

   TCanvas *c31 = new TCanvas("c31","Electron Isolation Eff Area Pile-Up Scenarios",200,10,700,500);
   gr18->Draw("AL");
   gr19->Draw("L");
   gr19->SetLineColor(2);
   gr19->SetMarkerColor(2);
   gr20->Draw("L");
   gr20->SetLineColor(4);
   gr20->SetMarkerColor(4);
   print_plots(c31, "output/", "electron_isolation_effarea_pu_scenarios");

   TCanvas *c32 = new TCanvas("c32","Electron Isolation DeltaBeta Low Pile-Up",200,10,700,500);
   TGraph *gr21 = new TGraph(99,z21,y21);
   gr21->Draw("AL");
   gr21->GetYaxis()->SetRangeUser(0.9,1.0);
   gr21->GetXaxis()->SetRangeUser(0.0,1.0);
   gr21->GetXaxis()->SetTitle("Background Efficiency");
   gr21->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c32, "output/", "electron_isolation_deltabeta_lowpu");

   TCanvas *c33 = new TCanvas("c33","Electron Isolation Delta Beta Medium Pile-Up",200,10,700,500);
   TGraph *gr22 = new TGraph(99,z22,y22);
   gr22->Draw("AL");
   gr22->GetYaxis()->SetRangeUser(0.9,1.0);
   gr22->GetXaxis()->SetRangeUser(0.0,1.0);
   gr22->GetXaxis()->SetTitle("Background Efficiency");
   gr22->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c33, "output/", "electron_isolation_deltabeta_medpu");

   TCanvas *c34 = new TCanvas("c34","Electron Isolation Delta Beta High Pile-Up",200,10,700,500);
   TGraph *gr23 = new TGraph(99,z23,y23);
   gr23->Draw("AL");
   gr23->GetYaxis()->SetRangeUser(0.9,1.0);
   gr23->GetXaxis()->SetRangeUser(0.0,1.0);
   gr23->GetXaxis()->SetTitle("Background Efficiency");
   gr23->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c34, "output/", "electron_isolation_deltabeta_highpu");

   TCanvas *c35 = new TCanvas("c35","Electron Isolation Delta Beta Pile-Up Scenarios",200,10,700,500);
   gr21->Draw("AL");
   gr22->Draw("L");
   gr22->SetLineColor(2);
   gr22->SetMarkerColor(2);
   gr23->Draw("L");
   gr23->SetLineColor(4);
   gr23->SetMarkerColor(4);
   print_plots(c35, "output/", "electron_isolation_deltabeta_pu_scenarios");

   TCanvas *c39 = new TCanvas("c39","Electron Isolation PUPPI",200,10,700,500);
   TGraph *gr24 = new TGraph(99,z24,y24);
   gr24->Draw("AL");
   gr24->GetYaxis()->SetRangeUser(0.9,1.0);
   gr24->GetXaxis()->SetRangeUser(0.0,1.0);
   gr24->GetXaxis()->SetTitle("Background Efficiency");
   gr24->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c39, "output/", "electron_isolation_puppi");

   TCanvas *c40 = new TCanvas("c40","Electron Isolation PUPPI Barrel",200,10,700,500);
   TGraph *gr25 = new TGraph(99,z25,y25);
   gr25->Draw("AL");
   gr25->GetYaxis()->SetRangeUser(0.9,1.0);
   gr25->GetXaxis()->SetRangeUser(0.0,1.0);
   gr25->GetXaxis()->SetTitle("Background Efficiency");
   gr25->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c40, "output/", "electron_isolation_puppi_barrel");

   TCanvas *c41 = new TCanvas("c41","Electron Isolation PUPPI Endcap",200,10,700,500);
   TGraph *gr26 = new TGraph(99,z26,y26);
   gr26->Draw("AL");
   gr26->GetYaxis()->SetRangeUser(0.9,1.0);
   gr26->GetXaxis()->SetRangeUser(0.0,1.0);
   gr26->GetXaxis()->SetTitle("Background Efficiency");
   gr26->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c41, "output/", "electron_isolation_puppi_endcap");

   TCanvas *c42 = new TCanvas("c42","Electron Isolation PUPPI All",200,10,700,500);
   gr24->Draw("AL");
   gr25->Draw("L");
   gr25->SetLineColor(2);
   gr25->SetMarkerColor(2);
   gr26->Draw("L");
   gr26->SetLineColor(4);
   gr26->SetMarkerColor(4);
   print_plots(c42, "output/", "electron_isolation_puppi_all");

   TCanvas *c43 = new TCanvas("c43","Electron Isolation PUPPI No Leptons",200,10,700,500);
   TGraph *gr27 = new TGraph(99,z27,y27);
   gr27->Draw("AL");
   gr27->GetYaxis()->SetRangeUser(0.9,1.0);
   gr27->GetXaxis()->SetRangeUser(0.0,1.0);
   gr27->GetXaxis()->SetTitle("Background Efficiency");
   gr27->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c43, "output/", "electron_isolation_puppinl");

   TCanvas *c44 = new TCanvas("c44","Electron Isolation PUPPI No Leptons Barrel",200,10,700,500);
   TGraph *gr28 = new TGraph(99,z28,y28);
   gr28->Draw("AL");
   gr28->GetYaxis()->SetRangeUser(0.9,1.0);
   gr28->GetXaxis()->SetRangeUser(0.0,1.0);
   gr28->GetXaxis()->SetTitle("Background Efficiency");
   gr28->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c44, "output/", "electron_isolation_puppinl_barrel");

   TCanvas *c45 = new TCanvas("c45","Electron Isolation PUPPI No Leptons Endcap",200,10,700,500);
   TGraph *gr29 = new TGraph(99,z29,y29);
   gr29->Draw("AL");
   gr29->GetYaxis()->SetRangeUser(0.9,1.0);
   gr29->GetXaxis()->SetRangeUser(0.0,1.0);
   gr29->GetXaxis()->SetTitle("Background Efficiency");
   gr29->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c45, "output/", "electron_isolation_puppinl_endcap");

   TCanvas *c46 = new TCanvas("c46","Electron Isolation PUPPI No Leptons All",200,10,700,500);
   gr27->Draw("AL");
   gr28->Draw("L");
   gr28->SetLineColor(2);
   gr28->SetMarkerColor(2);
   gr29->Draw("L");
   gr29->SetLineColor(4);
   gr29->SetMarkerColor(4);
   print_plots(c46, "output/", "electron_isolation_puppinl_all");

   TCanvas *c47 = new TCanvas("c47","Electron Isolation CITK",200,10,700,500);
   TGraph *gr30 = new TGraph(99,z30,y30);
   gr30->Draw("AL");
   gr30->GetYaxis()->SetRangeUser(0.9,1.0);
   gr30->GetXaxis()->SetRangeUser(0.0,1.0);
   gr30->GetXaxis()->SetTitle("Background Efficiency");
   gr30->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c47, "output/", "electron_isolation_citk");

   TCanvas *c48 = new TCanvas("c48","Electron Isolation CITK No Leptons Barrel",200,10,700,500);
   TGraph *gr31 = new TGraph(99,z31,y31);
   gr31->Draw("AL");
   gr31->GetYaxis()->SetRangeUser(0.9,1.0);
   gr31->GetXaxis()->SetRangeUser(0.0,1.0);
   gr31->GetXaxis()->SetTitle("Background Efficiency");
   gr31->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c48, "output/", "electron_isolation_citk_barrel");

   TCanvas *c49 = new TCanvas("c49","Electron Isolation CITK Endcap",200,10,700,500);
   TGraph *gr32 = new TGraph(99,z32,y32);
   gr32->Draw("AL");
   gr32->GetYaxis()->SetRangeUser(0.9,1.0);
   gr32->GetXaxis()->SetRangeUser(0.0,1.0);
   gr32->GetXaxis()->SetTitle("Background Efficiency");
   gr32->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c49, "output/", "electron_isolation_citk_endcap");

   TCanvas *c50 = new TCanvas("c50","Electron Isolation CITK All",200,10,700,500);
   gr30->Draw("AL");
   gr31->Draw("L");
   gr31->SetLineColor(2);
   gr31->SetMarkerColor(2);
   gr32->Draw("L");
   gr32->SetLineColor(4);
   gr32->SetMarkerColor(4);
   print_plots(c50, "output/", "electron_isolation_citk_all");

   TCanvas *c51 = new TCanvas("c51","Methods All",200,10,700,500);
   gr0->Draw("AL");
   gr0->SetLineColor(1);
   gr0->SetMarkerColor(1);
   gr3->Draw("L");
   gr3->SetLineColor(2);
   gr3->SetMarkerColor(2);
   gr6->Draw("L");
   gr6->SetLineColor(4);
   gr6->SetMarkerColor(4);
   gr24->Draw("L");
   gr24->SetLineColor(3);
   gr24->SetMarkerColor(3);
   gr27->Draw("LP");
   gr27->SetLineColor(6);
   gr27->SetMarkerColor(6);
   gr27->SetMarkerStyle(21);
   gr30->Draw("L");
   gr30->SetLineColor(6);
   gr30->SetMarkerColor(6);

   print_plots(c51, "output/", "methods_all");

   TCanvas *c52 = new TCanvas("c52","Methods Barrel",200,10,700,500);
   gr1->Draw("AL");
   gr1->SetLineColor(1);
   gr1->SetMarkerColor(1);
   gr4->Draw("L");
   gr4->SetLineColor(2);
   gr4->SetMarkerColor(2);
   gr7->Draw("L");
   gr7->SetLineColor(4);
   gr7->SetMarkerColor(4);
   gr25->Draw("L");
   gr25->SetLineColor(3);
   gr25->SetMarkerColor(3);
   gr28->Draw("L");
   gr28->SetLineColor(5);
   gr28->SetMarkerColor(5);
   gr31->Draw("L");
   gr31->SetLineColor(6);
   gr31->SetMarkerColor(6);
   print_plots(c52, "output/", "methods_barrel");

   TCanvas *c53 = new TCanvas("c53","Methods EndCap",200,10,700,500);
   gr2->Draw("AL");
   gr2->SetLineColor(1);
   gr2->SetMarkerColor(1);
   gr5->Draw("L");
   gr5->SetLineColor(2);
   gr5->SetMarkerColor(2);
   gr8->Draw("L");
   gr8->SetLineColor(4);
   gr8->SetMarkerColor(4);
   gr26->Draw("L");
   gr26->SetLineColor(3);
   gr26->SetMarkerColor(3);
   gr29->Draw("L");
   gr29->SetLineColor(5);
   gr29->SetMarkerColor(5);
   gr32->Draw("L");
   gr32->SetLineColor(6);
   gr32->SetMarkerColor(6);
   print_plots(c53, "output/", "methods_endcap");

   TCanvas *c54 = new TCanvas("c54","Electron Isolation PUPPI Low Pile-Up",200,10,700,500);
   TGraph *gr33 = new TGraph(99,z33,y33);
   gr33->Draw("AL");
   gr33->GetYaxis()->SetRangeUser(0.9,1.0);
   gr33->GetXaxis()->SetRangeUser(0.0,1.0);
   gr33->GetXaxis()->SetTitle("Background Efficiency");
   gr33->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c54, "output/", "electron_isolation_puppi_lowpu");

   TCanvas *c55 = new TCanvas("c55","Electron Isolation PUPPI Medium Pile-Up",200,10,700,500);
   TGraph *gr34 = new TGraph(99,z34,y34);
   gr34->Draw("AL");
   gr34->GetYaxis()->SetRangeUser(0.9,1.0);
   gr34->GetXaxis()->SetRangeUser(0.0,1.0);
   gr34->GetXaxis()->SetTitle("Background Efficiency");
   gr34->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c55, "output/", "electron_isolation_puppi_medpu");

   TCanvas *c56 = new TCanvas("c56","Electron Isolation PUPPI High Pile-Up",200,10,700,500);
   TGraph *gr35 = new TGraph(99,z35,y35);
   gr35->Draw("AL");
   gr35->GetYaxis()->SetRangeUser(0.9,1.0);
   gr35->GetXaxis()->SetRangeUser(0.0,1.0);
   gr35->GetXaxis()->SetTitle("Background Efficiency");
   gr35->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c56, "output/", "electron_isolation_puppi_highpu");

   TCanvas *c57 = new TCanvas("c57","Electron Isolation PUPPI Pile-Up Scenarios",200,10,700,500);
   gr33->Draw("AL");
   gr34->Draw("L");
   gr34->SetLineColor(2);
   gr34->SetMarkerColor(2);
   gr35->Draw("L");
   gr35->SetLineColor(4);
   gr35->SetMarkerColor(4);
   print_plots(c57, "output/", "electron_isolation_puppi_pu_scenarios");

   TCanvas *c58 = new TCanvas("c58","Electron Isolation PUPPI No Leptons Low Pile-Up",200,10,700,500);
   TGraph *gr36 = new TGraph(99,z36,y36);
   gr36->Draw("AL");
   gr36->GetYaxis()->SetRangeUser(0.9,1.0);
   gr36->GetXaxis()->SetRangeUser(0.0,1.0);
   gr36->GetXaxis()->SetTitle("Background Efficiency");
   gr36->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c58, "output/", "electron_isolation_puppinl_lowpu");

   TCanvas *c59 = new TCanvas("c59","Electron Isolation PUPPI No Leptons Medium Pile-Up",200,10,700,500);
   TGraph *gr37 = new TGraph(99,z37,y37);
   gr37->Draw("AL");
   gr37->GetYaxis()->SetRangeUser(0.9,1.0);
   gr37->GetXaxis()->SetRangeUser(0.0,1.0);
   gr37->GetXaxis()->SetTitle("Background Efficiency");
   gr37->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c59, "output/", "electron_isolation_puppinl_medpu");

   TCanvas *c60 = new TCanvas("c60","Electron Isolation PUPPI No Leptons High Pile-Up",200,10,700,500);
   TGraph *gr38 = new TGraph(99,z38,y38);
   gr38->Draw("AL");
   gr38->GetYaxis()->SetRangeUser(0.9,1.0);
   gr38->GetXaxis()->SetRangeUser(0.0,1.0);
   gr38->GetXaxis()->SetTitle("Background Efficiency");
   gr38->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c60, "output/", "electron_isolation_puppinl_highpu");

   TCanvas *c61 = new TCanvas("c60","Electron Isolation PUPPI No Leptons Pile-Up Scenarios", 200, 10, 700, 500);
   gr36->Draw("AL");
   gr37->Draw("L");
   gr37->SetLineColor(2);
   gr37->SetMarkerColor(2);
   gr38->Draw("L");
   gr38->SetLineColor(4);
   gr38->SetMarkerColor(4);
   print_plots(c61, "output/", "electron_isolation_puppinl_pu_scenarios");

   TCanvas *c62 = new TCanvas("c62","Electron Isolation CITK Low Pile-Up",200,10,700,500);
   TGraph *gr39 = new TGraph(99,z39,y39);
   gr39->Draw("AL");
   gr39->GetYaxis()->SetRangeUser(0.9,1.0);
   gr39->GetXaxis()->SetRangeUser(0.0,1.0);
   gr39->GetXaxis()->SetTitle("Background Efficiency");
   gr39->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c62, "output/", "electron_isolation_citk_lowpu");

   TCanvas *c63 = new TCanvas("c63","Electron Isolation CITK Medium Pile-Up",200,10,700,500);
   TGraph *gr40 = new TGraph(99,z40,y40);
   gr40->Draw("AL");
   gr40->GetYaxis()->SetRangeUser(0.9,1.0);
   gr40->GetXaxis()->SetRangeUser(0.0,1.0);
   gr40->GetXaxis()->SetTitle("Background Efficiency");
   gr40->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c63, "output/", "electron_isolation_citk_medpu");

   TCanvas *c64 = new TCanvas("c64","Electron Isolation CITK High Pile-Up",200,10,700,500);
   TGraph *gr41 = new TGraph(99,z41,y41);
   gr41->Draw("AL");
   gr41->GetYaxis()->SetRangeUser(0.9,1.0);
   gr41->GetXaxis()->SetRangeUser(0.0,1.0);
   gr41->GetXaxis()->SetTitle("Background Efficiency");
   gr41->GetYaxis()->SetTitle("Signal Efficiency");
   print_plots(c64, "output/", "electron_isolation_citk_highpu");

   TCanvas *c65 = new TCanvas("c60","Electron Isolation CITK Pile-Up Scenarios", 200, 10, 700, 500);
   gr39->Draw("AL");
   gr40->Draw("L");
   gr40->SetLineColor(2);
   gr40->SetMarkerColor(2);
   gr41->Draw("L");
   gr41->SetLineColor(4);
   gr41->SetMarkerColor(4);
   print_plots(c65, "output/", "electron_isolation_citk_pu_scenarios");

   TCanvas *c36 = new TCanvas("c36","Methods Low Pile-Up",200,10,700,500);
   gr15->Draw("AL");
   gr15->SetLineColor(1);
   gr15->SetMarkerColor(1);
   gr18->Draw("L");
   gr18->SetLineColor(2);
   gr18->SetMarkerColor(2);
   gr21->Draw("L");
   gr21->SetLineColor(4);
   gr21->SetMarkerColor(4);
   gr33->Draw("L");
   gr33->SetLineColor(3);
   gr33->SetMarkerColor(3);
   gr36->Draw("L");
   gr36->SetLineColor(5);
   gr36->SetMarkerColor(5);
   gr39->Draw("L");
   gr39->SetLineColor(6);
   gr39->SetMarkerColor(6);
   print_plots(c36, "output/", "methods_lowpu");

   TCanvas *c37 = new TCanvas("c37","Methods Medium Pile-Up",200,10,700,500);
   gr16->Draw("AL");
   gr16->SetLineColor(1);
   gr16->SetMarkerColor(1);
   gr19->Draw("L");
   gr19->SetLineColor(2);
   gr19->SetMarkerColor(2);
   gr22->Draw("L");
   gr22->SetLineColor(4);
   gr22->SetMarkerColor(4);
   gr34->Draw("L");
   gr34->SetLineColor(3);
   gr34->SetMarkerColor(3);
   gr37->Draw("L");
   gr37->SetLineColor(5);
   gr37->SetMarkerColor(5);
   gr40->Draw("L");
   gr40->SetLineColor(6);
   gr40->SetMarkerColor(6);
   print_plots(c37, "output/", "methods_medpu");

   TCanvas *c38 = new TCanvas("c38","Methods High Pile-Up",200,10,700,500);
   gr17->Draw("AL");
   gr17->SetLineColor(1);
   gr17->SetMarkerColor(1);
   gr20->Draw("L");
   gr20->SetLineColor(2);
   gr20->SetMarkerColor(2);
   gr23->Draw("L");
   gr23->SetLineColor(4);
   gr23->SetMarkerColor(4);
   gr35->Draw("L");
   gr35->SetLineColor(3);
   gr35->SetMarkerColor(3);
   gr38->Draw("L");
   gr38->SetLineColor(5);
   gr38->SetMarkerColor(5);
   gr41->Draw("L");
   gr41->SetLineColor(6);
   gr41->SetMarkerColor(6);
   print_plots(c38, "output/", "methods_highpu");

}
