#include <iostream> 
#include <fstream>
#include <cmath> 
#include "math.h" 
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMinuit.h"
#include "TPaveText.h"
#include "TText.h"
#include "TSystem.h"
#include "TArc.h"
#include "TString.h"
#include <vector>
#include "TRandom3.h"
#include "TGraphErrors.h"
#include "TString.h"
#include "TFile.h"

using namespace std;

void analysis_pid(string input_filename)
{
  gROOT->Reset();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1111111);

  const double DEG=180./3.1415926;

  string filemode;
  double event_actual=1;
  if(input_filename.find("BeamOnTarget",0) != string::npos) {
    filemode="BeamOnTarget";
    cout << "this is a BeamOnTarget file" << endl;  
  
    //  event_actual=atof(input_filename.substr(input_filename.find("BeamOnTarget",0)+13,input_filename.find("_")).c_str());
    //  cout << "event_actual " << event_actual <<  endl;  
  }
  else {
    cout << "this is not a BeamOnTarget file" << endl;  
    return;
  }

  char the_filename[200];
  sprintf(the_filename, "%s",input_filename.substr(0,input_filename.rfind(".")).c_str());


  TH1F *htotEdep[8][3];
  for(int i=0;i<8;i++){
    for(int j=0;j<3;j++){
      char hstname[100];
      sprintf(hstname,"totEdep_%i_%i",i,j);
      htotEdep[i][j]=new TH1F(hstname,hstname,100,0,10);
    }
  }

  string crName[8] = {"ALAINA","SUSAN","BROOKE","ROBERTA","LINDA","JONI","CINDY","KRISTA"};//DON'T CHANGE THE SEQUENCE!!! IT MATCHES THE CONFIGURATION IN GEMC _GEOMETRY.PL

  Double_t Emax = 500;
  Double_t Tmax = 300;
  Int_t nE = (Int_t)Emax*1;
  Int_t nT = (Int_t)Tmax*1;

  TH1F *hEcr[8];
  for(int i=0; i<8; i++)
    hEcr[i] = new TH1F(Form("hEcr_%s",crName[i].c_str()),Form("hEcr_%s",crName[i].c_str()),nE,0,Emax);
    // hEcr[i] = new TH1F(crName[i].c_str(),crName[i].c_str(),1000,0,1000);
  TH1F *hEcr_shldcut[8];
  for(int i=0; i<8; i++)
    hEcr_shldcut[i] = new TH1F(Form("hEcr_shldCut_%s",crName[i].c_str()),Form("hEcr_shldCut_%s",crName[i].c_str()),nE,0,Emax);
    // hEcr_shldcut[i] = new TH1F(crName[i].c_str(),crName[i].c_str(),nE,0,1000);
  TH1F *hEcr_shldTOFcut[8];
  for(int i=0; i<8; i++)
    hEcr_shldTOFcut[i] = new TH1F(Form("hEcr_shldTofCut_%s",crName[i].c_str()),Form("hEcr_shldTofCut_%s",crName[i].c_str()),nE,0,Emax);
  TH1F *hEcr_shldTOFcut_wide[8];
  for(int i=0; i<8; i++)
    hEcr_shldTOFcut_wide[i] = new TH1F(Form("hEcr_shldTofCut_wide_%s",crName[i].c_str()),Form("hEcr_shldTofCut_wide_%s",crName[i].c_str()),nE,0,Emax);
  TH1F *hEcr_gamma[8];
  for(int i=0; i<8; i++)
    hEcr_gamma[i] = new TH1F(Form("hEcr_g_%s",crName[i].c_str()),Form("hEcr_g_%s",crName[i].c_str()),nE,0,Emax);
  TH1F *hTOFcr[8];
  for(int i=0; i<8; i++)
    hTOFcr[i] = new TH1F(Form("hTOFcr_%s",crName[i].c_str()),Form("hTOFcr_%s",crName[i].c_str()),nT,0,Tmax);
  TH1F *hTOFcr_gamma[8];
  for(int i=0; i<8; i++)
    hTOFcr_gamma[i] = new TH1F(Form("hTOFcr_g_%s",crName[i].c_str()),Form("hTOFcr_g_%s",crName[i].c_str()),nT,0,Tmax);
  TH2F *hTOF_Ecr[8];
  for(int i=0; i<8; i++)
    hTOF_Ecr[i] = new TH2F(Form("h2D_%s",crName[i].c_str()),Form("h2D_%s",crName[i].c_str()),nT,0,Tmax,nE,0,Emax);



  TFile *file=new TFile(input_filename.c_str());
  if (file->IsZombie()) {
    cout << "Error opening file" << input_filename << endl;
    exit(-1);
  }
  else cout << "open file " << input_filename << endl;    


  TTree *tree_header = (TTree*) file->Get("header");
  vector <int> *evn=0,*evn_type=0;
  vector <double> *beamPol=0;
  vector <int> *var1=0,*var2=0,*var3=0,*var4=0,*var5=0,*var6=0,*var7=0,*var8=0;
  tree_header->SetBranchAddress("evn",&evn);
  tree_header->SetBranchAddress("evn_type",&evn_type);
  tree_header->SetBranchAddress("beamPol",&beamPol);
  tree_header->SetBranchAddress("var1",&var1);
  tree_header->SetBranchAddress("var2",&var2);
  tree_header->SetBranchAddress("var3",&var3);
  tree_header->SetBranchAddress("var4",&var4);
  tree_header->SetBranchAddress("var5",&var5);
  tree_header->SetBranchAddress("var6",&var6);
  tree_header->SetBranchAddress("var7",&var7);
  tree_header->SetBranchAddress("var8",&var8);

  TTree *tree_generated = (TTree*) file->Get("generated");
  vector <int> *gen_pid=0;
  vector <double> *gen_px=0,*gen_py=0,*gen_pz=0,*gen_vx=0,*gen_vy=0,*gen_vz=0;
  tree_generated->SetBranchAddress("pid",&gen_pid);
  tree_generated->SetBranchAddress("px",&gen_px);
  tree_generated->SetBranchAddress("py",&gen_py);
  tree_generated->SetBranchAddress("pz",&gen_pz);
  tree_generated->SetBranchAddress("vx",&gen_vx);
  tree_generated->SetBranchAddress("vy",&gen_vy);
  tree_generated->SetBranchAddress("vz",&gen_vz);

  TTree *tree_flux = (TTree*) file->Get("flux");
  vector<int> *flux_id=0,*flux_hitn=0;
  vector<int> *flux_pid=0,*flux_mpid=0,*flux_tid=0,*flux_mtid=0,*flux_otid=0;
  vector<double> *flux_trackE=0,*flux_totEdep=0,*flux_avg_x=0,*flux_avg_y=0,*flux_avg_z=0,*flux_avg_lx=0,*flux_avg_ly=0,*flux_avg_lz=0,*flux_px=0,*flux_py=0,*flux_pz=0,*flux_vx=0,*flux_vy=0,*flux_vz=0,*flux_mvx=0,*flux_mvy=0,*flux_mvz=0,*flux_avg_t=0;
  tree_flux->SetBranchAddress("hitn",&flux_hitn);
  tree_flux->SetBranchAddress("id",&flux_id);
  tree_flux->SetBranchAddress("pid",&flux_pid);
  tree_flux->SetBranchAddress("mpid",&flux_mpid);
  tree_flux->SetBranchAddress("tid",&flux_tid);
  tree_flux->SetBranchAddress("mtid",&flux_mtid);
  tree_flux->SetBranchAddress("otid",&flux_otid);
  tree_flux->SetBranchAddress("trackE",&flux_trackE);
  tree_flux->SetBranchAddress("totEdep",&flux_totEdep);
  tree_flux->SetBranchAddress("avg_x",&flux_avg_x);
  tree_flux->SetBranchAddress("avg_y",&flux_avg_y);
  tree_flux->SetBranchAddress("avg_z",&flux_avg_z);
  tree_flux->SetBranchAddress("avg_lx",&flux_avg_lx);
  tree_flux->SetBranchAddress("avg_ly",&flux_avg_ly);
  tree_flux->SetBranchAddress("avg_lz",&flux_avg_lz);
  tree_flux->SetBranchAddress("px",&flux_px);
  tree_flux->SetBranchAddress("py",&flux_py);
  tree_flux->SetBranchAddress("pz",&flux_pz);
  tree_flux->SetBranchAddress("vx",&flux_vx);
  tree_flux->SetBranchAddress("vy",&flux_vy);
  tree_flux->SetBranchAddress("vz",&flux_vz);
  tree_flux->SetBranchAddress("mvx",&flux_mvx);
  tree_flux->SetBranchAddress("mvy",&flux_mvy);
  tree_flux->SetBranchAddress("mvz",&flux_mvz);
  tree_flux->SetBranchAddress("avg_t",&flux_avg_t);


  double ftotE[8][3];
  int fPID[8][3];
  double fTOF[8][3];

  int nevent = (int)tree_generated->GetEntries();
  int nselected = 0;
  cout << "nevent " << nevent << endl;

  for (Int_t i=0; i<nevent; i++) { 
    if(i%10000 == 0) cout<<i<<endl;

    for(int l=0;l<8;l++)
      for(int k=0;k<3;k++){
	ftotE[l][k] = 0.0;
	fPID[l][k] = 0;
	fTOF[l][k] = 0.0;
      }

    tree_generated->GetEntry(i);
    double Eprim = gen_pz->at(0);

    tree_flux->GetEntry(i);    
    for (Int_t j=0;j<flux_hitn->size();j++) {
      int detector_ID=flux_id->at(j)/10;
      int subdetector_ID=flux_id->at(j)%10; //pad=0, core=1, shield=2
      ftotE[detector_ID-1][subdetector_ID] += flux_totEdep->at(j);

      if(fPID[detector_ID-1][subdetector_ID] == 0)
	fPID[detector_ID-1][subdetector_ID] = flux_pid->at(j);
      if(fTOF[detector_ID-1][subdetector_ID] == 0)
      	fTOF[detector_ID-1][subdetector_ID] = flux_avg_t->at(j);
      
    }

    for(int j=0; j<8; j++){
      if(ftotE[j][1]>0){ //Ecore>0
	hEcr[j]->Fill(ftotE[j][1]);
	if(ftotE[j][2]>0 && ftotE[j][2]<15){ //shield cut
	  hEcr_shldcut[j]->Fill(ftotE[j][1]);
	  hTOFcr[j]->Fill(fTOF[j][1]);
	  hTOF_Ecr[j]->Fill(fTOF[j][1], ftotE[j][1]);

	  if(fPID[j][1]== 22){ //select gamma in core
	    hEcr_gamma[j]->Fill(ftotE[j][1]);
	    hTOFcr_gamma[j]->Fill(fTOF[j][1]);
	  }

	  if(fTOF[j][1]>5 && fTOF[j][1]<8)//TOF cut 3ns
	    hEcr_shldTOFcut[j]->Fill(ftotE[j][1]);
	  if(fTOF[j][1]>5 && fTOF[j][1]<15)//TOF cut 10ns
	    hEcr_shldTOFcut_wide[j]->Fill(ftotE[j][1]);

	}


	// hEprim_Edep[j]->Fill(ftotE[j][1],Eprim);
	// hEshld_Ecr[j]->Fill(ftotE[j][1],ftotE[j][2]);

	// if(j==0 || j==1 || j==5 || j==6){
	//   hPID_Ecr[j]->Fill(ftotE[j][1],fPID[j][0]);
	//   hdE_Edep[j]->Fill(ftotE[j][1],ftotE[j][0]);
		    
	//   if(fPID[j][0]== 2212){
	//     hEcr_proton[j]->Fill(ftotE[j][1]);
	//     hdE_Edep_proton[j]->Fill(ftotE[j][1],ftotE[j][0]);
	//   }
	//   if(fPID[j][0]== 2112){
	//     hEcr_neutron[j]->Fill(ftotE[j][1]);
	//     hdE_Edep_neutron[j]->Fill(ftotE[j][1],ftotE[j][0]);
	//   }
	//   if(fPID[j][0]== 22){
	//     hEcr_gamma[j]->Fill(ftotE[j][1]);
	//     hdE_Edep_gamma[j]->Fill(ftotE[j][1],ftotE[j][0]);
	//   }
	//   if(fPID[j][0]== 11){
	//     hEcr_electron[j]->Fill(ftotE[j][1]);
	//     hdE_Edep_electron[j]->Fill(ftotE[j][1],ftotE[j][0]);
	//   }
	//   if(fPID[j][0]== -11){
	//     hEcr_positron[j]->Fill(ftotE[j][1]);
	//     hdE_Edep_positron[j]->Fill(ftotE[j][1],ftotE[j][0]);
	//   }
	//   if(fPID[j][0]== 211){
	//     hEcr_piplus[j]->Fill(ftotE[j][1]);
	//     hdE_Edep_piplus[j]->Fill(ftotE[j][1],ftotE[j][0]);
	//   }
	//   if(fPID[j][0]== -211){
	//     hEcr_piminus[j]->Fill(ftotE[j][1]);
	//     hdE_Edep_piminus[j]->Fill(ftotE[j][1],ftotE[j][0]);
	//   }
	  
	//   if(fPID[j][0]== 12)
	//     hEcr_nue[j]->Fill(ftotE[j][1]);
	//   if(fPID[j][0]== -12)
	//     hEcr_antinue[j]->Fill(ftotE[j][1]);
	//   if(fPID[j][0]== 13)
	//     hEcr_muon[j]->Fill(ftotE[j][1]);
	//   if(fPID[j][0]== -13)
	//     hEcr_antimuon[j]->Fill(ftotE[j][1]);
	//   if(fPID[j][0]== 14)
	//     hEcr_numu[j]->Fill(ftotE[j][1]);
	//   if(fPID[j][0]== -14)
	//     hEcr_antinumu[j]->Fill(ftotE[j][1]);
	// }//if paddle



      }//if Ecore>0
    }//loop over HINDA
  }//loop over events

  // cout<< hEcr[0]->Integral(100,500)<<endl;
  // cout<< hEcr_shldcut[0]->Integral(100,500)<<endl;

  // TCanvas *c1 = new TCanvas("c1","c1");
  // hdE_Edep[0]->Draw("colz");
  // TCanvas *c2 = new TCanvas("c2","c2");
  // hEprim_Edep[0]->Draw("colz");



  TCanvas *c1 = new TCanvas("cE","Ecore");
  TCanvas *c2 = new TCanvas("cTOF","TOF");
  TCanvas *c3 = new TCanvas("c2D","TOF vs Ecore");
  // hEprim_Edep[0]->Draw("colz");
  // hEcr[0]->SetLineColor(kBlack);
  // hEcr[0]->Draw();
  // hEcr_shldcut[0]->SetLineColor(kRed);
  // hEcr_shldcut[0]->Draw("same");

  c1->Divide(4,2);
  c2->Divide(4,2);
  c3->Divide(4,2);
  for(int i=0; i<8; i++){
    c1->cd(i+1);
    hEcr[i]->GetXaxis()->SetTitle("E [MeV]");
    hEcr[i]->GetXaxis()->SetTitleSize(0.045);
    hEcr[i]->GetXaxis()->SetLabelSize(0.045);
    hEcr[i]->GetYaxis()->SetTitle("counts / MeV");
    hEcr[i]->GetYaxis()->SetTitleSize(0.045);
    hEcr[i]->GetYaxis()->SetLabelSize(0.045);
    hEcr[i]->GetXaxis()->CenterTitle();
    hEcr[i]->GetYaxis()->CenterTitle();
    hEcr[i]->SetLineColor(kBlack);
    // hEcr[i]->Rebin(2);
    hEcr[i]->Draw();
    hEcr_shldcut[i]->SetLineColor(kRed);
    hEcr_shldcut[i]->Draw("same");  
    // hEcr_gamma[i]->SetLineColor(kGreen+1);
    // hEcr_gamma[i]->Draw("same");
    hEcr_shldTOFcut[i]->SetLineColor(kBlue);
    hEcr_shldTOFcut[i]->Draw("same");
    hEcr_shldTOFcut_wide[i]->SetLineColor(kGreen);
    hEcr_shldTOFcut_wide[i]->Draw("same");

    c2->cd(i+1);
    hTOFcr[i]->GetXaxis()->SetTitle("TOF");
    hTOFcr[i]->GetXaxis()->SetTitleSize(0.045);
    hTOFcr[i]->GetXaxis()->SetLabelSize(0.045);
    hTOFcr[i]->GetYaxis()->SetTitle("counts / MeV");
    hTOFcr[i]->GetYaxis()->SetTitleSize(0.045);
    hTOFcr[i]->GetYaxis()->SetLabelSize(0.045);
    hTOFcr[i]->GetXaxis()->CenterTitle();
    hTOFcr[i]->GetYaxis()->CenterTitle();
    hTOFcr[i]->SetLineColor(kBlack);
    hTOFcr[i]->Draw();
    hTOFcr_gamma[i]->SetLineColor(kRed);
    hTOFcr_gamma[i]->Draw("same");

    c3->cd(i+1);
    hTOF_Ecr[i]->GetXaxis()->SetTitle("TOF");
    hTOF_Ecr[i]->GetXaxis()->SetTitleSize(0.045);
    hTOF_Ecr[i]->GetXaxis()->SetLabelSize(0.045);
    hTOF_Ecr[i]->GetYaxis()->SetTitle("E [MeV]");
    hTOF_Ecr[i]->GetYaxis()->SetTitleSize(0.045);
    hTOF_Ecr[i]->GetYaxis()->SetLabelSize(0.045);
    hTOF_Ecr[i]->GetXaxis()->CenterTitle();
    hTOF_Ecr[i]->GetYaxis()->CenterTitle();
    hTOF_Ecr[i]->Draw("colz");
   }
  // TLegend *leg =new TLegend(0.65,0.35,0.9,0.9);
  // leg->AddEntry(hEcr[0],"all particles");
  // leg->AddEntry(hEcr_gamma[0],"gamma");
  // leg->AddEntry(hEcr_proton[0],"proton");
  // leg->AddEntry(hEcr_neutron[0],"neutron");
  // leg->AddEntry(hEcr_electron[0],"e-");
  // leg->AddEntry(hEcr_positron[0],"e+");
  // leg->AddEntry(hEcr_piplus[0],"pi+");
  // leg->AddEntry(hEcr_piminus[0],"pi-");
  // // leg->AddEntry(hEcr_nue[0],"nu_e");
  // // leg->AddEntry(hEcr_antinue[0],"anti-nu_e");
  // // leg->AddEntry(hEcr_muon[0],"mu-");
  // // leg->AddEntry(hEcr_antimuon[0],"mu+");
  // // leg->AddEntry(hEcr_numu[0],"nu_mu");
  // // leg->AddEntry(hEcr_antinumu[0],"anti-nu_mu");
  // leg->SetFillColor(0);
  // leg->Draw();


  // TCanvas *c2 = new TCanvas("c2","c2");
  // c2->Divide(4,2);
  // for(int i=0; i<8; i++){
  //   c2->cd(i+1);
  //   hEprim_Edep[i]->Draw("colz");
  //   // hdE_Edep[i]->Draw("colz");
  //   // hPID_Ecr[i]->Draw("colz");
  // }


  TFile *outf = new TFile("results/GEMC_1GeV_5e10_crTrg_LHe_cryo_kapton_empty.root","recreate");
  for(int i=0; i<8; i++){
    hEcr[i]->Write();
    hEcr_shldcut[i]->Write();
    hEcr_shldTOFcut[i]->Write();
    hEcr_shldTOFcut_wide[i]->Write();
    hEcr_gamma[i]->Write();
    hTOFcr[i]->Write();
    hTOFcr_gamma[i]->Write();
    hTOF_Ecr[i]->Write();
  }
  c1->Write();
  c2->Write();
  c3->Write();
  outf->Close();

}



//********* other hists ****************************
  // TH1F *hEcr_proton[8];
  // for(int i=0; i<8; i++)
  //   hEcr_proton[i] = new TH1F(Form("hEcr_p_%d",i),Form("hEcr_p_%d",i),1000,0,1000);
  // TH1F *hEcr_neutron[8];
  // for(int i=0; i<8; i++)
  //   hEcr_neutron[i] = new TH1F(Form("hEcr_n_%d",i),Form("hEcr_n_%d",i),1000,0,1000);
  // TH1F *hEcr_electron[8];
  // for(int i=0; i<8; i++)
  //   hEcr_electron[i] = new TH1F(Form("hEcr_electron_%d",i),Form("hEcr_e-_%d",i),1000,0,1000);
  // TH1F *hEcr_positron[8];
  // for(int i=0; i<8; i++)
  //   hEcr_positron[i] = new TH1F(Form("hEcr_positron_%d",i),Form("hEcr_e+_%d",i),1000,0,1000);
  // TH1F *hEcr_muon[8];
  // for(int i=0; i<8; i++)
  //   hEcr_muon[i] = new TH1F(Form("hEcr_muon_%d",i),Form("hEcr_mu-_%d",i),1000,0,1000);
  // TH1F *hEcr_antimuon[8];
  // for(int i=0; i<8; i++)
  //   hEcr_antimuon[i] = new TH1F(Form("hEcr_anti_muon_%d",i),Form("hEcr_mu+_%d",i),1000,0,1000);
  // TH1F *hEcr_nue[8];
  // for(int i=0; i<8; i++)
  //   hEcr_nue[i] = new TH1F(Form("hEcr_nu_e_%d",i),Form("hEcr_nu_e_%d",i),1000,0,1000);
  // TH1F *hEcr_antinue[8];
  // for(int i=0; i<8; i++)
  //   hEcr_antinue[i] = new TH1F(Form("hEcr_anti_nu_e_%d",i),Form("hEcr_anti_nu_e_%d",i),1000,0,1000);
  // TH1F *hEcr_numu[8];
  // for(int i=0; i<8; i++)
  //   hEcr_numu[i] = new TH1F(Form("hEcr_nu_mu_%d",i),Form("hEcr_nu_mu_%d",i),1000,0,1000);
  // TH1F *hEcr_antinumu[8];
  // for(int i=0; i<8; i++)
  //   hEcr_antinumu[i] = new TH1F(Form("hEcr_anti_nu_mu_%d",i),Form("hEcr_anti_nu_mu_%d",i),1000,0,1000);
  // TH1F *hEcr_piplus[8];
  // for(int i=0; i<8; i++)
  //   hEcr_piplus[i] = new TH1F(Form("hEcr_piplus_%d",i),Form("hEcr_pi+_%d",i),1000,0,1000);
  // TH1F *hEcr_piminus[8];
  // for(int i=0; i<8; i++)
  //   hEcr_piminus[i] = new TH1F(Form("hEcr_piminus_%d",i),Form("hEcr_pi-_%d",i),1000,0,1000);
  // TH1F *hEcr_kaonplus[8];
  // for(int i=0; i<8; i++)
  //   hEcr_kaonplus[i] = new TH1F(Form("hEcr_Kplus_%d",i),Form("hEcr_K+_%d",i),1000,0,1000);
  // TH1F *hEcr_kaonminus[8];
  // for(int i=0; i<8; i++)
  //   hEcr_kaonminus[i] = new TH1F(Form("hEcr_Kminus_%d",i),Form("hEcr_K-_%d",i),1000,0,1000);
  // TH1F *hEcr_kaonlong[8];
  // for(int i=0; i<8; i++)
  //   hEcr_kaonlong[i] = new TH1F(Form("hEcr_K0l_%d",i),Form("hEcr_K0l_%d",i),1000,0,1000);

  // TH2F *hdE_Edep[8];
  // for(int i=0; i<8; i++)
  //   hdE_Edep[i] = new TH2F(Form("h2D_%d",i),Form("h2D_%d",i),500,0,500,500,0,5);
  // TH2F *hdE_Edep_proton[8];
  // for(int i=0; i<8; i++)
  //   hdE_Edep_proton[i] = new TH2F(Form("h2D_p_%d",i),Form("h2D_p_%d",i),500,0,500,500,0,5);
  // TH2F *hdE_Edep_neutron[8];
  // for(int i=0; i<8; i++)
  //   hdE_Edep_neutron[i] = new TH2F(Form("h2D_n_%d",i),Form("h2D_n_%d",i),500,0,500,500,0,5);
  // TH2F *hdE_Edep_gamma[8];
  // for(int i=0; i<8; i++)
  //   hdE_Edep_gamma[i] = new TH2F(Form("h2D_g_%d",i),Form("h2D_g_%d",i),500,0,500,500,0,5);
  // TH2F *hdE_Edep_electron[8];
  // for(int i=0; i<8; i++)
  //   hdE_Edep_electron[i] = new TH2F(Form("h2D_electron_%d",i),Form("h2D_e-_%d",i),500,0,500,500,0,5);
  // TH2F *hdE_Edep_positron[8];
  // for(int i=0; i<8; i++)
  //   hdE_Edep_positron[i] = new TH2F(Form("h2D_positron_%d",i),Form("h2D_e+_%d",i),500,0,500,500,0,5);
  // TH2F *hdE_Edep_piplus[8];
  // for(int i=0; i<8; i++)
  //   hdE_Edep_piplus[i] = new TH2F(Form("h2D_piplus_%d",i),Form("h2D_pi+_%d",i),500,0,500,500,0,5);
  // TH2F *hdE_Edep_piminus[8];
  // for(int i=0; i<8; i++)
  //   hdE_Edep_piminus[i] = new TH2F(Form("h2D_piminus_%d",i),Form("h2D_pi-_%d",i),500,0,500,500,0,5);

  // TH2F *hPID_Ecr[8];
  // for(int i=0; i<8; i++)
  //   hPID_Ecr[i] = new TH2F(Form("hpid_%d",i),Form("hpid_%d",i),500,0,500,6000,-3000,3000);
  // TH2F *hEprim_Edep[8];
  // for(int i=0; i<8; i++)
  //   hEprim_Edep[i] = new TH2F(Form("hEprim_%d",i),Form("hprim_%d",i),500,0,500,2000,0,2000);
  // TH2F *hEshld_Ecr[8];
  // for(int i=0; i<8; i++)
  //   hEshld_Ecr[i] = new TH2F(Form("hEshld_%d",i),Form("hEshld_%d",i),500,0,500,500,0,100);






    // hEcr_proton[i]->Write();
    // hEcr_neutron[i]->Write();
    // hEcr_electron[i]->Write();
    // hEcr_positron[i]->Write();
    // hEcr_piplus[i]->Write();
    // hEcr_piminus[i]->Write();
    // hEcr_nue[i]->Write();
    // hEcr_antinue[i]->Write();
    // hEcr_muon[i]->Write();
    // hEcr_antimuon[i]->Write();
    // hEcr_numu[i]->Write();
    // hEcr_antinumu[i]->Write();
    // hdE_Edep[i]->Write();
    // hdE_Edep_proton[i]->Write();
    // hdE_Edep_neutron[i]->Write();
    // hdE_Edep_gamma[i]->Write();
    // hdE_Edep_electron[i]->Write();
    // hdE_Edep_positron[i]->Write();
    // hdE_Edep_piplus[i]->Write();
    // hdE_Edep_piminus[i]->Write();
    // hPID_Ecr[i]->Write();
    // hEprim_Edep[i]->Write();
    // hEshld_Ecr[i]->Write();








  // hEcr_proton[0]->SetLineColor(kRed+1);
  // // hEcr_proton[0]->Rebin(2);
  // hEcr_proton[0]->Draw("same");
  // hEcr_electron[0]->SetLineColor(kCyan);
  // // hEcr_electron[0]->Rebin(2);
  // hEcr_electron[0]->Draw("same");
  // hEcr_positron[0]->SetLineColor(kViolet+1);
  // // hEcr_positron[0]->Rebin(2);
  // hEcr_positron[0]->Draw("same");
  // hEcr_neutron[0]->SetLineColor(kOrange+1);
  // // hEcr_neutron[0]->Rebin(2);
  // hEcr_neutron[0]->Draw("same");
  // hEcr_piplus[0]->SetLineColor(kMagenta);
  // // hEcr_piplus[0]->Rebin(2);
  // hEcr_piplus[0]->Draw("same");
  // hEcr_piminus[0]->SetLineColor(kBlue);
  // // hEcr_piminus[0]->Rebin(2);
  // hEcr_piminus[0]->Draw("same");
  // hEcr_nue[0]->SetLineColor(30);
  // // hEcr_nue[0]->Rebin(2);
  // hEcr_nue[0]->Draw("same");
  // hEcr_antinue[0]->SetLineColor(34);
  // // hEcr_antinue[0]->Rebin(2);
  // hEcr_antinue[0]->Draw("same");
  // hEcr_muon[0]->SetLineColor(38);
  // // hEcr_muon[0]->Rebin(2);
  // hEcr_muon[0]->Draw("same");
  // hEcr_antimuon[0]->SetLineColor(40);
  // // hEcr_antimuon[0]->Rebin(2);
  // hEcr_antimuon[0]->Draw("same");
  // hEcr_numu[0]->SetLineColor(41);
  // // hEcr_numu[0]->Rebin(2);
  // hEcr_numu[0]->Draw("same");
  // hEcr_antinumu[0]->SetLineColor(43);
  // // hEcr_antinumu[0]->Rebin(2);
  // hEcr_antinumu[0]->Draw("same");
 
