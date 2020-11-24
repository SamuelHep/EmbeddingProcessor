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
  
  void InitBranchVectors(int max_entries);
  TChain * InitChain( TString filelist, TString tree_name );
  void SetBranchStatus(TString branch_name, Int_t active);
  
  std::vector<TString> branch_names_;

  //Event Variables
  short mEventId;
  short mRunId;
  short mOriginMult;
  short mCentralMult;
  short mCentrality;
  short mMcMult;
  
  double mVertexX;
  double mVertexY;
  double mVertexZ;
  double mMcVertexX;
  double mMcVertexY;
  double mMcVertexZ;
  double mMagField;

  short mNMcTrack;
  short mNMatchedPair;
  short mNMergedPair;
  short mNSplitPair;
  short mNGhostPair;
  short mNContamPair;
  short mNMatGlobPair;

  //Track Variables
  std::vector<float> mMcPt;
  std::vector<float> mMcPz;
  std::vector<float> mMcEta;
  std::vector<float> mMcPhi;
  std::vector<float> mMcNHit;

  std::vector<unsigned short> mMcGeantId;
  std::vector<short> mMcCharge;
  std::vector<unsigned short> mMcParentGeantId;

  std::vector<float> mMatchedPt;
  std::vector<float> mMatchedPz;
  std::vector<float> mMatchedEta;
  std::vector<float> mMatchedPhi;
  std::vector<short> mMatchedNHit;
  std::vector<short> mMatchedNPoss;

  std::vector<unsigned short> mMatchedGeantId;
  std::vector<short> mMatchedCharge;
  std::vector<unsigned short> mMatchedParentGeantId;

  std::vector<float> mMatchedPtPr;
  std::vector<float> mMatchedPzPr;
  std::vector<float> mMatchedEtaPr;
  std::vector<float> mMatchedPhiPr;
  std::vector<float> mMatchedDcaPr;
  std::vector<float> mMatchedDcaXYPr;
  std::vector<float> mMatchedDcaZPr;
  
 public:

  MiniMcReader(TString filelist);
  ~MiniMcReader();

  void GetEntry(int iEntry){ tchain_->GetEntry(iEntry);}
  int NEntries(){ return tchain_->GetEntries();}
  
  //Get Methods... How to reader the event
  short GetEventId(){ return mEventId; }
  short GetRunId(){ return mRunId; }
  short GetOrigin(){ return mOriginMult; }
  short GetCentralMult(){ return mCentralMult; }
  short GetCentrality(){ return mCentrality; }
  short GetMcMult(){ return mMcMult; }
  
  float GetVertexX(){ return mVertexX; }
  float GetVertexY(){ return mVertexY; }
  float GetVertexZ(){ return mVertexZ; }
  
  float GetMcVertexX(){ return mMcVertexX; }
  float GetMcVertexY(){ return mMcVertexY; }
  float GetMcVertexZ(){ return mMcVertexZ; }
  float GetMagField(){ return mMagField; }
  
  short GetNMcTrack(){ return mNMcTrack; } 
  short GetNMatchedPair(){ return mNMatchedPair; }
  
  float GetMcPt(int i){return mMcPt[i];}
  float GetMcPz(int i){return mMcPz[i];}
  float GetMcEta(int i){return mMcEta[i];}
  float GetMcPhi(int i){return mMcPhi[i];}
  short GetMcNHit(int i){return mMcNHit[i];}

  unsigned short GetMcGeantId(int i){return mMcGeantId[i];}
  short GetMcCharge(int i){return mMcCharge[i];}
  unsigned short GetMcParentGeantId(int i){return mMcParentGeantId[i];}

  float GetMatchedPt(int i){return mMatchedPt[i];}
  float GetMatchedPz(int i){return mMatchedPz[i];}
  float GetMatchedEta(int i){return mMatchedEta[i];}
  float GetMatchedPhi(int i){return mMatchedPhi[i];}
  short GetMatchedNHit(int i){return mMatchedNHit[i];}
  short GetMatchedNPoss(int i){return mMatchedNPoss[i];}

  unsigned short GetMatchedGeantId(int i){return mMatchedGeantId[i];}
  short GetMatchedCharge(int i){return mMatchedCharge[i];}
  unsigned short GetMatchedParentGeantId(int i){return mMatchedParentGeantId[i];}

  float GetMatchedPtPr(int i){return mMatchedPtPr[i];}
  float GetMatchedPzPr(int i){return mMatchedPzPr[i];}
  float GetMatchedEtaPr(int i){return mMatchedEtaPr[i];}
  float GetMatchedPhiPr(int i){return mMatchedPhiPr[i];}
  float GetMatchedDcaPr(int i){return mMatchedDcaPr[i];}
  float GetMatchedDcaXYPr(int i){return mMatchedDcaXYPr[i];}
  float GetMatchedDcaZPr(int i){return mMatchedDcaZPr[i];}

  ClassDef( MiniMcReader, 1);
  
};

#endif
