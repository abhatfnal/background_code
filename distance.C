//
//  distance.C
//
//
//  Created by Avinay Bhat on 3/13/18.
//
//

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
#include "TStopwatch.h"


//"art" includes (canvas, and gallery)
#include "canvas/Utilities/InputTag.h"
#include "gallery/Event.h"
#include "gallery/ValidHandle.h"
#include "canvas/Persistency/Common/FindMany.h"
#include "canvas/Persistency/Common/FindOne.h"
#include "lardataobj/MCBase/MCTrack.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/RecoBase/Cluster.h"
//#include "lardata/Utilities/GeometryUtilities.h"

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




void distance(){
    
    gStyle->SetOptStat(0);
    
    TFile f_output("/uboone/data/users/abhat/background/GammaCatcher/Gallery_distance_cluster.root","RECREATE");
    
    // VARIABLES
    
    Int_t ClusterStartWire=0;
    Int_t ClusterEndWire=0;
    Double_t ClusterStartTick=0;
    Double_t ClusterEndTick=0;
    
    Double_t X_reco=0.0;
    Double_t Y_reco=0.0;
    Double_t Z_reco=0.0;
    
    Double_t Wire_cluster=0.0;
    Double_t Tick_cluster=0.0;
    
    Double_t Wire_reco=0;
    Double_t Tick_reco=0.0;
    
    Double_t pointdistance=0.0;
    
    
    Double_t pointdistance_smallest;
    
    Double_t distance=0.0;
    Double_t distance_smallest;
    Double_t charge;
    Double_t charge1;
    Double_t cluster_charge;
    Double_t cluster_energy;
    
    //Trees
    
    
    TTree* Clustertree = new TTree("Clustertree","Clustertree");
    
    //Branches
    
    
    Clustertree->Branch("Wire_cluster",&Wire_cluster,"Wire_cluster/D");
    Clustertree->Branch("Tick_cluster",&Tick_cluster,"Tick_cluster/D");
    Clustertree->Branch("Wire_reco",&Wire_reco,"Wire_reco/D");
    Clustertree->Branch("Tick_reco",&Tick_reco,"Tick_reco/D");
    //   Clustertree->Branch("pointdistance_smallest",&pointdistance_smallest,"pointdistance_smallest/D");
    Clustertree->Branch("distance_smallest",&distance_smallest,"distance_smallest/D");
    Clustertree->Branch("cluster_charge",&cluster_charge,"cluster_charge/D");
    Clustertree->Branch("cluster_energy",&cluster_energy,"cluster_energy/D");
    Clustertree->Branch("charge",&charge,"charge/D");
    
    //INPUT FILES TO READ
    
    //   vector<string> filenames { "/pnfs/uboone/mc/uboone/reconstructed/prod_v06_26_06/prodcosmics_corsika_cmc_uboone_intime_reco/reco/prodcosmics_corsika_cmc_uboone_intime_9_20180106T234834_gen2_b68094ab-d48a-42de-84f1-274a79047091_20180125T160523_reco1_20180125T163723_reco2.root","/pnfs/uboone/mc/uboone/reconstructed/prod_v06_26_06/prodcosmics_corsika_cmc_uboone_intime_reco/reco/prodcosmics_corsika_cmc_uboone_intime_0_20171228T135151_gen2_ad665c20-75db-467b-80fc-d945e794f389_20180111T075909_reco1_20180111T082044_reco2.root" };
    
    vector<string> filenames { "/uboone/data/users/abhat/background/GammaCatcher/clusters.root" };
    
    //  vector<string> filenames;
    //  ifstream myfile("/uboone/app/users/abhat/background/file_list.txt");
    //  copy(istream_iterator<string>(myfile),istream_iterator<string>(),back_inserter(filenames));
    
    
    //INPUT TAGS
    
    InputTag mctrack_tag{"mcreco"};
    InputTag recotrack_tag{"pandoraCosmic"};
    InputTag cluster_tag{"proximityclustering"};
    InputTag hit_tag{"gaushit"};
    
    
    
    TStopwatch timer;
    timer.Start();
    Int_t counter=0;
    for (gallery::Event ev(filenames) ; !ev.atEnd(); ev.next()) {//START EVENT FOR LOOP
        
        counter++;
        
        
	//        cout << "Processing "
	//   << "Run " << ev.eventAuxiliary().run() << ", "
	// << "Event " << ev.eventAuxiliary().event() << endl;
        
        
        auto const& mctrack_handle = ev.getValidHandle<vector<sim::MCTrack>>(mctrack_tag);
        auto const& mctrack_vec(*mctrack_handle);
        
        
        auto const& recotrack_handle = ev.getValidHandle<vector<recob::Track>>(recotrack_tag);
        auto const& recotrack_vec(*recotrack_handle);
        
        auto const& cluster_handle = ev.getValidHandle<vector<recob::Cluster>>(cluster_tag);
        auto const& cluster_vec(*cluster_handle);
        
        auto const& hit_handle = ev.getValidHandle<vector<recob::Hit>>(hit_tag);
        auto const& hit_vec(*cluster_handle);
        
        FindMany<recob::Hit> clus_hit_assn_v(cluster_handle,ev,cluster_tag);
        
	//     cout<<"There are "<<cluster_handle->size()<<" Clusters in this event"<<endl;
	//      cout<<"There are "<<recotrack_vec.size()<<" Reco Tracks in this event"<<endl;
        Int_t clustercounter=0;
        
        
        
        for (size_t i_c = 0, size_cluster = cluster_handle->size(); i_c != size_cluster; ++i_c) { //START CLUSTER FOR LOOP
            clustercounter++;
            cluster_charge=0.0;
            cluster_energy=0.0;
            //     cout<<"Cluster Counter: "<<clustercounter<<endl;
            
            auto hits = clus_hit_assn_v.at(i_c);
            
            Int_t trackcounter=0;
            Int_t trackcounter_smallest=0;
            distance_smallest=1e10;
            for (auto const& b : recotrack_vec){//START RECO TRACK FOR LOOP
                trackcounter++;
                //     cout<<"Track Counter: "<<trackcounter<<endl;
                for(size_t m=0;m<(b.NumberTrajectoryPoints());m++){//START RECO POINT LOOP
                    
                    pointdistance_smallest=1e10;
                    X_reco=b.LocationAtPoint(m).X();
                    Y_reco=b.LocationAtPoint(m).Y();
                    Z_reco=b.LocationAtPoint(m).Z();
                    
                    Wire_reco=Z_reco;
                    Tick_reco=X_reco+44.5744;
                    
                    for (auto const& hit : hits) {//START CLUSTER HIT LOOP
                       charge1 = hit->Integral();
                        if (charge1 <0.0001)
                            continue;
                        Wire_cluster = hit->WireID().Wire * 0.3;//What is this?
                        Tick_cluster = hit->PeakTime() * 0.0557179;//What is this?
                        pointdistance=sqrt((pow(Wire_cluster-Wire_reco,2))+(pow(Tick_cluster-Tick_reco,2)));
                        
                        if(pointdistance<pointdistance_smallest){
                            
                            pointdistance_smallest=pointdistance;
                            //    trackcounter_smallest=trackcounter;
                            
                            //    cout<<"Pointdistance_smallest: "<<pointdistance_smallest<<endl;
                        }
                        
                    }//END CLUSTER HIT LOOP
                    
                    distance=pointdistance_smallest;
                    
                    //   cout<<"Distance: "<<distance<<endl;
                }//END RECO POINT LOOP
                
                if(distance<distance_smallest){
                    distance_smallest=distance;
                    trackcounter_smallest=trackcounter;
                }
                
            }//END RECO TRACK FOR LOOP
            
            //  cout<<"Smallest Distance: "<<distance_smallest<<endl;
            //    cout<<"******Best Match for Cluster : "<<clustercounter<<" is reco track number: "<<trackcounter_smallest<<" with distance:  "<<distance_smallest<<"*********"<<endl;
            
            
            
            for (auto const& hit : hits) {//START CLUSTER HIT LOOP
                charge = hit->Integral();
                if (charge <0.0001)
                    continue;
                cluster_charge += charge;
                cluster_energy += charge* 0.009558;
                
            }//END CLUSTER HIT LOOP
            
            
            
            Clustertree->Fill();
        }//END CLUSTER FOR LOOP
        
        
        //    cout<<"Smallest Distance: "<<pointdistance_smallest<<endl;
        
        
        
        
        
        
    }//END EVENT FOR LOOP
    
    timer.Stop();
    cout << "\tThis root file with " <<counter<<" events took " << timer.RealTime() << "s to process." << endl;
    
    f_output.Write();
    f_output.Close();
    
}
