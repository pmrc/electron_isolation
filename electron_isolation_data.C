// Pedro Cipriano, Jul 2015
// FESB - Split, CMS
// Last Update: 27 Jul 2015
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

void electron_isolation_data()
{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  std::cout << "Electron Isolation - Data Version" << endl;
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

  int samples = 4;
  int working_point = 39;
  string sample[4];
  string out[4];
  string prefix[4];

  sample[0] = "/data_CMS/cms/cipriano/isolationNtuples_SingleElectron_Run2015B_06_Ago_2015/SingleElectron.root";
  sample[1] = "/data_CMS/cms/cipriano/isolationNtuples_DoubleEg_Run2015B_06_Ago_2015/DoubleEG.root";
  sample[2] = "/data_CMS/cms/cipriano/isolationNtuples_DoubleMuonLowMass_Run2015B_05_Ago_2015/DoubleMuonLowMass.root";
  sample[3] = "/data_CMS/cms/cipriano/isolationNtuples_DoubleMuon_Run2015B_05_Ago_2015/DoubleMuon.root";

  out[0] = "output/SingleElectron.root";
  out[1] = "output/DoubleEG.root";
  out[2] = "output/DoubleMuonLowMass.root";
  out[3] = "output/DoubleMuon.root";

  prefix[0] = "SingleElectron";
  prefix[1] = "DoubleEG";
  prefix[2] = "DoubleMuonSingleMass";
  prefix[3] = "DoubleMuonSingleMass";

  int pt_nbins = 10;
  double pt_bins[11] = {7.0,10.0,15.0,20.0,25.0,30.0,35.0,40.0,45.0,60.0,100.0};
  int vtx_nbins = 25;
  double vtx_bins[26] = {5.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,21.0,22.0,23.0, 24.0,25.0,26.0,27.0,28.0,29.0,30.0,35.0,42.5,50.0,80.0};

TH1D *vertex_multiplicity = new TH1D("vertex_multiplicity","Generated Vertex Multiplicity;Number of Generated Vertices;N/N_{total}",70,-0.5,69.5);
TH1D *evt_rho = new TH1D("evt_rho","Event Rho",120,0,60.0);

TH1D *vertex_multiplicity_signal = new TH1D("vertex_multiplicity_signal","Generated Vertex Multiplicity;Number of Generated Vertices;N/N_{total}",70,-0.5,69.5);
TH1D *evt_rho_signal = new TH1D("evt_rho_signal","Event Rho",120,0,60.0);

TH1D *vertex_multiplicity_bkg = new TH1D("vertex_multiplicity_bkg","Generated Vertex Multiplicity;Number of Generated Vertices;N/N_{total}",70,-0.5,69.5);
TH1D *evt_rho_bkg = new TH1D("evt_rho_bkg","Event Rho",120,0,60.0);

TH1D *reco_ele_multiplicity = new TH1D("reco_ele_multiplicity","Reconstructed Electron Multiplicity;Number of Reconstructed Electrons;N/N_{total}",6,-0.5,5.5);
TH1D *reco_ele_pt = new TH1D("reco_ele_pt","Reconstructed Electron pT;Reconstructed Electron p_{T};N/N_{total}",100,0,200);
TH1D *reco_ele_eta = new TH1D("reco_ele_eta","Reconstructed Electron Eta;Reconstructed Electron #eta;N/N_{total}",60,-3,3);
TH1D *reco_ele_phi = new TH1D("reco_ele_phi","Reconstructed Electron Phi;Reconstructed Electron #phi;N/N_{total}",50,-3.5,3.5);
TH1D *reco_ele_charge = new TH1D("reco_ele_charge","Reconstructed Electron Charge;Reconstructed Electron Charge;N/N_{total}",3,-1.5,1.5);
TH1D *reco_ele_effarea = new TH1D("reco_ele_effarea","Reconstructed Electron Effective Area;Reconstructed Electron Effective Area;N/N_{total}",50,0.0,0.5);
TH1D *reco_ele_dxy = new TH1D("reco_ele_dxy","Reconstructed Electron dxy;Reconstructed Electron dxy;N/N_{total}",60,0,0.6);
TH1D *reco_ele_dz = new TH1D("reco_ele_dz","Reconstructed Electron dz;Reconstructed Electron dz;N/N_{total}",120,0,1.2);
TH1D *reco_ele_missinghit = new TH1D("reco_ele_missinghit","Reconstructed Electron Missing Hits;Reconstructed Electron Number of Missing Hits;N/N_{total}",3,-0.5,2.5);


TH1D *reco_ele_multiplicity_signal = new TH1D("reco_ele_multiplicity_signal","Reconstructed Electron Multiplicity;Number of Reconstructed Electrons;N/N_{total}",6,-0.5,5.5);
TH1D *reco_ele_pt_signal = new TH1D("reco_ele_pt_signal","Reconstructed Electron pT;Reconstructed Electron p_{T};N/N_{total}",100,0,200);
TH1D *reco_ele_eta_signal = new TH1D("reco_ele_eta_signal","Reconstructed Electron Eta;Reconstructed Electron #eta;N/N_{total}",60,-3,3);
TH1D *reco_ele_phi_signal = new TH1D("reco_ele_phi_signal","Reconstructed Electron Phi;Reconstructed Electron #phi;N/N_{total}",50,-3.5,3.5);
TH1D *reco_ele_charge_signal = new TH1D("reco_ele_charge_signal","Reconstructed Electron Charge;Reconstructed Electron Charge;N/N_{total}",3,-1.5,1.5);
TH1D *reco_ele_effarea_signal = new TH1D("reco_ele_effarea_signal","Reconstructed Electron Effective Area;Reconstructed Electron Effective Area;N/N_{total}",50,0.0,0.5);
TH1D *reco_ele_dxy_signal = new TH1D("reco_ele_dxy_signal","Reconstructed Electron dxy;Reconstructed Electron dxy;N/N_{total}",60,0,0.6);
TH1D *reco_ele_dz_signal = new TH1D("reco_ele_dz_signal","Reconstructed Electron dz;Reconstructed Electron dz;N/N_{total}",120,0,1.2);
TH1D *reco_ele_missinghit_signal = new TH1D("reco_ele_missinghit_signal","Reconstructed Electron Missing Hits;Reconstructed Electron Number of Missing Hits;N/N_{total}",3,-0.5,2.5);


TH1D *reco_ele_multiplicity_bkg = new TH1D("reco_ele_multiplicity_bkg","Reconstructed Electron Multiplicity;Number of Reconstructed Electrons;N/N_{total}",6,-0.5,5.5);
TH1D *reco_ele_pt_bkg = new TH1D("reco_ele_pt_bkg","Reconstructed Electron pT;Reconstructed Electron p_{T};N/N_{total}",100,0,200);
TH1D *reco_ele_eta_bkg = new TH1D("reco_ele_eta_bkg","Reconstructed Electron Eta;Reconstructed Electron #eta;N/N_{total}",60,-3,3);
TH1D *reco_ele_phi_bkg = new TH1D("reco_ele_phi_bkg","Reconstructed Electron Phi;Reconstructed Electron #phi;N/N_{total}",50,-3.5,3.5);
TH1D *reco_ele_charge_bkg = new TH1D("reco_ele_charge_bkg","Reconstructed Electron Charge;Reconstructed Electron Charge;N/N_{total}",3,-1.5,1.5);
TH1D *reco_ele_effarea_bkg = new TH1D("reco_ele_effarea_bkg","Reconstructed Electron Effective Area;Reconstructed Electron Effective Area;N/N_{total}",50,0.0,0.5);
TH1D *reco_ele_dxy_bkg = new TH1D("reco_ele_dxy_bkg","Reconstructed Electron dxy;Reconstructed Electron dxy;N/N_{total}",60,0,0.6);
TH1D *reco_ele_dz_bkg = new TH1D("reco_ele_dz_bkg","Reconstructed Electron dz;Reconstructed Electron dz;N/N_{total}",120,0,1.2);
TH1D *reco_ele_missinghit_bkg = new TH1D("reco_ele_missinghit_bkg","Reconstructed Electron Missing Hits;Reconstructed Electron Number of Missing Hits;N/N_{total}",3,-0.5,2.5);


TH1D *reco_ele_pfchhadiso = new TH1D("reco_ele_pfchhadiso","PF Charged Hadron Isolated;PF CH Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel = new TH1D("reco_ele_pfchhadisorel","PF Charged Hadron Isolated pT;PF CH Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_barrel = new TH1D("reco_ele_pfchhadiso_barrel","PF Charged Hadron Isolated Barrel;PF CH Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_barrel = new TH1D("reco_ele_pfchhadisorel_barrel","PF Charged Hadron Relative Isolated Barrel;PF CH Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_endcap = new TH1D("reco_ele_pfchhadiso_endcap","PF Charged Hadron Isolated EndCap;PF CH Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_endcap = new TH1D("reco_ele_pfchhadisorel_endcap","PF Charged Hadron Isolated Relative EndCap;PF CH Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso = new TH1D("reco_ele_pfnehadiso","PF Neutral Hadron Isolated;PF NH Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel = new TH1D("reco_ele_pfnehadisorel","PF Neutral Hadron Isolated pT;PF NH Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_barrel = new TH1D("reco_ele_pfnehadiso_barrel","PF Neutral Hadron Isolated Barrel;PF NH Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_barrel = new TH1D("reco_ele_pfnehadisorel_barrel","PF Neutral Hadron Isolated Relative Barrel;PF NH Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_endcap = new TH1D("reco_ele_pfnehadiso_endcap","PF Neutral Hadron Isolated EndCap;PF NH Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_endcap = new TH1D("reco_ele_pfnehadisorel_endcap","PF Neutral Hadron Isolated Relative EndCap;PF NH Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso = new TH1D("reco_ele_pfphotoniso","PF Photon Isolated;PF Photon Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel = new TH1D("reco_ele_pfphotonisorel","PF Photon Isolated pT;PF Photon Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_barrel = new TH1D("reco_ele_pfphotoniso_barrel","PF Photon Isolated Barrel;PF Photon Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_barrel = new TH1D("reco_ele_pfphotonisorel_barrel","PF Photon Isolated Relative Barrel;PF Photon Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_endcap = new TH1D("reco_ele_pfphotoniso_endcap","PF Photon Isolated EndCap;PF Photon Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_endcap = new TH1D("reco_ele_pfphotonisorel_endcap","PF Photon Isolated Relative EndCap;PF Photon Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu = new TH1D("reco_ele_pfchargedfrompu","PF Charged Hadrons from PU;PF Charged Hadrons From PU; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel = new TH1D("reco_ele_pfchargedfrompurel","PF Charged Hadrons from PU/p_{T};PF Charged Hadrons From PU/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu_barrel = new TH1D("reco_ele_pfchargedfrompu_barrel","PF Charged Hadrons from PU Barrel;PF Charged Hadrons From PU Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel_barrel = new TH1D("reco_ele_pfchargedfrompurel_barrel","PF Charged Hadrons from PU Relative Barrel;PF Charged Hadrons From PU Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu_endcap = new TH1D("reco_ele_pfchargedfrompu_endcap","PF Charged Hadrons from PU EndCap;PF Charged Hadrons From PU EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel_endcap = new TH1D("reco_ele_pfchargedfrompurel_endcap","PF Charged Hadrons from PU Relative EndCap;PF Charged Hadrons From PU EndCap/p_{T}; N/N_{total}",100,0,10.0);

TH1D *reco_ele_pfchhadiso_signal = new TH1D("reco_ele_pfchhadiso_signal","PF Charged Hadron Isolated;PF CH Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_signal = new TH1D("reco_ele_pfchhadisorel_signal","PF Charged Hadron Isolated pT;PF CH Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_barrel_signal = new TH1D("reco_ele_pfchhadiso_barrel_signal","PF Charged Hadron Isolated Barrel;PF CH Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_barrel_signal = new TH1D("reco_ele_pfchhadisorel_barrel_signal","PF Charged Hadron Isolated Relative Barrel;PF CH Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_endcap_signal = new TH1D("reco_ele_pfchhadiso_endcap_signal","PF Charged Hadron Isolated EndCap;PF CH Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_endcap_signal = new TH1D("reco_ele_pfchhadisorel_endcap_signal","PF Charged Hadron Isolated Relative EndCap;PF CH Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_signal = new TH1D("reco_ele_pfnehadiso_signal","PF Neutral Hadron Isolated;PF NH Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_signal = new TH1D("reco_ele_pfnehadisorel_signal","PF Neutral Hadron Isolated pT;PF NH Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_barrel_signal = new TH1D("reco_ele_pfnehadiso_barrel_signal","PF Neutral Hadron Isolated Barrel;PF NH Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_barrel_signal = new TH1D("reco_ele_pfnehadisorel_barrel_signal","PF Neutral Hadron Isolated Relative Barrel;PF NH Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_endcap_signal = new TH1D("reco_ele_pfnehadiso_endcap_signal","PF Neutral Hadron Isolated EndCap;PF NH Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_endcap_signal = new TH1D("reco_ele_pfnehadisorel_endcap_signal","PF Neutral Hadron Isolated Relative EndCap;PF NH Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_signal = new TH1D("reco_ele_pfphotoniso_signal","PF Photon Isolated;PF Photon Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_signal = new TH1D("reco_ele_pfphotonisorel_signal","PF Photon Isolated pT;PF Photon Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_barrel_signal = new TH1D("reco_ele_pfphotoniso_barrel_signal","PF Photon Isolated Barrel;PF Photon Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_barrel_signal = new TH1D("reco_ele_pfphotonisorel_barrel_signal","PF Photon Isolated Relative Barrel;PF Photon Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_endcap_signal = new TH1D("reco_ele_pfphotoniso_endcap_signal","PF Photon Isolated EndCap;PF Photon Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_endcap_signal = new TH1D("reco_ele_pfphotonisorel_endcap_signal","PF Photon Isolated Relative EndCap;PF Photon Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu_signal = new TH1D("reco_ele_pfchargedfrompu_signal","PF Charged Hadrons from PU;PF Charged Hadrons From PU; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel_signal = new TH1D("reco_ele_pfchargedfrompurel_signal","PF Charged Hadrons from PU/p_{T};PF Charged Hadrons From PU/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu_barrel_signal = new TH1D("reco_ele_pfchargedfrompu_barrel_signal","PF Charged Hadrons from PU Barrel;PF Charged Hadrons From PU Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel_barrel_signal = new TH1D("reco_ele_pfchargedfrompurel_barrel_signal","PF Charged Hadrons from PU Relative Barrel;PF Charged Hadrons From PU Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu_endcap_signal = new TH1D("reco_ele_pfchargedfrompu_endcap_signal","PF Charged Hadrons from PU EndCap;PF Charged Hadrons From PU EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel_endcap_signal = new TH1D("reco_ele_pfchargedfrompurel_endcap_signal","PF Charged Hadrons from PU Relative EndCap;PF Charged Hadrons From PU EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_bkg = new TH1D("reco_ele_pfchhadiso_bkg","PF Charged Hadron Isolated;PF CH Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_bkg = new TH1D("reco_ele_pfchhadisorel_bkg","PF Charged Hadron Isolated pT;PF CH Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_barrel_bkg = new TH1D("reco_ele_pfchhadiso_barrel_bkg","PF Charged Hadron Isolated Barrel;PF CH Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_barrel_bkg = new TH1D("reco_ele_pfchhadisorel_barrel_bkg","PF Charged Hadron Isolated Relative Barrel;PF CH Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_endcap_bkg = new TH1D("reco_ele_pfchhadiso_endcap_bkg","PF Charged Hadron Isolated EndCap;PF CH Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_endcap_bkg = new TH1D("reco_ele_pfchhadisorel_endcap_bkg","PF Charged Hadron Isolated Relative EndCap;PF CH Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_bkg = new TH1D("reco_ele_pfnehadiso_bkg","PF Neutral Hadron Isolated;PF NH Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_bkg = new TH1D("reco_ele_pfnehadisorel_bkg","PF Neutral Hadron Isolated pT;PF NH Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_barrel_bkg = new TH1D("reco_ele_pfnehadiso_barrel_bkg","PF Neutral Hadron Isolated Barrel;PF NH Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_barrel_bkg = new TH1D("reco_ele_pfnehadisorel_barrel_bkg","PF Neutral Hadron Isolated Relative Barrel;PF NH Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_endcap_bkg = new TH1D("reco_ele_pfnehadiso_endcap_bkg","PF Neutral Hadron Isolated EndCap;PF NH Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_endcap_bkg = new TH1D("reco_ele_pfnehadisorel_endcap_bkg","PF Neutral Hadron Isolated Relative EndCap;PF NH Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_bkg = new TH1D("reco_ele_pfphotoniso_bkg","PF Photon Isolated;PF Photon Iso; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_bkg = new TH1D("reco_ele_pfphotonisorel_bkg","PF Photon Isolated pT;PF Photon Iso/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_barrel_bkg = new TH1D("reco_ele_pfphotoniso_barrel_bkg","PF Photon Isolated Barrel;PF Photon Iso Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_barrel_bkg = new TH1D("reco_ele_pfphotonisorel_barrel_bkg","PF Photon Isolated Relative Barrel;PF Photon Iso Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_endcap_bkg = new TH1D("reco_ele_pfphotoniso_endcap_bkg","PF Photon Isolated EndCap;PF Photon Iso EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_endcap_bkg = new TH1D("reco_ele_pfphotonisorel_endcap_bkg","PF Photon Isolated Relative EndCap;PF Photon Iso EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu_bkg = new TH1D("reco_ele_pfchargedfrompu_bkg","PF Charged Hadrons from PU;PF Charged Hadrons From PU; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel_bkg = new TH1D("reco_ele_pfchargedfrompurel_bkg","PF Charged Hadrons from PU/p_{T};PF Charged Hadrons From PU/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu_barrel_bkg = new TH1D("reco_ele_pfchargedfrompu_barrel_bkg","PF Charged Hadrons from PU Barrel;PF Charged Hadrons From PU Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel_barrel_bkg = new TH1D("reco_ele_pfchargedfrompurel_barrel_bkg","PF Charged Hadrons from PU Barrel;PF Charged Hadrons From PU Relative Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchargedfrompu_endcap_bkg = new TH1D("reco_ele_pfchargedfrompu_endcap_bkg","PF Charged Hadrons from PU EndCap;PF Charged Hadrons From PU EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchargedfrompurel_endcap_bkg = new TH1D("reco_ele_pfchargedfrompurel_endcap_bkg","PF Charged Hadrons from PU EndCap;PF Charged Hadrons From PU Relative EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_puppi = new TH1D("reco_ele_pfchhadiso_puppi","PF Charged Hadron Isolated with PUPPI;PF CH Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi = new TH1D("reco_ele_pfchhadisorel_puppi","PF Charged Hadron Isolated Relative with PUPPI;PF CH Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppi_barrel = new TH1D("reco_ele_pfchhadiso_puppi_barrel","PF Charged Hadron Isolated with PUPPI Barrel;PF CH Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi_barrel = new TH1D("reco_ele_pfchhadisorel_puppi_barrel","PF Charged Hadron Isolated with PUPPI Relative Barrel;PF CH Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppi_endcap = new TH1D("reco_ele_pfchhadiso_puppi_endcap","PF Charged Hadron Isolated with PUPPI EndCap;PF CH Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi_endcap = new TH1D("reco_ele_pfchhadisorel_puppi_endcap","PF Charged Hadron Isolated with PUPPI Relative EndCap;PF CH Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi = new TH1D("reco_ele_pfnehadiso_puppi","PF Neutral Hadron Isolated with PUPPI;PF NE Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi = new TH1D("reco_ele_pfnehadisorel_puppi","PF Neutral Hadron Isolated Relative with PUPPI;PF NE Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi_barrel = new TH1D("reco_ele_pfnehadiso_puppi_barrel","PF Neutral Hadron Isolated with PUPPI Barrel;PF Ne Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi_barrel = new TH1D("reco_ele_pfnehadisorel_puppi_barrel","PF Neutral Hadron Isolated with PUPPI Relative Barrel;PF Ne Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi_endcap = new TH1D("reco_ele_pfnehadiso_puppi_endcap","PF Neutral Hadron Isolated with PUPPI EndCap;PF Ne Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi_endcap = new TH1D("reco_ele_pfnehadisorel_puppi_endcap","PF Neutral Hadron Isolated with PUPPI Relative EndCap;PF Ne Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi = new TH1D("reco_ele_pfphotoniso_puppi","PF Photon Isolated with PUPPI;PF Photon Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi = new TH1D("reco_ele_pfphotonisorel_puppi","PF Photon Isolated Relative with PUPPI;PF Photon Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi_barrel = new TH1D("reco_ele_pfphotoniso_puppi_barrel","PF Photon Isolated with PUPPI Barrel;PF Photon Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi_barrel = new TH1D("reco_ele_pfphotonisorel_puppi_barrel","PF Photon Isolated with PUPPI Relative Barrel;PF Photon Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi_endcap = new TH1D("reco_ele_pfphotoniso_puppi_endcap","PF Photon Isolated with PUPPI EndCap;PF Photon Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi_endcap = new TH1D("reco_ele_pfphotonisorel_puppi_endcap","PF Photon Isolated with PUPPI Relative EndCap;PF Photon Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_puppi_signal = new TH1D("reco_ele_pfchhadiso_puppi_signal","PF Charged Hadron Isolated with PUPPI;PF CH Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi_signal = new TH1D("reco_ele_pfchhadisorel_puppi_signal","PF Charged Hadron Isolated Relative with PUPPI;PF CH Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppi_barrel_signal = new TH1D("reco_ele_pfchhadiso_puppi_barrel_signal","PF Charged Hadron Isolated with PUPPI Barrel;PF CH Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi_barrel_signal = new TH1D("reco_ele_pfchhadisorel_puppi_barrel_signal","PF Charged Hadron Isolated with PUPPI Relative Barrel;PF CH Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppi_endcap_signal = new TH1D("reco_ele_pfchhadiso_puppi_endcap_signal","PF Charged Hadron Isolated with PUPPI EndCap;PF CH Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi_endcap_signal = new TH1D("reco_ele_pfchhadisorel_puppi_endcap_signal","PF Charged Hadron Isolated with PUPPI Relative EndCap;PF CH Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi_signal = new TH1D("reco_ele_pfnehadiso_puppi_signal","PF Neutral Hadron Isolated with PUPPI;PF NE Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi_signal = new TH1D("reco_ele_pfnehadisorel_puppi_signal","PF Neutral Hadron Isolated Relative with PUPPI;PF NE Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi_barrel_signal = new TH1D("reco_ele_pfnehadiso_puppi_barrel_signal","PF Neutral Hadron Isolated with PUPPI Barrel;PF Ne Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi_barrel_signal = new TH1D("reco_ele_pfnehadisorel_puppi_barrel_signal","PF Neutral Hadron Isolated with PUPPI Relative Barrel;PF Ne Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi_endcap_signal = new TH1D("reco_ele_pfnehadiso_puppi_endcap_signal","PF Neutral Hadron Isolated with PUPPI EndCap;PF Ne Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi_endcap_signal = new TH1D("reco_ele_pfnehadisorel_puppi_endcap_signal","PF Neutral Hadron Isolated with PUPPI Relative EndCap;PF Ne Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi_signal = new TH1D("reco_ele_pfphotoniso_puppi_signal","PF Photon Isolated with PUPPI;PF Photon Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi_signal = new TH1D("reco_ele_pfphotonisorel_puppi_signal","PF Photon Isolated Relative with PUPPI;PF Photon Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi_barrel_signal = new TH1D("reco_ele_pfphotoniso_puppi_barrel_signal","PF Photon Isolated with PUPPI Barrel;PF Photon Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi_barrel_signal = new TH1D("reco_ele_pfphotonisorel_puppi_barrel_signal","PF Photon Isolated with PUPPI Relative Barrel;PF Photon Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi_endcap_signal = new TH1D("reco_ele_pfphotoniso_puppi_endcap_signal","PF Photon Isolated with PUPPI EndCap;PF Photon Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi_endcap_signal = new TH1D("reco_ele_pfphotonisorel_puppi_endcap_signal","PF Photon Isolated with PUPPI Relative EndCap;PF Photon Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_puppi_bkg = new TH1D("reco_ele_pfchhadiso_puppi_bkg","PF Charged Hadron Isolated with PUPPI;PF CH Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi_bkg = new TH1D("reco_ele_pfchhadisorel_puppi_bkg","PF Charged Hadron Isolated Relative with PUPPI;PF CH Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppi_barrel_bkg = new TH1D("reco_ele_pfchhadiso_puppi_barrel_bkg","PF Charged Hadron Isolated with PUPPI Barrel;PF CH Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi_barrel_bkg = new TH1D("reco_ele_pfchhadisorel_puppi_barrel_bkg","PF Charged Hadron Isolated with PUPPI Relative Barrel;PF CH Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppi_endcap_bkg = new TH1D("reco_ele_pfchhadiso_puppi_endcap_bkg","PF Charged Hadron Isolated with PUPPI EndCap;PF CH Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppi_endcap_bkg = new TH1D("reco_ele_pfchhadisorel_puppi_endcap_bkg","PF Charged Hadron Isolated with PUPPI Relative EndCap;PF CH Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi_bkg = new TH1D("reco_ele_pfnehadiso_puppi_bkg","PF Neutral Hadron Isolated with PUPPI;PF NE Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi_bkg = new TH1D("reco_ele_pfnehadisorel_puppi_bkg","PF Neutral Hadron Isolated Relative with PUPPI;PF NE Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi_barrel_bkg = new TH1D("reco_ele_pfnehadiso_puppi_barrel_bkg","PF Neutral Hadron Isolated with PUPPI Barrel;PF Ne Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi_barrel_bkg = new TH1D("reco_ele_pfnehadisorel_puppi_barrel_bkg","PF Neutral Hadron Isolated with PUPPI Relative Barrel;PF Ne Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppi_endcap_bkg = new TH1D("reco_ele_pfnehadiso_puppi_endcap_bkg","PF Neutral Hadron Isolated with PUPPI EndCap;PF Ne Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppi_endcap_bkg = new TH1D("reco_ele_pfnehadisorel_puppi_endcap_bkg","PF Neutral Hadron Isolated with PUPPI Relative EndCap;PF Ne Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi_bkg = new TH1D("reco_ele_pfphotoniso_puppi_bkg","PF Photon Isolated with PUPPI;PF Photon Iso PUPPI; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi_bkg = new TH1D("reco_ele_pfphotonisorel_puppi-bkg","PF Photon Isolated Relative with PUPPI;PF Photon Iso PUPPI/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi_barrel_bkg = new TH1D("reco_ele_pfphotoniso_puppi_barrel_bkg","PF Photon Isolated with PUPPI Barrel;PF Photon Iso PUPPI Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi_barrel_bkg = new TH1D("reco_ele_pfphotonisorel_puppi_barrel_bkg","PF Photon Isolated with PUPPI Relative Barrel;PF Photon Iso PUPPI Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppi_endcap_bkg = new TH1D("reco_ele_pfphotoniso_puppi_endcap_bkg","PF Photon Isolated with PUPPI EndCap;PF Photon Iso PUPPI EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppi_endcap_bkg = new TH1D("reco_ele_pfphotonisorel_puppi_endcap_bkg","PF Photon Isolated with PUPPI Relative EndCap;PF Photon Iso PUPPI EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_puppinl = new TH1D("reco_ele_pfchhadiso_puppinl","PF Charged Hadron Isolated with PUPPI No LEptons;PF CH Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl = new TH1D("reco_ele_pfchhadisorel_puppinl","PF Charged Hadron Isolated Relative with PUPPI No Leptons;PF CH Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppinl_barrel = new TH1D("reco_ele_pfchhadiso_puppinl_barrel","PF Charged Hadron Isolated with PUPPI No Leptons Barrel;PF CH Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl_barrel = new TH1D("reco_ele_pfchhadisorel_puppinl_barrel","PF Charged Hadron Isolated with PUPPI No Leptons Relative Barrel;PF CH Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppinl_endcap = new TH1D("reco_ele_pfchhadiso_puppinl_endcap","PF Charged Hadron Isolated with PUPPI No Leptons EndCap;PF CH Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl_endcap = new TH1D("reco_ele_pfchhadisorel_puppinl_endcap","PF Charged Hadron Isolated with PUPPI No Leptons Relative EndCap;PF CH Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl = new TH1D("reco_ele_pfnehadiso_puppinl","PF Neutral Hadron Isolated with PUPPI No Leptons;PF NE Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl = new TH1D("reco_ele_pfnehadisorel_puppinl","PF Neutral Hadron Isolated Relative with PUPPI No Leptons;PF NE Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl_barrel = new TH1D("reco_ele_pfnehadiso_puppinl_barrel","PF Neutral Hadron Isolated with PUPPI No Leptons Barrel;PF Ne Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl_barrel = new TH1D("reco_ele_pfnehadisorel_puppinl_barrel","PF Neutral Hadron Isolated with PUPPI No Leptons Relative Barrel;PF Ne Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl_endcap = new TH1D("reco_ele_pfnehadiso_puppinl_endcap","PF Neutral Hadron Isolated with PUPPI No Leptons EndCap;PF Ne Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl_endcap = new TH1D("reco_ele_pfnehadisorel_puppinl_endcap","PF Neutral Hadron Isolated with PUPPI No Leptons Relative EndCap;PF Ne Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl = new TH1D("reco_ele_pfphotoniso_puppinl","PF Photon Isolated with PUPPI No Leptons;PF Photon Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl = new TH1D("reco_ele_pfphotonisorel_puppinl","PF Photon Isolated Relative with PUPPI No Leptons;PF Photon Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl_barrel = new TH1D("reco_ele_pfphotoniso_puppinl_barrel","PF Photon Isolated with PUPPI No Leptons Barrel No Leptons;PF Photon Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl_barrel = new TH1D("reco_ele_pfphotonisorel_puppinl_barrel","PF Photon Isolated with PUPPI No Leptons Barrel No Relative Leptons;PF Photon Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl_endcap = new TH1D("reco_ele_pfphotoniso_puppinl_endcap","PF Photon Isolated with PUPPI No Leptons EndCap;PF Photon Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl_endcap = new TH1D("reco_ele_pfphotonisorel_puppinl_endcap","PF Photon Isolated with PUPPI No Leptons Relative EndCap;PF Photon Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);

TH1D *reco_ele_pfchhadiso_puppinl_signal = new TH1D("reco_ele_pfchhadiso_puppinl_signal","PF Charged Hadron Isolated with PUPPI No LEptons;PF CH Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl_signal = new TH1D("reco_ele_pfchhadisorel_puppinl_signal","PF Charged Hadron Isolated Relative with PUPPI No Leptons;PF CH Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppinl_barrel_signal = new TH1D("reco_ele_pfchhadiso_puppinl_barrel_signal","PF Charged Hadron Isolated with PUPPI No Leptons Barrel;PF CH Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl_barrel_signal = new TH1D("reco_ele_pfchhadisorel_puppinl_barrel_signal","PF Charged Hadron Isolated with PUPPI No Leptons Relative Barrel;PF CH Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppinl_endcap_signal = new TH1D("reco_ele_pfchhadiso_puppinl_endcap_signal","PF Charged Hadron Isolated with PUPPI No Leptons EndCap;PF CH Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl_endcap_signal = new TH1D("reco_ele_pfchhadisorel_puppinl_endcap_signal","PF Charged Hadron Isolated with PUPPI No Leptons Relative EndCap;PF CH Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl_signal = new TH1D("reco_ele_pfnehadiso_puppinl_signal","PF Neutral Hadron Isolated with PUPPI No Leptons;PF NE Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl_signal = new TH1D("reco_ele_pfnehadisorel_puppinl_signal","PF Neutral Hadron Isolated Relative with PUPPI No Leptons;PF NE Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl_barrel_signal = new TH1D("reco_ele_pfnehadiso_puppinl_barrel_signal","PF Neutral Hadron Isolated with PUPPI No Leptons Barrel;PF Ne Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl_barrel_signal = new TH1D("reco_ele_pfnehadisorel_puppinl_barrel_signal","PF Neutral Hadron Isolated with PUPPI No Leptons Relative Barrel;PF Ne Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl_endcap_signal = new TH1D("reco_ele_pfnehadiso_puppinl_endcap_signal","PF Neutral Hadron Isolated with PUPPI No Leptons EndCap;PF Ne Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl_endcap_signal = new TH1D("reco_ele_pfnehadisorel_puppinl_endcap_signal","PF Neutral Hadron Isolated with PUPPI No Leptons Relative EndCap;PF Ne Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl_signal = new TH1D("reco_ele_pfphotoniso_puppinl_signal_signal","PF Photon Isolated with PUPPI No Leptons;PF Photon Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl_signal = new TH1D("reco_ele_pfphotonisorel_puppinl_signal","PF Photon Isolated Relative with PUPPI No Leptons;PF Photon Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl_barrel_signal = new TH1D("reco_ele_pfphotoniso_puppinl_barrel_signal","PF Photon Isolated with PUPPI No Leptons Barrel No Leptons;PF Photon Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl_barrel_signal = new TH1D("reco_ele_pfphotonisorel_puppinl_barrel_signal","PF Photon Isolated with PUPPI No Leptons Barrel No Relative Leptons;PF Photon Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl_endcap_signal = new TH1D("reco_ele_pfphotoniso_puppinl_endcap_signal","PF Photon Isolated with PUPPI No Leptons EndCap;PF Photon Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl_endcap_signal = new TH1D("reco_ele_pfphotonisorel_puppinl_endcap_signal","PF Photon Isolated with PUPPI No Leptons Relative EndCap;PF Photon Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_puppinl_bkg = new TH1D("reco_ele_pfchhadiso_puppinl_bkg","PF Charged Hadron Isolated with PUPPI No LEptons;PF CH Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl_bkg = new TH1D("reco_ele_pfchhadisorel_puppinl_bkg","PF Charged Hadron Isolated Relative with PUPPI No Leptons;PF CH Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppinl_barrel_bkg = new TH1D("reco_ele_pfchhadiso_puppinl_barrel_bkg","PF Charged Hadron Isolated with PUPPI No Leptons Barrel;PF CH Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl_barrel_bkg = new TH1D("reco_ele_pfchhadisorel_puppinl_barrel_bkg","PF Charged Hadron Isolated with PUPPI No Leptons Relative Barrel;PF CH Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_puppinl_endcap_bkg = new TH1D("reco_ele_pfchhadiso_puppinl_endcap_bkg","PF Charged Hadron Isolated with PUPPI No Leptons EndCap;PF CH Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_puppinl_endcap_bkg = new TH1D("reco_ele_pfchhadisorel_puppinl_endcap_bkg","PF Charged Hadron Isolated with PUPPI No Leptons Relative EndCap;PF CH Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl_bkg = new TH1D("reco_ele_pfnehadiso_puppinl_bkg","PF Neutral Hadron Isolated with PUPPI No Leptons;PF NE Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl_bkg = new TH1D("reco_ele_pfnehadisorel_puppinl_bkg","PF Neutral Hadron Isolated Relative with PUPPI No Leptons;PF NE Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl_barrel_bkg = new TH1D("reco_ele_pfnehadiso_puppinl_barrel_bkg","PF Neutral Hadron Isolated with PUPPI No Leptons Barrel;PF Ne Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl_barrel_bkg = new TH1D("reco_ele_pfnehadisorel_puppinl_barrel_bkg","PF Neutral Hadron Isolated with PUPPI No Leptons Relative Barrel;PF Ne Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_puppinl_endcap_bkg = new TH1D("reco_ele_pfnehadiso_puppinl_endcap_bkg","PF Neutral Hadron Isolated with PUPPI No Leptons EndCap;PF Ne Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_puppinl_endcap_bkg = new TH1D("reco_ele_pfnehadisorel_puppinl_endcap_bkg","PF Neutral Hadron Isolated with PUPPI No Leptons Relative EndCap;PF Ne Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl_bkg = new TH1D("reco_ele_pfphotoniso_puppinl_bkg","PF Photon Isolated with PUPPI No Leptons;PF Photon Iso PUPPI No Leptons; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl_bkg = new TH1D("reco_ele_pfphotonisorel_puppinl_bkg","PF Photon Isolated Relative with PUPPI No Leptons;PF Photon Iso PUPPI No Leptons/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl_barrel_bkg = new TH1D("reco_ele_pfphotoniso_puppinl_barrel_bkg","PF Photon Isolated with PUPPI No Leptons Barrel No Leptons;PF Photon Iso PUPPI No Leptons Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl_barrel_bkg = new TH1D("reco_ele_pfphotonisorel_puppinl_barrel_bkg","PF Photon Isolated with PUPPI No Leptons Relative Barrel;PF Photon Iso PUPPI No Leptons Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_puppinl_endcap_bkg = new TH1D("reco_ele_pfphotoniso_puppinl_endcap_bkg","PF Photon Isolated with PUPPI No Leptons EndCap;PF Photon Iso PUPPI No Leptons EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_puppinl_endcap_bkg = new TH1D("reco_ele_pfphotonisorel_puppinl_endcap_bkg","PF Photon Isolated with PUPPI No Leptons Relative EndCap;PF Photon Iso PUPPI No Leptons EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_citk = new TH1D("reco_ele_pfchhadiso_citk","PF Charged Hadron Isolated with CITK;PF CH Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk = new TH1D("reco_ele_pfchhadisorel_citk","PF Charged Hadron Isolated Relative with CITK;PF CH Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_citk_barrel = new TH1D("reco_ele_pfchhadiso_citk_barrel","PF Charged Hadron Isolated with CITK Barrel;PF CH Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk_barrel = new TH1D("reco_ele_pfchhadisorel_citk_barrel","PF Charged Hadron Isolated with CITK Relative Barrel;PF CH Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_citk_endcap = new TH1D("reco_ele_pfchhadiso_citk_endcap","PF Charged Hadron Isolated with CITK EndCap;PF CH Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk_endcap = new TH1D("reco_ele_pfchhadisorel_citk_endcap","PF Charged Hadron Isolated with CITK Relative EndCap;PF CH Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk = new TH1D("reco_ele_pfnehadiso_citk","PF Neutral Hadron Isolated with CITK;PF NE Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk = new TH1D("reco_ele_pfnehadisorel_citk","PF Neutral Hadron Isolated Relative with CITK;PF NE Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk_barrel = new TH1D("reco_ele_pfnehadiso_citk_barrel","PF Neutral Hadron Isolated with CITK Barrel;PF Ne Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk_barrel = new TH1D("reco_ele_pfnehadisorel_citk_barrel","PF Neutral Hadron Isolated with CITK Relative Barrel;PF Ne Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk_endcap = new TH1D("reco_ele_pfnehadiso_citk_endcap","PF Neutral Hadron Isolated with CITK EndCap;PF Ne Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk_endcap = new TH1D("reco_ele_pfnehadisorel_citk_endcap","PF Neutral Hadron Isolated with CITK Relative EndCap;PF Ne Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk = new TH1D("reco_ele_pfphotoniso_citk","PF Photon Isolated with CITK;PF Photon Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk = new TH1D("reco_ele_pfphotonisorel_citk","PF Photon Isolated Relative with CITK;PF Photon Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk_barrel = new TH1D("reco_ele_pfphotoniso_citk_barrel","PF Photon Isolated with CITK Barrel;PF Photon Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk_barrel = new TH1D("reco_ele_pfphotonisorel_citk_barrel","PF Photon Isolated with CITK Relative Barrel;PF Photon Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk_endcap = new TH1D("reco_ele_pfphotoniso_citk_endcap","PF Photon Isolated with CITK EndCap;PF Photon Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk_endcap = new TH1D("reco_ele_pfphotonisorel_citk_endcap","PF Photon Isolated with CITK Relative EndCap;PF Photon Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_citk_signal = new TH1D("reco_ele_pfchhadiso_citk_signal","PF Charged Hadron Isolated with CITK;PF CH Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk_signal = new TH1D("reco_ele_pfchhadisorel_citk_signal","PF Charged Hadron Isolated Relative with CITK;PF CH Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_citk_barrel_signal = new TH1D("reco_ele_pfchhadiso_citk_barrel_signal","PF Charged Hadron Isolated with CITK Barrel;PF CH Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk_barrel_signal = new TH1D("reco_ele_pfchhadisorel_citk_barrel_signal","PF Charged Hadron Isolated with CITK Relative Barrel;PF CH Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_citk_endcap_signal = new TH1D("reco_ele_pfchhadiso_citk_endcap_signal","PF Charged Hadron Isolated with CITK EndCap;PF CH Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk_endcap_signal = new TH1D("reco_ele_pfchhadisorel_citk_endcap_signal","PF Charged Hadron Isolated with CITK Relative EndCap;PF CH Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk_signal = new TH1D("reco_ele_pfnehadiso_citk_signal","PF Neutral Hadron Isolated with CITK;PF NE Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk_signal = new TH1D("reco_ele_pfnehadisorel_citk_signal","PF Neutral Hadron Isolated Relative with CITK;PF NE Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk_barrel_signal = new TH1D("reco_ele_pfnehadiso_citk_barrel_signal","PF Neutral Hadron Isolated with CITK Barrel;PF Ne Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk_barrel_signal = new TH1D("reco_ele_pfnehadisorel_citk_barrel_signal","PF Neutral Hadron Isolated with CITK Relative Barrel;PF Ne Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk_endcap_signal = new TH1D("reco_ele_pfnehadiso_citk_endcap_signal","PF Neutral Hadron Isolated with CITK EndCap;PF Ne Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk_endcap_signal = new TH1D("reco_ele_pfnehadisorel_citk_endcap_signal","PF Neutral Hadron Isolated with CITK Relative EndCap;PF Ne Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk_signal = new TH1D("reco_ele_pfphotoniso_citk_signal","PF Photon Isolated with CITK;PF Photon Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk_signal = new TH1D("reco_ele_pfphotonisorel_citk_signal","PF Photon Isolated Relative with CITK;PF Photon Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk_barrel_signal = new TH1D("reco_ele_pfphotoniso_citk_barrel_signal","PF Photon Isolated with CITK Barrel;PF Photon Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk_barrel_signal = new TH1D("reco_ele_pfphotonisorel_citk_barrel_signal","PF Photon Isolated with CITK Relative Barrel;PF Photon Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk_endcap_signal = new TH1D("reco_ele_pfphotoniso_citk_endcap_signal","PF Photon Isolated with CITK EndCap;PF Photon Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk_endcap_signal = new TH1D("reco_ele_pfphotonisorel_citk_endcap_signal","PF Photon Isolated with CITK Relative EndCap;PF Photon Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfchhadiso_citk_bkg = new TH1D("reco_ele_pfchhadiso_citk_bkg","PF Charged Hadron Isolated with CITK;PF CH Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk_bkg = new TH1D("reco_ele_pfchhadisorel_citk_bkg","PF Charged Hadron Isolated Relative with CITK;PF CH Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_citk_barrel_bkg = new TH1D("reco_ele_pfchhadiso_citk_barrel_bkg","PF Charged Hadron Isolated with CITK Barrel;PF CH Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk_barrel_bkg = new TH1D("reco_ele_pfchhadisorel_citk_barrel_bkg","PF Charged Hadron Isolated with CITK Relative Barrel;PF CH Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfchhadiso_citk_endcap_bkg = new TH1D("reco_ele_pfchhadiso_citk_endcap_bkg","PF Charged Hadron Isolated with CITK EndCap;PF CH Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfchhadisorel_citk_endcap_bkg = new TH1D("reco_ele_pfchhadisorel_citk_endcap_bkg","PF Charged Hadron Isolated with CITK Relative EndCap;PF CH Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk_bkg = new TH1D("reco_ele_pfnehadiso_citk-bkg","PF Neutral Hadron Isolated with CITK;PF NE Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk_bkg = new TH1D("reco_ele_pfnehadisorel_citk_bkg","PF Neutral Hadron Isolated Relative with CITK;PF NE Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk_barrel_bkg = new TH1D("reco_ele_pfnehadiso_citk_barrel_bkg","PF Neutral Hadron Isolated with CITK Barrel;PF Ne Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk_barrel_bkg = new TH1D("reco_ele_pfnehadisorel_citk_barrel_bkg","PF Neutral Hadron Isolated with CITK Relative Barrel;PF Ne Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfnehadiso_citk_endcap_bkg = new TH1D("reco_ele_pfnehadiso_citk_endcap_bkg","PF Neutral Hadron Isolated with CITK EndCap;PF Ne Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfnehadisorel_citk_endcap_bkg = new TH1D("reco_ele_pfnehadisorel_citk_endcap_bkg","PF Neutral Hadron Isolated with CITK Relative EndCap;PF Ne Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk_bkg = new TH1D("reco_ele_pfphotoniso_citk_bkg","PF Photon Isolated with CITK;PF Photon Iso CITK; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk_bkg = new TH1D("reco_ele_pfphotonisorel_citk_bkg","PF Photon Isolated Relative with CITK;PF Photon Iso CITK/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk_barrel_bkg = new TH1D("reco_ele_pfphotoniso_citk_barrel_bkg","PF Photon Isolated with CITK Barrel;PF Photon Iso CITK Barrel; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk_barrel_bkg = new TH1D("reco_ele_pfphotonisorel_citk_barrel_bkg","PF Photon Isolated with CITK Relative Barrel;PF Photon Iso CITK Barrel/p_{T}; N/N_{total}",100,0,10.0);
TH1D *reco_ele_pfphotoniso_citk_endcap_bkg = new TH1D("reco_ele_pfphotoniso_citk_endcap_bkg","PF Photon Isolated with CITK EndCap;PF Photon Iso CITK EndCap; N/N_{total}",100,0,100.0);
TH1D *reco_ele_pfphotonisorel_citk_endcap_bkg = new TH1D("reco_ele_pfphotonisorel_citk_endcap_bkg","PF Photon Isolated with CITK Relative EndCap;PF Photon Iso CITK EndCap/p_{T}; N/N_{total}",100,0,10.0);


TH1D *reco_ele_pfiso_simple = new TH1D("reco_ele_pfiso_simple","PF Combined Relation Isolation Simple;PF Iso Simple; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_barrel = new TH1D("reco_ele_pfiso_simple_barrel","PF Combined Relation Isolation Simple Barrel;PF Iso Simple Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_endcap = new TH1D("reco_ele_pfiso_simple_endcap","PF Combined Relation Isolation Simple EndCap;PF Iso Simple EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_lowpu = new TH1D("reco_ele_pfiso_simple_lowpu","PF Combined Relation Isolation Simple with Low Pile-Up;;PF Iso Simple Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_medpu = new TH1D("reco_ele_pfiso_simple_medpu","PF Combined Relation Isolation Simple with Medium Pile-Up;PF Iso Simple Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_highpu = new TH1D("reco_ele_pfiso_simple_highpu","PF Combined Relation Isolation Simple with High Pile-Up;PF Iso Simple High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_simple_signal = new TH1D("reco_ele_pfiso_simple_signal","PF Combined Relation Isolation Simple;PF Iso Simple; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_barrel_signal = new TH1D("reco_ele_pfiso_simple_barrel_signal","PF Combined Relation Isolation Simple Barrel;PF Iso Simple Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_endcap_signal = new TH1D("reco_ele_pfiso_simple_endcap_signal","PF Combined Relation Isolation Simple EndCap;PF Iso Simple EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_lowpu_signal = new TH1D("reco_ele_pfiso_simple_lowpu_signal","PF Combined Relation Isolation Simple with Low Pile-Up;;PF Iso Simple Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_medpu_signal = new TH1D("reco_ele_pfiso_simple_medpu_signal","PF Combined Relation Isolation Simple with Medium Pile-Up;PF Iso Simple Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_highpu_signal = new TH1D("reco_ele_pfiso_simple_highpu_signal","PF Combined Relation Isolation Simple with High Pile-Up;PF Iso Simple High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_simple_bkg = new TH1D("reco_ele_pfiso_simple_bkg","PF Combined Relation Isolation Simple;PF Iso Simple; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_barrel_bkg = new TH1D("reco_ele_pfiso_simple_barrel_bkg","PF Combined Relation Isolation Simple Barrel;PF Iso Simple Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_endcap_bkg = new TH1D("reco_ele_pfiso_simple_endcap_bkg","PF Combined Relation Isolation Simple EndCap;PF Iso Simple EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_lowpu_bkg = new TH1D("reco_ele_pfiso_simple_lowpu_bkg","PF Combined Relation Isolation Simple with Low Pile-Up;;PF Iso Simple Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_medpu_bkg = new TH1D("reco_ele_pfiso_simple_medpu_bkg","PF Combined Relation Isolation Simple with Medium Pile-Up;PF Iso Simple Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_simple_highpu_bkg = new TH1D("reco_ele_pfiso_simple_highpu_bkg","PF Combined Relation Isolation Simple with High Pile-Up;PF Iso Simple High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_effarea = new TH1D("reco_ele_pfiso_effarea","PF Combined Relation Isolation Effective Area;PF Iso Eff Area; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_barrel = new TH1D("reco_ele_pfiso_effarea_barrel","PF Combined Relation Isolation Effective Area Barrel;PF Iso Eff Area Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_endcap = new TH1D("reco_ele_pfiso_effarea_endcap","PF Combined Relation Isolation Effective Area EndCap;PF Iso Eff Area EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_lowpu = new TH1D("reco_ele_pfiso_effarea_lowpu","PF Combined Relation Isolation Effective Area with Low Pile-Up;PF Iso Eff Area Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_medpu = new TH1D("reco_ele_pfiso_effarea_medpu","PF Combined Relation Isolation Effective Area with Medium Pile-Up;PF Iso Eff Area Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_highpu = new TH1D("reco_ele_pfiso_effarea_highpu","PF Combined Relation Isolation Effective Area with High Pile-Up;PF Iso Eff Area High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_effarea_signal = new TH1D("reco_ele_pfiso_effarea_signal","PF Combined Relation Isolation Effective Area;PF Iso Eff Area; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_barrel_signal = new TH1D("reco_ele_pfiso_effarea_barrel_signal","PF Combined Relation Isolation Effective Area Barrel;PF Iso Eff Area Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_endcap_signal = new TH1D("reco_ele_pfiso_effarea_endcap_signal","PF Combined Relation Isolation Effective Area EndCap;PF Iso Eff Area EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_lowpu_signal = new TH1D("reco_ele_pfiso_effarea_lowpu_signal","PF Combined Relation Isolation Effective Area with Low Pile-Up;PF Iso Eff Area Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_medpu_signal = new TH1D("reco_ele_pfiso_effarea_medpu_signal","PF Combined Relation Isolation Effective Area with Medium Pile-Up;PF Iso Eff Area Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_highpu_signal = new TH1D("reco_ele_pfiso_effarea_highpu_signal","PF Combined Relation Isolation Effective Area with High Pile-Up;PF Iso Eff Area High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_effarea_bkg = new TH1D("reco_ele_pfiso_effarea_bkg","PF Combined Relation Isolation Effective Area;PF Iso Eff Area; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_barrel_bkg = new TH1D("reco_ele_pfiso_effarea_barrel_bkg","PF Combined Relation Isolation Effective Area Barrel;PF Iso Eff Area Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_endcap_bkg = new TH1D("reco_ele_pfiso_effarea_endcap_bkg","PF Combined Relation Isolation Effective Area EndCap;PF Iso Eff Area EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_lowpu_bkg = new TH1D("reco_ele_pfiso_effarea_lowpu_bkg","PF Combined Relation Isolation Effective Area with Low Pile-Up;PF Iso Eff Area Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_medpu_bkg = new TH1D("reco_ele_pfiso_effarea_medpu_bkg","PF Combined Relation Isolation Effective Area with Medium Pile-Up;PF Iso Eff Area Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_effarea_highpu_bkg = new TH1D("reco_ele_pfiso_effarea_highpu_bkg","PF Combined Relation Isolation Effective Area with High Pile-Up;PF Iso Eff Area High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_deltabeta = new TH1D("reco_ele_pfiso_deltabeta","PF Combined Relation Isolation Delta Eta;PF Iso #Delta#beta; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_barrel = new TH1D("reco_ele_pfiso_deltabeta_barrel","PF Combined Relation Isolation Delta Eta Barrel;PF Iso #Delta#beta Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_endcap = new TH1D("reco_ele_pfiso_deltabeta_endcap","PF Combined Relation Isolation Delta Eta EndCap;PF Iso #Delta#beta EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_lowpu = new TH1D("reco_ele_pfiso_deltabeta_lowpu","PF Combined Relation Isolation Delta Eta with Low Pile-Up;PF Iso #Delta#beta Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_medpu = new TH1D("reco_ele_pfiso_deltabeta_medpu","PF Combined Relation Isolation Delta Eta with Medium Pile-Up;PF Iso #Delta#beta Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_highpu = new TH1D("reco_ele_pfiso_deltabeta_highpu","PF Combined Relation Isolation Delta Eta with High Pile-Up;PF Iso #Delta#beta High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_deltabeta_signal = new TH1D("reco_ele_pfiso_deltabeta_signal","PF Combined Relation Isolation Delta Eta;PF Iso #Delta#beta; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_barrel_signal = new TH1D("reco_ele_pfiso_deltabeta_barrel_signal","PF Combined Relation Isolation Delta Eta Barrel;PF Iso #Delta#beta Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_endcap_signal = new TH1D("reco_ele_pfiso_deltabeta_endcap_signal","PF Combined Relation Isolation Delta Eta EndCap;PF Iso #Delta#beta EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_lowpu_signal = new TH1D("reco_ele_pfiso_deltabeta_lowpu_signal","PF Combined Relation Isolation Delta Eta with Low Pile-Up;PF Iso #Delta#beta Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_medpu_signal = new TH1D("reco_ele_pfiso_deltabeta_medpu_signal","PF Combined Relation Isolation Delta Eta with Medium Pile-Up;PF Iso #Delta#beta Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_highpu_signal = new TH1D("reco_ele_pfiso_deltabeta_highpu_signal","PF Combined Relation Isolation Delta Eta with High Pile-Up;PF Iso #Delta#beta High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_deltabeta_bkg = new TH1D("reco_ele_pfiso_deltabeta_bkg","PF Combined Relation Isolation Delta Eta;PF Iso #Delta#beta; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_barrel_bkg = new TH1D("reco_ele_pfiso_deltabeta_barrel_bkg","PF Combined Relation Isolation Delta Eta Barrel;PF Iso #Delta#beta Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_endcap_bkg = new TH1D("reco_ele_pfiso_deltabeta_endcap_bkg","PF Combined Relation Isolation Delta Eta EndCap;PF Iso #Delta#beta EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_lowpu_bkg = new TH1D("reco_ele_pfiso_deltabeta_lowpu_bkg","PF Combined Relation Isolation Delta Eta with Low Pile-Up;PF Iso #Delta#beta Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_medpu_bkg = new TH1D("reco_ele_pfiso_deltabeta_medpu_bkg","PF Combined Relation Isolation Delta Eta with Medium Pile-Up;PF Iso #Delta#beta Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_deltabeta_highpu_bkg = new TH1D("reco_ele_pfiso_deltabeta_highpu_bkg","PF Combined Relation Isolation Delta Eta with High Pile-Up;PF Iso #Delta#beta High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_puppi = new TH1D("reco_ele_pfiso_puppi","PF Combined Relation Isolation PUPPI;PF Iso PUPPI; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_barrel = new TH1D("reco_ele_pfiso_puppi_barrel","PF Combined Relation Isolation PUPPI Barrel;PF Iso PUPPI Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_endcap = new TH1D("reco_ele_pfiso_puppi_endcap","PF Combined Relation Isolation PUPPI EndCap;PF Iso PUPPI EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_lowpu = new TH1D("reco_ele_pfiso_puppi_lowpu","PF Combined Relation Isolation PUPPI with Low Pile-Up;;PF Iso PUPPI Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_medpu = new TH1D("reco_ele_pfiso_puppi_medpu","PF Combined Relation Isolation PUPPI with Medium Pile-Up;PF Iso PUPPI Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_highpu = new TH1D("reco_ele_pfiso_puppi_highpu","PF Combined Relation Isolation PUPPI with High Pile-Up;PF Iso PUPPI High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_puppi_signal = new TH1D("reco_ele_pfiso_puppi_signal","PF Combined Relation Isolation PUPPI;PF Iso PUPPI; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_barrel_signal = new TH1D("reco_ele_pfiso_puppi_barrel_signal","PF Combined Relation Isolation PUPPI Barrel;PF Iso PUPPI Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_endcap_signal = new TH1D("reco_ele_pfiso_puppi_endcap_signal","PF Combined Relation Isolation PUPPI EndCap;PF Iso PUPPI EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_lowpu_signal = new TH1D("reco_ele_pfiso_puppi_lowpu_signal","PF Combined Relation Isolation PUPPI with Low Pile-Up;;PF Iso PUPPI Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_medpu_signal = new TH1D("reco_ele_pfiso_puppi_medpu_signal","PF Combined Relation Isolation PUPPI with Medium Pile-Up;PF Iso PUPPI Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_highpu_signal = new TH1D("reco_ele_pfiso_puppi_highpu_signal","PF Combined Relation Isolation PUPPI with High Pile-Up;PF Iso PUPPI High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_puppi_bkg = new TH1D("reco_ele_pfiso_puppi_bkg","PF Combined Relation Isolation PUPPI;PF Iso PUPPI; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_barrel_bkg = new TH1D("reco_ele_pfiso_puppi_barrel_bkg","PF Combined Relation Isolation PUPPI Barrel;PF Iso PUPPI Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_endcap_bkg = new TH1D("reco_ele_pfiso_puppi_endcap_bkg","PF Combined Relation Isolation PUPPI EndCap;PF Iso PUPPI EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_lowpu_bkg = new TH1D("reco_ele_pfiso_puppi_lowpu_bkg","PF Combined Relation Isolation PUPPI with Low Pile-Up;;PF Iso PUPPI Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_medpu_bkg = new TH1D("reco_ele_pfiso_puppi_medpu_bkg","PF Combined Relation Isolation PUPPI with Medium Pile-Up;PF Iso PUPPI Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppi_highpu_bkg = new TH1D("reco_ele_pfiso_puppi_highpu_bkg","PF Combined Relation Isolation PUPPI with High Pile-Up;PF Iso PUPPI High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_puppinl = new TH1D("reco_ele_pfiso_puppinl","PF Combined Relation Isolation PUPPI No Leptons;PF Iso PUPPI No Leptons; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_barrel = new TH1D("reco_ele_pfiso_puppinl_barrel","PF Combined Relation Isolation PUPPI No Leptons Barrel;PF Iso PUPPI No Leptons Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_endcap = new TH1D("reco_ele_pfiso_puppinl_endcap","PF Combined Relation Isolation PUPPI No Leptons EndCap;PF Iso PUPPI No Leptons EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_lowpu = new TH1D("reco_ele_pfiso_puppinl_lowpu","PF Combined Relation Isolation PUPPI No Leptons with Low Pile-Up;;PF Iso PUPPI No Leptons Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_medpu = new TH1D("reco_ele_pfiso_puppinl_medpu","PF Combined Relation Isolation PUPPI No Leptons with Medium Pile-Up;PF Iso PUPPI Medium No Leptons Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_highpu = new TH1D("reco_ele_pfiso_puppinl_highpu","PF Combined Relation Isolation PUPPI No Leptons with High Pile-Up;PF Iso PUPPI No Leptons High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_puppinl_signal = new TH1D("reco_ele_pfiso_puppinl_signal","PF Combined Relation Isolation PUPPI No Leptons;PF Iso PUPPI No Leptons; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_barrel_signal = new TH1D("reco_ele_pfiso_puppinl_barrel_signal","PF Combined Relation Isolation PUPPI No Leptons Barrel;PF Iso PUPPI No Leptons Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_endcap_signal = new TH1D("reco_ele_pfiso_puppinl_endcap_signal","PF Combined Relation Isolation PUPPI No Leptons EndCap;PF Iso PUPPI No Leptons EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_lowpu_signal = new TH1D("reco_ele_pfiso_puppinl_lowpu_signal","PF Combined Relation Isolation PUPPI No Leptons with Low Pile-Up;;PF Iso PUPPI No Leptons Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_medpu_signal = new TH1D("reco_ele_pfiso_puppinl_medpu_signal","PF Combined Relation Isolation PUPPI No Leptons with Medium Pile-Up;PF Iso PUPPI Medium No Leptons Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_highpu_signal = new TH1D("reco_ele_pfiso_puppinl_highpu_signal","PF Combined Relation Isolation PUPPI No Leptons with High Pile-Up;PF Iso PUPPI No Leptons High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_puppinl_bkg = new TH1D("reco_ele_pfiso_puppinl_bkg","PF Combined Relation Isolation PUPPI No Leptons;PF Iso PUPPI No Leptons; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_barrel_bkg = new TH1D("reco_ele_pfiso_puppinl_barrel_bkg","PF Combined Relation Isolation PUPPI No Leptons Barrel;PF Iso PUPPI No Leptons Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_endcap_bkg = new TH1D("reco_ele_pfiso_puppinl_endcap_bkg","PF Combined Relation Isolation PUPPI No Leptons EndCap;PF Iso PUPPI No Leptons EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_lowpu_bkg = new TH1D("reco_ele_pfiso_puppinl_lowpu_bkg","PF Combined Relation Isolation PUPPI No Leptons with Low Pile-Up;;PF Iso PUPPI No Leptons Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_medpu_bkg = new TH1D("reco_ele_pfiso_puppinl_medpu_bkg","PF Combined Relation Isolation PUPPI No Leptons with Medium Pile-Up;PF Iso PUPPI Medium No Leptons Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_puppinl_highpu_bkg = new TH1D("reco_ele_pfiso_puppinl_highpu_bkg","PF Combined Relation Isolation PUPPI No Leptons with High Pile-Up;PF Iso PUPPI No Leptons High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_citk = new TH1D("reco_ele_pfiso_citk","PF Combined Relation Isolation CITK;PF Iso CITK; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_barrel = new TH1D("reco_ele_pfiso_citk_barrel","PF Combined Relation Isolation CITK Barrel;PF Iso CITK Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_endcap = new TH1D("reco_ele_pfiso_citk_endcap","PF Combined Relation Isolation CITK EndCap;PF Iso CITK EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_lowpu = new TH1D("reco_ele_pfiso_citk_lowpu","PF Combined Relation Isolation CITK with Low Pile-Up;;PF Iso CITK Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_medpu = new TH1D("reco_ele_pfiso_citk_medpu","PF Combined Relation Isolation CITK with Medium Pile-Up;PF Iso CITK Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_highpu = new TH1D("reco_ele_pfiso_citk_highpu","PF Combined Relation Isolation CITK with High Pile-Up;PF Iso CITK High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_citk_signal = new TH1D("reco_ele_pfiso_citk_signal","PF Combined Relation Isolation CITK;PF Iso CITK; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_barrel_signal = new TH1D("reco_ele_pfiso_citk_barrel_signal","PF Combined Relation Isolation CITK Barrel;PF Iso CITK Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_endcap_signal = new TH1D("reco_ele_pfiso_citk_endcap_signal","PF Combined Relation Isolation CITK EndCap;PF Iso CITK EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_lowpu_signal = new TH1D("reco_ele_pfiso_citk_lowpu_signal","PF Combined Relation Isolation CITK with Low Pile-Up;;PF Iso CITK Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_medpu_signal = new TH1D("reco_ele_pfiso_citk_medpu_signal","PF Combined Relation Isolation CITK with Medium Pile-Up;PF Iso CITK Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_highpu_signal = new TH1D("reco_ele_pfiso_citk_highpu_signal","PF Combined Relation Isolation CITK with High Pile-Up;PF Iso CITK High Pile-Up; N/N_{total}",2000,0,20.0);


TH1D *reco_ele_pfiso_citk_bkg = new TH1D("reco_ele_pfiso_citk_bkg","PF Combined Relation Isolation CITK;PF Iso CITK; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_barrel_bkg = new TH1D("reco_ele_pfiso_citk_barrel_bkg","PF Combined Relation Isolation CITK Barrel;PF Iso CITK Barrel; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_endcap_bkg = new TH1D("reco_ele_pfiso_citk_endcap_bkg","PF Combined Relation Isolation CITK EndCap;PF Iso CITK EndCap; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_lowpu_bkg = new TH1D("reco_ele_pfiso_citk_lowpu_bkg","PF Combined Relation Isolation CITK with Low Pile-Up;;PF Iso CITK Low Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_medpu_bkg = new TH1D("reco_ele_pfiso_citk_medpu_bkg","PF Combined Relation Isolation CITK with Medium Pile-Up;PF Iso CITK Medium Pile-Up; N/N_{total}",2000,0,20.0);
TH1D *reco_ele_pfiso_citk_highpu_bkg = new TH1D("reco_ele_pfiso_citk_highpu_bkg","PF Combined Relation Isolation CITK with High Pile-Up;PF Iso CITK High Pile-Up; N/N_{total}",2000,0,20.0);


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


TH1D *reco_ele_bdt_signal = new TH1D("reco_ele_bdt_signal","Electron BDT",100,-1.0,1.0);
TH1D *reco_ele_bdt_barrel_signal = new TH1D("reco_ele_bdt_barrel_signal","Electron BDT Barrel",100,-1.0,1.0);
TH1D *reco_ele_bdt_endcap_signal = new TH1D("reco_ele_bdt_endcap_signal","Electron BDT EndCap",100,-1.0,1.0);
TH1D *reco_ele_sip_signal = new TH1D("reco_ele_sip_signal","Electron SIP",100,0,25.0);
TH1D *reco_ele_sip_barrel_signal = new TH1D("reco_ele_sip_barrel_signal","Electron SIP Barrel",100,0,25.0);
TH1D *reco_ele_sip_endcap_signal = new TH1D("reco_ele_sip_endcap_signal","Electron SIP Endcap",100,0,25.0);
TH1D *reco_ele_id_signal = new TH1D("reco_ele_id_signal","Electron ID",2,-0.5,1.5);
TH1D *reco_ele_isgood_signal = new TH1D("reco_ele_isgood_signal","Electron is Good",2,-0.5,1.5);
TH1D *leading_reco_ele_pt_signal = new TH1D("leading_reco_ele_pt_signal","Leading Reconstructed Electron pT",40,0,200);
TH1D *leading_reco_ele_eta_signal = new TH1D("leading_reco_ele_eta_signal","Leading Reconstructed Electron Eta",22,-5.5,5.5);
TH1D *leading_reco_ele_phi_signal = new TH1D("leading_reco_ele_phi_signal","Leading Reconstructed Electron Phi",20,-3.15,3.15);


TH1D *reco_ele_bdt_bkg = new TH1D("reco_ele_bdt_bkg","Electron BDT",100,-1.0,1.0);
TH1D *reco_ele_bdt_barrel_bkg = new TH1D("reco_ele_bdt_barrel_bkg","Electron BDT Barrel",100,-1.0,1.0);
TH1D *reco_ele_bdt_endcap_bkg = new TH1D("reco_ele_bdt_endcap_bkg","Electron BDT EndCap",100,-1.0,1.0);
TH1D *reco_ele_sip_bkg = new TH1D("reco_ele_sip_bkg","Electron SIP",100,0,25.0);
TH1D *reco_ele_sip_barrel_bkg = new TH1D("reco_ele_sip_barrel_bkg","Electron SIP Barrel",100,0,25.0);
TH1D *reco_ele_sip_endcap_bkg = new TH1D("reco_ele_sip_endcap_bkg","Electron SIP Endcap",100,0,25.0);
TH1D *reco_ele_id_bkg = new TH1D("reco_ele_id_bkg","Electron ID",2,-0.5,1.5);
TH1D *reco_ele_isgood_bkg = new TH1D("reco_ele_isgood_bkg","Electron is Good",2,-0.5,1.5);
TH1D *leading_reco_ele_pt_bkg = new TH1D("leading_reco_ele_pt_bkg","Leading Reconstructed Electron pT",40,0,200);
TH1D *leading_reco_ele_eta_bkg = new TH1D("leading_reco_ele_eta_bkg","Leading Reconstructed Electron Eta",22,-5.5,5.5);
TH1D *leading_reco_ele_phi_bkg = new TH1D("leading_reco_ele_phi_bkg","Leading Reconstructed Electron Phi",20,-3.15,3.15);

TH2D *iso_simple_vs_pt = new TH2D("iso_simple_vs_pt","PFIso Simple Versus pT;Simple Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_simple_vs_vtx = new TH2D("iso_simple_vs_vtx","PFIso Simple Versus Number of Vertices;Simple Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_simple_vs_eta = new TH2D("iso_simple_vs_eta","PFIso Simple Versus Eta;Simple Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_simple_vs_pt_signal = new TH2D("iso_simple_vs_pt_signal","PFIso Simple Versus pT;Simple Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_simple_vs_vtx_signal = new TH2D("iso_simple_vs_vtx_signal","PFIso Simple Versus Number of Vertices;Simple Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_simple_vs_eta_signal = new TH2D("iso_simple_vs_eta_signal","PFIso Simple Versus Eta;Simple Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_simple_vs_pt_bkg = new TH2D("iso_simple_vs_pt_bkg","PFIso Simple Versus pT;Simple Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_simple_vs_vtx_bkg = new TH2D("iso_simple_vs_vtx_bkg","PFIso Simple Versus Number of Vertices;Simple Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_simple_vs_eta_bkg = new TH2D("iso_simple_vs_eta_bkg","PFIso Simple Versus Eta;Simple Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);


TH2D *iso_effarea_vs_pt = new TH2D("iso_effarea_vs_pt","PFIso Effective Area Versus pT;Effective Area Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_effarea_vs_vtx = new TH2D("iso_effarea_vs_vtx","PFIso Effective Area Versus Number of Vertices;Effective Area Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_effarea_vs_eta = new TH2D("iso_effarea_vs_eta","PFIso Effective Area Versus Eta;Effective Area Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_effarea_vs_pt_signal = new TH2D("iso_effarea_vs_pt_signal","PFIso Effective Area Versus pT;Effective Area Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_effarea_vs_vtx_signal = new TH2D("iso_effarea_vs_vtx_signal","PFIso Effective Area Versus Number of Vertices;Effective Area Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_effarea_vs_eta_signal = new TH2D("iso_effarea_vs_eta_signal","PFIso Effective Area Versus Eta;Effective Area Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_effarea_vs_pt_bkg = new TH2D("iso_effarea_vs_pt_bkg","PFIso Effective Area Versus pT;Effective Area Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_effarea_vs_vtx_bkg = new TH2D("iso_effarea_vs_vtx_bkg","PFIso Effective Area Versus Number of Vertices;Effective Area Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_effarea_vs_eta_bkg = new TH2D("iso_effarea_vs_eta_bkg","PFIso Effective Area Versus Eta;Effective Area Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);


TH2D *iso_deltabeta_vs_pt = new TH2D("iso_deltabeta_vs_pt","PFIso Delta Beta Versus pT;Delta Beta Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_deltabeta_vs_vtx = new TH2D("iso_deltabeta_vs_vtx","PFIso Delta Beta Versus Number of Vertices;Delta Beta Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_deltabeta_vs_eta = new TH2D("iso_deltabeta_vs_eta","PFIso Delta Beta Versus Eta;Delta Beta Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);


TH2D *iso_deltabeta_vs_pt_signal = new TH2D("iso_deltabeta_vs_pt_signal","PFIso Delta Beta Versus pT;Delta Beta Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_deltabeta_vs_vtx_signal = new TH2D("iso_deltabeta_vs_vtx_signal","PFIso Delta Beta Versus Number of Vertices;Delta Beta Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_deltabeta_vs_eta_signal = new TH2D("iso_deltabeta_vs_eta_signal","PFIso Delta Beta Versus Eta;Delta Beta Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_deltabeta_vs_pt_bkg = new TH2D("iso_deltabeta_vs_pt_bkg","PFIso Delta Beta Versus pT;Delta Beta Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_deltabeta_vs_vtx_bkg = new TH2D("iso_deltabeta_vs_vtx_bkg","PFIso Delta Beta Versus Number of Vertices;Delta Beta Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_deltabeta_vs_eta_bkg = new TH2D("iso_deltabeta_vs_eta_bkg","PFIso Delta Beta Versus Eta;Delta Beta Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);


TH2D *iso_puppi_vs_pt = new TH2D("iso_puppi_vs_pt","PFIso PUPPI Versus pT;PUPPI Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_puppi_vs_vtx = new TH2D("iso_puppi_vs_vtx","PFIso PUPPI Versus Number of Vertices;PUPPI Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_puppi_vs_eta = new TH2D("iso_puppi_vs_eta","PFIso PUPPI Versus Eta;PUPPI Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_puppi_vs_pt_signal = new TH2D("iso_puppi_vs_pt_signal","PFIso PUPPI Versus pT;PUPPI Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_puppi_vs_vtx_signal = new TH2D("iso_puppi_vs_vtx_signal","PFIso PUPPI Versus Number of Vertices;PUPPI Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_puppi_vs_eta_signal = new TH2D("iso_puppi_vs_eta_signal","PFIso PUPPI Versus Eta;PUPPI Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_puppi_vs_pt_bkg = new TH2D("iso_puppi_vs_pt_bkg","PFIso PUPPI Versus pT;PUPPI Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_puppi_vs_vtx_bkg = new TH2D("iso_puppi_vs_vtx_bkg","PFIso PUPPI Versus Number of Vertices;PUPPI Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_puppi_vs_eta_bkg = new TH2D("iso_puppi_vs_eta_bkg","PFIso PUPPI Versus Eta;PUPPI Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);


TH2D *iso_puppinl_vs_pt = new TH2D("iso_puppinl_vs_pt","PFIso PUPPI Versus pT;PUPPI No Leptons Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_puppinl_vs_vtx = new TH2D("iso_puppinl_vs_vtx","PFIso PUPPI Versus Number of Vertices;PUPPI No Leptons Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_puppinl_vs_eta = new TH2D("iso_puppinl_vs_eta","PFIso PUPPI Versus Eta;PUPPI No Leptons Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_puppinl_vs_pt_signal = new TH2D("iso_puppinl_vs_pt_signal","PFIso PUPPI Versus pT;PUPPI No Leptons Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_puppinl_vs_vtx_signal = new TH2D("iso_puppinl_vs_vtx_signal","PFIso PUPPI Versus Number of Vertices;PUPPI No Leptons Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_puppinl_vs_eta_signal = new TH2D("iso_puppinl_vs_eta_signal","PFIso PUPPI Versus Eta;PUPPI No Leptons Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_puppinl_vs_pt_bkg = new TH2D("iso_puppinl_vs_pt_bkg","PFIso PUPPI Versus pT;PUPPI No Leptons Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_puppinl_vs_vtx_bkg = new TH2D("iso_puppinl_vs_vtx_bkg","PFIso PUPPI Versus Number of Vertices;PUPPI No Leptons Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_puppinl_vs_eta_bkg = new TH2D("iso_puppinl_vs_eta_bkg","PFIso PUPPI Versus Eta;PUPPI No Leptons Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);


TH2D *iso_citk_vs_pt = new TH2D("iso_citk_vs_pt","PFIso CITK Versus pT;CITK Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_citk_vs_vtx = new TH2D("iso_citk_vs_vtx","PFIso CITK Versus Number of Vertices;CITK Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_citk_vs_eta = new TH2D("iso_citk_vs_eta","PFIso CITK Versus Eta;CITK Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_citk_vs_pt_signal = new TH2D("iso_citk_vs_pt_signal","PFIso CITK Versus pT;CITK Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_citk_vs_vtx_signal = new TH2D("iso_citk_vs_vtx_signal","PFIso CITK Versus Number of Vertices;CITK Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_citk_vs_eta_signal = new TH2D("iso_citk_vs_eta_signal","PFIso CITK Versus Eta;CITK Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

TH2D *iso_citk_vs_pt_bkg = new TH2D("iso_citk_vs_pt_bkg","PFIso CITK Versus pT;CITK Isolation;p_{T};Events",2000,0,20.0,pt_nbins,pt_bins);
TH2D *iso_citk_vs_vtx_bkg = new TH2D("iso_citk_vs_vtx_bkg","PFIso CITK Versus Number of Vertices;CITK Isolation;Number of Vertices;Events",2000,0,20.0,vtx_nbins,vtx_bins);
TH2D *iso_citk_vs_eta_bkg = new TH2D("iso_citk_vs_eta_bkg","PFIso CITK Versus Eta;CITK Isolation;#eta;Events",2000,0,20.0,25,-2.5,2.5);

  Int_t nEvent;
  Int_t nRun;
  Int_t nLumi;

  Int_t nPV;
  Float_t rho;

  //Missing ET
  double met_et, met_px, met_py, met_phi, met_set;

  //reco electrons  
  Int_t nele;
  Float_t ele_pt[100];
  Float_t ele_eta[100];
  Float_t ele_sclEta[100];
  Int_t ele_charge[100];
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

    TChain* chain[4];

   double max_reco_pt, radius;
   int id_leading_reco;
   bool disp_ini_info;
   int selected_electrons[samples], selected_electrons_signal[samples], selected_electrons_bkg[samples];
   int candidate1, candidate2, zzpair_candidate, extra_candidate;


   double isolation_simple[samples][2000], isolation_simple_barrel[samples][2000];
   double isolation_simple_endcap[samples][2000];
   double isolation_simple_lowpu[samples][2000], isolation_simple_medpu[samples][2000];
   double isolation_simple_highpu[samples][2000];

   double isolation_effarea[samples][2000], isolation_effarea_barrel[samples][2000];
   double isolation_effarea_endcap[samples][2000];
   double isolation_effarea_lowpu[samples][2000], isolation_effarea_medpu[samples][2000];
   double isolation_effarea_highpu[samples][2000];

   double isolation_deltabeta[samples][2000], isolation_deltabeta_barrel[samples][2000];
   double isolation_deltabeta_endcap[samples][2000]; 
   double isolation_deltabeta_lowpu[samples][2000], isolation_deltabeta_medpu[samples][2000];
   double isolation_deltabeta_highpu[samples][2000];

   double isolation_puppi[samples][2000], isolation_puppi_barrel[samples][2000];
   double isolation_puppi_endcap[samples][2000];
   double isolation_puppi_lowpu[samples][2000], isolation_puppi_medpu[samples][2000];
   double isolation_puppi_highpu[samples][2000];

   double isolation_puppinl[samples][2000], isolation_puppinl_barrel[samples][2000];
   double isolation_puppinl_endcap[samples][2000];
   double isolation_puppinl_lowpu[samples][2000], isolation_puppinl_medpu[samples][2000];
   double isolation_puppinl_highpu[samples][2000];

   double isolation_citk[samples][2000], isolation_citk_barrel[samples][2000];
   double isolation_citk_endcap[samples][2000]; 
   double isolation_citk_lowpu[samples][2000], isolation_citk_medpu[samples][2000];
   double isolation_citk_highpu[samples][2000];

   double sip[samples][100], sip_barrel[samples][100], sip_endcap[samples][100];
   double bdt[samples][100], bdt_barrel[samples][100], bdt_endcap[samples][100];
  
    for (int s=0; s<samples; ++s) {

    chain[s] = new TChain("tree");
    chain[s]->Add(sample[s].c_str());

    cout << "Reading " << sample[s] << "..." << endl;

    chain[s]->SetBranchAddress("nEvent", &nEvent);
    chain[s]->SetBranchAddress("nRun", &nRun);
    chain[s]->SetBranchAddress("nLumi", &nLumi);

    chain[s]->SetBranchAddress("nPV", &nPV);
    chain[s]->SetBranchAddress("rho", &rho);

    chain[s]->SetBranchAddress("met_pf_et", &met_et);
    chain[s]->SetBranchAddress("met_pf_px", &met_px);
    chain[s]->SetBranchAddress("met_pf_py", &met_py);
    chain[s]->SetBranchAddress("met_pf_phi", &met_phi);
    chain[s]->SetBranchAddress("met_pf_set", &met_set);

    chain[s]->SetBranchAddress("nele", &nele);
    chain[s]->SetBranchAddress("ele_pt", &ele_pt);
    chain[s]->SetBranchAddress("ele_eta", &ele_eta);
    chain[s]->SetBranchAddress("ele_sclEta", &ele_sclEta);
    chain[s]->SetBranchAddress("ele_charge", &ele_charge);
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
   evt_rho->Reset();

   vertex_multiplicity_signal->Reset();
   evt_rho_signal->Reset();

   vertex_multiplicity_bkg->Reset();
   evt_rho_bkg->Reset();


   reco_ele_multiplicity->Reset();
   reco_ele_pt->Reset();
   reco_ele_eta->Reset();
   reco_ele_phi->Reset();
   reco_ele_charge->Reset();
   reco_ele_effarea->Reset();
   reco_ele_dxy->Reset();
   reco_ele_dz->Reset();
   reco_ele_missinghit->Reset();

   reco_ele_pfchhadiso->Reset();
   reco_ele_pfchhadisorel->Reset();
   reco_ele_pfchhadiso_barrel->Reset();
   reco_ele_pfchhadisorel_barrel->Reset();
   reco_ele_pfchhadiso_endcap->Reset();
   reco_ele_pfchhadisorel_endcap->Reset();
   reco_ele_pfnehadisorel->Reset();
   reco_ele_pfnehadiso->Reset();
   reco_ele_pfnehadiso_barrel->Reset();
   reco_ele_pfnehadisorel_barrel->Reset();
   reco_ele_pfnehadiso_endcap->Reset();
   reco_ele_pfnehadisorel_endcap->Reset();
   reco_ele_pfphotoniso->Reset();
   reco_ele_pfphotonisorel->Reset();
   reco_ele_pfphotoniso_barrel->Reset();
   reco_ele_pfphotonisorel_barrel->Reset();
   reco_ele_pfphotoniso_endcap->Reset();
   reco_ele_pfphotonisorel_endcap->Reset();
   reco_ele_pfchargedfrompu->Reset();
   reco_ele_pfchargedfrompurel->Reset();
   reco_ele_pfchargedfrompu_barrel->Reset();
   reco_ele_pfchargedfrompurel_barrel->Reset();
   reco_ele_pfchargedfrompu_endcap->Reset();
   reco_ele_pfchargedfrompurel_endcap->Reset();

   reco_ele_multiplicity_signal->Reset();
   reco_ele_pt_signal->Reset();
   reco_ele_eta_signal->Reset();
   reco_ele_phi_signal->Reset();
   reco_ele_charge_signal->Reset();
   reco_ele_effarea_signal->Reset();
   reco_ele_dxy_signal->Reset();
   reco_ele_dz_signal->Reset();
   reco_ele_missinghit_signal->Reset();

   reco_ele_pfchhadiso_signal->Reset();
   reco_ele_pfchhadisorel_signal->Reset();
   reco_ele_pfchhadiso_barrel_signal->Reset();
   reco_ele_pfchhadisorel_barrel_signal->Reset();
   reco_ele_pfchhadiso_endcap_signal->Reset();
   reco_ele_pfchhadisorel_endcap_signal->Reset();
   reco_ele_pfnehadiso_signal->Reset();
   reco_ele_pfnehadisorel_signal->Reset();
   reco_ele_pfnehadiso_barrel_signal->Reset();
   reco_ele_pfnehadisorel_barrel_signal->Reset();
   reco_ele_pfnehadiso_endcap_signal->Reset();
   reco_ele_pfnehadisorel_endcap_signal->Reset();
   reco_ele_pfphotoniso_signal->Reset();
   reco_ele_pfphotonisorel_signal->Reset();
   reco_ele_pfphotoniso_barrel_signal->Reset();
   reco_ele_pfphotonisorel_barrel_signal->Reset();
   reco_ele_pfphotoniso_endcap_signal->Reset();
   reco_ele_pfphotonisorel_endcap_signal->Reset();
   reco_ele_pfchargedfrompu_signal->Reset();
   reco_ele_pfchargedfrompurel_signal->Reset();
   reco_ele_pfchargedfrompu_barrel_signal->Reset();
   reco_ele_pfchargedfrompurel_barrel_signal->Reset();
   reco_ele_pfchargedfrompu_endcap_signal->Reset();
   reco_ele_pfchargedfrompurel_endcap_signal->Reset();


   reco_ele_multiplicity_bkg->Reset();
   reco_ele_pt_bkg->Reset();
   reco_ele_eta_bkg->Reset();
   reco_ele_phi_bkg->Reset();
   reco_ele_charge_bkg->Reset();
   reco_ele_effarea_bkg->Reset();
   reco_ele_dxy_bkg->Reset();
   reco_ele_dz_bkg->Reset();
   reco_ele_missinghit_bkg->Reset();

   reco_ele_pfchhadiso_bkg->Reset();
   reco_ele_pfchhadisorel_bkg->Reset();
   reco_ele_pfchhadiso_barrel_bkg->Reset();
   reco_ele_pfchhadisorel_barrel_bkg->Reset();
   reco_ele_pfchhadiso_endcap_bkg->Reset();
   reco_ele_pfchhadisorel_endcap_bkg->Reset();
   reco_ele_pfnehadiso_bkg->Reset();
   reco_ele_pfnehadisorel_bkg->Reset();
   reco_ele_pfnehadiso_barrel_bkg->Reset();
   reco_ele_pfnehadisorel_barrel_bkg->Reset();
   reco_ele_pfnehadiso_endcap_bkg->Reset();
   reco_ele_pfnehadisorel_endcap_bkg->Reset();
   reco_ele_pfphotoniso_bkg->Reset();
   reco_ele_pfphotonisorel_bkg->Reset();
   reco_ele_pfphotoniso_barrel_bkg->Reset();
   reco_ele_pfphotonisorel_barrel_bkg->Reset();
   reco_ele_pfphotoniso_endcap_bkg->Reset();
   reco_ele_pfphotonisorel_endcap_bkg->Reset();
   reco_ele_pfchargedfrompu_bkg->Reset();
   reco_ele_pfchargedfrompurel_bkg->Reset();
   reco_ele_pfchargedfrompu_barrel_bkg->Reset();
   reco_ele_pfchargedfrompurel_barrel_bkg->Reset();
   reco_ele_pfchargedfrompu_endcap_bkg->Reset();
   reco_ele_pfchargedfrompurel_endcap_bkg->Reset();


   reco_ele_pfchhadiso_puppi->Reset();
   reco_ele_pfchhadisorel_puppi->Reset();
   reco_ele_pfchhadiso_puppi_barrel->Reset();
   reco_ele_pfchhadisorel_puppi_barrel->Reset();
   reco_ele_pfchhadiso_puppi_endcap->Reset();
   reco_ele_pfchhadisorel_puppi_endcap->Reset();
   reco_ele_pfnehadiso_puppi->Reset();
   reco_ele_pfnehadisorel_puppi->Reset();
   reco_ele_pfnehadiso_puppi_barrel->Reset();
   reco_ele_pfnehadisorel_puppi_barrel->Reset();
   reco_ele_pfnehadiso_puppi_endcap->Reset();
   reco_ele_pfnehadisorel_puppi_endcap->Reset();
   reco_ele_pfphotoniso_puppi->Reset();
   reco_ele_pfphotonisorel_puppi->Reset();
   reco_ele_pfphotoniso_puppi_barrel->Reset();
   reco_ele_pfphotonisorel_puppi_barrel->Reset();
   reco_ele_pfphotoniso_puppi_endcap->Reset();
   reco_ele_pfphotonisorel_puppi_endcap->Reset();

   reco_ele_pfchhadiso_puppi_signal->Reset();
   reco_ele_pfchhadisorel_puppi_signal->Reset();
   reco_ele_pfchhadiso_puppi_barrel_signal->Reset();
   reco_ele_pfchhadisorel_puppi_barrel_signal->Reset();
   reco_ele_pfchhadiso_puppi_endcap_signal->Reset();
   reco_ele_pfchhadisorel_puppi_endcap_signal->Reset();
   reco_ele_pfnehadiso_puppi_signal->Reset();
   reco_ele_pfnehadisorel_puppi_signal->Reset();
   reco_ele_pfnehadiso_puppi_barrel_signal->Reset();
   reco_ele_pfnehadisorel_puppi_barrel_signal->Reset();
   reco_ele_pfnehadiso_puppi_endcap_signal->Reset();
   reco_ele_pfnehadisorel_puppi_endcap_signal->Reset();
   reco_ele_pfphotoniso_puppi_signal->Reset();
   reco_ele_pfphotonisorel_puppi_signal->Reset();
   reco_ele_pfphotoniso_puppi_barrel_signal->Reset();
   reco_ele_pfphotonisorel_puppi_barrel_signal->Reset();
   reco_ele_pfphotoniso_puppi_endcap_signal->Reset();
   reco_ele_pfphotonisorel_puppi_endcap_signal->Reset();

   reco_ele_pfchhadiso_puppi_bkg->Reset();
   reco_ele_pfchhadisorel_puppi_bkg->Reset();
   reco_ele_pfchhadiso_puppi_barrel_bkg->Reset();
   reco_ele_pfchhadisorel_puppi_barrel_bkg->Reset();
   reco_ele_pfchhadiso_puppi_endcap_bkg->Reset();
   reco_ele_pfchhadisorel_puppi_endcap_bkg->Reset();
   reco_ele_pfnehadiso_puppi_bkg->Reset();
   reco_ele_pfnehadisorel_puppi_bkg->Reset();
   reco_ele_pfnehadiso_puppi_barrel_bkg->Reset();
   reco_ele_pfnehadisorel_puppi_barrel_bkg->Reset();
   reco_ele_pfnehadiso_puppi_endcap_bkg->Reset();
   reco_ele_pfnehadisorel_puppi_endcap_bkg->Reset();
   reco_ele_pfphotoniso_puppi_bkg->Reset();
   reco_ele_pfphotonisorel_puppi_bkg->Reset();
   reco_ele_pfphotoniso_puppi_barrel_bkg->Reset();
   reco_ele_pfphotonisorel_puppi_barrel_bkg->Reset();
   reco_ele_pfphotoniso_puppi_endcap_bkg->Reset();
   reco_ele_pfphotonisorel_puppi_endcap_bkg->Reset();


   reco_ele_pfchhadiso_puppinl->Reset();
   reco_ele_pfchhadisorel_puppinl->Reset();
   reco_ele_pfchhadiso_puppinl_barrel->Reset();
   reco_ele_pfchhadisorel_puppinl_barrel->Reset();
   reco_ele_pfchhadiso_puppinl_endcap->Reset();
   reco_ele_pfchhadisorel_puppinl_endcap->Reset();
   reco_ele_pfnehadiso_puppinl->Reset();
   reco_ele_pfnehadisorel_puppinl->Reset();
   reco_ele_pfnehadiso_puppinl_barrel->Reset();
   reco_ele_pfnehadisorel_puppinl_barrel->Reset();
   reco_ele_pfnehadiso_puppinl_endcap->Reset();
   reco_ele_pfnehadisorel_puppinl_endcap->Reset();
   reco_ele_pfphotoniso_puppinl->Reset();
   reco_ele_pfphotonisorel_puppinl->Reset();
   reco_ele_pfphotoniso_puppinl_barrel->Reset();
   reco_ele_pfphotonisorel_puppinl_barrel->Reset();
   reco_ele_pfphotoniso_puppinl_endcap->Reset();
   reco_ele_pfphotonisorel_puppinl_endcap->Reset();


   reco_ele_pfchhadiso_puppinl_signal->Reset();
   reco_ele_pfchhadisorel_puppinl_signal->Reset();
   reco_ele_pfchhadiso_puppinl_barrel_signal->Reset();
   reco_ele_pfchhadisorel_puppinl_barrel_signal->Reset();
   reco_ele_pfchhadiso_puppinl_endcap_signal->Reset();
   reco_ele_pfchhadisorel_puppinl_endcap_signal->Reset();
   reco_ele_pfnehadiso_puppinl_signal->Reset();
   reco_ele_pfnehadisorel_puppinl_signal->Reset();
   reco_ele_pfnehadiso_puppinl_barrel_signal->Reset();
   reco_ele_pfnehadisorel_puppinl_barrel_signal->Reset();
   reco_ele_pfnehadiso_puppinl_endcap_signal->Reset();
   reco_ele_pfnehadisorel_puppinl_endcap_signal->Reset();
   reco_ele_pfphotoniso_puppinl_signal->Reset();
   reco_ele_pfphotonisorel_puppinl_signal->Reset();
   reco_ele_pfphotoniso_puppinl_barrel_signal->Reset();
   reco_ele_pfphotonisorel_puppinl_barrel_signal->Reset();
   reco_ele_pfphotoniso_puppinl_endcap_signal->Reset();
   reco_ele_pfphotonisorel_puppinl_endcap_signal->Reset();

   reco_ele_pfchhadiso_puppinl_bkg->Reset();
   reco_ele_pfchhadisorel_puppinl_bkg->Reset();
   reco_ele_pfchhadiso_puppinl_barrel_bkg->Reset();
   reco_ele_pfchhadisorel_puppinl_barrel_bkg->Reset();
   reco_ele_pfchhadiso_puppinl_endcap_bkg->Reset();
   reco_ele_pfchhadisorel_puppinl_endcap_bkg->Reset();
   reco_ele_pfnehadiso_puppinl_bkg->Reset();
   reco_ele_pfnehadisorel_puppinl_bkg->Reset();
   reco_ele_pfnehadiso_puppinl_barrel_bkg->Reset();
   reco_ele_pfnehadisorel_puppinl_barrel_bkg->Reset();
   reco_ele_pfnehadiso_puppinl_endcap_bkg->Reset();
   reco_ele_pfnehadisorel_puppinl_endcap_bkg->Reset();
   reco_ele_pfphotoniso_puppinl_bkg->Reset();
   reco_ele_pfphotonisorel_puppinl_bkg->Reset();
   reco_ele_pfphotoniso_puppinl_barrel_bkg->Reset();
   reco_ele_pfphotonisorel_puppinl_barrel_bkg->Reset();
   reco_ele_pfphotoniso_puppinl_endcap_bkg->Reset();
   reco_ele_pfphotonisorel_puppinl_endcap_bkg->Reset();


   reco_ele_pfchhadiso_citk->Reset();
   reco_ele_pfchhadisorel_citk->Reset();
   reco_ele_pfchhadiso_citk_barrel->Reset();
   reco_ele_pfchhadisorel_citk_barrel->Reset();
   reco_ele_pfchhadiso_citk_endcap->Reset();
   reco_ele_pfchhadisorel_citk_endcap->Reset();
   reco_ele_pfnehadiso_citk->Reset();
   reco_ele_pfnehadisorel_citk->Reset();
   reco_ele_pfnehadiso_citk_barrel->Reset();
   reco_ele_pfnehadisorel_citk_barrel->Reset();
   reco_ele_pfnehadiso_citk_endcap->Reset();
   reco_ele_pfnehadisorel_citk_endcap->Reset();
   reco_ele_pfphotoniso_citk->Reset();
   reco_ele_pfphotonisorel_citk->Reset();
   reco_ele_pfphotoniso_citk_barrel->Reset();
   reco_ele_pfphotonisorel_citk_barrel->Reset();
   reco_ele_pfphotoniso_citk_endcap->Reset();
   reco_ele_pfphotonisorel_citk_endcap->Reset();

   reco_ele_pfchhadiso_citk_signal->Reset();
   reco_ele_pfchhadisorel_citk_signal->Reset();
   reco_ele_pfchhadiso_citk_barrel_signal->Reset();
   reco_ele_pfchhadisorel_citk_barrel_signal->Reset();
   reco_ele_pfchhadiso_citk_endcap_signal->Reset();
   reco_ele_pfchhadisorel_citk_endcap_signal->Reset();
   reco_ele_pfnehadiso_citk_signal->Reset();
   reco_ele_pfnehadisorel_citk_signal->Reset();
   reco_ele_pfnehadiso_citk_barrel_signal->Reset();
   reco_ele_pfnehadisorel_citk_barrel_signal->Reset();
   reco_ele_pfnehadiso_citk_endcap_signal->Reset();
   reco_ele_pfnehadisorel_citk_endcap_signal->Reset();
   reco_ele_pfphotoniso_citk_signal->Reset();
   reco_ele_pfphotonisorel_citk_signal->Reset();
   reco_ele_pfphotoniso_citk_barrel_signal->Reset();
   reco_ele_pfphotonisorel_citk_barrel_signal->Reset();
   reco_ele_pfphotoniso_citk_endcap_signal->Reset();
   reco_ele_pfphotonisorel_citk_endcap_signal->Reset();

   reco_ele_pfchhadiso_citk_bkg->Reset();
   reco_ele_pfchhadisorel_citk_bkg->Reset();
   reco_ele_pfchhadiso_citk_barrel_bkg->Reset();
   reco_ele_pfchhadisorel_citk_barrel_bkg->Reset();
   reco_ele_pfchhadiso_citk_endcap_bkg->Reset();
   reco_ele_pfchhadisorel_citk_endcap_bkg->Reset();
   reco_ele_pfnehadiso_citk_bkg->Reset();
   reco_ele_pfnehadisorel_citk_bkg->Reset();
   reco_ele_pfnehadiso_citk_barrel_bkg->Reset();
   reco_ele_pfnehadisorel_citk_barrel_bkg->Reset();
   reco_ele_pfnehadiso_citk_endcap_bkg->Reset();
   reco_ele_pfnehadisorel_citk_endcap_bkg->Reset();
   reco_ele_pfphotoniso_citk_bkg->Reset();
   reco_ele_pfphotonisorel_citk_bkg->Reset();
   reco_ele_pfphotoniso_citk_barrel_bkg->Reset();
   reco_ele_pfphotonisorel_citk_barrel_bkg->Reset();
   reco_ele_pfphotoniso_citk_endcap_bkg->Reset();
   reco_ele_pfphotonisorel_citk_endcap_bkg->Reset();

   reco_ele_pfiso_simple->Reset();
   reco_ele_pfiso_simple_barrel->Reset();
   reco_ele_pfiso_simple_endcap->Reset();
   reco_ele_pfiso_simple_lowpu->Reset();
   reco_ele_pfiso_simple_medpu->Reset();
   reco_ele_pfiso_simple_highpu->Reset();

   reco_ele_pfiso_simple_signal->Reset();
   reco_ele_pfiso_simple_barrel_signal->Reset();
   reco_ele_pfiso_simple_endcap_signal->Reset();
   reco_ele_pfiso_simple_lowpu_signal->Reset();
   reco_ele_pfiso_simple_medpu_signal->Reset();
   reco_ele_pfiso_simple_highpu_signal->Reset();

   reco_ele_pfiso_simple_bkg->Reset();
   reco_ele_pfiso_simple_barrel_bkg->Reset();
   reco_ele_pfiso_simple_endcap_bkg->Reset();
   reco_ele_pfiso_simple_lowpu_bkg->Reset();
   reco_ele_pfiso_simple_medpu_bkg->Reset();
   reco_ele_pfiso_simple_highpu_bkg->Reset();


   reco_ele_pfiso_effarea->Reset();
   reco_ele_pfiso_effarea_barrel->Reset();
   reco_ele_pfiso_effarea_endcap->Reset();
   reco_ele_pfiso_effarea_lowpu->Reset();
   reco_ele_pfiso_effarea_medpu->Reset();
   reco_ele_pfiso_effarea_highpu->Reset();

   reco_ele_pfiso_effarea_signal->Reset();
   reco_ele_pfiso_effarea_barrel_signal->Reset();
   reco_ele_pfiso_effarea_endcap_signal->Reset();
   reco_ele_pfiso_effarea_lowpu_signal->Reset();
   reco_ele_pfiso_effarea_medpu_signal->Reset();
   reco_ele_pfiso_effarea_highpu_signal->Reset();

   reco_ele_pfiso_effarea_bkg->Reset();
   reco_ele_pfiso_effarea_barrel_bkg->Reset();
   reco_ele_pfiso_effarea_endcap_bkg->Reset();
   reco_ele_pfiso_effarea_lowpu_bkg->Reset();
   reco_ele_pfiso_effarea_medpu_bkg->Reset();
   reco_ele_pfiso_effarea_highpu_bkg->Reset();


   reco_ele_pfiso_deltabeta->Reset();
   reco_ele_pfiso_deltabeta_barrel->Reset();
   reco_ele_pfiso_deltabeta_endcap->Reset();
   reco_ele_pfiso_deltabeta_lowpu->Reset();
   reco_ele_pfiso_deltabeta_medpu->Reset();
   reco_ele_pfiso_deltabeta_highpu->Reset();

   reco_ele_pfiso_deltabeta_signal->Reset();
   reco_ele_pfiso_deltabeta_barrel_signal->Reset();
   reco_ele_pfiso_deltabeta_endcap_signal->Reset();
   reco_ele_pfiso_deltabeta_lowpu_signal->Reset();
   reco_ele_pfiso_deltabeta_medpu_signal->Reset();
   reco_ele_pfiso_deltabeta_highpu_signal->Reset();

   reco_ele_pfiso_deltabeta_bkg->Reset();
   reco_ele_pfiso_deltabeta_barrel_bkg->Reset();
   reco_ele_pfiso_deltabeta_endcap_bkg->Reset();
   reco_ele_pfiso_deltabeta_lowpu_bkg->Reset();
   reco_ele_pfiso_deltabeta_medpu_bkg->Reset();
   reco_ele_pfiso_deltabeta_highpu_bkg->Reset();


   reco_ele_pfiso_puppi->Reset();
   reco_ele_pfiso_puppi_barrel->Reset();
   reco_ele_pfiso_puppi_endcap->Reset();
   reco_ele_pfiso_puppi_lowpu->Reset();
   reco_ele_pfiso_puppi_medpu->Reset();
   reco_ele_pfiso_puppi_highpu->Reset();

   reco_ele_pfiso_puppi_signal->Reset();
   reco_ele_pfiso_puppi_barrel_signal->Reset();
   reco_ele_pfiso_puppi_endcap_signal->Reset();
   reco_ele_pfiso_puppi_lowpu_signal->Reset();
   reco_ele_pfiso_puppi_medpu_signal->Reset();
   reco_ele_pfiso_puppi_highpu_signal->Reset();

   reco_ele_pfiso_puppi_bkg->Reset();
   reco_ele_pfiso_puppi_barrel_bkg->Reset();
   reco_ele_pfiso_puppi_endcap_bkg->Reset();
   reco_ele_pfiso_puppi_lowpu_bkg->Reset();
   reco_ele_pfiso_puppi_medpu_bkg->Reset();
   reco_ele_pfiso_puppi_highpu_bkg->Reset();


   reco_ele_pfiso_puppinl->Reset();
   reco_ele_pfiso_puppinl_barrel->Reset();
   reco_ele_pfiso_puppinl_endcap->Reset();
   reco_ele_pfiso_puppinl_lowpu->Reset();
   reco_ele_pfiso_puppinl_medpu->Reset();
   reco_ele_pfiso_puppinl_highpu->Reset();

   reco_ele_pfiso_puppinl_signal->Reset();
   reco_ele_pfiso_puppinl_barrel_signal->Reset();
   reco_ele_pfiso_puppinl_endcap_signal->Reset();
   reco_ele_pfiso_puppinl_lowpu_signal->Reset();
   reco_ele_pfiso_puppinl_medpu_signal->Reset();
   reco_ele_pfiso_puppinl_highpu_signal->Reset();

   reco_ele_pfiso_puppinl_bkg->Reset();
   reco_ele_pfiso_puppinl_barrel_bkg->Reset();
   reco_ele_pfiso_puppinl_endcap_bkg->Reset();
   reco_ele_pfiso_puppinl_lowpu_bkg->Reset();
   reco_ele_pfiso_puppinl_medpu_bkg->Reset();
   reco_ele_pfiso_puppinl_highpu_bkg->Reset();


   reco_ele_pfiso_citk->Reset();
   reco_ele_pfiso_citk_barrel->Reset();
   reco_ele_pfiso_citk_endcap->Reset();
   reco_ele_pfiso_citk_lowpu->Reset();
   reco_ele_pfiso_citk_medpu->Reset();
   reco_ele_pfiso_citk_highpu->Reset();

   reco_ele_pfiso_citk_signal->Reset();
   reco_ele_pfiso_citk_barrel_signal->Reset();
   reco_ele_pfiso_citk_endcap_signal->Reset();
   reco_ele_pfiso_citk_lowpu_signal->Reset();
   reco_ele_pfiso_citk_medpu_signal->Reset();
   reco_ele_pfiso_citk_highpu_signal->Reset();

   reco_ele_pfiso_citk_bkg->Reset();
   reco_ele_pfiso_citk_barrel_bkg->Reset();
   reco_ele_pfiso_citk_endcap_bkg->Reset();
   reco_ele_pfiso_citk_lowpu_bkg->Reset();
   reco_ele_pfiso_citk_medpu_bkg->Reset();
   reco_ele_pfiso_citk_highpu_bkg->Reset();

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

   reco_ele_bdt_signal->Reset();
   reco_ele_bdt_barrel_signal->Reset();
   reco_ele_bdt_endcap_signal->Reset();
   reco_ele_sip_signal->Reset();
   reco_ele_sip_barrel_signal->Reset();
   reco_ele_sip_endcap_signal->Reset();
   reco_ele_id_signal->Reset();
   reco_ele_isgood_signal->Reset();
   leading_reco_ele_pt_signal->Reset();
   leading_reco_ele_eta_signal->Reset();
   leading_reco_ele_phi_signal->Reset();

   reco_ele_bdt_bkg->Reset();
   reco_ele_bdt_barrel_bkg->Reset();
   reco_ele_bdt_endcap_bkg->Reset();
   reco_ele_sip_bkg->Reset();
   reco_ele_sip_barrel_bkg->Reset();
   reco_ele_sip_endcap_bkg->Reset();
   reco_ele_id_bkg->Reset();
   reco_ele_isgood_bkg->Reset();
   leading_reco_ele_pt_bkg->Reset();
   leading_reco_ele_eta_bkg->Reset();
   leading_reco_ele_phi_bkg->Reset();
   
   iso_simple_vs_pt->Reset();
   iso_simple_vs_vtx->Reset();
   iso_simple_vs_eta->Reset();

   iso_simple_vs_pt_signal->Reset();
   iso_simple_vs_vtx_signal->Reset();
   iso_simple_vs_eta_signal->Reset();

   iso_simple_vs_pt_bkg->Reset();
   iso_simple_vs_vtx_bkg->Reset();
   iso_simple_vs_eta_bkg->Reset();
   
   iso_effarea_vs_pt->Reset();
   iso_effarea_vs_vtx->Reset();
   iso_effarea_vs_eta->Reset();

   iso_effarea_vs_pt_signal->Reset();
   iso_effarea_vs_vtx_signal->Reset();
   iso_effarea_vs_eta_signal->Reset();

   iso_effarea_vs_pt_bkg->Reset();
   iso_effarea_vs_vtx_bkg->Reset();
   iso_effarea_vs_eta_bkg->Reset();
   

   iso_deltabeta_vs_pt->Reset();
   iso_deltabeta_vs_vtx->Reset();
   iso_deltabeta_vs_eta->Reset();

   iso_deltabeta_vs_pt_signal->Reset();
   iso_deltabeta_vs_vtx_signal->Reset();
   iso_deltabeta_vs_eta_signal->Reset();

   iso_deltabeta_vs_pt_bkg->Reset();
   iso_deltabeta_vs_vtx_bkg->Reset();
   iso_deltabeta_vs_eta_bkg->Reset();


   iso_puppi_vs_pt->Reset();
   iso_puppi_vs_vtx->Reset();
   iso_puppi_vs_eta->Reset();

   iso_puppi_vs_pt_signal->Reset();
   iso_puppi_vs_vtx_signal->Reset();
   iso_puppi_vs_eta_signal->Reset();

   iso_puppi_vs_pt_bkg->Reset();
   iso_puppi_vs_vtx_bkg->Reset();
   iso_puppi_vs_eta_bkg->Reset();

   
   iso_puppinl_vs_pt->Reset();
   iso_puppinl_vs_vtx->Reset();
   iso_puppinl_vs_eta->Reset();
   
   iso_puppinl_vs_pt_signal->Reset();
   iso_puppinl_vs_vtx_signal->Reset();
   iso_puppinl_vs_eta_signal->Reset();

   iso_puppinl_vs_pt_bkg->Reset();
   iso_puppinl_vs_vtx_bkg->Reset();
   iso_puppinl_vs_eta_bkg->Reset();

   iso_citk_vs_pt->Reset();
   iso_citk_vs_vtx->Reset();
   iso_citk_vs_eta->Reset();

   iso_citk_vs_pt_signal->Reset();
   iso_citk_vs_vtx_signal->Reset();
   iso_citk_vs_eta_signal->Reset();

   iso_citk_vs_pt_bkg->Reset();
   iso_citk_vs_vtx_bkg->Reset();
   iso_citk_vs_eta_bkg->Reset();

   selected_electrons[s] = 0;
   selected_electrons_signal[s] = 0;
   selected_electrons_bkg[s] = 0;
   for (int y=0; y<1000; ++y)
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
	}

   for (int y=0; y<100; ++y)
	{
	sip[s][y] = 0;
	sip_barrel[s][y] = 0;
	sip_endcap[s][y] = 0;
	bdt[s][y] = 0;
	bdt_barrel[s][y] = 0;
	bdt_endcap[s][y] = 0;
	}
	
    Int_t entries = chain[s]->GetEntries();
    if (test) { entries = 250; }
    cout << "Total Events: " << entries << endl;

    for (int z=0; z<entries; ++z)
	{

	max_reco_pt = 0.0;
	id_leading_reco = -1;
	disp_ini_info = false;

	candidate1 = -1;
	candidate2 = -1;
	zzpair_candidate = -1;
	extra_candidate = -1;

	chain[s]->GetEntry(z);
	if (detail or test) { cout << "z = " << z << " of " << entries << endl; }
	if (detail or test) { cout << "Number of Electrons = " << nele << endl; }
	if (detail) { cout << "Event Number = " << nEvent << endl; }
	if (detail) { cout << "Run Number = " << nRun << endl; }
	if (detail) { cout << "Lumi Block = " << nLumi << endl; }
	if (detail) { cout << "Number of Primary Vertexes = " << nPV << endl; }
	if (detail) { cout << "Electron Rho = " << rho << endl; }
	vertex_multiplicity->Fill(nPV);
	evt_rho->Fill(rho);
	reco_ele_multiplicity->Fill(nele);

	if (detail) { cout << "Reconstructed Electrons = " << nele << endl; }
	for(int iReco=0; iReco<nele; iReco++)
		{
		if (detail)
			{ cout << "#" << iReco << " pt = " << ele_pt[iReco] << " eta = " << ele_sclEta[iReco] << " phi = " << ele_phi[iReco] << endl;
			cout << "Charge = " << ele_charge[iReco] << endl;
                	//cout << " dxy = " << ele_dxy[iReco] << " dz = " << ele_dz[iReco] << " missing hits = " << ele_missingHit[iReco] << endl;
			//cout << " Effective Area = " << ele_effarea[iReco] << endl;
			//cout << " PF charged hadron isolation = " << ele_PFChargedHadIso[iReco] << endl;
			//cout << " PF neutral hadron isolation = " << ele_PFNeutralHadIso[iReco] << endl;
			//cout << " PF photon isolation = " << ele_PFPhotonIso[iReco] << endl;
			//cout << " PF charged hadron isolation with PUPPI = " << ele_PFChargedHadIso_PUPPI[iReco] << endl;
			//cout << " PF neutral hadron isolation with PUPPI = " << ele_PFNeutralHadIso_PUPPI[iReco] << endl;
			//cout << " PF photon isolation with PUPPI = " << ele_PFPhotonIso_PUPPI[iReco] << endl;
			//cout << " PF charged hadron isolation with PUPPI No Leptons = " << ele_PFChargedHadIso_PUPPINL[iReco] << endl;
			//cout << " PF neutral hadron isolation with PUPPI No Leptons = " << ele_PFNeutralHadIso_PUPPINL[iReco] << endl;
			//cout << " PF photon isolation with PUPPI No Leptons = " << ele_PFPhotonIso_PUPPINL[iReco] << endl;
			//cout << " PF charged hadron isolation with CITK = " << ele_PFChargedHadIso_CITK[iReco] << endl;
			//cout << " PF neutral hadron isolation with CITK = " << ele_PFNeutralHadIso_CITK[iReco] << endl;
			//cout << " PF photon isolation with CITK = " << ele_PFPhotonIso_CITK[iReco] << endl;
			//cout << " PF isolation simple = " << ele_PFIso_simple[iReco] << endl;
			//cout << " PF isolation Effective Area = " << ele_PFIso_effarea[iReco] << endl;
			//cout << " PF isolation Delta Beta = " << ele_PFIso_deltabeta[iReco] << endl;
                	//cout << " Electron BDT = " << ele_BDT[iReco] << " is BDT? " << ele_isBDT[iReco] << endl;
			//cout << " Electron SIP = " << ele_SIP[iReco] << endl;
			//cout << " Id = " << ele_ID[iReco] << " Electron Is Good = " << ele_isGood[iReco] << endl;
			}


		ele_PFPhotonIsoRel_PUPPINL[iReco] = ele_PFPhotonIso_PUPPINL[iReco] / ele_pt[iReco];


		if (ele_pt[iReco] > 20.0 and (TMath::Abs(ele_sclEta[iReco])) < 2.5 and ele_isBDT[iReco] == 1 and ele_PFIso_effarea[iReco] < 0.1 and candidate1 == -1)
			{
			candidate1 = iReco;
			if (test) { cout << " Candidate 1 selected " << endl; }
			if (test) { cout << "#" << iReco << " pt = " << ele_pt[iReco] << " eta = " << ele_sclEta[iReco] << " phi = " << ele_phi[iReco] << endl; }
			}
		if (ele_pt[iReco] > 10.0 and (TMath::Abs(ele_sclEta[iReco])) < 2.5 and ele_isBDT[iReco] == 1 and candidate1 > -1 and ele_charge[iReco] != ele_charge[candidate1] and candidate1 != iReco and candidate2 == -1)
			{
			candidate2 = iReco;
			if (test) { cout << " Candidate 2 selected " << endl; }
			if (test) { cout << "#" << iReco << " pt = " << ele_pt[iReco] << " eta = " << ele_sclEta[iReco] << " phi = " << ele_phi[iReco] << endl; }
			}
		if (candidate1 > -1 and candidate2 > -1 and zzpair_candidate == -1)
			{
			if (ele_pt[candidate1] + ele_pt[candidate2] > 60 and  ele_pt[candidate1] + ele_pt[candidate2] < 120) 
				{
				zzpair_candidate = 1;
				if (test) { cout << " ZZ Pair formed! " << endl; }
				}
			}

		if (zzpair_candidate == 1 and ele_pt[iReco] > 7.0 and (TMath::Abs(ele_sclEta[iReco])) < 2.5 and ele_dxy[iReco] < 0.5 and ele_dz[iReco] < 1.0 and  ele_PFIso_effarea[candidate1] < 0.1 and  ele_PFIso_effarea[candidate2] < 0.1 and met_et < 25.0 and candidate2 != iReco and extra_candidate == -1)
			{
			extra_candidate = iReco;
			if (test) { cout << " Fake selected" << endl; }
			if (test) { cout << "#" << iReco << " pt = " << ele_pt[iReco] << " eta = " << ele_sclEta[iReco] << " phi = " << ele_phi[iReco] << endl; }
			}

		if (ele_pt[iReco] > 7.0 and (TMath::Abs(ele_sclEta[iReco])) < 2.5 and ele_dxy[iReco] < 0.5 and ele_dz[iReco] < 1.0)
		{
		if (ele_pt[iReco] > max_reco_pt) { max_reco_pt = ele_pt[iReco]; id_leading_reco = iReco; }

		selected_electrons[s] = selected_electrons[s] + 1;	
		reco_ele_pt->Fill(ele_pt[iReco]);
		reco_ele_eta->Fill(ele_sclEta[iReco]);
		reco_ele_phi->Fill(ele_phi[iReco]);
		reco_ele_charge->Fill(ele_charge[iReco]);
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
			reco_ele_pfchhadisorel_barrel->Fill(ele_PFChargedHadIsoRel[iReco]);
			reco_ele_pfnehadiso_barrel->Fill(ele_PFNeutralHadIso[iReco]);
			reco_ele_pfnehadisorel_barrel->Fill(ele_PFNeutralHadIsoRel[iReco]);
			reco_ele_pfphotoniso_barrel->Fill(ele_PFPhotonIso[iReco]);
			reco_ele_pfphotonisorel_barrel->Fill(ele_PFPhotonIsoRel[iReco]);
			reco_ele_pfchargedfrompu_barrel->Fill(ele_PFChargedFromPU[iReco]);
			reco_ele_pfchargedfrompurel_barrel->Fill(ele_PFChargedFromPURel[iReco]);

			reco_ele_pfchhadiso_puppi_barrel->Fill(ele_PFChargedHadIso_PUPPI[iReco]);
			reco_ele_pfchhadisorel_puppi_barrel->Fill(ele_PFChargedHadIsoRel_PUPPI[iReco]);
			reco_ele_pfnehadiso_puppi_barrel->Fill(ele_PFNeutralHadIso_PUPPI[iReco]);
			reco_ele_pfnehadisorel_puppi_barrel->Fill(ele_PFNeutralHadIsoRel_PUPPI[iReco]);
			reco_ele_pfphotoniso_puppi_barrel->Fill(ele_PFPhotonIso_PUPPI[iReco]);
			reco_ele_pfphotonisorel_puppi_barrel->Fill(ele_PFPhotonIsoRel_PUPPI[iReco]);

			reco_ele_pfchhadiso_puppinl_barrel->Fill(ele_PFChargedHadIso_PUPPINL[iReco]);
			reco_ele_pfchhadisorel_puppinl_barrel->Fill(ele_PFChargedHadIsoRel_PUPPINL[iReco]);
			reco_ele_pfnehadiso_puppinl_barrel->Fill(ele_PFNeutralHadIso_PUPPINL[iReco]);
			reco_ele_pfnehadisorel_puppinl_barrel->Fill(ele_PFNeutralHadIsoRel_PUPPINL[iReco]);
			reco_ele_pfphotoniso_puppinl_barrel->Fill(ele_PFPhotonIso_PUPPINL[iReco]);
			reco_ele_pfphotonisorel_puppinl_barrel->Fill(ele_PFPhotonIsoRel_PUPPINL[iReco]);

			reco_ele_pfchhadiso_citk_barrel->Fill(ele_PFChargedHadIso_CITK[iReco]);
			reco_ele_pfchhadisorel_citk_barrel->Fill(ele_PFChargedHadIsoRel_CITK[iReco]);
			reco_ele_pfnehadiso_citk_barrel->Fill(ele_PFNeutralHadIso_CITK[iReco]);
			reco_ele_pfnehadisorel_citk_barrel->Fill(ele_PFNeutralHadIsoRel_CITK[iReco]);
			reco_ele_pfphotoniso_citk_barrel->Fill(ele_PFPhotonIso_CITK[iReco]);
			reco_ele_pfphotonisorel_citk_barrel->Fill(ele_PFPhotonIsoRel_CITK[iReco]);

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
			reco_ele_pfchhadisorel_endcap->Fill(ele_PFChargedHadIsoRel[iReco]);
			reco_ele_pfnehadiso_endcap->Fill(ele_PFNeutralHadIso[iReco]);
			reco_ele_pfnehadisorel_endcap->Fill(ele_PFNeutralHadIsoRel[iReco]);
			reco_ele_pfphotoniso_endcap->Fill(ele_PFPhotonIso[iReco]);
			reco_ele_pfphotonisorel_endcap->Fill(ele_PFPhotonIsoRel[iReco]);
			reco_ele_pfchargedfrompu_endcap->Fill(ele_PFChargedFromPU[iReco]);
			reco_ele_pfchargedfrompurel_endcap->Fill(ele_PFChargedFromPURel[iReco]);

			reco_ele_pfchhadiso_puppi_endcap->Fill(ele_PFChargedHadIso_PUPPI[iReco]);
			reco_ele_pfchhadisorel_puppi_endcap->Fill(ele_PFChargedHadIsoRel_PUPPI[iReco]);
			reco_ele_pfnehadiso_puppi_endcap->Fill(ele_PFNeutralHadIso_PUPPI[iReco]);
			reco_ele_pfnehadisorel_puppi_endcap->Fill(ele_PFNeutralHadIsoRel_PUPPI[iReco]);
			reco_ele_pfphotoniso_puppi_endcap->Fill(ele_PFPhotonIso_PUPPI[iReco]);
			reco_ele_pfphotonisorel_puppi_endcap->Fill(ele_PFPhotonIsoRel_PUPPI[iReco]);

			reco_ele_pfchhadiso_puppinl_endcap->Fill(ele_PFChargedHadIso_PUPPINL[iReco]);
			reco_ele_pfchhadisorel_puppinl_endcap->Fill(ele_PFChargedHadIsoRel_PUPPINL[iReco]);
			reco_ele_pfnehadiso_puppinl_endcap->Fill(ele_PFNeutralHadIso_PUPPINL[iReco]);
			reco_ele_pfnehadisorel_puppinl_endcap->Fill(ele_PFNeutralHadIsoRel_PUPPINL[iReco]);
			reco_ele_pfphotoniso_puppinl_endcap->Fill(ele_PFPhotonIso_PUPPINL[iReco]);
			reco_ele_pfphotonisorel_puppinl_endcap->Fill(ele_PFPhotonIsoRel_PUPPINL[iReco]);

			reco_ele_pfchhadiso_citk_endcap->Fill(ele_PFChargedHadIso_CITK[iReco]);
			reco_ele_pfchhadisorel_citk_endcap->Fill(ele_PFChargedHadIsoRel_CITK[iReco]);
			reco_ele_pfnehadiso_citk_endcap->Fill(ele_PFNeutralHadIso_CITK[iReco]);
			reco_ele_pfnehadisorel_citk_endcap->Fill(ele_PFNeutralHadIsoRel_CITK[iReco]);
			reco_ele_pfphotoniso_citk_endcap->Fill(ele_PFPhotonIso_CITK[iReco]);
			reco_ele_pfphotonisorel_citk_endcap->Fill(ele_PFPhotonIsoRel_CITK[iReco]);

			reco_ele_pfiso_simple_endcap->Fill(ele_PFIso_simple[iReco]);
			reco_ele_pfiso_effarea_endcap->Fill(ele_PFIso_effarea[iReco]);
			reco_ele_pfiso_deltabeta_endcap->Fill(ele_PFIso_deltabeta[iReco]);
			reco_ele_pfiso_puppi_endcap->Fill(ele_PFIso_PUPPI[iReco]);
			reco_ele_pfiso_puppinl_endcap->Fill(ele_PFIso_PUPPINL[iReco]);
			reco_ele_pfiso_citk_endcap->Fill(ele_PFIso_CITK[iReco]);
			}
		}

	for(int iReco=0; iReco<nele; iReco++)
		{
		if (zzpair_candidate == 1 and ele_pt[iReco] > 7.0 and (TMath::Abs(ele_sclEta[iReco])) < 2.5 and ele_dxy[iReco] < 0.5 and ele_dz[iReco] < 1.0 and candidate1 != iReco and candidate2 != iReco and extra_candidate == -1)
			{
			extra_candidate = iReco;
			if (test) { cout << " Fake selected" << endl; }
			if (test) { cout << "#" << iReco << " pt = " << ele_pt[iReco] << " eta = " << ele_sclEta[iReco] << " phi = " << ele_phi[iReco] << endl; }
			}
		}

		if (zzpair_candidate == 1)
			{
			selected_electrons_signal[s] = selected_electrons_signal[s] + 1;
			vertex_multiplicity_signal->Fill(nPV);
			evt_rho_signal->Fill(rho);
			reco_ele_multiplicity_signal->Fill(nele);

			reco_ele_pt_signal->Fill(ele_pt[candidate2]);
			reco_ele_eta_signal->Fill(ele_sclEta[candidate2]);
			reco_ele_phi_signal->Fill(ele_phi[candidate2]);
			reco_ele_charge_signal->Fill(ele_charge[candidate2]);
			reco_ele_effarea_signal->Fill(ele_effarea[candidate2]);
			reco_ele_dxy_signal->Fill(ele_dxy[candidate2]);
			reco_ele_dz_signal->Fill(ele_dz[candidate2]);
			reco_ele_missinghit_signal->Fill(ele_missingHit[candidate2]);

			reco_ele_pfchhadiso_signal->Fill(ele_PFChargedHadIso[candidate2]);
			reco_ele_pfchhadisorel_signal->Fill(ele_PFChargedHadIsoRel[candidate2]);
			reco_ele_pfnehadiso_signal->Fill(ele_PFNeutralHadIso[candidate2]);
			reco_ele_pfnehadisorel_signal->Fill(ele_PFNeutralHadIsoRel[candidate2]);
			reco_ele_pfphotoniso_signal->Fill(ele_PFPhotonIso[candidate2]);
			reco_ele_pfphotonisorel_signal->Fill(ele_PFPhotonIsoRel[candidate2]);
			reco_ele_pfchargedfrompu_signal->Fill(ele_PFChargedFromPU[candidate2]);
			reco_ele_pfchargedfrompurel_signal->Fill(ele_PFChargedFromPURel[candidate2]);

			reco_ele_pfchhadiso_puppi_signal->Fill(ele_PFChargedHadIso_PUPPI[candidate2]);
			reco_ele_pfchhadisorel_puppi_signal->Fill(ele_PFChargedHadIsoRel_PUPPI[candidate2]);
			reco_ele_pfnehadiso_puppi_signal->Fill(ele_PFNeutralHadIso_PUPPI[candidate2]);
			reco_ele_pfnehadisorel_puppi_signal->Fill(ele_PFNeutralHadIsoRel_PUPPI[candidate2]);
			reco_ele_pfphotoniso_puppi_signal->Fill(ele_PFPhotonIso_PUPPI[candidate2]);
			reco_ele_pfphotonisorel_puppi_signal->Fill(ele_PFPhotonIsoRel_PUPPI[candidate2]);

			reco_ele_pfchhadiso_puppinl_signal->Fill(ele_PFChargedHadIso_PUPPINL[candidate2]);
			reco_ele_pfchhadisorel_puppinl_signal->Fill(ele_PFChargedHadIsoRel_PUPPINL[candidate2]);
			reco_ele_pfnehadiso_puppinl_signal->Fill(ele_PFNeutralHadIso_PUPPINL[candidate2]);
			reco_ele_pfnehadisorel_puppinl_signal->Fill(ele_PFNeutralHadIsoRel_PUPPINL[candidate2]);
			reco_ele_pfphotoniso_puppinl_signal->Fill(ele_PFPhotonIso_PUPPINL[candidate2]);
			reco_ele_pfphotonisorel_puppinl_signal->Fill(ele_PFPhotonIsoRel_PUPPINL[candidate2]);

			reco_ele_pfchhadiso_citk_signal->Fill(ele_PFChargedHadIso_CITK[candidate2]);
			reco_ele_pfchhadisorel_citk_signal->Fill(ele_PFChargedHadIsoRel_CITK[candidate2]);
			reco_ele_pfnehadiso_citk_signal->Fill(ele_PFNeutralHadIso_CITK[candidate2]);
			reco_ele_pfnehadisorel_citk_signal->Fill(ele_PFNeutralHadIsoRel_CITK[candidate2]);
			reco_ele_pfphotoniso_citk_signal->Fill(ele_PFPhotonIso_CITK[candidate2]);
			reco_ele_pfphotonisorel_citk_signal->Fill(ele_PFPhotonIsoRel_CITK[candidate2]);

			reco_ele_pfiso_simple_signal->Fill(ele_PFIso_simple[candidate2]);
			reco_ele_pfiso_effarea_signal->Fill(ele_PFIso_effarea[candidate2]);
			reco_ele_pfiso_deltabeta_signal->Fill(ele_PFIso_deltabeta[candidate2]);
			reco_ele_pfiso_puppi_signal->Fill(ele_PFIso_PUPPI[candidate2]);
			reco_ele_pfiso_puppinl_signal->Fill(ele_PFIso_PUPPINL[candidate2]);
			reco_ele_pfiso_citk_signal->Fill(ele_PFIso_CITK[candidate2]);

			iso_simple_vs_pt_signal->Fill(ele_PFIso_simple[candidate2],ele_pt[candidate2]);
			iso_simple_vs_vtx_signal->Fill(ele_PFIso_simple[candidate2],nPV);
			iso_simple_vs_eta_signal->Fill(ele_PFIso_simple[candidate2],ele_sclEta[candidate2]);
			iso_effarea_vs_pt_signal->Fill(ele_PFIso_effarea[candidate2],ele_pt[candidate2]);
			iso_effarea_vs_vtx_signal->Fill(ele_PFIso_effarea[candidate2],nPV);
			iso_effarea_vs_eta_signal->Fill(ele_PFIso_effarea[candidate2],ele_sclEta[candidate2]);
			iso_deltabeta_vs_pt_signal->Fill(ele_PFIso_deltabeta[candidate2],ele_pt[candidate2]);
			iso_deltabeta_vs_vtx_signal->Fill(ele_PFIso_deltabeta[candidate2],nPV);
			iso_deltabeta_vs_eta_signal->Fill(ele_PFIso_deltabeta[candidate2],ele_sclEta[candidate2]);
			iso_puppi_vs_pt_signal->Fill(ele_PFIso_PUPPI[candidate2],ele_pt[candidate2]);
			iso_puppi_vs_vtx_signal->Fill(ele_PFIso_PUPPI[candidate2],nPV);
			iso_puppi_vs_eta_signal->Fill(ele_PFIso_PUPPI[candidate2],ele_sclEta[candidate2]);
			iso_puppinl_vs_pt_signal->Fill(ele_PFIso_PUPPINL[candidate2],ele_pt[candidate2]);
			iso_puppinl_vs_vtx_signal->Fill(ele_PFIso_PUPPINL[candidate2],nPV);
			iso_puppinl_vs_eta_signal->Fill(ele_PFIso_PUPPINL[candidate2],ele_sclEta[candidate2]);
			iso_citk_vs_pt_signal->Fill(ele_PFIso_CITK[candidate2],ele_pt[candidate2]);
			iso_citk_vs_vtx_signal->Fill(ele_PFIso_CITK[candidate2],nPV);
			iso_citk_vs_eta_signal->Fill(ele_PFIso_CITK[candidate2],ele_sclEta[candidate2]);
	
			
			if (nPV <= 15)
				{
				reco_ele_pfiso_simple_lowpu_signal->Fill(ele_PFIso_simple[candidate2]);
				reco_ele_pfiso_effarea_lowpu_signal->Fill(ele_PFIso_effarea[candidate2]);
				reco_ele_pfiso_deltabeta_lowpu_signal->Fill(ele_PFIso_deltabeta[candidate2]);
				reco_ele_pfiso_puppi_lowpu_signal->Fill(ele_PFIso_PUPPI[candidate2]);
				reco_ele_pfiso_puppinl_lowpu_signal->Fill(ele_PFIso_PUPPINL[candidate2]);
				reco_ele_pfiso_citk_lowpu_signal->Fill(ele_PFIso_CITK[candidate2]);
				}
			if (nPV > 15 and nPV < 25)
				{
				reco_ele_pfiso_simple_medpu_signal->Fill(ele_PFIso_simple[candidate2]);
				reco_ele_pfiso_effarea_medpu_signal->Fill(ele_PFIso_effarea[candidate2]);
				reco_ele_pfiso_deltabeta_medpu_signal->Fill(ele_PFIso_deltabeta[candidate2]);
				reco_ele_pfiso_puppi_medpu_signal->Fill(ele_PFIso_PUPPI[candidate2]);
				reco_ele_pfiso_puppinl_medpu_signal->Fill(ele_PFIso_PUPPINL[candidate2]);
				reco_ele_pfiso_citk_medpu_signal->Fill(ele_PFIso_CITK[candidate2]);
				}
			if (nPV >= 25)
				{
				reco_ele_pfiso_simple_highpu_signal->Fill(ele_PFIso_simple[candidate2]);
				reco_ele_pfiso_effarea_highpu_signal->Fill(ele_PFIso_effarea[candidate2]);
				reco_ele_pfiso_deltabeta_highpu_signal->Fill(ele_PFIso_deltabeta[candidate2]);
				reco_ele_pfiso_puppi_highpu_signal->Fill(ele_PFIso_PUPPI[candidate2]);
				reco_ele_pfiso_puppinl_highpu_signal->Fill(ele_PFIso_PUPPINL[candidate2]);
				reco_ele_pfiso_citk_highpu_signal->Fill(ele_PFIso_CITK[candidate2]);
				}


			reco_ele_bdt_signal->Fill(ele_BDT[candidate2]);
			reco_ele_sip_signal->Fill(ele_SIP[candidate2]);
			reco_ele_id_signal->Fill(ele_ID[candidate2]);
			reco_ele_isgood_signal->Fill(ele_isGood[candidate2]);

			if (TMath::Abs(ele_sclEta[candidate2]) < 1.479)
				{
				reco_ele_sip_barrel_signal->Fill(ele_SIP[candidate2]);
				reco_ele_bdt_barrel_signal->Fill(ele_BDT[candidate2]);

				reco_ele_pfchhadiso_barrel_signal->Fill(ele_PFChargedHadIso[candidate2]);
				reco_ele_pfchhadisorel_barrel_signal->Fill(ele_PFChargedHadIsoRel[candidate2]);
				reco_ele_pfnehadiso_barrel_signal->Fill(ele_PFNeutralHadIso[candidate2]);
				reco_ele_pfnehadisorel_barrel_signal->Fill(ele_PFNeutralHadIsoRel[candidate2]);
				reco_ele_pfphotoniso_barrel_signal->Fill(ele_PFPhotonIso[candidate2]);
				reco_ele_pfphotonisorel_barrel_signal->Fill(ele_PFPhotonIsoRel[candidate2]);
				reco_ele_pfchargedfrompu_barrel_signal->Fill(ele_PFChargedFromPU[candidate2]);
				reco_ele_pfchargedfrompurel_barrel_signal->Fill(ele_PFChargedFromPURel[candidate2]);
	
				reco_ele_pfchhadiso_puppi_barrel_signal->Fill(ele_PFChargedHadIso_PUPPI[candidate2]);
				reco_ele_pfnehadiso_puppi_barrel_signal->Fill(ele_PFNeutralHadIso_PUPPI[candidate2]);
				reco_ele_pfphotoniso_puppi_barrel_signal->Fill(ele_PFPhotonIso_PUPPI[candidate2]);
	
				reco_ele_pfchhadiso_puppinl_barrel_signal->Fill(ele_PFChargedHadIso_PUPPINL[candidate2]);
				reco_ele_pfnehadiso_puppinl_barrel_signal->Fill(ele_PFNeutralHadIso_PUPPINL[candidate2]);
				reco_ele_pfphotoniso_puppinl_barrel_signal->Fill(ele_PFPhotonIso_PUPPINL[candidate2]);
	
				reco_ele_pfchhadiso_citk_barrel_signal->Fill(ele_PFChargedHadIso_CITK[candidate2]);
				reco_ele_pfnehadiso_citk_barrel_signal->Fill(ele_PFNeutralHadIso_CITK[candidate2]);
				reco_ele_pfphotoniso_citk_barrel_signal->Fill(ele_PFPhotonIso_CITK[candidate2]);

				reco_ele_pfiso_simple_barrel_signal->Fill(ele_PFIso_simple[candidate2]);
				reco_ele_pfiso_effarea_barrel_signal->Fill(ele_PFIso_effarea[candidate2]);
				reco_ele_pfiso_deltabeta_barrel_signal->Fill(ele_PFIso_deltabeta[candidate2]);
				reco_ele_pfiso_puppi_barrel_signal->Fill(ele_PFIso_PUPPI[candidate2]);
				reco_ele_pfiso_puppinl_barrel_signal->Fill(ele_PFIso_PUPPINL[candidate2]);
				reco_ele_pfiso_citk_barrel_signal->Fill(ele_PFIso_CITK[candidate2]);
				}
			else
				{
				reco_ele_sip_endcap_signal->Fill(ele_SIP[candidate2]);
				reco_ele_bdt_endcap_signal->Fill(ele_BDT[candidate2]);

				reco_ele_pfchhadiso_endcap_signal->Fill(ele_PFChargedHadIso[candidate2]);
				reco_ele_pfchhadisorel_endcap_signal->Fill(ele_PFChargedHadIsoRel[candidate2]);
				reco_ele_pfnehadiso_endcap_signal->Fill(ele_PFNeutralHadIso[candidate2]);
				reco_ele_pfnehadisorel_endcap_signal->Fill(ele_PFNeutralHadIsoRel[candidate2]);
				reco_ele_pfphotoniso_endcap_signal->Fill(ele_PFPhotonIso[candidate2]);
				reco_ele_pfphotonisorel_endcap_signal->Fill(ele_PFPhotonIsoRel[candidate2]);
				reco_ele_pfchargedfrompu_endcap_signal->Fill(ele_PFChargedFromPU[candidate2]);
				reco_ele_pfchargedfrompurel_endcap_signal->Fill(ele_PFChargedFromPURel[candidate2]);
	
				reco_ele_pfchhadiso_puppi_endcap_signal->Fill(ele_PFChargedHadIso_PUPPI[candidate2]);
				reco_ele_pfnehadiso_puppi_endcap_signal->Fill(ele_PFNeutralHadIso_PUPPI[candidate2]);
				reco_ele_pfphotoniso_puppi_endcap_signal->Fill(ele_PFPhotonIso_PUPPI[candidate2]);
	
				reco_ele_pfchhadiso_puppinl_endcap_signal->Fill(ele_PFChargedHadIso_PUPPINL[candidate2]);
				reco_ele_pfnehadiso_puppinl_endcap_signal->Fill(ele_PFNeutralHadIso_PUPPINL[candidate2]);
				reco_ele_pfphotoniso_puppinl_endcap_signal->Fill(ele_PFPhotonIso_PUPPINL[candidate2]);
	
				reco_ele_pfchhadiso_citk_endcap_signal->Fill(ele_PFChargedHadIso_CITK[candidate2]);
				reco_ele_pfnehadiso_citk_endcap_signal->Fill(ele_PFNeutralHadIso_CITK[candidate2]);
				reco_ele_pfphotoniso_citk_endcap_signal->Fill(ele_PFPhotonIso_CITK[candidate2]);
	
				reco_ele_pfiso_simple_endcap_signal->Fill(ele_PFIso_simple[candidate2]);
				reco_ele_pfiso_effarea_endcap_signal->Fill(ele_PFIso_effarea[candidate2]);
				reco_ele_pfiso_deltabeta_endcap_signal->Fill(ele_PFIso_deltabeta[candidate2]);
				reco_ele_pfiso_puppi_endcap_signal->Fill(ele_PFIso_PUPPI[candidate2]);
				reco_ele_pfiso_puppinl_endcap_signal->Fill(ele_PFIso_PUPPINL[candidate2]);
				reco_ele_pfiso_citk_endcap_signal->Fill(ele_PFIso_CITK[candidate2]);
				}
	
			}

		if (extra_candidate > -1)
			{
			selected_electrons_bkg[s] = selected_electrons_bkg[s] + 1;
			vertex_multiplicity_bkg->Fill(nPV);
			evt_rho_bkg->Fill(rho);
			reco_ele_multiplicity_bkg->Fill(nele);

			reco_ele_pt_bkg->Fill(ele_pt[extra_candidate]);
			reco_ele_eta_bkg->Fill(ele_sclEta[extra_candidate]);
			reco_ele_phi_bkg->Fill(ele_phi[extra_candidate]);
			reco_ele_charge_bkg->Fill(ele_charge[extra_candidate]);
			reco_ele_effarea_bkg->Fill(ele_effarea[extra_candidate]);
			reco_ele_dxy_bkg->Fill(ele_dxy[extra_candidate]);
			reco_ele_dz_bkg->Fill(ele_dz[extra_candidate]);
			reco_ele_missinghit_bkg->Fill(ele_missingHit[extra_candidate]);

			reco_ele_pfchhadiso_bkg->Fill(ele_PFChargedHadIso[extra_candidate]);
			reco_ele_pfchhadisorel_bkg->Fill(ele_PFChargedHadIsoRel[extra_candidate]);
			reco_ele_pfnehadiso_bkg->Fill(ele_PFNeutralHadIso[extra_candidate]);
			reco_ele_pfnehadisorel_bkg->Fill(ele_PFNeutralHadIsoRel[extra_candidate]);
			reco_ele_pfphotoniso_bkg->Fill(ele_PFPhotonIso[extra_candidate]);
			reco_ele_pfphotonisorel_bkg->Fill(ele_PFPhotonIsoRel[extra_candidate]);
			reco_ele_pfchargedfrompu_bkg->Fill(ele_PFChargedFromPU[extra_candidate]);
			reco_ele_pfchargedfrompurel_bkg->Fill(ele_PFChargedFromPURel[extra_candidate]);

			reco_ele_pfchhadiso_puppi_bkg->Fill(ele_PFChargedHadIso_PUPPI[extra_candidate]);
			reco_ele_pfchhadisorel_puppi_bkg->Fill(ele_PFChargedHadIsoRel_PUPPI[extra_candidate]);
			reco_ele_pfnehadiso_puppi_bkg->Fill(ele_PFNeutralHadIso_PUPPI[extra_candidate]);
			reco_ele_pfnehadisorel_puppi_bkg->Fill(ele_PFNeutralHadIsoRel_PUPPI[extra_candidate]);
			reco_ele_pfphotoniso_puppi_bkg->Fill(ele_PFPhotonIso_PUPPI[extra_candidate]);
			reco_ele_pfphotonisorel_puppi_bkg->Fill(ele_PFPhotonIsoRel_PUPPI[extra_candidate]);

			reco_ele_pfchhadiso_puppinl_bkg->Fill(ele_PFChargedHadIso_PUPPINL[extra_candidate]);
			reco_ele_pfchhadisorel_puppinl_bkg->Fill(ele_PFChargedHadIsoRel_PUPPINL[extra_candidate]);
			reco_ele_pfnehadiso_puppinl_bkg->Fill(ele_PFNeutralHadIso_PUPPINL[extra_candidate]);
			reco_ele_pfnehadisorel_puppinl_bkg->Fill(ele_PFNeutralHadIsoRel_PUPPINL[extra_candidate]);
			reco_ele_pfphotoniso_puppinl_bkg->Fill(ele_PFPhotonIso_PUPPINL[extra_candidate]);
			reco_ele_pfphotonisorel_puppinl_bkg->Fill(ele_PFPhotonIsoRel_PUPPINL[extra_candidate]);

			reco_ele_pfchhadiso_citk_bkg->Fill(ele_PFChargedHadIso_CITK[extra_candidate]);
			reco_ele_pfchhadisorel_citk_bkg->Fill(ele_PFChargedHadIsoRel_CITK[extra_candidate]);
			reco_ele_pfnehadiso_citk_bkg->Fill(ele_PFNeutralHadIso_CITK[extra_candidate]);
			reco_ele_pfnehadisorel_citk_bkg->Fill(ele_PFNeutralHadIsoRel_CITK[extra_candidate]);
			reco_ele_pfphotoniso_citk_bkg->Fill(ele_PFPhotonIso_CITK[extra_candidate]);
			reco_ele_pfphotonisorel_citk_bkg->Fill(ele_PFPhotonIsoRel_CITK[extra_candidate]);

			reco_ele_pfiso_simple_bkg->Fill(ele_PFIso_simple[extra_candidate]);
			reco_ele_pfiso_effarea_bkg->Fill(ele_PFIso_effarea[extra_candidate]);
			reco_ele_pfiso_deltabeta_bkg->Fill(ele_PFIso_deltabeta[extra_candidate]);
			reco_ele_pfiso_puppi_bkg->Fill(ele_PFIso_PUPPI[extra_candidate]);
			reco_ele_pfiso_puppinl_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate]);
			reco_ele_pfiso_citk_bkg->Fill(ele_PFIso_CITK[extra_candidate]);

			iso_simple_vs_pt_bkg->Fill(ele_PFIso_simple[extra_candidate],ele_pt[extra_candidate]);
			iso_simple_vs_vtx_bkg->Fill(ele_PFIso_simple[extra_candidate],nPV);
			iso_simple_vs_eta_bkg->Fill(ele_PFIso_simple[extra_candidate],ele_sclEta[extra_candidate]);
			iso_effarea_vs_pt_bkg->Fill(ele_PFIso_effarea[extra_candidate],ele_pt[candidate2]);
			iso_effarea_vs_vtx_bkg->Fill(ele_PFIso_effarea[extra_candidate],nPV);
			iso_effarea_vs_eta_bkg->Fill(ele_PFIso_effarea[extra_candidate],ele_sclEta[extra_candidate]);
			iso_deltabeta_vs_pt_bkg->Fill(ele_PFIso_deltabeta[extra_candidate],ele_pt[extra_candidate]);
			iso_deltabeta_vs_vtx_bkg->Fill(ele_PFIso_deltabeta[extra_candidate],nPV);
			iso_deltabeta_vs_eta_bkg->Fill(ele_PFIso_deltabeta[extra_candidate],ele_sclEta[extra_candidate]);
			iso_puppi_vs_pt_bkg->Fill(ele_PFIso_PUPPI[extra_candidate],ele_pt[extra_candidate]);
			iso_puppi_vs_vtx_bkg->Fill(ele_PFIso_PUPPI[extra_candidate],nPV);
			iso_puppi_vs_eta_bkg->Fill(ele_PFIso_PUPPI[extra_candidate],ele_sclEta[extra_candidate]);
			iso_puppinl_vs_pt_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate],ele_pt[extra_candidate]);
			iso_puppinl_vs_vtx_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate],nPV);
			iso_puppinl_vs_eta_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate],ele_sclEta[extra_candidate]);
			iso_citk_vs_pt_bkg->Fill(ele_PFIso_CITK[extra_candidate],ele_pt[extra_candidate]);
			iso_citk_vs_vtx_bkg->Fill(ele_PFIso_CITK[extra_candidate],nPV);
			iso_citk_vs_eta_bkg->Fill(ele_PFIso_CITK[extra_candidate],ele_sclEta[extra_candidate]);
	
			
			if (nPV <= 15)
				{
				reco_ele_pfiso_simple_lowpu_bkg->Fill(ele_PFIso_simple[extra_candidate]);
				reco_ele_pfiso_effarea_lowpu_bkg->Fill(ele_PFIso_effarea[extra_candidate]);
				reco_ele_pfiso_deltabeta_lowpu_bkg->Fill(ele_PFIso_deltabeta[extra_candidate]);
				reco_ele_pfiso_puppi_lowpu_bkg->Fill(ele_PFIso_PUPPI[extra_candidate]);
				reco_ele_pfiso_puppinl_lowpu_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate]);
				reco_ele_pfiso_citk_lowpu_bkg->Fill(ele_PFIso_CITK[extra_candidate]);
				}
			if (nPV > 15 and nPV < 25)
				{
				reco_ele_pfiso_simple_medpu_bkg->Fill(ele_PFIso_simple[extra_candidate]);
				reco_ele_pfiso_effarea_medpu_bkg->Fill(ele_PFIso_effarea[extra_candidate]);
				reco_ele_pfiso_deltabeta_medpu_bkg->Fill(ele_PFIso_deltabeta[extra_candidate]);
				reco_ele_pfiso_puppi_medpu_bkg->Fill(ele_PFIso_PUPPI[extra_candidate]);
				reco_ele_pfiso_puppinl_medpu_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate]);
				reco_ele_pfiso_citk_medpu_bkg->Fill(ele_PFIso_CITK[extra_candidate]);
				}
			if (nPV >= 25)
				{
				reco_ele_pfiso_simple_highpu_bkg->Fill(ele_PFIso_simple[extra_candidate]);
				reco_ele_pfiso_effarea_highpu_bkg->Fill(ele_PFIso_effarea[extra_candidate]);
				reco_ele_pfiso_deltabeta_highpu_bkg->Fill(ele_PFIso_deltabeta[extra_candidate]);
				reco_ele_pfiso_puppi_highpu_bkg->Fill(ele_PFIso_PUPPI[extra_candidate]);
				reco_ele_pfiso_puppinl_highpu_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate]);
				reco_ele_pfiso_citk_highpu_bkg->Fill(ele_PFIso_CITK[extra_candidate]);
				}
			
			reco_ele_bdt_bkg->Fill(ele_BDT[extra_candidate]);
			reco_ele_sip_bkg->Fill(ele_SIP[extra_candidate]);
			reco_ele_id_bkg->Fill(ele_ID[extra_candidate]);
			reco_ele_isgood_bkg->Fill(ele_isGood[extra_candidate]);

			if (TMath::Abs(ele_sclEta[extra_candidate]) < 1.479)
				{
				reco_ele_sip_barrel_bkg->Fill(ele_SIP[extra_candidate]);
				reco_ele_bdt_barrel_bkg->Fill(ele_BDT[extra_candidate]);

				reco_ele_pfchhadiso_barrel_bkg->Fill(ele_PFChargedHadIso[extra_candidate]);
				reco_ele_pfchhadisorel_barrel_bkg->Fill(ele_PFChargedHadIsoRel[extra_candidate]);
				reco_ele_pfnehadiso_barrel_bkg->Fill(ele_PFNeutralHadIso[extra_candidate]);
				reco_ele_pfphotoniso_barrel_bkg->Fill(ele_PFPhotonIso[extra_candidate]);
				reco_ele_pfchargedfrompu_barrel_bkg->Fill(ele_PFChargedFromPU[extra_candidate]);

				reco_ele_pfchhadiso_puppi_barrel_bkg->Fill(ele_PFChargedHadIso_PUPPI[extra_candidate]);
				reco_ele_pfnehadiso_puppi_barrel_bkg->Fill(ele_PFNeutralHadIso_PUPPI[extra_candidate]);
				reco_ele_pfphotoniso_puppi_barrel_bkg->Fill(ele_PFPhotonIso_PUPPI[iReco]);

				reco_ele_pfchhadiso_puppinl_barrel_bkg->Fill(ele_PFChargedHadIso_PUPPINL[extra_candidate]);
				reco_ele_pfnehadiso_puppinl_barrel_bkg->Fill(ele_PFNeutralHadIso_PUPPINL[extra_candidate]);
				reco_ele_pfphotoniso_puppinl_barrel_bkg->Fill(ele_PFPhotonIso_PUPPINL[extra_candidate]);

				reco_ele_pfchhadiso_citk_barrel_bkg->Fill(ele_PFChargedHadIso_CITK[extra_candidate]);
				reco_ele_pfnehadiso_citk_barrel_bkg->Fill(ele_PFNeutralHadIso_CITK[extra_candidate]);
				reco_ele_pfphotoniso_citk_barrel_bkg->Fill(ele_PFPhotonIso_CITK[extra_candidate]);

				reco_ele_pfiso_simple_barrel_bkg->Fill(ele_PFIso_simple[extra_candidate]);
				reco_ele_pfiso_effarea_barrel_bkg->Fill(ele_PFIso_effarea[extra_candidate]);
				reco_ele_pfiso_deltabeta_barrel_bkg->Fill(ele_PFIso_deltabeta[extra_candidate]);
				reco_ele_pfiso_puppi_barrel_bkg->Fill(ele_PFIso_PUPPI[extra_candidate]);
				reco_ele_pfiso_puppinl_barrel_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate]);
				reco_ele_pfiso_citk_barrel_bkg->Fill(ele_PFIso_CITK[extra_candidate]);
				}
			else
				{
				reco_ele_sip_endcap_bkg->Fill(ele_SIP[extra_candidate]);
				reco_ele_bdt_endcap_bkg->Fill(ele_BDT[extra_candidate]);
				reco_ele_pfchhadiso_endcap_bkg->Fill(ele_PFChargedHadIso[extra_candidate]);
				reco_ele_pfnehadiso_endcap_bkg->Fill(ele_PFNeutralHadIso[extra_candidate]);
				reco_ele_pfphotoniso_endcap_bkg->Fill(ele_PFPhotonIso[extra_candidate]);
				reco_ele_pfchargedfrompu_endcap_bkg->Fill(ele_PFChargedFromPU[extra_candidate]);

				reco_ele_pfchhadiso_puppi_endcap_bkg->Fill(ele_PFChargedHadIso_PUPPI[extra_candidate]);
				reco_ele_pfnehadiso_puppi_endcap_bkg->Fill(ele_PFNeutralHadIso_PUPPI[extra_candidate]);
				reco_ele_pfphotoniso_puppi_endcap_bkg->Fill(ele_PFPhotonIso_PUPPI[extra_candidate]);

				reco_ele_pfchhadiso_puppinl_endcap_bkg->Fill(ele_PFChargedHadIso_PUPPINL[extra_candidate]);
				reco_ele_pfnehadiso_puppinl_endcap_bkg->Fill(ele_PFNeutralHadIso_PUPPINL[extra_candidate]);
				reco_ele_pfphotoniso_puppinl_endcap_bkg->Fill(ele_PFPhotonIso_PUPPINL[extra_candidate]);

				reco_ele_pfchhadiso_citk_endcap_bkg->Fill(ele_PFChargedHadIso_CITK[extra_candidate]);
				reco_ele_pfnehadiso_citk_endcap_bkg->Fill(ele_PFNeutralHadIso_CITK[extra_candidate]);
				reco_ele_pfphotoniso_citk_endcap_bkg->Fill(ele_PFPhotonIso_CITK[extra_candidate]);

				reco_ele_pfiso_simple_endcap_bkg->Fill(ele_PFIso_simple[extra_candidate]);
				reco_ele_pfiso_effarea_endcap_bkg->Fill(ele_PFIso_effarea[extra_candidate]);
				reco_ele_pfiso_deltabeta_endcap_bkg->Fill(ele_PFIso_deltabeta[extra_candidate]);
				reco_ele_pfiso_puppi_endcap_bkg->Fill(ele_PFIso_PUPPI[extra_candidate]);
				reco_ele_pfiso_puppinl_endcap_bkg->Fill(ele_PFIso_PUPPINL[extra_candidate]);
				reco_ele_pfiso_citk_endcap_bkg->Fill(ele_PFIso_CITK[extra_candidate]);
				}


			}



			

	if (id_leading_reco > -1)
		{
		leading_reco_ele_pt->Fill(ele_pt[id_leading_reco]);
		leading_reco_ele_eta->Fill(ele_sclEta[id_leading_reco]);
		leading_reco_ele_phi->Fill(ele_phi[id_leading_reco]);
		}

	}

	}


//normalization of the histograms
normalize_histogram(vertex_multiplicity, "Vertex Multiplicity", true, false);
normalize_histogram(evt_rho, "evt_rho", true, false);

normalize_histogram(vertex_multiplicity_signal, "Vertex Multiplicity Signal", true, false);
normalize_histogram(evt_rho_signal, "evt_rho_signal", true, false);

normalize_histogram(vertex_multiplicity_bkg, "Vertex Multiplicity Background", true, false);
normalize_histogram(evt_rho_bkg, "evt_rho_bkg", true, false);


normalize_histogram(reco_ele_multiplicity, "Reco Electron Multiplicity", true, false);
normalize_histogram(reco_ele_pt, "Reco Electron pT", true, false);
normalize_histogram(reco_ele_eta, "Reco Electron Eta", true, false);
normalize_histogram(reco_ele_phi, "Reco Electron Phi", true, false);
normalize_histogram(reco_ele_charge, "Reco Electron Charge", true, false);
normalize_histogram(reco_ele_effarea, "Reco Electron Effective Area", true, false);
normalize_histogram(reco_ele_dxy, "Reco Electron dxy", true, false);
normalize_histogram(reco_ele_dz, "Reco Electron dz", true, false);
normalize_histogram(reco_ele_missinghit, "Reco Electron Missing Hit", true, false);

normalize_histogram(reco_ele_multiplicity_signal, "Reco Electron Multiplicity Signal", true, false);
normalize_histogram(reco_ele_pt_signal, "Reco Electron pT Signal", true, false);
normalize_histogram(reco_ele_eta_signal, "Reco Electron Eta Signal", true, false);
normalize_histogram(reco_ele_phi_signal, "Reco Electron Phi Signal", true, false);
normalize_histogram(reco_ele_charge_signal, "Reco Electron Charge Signal", true, false);
normalize_histogram(reco_ele_effarea_signal, "Reco Electron Effective Area Signal", true, false);
normalize_histogram(reco_ele_dxy_signal, "Reco Electron dxy Signal", true, false);
normalize_histogram(reco_ele_dz_signal, "Reco Electron dz Siglnal", true, false);
normalize_histogram(reco_ele_missinghit_signal, "Reco Electron Missing Hit Signal", true, false);

normalize_histogram(reco_ele_multiplicity_bkg, "Reco Electron Multiplicity Background", true, false);
normalize_histogram(reco_ele_pt_bkg, "Reco Electron pT Background", true, false);
normalize_histogram(reco_ele_eta_bkg, "Reco Electron Eta Background", true, false);
normalize_histogram(reco_ele_phi_bkg, "Reco Electron Phi Background", true, false);
normalize_histogram(reco_ele_charge_bkg, "Reco Electron Charge Background", true, false);
normalize_histogram(reco_ele_effarea_bkg, "Reco Electron Effective Area Background", true, false);
normalize_histogram(reco_ele_dxy_bkg, "Reco Electron dxy Background", true, false);
normalize_histogram(reco_ele_dz_bkg, "Reco Electron dz_ Background", true, false);
normalize_histogram(reco_ele_missinghit_bkg, "Reco Electron Missing Hit Background", true, false);

normalize_histogram(reco_ele_pfchhadiso, "Reco Electron Charged Hadron Isolation", true, false);
normalize_histogram(reco_ele_pfchhadisorel, "Reco Electron Charged Hadron Isolation Relative", true, false);
normalize_histogram(reco_ele_pfchhadiso_barrel, "Reco Electron Charged Hadron Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfchhadisorel_barrel, "Reco Electron Charged Hadron Relative Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_endcap, "Reco Electron Charged Hadron Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfchhadisorel_endcap, "Reco Electron Charged Hadron Relative Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfnehadiso, "Reco Electron Neutral Hadron Isolation", true, false);
normalize_histogram(reco_ele_pfnehadisorel, "Reco Electron Neutral Hadron Isolation Relative", true, false);
normalize_histogram(reco_ele_pfnehadiso_barrel, "Reco Electron Neutral Hadron Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfnehadisorel_barrel, "Reco Electron Neutral Hadron Relative Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_endcap, "Reco Electron Neutral Hadron Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfnehadisorel_endcap, "Reco Electron Neutral Hadron Relative Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfphotoniso, "Reco Electron Photon Isolation", true, false);
normalize_histogram(reco_ele_pfphotonisorel, "Reco Electron Photon Isolation Relative", true, false);
normalize_histogram(reco_ele_pfphotoniso_barrel, "Reco Electron Photon Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfphotonisorel_barrel, "Reco Electron Photon Relative Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_endcap, "Reco Electron Photon Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfphotonisorel_endcap, "Reco Electron Photon Relative Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfchargedfrompu, "Reco Electron Charged Hadrom From Pile-Up Isolation", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel, "Reco Electron Charged Hadrom From Pile-Up Isolation Relative", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_barrel, "Reco Electron Charged Hadrom From Pile-Up Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel_barrel, "Reco Electron Charged Hadrom From Pile-Up Relative Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_endcap, "Reco Electron Charged Hadrom From Pile-Up Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel_endcap, "Reco Electron Charged Hadrom From Pile-Up Relative Isolation EndCap", true, false);

normalize_histogram(reco_ele_pfchhadiso_signal, "Reco Electron Charged Hadron Isolation Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_signal, "Reco Electron Charged Hadron Isolation Relative Signal", true, false);
normalize_histogram(reco_ele_pfchhadiso_barrel_signal, "Reco Electron Charged Hadron Isolation Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_barrel_signal, "Reco Electron Charged Hadron Relative Isolation Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchhadiso_endcap_signal, "Reco Electron Charged Hadron Isolation EndCap Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_endcap_signal, "Reco Electron Charged Hadron Relative Isolation EndCap Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_signal, "Reco Electron Neutral Hadron Isolation Signal ", true, false);
normalize_histogram(reco_ele_pfnehadisorel_signal, "Reco Electron Neutral Hadron Isolation Relative Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_barrel_signal, "Reco Electron Neutral Hadron Isolation Barrel Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_barrel_signal, "Reco Electron Neutral Hadron Relative Isolation Barrel Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_endcap_signal, "Reco Electron Neutral Hadron Isolation EndCap Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_endcap_signal, "Reco Electron Neutral Hadron Relative Isolation EndCap Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_signal, "Reco Electron Photon Isolation Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_signal, "Reco Electron Photon Isolation Relative Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_barrel_signal, "Reco Electron Photon Relative Isolation Barrel Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_barrel_signal, "Reco Electron Photon Isolation Barrel Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_endcap_signal, "Reco Electron Photon relative Isolation EndCap Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_endcap_signal, "Reco Electron Photon Isolation EndCap Signal", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_signal, "Reco Electron Charged Hadrom From Pile-Up Isolation Signal", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel_signal, "Reco Electron Charged Hadrom From Pile-Up Isolation Relative Signal", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_barrel_signal, "Reco Electron Charged Hadrom From Pile-Up Isolation Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel_barrel_signal, "Reco Electron Charged Hadrom From Pile-Up Relative Isolation Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_endcap_signal, "Reco Electron Charged Hadrom From Pile-Up Isolation EndCap Signal", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel_endcap_signal, "Reco Electron Charged Hadrom From Pile-Up Relative Isolation EndCap Signal", true, false);

normalize_histogram(reco_ele_pfchhadiso_bkg, "Reco Electron Charged Hadron Isolation Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_bkg, "Reco Electron Charged Hadron Isolation Relative Background", true, false);
normalize_histogram(reco_ele_pfchhadiso_barrel_bkg, "Reco Electron Charged Hadron Isolation Barrel Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_barrel_bkg, "Reco Electron Charged Hadron Relative Isolation Barrel Background", true, false);
normalize_histogram(reco_ele_pfchhadiso_endcap_bkg, "Reco Electron Charged Hadron Isolation EndCap Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_endcap_bkg, "Reco Electron Charged Hadron Relative Isolation EndCap Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_bkg, "Reco Electron Neutral Hadron Isolation Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_bkg, "Reco Electron Neutral Hadron Isolation Relative Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_barrel_bkg, "Reco Electron Neutral Hadron Isolation Barrel Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_barrel_bkg, "Reco Electron Neutral Hadron Relative Isolation Barrel Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_endcap_bkg, "Reco Electron Neutral Hadron Isolation EndCap Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_endcap_bkg, "Reco Electron Neutral Hadron Relative Isolation EndCap Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_bkg, "Reco Electron Photon Isolation Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_bkg, "Reco Electron Photon Isolation Relative Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_barrel_bkg, "Reco Electron Photon Isolation Barrel Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_barrel_bkg, "Reco Electron Photon Relative Isolation Barrel Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_endcap_bkg, "Reco Electron Photon Isolation EndCap Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_endcap_bkg, "Reco Electron Photon Relative Isolation EndCap Background", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_bkg, "Reco Electron Charged Hadrom From Pile-Up Isolation Background", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel_bkg, "Reco Electron Charged Hadrom From Pile-Up Isolation Relative Background", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel_barrel_bkg, "Reco Electron Charged Hadrom From Pile-Up Relative Isolation Barrel Background", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_barrel_bkg, "Reco Electron Charged Hadrom From Pile-Up Isolation Barrel Background", true, false);
normalize_histogram(reco_ele_pfchargedfrompurel_endcap_bkg, "Reco Electron Charged Hadrom From Pile-Up Relative Isolation EndCap Background", true, false);
normalize_histogram(reco_ele_pfchargedfrompu_endcap_bkg, "Reco Electron Charged Hadrom From Pile-Up Isolation EndCap Background", true, false);


normalize_histogram(reco_ele_pfchhadiso_puppi, "Reco Electron Charged Hadron Isolation From PUPPI", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi, "Reco Electron Charged Hadron Isolation From PUPPI Relative", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppi_barrel, "Reco Electron Charged Hadron Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi_barrel, "Reco Electron Charged Hadron Relative Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppi_endcap, "Reco Electron Charged Hadron Isolation From PUPPI EndCap", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi_endcap, "Reco Electron Charged Hadron Relative Isolation From PUPPI EndCap", true, false);

normalize_histogram(reco_ele_pfchhadiso_puppi_signal, "Reco Electron Charged Hadron Isolation From PUPPI Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi_signal, "Reco Electron Charged Hadron Isolation From PUPPI Relative Signal", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppi_barrel_signal, "Reco Electron Charged Hadron Isolation From PUPPI Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi_barrel_signal, "Reco Electron Charged Hadron Relative Isolation From PUPPI Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppi_endcap_signal, "Reco Electron Charged Hadron Isolation From PUPPI EndCap Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi_endcap_signal, "Reco Electron Charged Hadron Relative Isolation From PUPPI EndCap Signal", true, false);

normalize_histogram(reco_ele_pfchhadiso_puppi_bkg, "Reco Electron Charged Hadron Isolation From PUPPI Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi_bkg, "Reco Electron Charged Hadron Isolation From PUPPI Relative Background", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppi_barrel_bkg, "Reco Electron Charged Hadron Isolation From PUPPI Barrel Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi_barrel_bkg, "Reco Electron Charged Hadron Relative Isolation From PUPPI Barrel Background", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppi_endcap_bkg, "Reco Electron Charged Hadron Isolation From PUPPI EndCap Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppi_endcap_bkg, "Reco Electron Charged Hadron Relative Isolation From PUPPI EndCap Background", true, false);


normalize_histogram(reco_ele_pfnehadiso_puppi, "Reco Electron Neutral Hadron Isolation From PUPPI", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi, "Reco Electron Neutral Hadron Isolation From PUPPI Relative", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppi_barrel, "Reco Electron Neutral Hadron Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi_barrel, "Reco Electron Neutral Hadron Relative Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppi_endcap, "Reco Electron Neutral Hadron Isolation From PUPPI EndCap", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi_endcap, "Reco Electron Neutral Hadron Relative Isolation From PUPPI EndCap", true, false);

normalize_histogram(reco_ele_pfnehadiso_puppi_signal, "Reco Electron Neutral Hadron Isolation From PUPPI Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi_signal, "Reco Electron Neutral Hadron Relative Isolation From PUPPI Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppi_barrel_signal, "Reco Electron Neutral Hadron Isolation From PUPPI Barrel Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi_barrel_signal, "Reco Electron Neutral Hadron Relative Isolation From PUPPI Barrel Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppi_endcap_signal, "Reco Electron Neutral Hadron Isolation From PUPPI EndCap Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi_endcap_signal, "Reco Electron Neutral Hadron Relative Isolation From PUPPI EndCap Signal", true, false);

normalize_histogram(reco_ele_pfnehadiso_puppi_bkg, "Reco Electron Neutral Hadron Isolation From PUPPI Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi_bkg, "Reco Electron Neutral Hadron Isolation From PUPPI Relative Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppi_barrel_bkg, "Reco Electron Neutral Hadron Isolation From PUPPI Barrel Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi_barrel_bkg, "Reco Electron Neutral Hadron Relative Isolation From PUPPI Barrel Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppi_endcap_bkg, "Reco Electron Neutral Hadron Isolation From PUPPI EndCap Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppi_endcap_bkg, "Reco Electron Neutral Hadron Relative Isolation From PUPPI EndCap Background", true, false);


normalize_histogram(reco_ele_pfphotoniso_puppi, "Reco Electron Photon Isolation From PUPPI", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi, "Reco Electron Photon Isolation From PUPPI Relative", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppi_barrel, "Reco Electron Photon Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi_barrel, "Reco Electron Photon Relative Isolation From PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppi_endcap, "Reco Electron Photon Isolation From PUPPI EndCap", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi_endcap, "Reco Electron Photon Relative Isolation From PUPPI EndCap", true, false);

normalize_histogram(reco_ele_pfphotoniso_puppi_signal, "Reco Electron Photon Isolation From PUPPI Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi_signal, "Reco Electron Photon Isolation From PUPPI Relative Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppi_barrel_signal, "Reco Electron Photon Isolation From PUPPI Barrel Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi_barrel_signal, "Reco Electron Photon Relative Isolation From PUPPI Barrel Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppi_endcap_signal, "Reco Electron Photon Isolation From PUPPI EndCap Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi_endcap_signal, "Reco Electron Photon Relative Isolation From PUPPI EndCap Signal", true, false);

normalize_histogram(reco_ele_pfphotoniso_puppi_bkg, "Reco Electron Photon Isolation From PUPPI Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi_bkg, "Reco Electron Photon Isolation From PUPPI Relative Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppi_barrel_bkg, "Reco Electron Photon Isolation From PUPPI Barrel Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi_barrel_bkg, "Reco Electron Photon Relative Isolation From PUPPI Barrel Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppi_endcap_bkg, "Reco Electron Photon Isolation From PUPPI EndCap Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppi_endcap_bkg, "Reco Electron Photon Relative Isolation From PUPPI EndCap Background", true, false);

normalize_histogram(reco_ele_pfchhadiso_puppinl, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Relative", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppinl_barrel, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl_barrel, "Reco Electron Charged Hadron Relative Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppinl_endcap, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons EndCap", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl_endcap, "Reco Electron Charged Hadron Relative Isolation From PUPPI No Leptons EndCap", true, false);

normalize_histogram(reco_ele_pfchhadiso_puppinl_signal, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl_signal, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Relative Signal", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppinl_barrel_signal, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl_barrel_signal, "Reco Electron Charged Hadron Relative Isolation From PUPPI No Leptons Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppinl_endcap_signal, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons EndCap Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl_endcap_signal, "Reco Electron Charged Hadron Relative Isolation From PUPPI No Leptons EndCap Signal", true, false);

normalize_histogram(reco_ele_pfchhadiso_puppinl_bkg, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl_bkg, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Relative Background", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppinl_barrel_bkg, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons Barrel Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl_barrel_bkg, "Reco Electron Charged Hadron Relative Isolation From PUPPI No Leptons Barrel Background", true, false);
normalize_histogram(reco_ele_pfchhadiso_puppinl_endcap_bkg, "Reco Electron Charged Hadron Isolation From PUPPI No Leptons EndCap Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_puppinl_endcap_bkg, "Reco Electron Charged Hadron Relative Isolation From PUPPI No Leptons EndCap Background", true, false);


normalize_histogram(reco_ele_pfnehadiso_puppinl, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Relative", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppinl_barrel, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl_barrel, "Reco Electron Neutral Hadron Relative Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppinl_endcap, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons EndCap", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl_endcap, "Reco Electron Neutral Hadron Relative Isolation From PUPPI No Leptons EndCap", true, false);

normalize_histogram(reco_ele_pfnehadiso_puppinl_signal, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl_signal, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Relative Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppinl_barrel_signal, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Barrel Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl_barrel_signal, "Reco Electron Neutral Hadron Relative Isolation From PUPPI No Leptons Barrel Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppinl_endcap_signal, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons EndCap Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl_endcap_signal, "Reco Electron Neutral Hadron Relative Isolation From PUPPI No Leptons EndCap Signal", true, false);

normalize_histogram(reco_ele_pfnehadiso_puppinl_bkg, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl_bkg, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Relative Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppinl_barrel_bkg, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons Barrel Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl_barrel_bkg, "Reco Electron Neutral Hadron Relative Isolation From PUPPI No Leptons Barrel Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_puppinl_endcap_bkg, "Reco Electron Neutral Hadron Isolation From PUPPI No Leptons EndCap Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_puppinl_endcap_bkg, "Reco Electron Neutral Hadron Relative Isolation From PUPPI No Leptons EndCap Background", true, false);


normalize_histogram(reco_ele_pfphotoniso_puppinl, "Reco Electron Photon Isolation From PUPPI No Leptons", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl, "Reco Electron Photon Isolation From PUPPI No Leptons Relative", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppinl_barrel, "Reco Electron Photon Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl_barrel, "Reco Electron Photon Relative Isolation From PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppinl_endcap, "Reco Electron Photon Isolation From PUPPI No Leptons EndCap", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl_endcap, "Reco Electron Photon Relative Isolation From PUPPI No Leptons EndCap", true, false);

normalize_histogram(reco_ele_pfphotoniso_puppinl_signal, "Reco Electron Photon Isolation From PUPPI No Leptons Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl_signal, "Reco Electron Photon Isolation From PUPPI No Leptons Relative Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppinl_barrel_signal, "Reco Electron Photon Isolation From PUPPI No Leptons Barrel Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl_barrel_signal, "Reco Electron Photon Relative Isolation From PUPPI No Leptons Barrel Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppinl_endcap_signal, "Reco Electron Photon Isolation From PUPPI No Leptons EndCap Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl_endcap_signal, "Reco Electron Photon Relative Isolation From PUPPI No Leptons EndCap Signal", true, false);

normalize_histogram(reco_ele_pfphotoniso_puppinl_bkg, "Reco Electron Photon Isolation From PUPPI No Leptons Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl_bkg, "Reco Electron Photon Isolation From PUPPI No Leptons Relative Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppinl_barrel_bkg, "Reco Electron Photon Isolation From PUPPI No Leptons Barrel Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl_barrel_bkg, "Reco Electron Photon Relative Isolation From PUPPI No Leptons Barrel Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_puppinl_endcap_bkg, "Reco Electron Photon Isolation From PUPPI No Leptons EndCap Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_puppinl_endcap_bkg, "Reco Electron Photon Relative Isolation From PUPPI No Leptons EndCap Background", true, false);

normalize_histogram(reco_ele_pfchhadiso_citk, "Reco Electron Charged Hadron Isolation From CITK", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk, "Reco Electron Charged Hadron Isolation From CITK Relative", true, false);
normalize_histogram(reco_ele_pfchhadiso_citk_barrel, "Reco Electron Charged Hadron Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk_barrel, "Reco Electron Charged Hadron Relative Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_citk_endcap, "Reco Electron Charged Hadron Isolation From CITK EndCap", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk_endcap, "Reco Electron Charged Hadron Relative Isolation From CITK EndCap", true, false);

normalize_histogram(reco_ele_pfchhadiso_citk_signal, "Reco Electron Charged Hadron Isolation From CITK Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk_signal, "Reco Electron Charged Hadron Relative Isolation From CITK Signal", true, false);
normalize_histogram(reco_ele_pfchhadiso_citk_barrel_signal, "Reco Electron Charged Hadron Isolation From CITK Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk_barrel_signal, "Reco Electron Charged Hadron Relative Isolation From CITK Barrel Signal", true, false);
normalize_histogram(reco_ele_pfchhadiso_citk_endcap_signal, "Reco Electron Charged Hadron Isolation From CITK EndCap Signal", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk_endcap_signal, "Reco Electron Charged Hadron Relative Isolation From CITK EndCap Signal", true, false);

normalize_histogram(reco_ele_pfchhadiso_citk_bkg, "Reco Electron Charged Hadron Isolation From CITK Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk_bkg, "Reco Electron Charged Hadron Relative Isolation From CITK Background", true, false);
normalize_histogram(reco_ele_pfchhadiso_citk_barrel_bkg, "Reco Electron Charged Hadron Isolation From CITK Barrel Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk_barrel_bkg, "Reco Electron Charged Hadron Relative Isolation From CITK Barrel Background", true, false);
normalize_histogram(reco_ele_pfchhadiso_citk_endcap_bkg, "Reco Electron Charged Hadron Isolation From CITK EndCap Background", true, false);
normalize_histogram(reco_ele_pfchhadisorel_citk_endcap_bkg, "Reco Electron Charged Hadron Relative Isolation From CITK EndCap Background", true, false);

normalize_histogram(reco_ele_pfnehadiso_citk, "Reco Electron Neutral Hadron Isolation From CITK", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk, "Reco Electron Neutral Hadron Isolation From CITK Relative", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk_barrel, "Reco Electron Neutral Hadron Relative Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_citk_barrel, "Reco Electron Neutral Hadron Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk_endcap, "Reco Electron Neutral Hadron Relative Isolation From CITK EndCap", true, false);
normalize_histogram(reco_ele_pfnehadiso_citk_endcap, "Reco Electron Neutral Hadron Isolation From CITK EndCap", true, false);


normalize_histogram(reco_ele_pfnehadiso_citk_signal, "Reco Electron Neutral Hadron Isolation From CITK Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk_signal, "Reco Electron Neutral Hadron Isolation From CITK Relative Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk_barrel_signal, "Reco Electron Neutral Hadron Relative Isolation From CITK Barrel Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_citk_barrel_signal, "Reco Electron Neutral Hadron Isolation From CITK Barrel Signal", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk_endcap_signal, "Reco Electron Neutral Hadron Relative Isolation From CITK EndCap Signal", true, false);
normalize_histogram(reco_ele_pfnehadiso_citk_endcap_signal, "Reco Electron Neutral Hadron Isolation From CITK EndCap Signal", true, false);

normalize_histogram(reco_ele_pfnehadiso_citk_bkg, "Reco Electron Neutral Hadron Isolation From CITK Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk_bkg, "Reco Electron Neutral Hadron Isolation From CITK Relative Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk_barrel_bkg, "Reco Electron Neutral Hadron Relative Isolation From CITK Barrel Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_citk_barrel_bkg, "Reco Electron Neutral Hadron Isolation From CITK Barrel Background", true, false);
normalize_histogram(reco_ele_pfnehadisorel_citk_endcap_bkg, "Reco Electron Neutral Hadron Relative Isolation From CITK EndCap Background", true, false);
normalize_histogram(reco_ele_pfnehadiso_citk_endcap_bkg, "Reco Electron Neutral Hadron Isolation From CITK EndCap Background", true, false);

normalize_histogram(reco_ele_pfphotoniso_citk, "Reco Electron Photon Isolation From CITK", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk, "Reco Electron Photon Isolation From CITK Relative", true, false);
normalize_histogram(reco_ele_pfphotoniso_citk_barrel, "Reco Electron Photon Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk_barrel, "Reco Electron Photon Relative Isolation From CITK Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_citk_endcap, "Reco Electron Photon Isolation From CITK EndCap", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk_endcap, "Reco Electron Photon Relative Isolation From CITK EndCap", true, false);

normalize_histogram(reco_ele_pfphotoniso_citk_signal, "Reco Electron Photon Isolation From CITK Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk_signal, "Reco Electron Photon Isolation From CITK Relative Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_citk_barrel_signal, "Reco Electron Photon Isolation From CITK Barrel Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk_barrel_signal, "Reco Electron Photon Relative Isolation From CITK Barrel Signal", true, false);
normalize_histogram(reco_ele_pfphotoniso_citk_endcap_signal, "Reco Electron Photon Isolation From CITK EndCap Signal", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk_endcap_signal, "Reco Electron Photon Relative Isolation From CITK EndCap Signal", true, false);

normalize_histogram(reco_ele_pfphotoniso_citk_bkg, "Reco Electron Photon Isolation From CITK Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk_bkg, "Reco Electron Photon Isolation From CITK Relative Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_citk_barrel_bkg, "Reco Electron Photon Isolation From CITK Barrel Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk_barrel_bkg, "Reco Electron Photon Relative Isolation From CITK Barrel Background", true, false);
normalize_histogram(reco_ele_pfphotoniso_citk_endcap_bkg, "Reco Electron Photon Isolation From CITK EndCap Background", true, false);
normalize_histogram(reco_ele_pfphotonisorel_citk_endcap_bkg, "Reco Electron Photon Relative Isolation From CITK EndCap Background", true, false);


normalize_histogram(reco_ele_pfiso_simple, "Reco ele PFIso Simple", true, false);
normalize_histogram(reco_ele_pfiso_simple_barrel, "Reco ele PFIso Simple Barrel", true, false);
normalize_histogram(reco_ele_pfiso_simple_endcap, "Reco ele PFIso Simple EndCap", true, false);
normalize_histogram(reco_ele_pfiso_simple_lowpu, "Reco ele PFIso Simple Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_simple_medpu, "Reco ele PFIso Simple Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_simple_highpu, "Reco ele PFIso Simple High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_simple_signal, "Reco ele PFIso Simple Signal", true, false);
normalize_histogram(reco_ele_pfiso_simple_barrel_signal, "Reco ele PFIso Simple Barrel Signal", true, false);
normalize_histogram(reco_ele_pfiso_simple_endcap_signal, "Reco ele PFIso Simple EndCap Signal", true, false);
normalize_histogram(reco_ele_pfiso_simple_lowpu_signal, "Reco ele PFIso Simple Low Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_simple_medpu_signal, "Reco ele PFIso Simple Medium Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_simple_highpu_signal, "Reco ele PFIso Simple High Pile-Up Signal", true, false);


normalize_histogram(reco_ele_pfiso_simple_bkg, "Reco ele PFIso Simple Background", true, false);
normalize_histogram(reco_ele_pfiso_simple_barrel_bkg, "Reco ele PFIso Simple Barrel Background", true, false);
normalize_histogram(reco_ele_pfiso_simple_endcap_bkg, "Reco ele PFIso Simple EndCap Background", true, false);
normalize_histogram(reco_ele_pfiso_simple_lowpu_bkg, "Reco ele PFIso Simple Low Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_simple_medpu_bkg, "Reco ele PFIso Simple Medium Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_simple_highpu_bkg, "Reco ele PFIso Simple High Pile-Up Background", true, false);

normalize_histogram(reco_ele_pfiso_effarea, "Reco ele PFIso EffArea", true, false);
normalize_histogram(reco_ele_pfiso_effarea_barrel, "Reco ele PFIso EffArea Barrel", true, false);
normalize_histogram(reco_ele_pfiso_effarea_endcap, "Reco ele PFIso EffArea EndCap", true, false);
normalize_histogram(reco_ele_pfiso_effarea_lowpu, "Reco ele PFIso EffArea Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_effarea_medpu, "Reco ele PFIso EffArea Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_effarea_highpu, "Reco ele PFIso EffArea High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_effarea_signal, "Reco ele PFIso EffArea Signal", true, false);
normalize_histogram(reco_ele_pfiso_effarea_barrel_signal, "Reco ele PFIso EffArea Barrel Signal", true, false);
normalize_histogram(reco_ele_pfiso_effarea_endcap_signal, "Reco ele PFIso EffArea EndCap Signal", true, false);
normalize_histogram(reco_ele_pfiso_effarea_lowpu_signal, "Reco ele PFIso EffArea Low Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_effarea_medpu_signal, "Reco ele PFIso EffArea Medium Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_effarea_highpu_signal, "Reco ele PFIso EffArea High Pile-Up Signal", true, false);

normalize_histogram(reco_ele_pfiso_effarea_bkg, "Reco ele PFIso EffArea Background", true, false);
normalize_histogram(reco_ele_pfiso_effarea_barrel_bkg, "Reco ele PFIso EffArea Barrel Background", true, false);
normalize_histogram(reco_ele_pfiso_effarea_endcap_bkg, "Reco ele PFIso EffArea EndCap Background", true, false);
normalize_histogram(reco_ele_pfiso_effarea_lowpu_bkg, "Reco ele PFIso EffArea Low Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_effarea_medpu_bkg, "Reco ele PFIso EffArea Medium Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_effarea_highpu_bkg, "Reco ele PFIso EffArea High Pile-Up Background", true, false);

normalize_histogram(reco_ele_pfiso_deltabeta, "Reco ele PFIso DeltaBeta", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_barrel, "Reco ele PFIso DeltaBeta Barrel", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_endcap, "Reco ele PFIso DeltaBeta EndCap", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_lowpu, "Reco ele PFIso DeltaBeta Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_medpu, "Reco ele PFIso DeltaBeta Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_highpu, "Reco ele PFIso DeltaBeta High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_deltabeta_signal, "Reco ele PFIso DeltaBeta Signal", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_barrel_signal, "Reco ele PFIso DeltaBeta Barrel Signal", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_endcap_signal, "Reco ele PFIso DeltaBeta EndCap Signal", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_lowpu_signal, "Reco ele PFIso DeltaBeta Low Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_medpu_signal, "Reco ele PFIso DeltaBeta Medium Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_highpu_signal, "Reco ele PFIso DeltaBeta High Pile-Up Signal", true, false);

normalize_histogram(reco_ele_pfiso_deltabeta_bkg, "Reco ele PFIso DeltaBeta Background", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_barrel_bkg, "Reco ele PFIso DeltaBeta Barrel Background", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_endcap_bkg, "Reco ele PFIso DeltaBeta EndCap Background", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_lowpu_bkg, "Reco ele PFIso DeltaBeta Low Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_medpu_bkg, "Reco ele PFIso DeltaBeta Medium Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_deltabeta_highpu_bkg, "Reco ele PFIso DeltaBeta High Pile-Up Background", true, false);

normalize_histogram(reco_ele_pfiso_puppi, "Reco ele PFIso PUPPI", true, false);
normalize_histogram(reco_ele_pfiso_puppi_barrel, "Reco ele PFIso PUPPI Barrel", true, false);
normalize_histogram(reco_ele_pfiso_puppi_endcap, "Reco ele PFIso PUPPI EndCap", true, false);
normalize_histogram(reco_ele_pfiso_puppi_lowpu, "Reco ele PFIso PUPPI Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_puppi_medpu, "Reco ele PFIso PUPPI Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_puppi_highpu, "Reco ele PFIso PUPPI High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_puppi_signal, "Reco ele PFIso PUPPI Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppi_barrel_signal, "Reco ele PFIso PUPPI Barrel Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppi_endcap_signal, "Reco ele PFIso PUPPI EndCap Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppi_lowpu_signal, "Reco ele PFIso PUPPI Low Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppi_medpu_signal, "Reco ele PFIso PUPPI Medium Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppi_highpu_signal, "Reco ele PFIso PUPPI High Pile-Up Signal", true, false);

normalize_histogram(reco_ele_pfiso_puppi_bkg, "Reco ele PFIso PUPPI Background", true, false);
normalize_histogram(reco_ele_pfiso_puppi_barrel_bkg, "Reco ele PFIso PUPPI Barrel Background", true, false);
normalize_histogram(reco_ele_pfiso_puppi_endcap_bkg, "Reco ele PFIso PUPPI EndCap Background", true, false);
normalize_histogram(reco_ele_pfiso_puppi_lowpu_bkg, "Reco ele PFIso PUPPI Low Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_puppi_medpu_bkg, "Reco ele PFIso PUPPI Medium Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_puppi_highpu_bkg, "Reco ele PFIso PUPPI High Pile-Up Background", true, false);


normalize_histogram(reco_ele_pfiso_puppinl, "Reco ele PFIso PUPPI No Leptons", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_barrel, "Reco ele PFIso PUPPI No Leptons Barrel", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_endcap, "Reco ele PFIso PUPPI No Leptons EndCap", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_lowpu, "Reco ele PFIso PUPPI No Leptons Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_medpu, "Reco ele PFIso PUPPI No Leptons Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_highpu, "Reco ele PFIso PUPPI No Leptons High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_puppinl_signal, "Reco ele PFIso PUPPI No Leptons Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_barrel_signal, "Reco ele PFIso PUPPI No Leptons Barrel Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_endcap_signal, "Reco ele PFIso PUPPI No Leptons EndCap Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_lowpu_signal, "Reco ele PFIso PUPPI No Leptons Low Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_medpu_signal, "Reco ele PFIso PUPPI No Leptons Medium Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_highpu_signal, "Reco ele PFIso PUPPI No Leptons High Pile-Up Signal", true, false);

normalize_histogram(reco_ele_pfiso_puppinl_bkg, "Reco ele PFIso PUPPI No Leptons Background", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_barrel_bkg, "Reco ele PFIso PUPPI No Leptons Barrel Background", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_endcap_bkg, "Reco ele PFIso PUPPI No Leptons EndCap Background", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_lowpu_bkg, "Reco ele PFIso PUPPI No Leptons Low Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_medpu_bkg, "Reco ele PFIso PUPPI No Leptons Medium Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_puppinl_highpu_bkg, "Reco ele PFIso PUPPI No Leptons High Pile-Up Background", true, false);

normalize_histogram(reco_ele_pfiso_citk, "Reco ele PFIso CITK", true, false);
normalize_histogram(reco_ele_pfiso_citk_barrel, "Reco ele PFIso CITK Barrel", true, false);
normalize_histogram(reco_ele_pfiso_citk_endcap, "Reco ele PFIso CITK EndCap", true, false);
normalize_histogram(reco_ele_pfiso_citk_lowpu, "Reco ele PFIso CITK Low Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_citk_medpu, "Reco ele PFIso CITK Medium Pile-Up", true, false);
normalize_histogram(reco_ele_pfiso_citk_highpu, "Reco ele PFIso CITK High Pile-Up", true, false);

normalize_histogram(reco_ele_pfiso_citk_signal, "Reco ele PFIso CITK Signal", true, false);
normalize_histogram(reco_ele_pfiso_citk_barrel_signal, "Reco ele PFIso CITK Barrel Signal", true, false);
normalize_histogram(reco_ele_pfiso_citk_endcap_signal, "Reco ele PFIso CITK EndCap Signal", true, false);
normalize_histogram(reco_ele_pfiso_citk_lowpu_signal, "Reco ele PFIso CITK Low Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_citk_medpu_signal, "Reco ele PFIso CITK Medium Pile-Up Signal", true, false);
normalize_histogram(reco_ele_pfiso_citk_highpu_signal, "Reco ele PFIso CITK High Pile-Up Signal", true, false);

normalize_histogram(reco_ele_pfiso_citk_bkg, "Reco ele PFIso CITK Background", true, false);
normalize_histogram(reco_ele_pfiso_citk_barrel_bkg, "Reco ele PFIso CITK Barrel Background", true, false);
normalize_histogram(reco_ele_pfiso_citk_endcap_bkg, "Reco ele PFIso CITK EndCap Background", true, false);
normalize_histogram(reco_ele_pfiso_citk_lowpu_bkg, "Reco ele PFIso CITK Low Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_citk_medpu_bkg, "Reco ele PFIso CITK Medium Pile-Up Background", true, false);
normalize_histogram(reco_ele_pfiso_citk_highpu_bkg, "Reco ele PFIso CITK High Pile-Up Background", true, false);

normalize_histogram(reco_ele_sip, "Reco ele SIP", true, false);
normalize_histogram(reco_ele_sip_barrel, "Reco ele SIP Barrel", true, false);
normalize_histogram(reco_ele_sip_endcap, "Reco ele SIP EndCap", true, false);
normalize_histogram(reco_ele_bdt, "Reco ele BDT", true, false);
normalize_histogram(reco_ele_bdt_barrel, "Reco ele BDT Barrel", true, false);
normalize_histogram(reco_ele_bdt_endcap, "Reco ele BDT EndCap", true, false);
normalize_histogram(reco_ele_id, "Reco ele ID", true, false);
normalize_histogram(reco_ele_isgood, "Reco ele isGood", true, false);

normalize_histogram(reco_ele_sip_signal, "Reco ele SIP Signal", true, false);
normalize_histogram(reco_ele_sip_barrel_signal, "Reco ele SIP Barrel Singal", true, false);
normalize_histogram(reco_ele_sip_endcap_signal, "Reco ele SIP EndCap", true, false);
normalize_histogram(reco_ele_bdt_signal, "Reco ele BDT", true, false);
normalize_histogram(reco_ele_bdt_barrel_signal, "Reco ele BDT Barrel", true, false);
normalize_histogram(reco_ele_bdt_endcap_signal, "Reco ele BDT EndCap", true, false);
normalize_histogram(reco_ele_id_signal, "Reco ele ID", true, false);
normalize_histogram(reco_ele_isgood_signal, "Reco ele isGood", true, false);

normalize_histogram(reco_ele_sip_bkg, "Reco ele SIP Background", true, false);
normalize_histogram(reco_ele_sip_barrel_bkg, "Reco ele SIP Barrel Background", true, false);
normalize_histogram(reco_ele_sip_endcap_bkg, "Reco ele SIP EndCap Background", true, false);
normalize_histogram(reco_ele_bdt_bkg, "Reco ele BDT Background", true, false);
normalize_histogram(reco_ele_bdt_barrel_bkg, "Reco ele BDT Barrel Background", true, false);
normalize_histogram(reco_ele_bdt_endcap_bkg, "Reco ele BDT EndCap Background", true, false);
normalize_histogram(reco_ele_id_bkg, "Reco ele ID Background", true, false);
normalize_histogram(reco_ele_isgood_bkg, "Reco ele isGood Backgroud", true, false);

normalize_histogram(leading_reco_ele_pt, "Leading_Reco_ele_pT", true, false);
normalize_histogram(leading_reco_ele_eta, "Leading_Reco_ele_Eta", true, false);
normalize_histogram(leading_reco_ele_phi, "Leading_Reco_ele_Phi", true, false);

int nbins = reco_ele_pfiso_simple->GetNbinsX();
int x;

for (x=1; x<=nbins; x++)
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
	}

nbins = reco_ele_sip->GetNbinsX();

for (x=1; x<=nbins; x++)
	{
	sip[s][x-1] = reco_ele_sip->Integral(0,x);
	sip_barrel[s][x-1] = reco_ele_sip_barrel->Integral(0,x);
	sip_endcap[s][x-1] = reco_ele_sip_endcap->Integral(0,x);
	bdt[s][x-1] = reco_ele_bdt->Integral(nbins-x,nbins);
	bdt_barrel[s][x-1] = reco_ele_bdt_barrel->Integral(nbins-x,nbins);
	bdt_endcap[s][x-1] = reco_ele_bdt_endcap->Integral(nbins-x,nbins);
	}

     	//Open the output root file
     	TFile *data_output= TFile::Open( out[s].c_str() , "RECREATE");

     	//save histograms on the file
	vertex_multiplicity->Write();
	evt_rho->Write();

	vertex_multiplicity_signal->Write();
	evt_rho_signal->Write();

	vertex_multiplicity_bkg->Write();
	evt_rho_bkg->Write();

	reco_ele_multiplicity->Write();
	reco_ele_pt->Write();
	reco_ele_eta->Write();
	reco_ele_phi->Write();
	reco_ele_charge->Write();
	reco_ele_effarea->Write();
	reco_ele_dxy->Write();
	reco_ele_dz->Write();
	reco_ele_missinghit->Write();

	reco_ele_multiplicity_signal->Write();
	reco_ele_pt_signal->Write();
	reco_ele_eta_signal->Write();
	reco_ele_phi_signal->Write();
	reco_ele_charge_signal->Write();
	reco_ele_effarea_signal->Write();
	reco_ele_dxy_signal->Write();
	reco_ele_dz_signal->Write();
	reco_ele_missinghit_signal->Write();

	reco_ele_multiplicity_bkg->Write();
	reco_ele_pt_bkg->Write();
	reco_ele_eta_bkg->Write();
	reco_ele_phi_bkg->Write();
	reco_ele_charge_bkg->Write();
	reco_ele_effarea_bkg->Write();
	reco_ele_dxy_bkg->Write();
	reco_ele_dz_bkg->Write();
	reco_ele_missinghit_bkg->Write();

	reco_ele_pfchhadiso->Write();
	reco_ele_pfchhadisorel->Write();
	reco_ele_pfchhadiso_barrel->Write();
	reco_ele_pfchhadisorel_barrel->Write();
	reco_ele_pfchhadiso_endcap->Write();
	reco_ele_pfchhadisorel_endcap->Write();
	reco_ele_pfnehadiso->Write();
	reco_ele_pfnehadisorel->Write();
	reco_ele_pfnehadiso_barrel->Write();
	reco_ele_pfnehadisorel_barrel->Write();
	reco_ele_pfnehadiso_endcap->Write();
	reco_ele_pfnehadisorel_endcap->Write();
	reco_ele_pfphotoniso->Write();
	reco_ele_pfphotonisorel->Write();
	reco_ele_pfphotoniso_barrel->Write();
	reco_ele_pfphotonisorel_barrel->Write();
	reco_ele_pfphotoniso_endcap->Write();
	reco_ele_pfphotonisorel_endcap->Write();
	reco_ele_pfchargedfrompu->Write();
	reco_ele_pfchargedfrompurel->Write();
	reco_ele_pfchargedfrompu_barrel->Write();
	reco_ele_pfchargedfrompurel_barrel->Write();
	reco_ele_pfchargedfrompu_endcap->Write();
	reco_ele_pfchargedfrompurel_endcap->Write();

	reco_ele_pfchhadiso_signal->Write();
	reco_ele_pfchhadisorel_signal->Write();
	reco_ele_pfchhadiso_barrel_signal->Write();
	reco_ele_pfchhadisorel_barrel_signal->Write();
	reco_ele_pfchhadiso_endcap_signal->Write();
	reco_ele_pfchhadisorel_endcap_signal->Write();
	reco_ele_pfnehadiso_signal->Write();
	reco_ele_pfnehadisorel_signal->Write();
	reco_ele_pfnehadiso_barrel_signal->Write();
	reco_ele_pfnehadisorel_barrel_signal->Write();
	reco_ele_pfnehadiso_endcap_signal->Write();
	reco_ele_pfnehadisorel_endcap_signal->Write();
	reco_ele_pfphotoniso_signal->Write();
	reco_ele_pfphotonisorel_signal->Write();
	reco_ele_pfphotoniso_barrel_signal->Write();
	reco_ele_pfphotonisorel_barrel_signal->Write();
	reco_ele_pfphotoniso_endcap_signal->Write();
	reco_ele_pfphotonisorel_endcap_signal->Write();
	reco_ele_pfchargedfrompu_signal->Write();
	reco_ele_pfchargedfrompurel_signal->Write();
	reco_ele_pfchargedfrompu_barrel_signal->Write();
	reco_ele_pfchargedfrompurel_barrel_signal->Write();
	reco_ele_pfchargedfrompu_endcap_signal->Write();
	reco_ele_pfchargedfrompurel_endcap_signal->Write();


	reco_ele_pfchhadiso_bkg->Write();
	reco_ele_pfchhadisorel_bkg->Write();
	reco_ele_pfchhadiso_barrel_bkg->Write();
	reco_ele_pfchhadisorel_barrel_bkg->Write();
	reco_ele_pfchhadiso_endcap_bkg->Write();
	reco_ele_pfchhadisorel_endcap_bkg->Write();
	reco_ele_pfnehadiso_bkg->Write();
	reco_ele_pfnehadisorel_bkg->Write();
	reco_ele_pfnehadiso_barrel_bkg->Write();
	reco_ele_pfnehadisorel_barrel_bkg->Write();
	reco_ele_pfnehadiso_endcap_bkg->Write();
	reco_ele_pfnehadisorel_endcap_bkg->Write();
	reco_ele_pfphotoniso_bkg->Write();
	reco_ele_pfphotonisorel_bkg->Write();
	reco_ele_pfphotoniso_barrel_bkg->Write();
	reco_ele_pfphotonisorel_barrel_bkg->Write();
	reco_ele_pfphotoniso_endcap_bkg->Write();
	reco_ele_pfphotonisorel_endcap_bkg->Write();
	reco_ele_pfchargedfrompu_bkg->Write();
	reco_ele_pfchargedfrompurel_bkg->Write();
	reco_ele_pfchargedfrompu_barrel_bkg->Write();
	reco_ele_pfchargedfrompurel_barrel_bkg->Write();
	reco_ele_pfchargedfrompu_endcap_bkg->Write();
	reco_ele_pfchargedfrompurel_endcap_bkg->Write();

	reco_ele_pfchhadiso_puppi->Write();
	reco_ele_pfchhadisorel_puppi->Write();
	reco_ele_pfchhadiso_puppi_barrel->Write();
	reco_ele_pfchhadisorel_puppi_barrel->Write();
	reco_ele_pfchhadiso_puppi_endcap->Write();
	reco_ele_pfchhadisorel_puppi_endcap->Write();
	reco_ele_pfnehadiso_puppi->Write();
	reco_ele_pfnehadisorel_puppi->Write();
	reco_ele_pfnehadiso_puppi_barrel->Write();
	reco_ele_pfnehadisorel_puppi_barrel->Write();
	reco_ele_pfnehadiso_puppi_endcap->Write();
	reco_ele_pfnehadisorel_puppi_endcap->Write();
	reco_ele_pfphotoniso_puppi->Write();
	reco_ele_pfphotonisorel_puppi->Write();
	reco_ele_pfphotoniso_puppi_barrel->Write();
	reco_ele_pfphotonisorel_puppi_barrel->Write();
	reco_ele_pfphotoniso_puppi_endcap->Write();
	reco_ele_pfphotonisorel_puppi_endcap->Write();

	reco_ele_pfchhadiso_puppi_signal->Write();
	reco_ele_pfchhadisorel_puppi_signal->Write();
	reco_ele_pfchhadiso_puppi_barrel_signal->Write();
	reco_ele_pfchhadisorel_puppi_barrel_signal->Write();
	reco_ele_pfchhadiso_puppi_endcap_signal->Write();
	reco_ele_pfchhadisorel_puppi_endcap_signal->Write();
	reco_ele_pfnehadiso_puppi_signal->Write();
	reco_ele_pfnehadisorel_puppi_signal->Write();
	reco_ele_pfnehadiso_puppi_barrel_signal->Write();
	reco_ele_pfnehadisorel_puppi_barrel_signal->Write();
	reco_ele_pfnehadiso_puppi_endcap_signal->Write();
	reco_ele_pfnehadisorel_puppi_endcap_signal->Write();
	reco_ele_pfphotoniso_puppi_signal->Write();
	reco_ele_pfphotonisorel_puppi_signal->Write();
	reco_ele_pfphotoniso_puppi_barrel_signal->Write();
	reco_ele_pfphotonisorel_puppi_barrel_signal->Write();
	reco_ele_pfphotoniso_puppi_endcap_signal->Write();
	reco_ele_pfphotonisorel_puppi_endcap_signal->Write();

	reco_ele_pfchhadiso_puppi_bkg->Write();
	reco_ele_pfchhadisorel_puppi_bkg->Write();
	reco_ele_pfchhadiso_puppi_barrel_bkg->Write();
	reco_ele_pfchhadisorel_puppi_barrel_bkg->Write();
	reco_ele_pfchhadiso_puppi_endcap_bkg->Write();
	reco_ele_pfchhadisorel_puppi_endcap_bkg->Write();
	reco_ele_pfnehadiso_puppi_bkg->Write();
	reco_ele_pfnehadisorel_puppi_bkg->Write();
	reco_ele_pfnehadiso_puppi_barrel_bkg->Write();
	reco_ele_pfnehadisorel_puppi_barrel_bkg->Write();
	reco_ele_pfnehadiso_puppi_endcap_bkg->Write();
	reco_ele_pfnehadisorel_puppi_endcap_bkg->Write();
	reco_ele_pfphotoniso_puppi_bkg->Write();
	reco_ele_pfphotonisorel_puppi_bkg->Write();
	reco_ele_pfphotoniso_puppi_barrel_bkg->Write();
	reco_ele_pfphotonisorel_puppi_barrel_bkg->Write();
	reco_ele_pfphotoniso_puppi_endcap_bkg->Write();
	reco_ele_pfphotonisorel_puppi_endcap_bkg->Write();

	reco_ele_pfchhadiso_puppinl->Write();
	reco_ele_pfchhadisorel_puppinl->Write();
	reco_ele_pfchhadiso_puppinl_barrel->Write();
	reco_ele_pfchhadisorel_puppinl_barrel->Write();
	reco_ele_pfchhadiso_puppinl_endcap->Write();
	reco_ele_pfchhadisorel_puppinl_endcap->Write();
	reco_ele_pfnehadiso_puppinl->Write();
	reco_ele_pfnehadisorel_puppinl->Write();
	reco_ele_pfnehadiso_puppinl_barrel->Write();
	reco_ele_pfnehadisorel_puppinl_barrel->Write();
	reco_ele_pfnehadiso_puppinl_endcap->Write();
	reco_ele_pfnehadisorel_puppinl_endcap->Write();
	reco_ele_pfphotoniso_puppinl->Write();
	reco_ele_pfphotonisorel_puppinl->Write();
	reco_ele_pfphotoniso_puppinl_barrel->Write();
	reco_ele_pfphotonisorel_puppinl_barrel->Write();
	reco_ele_pfphotoniso_puppinl_endcap->Write();
	reco_ele_pfphotonisorel_puppinl_endcap->Write();

	reco_ele_pfchhadiso_puppinl_signal->Write();
	reco_ele_pfchhadisorel_puppinl_signal->Write();
	reco_ele_pfchhadiso_puppinl_barrel_signal->Write();
	reco_ele_pfchhadisorel_puppinl_barrel_signal->Write();
	reco_ele_pfchhadiso_puppinl_endcap_signal->Write();
	reco_ele_pfchhadisorel_puppinl_endcap_signal->Write();
	reco_ele_pfnehadiso_puppinl_signal->Write();
	reco_ele_pfnehadisorel_puppinl_signal->Write();
	reco_ele_pfnehadiso_puppinl_barrel_signal->Write();
	reco_ele_pfnehadisorel_puppinl_barrel_signal->Write();
	reco_ele_pfnehadiso_puppinl_endcap_signal->Write();
	reco_ele_pfnehadisorel_puppinl_endcap_signal->Write();
	reco_ele_pfphotoniso_puppinl_signal->Write();
	reco_ele_pfphotonisorel_puppinl_signal->Write();
	reco_ele_pfphotoniso_puppinl_barrel_signal->Write();
	reco_ele_pfphotonisorel_puppinl_barrel_signal->Write();
	reco_ele_pfphotoniso_puppinl_endcap_signal->Write();
	reco_ele_pfphotonisorel_puppinl_endcap_signal->Write();

	reco_ele_pfchhadiso_puppinl_bkg->Write();
	reco_ele_pfchhadisorel_puppinl_bkg->Write();
	reco_ele_pfchhadiso_puppinl_barrel_bkg->Write();
	reco_ele_pfchhadisorel_puppinl_barrel_bkg->Write();
	reco_ele_pfchhadiso_puppinl_endcap_bkg->Write();
	reco_ele_pfchhadisorel_puppinl_endcap_bkg->Write();
	reco_ele_pfnehadiso_puppinl_bkg->Write();
	reco_ele_pfnehadisorel_puppinl_bkg->Write();
	reco_ele_pfnehadiso_puppinl_barrel_bkg->Write();
	reco_ele_pfnehadisorel_puppinl_barrel_bkg->Write();
	reco_ele_pfnehadiso_puppinl_endcap_bkg->Write();
	reco_ele_pfnehadisorel_puppinl_endcap_bkg->Write();
	reco_ele_pfphotoniso_puppinl_bkg->Write();
	reco_ele_pfphotonisorel_puppinl_bkg->Write();
	reco_ele_pfphotoniso_puppinl_barrel_bkg->Write();
	reco_ele_pfphotonisorel_puppinl_barrel_bkg->Write();
	reco_ele_pfphotoniso_puppinl_endcap_bkg->Write();
	reco_ele_pfphotonisorel_puppinl_endcap_bkg->Write();


	reco_ele_pfchhadiso_citk->Write();
	reco_ele_pfchhadisorel_citk->Write();
	reco_ele_pfchhadiso_citk_barrel->Write();
	reco_ele_pfchhadisorel_citk_barrel->Write();
	reco_ele_pfchhadiso_citk_endcap->Write();
	reco_ele_pfchhadisorel_citk_endcap->Write();
	reco_ele_pfnehadiso_citk->Write();
	reco_ele_pfnehadisorel_citk->Write();
	reco_ele_pfnehadiso_citk_barrel->Write();
	reco_ele_pfnehadisorel_citk_barrel->Write();
	reco_ele_pfnehadiso_citk_endcap->Write();
	reco_ele_pfnehadisorel_citk_endcap->Write();
	reco_ele_pfphotoniso_citk->Write();
	reco_ele_pfphotonisorel_citk->Write();
	reco_ele_pfphotoniso_citk_barrel->Write();
	reco_ele_pfphotonisorel_citk_barrel->Write();
	reco_ele_pfphotoniso_citk_endcap->Write();
	reco_ele_pfphotonisorel_citk_endcap->Write();

	reco_ele_pfchhadiso_citk_signal->Write();
	reco_ele_pfchhadisorel_citk_signal->Write();
	reco_ele_pfchhadiso_citk_barrel_signal->Write();
	reco_ele_pfchhadisorel_citk_barrel_signal->Write();
	reco_ele_pfchhadiso_citk_endcap_signal->Write();
	reco_ele_pfchhadisorel_citk_endcap_signal->Write();
	reco_ele_pfnehadiso_citk_signal->Write();
	reco_ele_pfnehadisorel_citk_signal->Write();
	reco_ele_pfnehadiso_citk_barrel_signal->Write();
	reco_ele_pfnehadisorel_citk_barrel_signal->Write();
	reco_ele_pfnehadiso_citk_endcap_signal->Write();
	reco_ele_pfnehadisorel_citk_endcap_signal->Write();
	reco_ele_pfphotoniso_citk_signal->Write();
	reco_ele_pfphotonisorel_citk_signal->Write();
	reco_ele_pfphotoniso_citk_barrel_signal->Write();
	reco_ele_pfphotonisorel_citk_barrel_signal->Write();
	reco_ele_pfphotoniso_citk_endcap_signal->Write();
	reco_ele_pfphotonisorel_citk_endcap_signal->Write();

	reco_ele_pfchhadiso_citk_bkg->Write();
	reco_ele_pfchhadisorel_citk_bkg->Write();
	reco_ele_pfchhadiso_citk_barrel_bkg->Write();
	reco_ele_pfchhadisorel_citk_barrel_bkg->Write();
	reco_ele_pfchhadiso_citk_endcap_bkg->Write();
	reco_ele_pfchhadisorel_citk_endcap_bkg->Write();
	reco_ele_pfnehadiso_citk_bkg->Write();
	reco_ele_pfnehadisorel_citk_bkg->Write();
	reco_ele_pfnehadiso_citk_barrel_bkg->Write();
	reco_ele_pfnehadisorel_citk_barrel_bkg->Write();
	reco_ele_pfnehadiso_citk_endcap_bkg->Write();
	reco_ele_pfnehadisorel_citk_endcap_bkg->Write();
	reco_ele_pfphotoniso_citk_bkg->Write();
	reco_ele_pfphotonisorel_citk_bkg->Write();
	reco_ele_pfphotoniso_citk_barrel_bkg->Write();
	reco_ele_pfphotonisorel_citk_barrel_bkg->Write();
	reco_ele_pfphotoniso_citk_endcap_bkg->Write();
	reco_ele_pfphotonisorel_citk_endcap_bkg->Write();

	reco_ele_pfiso_simple->Write();
	reco_ele_pfiso_simple_barrel->Write();
	reco_ele_pfiso_simple_endcap->Write();
	reco_ele_pfiso_simple_lowpu->Write();
	reco_ele_pfiso_simple_medpu->Write();
	reco_ele_pfiso_simple_highpu->Write();

	reco_ele_pfiso_simple_signal->Write();
	reco_ele_pfiso_simple_barrel_signal->Write();
	reco_ele_pfiso_simple_endcap_signal->Write();
	reco_ele_pfiso_simple_lowpu_signal->Write();
	reco_ele_pfiso_simple_medpu_signal->Write();
	reco_ele_pfiso_simple_highpu_signal->Write();

	reco_ele_pfiso_simple_bkg->Write();
	reco_ele_pfiso_simple_barrel_bkg->Write();
	reco_ele_pfiso_simple_endcap_bkg->Write();
	reco_ele_pfiso_simple_lowpu_bkg->Write();
	reco_ele_pfiso_simple_medpu_bkg->Write();
	reco_ele_pfiso_simple_highpu_bkg->Write();

	reco_ele_pfiso_effarea->Write();
	reco_ele_pfiso_effarea_barrel->Write();
	reco_ele_pfiso_effarea_endcap->Write();
	reco_ele_pfiso_effarea_lowpu->Write();
	reco_ele_pfiso_effarea_medpu->Write();
	reco_ele_pfiso_effarea_highpu->Write();

	reco_ele_pfiso_effarea_signal->Write();
	reco_ele_pfiso_effarea_barrel_signal->Write();
	reco_ele_pfiso_effarea_endcap_signal->Write();
	reco_ele_pfiso_effarea_lowpu_signal->Write();
	reco_ele_pfiso_effarea_medpu_signal->Write();
	reco_ele_pfiso_effarea_highpu_signal->Write();

	reco_ele_pfiso_effarea_bkg->Write();
	reco_ele_pfiso_effarea_barrel_bkg->Write();
	reco_ele_pfiso_effarea_endcap_bkg->Write();
	reco_ele_pfiso_effarea_lowpu_bkg->Write();
	reco_ele_pfiso_effarea_medpu_bkg->Write();
	reco_ele_pfiso_effarea_highpu_bkg->Write();

	reco_ele_pfiso_deltabeta->Write();
	reco_ele_pfiso_deltabeta_barrel->Write();
	reco_ele_pfiso_deltabeta_endcap->Write();
	reco_ele_pfiso_deltabeta_lowpu->Write();
	reco_ele_pfiso_deltabeta_medpu->Write();
	reco_ele_pfiso_deltabeta_highpu->Write();

	reco_ele_pfiso_deltabeta_signal->Write();
	reco_ele_pfiso_deltabeta_barrel_signal->Write();
	reco_ele_pfiso_deltabeta_endcap_signal->Write();
	reco_ele_pfiso_deltabeta_lowpu_signal->Write();
	reco_ele_pfiso_deltabeta_medpu_signal->Write();
	reco_ele_pfiso_deltabeta_highpu_signal->Write();

	reco_ele_pfiso_deltabeta_bkg->Write();
	reco_ele_pfiso_deltabeta_barrel_bkg->Write();
	reco_ele_pfiso_deltabeta_endcap_bkg->Write();
	reco_ele_pfiso_deltabeta_lowpu_bkg->Write();
	reco_ele_pfiso_deltabeta_medpu_bkg->Write();
	reco_ele_pfiso_deltabeta_highpu_bkg->Write();

	reco_ele_pfiso_puppi->Write();
	reco_ele_pfiso_puppi_barrel->Write();
	reco_ele_pfiso_puppi_endcap->Write();
	reco_ele_pfiso_puppi_lowpu->Write();
	reco_ele_pfiso_puppi_medpu->Write();
	reco_ele_pfiso_puppi_highpu->Write();

	reco_ele_pfiso_puppi_signal->Write();
	reco_ele_pfiso_puppi_barrel_signal->Write();
	reco_ele_pfiso_puppi_endcap_signal->Write();
	reco_ele_pfiso_puppi_lowpu_signal->Write();
	reco_ele_pfiso_puppi_medpu_signal->Write();
	reco_ele_pfiso_puppi_highpu_signal->Write();

	reco_ele_pfiso_puppi_bkg->Write();
	reco_ele_pfiso_puppi_barrel_bkg->Write();
	reco_ele_pfiso_puppi_endcap_bkg->Write();
	reco_ele_pfiso_puppi_lowpu_bkg->Write();
	reco_ele_pfiso_puppi_medpu_bkg->Write();
	reco_ele_pfiso_puppi_highpu_bkg->Write();

	reco_ele_pfiso_puppinl->Write();
	reco_ele_pfiso_puppinl_barrel->Write();
	reco_ele_pfiso_puppinl_endcap->Write();
	reco_ele_pfiso_puppinl_lowpu->Write();
	reco_ele_pfiso_puppinl_medpu->Write();
	reco_ele_pfiso_puppinl_highpu->Write();

	reco_ele_pfiso_puppinl_signal->Write();
	reco_ele_pfiso_puppinl_barrel_signal->Write();
	reco_ele_pfiso_puppinl_endcap_signal->Write();
	reco_ele_pfiso_puppinl_lowpu_signal->Write();
	reco_ele_pfiso_puppinl_medpu_signal->Write();
	reco_ele_pfiso_puppinl_highpu_signal->Write();

	reco_ele_pfiso_puppinl_bkg->Write();
	reco_ele_pfiso_puppinl_barrel_bkg->Write();
	reco_ele_pfiso_puppinl_endcap_bkg->Write();
	reco_ele_pfiso_puppinl_lowpu_bkg->Write();
	reco_ele_pfiso_puppinl_medpu_bkg->Write();
	reco_ele_pfiso_puppinl_highpu_bkg->Write();

	reco_ele_pfiso_citk->Write();
	reco_ele_pfiso_citk_barrel->Write();
	reco_ele_pfiso_citk_endcap->Write();
	reco_ele_pfiso_citk_lowpu->Write();
	reco_ele_pfiso_citk_medpu->Write();
	reco_ele_pfiso_citk_highpu->Write();

	reco_ele_pfiso_citk_signal->Write();
	reco_ele_pfiso_citk_barrel_signal->Write();
	reco_ele_pfiso_citk_endcap_signal->Write();
	reco_ele_pfiso_citk_lowpu_signal->Write();
	reco_ele_pfiso_citk_medpu_signal->Write();
	reco_ele_pfiso_citk_highpu_signal->Write();

	reco_ele_pfiso_citk_bkg->Write();
	reco_ele_pfiso_citk_barrel_bkg->Write();
	reco_ele_pfiso_citk_endcap_bkg->Write();
	reco_ele_pfiso_citk_lowpu_bkg->Write();
	reco_ele_pfiso_citk_medpu_bkg->Write();
	reco_ele_pfiso_citk_highpu_bkg->Write();

	reco_ele_bdt->Write();
	reco_ele_bdt_barrel->Write();
	reco_ele_bdt_endcap->Write();
	reco_ele_sip->Write();
	reco_ele_sip_barrel->Write();
	reco_ele_sip_endcap->Write();
	reco_ele_id->Write();
	reco_ele_isgood->Write();

	reco_ele_bdt_bkg->Write();
	reco_ele_bdt_barrel_bkg->Write();
	reco_ele_bdt_endcap_bkg->Write();
	reco_ele_sip_bkg->Write();
	reco_ele_sip_barrel_bkg->Write();
	reco_ele_sip_endcap_bkg->Write();
	reco_ele_id_bkg->Write();
	reco_ele_isgood_bkg->Write();

	reco_ele_bdt_bkg->Write();
	reco_ele_bdt_barrel_bkg->Write();
	reco_ele_bdt_endcap_bkg->Write();
	reco_ele_sip_bkg->Write();
	reco_ele_sip_barrel_bkg->Write();
	reco_ele_sip_endcap_bkg->Write();
	reco_ele_id_bkg->Write();
	reco_ele_isgood_bkg->Write();

	leading_reco_ele_pt->Write();
	leading_reco_ele_eta->Write();
	leading_reco_ele_phi->Write();
	
	iso_simple_vs_pt->Write();
	iso_simple_vs_vtx->Write();
	iso_simple_vs_eta->Write();

	iso_simple_vs_pt_signal->Write();
	iso_simple_vs_vtx_signal->Write();
	iso_simple_vs_eta_signal->Write();

	iso_simple_vs_pt_bkg->Write();
	iso_simple_vs_vtx_bkg->Write();
	iso_simple_vs_eta_bkg->Write();
	
	iso_effarea_vs_pt->Write();
	iso_effarea_vs_vtx->Write();
	iso_effarea_vs_eta->Write();

	iso_effarea_vs_pt_signal->Write();
	iso_effarea_vs_vtx_signal->Write();
	iso_effarea_vs_eta_signal->Write();

	iso_effarea_vs_pt_bkg->Write();
	iso_effarea_vs_vtx_bkg->Write();
	iso_effarea_vs_eta_bkg->Write();
	
	iso_deltabeta_vs_pt->Write();
	iso_deltabeta_vs_vtx->Write();
	iso_deltabeta_vs_eta->Write();

	iso_deltabeta_vs_pt_signal->Write();
	iso_deltabeta_vs_vtx_signal->Write();
	iso_deltabeta_vs_eta_signal->Write();

	iso_deltabeta_vs_pt_bkg->Write();
	iso_deltabeta_vs_vtx_bkg->Write();
	iso_deltabeta_vs_eta_bkg->Write();

	iso_puppi_vs_pt->Write();
	iso_puppi_vs_vtx->Write();
	iso_puppi_vs_eta->Write();

	iso_puppi_vs_pt_signal->Write();
	iso_puppi_vs_vtx_signal->Write();
	iso_puppi_vs_eta_signal->Write();

	iso_puppi_vs_pt_bkg->Write();
	iso_puppi_vs_vtx_bkg->Write();
	iso_puppi_vs_eta_bkg->Write();
	
	iso_puppinl_vs_pt->Write();
	iso_puppinl_vs_vtx->Write();
	iso_puppinl_vs_eta->Write();

	iso_puppinl_vs_pt_signal->Write();
	iso_puppinl_vs_vtx_signal->Write();
	iso_puppinl_vs_eta_signal->Write();

	iso_puppinl_vs_pt_bkg->Write();
	iso_puppinl_vs_vtx_bkg->Write();
	iso_puppinl_vs_eta_bkg->Write();
	
	iso_citk_vs_pt->Write();
	iso_citk_vs_vtx->Write();
	iso_citk_vs_eta->Write();

	iso_citk_vs_pt_signal->Write();
	iso_citk_vs_vtx_signal->Write();
	iso_citk_vs_eta_signal->Write();

	iso_citk_vs_pt_bkg->Write();
	iso_citk_vs_vtx_bkg->Write();
	iso_citk_vs_eta_bkg->Write();
	//close the file
	data_output->Close();
}

cout << "Selected Electrons              " << selected_electrons[0] << " " << selected_electrons[1] << endl;
cout << "Selected Electrons - Signal     " << selected_electrons_signal[0] << " " << selected_electrons_signal[1] << endl;
cout << "Selected Electrons - Background " << selected_electrons_bkg[0] << " " << selected_electrons_bkg[1] << endl;


	delete(vertex_multiplicity);
	delete(evt_rho);

	delete(vertex_multiplicity_signal);
	delete(evt_rho_signal);

	delete(vertex_multiplicity_bkg);
	delete(evt_rho_bkg);

	delete(reco_ele_multiplicity);
	delete(reco_ele_pt);
	delete(reco_ele_eta);
	delete(reco_ele_phi);
	delete(reco_ele_effarea);
	delete(reco_ele_dxy);
	delete(reco_ele_dz);
	delete(reco_ele_missinghit);

	delete(reco_ele_multiplicity_signal);
	delete(reco_ele_pt_signal);
	delete(reco_ele_eta_signal);
	delete(reco_ele_phi_signal);
	delete(reco_ele_effarea_signal);
	delete(reco_ele_dxy_signal);
	delete(reco_ele_dz_signal);
	delete(reco_ele_missinghit_signal);

	delete(reco_ele_multiplicity_bkg);
	delete(reco_ele_pt_bkg);
	delete(reco_ele_eta_bkg);
	delete(reco_ele_phi_bkg);
	delete(reco_ele_effarea_bkg);
	delete(reco_ele_dxy_bkg);
	delete(reco_ele_dz_bkg);
	delete(reco_ele_missinghit_bkg);

	delete(reco_ele_pfchhadiso);
	delete(reco_ele_pfchhadisorel);
	delete(reco_ele_pfchhadiso_barrel);
	delete(reco_ele_pfchhadisorel_barrel);
	delete(reco_ele_pfchhadiso_endcap);
	delete(reco_ele_pfchhadisorel_endcap);
	delete(reco_ele_pfnehadiso);
	delete(reco_ele_pfnehadisorel);
	delete(reco_ele_pfnehadiso_barrel);
	delete(reco_ele_pfnehadisorel_barrel);
	delete(reco_ele_pfnehadiso_endcap);
	delete(reco_ele_pfnehadisorel_endcap);
	delete(reco_ele_pfphotoniso);
	delete(reco_ele_pfphotonisorel);
	delete(reco_ele_pfphotoniso_barrel);
	delete(reco_ele_pfphotonisorel_barrel);
	delete(reco_ele_pfphotoniso_endcap);
	delete(reco_ele_pfphotonisorel_endcap);
	delete(reco_ele_pfchargedfrompu);
	delete(reco_ele_pfchargedfrompurel);
	delete(reco_ele_pfchargedfrompu_barrel);
	delete(reco_ele_pfchargedfrompurel_barrel);
	delete(reco_ele_pfchargedfrompu_endcap);
	delete(reco_ele_pfchargedfrompurel_endcap);

	delete(reco_ele_pfchhadiso_puppi);
	delete(reco_ele_pfchhadisorel_puppi);
	delete(reco_ele_pfchhadiso_puppi_barrel);
	delete(reco_ele_pfchhadiso_puppi_endcap);
	delete(reco_ele_pfnehadiso_puppi);
	delete(reco_ele_pfnehadisorel_puppi);
	delete(reco_ele_pfnehadiso_puppi_barrel);
	delete(reco_ele_pfnehadiso_puppi_endcap);
	delete(reco_ele_pfphotoniso_puppi);
	delete(reco_ele_pfphotonisorel_puppi);
	delete(reco_ele_pfphotoniso_puppi_barrel);
	delete(reco_ele_pfphotoniso_puppi_endcap);

	delete(reco_ele_pfchhadiso_puppinl);
	delete(reco_ele_pfchhadisorel_puppinl);
	delete(reco_ele_pfchhadiso_puppinl_barrel);
	delete(reco_ele_pfchhadiso_puppinl_endcap);
	delete(reco_ele_pfnehadiso_puppinl);
	delete(reco_ele_pfnehadisorel_puppinl);
	delete(reco_ele_pfnehadiso_puppinl_barrel);
	delete(reco_ele_pfnehadiso_puppinl_endcap);
	delete(reco_ele_pfphotoniso_puppinl);
	delete(reco_ele_pfphotonisorel_puppinl);
	delete(reco_ele_pfphotoniso_puppinl_barrel);
	delete(reco_ele_pfphotoniso_puppinl_endcap);

	delete(reco_ele_pfchhadiso_citk);
	delete(reco_ele_pfchhadisorel_citk);
	delete(reco_ele_pfchhadiso_citk_barrel);
	delete(reco_ele_pfchhadiso_citk_endcap);
	delete(reco_ele_pfnehadiso_citk);
	delete(reco_ele_pfnehadisorel_citk);
	delete(reco_ele_pfnehadiso_citk_barrel);
	delete(reco_ele_pfnehadiso_citk_endcap);
	delete(reco_ele_pfphotoniso_citk);
	delete(reco_ele_pfphotonisorel_citk);
	delete(reco_ele_pfphotoniso_citk_barrel);
	delete(reco_ele_pfphotoniso_citk_endcap);

	delete(reco_ele_pfiso_simple);
	delete(reco_ele_pfiso_simple_barrel);
	delete(reco_ele_pfiso_simple_endcap);
	delete(reco_ele_pfiso_simple_lowpu);
	delete(reco_ele_pfiso_simple_medpu);
	delete(reco_ele_pfiso_simple_highpu);

	delete(reco_ele_pfiso_effarea);
	delete(reco_ele_pfiso_effarea_barrel);
	delete(reco_ele_pfiso_effarea_endcap);
	delete(reco_ele_pfiso_effarea_lowpu);
	delete(reco_ele_pfiso_effarea_medpu);
	delete(reco_ele_pfiso_effarea_highpu);

	delete(reco_ele_pfiso_deltabeta);
	delete(reco_ele_pfiso_deltabeta_barrel);
	delete(reco_ele_pfiso_deltabeta_endcap);
	delete(reco_ele_pfiso_deltabeta_lowpu);
	delete(reco_ele_pfiso_deltabeta_medpu);
	delete(reco_ele_pfiso_deltabeta_highpu);

	delete(reco_ele_pfiso_puppi);
	delete(reco_ele_pfiso_puppi_barrel);
	delete(reco_ele_pfiso_puppi_endcap);
	delete(reco_ele_pfiso_puppi_lowpu);
	delete(reco_ele_pfiso_puppi_medpu);
	delete(reco_ele_pfiso_puppi_highpu);

	delete(reco_ele_pfiso_puppinl);
	delete(reco_ele_pfiso_puppinl_barrel);
	delete(reco_ele_pfiso_puppinl_endcap);
	delete(reco_ele_pfiso_puppinl_lowpu);
	delete(reco_ele_pfiso_puppinl_medpu);
	delete(reco_ele_pfiso_puppinl_highpu);

	delete(reco_ele_pfiso_citk);
	delete(reco_ele_pfiso_citk_barrel);
	delete(reco_ele_pfiso_citk_endcap);
	delete(reco_ele_pfiso_citk_lowpu);
	delete(reco_ele_pfiso_citk_medpu);
	delete(reco_ele_pfiso_citk_highpu);

	delete(reco_ele_bdt);
	delete(reco_ele_bdt_barrel);
	delete(reco_ele_bdt_endcap);
	delete(reco_ele_sip);
	delete(reco_ele_sip_barrel);
	delete(reco_ele_sip_endcap);
	delete(reco_ele_id);
	delete(reco_ele_isgood);
	delete(leading_reco_ele_pt);
	delete(leading_reco_ele_eta);
	delete(leading_reco_ele_phi);
	
	delete(iso_simple_vs_pt);
	delete(iso_simple_vs_vtx);
	delete(iso_simple_vs_eta);
	
	delete(iso_effarea_vs_pt);
	delete(iso_effarea_vs_vtx);
	delete(iso_effarea_vs_eta);
	
	delete(iso_deltabeta_vs_pt);
	delete(iso_deltabeta_vs_vtx);
	delete(iso_deltabeta_vs_eta);

	delete(iso_puppi_vs_pt);
	delete(iso_puppi_vs_vtx);
	delete(iso_puppi_vs_eta);
	
	delete(iso_puppinl_vs_pt);
	delete(iso_puppinl_vs_vtx);
	delete(iso_puppinl_vs_eta);

	delete(iso_citk_vs_pt);
	delete(iso_citk_vs_vtx);
	delete(iso_citk_vs_eta);


  std::cout << "-------------------------------------" << endl;
  std::cout << "Execution ended!" << endl;
  std::cout << "-------------------------------------" << endl;
  std::cout << " " << endl;
}
