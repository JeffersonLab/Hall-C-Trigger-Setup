#include <iostream>
#include <fstream>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"


using namespace std;

Double_t dt_extended(Double_t *x, Double_t *par){
  Double_t dtts = 0;
  Float_t xx=x[0];
  Double_t muts;
  Int_t istart=int(par[0]);
  muts=par[1]*xx;
  for (Int_t i = istart; i < 20; i++) {
    dtts = dtts +  ( TMath::Power(muts,i) * TMath::Exp(-1.0*muts) )/ TMath::Factorial(i);   }
  dtts=100*dtts;
  return dtts;
}
Double_t dt_nonextended(Double_t *y, Double_t *par2){
  Float_t xx=y[0];
  Double_t dt; 
  dt=100.*(xx*par2[0]/(1+xx*par2[0]));
  return dt;
}
							    
void deadtime() {
  TLegend* leg1 = new TLegend(0.11,0.7,0.25,0.89);
  TCanvas *T1 = new TCanvas ("T1","T1", 1000, 700);
  T1->Divide(1,1);
  TMultiGraph *mg1 = new TMultiGraph();

  Double_t rate[9] = {1.,2.,3.,3.8,7.70,11.550,15.400,18.250,23.100};
  Double_t expected_LT[9] = {100., 100., 100., 100., 50., 33.3, 25., 20., 16.6};
  Double_t livetime_no_scl[9] = {99.99, 99.98, 99.84, 98.09, 48.92, 32.57, 24.44, 22.59, 18.37};
  Double_t livetime_scl[9] = {100., 99.89, 99.66, 97.92, 48.82, 32.55, 24.38, 22.50, 18.34};
  
  TGraph *gr1 = new TGraph(9, rate, expected_LT);
  TGraph *gr2 = new TGraph(9, rate, livetime_no_scl);
  TGraph *gr3 = new TGraph(9, rate, livetime_scl);

  //TGraph *gr2 = new TGraph(9, xs, ys);
  mg1->Add(gr1);
  mg1->Add(gr2);
  mg1->Add(gr3);

  mg1->Draw("AP");
  gr1->SetMarkerColor(kBlue);
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerSize(2.0);
  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(22);
  gr2->SetMarkerSize(2.0);
  gr3->SetMarkerColor(kGreen);
  gr3->SetMarkerStyle(23);
  gr3->SetMarkerSize(2.0);


  gr1->GetXaxis()->SetLimits(0,24.);
  gr1->SetTitle("EDTM");
  //gr2->GetXaxis()->SetLimits(0,3000);
  mg1->GetXaxis()->SetLimits(0,24.);

  mg1->SetMinimum(0);
  mg1->SetMaximum(105);
  mg1->SetTitle("EDTM Live-Time Measurements");
  mg1->GetXaxis()->SetTitle(" Rate (kHz)");
  mg1->GetYaxis()->SetTitle(" LiveTime (%)");
  leg1->AddEntry(gr1,"Expected HMS LiveTime","p");
  leg1->AddEntry(gr2,"Measured HMS LiveTime: No Scaler Reads","p");
  leg1->AddEntry(gr3,"Measured HMS LiveTime: With Scaler Reads","p");
  leg1->SetTextSize(0.02);

  /*
  TF1 *deadt1= new TF1("deadt1",dt_nonextended,0.,55000.,2);
  deadt1->SetParameters(.0001,1);
  deadt1->Draw("same");
  deadt1->SetLineColor(2);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->AddEntry(deadt1,"deadtime = 100 usec","l");
  TF1 *deadt2 = new TF1("deadt2",dt_nonextended,0,55000.,2);
  deadt2->SetParameters(220.e-6,1);
  deadt2->Draw("same");
  deadt2->SetLineColor(3);
  leg1->AddEntry(deadt2,"deadtime = 220 usec","l");
  
  TF1 *deadt3 = new TF1("deadt3",dt_nonextended,0,55000.,2);
  deadt3->SetParameters(260.e-6,1);
  deadt3->Draw("same");
  deadt3->SetLineColor(4);
  leg1->AddEntry(deadt3,"deadtime = 260 usec","l");

  
  TF1 *deadt4 = new TF1("deadt4",dt_nonextended,0,55000.,2);
  deadt4->SetParameters(280.e-6,1);
  deadt4->Draw("same");
  deadt4->SetLineColor(1);
  leg1->AddEntry(deadt4,"deadtime = 280 usec","l");
  leg1->Draw();
  TF1 *deadt5 = new TF1("deadt4",dt_extended,0,55000.,2);
  deadt5->SetParameters(2,280.e-6);
  deadt5->Draw("same");
  deadt5->SetLineColor(1);
  leg1->AddEntry(deadt5,"deadtime = 280 usec buf=2","l");
  */
  leg1->Draw();
}
