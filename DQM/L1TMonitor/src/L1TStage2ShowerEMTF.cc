#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "DQM/L1TMonitor/interface/L1TStage2ShowerEMTF.h"

L1TStage2ShowerEMTF::L1TStage2ShowerEMTF(const edm::ParameterSet& ps)
    : showerToken(consumes<l1t::RegionalMuonShowerBxCollection>(ps.getParameter<edm::InputTag>("emtfSource"))),
      monitorDir(ps.getUntrackedParameter<std::string>("monitorDir", "")),
      verbose(ps.getUntrackedParameter<bool>("verbose", false)) {}

L1TStage2ShowerEMTF::~L1TStage2ShowerEMTF() {}

void L1TStage2ShowerEMTF::bookHistograms(DQMStore::IBooker& ibooker, const edm::Run&, const edm::EventSetup&) {
  ibooker.setCurrentFolder(monitorDir);
  showerOccupancy = ibooker.book2D("showerOccupancy", "shower Occupancy", 6, 1, 7, 2, 0, 2);
  showerOccupancy->setAxisTitle("Sector", 1);
  showerOccupancy->setBinLabel(1, "ME-", 2);
  showerOccupancy->setBinLabel(2, "ME+", 2);

  showerCheckNomInTime = ibooker.book2D("showerCheckNomInTime", "Nominal in time, all vs valid", 5, 0, 5, 2, 0, 2);
  showerCheckNomInTime->setAxisTitle("nShower", 1);
  showerCheckNomInTime->setAxisTitle("isOneNominalInTime", 2);  

  showerInfoBX = ibooker.book2D("showerInfoBX", "showerInfo", 19, -9, 10, 19, -9, 10);
  showerInfoBX->setAxisTitle("ShowerCollection->getFirstBX()", 1);
  showerInfoBX->setAxisTitle("ShowerCollection->getLastBX()", 2);

  showerNperEvt = ibooker.book2D("showerNperEvt", "N showers per event", 5, 0, 5, 5, 0, 5);
  showerNperEvt->setAxisTitle("N showers", 1);
  showerNperEvt->setAxisTitle("N valid showers", 2);
}

void L1TStage2ShowerEMTF::analyze(const edm::Event& e, const edm::EventSetup& c) {
  edm::Handle<l1t::RegionalMuonShowerBxCollection> ShowerCollection;
  e.getByToken(showerToken, ShowerCollection);

//  auto shower = ShowerCollection->at(0, 0);

  showerInfoBX->Fill(ShowerCollection->getFirstBX(), ShowerCollection->getLastBX());
  int Nvalid = 0;
  for (auto Shower = ShowerCollection->begin(); Shower != ShowerCollection->end(); ++Shower) {
    int endcap = Shower->endcap();
    int sector = Shower->sector();
    if (not Shower->isValid()) continue;
    Nvalid += 1;
    showerOccupancy->Fill(sector, (endcap > 0) ? 1.5 : 0.5);
    showerCheckNomInTime->Fill(Nvalid, (Shower->isOneNominalInTime())? 1.5:0.5);
  }
  showerNperEvt->Fill(ShowerCollection->size(), Nvalid);
}
