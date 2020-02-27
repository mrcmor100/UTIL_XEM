
#ifndef MYEXEC_H
#define MYEXEC_H
Int_t i = 0;

void myexec()
{
  // get event information
  int event = gPad->GetEvent();
  int px    = gPad->GetEventX();
  int py    = gPad->GetEventY();

  // some magic to get the coordinates...
  double xd = gPad->AbsPixeltoX(px);
  double yd = gPad->AbsPixeltoY(py);
  float x = gPad->PadtoX(xd);
  float y = gPad->PadtoY(yd);
  
  //Determine x and y ranges (For making lines)
  Double_t xmin, ymin, xmax, ymax;
  gPad->GetRangeAxis(xmin, ymin, xmax, ymax);
  
  TString title = gPad->GetTitle();
   
  if (event==12) { // scroll wheel mouse button click
    std::cout << title << " " << i << " " << x << " " << y << std::endl;
    TLine *line = new TLine(x, gPad->PadtoY(ymin), x, gPad->PadtoY(ymax));
    line->SetLineColor(kRed);
    line->Draw();
    gPad->Update();
    i++;
    return;
  }
}

#endif

/*
void click()
{

  TFile *f1 = TFile::Open("shms_replay_production_all_7252_-1.root","READ");
  TH1F *hist;
  hist = dynamic_cast <TH1F*> (f1->Get("pcal_prshwr_raw_mult"));

  // draw hpx from hsimple.root
  //hpx->Draw();
  hist->Draw();

  // add exec
  gPad->AddExec("myexec","myexec()");
}
*/
