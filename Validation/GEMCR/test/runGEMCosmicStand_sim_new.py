# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: SingleMuPt100_cfi -s GEN,SIM,DIGI,L1,DIGI2RAW,RAW2DIGI,L1Reco,RECO --conditions auto:run2_mc --magField 38T_PostLS1 --datatier GEN-SIM --geometry GEMCosmicStand --eventcontent FEVTDEBUGHLT --era phase2_muon -n 100 --fileout out_reco.root
import datetime
print datetime.datetime.now()
import FWCore.ParameterSet.Config as cms

# options
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing('analysis')

#Next one line was changed by Jongseok Lee
options.register("runNum",1,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Run number")
#Next one line was changed by Jongseok Lee
options.register("eventsPerJob",10000,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "The number of events (in each file)")
#Next one line was changed by Jongseok Lee
options.register("idxJob","-1",
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "The index of this root file")

options.parseArguments()

#geomType = 'A'
geomType = 'B'
#geomType = 'C'

# Insert the type 0 , S , L of the superchambers in 15 positions: frontal view, 90 deg rotated
SuperChType = ['L','L','L','L','L',\
               'L','L','L','L','L',\
               'L','L','L','L','0']
#               'L','L','L','L','L']            

# Calculation of SuperChSeedingLayers from SuperChType
SuperChSeedingLayers = [1,3, 0,0, 0,0, 0,0, 4,2,\
                        1,3, 0,0, 0,0, 0,0, 4,2,\
                        1,3, 0,0, 0,0, 4,2, 0,0]
#                        1,3, 0,0, 0,0, 0,0, 4,2]

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.phase2_muon)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Geometry.GEMGeometry.GeometryGEMCosmicStand_cff')
process.load('Configuration.StandardSequences.MagneticField_0T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic50ns13TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('SimMuon.GEMDigitizer.muonGEMDigi_cff')
process.load('RecoLocalMuon.GEMRecHit.gemLocalReco_cff')

# DEFINITION OF THE SUPERCHAMBERS INSIDE THE STAND
####
#for i in range(1):
for i in range(len(SuperChType)):
    column_row = '_c%d_r%d' % ((i/5)+1, i%5+1)
    if SuperChType[i]=='L' : size = 'L'
    if SuperChType[i]=='S' : size = 'S'
    if SuperChType[i]!='0' : geomFile = 'Geometry/MuonCommonData/data/cosmic1/geom'+geomType+'/gem11'+size+column_row+'.xml'
    if SuperChType[i]!='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append(geomFile)

    #remo = ''
    #if SuperChType[i]=='0' : size = 'L'
    #if SuperChType[i]=='0' : remo = '_removed'
    #geomFile = 'Geometry/MuonCommonData/data/cosmic1/geom'+geomType+'/gem11'+size+column_row+remo+'.xml'
    #process.XMLIdealGeometryESSource.geomXMLFiles.append(geomFile)

# COLUMN 1
#if SuperChType[0]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r1.xml')
#if SuperChType[0]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c1_r1.xml')
#if SuperChType[0]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r1_removed.xml')

#if SuperChType[1]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r2.xml')
#if SuperChType[1]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c1_r2.xml')
#if SuperChType[1]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r2_removed.xml')

#if SuperChType[2]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r3.xml')
#if SuperChType[2]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c1_r3.xml')
#if SuperChType[2]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r3_removed.xml')

#if SuperChType[3]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r4.xml')
#if SuperChType[3]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c1_r4.xml')
#if SuperChType[3]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r4_removed.xml')

#if SuperChType[4]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r5.xml')
#if SuperChType[4]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c1_r5.xml')
#if SuperChType[4]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c1_r5_removed.xml')

# COLUMN 2
#if SuperChType[5]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r1.xml')
#if SuperChType[5]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c2_r1.xml')
#if SuperChType[5]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r1_removed.xml')

#if SuperChType[6]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r2.xml')
#if SuperChType[6]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c2_r2.xml')
#if SuperChType[6]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r2_removed.xml')

#if SuperChType[7]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r3.xml')
#if SuperChType[7]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c2_r3.xml')
#if SuperChType[7]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r3_removed.xml')

#if SuperChType[8]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r4.xml')
#if SuperChType[8]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c2_r4.xml')
#if SuperChType[8]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r4_removed.xml')

#if SuperChType[9]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r5.xml')
#if SuperChType[9]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c2_r5.xml')
#if SuperChType[9]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c2_r5_removed.xml')

# COLUMN 3
#if SuperChType[10]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r1.xml')
#if SuperChType[10]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c3_r1.xml')
#if SuperChType[10]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r1_removed.xml')

#if SuperChType[11]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r2.xml')
#if SuperChType[11]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c3_r2.xml')
#if SuperChType[11]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r2_removed.xml')

#if SuperChType[12]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r3.xml')
#if SuperChType[12]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c3_r3.xml')
#if SuperChType[12]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r3_removed.xml')

#if SuperChType[13]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r4.xml')
#if SuperChType[13]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c3_r4.xml')
#if SuperChType[13]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r4_removed.xml')

#if SuperChType[14]=='L' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r5.xml')
#if SuperChType[14]=='S' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11S_c3_r5.xml')
#if SuperChType[14]=='0' : process.XMLIdealGeometryESSource.geomXMLFiles.append('Geometry/MuonCommonData/data/cosmic1/gem11L_c3_r5_removed.xml')
	
# Config importation & settings
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.eventsPerJob))
import configureRun_cfi as runConfig
nIdxJob = int(options.idxJob)
strOutput = "out_reco_MC.root" if nIdxJob >= 0 else runConfig.OutputFileName
if nIdxJob < 0: nIdxJob = 0

# Input source
process.source = cms.Source("EmptySource", 
    firstRun = cms.untracked.uint32(options.runNum), 
    firstEvent = cms.untracked.uint32(options.eventsPerJob * nIdxJob + 1), 
    firstLuminosityBlock = cms.untracked.uint32(nIdxJob + 1), 
)
process.options = cms.untracked.PSet()

process.MessageLogger.cerr.FwkReport.reportEvery = 1000
#process.MessageLogger.cerr.threshold = 'ERROR'

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('CosmicMuonGenerator nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition
process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(10485760),
    fileName = cms.untracked.string('file:'+strOutput),
    #outputCommands = cms.untracked.vstring( ('keep *')),
    outputCommands = cms.untracked.vstring( ('drop *')),
    #outputCommands = cms.untracked.vstring( (
    # 'drop *'
    # 'keep *_*_MuonGEMHits_RECO',
    # 'keep *_*_unsmeared_RECO',
    # 'keep *_gemRecHits_*_RECO',
    # 'keep *_GEMCosmicMuonForQC8_*_RECO',
    # 'keep *_genParticles_*_RECO',
    # 'keep *_*GEMDigis_*_RECO'
    #)),

    splitLevel = cms.untracked.int32(0)
)

# Additional output definition
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

# Cosmic Muon generator
process.generator = cms.EDProducer("FlatRandomPtGunProducer",
    AddAntiParticle = cms.bool(True),
    PGunParameters = cms.PSet(
        MinPt = cms.double(99.99),
        MaxPt = cms.double(100.01),
        MinPhi = cms.double(3.141592),
        MaxPhi = cms.double(-3.141592),
        #MinTheta = cms.double(0.0),
        #MaxTheta = cms.double(1.5707963),
        MinTheta = cms.double(1.570796),
        MaxTheta = cms.double(3.141592),
        #MinPhi = cms.double(-2.5),
        #MaxPhi = cms.double(-0.5)
        #MinTheta = cms.double(0.7),
        #MaxTheta = cms.double(2.4),
        #IsThetaFlat = cms.bool(False), # If 'True': theta distribution is flat. If 'False': theta distribution is a cos^2

        #For only vertical muons (-y direction)
        #MinPhi = cms.double(-1.5707961),
        #MaxPhi = cms.double(-1.5707959),
        #MinTheta = cms.double(1.5707959),
        #MaxTheta = cms.double(1.5707961),
        IsThetaFlat = cms.bool(True),
        PartID = cms.vint32(-13)
    ),
    Verbosity = cms.untracked.int32(0),
    firstRun = cms.untracked.uint32(1),
    psethack = cms.string('single mu pt 100')
)

process.mix = cms.EDProducer("MixingModule",
    LabelPlayback = cms.string(''),
    bunchspace = cms.int32(450),
    maxBunch = cms.int32(3),
    minBunch = cms.int32(-5),
    mixProdStep1 = cms.bool(False),
    mixProdStep2 = cms.bool(False),
    playback = cms.untracked.bool(False),
    useCurrentProcessOnly = cms.bool(False),
    digitizers = cms.PSet(),
    
    mixObjects = cms.PSet(
        mixSH = cms.PSet(
            crossingFrames = cms.untracked.vstring('MuonGEMHits'),
            input = cms.VInputTag(cms.InputTag("g4SimHits","MuonGEMHits")),
            type = cms.string('PSimHit'),
            subdets = cms.vstring('MuonGEMHits'),
            
            )
        ),
    mixTracks = cms.PSet(
        input = cms.VInputTag(cms.InputTag("g4SimHits")),
        makeCrossingFrame = cms.untracked.bool(True),
        type = cms.string('SimTrack')
    ),
)
process.g4SimHits.UseMagneticField = cms.bool(False)
process.simCastorDigis = cms.EDAlias()
process.simEcalUnsuppressedDigis = cms.EDAlias()
process.simHcalUnsuppressedDigis = cms.EDAlias()
process.simSiPixelDigis = cms.EDAlias()
process.simSiStripDigis = cms.EDAlias()

process.load('RecoMuon.TrackingTools.MuonServiceProxy_cff')
process.MuonServiceProxy.ServiceParameters.Propagators.append('StraightLinePropagator')

process.GEMCosmicMuonForQC8 = cms.EDProducer("GEMCosmicMuonForQC8",
                                       process.MuonServiceProxy,
                                       gemRecHitLabel = cms.InputTag("gemRecHits"),
                                       maxClusterSize = cms.double(runConfig.maxClusterSize),
                                       minClusterSize = cms.double(runConfig.minClusterSize),
                                       trackChi2 = cms.double(runConfig.trackChi2),
                                       trackResX = cms.double(runConfig.trackResX),
                                       trackResY = cms.double(runConfig.trackResY),
                                       MulSigmaOnWindow = cms.double(runConfig.MulSigmaOnWindow),
                                       SuperChamberType = cms.vstring(SuperChType),
                                       SuperChamberSeedingLayers = cms.vdouble(SuperChSeedingLayers),
                                       MuonSmootherParameters = cms.PSet(
                                           PropagatorAlong = cms.string('SteppingHelixPropagatorAny'),
                                           PropagatorOpposite = cms.string('SteppingHelixPropagatorAny'),
                                           RescalingFactor = cms.double(5.0)
                                           ),
                                       )
process.GEMCosmicMuonForQC8.ServiceParameters.GEMLayers = cms.untracked.bool(True)
process.GEMCosmicMuonForQC8.ServiceParameters.CSCLayers = cms.untracked.bool(False)
process.GEMCosmicMuonForQC8.ServiceParameters.RPCLayers = cms.bool(False)

fScale = 1.0

process.gemcrValidation = cms.EDAnalyzer('gemcrValidation',
    process.MuonServiceProxy,
    verboseSimHit = cms.untracked.int32(1),
    simInputLabel = cms.InputTag('g4SimHits',"MuonGEMHits"),
    # PSimHits_g4SimHits_MuonGEMHits_RECO
    genVtx = cms.InputTag("generator","unsmeared", "RECO"),
    # edmHepMCProduct_generator_unsmeared_RECO
    recHitsInputLabel = cms.InputTag('gemRecHits'),
    # GEMDetIdGEMRecHitsOwnedRangeMap_gemRecHits__RECO
    tracksInputLabel = cms.InputTag('GEMCosmicMuonForQC8','','RECO'),
    seedInputLabel = cms.InputTag('GEMCosmicMuonForQC8','','RECO'),
    trajInputLabel = cms.InputTag('GEMCosmicMuonForQC8','','RECO'),
    chNoInputLabel = cms.InputTag('GEMCosmicMuonForQC8','','RECO'),
    seedTypeInputLabel = cms.InputTag('GEMCosmicMuonForQC8','','RECO'),
    # *_GEMCosmicMuonForQC8_*_RECO
    genParticleLabel = cms.InputTag('genParticles','','RECO'),
    # *_genParticles_*_RECO
    gemDigiLabel = cms.InputTag("muonGEMDigis","","RECO"),
    # *_*GEMDigis_*_RECO
    # st1, st2_short, st2_long of xbin, st1,st2_short,st2_long of ybin
    nBinGlobalZR = cms.untracked.vdouble(200,200,200,150,180,250),
    # st1 xmin, xmax, st2_short xmin, xmax, st2_long xmin, xmax, st1 ymin, ymax...
    RangeGlobalZR = cms.untracked.vdouble(564,572,786,794,786,802,110,260,170,350,100,350),
    maxClusterSize = cms.double(runConfig.maxClusterSize),
    minClusterSize = cms.double(runConfig.minClusterSize),
    maxResidual = cms.double(runConfig.maxResidual),
    makeTrack = cms.bool(runConfig.makeTrack),
    isMC = cms.bool(True),
    trackChi2 = cms.double(runConfig.trackChi2),
    trackResX = cms.double(runConfig.trackResX),
    trackResY = cms.double(runConfig.trackResY),
    MulSigmaOnWindow = cms.double(runConfig.MulSigmaOnWindow),
    SuperChamberType = cms.vstring(SuperChType),
    SuperChamberSeedingLayers = cms.vdouble(SuperChSeedingLayers),
    MuonSmootherParameters = cms.PSet(
                      PropagatorAlong = cms.string('SteppingHelixPropagatorAny'),
                      PropagatorOpposite = cms.string('SteppingHelixPropagatorAny'),
                      RescalingFactor = cms.double(5.0)
                      ),
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('temp_'+strOutput)
)

# Path and EndPath definitions
process.generation_step = cms.Path(process.generator+process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.reconstruction_step    = cms.Path(process.gemLocalReco+process.GEMCosmicMuonForQC8)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)
process.validation_step = cms.Path(process.gemcrValidation)
process.digitisation_step.remove(process.simMuonME0Digis)
process.digitisation_step.remove(process.simMuonME0ReDigis)
process.digitisation_step.remove(process.simEcalTriggerPrimitiveDigis)
process.digitisation_step.remove(process.simEcalDigis)
process.digitisation_step.remove(process.simEcalPreshowerDigis)
process.digitisation_step.remove(process.simHcalTriggerPrimitiveDigis)
process.digitisation_step.remove(process.simHcalDigis)
process.digitisation_step.remove(process.simHcalTTPDigis)
process.digitisation_step.remove(process.simMuonCSCDigis)
process.digitisation_step.remove(process.simMuonRPCDigis)
process.digitisation_step.remove(process.addPileupInfo)
process.digitisation_step.remove(process.simMuonDTDigis)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,
                                process.digitisation_step,
                                process.reconstruction_step,
                                process.validation_step,
                                process.endjob_step,
                                process.FEVTDEBUGHLToutput_step,
                                )
# filter all path with the production filter sequence
#for path in process.paths:
#	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

process.RandomNumberGeneratorService.generator = cms.PSet(
    #initialSeed = cms.untracked.uint32( ( nIdxJob + 1 ) + options.runNum*10000),
    #initialSeed = cms.untracked.uint32( ( nIdxJob + 1 ) ),
    initialSeed = cms.untracked.uint32( ( nIdxJob + 1 + 1350000) ),
    engineName = cms.untracked.string('HepJamesRandom')
)
process.RandomNumberGeneratorService.simMuonGEMDigis = process.RandomNumberGeneratorService.generator
process.RandomNumberGeneratorService.VtxSmeared = process.RandomNumberGeneratorService.generator
process.RandomNumberGeneratorService.g4SimHits = process.RandomNumberGeneratorService.generator

process.gemSegments.maxRecHitsInCluster = cms.int32(10)
process.gemSegments.minHitsPerSegment = cms.uint32(3)
process.gemSegments.clusterOnlySameBXRecHits = cms.bool(True)
process.gemSegments.dEtaChainBoxMax = cms.double(1.05)
process.gemSegments.dPhiChainBoxMax = cms.double(1.12)
process.gemSegments.dXclusBoxMax = cms.double(10.0)
process.gemSegments.dYclusBoxMax = cms.double(50.0)
process.gemSegments.preClustering = cms.bool(False)
process.gemSegments.preClusteringUseChaining = cms.bool(False)

process.simMuonGEMDigis.averageEfficiency = cms.double(0.98)
process.simMuonGEMDigis.averageNoiseRate = cms.double(0.0)
process.simMuonGEMDigis.doBkgNoise = cms.bool(False)
process.simMuonGEMDigis.doNoiseCLS = cms.bool(False)
process.simMuonGEMDigis.simulateElectronBkg = cms.bool(False)
