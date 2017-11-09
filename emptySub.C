{
  const TString crName[8] = {"ALAINA","SUSAN","BROOKE","ROBERTA","LINDA","JONI","CINDY","KRISTA"};//DON'T CHANGE THE SEQUENCE!!! IT MATCHES THE CONFIGURATION IN GEMC _GEOMETRY.PL

  TFile *ffull = new TFile("results/GEMC_1GeV_5e10_crTrg_LHe_cryo_kapton.root");
  TFile *fempty = new TFile("results/GEMC_1GeV_5e10_crTrg_LHe_cryo_kapton_empty.root");

  TH1F *hEcr_shldTofCut[8],*hEcr_shldTofCut_empty[8];
  TH1F *hEcr_shldTofCut_wide[8],*hEcr_shldTofCut_wide_empty[8];


  TFile *fnet = new TFile("GEMC_1GeV_5e10_crTrg_LHe_cryo_kapton_NET.root","recreate");
  for(int i=0; i<8; i++){
    hEcr_shldTofCut[i] = (TH1F*)ffull->Get("hEcr_shldTofCut_"+crName[i]);
    hEcr_shldTofCut_wide[i] = (TH1F*)ffull->Get("hEcr_shldTofCut_wide_"+crName[i]);
    hEcr_shldTofCut_empty[i] = (TH1F*)fempty->Get("hEcr_shldTofCut_"+crName[i]);
    hEcr_shldTofCut_wide_empty[i] = (TH1F*)fempty->Get("hEcr_shldTofCut_wide_"+crName[i]);


    hEcr_shldTofCut[i]->Add(hEcr_shldTofCut_empty[i], -1.0);
    hEcr_shldTofCut_wide[i]->Add(hEcr_shldTofCut_wide_empty[i], -1.0);


    hEcr_shldTofCut[i]->Write();
    hEcr_shldTofCut_wide[i]->Write();



  }




















}
