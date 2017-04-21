#include "TFile.h"
#include "TTree.h"
#include "stdio.h"

using namespace std;

void plotLSEvents(){
	//Variable Declarations
	Double_t EventsProcessed;
	Double_t JobTime;
	Int_t Hour;
	Int_t Day;

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
	metadata_TTree->SetBranchAddress("EventsProcessed", &EventsProcessed);	
	metadata_TTree->SetBranchAddress("Hour", &Hour);	
	metadata_TTree->SetBranchAddress("Day", &Day);	

	//Histogram Parameter Declarations
	Int_t nbinsx = 100;
	Double_t xlow = 0;
	Double_t xhigh = 300000;
	
	//Initialize Histogram
	TH1D *h1 = new TH1D("h1", "Events Processed", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		if (JobTime >= 1800){
			h1->Fill(EventsProcessed);
		}
	}
	
	//Draw Histogram
	h1->SetLineColor(4);
	h1->SetLineWidth(2);
	
	//New Histogram: (h2)	
	//Initialize Histogram
	TH1D *h2 = new TH1D("h2", "Events Processed", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		if (JobTime < 1800){
			h2->Fill(EventsProcessed);
		}
	}
	
	h2->GetXaxis()->SetTitle("Copy Time (s)");
	h2->SetLineColor(2);
	h2->SetLineWidth(2);
	h2->DrawNormalized();
	h1->DrawNormalized("SAME");
	
	auto legend = new TLegend(0.7,0.7,0.9,0.9);
	legend->AddEntry(h1, "Job Time #geq 30 mins");
	legend->AddEntry(h2, "Job Time < 30 mins");
	legend->Draw();
	
	return;
}
