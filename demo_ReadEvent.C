
/*************************************************************
 * 
 * demo_ReadEvent program
 * 
 * This is a simple demonstration of reading a LArSoft file 
 * and printing out the run and event numbers. You can also
 * put the event numbers into a histogram!
 *
 * Original Author: Wesley Ketchum (wketchum@fnal.gov), Aug28, 2016
 * Eidted by : Avinay Bhat (abhat@fnal.gov)
 *************************************************************/


//some standard C++ includes
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

//some ROOT includes
#include "TInterpreter.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TStopwatch.h"
#include "TTree.h"
#include "TBranch.h"
#include "TVector3.h"
#include "TGraph.h"

//"art" includes (canvas, and gallery)
#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"
#include "canvas/Persistency/Common/FindMany.h"
#include "canvas/Persistency/Common/FindOne.h"
#include "lardataobj/MCBase/MCTrack.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Hit.h"

//convenient for us! let's not bother with art and std namespaces!
using namespace art;
using namespace std;

void ShowUnderOverFlow( TH1* h1){
  h1->SetBinContent(1, h1->GetBinContent(0)+h1->GetBinContent(1));
  h1->SetBinContent(0,0);
    
  Int_t nbins = h1->GetNbinsX();
  h1->SetBinContent(nbins, h1->GetBinContent(nbins)+h1->GetBinContent(nbins+1));
  h1->SetBinContent(nbins+1,0);
}




void demo_ReadEvent(){
 
  gStyle->SetOptStat(0);
    
  TFile f_output("Gallery_output.root","RECREATE");
    
    
    
  //MC VARIABLES
    
  Int_t mypdg;
  Double_t StartX;
  Double_t StartY;
  Double_t StartZ;
  Double_t EndX;
  Double_t EndY;
  Double_t EndZ;
    
    
  Double_t StartX_det;
  Double_t StartY_det;
  Double_t StartZ_det;
  Double_t EndX_det;
  Double_t EndY_det;
  Double_t EndZ_det;
    
    
    
  Double_t tracklength;
  
    
    
    
  Double_t muonStartX;
  Double_t muonStartY;
  Double_t muonStartZ;
  Double_t muonEndX;
  Double_t muonEndY;
  Double_t muonEndZ;
    
    
    
  Double_t muonStartX_det;
  Double_t muonStartY_det;
  Double_t muonStartZ_det;
  Double_t muonEndX_det;
  Double_t muonEndY_det;
  Double_t muonEndZ_det;
    
    
    
  Double_t muontracklength;
  Double_t muontracklength_det;
    
    
    
  //RECO VARIABLES////
    
    
    
  Double_t StartX_reco;
  Double_t StartY_reco;
  Double_t StartZ_reco;
  Double_t EndX_reco;
  Double_t EndY_reco;
  Double_t EndZ_reco;
    
  Double_t tracklength_reco;
    
  Double_t dotprod=0;
  Double_t costheta;
  Double_t angle=0;
  Double_t angle_smallest=0;
    
    
  //match
    

  Double_t tracklength_reco_smallest=0;
  Double_t dotprod_smallest=0;
  Double_t StartX_reco_smallest=0;
  Double_t StartY_reco_smallest=0;
  Double_t StartZ_reco_smallest=0;
  Double_t EndX_reco_smallest=0;
  Double_t EndY_reco_smallest=0;
  Double_t EndZ_reco_smallest=0;
  Double_t costheta_smallest=0;
  Double_t tracklength_diff=0; //reco-muon
  Double_t tracklength_ratio=0; //(reco/muon)
    
    
 

    
  //MC Tree
  TTree* MCTracktree = new TTree("MCTracktree","MCTracktree");
 
  //Reco Tree
    
    
  TTree* RecoTracktree = new TTree("RecoTracktree","RecoTracktree");
    
    
  //MC Tree Branches
    
  MCTracktree->Branch("mypdg",&mypdg,"mypdg/D");
  MCTracktree->Branch("StartX",&StartX,"StartX/D");
  MCTracktree->Branch("StartY",&StartY,"StartY/D");
  MCTracktree->Branch("StartZ",&StartZ,"StartZ/D");
  MCTracktree->Branch("EndX",&EndX,"EndX/D");
  MCTracktree->Branch("EndY",&EndY,"EndY/D");
  MCTracktree->Branch("EndZ",&EndZ,"EndZ/D");
  
    
  MCTracktree->Branch("StartX_det",&StartX_det,"StartX_det/D");
  MCTracktree->Branch("StartY_det",&StartY_det,"StartY_det/D");
  MCTracktree->Branch("StartZ_det",&StartZ_det,"StartZ_det/D");
  MCTracktree->Branch("EndX_det",&EndX_det,"EndX_det/D");
  MCTracktree->Branch("EndY_det",&EndY_det,"EndY_det/D");
  MCTracktree->Branch("EndZ_det",&EndZ_det,"EndZ_det/D");

  
  MCTracktree->Branch("muonStartX",&muonStartX,"muonStartX/D");
  MCTracktree->Branch("muonStartY",&muonStartY,"muonStartY/D");
  MCTracktree->Branch("muonStartZ",&muonStartZ,"muonStartZ/D");
  MCTracktree->Branch("muonEndX",&muonEndX,"muonEndX/D");
  MCTracktree->Branch("muonEndY",&muonEndY,"muonEndY/D");
  MCTracktree->Branch("muonEndZ",&muonEndZ,"muonEndZ/D");

    
  
  MCTracktree->Branch("muonStartX_det",&muonStartX_det,"muonStartX_det/D");
  MCTracktree->Branch("muonStartY_det",&muonStartY_det,"muonStartY_det/D");
  MCTracktree->Branch("muonStartZ_det",&muonStartZ_det,"muonStartZ_det/D");
  MCTracktree->Branch("muonEndX_det",&muonEndX_det,"muonEndX_det/D");
  MCTracktree->Branch("muonEndY_det",&muonEndY_det,"muonEndY_det/D");
  MCTracktree->Branch("muonEndZ_det",&muonEndZ_det,"muonEndZ_det/D");
    
    
  MCTracktree->Branch("tracklength",&tracklength,"tracklength/D");
  MCTracktree->Branch("muontracklength",&muontracklength,"muontracklength/D");
  MCTracktree->Branch("muontracklength_det",&muontracklength_det,"muontracklength_det/D");
  //   MCTracktree->Branch("tracklength_det",&tracklength_det,"tracklength_det/D");
    
   
  //Reco Tree Branches
    
    
    
  RecoTracktree->Branch("StartX_reco",&StartX_reco,"StartX_reco/D");
  RecoTracktree->Branch("StartY_reco",&StartY_reco,"StartY_reco/D");
  RecoTracktree->Branch("StartZ_reco",&StartZ_reco,"StartZ_reco/D");
  RecoTracktree->Branch("EndX_reco",&EndX_reco,"EndX_reco/D");
  RecoTracktree->Branch("EndY_reco",&EndY_reco,"EndY_reco/D");
  RecoTracktree->Branch("EndZ_reco",&EndZ_reco,"EndZ_reco/D");
  RecoTracktree->Branch("tracklength_reco",&tracklength_reco,"tracklength_reco/D");
    
    
  // Match  Branches for MCTracktree
    
    
  MCTracktree->Branch("StartX_reco_smallest",&StartX_reco_smallest,"StartX_reco_smallest/D");
  MCTracktree->Branch("StartY_reco_smallest",&StartY_reco_smallest,"StartY_reco_smallest/D");
  MCTracktree->Branch("StartZ_reco_smallest",&StartZ_reco_smallest,"StartZ_reco_smallest/D");
  MCTracktree->Branch("EndX_reco_smallest",&EndX_reco_smallest,"EndX_reco_smallest/D");
  MCTracktree->Branch("EndY_reco_smallest",&EndY_reco_smallest,"EndY_reco_smallest/D");
  MCTracktree->Branch("EndZ_reco_smallest",&EndZ_reco_smallest,"EndZ_reco_smallest/D");
  MCTracktree->Branch("costheta_smallest",&costheta_smallest,"costheta_smallest/D");
  MCTracktree->Branch("angle_smallest",&angle_smallest,"angle_smallest/D");
  MCTracktree->Branch("tracklength_reco_smallest",&tracklength_reco_smallest,"tracklength_reco_smallest/D");
  MCTracktree->Branch("dotprod_smallest",&dotprod_smallest,"dotprod_smallest/D");
  MCTracktree->Branch("tracklength_diff",&tracklength_diff,"tracklength_diff/D");
  MCTracktree->Branch("tracklength_ratio",&tracklength_ratio,"tracklength_ratio/D");
    

    
    
    
  //We specify our files in a list of file names!
  //Note: multiple files allowed. Just separate by comma.
  //  vector<string> filenames { "MyInputFile_1.root" };
  // vector<string> filenames { "/pnfs/uboone/mc/uboone/reconstructed/prod_v06_26_06/prodcosmics_corsika_cmc_uboone_intime_reco/reco/prodcosmics_corsika_cmc_uboone_intime_9_20180106T234834_gen2_b68094ab-d48a-42de-84f1-274a79047091_20180125T160523_reco1_20180125T163723_reco2.root","/pnfs/uboone/mc/uboone/reconstructed/prod_v06_26_06/prodcosmics_corsika_cmc_uboone_intime_reco/reco/prodcosmics_corsika_cmc_uboone_intime_0_20171228T135151_gen2_ad665c20-75db-467b-80fc-d945e794f389_20180111T075909_reco1_20180111T082044_reco2.root" };
    
  vector<string> filenames;
  ifstream myfile("/uboone/app/users/abhat/background/file_list.txt");
  copy(istream_iterator<string>(myfile),istream_iterator<string>(),back_inserter(filenames));
   
    
  
  InputTag mctrack_tag{"mcreco"};
  InputTag recotrack_tag{"pandoraCosmic"};
  //ok, now for the event loop! Here's how it works.
  //
  //gallery has these built-in iterator things.
  //
  //You declare an event with a list of file names. Then, you
  //move to the next event by using the "next()" function.
  //Do that until you are "atEnd()".
  //
  //In a for loop, that looks like this:
  
  Double_t x1[1000],y1[1000],x2[1000],y2[1000];
    
    
    
    
    
    
    
  Int_t counter=0;
  for (gallery::Event ev(filenames) ; !ev.atEnd(); ev.next()) {
   

    //to get run and event info, you use this "eventAuxillary()" object.
    cout << "Processing "
	 << "Run " << ev.eventAuxiliary().run() << ", "
	 << "Event " << ev.eventAuxiliary().event() << endl;

    // Track Handle Information in the loop.
      
    auto const& mctrack_handle = ev.getValidHandle<vector<sim::MCTrack>>(mctrack_tag);
    auto const& mctrack_vec(*mctrack_handle);
 
      
    auto const& recotrack_handle = ev.getValidHandle<vector<recob::Track>>(recotrack_tag);
    auto const& recotrack_vec(*recotrack_handle);
      
      
    counter++;
      
    cout << "\tThere are " <<mctrack_vec.size()<< " MC tracks in this event." << endl;
  
    // h_MCTrack_length->Fill(mctrack_vec.size());
      
    cout << "\tThere are " <<recotrack_vec.size()<< " Reco tracks in this event." << endl;
      
      
    x1[counter]=counter;
    y1[counter]=mctrack_vec.size();
      
      
      
      
    Int_t muontrackcount=0;
      
    for (auto const& a : mctrack_vec){
         
          
      if(a.size() < 2)
	continue;
          
      StartX=a.Start().X();
      StartY=a.Start().Y();
      StartZ=a.Start().Z();
      EndX=a.End().X();
      EndY=a.End().Y();
      EndZ=a.End().Z();
      tracklength=sqrt(pow((EndX-StartX),2)+pow((EndY-StartY),2)+pow((EndZ-StartZ),2));
          
          
          
      StartX_det=a.at(0).X();
      StartY_det=a.at(0).Y();
      StartZ_det=a.at(0).Z();
      EndX_det=a.at(a.size()-1).X();
      EndY_det=a.at(a.size()-1).Y();
      EndZ_det=a.at(a.size()-1).Z();
      
          
          
      mypdg= a.PdgCode();
      //   cout<<"Start Y is: "<<StartY<<endl;
      //   cout<<"End Y is: "<<EndY<<endl;
         
     
      //MATCH VARIABLES
        
        

          
          
      if (mypdg==13 || mypdg==-13){
              
              
	muontrackcount++;
              
	muonStartX=a.Start().X();
	muonStartY=a.Start().Y();
	muonStartZ=a.Start().Z();
	muonEndX=a.End().X();
	muonEndY=a.End().Y();
	muonEndZ=a.End().Z();
	muontracklength=sqrt(pow((muonEndX-muonStartX),2)+pow((muonEndY-muonStartY),2)+pow((muonEndZ-muonStartZ),2));
          
	muonStartX_det=a.at(0).X();
	muonStartY_det=a.at(0).Y();
	muonStartZ_det=a.at(0).Z();
	muonEndX_det=a.at(a.size()-1).X();
	muonEndY_det=a.at(a.size()-1).Y();
	muonEndZ_det=a.at(a.size()-1).Z();
	muontracklength_det=sqrt(pow((muonEndX_det-muonStartX_det),2)+pow((muonEndY_det-muonStartY_det),2)+pow((muonEndZ_det-muonStartZ_det),2));

              
	x2[counter]=counter;
	y2[counter]=muontrackcount;
              
              
	
          
	Int_t recotrackcount=0;
	Int_t recotrackcount_smallest=0;
          

          
	for (auto const& b : recotrack_vec){
    
        
	  StartX_reco=b.Vertex().X();
	  StartY_reco=b.Vertex().Y();
	  StartZ_reco=b.Vertex().Z();
	  EndX_reco=b.End().X();
	  EndY_reco=b.End().Y();;
	  EndZ_reco=b.End().Z();;
	  tracklength_reco=sqrt(pow((EndX_reco-StartX_reco),2)+pow((EndY_reco-StartY_reco),2)+pow((EndZ_reco-StartZ_reco),2));
                  
      
                  
      dotprod=abs(((muonEndX_det-muonStartX_det)*(EndX_reco-StartX_reco))+((muonEndY_det-muonStartY_det)*(EndY_reco-StartY_reco))+((muonEndZ_det-muonStartZ_det)*(EndZ_reco-StartZ_reco)));
                  
	  costheta=((dotprod)/(muontracklength_det*tracklength_reco));
                 
                  
	  angle = acos(costheta);
        
  
        
      angle_smallest=angle;
 
      tracklength_reco_smallest=tracklength_reco;
      dotprod_smallest=dotprod;
      StartX_reco_smallest=StartX_reco;
      StartY_reco_smallest=StartY_reco;
      StartZ_reco_smallest=StartZ_reco;
      EndX_reco_smallest=EndX_reco;
      EndY_reco_smallest=EndY_reco;
      EndZ_reco_smallest=EndZ_reco;
      costheta_smallest=costheta;
      tracklength_diff=tracklength_reco_smallest-muontracklength_det;
      tracklength_ratio=tracklength_reco_smallest/muontracklength_det;

     
    if(tracklength_reco < 11.0 )
        continue;
    else
        break;
        
    }

	for (auto const& b : recotrack_vec){
                  
              
	  recotrackcount++;
	  StartX_reco=b.Vertex().X();
	  StartY_reco=b.Vertex().Y();
	  StartZ_reco=b.Vertex().Z();
	  EndX_reco=b.End().X();
	  EndY_reco=b.End().Y();;
	  EndZ_reco=b.End().Z();;
	  tracklength_reco=sqrt(pow((EndX_reco-StartX_reco),2)+pow((EndY_reco-StartY_reco),2)+pow((EndZ_reco-StartZ_reco),2));
	 
        if(tracklength_reco < 11.0)
        continue;
        
        RecoTracktree->Fill();
        
    

                  
	  
                  
                  
  
	  cout<<"muontrackcount: "<<muontrackcount<<endl;
	  cout<<"recotrackcount: "<<recotrackcount<<endl;
                  
  
	  dotprod=abs(((muonEndX_det-muonStartX_det)*(EndX_reco-StartX_reco))+((muonEndY_det-muonStartY_det)*(EndY_reco-StartY_reco))+((muonEndZ_det-muonStartZ_det)*(EndZ_reco-StartZ_reco)));
                  
	  costheta=((dotprod)/(muontracklength_det*tracklength_reco));
                  
                  
	  angle = acos(costheta);
	  



        
                  
	  cout<<"Angle: "<<angle<<endl;
                  
                  
	  if(angle <= angle_smallest){
          
                  
	    angle_smallest=angle;
        
	    
	    cout<<"Test Recotrackcount: "<<recotrackcount<<endl;
	    cout<<"Test dotprod: "<<dotprod<<endl;
	    recotrackcount_smallest = recotrackcount;
	    tracklength_reco_smallest=tracklength_reco;
	    dotprod_smallest=dotprod;
	    StartX_reco_smallest=StartX_reco;
	    StartY_reco_smallest=StartY_reco;
	    StartZ_reco_smallest=StartZ_reco;
	    EndX_reco_smallest=EndX_reco;
	    EndY_reco_smallest=EndY_reco;
	    EndZ_reco_smallest=EndZ_reco;
	    costheta_smallest=costheta;
	    tracklength_diff=tracklength_reco_smallest-muontracklength_det;
	    tracklength_ratio=tracklength_reco_smallest/muontracklength_det;
          
                  
      
	  }
        
	}//end of real reco for loop
 
	cout<<"******Best Match for muontrack number: "<<muontrackcount<<" is reco track number: "<<recotrackcount_smallest<<endl;
	cout<<"Best Match Angle in radians: "<<angle_smallest<<endl;
	cout<<"Best Match muon track length: "<<muontracklength_det<<endl;
	cout<<"Best Match reco track length: "<<tracklength_reco_smallest<<endl;
	cout<<"Best muon-reco track dot product magnitude: "<<dotprod_smallest<<endl;
          
	MCTracktree->Fill();
     
      }//end of if mc loop
          
      
          
      
    }//end of mc for loop
      
      
  } //end loop over events!
  cout<<"Total Events: "<<counter<<endl;

  f_output.Write();
  f_output.Close();
    
}

