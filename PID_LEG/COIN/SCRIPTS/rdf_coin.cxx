#include "TFile.h"
#include "TStyle.h"
#include "TTree.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "string"
#include <ROOT/RDataFrame.hxx>

using namespace ROOT::RDF;

void pid_leg(int RunNumber=0, int nEntries=0){
  if (RunNumber == 0){
    cout<<"enter a run number:";
    cin >> RunNumber;
    if(RunNumber <= 0)
      return;
  }
  if (nEntries == 0){
    cout<<"enter a run number:";
    cin >> nEntries;
    if(nEntries <= 0)
      return;
  }

  string etottracknorm = "H.cal.etottracknorm";
  string eprtracknorm = "H.cal.eprtracknorm";
  string cer = "H.cer.npeSum";
  string delta = "H.gtr.dp";
  string ello = "T.coin.hEL_LO_ROC1_tdcTimeRaw";
  string ellolo = "T.coin.hEL_LO_LO_ROC1_tdcTimeRaw";
  string elhi = "T.coin.hEL_HI_ROC1_tdcTimeRaw";
  string elreal = "T.coin.hEL_REAL_ROC1_tdcTimeRaw";
  string elclean = "T.coin.hEL_CLEAN_ROC1_tdcTimeRaw";
  string prlo = "T.coin.hPRLO_tdcTimeRaw";
  string prhi = "T.coin.hPRHI_tdcTimeRaw";
  string shlo = "T.coin.hSHWR_tdcTimeRaw";
  string cerleg = "T.coin.hCER_tdcTimeRaw";
  string cer_amp = "T.coin.hCER_adcPulseAmp";
  string cer_mult = "T.coin.hCER_adcMultiplicity";
  string pre_amp = "T.coin.hPSHWR_adcPulseAmp";
  string pre_mult = "T.coin.hPSHWR_adcMultiplicity";
  string sh_amp = "T.coin.hSHWR_adcPulseAmp";
  string sh_mult = "T.coin.hSHWR_adcMultiplicity";
  string edtm = "T.coin.hEDTM_tdcTime";

  string c_delta = "H.gtr.dp > -8. && H.gtr.dp < 8.";
  string c_ello = "T.coin.hEL_LO_ROC1_tdcTimeRaw > 0.";
  string c_ellolo = "T.coin.hEL_LO_LO_ROC1_tdcTimeRaw > 0.";
  string c_elhi = "T.coin.hEL_HI_ROC1_tdcTimeRaw > 0.";
  string c_elreal = "T.coin.hEL_REAL_ROC1_tdcTimeRaw > 0.";
  string c_elclean = "T.coin.hEL_CLEAN_ROC1_tdcTimeRaw > 0.";
  string c_prlo = "T.coin.hPRLO_tdcTimeRaw > 0.";
  string c_prhi = "T.coin.hPRHI_tdcTimeRaw > 0.";
  string c_shlo = "T.coin.hSHWR_tdcTimeRaw > 0.";
  string c_cerleg = "T.coin.hCER_tdcTimeRaw > 0.";
  string c_cer_mult = "T.coin.hCER_adcMultiplicity > 0.";
  string c_pre_mult = "T.coin.hPSHWR_adcMultiplicity > 0.";
  string c_sh_mult = "T.coin.hSHWR_adcMultiplicity > 0.";

  
  TString filename = Form("ROOTfiles/Analysis/General/Full_Online_coin_replay_%d_%d.root",RunNumber,nEntries);
  TFile *f = new TFile(filename, "READ");
  TTree *t = (TTree*) f->Get("T");

  //HMS Total Shower histograms 
  TH1DModel m_hPcal_E_p ("hPcal_E_p","HMS Calorimeter Total E/P for Different PID Legs; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_elreal ("hPcal_E_p_elreal","HMS Calorimeter Total E/P ELREAL; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_elclean ("hPcal_E_p_elclean","HMS Calorimeter Total E/P ELCLEAN; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_ello ("hPcal_E_p_ello","HMS Calorimeter Total E/P ELLO; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_ellolo ("hPcal_E_p_ellolo","HMS Calorimeter Total E/P ELLOLO; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_elhi ("hPcal_E_p_elhi","HMS Calorimeter Total E/P ELHI; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_prlo ("hPcal_E_p_prlo","HMS Calorimeter Total E/P PRLO; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_prhi ("hPcal_E_p_prhi","HMS Calorimeter Total E/P PRHI; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_shlo ("hPcal_E_p_shlo","HMS Calorimeter Total E/P SHLO; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_E_p_cer ("hPcal_E_p_cer","HMS Calorimeter Total E/P CER; etottracknorm E/p; counts", 100, 0.0, 2.0);
  TH1DModel m_hPcal_amp ("hPcal_amp","Shower Pulse Amplitude;Pulse Amplitude (mV);counts", 100, 0.0, 700.0);
  TH1DModel m_hPcal_amp_shlo ("hPcal_amp_shlo","Shower Pulse Amplitude SHLO;Pulse Amplitude (mV);counts", 100, 0.0, 700.0);
  //HMS Cherenkov histograms
  TH1DModel m_hPcer ("hPcer","CER NPE SUM;npeSum;counts", 100, 0.0, 30.0);
  TH1DModel m_hPcer_cer ("hPcer_cer","CER NPE SUM CER;npeSum;counts", 100, 0.0, 30.0);
  TH1DModel m_hPcer_amp ("hPcer_amp","CER Pulse Amplitude;Pulse Amplitude (mV);counts", 100, 0.0, 600.0);
  TH1DModel m_hPcer_amp_cer ("hPcer_amp_cer","CER Pulse Amplitude CER;Pulse Amplitude (mV);counts", 100, 0.0, 600.0);
  //HMS Preshower histograms
  TH1DModel m_hPpre_amp ("hPpre_amp","Preshower Pulse Amplitude;Pulse Amplitude (mV);counts", 100, 0.0, 400.0);
  TH1DModel m_hPpre_amp_prlo ("hPpre_amp_prlo","Preshower Pulse Amplitude PRLO;Pulse Amplitude (mV);counts", 100, 0.0, 400.0);
  TH1DModel m_hPpre_amp_prhi ("hPpre_amp_prhi","Preshower Pulse Amplitude PRHI;Pulse Amplitude (mV);counts", 100, 0.0, 400.0);
  TH1DModel m_hPpre_E_p ("hPpre_E_p","HMS Preshower E/p for Different PID legs;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_elreal ("hPpre_E_p_elreal","HMS preshower E/P ELREAL;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_elclean ("hPpre_E_p_elclean","HMS preshower E/P ELCLEAN;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_ello ("hPpre_E_p_ello","HMS preshower E/P ELLO;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_ellolo ("hPpre_E_p_ellolo","HMS preshower E/P ELLOLO;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_elhi ("hPpre_E_p_elhi","HMS preshower E/P ELHI;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_prlo ("hPpre_E_p_prlo","HMS preshower E/P PRLO;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_prhi ("hPpre_E_p_prhi","HMS preshower E/P PRHI;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_shlo ("hPpre_E_p_shlo","HMS preshower E/P SHLO;preshower E/p;counts", 100, 0.0, 1.0);
  TH1DModel m_hPpre_E_p_cer ("hPpre_E_p_cer","HMS preshower E/P CER;preshower E/p;counts", 100, 0.0, 1.0);
  // 2D Preshower vs Total E/p plots 
  TH2DModel m_hPpre_vs_cal ("hPpre_vs_cal","preshower vs total E/p;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_elreal ("hPpre_vs_cal_elreal","preshower vs total E/p ELREAL;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_elclean ("hPpre_vs_cal_elclean","preshower vs total E/p ELCLEAN;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_prlo ("hPpre_vs_cal_prlo","preshower vs total E/p PRLO;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_prhi ("hPpre_vs_cal_prhi","preshower vs total E/p PRHI;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_ello ("hPpre_vs_cal_ello","preshower vs total E/p ELLO;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_ellolo ("hPpre_vs_cal_ellolo","preshower vs total E/p ELLO;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_shlo ("hPpre_vs_cal_shlo","preshower vs total E/p SHLO;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_elhi ("hPpre_vs_cal_elhi","preshower vs total E/p ELHI;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  TH2DModel m_hPpre_vs_cal_cer ("hPpre_vs_cal_cer","preshower vs total E/p CER;total E/p;Preshower E/p", 100, 0.0, 2.0, 100, 0.0, 1.0);
  // 2D preshower pulse amp vs total E/p plots
  TH2DModel m_hPpre_amp_vs_cal ("hPpre_amp_vs_cal","preshower Pulse Amp vs total E/p;total E/;Preshower Pulse Amp (mV)", 100, 0.0, 400.0, 100, 0.0, 2.0);
  TH2DModel m_hPpre_amp_vs_cal_prlo ("hPpre_amp_vs_cal_prlo","preshower Pulse Amp vs total E/p PRLO;total E/;Preshower Pulse Amp (mV)", 100, 0.0, 400.0, 100, 0.0, 2.0);
  TH2DModel m_hPpre_amp_vs_cal_prhi ("hPpre_amp_vs_cal_prhi","preshower Pulse Amp vs total E/p PRHI;total E/;Preshower Pulse Amp (mV)", 100, 0.0, 400.0, 100, 0.0, 2.0);
  TH2DModel m_hPpre_amp_vs_cal_shlo ("hPpre_amp_vs_cal_shlo","preshower Pulse Amp vs total E/p SHLO;total E/;Preshower Pulse Amp (mV)", 100, 0.0, 400.0, 100, 0.0, 2.0);
  // 2D shower pulse amp vs total E/p plots
  TH2DModel m_hPsh_amp_vs_cal ("hPsh_amp_vs_cal","shower Pulse Amp vs total E/p;total E/;Shower Pulse Amp (mV)", 100, 0.0, 700.0, 100, 0.0, 2.0);
  TH2DModel m_hPsh_amp_vs_cal_shlo ("hPsh_amp_vs_cal_shlo","shower Pulse Amp vs total E/p SHLO;total E/;Shower Pulse Amp (mV)", 100, 0.0, 700.0, 100, 0.0, 2.0);

  ROOT::EnableImplicitMT(16);
  ROOT::RDataFrame d(*t);

  auto d2 = d.Filter(c_delta);
   auto hPcal_E_p = d2.Histo1D(m_hPcal_E_p,etottracknorm);
   auto hPpre_E_p = d2.Histo1D(m_hPpre_E_p,eprtracknorm);
   auto hPpre_vs_cal = d2.Histo2D(m_hPpre_vs_cal,etottracknorm, eprtracknorm);
   auto hPcer = d2.Histo1D(m_hPcer, cer);
  //EL_REAL TDC
  auto d_elreal = d2.Filter(c_elreal);
   auto hPcal_E_p_elreal = d_elreal.Histo1D(m_hPcal_E_p_elreal,etottracknorm);
   auto hPpre_E_p_elreal = d_elreal.Histo1D(m_hPpre_E_p_elreal,eprtracknorm);
   auto hPpre_vs_cal_elreal = d_elreal.Histo2D(m_hPpre_vs_cal_elreal,etottracknorm, eprtracknorm);
  //EL_CLEAN TDC
  auto d_elclean = d2.Filter(c_elclean);
   auto hPcal_E_p_elclean = d_elclean.Histo1D(m_hPcal_E_p_elclean,etottracknorm);
   auto hPpre_E_p_elclean = d_elclean.Histo1D(m_hPpre_E_p_elclean,eprtracknorm);
   auto hPpre_vs_cal_elclean = d_elclean.Histo2D(m_hPpre_vs_cal_elclean,etottracknorm, eprtracknorm);
  //EL_LO TDC
  auto d_ello = d2.Filter(c_ello);
   auto hPcal_E_p_ello = d_ello.Histo1D(m_hPcal_E_p_ello,etottracknorm);
   auto hPpre_E_p_ello = d_ello.Histo1D(m_hPpre_E_p_ello,eprtracknorm);
   auto hPpre_vs_cal_ello = d_ello.Histo2D(m_hPpre_vs_cal_ello,etottracknorm, eprtracknorm);
  //EL_LO_LO TDC
  auto d_ellolo = d2.Filter(c_ellolo);
   auto hPcal_E_p_ellolo = d_ellolo.Histo1D(m_hPcal_E_p_ellolo,etottracknorm);
   auto hPpre_E_p_ellolo = d_ellolo.Histo1D(m_hPpre_E_p_ellolo,eprtracknorm);
   auto hPpre_vs_cal_ellolo = d_ellolo.Histo2D(m_hPpre_vs_cal_ellolo,etottracknorm, eprtracknorm);
  //EL_HI TDC
  auto d_elhi = d2.Filter(c_elhi);
   auto hPcal_E_p_elhi = d_elhi.Histo1D(m_hPcal_E_p_elhi,etottracknorm);
   auto hPpre_E_p_elhi = d_elhi.Histo1D(m_hPpre_E_p_elhi,eprtracknorm);
   auto hPpre_vs_cal_elhi = d_elhi.Histo2D(m_hPpre_vs_cal_elhi,etottracknorm, eprtracknorm);
  //PR_LO TDC
  auto d_prlo = d2.Filter(c_prlo);
   auto hPcal_E_p_prlo = d_prlo.Histo1D(m_hPcal_E_p_prlo,etottracknorm);
   auto hPpre_E_p_prlo = d_prlo.Histo1D(m_hPpre_E_p_prlo,eprtracknorm);
   auto hPpre_vs_cal_prlo = d_prlo.Histo2D(m_hPpre_vs_cal_prlo,etottracknorm, eprtracknorm);
  //PR_HI TDC
  auto d_prhi = d2.Filter(c_prhi);
   auto hPcal_E_p_prhi = d_prhi.Histo1D(m_hPcal_E_p_prhi,etottracknorm);
   auto hPpre_E_p_prhi = d_prhi.Histo1D(m_hPpre_E_p_prhi,eprtracknorm);
   auto hPpre_vs_cal_prhi = d_prhi.Histo2D(m_hPpre_vs_cal_prhi,etottracknorm, eprtracknorm);
  //SH_LO TDC
  auto d_shlo = d2.Filter(c_shlo);
   auto hPcal_E_p_shlo = d_shlo.Histo1D(m_hPcal_E_p_shlo,etottracknorm);
   auto hPpre_E_p_shlo = d_shlo.Histo1D(m_hPpre_E_p_shlo,eprtracknorm);
   auto hPpre_vs_cal_shlo = d_shlo.Histo2D(m_hPpre_vs_cal_shlo,etottracknorm, eprtracknorm);
  //CER TDC
  auto d_cer = d2.Filter(c_cerleg);
   auto hPcal_E_p_cer = d_cer.Histo1D(m_hPcal_E_p_cer,etottracknorm);
   auto hPpre_E_p_cer = d_cer.Histo1D(m_hPpre_E_p_cer,eprtracknorm);
   auto hPpre_vs_cal_cer = d_cer.Histo2D(m_hPpre_vs_cal_cer,etottracknorm, eprtracknorm);
   auto hPcer_cer = d_cer.Histo1D(m_hPcer_cer,cer);

   //Require hit in adc cer
   auto d_cer_adc_mult = d2.Filter(c_cer_mult);
    auto hPcer_amp = d_cer_adc_mult.Histo1D(m_hPcer_amp,cer_amp);
    //Require hit in adc and tdc
    auto d_cer_tdc = d_cer_adc_mult.Filter(c_cerleg);
     auto hPcer_amp_cer = d_cer_tdc.Histo1D(m_hPcer_amp_cer,cer_amp);

   //Require hit in adc preshower
   auto d_pre_adc_mult = d2.Filter(c_pre_mult);
    auto hPpre_amp = d_pre_adc_mult.Histo1D(m_hPpre_amp,pre_amp);
    auto hPpre_amp_vs_cal = d_pre_adc_mult.Histo2D(m_hPpre_amp_vs_cal,pre_amp,etottracknorm);
   //Require hit in adc and tdc PRLO
    auto d_pre_tdc_prlo = d_pre_adc_mult.Filter(c_prlo);
     auto hPpre_amp_vs_cal_prlo = d_pre_tdc_prlo.Histo2D(m_hPpre_amp_vs_cal_prlo,pre_amp,etottracknorm);
     auto hPpre_amp_prlo = d_pre_tdc_prlo.Histo1D(m_hPpre_amp_prlo,pre_amp);
   //Require hit in adc and tdc PRHI
    auto d_pre_tdc_prhi = d_pre_adc_mult.Filter(c_prhi);
     auto hPpre_amp_vs_cal_prhi = d_pre_tdc_prhi.Histo2D(m_hPpre_amp_vs_cal_prhi,pre_amp,etottracknorm);
     auto hPpre_amp_prhi = d_pre_tdc_prhi.Histo1D(m_hPpre_amp_prhi,pre_amp);

    //Require hit in adc shower
    auto d_sh_adc_mult = d2.Filter(c_sh_mult);
     auto hPcal_amp = d_sh_adc_mult.Histo1D(m_hPcal_amp,sh_amp);
     auto hPsh_amp_vs_cal = d_sh_adc_mult.Histo2D(m_hPsh_amp_vs_cal,sh_amp,etottracknorm);
     //Require hit in adc and tdc shlo
     auto d_sh_tdc_shlo = d_sh_adc_mult.Filter(c_shlo);
      auto hPsh_amp_vs_cal_shlo = d_sh_tdc_shlo.Histo2D(m_hPsh_amp_vs_cal_shlo,sh_amp,etottracknorm);
      auto hPcal_amp_shlo = d_sh_tdc_shlo.Histo1D(m_hPcal_amp_shlo,sh_amp);

  TFile *f2 = new TFile("tmp.root","RECREATE");
  hPcal_E_p->Write();
  hPpre_E_p->Write();
  hPcer->Write();
  hPpre_vs_cal->Write();
  hPcal_E_p_elreal->Write();
  hPpre_E_p_elreal->Write();
  hPpre_vs_cal_elreal->Write();
  hPcal_E_p_elclean->Write();
  hPpre_E_p_elclean->Write();
  hPpre_vs_cal_elclean->Write();
  hPcal_E_p_ello->Write();
  hPpre_E_p_ello->Write();
  hPpre_vs_cal_ello->Write();
  hPcal_E_p_ellolo->Write();
  hPpre_E_p_ellolo->Write();
  hPpre_vs_cal_ellolo->Write();
  hPcal_E_p_elhi->Write();
  hPpre_E_p_elhi->Write();
  hPpre_vs_cal_elhi->Write();
  hPcal_E_p_prlo->Write();
  hPpre_E_p_prlo->Write();
  hPpre_vs_cal_prlo->Write();
  hPcal_E_p_prhi->Write();
  hPpre_E_p_prhi->Write();
  hPpre_vs_cal_prhi->Write();
  hPcal_E_p_shlo->Write();
  hPpre_E_p_shlo->Write();
  hPpre_vs_cal_shlo->Write();
  hPcal_E_p_cer->Write();
  hPpre_E_p_cer->Write();
  hPpre_vs_cal_cer->Write();
  hPcer_amp->Write();
  hPcer_amp_cer->Write();
  hPpre_amp->Write();
  hPpre_amp_vs_cal->Write();
  hPpre_amp_prlo->Write();
  hPpre_amp_vs_cal_prlo->Write();
  hPpre_amp_prhi->Write();
  hPpre_amp_vs_cal_prhi->Write();
  hPcal_amp->Write();
  hPsh_amp_vs_cal->Write();
  hPcal_amp_shlo->Write();
  hPsh_amp_vs_cal_shlo->Write();
  hPcer_cer->Write();
    
  return;
}
