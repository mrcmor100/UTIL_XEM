/******************************************************************
 * This macro makes histograms of Calo. windows to save to a file.
 * It assumes the usual hodoscope PMTs.
 * MultCut is a Bool to turn on Multiplicity Cuts {Mult==2 only}
 * Casey Morean     cmorean@jlab.org     Created 2/26/2020
 ******************************************************************/

using namespace std;

static const Int_t    NBINS      = 200;
static const Double_t XSTARTPRSH = -30;
static const Double_t XSTOPPRSH  = 70;
static const Double_t XSTARTFLY  = -20;
static const Double_t XSTOPFLY   = 80;

static const Int_t    NPrShPosPMT = 14;
static const Int_t    NPrShNegPMT = 14;
static const Int_t    NFlyPMT     = 224;

TFile *runFile, *outFile;
TTree *T;

TH1F *histPrShPos[NPrShPosPMT], *histPrShNeg[NPrShNegPMT],
     *histFly[NFlyPMT];

TH1F *histPrShPosMult[NPrShPosPMT], *histPrShNegMult[NPrShNegPMT];

Double_t calPrShPosArr[NPrShPosPMT], calPrShNegArr[NPrShNegPMT], 
         calFlyArr[NFlyPMT];

Double_t calPrShPosMult[NPrShPosPMT], calPrShNegMult[NPrShNegPMT], 
         calFlyMult[NFlyPMT];


void makeHistArr(TH1F* histArr[], string det, string end, Int_t nPMT,
		 TString xaxis, TString yaxis, Int_t nBins,
		 Double_t xStart, Double_t xStop, string opt="");



void cal_timing(int run_no, string spect, Bool_t cut) {
  gStyle->SetPalette(kRainBow);

  string spectL;
  if(spect == "shms") {
    spectL = "P";
  }
  else if (spect == "hms") {
    spectL = "H";
  }
  else { 
    cout << "ERROR! Not a known Spectrometer: " << spect << endl;
    return;}

  runFile = TFile::Open(Form("runs_2019/shms_replay_production_all_%d_-1.root",run_no));
  T = dynamic_cast<TTree*> (runFile->Get("T"));

  outFile = new TFile("calTimingHistos.root","RECREATE");

  T->SetBranchStatus("*",0);
  T->SetBranchStatus("P.cal.pr.goodPosAdcTdcDiffTime",1);
  T->SetBranchStatus("P.cal.pr.goodNegAdcTdcDiffTime",1);
  T->SetBranchStatus("P.cal.fly.goodAdcTdcDiffTime",1);

  T->SetBranchStatus("P.cal.pr.goodPosAdcMult",1);
  T->SetBranchStatus("P.cal.pr.goodNegAdcMult",1);
  //T->SetBranchStatus("P.cal.fly.goodAdcMult",1);

  //Setting Variables to hold vars.
  T->SetBranchAddress("P.cal.pr.goodPosAdcTdcDiffTime",&calPrShPosArr);
  T->SetBranchAddress("P.cal.pr.goodNegAdcTdcDiffTime",&calPrShNegArr);
  T->SetBranchAddress("P.cal.fly.goodAdcTdcDiffTime",&calFlyArr);

  T->SetBranchAddress("P.cal.pr.goodPosAdcMult",&calPrShPosMult);
  T->SetBranchAddress("P.cal.pr.goodNegAdcMult",&calPrShNegMult);
  //T->SetBranchAddress("P.cal.fly.goodAdcMult",&calFlyMult);

  makeHistArr(histPrShPos, "PrSh", "Pos", NPrShPosPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTARTPRSH, XSTOPPRSH);
  makeHistArr(histPrShNeg, "PrSh", "Neg", NPrShNegPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTARTPRSH, XSTOPPRSH);
  makeHistArr(histFly, "Fly", "", NFlyPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTARTFLY, XSTOPFLY);

  makeHistArr(histPrShPosMult, "PrSh", "Pos", NPrShPosPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTARTPRSH, XSTOPPRSH, "_Mult");
  makeHistArr(histPrShNegMult, "PrSh", "Neg", NPrShNegPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTARTPRSH, XSTOPPRSH, "_Mult");

  Long64_t nEntries = T->GetEntries();
  //Loop Entries
  for(Long64_t event = 0; event < nEntries; event++) {
    T->GetEntry(event);

    if(event % 100000 == 0) {cout << "Made it through: " << event <<
	" entries." << endl;}

    //Loop For Preshower
    for(Int_t NPrPos = 0; NPrPos < NPrShPosPMT; NPrPos++) {
      histPrShPos[NPrPos]->Fill(calPrShPosArr[NPrPos]);
      histPrShNeg[NPrPos]->Fill(calPrShNegArr[NPrPos]);
      if(calPrShPosMult[NPrPos]==2) {
	histPrShPosMult[NPrPos]->Fill(calPrShPosArr[NPrPos]);
      }
      if(calPrShNegMult[NPrPos]==2) {
	histPrShNegMult[NPrPos]->Fill(calPrShNegArr[NPrPos]);
      }
    }

    //Loop For Fly
    for(Int_t NFly = 0; NFly < NFlyPMT; NFly++) {
      histFly[NFly]->Fill(calFlyArr[NFly]);
      //if(calFlyMult[NFly]==2) {
      //histFlyMult[NFly]->Fill(calFlyArr[NFly]);
      //}
    }
  }

  outFile->Write();
  outFile->Close();

}

//Name, Title, Xaxis, Yaxis, nBins, xStart, xStop, nHistos
void makeHistArr(TH1F* histArr[], string det, string end, Int_t nPMT,
		   TString xaxis, TString yaxis, Int_t nBins,
		   Double_t xStart, Double_t xStop, string opt="") {

  for(Int_t nH = 0; nH < nPMT; nH++) {
    TString name = Form("Calo_%s_%s%s[%d]",det.c_str(), end.c_str(),
			opt.c_str(), nH);
    histArr[nH] = new TH1F(name, name, nBins, xStart, xStop);
    histArr[nH]->GetXaxis()->SetTitle(xaxis);
    histArr[nH]->GetYaxis()->SetTitle(yaxis);
    histArr[nH]->SetStats(0);
  }
  return;
}
