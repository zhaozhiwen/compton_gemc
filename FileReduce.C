#include <vector>
#include <iostream> 
#include <fstream>
#include <cmath> 
#include <math.h> 
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TEllipse.h>
#include <TBox.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TMinuit.h>
#include <TPaveText.h>
#include <TText.h>
#include <TSystem.h>
#include <TArc.h>
#include <TColor.h>

using namespace std;

void FileReduce(string input_filename)
{
	bool Is_morebanks;
  
	TFile *f1 = new TFile(input_filename.c_str());
	TFile *f2 = new TFile(Form("%s_skim",input_filename.c_str()), "RECREATE");
	
	TTree *header;
	TTree *generated;
	TTree *allraws;  
	TTree *flux;	

	header = (TTree*)f1->Get("header");	
	generated = (TTree*)f1->Get("generated");
	allraws = (TTree*)f1->Get("allraws");
	flux = (TTree*)f1->Get("flux");
	
// 	cout <<   flux->GetBranch("hitn")->GetLeaf("hitn")->GetTypeName() << endl;
// 	cout <<   flux->FindLeaf("hitn")->GetValue(1) << endl;
	
	TTree *output_header;
	TTree *output_generated;
	TTree *output_allraws;  
	TTree *output_flux;
	
	output_header = header->CloneTree(0);
	output_generated = generated->CloneTree(0);
	output_allraws = allraws->CloneTree(0);
	output_flux = flux->CloneTree(0);

vector<double> *flux_hitn=0;
vector<double> *allraws_hitn=0,*solid_gem_hitn=0,*solid_ec_hitn=0,*solid_lgc_hitn=0,*solid_mrpc_hitn=0,*solid_spd_hitn=0,*solid_hgc_hitn=0;
allraws->SetBranchAddress("hitn", &allraws_hitn);
flux->SetBranchAddress("hitn", &flux_hitn);

	long long int fNentries = generated->GetEntries();
	
	cout << "total number of events " << fNentries << endl;
	
	int counter=0;
	for (int i=0; i<fNentries; i++){
// 		if (i % 1000000 == 0) std::cout<<i<<endl;
			header->GetEntry(i);
			generated->GetEntry(i);
			allraws->GetEntry(i);
			flux->GetEntry(i);	

		
			  if (flux_hitn->size() > 0){			   

			      counter++;
			      
			      output_header->Fill();
			      output_generated->Fill();
			      output_allraws->Fill();
			      output_flux->Fill();	
			  }				  

	}
	cout << "skim counter " <<  counter << endl;
	
	f2->cd();
	
	output_header->Write();
	output_generated->Write();
	output_allraws->Write();
	output_flux->Write();
	
	f2->Close();
	f1->Close();
	
};
