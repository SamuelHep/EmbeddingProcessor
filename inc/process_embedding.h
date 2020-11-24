#ifndef EMBEDDING_PROCESSOR_H_
#define EMBEDDING_PROCESSOR_H_

#include <utility>
#include "TH2D.h"
#include "minimc_reader.h"

class EmbeddingProcessor : public TObject {

 private:
  
  MiniMcReader * minimc_reader_;
  TH2D * matched_hist_;
  TH2D * mc_hist_;

  std::pair<double,double> vertexR_min_max_;
  std::pair<double,double> vertexZ_min_max_;
  std::pair<double,double> beamSpot_X_Y_;

  int fxt3_nhitsfit_min_;
  double fxt3_dca_max_;

  int nhitsfit_min_;
  double dca_max_;

  double proton_mass;
  static const int kProtonPid = 14;

  int CheckIfGoodMatchedTrack(MiniMcReader * minimc_reader,int itrack);
  int CheckIfGoodFxtMult3Track(MiniMcReader * minimc_reader,int itrack);
  

 public:

  EmbeddingProcessor(MiniMcReader * minimc_reader);
  ~EmbeddingProcessor(){};
  
  int Run();

  //Sets
  void SetFxt3_NHitsFit(int val){ fxt3_nhitsfit_min_ = val; }
  void SetFxt3_Dca(double val){fxt3_dca_max_ = val;}

  void SetNHitsFit(int val){ nhitsfit_min_ = val; }
  void SetDca(double val){dca_max_ = val;}

  //Gets
  TH2D * GetMatchedHistogram(){return matched_hist_;}
  TH2D * GetMCHistogram(){return mc_hist_;}
  

  ClassDef( EmbeddingProcessor, 1 );

};

#endif 
