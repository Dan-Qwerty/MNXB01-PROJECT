#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include "csvregex.h"
#include "WeatherDataLine.h"
#include "WeatherDataVec.h"

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TVirtualFitter.h>
#include <TLatex.h>
#include "monthly.h"
#include "RootClass.C"


Analyse_Monthly::Analyse_Monthly(Int_t month): _month{month}{
Month_tree();
}


void Analyse_Monthly::Month_tree() {
	TFile* file = new TFile("monthdata.root", "RECREATE");
	TTree* tree = new TTree("tree", "Output tree");
	Year* byyear = new Year();
	tree->Branch("byyear", &byyear);
	TClonesArray* dataArray = new TClonesArray("TempData", 1000);
	tree->Branch("data", "TClonesArray", &dataArray);
	Int_t nT = 0;
	
	std::string filename {"../datasets/smhi-opendata_1_53430_20210926_101122_Lund.csv"};
	WeatherDataVec Wdata {datavec(filename)};
	WeatherDataVec datamonth = Wdata.get_by_month(_month);
	std::vector<int> list_years = datamonth.list_years();
	for(Int_t n = 0; n < (Int_t) list_years.size() ; n++){
		byyear->year = list_years[n];

		WeatherDataVec _data = datamonth.get_by_year(byyear->year);
		
		byyear->nData = (Int_t) _data.data.size();

		Double_t Temp[byyear->nData];
		for(Int_t i = 0; i < byyear->nData; i++){
		Temp[i] = _data.data[i].get_temp();
		TempData* TD = new((*dataArray)[i]) TempData();
		nT++;
		TD->temp = Temp[i];
		}
	tree->Fill();
	}
	file->Write();
	file->Close();
}

void Analyse_Monthly::Temp_PerMonth() {
	TFile* file = TFile::Open("monthdata.root");
	TTree* tree = (TTree*)file->Get("tree");
	Year* byyear = 0;
	TClonesArray* dataArray = 0;
	tree->SetBranchAddress("byyear", &byyear);
	tree->SetBranchAddress("data", &dataArray);
	

	TH1D* h1 = new TH1D("h1", "Monthly temperatures distribution; Celsius; Counts", 100, -10, 30);
	
	const Int_t nYears = tree->GetEntries();
	for (Int_t n = 0; n < nYears; n++) {
		tree->GetEntry(n);
		const Int_t ndata = dataArray->GetEntries();	
		Double_t TempSum = 0.0;
		for (Int_t i = 0; i < ndata; i++){
			TempData* TD = (TempData*)dataArray->At(i);
			TempSum += TD->temp;
		}
		Double_t TempAver = TempSum/ndata;
		
		h1->Fill(TempAver);
	}
	h1->Fit("gaus");
	h1->Draw();

	TH1D *h2 = new TH1D("h2", "Monthly temperatures distribution; Temperature ^{o}C; Year Count", 100, -10, 30);
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(h2);
	h2->SetStats(kFALSE);
	h2->SetFillColor(41);
	h2->Draw("e3");
	h1->Draw("same");
}

void Analyse_Monthly::Month_Extreme() {
	TFile* file = TFile::Open("monthdata.root");
	TTree* tree = (TTree*)file->Get("tree");
	Year* byyear = 0;
	TClonesArray* dataArray = 0;
	tree->SetBranchAddress("byyear", &byyear);
	tree->SetBranchAddress("data", &dataArray);
	
	const Int_t nYears = tree->GetEntries();
	Double_t x[nYears], yH[nYears], yC[nYears], yA[nYears];
	
	for (Int_t n = 0; n < nYears; n++) {
		tree->GetEntry(n);
		x[n] = byyear->year;
		const Int_t ndata = dataArray->GetEntries();	
		Double_t HTemp = 0.0;
		Double_t CTemp = 0.0;
		Double_t TempSum = 0.0;
		for (Int_t i = 0; i < ndata; i++) {
			TempData* TD = (TempData*)dataArray->At(i);
			TempSum += TD->temp;
			if (i==0){
				HTemp = TD->temp;
				CTemp = TD->temp;
			}
			else{
				HTemp = max(TD->temp, HTemp);
				CTemp = min(TD->temp, CTemp);
			}
		}
		Double_t TempAver = TempSum/ndata;
		yA[n] = TempAver;
		yH[n] = HTemp;
		yC[n] = CTemp;
	}
	
	TCanvas *c1 = new TCanvas("c1","Month Extreme Temperature",200,10,1000,600);
	TGraph* g1 = new TGraph(nYears, x, yH);
	TGraph* g2 = new TGraph(nYears, x, yC);
	TGraph* g3 = new TGraph(nYears, x, yA);
	TMultiGraph *mg = new TMultiGraph();
	mg->SetTitle("Month Extreme Temperature; Year; Temperature ^{o}C");
	g1->SetFillColor(46);
	g2->SetFillColor(38);
	g3->SetLineWidth(3);
	g3->SetLineColor(12);
	g3->Fit("pol1");
	mg->Add(g1);
	mg->Add(g2);
	mg->Draw("AB");
	mg->GetXaxis()->SetTitleSize(0.03);
	mg->GetXaxis()->SetLabelSize(0.03);
	mg->GetYaxis()->SetTitleSize(0.03);
	mg->GetYaxis()->SetLabelSize(0.03);
	g3->Draw("C same");
}
