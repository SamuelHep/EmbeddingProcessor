#include <vector>
#include "TString.h"
#include "TChain.h"
#include "TMath.h"
#include <fstream>
#include <iostream>
#include <map>

#include "minimc_reader.h"

using namespace std;

ClassImp(MiniMcReader)

MiniMcReader::MiniMcReader( TString filelist )
{

  //Init Chain
  tree_name_ = ""; //MiniMcTree name
  tchain_ = InitChain( filelist, tree_name_ );

  //Turn off all branches
  SetBranchStatus("*",0);

  //Estimate Max Entries
  Double_t *arr = tchain_->GetV1();
  int max_entries = (int) TMath::MaxElement(tchain_->GetSelectedRows(),arr) + 300;
  
  //Init Branch vectors and add to branch list
  //      intialize event_int_map_[""], event_float_map_[""], track_int_map_[""] and event_float_map_[""]
  InitBranchVectors(max_entries); //Fills branch_names_[i]
  
  //Turn on useful branches
  for ( int i=0; i<branch_names_.size();i++)
    {
      SetBranchStatus( branch_names_[i] , 1 );
    }

  //Set Tree Address to initialized vectors
  for ( auto & imap : event_int_map_){ tchain_->SetBranchAddress(imap.first,&imap.second);}
  for ( auto & imap : event_float_map_){ tchain_->SetBranchAddress(imap.first,&imap.second);}
  for ( auto & imap : track_int_map_){ tchain_->SetBranchAddress(imap.first,&imap.second);}
  for ( auto & imap : track_float_map_){ tchain_->SetBranchAddress(imap.first,&imap.second);}
  
}

MiniMcReader::~MiniMcReader()
{
  delete tchain_;
}

std::vector<float> MiniMcReader::MakeEmptyFloatVector(int max_entries)
{
  std::vector<float> v(max_entries,kEmpty);
  return v;
}

std::vector<int> MiniMcReader::MakeEmptyIntVector(int max_entries)
{
  std::vector<int> v(max_entries,kEmpty);
  return v;
}

void MiniMcReader::InitBranchVectors(int max_entries)
{

  event_int_map_["mEventId"] = kEmpty;
  event_int_map_["mRunId"] = kEmpty;    
  event_int_map_["mOrigin"] = kEmpty;
  event_int_map_["mCentralMult"] = kEmpty;
  event_int_map_["mCentrality"] =kEmpty;
  event_int_map_["mMcMult"] =kEmpty;

  event_float_map_["mVertexX"] =kEmpty;
  event_float_map_["mVertexY"] = kEmpty;
  event_float_map_["mVertexZ"] = kEmpty;
  event_float_map_["mMcVertexX"] = kEmpty;
  event_float_map_["mMcVertexY"] = kEmpty;
  event_float_map_["mMcVertexZ"] = kEmpty;
  event_float_map_["mMagField"] = kEmpty;

  event_int_map_["mNMcTrack"] = kEmpty;
  event_int_map_["mNMatchedPair"] = kEmpty;
  event_int_map_["mNMergedPair"] = kEmpty;
  event_int_map_["mNSplitPair"] = kEmpty;
  event_int_map_["mNGhostPair"] = kEmpty;
  event_int_map_["mNContamPair"] = kEmpty;
  event_int_map_["mNMatGlobPair"] = kEmpty;

  track_float_map_["mMcTracks.mPtMc"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMcTracks.mPzMc"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMcTracks.mEtaMc"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMcTracks.mPhiMc"] = MakeEmptyFloatVector( max_entries );
  track_int_map_["mMcTracks.mNHitMc"] = MakeEmptyIntVector( max_entries );
  
  track_int_map_["mMcTracks.mGeantId"] = MakeEmptyIntVector( max_entries );
  track_int_map_["mMcTracks.mPdgId"] = MakeEmptyIntVector( max_entries );
  track_int_map_["mMcTracks.mChargeMc"] = MakeEmptyIntVector( max_entries );
  track_int_map_["mMcTracks.mParentGeantId"] = MakeEmptyIntVector( max_entries );
  track_int_map_["mMcTracks.mIsPrimary"] = MakeEmptyIntVector( max_entries );

  track_float_map_["mMatchedPairs.mPtMc"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mPzMc"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mEtaMc"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mPhiMc"] = MakeEmptyFloatVector( max_entries );

  track_int_map_["mMatchedPairs.mNHitMc"] = MakeEmptyIntVector( max_entries );
  track_int_map_["mMatchedPairs.mGeantId"] = MakeEmptyIntVector( max_entries );
  track_int_map_["mMatchedPairs.mPdgId"] = MakeEmptyIntVector( max_entries );
  track_int_map_["mMatchedPairs.mChargeMc"] = MakeEmptyIntVector( max_entries );

  track_int_map_["mMatchedPairs.mParentGeantId"] = MakeEmptyIntVector( max_entries );

  track_int_map_["mMatchedPairs.mIsPrimary"] = MakeEmptyIntVector( max_entries );
  track_int_map_["mMatchedPairs.mIsDca"] = MakeEmptyIntVector( max_entries );
  track_float_map_["mMatchedPairs.mPtPr"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mPzPr"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mEtaPr"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mPhiPr"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mDcaPr"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mDcaXYPr"] = MakeEmptyFloatVector( max_entries );
  track_float_map_["mMatchedPairs.mDcaZPr"] = MakeEmptyFloatVector( max_entries );

  //Add to branch names list
  for ( auto & imap : event_int_map_){ branch_names_.push_back(imap.first);}
  for ( auto & imap : event_float_map_){ branch_names_.push_back(imap.first);}
  for ( auto & imap : track_int_map_){ branch_names_.push_back(imap.first);}
  for ( auto & imap : track_float_map_){ branch_names_.push_back(imap.first);}
  
}

TChain * MiniMcReader::InitChain( TString filelist, TString tree_name )
{

  TChain * tchain = new TChain( tree_name );
  
  ifstream file_stream( filelist );
  if (!file_stream.is_open()){
    fputs("ERROR:: UrQMDReader::ConstructTree() - File list not open! Exiting\n",stderr);
    exit (EXIT_FAILURE);
  }

  string file_name;
  while (file_stream.good()){
    getline(file_stream,file_name);
    if (file_name.length() != 0 && file_name.find(".root") != std::string::npos){
      cout <<"Adding: " <<file_name <<endl;
      tchain->Add(file_name.c_str());
    }
  };

  file_stream.close();
  
  return tchain;
}

void MiniMcReader::SetBranchStatus(TString branch_name, Int_t active)
{
  tchain_->SetBranchStatus(branch_name,active);
}
