

void makePlots_shms(int RunNumber=0) {
  
  TFile *f1 = new TFile("tmp.root","READ");
  TH1D* hPcal_E_p = (TH1D*) f1->Get("hPcal_E_p");
  TH1D* hPpre_E_p = (TH1D*) f1->Get("hPpre_E_p");
  TH1D* hPcer = (TH1D*) f1->Get("hPcer");
  TH2D* hPpre_vs_cal = (TH2D*) f1->Get("hPpre_vs_cal");
  TH1D* hPcal_E_p_elreal = (TH1D*) f1->Get("hPcal_E_p_elreal");
  TH1D* hPpre_E_p_elreal = (TH1D*) f1->Get("hPpre_E_p_elreal");
  TH2D* hPpre_vs_cal_elreal = (TH2D*) f1->Get("hPpre_vs_cal_elreal");
  TH1D* hPcal_E_p_elclean = (TH1D*) f1->Get("hPcal_E_p_elclean");
  TH1D* hPpre_E_p_elclean = (TH1D*) f1->Get("hPpre_E_p_elclean");
  TH2D* hPpre_vs_cal_elclean = (TH2D*) f1->Get("hPpre_vs_cal_elclean");
  TH1D* hPcal_E_p_ello = (TH1D*) f1->Get("hPcal_E_p_ello");
  TH1D* hPpre_E_p_ello = (TH1D*) f1->Get("hPpre_E_p_ello");
  TH2D* hPpre_vs_cal_ello = (TH2D*) f1->Get("hPpre_vs_cal_ello");
  TH1D* hPcal_E_p_ellolo = (TH1D*) f1->Get("hPcal_E_p_ellolo");
  TH1D* hPpre_E_p_ellolo = (TH1D*) f1->Get("hPpre_E_p_ellolo");
  TH2D* hPpre_vs_cal_ellolo = (TH2D*) f1->Get("hPpre_vs_cal_ellolo");
  TH1D* hPcal_E_p_elhi = (TH1D*) f1->Get("hPcal_E_p_elhi");
  TH1D* hPpre_E_p_elhi = (TH1D*) f1->Get("hPpre_E_p_elhi");
  TH2D* hPpre_vs_cal_elhi = (TH2D*) f1->Get("hPpre_vs_cal_elhi");
  TH1D* hPcal_E_p_prlo = (TH1D*) f1->Get("hPcal_E_p_prlo");
  TH1D* hPpre_E_p_prlo = (TH1D*) f1->Get("hPpre_E_p_prlo");
  TH2D* hPpre_vs_cal_prlo = (TH2D*) f1->Get("hPpre_vs_cal_prlo");
  TH1D* hPcal_E_p_prhi = (TH1D*) f1->Get("hPcal_E_p_prhi");
  TH1D* hPpre_E_p_prhi = (TH1D*) f1->Get("hPpre_E_p_prhi");
  TH2D* hPpre_vs_cal_prhi = (TH2D*) f1->Get("hPpre_vs_cal_prhi");
  //TH1D* hPcal_E_p_shlo = (TH1D*) f1->Get("hPcal_E_p_shlo");
  TH1D* hPpre_E_p_shlo = (TH1D*) f1->Get("hPpre_E_p_shlo");
  TH2D* hPpre_vs_cal_shlo = (TH2D*) f1->Get("hPpre_vs_cal_shlo");
  TH1D* hPcal_E_p_cer = (TH1D*) f1->Get("hPcal_E_p_cer");
  TH1D* hPpre_E_p_cer = (TH1D*) f1->Get("hPpre_E_p_cer");
  TH2D* hPpre_vs_cal_cer = (TH2D*) f1->Get("hPpre_vs_cal_cer");
  TH1D* hPcer_amp = (TH1D*) f1->Get("hPcer_amp");
  TH1D* hPcer_amp_cer = (TH1D*) f1->Get("hPcer_amp_cer");
  TH1D* hPpre_amp = (TH1D*) f1->Get("hPpre_amp");
  TH2D* hPpre_amp_vs_cal = (TH2D*) f1->Get("hPpre_amp_vs_cal");
  TH1D* hPpre_amp_prlo = (TH1D*) f1->Get("hPpre_amp_prlo");
  TH2D* hPpre_amp_vs_cal_prlo = (TH2D*) f1->Get("hPpre_amp_vs_cal_prlo");
  TH1D* hPpre_amp_prhi = (TH1D*) f1->Get("hPpre_amp_prhi");
  TH2D* hPpre_amp_vs_cal_prhi = (TH2D*) f1->Get("hPpre_amp_vs_cal_prhi");
  TH1D* hPcal_amp = (TH1D*) f1->Get("hPcal_amp");
  TH2D* hPsh_amp_vs_cal = (TH2D*) f1->Get("hPsh_amp_vs_cal");
  TH1D* hPcal_amp_shlo = (TH1D*) f1->Get("hPcal_amp_shlo");
  TH2D* hPsh_amp_vs_cal_shlo = (TH2D*) f1->Get("hPsh_amp_vs_cal_shlo");
  TH1D* hPcer_cer = (TH1D*) f1->Get("hPcer_cer");

          hPcal_E_p->SetLineColor(kBlack);
          hPcal_E_p->SetLineWidth(3.);
          hPcal_E_p->SetLineStyle(2);
          hPcal_E_p_elreal->SetLineColor(kRed);
          hPcal_E_p_elreal->SetLineWidth(2.);
          hPcal_E_p_elreal->SetLineStyle(2);
          hPcal_E_p_elclean->SetLineColor(kMagenta-8);
          hPcal_E_p_elclean->SetLineWidth(2.);
          hPcal_E_p_elclean->SetLineStyle(2);
          hPcal_E_p_ello->SetLineColor(kMagenta);
          hPcal_E_p_ello->SetLineWidth(2.);
          hPcal_E_p_ello->SetLineStyle(2);
          hPcal_E_p_elhi->SetLineColor(kGreen+1);
          hPcal_E_p_elhi->SetLineWidth(2.);
          hPcal_E_p_elhi->SetLineStyle(2);
          hPcal_E_p_prlo->SetLineColor(kOrange);
          hPcal_E_p_prlo->SetLineWidth(2.);
          hPcal_E_p_prlo->SetLineStyle(2);
          hPcal_E_p_prhi->SetLineColor(kBlue-3);
          hPcal_E_p_prhi->SetLineWidth(2.);
          hPcal_E_p_prhi->SetLineStyle(2);
          hPcal_E_p_cer->SetLineColor(kTeal-4);
          hPcal_E_p_cer->SetLineWidth(2.);
          hPcal_E_p_cer->SetLineStyle(2);

          hPpre_E_p->SetLineColor(kBlack);
          hPpre_E_p->SetLineWidth(3.);
          hPpre_E_p->SetLineStyle(2);
          hPpre_E_p_elreal->SetLineColor(kRed);
          hPpre_E_p_elreal->SetLineWidth(2.);
          hPpre_E_p_elreal->SetLineStyle(2);
          hPpre_E_p_elclean->SetLineColor(kMagenta-8);
          hPpre_E_p_elclean->SetLineWidth(2.);
          hPpre_E_p_elclean->SetLineStyle(2);
          hPpre_E_p_ello->SetLineColor(kMagenta);
          hPpre_E_p_ello->SetLineWidth(2.);
          hPpre_E_p_ello->SetLineStyle(2);
          hPpre_E_p_elhi->SetLineColor(kGreen+1);
          hPpre_E_p_elhi->SetLineWidth(2.);
          hPpre_E_p_elhi->SetLineStyle(2);
          hPpre_E_p_prlo->SetLineColor(kOrange);
          hPpre_E_p_prlo->SetLineWidth(2.);
          hPpre_E_p_prlo->SetLineStyle(2);
          hPpre_E_p_prhi->SetLineColor(kBlue-3);
          hPpre_E_p_prhi->SetLineWidth(2.);
          hPpre_E_p_prhi->SetLineStyle(2);
          hPpre_E_p_cer->SetLineColor(kTeal-4);
          hPpre_E_p_cer->SetLineWidth(2.);
          hPpre_E_p_cer->SetLineStyle(2);
          hPcer_cer->SetLineColor(kCyan+1);
          hPcer_cer->SetLineWidth(2.);
          hPcer_cer->SetLineStyle(2);
          hPcer->SetLineColor(kMagenta);
          hPcer->SetLineWidth(2.);
          hPcer->SetLineStyle(2);

          hPcer_amp->SetLineColor(kMagenta);
          hPcer_amp->SetLineWidth(3.);
          hPcer_amp->SetLineStyle(2);
          hPcer_amp_cer->SetLineColor(kCyan+1);
          hPcer_amp_cer->SetLineWidth(2.);
          hPcer_amp_cer->SetLineStyle(2);
          hPpre_amp_prlo->SetLineColor(kGreen+1);
          hPpre_amp_prlo->SetLineWidth(2.);
          hPpre_amp_prlo->SetLineStyle(2);
          hPpre_amp_prhi->SetLineColor(kOrange);
          hPpre_amp_prhi->SetLineWidth(2.);
          hPpre_amp_prhi->SetLineStyle(2);
          hPpre_amp->SetLineColor(kBlue-3);
          hPpre_amp->SetLineWidth(3.);
          hPpre_amp->SetLineStyle(2);

       TCanvas *c1 = new TCanvas("c1", "c1", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg1 = new TLegend(0.7,0.6,.9,0.95);
       leg1->SetFillStyle(0);
       leg1->SetTextSize(0.045);
       leg1->SetBorderSize(0);
       leg1->SetFillColor(-1);
       leg1->SetTextColor(kBlack);
       leg1->AddEntry(hPcal_E_p,"3/4-ALL","");
       TLegend *leg2 = new TLegend(0.7,0.55,.9,0.9);
       leg2->SetFillStyle(0);
       leg2->SetTextSize(0.045);
       leg2->SetBorderSize(0);
       leg2->SetFillColor(-1);
       leg2->SetTextColor(kRed);
       leg2->AddEntry(hPcal_E_p_elreal,"ELREAL","");
       TLegend *leg3 = new TLegend(0.7,0.5,.9,0.85);
       leg3->SetFillStyle(0);
       leg3->SetTextSize(0.045);
       leg3->SetBorderSize(0);
       leg3->SetFillColor(-1);
       leg3->SetTextColor(kMagenta-8);
       leg3->AddEntry(hPcal_E_p_elclean,"ELCLEAN","");
       TLegend *leg4 = new TLegend(0.7,0.45,.9,0.8);
       leg4->SetFillStyle(0);
       leg4->SetTextSize(0.045);
       leg4->SetBorderSize(0);
       leg4->SetFillColor(-1);
       leg4->SetTextColor(kMagenta);
       leg4->AddEntry(hPcal_E_p_ello,"ELLO","");
       TLegend *leg5= new TLegend(0.7,0.4,.9,0.75);
       leg5->SetFillStyle(0);
       leg5->SetTextSize(0.045);
       leg5->SetBorderSize(0);
       leg5->SetFillColor(-1);
       leg5->SetTextColor(kGreen+1);
       leg5->AddEntry(hPcal_E_p_elhi,"ELHI","");
       TLegend *leg6 = new TLegend(0.7,0.35,.9,0.7);
       leg6->SetFillStyle(0);
       leg6->SetTextSize(0.045);
       leg6->SetBorderSize(0);
       leg6->SetFillColor(-1);
       leg6->SetTextColor(kOrange);
       leg6->AddEntry(hPcal_E_p_prlo,"PRLO","");
       TLegend *leg7 = new TLegend(0.7,0.3,.9,0.65);
       leg7->SetFillStyle(0);
       leg7->SetTextSize(0.045);
       leg7->SetBorderSize(0);
       leg7->SetFillColor(-1);
       leg7->SetTextColor(kBlue-3);
       leg7->AddEntry(hPcal_E_p_prhi,"PRHI","");
       TLegend *leg8 = new TLegend(0.7,0.25,.9,0.6);
       leg8->SetFillStyle(0);
       leg8->SetTextSize(0.045);
       leg8->SetBorderSize(0);
       leg8->SetFillColor(-1);
       leg8->SetTextColor(kTeal-4);
       leg8->AddEntry(hPcal_E_p_cer,"CER","");
       hPcal_E_p->SetStats(0);
       hPcal_E_p->Draw("hist");
       hPcal_E_p_elreal->Draw("hist same");
       hPcal_E_p_elclean->Draw("hist same");
       hPcal_E_p_ello->Draw("hist same");
       hPcal_E_p_elhi->Draw("hist same");
       hPcal_E_p_prlo->Draw("hist same");
       hPcal_E_p_prhi->Draw("hist same");
       hPcal_E_p_cer->Draw("hist same");
       leg1->Draw();
       leg2->Draw();
       leg3->Draw();
       leg4->Draw();
       leg5->Draw();
       leg6->Draw();
       leg7->Draw();
       leg8->Draw();
       c1->SaveAs(Form("../PLOTS/SHMS_%d_Total_E_p_with_PID_LEGS.pdf",RunNumber));

       TCanvas *c2 = new TCanvas("c2", "c2", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg9 = new TLegend(0.7,0.6,.9,0.95);
       leg9->SetFillStyle(0);
       leg9->SetTextSize(0.045);
       leg9->SetBorderSize(0);
       leg9->SetFillColor(-1);
       leg9->SetTextColor(kBlack);
       leg9->AddEntry(hPpre_E_p,"3/4-ALL","");
       TLegend *leg10 = new TLegend(0.7,0.55,.9,0.9);
       leg10->SetFillStyle(0);
       leg10->SetTextSize(0.045);
       leg10->SetBorderSize(0);
       leg10->SetFillColor(-1);
       leg10->SetTextColor(kRed);
       leg10->AddEntry(hPpre_E_p_elreal,"ELREAL","");
       TLegend *leg11 = new TLegend(0.7,0.5,.9,0.85);
       leg11->SetFillStyle(0);
       leg11->SetTextSize(0.045);
       leg11->SetBorderSize(0);
       leg11->SetFillColor(-1);
       leg11->SetTextColor(kMagenta-8);
       leg11->AddEntry(hPpre_E_p_elclean,"ELCLEAN","");
       TLegend *leg12 = new TLegend(0.7,0.45,.9,0.8);
       leg12->SetFillStyle(0);
       leg12->SetTextSize(0.045);
       leg12->SetBorderSize(0);
       leg12->SetFillColor(-1);
       leg12->SetTextColor(kMagenta);
       leg12->AddEntry(hPpre_E_p_ello,"ELLO","");
       TLegend *leg13= new TLegend(0.7,0.4,.9,0.75);
       leg13->SetFillStyle(0);
       leg13->SetTextSize(0.045);
       leg13->SetBorderSize(0);
       leg13->SetFillColor(-1);
       leg13->SetTextColor(kGreen+1);
       leg13->AddEntry(hPpre_E_p_elhi,"ELHI","");
       TLegend *leg14 = new TLegend(0.7,0.35,.9,0.7);
       leg14->SetFillStyle(0);
       leg14->SetTextSize(0.045);
       leg14->SetBorderSize(0);
       leg14->SetFillColor(-1);
       leg14->SetTextColor(kOrange);
       leg14->AddEntry(hPpre_E_p_prlo,"PRLO","");
       TLegend *leg15 = new TLegend(0.7,0.3,.9,0.65);
       leg15->SetFillStyle(0);
       leg15->SetTextSize(0.045);
       leg15->SetBorderSize(0);
       leg15->SetFillColor(-1);
       leg15->SetTextColor(kBlue-3);
       leg15->AddEntry(hPpre_E_p_prhi,"PRHI","");
       TLegend *leg16 = new TLegend(0.7,0.25,.9,0.6);
       leg16->SetFillStyle(0);
       leg16->SetTextSize(0.045);
       leg16->SetBorderSize(0);
       leg16->SetFillColor(-1);
       leg16->SetTextColor(kTeal-4);
       leg16->AddEntry(hPpre_E_p_cer,"CER","");
       hPpre_E_p->SetStats(0);
       hPpre_E_p->Draw("hist");
       hPpre_E_p_elreal->Draw("hist same");
       hPpre_E_p_elclean->Draw("hist same");
       hPpre_E_p_ello->Draw("hist same");
       hPpre_E_p_elhi->Draw("hist same");
       hPpre_E_p_prlo->Draw("hist same");
       hPpre_E_p_prhi->Draw("hist same");
       hPpre_E_p_cer->Draw("hist same");
       leg9->Draw();
       leg10->Draw();
       leg11->Draw();
       leg12->Draw();
       leg13->Draw();
       leg14->Draw();
       leg15->Draw();
       leg16->Draw();
       c2->SaveAs(Form("../PLOTS/SHMS_%d_PreSh_E_p_with_PID_LEGS.pdf",RunNumber));


       TCanvas *c3 = new TCanvas("c3", "c3", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg17 = new TLegend(0.7,0.6,.9,0.95);
       leg17->SetFillStyle(0);
       leg17->SetTextSize(0.045);
       leg17->SetBorderSize(0);
       leg17->SetFillColor(-1);
       leg17->SetTextColor(kMagenta);
       leg17->AddEntry(hPcer,"3/4-ALL","");
       hPcer->SetStats(0);
       hPcer->Draw("hist");
       TLegend *leg18 = new TLegend(0.7,0.55,.9,0.9);
       leg18->SetFillStyle(0);
       leg18->SetTextSize(0.045);
       leg18->SetBorderSize(0);
       leg18->SetFillColor(-1);
       leg18->SetTextColor(kCyan+1);
       leg18->AddEntry(hPcer_cer,"CER","");
       hPcer_cer->Draw("hist same");
       leg17->Draw();
       leg18->Draw();
       c3->SaveAs(Form("../PLOTS/SHMS_%d_NGCER_npe_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c4 = new TCanvas("c4", "c4", 2000, 1200);
       c4->Divide(4,2);
       c4->cd(1);
       gPad->SetLogz();
       TLegend *leg19 = new TLegend(0.15,0.75,.35,0.9);
       leg19->SetFillStyle(0);
       leg19->SetTextSize(0.045);
       leg19->SetBorderSize(0);
       leg19->SetFillColor(-1);
       leg19->SetTextColor(kBlack);
       leg19->AddEntry(hPpre_vs_cal,"3/4-ALL","");
       hPpre_vs_cal->SetStats(0);
       hPpre_vs_cal->Draw("colz");
       leg19->Draw();
       c4->cd(2);
       gPad->SetLogz();
       TLegend *leg20 = new TLegend(0.15,0.75,.35,0.9);
       leg20->SetFillStyle(0);
       leg20->SetTextSize(0.045);
       leg20->SetBorderSize(0);
       leg20->SetFillColor(-1);
       leg20->SetTextColor(kRed);
       leg20->AddEntry(hPpre_vs_cal_elreal,"ELREAL","");
       hPpre_vs_cal_elreal->SetStats(0);
       hPpre_vs_cal_elreal->Draw("colz");
       leg20->Draw();
       c4->cd(3);
       gPad->SetLogz();
       TLegend *leg21 = new TLegend(0.15,0.75,.35,0.9);
       leg21->SetFillStyle(0);
       leg21->SetTextSize(0.045);
       leg21->SetBorderSize(0);
       leg21->SetFillColor(-1);
       leg21->SetTextColor(kMagenta-8);
       leg21->AddEntry(hPpre_vs_cal_elclean,"ELCLEAN","");
       hPpre_vs_cal_elclean->SetStats(0);
       hPpre_vs_cal_elclean->Draw("colz");
       leg21->Draw();
       c4->cd(4);
       gPad->SetLogz();
       TLegend *leg22 = new TLegend(0.15,0.75,.35,0.9);
       leg22->SetFillStyle(0);
       leg22->SetTextSize(0.045);
       leg22->SetBorderSize(0);
       leg22->SetFillColor(-1);
       leg22->SetTextColor(kMagenta);
       leg22->AddEntry(hPpre_vs_cal_ello,"ELLO","");
       hPpre_vs_cal_ello->SetStats(0);
       hPpre_vs_cal_ello->Draw("colz");
       leg22->Draw();
       c4->cd(5);
       gPad->SetLogz();
       TLegend *leg23 = new TLegend(0.15,0.75,.35,0.9);
       leg23->SetFillStyle(0);
       leg23->SetTextSize(0.045);
       leg23->SetBorderSize(0);
       leg23->SetFillColor(-1);
       leg23->SetTextColor(kGreen+1);
       leg23->AddEntry(hPpre_vs_cal_elhi,"ELHI","");
       hPpre_vs_cal_elhi->SetStats(0);
       hPpre_vs_cal_elhi->Draw("colz");
       leg23->Draw();
       c4->cd(6);
       gPad->SetLogz();
       TLegend *leg24 = new TLegend(0.15,0.75,.35,0.9);
       leg24->SetFillStyle(0);
       leg24->SetTextSize(0.045);
       leg24->SetBorderSize(0);
       leg24->SetFillColor(-1);
       leg24->SetTextColor(kOrange);
       leg24->AddEntry(hPpre_vs_cal_prlo,"PRLO","");
       hPpre_vs_cal_prlo->SetStats(0);
       hPpre_vs_cal_prlo->Draw("colz");
       leg24->Draw();
       c4->cd(7);
       gPad->SetLogz();
       TLegend *leg25 = new TLegend(0.15,0.75,.35,0.9);
       leg25->SetFillStyle(0);
       leg25->SetTextSize(0.045);
       leg25->SetBorderSize(0);
       leg25->SetFillColor(-1);
       leg25->SetTextColor(kBlue-3);
       leg25->AddEntry(hPpre_vs_cal_prhi,"PRHI","");
       hPpre_vs_cal_prhi->SetStats(0);
       hPpre_vs_cal_prhi->Draw("colz");
       leg25->Draw();
       c4->cd(8);
       gPad->SetLogz();
       TLegend *leg26 = new TLegend(0.15,0.75,.35,0.9);
       leg26->SetFillStyle(0);
       leg26->SetTextSize(0.045);
       leg26->SetBorderSize(0);
       leg26->SetFillColor(-1);
       leg26->SetTextColor(kTeal-4);
       leg26->AddEntry(hPpre_vs_cal_cer,"CER","");
       hPpre_vs_cal_cer->SetStats(0);
       hPpre_vs_cal_cer->Draw("colz");
       leg26->Draw();
       c4->SaveAs(Form("../PLOTS/SHMS_%d_PreSh_vs_Total_E_p_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c5 = new TCanvas("c5", "c5", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg27 = new TLegend(0.7,0.6,.9,0.95);
       leg27->SetFillStyle(0);
       leg27->SetTextSize(0.045);
       leg27->SetBorderSize(0);
       leg27->SetFillColor(-1);
       leg27->SetTextColor(kMagenta);
       leg27->AddEntry(hPcer_amp,"3/4-ALL","");
       hPcer_amp->SetStats(0);
       hPcer_amp->Draw("hist");
       TLegend *leg28 = new TLegend(0.7,0.55,.9,0.9);
       leg28->SetFillStyle(0);
       leg28->SetTextSize(0.045);
       leg28->SetBorderSize(0);
       leg28->SetFillColor(-1);
       leg28->SetTextColor(kCyan+1);
       leg28->AddEntry(hPcer_amp_cer,"CER","");
       hPcer_amp_cer->Draw("hist same");
       leg27->Draw();
       leg28->Draw();
       c5->SaveAs(Form("../PLOTS/SHMS_%d_NGCER_PulseAmp_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c6 = new TCanvas("c6", "c6", 1600, 1200);
       gPad->SetLogy();
       TLegend *leg29 = new TLegend(0.7,0.6,.9,0.95);
       leg29->SetFillStyle(0);
       leg29->SetTextSize(0.045);
       leg29->SetBorderSize(0);
       leg29->SetFillColor(-1);
       leg29->SetTextColor(kBlue-3);
       leg29->AddEntry(hPpre_amp,"3/4-ALL","");
       hPpre_amp->SetStats(0);
       hPpre_amp->Draw("hist");
       TLegend *leg30 = new TLegend(0.7,0.55,.9,0.9);
       leg30->SetFillStyle(0);
       leg30->SetTextSize(0.045);
       leg30->SetBorderSize(0);
       leg30->SetFillColor(-1);
       leg30->SetTextColor(kGreen+1);
       leg30->AddEntry(hPpre_amp_prlo,"PRLO","");
       hPpre_amp_prlo->Draw("hist same");
       TLegend *leg31 = new TLegend(0.7,0.5,.9,0.85);
       leg31->SetFillStyle(0);
       leg31->SetTextSize(0.045);
       leg31->SetBorderSize(0);
       leg31->SetFillColor(-1);
       leg31->SetTextColor(kOrange);
       leg31->AddEntry(hPpre_amp_prhi,"PRHI","");
       hPpre_amp_prhi->Draw("hist same");
       leg29->Draw();
       leg30->Draw();
       leg31->Draw();
       c6->SaveAs(Form("../PLOTS/SHMS_%d_PreSh_PulseAmp_with_PID_LEGS.pdf",RunNumber));
       
       TCanvas *c7 = new TCanvas("c7", "c7", 2000, 1200);
       c7->Divide(2,2);
       c7->cd(1);
       gPad->SetLogz();
       TLegend *leg32 = new TLegend(0.15,0.75,.35,0.9);
       leg32->SetFillStyle(0);
       leg32->SetTextSize(0.045);
       leg32->SetBorderSize(0);
       leg32->SetFillColor(-1);
       leg32->SetTextColor(kBlack);
       leg32->AddEntry(hPpre_amp_vs_cal,"3/4-ALL","");
       hPpre_amp_vs_cal->SetStats(0);
       hPpre_amp_vs_cal->Draw("colz");
       leg32->Draw();
       c7->cd(2);
       gPad->SetLogz();
       TLegend *leg33 = new TLegend(0.15,0.75,.35,0.9);
       leg33->SetFillStyle(0);
       leg33->SetTextSize(0.045);
       leg33->SetBorderSize(0);
       leg33->SetFillColor(-1);
       leg33->SetTextColor(kOrange);
       leg33->AddEntry(hPpre_amp_vs_cal_prlo,"PRLO","");
       hPpre_amp_vs_cal_prlo->SetStats(0);
       hPpre_amp_vs_cal_prlo->Draw("colz");
       leg33->Draw();
       c7->cd(3);
       gPad->SetLogz();
       TLegend *leg34 = new TLegend(0.15,0.75,.35,0.9);
       leg34->SetFillStyle(0);
       leg34->SetTextSize(0.045);
       leg34->SetBorderSize(0);
       leg34->SetFillColor(-1);
       leg34->SetTextColor(kBlue-3);
       leg34->AddEntry(hPpre_amp_vs_cal_prhi,"PRHI","");
       hPpre_amp_vs_cal_prhi->SetStats(0);
       hPpre_amp_vs_cal_prhi->Draw("colz");
       leg34->Draw();
       c7->SaveAs(Form("../PLOTS/SHMS_%d_PreSh_PulseAmp_vs_Total_E_p_with_PID_LEGS.pdf",RunNumber));
       return;
}
