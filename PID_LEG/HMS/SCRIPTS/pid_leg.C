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

void pid_leg(int RunNumber=0, int Events=0){
   if (RunNumber == 0){
     cout<<"enter a run number:";
     cin >> RunNumber;
     if(RunNumber <= 0)
     return;
     }
   if (Events == 0){
     cout<<"how many events?:";
     cin >> Events;
     }

  TString filename = Form("ROOTfiles/HMS/hms_replay_pid_leg_%d_%d.root", RunNumber, Events);
  TFile *f = new TFile(filename, "READ");
  TTree *t = (TTree*) f->Get("T");


  double etotnorm;
  double etottracknorm;
  double eprtracknorm;
  double cer;
  double delta;
  double ello;
  double ellolo;
  double elhi;
  double elreal;
  double elclean;
  double prlo;
  double prhi;
  double shlo;
  double cerleg;
  double cer_amp;
  double cer_mult;
  double pre_amp;
  double pre_mult;
  double sh_amp;
  double sh_mult;
  double edtm;
   

  t->SetBranchAddress("H.cal.etottracknorm",&etottracknorm);
  t->SetBranchAddress("H.cal.eprtracknorm",&eprtracknorm);
  t->SetBranchAddress("H.cer.npeSum",&cer);
  t->SetBranchAddress("H.gtr.dp", &delta);
  t->SetBranchAddress("T.hms.hEL_LO_tdcTimeRaw", &ello);
  t->SetBranchAddress("T.hms.hEL_LO_LO_tdcTimeRaw", &ellolo);
  t->SetBranchAddress("T.hms.hEL_HI_tdcTimeRaw", &elhi);
  t->SetBranchAddress("T.hms.hEL_REAL_tdcTimeRaw", &elreal);
  t->SetBranchAddress("T.hms.hEL_CLEAN_tdcTimeRaw", &elclean);
  t->SetBranchAddress("T.hms.hPRLO_tdcTimeRaw", &prlo);
  t->SetBranchAddress("T.hms.hPRHI_tdcTimeRaw", &prhi);
  t->SetBranchAddress("T.hms.hSHWR_tdcTimeRaw", &shlo);
  t->SetBranchAddress("T.hms.hCER_tdcTimeRaw", &cerleg);
  t->SetBranchAddress("T.hms.hCER_adcPulseAmp", &cer_amp);
  t->SetBranchAddress("T.hms.hCER_adcMultiplicity", &cer_mult);
  t->SetBranchAddress("T.hms.hPSHWR_adcPulseAmp", &pre_amp);
  t->SetBranchAddress("T.hms.hPSHWR_adcMultiplicity", &pre_mult);
  t->SetBranchAddress("T.hms.hSHWR_adcPulseAmp", &sh_amp);
  t->SetBranchAddress("T.hms.hSHWR_adcMultiplicity", &sh_mult);
  t->SetBranchAddress("T.hms.hEDTM_tdcTime", &edtm);

  //HMS Total Shower histograms 
  TH1F *hPcal_E_p  = new TH1F("total calo E/p","HMS Calorimeter Total E/P for Different PID Legs", 100, 0.0, 2.0);
  hPcal_E_p->GetXaxis()->SetTitle("etottracknorm E/p");
  hPcal_E_p->GetYaxis()->SetTitle("counts");
  TH1F *hPcal_E_p_elreal  = new TH1F("total calo E/p ELREAL","HMS Calorimeter Total E/P ELREAL", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_elclean  = new TH1F("total calo E/p ELCLEAN","HMS Calorimeter Total E/P ELCLEAN", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_ello  = new TH1F("total calo E/p ELLO","HMS Calorimeter Total E/P ELLO", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_ellolo  = new TH1F("total calo E/p ELLOLO","HMS Calorimeter Total E/P ELLOLO", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_elhi  = new TH1F("total calo E/p ELHI","HMS Calorimeter Total E/P ELHI", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_prlo  = new TH1F("total calo E/p PRLO","HMS Calorimeter Total E/P PRLO", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_prhi  = new TH1F("total calo E/p PRHI","HMS Calorimeter Total E/P PRHI", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_shlo  = new TH1F("total calo E/p SHLO","HMS Calorimeter Total E/P SHLO", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_cer  = new TH1F("total calo E/p CER","HMS Calorimeter Total E/P CER", 100, 0.0, 2.0);
  TH1F *hPcal_amp  = new TH1F("total amp","Shower Pulse Amplitude", 100, 0.0, 700.0);
  hPcal_amp->GetXaxis()->SetTitle("Pulse Amplitude (mV)");
  hPcal_amp->GetYaxis()->SetTitle("counts");
  TH1F *hPcal_amp_shlo  = new TH1F("total amp SHLO","", 100, 0.0, 700.0);
  //HMS Cherenkov histograms
  TH1F *hPcer  = new TH1F("CER npe","CER NPE SUM", 100, 0.0, 30.0);
  hPcer->GetXaxis()->SetTitle("npe");
  hPcer->GetYaxis()->SetTitle("counts");
  TH1F *hPcer_cer  = new TH1F("CER npe CER","CER NPE SUM CER", 100, 0.0, 30.0);
  TH1F *hPcer_amp  = new TH1F("CER amp","CER Pulse Amplitude CER", 100, 0.0, 600.0);
  hPcer_amp->GetXaxis()->SetTitle("Pulse Amplitude (mV)");
  hPcer_amp->GetYaxis()->SetTitle("counts");
  TH1F *hPcer_amp_cer  = new TH1F("CER amp CER","", 100, 0.0, 600.0);
  //HMS Preshower histograms
  TH1F *hPpre_amp  = new TH1F("pre amp","Preshower Pulse Amplitude", 100, 0.0, 400.0);
  hPpre_amp->GetXaxis()->SetTitle("Pulse Amplitude (mV)");
  hPpre_amp->GetYaxis()->SetTitle("counts");
  TH1F *hPpre_amp_prlo  = new TH1F("pre amp PRLO","", 100, 0.0, 400.0);
  TH1F *hPpre_amp_prhi  = new TH1F("pre amp PRHI","", 100, 0.0, 400.0);
  TH1F *hPpre_E_p  = new TH1F("preshower E/p","HMS Preshower E/p for Different PID legs", 100, 0.0, 1.0);
  hPpre_E_p->GetXaxis()->SetTitle("preshower E/p");
  hPpre_E_p->GetYaxis()->SetTitle("counts");
  TH1F *hPpre_E_p_elreal  = new TH1F("preshower E/p ELREAL","HMS preshower E/P ELREAL", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_elclean  = new TH1F("preshower E/p ELCLEAN","HMS preshower E/P ELCLEAN", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_ello  = new TH1F("preshower E/p ELLO","HMS preshower E/P ELLO", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_ellolo  = new TH1F("preshower E/p ELLOLO","HMS preshower E/P ELLOLO", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_elhi  = new TH1F("preshower E/p ELHI","HMS preshower E/P ELHI", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_prlo  = new TH1F("preshower E/p PRLO","HMS preshower E/P PRLO", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_prhi  = new TH1F("preshower E/p PRHI","HMS preshower E/P PRHI", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_shlo  = new TH1F("preshower E/p SHLO","HMS preshower E/P SHLO", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_cer  = new TH1F("preshower E/p CER","HMS preshower E/P CER", 100, 0.0, 1.0);
  // 2D Preshower vs Total E/p plots 
  TH2F *hPpre_vs_cal  = new TH2F("preshower vs total E/p","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal->GetYaxis()->SetTitle("Preshower E/p");
  TH2F *hPpre_vs_cal_elreal  = new TH2F("preshower vs total E/p ELREAL","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal_elreal->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal_elreal->GetYaxis()->SetTitle("Preshower E/p");
  TH2F *hPpre_vs_cal_elclean  = new TH2F("preshower vs total E/p ELCLEAN","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal_elclean->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal_elclean->GetYaxis()->SetTitle("Preshower E/p");
  TH2F *hPpre_vs_cal_prlo  = new TH2F("preshower vs total E/p PRLO","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal_prlo->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal_prlo->GetYaxis()->SetTitle("Preshower E/p");
  TH2F *hPpre_vs_cal_prhi  = new TH2F("preshower vs total E/p PRHI","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal_prhi->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal_prhi->GetYaxis()->SetTitle("Preshower E/p");
  TH2F *hPpre_vs_cal_ello  = new TH2F("preshower vs total E/p ELLO","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal_ello->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal_ello->GetYaxis()->SetTitle("Preshower E/p");
  TH2F *hPpre_vs_cal_elhi  = new TH2F("preshower vs total E/p ELHI","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal_elhi->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal_elhi->GetYaxis()->SetTitle("Preshower E/p");
  TH2F *hPpre_vs_cal_cer  = new TH2F("preshower vs total E/p CER","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal_cer->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal_cer->GetYaxis()->SetTitle("Preshower E/p");
  TH2F *hPpre_vs_cal_shlo  = new TH2F("preshower vs total E/p SHLO","", 100, 0.0, 2.0, 100, 0.0, 1.0);
  hPpre_vs_cal_shlo->GetXaxis()->SetTitle("total E/p");
  hPpre_vs_cal_shlo->GetYaxis()->SetTitle("Preshower E/p");
  // 2D preshower pulse amp vs total E/p plots
  TH2F *hPpre_amp_vs_cal  = new TH2F("preshower Pulse Amp vs total E/p","", 100, 0.0, 400.0, 100, 0.0, 2.0);
  hPpre_amp_vs_cal->GetYaxis()->SetTitle("total E/p");
  hPpre_amp_vs_cal->GetXaxis()->SetTitle("Preshower Pulse Amp (mV)");
  TH2F *hPpre_amp_vs_cal_prlo  = new TH2F("preshower Pulse Amp vs total E/p PRLO","", 100, 0.0, 400.0, 100, 0.0, 2.0);
  hPpre_amp_vs_cal_prlo->GetYaxis()->SetTitle("total E/p");
  hPpre_amp_vs_cal_prlo->GetXaxis()->SetTitle("Preshower Pulse Amp (mV)");
  TH2F *hPpre_amp_vs_cal_prhi  = new TH2F("preshower Pulse Amp vs total E/p PRHI","", 100, 0.0, 400.0, 100, 0.0, 2.0);
  hPpre_amp_vs_cal_prhi->GetYaxis()->SetTitle("total E/p");
  hPpre_amp_vs_cal_prhi->GetXaxis()->SetTitle("Preshower Pulse Amp (mV)");
  TH2F *hPpre_amp_vs_cal_shlo  = new TH2F("preshower Pulse Amp vs total E/p SHLO","", 100, 0.0, 400.0, 100, 0.0, 2.0);
  hPpre_amp_vs_cal_shlo->GetYaxis()->SetTitle("total E/p");
  hPpre_amp_vs_cal_shlo->GetXaxis()->SetTitle("Preshower Pulse Amp (mV)");
  // 2D shower pulse amp vs total E/p plots
  TH2F *hPsh_amp_vs_cal  = new TH2F("shower Pulse Amp vs total E/p","", 100, 0.0, 700.0, 100, 0.0, 2.0);
  hPsh_amp_vs_cal->GetYaxis()->SetTitle("total E/p");
  hPsh_amp_vs_cal->GetXaxis()->SetTitle("shower Pulse Amp (mV)");
  TH2F *hPsh_amp_vs_cal_shlo  = new TH2F("shower Pulse Amp vs total E/p SHLO","", 100, 0.0, 700.0, 100, 0.0, 2.0);
  hPsh_amp_vs_cal_shlo->GetYaxis()->SetTitle("total E/p");
  hPsh_amp_vs_cal_shlo->GetXaxis()->SetTitle("shower Pulse Amp (mV)");
  


  Long64_t nentries = t->GetEntries();
    cout<<"num of entries: "<<nentries<<endl;

    for (Long64_t i=0; i<nentries; i++){
        t->GetEntry(i);
        if(delta > -8. && delta < 8.){
          hPcal_E_p->Fill(etottracknorm);
          hPpre_E_p->Fill(eprtracknorm);
          hPpre_vs_cal->Fill(etottracknorm, eprtracknorm);
          hPcer->Fill(cer);
          if(elreal>0.){
            hPcal_E_p_elreal->Fill(etottracknorm);
            hPpre_E_p_elreal->Fill(eprtracknorm);
            hPpre_vs_cal_elreal->Fill(etottracknorm, eprtracknorm);}
          if(elclean>0.){
            hPcal_E_p_elclean->Fill(etottracknorm);
            hPpre_E_p_elclean->Fill(eprtracknorm);
            hPpre_vs_cal_elclean->Fill(etottracknorm, eprtracknorm);}
          if(ello>0.){
            hPcal_E_p_ello->Fill(etottracknorm);
            hPpre_E_p_ello->Fill(eprtracknorm);
            hPpre_vs_cal_ello->Fill(etottracknorm, eprtracknorm);}
          if(ellolo>0.){
            hPcal_E_p_ellolo->Fill(etottracknorm);
            hPpre_E_p_ellolo->Fill(eprtracknorm);}
          if(elhi>0.){
           hPcal_E_p_elhi->Fill(etottracknorm);
           hPpre_E_p_elhi->Fill(eprtracknorm);
           hPpre_vs_cal_elhi->Fill(etottracknorm, eprtracknorm);}
          if(prlo>0.){
           hPcal_E_p_prlo->Fill(etottracknorm);
           hPpre_E_p_prlo->Fill(eprtracknorm);
           hPpre_vs_cal_prlo->Fill(etottracknorm, eprtracknorm);}
          if(prhi>0.){
           hPcal_E_p_prhi->Fill(etottracknorm);
           hPpre_E_p_prhi->Fill(eprtracknorm);
           hPpre_vs_cal_prhi->Fill(etottracknorm, eprtracknorm);}
          if(shlo>0.){
           hPcal_E_p_shlo->Fill(etottracknorm);
           hPpre_E_p_shlo->Fill(eprtracknorm);
           hPpre_vs_cal_shlo->Fill(etottracknorm, eprtracknorm);}
          if(cerleg>0.){
           hPcal_E_p_cer->Fill(etottracknorm);
           hPpre_E_p_cer->Fill(eprtracknorm);
           hPcer_cer->Fill(cer);
           hPpre_vs_cal_cer->Fill(etottracknorm, eprtracknorm);}
           
        if(cer_mult>0){
          hPcer_amp->Fill(cer_amp);
          if(cerleg>0){
          hPcer_amp_cer->Fill(cer_amp);
          }
        }
        if(pre_mult>0){
          hPpre_amp->Fill(pre_amp);
          hPpre_amp_vs_cal->Fill(pre_amp,etottracknorm);
          if(prlo>0){
          hPpre_amp_vs_cal_prlo->Fill(pre_amp,etottracknorm);
          hPpre_amp_prlo->Fill(pre_amp);
          }
          if(prhi>0){
          hPpre_amp_vs_cal_prhi->Fill(pre_amp,etottracknorm);
          hPpre_amp_prhi->Fill(pre_amp);
          }
        }
        if(sh_mult>0){
          hPcal_amp->Fill(sh_amp);
          hPsh_amp_vs_cal->Fill(sh_amp,etottracknorm);
        if(shlo>0){
          hPsh_amp_vs_cal_shlo->Fill(sh_amp,etottracknorm);
          hPcal_amp_shlo->Fill(sh_amp);
          }
        }
      }
    }
          hPcal_E_p->SetLineColor(kBlack);
          hPcal_E_p->SetLineWidth(3.);
          hPcal_E_p->SetLineStyle(2);
          hPcal_E_p_elreal->SetLineColor(kRed);
          hPcal_E_p_elreal->SetLineWidth(2.);
          hPcal_E_p_elreal->SetLineStyle(2);
          hPcal_E_p_elclean->SetLineColor(kMagenta-8);
          hPcal_E_p_elclean->SetLineWidth(2.);
          hPcal_E_p_elclean->SetLineStyle(2);
          hPcal_E_p_ello->SetLineColor(kMagenta);
          hPcal_E_p_ello->SetLineWidth(2.);
          hPcal_E_p_ello->SetLineStyle(2);
          hPcal_E_p_elhi->SetLineColor(kGreen+1);
          hPcal_E_p_elhi->SetLineWidth(2.);
          hPcal_E_p_elhi->SetLineStyle(2);
          hPcal_E_p_prlo->SetLineColor(kOrange);
          hPcal_E_p_prlo->SetLineWidth(2.);
          hPcal_E_p_prlo->SetLineStyle(2);
          hPcal_E_p_prhi->SetLineColor(kBlue-3);
          hPcal_E_p_prhi->SetLineWidth(2.);
          hPcal_E_p_prhi->SetLineStyle(2);
          hPcal_E_p_cer->SetLineColor(kTeal-4);
          hPcal_E_p_cer->SetLineWidth(2.);
          hPcal_E_p_cer->SetLineStyle(2);
          hPcal_E_p_shlo->SetLineColor(kCyan+2);
          hPcal_E_p_shlo->SetLineWidth(2.);
          hPcal_E_p_shlo->SetLineStyle(2);

          hPpre_E_p->SetLineColor(kBlack);
          hPpre_E_p->SetLineWidth(3.);
          hPpre_E_p->SetLineStyle(2);
          hPpre_E_p_elreal->SetLineColor(kRed);
          hPpre_E_p_elreal->SetLineWidth(2.);
          hPpre_E_p_elreal->SetLineStyle(2);
          hPpre_E_p_elclean->SetLineColor(kMagenta-8);
          hPpre_E_p_elclean->SetLineWidth(2.);
          hPpre_E_p_elclean->SetLineStyle(2);
          hPpre_E_p_ello->SetLineColor(kMagenta);
          hPpre_E_p_ello->SetLineWidth(2.);
          hPpre_E_p_ello->SetLineStyle(2);
          hPpre_E_p_elhi->SetLineColor(kGreen+1);
          hPpre_E_p_elhi->SetLineWidth(2.);
          hPpre_E_p_elhi->SetLineStyle(2);
          hPpre_E_p_prlo->SetLineColor(kOrange);
          hPpre_E_p_prlo->SetLineWidth(2.);
          hPpre_E_p_prlo->SetLineStyle(2);
          hPpre_E_p_prhi->SetLineColor(kBlue-3);
          hPpre_E_p_prhi->SetLineWidth(2.);
          hPpre_E_p_prhi->SetLineStyle(2);
          hPpre_E_p_cer->SetLineColor(kTeal-4);
          hPpre_E_p_cer->SetLineWidth(2.);
          hPpre_E_p_cer->SetLineStyle(2);
          hPcer_cer->SetLineColor(kCyan+1);
          hPcer_cer->SetLineWidth(2.);
          hPcer_cer->SetLineStyle(2);
          hPcer->SetLineColor(kMagenta);
          hPcer->SetLineWidth(2.);
          hPcer->SetLineStyle(2);
          hPpre_E_p_shlo->SetLineColor(kCyan+2);
          hPpre_E_p_shlo->SetLineWidth(2.);
          hPpre_E_p_shlo->SetLineStyle(2);

          hPcer_amp->SetLineColor(kMagenta);
          hPcer_amp->SetLineWidth(3.);
          hPcer_amp->SetLineStyle(2);
          hPcer_amp_cer->SetLineColor(kCyan+1);
          hPcer_amp_cer->SetLineWidth(2.);
          hPcer_amp_cer->SetLineStyle(2);
          hPpre_amp_prlo->SetLineColor(kGreen+1);
          hPpre_amp_prlo->SetLineWidth(2.);
          hPpre_amp_prlo->SetLineStyle(2);
          hPpre_amp_prhi->SetLineColor(kOrange);
          hPpre_amp_prhi->SetLineWidth(2.);
          hPpre_amp_prhi->SetLineStyle(2);
          hPpre_amp->SetLineColor(kBlue-3);
          hPpre_amp->SetLineWidth(3.);
          hPpre_amp->SetLineStyle(2);
          hPcal_amp_shlo->SetLineColor(kCyan+2);
          hPcal_amp_shlo->SetLineWidth(2.);
          hPcal_amp_shlo->SetLineStyle(2);
          hPcal_amp->SetLineColor(kOrange);
          hPcal_amp->SetLineWidth(2.);
          hPcal_amp->SetLineStyle(2);

       TCanvas *c1 = new TCanvas("c1", "c1", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg1 = new TLegend(0.7,0.6,.9,0.95);
       leg1->SetFillStyle(0);
       leg1->SetTextSize(0.045);
       leg1->SetBorderSize(0);
       leg1->SetFillColor(-1);
       leg1->SetTextColor(kBlack);
       leg1->AddEntry(hPcal_E_p,"3/4-ALL","");
       TLegend *leg2 = new TLegend(0.7,0.55,.9,0.9);
       leg2->SetFillStyle(0);
       leg2->SetTextSize(0.045);
       leg2->SetBorderSize(0);
       leg2->SetFillColor(-1);
       leg2->SetTextColor(kRed);
       leg2->AddEntry(hPcal_E_p_elreal,"ELREAL","");
       TLegend *leg3 = new TLegend(0.7,0.5,.9,0.85);
       leg3->SetFillStyle(0);
       leg3->SetTextSize(0.045);
       leg3->SetBorderSize(0);
       leg3->SetFillColor(-1);
       leg3->SetTextColor(kMagenta-8);
       leg3->AddEntry(hPcal_E_p_elclean,"ELCLEAN","");
       TLegend *leg4 = new TLegend(0.7,0.45,.9,0.8);
       leg4->SetFillStyle(0);
       leg4->SetTextSize(0.045);
       leg4->SetBorderSize(0);
       leg4->SetFillColor(-1);
       leg4->SetTextColor(kMagenta);
       leg4->AddEntry(hPcal_E_p_ello,"ELLO","");
       TLegend *leg5= new TLegend(0.7,0.4,.9,0.75);
       leg5->SetFillStyle(0);
       leg5->SetTextSize(0.045);
       leg5->SetBorderSize(0);
       leg5->SetFillColor(-1);
       leg5->SetTextColor(kGreen+1);
       leg5->AddEntry(hPcal_E_p_elhi,"ELHI","");
       TLegend *leg6 = new TLegend(0.7,0.35,.9,0.7);
       leg6->SetFillStyle(0);
       leg6->SetTextSize(0.045);
       leg6->SetBorderSize(0);
       leg6->SetFillColor(-1);
       leg6->SetTextColor(kOrange);
       leg6->AddEntry(hPcal_E_p_prlo,"PRLO","");
       TLegend *leg7 = new TLegend(0.7,0.3,.9,0.65);
       leg7->SetFillStyle(0);
       leg7->SetTextSize(0.045);
       leg7->SetBorderSize(0);
       leg7->SetFillColor(-1);
       leg7->SetTextColor(kBlue-3);
       leg7->AddEntry(hPcal_E_p_prhi,"PRHI","");
       TLegend *leg8 = new TLegend(0.7,0.25,.9,0.6);
       leg8->SetFillStyle(0);
       leg8->SetTextSize(0.045);
       leg8->SetBorderSize(0);
       leg8->SetFillColor(-1);
       leg8->SetTextColor(kTeal-4);
       leg8->AddEntry(hPcal_E_p_cer,"CER","");
       TLegend *leg9 = new TLegend(0.7,0.20,.9,0.55);
       leg9->SetFillStyle(0);
       leg9->SetTextSize(0.045);
       leg9->SetBorderSize(0);
       leg9->SetFillColor(-1);
       leg9->SetTextColor(kCyan+2);
       leg9->AddEntry(hPcal_E_p_shlo,"SHLO","");
       hPcal_E_p->SetStats(0);
       hPcal_E_p->Draw("hist");
       hPcal_E_p_elreal->Draw("hist same");
       hPcal_E_p_elclean->Draw("hist same");
       hPcal_E_p_ello->Draw("hist same");
       hPcal_E_p_elhi->Draw("hist same");
       hPcal_E_p_shlo->Draw("hist same");
       hPcal_E_p_prlo->Draw("hist same");
       hPcal_E_p_prhi->Draw("hist same");
       hPcal_E_p_cer->Draw("hist same");
       leg1->Draw();
       leg2->Draw();
       leg3->Draw();
       leg4->Draw();
       leg5->Draw();
       leg6->Draw();
       leg7->Draw();
       leg8->Draw();
       leg9->Draw();
       c1->SaveAs(Form("../PLOTS/HMS_%d_Total_E_p_with_PID_LEGS.pdf",RunNumber));

       TCanvas *c2 = new TCanvas("c2", "c2", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg10 = new TLegend(0.7,0.6,.9,0.95);
       leg10->SetFillStyle(0);
       leg10->SetTextSize(0.045);
       leg10->SetBorderSize(0);
       leg10->SetFillColor(-1);
       leg10->SetTextColor(kBlack);
       leg10->AddEntry(hPpre_E_p,"3/4-ALL","");
       TLegend *leg11 = new TLegend(0.7,0.55,.9,0.9);
       leg11->SetFillStyle(0);
       leg11->SetTextSize(0.045);
       leg11->SetBorderSize(0);
       leg11->SetFillColor(-1);
       leg11->SetTextColor(kRed);
       leg11->AddEntry(hPpre_E_p_elreal,"ELREAL","");
       TLegend *leg12 = new TLegend(0.7,0.5,.9,0.85);
       leg12->SetFillStyle(0);
       leg12->SetTextSize(0.045);
       leg12->SetBorderSize(0);
       leg12->SetFillColor(-1);
       leg12->SetTextColor(kMagenta-8);
       leg12->AddEntry(hPpre_E_p_elclean,"ELCLEAN","");
       TLegend *leg13 = new TLegend(0.7,0.45,.9,0.8);
       leg13->SetFillStyle(0);
       leg13->SetTextSize(0.045);
       leg13->SetBorderSize(0);
       leg13->SetFillColor(-1);
       leg13->SetTextColor(kMagenta);
       leg13->AddEntry(hPpre_E_p_ello,"ELLO","");
       TLegend *leg14= new TLegend(0.7,0.4,.9,0.75);
       leg14->SetFillStyle(0);
       leg14->SetTextSize(0.045);
       leg14->SetBorderSize(0);
       leg14->SetFillColor(-1);
       leg14->SetTextColor(kGreen+1);
       leg14->AddEntry(hPpre_E_p_elhi,"ELHI","");
       TLegend *leg15 = new TLegend(0.7,0.35,.9,0.7);
       leg15->SetFillStyle(0);
       leg15->SetTextSize(0.045);
       leg15->SetBorderSize(0);
       leg15->SetFillColor(-1);
       leg15->SetTextColor(kOrange);
       leg15->AddEntry(hPpre_E_p_prlo,"PRLO","");
       TLegend *leg16 = new TLegend(0.7,0.3,.9,0.65);
       leg16->SetFillStyle(0);
       leg16->SetTextSize(0.045);
       leg16->SetBorderSize(0);
       leg16->SetFillColor(-1);
       leg16->SetTextColor(kBlue-3);
       leg16->AddEntry(hPpre_E_p_prhi,"PRHI","");
       TLegend *leg17 = new TLegend(0.7,0.25,.9,0.6);
       leg17->SetFillStyle(0);
       leg17->SetTextSize(0.045);
       leg17->SetBorderSize(0);
       leg17->SetFillColor(-1);
       leg17->SetTextColor(kTeal-4);
       leg17->AddEntry(hPpre_E_p_cer,"CER","");
       TLegend *leg18 = new TLegend(0.7,0.20,.9,0.55);
       leg18->SetFillStyle(0);
       leg18->SetTextSize(0.045);
       leg18->SetBorderSize(0);
       leg18->SetFillColor(-1);
       leg18->SetTextColor(kCyan+2);
       leg18->AddEntry(hPpre_E_p_shlo,"SHLO","");
       hPpre_E_p->SetStats(0);
       hPpre_E_p->Draw("hist");
       hPpre_E_p_elreal->Draw("hist same");
       hPpre_E_p_elclean->Draw("hist same");
       hPpre_E_p_ello->Draw("hist same");
       hPpre_E_p_elhi->Draw("hist same");
       hPpre_E_p_prlo->Draw("hist same");
       hPpre_E_p_shlo->Draw("hist same");
       hPpre_E_p_prhi->Draw("hist same");
       hPpre_E_p_cer->Draw("hist same");
       leg10->Draw();
       leg11->Draw();
       leg12->Draw();
       leg13->Draw();
       leg14->Draw();
       leg15->Draw();
       leg16->Draw();
       leg17->Draw();
       leg18->Draw();
       c2->SaveAs(Form("../PLOTS/HMS_%d_PreSh_E_p_with_PID_LEGS.pdf",RunNumber));


       TCanvas *c3 = new TCanvas("c3", "c3", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg19 = new TLegend(0.7,0.6,.9,0.95);
       leg19->SetFillStyle(0);
       leg19->SetTextSize(0.045);
       leg19->SetBorderSize(0);
       leg19->SetFillColor(-1);
       leg19->SetTextColor(kMagenta);
       leg19->AddEntry(hPcer,"3/4-ALL","");
       hPcer->SetStats(0);
       hPcer->Draw("hist");
       TLegend *leg20 = new TLegend(0.7,0.55,.9,0.9);
       leg20->SetFillStyle(0);
       leg20->SetTextSize(0.045);
       leg20->SetBorderSize(0);
       leg20->SetFillColor(-1);
       leg20->SetTextColor(kCyan+1);
       leg20->AddEntry(hPcer_cer,"CER","");
       hPcer_cer->Draw("hist same");
       leg19->Draw();
       leg20->Draw();
       c3->SaveAs(Form("../PLOTS/HMS_%d_CER_npe_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c4 = new TCanvas("c4", "c4", 1200, 1200);
       c4->Divide(3,3);
       c4->cd(1);
       gPad->SetLogz();
       TLegend *leg21 = new TLegend(0.15,0.75,.35,0.9);
       leg21->SetFillStyle(0);
       leg21->SetTextSize(0.045);
       leg21->SetBorderSize(0);
       leg21->SetFillColor(-1);
       leg21->SetTextColor(kBlack);
       leg21->AddEntry(hPpre_vs_cal,"3/4-ALL","");
       hPpre_vs_cal->SetStats(0);
       hPpre_vs_cal->Draw("colz");
       leg21->Draw();
       c4->cd(2);
       gPad->SetLogz();
       TLegend *leg22 = new TLegend(0.15,0.75,.35,0.9);
       leg22->SetFillStyle(0);
       leg22->SetTextSize(0.045);
       leg22->SetBorderSize(0);
       leg22->SetFillColor(-1);
       leg22->SetTextColor(kRed);
       leg22->AddEntry(hPpre_vs_cal_elreal,"ELREAL","");
       hPpre_vs_cal_elreal->SetStats(0);
       hPpre_vs_cal_elreal->Draw("colz");
       leg22->Draw();
       c4->cd(3);
       gPad->SetLogz();
       TLegend *leg23 = new TLegend(0.15,0.75,.35,0.9);
       leg23->SetFillStyle(0);
       leg23->SetTextSize(0.045);
       leg23->SetBorderSize(0);
       leg23->SetFillColor(-1);
       leg23->SetTextColor(kMagenta-8);
       leg23->AddEntry(hPpre_vs_cal_elclean,"ELCLEAN","");
       hPpre_vs_cal_elclean->SetStats(0);
       hPpre_vs_cal_elclean->Draw("colz");
       leg23->Draw();
       c4->cd(4);
       gPad->SetLogz();
       TLegend *leg24 = new TLegend(0.15,0.75,.35,0.9);
       leg24->SetFillStyle(0);
       leg24->SetTextSize(0.045);
       leg24->SetBorderSize(0);
       leg24->SetFillColor(-1);
       leg24->SetTextColor(kMagenta);
       leg24->AddEntry(hPpre_vs_cal_ello,"ELLO","");
       hPpre_vs_cal_ello->SetStats(0);
       hPpre_vs_cal_ello->Draw("colz");
       leg24->Draw();
       c4->cd(5);
       gPad->SetLogz();
       TLegend *leg25 = new TLegend(0.15,0.75,.35,0.9);
       leg25->SetFillStyle(0);
       leg25->SetTextSize(0.045);
       leg25->SetBorderSize(0);
       leg25->SetFillColor(-1);
       leg25->SetTextColor(kGreen+1);
       leg25->AddEntry(hPpre_vs_cal_elhi,"ELHI","");
       hPpre_vs_cal_elhi->SetStats(0);
       hPpre_vs_cal_elhi->Draw("colz");
       leg25->Draw();
       c4->cd(6);
       gPad->SetLogz();
       TLegend *leg26 = new TLegend(0.15,0.75,.35,0.9);
       leg26->SetFillStyle(0);
       leg26->SetTextSize(0.045);
       leg26->SetBorderSize(0);
       leg26->SetFillColor(-1);
       leg26->SetTextColor(kOrange);
       leg26->AddEntry(hPpre_vs_cal_prlo,"PRLO","");
       hPpre_vs_cal_prlo->SetStats(0);
       hPpre_vs_cal_prlo->Draw("colz");
       leg26->Draw();
       c4->cd(7);
       gPad->SetLogz();
       TLegend *leg27 = new TLegend(0.15,0.75,.35,0.9);
       leg27->SetFillStyle(0);
       leg27->SetTextSize(0.045);
       leg27->SetBorderSize(0);
       leg27->SetFillColor(-1);
       leg27->SetTextColor(kBlue-3);
       leg27->AddEntry(hPpre_vs_cal_prhi,"PRHI","");
       hPpre_vs_cal_prhi->SetStats(0);
       hPpre_vs_cal_prhi->Draw("colz");
       leg27->Draw();
       c4->cd(8);
       gPad->SetLogz();
       TLegend *leg28 = new TLegend(0.15,0.75,.35,0.9);
       leg28->SetFillStyle(0);
       leg28->SetTextSize(0.045);
       leg28->SetBorderSize(0);
       leg28->SetFillColor(-1);
       leg28->SetTextColor(kTeal-4);
       leg28->AddEntry(hPpre_vs_cal_cer,"CER","");
       hPpre_vs_cal_cer->SetStats(0);
       hPpre_vs_cal_cer->Draw("colz");
       leg28->Draw();
       c4->cd(9);
       gPad->SetLogz();
       TLegend *leg29 = new TLegend(0.15,0.75,.35,0.9);
       leg29->SetFillStyle(0);
       leg29->SetTextSize(0.045);
       leg29->SetBorderSize(0);
       leg29->SetFillColor(-1);
       leg29->SetTextColor(kCyan+2);
       leg29->AddEntry(hPpre_vs_cal_shlo,"SHLO","");
       hPpre_vs_cal_shlo->SetStats(0);
       hPpre_vs_cal_shlo->Draw("colz");
       leg29->Draw();
       c4->SaveAs(Form("../PLOTS/HMS_%d_PreSh_vs_Total_E_p_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c5 = new TCanvas("c5", "c5", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg30 = new TLegend(0.7,0.6,.9,0.95);
       leg30->SetFillStyle(0);
       leg30->SetTextSize(0.045);
       leg30->SetBorderSize(0);
       leg30->SetFillColor(-1);
       leg30->SetTextColor(kMagenta);
       leg30->AddEntry(hPcer_amp,"3/4-ALL","");
       hPcer_amp->SetStats(0);
       hPcer_amp->Draw("hist");
       TLegend *leg31 = new TLegend(0.7,0.55,.9,0.9);
       leg31->SetFillStyle(0);
       leg31->SetTextSize(0.045);
       leg31->SetBorderSize(0);
       leg31->SetFillColor(-1);
       leg31->SetTextColor(kCyan+1);
       leg31->AddEntry(hPcer_amp_cer,"CER","");
       hPcer_amp_cer->Draw("hist same");
       leg30->Draw();
       leg31->Draw();
       c5->SaveAs(Form("../PLOTS/HMS_%d_CER_PulseAmp_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c6 = new TCanvas("c6", "c6", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg32 = new TLegend(0.7,0.6,.9,0.95);
       leg32->SetFillStyle(0);
       leg32->SetTextSize(0.045);
       leg32->SetBorderSize(0);
       leg32->SetFillColor(-1);
       leg32->SetTextColor(kBlue-3);
       leg32->AddEntry(hPpre_amp,"3/4-ALL","");
       hPpre_amp->SetStats(0);
       hPpre_amp->Draw("hist");
       TLegend *leg33 = new TLegend(0.7,0.55,.9,0.9);
       leg33->SetFillStyle(0);
       leg33->SetTextSize(0.045);
       leg33->SetBorderSize(0);
       leg33->SetFillColor(-1);
       leg33->SetTextColor(kGreen+1);
       leg33->AddEntry(hPpre_amp_prlo,"PRLO","");
       hPpre_amp_prlo->Draw("hist same");
       TLegend *leg34 = new TLegend(0.7,0.5,.9,0.85);
       leg34->SetFillStyle(0);
       leg34->SetTextSize(0.045);
       leg34->SetBorderSize(0);
       leg34->SetFillColor(-1);
       leg34->SetTextColor(kOrange);
       leg34->AddEntry(hPpre_amp_prhi,"PRHI","");
       hPpre_amp_prhi->Draw("hist same");
       leg32->Draw();
       leg33->Draw();
       leg34->Draw();
       c6->SaveAs(Form("../PLOTS/HMS_%d_PreSh_PulseAmp_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c7 = new TCanvas("c7", "c7", 2000, 1200);
       c7->Divide(2,2);
       c7->cd(1);
       gPad->SetLogz();
       TLegend *leg36 = new TLegend(0.15,0.75,.35,0.9);
       leg36->SetFillStyle(0);
       leg36->SetTextSize(0.045);
       leg36->SetBorderSize(0);
       leg36->SetFillColor(-1);
       leg36->SetTextColor(kBlack);
       leg36->AddEntry(hPpre_amp_vs_cal,"3/4-ALL","");
       hPpre_amp_vs_cal->SetStats(0);
       hPpre_amp_vs_cal->Draw("colz");
       leg36->Draw();
       c7->cd(2);
       gPad->SetLogz();
       TLegend *leg37 = new TLegend(0.15,0.75,.35,0.9);
       leg37->SetFillStyle(0);
       leg37->SetTextSize(0.045);
       leg37->SetBorderSize(0);
       leg37->SetFillColor(-1);
       leg37->SetTextColor(kOrange);
       leg37->AddEntry(hPpre_amp_vs_cal_prlo,"PRLO","");
       hPpre_amp_vs_cal_prlo->SetStats(0);
       hPpre_amp_vs_cal_prlo->Draw("colz");
       leg37->Draw();
       c7->cd(3);
       gPad->SetLogz();
       TLegend *leg38 = new TLegend(0.15,0.75,.35,0.9);
       leg38->SetFillStyle(0);
       leg38->SetTextSize(0.045);
       leg38->SetBorderSize(0);
       leg38->SetFillColor(-1);
       leg38->SetTextColor(kBlue-3);
       leg38->AddEntry(hPpre_amp_vs_cal_prhi,"PRHI","");
       hPpre_amp_vs_cal_prhi->SetStats(0);
       hPpre_amp_vs_cal_prhi->Draw("colz");
       leg38->Draw();
       c7->SaveAs(Form("../PLOTS/HMS_%d_PreSh_PulseAmp_vs_Total_E_p_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c8 = new TCanvas("c8", "c8", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg35 = new TLegend(0.7,0.6,.9,0.95);
       leg35->SetFillStyle(0);
       leg35->SetTextSize(0.045);
       leg35->SetBorderSize(0);
       leg35->SetFillColor(-1);
       leg35->SetTextColor(kBlue-3);
       leg35->AddEntry(hPcal_amp,"3/4-ALL","");
       hPcal_amp->SetStats(0);
       hPcal_amp->Draw("hist");
       TLegend *leg39 = new TLegend(0.7,0.55,.9,0.9);
       leg39->SetFillStyle(0);
       leg39->SetTextSize(0.045);
       leg39->SetBorderSize(0);
       leg39->SetFillColor(-1);
       leg39->SetTextColor(kGreen+1);
       leg39->AddEntry(hPcal_amp_shlo,"SHLO","");
       hPcal_amp_shlo->Draw("hist same");
       leg35->Draw();
       leg39->Draw();
       c8->SaveAs(Form("../PLOTS/HMS_%d_Sh_PulseAmp_with_PID_LEGS.pdf",RunNumber));

       TCanvas *c9 = new TCanvas("c9", "c9", 2000, 1200);
       c9->Divide(2,2);
       c9->cd(1);
       gPad->SetLogz();
       TLegend *leg40 = new TLegend(0.15,0.75,.35,0.9);
       leg40->SetFillStyle(0);
       leg40->SetTextSize(0.045);
       leg40->SetBorderSize(0);
       leg40->SetFillColor(-1);
       leg40->SetTextColor(kBlack);
       leg40->AddEntry(hPsh_amp_vs_cal,"3/4-ALL","");
       hPsh_amp_vs_cal->SetStats(0);
       hPsh_amp_vs_cal->Draw("colz");
       leg40->Draw();
       c9->cd(2);
       gPad->SetLogz();
       TLegend *leg41 = new TLegend(0.15,0.75,.35,0.9);
       leg41->SetFillStyle(0);
       leg41->SetTextSize(0.045);
       leg41->SetBorderSize(0);
       leg41->SetFillColor(-1);
       leg41->SetTextColor(kOrange);
       leg41->AddEntry(hPsh_amp_vs_cal_shlo,"SHLO","");
       hPsh_amp_vs_cal_shlo->SetStats(0);
       hPsh_amp_vs_cal_shlo->Draw("colz");
       leg41->Draw();
       c9->SaveAs(Form("../PLOTS/HMS_%d_Sh_PulseAmp_vs_Total_E_p_with_PID_LEGS.pdf",RunNumber));
}

