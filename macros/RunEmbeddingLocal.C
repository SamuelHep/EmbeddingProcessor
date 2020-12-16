


void RunEmbeddingLocal(TString filelist, TString jobid)
{
  cout << "hi" << endl;

  gSystem->Load("../lib/embeddingCode.so");
  RunEmbedding( filelist, jobid );

}
