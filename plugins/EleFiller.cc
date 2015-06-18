/** \class EleFiller
 *
 *  No description available.
 *
 *  $Date: 2013/05/24 15:42:42 $
 *  $Revision: 1.28 $
 *  \author N. Amapane (Torino)
 *  \author S. Bolognesi (JHU)
 *  \author C. Botta (CERN)
 *  \author S. Casasso (Torino)
 */

#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/EDProducer.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/ParameterSet/interface/ParameterSet.h>
#include <FWCore/Framework/interface/ESHandle.h>

#include <ZZAnalysis/AnalysisStep/interface/CutSet.h>
#include <ZZAnalysis/AnalysisStep/interface/LeptonIsoHelper.h>

//#include "EgammaAnalysis/ElectronTools/interface/EGammaMvaEleEstimatorCSA14.h"

#include <vector>
#include <string>

using namespace edm;
using namespace std;
using namespace reco;


bool recomputeBDT = true;

class EleFiller : public edm::EDProducer {
 public:
  /// Constructor
  explicit EleFiller(const edm::ParameterSet&);
    
  /// Destructor
  ~EleFiller(){
    //delete myMVATrig;
  };  

 private:
  virtual void beginJob(){};  
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob(){};

  const edm::InputTag theCandidateTag;
  int sampleType;
  int setup;
  const StringCutObjectSelector<pat::Electron, true> cut;
  const CutSet<pat::Electron> flags;
  //EGammaMvaEleEstimatorCSA14* myMVATrig;
};


EleFiller::EleFiller(const edm::ParameterSet& iConfig) :
  theCandidateTag(iConfig.getParameter<InputTag>("src")),
  sampleType(iConfig.getParameter<int>("sampleType")),
  setup(iConfig.getParameter<int>("setup")),
  cut(iConfig.getParameter<std::string>("cut")),
  flags(iConfig.getParameter<ParameterSet>("flags"))
  //,myMVATrig(0)
{
  produces<pat::ElectronCollection>();

  if (recomputeBDT) {
    std::vector<std::string> myManualCatWeigths;

    myManualCatWeigths.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB1_5_oldscenario2phys14_BDT.weights.xml");
    myManualCatWeigths.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB2_5_oldscenario2phys14_BDT.weights.xml");
    myManualCatWeigths.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EE_5_oldscenario2phys14_BDT.weights.xml");
    myManualCatWeigths.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB1_10_oldscenario2phys14_BDT.weights.xml");
    myManualCatWeigths.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EB2_10_oldscenario2phys14_BDT.weights.xml");
    myManualCatWeigths.push_back("EgammaAnalysis/ElectronTools/data/PHYS14/EIDmva_EE_10_oldscenario2phys14_BDT.weights.xml");

    vector<string> myManualCatWeigthsTrig;
    string the_path;
    for (unsigned i = 0 ; i < myManualCatWeigths.size() ; i++){
      the_path = edm::FileInPath ( myManualCatWeigths[i] ).fullPath();
      myManualCatWeigthsTrig.push_back(the_path);
    }
    //myMVATrig = new EGammaMvaEleEstimatorCSA14();
    //myMVATrig->initialize("BDT",
    //			  EGammaMvaEleEstimatorCSA14::kNonTrigPhys14,
    //			  true,
    //			  myManualCatWeigthsTrig);
  }

}


void
EleFiller::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{  

  // Get leptons and rho
  edm::Handle<pat::ElectronRefVector> electronHandle;
  iEvent.getByLabel(theCandidateTag, electronHandle);

  InputTag theRhoTag = LeptonIsoHelper::getEleRhoTag(sampleType,setup);
  edm::Handle<double> rhoHandle;
  iEvent.getByLabel(theRhoTag, rhoHandle);
  double rho = *rhoHandle;

  edm::Handle<vector<Vertex> >  vertexs;
  iEvent.getByLabel("goodPrimaryVertices",vertexs);

  // Output collection
  auto_ptr<pat::ElectronCollection> result( new pat::ElectronCollection() );

  for (unsigned int i = 0; i< electronHandle->size(); ++i){

    //---Clone the pat::Electron
    pat::Electron l(*((*electronHandle)[i].get()));

    float pt = l.pt();

    //--- PF ISO
    float PFChargedHadIso   = l.chargedHadronIso();
    float PFNeutralHadIso   = l.neutralHadronIso();
    float PFPhotonIso       = l.photonIso();
    float PFChargedFromPU   = l.puChargedHadronIso();
    float PFChargedHadIsoRel= l.chargedHadronIso()/pt;
    float PFNeutralHadIsoRel= l.neutralHadronIso()/pt;
    float PFPhotonIsoRel    = l.photonIso()/pt;
    float PFChargedFromPURel= l.puChargedHadronIso()/pt;

    //float fSCeta = fabs(l.eta()); 
    float fSCeta = fabs(l.superCluster()->eta());

    float Iso_simple = LeptonIsoHelper::combRelIsoPF(sampleType, setup, rho, l, 0.0, 0);
    float Iso_effarea = LeptonIsoHelper::combRelIsoPF(sampleType, setup, rho, l, 0.0, 1);
    float Iso_deltabeta = LeptonIsoHelper::combRelIsoPF(sampleType, setup, rho, l, 0.0, 2);
    float effective_area = LeptonIsoHelper::effective_area(sampleType, setup, l);

    //--- SIP, dxy, dz
    float IP      = fabs(l.dB(pat::Electron::PV3D));
    float IPError = l.edB(pat::Electron::PV3D);
    float SIP     = IP/IPError;

    float dxy = 999.;
    float dz  = 999.;
    const Vertex* vertex = 0;
    if (vertexs->size()>0) {
      vertex = &(vertexs->front());
      dxy = fabs(l.gsfTrack()->dxy(vertex->position()));
      dz  = fabs(l.gsfTrack()->dz(vertex->position()));
    } 

    
    // new RunII BDT ID (for the moment, it is added on top of the miniAOD)
    float BDT = 0;
    if (recomputeBDT) {
      //BDT = myMVATrig->mvaValue(l,false);
      BDT = 0;
    } else {
      //BDT = l. ... ;
    }
    
//     //Legacy cuts
//     bool isBDT = (pt <= 10 && (( fSCeta < 0.8 && BDT > 0.47)  ||
// 			       (fSCeta >= 0.8 && fSCeta < 1.479 && BDT > 0.004) ||
// 			       (fSCeta >= 1.479               && BDT > 0.295))) ||
//                  //Moriond13 eID cuts updated for the paper
// 		 //(pt >  10 && ((fSCeta < 0.8 && BDT > 0.5)  ||
// 		 //	       (fSCeta >= 0.8 && fSCeta < 1.479 && BDT > 0.12) ||
//                  (pt >  10 && ((fSCeta < 0.8 && BDT > -0.34)  ||
// 			       (fSCeta >= 0.8 && fSCeta < 1.479 && BDT > -0.65) ||
// 			       (fSCeta >= 1.479               && BDT > 0.6)));

    //tentative cuts for first 2015 sync
    bool isBDT = (pt <= 10 && ((fSCeta < 0.8                    && BDT > -0.202) ||
			       (fSCeta >= 0.8 && fSCeta < 1.479 && BDT > -0.444) ||
			       (fSCeta >= 1.479                 && BDT >  0.264)   )) ||
                 (pt >  10 && ((fSCeta < 0.8                    && BDT > -0.110) ||
		               (fSCeta >= 0.8 && fSCeta < 1.479 && BDT > -0.284) ||
		               (fSCeta >= 1.479                 && BDT > -0.212)   ));

   isBDT = true;

    //-- Missing hit  
    int missingHit = l.gsfTrack()->hitPattern().numberOfHits(HitPattern::MISSING_INNER_HITS);
    //--- Trigger matching
    int HLTMatch = 0; //FIXME
    
    //--- Embed user variables
    l.addUserFloat("effective_area",effective_area);
    l.addUserFloat("PFChargedHadIso",PFChargedHadIso);
    l.addUserFloat("PFNeutralHadIso",PFNeutralHadIso);
    l.addUserFloat("PFPhotonIso",PFPhotonIso);
    l.addUserFloat("PFChargedFromPU",PFChargedFromPU);
    l.addUserFloat("PFChargedHadIsoRel",PFChargedHadIsoRel);
    l.addUserFloat("PFNeutralHadIsoRel",PFNeutralHadIsoRel);
    l.addUserFloat("PFPhotonIsoRel",PFPhotonIsoRel);
    l.addUserFloat("PFChargedFromPURel",PFChargedFromPURel);
    l.addUserFloat("PFIso_simple",Iso_simple);
    l.addUserFloat("PFIso_effarea",Iso_effarea);
    l.addUserFloat("PFIso_deltabeta",Iso_deltabeta);
    l.addUserFloat("rho",rho);
    l.addUserFloat("SIP",SIP);
    l.addUserFloat("dxy",dxy);
    l.addUserFloat("dz",dz);
    l.addUserFloat("BDT",BDT);    
    l.addUserFloat("isBDT",isBDT);
    l.addUserFloat("HLTMatch", HLTMatch);
    l.addUserFloat("missingHit", missingHit);

    //--- MC parent code 
//     MCHistoryTools mch(iEvent);
//     if (mch.isMC()) {
//       int MCParentCode = 0;
//       //      int MCParentCode = mch.getParentCode(&l); //FIXME: does not work on cmg
//       l.addUserFloat("MCParentCode",MCParentCode);
//     }

    //--- Check selection cut. Being done here, flags are not available; but this way we 
    //    avoid wasting time on rejected leptons.
    if (!cut(l)) continue;

    //--- Embed flags (ie flags specified in the "flags" pset)
    for(CutSet<pat::Electron>::const_iterator flag = flags.begin(); flag != flags.end(); ++flag) {
      l.addUserFloat(flag->first,int((*(flag->second))(l)));
    }

    result->push_back(l);
  }
  iEvent.put(result);
}


#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(EleFiller);

