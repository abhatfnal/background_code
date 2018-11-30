////////////////////////////////////////////////////////////////////////
// Class:       RecoEfficiency
// Plugin Type: analyzer (art v2_05_01)
// File:        RecoEfficiency_module.cc
//
// Generated at Tue Nov 13 10:31:21 2018 by Avinay Bhat using cetskelgen
// from cetlib version v1_21_00.
////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "canvas/Persistency/Common/FindMany.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "art/Persistency/Common/PtrMaker.h"
#include "canvas/Persistency/Common/FindOne.h"
//#include "canvas/Persistency/Common/Assns.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include <memory>
#include <map>
// Services
#include "art/Framework/Services/Optional/TFileService.h"
#include "larcore/Geometry/Geometry.h"
//#include "larcore/Geometry/GeometryCore.h"
#include "lardata/Utilities/GeometryUtilities.h"
#include "lardata/DetectorInfoServices/DetectorPropertiesService.h"
#include "lardataobj/MCBase/MCTrack.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardata/Utilities/AssociationUtil.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/AnalysisBase/BackTrackerMatchingData.h"
#include "lardataobj/AnalysisBase/Calorimetry.h"
#include "nusimdata/SimulationBase/MCParticle.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/MCFlux.h"
#include "lardataobj/RecoBase/Vertex.h"



// ROOT
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


class RecoEfficiency;


class RecoEfficiency : public art::EDAnalyzer {
public:
    explicit RecoEfficiency(fhicl::ParameterSet const & p);
    // The compiler-generated destructor is fine for non-base
    // classes without bare pointers or other resource use.
    
    // Plugins should not be copied or assigned.
    RecoEfficiency(RecoEfficiency const &) = delete;
    RecoEfficiency(RecoEfficiency &&) = delete;
    RecoEfficiency & operator = (RecoEfficiency const &) = delete;
    RecoEfficiency & operator = (RecoEfficiency &&) = delete;
    
    // Required functions.
    void analyze(art::Event const & e) override;
    
    // Selected optional functions.
    void beginJob() override;
    void endJob() override;
    
private:
    
    // Declare member data here.
    
    Int_t fEvent;
    
    std::string fMC_track_tag,fReco_track_tag,fHit_tag,fMatch_tag;
    
    
    
    Double_t MC_Track_StartX_det=0.0;
    Double_t MC_Track_StartY_det=0.0;
    Double_t MC_Track_StartZ_det=0.0;
    Double_t MC_Track_EndX_det=0.0;
    Double_t MC_Track_EndY_det=0.0;
    Double_t MC_Track_EndZ_det=0.0;
    Double_t MC_Track_Length=0.0;
    Double_t XZangle=0.0;
    Double_t Yangle=0.0;
    
    
    
    Double_t Reco_Track_StartX=0.0;
    Double_t Reco_Track_StartY=0.0;
    Double_t Reco_Track_StartZ=0.0;
    Double_t Reco_Track_EndX=0.0;
    Double_t Reco_Track_EndY=0.0;
    Double_t Reco_Track_EndZ=0.0;
    Double_t Reco_Track_Length=0.0;
    
    Double_t Reco_Track_StartX_match=0.0;
    Double_t Reco_Track_StartY_match=0.0;
    Double_t Reco_Track_StartZ_match=0.0;
    Double_t Reco_Track_EndX_match=0.0;
    Double_t Reco_Track_EndY_match=0.0;
    Double_t Reco_Track_EndZ_match=0.0;
    Double_t Reco_Track_Length_match=0.0;
    
    
    
    art::ServiceHandle<art::TFileService> tfs;
    
    TTree *Tracktree = new TTree("Tracktree","Tracktree");
    TTree *Matchtree = new TTree("Matchtree","Matchtree");
};





RecoEfficiency::RecoEfficiency(fhicl::ParameterSet const & p)
: EDAnalyzer(p)  // ,
// More initializers here.
{
    
    
    fMC_track_tag   = p.get<std::string>("mctrack_tag");
    fReco_track_tag = p.get<std::string>("recotrack_tag");
    fHit_tag = p.get<std::string>("hit_tag");
    fMatch_tag = p.get<std::string>("match_tag");
    
    
}

void RecoEfficiency::analyze(art::Event const & e)
{
    fEvent= e.id().event();
    // Implementation of required member function here.
    art::Handle<std::vector<sim::MCTrack> > mctrack_handle;
    e.getByLabel(fMC_track_tag,mctrack_handle);
    if (!mctrack_handle.isValid()) return;
    
    art::Handle<std::vector<recob::Track> > recotrack_handle;
    e.getByLabel(fReco_track_tag,recotrack_handle);
    
    art::Handle<std::vector<recob::Hit> > hit_handle;
    e.getByLabel(fHit_tag,hit_handle);
    
    art::FindManyP<recob::Hit> track_hit_assn_v(recotrack_handle, e, fReco_track_tag);
    
    art::FindMany<simb::MCParticle,anab::BackTrackerHitMatchingData> backtrack_handle(hit_handle,e,fMatch_tag);
    
    cout <<"Event: "<<fEvent<<endl;
    
    //   LoadVertex(e.run(),e.event());
    
    auto const& mctrack_vec(*mctrack_handle);
    
    auto const& recotrack_vec(*recotrack_handle);
    
    Int_t mctrackcounter=0;
    
    
    for (size_t i_c = 0; i_c < mctrack_vec.size(); ++i_c) { //START MCTRACK FOR LOOP
        
        auto pdg=mctrack_vec[i_c].PdgCode();

      if (mctrack_vec.size() <2 || abs(pdg)!=13)
          continue;

        mctrackcounter++;
        auto mctrackid=mctrack_vec[i_c].TrackID();
        
        
        //     cout<<"MCTrack Counter: "<<mctrackcounter<<endl;
        //   cout<<"MC TRACK ID: "<<mctrackid<<endl;
   /*
        MC_Track_StartX_det=mctrack_vec[i_c].at(0).X();
        MC_Track_StartY_det=mctrack_vec[i_c].at(0).Y();
        MC_Track_StartZ_det=mctrack_vec[i_c].at(0).Z();
        
        MC_Track_EndX_det=mctrack_vec[i_c].at(mctrack_vec.size()-1).X();
        MC_Track_EndY_det=mctrack_vec[i_c].at(mctrack_vec.size()-1).Y();
        MC_Track_EndZ_det=mctrack_vec[i_c].at(mctrack_vec.size()-1).Z();
   */
        MC_Track_Length=sqrt(pow((MC_Track_EndX_det-MC_Track_StartX_det),2)+pow((MC_Track_EndY_det-MC_Track_StartY_det),2)+pow((MC_Track_EndZ_det-MC_Track_StartZ_det),2));
        
        XZangle=((MC_Track_EndX_det-MC_Track_StartX_det)/(MC_Track_EndZ_det-MC_Track_StartZ_det));
        
        Yangle=(sqrt(pow((MC_Track_EndZ_det-MC_Track_StartZ_det),2)+pow((MC_Track_EndX_det-MC_Track_StartX_det),2))/(MC_Track_EndY_det-MC_Track_StartY_det));
        
        Double_t ratio_largest=0.0;
        Int_t recotrackcounter=0;
        Int_t recotrackcounter_largestratio=0;
        if (recotrack_handle->size()==0)
        {cout<<"*************ZERO RECO TRACKS FOUND"<<endl;}
        for (size_t i_t = 0; i_t < recotrack_vec.size(); ++i_t) {//START RECOTRACK FOR LOOP
            recotrackcounter++;
            //cout<<"RecoTrack Counter: "<<recotrackcounter<<endl;
            
            Reco_Track_StartX= recotrack_vec[i_t].Vertex().X();
            
             Reco_Track_StartY= recotrack_vec[i_t].Vertex().Y();
             Reco_Track_StartZ= recotrack_vec[i_t].Vertex().Z();
             
             Reco_Track_EndX=recotrack_vec[i_t].End().X();
             Reco_Track_EndY=recotrack_vec[i_t].End().Y();
             Reco_Track_EndZ=recotrack_vec[i_t].End().Z();
             
             Reco_Track_Length=sqrt(pow((Reco_Track_EndX-Reco_Track_StartX),2)+pow((Reco_Track_EndY-Reco_Track_StartY),2)+pow((Reco_Track_EndZ-Reco_Track_StartZ),2));
             
            
            const std::vector<art::Ptr<recob::Hit> > hit_v = track_hit_assn_v.at(i_t);
            
            Double_t hitcounter=0.0;
            Double_t backtrackedhitcounter=0.0;
            Double_t ratio=0.0;
            for (art::Ptr<recob::Hit> hit : hit_v){//START HIT FOR LOOP
                
                hitcounter++;
                
                auto hitidx = hit.key();
                
                std::vector<simb::MCParticle const*> particle_vec;
                std::vector<anab::BackTrackerHitMatchingData const*> match_vec;
                backtrack_handle.get(hitidx, particle_vec, match_vec);
                
                
                
                for(size_t i_p=0; i_p<particle_vec.size(); ++i_p){//START MC PARTICLE FOR LOOP
                    
                    auto pdg_particle=particle_vec.at(i_p)->PdgCode();
                    
                    auto mcparticleid = particle_vec.at(i_p)->TrackId();
                    
                    if (abs(pdg_particle)!=13 || (int)mcparticleid!=(int)mctrackid || match_vec[i_p]->isMaxIDE!=1  )
                        continue;
                    
                    //          cout<<"PARTICLE ID: "<<mcparticleid<<endl;
                    //          cout<<"MC TRACK ID: "<<mctrackid<<endl;
                    
                    backtrackedhitcounter++;
                    
                    
                }//END MC PARTICLE FOR LOOP
            }//END HIT FOR LOOP
            //   cout<<"hitcounter: "<<hitcounter<<endl;
            //   cout<<"backtrackedhitcounter: "<<backtrackedhitcounter<<endl;
            ratio=backtrackedhitcounter/hitcounter;
            if (ratio>ratio_largest){
                recotrackcounter_largestratio=recotrackcounter;
                ratio_largest=ratio;
                /*
                 Reco_Track_StartX_match=Reco_Track_StartX;
                 Reco_Track_StartY_match=Reco_Track_StartY;
                 Reco_Track_StartZ_match=Reco_Track_StartZ;
                 Reco_Track_EndX_match=Reco_Track_EndX;
                 Reco_Track_EndY_match=Reco_Track_EndY;
                 Reco_Track_EndZ_match=Reco_Track_EndZ;
                 Reco_Track_Length_match=Reco_Track_Length;
                 */
                cout<<"**********************************ratio: "<<ratio<<endl;
            }
            
            //         Matchtree->Fill();
            
        }//END RECO TRACK FOR LOOP
        if (ratio_largest==0){
            cout<<"MC TRACK # "<<mctrackcounter<<" DOES NOT have a RECO TRACK match."<<endl;
        }
        else {cout<<"MC TRACK # "<<mctrackcounter<<" matches RECO TRACK # "<<recotrackcounter_largestratio<<" with RATIO: "<<ratio_largest<<endl;}
        /*
         
         for (auto const& hit : hits) {//START CLUSTER HIT LOOP
         charge = hit->Integral();
         cluster_charge += charge;
         cluster_energy += charge* 0.009558;
         
         }//END CLUSTER HIT LOOP
         
         
         */
        //     Tracktree->Fill();

    }//END MCTRACK FOR LOOP
    
    
}


void RecoEfficiency::beginJob()
{ // get detector specific properties
    
    /*
     auto const* geom = ::lar::providerFrom<geo::Geometry>();
     auto const* detp = lar::providerFrom<detinfo::DetectorPropertiesService>();
     wire2cm = geom->WirePitch(0,1,0);
     time2cm = detp->SamplingRate() / 1000.0 * detp->DriftVelocity( detp->Efield(), detp->Temperature() );
     
     
     
     art::ServiceHandle<art::TFileService> tfs;
     
     
     Matchtree->Branch("Z_reco",&Z_reco,"Z_reco/D");
     Matchtree->Branch("X_reco",&X_reco,"X_reco/D");
     //   Matchtree->Branch("pointdistance_smallest",&pointdistance_smallest,"pointdistance_smallest/D");
     Matchtree->Branch("distance_smallest",&distance_smallest,"distance_smallest/D");
     */
    art::ServiceHandle<art::TFileService> tfs;
    Tracktree->Branch("MC_Track_StartX_det",&MC_Track_StartX_det,"MC_Track_StartX_det/D");
    Tracktree->Branch("MC_Track_StartY_det",&MC_Track_StartY_det,"MC_Track_StartY_det/D");
    Tracktree->Branch("MC_Track_StartZ_det",&MC_Track_StartZ_det,"MC_Track_StartZ_det/D");
    Tracktree->Branch("MC_Track_EndX_det",&MC_Track_EndX_det,"MC_Track_EndX_det/D");
    Tracktree->Branch("MC_Track_EndY_det",&MC_Track_EndY_det,"MC_Track_EndY_det/D");
    Tracktree->Branch("MC_Track_EndZ_det",&MC_Track_EndZ_det,"MC_Track_EndZ_det/D");
    Tracktree->Branch("XZangle",&XZangle,"XZangle/D");
    Tracktree->Branch("Yangle",&Yangle,"Yangle/D");
    Tracktree->Branch("Reco_Track_StartX",&Reco_Track_StartX,"Reco_Track_StartX/D");
    Tracktree->Branch("Reco_Track_StartY",&Reco_Track_StartY,"Reco_Track_StartY/D");
    Tracktree->Branch("Reco_Track_StartZ",&Reco_Track_StartZ,"Reco_Track_StartZ/D");
    Tracktree->Branch("Reco_Track_EndX",&Reco_Track_EndX,"Reco_Track_EndX/D");
    Tracktree->Branch("Reco_Track_EndY",&Reco_Track_EndY,"Reco_Track_EndY/D");
    Tracktree->Branch("Reco_Track_EndZ",&Reco_Track_EndZ,"Reco_Track_EndZ/D");
    
    
    Matchtree->Branch("Reco_Track_StartX_match",&Reco_Track_StartX_match,"Reco_Track_StartX_match/D");
    Matchtree->Branch("Reco_Track_StartY_match",&Reco_Track_StartY_match,"Reco_Track_StartY_match/D");
    Matchtree->Branch("Reco_Track_StartZ_match",&Reco_Track_StartZ_match,"Reco_Track_StartZ_match/D");
    Matchtree->Branch("Reco_Track_EndX_match",&Reco_Track_EndX_match,"Reco_Track_EndX_match/D");
    Matchtree->Branch("Reco_Track_EndY_match",&Reco_Track_EndY_match,"Reco_Track_EndY_match/D");
    Matchtree->Branch("Reco_Track_EndZ_match",&Reco_Track_EndZ_match,"Reco_Track_EndZ_match/D");
    
    
}

void RecoEfficiency::endJob()
{
    // Implementation of optional member function here.
}









DEFINE_ART_MODULE(RecoEfficiency)
