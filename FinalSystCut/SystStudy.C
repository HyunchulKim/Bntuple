#include "utilities.h"

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.05;
double setparam3=0.03;
double fixparam1=5.279;
int variationoption=4;

TString inputdata="/d00/bmeson/data/nt_20140309_PAMuon_HIRun2013_PromptRecoAndRereco_v1_MuonMatching.root";
//TString inputdata="../InputsFits/nt_mc_Kp.root";
//TString inputdata="../InputsFits/nt_mc_Kp.root";
//TString inputdata="nt_nonPrompt_Jpsi.root";
//TString inputdata="/d00/bmeson/MC/nt_BoostedMC_20140303_kp.root";
TString inputmc="/d00/bmeson/MC/nt_BoostedMC_20140303_kp.root";

//TString cut="chi2cl>0.01&&(d0)/d0Err>3.4&&dtheta<2.98&&TMath::Abs((trk1Dxy)/trk1D0Err)>2.4";
TString cut,seldata,selmc,selmcgen;


void clean0(TH1D *h){
  for (int i=1;i<=h->GetNbinsX();i++){
    if (h->GetBinContent(i)==0) h->SetBinError(i,1);
  }
}

TF1 *fit(TTree *nt,TTree *ntMC,double ptmin,double ptmax){   
   //cout<<cut.Data()<<endl;
   static int count=0;
   count++;
   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",50,5,6);
   TH1D *hMC = new TH1D(Form("hMC%d",count),"",50,5,6);
   // Fit function
   TF1 *f = new TF1(Form("f%d",count),"[0]*([7]*Gaus(x,[1],[2])+(1-[7])*Gaus(x,[1],[8]))+[3]+[4]*x+[5]*(1.24e2*Gaus(x,5.107,0.02987)+1.886e2*Gaus(x,5.0116,5.546e-2))");
   nt->Project(Form("h%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),ptmin,ptmax));   
   ntMC->Project(Form("hMC%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),ptmin,ptmax));   
   clean0(h);
   h->Draw();
   f->SetParLimits(4,-1000,0);
   f->SetParLimits(2,0.01,0.05);
   f->SetParLimits(8,0.01,0.05);
   f->SetParLimits(7,0,1);
   f->SetParameter(0,setparam0);
   f->SetParameter(1,setparam1);
   f->SetParameter(2,setparam2);
   f->SetParameter(8,setparam3);
   f->FixParameter(1,fixparam1);
   h->GetEntries();

   hMC->Fit(Form("f%d",count),"q","",5,6);
   hMC->Fit(Form("f%d",count),"q","",5,6);
   f->ReleaseParameter(1);
   hMC->Fit(Form("f%d",count),"L q","",5,6);
   hMC->Fit(Form("f%d",count),"L q","",5,6);
   hMC->Fit(Form("f%d",count),"L q","",5,6);
   hMC->Fit(Form("f%d",count),"L m","",5,6);

   f->FixParameter(1,f->GetParameter(1));
   f->FixParameter(2,f->GetParameter(2));
   f->FixParameter(7,f->GetParameter(7));
   f->FixParameter(8,f->GetParameter(8));
   
   h->Fit(Form("f%d",count),"q","",5,6);
   h->Fit(Form("f%d",count),"q","",5,6);
   f->ReleaseParameter(1);
   h->Fit(Form("f%d",count),"L q","",5,6);
   h->Fit(Form("f%d",count),"L q","",5,6);
   h->Fit(Form("f%d",count),"L q","",5,6);
   h->Fit(Form("f%d",count),"L m","",5,6);
   h->SetMarkerSize(0.8);
   h->SetMarkerStyle(20);
   cout <<h->GetEntries()<<endl;

   // function for background shape plotting. take the fit result from f
   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x");
//   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*(1.24e2*Gaus(x,5.107,0.02987)+1.886e2*Gaus(x,5.0116,5.546e-2))");
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetParameter(2,f->GetParameter(5));
   background->SetParameter(3,f->GetParameter(6));
   background->SetLineColor(4);
   background->SetRange(5,6);
   background->SetLineStyle(2);
   
   // function for signal shape plotting. take the fit result from f
   TF1 *Bkpi = new TF1(Form("fBkpi",count),"[0]*(1.24e2*Gaus(x,5.107,0.02987)+1.886e2*Gaus(x,5.0116,5.546e-2))");
   Bkpi->SetParameter(0,f->GetParameter(5));
   Bkpi->SetLineColor(kGreen+1);
   Bkpi->SetFillColor(kGreen+1);
   Bkpi->SetRange(5.00,5.28);
   Bkpi->SetLineStyle(1);
   Bkpi->SetFillStyle(3004);

   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1(Form("fmass",count),"[0]*([3]*Gaus(x,[1],[2])+(1-[3])*Gaus(x,[1],[4]))");
   mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(8));
   mass->SetParError(0,f->GetParError(0));
   mass->SetParError(1,f->GetParError(1));
   mass->SetParError(2,f->GetParError(2));
   mass->SetParError(7,f->GetParError(7));
   mass->SetParError(8,f->GetParError(8));
   mass->SetLineColor(2);
   mass->SetLineStyle(2);

//   cout <<mass->Integral(0,1.2)<<" "<<mass->IntegralError(0,1.2)<<endl;
   h->SetMarkerStyle(24);
   h->SetStats(0);
   h->Draw("e");
   h->SetXTitle("M_{B} (GeV/c^{2})");
   h->SetYTitle("Entries / (2 MeV/c^{2})");
   h->GetXaxis()->CenterTitle();
   h->GetYaxis()->CenterTitle();
   h->SetTitleOffset(1.4,"Y");
   h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
   Bkpi->Draw("same");
   background->Draw("same");   
   mass->SetRange(5,6);
   mass->Draw("same");
   mass->SetLineStyle(2);
   mass->SetFillStyle(3004);
   mass->SetFillColor(2);
   f->Draw("same");

   double yield = mass->Integral(5,6)/0.02;
   double yieldErr = mass->Integral(5,6)/0.02*mass->GetParError(0)/mass->GetParameter(0);


   // Draw the legend:)   
   TLegend *leg = myLegend(0.50,0.5,0.86,0.92);
   leg->AddEntry(h,"CMS Preliminary","");
   leg->AddEntry(h,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
   leg->AddEntry(h,Form("%.0f<p_{T}^{B}<%.0f GeV/c",ptmin,ptmax),"");
   leg->AddEntry(h,"Data","pl");
   leg->AddEntry(f,"Fit","l");
   leg->AddEntry(mass,"Signal","f");
   leg->AddEntry(background,"Combinatorial Background","l");
   leg->AddEntry(Bkpi,"Non-prompt J/#psi","f");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
   leg2->AddEntry(h,"B meson","");
   leg2->AddEntry(h,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
   leg2->AddEntry(h,Form("N_{B}=%.0f #pm %.0f", yield, yieldErr),"");
   leg2->Draw();

   //c->SaveAs(Form("ResultsBplus/BMass-%d.C",count));
   //c->SaveAs(Form("ResultsBplus/BMass-%d.gif",count));
   //c->SaveAs(Form("ResultsBplus/BMass-%d.eps",count));

   return mass;
}

void fitB(int stepcut)
{
  TString infname=inputdata.Data();
  TFile *inf = new TFile(infname.Data());
  TTree *nt = (TTree*) inf->Get("ntKp");

  TFile *infMC = new TFile(inputmc.Data());
  TTree *ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntMC = (TTree*)infMC->Get("ntKp");
    
  const int nBins = 5;
  double ptBins[nBins+1] = {10,15,20,25,30,60};
  TH1D *hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D *hRecoTruth = new TH1D("hRecoTruth","",nBins,ptBins);
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D *hPtGen = new TH1D("hPtGen","",nBins,ptBins);

  for (int i=0;i<nBins;i++)
    {
      TF1 *f = fit(nt,ntMC,ptBins[i],ptBins[i+1]);
      double yield = f->Integral(5,6)/0.02;
      double yieldErr = f->Integral(5,6)/0.02*f->GetParError(0)/f->GetParameter(0);
      hPt->SetBinContent(i+1,yield/(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,yieldErr/(ptBins[i+1]-ptBins[i]));
    }  
  
  TCanvas *c=  new TCanvas("cResult","",600,600);
  hPt->SetXTitle("B^{+} p_{T} (GeV/c)");
  hPt->SetYTitle("Uncorrected B^{+} dN/dp_{T}");
  hPt->Sumw2();
  hPt->Draw();
  
  ntMC->Project("hPtMC","pt",TCut(selmc.Data())&&"gen==22233");
  nt->Project("hRecoTruth","pt",TCut(seldata.Data())&&"gen==22233");
  ntGen->Project("hPtGen","pt",selmcgen.Data());
  divideBinWidth(hRecoTruth);
  
  hRecoTruth->Draw("same hist");
  divideBinWidth(hPtMC);
  divideBinWidth(hPtGen);
  
  hPtMC->Sumw2();
  TH1D *hEff = (TH1D*)hPtMC->Clone("hEff");
  hPtMC->Sumw2();
  hEff->Divide(hPtGen);
  
  TH1D *hPtCor = (TH1D*)hPt->Clone("hPtCor");
  hPtCor->Divide(hEff);
  TCanvas *cCor=  new TCanvas("cCorResult","",600,600);
  hPtCor->SetYTitle("Corrected B^{+} dN/dp_{T}");
  hPtCor->Draw();
  hPtGen->Draw("same hist");

  TH1D *hPtSigma= (TH1D*)hPtCor->Clone("hPtSigma");
  hPtSigma->Scale(1./(2*luminosity));
  hPtSigma->SetYTitle("d#sigma (B^{+})/dp_{T}");

  TCanvas *cSigma=  new TCanvas("cSigma","",600,600);

  hPtSigma->Draw();
  
  TFile *outf = new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step%d.root",variationoption,stepcut),"recreate");
  outf->cd();
  hPt->Write();
  hEff->Write();
  hPtGen->Write();
  hPtCor->Write();
  hPtSigma->Write();
  outf->Close();
  delete outf;
}

void SystStudy(){

  Int_t steps=10;
  Double_t valuemin,valuemax,stepvalue,cutvalue;
    
  for (int i=0;i<steps;i++){
    
    if(variationoption==1){
      valuemin=0.0;
      valuemax=0.3;
      stepvalue=(valuemax-valuemin)/(double)(steps);
      cutvalue=valuemin+i*stepvalue;
      cout<<"AAAA"<<cutvalue<<endl;
      cut=Form("(HLT_PAMu3_v1)&&chi2cl>%f&&(d0)/d0Err>3.3&&cos(dtheta)>-0.53&&TMath::Abs((trk1Dxy)/trk1D0Err)>1.9",cutvalue);

    } 
    if(variationoption==2){
      valuemin=3.3-2.0;
      valuemax=3.3+2.0;
      stepvalue=(valuemax-valuemin)/(double)(steps);
      cutvalue=valuemin+i*stepvalue;
      cut=Form("(HLT_PAMu3_v1)&&chi2cl>0.0054&&(d0)/d0Err>%f&&cos(dtheta)>-0.53&&TMath::Abs((trk1Dxy)/trk1D0Err)>1.9",cutvalue);

    }
    
    if(variationoption==3){
      valuemin=0.5;
      valuemax=1.0;
      stepvalue=(valuemax-valuemin)/(double)(steps);
      cutvalue=valuemin+i*stepvalue;
      cut=Form("(HLT_PAMu3_v1)&&chi2cl>0.0054&&(d0)/d0Err>3.3&&cos(dtheta)>%f&&TMath::Abs((trk1Dxy)/trk1D0Err)>1.9",cutvalue);

    }
    
    if(variationoption==4){
      valuemin=1.9-1.;
      valuemax=1.9+1.;
      stepvalue=(valuemax-valuemin)/(double)(steps);
      cutvalue=valuemin+i*stepvalue;
      cut=Form("(HLT_PAMu3_v1)&&chi2cl>0.0054&&(d0)/d0Err>3.3&&cos(dtheta)>-0.53&&TMath::Abs((trk1Dxy)/trk1D0Err)>%f",cutvalue);

    }
      seldata=Form("abs(y+0.465)<1.93&&%s",cut.Data());
      selmc=Form("abs(y+0.465)<1.93&&gen==22233&&%s",cut.Data());
      selmcgen="abs(y+0.465)<1.93&&abs(pdgId)==521&&isSignal==1";
      void fitB(int);  
      fitB(i);    


   } 
}