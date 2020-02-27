/******************************************************************
 * This macro makes histograms to save to a file.
 * It assumes the usual hodoscope PMTs.
 * MultCut is a Bool to turn on Multiplicity Cuts {Mult==2 only}
 * Casey Morean     cmorean@jlab.org     Created 2/26/2020
 ******************************************************************/

using namespace std;

static const Int_t    NBINS  = 400;
static const Double_t XSTART = -80;
static const Double_t XSTOP  = 120;

static const Int_t    N1xPMT = 13;
static const Int_t    N1yPMT = 13;
static const Int_t    N2xPMT = 14;
static const Int_t    N2yPMT = 18;

TFile *runFile, *outFile;
TTree *T;

TH1F *hist1xPos[N1xPMT], *hist1xNeg[N1xPMT],
     *hist1yPos[N1yPMT], *hist1yNeg[N1yPMT],
     *hist2xPos[N2xPMT], *hist2xNeg[N2xPMT],
     *hist2yPos[N2yPMT], *hist2yNeg[N2yPMT];

TH1F *hist1xPosMult[N1xPMT], *hist1xNegMult[N1xPMT],
     *hist1yPosMult[N1yPMT], *hist1yNegMult[N1yPMT],
     *hist2xPosMult[N2xPMT], *hist2xNegMult[N2xPMT],
     *hist2yPosMult[N2yPMT], *hist2yNegMult[N2yPMT];

Double_t hod1xPosArr[N1xPMT], hod1xNegArr[N1xPMT], 
         hod1yPosArr[N1yPMT], hod1yNegArr[N1yPMT],
         hod2xPosArr[N2xPMT], hod2xNegArr[N2xPMT],
         hod2yPosArr[N2yPMT], hod2yNegArr[N2yPMT];

Double_t hod1xPosMult[N1xPMT], hod1xNegMult[N1xPMT],
         hod1yPosMult[N1yPMT], hod1yNegMult[N1yPMT],
         hod2xPosMult[N2xPMT], hod2xNegMult[N2xPMT],
         hod2yPosMult[N2yPMT], hod2yNegMult[N2yPMT];


void makeHistArr(TH1F* histArr[], string plane, string end, Int_t nPMT,
		 TString xaxis, TString yaxis, Int_t nBins,
		 Double_t xStart, Double_t xStop, string opt="");



void hodo_timing(int run_no, string spect, Bool_t cut) {
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

  outFile = new TFile("hodoTimingHistos.root","RECREATE");

  T->SetBranchStatus("*",0);
  T->SetBranchStatus("P.hod.1x.GoodPosAdcTdcDiffTime",1);
  T->SetBranchStatus("P.hod.1x.GoodNegAdcTdcDiffTime",1);
  T->SetBranchStatus("P.hod.1y.GoodPosAdcTdcDiffTime",1);
  T->SetBranchStatus("P.hod.1y.GoodNegAdcTdcDiffTime",1);
  T->SetBranchStatus("P.hod.2x.GoodPosAdcTdcDiffTime",1);
  T->SetBranchStatus("P.hod.2x.GoodNegAdcTdcDiffTime",1);
  T->SetBranchStatus("P.hod.2y.GoodPosAdcTdcDiffTime",1);
  T->SetBranchStatus("P.hod.2y.GoodNegAdcTdcDiffTime",1);

  T->SetBranchStatus("P.hod.1x.GoodPosAdcMult",1);
  T->SetBranchStatus("P.hod.1x.GoodNegAdcMult",1);
  T->SetBranchStatus("P.hod.1y.GoodPosAdcMult",1);
  T->SetBranchStatus("P.hod.1y.GoodNegAdcMult",1);
  T->SetBranchStatus("P.hod.2x.GoodPosAdcMult",1);
  T->SetBranchStatus("P.hod.2x.GoodNegAdcMult",1);
  T->SetBranchStatus("P.hod.2y.GoodPosAdcMult",1);
  T->SetBranchStatus("P.hod.2y.GoodNegAdcMult",1);

  //Setting Variables to hold vars.
  T->SetBranchAddress("P.hod.1x.GoodPosAdcTdcDiffTime",&hod1xPosArr);
  T->SetBranchAddress("P.hod.1x.GoodNegAdcTdcDiffTime",&hod1xNegArr);
  T->SetBranchAddress("P.hod.1y.GoodPosAdcTdcDiffTime",&hod1yPosArr);
  T->SetBranchAddress("P.hod.1y.GoodNegAdcTdcDiffTime",&hod1yNegArr);
  T->SetBranchAddress("P.hod.2x.GoodPosAdcTdcDiffTime",&hod2xPosArr);
  T->SetBranchAddress("P.hod.2x.GoodNegAdcTdcDiffTime",&hod2xNegArr);
  T->SetBranchAddress("P.hod.2y.GoodPosAdcTdcDiffTime",&hod2yPosArr);
  T->SetBranchAddress("P.hod.2y.GoodNegAdcTdcDiffTime",&hod2yNegArr);

  T->SetBranchAddress("P.hod.1x.GoodPosAdcMult",&hod1xPosMult);
  T->SetBranchAddress("P.hod.1x.GoodNegAdcMult",&hod1xNegMult);
  T->SetBranchAddress("P.hod.1y.GoodPosAdcMult",&hod1yPosMult);
  T->SetBranchAddress("P.hod.1y.GoodNegAdcMult",&hod1yNegMult);
  T->SetBranchAddress("P.hod.2x.GoodPosAdcMult",&hod2xPosMult);
  T->SetBranchAddress("P.hod.2x.GoodNegAdcMult",&hod2xNegMult);
  T->SetBranchAddress("P.hod.2y.GoodPosAdcMult",&hod2yPosMult);
  T->SetBranchAddress("P.hod.2y.GoodNegAdcMult",&hod2yNegMult);

  makeHistArr(hist1xPos, "1x", "Pos", N1xPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTART, XSTOP);
  makeHistArr(hist1xNeg, "1x", "Neg", N1xPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTART, XSTOP);
  makeHistArr(hist1yPos, "1y", "Pos", N1yPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTART, XSTOP);
  makeHistArr(hist1yNeg, "1y", "Neg", N1yPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTART, XSTOP);
  makeHistArr(hist2xPos, "2x", "Pos", N2xPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTART, XSTOP);
  makeHistArr(hist2xNeg, "2x", "Neg", N2xPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTART, XSTOP);
  makeHistArr(hist2yPos, "2y", "Pos", N2yPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTART, XSTOP);
  makeHistArr(hist2yNeg, "2y", "Neg", N2yPMT, "ADC Channel (~0.0625 ns/Ch)",
	      "Counts", NBINS, XSTART, XSTOP);

  makeHistArr(hist1xPosMult, "1x", "Pos", N1xPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTART, XSTOP, "_Mult");
  makeHistArr(hist1xNegMult, "1x", "Neg", N1xPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTART, XSTOP, "_Mult");
  makeHistArr(hist1yPosMult, "1y", "Pos", N1yPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTART, XSTOP, "_Mult");
  makeHistArr(hist1yNegMult, "1y", "Neg", N1yPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTART, XSTOP, "_Mult");
  makeHistArr(hist2xPosMult, "2x", "Pos", N2xPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTART, XSTOP, "_Mult");
  makeHistArr(hist2xNegMult, "2x", "Neg", N2xPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTART, XSTOP, "_Mult");
  makeHistArr(hist2yPosMult, "2y", "Pos", N2yPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTART, XSTOP, "_Mult");
  makeHistArr(hist2yNegMult, "2y", "Neg", N2yPMT,
   "ADC Channel (~0.0625 ns/Ch)", "Counts", NBINS, XSTART, XSTOP, "_Mult");

  Long64_t nEntries = T->GetEntries();
  //Loop Entries
  for(Long64_t event = 0; event < nEntries; event++) {
    T->GetEntry(event);

    if(event % 100000 == 0) {cout << "Made it through: " << event <<
	" entries." << endl;}

    //Loop Plane 1x
    for(Int_t N1x = 0; N1x < N1xPMT; N1x++) {
      hist1xPos[N1x]->Fill(hod1xPosArr[N1x]);
      hist1xNeg[N1x]->Fill(hod1xNegArr[N1x]);
      if(hod1xPosMult[N1x]==2) {
	hist1xPosMult[N1x]->Fill(hod1xPosArr[N1x]);
      }
      if(hod1xNegMult[N1x]==2) {
	hist1xNegMult[N1x]->Fill(hod1xNegArr[N1x]);
      }
    }

    //Loop Plane 1y
    for(Int_t N1y = 0; N1y < N1yPMT; N1y++) {
      hist1yPos[N1y]->Fill(hod1yPosArr[N1y]);
      hist1yNeg[N1y]->Fill(hod1yNegArr[N1y]);
      if(hod1yPosMult[N1y]==2) {
	hist1yPosMult[N1y]->Fill(hod1yPosArr[N1y]);
      }
      if(hod1yNegMult[N1y]==2) {
	hist1yNegMult[N1y]->Fill(hod1yNegArr[N1y]);
      }
    }

    //Loop Plane 2x
    for(Int_t N2x = 0; N2x < N2xPMT; N2x++) {
      hist2xPos[N2x]->Fill(hod2xPosArr[N2x]);
      hist2xNeg[N2x]->Fill(hod2xNegArr[N2x]);
      if(hod2xPosMult[N2x]==2) {
	hist2xPosMult[N2x]->Fill(hod2xPosArr[N2x]);
      }
      if(hod2xNegMult[N2x]==2) {
	hist2xNegMult[N2x]->Fill(hod2xNegArr[N2x]);
      }
    }

    //Loop Plane 2y
    for(Int_t N2y = 0; N2y < N2yPMT; N2y++) {
      hist2yPos[N2y]->Fill(hod2yPosArr[N2y]);
      hist2yNeg[N2y]->Fill(hod2yNegArr[N2y]);
      if(hod2yPosMult[N2y]==2) {
	hist2yPosMult[N2y]->Fill(hod2yPosArr[N2y]);
      }
      if(hod2yNegMult[N2y]==2) {
	hist2yNegMult[N2y]->Fill(hod2yNegArr[N2y]);
      }
    }
  }

  outFile->Write();
  outFile->Close();

}

//Name, Title, Xaxis, Yaxis, nBins, xStart, xStop, nHistos
void makeHistArr(TH1F* histArr[], string plane, string end, Int_t nPMT,
		   TString xaxis, TString yaxis, Int_t nBins,
		   Double_t xStart, Double_t xStop, string opt="") {

  for(Int_t nH = 0; nH < nPMT; nH++) {
    TString name = Form("Hodo_%s_%s%s[%d]",plane.c_str(), end.c_str(),
			opt.c_str(), nH);
    histArr[nH] = new TH1F(name, name, nBins, xStart, xStop);
    histArr[nH]->GetXaxis()->SetTitle(xaxis);
    histArr[nH]->GetYaxis()->SetTitle(yaxis);
    histArr[nH]->SetStats(0);
  }
  return;
}
