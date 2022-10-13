/************************************************
 * paddle_cut_plots.C(int run_no, int S1Xopt, int S2Xopt)
 * Make plots to assess paddle cuts in S1X 
 * 	and S2X
 *
 * Run_no - Run number to analyze
 * S1Xopt - "Optimal" number of S1X paddles to
 * 	turn off
 * S2Xopt - "Optimal" number of S2X paddles to
 * 	turn off
 *
 * Tyler Hague - Oct 2, 2022 (created)
 *             - Oct 7, 2022 (done ~ish... need to test)
 * *********************************************/

static const Int_t nElem=100;
static const Int_t    N1xPMT = 13;
static const Int_t    N1yPMT = 13;
static const Int_t    N2xPMT = 14;
static const Int_t    N2yPMT = 18;

static const double S1x_width = 8;
static const double S2x_width = 10;
static const double S1x_centers[N1xPMT] = {-45, -37.5, -30, -22.5, -15, -7.5, 0, 7.5, 15, 22.5, 30, 37.5, 45};
static const double S2x_centers[N2xPMT] = {-61.75, -52.25, -42.75, -33.25, -23.75, -14.25, -4.75, 4.75, 14.25, 23.75, 33.25, 42.75, 52.25, 61.75};
static const double S1x_z = 56.9-4.8;
static const double S1x_dz = 2.12;
static const double S2x_z = 267.7+3.7; 
static const double S2x_dz = -2.12;
//dz should be applied to z for i%2==1 (i.e. even numbered paddles, as entry i is paddle i+1)

//Return a vector since it can potentially hit 2 paddles
vector<int> S1X_paddle(double x, double dxdz){
  double x_zodd = x + (dxdz * S1x_z);
  double x_zeven = x + (dxdz * (S1x_z + S1x_dz));

  vector<int> hits;

  for(int i=0; i<N1xPMT; i++){
    //how many hits at start of loop
    int old_l = hits.size();
    if(i%2==0){
      if(x_zodd > (S1x_centers[i] - (S1x_width/2.)) && x_zodd < (S1x_centers[i] + (S1x_width/2.))){
        hits.push_back(i+1);
      }
    }else if(i%2==1){
      if(x_zeven > (S1x_centers[i] - (S1x_width/2.)) && x_zeven < (S1x_centers[i] + (S1x_width/2.))){
        hits.push_back(i+1);
      }
    }

    //Can't have more than 2 hits, so stop checking if we have that
    //Hits have to be adjacent, so stop checking if we have a hit and the next one didn't get hit
    if(hits.size()==2 || (hits.size()==old_l && old_l>0)){
      break;
    }
  }
  return hits;
}

vector<int> S2X_paddle(double x, double dxdz){
  double x_zodd = x + (dxdz * S2x_z);
  double x_zeven = x + (dxdz * (S2x_z + S2x_dz));

  vector<int> hits;

  for(int i=0; i<N2xPMT; i++){
    //how many hits at start of loop
    int old_l = hits.size();
    if(i%2==0){
      if(x_zodd > (S2x_centers[i] - (S2x_width/2.)) && x_zodd < (S2x_centers[i] + (S2x_width/2.))){
        hits.push_back(i+1);
      }
    }else if(i%2==1){
      if(x_zeven > (S2x_centers[i] - (S2x_width/2.)) && x_zeven < (S2x_centers[i] + (S2x_width/2.))){
        hits.push_back(i+1);
      }
    }

    //Can't have more than 2 hits, so stop checking if we have that
    //Hits have to be adjacent, so stop checking if we have a hit and the next one didn't get hit
    if(hits.size()==2 || (hits.size()==old_l && old_l>0)){
      break;
    }
  }
  return hits;
}

//********************
//Parameters
//  run_no - Run number for grabbing file
//  S1Xopt - Number of S1X Paddles to turn off
//  S2Xopt - Number of S2X Paddles to turn off
//
//Will make plots for all combinations of [S1Xopt +/- 1, S2Xopt +/- 1]
//********************

void paddle_cut_plots(int run_no, int S1Xopt, int S2Xopt){
  gStyle->SetPalette(kViridis);

  //Placeholder location, will refine later
  TFile *runFile = TFile::Open(Form("ROOTfiles/SHMS/shms_replay_hodo_check_%d_-1.root",run_no));
  TTree *T = dynamic_cast<TTree*> (runFile->Get("T"));

  TFile *outFile = new TFile(Form("UTIL_XEM/paddle_plots_out/paddle_cut_plots_%d_S1X%d_S2X%d.root", run_no, S1Xopt, S2Xopt),"RECREATE");

  //********************
  //Define some histograms
  //********************

  TH1D *h34Trig = new TH1D("h34Trig", "3/4 Trigger Scaler Rate; Rate (Hz)", 10000, 0, 100000);
  TH1D *hELTrig = new TH1D("hELTrig", "ELREAL Trigger Scaler Rate; Rate (Hz)", 10000, 0, 100000);

  TH1D *hS1Xgoodhits = new TH1D("hS1Xgoodhits", "Good Hits per Paddle (S1X)", N1xPMT,0.5,N1xPMT+0.5);
  TH1D *hS2Xgoodhits = new TH1D("hS2Xgoodhits", "Good Hits per Paddle (S2X)", N2xPMT,0.5,N2xPMT+0.5);

  TH2D *hProjHits = new TH2D("hProjHits", "Projected hit position of golden track; S1X PMT; S2X PMT", N1xPMT, 0.5, N1xPMT+0.5, N2xPMT, 0.5, N2xPMT+0.5);
  TH2D *hProjHits_lox = new TH2D("hProjHits_lox", "Projected hit position of golden track (x<1); S1X PMT; S2X PMT", N1xPMT, 0.5, N1xPMT+0.5, N2xPMT, 0.5, N2xPMT+0.5);

  //Increment [1xpaddle][2xpaddle] if turning it off would remove the event
  //[0][0] means nothing
  //[i][0] or [0][i] means that the column with 0 can have all on and still reject the event
  TH2D *hSXkeep = new TH2D("hSXkeep", "Number of events kept if paddle pair turned off; S1X Paddle Number; S2X Paddle Number", N1xPMT+1, -0.5, N1xPMT+0.5, N2xPMT+1, -0.5, N2xPMT+0.5);
  TH2D *hSXkeep_frac = new TH2D("hSXkeep_frac", "Fraction of events kept if paddle pair turned off; S1X Paddle Number; S2X Paddle Number", N1xPMT+1, -0.5, N1xPMT+0.5, N2xPMT+1, -0.5, N2xPMT+0.5);

  //Will have more entries than events
  //Each event can fill twice due to potentially hitting two paddles
  TH1D *hS1X_gtr_match = new TH1D("hS1X_gtr_match", "Number of calculated S1X hits with matching real hits; Match (bool); Count", 2, -0.5, 1.5);
  TH1D *hS2X_gtr_match = new TH1D("hS2X_gtr_match", "Number of calculated S2X hits with matching real hits; Match (bool); Count", 2, -0.5, 1.5);

  TH1D *hkeep_cut_track = new TH1D("hkeep_cut_track", "Number of events where golden track can be cut but event triggers; GTR can be cut while EVT kept (bool); Count", 2, -0.5, 1.5);

  TH2D *hx_v_S1X = new TH2D("hx_v_S1X", "x_{bj} vs. Calculated S1X Paddle; x_{bj}; S1X Paddle", 300, 0, 3, N1xPMT, 0.5, N1xPMT+0.5);
  TH2D *hx_v_S2X = new TH2D("hx_v_S2X", "x_{bj} vs. Calculated S2X Paddle; x_{bj}; S2X Paddle", 300, 0, 3, N1xPMT, 0.5, N1xPMT+0.5);

  TH1D *hx = new TH1D("hx", "x_{bj} of all good events; x_{bj}; Count", 300, 0, 3);

  TH1D *hx_paddlecut[3][3];
  TH1D *hx_keep_cut_track[3][3];

  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      hx_paddlecut[i][j] = new TH1D(Form("hx_pc_%d_%d", S1Xopt-1+i, S2Xopt-1+j), Form("x_{bj} of events with HV off for paddles S1{1-%d} S2{1-%d}", S1Xopt-1+i, S2Xopt-1+j), 300, 0, 3);
      hx_keep_cut_track[i][j] = new TH1D(Form("hx_keep_cut_track_%d_%d", S1Xopt-1+i, S2Xopt-1+j), Form("x_{bj} of events kept but golden track cut with HV off for paddles S1{1-%d} S2{1-%d}", S1Xopt-1+i, S2Xopt-1+j), 300, 0, 3);
    }
  }

  //********************
  //Set up Branches
  //********************

  T->SetBranchStatus("*",0);

  //********************
  //Beam Current
  //********************

  double Ibeam;

  T->SetBranchStatus("hac_bcm_average", 1);

  T->SetBranchAddress("hac_bcm_average", &Ibeam);

  //********************
  //Trigger Rates
  //********************

  double T1rate;
  double T2rate;

  T->SetBranchStatus("P.pTRIG1.scalerRate", 1);
  T->SetBranchStatus("P.pTRIG2.scalerRate", 1);

  T->SetBranchAddress("P.pTRIG1.scalerRate", &T1rate);
  T->SetBranchAddress("P.pTRIG2.scalerRate", &T2rate);

  //********************
  //Golden Track
  //********************

  double gtr_i;
  double delta, theta, phi;

  T->SetBranchStatus("P.gtr.index", 1);
  T->SetBranchStatus("P.gtr.dp", 1);
  T->SetBranchStatus("P.gtr.th", 1);
  T->SetBranchStatus("P.gtr.ph", 1);

  T->SetBranchAddress("P.gtr.index", &gtr_i);
  T->SetBranchAddress("P.gtr.dp", &delta);
  T->SetBranchAddress("P.gtr.th", &theta);
  T->SetBranchAddress("P.gtr.ph", &phi);

  //********************
  //Kinematic variables
  //********************

  double xbj;

  T->SetBranchStatus("P.kin.x_bj", 1);

  T->SetBranchAddress("P.kin.x_bj", &xbj);

  //********************
  //Track
  //********************

  Double_t trx[nElem], dxdz[nElem];

  T->SetBranchStatus("P.tr.x", 1);
  T->SetBranchStatus("P.tr.th", 1);

  T->SetBranchAddress("P.tr.x", trx);
  T->SetBranchAddress("P.tr.th", dxdz);

  //********************
  //Calorimeter + Cer
  //********************

  double E_p;
  double npe[4];

  T->SetBranchStatus("P.cal.etottracknorm", 1);

  T->SetBranchAddress("P.cal.etottracknorm", &E_p);

  T->SetBranchStatus("P.ngcer.npe", 1);

  T->SetBranchAddress("P.ngcer.npe", npe);

  //********************
  //Hodoscope
  //********************

  /*vector<Double_t> hod1x_nGPAdc, hod1x_nGNAdc;
    hod1x_nGPAdc = vector<Double_t>(N1xPMT, 0.0);
    hod1x_nGNAdc = vector<Double_t>(N1xPMT, 0.0);
    vector<Double_t> hod2x_nGPAdc, hod2x_nGNAdc;
    hod2x_nGPAdc = vector<Double_t>(N2xPMT, 0.0);
    hod2x_nGNAdc = vector<Double_t>(N2xPMT, 0.0);*/
  double hod1x_nGPAdc[N1xPMT], hod1x_nGNAdc[N1xPMT];
  double hod2x_nGPAdc[N2xPMT], hod2x_nGNAdc[N2xPMT];
  double hod1y_totnGPAdc, hod1y_totnGNAdc;
  double hod2y_totnGPAdc, hod2y_totnGNAdc;

  T->SetBranchStatus("P.hod.1x.numGoodPosAdcHits", 1);
  T->SetBranchStatus("P.hod.1x.numGoodNegAdcHits", 1);
  T->SetBranchStatus("P.hod.2x.numGoodPosAdcHits", 1);
  T->SetBranchStatus("P.hod.2x.numGoodNegAdcHits", 1);
  T->SetBranchStatus("P.hod.1y.totNumGoodPosAdcHits", 1);
  T->SetBranchStatus("P.hod.1y.totNumGoodNegAdcHits", 1);
  T->SetBranchStatus("P.hod.2y.totNumGoodPosAdcHits", 1);
  T->SetBranchStatus("P.hod.2y.totNumGoodNegAdcHits", 1);

  T->SetBranchAddress("P.hod.1x.numGoodPosAdcHits", hod1x_nGPAdc);
  T->SetBranchAddress("P.hod.1x.numGoodNegAdcHits", hod1x_nGNAdc);
  T->SetBranchAddress("P.hod.2x.numGoodPosAdcHits", hod2x_nGPAdc);
  T->SetBranchAddress("P.hod.2x.numGoodNegAdcHits", hod2x_nGNAdc);
  T->SetBranchAddress("P.hod.1y.totNumGoodPosAdcHits", &hod1y_totnGPAdc);
  T->SetBranchAddress("P.hod.1y.totNumGoodNegAdcHits", &hod1y_totnGNAdc);
  T->SetBranchAddress("P.hod.2y.totNumGoodPosAdcHits", &hod2y_totnGPAdc);
  T->SetBranchAddress("P.hod.2y.totNumGoodNegAdcHits", &hod2y_totnGNAdc);


  //********************
  //Event Loop
  //********************

  Int_t nev = T->GetEntries();
  for(int ev=0; ev<nev; ev++){
    T->GetEntry(ev);
    //check raw rates
    //  this should be ~trigger rate
    //also check x_bj of best tracks

    //Beam current is approximately at set point
    //if(Ibeam<55) continue;

    //Plot Trig1 and Trig2 rates
    //  Trig1 rate should be same as requiring that 3/4 P.hod.[12][xy].totNumGoodAdcHits are >= 1
    //  Check that
    //Then calculate that using P.hod.[12][x]n.?
    h34Trig->Fill(T1rate);
    hELTrig->Fill(T2rate);

    for(int i=0; i<N1xPMT; i++){
      double prev_val = hS1Xgoodhits->GetBinContent(i+1);
      hS1Xgoodhits->SetBinContent(i+1, hod1x_nGPAdc[i] + hod1x_nGNAdc[i] + prev_val);
    }
    for(int i=0; i<N2xPMT; i++){
      double prev_val = hS2Xgoodhits->GetBinContent(i+1);
      hS2Xgoodhits->SetBinContent(i+1, hod2x_nGPAdc[i] + hod2x_nGNAdc[i] + prev_val);
    }

    //Using P.hod.[12][xy].numGood[Pos,Neg]AdcHits, construct the trigger
    //For each event determine if it would pass for the test cases of turning off paddles
    int ny_pretrig = 0;
    if(hod1y_totnGPAdc > 0 && hod1y_totnGNAdc > 0){
      ny_pretrig++;
    }
    if(hod2y_totnGPAdc > 0 && hod2y_totnGNAdc > 0){
      ny_pretrig++;
    }

    int l1xhit_p=0; //last pmt with a hit
    int l1xhit_n=0; //last pmt with a hit
    int l1xhit=0;
    int l2xhit_p=0; //NPMT+1 means no hit (i.e. can turn off any number and would still pass)
    int l2xhit_n=0; //NPMT+1 means no hit (i.e. can turn off any number and would still pass)
    int l2xhit=0;
    for(int i=0; i<N1xPMT; i++){
      if(hod1x_nGPAdc[i]>0){
        l1xhit_p=i+1;
      }
      if(hod1x_nGNAdc[i]>0){
        l1xhit_n=i+1;
      }
    }
    for(int i=0; i<N2xPMT; i++){
      if(hod2x_nGPAdc[i]>0){
        l2xhit_p=i+1;
      }
      if(hod2x_nGNAdc[i]>0){
        l2xhit_n=i+1;
      }
    }
    l1xhit = l1xhit_p>l1xhit_n ? l1xhit_n : l1xhit_p;
    l2xhit = l2xhit_p>l2xhit_n ? l2xhit_n : l2xhit_p;

    if(ny_pretrig==1){
      for(int i=0; i<l1xhit; i++){
        for(int j=0; j<l2xhit; j++){
          hSXkeep->Fill(i, j);
        }
      }
    }else if(ny_pretrig==2){
      for(int i=0; i<=N1xPMT; i++){
        for(int j=0; j<=N2xPMT; j++){
          if(i<l1xhit || j<l2xhit){
            hSXkeep->Fill(i, j);
          }
        }
      }
    }


    //Plots of paddle cut effects:
    //  2D histogram of the SXkeep matrix - This is useful, but does not have any direct comparison in the simulation due to this focusing on accidentals - can be done here
    //  2D histogram of fraction of events that pass paddle cut - easy to create from simulation - needs to be done after event loop
    //  
    //Print to file the fractions for "optimal" cut +/- 1


    //Place cuts
    //  energy conservation
    //  cherenkov
    //  has a golden track
    //  from target
    //  acceptance?
    //    maybe not, acceptance is good for final data but maybe not right for rates
    //  one track?
    if(E_p < 0.7) continue;
    if(delta > 15) continue;
    if(gtr_i < 0) continue;
    if(delta < -10) continue;
    if(TMath::Abs(phi) > 0.1) continue;
    if(TMath::Abs(theta) >0.1) continue;
    if((npe[0]+npe[1]+npe[2]+npe[3])<3) continue;

    //Use P.hod.[12][xy].Track[XY]Pos to figure out which paddle was hit
    //  Figure out how these variables are calculated (do I need to look up position values in DB)
    //  Plot paddle vs x
    //Calculation of P.hod.[12][xy].Track[XY]Pos is confusing me (the /num_good_pad part when dealing with pl_zpos)
    //  So, calculating myself from P.gtr values
    //  Hardcoding in z and x positions of planes/paddles
    //  Ideally would get these from the database, but there's no offsets away from a center of 0 so it's safe to hardcode for now

    vector<int> S1X_hits = S1X_paddle(trx[(int) gtr_i], dxdz[(int) gtr_i]);
    vector<int> S2X_hits = S2X_paddle(trx[(int) gtr_i], dxdz[(int) gtr_i]);

    for(int i=0; i<S1X_hits.size(); i++){
      if(hod1x_nGPAdc[S1X_hits[i]] > 0 || hod1x_nGNAdc[S1X_hits[i]] > 0){
        hS1X_gtr_match->Fill(1);
      }else{
        hS1X_gtr_match->Fill(0);
      }
      for(int j=0; j<S2X_hits.size(); j++){
        hProjHits->Fill(S1X_hits[i],S2X_hits[j]);
	if(xbj < 1){
	  hProjHits_lox->Fill(S1X_hits[i],S2X_hits[j]);
	}
      }
    }
    for(int i=0; i<S2X_hits.size(); i++){
      if(hod2x_nGPAdc[S2X_hits[i]] > 0 || hod2x_nGNAdc[S2X_hits[i]] > 0){
        hS2X_gtr_match->Fill(1);
      }else{
        hS2X_gtr_match->Fill(0);
      }
    }

    if(ny_pretrig==1){
      //Only need to check the last hit within the golden track as that is the "highest" paddle
      //Both need hits if there's only 1 y hit
      if(S1X_hits.size()>0){
        if(S2X_hits.size()>0){
          if(l1xhit > S1X_hits[S1X_hits.size()-1] && l2xhit > S2X_hits[S2X_hits.size()-1]){
            hkeep_cut_track->Fill(1);
          }else{
            hkeep_cut_track->Fill(0);
          }
        }else{
          if(l1xhit > S1X_hits[S1X_hits.size()-1]){
            hkeep_cut_track->Fill(1);
          }else{
            hkeep_cut_track->Fill(0);
          }
        }
      }else{
        if(S2X_hits.size()>0){
          if(l2xhit > S2X_hits[S2X_hits.size()-1]){
            hkeep_cut_track->Fill(1);
          }
        }
      }
    }else if(ny_pretrig==2){
      //Only need one hit if there are 2 y hits
      if(S1X_hits.size()>0){
        if(S2X_hits.size()>0){
          if(l1xhit > S1X_hits[S1X_hits.size()-1] || l2xhit > S2X_hits[S2X_hits.size()-1]){
            hkeep_cut_track->Fill(1);
          }else{
            hkeep_cut_track->Fill(0);
          }
        }else{
          if(l1xhit > S1X_hits[S1X_hits.size()-1]){
            hkeep_cut_track->Fill(1);
          }else{
            hkeep_cut_track->Fill(0);
          }
        }
      }else{
        if(S2X_hits.size()>0){
          if(l2xhit > S2X_hits[S2X_hits.size()-1]){
            hkeep_cut_track->Fill(1);
          }
        }
      }
    }

    for(int i=0; i<S1X_hits.size(); i++){
      hx_v_S1X->Fill(xbj, S1X_hits[i]);
    }
    for(int i=0; i<S2X_hits.size(); i++){
      hx_v_S2X->Fill(xbj, S2X_hits[i]);
    }

    hx->Fill(xbj);

    /*for(int i=-1; i<=1; i++){
      for(int j=-1; j<=1; j++){
      if(l1xhit > S1Xopt+i && l2xhit > S2Xopt+j){
      if(S1X_hits.size()>0){
      if(S2X_hits.size()>0){
      if(S1X_hits[S1X_hits.size()-1] > S1Xopt+i && S2X_hits[S2X_hits.size()-1] > S2Xopt+j){
      hx_paddlecut[i+1][j+1]->Fill(xbj);
      }else{
      hx_keep_cut_track[i+1][j+1]->Fill(xbj);
      }
      }else{
      if(S1X_hits[S1X_hits.size()-1] > S1Xopt+i){
      hx_paddlecut[i+1][j+1]->Fill(xbj);	
      }else{
      hx_keep_cut_track[i+1][j+1]->Fill(xbj);
      }
      }
      }else{
      if(S2X_hits.size()>0){
      if(S2X_hits[S2X_hits.size()-1] > S2Xopt+j){
      hx_paddlecut[i+1][j+1]->Fill(xbj);
      }else{
      hx_keep_cut_track[i+1][j+1]->Fill(xbj);
      }
      }
      }
      }
      }
      }*/
    for(int i=-1; i<=1; i++){
      for(int j=-1; j<=1; j++){
        if(ny_pretrig==1 && l1xhit > S1Xopt+i && l2xhit > S2Xopt+j){
          hx_paddlecut[i+1][j+1]->Fill(xbj);
        }else if(ny_pretrig==2 && ((l1xhit > S1Xopt+i) || (l2xhit > S2Xopt+j))){
          hx_paddlecut[i+1][j+1]->Fill(xbj);
        }
      }
    }
  }

  double b00 = hSXkeep->GetBinContent(1, 1);
  cout << b00 << endl;

  for(int i=1; i<=N1xPMT+1; i++){
    for(int j=1; j<=N2xPMT+1; j++){
      double raw = hSXkeep->GetBinContent(i, j);
      hSXkeep_frac->SetBinContent(i, j, raw/b00);
    }
  }


  outFile->cd();

  h34Trig->Write();
  hELTrig->Write();
  hS1Xgoodhits->Write();
  hS2Xgoodhits->Write();
  hProjHits->Write();
  hProjHits_lox->Write();
  hSXkeep->Write();
  hSXkeep_frac->Write();
  hS1X_gtr_match->Write();
  hS2X_gtr_match->Write();
  hkeep_cut_track->Write();
  hx_v_S1X->Write();
  hx_v_S2X->Write();
  hx->Write();
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      hx_paddlecut[i][j]->Write();
    }
  }
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      hx_keep_cut_track[i][j]->Write();
    }
  }

  TString pdf_out = Form("UTIL_XEM/paddle_plots_out/paddle_cut_plots_%d_S1X%d_S2X%d.pdf", run_no, S1Xopt, S2Xopt);

/*  auto *c = new TCanvas();

  h34Trig->Draw();
  c->Print(pdf_out + "[" + pdf_out);
  c->Print(pdf_out);
  hELTrig->Draw();
  c->Print(pdf_out);
  hSXkeep->Draw("colz");
  c->Print(pdf_out);
  hSXkeep_frac->Draw("colz");
  c->Print(pdf_out);
  hS1X_gtr_match->Draw();
  c->Print(pdf_out);
  hS2X_gtr_match->Draw();
  c->Print(pdf_out);
  hkeep_cut_track->Draw();
  c->Print(pdf_out);
  hx_v_S1X->Draw("colz");
  c->Print(pdf_out);
  hx_v_S2X->Draw("colz");
  c->Print(pdf_out);
  hx->Draw();
  c->Print(pdf_out);
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      hx_paddlecut[i][j]->Draw();
      c->Print(pdf_out);
    }
  }
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      hx_keep_cut_track[i][j]->Draw();
      c->Print(pdf_out);
    }
  }
  c->Print(pdf_out + "]");*/

  runFile->Close();
  outFile->Close();
}
