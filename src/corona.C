#include "corona.h"

Analyse_Corona::Analyse_Corona(std::string city, std::string filename): _city{city}, _filename{filename}{
	Plot_Corona();//plot the figure of the relation between the temperature and number of people infected with the COVID-19 when a new object is created.
}

/*
tuple<int, int, int> Analyse_Corona::dateCalculation(int year, int month, int date, int period) const{
	date = date + period; // period is day, from 0 to any positive integer
	int count =1; // initialize the condition counter: count
	while(count !=0){ 
		count =0; // clear the condition counter

		// check if the day is exceeded maximum days the currect month owns
		// minus the maximum days(28/29/30/31) if the day is exceeded, if so, do month++ and count++
		// the count++ is in case of the period > one month, so the while loop will run continuously till all of the following conditions do not be staisfied any more, which means the new date is "legal" and can be returned.
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
			// for the Feb of a common year
			date = date - 28;
			month++;
			count++;
		}
		else if (date>29 && month ==2 && (year%4 ==0)){
			// for the Feb of a leap year
			date = date - 29;
			month++;
			count++;
		}

		// if the month > 12 after the above calculations, year will be +1 and month = 1
		if (month > 12){
			month = 1;
			year++;
		}
	}

	return make_tuple(year, month, date);
}
*/

/*
Double_t Analyse_Corona::meanOfPeriod (WeatherDataVec data, int frYear, int frMonth, int frDate, int period) const{
// return the mean temperature between the date frYear.frMonth.frDate to the date (frYear.frMonth.frDate)+period
	Double_t sum = 0.0;
	Int_t count = 0; // the number of temperature data
	while(period != 0){
		WeatherDataVec _data = data.get_by_year(frYear).get_by_month(frMonth).get_by_day(frDate);
		for(unsigned i = 0; i < _data.data.size(); i++){
			// get temperature for one day
			sum = sum + _data.data[i].get_temp(); // sum the temperature data
			count++;
		}
		tie(frYear, frMonth, frDate) = dateCalculation(frYear, frMonth, frDate, 1);	// detemine the date for the next day
		period--; // count days
	}
	std::cout << sum/count << std::endl;
	return sum/count;
}
*/

void Analyse_Corona::Plot_Corona() const{
	std::string fname = "../datasets/Covid Data/Covid_" + _city + ".csv";

	std::ifstream file;
	file.open(fname);
	Int_t veck1[58];
	Int_t antal[58];
	Double_t veck2[58];

	Int_t i1 = 0;
	Double_t i2 = 0.0;
	std::string yearstring, weekstring, numberstring;
	Int_t year = 0;
	Int_t week = 0;
	std::string city;
	Int_t number = 0;
	std::string fileline;
	std::getline(file, fileline); // the first line will be ignored

	while(std::getline(file, fileline)) {
		std::istringstream filesteam(fileline);
		std::getline(filesteam, yearstring,',');
		std::istringstream ss1(yearstring);
		ss1 >> year;
		std::getline(filesteam, weekstring, ',');
		std::istringstream ss2(weekstring);
		ss2 >> week;
		std::getline(filesteam, city, ',');
		std::getline(filesteam, numberstring, ',');
		std::istringstream ss3(numberstring);
		ss3 >> number;
		if( (year == 2020 && week >= 9) || (year == 2021 && week <=13) ) {
			veck1[i1] = i1;
			veck2[i1] = i2;
			antal[i1] = number;
			i1++;
			i2 = i2 + 1.0;
		}
	}

	WeatherDataVec Wdata {"../datasets/" + _filename};

	Double_t temp[58];
	// set the begining date and the due date we want to analyse
	int frYear = 2020;
	int frMonth = 2;
	int frDay = 24;
	int toYear = 2021;
	int toMonth = 4;
	int toDay = 4;
	int _i = 0; // counter
	std::cout << "\nYY.MM.DD -- Degree Celsius" << std::endl;

	//This should be equivalent to all the previous code modulo some compile errors -- might need to fix
	WeatherDataVec Wbetween {Wdata.get_between(frYear,frMonth,frYear,toYear,toMonth,toDay).avg_by_day()};
	Gregorian counter_date {frYear,frMonth,frDay};
	std::vector<double> tempvec;
	while(counter_date < Gregorian(toYear,toMonth,toDay)){
		tempvec.push_back(Wdata.get_between(counter_date.get_datestr(),(counter_date+7).get_datestr()).avgtemp());
		counter_date = counter_date+7;
	}
	for(int i = 0 ; i < tempvec.size(); i++){
		temp[i] = tempvec[i];
	}


/*	
	// determine weekly mean temperature from the date frYear.frMonth.frDate to the date toYear.toMonth.toDate
	while (!(frYear >= toYear && frMonth >= toMonth && frDate >= toDate)){
		//do the following if the current date is not beyond the target date
		std::cout << frYear << "." << frMonth<< "." << frDate << " -- ";
		temp[_i] = meanOfPeriod(Wdata, frYear, frMonth, frDate, 7); // mean temperature for one week(7days)
		tie(frYear, frMonth, frDate) = dateCalculation(frYear, frMonth, frDate, 7); // determine the next date and assign to current
		_i++;
	}
*/


	TCanvas *c3 = new TCanvas("c3","Temperature & Corona",200,10,1200,600);
	TGraph* g1 = new TGraph(58, veck1, antal); // figure of the number of infected people
	TGraph* g2 = new TGraph(58, veck2, temp); // figure of the weekly average temperature
	TPad *pad1 = new TPad("pad1","",0,0,1,1);
	TPad *pad2 = new TPad("pad2","",0,0,1,1);
	pad2->SetFillStyle(4000); // the window is transparent
	pad2->SetFrameFillStyle(0); // hollow
	g1->SetFillColor(46); // red
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
	g1->GetXaxis()->ChangeLabel(1,-1,-1,-1,-1,-1,"2020/9");	// change the original x-axis to the week we need
	g1->GetXaxis()->ChangeLabel(2,-1,-1,-1,-1,-1,"19");
	g1->GetXaxis()->ChangeLabel(3,-1,-1,-1,-1,-1,"29");
	g1->GetXaxis()->ChangeLabel(4,-1,-1,-1,-1,-1,"39");
	g1->GetXaxis()->ChangeLabel(5,-1,-1,-1,-1,-1,"49");
	g1->GetXaxis()->ChangeLabel(6,-1,-1,-1,-1,-1,"2021/6");
	g1->GetXaxis()->ChangeLabel(7,-1,-1,-1,-1,-1,"16");	
	g2->SetLineColor(9); // purple
	g2->SetLineWidth(3);
	g2->GetXaxis()->SetTickLength(0);
	g2->GetXaxis()->SetLabelOffset(999);
	g2->GetXaxis()->SetLabelSize(0);
	g2->GetYaxis()->SetLabelColor(9);
	g2->GetYaxis()->SetLabelSize(0.03); // default 0.04
	g2->GetYaxis()->SetTitle(" ^{o}C");
	g2->GetYaxis()->SetTitleColor(9);
	g2->GetYaxis()->SetTitleSize(0.03); // default 0.04
	pad1->Draw();
	pad1->cd();
	g1->Draw("AB, Y+"); //a bar chart(B) is drawn with axis(A) on the right side(Y+) of the plot
	pad2->Draw();
	pad2->cd();
	g2->Draw();

	TLegend *l1 = new TLegend(0.28, 0.273, 0.5, 0.436);
	l1->AddEntry(g1,"number of people infected","f");
	l1->AddEntry(g2,"average temp","l");
	l1->Draw();
}
