#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TEfficiency.h>
void MyClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MyClass.C
//      root> MyClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   

    TH1D* h1 = new TH1D("h1","Denom",100,0,900);
    TH1D* h2 = new TH1D("h2","Reconstruction Efficiency v/s MCTrack length;MCTrack length;Efficiency",100,0,900);
 //   TEfficiency* eff = new TEfficiency(h2,h1);
    
    if (fChain == 0) return;
    
    
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
    
    Int_t binsize=30;
    
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
       
       h1->Fill(muontracklength_det);
       if(angle_smallest<0.1)
       {
           h2->Fill(muontracklength_det);
       }
       
      // if (Cut(ientry) < 0) continue;
       
         }
//    h1->Draw();
 
 //   h2->Draw();

//    h2->Divide(h1);
    TEfficiency* eff = new TEfficiency(*h2,*h1);
  //  eff->SetStatisticOption(TEfficiency::kFCP);
  //  eff->SetConfidenceLevel(0.68);

  
 TCanvas* canvas = new TCanvas("canvas","Hit Info!",1500,500);
  

 
    
    eff->SetTitle("Efficiency Plot;MCTrack length (cm);Efficiency");
  //  eff->SetFillColor(kGreen);
    eff->Draw("AB");
}
