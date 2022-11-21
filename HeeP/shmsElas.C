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



void shmsElas(Int_t runNum, Int_t nEvts=-1){
//void coinElas(){
    
//   TFile* fdata = new TFile(Form("../../ROOTfiles/COIN/HeeP/coin_elas_sum.root"));
    TFile* fdata = new TFile(Form("../../ROOTfiles/SHMS/HeeP/shms_replay_production_%d_%d.root",runNum,nEvts));
    TTree *tdata = (TTree*) fdata->Get("T");
    
    double sdelta; //DATA SHMS reconstructed 100*(p - pc)/pc with pc = central SHMS mnuentum
    double syptar; //DATA SHMS reconstructed target dy/dz vertical slope
    double sxptar; //DATA SHMS reconstructed target dx/dz vertical slope
    double sytar; //DATA SHMS reconstructed target y
    double W;
    double ngcer;
    double ecal;
    double petottracknorm;
    
    tdata->SetBranchAddress("P.cal.etottracknorm",&petottracknorm);
    tdata->SetBranchAddress("P.ngcer.npeSum",&ngcer);
    tdata->SetBranchAddress("P.gtr.dp", &sdelta);
    tdata->SetBranchAddress("P.gtr.th", &sxptar);
    tdata->SetBranchAddress("P.gtr.ph", &syptar);
    tdata->SetBranchAddress("P.gtr.y", &sytar); 
    tdata->SetBranchAddress("P.kin.W", &W);
        
    //HISTOGRAMS
    TH1F *hW = new TH1F("W", "W", 100, 0.5, 1.5);
    hW->GetXaxis()->SetTitle("W [GeV]");
    hW->GetYaxis()->SetTitle("counts");
    TH1F *hShmsDelta = new TH1F("SHMS delta", "SHMS delta", 100, -30, 40);
    TH1F *hShmsXptar = new TH1F("SHMS XPTAR", "SHMS XPTAR", 100, -.2, .2);
    TH1F *hShmsYptar = new TH1F("SHMS YPTAR", "SHMS YPTAR", 100, -.2, .2);
    TH1F *hShmsYtar = new TH1F("SHMS YTAR", "SHMS YTAR", 100, -10., 10.);
    TH1F *hShmsCal = new TH1F("SHMS CAL", "SHMS CAL", 100, -10., 10.);
    
   hShmsDelta->Sumw2(); 
   hShmsXptar->Sumw2(); 
   hShmsYptar->Sumw2(); 
   hShmsYtar->Sumw2(); 
   hShmsCal->Sumw2();
   hW->Sumw2();

    Long64_t nentries_data = tdata->GetEntries();
    for (int j = 0; j < nentries_data; j++) {
        tdata->GetEntry(j);
        if(sdelta>-10. && sdelta<22. && W < 1.05 && petottracknorm > 0.7){
            hW->Fill(W);
            hShmsXptar->Fill(sxptar);
            hShmsDelta->Fill(sdelta);
            hShmsYptar->Fill(syptar);
            hShmsYtar->Fill(sytar);
            hShmsCal->Fill(petottracknorm);
     	}
    }
    double elasCount = hShmsXptar->Integral(hShmsXptar->GetXaxis()->FindBin(-1.), hShmsXptar->GetXaxis()->FindBin(1.));
    cout<<"# of elastics:"<<" "<<elasCount<<" "<<endl;
    
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
    
    TCanvas *c4 = new TCanvas("c4", "W", 1200, 600);
    c4->cd();
    hShmsCal->SetMarkerColor(kGreen+1);
    hShmsCal->SetMarkerStyle(kFullCircle); 
    hShmsCal->SetMarkerSize(0.5);
    hShmsCal->SetMinimum(0);
    hShmsCal->SetStats(0);
    hShmsCal->Draw("hist e0 x0");
}





