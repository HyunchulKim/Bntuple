#include <TTree.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
#include <iostream>
#include <TNtuple.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <cmath>
#include "loop.h"


void fillTree(bNtuple* b, TVector3* bP, TVector3* bVtx, TLorentzVector* b4P, int j, int REAL)
{
  // event and trigger info
  b->Event = Event;
  b->Run = Run;
  b->HLT_PAL1DoubleMu0_v1 = HLT_PAL1DoubleMu0_v1;
  b->HLT_PAL1DoubleMu0_v1_Prescl = HLT_PAL1DoubleMu0_v1_Prescl;
  b->HLT_PADimuon0_NoVertexing_v1 = HLT_PADimuon0_NoVertexing_v1;
  b->HLT_PADimuon0_NoVertexing_v1_Prescl = HLT_PADimuon0_NoVertexing_v1_Prescl;
  b->HLT_PAL1DoubleMu0_HighQ_v1 = HLT_PAL1DoubleMu0_HighQ_v1;
  b->HLT_PAL1DoubleMu0_HighQ_v1_Prescl = HLT_PAL1DoubleMu0_HighQ_v1_Prescl;
  b->HLT_PAL1DoubleMuOpen_v1 = HLT_PAL1DoubleMuOpen_v1;
  b->HLT_PAL1DoubleMuOpen_v1_Prescl = HLT_PAL1DoubleMuOpen_v1_Prescl;
  b->HLT_PAL2DoubleMu3_v1 = HLT_PAL2DoubleMu3_v1;
  b->HLT_PAL2DoubleMu3_v1_Prescl = HLT_PAL2DoubleMu3_v1_Prescl;
  b->HLT_PAMu3_v1 = HLT_PAMu3_v1;
  b->HLT_PAMu3_v1_Prescl = HLT_PAMu3_v1_Prescl;
  b->HLT_PAMu7_v1 = HLT_PAMu7_v1;
  b->HLT_PAMu7_v1_Prescl = HLT_PAMu7_v1_Prescl;
  b->HLT_PAMu12_v1 = HLT_PAMu12_v1;
  b->HLT_PAMu12_v1_Prescl = HLT_PAMu12_v1_Prescl;

  //b section
  bP->SetXYZ(BInfo_px[j],BInfo_py[j],BInfo_pz[j]*0);
  bVtx->SetXYZ(BInfo_vtxX[j]-EvtInfo_PVx,
	       BInfo_vtxY[j]-EvtInfo_PVy,
	       BInfo_vtxZ[j]*0-EvtInfo_PVz*0);

  b4P->SetXYZM(BInfo_px[j],BInfo_py[j],BInfo_pz[j],BInfo_mass[j]);
  b->y = b4P->Rapidity();
  b->dtheta = bP->Angle(*bVtx);
  b->pt = BInfo_pt[j];
  b->eta = BInfo_eta[j];
  b->phi = BInfo_phi[j];
  b->chi2cl = TMath::Prob(BInfo_vtxchi2[j],BInfo_vtxdof[j]);
  b->d0 = sqrt((BInfo_vtxX[j]-EvtInfo_PVx)*(BInfo_vtxX[j]-EvtInfo_PVx)+(BInfo_vtxY[j]-EvtInfo_PVy)*(BInfo_vtxY[j]-EvtInfo_PVy));
  b->vx = BInfo_vtxX[j] - EvtInfo_PVx;
  b->vy = BInfo_vtxY[j] - EvtInfo_PVy;
  b->d0Err = sqrt(BInfo_vtxXE[j]*BInfo_vtxXE[j]+BInfo_vtxYE[j]*BInfo_vtxYE[j]);
  b->mass = BInfo_mass[j];
  b->tktkmass = BInfo_tktk_mass[j];
  b->chi2ndf = BInfo_vtxchi2[j]/BInfo_vtxdof[j];
  b->lxy = ((BInfo_vtxX[j]-EvtInfo_PVx)*BInfo_px[j] + (BInfo_vtxY[j]-EvtInfo_PVy)*BInfo_py[j])/BInfo_pt[j];

  //muon section
  b->mu1Striplayer = MuonInfo_i_nStripLayer[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  b->mu1Pixellayer = MuonInfo_i_nPixelLayer[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  b->mu1Chi2ndf = MuonInfo_i_chi2[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]/MuonInfo_i_ndf[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  b->mu1dxy = MuonInfo_dxyPV[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  b->mu1dz = MuonInfo_dzPV[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]];
  if(MuonInfo_muqual[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]&16) b->mu1TrackerMuArbitrated = 1;
  else b->mu1TrackerMuArbitrated = 0;
  if(MuonInfo_muqual[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]&4096) b->mu1StationTight = 1;
  else b->mu1StationTight = 0;

  b->mu2Striplayer = MuonInfo_i_nStripLayer[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  b->mu2Pixellayer = MuonInfo_i_nPixelLayer[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  b->mu2Chi2ndf = MuonInfo_i_chi2[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]/MuonInfo_i_ndf[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  b->mu2dxy = MuonInfo_dxyPV[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  b->mu2dz = MuonInfo_dzPV[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]];
  if(MuonInfo_muqual[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]&16) b->mu2TrackerMuArbitrated = 1;
  else b->mu2TrackerMuArbitrated = 0;
  if(MuonInfo_muqual[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]&4096) b->mu2StationTight = 1;
  else b->mu2StationTight = 0;
  
  //jpsi section
  b->ujmass = BInfo_uj_mass[BInfo_rfuj_index[j]];
  b->ujvProb = TMath::Prob(BInfo_uj_vtxchi2[BInfo_rfuj_index[j]],BInfo_uj_vtxdof[BInfo_rfuj_index[j]]);
  b4P->SetXYZM(BInfo_uj_px[BInfo_rfuj_index[j]],
	       BInfo_uj_py[BInfo_rfuj_index[j]],
	       BInfo_uj_pz[BInfo_rfuj_index[j]],
	       BInfo_uj_mass[BInfo_rfuj_index[j]]);
  b->ujpt = b4P->Pt();
  b->ujeta = b4P->PseudoRapidity();
  b->ujy = b4P->Rapidity();
  b->ujlxy = ((BInfo_uj_vtxX[BInfo_rfuj_index[j]]-EvtInfo_PVx)*BInfo_uj_px[BInfo_rfuj_index[j]] + (BInfo_uj_vtxY[BInfo_rfuj_index[j]]-EvtInfo_PVy)*BInfo_uj_py[BInfo_rfuj_index[j]])/b->ujpt;

  //track section
  b->trk1Dxy = TrackInfo_dxyPV[BInfo_rftk1_index[j]];
  b->trk1D0Err = TrackInfo_d0error[BInfo_rftk1_index[j]];
  b->trk1PixelHit = TrackInfo_pixelhit[BInfo_rftk1_index[j]];
  b->trk1StripHit = TrackInfo_striphit[BInfo_rftk1_index[j]];
  b->trk1Pt = TrackInfo_pt[BInfo_rftk1_index[j]];
  b->trk1Chi2ndf = TrackInfo_chi2[BInfo_rftk1_index[j]]/TrackInfo_ndf[BInfo_rftk1_index[j]];
  
  if(BInfo_type[j]==1 || BInfo_type[j]==2)
    {
      b->trk2Dxy = 0;
      b->trk2D0Err = 0;
      b->trk2PixelHit = 0;
      b->trk2StripHit = 0;
      b->trk2Pt = 0;
      b->trk2Chi2ndf = 0;
      b->tktkmass = -1;
      b->tktkvProb = -1;
      b->tktkpt = -1;
      b->tktketa = -1;
      b->tktky = -1;
    }  
  else
    {
      b->trk2Dxy = TrackInfo_dxyPV[BInfo_rftk2_index[j]];
      b->trk2D0Err = TrackInfo_d0error[BInfo_rftk2_index[j]];
      b->trk2PixelHit = TrackInfo_pixelhit[BInfo_rftk2_index[j]];
      b->trk2StripHit = TrackInfo_striphit[BInfo_rftk2_index[j]];
      b->trk2Pt = TrackInfo_pt[BInfo_rftk2_index[j]];
      b->trk2Chi2ndf = TrackInfo_chi2[BInfo_rftk2_index[j]]/TrackInfo_ndf[BInfo_rftk2_index[j]];
      b->tktkmass = BInfo_tktk_mass[j];
      b->tktkvProb = TMath::Prob(BInfo_tktk_vtxchi2[j],BInfo_tktk_vtxdof[j]);
      b4P->SetXYZM(BInfo_tktk_px[j],BInfo_tktk_py[j],BInfo_tktk_pz[j],BInfo_tktk_mass[j]);
      b->tktkpt = b4P->Pt();
      b->tktketa = b4P->PseudoRapidity();
      b->tktky = b4P->Rapidity();
    }

  
  //gen info judgement

  if(!REAL)
    {
      b->gen=0;//gen init
      b->genIndex=-1;//gen init
      b->genpt=-1;
      b->geny=-1;
      int mGenIdxTk1=-1;
      int mGenIdxTk2=-1;
      int bGenIdxTk1=-1;
      int bGenIdxTk2=-1;
      int bGenIdxMu1=-1;
      int bGenIdxMu2=-1;
      
      
      float BId,MId,tk1Id,tk2Id;
      //tk1:positive, tk2:negtive
      if(BInfo_type[j]==1)
	{
	  BId = 521;//B+-
	  MId = -1;
	  tk1Id = 321;//K+-
	  tk2Id = -1;
	}
      if(BInfo_type[j]==2)
	{
	  BId = 521;//B+-
	  MId = -1;
	  tk1Id = 211;//pi+-
	  tk2Id = -1;
	}
      if(BInfo_type[j]==3)
	{
	  BId = 511;//B0
	  MId = 310;//Ks
	  tk1Id = 211;//pi+
	  tk2Id = 211;//pi-
	}
      if(BInfo_type[j]==4)
	{
	  BId = 511;//B0
	  MId = 313;//K*0
	  tk1Id = 321;//K+
	  tk2Id = 211;//pi-
	}
      if(BInfo_type[j]==5)
	{
	  BId = 511;//B0
	  MId = 313;//K*0
	  tk1Id = 211;//pi+
	  tk2Id = 321;//K-
	}
      if(BInfo_type[j]==6)
	{
	  BId = 531;//Bs
	  MId = 333;//phi
	  tk1Id = 321;//K+
	  tk2Id = 321;//K-
	}
      
      int twoTks,kStar,flagkstar=0;
      if(BInfo_type[j]==1 || BInfo_type[j]==2) twoTks=0;
      else twoTks=1;
      if(BInfo_type[j]==4 || BInfo_type[j]==5) kStar=1;
      else kStar=0;

      // tk1
      if(TrackInfo_geninfo_index[BInfo_rftk1_index[j]]>-1)
	{
	  int level =0;
	  if(fabs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]])==tk1Id)
	    {
	      level = 1;
	      if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]>-1)
		{
		  if(!twoTks)//one trk channel
		    {
		      mGenIdxTk1=0;
		      if(fabs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==BId)
			{
			  level = 3;
			  bGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}		  
		    }
		  else//two trk channel
		    {
		      if(fabs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==MId)
			{
			  level = 2;
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]>-1)
			    {
			      if(fabs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]])==BId)
				{
				  level = 3;
				  bGenIdxTk1=GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]];
				}
			    }
			  mGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}
		    }
		}
	    }
	  b->gen=level;
	}
      
      //tk2
      if(!twoTks)//one trk channel
	{
	  b->gen+=30;
	  mGenIdxTk2=0;
	  bGenIdxTk2=0;
	}
      else//two trk channel
	{
	  if(TrackInfo_geninfo_index[BInfo_rftk2_index[j]]>-1)
	    {
	      int level =0;
	      if(fabs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]])==tk2Id)
		{
		  level = 1;
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]>-1)
		    {
		      if(fabs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]])==MId)
			{
			  level = 2;
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]>-1)
			    {
			      if(fabs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]])==BId)
				{
				  level = 3;
				  bGenIdxTk2 = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]];
				}
			    }
			  mGenIdxTk2 = GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]];
			}
		    }
		}
	      b->gen+=(level*10);
	    }
	}

     
      //mu1
      if(MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]>-1)
	{  
	  int level =0;
	  if(fabs(GenInfo_pdgId[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]])==13) level=1;
	  if(GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]>-1)
	    {
	      if(GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]>-1)
		{
		  if(fabs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]]])==BId)
		    {
		      level = 2;
		      bGenIdxMu1=GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu1_index[BInfo_rfuj_index[j]]]]];
		      flagkstar++;///////////////////////////////////////////////=1
		    }
		} 
	    }
	  b->gen+=(level*100);
	}
      
      //mu2
      if(MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]>-1)
	{  
	  int level =0;
	  if(fabs(GenInfo_pdgId[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]])==13) level = 1;
	  if(GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]>-1)
	    {
	      if(GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]]>-1)
		{
		  if(fabs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]]])==BId)
		    {
		      level = 2;
		      bGenIdxMu2=GenInfo_mo1[GenInfo_mo1[MuonInfo_geninfo_index[BInfo_uj_rfmu2_index[BInfo_rfuj_index[j]]]]];
		      flagkstar++;///////////////////////////////////////////////////=2
		    }
		}
	    }
	  b->gen+=(level*1000);
	}
      
      int level=0;
      if(mGenIdxTk1!=-1 && mGenIdxTk2!=-1)
	{
	  if(!twoTks) level=1;
	  else
	    {
	      if(mGenIdxTk1==mGenIdxTk2) level=1;
	    }
	}
      if(bGenIdxMu1!=-1 && bGenIdxMu1==bGenIdxMu2 && bGenIdxMu1==bGenIdxTk1)
	{
	  if(!twoTks)
	    {
	      level=2;
	      b->genIndex = bGenIdxMu1;
	    }
	  else if(bGenIdxMu1==bGenIdxTk2)
	    {
	      level=2;
	      b->genIndex = bGenIdxMu1;
	    }
	}
      b->gen+=(level*10000);

      //kstar#############################################################################
      if(kStar)
	{
	  //tk1
	  if(TrackInfo_geninfo_index[BInfo_rftk1_index[j]]>-1)
	    {
	      if(fabs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]])==tk2Id)
		{
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]>-1)
		    {
		      if(fabs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]])==MId)
			{
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]>-1)
			    {
			      if(fabs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]]])==BId)
				{
				  flagkstar++;//////////////////////////////////////////////=3
				  bGenIdxTk1=GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]]];
				}
			    }
			  mGenIdxTk1=GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk1_index[j]]];
			}
		    }
		}
	    }
	  
	  //tk2
	  if(TrackInfo_geninfo_index[BInfo_rftk2_index[j]]>-1)
	    {
	      if(fabs(GenInfo_pdgId[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]])==tk1Id)
		{
		  if(GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]>-1)
		    {
		      if(fabs(GenInfo_pdgId[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]])==MId)
			{
			  if(GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]>-1)
			    {
			      if(fabs(GenInfo_pdgId[GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]]])==BId)
				{
				  flagkstar++;////////////////////////////////////////////////////=4
				  bGenIdxTk2 = GenInfo_mo1[GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]]];
				}
			    }
			  mGenIdxTk2 = GenInfo_mo1[TrackInfo_geninfo_index[BInfo_rftk2_index[j]]];
			}
		    }
		}
	    }
	  if(flagkstar==4)
	    {
	      if((bGenIdxMu1!=-1) 
		 && (bGenIdxMu1==bGenIdxMu2)
		 && (bGenIdxMu1==bGenIdxTk1)
		 && (bGenIdxMu1==bGenIdxTk2)
		 )
		{
		  b->gen=41000;
		}
	    }
	}//kstar End#############################################################################

      int tgenIndex=b->genIndex;
      if(b->gen==22233)
	{
	  b->genpt = GenInfo_pt[tgenIndex];
	  b->geneta = GenInfo_eta[tgenIndex];
	  b4P->SetXYZM(GenInfo_pt[tgenIndex]*cos(GenInfo_phi[tgenIndex]),
		       GenInfo_pt[tgenIndex]*sin(GenInfo_phi[tgenIndex]),
		       GenInfo_pt[tgenIndex]*sinh(GenInfo_eta[tgenIndex]),
		       GenInfo_mass[tgenIndex]);
	  b->geny = b4P->Rapidity();
	}
    }
}

int signalGen(int Btype, int j)
{
  float BId,MId,tk1Id,tk2Id;
  int twoTks;
  //tk1:positive, tk2:negtive
  if(Btype==1)
    {
      BId = 521;//B+-
      MId = -1;
      tk1Id = 321;//K+-
      tk2Id = -1;
      twoTks = 0;
    }
  if(Btype==2)
    {
      BId = 521;//B+-
      MId = -1;
      tk1Id = 211;//pi+-
      tk2Id = -1;
      twoTks = 0;
    }
  if(Btype==3)
    {
      BId = 511;//B0
      MId = 310;//Ks
      tk1Id = 211;//pi+
      tk2Id = 211;//pi-
      twoTks = 1;
    }
  if(Btype==4)
    {
      BId = 511;//B0
      MId = 313;//K*0
      tk1Id = 321;//K+
      tk2Id = 211;//pi-
      twoTks = 1;
    }
  if(Btype==5)
    {
      BId = 511;//B0
      MId = 313;//K*0
      tk1Id = 211;//pi+
      tk2Id = 321;//K-
      twoTks = 1;
    }
  if(Btype==6)
    {
      BId = 531;//Bs
      MId = 333;//phi
      tk1Id = 321;//K+
      tk2Id = 321;//K-
      twoTks = 1;
    }

  int flag=0;
  if (fabs(GenInfo_pdgId[j])==BId&&GenInfo_nDa[j]==2&&GenInfo_da1[j]!=-1&&GenInfo_da2[j]!=-1)
    {
      if (fabs(GenInfo_pdgId[GenInfo_da1[j]]==443))//jpsi
	{
	  if(!twoTks)
	    {
	      if(fabs(GenInfo_pdgId[GenInfo_da2[j]])==tk1Id) flag++;
	    }
	  else
	    {
	      if (fabs(GenInfo_pdgId[GenInfo_da2[j]])==MId) 
		{
		  if(GenInfo_da1[GenInfo_da2[j]]!=-1 && GenInfo_da2[GenInfo_da2[j]]!=-1)
		    {
		      if(fabs(GenInfo_pdgId[GenInfo_da1[GenInfo_da2[j]]])==tk1Id && fabs(GenInfo_pdgId[GenInfo_da2[GenInfo_da2[j]]])==tk2Id) flag++;
		    }
		}
	    }
	}
    }

  return flag;
}



void loop(string infile="/d00/bmeson/MC/Bfinder_BoostedMC_20140303_kstar.root", string outfile="test_kstar.root", bool REAL=0){
//////////////////////////////////////////////////////////Phi
//   This file has been automatically generated 
//     (Thu Nov 21 13:34:42 2013 by ROOT version5.27/06b)
//   from TTree root/root
//   found on file: merged_pPbData_20131114.root
//////////////////////////////////////////////////////////

  const char* infname;
  const char* outfname;


  if(REAL) cout<<"--- REAL DATA ---"<<endl;
  else cout<<"--- MC ---"<<endl;

  /*
  if(REAL)
    {
      cout<<"--- REAL DATA ---"<<endl;
      //infname = "/net/hidsk0001/d00/scratch/yjlee/bmeson/merged_pPbData_20131114.root";
      //infname = "/net/hidsk0001/d00/scratch/jwang/data_merge.root";
      //infname = "/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140218_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_100_1_Jrd.root";
      //outfname = "/export/d00/scratch/jwang/ntfile/nt_data.root";
      //outfname = "nt_data_test.root";
    }
   else
     {
       cout<<"--- MC ---"<<endl;
       infname = "/net/hidsk0001/d00/scratch/jwang/Bfinder_all_full_20140219/Bfinder_all_MC_Kp.root";
       //outfname = "/export/d00/scratch/jwang/ntfile/mc_20140218/nt_mc_Kstar.root";
       outfname = "nt_mc_kp.root";
//      infname = "/net/hidsk0001/d00/scratch/jwang/data_merge.root";
        infname = "sample/merged_20140213_PAMuon_HIRun2013_PromptReco_v1.root";
      outfname = "test.root";
     }
   else
     {
      cout<<"--- MC ---"<<endl;
      infname = "/net/hidsk0001/d00/scratch/jwang/Bfinder_all_full_20140215/Bfinder_all_MC_Phi.root";
//        infname = "/net/hidsk0001/d00/scratch/jwang/Bfinder_all_full_20140215/Bfinder_all_MC_Kstar.root";
//        infname = "/net/hidsk0001/d00/scratch/jwang/Bfinder_all_full_20140215/Bfinder_all_MC_.root";
      //outfname = "/export/d00/scratch/jwang/ntfile/nt_mc_Phi.root";
      outfname = "test_mc.root";
     }
  */

  infname = infile.c_str();
  outfname = outfile.c_str();

  //File type
  TFile *f = new TFile(infname);
  TTree *root = (TTree*)f->Get("demo/root");
  TTree *hlt = (TTree*)f->Get("hltanalysis/HltTree");
  if (root->GetEntries()!=hlt->GetEntries()) {
     cout <<"Inconsistent number of entries!!!"<<endl;
     cout <<"HLT tree: "<<hlt->GetEntries()<<endl;
     cout <<"Bfinder tree: "<<root->GetEntries()<<endl;
  }
  
  //Chain type
  //TChain* root = new TChain("demo/root");
  //root->Add("/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140213_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_100_1_dXJ.root");
  //root->Add("/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140213_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_101_1_kuy.root");
  //root->Add("/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140213_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_10_1_ZkX.root");
  //root->Add("/mnt/hadoop/cms/store/user/wangj/HI_Btuple/20140213_PAMuon_HIRun2013_PromptReco_v1/Bfinder_all_102_1_NyI.root");
  
  TFile *outf = new TFile(outfname,"recreate");
  setBranch(root);
  setHltBranch(hlt);
  
  
  int ifchannel[7];
  ifchannel[0] = 1; //jpsi+Kp
  ifchannel[1] = 1; //jpsi+pi
  ifchannel[2] = 1; //jpsi+Ks(pi+,pi-)
  ifchannel[3] = 1; //jpsi+K*(K+,pi-)
  ifchannel[4] = 1; //jpsi+K*(K-,pi+)
  ifchannel[5] = 1; //jpsi+phi
  ifchannel[6] = 1; //jpsi+pi pi <= psi', X(3872), Bs->J/psi f0
  bNtuple* b0 = new bNtuple;
  bNtuple* b1 = new bNtuple;
  bNtuple* b2 = new bNtuple;
  bNtuple* b3 = new bNtuple;
  bNtuple* b4 = new bNtuple;
  bNtuple* b5 = new bNtuple;
  bNtuple* b6 = new bNtuple;
  
  TTree* nt0 = new TTree("ntKp","");
  b0->buildBranch(nt0);
  TTree* nt1 = new TTree("ntpi","");
  b1->buildBranch(nt1);
  TTree* nt2 = new TTree("ntKs","");
  b2->buildBranch(nt2);
  TTree* nt3 = new TTree("ntKstar1","");
  b3->buildBranch(nt3);
  TTree* nt4 = new TTree("ntKstar2","");
  b4->buildBranch(nt4);
  TTree* nt5 = new TTree("ntphi","");
  b5->buildBranch(nt5);
  TTree* nt6 = new TTree("ntmix","");
  b6->buildBranch(nt6);
  
  TNtuple* ntGen = new TNtuple("ntGen","","y:eta:phi:pt:pdgId:isSignal");
  
  Long64_t nentries = root->GetEntries();
  Long64_t nbytes = 0;
  TVector3* bP = new TVector3;
  TVector3* bVtx = new TVector3;
  TLorentzVector* b4P = new TLorentzVector;
  TLorentzVector bGen;
  int type,flag;
  int flagEvt=0;  
  int offsetHltTree=0;
  
  for (Long64_t i=0; i<nentries;i++) {
    nbytes += root->GetEntry(i);

    flagEvt=0;
    while (flagEvt==0)
    {
       hlt->GetEntry(i+offsetHltTree);
//       cout <<offsetHltTree<<" "<<Event<<" "<<EvtInfo_EvtNo<<endl;
       if (Event ==EvtInfo_EvtNo && Run == EvtInfo_RunNo) flagEvt=1; else offsetHltTree++;
    } 
    if (i%10000==0) cout <<i<<" / "<<nentries<<"   offset HLT:"<<offsetHltTree<<endl;
    for (int j=0;j<BInfo_size;j++) {
      if(BInfo_type[j]>7) continue;
      if (ifchannel[BInfo_type[j]-1]!=1) continue;
      if(BInfo_type[j]==1)
	{
	  fillTree(b0,bP,bVtx,b4P,j,REAL);
	  nt0->Fill();
	}
      if(BInfo_type[j]==2)
	{
	  fillTree(b1,bP,bVtx,b4P,j,REAL);
	  nt1->Fill();
	}
      if(BInfo_type[j]==3)
	{
	  fillTree(b2,bP,bVtx,b4P,j,REAL);
	  nt2->Fill();
	}
      if(BInfo_type[j]==4)
	{
	  fillTree(b3,bP,bVtx,b4P,j,REAL);
	  nt3->Fill();
	  }
      if(BInfo_type[j]==5)
	{
	  fillTree(b4,bP,bVtx,b4P,j,REAL);
	  nt4->Fill();
	}
      if(BInfo_type[j]==6)
	{
	  fillTree(b5,bP,bVtx,b4P,j,REAL);
	  nt5->Fill();
	}
      if(BInfo_type[j]==7)
	{
	  fillTree(b6,bP,bVtx,b4P,j,REAL);
	  nt6->Fill();
	}
    }
    
    if(!REAL)
      {
	for (int j=0;j<GenInfo_size;j++)
	  {
	    flag=0;
	    for(type=1;type<8;type++)
	      {
		if (signalGen(type,j)) {
                  flag=type;
		  break;
                }
	      }
	    bGen.SetPtEtaPhiM(GenInfo_pt[j],GenInfo_eta[j],GenInfo_phi[j],GenInfo_mass[j]);
	    ntGen->Fill(bGen.Rapidity(),bGen.Eta(),bGen.Phi(),bGen.Pt(),GenInfo_pdgId[j],flag);
	  }
      }
  }
  
  outf->Write();
  outf->Close();
}


