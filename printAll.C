

void printAll()
{

  TFile * f = new TFile("embed/st_physics_adc_19151034_raw_1500002.minimc.root","read");
  TTree* tree = (TTree*) f->Get("StMiniMcTree");
  tree->Print();
  
}
