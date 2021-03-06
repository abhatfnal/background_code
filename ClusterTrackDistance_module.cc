////////////////////////////////////////////////////////////////////////
// Class:       ClusterTrackDistance
// Plugin Type: analyzer (art v2_05_01)
// File:        ClusterTrackDistance_module.cc
//
// Generated at Mon Jul 16 11:12:21 2018 by Avinay Bhat using cetskelgen
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



class ClusterTrackDistance;


class ClusterTrackDistance : public art::EDAnalyzer {
public:
  explicit ClusterTrackDistance(fhicl::ParameterSet const & p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  ClusterTrackDistance(ClusterTrackDistance const &) = delete;
  ClusterTrackDistance(ClusterTrackDistance &&) = delete;
  ClusterTrackDistance & operator = (ClusterTrackDistance const &) = delete;
  ClusterTrackDistance & operator = (ClusterTrackDistance &&) = delete;

  // Required functions.
  void analyze(art::Event const & e) override;

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

private:

  // Declare member data here.


  std::string fMC_track_tag,fReco_track_tag,fCluster_tag,fHit_tag;



  Int_t ClusterStartWire=0;
  Int_t ClusterEndWire=0;
  Double_t ClusterStartTick=0;
  Double_t ClusterEndTick=0;

  Double_t X_reco=0.0;
  Double_t Y_reco=0.0;
  Double_t Z_reco=0.0;

  Double_t X_reco3d=0.0;
  Double_t Y_reco3d=0.0;
  Double_t Z_reco3d=0.0;


  Double_t cluster_hit_z=0.0;
  Double_t cluster_hit_x=0.0;

  Double_t Y_cluster_hit_z=0.0;
  Double_t Y_cluster_hit_x=0.0;

  Double_t Y_cluster_3d_hit_x=0.0;
  Double_t Y_cluster_3d_hit_z=0.0;
  Double_t YU_cluster_3d_hit_y=0.0;
  Double_t YV_cluster_3d_hit_y=0.0;


  Double_t X_reco_best=0.0;
  Double_t Y_reco_best=0.0;
  Double_t Z_reco_best=0.0;

  Double_t X_reco_best3dV=0.0;
  Double_t Y_reco_best3dV=0.0;
  Double_t Z_reco_best3dV=0.0;

  Double_t X_reco_best3dU=0.0;
  Double_t Y_reco_best3dU=0.0;
  Double_t Z_reco_best3dU=0.0;

  Double_t pointdistance=0;
  Double_t pointdistance3dV=0;
  Double_t pointdistance3dU=0;

  Double_t V_cluster_y;
  Double_t U_cluster_y;
  Double_t V_cluster_z;
  Double_t U_cluster_z;
  Double_t U_cluster_y_new;



  Int_t plane;

  Double_t X_reco_smallest=0;
  Double_t Z_reco_smallest=0;

  Double_t X_reco_smallest3dV=0;
  Double_t Z_reco_smallest3dV=0;
  Double_t Y_reco_smallest3dV=0;

  Double_t X_reco_smallest3dU=0;
  Double_t Z_reco_smallest3dU=0;
  Double_t Y_reco_smallest3dU=0;



  Double_t pointdistance_smallest;
  Double_t pointdistance_smallestV;
  Double_t pointdistance_smallestU;

  Double_t distance_smallest;
  Double_t distance_smallestV;
  Double_t distance_smallestU;

  Double_t charge;
  Double_t chargediam;


  Double_t cluster_charge;
  Double_t cluster_energy;




  Double_t wire2cm,time2cm;

  Double_t start_tick1,start_tick2,start_tick0,end_tick1,end_tick2,end_tick0;
  std::vector<Double_t> Start_Cluster0;
  std::vector<Double_t> End_Cluster0;
  std::vector<Double_t> Start_Cluster1;
  std::vector<Double_t> End_Cluster1;
  std::vector<Double_t> Start_Cluster2;
  std::vector<Double_t> End_Cluster2;
  std::vector<Double_t> Y_clus_hitsize;
  std::vector<Int_t> Y_index_vector;
  std::vector<Int_t> V_index_vector;
  std::vector<Int_t> U_index_vector;



  Double_t V_t_min_abs; // smallest start point of the 2
  Double_t V_t_max_abs;    // largest start point of the three

  Double_t V_t_min_common; //  start point of the overlap
  Double_t V_t_max_common; // end point of the overlap
  ///////////////////////////////////////////////////////////////////////////
  Double_t U_t_min_abs; // smallest start point of the 2
  Double_t U_t_max_abs;    // largest start point of the three

  Double_t U_t_min_common; //  start point of the overlap
  Double_t U_t_max_common; // end point of the overlap


  Double_t  V_iou;
  Double_t V_biggest_iou;
  Int_t V_match_multiplicity;

  Double_t  U_iou;
  Double_t U_biggest_iou;
  Int_t U_match_multiplicity;

  Double_t Y_clus_lifetime;
  Double_t Y_clus_hitSize;


  TTree *Clustertree;
  //    TTree *V_Clustertree;
  //   TTree *U_Clustertree;
  TTree *Matchingtree;
};

ClusterTrackDistance::ClusterTrackDistance(fhicl::ParameterSet const & p)
: EDAnalyzer(p)  // ,
// More initializers here.
{

  //All tags get filled in the runClusterTrackDistance.fcl file
  fMC_track_tag   = p.get<std::string>("mctrack_tag"    );
  fReco_track_tag = p.get<std::string>("recotrack_tag"  );
  fCluster_tag = p.get<std::string>("cluster_tag"  );
  fHit_tag = p.get<std::string>("hit_tag"  );


}

void ClusterTrackDistance::analyze(art::Event const & e)
{
  // std::cout << "Event Number: " << e.event() << " Run Number: " << e.run() << std::endl;

  // Implementation of required member function here.
  art::Handle<std::vector<recob::Cluster> > cluster_handle;
  e.getByLabel(fCluster_tag,cluster_handle);

  art::Handle<std::vector<recob::Track> > recotrack_handle;
  e.getByLabel(fReco_track_tag,recotrack_handle);

  art::Handle<std::vector<recob::Hit> > hit_handle;
  e.getByLabel(fHit_tag,hit_handle);

  art::FindMany<recob::Hit> clus_hit_assn_v(cluster_handle, e, fCluster_tag);

  auto const& cluster(*cluster_handle);

  Int_t clustercounter=0; //Variable to keep track of cluster index


  for (size_t i_c = 0, size_cluster = cluster_handle->size(); i_c != size_cluster; ++i_c) { //START CLUSTER FOR LOOP

    //  if(cluster[i_c].View()==2){//Y CLUSTER IF LOOP
    distance_smallest=1e10; //Variable for distance between a cluster and nearest reco track, initialized to a large number for comparison
    cluster_charge=0.0;//Cluster variable initialized to zero
    cluster_energy=0.0;//Cluster variable initialized to zero
    start_tick1=0;
    start_tick2=0;
    start_tick0=0;
    end_tick1=0;
    end_tick2=0;
    end_tick0=0;

    auto hits = clus_hit_assn_v.at(i_c);
    //  cout<<"hits.size(): "<<hits.size()<<endl;

    Int_t trackcounter=0;//Variable to keep track of cluster index
    //Int_t trackcounter_smallest=0;

    for (size_t i_t = 0, size_track = recotrack_handle->size(); i_t != size_track; ++i_t) {//START RECO TRACK FOR LOOP
      trackcounter++;
      //cout<<"***************************************Track Counter: "<<trackcounter<<endl;


      auto const& track = recotrack_handle->at(i_t);


      pointdistance_smallest=1e10;////Variable for distance between a cluster hit and a reco track point, initialized to a large number for comparison
      for(size_t m=0;m<(track.NumberTrajectoryPoints());m++){//START RECO POINT LOOP


        X_reco=track.LocationAtPoint(m).X();
        Y_reco=track.LocationAtPoint(m).Y();
        Z_reco=track.LocationAtPoint(m).Z();

        //   cout<<"X_reco: "<<X_reco<<endl;
        auto const* geom = ::lar::providerFrom<geo::Geometry>();
        auto V_wire_cm = geom->WireCoordinate(Y_reco,Z_reco,geo::PlaneID(0,0,1)) * wire2cm;
        //  auto V_wire_id = geom->WireCoordinate(Y_reco,Z_reco,geo::PlaneID(0,0,1));
        auto V_time_cm = X_reco;

        auto U_wire_cm = geom->WireCoordinate(Y_reco,Z_reco,geo::PlaneID(0,0,0)) * wire2cm;
        //  auto U_wire_id = geom->WireCoordinate(Y_reco,Z_reco,geo::PlaneID(0,0,0));
        auto U_time_cm = X_reco;


        for (auto const& hit : hits) {//START CLUSTER HIT LOOP

          cluster_hit_z = hit->WireID().Wire * wire2cm;//Also equal to Cluster_hit_wire_cm
          cluster_hit_x = (hit->PeakTime() * time2cm)-44.575 ;//Also equal to Cluster_hit_time_cm

          if(cluster[i_c].View()==2){
            plane=2;
            pointdistance=sqrt((pow(cluster_hit_z-Z_reco,2))+(pow(cluster_hit_x-X_reco,2)));

          }
          if (cluster[i_c].View()==1){     //    cout<<"pointdistance: "<<pointdistance<<endl;
          plane=1;

          pointdistance=sqrt((pow(cluster_hit_z-V_wire_cm,2))+(pow(cluster_hit_x-V_time_cm,2)));
        }

        if (cluster[i_c].View()==0){     //    cout<<"pointdistance: "<<pointdistance<<endl;
        plane=0;
        pointdistance=sqrt((pow(cluster_hit_z-U_wire_cm,2))+(pow(cluster_hit_x-U_time_cm,2)));
      }

      if(pointdistance<pointdistance_smallest){//comparison IF loop

        pointdistance_smallest=pointdistance;

        X_reco_smallest=X_reco;
        Z_reco_smallest=Z_reco;

      }

    }//END CLUSTER HIT LOOP


    //cout<<"Pointdistance_smallest1: "<<pointdistance_smallest<<endl;

  }//END RECO POINT LOOP


  if(pointdistance_smallest<distance_smallest){
    distance_smallest=pointdistance_smallest;
    //   trackcounter_smallest=trackcounter;
    X_reco_best=X_reco_smallest;
    Z_reco_best=Z_reco_smallest;
  }
  //      cout<<"distance_smallest: "<<distance_smallest<<endl;

}//END RECO TRACK FOR LOOP


for (auto const& hit : hits) {//START CLUSTER HIT LOOP
  //  charge=0;
  charge = hit->Integral();
  cluster_charge += charge;
  cluster_energy += charge*240*23.6*1e-6/0.5;

}//END CLUSTER HIT LOOP



//  cout<<"Smallest Distance: "<<distance_smallest<<endl;
//      cout<<"X_reco_best: "<<X_reco_best<<endl;
//     cout<<"cluster_energy: "<<cluster_energy<<" MeV"<<endl;



Clustertree->Fill();


clustercounter++;
//  cout<<"***************************************************Cluster Counter: "<<clustercounter<<endl;

//    cout<<"Cluster Plane: "<<cluster[i_c].View()<<endl;


if(cluster[i_c].View()==2 && distance_smallest>15.0 ){// IF LOOP TO CHECK WHAT PLANE A CLUSTER BELONGS TO

  //    cout<<"This cluster is from Plane2"<<endl;
  Start_Cluster2.push_back((cluster[i_c].StartTick ())-3.0);//added +- 3.0 time tick tolerances
  End_Cluster2.push_back((cluster[i_c].EndTick ())+3.0);
  Y_clus_hitsize.push_back(clus_hit_assn_v.at(i_c).size());
  Y_index_vector.push_back(i_c);
  //  auto Start_wire_Cluster2.push_back(cluster[i_c].StartWire().WireID());
}

if(cluster[i_c].View()==1 && distance_smallest>5.0){//IF LOOP TO CHECK WHAT PLANE A CLUSTER BELONGS TO

  //    cout<<"This cluster is from Plane2"<<endl;
  Start_Cluster1.push_back((cluster[i_c].StartTick ())-3.0);
  End_Cluster1.push_back((cluster[i_c].EndTick ())+3.0);
  V_index_vector.push_back(i_c);
}

if(cluster[i_c].View()==0 && distance_smallest>5.0){//IF LOOP TO CHECK WHAT PLANE A CLUSTER BELONGS TO

  //    cout<<"This cluster is from Plane2"<<endl;
  Start_Cluster0.push_back((cluster[i_c].StartTick ())-3.0);
  End_Cluster0.push_back((cluster[i_c].EndTick ())+3.0);
  U_index_vector.push_back(i_c);
  //  cout<<"End_Cluster0.push_back(cluster[i_c].EndTick ()): "<<End_Cluster0[i_c]<<endl;
}



}//END CLUSTER FOR LOOP



V_t_min_common = -999.; //  start point of the overlap
V_t_max_common = -999.; // end point of the overlap

U_t_min_common = -999.; //  start point of the overlap
U_t_max_common = -999.; // end point of the overlap

auto const* geom = ::lar::providerFrom<geo::Geometry>();
for (size_t i = 0; i < Start_Cluster2.size(); i++) {//START PLANE MATCHING FOR LOOP (Y-COLLECTION PLANE LOOP)
  Y_clus_hitSize=Y_clus_hitsize[i];
    distance_smallestV=1e10;
    distance_smallestU=1e10;

  // if (Y_clus_hitSize < 1)
  // continue;
  auto hiti = clus_hit_assn_v.at(Y_index_vector[i]);

  for (auto const& hity : hiti) {//START CLUSTER HIT LOOP

    Y_cluster_hit_z = hity->WireID().Wire * wire2cm;//Also equal to Cluster_hit_wire_cm
    Y_cluster_hit_x = (hity->PeakTime() * time2cm)-44.575 ;//Also equal to Cluster_hit_time_cm
  }



  V_match_multiplicity=0;
  U_match_multiplicity=0;
  Y_clus_lifetime=End_Cluster2[i]-Start_Cluster2[i];

  //  auto Yhits = clus_hit_assn_v.at(i);
  //  cout<<"Start_Cluster2 at "<<i<<" :"<<Start_Cluster2[i]<<endl;
  //  cout<<"End_Cluster2 at "<<i<<" :"<<End_Cluster2[i]<<endl;
  //    cout<<"Y_clus_lifetime: "<<Y_clus_lifetime<<endl;
  //    cout<<"Y_clus_hitSize: "<<Y_clus_hitSize<<endl;

  V_biggest_iou=-1;
  V_cluster_y= -999.0;

  for (size_t j = 0; j < Start_Cluster1.size(); j++) {//START V-INDUCTION PLANE FOR LOOP)


    V_iou=-999.0;
    // cout<<"Start_Cluster2 : "<<Start_Cluster2[i]<<endl;
    // cout<<"End_Cluster2 : "<<End_Cluster2[i]<<endl;


    // cout<<"Start_Cluster1 : "<<Start_Cluster1[j]<<endl;
    // cout<<"End_Cluster1 : "<<End_Cluster1[j]<<endl;


    V_t_min_abs = 9600.0;
    V_t_max_abs = 0.0;
    if ( Start_Cluster2[i] < V_t_min_abs )
    V_t_min_abs = Start_Cluster2[i];
    if ( End_Cluster2[i]   > V_t_max_abs )
    V_t_max_abs = End_Cluster2[i];

    if ( Start_Cluster1[j] < V_t_min_abs )
    V_t_min_abs = Start_Cluster1[j];
    if ( End_Cluster1[j]   > V_t_max_abs )
    V_t_max_abs = End_Cluster1[j];

    if (Start_Cluster2[i]<Start_Cluster1[j])
    V_t_min_common = Start_Cluster1[j];
    if (Start_Cluster2[i]>Start_Cluster1[j])
    V_t_min_common = Start_Cluster2[i];

    if (End_Cluster2[i]<End_Cluster1[j])
    V_t_max_common = End_Cluster2[i];
    if (End_Cluster2[i]>End_Cluster1[j])
    V_t_max_common = End_Cluster1[j];



    // cout << fixed << setprecision(11) <<"V_t max abs"  << "  " << V_t_max_abs << " V_t min abs" << "  " << V_t_min_abs <<  endl;
    // cout << fixed << setprecision(11) <<"V_t max common"  << "  " << V_t_max_common << " V_t min common" << "  " << V_t_min_common <<  endl;


    auto hitj = clus_hit_assn_v.at(V_index_vector[j]);

    geo::WireIDIntersection clusterintersectionV;
    auto Vintersect = geom->WireIDsIntersect(hiti[0]->WireID(),hitj[0]->WireID(),clusterintersectionV);
    // cout<<"Vintersect: "<<Vintersect<<endl;

    if (V_t_min_common > V_t_max_common){//NO OVERLAP
      V_iou = -1;
    }
    if ((V_t_min_common < V_t_max_common) && (Vintersect==1))//OVERLAP
    {
      V_iou = (V_t_max_common - V_t_min_common) / (V_t_max_abs - V_t_min_abs);
      V_match_multiplicity++;

    }

    // cout<<"V_iou: "<<V_iou<<endl;

    if ((V_iou > V_biggest_iou) && (Vintersect==1)){
      V_biggest_iou = V_iou;
      V_cluster_y= clusterintersectionV.y;
      V_cluster_z= clusterintersectionV.z;
    }




  }//END V-INDUCTION PLANE FOR LOOP

  U_biggest_iou=-1;
  U_cluster_y= -999.0;
  for (size_t k = 0; k < Start_Cluster0.size(); k++) {//START U-INDUCTION PLANE FOR LOOP
    // cout<<"Start_Cluster0 at "<<k<<" :"<<Start_Cluster0[k]<<endl;
    // cout<<"End_Cluster0 at "<<k<<" :"<<End_Cluster0[k]<<endl;


    U_iou=-999.0;
    U_t_min_abs = 9600.0;
    U_t_max_abs = 0.0;


    if ( Start_Cluster2[i] < U_t_min_abs )
    U_t_min_abs = Start_Cluster2[i];
    if ( End_Cluster2[i]   > U_t_max_abs )
    U_t_max_abs = End_Cluster2[i];

    if ( Start_Cluster0[k] < U_t_min_abs )
    U_t_min_abs = Start_Cluster0[k];
    if ( End_Cluster0[k]   > U_t_max_abs )
    U_t_max_abs = End_Cluster0[k];

    if (Start_Cluster2[i]<Start_Cluster0[k])
    U_t_min_common = Start_Cluster0[k];
    if (Start_Cluster2[i]>Start_Cluster0[k])
    U_t_min_common = Start_Cluster2[i];

    if (End_Cluster2[i]<End_Cluster0[k])
    U_t_max_common = End_Cluster2[i];
    if (End_Cluster2[i]>End_Cluster0[k])
    U_t_max_common = End_Cluster0[k];

    // cout << i << j << "  " << "t max abs"  << "  " << t_max_abs << " t min abs" << "  " << t_min_abs <<  endl;
    // cout << i << j << "  " << "t max common"  << "  " << t_max_common << " t min common" << "  " << t_min_common <<  endl;

    auto hitk = clus_hit_assn_v.at(U_index_vector[k]);

    geo::WireIDIntersection clusterintersectionU;
    // geo::WireIDIntersection clusterintersectionUnew;
    auto Uintersect = geom->WireIDsIntersect(hiti[0]->WireID(),hitk[0]->WireID(),clusterintersectionU);

    // cout<<"Uintersect: "<<Uintersect<<endl;

    /*
    for(auto const& hitynew : hiti){

      for(auto const& hitunew : hitk){
        auto newUintersect = geom->WireIDsIntersect(hitynew->WireID(),hitunew->WireID(),clusterintersectionUnew);
        if (Uintersect==1){
          chargediam=1.0;
        }
      }

    }
    */

    if (U_t_min_common > U_t_max_common)//NO OVERLAP
    U_iou = U_biggest_iou;
    if ((U_t_min_common < U_t_max_common) && (Uintersect==1) )//OVERLAP
    {
      U_iou = (U_t_max_common - U_t_min_common) / (U_t_max_abs - U_t_min_abs);
      U_match_multiplicity++;
    }

    // cout<<"iou: "<<iou<<endl;

    if ((U_iou > U_biggest_iou) && (Uintersect==1)){
      U_biggest_iou = U_iou;
      U_cluster_y= clusterintersectionU.y;
      U_cluster_z= clusterintersectionU.z;
      // U_cluster_y_new= clusterintersectionUnew.y;
    }

  }//END U-INDUCTION PLANE FOR LOOP

  // cout<<"******************************V_biggest_iou for cluster: "<<i<<" is: "<<V_biggest_iou<<"**********************************"<<endl;
  //  cout<<"Cluster2# has : "<<i<<" Match Multiplicity: "<<match_multiplicity<<endl;
  // Matchingtree->Fill();

// if (V_match_multiplicity<1 || U_match_multiplicity<1)
// continue;

  for (size_t i_tr = 0, size_tr = recotrack_handle->size(); i_tr != size_tr; ++i_tr) {//START RECO TRACK FOR LOOP

    auto const& rtrack = recotrack_handle->at(i_tr);


    Double_t pointdistance_smallestV=1e10;////Variable for distance between a cluster hit and a reco track point, initialized to a large number for comparison
    Double_t pointdistance_smallestU=1e10;
    for(size_t n=0;n<(rtrack.NumberTrajectoryPoints());n++){//START RECO POINT LOOP
      X_reco3d=rtrack.LocationAtPoint(n).X();
      Y_reco3d=rtrack.LocationAtPoint(n).Y();
      Z_reco3d=rtrack.LocationAtPoint(n).Z();


      for (auto const& hitY : hiti) {//START CLUSTER HIT LOOP
        Y_cluster_3d_hit_z = hitY->WireID().Wire * wire2cm;//Also equal to Cluster_hit_wire_cm
        Y_cluster_3d_hit_x = (hitY->PeakTime() * time2cm)-44.575 ;//Also equal to Cluster_hit_time_cm
        auto  YU_cluster_3d_hit_y = U_cluster_y;
        auto  YV_cluster_3d_hit_y = V_cluster_y;
        if (V_match_multiplicity>1){
        pointdistance3dV=sqrt((pow(Y_cluster_3d_hit_z-Z_reco3d,2))+(pow(Y_cluster_3d_hit_x-X_reco3d,2))+ (pow(YV_cluster_3d_hit_y-Y_reco3d,2)));
      }
        if (U_match_multiplicity>1){
        pointdistance3dU=sqrt((pow(Y_cluster_3d_hit_z-Z_reco3d,2))+(pow(Y_cluster_3d_hit_x-X_reco3d,2))+ (pow(YU_cluster_3d_hit_y-Y_reco3d,2)));
      }

        if(pointdistance3dV<pointdistance_smallestV){//comparison IF loop

          pointdistance_smallestV=pointdistance3dV;

          X_reco_smallest3dV=X_reco3d;
          Z_reco_smallest3dV=Z_reco3d;
          Y_reco_smallest3dV=Y_reco3d;

        }

        if(pointdistance3dU<pointdistance_smallestU){//comparison IF loop

          pointdistance_smallestU=pointdistance3dU;

          X_reco_smallest3dU=X_reco3d;
          Z_reco_smallest3dU=Z_reco3d;
          Y_reco_smallest3dU=Y_reco3d;

        }



      }



    }//END RECO POINT LOOP

    if(pointdistance_smallestV<distance_smallestV){
      distance_smallestV=pointdistance_smallestV;

      X_reco_best3dV=X_reco_smallest3dV;
      Z_reco_best3dV=Z_reco_smallest3dV;
      Y_reco_best3dV=Y_reco_smallest3dV;
    }

    if(pointdistance_smallestU<distance_smallestU){
      distance_smallestU=pointdistance_smallestU;

      X_reco_best3dU=X_reco_smallest3dU;
      Z_reco_best3dU=Z_reco_smallest3dU;
      Y_reco_best3dU=Y_reco_smallest3dU;
    }



  }// END RECO TRACK FOR LOOP


Matchingtree->Fill();

}//END PLANE MATCHING FOR LOOP (Y-COLLECTION PLANE LOOP)

Start_Cluster0.clear();
End_Cluster0.clear();
Start_Cluster1.clear();
End_Cluster1.clear();
Start_Cluster2.clear();
End_Cluster2.clear();
Y_clus_hitsize.clear();
Y_index_vector.clear();
V_index_vector.clear();
U_index_vector.clear();
}//END EVENT LOOP


void ClusterTrackDistance::beginJob()
{ // get detector specific properties

  auto const* geom = ::lar::providerFrom<geo::Geometry>();
  auto const* detp = lar::providerFrom<detinfo::DetectorPropertiesService>();
  //  auto const* geomcore = lar::providerFrom<geo::GeometryCore>();

  wire2cm = geom->WirePitch(0,0,0);
  time2cm = detp->SamplingRate() / 1000.0 * detp->DriftVelocity( detp->Efield(), detp->Temperature() );



  art::ServiceHandle<art::TFileService> tfs;

  Clustertree = tfs->make<TTree>("Clustertree",    "Clustertree");
  Matchingtree = tfs->make<TTree>("Matchingtree",    "Matchingtree");

  Clustertree->Branch("cluster_hit_z",&cluster_hit_z,"cluster_hit_z/D");
  Clustertree->Branch("cluster_hit_x",&cluster_hit_x,"cluster_hit_x/D");
  Clustertree->Branch("Z_reco_best",&Z_reco_best,"Z_reco_best/D");
  Clustertree->Branch("X_reco_best",&X_reco_best,"X_reco_best/D");
  Clustertree->Branch("distance_smallest",&distance_smallest,"distance_smallest/D");
  Clustertree->Branch("cluster_charge",&cluster_charge,"cluster_charge/D");
  Clustertree->Branch("cluster_energy",&cluster_energy,"cluster_energy/D");
  Clustertree->Branch("plane",&plane,"plane/I");


  Matchingtree->Branch("V_biggest_iou",&V_biggest_iou,"V_biggest_iou/D");
  Matchingtree->Branch("V_match_multiplicity",&V_match_multiplicity,"V_match_multiplicity/I");
  Matchingtree->Branch("U_biggest_iou",&U_biggest_iou,"U_biggest_iou/D");
  Matchingtree->Branch("U_match_multiplicity",&U_match_multiplicity,"U_match_multiplicity/I");
  Matchingtree->Branch("Y_clus_lifetime",&Y_clus_lifetime,"Y_clus_lifetime/D");
  Matchingtree->Branch("Y_clus_hitSize",&Y_clus_hitSize,"Y_clus_hitSize/D");
  Matchingtree->Branch("Y_cluster_hit_z",&Y_cluster_hit_z,"Y_cluster_hit_z/D");
  Matchingtree->Branch("Y_cluster_hit_x",&Y_cluster_hit_x,"Y_cluster_hit_x/D");
  Matchingtree->Branch("V_cluster_y",&V_cluster_y,"V_cluster_y/D");
  Matchingtree->Branch("U_cluster_y",&U_cluster_y,"U_cluster_y/D");
  Matchingtree->Branch("V_cluster_z",&V_cluster_z,"V_cluster_z/D");
  Matchingtree->Branch("U_cluster_z",&U_cluster_z,"U_cluster_z/D");
  Matchingtree->Branch("Y_cluster_3d_hit_z",&Y_cluster_3d_hit_z,"Y_cluster_3d_hit_z/D");
  Matchingtree->Branch("Y_cluster_3d_hit_x",&Y_cluster_3d_hit_x,"Y_cluster_3d_hit_x/D");
  Matchingtree->Branch("YV_cluster_3d_hit_y",&YV_cluster_3d_hit_y,"YV_cluster_3d_hit_y/D");
  Matchingtree->Branch("YU_cluster_3d_hit_y",&YU_cluster_3d_hit_y,"YU_cluster_3d_hit_y/D");
  Matchingtree->Branch("Z_reco_best3dV",&Z_reco_best3dV,"Z_reco_best3dV/D");
  Matchingtree->Branch("X_reco_best3dV",&X_reco_best3dV,"X_reco_best3dV/D");
  Matchingtree->Branch("Y_reco_best3dV",&Y_reco_best3dV,"Y_reco_best3dV/D");
  Matchingtree->Branch("Z_reco_best3dU",&Z_reco_best3dU,"Z_reco_best3dU/D");
  Matchingtree->Branch("X_reco_best3dU",&X_reco_best3dU,"X_reco_best3dU/D");
  Matchingtree->Branch("Y_reco_best3dU",&Y_reco_best3dU,"Y_reco_best3dU/D");
  Matchingtree->Branch("distance_smallestV",&distance_smallestV,"distance_smallestV/D");
  Matchingtree->Branch("distance_smallestU",&distance_smallestU,"distance_smallestU/D");


}

void ClusterTrackDistance::endJob()
{
  // Implementation of optional member function here.
}


DEFINE_ART_MODULE(ClusterTrackDistance)
