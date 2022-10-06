/* 
Cameron Cotton - 10/20/2021
Used to get a quick count of the number of electrons in a given SHMS/HMS dataset.
*/
void run_el_counter_shms(TString file_name = "") {
	TFile *file0=new TFile(file_name);
	TTree *tr1=(TTree*)file0->Get("T");
	
	Double_t dp, etottracknorm, npeSum;
	tr1->SetBranchAddress("P.gtr.dp",&dp);
	tr1->SetBranchAddress("P.cal.etottracknorm",&etottracknorm);
	tr1->SetBranchAddress("P.ngcer.npeSum",&npeSum);
	Int_t nentries = (Int_t)tr1->GetEntries();
	Int_t counter = 0;
	for (Int_t i = 0; i < nentries; i++){
		tr1->GetEntry(i);
		if (etottracknorm > 0.7 && etottracknorm < 2.0 && dp > -10 && dp < 22 && npeSum > 2){ //cuts
			counter = counter+1;
		}
	}
	cout << "Electron Count = " << counter << endl;
	// Notes on CUTS:
	// Cuts are loose. Poorly calibrated replay may change the result considerably.
}

void run_calib_counter_shms(TString file_name = "") {
	TFile *file0=new TFile(file_name);
	TTree *tr1=(TTree*)file0->Get("T");
	
	Double_t dp, etottracknorm, npeSum;
	tr1->SetBranchAddress("P.gtr.dp",&dp);
	tr1->SetBranchAddress("P.cal.etottracknorm",&etottracknorm);
	tr1->SetBranchAddress("P.ngcer.npeSum",&npeSum);
	Int_t nentries = (Int_t)tr1->GetEntries();
	Int_t counter = 0;
	for (Int_t i = 0; i < nentries; i++){
		tr1->GetEntry(i);
		if (dp > -10 && dp < 22){ //cuts
			counter = counter+1;
		}
	}
	cout << "Event count with delta cut only, Count = " << counter << endl;
	// Notes on CUTS:
	// Cuts are loose. Poorly calibrated replay may change the result considerably.
}

void run_el_counter_hms(TString file_name = "") {
	TFile *file0=new TFile(file_name);
	TTree *tr1=(TTree*)file0->Get("T");
	
	Double_t dp, etottracknorm, npeSum;
	tr1->SetBranchAddress("H.gtr.dp",&dp);
	tr1->SetBranchAddress("H.cal.etottracknorm",&etottracknorm);
	tr1->SetBranchAddress("H.cer.npeSum",&npeSum);
	Int_t nentries = (Int_t)tr1->GetEntries();
	Int_t counter = 0;
	for (Int_t i = 0; i < nentries; i++){
		tr1->GetEntry(i);
		if (etottracknorm > 0.7 && etottracknorm < 2.0 && dp > -8 && dp < 8 && npeSum > 2){ //cuts
			counter = counter+1;
		}
	}
	cout << "Electron Count = " << counter << endl;
	// Notes on CUTS:
	// Cuts are loose. Poorly calibrated replay may change the result considerably.
}

void run_calib_counter_hms(TString file_name = "") {
	TFile *file0=new TFile(file_name);
	TTree *tr1=(TTree*)file0->Get("T");
	
	Double_t dp, etottracknorm, npeSum;
	tr1->SetBranchAddress("H.gtr.dp",&dp);
	tr1->SetBranchAddress("H.cal.etottracknorm",&etottracknorm);
	tr1->SetBranchAddress("H.cer.npeSum",&npeSum);
	Int_t nentries = (Int_t)tr1->GetEntries();
	Int_t counter = 0;
	for (Int_t i = 0; i < nentries; i++){
		tr1->GetEntry(i);
		if (dp > -8 && dp < 8){ //cuts
			counter = counter+1;
		}
	}
	cout << "Event count with delta cut only, Count = " << counter << endl;
	// Notes on CUTS:
	// Cuts are loose. Poorly calibrated replay may change the result considerably.
}
