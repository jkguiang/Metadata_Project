#include "TFile.h"
#include "TTree.h"
#include "stdio.h"

using namespace std;

void plotJvsM(){
	//Variable Declarations
	Double_t JobTime;
	Double_t MergeTime;

	//Build Canvas
	TCanvas *c1 = new TCanvas();
	gStyle->SetOptStat(0);
	c1->SetLogz(1);

	//Open TFile and retrieve TTree
	TFile *f = TFile::Open("metadata_TTree.root","READ");
	if (f == 0){
		printf("Unable to open file.");
		return;
	}

	TTree* metadata_TTree = (TTree*)f->Get("t");
	metadata_TTree->SetBranchAddress("JobTime", &JobTime);	
	metadata_TTree->SetBranchAddress("MergeTime", &MergeTime);	


	//Histogram Parameter Declarations
	Int_t nbinsx = 200;
	Double_t xlow = 2500;
	Double_t xhigh = 14000;

	Int_t nbinsy = 200;
	Double_t ylow = 0;
	Double_t yhigh = 8000;
	
	//Initialize Histogram
	TH2D *hist = new TH2D("hist","Job Time vs Merge Time, for Job Time > 2500s", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		if (JobTime > 2500){
			hist->Fill(JobTime, MergeTime);
		}
	}
	
	//Draw Histogram
	hist->GetXaxis()->SetTitle("Job Time (s)");
	hist->GetYaxis()->SetTitle("Copy Time (s)");
	hist->GetYaxis()->SetTitleOffset(1.4);
	hist->Draw("colz");
	
	return;
}
