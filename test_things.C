#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"


void test_things(){
  //define the variables
  double ptardp;
  double ptarth;
  double ptarph;
  double shmsCal;
  double ngcer;
  double xbj;
  
  int run, totes;
  //17311 All ON
  //17282 Setting 2 
  //17294 Setting 3
  //17292 Setting 4
  //17293 Setting 5
  //17295 Setting 6 
  //open the root file and access to the tree
  //TFile *f = new TFile("/cache/hallc/E12-10-002/abishek/realpass-3c-shms-data/shms_replay_production_3131_-1.root");
  //  run=17311;

  FILE* out1=fopen("blah.dat", "w");
  
  //17311 17294 17292
  //loop
  std::ifstream ifs("runlist.dat", std::ifstream::in);
  vector<int> runs;

  while(!ifs.eof())
    {
      int run;
      ifs>>run;
      runs.push_back(run);
      printf("Read in %i\n", run);
    }
  ifs.close();
  
  for (int ii=0; ii<runs.size(); ii++)
    {
      printf("Look at me %i, run %i\n", ii, runs[ii]);
      TFile *f1 = new TFile(Form("/net/cdaq/cdaql1data/cdaq/hallc-online-xem2022/ROOTfiles/SHMS/shms_replay_hodo_check_%d_-1.root",runs[ii]));
      TTree *t1 = (TTree*) f1->Get("T");
      
      
      //Define the histograms
      TH1F *histo_x = new TH1F("xbj", "muh bukkit", 200, 0.2, 2.5);
      t1->Project("P.kin.x_bj>>xbj", "P.gtr.dp > -10 && P.gtr.dp<20 && P.kin.x_bj>0.2 && P.kin.x_bj<2.5 && (P.ngcer.npe[0]+P.ngcer.npe[1]+P.ngcer.npe[2]+P.ngcer.npe[3])>2 && P.cal.etottracknorm>0", "");
      
      totes=histo_x->GetEntries();
      fprintf(out1, "%i %i \n", runs[ii], totes);
      f1->Close();
      //      delete t;
    }

  fclose(out1);

}





