import FWCore.ParameterSet.Config as cms

from DQMServices.Core.DQMEDAnalyzer import DQMEDAnalyzer
l1tStage2ShowerEmtf = DQMEDAnalyzer(
    "L1TStage2ShowerEMTF",
#    emtfSource = cms.InputTag("emtfStage2Digis"),
    emtfSource = cms.InputTag("simEmtfShowers", "EMTF"),  ## use emu for test
    monitorDir = cms.untracked.string("L1T/L1TStage2EMTF/Shower"), 
    verbose = cms.untracked.bool(False),
)

