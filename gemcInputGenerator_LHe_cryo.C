#include <iostream>
#include <fstream>
#include <cmath>
#include "TROOT.h"
#include "TLine.h"
#include "TAxis.h"
#include "TApplication.h"
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TString.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TMatrixD.h"
#include "TEventList.h"
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TError.h"
#include "TMath.h"
#include "TStyle.h"
#include "TRandom2.h"

using namespace std;


void gemcInputGenerator_LHe_cryo(int nEvent, double E_min, double E_max){//E_min and E_max are in GeV

//  const nEvent = 100;
  ofstream outfile("GemcInput.dat");

  TFile *infile = new TFile("brem_spectrum.root");
  TH1F *hist = (TH1F*)infile->Get("brem_spectrum");
  Double_t bincount;
  // double E_min = 0.05; //GeV
  // Double_t max = hist->GetBinContent(hist->FindBin(E_min*1000));
  Double_t max = hist->GetMaximum();
  Double_t val, prob, E;
  Bool_t found;
  TRandom2 rand;
  rand.SetSeed(0);

  // TH1F *h = new TH1F("h1","h1",100,0,100);

  for(int i=0; i<nEvent; i++){
    outfile << "1\t0.\t0.\t0\t0\t0\t0.\t0.\t0.\t0."<< endl;
    outfile << "1\t0.\t1\t22\t0\t0\t0.\t0.\t";

    found = false;
    while(!found){
      val = E_min + rand.Rndm()*(E_max-E_min);
      prob = rand.Rndm()*max;
      // val = Rx.Rndm()*7e7;
      // prob = Ry.Rndm()*max;
      bincount = hist->GetBinContent(hist->FindBin(val*1000));

      if(prob <= bincount){
	E = val;
	found = true;
      }
    }

    outfile << E << "\t" << E << "\t0.\t0.\t0.\t-100.0"<<endl;

    // h->Fill(E*1000);
  }

  outfile.close();
  // h.Draw();
}
