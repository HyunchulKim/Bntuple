#include "utilities.h"
TF1 *fit(TTree *nt,double ptmin,double ptmax)
{   
   static int count=0;
   count++;
   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",100,4.8,5.8);

   // Fit function
   TF1 *f = new TF1(Form("f%d",count),"[0]*TMath::BreitWigner(x,[1],[2])+[3]+[4]*x+[5]*x*x+[6]*x*x*x+[7]*x*x*x*x");
   nt->Project(Form("h%d",count),"mass",Form("LD>0.02&&pt>%f&&pt<%f",ptmin,ptmax));    // You can change the selection cut here
   h->Draw();
   f->SetParameter(1,5.37);
   f->SetParameter(2,0.02);
   f->SetParameter(0,100);
   h->Fit(Form("f%d",count),"","",4.8,5.8);
   h->Fit(Form("f%d",count),"LL","",4.8,5.8);
   h->SetMarkerSize(0.8);
   h->SetMarkerStyle(20);
   cout <<Form("LD>0.02&&pt>%f&&pt<%f",ptmin,ptmax)<<endl;
   // function for background shape plotting. take the fit result from f
   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetParameter(2,f->GetParameter(5));
   background->SetParameter(3,f->GetParameter(6));
   background->SetParameter(4,f->GetParameter(7));
   background->SetLineColor(4);
   background->SetRange(4.8,5.8);
   background->SetLineStyle(2);
   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1(Form("fmass",count),"[0]*TMath::BreitWigner(x,[1],[2])");
   mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2));
   mass->SetParError(0,f->GetParError(0));
   mass->SetParError(1,f->GetParError(1));
   mass->SetParError(2,f->GetParError(2));
   mass->SetLineColor(2);
   mass->SetLineStyle(2);

//   cout <<mass->Integral(0,1.2)<<" "<<mass->IntegralError(0,1.2)<<endl;
   h->SetMarkerStyle(24);
   h->SetStats(0);
   h->Draw("e");
   h->SetXTitle("M_{B} (GeV/c^{2})");
   h->SetYTitle("Entries / (1 MeV/c^{2})");
   h->GetXaxis()->CenterTitle();
   h->GetYaxis()->CenterTitle();
   h->SetTitleOffset(1.65,"Y");
   h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
   background->Draw("same");   
   mass->SetRange(4.8,5.8);
   mass->Draw("same");
   mass->SetLineStyle(2);
   mass->SetFillStyle(3004);
   mass->SetFillColor(2);
   f->Draw("same");

   // Draw the legend:)   
   TLegend *leg = myLegend(0.50,0.78,0.86,0.92);
   leg->AddEntry(h,"CMS Preliminary","");
   leg->AddEntry(h,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","pl");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.23,0.89,0.40);
   leg2->AddEntry(h,"B meson","");
   leg2->AddEntry(h,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",f->GetParameter(1)*1000.,f->GetParError(1)*100.),"");
   leg2->AddEntry(h,Form("N_{B}=%.0f #pm %.0f",f->GetParameter(0)*100.,f->GetParError(0)*100.),"");
   leg2->Draw();
//   c->Write();

   c->SaveAs(Form("BFigure/BMass-%d.C",count));
   c->SaveAs(Form("BFigure/BMass-%d.gif",count));
   c->SaveAs(Form("BFigure/phiMass-%d.eps",count));

   return f;
}

void fitBs(char *infname)
{

   TFile *inf = new TFile(infname);
   TTree *nt = (TTree*) inf->Get("ntphi");

   nt->SetAlias("LD","(4.239e-03*abs(trk1Dxy)/trk1D0Err +chi2ndf*1.168e-03+trk1Chi2ndf*4.045e-04+trk1PixelHit*1.595e-04+trk1StripHit*3.943e-05)");
//   nt->SetAlias("LD","chi2ndf*(-1.3985225504085084e-03)+abs(trk1Dxy)/trk1D0Err*(-1.4107071123183248e-03)+abs(trk2Dxy)/trk2D0Err*(5.8363535276008153e-03)+abs(trk1Dxy-trk2Dxy)/sqrt(trk1D0Err*trk1D0Err+trk2D0Err*trk2D0Err)*(5.8063670890090430e-03)+(-5.3788041353745389e-03)");


//   TFile *outf = new TFile("phiHistos.root","recreate");
//   outf->cd();
   const int nBins = 1;
   double ptBins[nBins+1] = {10,60};
   TH1D *hPt = new TH1D("hPt","",nBins,ptBins);

   for (int i=0;i<nBins;i++)
   {
      TF1 *f = fit(nt,ptBins[i],ptBins[i+1]);
      hPt->SetBinContent(i+1,f->GetParameter(0)*100./(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,f->GetParError(0)*100./(ptBins[i+1]-ptBins[i]));
   }  

   TCanvas *c=  new TCanvas("cResult","",600,600);
   hPt->SetXTitle("B^{+} p_{T} (GeV/c)");
   hPt->SetYTitle("Uncorrected dN/dp_{T}");
   hPt->Draw();
   

//   outf->Write();

}