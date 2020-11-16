




EmbeddingProcessor::EmbeddingProccessor(MiniMcReader * minimc_reader)
{
  minimc_reader_  = minimc_reader;
  matched_hist = TH3D("efficiency_hist","",120,0,120,100,0,2,110,0,2.2); // Mult, y, pt
  mc_hist      = TH3D("efficiency_hist","",120,0,120,100,0,2,110,0,2.2); // Mult, y, pt

  vertexR_min_max_ = make_pair<double,double>(0,3);
  vertexZ_min_max_ = make_pair<double,double>(199,202);
  beamSpot_X_Y_    = make_pair<double,double>(-2,0);
}

EmbeddingProcessor::Run()
{
  for (int i_entry; i_entry<minimc_reader_->NEntries(); i_entry++)
    {
      minimc_reader_->GetEntry(i_entry);

      //Determine Multiplicity
      int fxtmult3=0;
      for ( int i_track=0;i_track<minimc_reader_->GetNMatchedPair();i_track++)
	{
	  fxtmult3 += CheckIfGoodTrack(mini_mc_reader_);
	}
	      
    }
  
}

int EmbeddingProcessor::CheckIfGoodTrack(MiniMcReader * minimc_reader)
{
  int nhits_fit = minimc_reader->Get
}

