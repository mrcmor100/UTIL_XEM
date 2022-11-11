/* 
Cameron Cotton - 10/20/2021
Used to get a quick count of the number of electrons in a given SHMS/HMS dataset.
*/
void run_el_counter_shms(TString file_name = "") {
	TFile *file0=new TFile(file_name);
	TTree *tr1=(TTree*)file0->Get("T");
	
	Double_t dp, etottracknorm, npeSum, xbj;
	TCanvas *canvas1 = new TCanvas("canvas1","Double-click to close window!");
	TH1F *h1 = new TH1F("h1","Ecal/P",50,-0.1,1.5);
	TH1F *h2 = new TH1F("h2","Ecal/P (cut)",50,-0.1,1.5);
	tr1->SetBranchAddress("P.gtr.dp",&dp);
	tr1->SetBranchAddress("P.cal.etottracknorm",&etottracknorm);
	tr1->SetBranchAddress("P.ngcer.npeSum",&npeSum);
	tr1->SetBranchAddress("P.kin.x_bj",&xbj);
	Int_t nentries = (Int_t)tr1->GetEntries();
	Int_t counter = 0;
	for (Int_t i = 0; i < nentries; i++){
		tr1->GetEntry(i);
		h1->Fill(etottracknorm);
		//		if (etottracknorm > 0.7 && etottracknorm < 2.0 && dp > -10 && dp < 22 && npeSum > 2 && xbj > 1.4 && xbj < 1.95){ //cuts
		if (etottracknorm > 0.7 && etottracknorm < 2.0 && dp > -10 && dp < 22 && npeSum > 2 && xbj > 1.4){ //cuts
			counter = counter+1;
			h2->Fill(etottracknorm);
		}
	}
	cout << "Electron Count = " << counter << endl;
	// Notes on CUTS:
	// Cuts are loose. Poorly calibrated replay may change the result considerably.
	canvas1->SetLogy();
	h1->SetTitle(Form("All events: %d",nentries));
	h2->SetTitle(Form("Number of good electrons: %d",counter));
	h1->GetXaxis()->SetTitle("Calorimeter E/P");
	h1->Draw();
	h2->SetLineColor(kRed);
	h2->Draw("same");
	TLegend* legend_of_dave = canvas1->BuildLegend();
        legend_of_dave->SetTextSize(0.04);
        legend_of_dave->SetBorderSize(0);
        legend_of_dave->SetFillStyle(0);
	cout << "Double click in root window when you feel like it ";
	canvas1->WaitPrimitive();

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
  //       gROOT->SetBorderSize(0);
	TFile *file0=new TFile(file_name);
	TTree *tr1=(TTree*)file0->Get("T");
	
	Double_t dp, etottracknorm, npeSum;
	TCanvas *canvas1 = new TCanvas("canvas1","Double-click to close window!");
	TH1F *h1 = new TH1F("h1","Ecal/P",50,-0.1,1.5);
	TH1F *h2 = new TH1F("h2","Ecal/P (cut)",50,-0.1,1.5);
	tr1->SetBranchAddress("H.gtr.dp",&dp);
	tr1->SetBranchAddress("H.cal.etottracknorm",&etottracknorm);
	tr1->SetBranchAddress("H.cer.npeSum",&npeSum);
	Int_t nentries = (Int_t)tr1->GetEntries();
	Int_t counter = 0;
	for (Int_t i = 0; i < nentries; i++){
		tr1->GetEntry(i);
		h1->Fill(etottracknorm);
		if (etottracknorm > 0.7 && etottracknorm < 2.0 && dp > -8 && dp < 8 && npeSum > 2){ //cuts
			counter = counter+1;
			h2->Fill(etottracknorm);
		}
	}
	cout << "Electron Count = " << counter << endl;
	// Notes on CUTS:
	// Cuts are loose. Poorly calibrated replay may change the result considerably.

	canvas1->SetLogy();
	h1->SetTitle(Form("All events: %d",nentries));
	h2->SetTitle(Form("Number of good electrons: %d",counter));
	h1->GetXaxis()->SetTitle("Calorimeter E/P");
	h1->Draw();
	h2->SetLineColor(kRed);
	h2->Draw("same");
	TLegend* legend_of_dave = canvas1->BuildLegend();
        legend_of_dave->SetTextSize(0.04);
        legend_of_dave->SetBorderSize(0);
        legend_of_dave->SetFillStyle(0);

	cout << "Double click in root window when Don " << endl ;
	canvas1->WaitPrimitive();
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
