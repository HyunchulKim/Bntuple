  const int nBins = 10;
  int idcut=1; double ptBins[nBins+1] = {0.,0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.24,0.27,0.3};
  //int idcut=2; double ptBins[nBins+1] = {1.3,1.7,2.1,2.5,2.9,3.3,3.7,4.1,4.5,4.9,5.3};
  //int idcut=3; double ptBins[nBins+1] = {0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1.};
  //int idcut=4; double ptBins[nBins+1] = {0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5,2.7,2.9};

void CompareSyst(){

   gROOT->SetStyle("Plain");	
   gStyle->SetOptStat(0);
   gStyle->SetOptStat(0000);
   gStyle->SetPalette(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetFrameFillColor(0);
   gStyle->SetOptTitle(0);

  TFile*file0=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step0.root",idcut));
  TFile*file1=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step1.root",idcut));
  TFile*file2=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step2.root",idcut));
  TFile*file3=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step3.root",idcut));
  TFile*file4=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step4.root",idcut));
  TFile*file5=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step5.root",idcut));
  TFile*file6=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step6.root",idcut));
  TFile*file7=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step7.root",idcut));
  TFile*file8=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step8.root",idcut));
  TFile*file9=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step9.root",idcut));
  
  
 TH1F*hSigmaBis0=(TH1F*)file0->Get("hPtSigma");
 TH1F*hSigmaBis1=(TH1F*)file1->Get("hPtSigma");
 TH1F*hSigmaBis2=(TH1F*)file2->Get("hPtSigma");
 TH1F*hSigmaBis3=(TH1F*)file3->Get("hPtSigma");
 TH1F*hSigmaBis4=(TH1F*)file4->Get("hPtSigma");
 TH1F*hSigmaBis5=(TH1F*)file5->Get("hPtSigma");
 TH1F*hSigmaBis6=(TH1F*)file6->Get("hPtSigma");
 TH1F*hSigmaBis7=(TH1F*)file7->Get("hPtSigma");
 TH1F*hSigmaBis8=(TH1F*)file8->Get("hPtSigma");
 TH1F*hSigmaBis9=(TH1F*)file9->Get("hPtSigma");
 
 hSigmaBis0->SetName("hSigmaBis0");
 hSigmaBis1->SetName("hSigmaBis1");
 hSigmaBis2->SetName("hSigmaBis2");
 hSigmaBis3->SetName("hSigmaBis3");
 hSigmaBis4->SetName("hSigmaBis4");
 hSigmaBis5->SetName("hSigmaBis5");
 hSigmaBis6->SetName("hSigmaBis6");
 hSigmaBis7->SetName("hSigmaBis7");
 hSigmaBis8->SetName("hSigmaBis8");
 hSigmaBis9->SetName("hSigmaBis9");

  
  
  

  TH1D *hPt0 = new TH1D("hPt0","",nBins,ptBins);
  TH1D *hPt1 = new TH1D("hPt1","",nBins,ptBins);
  TH1D *hPt2 = new TH1D("hPt2","",nBins,ptBins);
  TH1D *hPt3 = new TH1D("hPt3","",nBins,ptBins);
  TH1D *hPt4 = new TH1D("hPt4","",nBins,ptBins);
  TH1D *hPt5 = new TH1D("hPt5","",nBins,ptBins);
  
  hPt0->SetBinContent(1,hSigmaBis0->GetBinContent(1));
  hPt0->SetBinContent(2,hSigmaBis1->GetBinContent(1));
  hPt0->SetBinContent(3,hSigmaBis2->GetBinContent(1));
  hPt0->SetBinContent(4,hSigmaBis3->GetBinContent(1));
  hPt0->SetBinContent(5,hSigmaBis4->GetBinContent(1));
  hPt0->SetBinContent(6,hSigmaBis5->GetBinContent(1));
  hPt0->SetBinContent(7,hSigmaBis6->GetBinContent(1));
  hPt0->SetBinContent(8,hSigmaBis7->GetBinContent(1));
  hPt0->SetBinContent(9,hSigmaBis8->GetBinContent(1));
  hPt0->SetBinContent(10,hSigmaBis9->GetBinContent(1));
  
  hPt1->SetBinContent(1,hSigmaBis0->GetBinContent(2));
  hPt1->SetBinContent(2,hSigmaBis1->GetBinContent(2));
  hPt1->SetBinContent(3,hSigmaBis2->GetBinContent(2));
  hPt1->SetBinContent(4,hSigmaBis3->GetBinContent(2));
  hPt1->SetBinContent(5,hSigmaBis4->GetBinContent(2));
  hPt1->SetBinContent(6,hSigmaBis5->GetBinContent(2));
  hPt1->SetBinContent(7,hSigmaBis6->GetBinContent(2));
  hPt1->SetBinContent(8,hSigmaBis7->GetBinContent(2));
  hPt1->SetBinContent(9,hSigmaBis8->GetBinContent(2));
  hPt1->SetBinContent(10,hSigmaBis9->GetBinContent(2));
  
  hPt2->SetBinContent(1,hSigmaBis0->GetBinContent(3));
  hPt2->SetBinContent(2,hSigmaBis1->GetBinContent(3));
  hPt2->SetBinContent(3,hSigmaBis2->GetBinContent(3));
  hPt2->SetBinContent(4,hSigmaBis3->GetBinContent(3));
  hPt2->SetBinContent(5,hSigmaBis4->GetBinContent(3));
  hPt2->SetBinContent(6,hSigmaBis5->GetBinContent(3));
  hPt2->SetBinContent(7,hSigmaBis6->GetBinContent(3));
  hPt2->SetBinContent(8,hSigmaBis7->GetBinContent(3));
  hPt2->SetBinContent(9,hSigmaBis8->GetBinContent(3));
  hPt2->SetBinContent(10,hSigmaBis9->GetBinContent(3));
  
  hPt3->SetBinContent(1,hSigmaBis0->GetBinContent(4));
  hPt3->SetBinContent(2,hSigmaBis1->GetBinContent(4));
  hPt3->SetBinContent(3,hSigmaBis2->GetBinContent(4));
  hPt3->SetBinContent(4,hSigmaBis3->GetBinContent(4));
  hPt3->SetBinContent(5,hSigmaBis4->GetBinContent(4));
  hPt3->SetBinContent(6,hSigmaBis5->GetBinContent(4));
  hPt3->SetBinContent(7,hSigmaBis6->GetBinContent(4));
  hPt3->SetBinContent(8,hSigmaBis7->GetBinContent(4));
  hPt3->SetBinContent(9,hSigmaBis8->GetBinContent(4));
  hPt3->SetBinContent(10,hSigmaBis9->GetBinContent(4));
  
  hPt4->SetBinContent(1,hSigmaBis0->GetBinContent(5));
  hPt4->SetBinContent(2,hSigmaBis1->GetBinContent(5));
  hPt4->SetBinContent(3,hSigmaBis2->GetBinContent(5));
  hPt4->SetBinContent(4,hSigmaBis3->GetBinContent(5));
  hPt4->SetBinContent(5,hSigmaBis4->GetBinContent(5));
  hPt4->SetBinContent(6,hSigmaBis5->GetBinContent(5));
  hPt4->SetBinContent(7,hSigmaBis6->GetBinContent(5));
  hPt4->SetBinContent(8,hSigmaBis7->GetBinContent(5));
  hPt4->SetBinContent(9,hSigmaBis8->GetBinContent(5));
  hPt4->SetBinContent(10,hSigmaBis9->GetBinContent(5));

  
  hPt0->SetBinError(1,hSigmaBis0->GetBinError(1));
  hPt0->SetBinError(2,hSigmaBis1->GetBinError(1));
  hPt0->SetBinError(3,hSigmaBis2->GetBinError(1));
  hPt0->SetBinError(4,hSigmaBis3->GetBinError(1));
  hPt0->SetBinError(5,hSigmaBis4->GetBinError(1));
  hPt0->SetBinError(6,hSigmaBis5->GetBinError(1));
  hPt0->SetBinError(7,hSigmaBis6->GetBinError(1));
  hPt0->SetBinError(8,hSigmaBis7->GetBinError(1));
  hPt0->SetBinError(9,hSigmaBis8->GetBinError(1));
  hPt0->SetBinError(10,hSigmaBis9->GetBinError(1));
  
  hPt1->SetBinError(1,hSigmaBis0->GetBinError(2));
  hPt1->SetBinError(2,hSigmaBis1->GetBinError(2));
  hPt1->SetBinError(3,hSigmaBis2->GetBinError(2));
  hPt1->SetBinError(4,hSigmaBis3->GetBinError(2));
  hPt1->SetBinError(5,hSigmaBis4->GetBinError(2));
  hPt1->SetBinError(6,hSigmaBis5->GetBinError(2));
  hPt1->SetBinError(7,hSigmaBis6->GetBinError(2));
  hPt1->SetBinError(8,hSigmaBis7->GetBinError(2));
  hPt1->SetBinError(9,hSigmaBis8->GetBinError(2));
  hPt1->SetBinError(10,hSigmaBis9->GetBinError(2));
  
  hPt2->SetBinError(1,hSigmaBis0->GetBinError(3));
  hPt2->SetBinError(2,hSigmaBis1->GetBinError(3));
  hPt2->SetBinError(3,hSigmaBis2->GetBinError(3));
  hPt2->SetBinError(4,hSigmaBis3->GetBinError(3));
  hPt2->SetBinError(5,hSigmaBis4->GetBinError(3));
  hPt2->SetBinError(6,hSigmaBis5->GetBinError(3));
  hPt2->SetBinError(7,hSigmaBis6->GetBinError(3));
  hPt2->SetBinError(8,hSigmaBis7->GetBinError(3));
  hPt2->SetBinError(9,hSigmaBis8->GetBinError(3));
  hPt2->SetBinError(10,hSigmaBis9->GetBinError(3));
  
  hPt3->SetBinError(1,hSigmaBis0->GetBinError(4));
  hPt3->SetBinError(2,hSigmaBis1->GetBinError(4));
  hPt3->SetBinError(3,hSigmaBis2->GetBinError(4));
  hPt3->SetBinError(4,hSigmaBis3->GetBinError(4));
  hPt3->SetBinError(5,hSigmaBis4->GetBinError(4));
  hPt3->SetBinError(6,hSigmaBis5->GetBinError(4));
  hPt3->SetBinError(7,hSigmaBis6->GetBinError(4));
  hPt3->SetBinError(8,hSigmaBis7->GetBinError(4));
  hPt3->SetBinError(9,hSigmaBis8->GetBinError(4));
  hPt3->SetBinError(10,hSigmaBis9->GetBinError(4));
  
  hPt4->SetBinError(1,hSigmaBis0->GetBinError(5));
  hPt4->SetBinError(2,hSigmaBis1->GetBinError(5));
  hPt4->SetBinError(3,hSigmaBis2->GetBinError(5));
  hPt4->SetBinError(4,hSigmaBis3->GetBinError(5));
  hPt4->SetBinError(5,hSigmaBis4->GetBinError(5));
  hPt4->SetBinError(6,hSigmaBis5->GetBinError(5));
  hPt4->SetBinError(7,hSigmaBis6->GetBinError(5));
  hPt4->SetBinError(8,hSigmaBis7->GetBinError(5));
  hPt4->SetBinError(9,hSigmaBis8->GetBinError(5));
  hPt4->SetBinError(10,hSigmaBis9->GetBinError(5));
  

  if (idcut==1 || idcut==3) {hPt0->Scale(1/hSigmaBis0->GetBinContent(1)); hPt3->Scale(1/hSigmaBis0->GetBinContent(4)); }
  if (idcut==2 || idcut==4) {hPt0->Scale(1/hSigmaBis5->GetBinContent(1)); hPt3->Scale(1/hSigmaBis5->GetBinContent(4)); }

  TCanvas *canvasVscut=new TCanvas("canvasVscut","canvasVscut",1000,500);
  canvasVscut->cd();
  canvasVscut->Divide(2,1);
  canvasVscut->cd(1);
  if(idcut==1) hPt0->GetXaxis()->SetTitle("chi2cl cut value");
  if(idcut==2) hPt0->GetXaxis()->SetTitle("d0/d0err cut value");
  if(idcut==3) hPt0->GetXaxis()->SetTitle("cosTheta cut value");
  if(idcut==4) hPt0->GetXaxis()->SetTitle("|(trk1Dxy)/trk1D0Err)| cut value");
  hPt0->GetYaxis()->SetTitle("Ratio of corrected yield w.r.t. default");
  hPt0->GetXaxis()->SetTitleOffset(1.);
  hPt0->GetYaxis()->SetTitleOffset(1.);
  hPt0->GetXaxis()->SetTitleSize(0.04);
  hPt0->GetYaxis()->SetTitleSize(0.04);
  hPt0->GetXaxis()->SetTitleFont(42);
  hPt0->GetYaxis()->SetTitleFont(42);
  hPt0->GetXaxis()->SetLabelFont(42);
  hPt0->GetYaxis()->SetLabelFont(42);
  hPt0->GetXaxis()->SetLabelSize(0.035);
  hPt0->GetYaxis()->SetLabelSize(0.035);  
  hPt0->SetMinimum(0.);
  hPt0->Draw();
  TF1 *flowpt = new TF1("flowpt","[0]");
  hPt0->Fit("flowpt","L q","",ptBins[0],ptBins[10]);
  TLatex * tlatexlowpt=new TLatex(0.1,0.35,Form("Average discrepancy in 10 <p_{t}<15 GeV/c is %.2f",flowpt->GetParameter(0)));
  tlatexlowpt->SetNDC();
  tlatexlowpt->SetTextColor(1);
  tlatexlowpt->SetTextFont(42);
  tlatexlowpt->SetTextSize(0.035);
  tlatexlowpt->Draw();

  
  
  canvasVscut->cd(2);
  if(idcut==1) hPt3->GetXaxis()->SetTitle("chi2cl cut value");
  if(idcut==2) hPt3->GetXaxis()->SetTitle("d0/d0err cut value");
  if(idcut==3) hPt3->GetXaxis()->SetTitle("cosTheta cut value");
  if(idcut==4) hPt3->GetXaxis()->SetTitle("|(trk1Dxy)/trk1D0Err)| cut value");

  hPt3->GetYaxis()->SetTitle("Ratio of corrected yield w.r.t. default");
  hPt3->GetXaxis()->SetTitleOffset(1.);
  hPt3->GetYaxis()->SetTitleOffset(1.1);
  hPt3->GetXaxis()->SetTitleSize(0.04);
  hPt3->GetYaxis()->SetTitleSize(0.04);
  hPt3->GetXaxis()->SetTitleFont(42);
  hPt3->GetYaxis()->SetTitleFont(42);
  hPt3->GetXaxis()->SetLabelFont(42);
  hPt3->GetYaxis()->SetLabelFont(42);
  hPt3->GetXaxis()->SetLabelSize(0.035);
  hPt3->GetYaxis()->SetLabelSize(0.035);  
  hPt3->SetMinimum(0.);
  hPt3->Draw();
    TF1 *fhighpt = new TF1("fhighpt","[0]");
  hPt3->Fit("fhighpt","L q","",ptBins[0],ptBins[10]);
  TLatex * tlatexhighpt=new TLatex(0.1,0.35,Form("Average discrepancy in 25 <p_{t}<30 GeV/c is %.2f",fhighpt->GetParameter(0)));
  tlatexhighpt->SetNDC();
  tlatexhighpt->SetTextColor(1);
  tlatexhighpt->SetTextFont(42);
  tlatexhighpt->SetTextSize(0.035);
  tlatexhighpt->Draw();

  
  canvasVscut->SaveAs(Form("canvasVscutId%d.eps",idcut));
  
  
}
