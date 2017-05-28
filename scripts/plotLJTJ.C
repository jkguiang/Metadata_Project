#include "TFile.h"
#include "TTree.h"
#include "stdio.h"

using namespace std;

void plotLJTJ(){
	//Variable Declarations
	Double_t JobTime;
	Int_t Year;
	Int_t Month;
	Int_t Day;
	Int_t Hour;

	//Build Canvas
	TCanvas *c1 = new TCanvas();
	gStyle->SetOptStat(0);
	//c1->SetLogz(1); //SetLogz(0) disables logarithmic scale on z axis

	//Open TFile and retrieve TTree
	TFile *f = TFile::Open("metadata_TTree.root","READ");
	if (f == 0){
		printf("Unable to open file.");
		return;
	}

	TTree* metadata_TTree = (TTree*)f->Get("t");
	metadata_TTree->SetBranchAddress("JobTime", &JobTime);	
	metadata_TTree->SetBranchAddress("Year", &Year);	
	metadata_TTree->SetBranchAddress("Month", &Month);	
	metadata_TTree->SetBranchAddress("Day", &Day);	
	metadata_TTree->SetBranchAddress("Hour", &Hour);	

	//Histogram Parameter Declarations
	Int_t nbinsx = 31;
	Double_t xlow = 0;
	Double_t xhigh = 31;
	
	//Initialize Histogram
	TH1D *h1 = new TH1D("h1", "Long Job Time/All Jobs Distribution (January 2017)", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		if (Month == 1 && Year == 2017){
			h1->Fill(Day);
		}
	}
	
	//Initialize Histogram
	TH1D *h2 = new TH1D("h2", "Long Job/All Jobs Time Distribution (January 2017)", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		if (JobTime > 1800 && Month == 1 && Year == 2017){
			h2->Fill(Day);
		}
	}
	
	h2->GetYaxis()->SetTitle("#frac{Long Jobs}{Total Jobs}");
	h2->GetXaxis()->SetTitle("Day");
	h2->SetLineColor(2);
	h2->SetLineWidth(2);
	h2->Divide(h1);
	h2->Draw();

	return;
}
