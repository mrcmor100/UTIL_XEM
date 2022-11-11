#include <fstream>
#include <iostream>

//File Name Patterns
//const char* formatRootFilePath = "ROOTfiles/%s/SCALARS/%s_replay_scalars_%d_-1.root";
const char* formatRootFilePath = "ROOTfiles/%s/shms50k/%s_replay_production_%d_-1.root";
TDirectory *runDir;
TFile *currCutFile;
//TTrees
TTree *tScaler;
//Scaler Analysis Histograms
TGraph *gr_BCM_IvsT;
TH2F *h2_BCM_IvsT; TH1F *h_BCM_Current;

//Electron Yield Variables
Double_t sclY2,   sclY2Err, sclY3, sclY3Err;

//Cut Efficiencies Variables
Double_t avgCurrent,  Qtot, TRIG2Rate, TRIG3Rate, EDTMRate;
Double_t cpuLT, eDid, eShould, eTrkEff, eTrkEffErr, elt;

string isCutStr;

//Spectrometer Parameters
string fSpecName, fSpecLow, fSpecCap;

//Scaler Tree Variables
Int_t    scalerEntries;

//Scaler Tree Variables
double evtNum;
double trig1Scaler,trig2Scaler,trig3Scaler,
  trig4Scaler,trig5Scaler,trig6Scaler;

double edtmScaler;
double elloScaler,elloloScaler,elhiScaler,
  stofScaler,elrealScaler,elcleanScaler;

double prloScaler, prhiScaler, ncerScaler, hcerScaler, cerScaler;

double s1xScaler,s1yScaler,s2xScaler,
  s2yScaler,s1xs1yScaler,s2xs2yScaler;

double pre40Scaler,pre100Scaler,
  pre150Scaler,pre200Scaler;

double trefScaler;

double bcm1ChargeScaler,bcm2ChargeScaler,bcm4aChargeScaler,
  bcm4bChargeScaler,bcm4cChargeScaler,unserChargeScaler;

double bcm1CurrentScaler,bcm2CurrentScaler,bcm4aCurrentScaler,
  bcm4bCurrentScaler,bcm4cCurrentScaler,unserCurrentScaler;

double oneMHzScaler;

//Current Cut items
double cutCurrentBranch;

UInt_t  edtmScalerCntr_beamOn, edtmScalerCntr_beamOff;
UInt_t  trig1ScalerCntr_beamOn, trig1ScalerCntr_beamOff;
UInt_t  trig2ScalerCntr_beamOn, trig2ScalerCntr_beamOff;
UInt_t  trig3ScalerCntr_beamOn, trig3ScalerCntr_beamOff;
UInt_t  trig4ScalerCntr_beamOn, trig4ScalerCntr_beamOff;
UInt_t  trig5ScalerCntr_beamOn, trig5ScalerCntr_beamOff;
UInt_t  trig6ScalerCntr_beamOn, trig6ScalerCntr_beamOff;

UInt_t  qBCM1ScalerCntr_beamOn, qBCM1ScalerCntr_beamOff;
UInt_t  qBCM2ScalerCntr_beamOn, qBCM2ScalerCntr_beamOff;
UInt_t  qBCM4AScalerCntr_beamOn, qBCM4AScalerCntr_beamOff;
UInt_t  qBCM4BScalerCntr_beamOn, qBCM4BScalerCntr_beamOff;
UInt_t  qBCM4CScalerCntr_beamOn, qBCM4CScalerCntr_beamOff;
UInt_t  qUnserScalerCntr_beamOn, qUnserScalerCntr_beamOff;

UInt_t elloScalerCntr_beamOn, elloScalerCntr_beamOff;
UInt_t elloloScalerCntr_beamOn, elloloScalerCntr_beamOff;
UInt_t elhiScalerCntr_beamOn, elhiScalerCntr_beamOff;
UInt_t elrealScalerCntr_beamOn, elrealScalerCntr_beamOff;
UInt_t elcleanScalerCntr_beamOn, elcleanScalerCntr_beamOff;
UInt_t prloScalerCntr_beamOn, prloScalerCntr_beamOff;
UInt_t prhiScalerCntr_beamOn, prhiScalerCntr_beamOff;
UInt_t ncerScalerCntr_beamOn, ncerScalerCntr_beamOff;
UInt_t cerScalerCntr_beamOn, cerScalerCntr_beamOff;
UInt_t hcerScalerCntr_beamOn, hcerScalerCntr_beamOff;
UInt_t stofScalerCntr_beamOn, stofScalerCntr_beamOff;
UInt_t s1xScalerCntr_beamOn, s1xScalerCntr_beamOff;
UInt_t s1yScalerCntr_beamOn, s1yScalerCntr_beamOff;
UInt_t s2xScalerCntr_beamOn, s2xScalerCntr_beamOff;
UInt_t s2yScalerCntr_beamOn, s2yScalerCntr_beamOff;
UInt_t s1xs1yScalerCntr_beamOn, s1xs1yScalerCntr_beamOff;
UInt_t s2xs2yScalerCntr_beamOn, s2xs2yScalerCntr_beamOff;

UInt_t oneMHzScalerCntr_beamOn, oneMHzScalerCntr_beamOff;

std::ofstream scalerOutfile;
std::ofstream scalerRatesOutfile;
std::ofstream bcmOutfile;
const char* scalerFileName="UTIL_XEM/RUN_INFO/shms_scalers.dat";
const char* scalerRatesFileName="UTIL_XEM/RUN_INFO/shms_scaler_rates.dat";
const char* scalerBCMName="UTIL_XEM/RUN_INFO/shms_bcm.dat";
void initializeFiles() {
  scalerOutfile.open(scalerFileName);
  scalerRatesOutfile.open(scalerRatesFileName);
  bcmOutfile.open(scalerBCMName);
  //SHMS
  //scalerOutfile << "RUN,edtm,trig1,trig2,trig3,trig4,trig5,trig6,elreal,elclean,ello,ellolo,elhi,prlo,prhi,ncer,hcer,stof,s1x,s1y,s2x,s2y,s1xs1y,s2xs2y,1MHz\n";
  //scalerRatesOutfile << "RUN,r_edtm,r_trig1,r_trig2,r_trig3,r_trig4,r_trig5,r_trig6,r_elreal,r_elclean,r_ello,r_ellolo,r_elhi,r_prlo,r_prhi,r_ncer,r_hcer,r_stof,r_s1x,r_s1y,r_s2x,r_s2y,r_s1xs1y,r_s2xs2y\n";
  //bcmOutfile << "RUN,qBCM1,qBCM2,qBCM4A,qBCM4B,qBCM4C\n";
  //HMS
  scalerOutfile << "RUN,edtm,trig1,trig2,trig3,trig4,trig5,trig6,elreal,elclean,ello,ellolo,elhi,prlo,prhi,cer,stof,s1x,s1y,s2x,s2y,s1xs1y,s2xs2y,1MHz\n";
  scalerRatesOutfile << "RUN,r_edtm,r_trig1,r_trig2,r_trig3,r_trig4,r_trig5,r_trig6,r_elreal,r_elclean,r_ello,r_ellolo,r_elhi,r_prlo,r_prhi,r_ncer,r_hcer,r_stof,r_s1x,r_s1y,r_s2x,r_s2y,r_s1xs1y,r_s2xs2y\n";
  bcmOutfile << "RUN,qBCM1,qBCM2,qBCM4A,qBCM4B,qBCM4C\n";
  scalerOutfile.close();
  scalerRatesOutfile.close();
  bcmOutfile.close();
  return;
}

bool currentCut(double scalerCurrent, bool initialize=false, int method=0) {
  bool initialized=false;
  
  return true;
}

int scalerAnalysis(int runNo, double setCurrent, string SPEC, string spec, Bool_t tightCut=true) {
  int kin = 0;

  cout << Form(formatRootFilePath, SPEC.c_str(), spec.c_str(), runNo) << endl;

  TFile *file = TFile::Open(Form(formatRootFilePath, SPEC.c_str(), spec.c_str(),runNo));
  TH1F::SetDefaultSumw2(kTRUE);

  if(file->GetListOfKeys()->Contains("TSP")) {
    tScaler  = (TTree*)file->Get("TSP");
    fSpecName = "shms";
    fSpecCap  = "P";
    fSpecLow = "p";
  }
  else if(file->GetListOfKeys()->Contains("TSH")) {
    tScaler  = (TTree*)file->Get("TSH");
    fSpecName = "hms";
    fSpecCap  = "H";
    fSpecLow = "h";
  }
  else {
    cout << "Error: couldn't find the Scaler Tree" << endl;
    return -1;
  }

  if(!tightCut) {
    cout << "Using current cut of 5uA\n";
    isCutStr = "NoCut";
    setCurrent = 5;
  }

  //Create Histograms for diagnostics
  //Scaler Diagnostic Plots
  //h_BCM_Current = new TH1F("h_BCM_Current",Form("%s %s Current",fSpecName.c_str(), BCM_Name), 1760, 2, 90);
  //h2_BCM_IvsT = new TH2F("h2_BCM_IvsT", Form("%s %s Current vs. Time",fSpecName.c_str(), BCM_Name), 2000,0,2000,200,0,100);

  //Scaler Leaves
  tScaler->SetBranchAddress("evNumber", &evtNum);
  //DAQ Trigger Scalers
  tScaler->SetBranchAddress(Form("%s.%sTRIG1.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &trig1Scaler);
  tScaler->SetBranchAddress(Form("%s.%sTRIG2.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &trig2Scaler);
  tScaler->SetBranchAddress(Form("%s.%sTRIG3.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &trig3Scaler);
  tScaler->SetBranchAddress(Form("%s.%sTRIG4.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &trig4Scaler);
  tScaler->SetBranchAddress(Form("%s.%sTRIG5.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &trig5Scaler);
  tScaler->SetBranchAddress(Form("%s.%sTRIG6.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &trig6Scaler);
  tScaler->SetBranchAddress(Form("%s.EDTM.scaler",fSpecCap.c_str() ), &edtmScaler);
  //Pre-Trigger Scalers
  tScaler->SetBranchAddress(Form("%s.%sEL_LO.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &elloScaler);
  tScaler->SetBranchAddress(Form("%s.%sEL_LO_LO.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &elloloScaler);
  tScaler->SetBranchAddress(Form("%s.%sEL_HI.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &elhiScaler);
  tScaler->SetBranchAddress(Form("%s.%sSTOF.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &stofScaler);
  tScaler->SetBranchAddress(Form("%s.%sEL_REAL.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &elrealScaler);
  tScaler->SetBranchAddress(Form("%s.%sEL_CLEAN.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &elcleanScaler);
  //Things that don't start with P.p
  tScaler->SetBranchAddress(Form("%s.PRLO.scaler",fSpecCap.c_str() ), &prloScaler);
  tScaler->SetBranchAddress(Form("%s.PRHI.scaler",fSpecCap.c_str() ), &prhiScaler);
  tScaler->SetBranchAddress(Form("%s.NCER.scaler",fSpecCap.c_str() ), &ncerScaler);
  tScaler->SetBranchAddress(Form("%s.HCER.scaler",fSpecCap.c_str() ), &hcerScaler);
  tScaler->SetBranchAddress(Form("%s.CER.scaler",fSpecCap.c_str() ), &cerScaler);
  //Hodoscope Plane Scalers
  tScaler->SetBranchAddress(Form("%s.S1X.scaler", fSpecCap.c_str() ), &s1xScaler);
  tScaler->SetBranchAddress(Form("%s.S1Y.scaler", fSpecCap.c_str() ), &s1yScaler);
  tScaler->SetBranchAddress(Form("%s.S2X.scaler", fSpecCap.c_str() ), &s2xScaler);
  tScaler->SetBranchAddress(Form("%s.S2Y.scaler", fSpecCap.c_str() ), &s2yScaler);
  tScaler->SetBranchAddress(Form("%s.S1XS1Y.scaler", fSpecCap.c_str() ), &s1xs1yScaler);
  tScaler->SetBranchAddress(Form("%s.S2XS2Y.scaler", fSpecCap.c_str() ), &s2xs2yScaler);
  //Old Computer Live Time Scalers
  tScaler->SetBranchAddress(Form("%s.%sPRE40.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &pre40Scaler);
  tScaler->SetBranchAddress(Form("%s.%sPRE100.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &pre100Scaler);
  tScaler->SetBranchAddress(Form("%s.%sPRE150.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &pre150Scaler);
  tScaler->SetBranchAddress(Form("%s.%sPRE200.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &pre200Scaler);
  //TREF1 or TREF 3 scaler
  if(std::strncmp(fSpecLow.c_str(),"p",0)) {
    tScaler->SetBranchAddress(Form("%s.%sTREF3.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &trefScaler);
  } else if(std::strncmp(fSpecLow.c_str(),"h",0)) {
    tScaler->SetBranchAddress(Form("%s.%sTREF1.scaler",fSpecCap.c_str(),fSpecLow.c_str() ), &trefScaler);
  }
  //BCM Scalers (Charge and Current)
  tScaler->SetBranchAddress(Form("%s.BCM1.scalerCharge", fSpecCap.c_str()), &bcm1ChargeScaler);
  tScaler->SetBranchAddress(Form("%s.BCM1.scalerCurrent", fSpecCap.c_str()), &bcm1CurrentScaler);
  tScaler->SetBranchAddress(Form("%s.BCM2.scalerCharge", fSpecCap.c_str()), &bcm2ChargeScaler);
  tScaler->SetBranchAddress(Form("%s.BCM2.scalerCurrent", fSpecCap.c_str()), &bcm2CurrentScaler);
  tScaler->SetBranchAddress(Form("%s.BCM4A.scalerCharge", fSpecCap.c_str()), &bcm4aChargeScaler);
  tScaler->SetBranchAddress(Form("%s.BCM4A.scalerCurrent", fSpecCap.c_str()), &bcm4aCurrentScaler);
  tScaler->SetBranchAddress(Form("%s.BCM4B.scalerCharge", fSpecCap.c_str()), &bcm4bChargeScaler);
  tScaler->SetBranchAddress(Form("%s.BCM4B.scalerCurrent", fSpecCap.c_str()), &bcm4bCurrentScaler);
  tScaler->SetBranchAddress(Form("%s.BCM4C.scalerCharge", fSpecCap.c_str()), &bcm4cChargeScaler);
  tScaler->SetBranchAddress(Form("%s.BCM4C.scalerCurrent", fSpecCap.c_str()), &bcm4cCurrentScaler);
  tScaler->SetBranchAddress(Form("%s.Unser.scalerCharge", fSpecCap.c_str()), &unserChargeScaler);
  tScaler->SetBranchAddress(Form("%s.Unser.scalerCurrent", fSpecCap.c_str()), &unserCurrentScaler);
  //1MHz Scaler Time Readback
  tScaler->SetBranchAddress(Form("%s.1MHz.scaler", fSpecCap.c_str() ), &oneMHzScaler);

  //Initialize function for checking BCM based on user input
  //5uA cut, current threshold cut, set current +/- tolerance cut
  //Human validated for threshold cut and tolerance cut
  //BCM option (string name)
  //
  edtmScalerCntr_beamOn = 0;   edtmScalerCntr_beamOff = 0;
  trig1ScalerCntr_beamOn  = 0;   trig1ScalerCntr_beamOff = 0;
  trig2ScalerCntr_beamOn  = 0;   trig2ScalerCntr_beamOff = 0;
  trig3ScalerCntr_beamOn  = 0;   trig3ScalerCntr_beamOff = 0;
  trig4ScalerCntr_beamOn  = 0;   trig4ScalerCntr_beamOff = 0;
  trig5ScalerCntr_beamOn  = 0;   trig5ScalerCntr_beamOff = 0;
  trig6ScalerCntr_beamOn  = 0;   trig6ScalerCntr_beamOff = 0;

  qBCM1ScalerCntr_beamOn = 0; qBCM1ScalerCntr_beamOff = 0;
  qBCM2ScalerCntr_beamOn = 0; qBCM2ScalerCntr_beamOff = 0;
  qBCM4AScalerCntr_beamOn = 0; qBCM4AScalerCntr_beamOff = 0;
  qBCM4BScalerCntr_beamOn = 0; qBCM4BScalerCntr_beamOff = 0;
  qBCM4CScalerCntr_beamOn = 0; qBCM4CScalerCntr_beamOff = 0;
  qUnserScalerCntr_beamOn = 0; qUnserScalerCntr_beamOff = 0;

  elloScalerCntr_beamOn  = 0;   elloScalerCntr_beamOff = 0;
  elloloScalerCntr_beamOn  = 0;   elloloScalerCntr_beamOff = 0;
  elhiScalerCntr_beamOn  = 0;   elhiScalerCntr_beamOff = 0;
  elrealScalerCntr_beamOn  = 0;   elrealScalerCntr_beamOff = 0;
  elcleanScalerCntr_beamOn  = 0;   elcleanScalerCntr_beamOff = 0;
  prloScalerCntr_beamOn  = 0;   prloScalerCntr_beamOff = 0;
  prhiScalerCntr_beamOn  = 0;   prhiScalerCntr_beamOff = 0;
  ncerScalerCntr_beamOn  = 0;   ncerScalerCntr_beamOff = 0;
  hcerScalerCntr_beamOn  = 0;   hcerScalerCntr_beamOff = 0;
  cerScalerCntr_beamOn  = 0;   cerScalerCntr_beamOff = 0;

  stofScalerCntr_beamOn  = 0;   stofScalerCntr_beamOff = 0;
  s1xScalerCntr_beamOn  = 0;   s1xScalerCntr_beamOff = 0;
  s1yScalerCntr_beamOn  = 0;   s1yScalerCntr_beamOff = 0;
  s2xScalerCntr_beamOn  = 0;   s2xScalerCntr_beamOff = 0;
  s2yScalerCntr_beamOn  = 0;   s2yScalerCntr_beamOff = 0;
  s1xs1yScalerCntr_beamOn  = 0;   s1xs1yScalerCntr_beamOff = 0;
  s2xs2yScalerCntr_beamOn  = 0;   s2xs2yScalerCntr_beamOff = 0;
  oneMHzScalerCntr_beamOn = 0;  oneMHzScalerCntr_beamOff = 0;

  scalerEntries = tScaler->GetEntries();
  for(int jevent = 0; jevent < scalerEntries; jevent++) { 
    tScaler->GetEntry(jevent);
    cutCurrentBranch = bcm1CurrentScaler;
    if (cutCurrentBranch >= setCurrent) { 
      edtmScalerCntr_beamOn = edtmScaler - edtmScalerCntr_beamOff;
      trig1ScalerCntr_beamOn = trig1Scaler - trig1ScalerCntr_beamOff;
      trig2ScalerCntr_beamOn = trig2Scaler - trig2ScalerCntr_beamOff;
      trig3ScalerCntr_beamOn = trig3Scaler - trig3ScalerCntr_beamOff;
      trig4ScalerCntr_beamOn = trig4Scaler - trig4ScalerCntr_beamOff;
      trig5ScalerCntr_beamOn = trig5Scaler - trig5ScalerCntr_beamOff;
      trig6ScalerCntr_beamOn = trig6Scaler - trig6ScalerCntr_beamOff;

      elloScalerCntr_beamOn  =  elloScaler - elloScalerCntr_beamOff;
      elloloScalerCntr_beamOn  =  elloloScaler - elloloScalerCntr_beamOff;
      elhiScalerCntr_beamOn  =  elhiScaler - elhiScalerCntr_beamOff;
      elrealScalerCntr_beamOn = elrealScaler - elrealScalerCntr_beamOff;
      elcleanScalerCntr_beamOn = elcleanScaler - elcleanScalerCntr_beamOff;
      prloScalerCntr_beamOn  =  prloScaler - prloScalerCntr_beamOff;
      prhiScalerCntr_beamOn  =  prhiScaler - prhiScalerCntr_beamOff;
      ncerScalerCntr_beamOn  =  ncerScaler - ncerScalerCntr_beamOff;
      hcerScalerCntr_beamOn  =  hcerScaler - hcerScalerCntr_beamOff;
      cerScalerCntr_beamOn  =  cerScaler - cerScalerCntr_beamOff;

      stofScalerCntr_beamOn  = stofScaler - stofScalerCntr_beamOff;
      s1xScalerCntr_beamOn  = s1xScaler - s1xScalerCntr_beamOff;
      s1yScalerCntr_beamOn  = s1yScaler - s1yScalerCntr_beamOff;
      s2xScalerCntr_beamOn  = s2xScaler - s2xScalerCntr_beamOff;
      s2yScalerCntr_beamOn  = s2yScaler - s2yScalerCntr_beamOff;
      s1xs1yScalerCntr_beamOn  = s1xs1yScaler - s1xs1yScalerCntr_beamOff;
      s2xs2yScalerCntr_beamOn  = s2xs2yScaler - s2xs2yScalerCntr_beamOff;

      qBCM1ScalerCntr_beamOn = bcm1ChargeScaler - qBCM1ScalerCntr_beamOff;
      qBCM2ScalerCntr_beamOn = bcm2ChargeScaler - qBCM2ScalerCntr_beamOff;
      qBCM4AScalerCntr_beamOn = bcm4aChargeScaler - qBCM4AScalerCntr_beamOff;
      qBCM4BScalerCntr_beamOn = bcm4bChargeScaler - qBCM4BScalerCntr_beamOff;
      qBCM4CScalerCntr_beamOn = bcm4cChargeScaler - qBCM4CScalerCntr_beamOff;
      qUnserScalerCntr_beamOn = unserChargeScaler - qUnserScalerCntr_beamOff;

      oneMHzScalerCntr_beamOn = oneMHzScaler - oneMHzScalerCntr_beamOff;
    }
    if (cutCurrentBranch < setCurrent) { 
      edtmScalerCntr_beamOff = edtmScaler - edtmScalerCntr_beamOn;
      trig1ScalerCntr_beamOff = trig1Scaler - trig1ScalerCntr_beamOn;
      trig2ScalerCntr_beamOff = trig2Scaler - trig2ScalerCntr_beamOn;
      trig3ScalerCntr_beamOff = trig3Scaler - trig3ScalerCntr_beamOn;
      trig4ScalerCntr_beamOff = trig4Scaler - trig4ScalerCntr_beamOn;
      trig5ScalerCntr_beamOff = trig5Scaler - trig5ScalerCntr_beamOn;
      trig6ScalerCntr_beamOff = trig6Scaler - trig6ScalerCntr_beamOn;

      elloScalerCntr_beamOff  =  elloScaler - elloScalerCntr_beamOn;
      elloloScalerCntr_beamOff  =  elloloScaler - elloloScalerCntr_beamOn;
      elhiScalerCntr_beamOff  =  elhiScaler - elhiScalerCntr_beamOn;
      elrealScalerCntr_beamOff = elrealScaler - elrealScalerCntr_beamOn;
      elcleanScalerCntr_beamOff = elcleanScaler - elcleanScalerCntr_beamOn;
      prloScalerCntr_beamOff  =  prloScaler - prloScalerCntr_beamOn;
      prhiScalerCntr_beamOff  =  prhiScaler - prhiScalerCntr_beamOn;
      ncerScalerCntr_beamOff  =  ncerScaler - ncerScalerCntr_beamOn;
      hcerScalerCntr_beamOff  =  hcerScaler - hcerScalerCntr_beamOn;
      cerScalerCntr_beamOff  =  cerScaler - cerScalerCntr_beamOn;

      stofScalerCntr_beamOff  = stofScaler - stofScalerCntr_beamOn;
      s1xScalerCntr_beamOff  = s1xScaler - s1xScalerCntr_beamOn;
      s1yScalerCntr_beamOff  = s1yScaler - s1yScalerCntr_beamOn;
      s2xScalerCntr_beamOff  = s2xScaler - s2xScalerCntr_beamOn;
      s2yScalerCntr_beamOff  = s2yScaler - s2yScalerCntr_beamOn;
      s1xs1yScalerCntr_beamOff  = s1xs1yScaler - s1xs1yScalerCntr_beamOn;
      s2xs2yScalerCntr_beamOff  = s2xs2yScaler - s2xs2yScalerCntr_beamOn;

      qBCM1ScalerCntr_beamOff = bcm1ChargeScaler - qBCM1ScalerCntr_beamOn;
      qBCM2ScalerCntr_beamOff = bcm2ChargeScaler - qBCM2ScalerCntr_beamOn;
      qBCM4AScalerCntr_beamOff = bcm4aChargeScaler - qBCM4AScalerCntr_beamOn;
      qBCM4BScalerCntr_beamOff = bcm4bChargeScaler - qBCM4BScalerCntr_beamOn;
      qBCM4CScalerCntr_beamOff = bcm4cChargeScaler - qBCM4CScalerCntr_beamOn;
      qUnserScalerCntr_beamOff = unserChargeScaler - qUnserScalerCntr_beamOn;

      oneMHzScalerCntr_beamOff = oneMHzScaler - oneMHzScalerCntr_beamOn;
    }
    if (jevent % 1000 == 0 && jevent != 0)
      cout << jevent << " Events Have Been Processed..." << endl;
  } // scaler tree entries loop

  //SHMS
  /*
  scalerOutfile.open(scalerFileName, std::ios_base::app); // append instead of overwrite
  scalerOutfile << runNo << "," << edtmScalerCntr_beamOn << "," << trig1ScalerCntr_beamOn << "," << trig2ScalerCntr_beamOn << "," <<trig3ScalerCntr_beamOn << "," << trig4ScalerCntr_beamOn << "," << trig5ScalerCntr_beamOn << "," <<trig6ScalerCntr_beamOn << "," << elrealScalerCntr_beamOn << "," << elcleanScalerCntr_beamOn << "," << elloScalerCntr_beamOn << "," << elloloScalerCntr_beamOn << "," << elhiScalerCntr_beamOn << "," << prloScalerCntr_beamOn << "," << prhiScalerCntr_beamOn << "," << ncerScalerCntr_beamOn << "," << hcerScalerCntr_beamOn << "," << stofScalerCntr_beamOn << "," << s1xScalerCntr_beamOn << "," << s1yScalerCntr_beamOn << "," << s2xScalerCntr_beamOn << "," << s2yScalerCntr_beamOn << "," << s1xs1yScalerCntr_beamOn << "," << s2xs2yScalerCntr_beamOn << "," << oneMHzScalerCntr_beamOn << endl;

  scalerRatesOutfile.open(scalerRatesFileName, std::ios_base::app); // append instead of overwrite
  double cutScalerTime = oneMHzScalerCntr_beamOn * 1.E6;
  scalerRatesOutfile << runNo << "," << (float)edtmScalerCntr_beamOn/cutScalerTime  << "," << (float)trig1ScalerCntr_beamOn/cutScalerTime  << "," << (float)trig2ScalerCntr_beamOn << "," <<trig3ScalerCntr_beamOn/cutScalerTime  << "," << (float)trig4ScalerCntr_beamOn/cutScalerTime  << "," << (float)trig5ScalerCntr_beamOn << "," <<trig6ScalerCntr_beamOn/cutScalerTime  << "," << (float)elrealScalerCntr_beamOn/cutScalerTime  << "," << (float)elcleanScalerCntr_beamOn/cutScalerTime  << "," << (float)elloScalerCntr_beamOn/cutScalerTime  << "," << (float)elloloScalerCntr_beamOn/cutScalerTime  << "," << (float)elhiScalerCntr_beamOn/cutScalerTime  << "," << (float)prloScalerCntr_beamOn/cutScalerTime  << "," << (float)prhiScalerCntr_beamOn/cutScalerTime  << "," << (float)ncerScalerCntr_beamOn/cutScalerTime  << "," << (float)hcerScalerCntr_beamOn/cutScalerTime  << "," << (float)stofScalerCntr_beamOn/cutScalerTime  << "," << (float)s1xScalerCntr_beamOn/cutScalerTime  << "," << (float)s1yScalerCntr_beamOn/cutScalerTime  << "," << (float)s2xScalerCntr_beamOn/cutScalerTime  << "," << (float)s2yScalerCntr_beamOn/cutScalerTime  << "," << (float)s1xs1yScalerCntr_beamOn/cutScalerTime  << "," << (float)s2xs2yScalerCntr_beamOn/cutScalerTime << endl;

  bcmOutfile.open(scalerBCMName, std::ios_base::app); // append instead of overwrite
  bcmOutfile << runNo << "," << qBCM1ScalerCntr_beamOn << "," << qBCM2ScalerCntr_beamOn << "," << qBCM4AScalerCntr_beamOn << "," << qBCM4BScalerCntr_beamOn << "," << qBCM4CScalerCntr_beamOn << endl;
  */
  //HMS
  scalerOutfile.open(scalerFileName, std::ios_base::app); // append instead of overwrite
  scalerOutfile << runNo << "," << edtmScalerCntr_beamOn << "," << trig1ScalerCntr_beamOn << "," << trig2ScalerCntr_beamOn << "," <<trig3ScalerCntr_beamOn << "," << trig4ScalerCntr_beamOn << "," << trig5ScalerCntr_beamOn << "," <<trig6ScalerCntr_beamOn << "," << elrealScalerCntr_beamOn << "," << elcleanScalerCntr_beamOn << "," << elloScalerCntr_beamOn << "," << elloloScalerCntr_beamOn << "," << elhiScalerCntr_beamOn << "," << prloScalerCntr_beamOn << "," << prhiScalerCntr_beamOn << "," << cerScalerCntr_beamOn << "," << stofScalerCntr_beamOn << "," << s1xScalerCntr_beamOn << "," << s1yScalerCntr_beamOn << "," << s2xScalerCntr_beamOn << "," << s2yScalerCntr_beamOn << "," << s1xs1yScalerCntr_beamOn << "," << s2xs2yScalerCntr_beamOn << "," << oneMHzScalerCntr_beamOn << ", " << qBCM4AScalerCntr_beamOn << endl;

  scalerRatesOutfile.open(scalerRatesFileName, std::ios_base::app); // append instead of overwrite
  double cutScalerTime = oneMHzScalerCntr_beamOn * 1.E6;
  scalerRatesOutfile << runNo << "," << (float)edtmScalerCntr_beamOn/cutScalerTime  << "," << (float)trig1ScalerCntr_beamOn/cutScalerTime  << "," << (float)trig2ScalerCntr_beamOn << "," <<trig3ScalerCntr_beamOn/cutScalerTime  << "," << (float)trig4ScalerCntr_beamOn/cutScalerTime  << "," << (float)trig5ScalerCntr_beamOn << "," <<trig6ScalerCntr_beamOn/cutScalerTime  << "," << (float)elrealScalerCntr_beamOn/cutScalerTime  << "," << (float)elcleanScalerCntr_beamOn/cutScalerTime  << "," << (float)elloScalerCntr_beamOn/cutScalerTime  << "," << (float)elloloScalerCntr_beamOn/cutScalerTime  << "," << (float)elhiScalerCntr_beamOn/cutScalerTime  << "," << (float)prloScalerCntr_beamOn/cutScalerTime  << "," << (float)prhiScalerCntr_beamOn/cutScalerTime  << "," << (float)cerScalerCntr_beamOn/cutScalerTime << "," << (float)stofScalerCntr_beamOn/cutScalerTime  << "," << (float)s1xScalerCntr_beamOn/cutScalerTime  << "," << (float)s1yScalerCntr_beamOn/cutScalerTime  << "," << (float)s2xScalerCntr_beamOn/cutScalerTime  << "," << (float)s2yScalerCntr_beamOn/cutScalerTime  << "," << (float)s1xs1yScalerCntr_beamOn/cutScalerTime  << "," << (float)s2xs2yScalerCntr_beamOn/cutScalerTime << endl;

  bcmOutfile.open(scalerBCMName, std::ios_base::app); // append instead of overwrite
  bcmOutfile << runNo << "," << qBCM1ScalerCntr_beamOn << "," << qBCM2ScalerCntr_beamOn << "," << qBCM4AScalerCntr_beamOn << "," << qBCM4BScalerCntr_beamOn << "," << qBCM4CScalerCntr_beamOn << endl;



  cout << runNo << "," << edtmScalerCntr_beamOn << "," << trig1ScalerCntr_beamOn << "," << trig2ScalerCntr_beamOn << "," <<trig3ScalerCntr_beamOn << "," << trig4ScalerCntr_beamOn << "," << trig5ScalerCntr_beamOn << "," <<trig6ScalerCntr_beamOn << "," << elloScalerCntr_beamOn << "," << elloloScalerCntr_beamOn << "," << elhiScalerCntr_beamOn << "," << prloScalerCntr_beamOn << "," << prhiScalerCntr_beamOn << "," << cerScalerCntr_beamOn << ", " << ncerScalerCntr_beamOn << "," << hcerScalerCntr_beamOn << "," << stofScalerCntr_beamOn << "," << s1xScalerCntr_beamOn << "," << s1yScalerCntr_beamOn << "," << s2xScalerCntr_beamOn << "," << s2yScalerCntr_beamOn << "," << s1xs1yScalerCntr_beamOn << "," << s2xs2yScalerCntr_beamOn << "," << qBCM1ScalerCntr_beamOn << endl;
  scalerOutfile.close();
  scalerRatesOutfile.close();
  bcmOutfile.close();
  return 0;
}

int run_scalerAnalysis() {
  string runlist = "./UTIL_XEM/RUN_INFO/hms_boil_runs.dat";
  ifstream rl_stream(runlist);
  int currentRun;
  float cutCurrent;
  string line;
  while(getline(rl_stream, line)) {
    stringstream ss(line);
    ss >> currentRun >> cutCurrent;
    cout << "Working on run: " << currentRun << "\n";
    //int runNo, double setCurrent, string SPEC, string spec, Bool_t tightCut=true
    scalerAnalysis(currentRun,cutCurrent,"HMS","hms",true);
  }

    return 0;
}
