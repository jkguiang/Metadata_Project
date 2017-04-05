#include "TFile.h"
#include "TTree.h"
#include "stdio.h"

using namespace std;

void plot1DHist(){
	//Variable Declarations
	Double_t TimePerEvent;

	//Build Canvas
	TCanvas *c1 = new TCanvas("t_vs_EventsProcessed","t_vs_EventsProcessed",800,800);
	gPad->Divide(0,2);
	//gStyle->SetOptStat(0);
	//c1->SetLogz(1); //SetLogz(0) disables logarithmic scale on z axis

	//Open TFile and retrieve TTree
	TFile *f = TFile::Open("metadata_TTree.root","READ");
	if (f == 0){
		printf("Unable to open file.");
		return;
	}

	TTree* metadata_TTree = (TTree*)f->Get("t");
	metadata_TTree->SetBranchAddress("TimePerEvent", &TimePerEvent);	

	//Histogram Parameter Declarations
	Int_t nbinsx = 1000;
	Double_t xlow = 0;
	Double_t xhigh = 0.15;
	
	//Initialize Histogram
	TH1D *hist = new TH1D("hist","Time per Event Processed", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		hist->Fill(TimePerEvent);
	}
	
	//Draw Histogram
	hist->GetXaxis()->SetTitle("Time per Event Processed (s/event)");
	hist->Draw();
	
	return;
}
