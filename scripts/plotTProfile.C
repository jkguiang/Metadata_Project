#include "TFile.h"
#include "TTree.h"
#include "stdio.h"

using namespace std;

void plotTProfile(){
	//Variable Declarations
	Double_t TimePerEvent;
	Int_t ComputerNumber;

	//Build Canvas
	TCanvas *TperE_vs_Machine = new TCanvas("TperE_vs_Machine","TperE_vs_Machine",800,800);
	gPad->Divide(0,2);

	//Open TFile and retrieve TTree
	TFile *f = TFile::Open("metadata_TTree.root","READ");
	if (f == 0){
		printf("Unable to open file.");
		return;
	}

	TTree* metadata_TTree = (TTree*)f->Get("t");
	metadata_TTree->SetBranchAddress("TimePerEvent", &TimePerEvent);	
	metadata_TTree->SetBranchAddress("ComputerNumber", &ComputerNumber);	


	//Histogram Parameter Declarations
	Int_t nbinsx = 270;
	Double_t xlow = 0;
	Double_t xhigh = 270;

	Double_t ylow = 0;
	Double_t yhigh = 100;
	
	//Initialize Histogram
	TProfile *prof = new TProfile("prof","Time per Event Processed vs Machine", nbinsx, xlow, xhigh, ylow, yhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		prof->Fill(ComputerNumber, TimePerEvent);
	}
	
	//Draw Histogram
	prof->GetXaxis()->SetTitle("Computer Number");
	//Y-axis label clipped into tick labels
	//prof->GetYaxis()->SetTitle("Time per Event Processed (s/event)");
	prof->Draw();
	
	return;
}
