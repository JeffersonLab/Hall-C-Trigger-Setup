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
  Float_t xx=y[0]*1000.;
  Double_t dt; 
  Double_t lt;
  dt=100.*(xx*par2[0]/(1+xx*par2[0]));
  lt = (100. - dt);
  return lt;
}
							    
void deadtime_poiss() {
  TLegend* leg1 = new TLegend(0.11,0.7,0.25,0.89);
  TCanvas *T1 = new TCanvas ("T1","T1", 1000, 700);
  T1->Divide(1,1);
  
  TMultiGraph *mg1 = new TMultiGraph();

  Double_t rate[9]={1.0, 5.3, 10.9, 20.0, 30.6, 53.0, 101.0};   //poisson rate
  Double_t CLT[9]={81.07, 47.28, 30.73, 18.1, 13.2, 7.91, 4.25};  //computer live time
  Double_t TLT[9]={83.36, 47.53, 30.78, 18.5, 13.3, 7.81, 4.13};


  //Double_t xs[9]={154,265.,476,1040,1040,1040,1040,1040,1500.};
  //Double_t ys[9]={3.29,6.28,10.79,17.6,0.0,14.20,20.23,19.86,24.74};
  TGraph *gr1 = new TGraph(7, rate, CLT);
  TGraph *gr2 = new TGraph(7, rate, TLT);

  mg1->Add(gr1);
  mg1->Add(gr2);
  mg1->Draw("AP");
  gr1->SetMarkerColor(2);
  gr1->SetMarkerStyle(21);
  gr1->SetMarkerSize(1.5);

  gr2->SetMarkerColor(1);
  gr2->SetMarkerStyle(21);
  gr2->SetMarkerSize(1.5);

  gr1->GetXaxis()->SetLimits(0,110);
  mg1->GetXaxis()->SetLimits(0,110);
  mg1->SetMinimum(0);
  mg1->SetMaximum(100);
  mg1->SetTitle("");
  mg1->GetXaxis()->SetTitle("Rate (kHz)");
  mg1->GetYaxis()->SetTitle("Live Time (%)");
  leg1->AddEntry(gr1,"HMS Measured Computer Live Time","p");
  leg1->AddEntry(gr2,"HMS Measured Total Live Time","p");
   
 //leg1->AddEntry(gr2,"SHMS EDTM","p");
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
  */
  TF1 *deadt3 = new TF1("deadt3",dt_nonextended,0,110.,2);
  deadt3->SetParameters(200.e-6,1);
  deadt3->Draw("same");
  deadt3->SetLineColor(4);
  leg1->AddEntry(deadt3,"BUSY MIN = 200 #mus","l");
  
  TF1 *deadt4 = new TF1("EDTM + Poisson Live Time Measurements",dt_nonextended,0,110.,2);
  deadt4->SetParameters(270.e-6,1);
  deadt4->Draw("same");
  deadt4->SetLineColor(1);
  leg1->AddEntry(deadt4,"BUSY MAX = 270 #mus","l");
  leg1->Draw();
  /*
  TF1 *deadt5 = new TF1("deadt4",dt_extended,0,55000.,2);
  deadt5->SetParameters(2,280.e-6);
  deadt5->Draw("same");
  deadt5->SetLineColor(1);
  leg1->AddEntry(deadt5,"deadtime = 280 usec buf=2","l");
  leg1->Draw();
  */
}
