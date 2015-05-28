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
#include "common_methods.h"

using namespace std;

void electron_isolation()
{
  gROOT -> Reset();
  gROOT->SetStyle("Plain");

  cout << "Electron Isolation" << endl;
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

  int samples = 2;
  string sample[samples];
  string out[samples];
  string prefix[samples];
  bool signal[samples];

  sample[0] = "/data_CMS/cms/cipriano/leptonNtuples_DYJetsToLL_PHYS14_PU20bx25_28_May/DY.root";
  sample[1] = "/data_CMS/cms/cipriano/leptonNtuples_ggH_PHYS14_PU20bx25_28_May/ggH.root";
  out[0] = "output/DY.root";
  out[1] = "output/ggH.root";

  prefix[0] = "DY";
  prefix[1] = "GluGluToH";

  signal[0] = false;
  signal[1] = true;

  //TFile *dy = TFile::Open( dy_sample.c_str() );

TH1D *vertex_multiplicity = new TH1D("vertex_multiplicity","Generated Vertex Multiplicity",50,-0.5,49.5);

TH1D *gen_ele_multiplicity = new TH1D("gen_ele_multiplicity","Generated Electron Multiplicity",6,-0.5,5.5);
TH1D *gen_ele_pt = new TH1D("gen_ele_pt","Generated Electron pT",40,0,200);
TH1D *gen_ele_eta = new TH1D("gen_ele_eta","Generated Electron Eta",22,-5.5,5.5);
TH1D *gen_ele_phi = new TH1D("gen_ele_phi","Generated Electron Phi",20,-3.15,3.15);
TH1D *leading_gen_ele_pt = new TH1D("leading_gen_ele_pt","Leading Generated Electron pT",40,0,200);
TH1D *leading_gen_ele_eta = new TH1D("leading_gen_ele_eta","Leading Generated Electron Eta",22,-5.5,5.5);
TH1D *leading_gen_ele_phi = new TH1D("leading_gen_ele_phi","Leading Generated Electron Phi",20,-3.15,3.15);


TH1D *reco_ele_multiplicity = new TH1D("reco_ele_multiplicity","Reconstructed Electron Multiplicity",6, -0.5,5.5);
TH1D *reco_ele_pt = new TH1D("reco_ele_pt","Reconstructed Electron pT",40,0,200);
TH1D *reco_ele_eta = new TH1D("reco_ele_eta","Reconstructed Electron Eta",22,-5.5,5.5);
TH1D *reco_ele_phi = new TH1D("reco_ele_phi","Reconstructed Electron Phi",20,-3.15,3.15);
TH1D *reco_ele_dxy = new TH1D("reco_ele_dxz","Reconstructed Electron dxy",60,0,0.6);
TH1D *reco_ele_dz = new TH1D("reco_ele_dz","Reconstructed Electron dz",120,0,1.2);
TH1D *reco_ele_missinghit = new TH1D("reco_ele_missinghit","Reconstructed Electron Missing Hits",3,-0.5,2.5);
TH1D *reco_ele_pfchhadiso = new TH1D("reco_ele_pfchhadiso","PF Charged Hadron Isolated",100,0,100.0);
TH1D *reco_ele_pfchhadiso_barrel = new TH1D("reco_ele_pfchhadiso_barrel","PF Charged Hadron Isolated Barrel",100,0,100.0);
TH1D *reco_ele_pfchhadiso_endcap = new TH1D("reco_ele_pfchhadiso_endcap","PF Charged Hadron Isolated EndCap",100,0,100.0);
TH1D *reco_ele_pfnehadiso = new TH1D("reco_ele_pfnehadiso","PF Neutral Hadron Isolated",100,0,100.0);
TH1D *reco_ele_pfnehadiso_barrel = new TH1D("reco_ele_pfnehadiso_barrel","PF Neutral Hadron Isolated Barrel",100,0,100.0);
TH1D *reco_ele_pfnehadiso_endcap = new TH1D("reco_ele_pfnehadiso_endcap","PF Neutral Hadron Isolated EndCap",100,0,100.0);
TH1D *reco_ele_pfphotoniso = new TH1D("reco_ele_pfphotoniso","PF Photon Isolated",100,0,100.0);
TH1D *reco_ele_pfphotoniso_barrel = new TH1D("reco_ele_pfphotoniso_barrel","PF Photon Isolated Barrel",100,0,100.0);
TH1D *reco_ele_pfphotoniso_endcap = new TH1D("reco_ele_pfphotoniso_endcap","PF Photon Isolated EndCap",100,0,100.0);

TH1D *reco_ele_pfiso_simple = new TH1D("reco_ele_pfiso_simple","PF Combined Relation Isolation Simple",100,0,2.0);
TH1D *reco_ele_pfiso_simple_barrel = new TH1D("reco_ele_pfiso_simple_barrel","PF Combined Relation Isolation Simple Barrel",100,0,2.0);
TH1D *reco_ele_pfiso_simple_endcap = new TH1D("reco_ele_pfiso_simple_endcap","PF Combined Relation Isolation Simple EndCap",100,0,2.0);
TH1D *reco_ele_pfiso_effarea = new TH1D("reco_ele_pfiso_effarea","PF Combined Relation Isolation Effective Area",100,0,2.0);
TH1D *reco_ele_pfiso_effarea_barrel = new TH1D("reco_ele_pfiso_effarea_barrel","PF Combined Relation Isolation Effective Area Barrel",100,0,2.0);
TH1D *reco_ele_pfiso_effarea_endcap = new TH1D("reco_ele_pfiso_effarea_endcap","PF Combined Relation Isolation Effective Area EndCap",100,0,2.0);
TH1D *reco_ele_pfiso_deltaeta = new TH1D("reco_ele_pfiso_deltaeta","PF Combined Relation Isolation Delta Eta",100,0,2.0);
TH1D *reco_ele_pfiso_deltaeta_barrel = new TH1D("reco_ele_pfiso_deltaeta_barrel","PF Combined Relation Isolation Delta Eta Barrel",100,0,2.0);
TH1D *reco_ele_pfiso_deltaeta_endcap = new TH1D("reco_ele_pfiso_deltaeta_endcap","PF Combined Relation Isolation Delta Eta EndCap",100,0,2.0);

TH1D *reco_ele_bdt = new TH1D("reco_ele_bdt","Electron BDT",100,0,1.0);
TH1D *reco_ele_bdt_barrel = new TH1D("reco_ele_bdt_barrel","Electron BDT Barrel",100,0,1.0);
TH1D *reco_ele_bdt_endcap = new TH1D("reco_ele_bdt_endcap","Electron BDT EndCap",100,0,1.0);
TH1D *reco_ele_rho = new TH1D("reco_ele_rho","Electron Rho",100,0,25.0);
TH1D *reco_ele_sip = new TH1D("reco_ele_sip","Electron SIP",100,0,25.0);
TH1D *reco_ele_sip_barrel = new TH1D("reco_ele_sip_barrel","Electron SIP Barrel",100,0,25.0);
TH1D *reco_ele_sip_endcap = new TH1D("reco_ele_sip_endcap","Electron SIP Endcap",100,0,25.0);
TH1D *leading_reco_ele_pt = new TH1D("leading_reco_ele_pt","Leading Reconstructed Electron pT",40,0,200);
TH1D *leading_reco_ele_eta = new TH1D("leading_reco_ele_eta","Leading Reconstructed Electron Eta",22,-5.5,5.5);
TH1D *leading_reco_ele_phi = new TH1D("leading_reco_ele_phi","Leading Reconstructed Electron Phi",20,-3.15,3.15);

  Int_t nEvent;
  Int_t nRun;
  Int_t nLumi;
  Int_t nGenVtx;

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
  Float_t ele_PFChargedHadIso[100];
  Float_t ele_PFNeutralHadIso[100];
  Float_t ele_PFPhotonIso[100];
  Float_t ele_PFIso_simple[100];
  Float_t ele_PFIso_effarea[100];
  Float_t ele_PFIso_deltaeta[100];
  Float_t ele_rho[100];
  Float_t ele_SIP[100];
  Float_t ele_dxy[100];
  Float_t ele_dz[100];
  Float_t ele_BDT[100];
  Float_t ele_isBDT[100];
  Float_t ele_missingHit[100];
  Float_t ele_ID[100];
  Float_t ele_isGood[100];

    TChain* chain[2];

   double max_gen_pt, max_reco_pt;
   int id_leading_gen, id_leading_reco;
   int ele_matched, ele_separated;
   bool use_electrons, matched, separated;
   int selected_electrons[samples];
   double isolation_simple[samples][100], isolation_simple_barrel[samples][100];
   double isolation_simple_endcap[samples][100];
   double isolation_effarea[samples][100], isolation_effarea_barrel[samples][100];
   double isolation_effarea_endcap[samples][100];
   double isolation_deltaeta[samples][100], isolation_deltaeta_barrel[samples][100];
   double isolation_deltaeta_endcap[samples][100]; 
   double sip[samples][100], sip_barrel[samples][100], sip_endcap[samples][100];
   double bdt[samples][100], bdt_barrel[samples][100], bdt_endcap[samples][100];

    for (int s=0; s<samples; ++s) {

    chain[s] = new TChain("tree");
    chain[s]->Add(sample[s].c_str());

    cout << "Reading " << sample[s] << "..." << endl;

    chain[s]->SetBranchAddress("nEvent", &nEvent);
    chain[s]->SetBranchAddress("nRun", &nRun);
    chain[s]->SetBranchAddress("nLumi", &nLumi);
    chain[s]->SetBranchAddress("nGenVtx", &nGenVtx);
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
    chain[s]->SetBranchAddress("ele_PFChargedHadIso", &ele_PFChargedHadIso);
    chain[s]->SetBranchAddress("ele_PFNeutralHadIso", &ele_PFNeutralHadIso);
    chain[s]->SetBranchAddress("ele_PFPhotonIso", &ele_PFPhotonIso);
    chain[s]->SetBranchAddress("ele_PFIso_simple", &ele_PFIso_simple);
    chain[s]->SetBranchAddress("ele_PFIso_effarea", &ele_PFIso_effarea);
    chain[s]->SetBranchAddress("ele_PFIso_deltaeta", &ele_PFIso_effarea);
    chain[s]->SetBranchAddress("ele_rho", &ele_rho);
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
   reco_ele_dxy->Reset();
   reco_ele_dz->Reset();
   reco_ele_missinghit->Reset();
   reco_ele_pfchhadiso->Reset();
   reco_ele_pfchhadiso_barrel->Reset();
   reco_ele_pfchhadiso_endcap->Reset();
   reco_ele_pfnehadiso->Reset();
   reco_ele_pfnehadiso_barrel->Reset();
   reco_ele_pfnehadiso_endcap->Reset();
   reco_ele_pfphotoniso->Reset();
   reco_ele_pfphotoniso_barrel->Reset();
   reco_ele_pfphotoniso_endcap->Reset();

   reco_ele_pfiso_simple->Reset();
   reco_ele_pfiso_simple_barrel->Reset();
   reco_ele_pfiso_simple_endcap->Reset();
   reco_ele_pfiso_effarea->Reset();
   reco_ele_pfiso_effarea_barrel->Reset();
   reco_ele_pfiso_effarea_endcap->Reset();
   reco_ele_pfiso_deltaeta->Reset();
   reco_ele_pfiso_deltaeta_barrel->Reset();
   reco_ele_pfiso_deltaeta_endcap->Reset();

   reco_ele_bdt->Reset();
   reco_ele_bdt_barrel->Reset();
   reco_ele_bdt_endcap->Reset();
   reco_ele_rho->Reset();
   reco_ele_sip->Reset();
   reco_ele_sip_barrel->Reset();
   reco_ele_sip_endcap->Reset();
   leading_reco_ele_pt->Reset();
   leading_reco_ele_eta->Reset();
   leading_reco_ele_phi->Reset();

   selected_electrons[s] = 0;
   for (int y=0; y<100; ++y)
	{
	isolation_simple[s][y] = 0;
	isolation_simple_barrel[s][y] = 0;
	isolation_simple_endcap[s][y] = 0;
	isolation_effarea[s][y] = 0;
	isolation_effarea_barrel[s][y] = 0;
	isolation_effarea_endcap[s][y] = 0;
	isolation_deltaeta[s][y] = 0;
	isolation_deltaeta_barrel[s][y] = 0;
	isolation_deltaeta_endcap[s][y] = 0;
	sip[s][y] = 0;
	sip_barrel[s][y] = 0;
	sip_endcap[s][y] = 0;
	bdt[s][y] = 0;
	bdt_barrel[s][y] = 0;
	bdt_endcap[s][y] = 0;
	}

    Int_t entries = chain[s]->GetEntries();
    if (test) { entries = 25; }
    cout << "Total Events: " << entries << endl;

    for (int z=0; z<entries; ++z)
	{

	max_gen_pt = 0.0;
	id_leading_gen = -1;
	max_reco_pt = 0.0;
	id_leading_reco = -1;
	ele_matched = 0;
	ele_separated = 0;
	use_electrons = false;
	matched = false;
	separated = true;

	chain[s]->GetEntry(z);
	if (detail) { cout << "z = " << z << " of " << entries << endl; }
	if (detail) { cout << "Event Number = " << nEvent << endl; }
	if (detail) { cout << "Run Number = " << nRun << endl; }
	if (detail) { cout << "Lumi Block = " << nLumi << endl; }
	if (detail) { cout << "Number of Generated Vertexes = " << nGenVtx << endl; }
	vertex_multiplicity->Fill(nGenVtx);
	if (detail) { cout << "Generated Electrons = " << gen << endl; }
	if (detail) { cout << "Generated Muons = " << gmn << endl; }

	if (signal[s]) { if ((gen==4&&gmn==0) || (gen==2&&gmn==2)) {use_electrons = true; }}
	if (!signal[s]) { if ((gen==2&&gmn==0) || (gen==0&&gmn==2)) {use_electrons = true; }}

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
		{ if (detail) { cout << "#" << iReco << " pt = " << ele_pt[iReco] << " eta = " << ele_sclEta[iReco] << " phi = " << ele_phi[iReco] << endl;
                cout << " dxy = " << ele_dxy[iReco] << " dz = " << ele_dz[iReco] << " missing hits = " << ele_missingHit[iReco] << endl;
		cout << " PF charged hadron isolation = " << ele_PFChargedHadIso[iReco] << endl;
		cout << " PF neutral hadron isolation = " << ele_PFNeutralHadIso[iReco] << endl;
		cout << " PF photon isolation = " << ele_PFPhotonIso[iReco] << endl;
		cout << " PF isolation simple = " << ele_PFIso_simple[iReco] << endl;
		cout << " PF isolation Effective Area = " << ele_PFIso_effarea[iReco] << endl;
		cout << " PF isolation Delta Eta = " << ele_PFIso_deltaeta[iReco] << endl;
                cout << " Electron BDT = " << ele_BDT[iReco] << " is BDT? " << ele_isBDT[iReco] << endl;
		cout << " Electron Rho = " << ele_rho[iReco] << " Electron SIP = " << ele_SIP[iReco] << endl; }
		for(int iGen=0; iGen<gen; iGen++)
			{			
			if (signal[s] and delta_r(geeta[iGen],gephi[iGen],ele_sclEta[iReco],ele_phi[iReco]) < 0.1) {
			if (detail) {cout << "Matched to #" << iGen << " (eta = " << geeta[iGen] << " and phi = " << gephi[iGen] << ")" << endl; }
			matched = true;
			}
			if (!signal[s] and delta_r(geeta[iGen],gephi[iGen],ele_sclEta[iReco],ele_phi[iReco]) < 0.1) {
			if (detail) {cout << "Separated to #" << iGen << " (eta = " << geeta[iGen] << " and phi = " << gephi[iGen] << ")" << endl; }
			separated = false;
			}
			}
		if ((ele_pt[iReco] > 10.0 and (ele_eta[iReco] < abs(2.5)) and ele_dxy[iReco] < 0.5 and ele_dz[iReco] < 1.0 and use_electrons) and ((signal[s] and matched) or (!signal[s] and separated)))
		{
		if (ele_pt[iReco] > max_reco_pt) { max_reco_pt = ele_pt[iReco]; id_leading_reco = iReco; }
		if (detail) { cout << "Electron Selected" << endl; }
		if (signal[s]) { ele_matched = ele_matched + 1; }
		if (!signal[s]) { ele_separated = ele_separated + 1; }
		selected_electrons[s] = selected_electrons[s] + 1;	
		reco_ele_pt->Fill(ele_pt[iReco]);
		reco_ele_eta->Fill(ele_sclEta[iReco]);
		reco_ele_phi->Fill(ele_phi[iReco]);
		reco_ele_dxy->Fill(ele_dxy[iReco]);
		reco_ele_dz->Fill(ele_dz[iReco]);
		reco_ele_missinghit->Fill(ele_missingHit[iReco]);
		reco_ele_pfchhadiso->Fill(ele_PFChargedHadIso[iReco]);
		reco_ele_pfnehadiso->Fill(ele_PFNeutralHadIso[iReco]);
		reco_ele_pfphotoniso->Fill(ele_PFPhotonIso[iReco]);
		reco_ele_pfiso_simple->Fill(ele_PFIso_simple[iReco]);
		reco_ele_pfiso_effarea->Fill(ele_PFIso_effarea[iReco]);
		reco_ele_pfiso_deltaeta->Fill(ele_PFIso_deltaeta[iReco]);
		reco_ele_bdt->Fill(ele_BDT[iReco]);
		reco_ele_rho->Fill(ele_rho[iReco]);
		reco_ele_sip->Fill(ele_SIP[iReco]);
		if (ele_sclEta[iReco] < abs(1.479))
			{
			reco_ele_sip_barrel->Fill(ele_SIP[iReco]);
			reco_ele_bdt_barrel->Fill(ele_BDT[iReco]);
			reco_ele_pfchhadiso_barrel->Fill(ele_PFChargedHadIso[iReco]);
			reco_ele_pfnehadiso_barrel->Fill(ele_PFNeutralHadIso[iReco]);
			reco_ele_pfphotoniso_barrel->Fill(ele_PFPhotonIso[iReco]);
			reco_ele_pfiso_simple_barrel->Fill(ele_PFIso_simple[iReco]);
			reco_ele_pfiso_effarea_barrel->Fill(ele_PFIso_effarea[iReco]);
			reco_ele_pfiso_deltaeta_barrel->Fill(ele_PFIso_deltaeta[iReco]);
			}
		if (ele_sclEta[iReco] > abs(1.653) and ele_sclEta[iReco] < abs(2.5))
			{
			reco_ele_sip_endcap->Fill(ele_SIP[iReco]);
			reco_ele_bdt_endcap->Fill(ele_BDT[iReco]);
			reco_ele_pfchhadiso_endcap->Fill(ele_PFChargedHadIso[iReco]);
			reco_ele_pfnehadiso_endcap->Fill(ele_PFNeutralHadIso[iReco]);
			reco_ele_pfphotoniso_endcap->Fill(ele_PFPhotonIso[iReco]);
			reco_ele_pfiso_simple_endcap->Fill(ele_PFIso_simple[iReco]);
			reco_ele_pfiso_effarea_endcap->Fill(ele_PFIso_effarea[iReco]);
			reco_ele_pfiso_deltaeta_endcap->Fill(ele_PFIso_deltaeta[iReco]);
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

		gen_ele_multiplicity->Fill(gen);
		reco_ele_multiplicity->Fill(nele);
	}
	else
	{
	if (detail) { cout << "Event rejected!" << endl; }
	}

	}


//plot all histograms
plot_histogram(leading_gen_ele_pt, "output/", prefix[s] + "_leading_gen_ele_pt", "Leading Generated Electron pT", "top_right", true);
plot_histogram(leading_gen_ele_eta, "output/", prefix[s] + "_leading_gen_ele_eta", "Leading Generated Electron Eta", "top_right", true);
plot_histogram(leading_gen_ele_phi, "output/", prefix[s] + "_leading_gen_ele_phi", "Leading Generated Electron Phi", "top_right", true);
plot_histogram(reco_ele_multiplicity, "output/", prefix[s] + "_reco_ele_multiplicity", "Reconstructed Electron Multiplicity", "top_right", true);
plot_histogram(reco_ele_pt, "output/", prefix[s] +  "_reco_ele_pt", "Reconstructed Electron pT", "top_right", true);
plot_histogram(reco_ele_eta, "output/", prefix[s] + "_reco_ele_eta", "Reconstructed Electron Eta", "top_right", true);
plot_histogram(reco_ele_phi, "output/", prefix[s] + "_reco_ele_phi", "Reconstructed Electron Phi", "top_right", true);
plot_histogram(reco_ele_dxy, "output/", prefix[s] + "_reco_ele_dxy", "Reconstructed Electron dxy", "top_right", true);
plot_histogram(reco_ele_missinghit, "output/", prefix[s] + "_reco_ele_missinghit", "Reconstructed Electron Missing Hits", "top_right", true);
plot_histogram(reco_ele_pfchhadiso, "output/", prefix[s] +  "_reco_ele_pfchhadiso", "PF Charged Hadron Isolation", "top_right", true);
plot_histogram(reco_ele_pfchhadiso_barrel, "output/", prefix[s] +  "_reco_ele_pfchhadiso_barrel", "PF Charged Hadron Isolation Barrel", "top_right", true);
plot_histogram(reco_ele_pfchhadiso_endcap, "output/", prefix[s] +  "_reco_ele_pfchhadiso_endcap", "PF Charged Hadron Isolation EndCap", "top_right", true);
plot_histogram(reco_ele_pfnehadiso, "output/", prefix[s] + "_reco_ele_pfnehadiso", "PF Neutral Hadron Isolation", "top_right", true);
plot_histogram(reco_ele_pfnehadiso_barrel, "output/", prefix[s] + "_reco_ele_pfnehadiso_barrel", "PF Neutral Hadron Isolation Barrel", "top_right", true);
plot_histogram(reco_ele_pfnehadiso_endcap, "output/", prefix[s] + "_reco_ele_pfnehadiso_endcap", "PF Neutral Hadron Isolation EndCap", "top_right", true);
plot_histogram(reco_ele_pfphotoniso, "output/", prefix[s] + "_reco_ele_pfphotoniso", "PF Photon Isolation", "top_right", true);
plot_histogram(reco_ele_pfphotoniso_barrel, "output/", prefix[s] + "_reco_ele_pfphotoniso_barrel", "PF Photon Isolation Barrel", "top_right", true);
plot_histogram(reco_ele_pfphotoniso_endcap, "output/", prefix[s] + "_reco_ele_pfphotoniso_endcap", "PF Photon Isolation EndCap", "top_right", true);

plot_histogram(reco_ele_pfiso_simple, "output/", prefix[s] + "_reco_ele_pfiso_simple", "PF Combined Relation Isolation Simple", "top_right", true);
plot_histogram(reco_ele_pfiso_simple_barrel, "output/", prefix[s] + "_reco_ele_pfiso_simple_barrel", "PF Combined Relation Isolation Simple Barrel", "top_right", true);
plot_histogram(reco_ele_pfiso_simple_endcap, "output/", prefix[s] + "_reco_ele_pfiso_simple_endcap", "PF Combined Relation Isolation Simple Endcap", "top_right", true);

plot_histogram(reco_ele_pfiso_effarea, "output/", prefix[s] + "_reco_ele_pfiso_effarea", "PF Combined Relation Isolation Effective Area", "top_right", true);
plot_histogram(reco_ele_pfiso_effarea_barrel, "output/", prefix[s] + "_reco_ele_pfiso_effarea_barrel", "PF Combined Relation Isolation Effective Area Barrel", "top_right", true);
plot_histogram(reco_ele_pfiso_effarea_endcap, "output/", prefix[s] + "_reco_ele_pfiso_effarea_endcap", "PF Combined Relation Isolation Effective Area Endcap", "top_right", true);

plot_histogram(reco_ele_pfiso_deltaeta, "output/", prefix[s] + "_reco_ele_pfiso_deltaeta", "PF Combined Relation Isolation Delta Eta", "top_right", true);
plot_histogram(reco_ele_pfiso_deltaeta_barrel, "output/", prefix[s] + "_reco_ele_pfiso_deltaeta_barrel", "PF Combined Relation Isolation Delta Eta Barrel", "top_right", true);
plot_histogram(reco_ele_pfiso_deltaeta_endcap, "output/", prefix[s] + "_reco_ele_pfiso_deltaeta_endcap", "PF Combined Relation Isolation Delta Eta Endcap", "top_right", true);

plot_histogram(reco_ele_bdt, "output/", prefix[s] + "_reco_ele_bdt", "Electron BDT", "top_left", true);
plot_histogram(reco_ele_bdt_barrel, "output/", prefix[s] + "_reco_ele_bdt_barrel", "Electron BDT Barrel", "top_left", true);
plot_histogram(reco_ele_bdt_endcap, "output/", prefix[s] + "_reco_ele_bdt_endcap", "Electron BDT Endcap", "top_left", true);
plot_histogram(reco_ele_rho, "output/", prefix[s] + "_reco_ele_rho", "Electron Rho", "top_right", true);
plot_histogram(reco_ele_sip, "output/", prefix[s] + "_reco_ele_sip", "Electron SIP", "top_right", true);
plot_histogram(reco_ele_sip_barrel, "output/", prefix[s] + "_reco_ele_sip_barrel", "Electron SIP Barrel", "top_right", true);
plot_histogram(reco_ele_sip_endcap, "output/", prefix[s] + "_reco_ele_sip_endcap", "Electron SIP Endcap", "top_right", true);
plot_histogram(leading_reco_ele_pt, "output/", prefix[s] + "_leading_reco_ele_pt", "Leading Reconstructed Electron pT", "top_right", true);
plot_histogram(leading_reco_ele_eta, "output/", prefix[s] + "_leading_reco_ele_eta", "Leading Reconstructed Electron Eta", "top_right", true);
plot_histogram(leading_reco_ele_phi, "output/", prefix[s] + "_leading_reco_ele_phi", "Leading Reconstructed Electron Phi", "top_right", true);


//normalization of the histograms
normalize_histogram(vertex_multiplicity, "Vertex Multiplicity", true, false);

normalize_histogram(gen_ele_multiplicity, "Generated Electron Multiplicity", true, false);
normalize_histogram(gen_ele_pt, "Gen Electron pT", true, false);
normalize_histogram(gen_ele_eta, "Gen Electron Eta", true, false);
normalize_histogram(gen_ele_phi, "Gen Electron Phi", true, false);
normalize_histogram(leading_gen_ele_pt, "Leading Gen Electron pT", true, false);
normalize_histogram(leading_gen_ele_eta, "Leading Gen Electron Eta", true, false);
normalize_histogram(leading_gen_ele_phi, "Leading Gen Electron Phi", true, false);

normalize_histogram(reco_ele_multiplicity, "Reco Electron Multiplicity", true, false);
normalize_histogram(reco_ele_pt, "Reco Electron pT", true, false);
normalize_histogram(reco_ele_eta, "Reco Electron Eta", true, false);
normalize_histogram(reco_ele_phi, "Reco Electron Phi", true, false);
normalize_histogram(reco_ele_dxy, "Reco Electron dxy", true, false);
normalize_histogram(reco_ele_dz, "Reco Electron dz", true, false);
normalize_histogram(reco_ele_missinghit, "Reco Electron Missing Hit", true, false);
normalize_histogram(reco_ele_pfchhadiso, "Reco Electron Charged Hadron Isolation", true, false);
normalize_histogram(reco_ele_pfchhadiso_barrel, "Reco Electron Charged Hadron Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfchhadiso_endcap, "Reco Electron Charged Hadron Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfnehadiso, "Reco Electron Neutral Hadron Isolation", true, false);
normalize_histogram(reco_ele_pfnehadiso_barrel, "Reco Electron Neutral Hadron Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfnehadiso_endcap, "Reco Electron Neutral Hadron Isolation EndCap", true, false);
normalize_histogram(reco_ele_pfphotoniso, "Reco Electron Photon Isolation", true, false);
normalize_histogram(reco_ele_pfphotoniso_barrel, "Reco Electron Photon Isolation Barrel", true, false);
normalize_histogram(reco_ele_pfphotoniso_endcap, "Reco Electron Photon Isolation EndCap", true, false);

normalize_histogram(reco_ele_pfiso_simple, "Reco_ele_PFIso_Simple", true, false);
normalize_histogram(reco_ele_pfiso_simple_barrel, "Reco_ele_PFIso_Simple_Barrel", true, false);
normalize_histogram(reco_ele_pfiso_simple_endcap, "Reco_ele_PFIso_Simple_EndCap", true, false);

normalize_histogram(reco_ele_pfiso_effarea, "Reco_ele_PFIso_EffArea", true, false);
normalize_histogram(reco_ele_pfiso_effarea_barrel, "Reco_ele_PFIso_Simple_EffArea", true, false);
normalize_histogram(reco_ele_pfiso_effarea_endcap, "Reco_ele_PFIso_Simple_EffArea", true, false);

normalize_histogram(reco_ele_pfiso_deltaeta, "Reco_ele_PFIso_DeltaEta", true, false);
normalize_histogram(reco_ele_pfiso_deltaeta_barrel, "Reco_ele_PFIso_DeltaEta_Barrel", true, false);
normalize_histogram(reco_ele_pfiso_deltaeta_endcap, "Reco_ele_PFIso_DeltaEta_EndCap", true, false);

normalize_histogram(reco_ele_sip, "Reco_ele_SIP", true, false);
normalize_histogram(reco_ele_sip_barrel, "Reco_ele_SIP_Barrel", true, false);
normalize_histogram(reco_ele_sip_endcap, "Reco_ele_SIP_EndCap", true, false);
normalize_histogram(reco_ele_bdt, "Reco_ele_BDT", true, false);
normalize_histogram(reco_ele_bdt_barrel, "Reco_ele_BDT_Barrel", true, false);
normalize_histogram(reco_ele_bdt_endcap, "Reco_ele_BDT_EndCap", true, false);

normalize_histogram(leading_reco_ele_pt, "Leading_Reco_ele_pT", true, false);
normalize_histogram(leading_reco_ele_eta, "Leading_Reco_ele_Eta", true, false);
normalize_histogram(leading_reco_ele_phi, "Leading_Reco_ele_Phi", true, false);



int nbins = reco_ele_pfiso_simple->GetNbinsX();

for (int x=1; x<nbins; x++)
	{
	if (detail or show_steps) { cout << "Isolation Simple x = " << x << " integral = " << reco_ele_pfiso_simple->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "Isolation Simple Barrel x = " << x << " integral = " << reco_ele_pfiso_simple_barrel->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "Isolation Simple Endcap x = " << x << " integral = " << reco_ele_pfiso_simple_endcap->Integral(0,x) << endl; }

	if (detail or show_steps) { cout << "Isolation Effective Area x = " << x << " integral = " << reco_ele_pfiso_effarea->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "Isolation Effective Area Barrel x = " << x << " integral = " << reco_ele_pfiso_effarea_barrel->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "Isolation Effective Area Endcap x = " << x << " integral = " << reco_ele_pfiso_effarea_endcap->Integral(0,x) << endl; }

	if (detail or show_steps) { cout << "Isolation Delta Eta x = " << x << " integral = " << reco_ele_pfiso_deltaeta->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "Isolation Delta Eta Barrel x = " << x << " integral = " << reco_ele_pfiso_deltaeta_barrel->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "Isolation Delta Eta Endcap x = " << x << " integral = " << reco_ele_pfiso_deltaeta_endcap->Integral(0,x) << endl; }

	if (detail or show_steps) { cout << "SIP x = " << x << " integral = " << reco_ele_sip->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "SIP Barrel x = " << x << " integral = " << reco_ele_sip_barrel->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "SIP Endcap x = " << x << " integral = " << reco_ele_sip_endcap->Integral(0,x) << endl; }
	if (detail or show_steps) { cout << "BDT x = " << x << " integral = " << reco_ele_bdt->Integral(nbins-x,nbins) << endl; }
	if (detail or show_steps) { cout << "BDT Barrel x = " << x << " integral = " << reco_ele_bdt_barrel->Integral(nbins-x,nbins) << endl; }
	if (detail or show_steps) { cout << "BDT Endcap x = " << x << " integral = " << reco_ele_bdt_endcap->Integral(nbins-x,nbins) << endl; }
	isolation_simple[s][x-1] = reco_ele_pfiso_simple->Integral(0,x);
	isolation_simple_barrel[s][x-1] = reco_ele_pfiso_simple_barrel->Integral(0,x);
	isolation_simple_endcap[s][x-1] = reco_ele_pfiso_simple_endcap->Integral(0,x);

	isolation_effarea[s][x-1] = reco_ele_pfiso_effarea->Integral(0,x);
	isolation_effarea_barrel[s][x-1] = reco_ele_pfiso_effarea_barrel->Integral(0,x);
	isolation_effarea_endcap[s][x-1] = reco_ele_pfiso_effarea_endcap->Integral(0,x);

	isolation_deltaeta[s][x-1] = reco_ele_pfiso_deltaeta->Integral(0,x);
	isolation_deltaeta_barrel[s][x-1] = reco_ele_pfiso_deltaeta_barrel->Integral(0,x);
	isolation_deltaeta_endcap[s][x-1] = reco_ele_pfiso_deltaeta_endcap->Integral(0,x);

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

	gen_ele_multiplicity->Write();
	gen_ele_pt->Write();
	gen_ele_eta->Write();
	gen_ele_phi->Write();
	leading_gen_ele_pt->Write();
	leading_gen_ele_eta->Write();
	leading_gen_ele_phi->Write();

	reco_ele_multiplicity->Write();
	reco_ele_pt->Write();
	reco_ele_eta->Write();
	reco_ele_phi->Write();
	reco_ele_dxy->Write();
	reco_ele_dz->Write();
	reco_ele_missinghit->Write();
	reco_ele_pfchhadiso->Write();
	reco_ele_pfchhadiso_barrel->Write();
	reco_ele_pfchhadiso_endcap->Write();
	reco_ele_pfnehadiso->Write();
	reco_ele_pfnehadiso_barrel->Write();
	reco_ele_pfnehadiso_endcap->Write();
	reco_ele_pfphotoniso->Write();
	reco_ele_pfphotoniso_barrel->Write();
	reco_ele_pfphotoniso_endcap->Write();

	reco_ele_pfiso_simple->Write();
	reco_ele_pfiso_simple_barrel->Write();
	reco_ele_pfiso_simple_endcap->Write();
	reco_ele_pfiso_effarea->Write();
	reco_ele_pfiso_effarea_barrel->Write();
	reco_ele_pfiso_effarea_endcap->Write();
	reco_ele_pfiso_deltaeta->Write();
	reco_ele_pfiso_deltaeta_barrel->Write();
	reco_ele_pfiso_deltaeta_endcap->Write();

	reco_ele_bdt->Write();
	reco_ele_bdt_barrel->Write();
	reco_ele_bdt_endcap->Write();
	reco_ele_rho->Write();
	reco_ele_sip->Write();
	reco_ele_sip_barrel->Write();
	reco_ele_sip_endcap->Write();
	leading_reco_ele_pt->Write();
	leading_reco_ele_eta->Write();
	leading_reco_ele_phi->Write();

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
	z4[x] = isolation_effarea_barrel[1][x];
	z5[x] = isolation_effarea_endcap[0][x];
	y5[x] = isolation_effarea_endcap[1][x];

	z6[x] = isolation_deltaeta[0][x];
	y6[x] = isolation_deltaeta[1][x];
	z7[x] = isolation_deltaeta_barrel[0][x];
	y7[x] = isolation_deltaeta_barrel[1][x];
	z8[x] = isolation_deltaeta_endcap[0][x];
	y8[x] = isolation_deltaeta_endcap[1][x];

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

	if (show_steps) { cout << "x = " << x << " - " << z4[x] << " - " << y4[x] << " - " << z6[x] << endl; }
	}

   TCanvas *c1 = new TCanvas("c1","Electron Isolation Simple",200,10,700,500);
   TGraph *gr0 = new TGraph(99,z0,y0);
   gr0->Draw("AL*");
   gr0->GetYaxis()->SetRangeUser(0.9,1.0);
   gr0->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c1, "output/", "electron_isolation_simple");

   TCanvas *c2 = new TCanvas("c2","Electron Isolation Simple Barrel",200,10,700,500);
   TGraph *gr1 = new TGraph(99,z1,y1);
   gr1->Draw("AL*");
   gr1->GetYaxis()->SetRangeUser(0.9,1.0);
   gr1->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c2, "output/", "electron_isolation_simple_barrel");

   TCanvas *c3 = new TCanvas("c3","Electron Isolation Simple Endcap",200,10,700,500);
   TGraph *gr2 = new TGraph(99,z2,y2);
   gr2->Draw("AL*");
   gr2->GetYaxis()->SetRangeUser(0.9,1.0);
   gr2->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c3, "output/", "electron_isolation_simple_endcap");

   TCanvas *c4 = new TCanvas("c4","Electron Isolation Simple All",200,10,700,500);
   gr0->Draw("AL*");
   gr1->Draw("L*");
   gr1->SetLineColor(2);
   gr1->SetMarkerColor(2);
   gr2->Draw("L*");
   gr2->SetLineColor(4);
   gr2->SetMarkerColor(4);
   print_plots(c4, "output/", "electron_isolation_simple_all");


   TCanvas *c5 = new TCanvas("c5","Electron Isolation Effective Area",200,10,700,500);
   TGraph *gr3 = new TGraph(99,z3,y3);
   gr3->Draw("AL*");
   gr3->GetYaxis()->SetRangeUser(0.9,1.0);
   gr3->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c5, "output/", "electron_isolation_effarea");

   TCanvas *c6 = new TCanvas("c6","Electron Isolation Effective Area Barrel",200,10,700,500);
   TGraph *gr4 = new TGraph(99,z4,y4);
   gr4->Draw("AL*");
   gr4->GetYaxis()->SetRangeUser(0.9,1.0);
   gr4->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c6, "output/", "electron_isolation_effarea_barrel");

   TCanvas *c7 = new TCanvas("c3","Electron Isolation Effective Area Endcap",200,10,700,500);
   TGraph *gr5 = new TGraph(99,z5,y5);
   gr5->Draw("AL*");
   gr5->GetYaxis()->SetRangeUser(0.9,1.0);
   gr5->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c7, "output/", "electron_isolation_effarea_endcap");

   TCanvas *c8 = new TCanvas("c8","Electron Isolation Effective Area All",200,10,700,500);
   gr3->Draw("AL*");
   gr4->Draw("L*");
   gr4->SetLineColor(2);
   gr4->SetMarkerColor(2);
   gr5->Draw("L*");
   gr5->SetLineColor(4);
   gr5->SetMarkerColor(4);
   print_plots(c8, "output/", "electron_isolation_effarea_all");


   TCanvas *c9 = new TCanvas("c9","Electron Isolation Delta Eta",200,10,700,500);
   TGraph *gr6 = new TGraph(99,z6,y6);
   gr6->Draw("AL*");
   gr6->GetYaxis()->SetRangeUser(0.9,1.0);
   gr6->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c9, "output/", "electron_isolation_deltaeta");

   TCanvas *c10 = new TCanvas("c10","Electron Isolation Delta Eta Barrel",200,10,700,500);
   TGraph *gr7 = new TGraph(99,z7,y7);
   gr7->Draw("AL*");
   gr7->GetYaxis()->SetRangeUser(0.9,1.0);
   gr7->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c10, "output/", "electron_isolation_deltaeta_barrel");

   TCanvas *c11 = new TCanvas("c11","Electron Isolation Delta Eta Endcap",200,10,700,500);
   TGraph *gr8 = new TGraph(99,z8,y8);
   gr8->Draw("AL*");
   gr8->GetYaxis()->SetRangeUser(0.9,1.0);
   gr8->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c11, "output/", "electron_isolation_deltaeta_endcap");


   TCanvas *c12 = new TCanvas("c12","Electron Isolation Delta Eta All",200,10,700,500);
   gr6->Draw("AL*");
   gr7->Draw("L*");
   gr7->SetLineColor(2);
   gr7->SetMarkerColor(2);
   gr8->Draw("L*");
   gr8->SetLineColor(4);
   gr8->SetMarkerColor(4);
   print_plots(c12, "output/", "electron_isolation_deltaeta_all");


   TCanvas *c13 = new TCanvas("c13","SIP",200,10,700,500);
   TGraph *gr9 = new TGraph(99,z9,y9);
   gr9->Draw("AL*");
   gr9->GetYaxis()->SetRangeUser(0.8,1.0);
   gr9->GetXaxis()->SetRangeUser(0.6,1.0);
   print_plots(c13, "output/", "sip");

   TCanvas *c14 = new TCanvas("c14","SIP Barrel",200,10,700,500);
   TGraph *gr10 = new TGraph(99,z10,y10);
   gr10->Draw("AL*");
   gr10->GetYaxis()->SetRangeUser(0.8,1.0);
   gr10->GetXaxis()->SetRangeUser(0.6,1.0);
   print_plots(c14, "output/", "sip_barrel");

   TCanvas *c15 = new TCanvas("c15","SIP Endcap",200,10,700,500);
   TGraph *gr11 = new TGraph(99,z11,y11);
   gr11->Draw("AL*");
   gr11->GetYaxis()->SetRangeUser(0.8,1.0);
   gr11->GetXaxis()->SetRangeUser(0.6,1.0);
   print_plots(c15, "output/", "sip_endcap");

   TCanvas *c16 = new TCanvas("c16","SIP All",200,10,700,500);
   gr9->Draw("AL*");
   gr10->Draw("L*");
   gr10->SetLineColor(2);
   gr10->SetMarkerColor(2);
   gr11->Draw("L*");
   gr11->SetLineColor(4);
   gr11->SetMarkerColor(4);
   print_plots(c16, "output/", "sip_all");

   TCanvas *c17 = new TCanvas("c17","BDT",200,10,700,500);
   TGraph *gr12 = new TGraph(99,z12,y12);
   gr12->Draw("AL*");
   gr12->GetYaxis()->SetRangeUser(0.9,1.0);
   gr12->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c17, "output/", "bdt");

   TCanvas *c18 = new TCanvas("c18","BDT Barrel",200,10,700,500);
   TGraph *gr13 = new TGraph(99,z13,y13);
   gr13->Draw("AL*");
   gr13->GetYaxis()->SetRangeUser(0.9,1.0);
   gr13->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c18, "output/", "bdt_barrel");

   TCanvas *c19 = new TCanvas("c19","BDT Endcap",200,10,700,500);
   TGraph *gr14 = new TGraph(99,z14,y14);
   gr14->Draw("AL*");
   gr14->GetYaxis()->SetRangeUser(0.9,1.0);
   gr14->GetXaxis()->SetRangeUser(0.0,1.0);
   print_plots(c19, "output/", "bdt_endcap");

   TCanvas *c20 = new TCanvas("c20","BDT All",200,10,700,500);
   gr12->Draw("AL*");
   gr13->Draw("L*");
   gr13->SetLineColor(2);
   gr13->SetMarkerColor(2);
   gr14->Draw("L*");
   gr14->SetLineColor(4);
   gr14->SetMarkerColor(4);
   print_plots(c20, "output/", "bdt_all");

}
