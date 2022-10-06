#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph2DErrors.h"
#include "TLegend.h"
#include <TStyle.h>
#include <TROOT.h>



void sDeltaScan(Int_t runNum, Int_t nEvts=-1){
    
    TFile* fdata = new TFile(Form("../../ROOTfiles/COIN/HeeP/coin_replay_production_%d_%d.root",runNum,nEvts));
    TTree *tdata = (TTree*) fdata->Get("T");
    
    double sdelta; //DATA SHMS reconstructed 100*(p - pc)/pc with pc = central SHMS mnuentum
    double syptar; //DATA SHMS reconstructed target dy/dz vertical slope
    double sxptar; //DATA SHMS reconstructed target dx/dz vertical slope
    double sytar; //DATA SHMS reconstructed target y
    double hdelta; //DATA SHMS reconstructed 100*(p - pc)/pc with pc = central SHMS mnuentum
    double hyptar; //DATA SHMS reconstructed target dy/dz vertical slope
    double hxptar; //DATA SHMS reconstructed target dx/dz vertical slope
    double hytar; //DATA SHMS reconstructed target y
    double W;
    double ngcer;
    double ecal;
    double pgoodstart;
    double pgoodscinhit;
    double emiss;
    double pmiss;
    double cointime;
    double petottracknorm;
    
    tdata->SetBranchAddress("CTime.epCoinTime_ROC1",&cointime);
    tdata->SetBranchAddress("P.hod.goodstarttime", &pgoodstart);
    tdata->SetBranchAddress("P.hod.goodscinhit", &pgoodscinhit);
    tdata->SetBranchAddress("H.kin.secondary.emiss",&emiss);
    tdata->SetBranchAddress("P.cal.etottracknorm",&petottracknorm);
    tdata->SetBranchAddress("P.ngcer.npeSum",&ngcer);
    tdata->SetBranchAddress("P.gtr.dp", &sdelta);
    tdata->SetBranchAddress("P.gtr.th", &sxptar);
    tdata->SetBranchAddress("P.gtr.ph", &syptar);
    tdata->SetBranchAddress("P.gtr.y", &sytar);
    tdata->SetBranchAddress("H.gtr.dp", &hdelta);
    tdata->SetBranchAddress("H.gtr.th", &hxptar);
    tdata->SetBranchAddress("H.gtr.ph", &hyptar);
    tdata->SetBranchAddress("H.gtr.y", &hytar);
    tdata->SetBranchAddress("P.kin.primary.W", &W);
        
    //HISTOGRAMS
    TH1F *hW = new TH1F("W", "W", 225, 0.25, 2.5);
    hW->GetXaxis()->SetTitle("W [GeV]");
    hW->GetYaxis()->SetTitle("counts");
    TH1F *hcointime = new TH1F("hcointime", "Coincidence Time",200, 60., 100.);
    hcointime->SetTitle("Coincidence Time");
    hcointime->GetXaxis()->SetTitle("Coin Time (ns)");
    hcointime->GetYaxis()->SetTitle("counts");
    TH1F *hShmsDelta = new TH1F("SHMS delta", "SHMS delta", 100, -30, 40);
    TH1F *hShmsXptar = new TH1F("SHMS XPTAR", "SHMS XPTAR", 100, -.2, .2);
    TH1F *hShmsYptar = new TH1F("SHMS YPTAR", "SHMS YPTAR", 100, -.2, .2);
    TH1F *hShmsYtar = new TH1F("SHMS YTAR", "SHMS YTAR", 100, -10., 10.);
    TH1F *hHmsDelta = new TH1F("HMS delta", "HMS delta", 100, -20, 20);
    TH1F *hHmsXptar = new TH1F("HMS XPTAR", "HMS XPTAR", 100, -.2, .2);
    TH1F *hHmsYptar = new TH1F("HMS YPTAR", "HMS YPTAR", 100, -.2, .2);
    TH1F *hHmsYtar = new TH1F("HMS YTAR", "HMS YTAR", 100, -10., 10.);
    
   hShmsDelta->Sumw2(); 
   hShmsXptar->Sumw2(); 
   hShmsYptar->Sumw2(); 
   hShmsYtar->Sumw2(); 
   hHmsDelta->Sumw2(); 
   hHmsXptar->Sumw2(); 
   hHmsYptar->Sumw2(); 
   hHmsYtar->Sumw2(); 
   hW->Sumw2();

    Long64_t nentries_data = tdata->GetEntries();
    for (int j = 0; j < nentries_data; j++) {
        tdata->GetEntry(j);
        if(abs(hdelta)<8.){
            hW->Fill(W);
            hShmsXptar->Fill(sxptar);
            hShmsDelta->Fill(sdelta);
            hShmsYptar->Fill(syptar);
            hShmsYtar->Fill(sytar);
            hHmsXptar->Fill(hxptar);
            hHmsDelta->Fill(hdelta);
            hHmsYptar->Fill(hyptar);
            hHmsYtar->Fill(hytar);
            hcointime->Fill(cointime);
        }
    }
    double elasCount = hShmsXptar->Integral(hShmsXptar->GetXaxis()->FindBin(-1.), hShmsXptar->GetXaxis()->FindBin(1.));
    cout<<"# of good events:"<<" "<<elasCount<<" "<<endl;
    
    TCanvas *c1 = new TCanvas("c1", "HMS target variables", 1200, 1200);
    c1->Divide(2,2);
    c1->cd(1);
    hHmsDelta->SetMarkerColor(kGreen+1);
    hHmsDelta->SetMarkerStyle(kFullCircle); 
    hHmsDelta->SetMarkerSize(0.5);
    hHmsDelta->SetMinimum(0);
    hHmsDelta->SetStats(0);
    hHmsDelta->Draw("hist e0 x0");
    c1->cd(2);
    hHmsXptar->SetMarkerColor(kGreen+1);
    hHmsXptar->SetMarkerStyle(kFullCircle); 
    hHmsXptar->SetMarkerSize(0.5);
    hHmsXptar->SetMinimum(0);
    hHmsXptar->SetStats(0);
    hHmsXptar->Draw("hist e0 x0");
    c1->cd(3);
    hHmsYptar->SetMarkerColor(kGreen+1);
    hHmsYptar->SetMarkerStyle(kFullCircle); 
    hHmsYptar->SetMarkerSize(0.5);
    hHmsYptar->SetMinimum(0);
    hHmsYptar->SetStats(0);
    hHmsYptar->Draw("hist e0 x0");
    c1->cd(4);
    hHmsYtar->SetMarkerColor(kGreen+1);
    hHmsYtar->SetMarkerStyle(kFullCircle); 
    hHmsYtar->SetMarkerSize(0.5);
    hHmsYtar->SetMinimum(0);
    hHmsYtar->SetStats(0);
    hHmsYtar->Draw("hist e0 x0");
    
    TCanvas *c2 = new TCanvas("c2", "SHMS target variables", 1200, 1200);
    c2->Divide(2,2);
    c2->cd(1);
    hShmsDelta->SetMarkerColor(kGreen+1);
    hShmsDelta->SetMarkerStyle(kFullCircle); 
    hShmsDelta->SetMarkerSize(0.5);
    hShmsDelta->SetMinimum(0);
    hShmsDelta->SetStats(0);
    hShmsDelta->Draw("hist e0 x0");
    c2->cd(2);
    hShmsXptar->SetMarkerColor(kGreen+1);
    hShmsXptar->SetMarkerStyle(kFullCircle); 
    hShmsXptar->SetMarkerSize(0.5);
    hShmsXptar->SetMinimum(0);
    hShmsXptar->SetStats(0);
    hShmsXptar->Draw("hist e0 x0");
    c2->cd(3);
    hShmsYptar->SetMarkerColor(kGreen+1);
    hShmsYptar->SetMarkerStyle(kFullCircle); 
    hShmsYptar->SetMarkerSize(0.5);
    hShmsYptar->SetMinimum(0);
    hShmsYptar->Draw("hist e0 x0");
    hShmsYptar->SetStats(0);
    c2->cd(4);
    hShmsYtar->SetMarkerColor(kGreen+1);
    hShmsYtar->SetMarkerStyle(kFullCircle); 
    hShmsYtar->SetMarkerSize(0.5);
    hShmsYtar->SetMinimum(0);
    hShmsYtar->SetStats(0);
    hShmsYtar->Draw("hist e0 x0");
    
    TCanvas *c3 = new TCanvas("c3", "W", 1200, 600);
    c3->cd();
    hW->SetMarkerColor(kGreen+1);
    hW->SetMarkerStyle(kFullCircle); 
    hW->SetMarkerSize(0.5);
    hW->SetMinimum(0);
    hW->SetStats(0);
    hW->Draw("hist e0 x0");
}





