
LEPTON_SETUP = 2015
PD = ""
MCFILTER = ""
ELECORRTYPE   = "None" # "None", "Moriond", or "Paper"
ELEREGRESSION = "None" # "None", "Moriond", "PaperNoComb", or "Paper" 
APPLYMUCORR = False


# Get absolute path
import os
PyFilePath = os.environ['CMSSW_BASE'] + "/src/ZZAnalysis/AnalysisStep/test/"
execfile(PyFilePath + "analyzer.py")


# Replace parameters
process.source.fileNames = cms.untracked.vstring(

    'root://cms-xrd-global.cern.ch//store/data/Run2015B/DoubleEG/MINIAOD/17Jul2015-v1/40000/02FC1E69-AF2E-E511-ABA6-0025905B858E.root', # PHYS14 sample

)

process.maxEvents.input = -1

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("CommonTools.PileupAlgos.Puppi_cff")
process.load("EgammaWork.ElectronNtupler.pfNoLeptons_cfi")

process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange( *(
    '251244:85-251244:86',
    '251244:88-251244:93',
    '251244:96-251244:121',
    '251244:123-251244:156',
    '251244:158-251244:428',
    '251244:430-251244:442',
    '251251:1-251251:31',
    '251251:33-251251:97',
    '251251:99-251251:167',
    '251252:1-251252:283',
    '251252:285-251252:505',
    '251252:507-251252:554',
    '251561:1-251561:94',
    '251562:1-251562:439',
    '251562:443-251562:691',
    '251643:1-251643:216',
    '251643:222-251643:606',
    '251721:21-251721:36',
    '251721:123-251721:244',
    '251883:56-251883:56',
    '251883:58-251883:60',
    '251883:62-251883:144',
    '251883:156-251883:437',
))

process.puppi.candName = cms.InputTag('packedPFCandidates')
process.puppi.vertexName = cms.InputTag('offlineSlimmedPrimaryVertices')

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.options.allowUnscheduled = cms.untracked.bool(False) 

process.puppiNoLeptons = process.puppi.clone()
process.puppiNoLeptons.candName = cms.InputTag('pfNoLeptons')

process.ElectronIsolation = cms.EDProducer("CITKPFIsolationSumProducer",
					    srcToIsolate = cms.InputTag("slimmedElectrons"),
					    srcForIsolationCone = cms.InputTag('packedPFCandidates'),
					    isolationConeDefinitions = cms.VPSet(
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.015),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('h+'),
									miniAODVertexCodes = cms.vuint32(2,3) ),
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.0),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('h0'),
									miniAODVertexCodes = cms.vuint32(2,3) ),
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.08),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('gamma'),
									miniAODVertexCodes = cms.vuint32(2,3) )
								      )
					)
									
process.ElectronIsolationOnPUPPI = cms.EDProducer("CITKPFIsolationSumProducer",
					    srcToIsolate = cms.InputTag("slimmedElectrons"),
					    srcForIsolationCone = cms.InputTag('puppi'),
					    isolationConeDefinitions = cms.VPSet(
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.015),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('h+'),
									miniAODVertexCodes = cms.vuint32(2,3) ),
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.0),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('h0'),
									miniAODVertexCodes = cms.vuint32(2,3) ),
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.08),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('gamma'),
									miniAODVertexCodes = cms.vuint32(2,3) )
								      )
					)

process.ElectronIsolationOnPUPPINoLeptons = cms.EDProducer("CITKPFIsolationSumProducer",
					    srcToIsolate = cms.InputTag("slimmedElectrons"),
					    srcForIsolationCone = cms.InputTag('puppiNoLeptons'),
					    isolationConeDefinitions = cms.VPSet(
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.015),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('h+'),
									miniAODVertexCodes = cms.vuint32(2,3) ),
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.0),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('h0'),
									miniAODVertexCodes = cms.vuint32(2,3) ),
									cms.PSet( isolationAlgo = cms.string('ElectronPFIsolationWithConeVeto'), 
									coneSize = cms.double(0.4),
									VetoConeSizeEndcaps = cms.double(0.08),
									VetoConeSizeBarrel = cms.double(0.0),
									isolateAgainst = cms.string('gamma'),
									miniAODVertexCodes = cms.vuint32(2,3) )
								      )
					)

process.storeVars = cms.EDAnalyzer('LeptonVariableNtuplizerData',
     OutputFileName = cms.string(
        "output_lepVars.root",
     ),
     electronSrc = cms.InputTag("softElectrons"),
)

# remove preselection
#process.bareSoftMuons.cut = cms.string("")
#process.softMuons.cut = cms.string("")
#process.bareSoftElectrons.cut = cms.string("")
#process.softElectrons.cut = cms.string("")

# replace the paths 
process.triggerTriEle = cms.Path() # doesn't affect the selection per se
process.triggerDiMu = cms.Path() # doesn't affect the selection per se
process.triggerDiEle = cms.Path() # doesn't affect the selection per se
process.triggerMuEle = cms.Path() # doesn't affect the selection per se
###process.PVfilter = cms.Path() # we actually need this one
process.Candidates = cms.Path( 
    process.pfNoLeptons +  process.puppi + process.puppiNoLeptons + process.ElectronIsolation + process.ElectronIsolationOnPUPPI + process.ElectronIsolationOnPUPPINoLeptons + process.electrons)
process.p = cms.EndPath(process.storeVars)
process.trees = cms.EndPath() # doesn't affect the selection per se
