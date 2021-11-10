#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "DQM/L1TMonitor/interface/L1TStage2ShowerEMTF.h"

L1TStage2ShowerEMTF::L1TStage2ShowerEMTF(const edm::ParameterSet& ps)
    : EMTFShowerToken(consumes<l1t::RegionalMuonShowerBxCollection>(ps.getParameter<edm::InputTag>("emtfSource"))),
      CSCShowerToken(consumes<CSCShowerDigiCollection>(ps.getParameter<edm::InputTag>("cscSource"))),
      monitorDir(ps.getUntrackedParameter<std::string>("monitorDir", "")),
      verbose(ps.getUntrackedParameter<bool>("verbose", false)) {}

L1TStage2ShowerEMTF::~L1TStage2ShowerEMTF() {}

void L1TStage2ShowerEMTF::bookHistograms(DQMStore::IBooker& ibooker, const edm::Run&, const edm::EventSetup&) {
  ibooker.setCurrentFolder(monitorDir);

  const std::array<std::string, 9> suffix_label{
      {"4/2", "4/1", "3/2", "3/1", " 2/2", "2/1", "1/3", "1/2", "1/1"}};

  // CSC local shower
  cscShowerOccupancyLoose = ibooker.book2D("cscShowerOccupancyLoose", "CSC Loose Shower Occupancy", 36, 1, 37, 18, 0, 18);
  cscShowerOccupancyLoose->setAxisTitle("Chamber", 1);
  for (int ybin = 1; ybin <= 9; ++ybin) {
    cscShowerOccupancyLoose->setBinLabel(ybin, "ME-" + suffix_label[ybin - 1], 2);
    cscShowerOccupancyLoose->setBinLabel(19 - ybin, "ME+" + suffix_label[ybin - 1], 2);
  }

  cscShowerOccupancyNom = ibooker.book2D("cscShowerOccupancyNom", "CSC Nominal Shower Occupancy", 36, 1, 37, 18, 0, 18);
  cscShowerOccupancyNom->setAxisTitle("Chamber", 1);
  for (int ybin = 1; ybin <= 9; ++ybin) {
    cscShowerOccupancyNom->setBinLabel(ybin, "ME-" + suffix_label[ybin - 1], 2);
    cscShowerOccupancyNom->setBinLabel(19 - ybin, "ME+" + suffix_label[ybin - 1], 2);
  }

  cscShowerOccupancyTight = ibooker.book2D("cscShowerOccupancyTight", "CSC Tight Shower Occupancy", 36, 1, 37, 18, 0, 18);
  cscShowerOccupancyTight->setAxisTitle("Chamber", 1);
  for (int ybin = 1; ybin <= 9; ++ybin) {
    cscShowerOccupancyTight->setBinLabel(ybin, "ME-" + suffix_label[ybin - 1], 2);
    cscShowerOccupancyTight->setBinLabel(19 - ybin, "ME+" + suffix_label[ybin - 1], 2);
  }

  cscShowerStationRing = ibooker.book2D("cscShowerStationRing", "CSC shower types in stations and rings", 4, 0, 4, 18, 0, 18);
  cscShowerStationRing->setAxisTitle("Type", 1);
  cscShowerStationRing->setBinLabel(1, "Total", 1);
  cscShowerStationRing->setBinLabel(2, "Loose", 1);
  cscShowerStationRing->setBinLabel(3, "Nominal", 1);
  cscShowerStationRing->setBinLabel(4, "Tight", 1);
  for (int ybin = 1; ybin <= 9; ++ybin) {
    cscShowerStationRing->setBinLabel(ybin, "ME-" + suffix_label[ybin - 1], 2);
    cscShowerStationRing->setBinLabel(19 - ybin, "ME+" + suffix_label[ybin - 1], 2);
  }

  cscShowerChamber = ibooker.book2D("cscShowerChamber", "CSC shower types in chambers", 36, 1, 37, 4, 0, 4);
  cscShowerChamber->setAxisTitle("Chamber", 1);
  cscShowerChamber->setAxisTitle("Type", 2);
  cscShowerChamber->setBinLabel(1, "Total", 2);
  cscShowerChamber->setBinLabel(2, "Loose", 2);
  cscShowerChamber->setBinLabel(3, "Nominal", 2);
  cscShowerChamber->setBinLabel(4, "Tight", 2);
 
  // EMTF regional shower
  emtfShowerOccupancy = ibooker.book2D("emtfShowerOccupancy", "EMTFshower Occupancy", 6, 1, 7, 2, 0, 2);
  emtfShowerOccupancy->setAxisTitle("Sector", 1);
  emtfShowerOccupancy->setBinLabel(1, "ME-", 2);
  emtfShowerOccupancy->setBinLabel(2, "ME+", 2);

  emtfShowerTypeOccupancy = ibooker.book2D("emtfShowerTypeOccupancy", "EMTF shower Type Occupancy", 6, 1, 7, 8, 0, 8);
  emtfShowerTypeOccupancy->setAxisTitle("Sector", 1);
  emtfShowerTypeOccupancy->setBinLabel(8, "ME+ Tight",  2);
  emtfShowerTypeOccupancy->setBinLabel(7, "ME+ 2Loose", 2);
  emtfShowerTypeOccupancy->setBinLabel(6, "ME+ Nom",    2);
  emtfShowerTypeOccupancy->setBinLabel(5, "ME+ Tot",    2);
  emtfShowerTypeOccupancy->setBinLabel(4, "ME- Tot",    2);
  emtfShowerTypeOccupancy->setBinLabel(3, "ME- Nom",    2);
  emtfShowerTypeOccupancy->setBinLabel(2, "ME- 2Loose", 2);
  emtfShowerTypeOccupancy->setBinLabel(1, "ME- Tight",  2);

  showerCheckNomInTime = ibooker.book2D("showerCheckNomInTime", "Nominal in time, all vs valid", 5, 0, 5, 4, 0, 4);
  showerCheckNomInTime->setAxisTitle("nShower", 1);
  showerCheckNomInTime->setAxisTitle("isNominalInTime", 2);  
  showerCheckNomInTime->setBinLabel(1, "NeitherInTime",     2);
  showerCheckNomInTime->setBinLabel(2, "OneNomNotTwoLoose", 2);
  showerCheckNomInTime->setBinLabel(3, "TwoLooseNotOneNom", 2);
  showerCheckNomInTime->setBinLabel(4, "BothInTime",        2);

  showerInfoBX = ibooker.book2D("showerInfoBX", "showerInfo", 19, -9, 10, 19, -9, 10);
  showerInfoBX->setAxisTitle("ShowerCollection->getFirstBX()", 1);
  showerInfoBX->setAxisTitle("ShowerCollection->getLastBX()", 2);

  showerNperEvt = ibooker.book2D("showerNperEvt", "N showers per event", 5, 0, 5, 5, 0, 5);
  showerNperEvt->setAxisTitle("N showers", 1);
  showerNperEvt->setAxisTitle("N valid showers", 2);
}

void L1TStage2ShowerEMTF::analyze(const edm::Event& e, const edm::EventSetup& c) {
  edm::Handle<l1t::RegionalMuonShowerBxCollection> EmtfShowers;
  e.getByToken(EMTFShowerToken, EmtfShowers);

  edm::Handle<CSCShowerDigiCollection> CscShowers;
  e.getByToken(CSCShowerToken, CscShowers);

  const std::map<std::pair<int, int>, int> histIndexCSC = {{{1, 1}, 8},
                                                           {{1, 2}, 7},
                                                           {{1, 3}, 6},
                                                           {{2, 1}, 5},
                                                           {{2, 2}, 4},
                                                           {{3, 1}, 3},
                                                           {{3, 2}, 2},
                                                           {{4, 1}, 1},
                                                           {{4, 2}, 0}};

  for (auto element = CscShowers->begin(); element != CscShowers->end(); ++element) {
    auto detId = (*element).first;
    int endcap  = (detId.endcap() == 1 ? 1 : -1);
    int station = detId.station();
    int ring    = detId.ring();
    int chamber = detId.chamber();
    int sr = histIndexCSC.at({station, ring});
    if (endcap == -1) sr = 17 - sr;
    float evt_wgt = (station > 1 && ring == 1) ? 0.5 : 1.0;

    auto cscShower    = (*element).second.first;
    auto cscShowerEnd = (*element).second.second;
    for (; cscShower != cscShowerEnd; ++cscShower) {
//      auto cscShower = *cscIter;
      if (station > 1 && (ring % 2) == 1) {
        if (cscShower->isLooseInTime()) cscShowerOccupancyLoose->Fill(chamber * 2,     sr, evt_wgt);
        if (cscShower->isNominalInTime()) cscShowerOccupancyNom->Fill(chamber * 2,     sr, evt_wgt);
        if (cscShower->isTightInTime()) cscShowerOccupancyTight->Fill(chamber * 2,     sr, evt_wgt);
        if (cscShower->isLooseInTime()) cscShowerOccupancyLoose->Fill(chamber * 2 - 1, sr, evt_wgt);
        if (cscShower->isNominalInTime()) cscShowerOccupancyNom->Fill(chamber * 2 - 1, sr, evt_wgt);
        if (cscShower->isTightInTime()) cscShowerOccupancyTight->Fill(chamber * 2 - 1, sr, evt_wgt);
      }
      else {
        if (cscShower->isLooseInTime()) cscShowerOccupancyLoose->Fill(chamber, sr);
        if (cscShower->isNominalInTime()) cscShowerOccupancyNom->Fill(chamber, sr);
        if (cscShower->isTightInTime()) cscShowerOccupancyTight->Fill(chamber, sr);
      }      

      cscShowerStationRing->Fill(0.5, sr);
      if (cscShower->isLooseInTime())   cscShowerStationRing->Fill(1.5, sr);
      if (cscShower->isNominalInTime()) cscShowerStationRing->Fill(2.5, sr);
      if (cscShower->isTightInTime())   cscShowerStationRing->Fill(3.5, sr);

      if (station > 1 && (ring % 2) == 1) {
        cscShowerChamber->Fill(chamber * 2,     0.5, evt_wgt);
        cscShowerChamber->Fill(chamber * 2 - 1, 0.5, evt_wgt);
        if (cscShower->isLooseInTime())   cscShowerChamber->Fill(chamber * 2,     1.5, evt_wgt);
        if (cscShower->isNominalInTime()) cscShowerChamber->Fill(chamber * 2,     2.5, evt_wgt);
        if (cscShower->isTightInTime())   cscShowerChamber->Fill(chamber * 2,     3.5, evt_wgt);
        if (cscShower->isLooseInTime())   cscShowerChamber->Fill(chamber * 2 - 1, 1.5, evt_wgt);
        if (cscShower->isNominalInTime()) cscShowerChamber->Fill(chamber * 2 - 1, 2.5, evt_wgt);
        if (cscShower->isTightInTime())   cscShowerChamber->Fill(chamber * 2 - 1, 3.5, evt_wgt);
      }
      else {
        cscShowerChamber->Fill(chamber, 0.5);
        if (cscShower->isLooseInTime())   cscShowerChamber->Fill(chamber, 1.5);
        if (cscShower->isNominalInTime()) cscShowerChamber->Fill(chamber, 2.5);
        if (cscShower->isTightInTime())   cscShowerChamber->Fill(chamber, 3.5);
      }
    }
  }

  showerInfoBX->Fill(EmtfShowers->getFirstBX(), EmtfShowers->getLastBX());
  int Nvalid = 0;
  for (auto Shower = EmtfShowers->begin(); Shower != EmtfShowers->end(); ++Shower) {
    int endcap = Shower->endcap();
    int sector = Shower->sector();
    if (not Shower->isValid()) continue;
    Nvalid += 1;
    // As of Oct 21 2021, endcap convention is 1 for pos, 2 for neg
    // Will change convention to 1 for pos, -1 for neg. (No need to change the line below)
    emtfShowerOccupancy->Fill(sector, (endcap == 1) ? 1.5 : 0.5);
    if (Shower->isOneNominalInTime() or Shower->isTwoLooseInTime() or Shower->isOneTightInTime()) {
      if (Shower->isOneTightInTime())   emtfShowerTypeOccupancy->Fill(sector, (endcap == 1) ? 7.5 : 0.5);
      if (Shower->isTwoLooseInTime())   emtfShowerTypeOccupancy->Fill(sector, (endcap == 1) ? 6.5 : 1.5);
      if (Shower->isOneNominalInTime()) emtfShowerTypeOccupancy->Fill(sector, (endcap == 1) ? 5.5 : 2.5);
      emtfShowerTypeOccupancy->Fill(sector, (endcap == 1) ? 4.5 : 3.5);
    }

    showerCheckNomInTime->Fill(Nvalid, Shower->isOneNominalInTime() * 1 + Shower->isTwoLooseInTime() * 2);
  }
  showerNperEvt->Fill(EmtfShowers->size(), Nvalid);
}
