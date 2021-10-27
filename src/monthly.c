#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include "csvregex.h"
#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
//#include "csvregex.cpp"
//#include "WeatherDataVec.cpp"
using namespace std;

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TCanvas.h>
//#include <TPad.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TVirtualFitter.h>
#include <TLatex.h>
#include "RootClass.C"

void temPerMonth_tree(Int_t month) // ttree built
{
	TFile* file = new TFile("monthdata.root", "RECREATE");
	TTree* tree = new TTree("tree", "Output tree");
	Year* byyear = new Year();
	tree->Branch("byyear", &byyear);
	TClonesArray* dataArray = new TClonesArray("TempData", 1000);
	tree->Branch("data", "TClonesArray", &dataArray);
	Int_t nT = 0;
	
	string filename {"../datasets/smhi-opendata_1_53430_20210926_101122_Lund.csv"};
	WeatherDataVec Wdata {datavec(filename)};
	WeatherDataVec datamonth = Wdata.get_by_month(month);
	vector<int> list_years = datamonth.list_years();
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

void temPerMonth()//plot the histo of the average temperature of the month
{

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
		for (Int_t i = 0; i < ndata; i++)
		{
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

void MonthExtreme()//plot the extreme temperatures & average temperature of the month
{
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
		for (Int_t i = 0; i < ndata; i++)
		{
			TempData* TD = (TempData*)dataArray->At(i);
			TempSum += TD->temp;
			if (i==0)
			{
				HTemp = TD->temp;
				CTemp = TD->temp;
			}
			else
			{
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

tuple<int, int, int> dateCalculation(int year, int month, int date, int period)//determine the day+period from y.m.d 
{
	date = date + period;
	int count =1;
	while(count !=0){
		count =0;
		if (date>31 && ( month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12 ) ){
			date = date - 31;
			month++;
			count++;
		}
		else if (date>30 &&  ( month== 4 || month==6 || month==9 || month==11 ) ){
			date = date - 30;
			month++;
			count++;
		}
		else if (date>28 && month ==2 && (year%4 !=0)){
			date = date - 28;
			month++;
			count++;
		}
		else if (date>29 && month ==2 && (year%4 ==0)){
			date = date - 29;
			month++;
			count++;
		}

		if (month > 12){
			month = 1;
			year++;
		}
	}

	return make_tuple(year, month, date);

}

Double_t meanOfPeriod (WeatherDataVec data, int frYear, int frMonth, int frDate, int period)// determine the mean temp from fY,fM,fD with step length period
{
// from date included, to date not included.
	Double_t sum=0.0;
	Int_t count=0;
	while(period!=0){
		WeatherDataVec _data = data.get_by_year(frYear);
		WeatherDataVec __data = _data.get_by_month(frMonth);
		WeatherDataVec ___data = __data.get_by_day(frDate);
		for(unsigned i=0; i<___data.data.size(); i++){
			sum = sum + ___data.data[i].get_temp();
			count++;
		}
		tie(frYear, frMonth, frDate) = dateCalculation(frYear, frMonth, frDate, 1);	
		period--;	
	}
	cout << sum/count << endl;
	return sum/count;
}


void Corona()//discover the relation between the temperature and corona
{
	ifstream file("../datasets/lund_corona_data");
	Int_t veck1[58];
	Int_t antal[58];
	Double_t veck2[58];

	Int_t i1 = 0;
	Double_t i2 = 0.0;
	Int_t year, week, kod, a, b, c, d;
	string lund;
	string _temp;
	while(file >> _temp)
	{
		if (_temp == "nya_fall_vecka")
		{
			break;
		}
	}

	while(file >> year >> week >> kod >> lund >> lund >> a >> b >> c >> d)
	{	
		if( (year == 2020 && week >= 9) || (year == 2021 && week <=13) )
		{
			veck1[i1] = i1;
			veck2[i1] = i2;
			antal[i1] = d;
			i1++;
			i2 = i2 + 1.0;
		}
	}


	string filename {"../datasets/smhi-opendata_1_53430_20210926_101122_Lund.csv"};
	WeatherDataVec Wdata {datavec(filename)};

	Double_t temp[58];
	////////yixiawei ceshi yong
	for (int i = 0; i < 58; i++)
	temp[i] = 14.4;
	//////////////////////////
	/*Int_t frYear = 2020;
	Int_t frMonth = 2;
	Int_t frDate = 24;
	Int_t toYear = 2021;
	Int_t toMonth = 4;
	Int_t toDate = 4;
	Int_t _i = 0;
	while (!(frYear >= toYear && frMonth >= toMonth && frDate >= toDate)){
		cout<< frYear << ":" << frMonth<< " :" << frDate << endl;
		temp[_i] = meanOfPeriod(Wdata, frYear, frMonth, frDate, 7);
		tie(frYear, frMonth, frDate) = dateCalculation(frYear, frMonth, frDate, 7);
		_i++;
	}*/

	TCanvas *c1 = new TCanvas("c1","Temperature & Corona",200,10,1200,600);
	TGraph* g1 = new TGraph(58, veck1, antal);
	TGraph* g2 = new TGraph(58, veck2, temp);
	TPad *pad1 = new TPad("pad1","",0,0,1,1);
	TPad *pad2 = new TPad("pad2","",0,0,1,1);
	pad2->SetFillStyle(4000); // transparent
	pad2->SetFrameFillStyle(0);
	g1->SetFillColor(46);
	g1->SetTitle("Temperature & Corona");
	g1->GetYaxis()->SetLabelColor(46);
	g1->GetYaxis()->SetLabelSize(0.03); // default 0.04
	g1->GetYaxis()->SetTitle("Counts");
	g1->GetYaxis()->SetTitleColor(46);
	g1->GetYaxis()->SetTitleSize(0.03); // default 0.04
	g1->GetXaxis()->SetRangeUser(0, 62);
	g1->GetXaxis()->SetTitle("Weeks");
	g1->GetXaxis()->SetTitleSize(0.03); // default 0.04
	g1->GetXaxis()->SetLabelSize(0.03); // default 0.04
	g1->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"2020/9");
	g1->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"19");
	g1->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"29");
	g1->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"39");
	g1->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"49");
	g1->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"2021/6");
	g1->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"16");	
	g2->SetLineColor(9);
	g2->SetLineWidth(3);
	g2->GetXaxis()->SetTickLength(0);// transparent
	g2->GetXaxis()->SetLabelOffset(999);// transparent
	g2->GetXaxis()->SetLabelSize(0);// transparent
	g2->GetYaxis()->SetLabelColor(9);
	g2->GetYaxis()->SetLabelSize(0.03); // default 0.04
	g2->GetYaxis()->SetTitle(" ^{o}C");
	g2->GetYaxis()->SetTitleColor(9);
	g2->GetYaxis()->SetTitleSize(0.03); // default 0.04
	/*g2->GetYaxis()->SetTickLength(0);
	g2->GetYaxis()->SetLabelOffset(999);
	g2->GetYaxis()->SetLabelSize(0);*/
	pad1->Draw();
	pad1->cd();
	g1->Draw("AB, Y+");
	pad2->Draw();
	pad2->cd();
	g2->Draw();
	/*TGaxis *a1 = new TGaxis(62, 0, 62, 800, -10, 25, 510, "+L");
	a1->SetName("a1");
	a1->SetTitle("Temperature ^{o}C");
 	a1->Draw("same");*/





/*
	//mg->SetTitle("Month Extreme Temperature; Week; Temperature ^{o}C");
	g1->SetFillColor(46);
	g2->GetXaxis()->SetTickLength(0);
	g2->GetXaxis()->SetLabelOffset(999);
	g2->GetXaxis()->SetLabelSize(0);
	g1->GetXaxis()->SetRangeUser(0, 62);
	g1->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"9");
	g1->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"19");
	g1->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"29");
	g1->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"39");
	g1->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"49");
	g1->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"6");
	g1->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"16");
	g1->Draw("AB");
	g2->Draw("same");

	TGaxis *a1 = new TGaxis(62, 0, 62, 800, -10, 25, 510, "+L");
	a1->SetName("a1");
	a1->SetTitle("Temperature ^{o}C");
 	a1->Draw();
*/


}

