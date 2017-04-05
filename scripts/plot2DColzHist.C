#include "TFile.h"
#include "TTree.h"
#include "stdio.h"

using namespace std;

void plot2DColzHist(){
	//Variable Declarations
	Double_t JobTime;
	Double_t EventsProcessed;

	//Build Canvas
	TCanvas *c1 = new TCanvas("t_vs_EventsProcessed","t_vs_EventsProcessed",800,800);
	gPad->Divide(0,2);
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
	metadata_TTree->SetBranchAddress("EventsProcessed", &EventsProcessed);	


	//Histogram Parameter Declarations
	Int_t nbinsx = 100;
	Double_t xlow = 0;
	Double_t xhigh = 300000;

	Int_t nbinsy = 150;
	Double_t ylow = 0;
	Double_t yhigh = 15000;
	
	//Initialize Histogram
	TH2D *hist = new TH2D("hist","Total Time vs Events Processed", nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		hist->Fill(EventsProcessed, JobTime);
	}
	
	//Draw Histogram
	hist->GetXaxis()->SetTitle("Number of Events Processed (x10^{3})");
	//hist->GetYaxis()->SetTitle("Total Job Time (s)");
	hist->Draw("colz");
	
	return;
}
