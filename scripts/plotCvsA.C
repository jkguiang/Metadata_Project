#include "TFile.h"
#include "TTree.h"
#include "stdio.h"

using namespace std;

void plotCvsA(){
	//Variable Declarations
	Double_t CopyTime;
	Double_t AddInfoTime;

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
	metadata_TTree->SetBranchAddress("CopyTime", &CopyTime);	
	metadata_TTree->SetBranchAddress("AddInfoTime", &AddInfoTime);	


	//Histogram Parameter Declarations
	Int_t nbinsx = 100;
	Double_t xlow = 0;
	Double_t xhigh = 4000;

	Int_t nbinsy = 100;
	Double_t ylow = 0;
	Double_t yhigh = 4000;
	
	//Initialize Histogram
	TH2D *hist = new TH2D("hist","Copy Time vs Add Info Time", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		hist->Fill(CopyTime, AddInfoTime);
	}
	
	//Draw Histogram
	hist->GetXaxis()->SetTitle("Copy Time (s)");
	hist->GetYaxis()->SetTitle("Add Info Time (s)");
	hist->GetYaxis()->SetTitleOffset(1.4);
	hist->Draw("colz");
	
	return;
}
