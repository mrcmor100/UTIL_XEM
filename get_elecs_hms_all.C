#include <iostream>
#include <fstream>
#include <string>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TMatrixD.h>
#include <TROOT.h>
#include <TMatrixDBase.h>
#include <TMath.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>
#include <cstdlib>
#include "TColor.h"
#include "TH3.h"


using namespace std;

static const double degtorad = 3.141592653589793/180.;

void formatit(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag, Int_t flag2, Int_t flagc){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kAzure-2);
  histo->SetLineWidth(3);
  histo->SetLineStyle(1);

  if(flag2 == 0){
    histo->Draw("");  
  }
  if(flag2 == 1){
    histo->Draw("same");  
  }
  if(flagc == 2){
    histo->SetLineStyle(1);
    histo->SetLineColor(kAzure-2);  
  }
  if(flagc == 3){
    histo->SetLineStyle(1);
    histo->SetLineColor(kPink+10);  
  }
  
  leg = new TLegend(0.15,0.85,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kAzure-2);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}


TH1F *pion_histo = new TH1F("","",150,0.,1.5);
TH1F *elec_histo = new TH1F("","",150,0.,1.5);
TH1F *all_histo = new TH1F("","",150,0.,1.5);

void get_elecs_hms_all(Int_t run_num, Double_t elec_goal){  

  Double_t shtrk, npe, delta;
  
  string myfile; 
  myfile = Form("/net/cdaqfs/home/cdaq/hallc-online/hallc_replay/ROOTfiles/hms_replay_production_%d_-1.root",run_num);

  TFile *fileis = new TFile(myfile.c_str());
  cout << "root file is: " << myfile << endl;

  TTree *tis = (TTree*)fileis->Get("T");
  
  tis->SetBranchAddress("H.cal.etracknorm",&shtrk);
  tis->SetBranchAddress("H.cer.npeSum",&npe);
  tis->SetBranchAddress("H.gtr.dp",&delta);
  

  Int_t nentries = tis->GetEntries();
  cout << " ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << "you are indeed sampling " << nentries << " coda events " << endl;
  cout << " ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;

  for(Int_t i=0; i < nentries; i++){

    tis->GetEntry(i);

    if(delta > -8. && delta < 8.){
      all_histo->Fill(shtrk);
    }

    if(npe > 2. && shtrk > 0.7 && delta > -8. && delta < 8.){
      elec_histo->Fill(shtrk);
    }
    if(npe == 0. && shtrk < 0.7 && delta > -8. && delta < 8.){
      pion_histo->Fill(shtrk);
    }
  }

  Double_t elec_events = elec_histo->Integral();
  Double_t pion_events = pion_histo->Integral();

  cout << "Look here for your desired HMS electrons: " << elec_events << endl;
  cout << " ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << "this is " <<  elec_events*100./elec_goal/1000 << "% of" << " " << elec_goal << " " << " K electrons" << endl;
  cout << " ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
  cout << " ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;


  
}




