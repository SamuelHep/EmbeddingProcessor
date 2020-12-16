


void RunEmbeddingCondor(TString filelist,TString jobid)
{

  gSystem->Load("embeddingCode.so");
  RunEmbedding( filelist, jobid );

}
