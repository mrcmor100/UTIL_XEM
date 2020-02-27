/*******************************
 * This macro overlays two histograms.
 * The label1 and label2 are optional
 * and can be used to label the
 * different histograms as they are 
 * drawn.
 *
 * hszumila@jlab.org
 *******************************/

#include "myexec.h"

using namespace std;

void twoHists(string spect, string det, string plane, string end, string pmt, string opt="", Int_t Mcut=0) {

  gStyle->SetPalette(kRainBow);

  string spectL;
  TH1F* H1;
  TH1F* H2;

  if(spect == "shms") {
    spectL = "P";
  }
  else
    spectL = "H";

  TString histName = Form(("%s_%s_%s[%s]"), det.c_str(),
            plane.c_str(), end.c_str(), pmt.c_str());
  gPad->SetTitle(histName);  
  H1 = (TH1F*) gDirectory->Get(histName);
  H1->Draw("X0 L PLC");

  if(Mcut==1) {
    TString histNameCut = Form(("%s_%s_%s%s[%s]"), det.c_str(),
	      plane.c_str(), end.c_str(), opt.c_str(), pmt.c_str());
    H2 = (TH1F*) gDirectory->Get(histNameCut);
    H2->Draw("SAME X0 L PLC");
  }

  gPad->AddExec("myexec","myexec()");
}
