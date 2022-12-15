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



void hmsElas(Int_t runNum, Int_t nEvts=-1){
//void coinElas(){
    
//   TFile* fdata = new TFile(Form("../../ROOTfiles/COIN/HeeP/coin_elas_sum.root"));
  // TFile* fdata = new TFile(Form("../../ROOTfiles/HMS/HeeP/hms_replay_production_%d_%d.root",runNum,nEvts));
 TFile* fdata = new TFile(Form("../../ROOTfiles/HMS/hms50k/hms_replay_production_%d_%d.root",runNum,nEvts));
    TTree *tdata = (TTree*) fdata->Get("T");
    
    double hdelta; //DATA HMS reconstructed 100*(p - pc)/pc with pc = central SHMS mnuentum
    double hyptar; //DATA HMS reconstructed target dy/dz vertical slope
    double hxptar; //DATA HMS reconstructed target dx/dz vertical slope
    double hytar; //DATA HMS reconstructed target y
    double W;
    double hcer;
    double hecal;
    double hetottracknorm;
    
    tdata->SetBranchAddress("H.cal.etottracknorm",&hetottracknorm);
    tdata->SetBranchAddress("H.cer.npeSum",&hcer);
    tdata->SetBranchAddress("H.gtr.dp", &hdelta);
    tdata->SetBranchAddress("H.gtr.th", &hxptar);
    tdata->SetBranchAddress("H.gtr.ph", &hyptar);
    tdata->SetBranchAddress("H.gtr.y", &hytar); 
    tdata->SetBranchAddress("H.kin.W", &W);
        
    //HISTOGRAMS
    TH1F *hW = new TH1F("W", "W", 100, 0., 2.);
    hW->GetXaxis()->SetTitle("W [GeV]");
    hW->GetYaxis()->SetTitle("counts");
    TH1F *hhmsDelta = new TH1F("HMS delta", "HMS delta", 100, -30, 40);
    TH1F *hhmsXptar = new TH1F("HMS XPTAR", "HMS XPTAR", 100, -.2, .2);
    TH1F *hhmsYptar = new TH1F("HMS YPTAR", "HMS YPTAR", 100, -.2, .2);
    TH1F *hhmsYtar = new TH1F("HMS YTAR", "HMS YTAR", 100, -10., 10.);
    TH1F *hhmsCal = new TH1F("HMS CAL", "CAL", 100, 0., 2.);
    
   hhmsDelta->Sumw2(); 
   hhmsXptar->Sumw2(); 
   hhmsYptar->Sumw2(); 
   hhmsYtar->Sumw2(); 
   hW->Sumw2();

    Long64_t nentries_data = tdata->GetEntries();
    for (int j = 0; j < nentries_data; j++) {
        tdata->GetEntry(j);
        if(hdelta>-8. && hdelta<8.  && hetottracknorm>0.7){
            hW->Fill(W);
            hhmsXptar->Fill(hxptar);
            hhmsDelta->Fill(hdelta);
            hhmsYptar->Fill(hyptar);
            hhmsYtar->Fill(hytar);
	    hhmsCal->Fill(hetottracknorm);
            
     	}
    }
    double elasCount = hhmsXptar->Integral(hhmsXptar->GetXaxis()->FindBin(-1.), hhmsXptar->GetXaxis()->FindBin(1.));
    cout<<"# of elastics:"<<" "<<elasCount<<" "<<endl;
    
    TCanvas *c2 = new TCanvas("c2", "HMS target variables", 1200, 1200);
    c2->Divide(2,2);
    c2->cd(1);
    hhmsDelta->SetMarkerColor(kGreen+1);
    hhmsDelta->SetMarkerStyle(kFullCircle); 
    hhmsDelta->SetMarkerSize(0.5);
    hhmsDelta->SetMinimum(0);
    hhmsDelta->SetStats(0);
    hhmsDelta->Draw("hist e0 x0");
    c2->cd(2);
    hhmsXptar->SetMarkerColor(kGreen+1);
    hhmsXptar->SetMarkerStyle(kFullCircle); 
    hhmsXptar->SetMarkerSize(0.5);
    hhmsXptar->SetMinimum(0);
    hhmsXptar->SetStats(0);
    hhmsXptar->Draw("hist e0 x0");
    c2->cd(3);
    hhmsYptar->SetMarkerColor(kGreen+1);
    hhmsYptar->SetMarkerStyle(kFullCircle); 
    hhmsYptar->SetMarkerSize(0.5);
    hhmsYptar->SetMinimum(0);
    hhmsYptar->Draw("hist e0 x0");
    hhmsYptar->SetStats(0);
    c2->cd(4);
    hhmsYtar->SetMarkerColor(kGreen+1);
    hhmsYtar->SetMarkerStyle(kFullCircle); 
    hhmsYtar->SetMarkerSize(0.5);
    hhmsYtar->SetMinimum(0);
    hhmsYtar->SetStats(0);
    hhmsYtar->Draw("hist e0 x0");
    
    TCanvas *c3 = new TCanvas("c3", "W", 1200, 600);
    c3->cd();
    hW->SetMarkerColor(kGreen+1);
    hW->SetMarkerStyle(kFullCircle); 
    hW->SetMarkerSize(0.5);
    hW->SetMinimum(0);
    hW->SetStats(0);
    hW->Draw("hist e0 x0");
    c3->SaveAs("W.pdf");
    TCanvas *c4 = new TCanvas("c4", "HMS CAL", 1200, 600);
    c4->cd();
    hhmsCal->SetMarkerColor(kGreen+1);
    hhmsCal->SetMarkerStyle(kFullCircle); 
    hhmsCal->SetMarkerSize(0.5);
    hhmsCal->SetMinimum(0);
    hhmsCal->SetStats(0);
    hhmsCal->Draw("hist e0 x0");
    
}





