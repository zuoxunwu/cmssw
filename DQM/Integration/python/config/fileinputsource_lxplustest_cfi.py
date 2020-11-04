from __future__ import print_function
from __future__ import absolute_import
from builtins import range
import FWCore.ParameterSet.Config as cms

# Parameters for runType
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
import fnmatch
from .dqmPythonTypes import *

# part of the runTheMatrix magic
from Configuration.Applications.ConfigBuilder import filesFromDASQuery

options = VarParsing.VarParsing("analysis")

options.register(
    "runkey",
    "pp_run",
    VarParsing.VarParsing.multiplicity.singleton,
    VarParsing.VarParsing.varType.string,
    "Run Keys of CMS"
)

options.register('runNumber',
                 286520,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Run number. This run number has to be present in the dataset configured with the dataset option.")

options.register('maxLumi',
                 2000,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Only lumisections up to maxLumi are processed.")

options.register('minLumi',
                 1,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "Only lumisections starting from minLumi are processed.")

options.register('lumiPattern',
                 '*0',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Only lumisections with numbers matching lumiPattern are processed.")

options.register('dataset',
                 'auto',
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.string,
                 "Dataset name like '/ExpressPhysicsPA/PARun2016D-Express-v1/FEVT', or 'auto' to guess it with a DAS query. A dataset_cfi.py that defines 'readFiles' and 'secFiles' (like a DAS Python snippet) will override this, to avoid DAS queries.")

options.register('transDelay',
                 0, #default value, int limit -3
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.int,
                 "delay in seconds for the commit of the db transaction")

options.register('noDB',
                 True, # default value
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Don't upload the BeamSpot conditions to the DB")

options.parseArguments()

#try:
#  # fixed dataset, DAS 'py' snippet
#  from dataset_cfi import readFiles, secFiles
#  print("Using filenames from dataset_cfi.py.")
#except:
#  if options.dataset == 'auto':
#    print("Querying DAS for a dataset...")
#    import subprocess
#    out = subprocess.check_output("dasgoclient --query 'dataset run=%d dataset=/*Express*/*/*FEVT*'" % options.runNumber, shell=True)
#    dataset = out.splitlines()[-1]
#    print("Using dataset=%s." % dataset)
#  else:
#    dataset = options.dataset
#
#  print("Querying DAS for files...")
#  readFiles = cms.untracked.vstring()
#  secFiles = cms.untracked.vstring()
#  # this outputs all results, which can be a lot...
#  read, sec = filesFromDASQuery("file run=%d dataset=%s" % (options.runNumber, dataset), option=" --limit 10000 ")
#  readFiles.extend(read)
#  secFiles.extend(sec)
#
#print("Got %d files." % len(readFiles))
#
#runstr = str(options.runNumber)
#runpattern = "*" + runstr[0:3] + "/" + runstr[3:] + "*"
#readFiles = cms.untracked.vstring([f for f in readFiles if fnmatch.fnmatch(f, runpattern)])
#secFiles = cms.untracked.vstring([f for f in secFiles if fnmatch.fnmatch(f, runpattern)])
#lumirange =  cms.untracked.VLuminosityBlockRange(
#  [ str(options.runNumber) + ":" + str(ls) 
#      for ls in range(options.minLumi, options.maxLumi+1)
#      if fnmatch.fnmatch(str(ls), options.lumiPattern)
#  ]
#)
#
#print("Selected %d files and %d LS." % (len(readFiles), len(lumirange)))

#source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring("/store/data/Run2018D/SingleMuon/RAW/v1/000/321/887/00000/EECFAFF8-44AB-E811-9C88-FA163EFD0C51.root"))
#source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring("/store/data/Commissioning2020/Cosmics/RAW/v1/000/337/136/00000/98B7DCED-426E-274F-BE56-F956D2E22EC1.root"))
#source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring("/store/data/Commissioning2020/Cosmics/RAW/v1/000/337/973/00000/FE3F0FD9-CFA9-2344-BBA4-316BD8260821.root"))
#source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring("/store/data/Commissioning2020/Cosmics/RAW/v1/000/337/973/00000/FD3754B9-F9F2-EC40-8300-31F9FA04B7B8.root"))

#source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring("/store/mc/Run3Winter20DRPremixMiniAOD/VectorZPrimeToQQ_M100_pT300_TuneCP5_14TeV_madgraph_pythia8/GEN-SIM-RAW/110X_mcRun3_2021_realistic_v6-v1/270000/12665FE2-5123-6046-A76A-52846431723E.root"))
source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring("/store/mc/Run3Winter20DRPremixMiniAOD/HTo2LongLivedTo4mu_MH-125_MFF-50_CTau-3000mm_TuneCP5_14TeV_pythia8/GEN-SIM-RAW/110X_mcRun3_2021_realistic_v6-v2/10000/13625078-168A-9A4F-BD90-9D105B09C04E.root"))
#source = cms.Source ("PoolSource",fileNames = cms.untracked.vstring("/store/mc/Run3Winter20DRPremixMiniAOD/Neutrino_Pt-2to20_gun/GEN-SIM-RAW/SNB_110X_mcRun3_2021_realistic_v6-v1/10000/FF7C3303-BBC7-944B-A1D0-D62BA2A581FC.root"))  #readFiles, secondaryFileNames = secFiles, lumisToProcess = lumirange)
maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000000)
)

# Fix to allow scram to compile
#if len(sys.argv) > 1:
#  options.parseArguments()

runType = RunType()
if not options.runkey.strip():
    options.runkey = "pp_run"

runType.setRunType(options.runkey.strip())
