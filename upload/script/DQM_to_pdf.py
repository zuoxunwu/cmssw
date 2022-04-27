from ROOT import *

def main():

  run_num = 222222
  out_dir = "shower_plots/"

  in_file = TFile.Open('DQM_V0001_L1TEMU_R000%d.root'%run_num, 'OPEN')
  plots = [
           'L1TdeCSCTPGShower/alct_cscshower_data_nom_summary_eff',
           'L1TdeCSCTPGShower/alct_cscshower_emul_nom_summary_eff',
           'L1TdeCSCTPGShower/clct_cscshower_data_nom_summary_eff',
           'L1TdeCSCTPGShower/clct_cscshower_emul_nom_summary_eff',
           'L1TdeCSCTPGShower/lct_cscshower_data_nom_summary_eff',
           'L1TdeCSCTPGShower/lct_cscshower_emul_nom_summary_eff',

           'L1TdeCSCTPGShower/alct_cscshower_data_tight_summary_eff',
           'L1TdeCSCTPGShower/alct_cscshower_emul_tight_summary_eff',
           'L1TdeCSCTPGShower/clct_cscshower_data_tight_summary_eff',
           'L1TdeCSCTPGShower/clct_cscshower_emul_tight_summary_eff',
           'L1TdeCSCTPGShower/lct_cscshower_data_tight_summary_eff',
           'L1TdeCSCTPGShower/lct_cscshower_emul_tight_summary_eff',

           'L1TdeCSCTPGShower/alct_cscshower_data_nom_summary_denom',
           'L1TdeCSCTPGShower/alct_cscshower_emul_nom_summary_denom',
           'L1TdeCSCTPGShower/clct_cscshower_data_nom_summary_denom',
           'L1TdeCSCTPGShower/clct_cscshower_emul_nom_summary_denom',
           'L1TdeCSCTPGShower/lct_cscshower_data_nom_summary_denom',
           'L1TdeCSCTPGShower/lct_cscshower_emul_nom_summary_denom',

           'L1TdeCSCTPGShower/alct_cscshower_data_tight_summary_denom',
           'L1TdeCSCTPGShower/alct_cscshower_emul_tight_summary_denom',
           'L1TdeCSCTPGShower/clct_cscshower_data_tight_summary_denom',
           'L1TdeCSCTPGShower/clct_cscshower_emul_tight_summary_denom',
           'L1TdeCSCTPGShower/lct_cscshower_data_tight_summary_denom',
           'L1TdeCSCTPGShower/lct_cscshower_emul_tight_summary_denom',

           'L1TdeCSCTPGShower/alct_cscshower_data_nom_summary_num',
           'L1TdeCSCTPGShower/alct_cscshower_emul_nom_summary_num',
           'L1TdeCSCTPGShower/clct_cscshower_data_nom_summary_num',
           'L1TdeCSCTPGShower/clct_cscshower_emul_nom_summary_num',
           'L1TdeCSCTPGShower/lct_cscshower_data_nom_summary_num',
           'L1TdeCSCTPGShower/lct_cscshower_emul_nom_summary_num',

           'L1TdeCSCTPGShower/alct_cscshower_data_tight_summary_num',
           'L1TdeCSCTPGShower/alct_cscshower_emul_tight_summary_num',
           'L1TdeCSCTPGShower/clct_cscshower_data_tight_summary_num',
           'L1TdeCSCTPGShower/clct_cscshower_emul_tight_summary_num',
           'L1TdeCSCTPGShower/lct_cscshower_data_tight_summary_num',
           'L1TdeCSCTPGShower/lct_cscshower_emul_tight_summary_num',

           'L1TdeStage2EMTF/Shower/emtf_shower_data_summary_eff',
           'L1TdeStage2EMTF/Shower/emtf_shower_emul_summary_eff',
           'L1TdeStage2EMTF/Shower/emtf_shower_data_summary_denom',
           'L1TdeStage2EMTF/Shower/emtf_shower_emul_summary_denom',
           'L1TdeStage2EMTF/Shower/emtf_shower_data_summary_num',
           'L1TdeStage2EMTF/Shower/emtf_shower_emul_summary_num',
          ]


  gStyle.SetOptStat(0000)
  gStyle.SetPadTopMargin(0.07);
  gStyle.SetPadBottomMargin(0.10);
  gStyle.SetPadLeftMargin(0.13);
  gStyle.SetPadRightMargin(0.14);
#  gStyle.SetPalette(kLightTemperature);
#  gStyle.SetPaintTextFormat(".1e");
  for plot in plots:
    hist = False
    hist = in_file.Get('DQMData/Run %d/L1TEMU/Run summary/'%run_num+plot).Clone(plot.replace('/','_'))
    canv = TCanvas(plot.replace('/','_'), plot.replace('/','_'), 1000, 600) # 2000,500

    canv.cd()

    hist.Draw('colz')    
    canv.SaveAs(out_dir + plot.replace('/','_') + '.png')


main()
