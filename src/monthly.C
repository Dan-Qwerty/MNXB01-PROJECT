#include "monthly.h"

Analyse_Monthly::Analyse_Monthly(Int_t month, std::string filename): _month{month}, _filename{filename}{
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
	
	std::string name1 = "../datasets/";
	std::string name2 = _filename;
	std::string filename = name1 + name2;
	//std::string filename {"../datasets/smhi-opendata_1_53430_20210926_101122_Lund.csv"};
	WeatherDataVec Wdata {(filename)};
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
	
	TCanvas *c2 = new TCanvas("c2","Monthly temperatures distribution",250,10,1000,600);
	TH1D* h1 = new TH1D("h1", "Monthly temperatures distribution; Celsius; Counts", 150, -10, 30);
	
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
	TF1* fitfcn = new TF1("fitfcn", "gaus", -10, 30);
	h1->Fit("fitfcn");
	h1->SetLineWidth(2);
	h1->GetXaxis()->SetTitleSize(0.03);
	h1->GetXaxis()->SetLabelSize(0.03);
	h1->GetYaxis()->SetTitleSize(0.03);
	h1->GetYaxis()->SetLabelSize(0.03);
	h1->Draw();

	TH1D *h2 = new TH1D("h2", "Monthly temperatures distribution; Temperature ^{o}C; Year Counts", 150, -10, 30);
	(TVirtualFitter::GetFitter())->GetConfidenceIntervals(h2);
	h2->SetStats(kFALSE);
	h2->SetFillColor(41);
	h2->GetXaxis()->SetTitleSize(0.03);
	h2->GetXaxis()->SetLabelSize(0.03);
	h2->GetYaxis()->SetTitleSize(0.03);
	h2->GetYaxis()->SetLabelSize(0.03);
	h2->Draw("e3");
	h1->Draw("same");

	TLegend *l1 = new TLegend(0.73, 0.847, 0.946, 0.945);
	l1->AddEntry(h1,"temp distribution","l");
	l1->AddEntry(fitfcn,"fit","l");
	l1->AddEntry(h2,"95% CI of fitting function","f");
	l1->Draw();
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
	Double_t Highest = 0.0;
	Double_t Lowest = 0.0;
	Int_t year_highest = 0;
	Int_t year_lowest = 0;
	
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
			if (i==0) {   //find out the monthly highest and lowest temperature: HTemp and CTemp
				HTemp = TD->temp;
				CTemp = TD->temp;
			}
			else{
				HTemp = std::max(TD->temp, HTemp);
				CTemp = std::min(TD->temp, CTemp);
			}
		}
		Double_t TempAver = TempSum/ndata;
		yA[n] = TempAver;
		yH[n] = HTemp;
		yC[n] = CTemp;
	//////the following is to find out the highest/lowest temperatures over all of the years. 
		if (n != 0) {
			Highest = std::max(yH[n], Highest);
			Lowest = std::min(yC[n], Lowest);
			if (Highest == yH[n])
				year_highest = x[n];
			if (Lowest == yC[n])
				year_lowest = x[n];

		} else {
			Highest = yH[0];
			Lowest = yC[0];
			year_highest = x[0];
			year_lowest	= x[0];
		}
	}
	std::cout << "\nThe highest temperature of this month is " << Highest << " occuring in " << year_highest << std::endl;
	std::cout << "The lowest temperature of this month is " << Lowest << " occuring in " << year_lowest << std::endl;
	
	TCanvas *c1 = new TCanvas("c1","Month Extreme Temperature",200,10,1000,600);
	TGraph* g1 = new TGraph(nYears, x, yH);
	TGraph* g2 = new TGraph(nYears, x, yC);
	TGraph* g3 = new TGraph(nYears, x, yA);
	TMultiGraph *mg = new TMultiGraph();
	TF1* fitfcn = new TF1("fitfcn", "pol1", x[0], x[nYears]); // fitting function for average temp
	mg->SetTitle("Month Extreme Temperature; Year; Temperature ^{o}C");
	g1->SetFillColor(46);
	g2->SetFillColor(38);
	g3->SetLineWidth(3);
	g3->SetLineColor(12);
	g3->Fit("fitfcn");
	mg->Add(g1);
	mg->Add(g2);
	mg->Draw("AB");
	mg->GetXaxis()->SetTitleSize(0.03);
	mg->GetXaxis()->SetLabelSize(0.03);
	mg->GetYaxis()->SetTitleSize(0.03);
	mg->GetYaxis()->SetLabelSize(0.03);
	g3->Draw("same");

	TLegend *l1 = new TLegend(0.0051, 0.5178, 0.144, 0.652);
	l1->AddEntry(g1,"highest temp","f");
	l1->AddEntry(g2,"lowest temp","f");
	l1->AddEntry(g3,"average temp","l");
	l1->AddEntry(fitfcn,"linear fit","l");
	l1->Draw();
}
