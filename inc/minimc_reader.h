#ifndef MINI_MCREADER_H_
#define MINI_MCREADER_H_

#include "TString.h"
#include "TChain.h"
#include <vector>
#include <map>

class MiniMcReader : public TObject {
  
 private:

  enum{kEmpty=-999};
  TString tree_name_;
  TChain * tchain_;
  
  std::vector<float> MakeEmptyFloatVector(int max_entries);
  std::vector<int> MakeEmptyIntVector(int max_entries);

  void InitBranchVectors(int max_entries);
  TChain * InitChain( TString filelist, TString tree_name );
  void SetBranchStatus(TString branch_name, Int_t active);
  
  std::map <TString, int> event_int_map_;
  std::map <TString, float> event_float_map_;
  std::map <TString, std::vector<int> > track_int_map_;
  std::map <TString, std::vector<float> > track_float_map_;
  std::vector<TString> branch_names_;
  
 public:

  MiniMcReader(TString filelist);
  ~MiniMcReader();

  void GetEntry(int iEntry){ tchain_->GetEntry(iEntry);}
  int NEntries(){ return tchain_->GetEntries();}
  
  //Get Methods... How to reader the event
  int GetEventId(){ return event_int_map_["mEventId"]; }
  int GetRunId(){ return event_int_map_["mRunId"]; }
  int GetOrigin(){ return event_int_map_["mOrigin"]; }
  int GetCentralMult(){ return event_int_map_["mCentralMult"]; }
  int GetCentrality(){ return event_int_map_["mCentrality"]; }
  int GetMcMult(){ return event_int_map_["mMcMult"]; }
  
  float GetVertexX(){ return event_float_map_["mVertexX"]; }
  float GetVertexY(){ return event_float_map_["mVertexY"]; }
  float GetVertexZ(){ return event_float_map_["mVertexZ"]; }
  
  float GetMcVertexX(){ return event_float_map_["mMcVertexX"]; }
  float GetMcVertexY(){ return event_float_map_["mMcVertexY"]; }
  float GetMcVertexZ(){ return event_float_map_["mMcVertexZ"]; }
  float GetMagField(){ return event_float_map_["mMagField"]; }
  
  int GetNMcTrack(){ return event_int_map_["mNMcTrack"]; } 
  int GetNMatchedPair(){ return event_int_map_["mNMatchedPair"]; }
  
  float GetMcPt(int iTrack){ return track_float_map_["mMcTracks.mPtMc"][iTrack];}
  float GetMcPz(int iTrack){ return track_float_map_["mMcTracks.mPzMc"][iTrack];}
  float GetMcEta(int iTrack){ return track_float_map_["mMcTracks.mEtaMc"][iTrack];}
  float GetMcPhi(int iTrack){ return track_float_map_["mMcTracks.mPhiMc"][iTrack];}
  
  int GetMcNHit(int iTrack){ return track_int_map_["mMcTracks.mNHitMc"][iTrack];}  
  int GetMcGeantId(int iTrack){ return track_int_map_["mMcTracks.mGeantId"][iTrack];}
  int GetMcPdgId(int iTrack){ return track_int_map_["mMcTracks.mPdgId"][iTrack];}
  int GetMcCharge(int iTrack){ return track_int_map_["mMcTracks.mChargeMc"][iTrack];}
  int GetMcParentGeantId(int iTrack){ return track_int_map_["mMcTracks.mParentGeantId"][iTrack];}
  int GetMcIsPrimary(int iTrack){ return track_int_map_["mMcTracks.mIsPrimary"][iTrack];}
  
  float GetMatchedMcPt(int iTrack){ return track_float_map_["mMatchedPairs.mPtMc"][iTrack];}
  float GetMatchedMcPz(int iTrack){ return track_float_map_["mMatchedPairs.mPzMc"][iTrack];}
  float GetMatchedMcEta(int iTrack){ return track_float_map_["mMatchedPairs.mEtaMc"][iTrack];}
  float GetMatchedMcPhi(int iTrack){ return track_float_map_["mMatchedPairs.mPhiMc"][iTrack];}

  int GetMatchedMcNHit(int iTrack){ return track_int_map_["mMatchedPairs.mNHitMc"][iTrack];}
  int GetMatchedGeantId(int iTrack){ return track_int_map_["mMatchedPairs.mGeantId"][iTrack];}
  int GetMatchedPdgId(int iTrack){ return track_int_map_["mMatchedPairs.mPdgId"][iTrack];}
  int GetMatchedMcCharge(int iTrack){ return track_int_map_["mMatchedPairs.mChargeMc"][iTrack];}
  int GetMatchedParentGeantId(int iTrack){ return track_int_map_["mMatchedPairs.mParentGeantId"][iTrack];}
  int GetMatchedIsPrimary(int iTrack){ return track_int_map_["mMatchedPairs.mIsPrimary"][iTrack];}
  int GetMatchedIsDca(int iTrack){ return track_int_map_["mMatchedPairs.mIsDca"][iTrack];}
  
  float GetMatchedPt(int iTrack){ return track_float_map_["mMatchedPairs.mPtPr"][iTrack];}
  float GetMatchedPz(int iTrack){ return track_float_map_["mMatchedPairs.mPzPr"][iTrack];}
  float GetMatchedEta(int iTrack){ return track_float_map_["mMatchedPairs.mEtaPr"][iTrack];}
  float GetMatchedPhi(int iTrack){ return track_float_map_["mMatchedPairs.mPhiPr"][iTrack];}
  float GetMatchedDca(int iTrack){ return track_float_map_["mMatchedPairs.mDcaPr"][iTrack];}
  float GetMatchedDcaXY(int iTrack){ return track_float_map_["mMatchedPairs.mDcaXYPr"][iTrack];}
  float GetMatchedDcaZ(int iTrack){ return track_float_map_["mMatchedPairs.mDcaZPr"][iTrack];}

  ClassDef( MiniMcReader, 1);
  
};

#endif
