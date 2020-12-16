#include "process_embedding.h"
#include "minimc_reader.h"
#include "TFile.h"
#include "TString.h"
#include "TH3D.h"
#include <iostream>

using namespace std;

int RunEmbedding(TString file_list,TString jobid)
{
  
  MiniMcReader * mc_reader = new MiniMcReader( file_list );
  EmbeddingProcessor * embed_proc = new EmbeddingProcessor( mc_reader );

  //Set FxtMult3 conditions
  embed_proc->SetFxt3_NHitsFit( 10 );
  embed_proc->SetFxt3_Dca( 3.0 );
  
  //Set Analysis Proton conditions
  embed_proc->SetNHitsFit( 10 );
  embed_proc->SetDca( 3.0 );

  embed_proc->Run();

  TH2D * matched_hist = embed_proc->GetMatchedHistogram();
  TH2D * mc_hist      = embed_proc->GetMCHistogram();

  TString outfilename = TString::Format("embed_%s.root",jobid.Data());
  cout << "Outfile = " << outfilename << endl;
  TFile * outfile = new TFile( outfilename , "RECREATE" );
  matched_hist->Write();
  mc_hist->Write();
  outfile->Close();

}
