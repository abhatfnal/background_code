//some standard C++ includes
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <math.h>
#include <iterator>
#include <algorithm>
#include <fstream>


//some ROOT includes
#include "TInterpreter.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TBranch.h"
#include "TVector3.h"
#include "TCanvas.h"

//"art" includes (canvas, and gallery)
#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"
#include "canvas/Persistency/Common/FindMany.h"
#include "canvas/Persistency/Common/FindOne.h"
#include "gallery/Handle.h"

//"larsoft" object includes
#include "lardataobj/RecoBase/OpFlash.h"
#include "lardataobj/RecoBase/OpHit.h"
#include "lardataobj/RawData/RawDigit.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/SpacePoint.h"
#include "lardataobj/AnalysisBase/T0.h"
#include "lardataobj/MCBase/MCTrack.h"
#include "lardataobj/MCBase/MCStep.h"

//(timing information for the beam)
#include "lardataobj/RawData/TriggerData.h"
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"
#include "larcoreobj/SimpleTypesAndConstants/RawTypes.h"

//"larreco" reconstruction for MCS.
#include "larreco/RecoAlg/TrajectoryMCSFitter.h"

using namespace art;
using namespace std;
using namespace std::chrono;
using std::vector;

void readTTree() {
    
   // gStyle->SetOptStat(0);
    
    TFile *f1 = new TFile("Gallery_output.root");
  //  TFile *f2 = new TFile("/uboone/app/users/abhat/new_nospacecharge_gallery_output.root");
    TTree *t1 = (TTree*)f1->Get("MCTracktree");
  //  TTree *t2 = (TTree*)f1->Get("RecoTracktree");

    //Variables to hold the muon track starts and ends within the detector
  //   Double_t muontrack_startX;
  //   Double_t muontrack_startZ;
  //   Double_t muontrack_startY;
  //   Double_t muontrack_endX;
  //   Double_t muontrack_endY;
   //  Double_t muontrack_endZ;
   //  Double_t muontracklength;
    
    //Variables to hold the reco track start and ends (ofcourse within the detector)
  //   Double_t recotrack_startX;
  //   Double_t recotrack_startZ;
  //   Double_t recotrack_startY;
  //   Double_t recotrack_endX;
  //   Double_t recotrack_endY;
  //   Double_t recotrack_endZ;
   //  Double_t recotracklength;
    
    Double_t angle_smallest;
    Double_t tracklength_diff; //reco-muon
    Double_t tracklength_ratio; //(reco/muon)
    


    //Branch declaration (pointers)
   
    //MC Branches
 /*
    TBranch *b_muontrack_startX = t1->GetBranch("muonStartX_det");
    TBranch *b_muontrack_startY = t1->GetBranch("muonStartY_det");
    TBranch *b_muontrack_startZ = t1->GetBranch("muonStartZ_det");
    
    TBranch *b_muontrack_endX = t1->GetBranch("muonEndX_det");
    TBranch *b_muontrack_endY = t1->GetBranch("muonEndY_det");
    TBranch *b_muontrack_endZ = t1->GetBranch("muonEndZ_det");
    
    TBranch *b_muontracklength = t1->GetBranch("muontracklength_det");
    
    //Reco Branches
    
    TBranch *b_recotrack_startX = t2->GetBranch("StartX_reco");
    TBranch *b_recotrack_startY = t2->GetBranch("StartY_reco");
    TBranch *b_recotrack_startZ = t2->GetBranch("StartZ_reco");
    
    TBranch *b_recotrack_endX = t2->GetBranch("EndX_reco");
    TBranch *b_recotrack_endY = t2->GetBranch("EndY_reco");
    TBranch *b_recotrack_endZ = t2->GetBranch("EndZ_reco");
    
    TBranch *b_recotracklength = t2->GetBranch("tracklength_reco");
  */
    TBranch *b_angle_smallest= t1->GetBranch("angle_smallest");
    TBranch *b_tracklength_diff= t1->GetBranch("tracklength_diff");
    TBranch *b_tracklength_ratio= t1->GetBranch("tracklength_ratio");
    
    
    
   //Set Address for all branch pointers
/*
    //MC
    b_muontrack_startX->SetAddress(&muontrack_startX);
    b_muontrack_startY->SetAddress(&muontrack_startY);
    b_muontrack_startZ->SetAddress(&muontrack_startZ);
    
    b_muontrack_endX->SetAddress(&muontrack_endX);
    b_muontrack_endY->SetAddress(&muontrack_endY);
    b_muontrack_endZ->SetAddress(&muontrack_endZ);
    
    b_muontracklength->SetAddress(&muontracklength);
    
    
    //Reco
    
    b_recotrack_startX->SetAddress(&recotrack_startX);
    b_recotrack_startY->SetAddress(&recotrack_startY);
    b_recotrack_startZ->SetAddress(&recotrack_startZ);
    
    b_recotrack_endX->SetAddress(&recotrack_endX);
    b_recotrack_endY->SetAddress(&recotrack_endY);
    b_recotrack_endZ->SetAddress(&recotrack_endZ);
    
    b_recotracklength->SetAddress(&recotracklength);
    
  */
    b_angle_smallest->SetAddress(&angle_smallest);
    b_tracklength_diff->SetAddress(&tracklength_diff);
    b_tracklength_ratio->SetAddress(&tracklength_ratio);
    
    TH1D* h_angle_smallest = new TH1D("h_angle_smallest","Angle difference ;Difference(radians);Number of track pairs",100000,0,90);
    TH1D* h_tracklength_diff = new TH1D("h_tracklength_diff","Tracklength difference (Reco-True) ;Difference(cm);Number of track pairs",100000,-1000,1000);
    TH1D* h_tracklength_ratio = new TH1D("h_tracklength_ratio","Tracklength ratio (Reco/True) ;Ratio;Number of track pairs",100000,0,5);
    
    
    Int_t nentries = (Int_t)t1->GetEntries();
    for (Int_t i=0;i<nentries;i++) {
        b_angle_smallest->GetEntry(i);
        b_tracklength_diff->GetEntry(i);
        b_tracklength_ratio->GetEntry(i);
        // fill the histogram with the destep entry
        h_angle_smallest->Fill(angle_smallest);
        h_tracklength_diff->Fill(tracklength_diff);
        h_tracklength_ratio->Fill(tracklength_ratio);
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    t1->Print();
  //  t2->Print();
    
    
  
    
    
    
    
    // we do not close the file; we want to keep the generated histograms;
    // we fill a 3-d scatter plot with the particle step coordinates
    TCanvas* canvas = new TCanvas("canvas","Hit Info!",1500,500);
    canvas->Divide(3);
    canvas->cd(1);
    h_angle_smallest->Draw();
    canvas->cd(2);
    h_tracklength_diff->Draw();
    canvas->cd(3);
    h_tracklength_ratio->Draw();

    

  
}
