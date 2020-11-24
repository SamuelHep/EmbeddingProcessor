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
  tree_name_ = "StMiniMcTree"; //MiniMcTree name
  tchain_ = InitChain( filelist, tree_name_ );
  cout << "Chain initialized" << endl;

  //Turn off all branches
  SetBranchStatus("*",0);
  cout << "All Branches turned off" << endl;

  //Estimate Max Entries
  //  Double_t *arr = tchain_->GetV1();
  int max_entries = 2000; //(int) TMath::MaxElement(tchain_->GetSelectedRows(),arr) + 300;
  cout << "Estimated max entries = " << max_entries << endl;

  //Init Branch vectors and add to branch list
  //      intialize event_int_map_[""], event_float_map_[""], track_int_map_[""] and event_float_map_[""]
  InitBranchVectors(max_entries); //Fills branch_names_[i]
  cout << "Useful branches turned back on" << endl;  

  //Turn on useful branches
  for ( int i=0; i<branch_names_.size();i++)
    {
      SetBranchStatus( branch_names_[i] , 1 );
    }

  //Set Tree Address to initialized vectors
  cout << "All Branches Set" << endl;
  
}

MiniMcReader::~MiniMcReader()
{
  delete tchain_;
}

void MiniMcReader::InitBranchVectors(int max_entries)
{

  mEventId = -999;
  mRunId = -999;
  mOriginMult = -999;
  mCentralMult =-999;
  mCentrality = -999;
  mMcMult = -999;
  
  mVertexX = -999; mVertexY = -999; mVertexZ = -999;
  mMcVertexX = -999; mMcVertexY = -999; mMcVertexZ = -999;

  mMagField = -999;

  mNMcTrack = -999;
  mNMatchedPair = -999;
  mNMergedPair = -999;
  mNSplitPair = -999;
  mNGhostPair = -999;
  mNContamPair = -999;
  mNMatGlobPair = -999;

  mMcPt.resize(max_entries,-999);
  mMcPz.resize(max_entries,-999);
  mMcEta.resize(max_entries,-999);
  mMcPhi.resize(max_entries,-999);
  mMcNHit.resize(max_entries,-999);

  mMcGeantId.resize(max_entries,-999);
  mMcCharge.resize(max_entries,-999);
  mMcParentGeantId.resize(max_entries,-999);

  mMatchedPt.resize(max_entries,-999);
  mMatchedPz.resize(max_entries,-999);
  mMatchedEta.resize(max_entries,-999);
  mMatchedPhi.resize(max_entries,-999);
  mMatchedNHit.resize(max_entries,-999);
  mMatchedNPoss.resize(max_entries,-999);

  mMatchedGeantId.resize(max_entries,-999);
  mMatchedCharge.resize(max_entries,-999);
  mMatchedParentGeantId.resize(max_entries,-999);

  mMatchedPtPr.resize(max_entries,-999);
  mMatchedPzPr.resize(max_entries,-999);
  mMatchedEtaPr.resize(max_entries,-999);
  mMatchedPhiPr.resize(max_entries,-999);
  mMatchedDcaPr.resize(max_entries,-999);
  mMatchedDcaXYPr.resize(max_entries,-999);
  mMatchedDcaZPr.resize(max_entries,-999);

  //Event Branches
  tchain_->SetBranchAddress("mEventId",&mEventId);
  tchain_->SetBranchAddress("mRunId",&mRunId);
  tchain_->SetBranchAddress("mOriginMult",&mOriginMult);
  tchain_->SetBranchAddress("mCentralMult",&mCentralMult);
  tchain_->SetBranchAddress("mCentrality",&mCentrality);
  tchain_->SetBranchAddress("mMcMult",&mMcMult);
  tchain_->SetBranchAddress("mVertexX",&mVertexX);
  tchain_->SetBranchAddress("mVertexY",&mVertexY);
  tchain_->SetBranchAddress("mVertexZ",&mVertexZ);
  tchain_->SetBranchAddress("mMcVertexX",&mMcVertexX);
  tchain_->SetBranchAddress("mMcVertexY",&mMcVertexY);
  tchain_->SetBranchAddress("mMcVertexZ",&mMcVertexZ);
  tchain_->SetBranchAddress("mMagField",&mMagField);
  tchain_->SetBranchAddress("mNMcTrack",&mNMcTrack);
  tchain_->SetBranchAddress("mNMatchedPair",&mNMatchedPair);
  tchain_->SetBranchAddress("mNMergedPair",&mNMergedPair);
  tchain_->SetBranchAddress("mNSplitPair",&mNSplitPair);
  tchain_->SetBranchAddress("mNGhostPair",&mNGhostPair);
  tchain_->SetBranchAddress("mNContamPair",&mNContamPair);
  tchain_->SetBranchAddress("mNMatGlobPair",&mNMatGlobPair);

  //Set Track Branches 
  tchain_->SetBranchAddress("mMcTracks.mPtMc",&mMcPt[0]);  
  tchain_->SetBranchAddress("mMcTracks.mPzMc", &mMcPz[0]);
  tchain_->SetBranchAddress("mMcTracks.mEtaMc",&mMcEta[0]);
  tchain_->SetBranchAddress("mMcTracks.mPhiMc",&mMcPhi[0]);
  tchain_->SetBranchAddress("mMcTracks.mNHitMc",&mMcNHit[0]);
  tchain_->SetBranchAddress("mMcTracks.mGeantId",&mMcGeantId[0]);
  tchain_->SetBranchAddress("mMcTracks.mChargeMc",&mMcCharge[0]);
  tchain_->SetBranchAddress("mMcTracks.mParentGeantId",&mMcParentGeantId[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mPtMc",&mMatchedPt[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mPzMc",&mMatchedPz[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mEtaMc",&mMatchedEta[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mPhiMc",&mMatchedPhi[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mFitPts",&mMatchedNHit[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mNPossible",&mMatchedNPoss[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mGeantId",&mMatchedGeantId[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mChargeMc",&mMatchedCharge[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mParentGeantId",&mMatchedParentGeantId[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mPtPr",&mMatchedPtPr[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mPzPr",&mMatchedPzPr[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mEtaPr",&mMatchedEtaPr[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mPhiPr",&mMatchedPhiPr[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mDcaPr",&mMatchedDcaPr[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mDcaXYPr",&mMatchedDcaXYPr[0]);
  tchain_->SetBranchAddress("mMatchedPairs.mDcaZPr",&mMatchedDcaZPr[0]);

  //Event Branches
  branch_names_.push_back("mEventId");
  branch_names_.push_back("mRunId");
  branch_names_.push_back("mOriginMult");
  branch_names_.push_back("mCentralMult");
  branch_names_.push_back("mCentrality");
  branch_names_.push_back("mMcMult");
  branch_names_.push_back("mVertexX");
  branch_names_.push_back("mVertexY");
  branch_names_.push_back("mVertexZ");
  branch_names_.push_back("mMcVertexX");
  branch_names_.push_back("mMcVertexY");
  branch_names_.push_back("mMcVertexZ");
  branch_names_.push_back("mMagField");
  branch_names_.push_back("mNMcTrack");
  branch_names_.push_back("mNMatchedPair");
  branch_names_.push_back("mNMergedPair");
  branch_names_.push_back("mNSplitPair");
  branch_names_.push_back("mNGhostPair");
  branch_names_.push_back("mNContamPair");
  branch_names_.push_back("mNMatGlobPair");

  //Set Track Branches 
  branch_names_.push_back("mMcTracks.mPtMc");
  branch_names_.push_back("mMcTracks.mPzMc");
  branch_names_.push_back("mMcTracks.mEtaMc");
  branch_names_.push_back("mMcTracks.mPhiMc");
  branch_names_.push_back("mMcTracks.mNHitMc");
  branch_names_.push_back("mMcTracks.mGeantId");
  branch_names_.push_back("mMcTracks.mChargeMc");
  branch_names_.push_back("mMcTracks.mParentGeantId");
  branch_names_.push_back("mMatchedPairs.mPtMc");
  branch_names_.push_back("mMatchedPairs.mPzMc");
  branch_names_.push_back("mMatchedPairs.mEtaMc");
  branch_names_.push_back("mMatchedPairs.mPhiMc");
  branch_names_.push_back("mMatchedPairs.mNHitMc");
  branch_names_.push_back("mMatchedPairs.mGeantId");
  branch_names_.push_back("mMatchedPairs.mChargeMc");
  branch_names_.push_back("mMatchedPairs.mParentGeantId");
  branch_names_.push_back("mMatchedPairs.mPtPr");
  branch_names_.push_back("mMatchedPairs.mPzPr");
  branch_names_.push_back("mMatchedPairs.mEtaPr");
  branch_names_.push_back("mMatchedPairs.mPhiPr");
  branch_names_.push_back("mMatchedPairs.mDcaPr");
  branch_names_.push_back("mMatchedPairs.mDcaXYPr");
  branch_names_.push_back("mMatchedPairs.mDcaZPr");
  
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
