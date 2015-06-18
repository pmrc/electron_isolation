// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"

#include "TFile.h"
#include "TTree.h"

#include <string>
#include <iostream>

using namespace std;

namespace reco {
  typedef edm::Ptr<reco::GsfElectron> GsfElectronPtr;
}

class LeptonVariableNtuplizer : public edm::EDAnalyzer {

public:
  explicit LeptonVariableNtuplizer(const edm::ParameterSet&);
  ~LeptonVariableNtuplizer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
  //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
  
  // ----------member data ---------------------------

  string outputFileName_;
  edm::InputTag electronTag_;
  edm::InputTag muonTag_;
  edm::InputTag genParticleTag_;
  edm::InputTag vtxToken_;

  TFile* f;
  TTree* t;

  Int_t nEvent;
  Int_t nRun;
  Int_t nLumi;
  Int_t nPV_;
  Int_t nPU_;
  Int_t nPUTrue_;
  Float_t rho_;

  //gen electrons
  Int_t ge_n;
  Float_t ge_pt[100];
  Float_t ge_eta[100];
  Float_t ge_phi[100];

  //gen muons
  Int_t gm_n;
  Float_t gm_pt[100];
  Float_t gm_eta[100];
  Float_t gm_phi[100];

  //reco electrons  
  Int_t nele;
  Float_t ele_pt[100];
  Float_t ele_eta[100];
  Float_t ele_sclEta[100];
  Int_t ele_isEB[100];
  Int_t ele_isEE[100];
  Float_t ele_phi[100];

  Float_t ele_effective_area[100];
  Float_t ele_PFChargedHadIsoRel[100];
  Float_t ele_PFNeutralHadIsoRel[100];
  Float_t ele_PFPhotonIsoRel[100];
  Float_t ele_PFChargedFromPURel[100];
  Float_t ele_PFChargedHadIso[100];
  Float_t ele_PFNeutralHadIso[100];
  Float_t ele_PFPhotonIso[100];
  Float_t ele_PFChargedFromPU[100];
  Float_t ele_PFIso_simple[100];
  Float_t ele_PFIso_effarea[100];
  Float_t ele_PFIso_deltabeta[100];

  Float_t sumChargedHadronPt_CITK[100];
  Float_t sumNeutralHadronPt_CITK[100];
  Float_t sumPhotonPt_CITK[100];
  Float_t reliso_CITK[100];
  Float_t sumChargedHadronPt_PUPPI[100];
  Float_t sumNeutralHadronPt_PUPPI[100];
  Float_t sumPhotonPt_PUPPI[100];
  Float_t reliso_PUPPI[100];
  Float_t sumChargedHadronPt_PUPPI_NoLeptons[100];
  Float_t sumNeutralHadronPt_PUPPI_NoLeptons[100];
  Float_t sumPhotonPt_PUPPI_NoLeptons[100];
  Float_t reliso_PUPPI_NoLeptons[100];
  Float_t relisoChargedHadronPt_CITK[100];
  Float_t relisoNeutralHadronPt_CITK[100];
  Float_t relisoPhotonPt_CITK[100];
  Float_t relisoChargedHadronPt_PUPPI[100];
  Float_t relisoNeutralHadronPt_PUPPI[100];
  Float_t relisoPhotonPt_PUPPI[100];
  Float_t relisoChargedHadronPt_PUPPINoLeptons[100];
  Float_t relisoNeutralHadronPt_PUPPINoLeptons[100];
  Float_t relisoPhotonPt_PUPPINoLeptons[100];

  Float_t ele_SIP[100];
  Float_t ele_dxy[100];
  Float_t ele_dz[100];
  Float_t ele_BDT[100];
  Float_t ele_isBDT[100];
  Float_t ele_missingHit[100];
  Float_t ele_ID[100];
  Float_t ele_isGood[100];

  Float_t fMVAVar_kfhits[100];
  Float_t fMVAVar_see[100];
  Float_t fMVAVar_spp[100];
  Float_t fMVAVar_OneMinusE1x5E5x5[100];
  Float_t fMVAVar_R9[100];
  Float_t fMVAVar_etawidth[100];
  Float_t fMVAVar_phiwidth[100];
  Float_t fMVAVar_HoE[100];
  Float_t fMVAVar_PreShowerOverRaw[100];
  Float_t fMVAVar_kfchi2[100];
  Float_t fMVAVar_gsfchi2[100];
  Float_t fMVAVar_fbrem[100];
  Float_t fMVAVar_EoP[100];
  Float_t fMVAVar_eleEoPout[100];
  Float_t fMVAVar_IoEmIoP[100];
  Float_t fMVAVar_deta[100];
  Float_t fMVAVar_dphi[100];
  Float_t fMVAVar_hOverE[100];
  Float_t fMVAVar_detacalo[100]; 
  Float_t fMVAVar_full5x5_sigmaIetaIeta[100];
  Float_t fMVAVar_ooEmooP[100];
  //Float_t fMVAVar_classification[100];

  //reco muons  
  Int_t nmu;
  Float_t mu_pt[100];
  Float_t mu_eta[100];
  Float_t mu_phi[100];
  Float_t mu_PFChargedHadIso[100];
  Float_t mu_PFNeutralHadIso[100];
  Float_t mu_PFPhotonIso[100];
  Float_t mu_combRelIsoPF[100];
  Float_t mu_rho[100];
  Float_t mu_SIP[100];
  Float_t mu_dxy[100];
  Float_t mu_dz[100];
  Float_t mu_ID[100];
  Float_t mu_isGood[100];

};

LeptonVariableNtuplizer::LeptonVariableNtuplizer(const edm::ParameterSet& iConfig) {
  outputFileName_ = iConfig.getParameter<std::string>("OutputFileName");
  electronTag_ = iConfig.getParameter<edm::InputTag>("electronSrc");
  muonTag_ = iConfig.getParameter<edm::InputTag>("muonSrc");
  genParticleTag_ = iConfig.getParameter<edm::InputTag>("genParticleSrc");
}

LeptonVariableNtuplizer::~LeptonVariableNtuplizer() {}


bool isGoodGenElectron2(reco::GenParticleRef p){

  if(fabs(p->pdgId())==11){
    if(p->status()==1){
      if(p->numberOfMothers()>0){
	const reco::Candidate  *Mom = p->mother();
	while(Mom!=0){
	  if(fabs(Mom->pdgId()) == 23){ 
	    return true;
	  }else if(fabs(Mom->pdgId())==15 || fabs(Mom->pdgId())>50){ 
	    break;
	  }
	  Mom = Mom->mother();
	}
      }
    }
  }

  return false;

}

bool isGoodGenMuon2(reco::GenParticleRef p){

  if(fabs(p->pdgId())==13){
    if(p->status()==1){
      if(p->numberOfMothers()>0){
	const reco::Candidate  *Mom = p->mother();
	while(Mom!=0){
	  if(fabs(Mom->pdgId()) == 23){ 
	    return true;
	  }else if(fabs(Mom->pdgId())==15 || fabs(Mom->pdgId())>50){ 
	    break;
	  }
	  Mom = Mom->mother();
	}
      }
    }
  }

  return false;

}

double ismatched(double phi1, double eta1, double phi2, double eta2)
{
  double delta_phi = TMath::ACos(TMath::Cos(phi1-phi2));
  double r = TMath::Sqrt((eta1-eta2)*(eta1-eta2) + delta_phi*delta_phi);
  return r;
}


// ------------ method called for each event  ------------
void
LeptonVariableNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  cout<<"call method analyze"<<endl;

  nEvent = iEvent.id().event();
  nRun   = iEvent.id().run();
  nLumi  = iEvent.luminosityBlock();

  edm::Handle<reco::GenParticleCollection> gpH;
  iEvent.getByLabel(genParticleTag_, gpH);

  //gp_n = 0;
  ge_n = 0;
  gm_n = 0;
  for (size_t i=0; i<gpH->size(); ++i) {
    const reco::GenParticleRef gp(gpH, i);
    if(isGoodGenElectron2(gp)){
      ge_pt [ge_n] = gp->pt ();
      ge_eta[ge_n] = gp->eta();
      ge_phi[ge_n] = gp->phi();
      ge_n++;
    }
    if(isGoodGenMuon2(gp)){
      gm_pt [gm_n] = gp->pt ();
      gm_eta[gm_n] = gp->eta();
      gm_phi[gm_n] = gp->phi();
      gm_n++;
    }
  }    

  edm::Handle<std::vector< PileupSummaryInfo > > PupInfo;
  iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
  for(std::vector<PileupSummaryInfo>::const_iterator PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI){
    if(PVI->getBunchCrossing()==0){
      nPU_    = PVI->getPU_NumInteractions();
      nPUTrue_= PVI->getTrueNumInteractions();
      break;
    }
  }
  

   //from puppi
  // Get Pileup info
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(edm::InputTag("offlineSlimmedPrimaryVertices"), vertices);
  //if (vertices->empty()) return; // skip the event if no PV found
  //const reco::Vertex &pv = vertices->front();
  nPV_ = vertices -> size();
  //end of puppi section

  edm::Handle<pat::ElectronCollection> electronHandle;
  iEvent.getByLabel(electronTag_, electronHandle);

  // Get electron collection
  edm::Handle<edm::View<reco::Candidate> > electrons;
  iEvent.getByLabel("slimmedElectrons", electrons);

  nele = 0;
  //cout<<"in LeptonVariableNtuplizer.cc : electronHandle->size() = "<<electronHandle->size()<<endl;

  //CITK
  edm::Handle <edm::ValueMap <float> > ValueMaps_ChargedHadrons, ValueMaps_NeutralHadrons, ValueMaps_Photons;
  edm::Handle <edm::ValueMap <float> > ValueMaps_PUPPI_ChargedHadrons, ValueMaps_PUPPI_NeutralHadrons, ValueMaps_PUPPI_Photons;
  edm::Handle <edm::ValueMap <float> > ValueMaps_PUPPI_NoLeptons_ChargedHadrons, ValueMaps_PUPPI_NoLeptons_NeutralHadrons, ValueMaps_PUPPI_NoLeptons_Photons;

  //CITK
  iEvent.getByLabel( edm::InputTag("ElectronIsolation", "h+-DR030-BarVeto000-EndVeto001") , ValueMaps_ChargedHadrons);
  iEvent.getByLabel( edm::InputTag("ElectronIsolation", "h0-DR030-BarVeto000-EndVeto000") , ValueMaps_NeutralHadrons);
  iEvent.getByLabel( edm::InputTag("ElectronIsolation", "gamma-DR030-BarVeto000-EndVeto008") , ValueMaps_Photons);
  
  //PUPPI 
  iEvent.getByLabel( edm::InputTag("ElectronIsolationOnPUPPI", "h+-DR030-BarVeto000-EndVeto001") , ValueMaps_PUPPI_ChargedHadrons);
  iEvent.getByLabel( edm::InputTag("ElectronIsolationOnPUPPI", "h0-DR030-BarVeto000-EndVeto000") , ValueMaps_PUPPI_NeutralHadrons);
  iEvent.getByLabel( edm::InputTag("ElectronIsolationOnPUPPI", "gamma-DR030-BarVeto000-EndVeto008") , ValueMaps_PUPPI_Photons);
  
  //PUPPI_NoLeptons 
  iEvent.getByLabel( edm::InputTag("ElectronIsolationOnPUPPINoLeptons", "h+-DR030-BarVeto000-EndVeto001") , ValueMaps_PUPPI_NoLeptons_ChargedHadrons);
  iEvent.getByLabel( edm::InputTag("ElectronIsolationOnPUPPINoLeptons", "h0-DR030-BarVeto000-EndVeto000") , ValueMaps_PUPPI_NoLeptons_NeutralHadrons);
  iEvent.getByLabel( edm::InputTag("ElectronIsolationOnPUPPINoLeptons", "gamma-DR030-BarVeto000-EndVeto008") , ValueMaps_PUPPI_NoLeptons_Photons);

    //Float_t isoChargedFromPU_;

    rho_ = 0.0;    

  for(unsigned int iele=0; iele<electronHandle->size(); iele++){

    ele_pt[nele] = -9999.;
    ele_eta[nele] = -9999.;
    ele_sclEta[nele] = -9999.;
    ele_isEB[nele] = -9999.;
    ele_isEE[nele] = -9999.;
    ele_phi[nele] = -9999.;
    ele_effective_area[nele] = -9999.;
    ele_PFChargedHadIsoRel[nele] = -9999.;
    ele_PFNeutralHadIsoRel[nele] = -9999.;
    ele_PFPhotonIsoRel[nele] = -9999.;
    ele_PFChargedFromPURel[nele] = -9999.;
    ele_PFChargedHadIso[nele] = -9999.;
    ele_PFNeutralHadIso[nele] = -9999.;
    ele_PFPhotonIso[nele] = -9999.;
    ele_PFChargedFromPU[nele] = -9999.;
    ele_PFIso_simple[nele] = -9999.;
    ele_PFIso_effarea[nele] = -9999.;
    ele_PFIso_deltabeta[nele] = -9999.;
    ele_SIP[nele] = -9999.;
    ele_dxy[nele] = -9999.;
    ele_dz[nele] = -9999.;
    ele_BDT[nele] = -9999.;
    ele_isBDT[nele] = -9999.;
    ele_missingHit[nele] = -9999.;
    ele_ID[nele] = -9999.;
    ele_isGood[nele] = -9999.;
    fMVAVar_kfhits[nele] = -9999.;
    fMVAVar_see[nele] = -9999.;
    fMVAVar_spp[nele] = -9999.;
    fMVAVar_OneMinusE1x5E5x5[nele] = -9999.;
    fMVAVar_R9[nele] = -9999.;
    fMVAVar_etawidth[nele] = -9999.;
    fMVAVar_phiwidth[nele] = -9999.;
    fMVAVar_HoE[nele] = -9999.;
    fMVAVar_PreShowerOverRaw[nele] = -9999.;
    fMVAVar_kfchi2[nele] = -9999.;
    fMVAVar_gsfchi2[nele] = -9999.;
    fMVAVar_fbrem[nele] = -9999.;
    fMVAVar_EoP[nele] = -9999.;
    fMVAVar_eleEoPout[nele] = -9999.;
    fMVAVar_IoEmIoP[nele] = -9999.;
    fMVAVar_deta[nele] = -9999.;
    fMVAVar_dphi[nele] = -9999.;
    fMVAVar_hOverE[nele] = -9999.;
    fMVAVar_detacalo[nele] = -9999.;
    fMVAVar_full5x5_sigmaIetaIeta[nele] = -9999.;
    fMVAVar_ooEmooP[nele] = -9999.;
    //fMVAVar_classification[nele] = -9999.;

  
    const pat::Electron* e = &((*electronHandle)[iele]);
    auto elePtr = electrons -> ptrAt(0);

    for (unsigned int iElectron = 0; iElectron < electrons -> size(); iElectron++)
	{
	auto elePtr_tmp = electrons -> ptrAt(iElectron);
	reco::GsfElectronPtr eleGsfPtr(elePtr_tmp);
	double r = ismatched(e->phi(), e->eta(), eleGsfPtr->phi(), eleGsfPtr->eta());
	if (r <= 0.05) { elePtr = electrons -> ptrAt(iElectron); break; }
	}

    //reco::GsfElectronPtr eleGsfPtr(elePtr);
    //reco::GsfElectron::PflowIsolationVariables pfIso = eleGsfPtr -> pfIsolationVariables();
    //isoChargedFromPU_  = pfIso.sumPUPt ;

    if(e->pt()<5.) continue;

    rho_ = e->userFloat("rho");
    ele_pt[nele] = e->pt(); // ->et() gives same result
    ele_eta[nele] = e->eta();
    ele_sclEta[nele] = e->superCluster()->eta();
    ele_isEB[nele] = e->isEB();
    ele_isEE[nele] = e->isEE();
    ele_phi[nele] = e->phi();
    ele_effective_area[nele] = e->userFloat("effective_area");
    ele_PFChargedHadIsoRel[nele] = e->userFloat("PFChargedHadIsoRel");
    ele_PFNeutralHadIsoRel[nele] = e->userFloat("PFNeutralHadIsoRel");
    ele_PFPhotonIsoRel[nele] = e->userFloat("PFPhotonIsoRel");
    ele_PFChargedFromPURel[nele] = e->userFloat("PFChargedFromPURel");
    ele_PFChargedHadIso[nele] = e->userFloat("PFChargedHadIso");
    ele_PFNeutralHadIso[nele] = e->userFloat("PFNeutralHadIso");
    ele_PFPhotonIso[nele] = e->userFloat("PFPhotonIso");
    ele_PFChargedFromPU[nele] = e->userFloat("PFChargedFromPU");
    ele_PFIso_simple[nele] = e->userFloat("PFIso_simple");
    ele_PFIso_effarea[nele] = e->userFloat("PFIso_effarea");
    ele_PFIso_deltabeta[nele] = e->userFloat("PFIso_deltabeta");
    ele_SIP[nele] = e->userFloat("SIP");
    ele_dxy[nele] = e->userFloat("dxy");
    ele_dz[nele] = e->userFloat("dz");
    ele_BDT[nele] = e->userFloat("BDT");
    ele_isBDT[nele] = e->userFloat("isBDT");
    ele_missingHit[nele] = e->userFloat("missingHit");
    ele_ID[nele] = e->userFloat("ID");
    ele_isGood[nele] = e->userFloat("isGood");

    bool validKF= false;
    reco::TrackRef myTrackRef = e->closestCtfTrackRef();
    validKF = (myTrackRef.isAvailable());
    validKF = (myTrackRef.isNonnull());
    fMVAVar_kfhits[nele]    = (validKF) ? myTrackRef->hitPattern().trackerLayersWithMeasurement() : -1. ;
    fMVAVar_see[nele]       = e->full5x5_sigmaIetaIeta();
    fMVAVar_spp[nele]       = e->full5x5_sigmaIphiIphi();
    fMVAVar_OneMinusE1x5E5x5[nele] = (e->full5x5_e5x5()) !=0. ? 1.-(e->full5x5_e1x5()/e->full5x5_e5x5()) : -1. ;
    fMVAVar_R9[nele]        = e->full5x5_r9();
    fMVAVar_etawidth[nele]  = e->superCluster()->etaWidth();
    fMVAVar_phiwidth[nele]  = e->superCluster()->phiWidth();
    fMVAVar_HoE[nele]       = e->hadronicOverEm();
    fMVAVar_PreShowerOverRaw[nele] = e->superCluster()->preshowerEnergy() / e->superCluster()->rawEnergy();
    fMVAVar_kfchi2[nele]    = (validKF) ? myTrackRef->normalizedChi2() : 0 ;
    fMVAVar_gsfchi2[nele]   = e->gsfTrack()->normalizedChi2();
    fMVAVar_fbrem[nele]     = e->fbrem();
    fMVAVar_EoP[nele]       = e->eSuperClusterOverP();;
    fMVAVar_eleEoPout[nele] = e->eEleClusterOverPout();
    fMVAVar_IoEmIoP[nele]   = (1.0/e->ecalEnergy()) - (1.0 / e->trackMomentumAtVtx().R());
    fMVAVar_deta[nele]      = e->deltaEtaSuperClusterTrackAtVtx();
    fMVAVar_dphi[nele]      = e->deltaPhiSuperClusterTrackAtVtx();
    fMVAVar_hOverE[nele]    = e->hcalOverEcal();
    fMVAVar_detacalo[nele]  = e->deltaEtaSeedClusterTrackAtCalo();
    fMVAVar_full5x5_sigmaIetaIeta[nele] = e->full5x5_sigmaIetaIeta();
    if( e->ecalEnergy() == 0 ){
      printf("Electron energy is zero!\n");
      fMVAVar_ooEmooP[nele] = 1e30;
    }else if( !std::isfinite(e->ecalEnergy())){
      printf("Electron energy is not finite!\n");
      fMVAVar_ooEmooP[nele] = 1e30;
    }else{
      fMVAVar_ooEmooP[nele] = fabs(1.0/e-> ecalEnergy() - e-> eSuperClusterOverP()/e-> ecalEnergy() );
    }
    //fMVAVar_classification[nele] = e->classification();


    //directly form puppi
    //CITK
    sumChargedHadronPt_CITK[nele] =  (*ValueMaps_ChargedHadrons)[elePtr];
    sumNeutralHadronPt_CITK[nele] =  (*ValueMaps_NeutralHadrons)[elePtr];
    sumPhotonPt_CITK[nele]        =  (*ValueMaps_Photons)[elePtr];
    
    cout << "#" << nele << " - > " <<  sumChargedHadronPt_CITK[nele] << endl;

    //PUPPI
    sumChargedHadronPt_PUPPI[nele] =  (*ValueMaps_PUPPI_ChargedHadrons)[elePtr];
    sumNeutralHadronPt_PUPPI[nele] =  (*ValueMaps_PUPPI_NeutralHadrons)[elePtr];
    sumPhotonPt_PUPPI[nele]        =  (*ValueMaps_PUPPI_Photons)[elePtr];

    //PUPPINoLeptons
    sumChargedHadronPt_PUPPI_NoLeptons[nele] =  (*ValueMaps_PUPPI_NoLeptons_ChargedHadrons)[elePtr];
    sumNeutralHadronPt_PUPPI_NoLeptons[nele] =  (*ValueMaps_PUPPI_NoLeptons_NeutralHadrons)[elePtr];
    sumPhotonPt_PUPPI_NoLeptons[nele]        =  (*ValueMaps_PUPPI_NoLeptons_Photons)[elePtr];
 
    //CITK
    relisoChargedHadronPt_CITK[nele] = sumChargedHadronPt_CITK[nele]/ele_pt[nele];
    relisoNeutralHadronPt_CITK[nele] = sumNeutralHadronPt_CITK[nele]/ele_pt[nele];
    relisoPhotonPt_CITK[nele] = sumPhotonPt_CITK[nele]/ele_pt[nele];
    
    //PUPPI
    relisoChargedHadronPt_PUPPI[nele] = sumChargedHadronPt_PUPPI[nele]/ele_pt[nele];
    relisoNeutralHadronPt_PUPPI[nele] = sumNeutralHadronPt_PUPPI[nele]/ele_pt[nele];
    relisoPhotonPt_PUPPI[nele] = sumPhotonPt_PUPPI[nele]/ele_pt[nele];
    
    //PUPPI_NoLeptons
    relisoChargedHadronPt_PUPPINoLeptons[nele] = sumChargedHadronPt_PUPPI_NoLeptons[nele]/ele_pt[nele];
    relisoNeutralHadronPt_PUPPINoLeptons[nele] = sumNeutralHadronPt_PUPPI_NoLeptons[nele]/ele_pt[nele];
    relisoPhotonPt_PUPPINoLeptons[nele] = sumPhotonPt_PUPPI_NoLeptons[nele]/ele_pt[nele];
    
    //CITK total isolation   
    reliso_CITK[nele] = (sumChargedHadronPt_CITK[nele] + sumNeutralHadronPt_CITK[nele] + sumPhotonPt_CITK[nele])/ele_pt[nele];

    //PUPPI total isolation   
    reliso_PUPPI[nele] = (sumChargedHadronPt_PUPPI[nele] + sumNeutralHadronPt_PUPPI[nele] + sumPhotonPt_PUPPI[nele])/ele_pt[nele];
    //PUPPINoLeptons total isolation
    reliso_PUPPI_NoLeptons[nele] = (sumChargedHadronPt_PUPPI_NoLeptons[nele] + sumNeutralHadronPt_PUPPI_NoLeptons[nele] + sumPhotonPt_PUPPI_NoLeptons[nele])/ele_pt[nele];

    //end of puppi section

    nele++;

  }
  
  //cout << "Number of electrons = " << nele << endl;

  edm::Handle<pat::MuonCollection> muonHandle;
  iEvent.getByLabel(muonTag_, muonHandle);

  nmu = 0;
  //cout<<"in LeptonVariableNtuplizer.cc : muonHandle->size() = "<<muonHandle->size()<<endl;

  for(unsigned int imu=0; imu<muonHandle->size(); imu++){

    mu_pt[nmu] = -9999.;
    mu_eta[nmu] = -9999.;
    mu_phi[nmu] = -9999.;
    mu_PFChargedHadIso[nmu] = -9999.;
    mu_PFNeutralHadIso[nmu] = -9999.;
    mu_PFPhotonIso[nmu] = -9999.;
    mu_combRelIsoPF[nmu] = -9999.;
    mu_rho[nmu] = -9999.;
    mu_SIP[nmu] = -9999.;
    mu_dxy[nmu] = -9999.;
    mu_dz[nmu] = -9999.;
    mu_ID[nmu] = -9999.;
    mu_isGood[nmu] = -9999.;
      
    const pat::Muon* m = &((*muonHandle)[imu]);

    if(m->pt()<5.) continue;

    mu_pt[nmu] = m->pt();
    mu_eta[nmu] = m->eta();
    mu_phi[nmu] = m->phi();
    mu_PFChargedHadIso[nmu] = m->userFloat("PFChargedHadIso");
    mu_PFNeutralHadIso[nmu] = m->userFloat("PFNeutralHadIso");
    mu_PFPhotonIso[nmu] = m->userFloat("PFPhotonIso");
    mu_combRelIsoPF[nmu] = m->userFloat("combRelIsoPF");
    mu_rho[nmu] = m->userFloat("rho");
    mu_SIP[nmu] = m->userFloat("SIP");
    mu_dxy[nmu] = m->userFloat("dxy");
    mu_dz[nmu] = m->userFloat("dz");
    mu_ID[nmu] = m->userFloat("ID");
    mu_isGood[nmu] = m->userFloat("isGood");

    nmu++;

  }
  
  t->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
LeptonVariableNtuplizer::beginJob(){
  //cout<<"call method beginJob"<<endl;
  f = new TFile(outputFileName_.c_str(), "recreate");
  t = new TTree("tree", "tree");
  
  t->Branch("nEvent", &nEvent, "nEvent/I");
  t->Branch("nRun", &nRun, "nRun/I");
  t->Branch("nLumi", &nLumi, "nLumi/I");
  
  t->Branch("nPV"        ,  &nPV_     , "nPV/I");
  t->Branch("nPU"        ,  &nPU_     , "nPU/I");
  t->Branch("nPUTrue"    ,  &nPUTrue_ , "nPUTrue/I");
  t->Branch("rho"        ,  &rho_ , "rho/F");

  t->Branch("gen", &ge_n, "gen/I");
  t->Branch("gept", &ge_pt, "gept[gen]/F");
  t->Branch("geeta", &ge_eta, "geeta[gen]/F");
  t->Branch("gephi", &ge_phi, "gephi[gen]/F");
  t->Branch("gmn", &gm_n, "gmn/I");
  t->Branch("gmpt", &gm_pt, "gmpt[gmn]/F");
  t->Branch("gmeta", &gm_eta, "gmeta[gmn]/F");
  t->Branch("gmphi", &gm_phi, "gmphi[gmn]/F");
  
  t->Branch("nele", &nele, "nele/I");
  t->Branch("ele_pt" , &ele_pt , "ele_pt[nele]/F" );
  t->Branch("ele_eta", &ele_eta, "ele_eta[nele]/F");
  t->Branch("ele_sclEta", &ele_sclEta, "ele_sclEta[nele]/F");
  t->Branch("ele_isEB", &ele_isEB, "ele_isEB[nele]/I");
  t->Branch("ele_isEE", &ele_isEE, "ele_isEE[nele]/I");
  t->Branch("ele_phi", &ele_phi, "ele_phi[nele]/F");
  t->Branch("ele_effective_area", &ele_effective_area, "ele_effective_area[nele]/F");

  t->Branch("ele_PFChargedHadIsoRel", &ele_PFChargedHadIsoRel, "ele_PFChargedHadIsoRel[nele]/F");
  t->Branch("ele_PFNeutralHadIsoRel", &ele_PFNeutralHadIsoRel, "ele_PFNeutralHadIsoRel[nele]/F");
  t->Branch("ele_PFPhotonIsoRel", &ele_PFPhotonIsoRel, "ele_PFPhotonIsoRel[nele]/F");
  t->Branch("ele_PFChargedFromPURel"       , &ele_PFChargedFromPURel, "ele_PFChargedFromPURel[nele]/F");
  t->Branch("ele_PFChargedHadIso"      , &ele_PFChargedHadIso , "ele_PFChargedHadIso[nele]/F");
  t->Branch("ele_PFNeutralHadIso"      , &ele_PFNeutralHadIso, "ele_PFNeutralHadIsoRel[nele]/F");
  t->Branch("ele_PFPhotonIso"          , &ele_PFPhotonIso, "ele_PFPhotonIsoRel[nele]/F");
  t->Branch("ele_PFChargedFromPU"       , &ele_PFChargedFromPU, "ele_PFChargedFromPU[nele]/F");

  t->Branch("ele_PFChargedHadIsoRel_PUPPI", &relisoChargedHadronPt_PUPPI, "relisoChargedHadronPt_PUPPI[nele]/F");
  t->Branch("ele_PFNeutralHadIsoRel_PUPPI", &relisoNeutralHadronPt_PUPPI, "relisoNeutralHadronPt_PUPPI[nele]/F");
  t->Branch("ele_PFPhotonIsoRel_PUPPI", &relisoPhotonPt_PUPPI, "relisoPhotonPt_PUPPI[nele]/F");
  t->Branch("ele_PFChargedHadIso_PUPPI", &sumChargedHadronPt_PUPPI, "sumChargedHadronPt_PUPPI[nele]/F");
  t->Branch("ele_PFNeutralHadIso_PUPPI", &sumNeutralHadronPt_PUPPI, "sumNeutralHadronPt_PUPPI[nele]/F");
  t->Branch("ele_PFPhotonIso_PUPPI", &sumPhotonPt_PUPPI, "sumPhotonPt_PUPPI[nele]/F");
  t->Branch("ele_PFChargedHadIsoRel_PUPPI_NoLeptons", &relisoChargedHadronPt_PUPPINoLeptons, "relisoChargedHadronPt_PUPPINoLeptons[nele]/F");
  t->Branch("ele_PFNeutralHadIsoRel_PUPPI_NoLeptons", &relisoNeutralHadronPt_PUPPINoLeptons, "relisoNeutralHadronPt_PUPPINoLeptons[nele]/F");
  t->Branch("ele_PFPhotonIso_PUPPI_NoLeptons", &relisoPhotonPt_PUPPINoLeptons, "relisoPhotonPt_PUPPINoLeptons[nele]/F");
  t->Branch("ele_PFChargedHadIso_PUPPI_NoLeptons", &sumChargedHadronPt_PUPPI_NoLeptons, "sumChargedHadronPt_PUPPI_NoLeptons[nele]/F");
  t->Branch("ele_PFNeutralHadIso_PUPPI_NoLeptons", &sumNeutralHadronPt_PUPPI_NoLeptons, "sumNeutralHadronPt_PUPPI_NoLeptons[nele]/F");
  t->Branch("ele_PFPhotonIso_PUPPI_NoLeptons", &sumPhotonPt_PUPPI_NoLeptons, "sumPhotonPt_PUPPI_NoLeptons[nele]/F");
  t->Branch("ele_PFChargedHadIsoRel_CITK", &relisoChargedHadronPt_CITK, "relisoChargedHadronPt_CITK[nele]/F");
  t->Branch("ele_PFNeutralHadIsoRel_CITK", &relisoNeutralHadronPt_CITK, "relisoNeutralHadronPt_CITK[nele]/F");
  t->Branch("ele_PFPhotonIsoRel_CITK", &relisoPhotonPt_CITK, "relisoPhotonPt_CITK/F");
  t->Branch("ele_PFChargedHadIso_CITK", &sumChargedHadronPt_CITK, "sumChargedHadronPt_CITK[nele]/F");
  t->Branch("ele_PFNeutralHadIso_CITK", &sumNeutralHadronPt_CITK, "sumNeutralHadronPt_CITK[nele]/F");
  t->Branch("ele_PFPhotonIso_CITK", &sumPhotonPt_CITK, "sumPhotonPt_CITK[nele]/F");

  t->Branch("ele_PFIso_simple", &ele_PFIso_simple, "ele_PFIso_simples[nele]/F");
  t->Branch("ele_PFIso_effarea", &ele_PFIso_effarea, "ele_PFIso_effarea[nele]/F");
  t->Branch("ele_PFIso_deltabeta", &ele_PFIso_deltabeta, "ele_PFIso_deltabeta[nele]/F");
  t->Branch("ele_PFIso_PUPPI", &reliso_PUPPI, "reliso_PUPPI[nele]/F");
  t->Branch("ele_PFIso_NoLeptons", &reliso_PUPPI_NoLeptons, "reliso_PUPPI_NoLeptons[nele]/F");
  t->Branch("ele_PFIso_CITK", &reliso_CITK, "reliso_CITK[nele]/F");

  t->Branch("ele_SIP", &ele_SIP, "ele_SIP[nele]/F");
  t->Branch("ele_dxy", &ele_dxy, "ele_dxy[nele]/F");
  t->Branch("ele_dz", &ele_dz, "ele_dz[nele]/F");
  t->Branch("ele_BDT", &ele_BDT, "ele_BDT[nele]/F");
  t->Branch("ele_isBDT", &ele_isBDT, "ele_isBDT[nele]/F");
  t->Branch("ele_missingHit", &ele_missingHit, "ele_missingHit[nele]/F");
  t->Branch("ele_ID", &ele_ID, "ele_ID[nele]/F");
  t->Branch("ele_isGood", &ele_isGood, "ele_isGood[nele]/F");     

  t->Branch("ele_kfhits", &fMVAVar_kfhits, "ele_kfhits[nele]/F");
  t->Branch("ele_oldsigmaietaieta", &fMVAVar_see, "ele_oldsigmaietaieta[nele]/F");
  t->Branch("ele_oldsigmaiphiiphi", &fMVAVar_spp, "ele_oldsigmaiphiiphi[nele]/F");
  t->Branch("ele_oldcircularity", &fMVAVar_OneMinusE1x5E5x5, "ele_oldcircularity[nele]/F");
  t->Branch("ele_oldr9", &fMVAVar_R9, "ele_oldr9[nele]/F");
  t->Branch("ele_scletawidth", &fMVAVar_etawidth, "ele_scletawidth[nele]/F");
  t->Branch("ele_sclphiwidth", &fMVAVar_phiwidth, "ele_sclphiwidth[nele]/F");
  t->Branch("ele_he", &fMVAVar_HoE, "ele_he[nele]/F");
  t->Branch("ele_psEoverEraw", &fMVAVar_PreShowerOverRaw, "ele_psEoverEraw[nele]/F");
  t->Branch("ele_kfchi2", &fMVAVar_kfchi2, "ele_kfchi2[nele]/F");
  t->Branch("ele_chi2_hits", &fMVAVar_gsfchi2, "ele_chi2_hits[nele]/F");
  t->Branch("ele_fbrem", &fMVAVar_fbrem, "ele_fbrem[nele]/F");
  t->Branch("ele_ep", &fMVAVar_EoP, "ele_ep[nele]/F");
  t->Branch("ele_eelepout", &fMVAVar_eleEoPout, "ele_eelepout[nele]/F");
  t->Branch("ele_IoEmIop", &fMVAVar_IoEmIoP, "ele_IoEmIop[nele]/F");
  t->Branch("ele_deltaetain", &fMVAVar_deta, "ele_deltaetain[nele]/F");
  t->Branch("ele_deltaphiin", &fMVAVar_dphi, "ele_deltaphiin[nele]/F");
  t->Branch("ele_hOverE",  &fMVAVar_hOverE, "ele_hOverE[nele]/F");
  t->Branch("ele_deltaetaseed", &fMVAVar_detacalo, "ele_deltaetaseed[nele]/F");
  t->Branch("ele_full5x5_sigmaIetaIeta", &fMVAVar_full5x5_sigmaIetaIeta, "ele_full5x5_sigmaIetaIeta[nele]/F");
  t->Branch("ele_ooEmooP", &fMVAVar_ooEmooP, "ele_ooEmooP[nele]/F");
  //t->Branch("ele_classification"    , &fMVAVar_classification,     "ele_classification[nele]/I");
  //t->Branch("ele_isTrueElectron"    , &isTrueElectron_,     "isTrueElectron[nele]/I"); //not used at the moment

  t->Branch("nmu", &nmu, "nmu/I");
  t->Branch("mu_pt" , &mu_pt , "mu_pt[nmu]/F" );
  t->Branch("mu_eta", &mu_eta, "mu_eta[nmu]/F");
  t->Branch("mu_phi", &mu_phi, "mu_phi[nmu]/F");
  t->Branch("mu_PFChargedHadIso", &mu_PFChargedHadIso, "mu_PFChargedHadIso[nmu]/F");
  t->Branch("mu_PFNeutralHadIso", &mu_PFNeutralHadIso, "mu_PFNeutralHadIso[nmu]/F");
  t->Branch("mu_PFPhotonIso", &mu_PFPhotonIso, "mu_PFPhotonIso[nmu]/F");
  t->Branch("mu_combRelIsoPF", &mu_combRelIsoPF, "mu_combRelIsoPF[nmu]/F");
  t->Branch("mu_rho", &mu_rho, "mu_rho[nmu]/F");
  t->Branch("mu_SIP", &mu_SIP, "mu_SIP[nmu]/F");
  t->Branch("mu_dxy", &mu_dxy, "mu_dxy[nmu]/F");
  t->Branch("mu_dz", &mu_dz, "mu_dz[nmu]/F");
  t->Branch("mu_ID", &mu_ID, "mu_ID[nmu]/F");
  t->Branch("mu_isGood", &mu_isGood, "mu_isGood[nmu]/F");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
LeptonVariableNtuplizer::endJob() {
  //cout<<"call method endJob"<<endl;
  //f = new TFile(outputFileName_.c_str(), "recreate");
  f->cd();
  t->Write();
  //cout<<"write file sucessfull" << endl;
  f->Close();
}

// ------------ method called when starting to processes a run  ------------
/*
void 
LeptonVariableNtuplizer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
LeptonVariableNtuplizer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
LeptonVariableNtuplizer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
LeptonVariableNtuplizer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
LeptonVariableNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(LeptonVariableNtuplizer);
