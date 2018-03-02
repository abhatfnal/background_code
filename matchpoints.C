
/*************************************************************
 *
 * demo_ReadEvent program
 *
 * This is a simple demonstration of reading a LArSoft file
 * and printing out the run and event numbers. You can also
 * put the event numbers into a histogram!
 *
 * Original Author: Wesley Ketchum (wketchum@fnal.gov), Aug28, 2016
 * Eidted by : Avinay Bhat (abhat@fnal.gov), Feb 26, 2018
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
#include "TH2D.h"
#include "TH1D.h"
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




void matchpoints(){
    
    gStyle->SetOptStat(0);
    
    TFile f_output("Gallery_output_points.root","RECREATE");
    
    
    
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
    
    Double_t muonY_det;
    Double_t muonZ_det;
    
    Double_t muontracklength;
    Double_t muontracklength_det;
    
    
    
    //RECO VARIABLES////
    
    
    
    Double_t StartX_reco;
    Double_t StartY_reco;
    Double_t StartZ_reco;
    Double_t EndX_reco;
    Double_t EndY_reco;
    Double_t EndZ_reco;
    
    Double_t Y_reco;
    Double_t Z_reco;
    
    
    Double_t tracklength_reco;
    
    Double_t dotprod=0;
    Double_t costheta;
    Double_t angle=0;
    Double_t angle_smallest=0;
    
    
    //ANGLE match
    
    
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
    
    
    //POINT match
    
    Double_t pointdistance=0;
    Double_t pointdistance_smallest;
    Int_t muonpoint_smallest;
    Int_t muonpoint=0;
    Int_t muonpoint_count=0;
    Int_t recopoint_count=0;
    Double_t fom;
    Int_t recopoint;
    Int_t recopoint_smallest;
    Double_t fom_smallest;
    
    
    Double_t XZangle;
    Double_t XZangle_smallest=0;
    Double_t Yangle;
    Double_t Yangle_smallest=0;
    
    //MC Tree
    TTree* PointTracktree = new TTree("PointTracktree","PointTracktree");
    
    //Reco Tree
    
    
    TTree* FOMtree = new TTree("FOMtree","FOMtree");
    
    
    //MC Tree Branches
    /*
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
     
     */
    
    PointTracktree->Branch("muonStartX_det",&muonStartX_det,"muonStartX_det/D");
    PointTracktree->Branch("muonStartY_det",&muonStartY_det,"muonStartY_det/D");
    PointTracktree->Branch("muonStartZ_det",&muonStartZ_det,"muonStartZ_det/D");
    PointTracktree->Branch("muonEndX_det",&muonEndX_det,"muonEndX_det/D");
    PointTracktree->Branch("muonEndY_det",&muonEndY_det,"muonEndY_det/D");
    PointTracktree->Branch("muonEndZ_det",&muonEndZ_det,"muonEndZ_det/D");
    PointTracktree->Branch("XZangle",&XZangle,"XZangle/D");
    PointTracktree->Branch("Yangle",&Yangle,"Yangle/D");
    // PointTracktree->Branch("tracklength",&tracklength,"tracklength/D");
    //  PointTracktree->Branch("muontracklength",&muontracklength,"muontracklength/D");
    PointTracktree->Branch("muontracklength_det",&muontracklength_det,"muontracklength_det/D");
    
    PointTracktree->Branch("StartX_reco_smallest",&StartX_reco_smallest,"StartX_reco_smallest/D");
    PointTracktree->Branch("StartY_reco_smallest",&StartY_reco_smallest,"StartY_reco_smallest/D");
    PointTracktree->Branch("StartZ_reco_smallest",&StartZ_reco_smallest,"StartZ_reco_smallest/D");
    PointTracktree->Branch("EndX_reco_smallest",&EndX_reco_smallest,"EndX_reco_smallest/D");
    PointTracktree->Branch("EndY_reco_smallest",&EndY_reco_smallest,"EndY_reco_smallest/D");
    PointTracktree->Branch("EndZ_reco_smallest",&EndZ_reco_smallest,"EndZ_reco_smallest/D");
    PointTracktree->Branch("tracklength_reco_smallest",&tracklength_reco_smallest,"tracklength_reco_smallest/D");
    
    
    
    //  PointTracktree->Branch("muonpoint_count",&muonpoint_count,"muonpoint_count/D");
    //  PointTracktree->Branch("muonpoint_smallest",&muonpoint_smallest,"muonpoint_smallest/D");
    //  PointTracktree->Branch("recopoint_count",&recopoint_count,"recopoint_count/D");
    //  PointTracktree->Branch("recopoint_smallest",&recopoint_smallest,"recopoint_smallest/D");
    PointTracktree->Branch("pointdistance",&pointdistance,"pointdistance/D");
    PointTracktree->Branch("pointdistance_smallest",&pointdistance_smallest,"pointdistance_smallest/D");
    
    PointTracktree->Branch("fom_smallest",&fom_smallest,"fom_smallest/D");
    
    PointTracktree->Branch("tracklength_diff",&tracklength_diff,"tracklength_diff/D");
    PointTracktree->Branch("tracklength_ratio",&tracklength_ratio,"tracklength_ratio/D");
    FOMtree->Branch("fom",&fom,"fom/D");
    //  FOMtree->Branch("fom",&mypdg,"mypdg/D");
    //Reco Tree Branches
    
    /*
     
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
     
     */
    //We specify our files in a list of file names!
    //Note: multiple files allowed. Just separate by comma.
    //  vector<string> filenames { "MyInputFile_1.root" };
    //   vector<string> filenames { "/pnfs/uboone/mc/uboone/reconstructed/prod_v06_26_06/prodcosmics_corsika_cmc_uboone_intime_reco/reco/prodcosmics_corsika_cmc_uboone_intime_9_20180106T234834_gen2_b68094ab-d48a-42de-84f1-274a79047091_20180125T160523_reco1_20180125T163723_reco2.root","/pnfs/uboone/mc/uboone/reconstructed/prod_v06_26_06/prodcosmics_corsika_cmc_uboone_intime_reco/reco/prodcosmics_corsika_cmc_uboone_intime_0_20171228T135151_gen2_ad665c20-75db-467b-80fc-d945e794f389_20180111T075909_reco1_20180111T082044_reco2.root" };
    
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
        
        //    cout << "\tThere are " <<mctrack_vec.size()<< " MC tracks in this event." << endl;
        
        // h_MCTrack_length->Fill(mctrack_vec.size());
        
        //     cout << "\tThere are " <<recotrack_vec.size()<< " Reco tracks in this event." << endl;
        
        
        x1[counter]=counter;
        y1[counter]=mctrack_vec.size();
        
        
        Int_t muontrackcount=0;
        Int_t muontrackcount_smallest=0;
        Double_t totalpointdistance;
        //  muonpointcount=0;
        
        for (auto const& a : mctrack_vec){   //START OF MC TRACK FOR LOOP
            if(a.size() < 2)
                continue;
            
            mypdg= a.PdgCode();
            
            if (mypdg==13 || mypdg==-13){     //START OF MUON IF LOOP
                muontrackcount++;
                //  fom_smallest=0;
                fom_smallest=1e10;
                muonStartX_det=a.at(0).X();
                muonStartY_det=a.at(0).Y();
                muonStartZ_det=a.at(0).Z();
                muonEndX_det=a.at(a.size()-1).X();
                muonEndY_det=a.at(a.size()-1).Y();
                muonEndZ_det=a.at(a.size()-1).Z();
                muontracklength_det=sqrt(pow((muonEndX_det-muonStartX_det),2)+pow((muonEndY_det-muonStartY_det),2)+pow((muonEndZ_det-muonStartZ_det),2));
                XZangle=((muonEndX_det-muonStartX_det)/(muonEndZ_det-muonStartZ_det));
                Yangle=(sqrt(pow((muonEndZ_det-muonStartZ_det),2)+pow((muonEndX_det-muonStartX_det),2))/(muonEndY_det-muonStartY_det));
                //     cout<<"Muon track number: "<<muontrackcount<<endl;
                //   cout<<"XZangle: "<<XZangle<<endl;
                //   cout<<"Yangle: "<<Yangle<<endl;
                
                Int_t recotrackcount=0;
                Int_t recotrackcount_smallest=0;
                size_t p=0;
                for (auto const& b : recotrack_vec){ //START OF RECO TRACK FOR LOOP
                    
                    recotrackcount++;
                    
                    StartX_reco=b.Vertex().X();
                    StartY_reco=b.Vertex().Y();
                    StartZ_reco=b.Vertex().Z();
                    EndX_reco=b.End().X();
                    EndY_reco=b.End().Y();
                    EndZ_reco=b.End().Z();
                    tracklength_reco=sqrt(pow((EndX_reco-StartX_reco),2)+pow((EndY_reco-StartY_reco),2)+pow((EndZ_reco-StartZ_reco),2));
                    
                    
                    Double_t mcFront = muonStartZ_det;
                    Double_t mcBack = muonEndZ_det;
                    Double_t rcFront = StartZ_reco;
                    Double_t rcBack = EndZ_reco;
                    if (mcFront > mcBack) {
                        mcFront = muonEndZ_det;
                        mcBack = muonStartZ_det;
                    }
                    
                    
                    if (rcFront > rcBack) {
                        rcFront = EndZ_reco;
                        rcBack = StartZ_reco;
                    }
                    
                    if (rcBack < mcFront || rcFront > mcBack)
                        
                        continue;
                    
                    if(tracklength_reco < 11.0 )
                        continue;
                    
                    
                    //    cout<<"Reco Track Number: "<<recotrackcount<<endl;
                    p=b.NumberTrajectoryPoints();
                    //   cout<<"There are: "<<p<<" recopoints in this reco track"<<endl;
                    
                    recopoint_smallest=0;
                    
                    totalpointdistance=0;
                    for(size_t m=0;m<(b.NumberTrajectoryPoints());m++){//START RECO POINT LOOP
                        recopoint++;
                        pointdistance_smallest=1e10;
                        Y_reco=b.LocationAtPoint(m).Y();
                        Z_reco=b.LocationAtPoint(m).Z();
                        
                        
                        for(size_t n=0;n<(a.size());n++){   //START OF  MUON POINT FOR LOOP
                            muonY_det=a.at(n).Y();
                            muonZ_det=a.at(n).Z();
                            
                            pointdistance=sqrt(pow((Y_reco-muonY_det),2)+pow((Z_reco-muonZ_det),2));
                            //    cout<<"Point distance: "<<pointdistance<<endl;
                            if(pointdistance<pointdistance_smallest){
                                
                                pointdistance_smallest=pointdistance;
                                
                                
                                //      cout<<"Pointdistance_smallest: "<<pointdistance_smallest<<endl;
                            }
                            
                            //    totalpointdistance+=pointdistance_smallest;
                            
                            
                            //   cout<<"FOM: "<<fom<<endl;
                        }//END MUON POINT FOR LOOP
                        
                        //   cout<<"Reco Point Number: "<<recopoint<<endl;
                        
                        totalpointdistance+=pointdistance_smallest;
                    }//END RECO POINT LOOP
                    
                    
                    fom=totalpointdistance/p;
                    
                    if(fom<fom_smallest){
                        recotrackcount_smallest=recotrackcount;
                        fom_smallest=fom;
                        tracklength_reco_smallest=tracklength_reco;
                        StartX_reco_smallest=StartX_reco;
                        StartY_reco_smallest=StartY_reco;
                        StartZ_reco_smallest=StartZ_reco;
                        EndX_reco_smallest=EndX_reco;
                        EndY_reco_smallest=EndY_reco;
                        EndZ_reco_smallest=EndZ_reco;
                        tracklength_diff=tracklength_reco_smallest-muontracklength_det;
                        tracklength_ratio=tracklength_reco_smallest/muontracklength_det;
                        //    cout<<"FOM SMALLEST: "<<fom_smallest<<endl;
                        
                    }
                    FOMtree->Fill();
                    
                    
                }//END OF RECO TRACK FOR LOOP
                
                //    cout<<"******Best Match for muontrack number: "<<muontrackcount<<" is reco track number: "<<recotrackcount_smallest<<" with FOM SMALLEST:  "<<fom_smallest<<"*********"<<endl;
                
                
                PointTracktree->Fill();
                
            }//END MUON IF LOOP
            
            
            //  FOMtree->Fill();
        }//END MC TRACK FOR LOOP
        
        
        
    } //end loop over events!
    cout<<"Total Events: "<<counter<<endl;
    
    f_output.Write();
    f_output.Close();
    
}

