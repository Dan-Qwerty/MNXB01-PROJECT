#include "corona.h"

Analyse_Corona::Analyse_Corona() {
	Plot_Corona();
}

tuple<int, int, int> Analyse_Corona::dateCalculation(int year, int month, int date, int period) {
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

Double_t Analyse_Corona::meanOfPeriod (WeatherDataVec data, int frYear, int frMonth, int frDate, int period) {
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
	std::cout << sum/count << endl;
	return sum/count;
}


void Analyse_Corona::Plot_Corona() {
	ifstream file("../datasets/lund_corona_data");
	Int_t veck1[58];
	Int_t antal[58];
	Double_t veck2[58];

	Int_t i1 = 0;
	Double_t i2 = 0.0;
	Int_t year, week, kod, a, b, c, d;
	std::string lund;
	std::string _temp;
	while(file >> _temp) {
		if (_temp == "nya_fall_vecka") {
			break;
		}
	}

	while(file >> year >> week >> kod >> lund >> lund >> a >> b >> c >> d) {	
		if( (year == 2020 && week >= 9) || (year == 2021 && week <=13) ) {
			veck1[i1] = i1;
			veck2[i1] = i2;
			antal[i1] = d;
			i1++;
			i2 = i2 + 1.0;
		}
	}


	std::string filename {"../datasets/smhi-opendata_1_53430_20210926_101122_Lund.csv"};
	WeatherDataVec Wdata {datavec(filename)};

	Double_t temp[58];
	////////this is for test, saving time
	//for (int i = 0; i < 58; i++)
	//temp[i] = 14.4;
	//////////////////////////
	Int_t frYear = 2020;
	Int_t frMonth = 2;
	Int_t frDate = 24;
	Int_t toYear = 2021;
	Int_t toMonth = 4;
	Int_t toDate = 4;
	Int_t _i = 0;
	while (!(frYear >= toYear && frMonth >= toMonth && frDate >= toDate)){
		std::cout<< frYear << ":" << frMonth<< ":" << frDate << std::endl;
		temp[_i] = meanOfPeriod(Wdata, frYear, frMonth, frDate, 7);
		tie(frYear, frMonth, frDate) = dateCalculation(frYear, frMonth, frDate, 7);
		_i++;
	}

	TCanvas *c3 = new TCanvas("c3","Temperature & Corona",200,10,1200,600);
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

}
