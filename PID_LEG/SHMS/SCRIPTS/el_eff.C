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

void el_eff(int RunNumber=0){
   if (RunNumber == 0){
     cout<<"enter a run number:";
     cin >> RunNumber;
     if(RunNumber <= 0)
     return;
     }

  TString filename = Form("/work/hallc/jpsi-007/bduran/ROOTfiles/shms_replay_production_%d_1000000.root", RunNumber);
  //TString filename = Form("/work/hallc/xem2/bduran/ROOTfiles/SHMS/PRODUCTION/shms_replay_production_%d_1000000.root", RunNumber);
  TFile *f = new TFile(filename, "READ");
  TTree *t = (TTree*) f->Get("T");


  double etotnorm;
	double etottracknorm;
	double eprtracknorm;
  double ngcer;
  double delta;
  double ello;
  double ellolo;
  double elhi;
  double elreal;
  double elclean;
  double prlo;
  double prhi;
  double shlo;
  double cer;
  double cer_amp;
  double cer_mult;
  double pre_amp;
  double pre_mult;
  double sh_amp;
  double sh_mult;
  double edtm;
   

	t->SetBranchAddress("P.cal.etottracknorm",&etottracknorm);
	t->SetBranchAddress("P.cal.eprtracknorm",&eprtracknorm);
  t->SetBranchAddress("P.ngcer.npeSum",&ngcer);
  t->SetBranchAddress("P.gtr.dp", &delta);
  t->SetBranchAddress("T.shms.pEL_LO_tdcTimeRaw", &ello);
  t->SetBranchAddress("T.shms.pEL_LO_LO_tdcTimeRaw", &ellolo);
  t->SetBranchAddress("T.shms.pEL_HI_tdcTimeRaw", &elhi);
  t->SetBranchAddress("T.shms.pEL_REAL_tdcTimeRaw", &elreal);
  t->SetBranchAddress("T.shms.pEL_CLEAN_tdcTimeRaw", &elclean);
  t->SetBranchAddress("T.shms.pPRLO_tdcTimeRaw", &prlo);
  t->SetBranchAddress("T.shms.pPRHI_tdcTimeRaw", &prhi);
  //t->SetBranchAddress("T.shms.pSHWRLO_tdcTimeRaw", &shlo);
  t->SetBranchAddress("T.shms.pNGCER_tdcTimeRaw", &cer);
  t->SetBranchAddress("T.shms.pNGCER_adcPulseAmp", &cer_amp);
  t->SetBranchAddress("T.shms.pNGCER_adcMultiplicity", &cer_mult);
  t->SetBranchAddress("T.shms.pPSHWR_adcPulseAmp", &pre_amp);
  t->SetBranchAddress("T.shms.pPSHWR_adcMultiplicity", &pre_mult);
  //t->SetBranchAddress("T.shms.pSHWR_adcPulseAmp", &sh_amp);
  //t->SetBranchAddress("T.shms.pSHWR_adcMultiplicity", &sh_mult);
  t->SetBranchAddress("T.shms.pEDTM_tdcTime", &edtm);

  
  TH1F *hPcal_E_p  = new TH1F("total calo E/p","SHMS Calorimeter Total E/P for Different PID Legs", 100, 0.0, 2.0);
  hPcal_E_p->GetXaxis()->SetTitle("etottracknorm E/p");
  hPcal_E_p->GetYaxis()->SetTitle("counts");
  TH1F *hPcal_E_p_elreal  = new TH1F("total calo E/p ELREAL","SHMS Calorimeter Total E/P ELREAL", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_elclean  = new TH1F("total calo E/p ELCLEAN","SHMS Calorimeter Total E/P ELCLEAN", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_ello  = new TH1F("total calo E/p ELLO","SHMS Calorimeter Total E/P ELLO", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_ellolo  = new TH1F("total calo E/p ELLOLO","SHMS Calorimeter Total E/P ELLOLO", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_elhi  = new TH1F("total calo E/p ELHI","SHMS Calorimeter Total E/P ELHI", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_prlo  = new TH1F("total calo E/p PRLO","SHMS Calorimeter Total E/P PRLO", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_prhi  = new TH1F("total calo E/p PRHI","SHMS Calorimeter Total E/P PRHI", 100, 0.0, 2.0);
  //TH1F *hPcal_E_p_shlo  = new TH1F("total calo E/p SHLO","SHMS Calorimeter Total E/P SHLO", 100, 0.0, 2.0);
  TH1F *hPcal_E_p_cer  = new TH1F("total calo E/p CER","SHMS Calorimeter Total E/P CER", 100, 0.0, 2.0);
  TH1F *hPsh_E_p  = new TH1F("shower E/p","SHMS Shower E/P", 100, 0.0, 2.0);
  TH1F *hPngcer  = new TH1F("NGCER npe","NGCER NPE SUM", 100, 0.0, 30.0);
  hPngcer->GetXaxis()->SetTitle("npe");
  hPngcer->GetYaxis()->SetTitle("counts");
  TH1F *hPngcer_cer  = new TH1F("NGCER npe CER","NGCER NPE SUM CER", 100, 0.0, 30.0);
  TH1F *hPngcer_amp  = new TH1F("NGCER amp","NGCER Pulse Amplitude CER", 100, 0.0, 600.0);
  hPngcer_amp->GetXaxis()->SetTitle("Pulse Amplitude (mV)");
  hPngcer_amp->GetYaxis()->SetTitle("counts");
  TH1F *hPngcer_amp_cer  = new TH1F("NGCER amp CER","", 100, 0.0, 600.0);
  TH1F *hPpre_amp  = new TH1F("pre amp","Preshower Pulse Amplitude", 100, 0.0, 600.0);
  hPpre_amp->GetXaxis()->SetTitle("Pulse Amplitude (mV)");
  hPpre_amp->GetYaxis()->SetTitle("counts");
  TH1F *hPpre_amp_prlo  = new TH1F("pre amp PRLO","", 100, 0.0, 600.0);
  TH1F *hPpre_amp_prhi  = new TH1F("pre amp PRHI","", 100, 0.0, 600.0);
  TH1F *hPpre_E_p  = new TH1F("preshower E/p","SHMS Preshower E/p for Different PID legs", 100, 0.0, 1.0);
  hPpre_E_p->GetXaxis()->SetTitle("preshower E/p");
  hPpre_E_p->GetYaxis()->SetTitle("counts");
  TH1F *hPpre_E_p_elreal  = new TH1F("preshower E/p ELREAL","SHMS preshower E/P ELREAL", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_elclean  = new TH1F("preshower E/p ELCLEAN","SHMS preshower E/P ELCLEAN", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_ello  = new TH1F("preshower E/p ELLO","SHMS preshower E/P ELLO", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_ellolo  = new TH1F("preshower E/p ELLOLO","SHMS preshower E/P ELLOLO", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_elhi  = new TH1F("preshower E/p ELHI","SHMS preshower E/P ELHI", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_prlo  = new TH1F("preshower E/p PRLO","SHMS preshower E/P PRLO", 100, 0.0, 1.0);
  TH1F *hPpre_E_p_prhi  = new TH1F("preshower E/p PRHI","SHMS preshower E/P PRHI", 100, 0.0, 1.0);
  //TH1F *hPcal_E_p_shlo  = new TH1F("total calo E/p SHLO","SHMS Calorimeter Total E/P SHLO", 100, 0.0, 2.0);
  TH1F *hPpre_E_p_cer  = new TH1F("preshower E/p CER","SHMS preshower E/P CER", 100, 0.0, 1.0);
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
  


  Long64_t nentries = t->GetEntries();
    cout<<"num of entries: "<<nentries<<endl;

    for (Long64_t i=0; i<nentries; i++){
        t->GetEntry(i);
        if(delta > -10. && delta < 22.){
          //Choose electrons with NGCER for the calo plots
          if(ngcer > 3. && etottracknorm > 0.7){
          hPcal_E_p->Fill(etottracknorm);
          hPpre_E_p->Fill(eprtracknorm);
          hPpre_vs_cal->Fill(etottracknorm, eprtracknorm);
          //Check the impact of different PID legs for the electrons  
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
    //      if(shlo>0.){
    //       hPcal_E_p_shlo->Fill(etottracknorm);}
            if(cer>0.){
              hPcal_E_p_cer->Fill(etottracknorm);
              hPpre_E_p_cer->Fill(eprtracknorm);
              hPpre_vs_cal_cer->Fill(etottracknorm, eprtracknorm);
            }
            if(pre_mult>0){
              hPpre_amp->Fill(pre_amp);
              if(prlo>0){
                hPpre_amp_prlo->Fill(pre_amp);
          }
              if(prhi>0){
                hPpre_amp_prhi->Fill(pre_amp);
          }
        }
    }
        //Choose electrons with calorimeter for the Cherenkov plots
          if(etottracknorm > 0.7){
            hPngcer->Fill(ngcer);
            if(cer>0){
              hPngcer_cer->Fill(ngcer);}
            if(cer_mult>0){
              hPngcer_amp_cer->Fill(cer_amp);
              if(cer>0){
              hPngcer_amp_cer->Fill(cer_amp);}
          }
        }
          }
}
           
          double tote = hPcal_E_p->GetEntries();
          double tote_elreal = hPcal_E_p_elreal->GetEntries();
          double tote_elclean = hPcal_E_p_elclean->GetEntries();
          double tote_ello = hPcal_E_p_ello->GetEntries();
          double tote_elhi = hPcal_E_p_elhi->GetEntries();
          double tote_prlo = hPcal_E_p_prlo->GetEntries();
          double tote_prhi = hPcal_E_p_prhi->GetEntries();
          
          cout<<"Total Number of Electrons:"<<tote<<" "<<"Total Number of Electrons with ELREAL:"<<tote_elreal<<" "<<"ELREAL Efficiency:"<<tote_elreal/tote<<endl;
          cout<<"Total Number of Electrons:"<<tote<<" "<<"Total Number of Electrons with ELCLEAN:"<<tote_elclean<<" "<<"ELCLEAN Efficiency:"<<tote_elclean/tote<<endl;
          cout<<"Total Number of Electrons:"<<tote<<" "<<"Total Number of Electrons with ELLO:"<<tote_ello<<" "<<"ELLO Efficiency:"<<tote_ello/tote<<endl;
          cout<<"Total Number of Electrons:"<<tote<<" "<<"Total Number of Electrons with ELHI:"<<tote_elhi<<" "<<"ELHI Efficiency:"<<tote_elhi/tote<<endl;
          cout<<"Total Number of Electrons:"<<tote<<" "<<"Total Number of Electrons with PRLO:"<<tote_prlo<<" "<<"PRLO Efficiency:"<<tote_prlo/tote<<endl;
          cout<<"Total Number of Electrons:"<<tote<<" "<<"Total Number of Electrons with PRHI:"<<tote_prhi<<" "<<"PRHI Efficiency:"<<tote_prhi/tote<<endl;
          
}

