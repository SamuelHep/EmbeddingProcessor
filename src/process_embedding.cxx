#include <utility>
#include "TH2D.h"
#include "minimc_reader.h"
#include "TMath.h"
#include "process_embedding.h"
#include <iostream>

using namespace std;

ClassImp(EmbeddingProcessor)

EmbeddingProcessor::EmbeddingProcessor(MiniMcReader * minimc_reader)
{

  minimc_reader_  = minimc_reader;
  //  matched_hist_   = new TH3D("efficiency_hist","",120,-0.5,119.5,100,0,2,110,0,2.2); // Mult, y, pt
  //  mc_hist_        = new TH3D("mc_hist","",120,-0.5,119.5,100,0,2,110,0,2.2); // Mult, y, pt
  matched_hist_   = new TH2D("efficiency_hist","",100,0,2,110,0,2.2); // Mult, y, pt
  mc_hist_        = new TH2D("mc_hist","",100,0,2,110,0,2.2); // Mult, y, pt

  vertexR_min_max_ = make_pair<double,double>(0,3);
  vertexZ_min_max_ = make_pair<double,double>(199,202);
  beamSpot_X_Y_    = make_pair<double,double>(-2,0);

  fxt3_nhitsfit_min_ = 10;
  fxt3_dca_max_= 3.0;

  nhitsfit_min_ = 10;
  dca_max_= 3.0;

  proton_mass = 0.93827;
  cout << "Embedding Processor Initialized" << endl;

}

int EmbeddingProcessor::Run()
{

  cout << "Loop Over entries" << endl;

  for (int i_entry; i_entry<minimc_reader_->NEntries(); i_entry++)
    {
      //      cout << "Entry#=" << i_entry << endl;
      minimc_reader_->GetEntry(i_entry);

      //Determine Multiplicity
      int fxtmult3=0;
      for ( int i_track=0;i_track<minimc_reader_->GetNMatchedPair();i_track++)
	{
	  //Check if bad track
	  if ( minimc_reader_->GetMatchedGeantId(i_track) == -999) continue;
	  fxtmult3 += CheckIfGoodFxtMult3Track(minimc_reader_,i_track);
	}
	      
      //      cout << "FxtMult3=" << fxtmult3 << endl;

      for ( int i_track=0;i_track<minimc_reader_->GetNMatchedPair();i_track++)
	{

	  //Check if bad track
	  if ( minimc_reader_->GetMatchedGeantId(i_track) == -999) continue;

	  //Check if good matched proton
	  if (!CheckIfGoodMatchedTrack(minimc_reader_,i_track)) continue;

	  float pt = minimc_reader_->GetMatchedPt(i_track);
	  float pz = minimc_reader_->GetMatchedPz(i_track);
	  float E  = sqrt(pt*pt + pz*pz + proton_mass*proton_mass);
	  float rap  = -0.5*TMath::Log( ( E + pz ) / ( E - pz ) );
	  //	  cout << " pz=" << pz << " E=" << E << endl;
	  //	  cout << " y=" << rap << " pt=" << pt << endl;
	  matched_hist_->Fill( rap, pt );
	}

      for ( int i_track=0;i_track<minimc_reader_->GetNMcTrack();i_track++)
	{

	  //Check if bad track
	  if ( minimc_reader_->GetMcGeantId(i_track) == -999) continue;

	  if ( minimc_reader_->GetMcGeantId(i_track) != kProtonPid ) continue;
	  float pt = minimc_reader_->GetMcPt(i_track);
	  float pz = minimc_reader_->GetMcPz(i_track);
	  float E  = sqrt(pt*pt + pz*pz + proton_mass*proton_mass);
	  float rap  = -0.5*TMath::Log( ( E + pz ) / ( E - pz ) );
	  //	  cout << " y=" << rap << " pt=" << pt << endl;
	  mc_hist_->Fill( rap, pt );
	}

    }
  
  return 0;

}

int EmbeddingProcessor::CheckIfGoodMatchedTrack(MiniMcReader * minimc_reader,int itrack)
{
  int nhits_fit = minimc_reader->GetMatchedNHit(itrack);
  int nhits_pos = minimc_reader->GetMatchedNPoss(itrack);
  float dca = sqrt( pow(minimc_reader->GetMatchedDcaXYPr(itrack),2) + pow(minimc_reader->GetMatchedDcaXYPr(itrack),2) );
  int geant_id = minimc_reader->GetMatchedGeantId(itrack);

  if ( ((double)nhits_fit)/nhits_pos < 0.51) return 0;
  if ( nhits_fit < nhitsfit_min_ ) return 0;
  if ( dca > dca_max_ ) return 0;
  if ( geant_id != 14 ) return 0;

  return 1; // GoodTrack
}

int EmbeddingProcessor::CheckIfGoodFxtMult3Track(MiniMcReader * minimc_reader,int itrack)
{
  int nhits_fit = minimc_reader->GetMatchedNHit(itrack);
  int nhits_pos = minimc_reader->GetMatchedNPoss(itrack);
  float dca = sqrt( pow(minimc_reader->GetMatchedDcaXYPr(itrack),2) + pow(minimc_reader->GetMatchedDcaXYPr(itrack),2) );
  int geant_id = minimc_reader->GetMatchedGeantId(itrack);
  //  cout << "NHitsFit = " << nhits_fit << " dca = " << dca << " GeantID = " << geant_id << endl;

  if ( ((double)nhits_fit)/nhits_pos < 0.51) return 0;
  if ( nhits_fit < fxt3_nhitsfit_min_ ) return 0;
  if ( dca > fxt3_dca_max_ ) return 0;
  if ( geant_id == kProtonPid ) return 0;

  return 1; // GoodTrack
}


