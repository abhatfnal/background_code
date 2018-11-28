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
    
    
    std::string fMC_track_tag,fReco_track_tag,fHit_tag,fMatch_tag;
    
    //  Int_t pdg;
    Double_t X_reco=0.0;
    
    
    art::ServiceHandle<art::TFileService> tfs;
    
    //   TTree *Matchtree = new TTree("Matchtree","Matchtree");
    
    
    
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
    
    // Implementation of required member function here.
    art::Handle<std::vector<sim::MCTrack> > mctrack_handle;
    e.getByLabel(fMC_track_tag,mctrack_handle);
    
    art::Handle<std::vector<recob::Track> > recotrack_handle;
    e.getByLabel(fReco_track_tag,recotrack_handle);
    
    art::Handle<std::vector<recob::Hit> > hit_handle;
    e.getByLabel(fHit_tag,hit_handle);
    
    art::FindManyP<recob::Hit> track_hit_assn_v(recotrack_handle, e, fReco_track_tag);
    
    art::FindMany<simb::MCParticle,anab::BackTrackerHitMatchingData> backtrack_handle(hit_handle,e,fMatch_tag);
    
    //   LoadVertex(e.run(),e.event());
    
    auto const& mctrack_vec(*mctrack_handle);
    
    
    Int_t mctrackcounter=0;
    
    
    
    for (size_t i_c = 0, size_mctrackvec = mctrack_handle->size(); i_c != size_mctrackvec; ++i_c) { //START MCTRACK FOR LOOP
        
        
        auto pdg=mctrack_vec[i_c].PdgCode();
        
        if (mctrack_handle->size() <0 || abs(pdg)!=13)
            continue;
        
        mctrackcounter++;
        
        
        cout<<"MCTrack Counter: "<<mctrackcounter<<endl;
        
        
        
        Int_t recotrackcounter=0;
        
        for (size_t i_t = 0, size_track = recotrack_handle->size(); i_t != size_track; ++i_t) {//START RECOTRACK FOR LOOP
            recotrackcounter++;
            cout<<"RecoTrack Counter: "<<recotrackcounter<<endl;
            
            //     auto hits = track_hit_assn_v.at(i_t);
            const std::vector<art::Ptr<recob::Hit> > hit_v = track_hit_assn_v.at(i_t);
            
            Int_t hitcounter=0;
            Int_t backtrackedhitcounter=0;
            Double_t ratio=0.0;
            for (art::Ptr<recob::Hit> hit : hit_v){
                
                hitcounter++;
            //    cout<<"hitcounter1: "<<hitcounter<<endl;
                auto hitidx = hit.key();
                
                std::vector<simb::MCParticle const*> particle_vec;
                std::vector<anab::BackTrackerHitMatchingData const*> match_vec;
                backtrack_handle.get(hitidx, particle_vec, match_vec);
                
                Int_t btmu=0;
                
                for(size_t i_p=0; i_p<particle_vec.size(); ++i_p){
                    
                    auto mctrkid = particle_vec.at(i_p)->TrackId();
                    
                //    cout<<"isMaxIDE: "<<match_vec[i_p]->isMaxIDE<<endl;
                    
                    if (match_vec[i_p]->isMaxIDE==1){
                        btmu=mctrkid;
                        backtrackedhitcounter++;
                        cout<<"btmu: "<<btmu<<endl;
                  //      cout<<"hitcounter2: "<<hitcounter<<endl;
                  //      cout<<"backtrackedhitcounter1: "<<backtrackedhitcounter<<endl;
                        
                    }
                    
                    //    cout<<"MCTRACK ID: "<<mctrkid<<endl;
               //     cout<<"hitcounter3: "<<hitcounter<<endl;
               //     cout<<"backtrackedhitcounter2: "<<backtrackedhitcounter<<endl;
                    
                }
              //  cout<<"hitcounter4: "<<hitcounter<<endl;
             //   cout<<"backtrackedhitcounter3: "<<backtrackedhitcounter<<endl;
            }
            cout<<"hitcounter: "<<hitcounter<<endl;
            cout<<"backtrackedhitcounter: "<<backtrackedhitcounter<<endl;
            ratio=backtrackedhitcounter/hitcounter;
            cout<<"ratio: "<<ratio<<endl;
        }//END RECO TRACK FOR LOOP
        
        //  cout<<"Smallest Distance: "<<distance_smallest<<endl;
        //    cout<<"******Best Match for Cluster : "<<mctrackcounter<<" is reco track number: "<<trackcounter_smallest<<" with distance:  "<<distance_smallest<<"*********"<<endl;
   //     cout<<"hitcounter6: "<<hitcounter<<endl;
   //     cout<<"backtrackedhitcounter5: "<<backtrackedhitcounter<<endl;
        /*
         
         for (auto const& hit : hits) {//START CLUSTER HIT LOOP
         charge = hit->Integral();
         cluster_charge += charge;
         cluster_energy += charge* 0.009558;
         
         }//END CLUSTER HIT LOOP
         
         
         
         Matchtree->Fill();
         */
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
    
}

void RecoEfficiency::endJob()
{
    // Implementation of optional member function here.
}









DEFINE_ART_MODULE(RecoEfficiency)
