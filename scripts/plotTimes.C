#include "TFile.h"
#include "TTree.h"
#include "stdio.h"

using namespace std;

void plotTimes(){
	//Variable Declarations
	Double_t JobTime;
	Double_t MergeTime;
	Double_t AddInfoTime;
	Double_t CopyTime;

	//Build Canvas
	TCanvas *c1 = new TCanvas();
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	//c1->SetLogz(1); //SetLogz(0) disables logarithmic scale on z axis

	//Open TFile and retrieve TTree
	TFile *f = TFile::Open("metadata_TTree.root","READ");
	if (f == 0){
		printf("Unable to open file.");
		return;
	}

	TTree* metadata_TTree = (TTree*)f->Get("t");
	metadata_TTree->SetBranchAddress("JobTime", &JobTime);	
	metadata_TTree->SetBranchAddress("MergeTime", &MergeTime);	
	metadata_TTree->SetBranchAddress("AddInfoTime", &AddInfoTime);	
	metadata_TTree->SetBranchAddress("CopyTime", &CopyTime);	

	//Histogram Parameter Declarations
	Int_t nbinsx = 100;
	Double_t xlow = 0;
	Double_t xhigh = 4000;
	
	//Initialize Histogram
	TH1D *hist1 = new TH1D("hist","Copy Time", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		hist1->Fill(CopyTime);
	}
	
	//Draw Histogram
	hist1->GetXaxis()->SetTitle("Time (s)");
	hist1->SetLineColor(4);
	hist1->SetLineWidth(2);
	hist1->Draw();
	
	//Initialize New Histogram
	TH1D *hist2 = new TH1D("hist2","Add Info Time", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		hist2->Fill(AddInfoTime);
	}
	
	//Redraw Histogram
	hist2->SetLineColor(2);
	hist2->SetLineWidth(2);
	hist2->Draw("SAME");

	//Initialize New Histogram
	TH1D *hist3 = new TH1D("hist3","Job Time", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		hist3->Fill(JobTime);
	}
	
	//Redraw Histogram
	hist3->SetLineColor(3);
	hist3->SetLineWidth(2);
	hist3->Draw("SAME");

	//Initialize New Histogram
	TH1D *hist4 = new TH1D("hist4","Merge Time", nbinsx, xlow, xhigh);	
	
	//Loop over entries in branch, fill histogram one bin at a time
	for (Int_t i = 0; i < metadata_TTree->GetEntries(); i++){
		metadata_TTree->GetEntry(i);
		hist4->Fill(MergeTime);
	}
	
	//Redraw Histogram
	hist4->SetLineColor(6);
	hist4->SetLineWidth(2);
	hist4->Draw("SAME");

	//Build Legend
	gPad->BuildLegend();
	
	return;
}
