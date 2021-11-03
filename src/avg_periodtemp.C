#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>

// ROOT library objects
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TLegend.h>


int convert_dm_to_day(int day, int month){
    int monthdays[] = { 31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31 };

    int days_prior = 0;
    for(int m = 0; m < month-1; m++)
        days_prior += monthdays[m];
    return days_prior + day;
}

TH1D* temperature_over_period(const char* name, Int_t yeara, Int_t yearb, WeatherDataVec rdata){
    auto hist = new TH1D(name, "Average Temperature; Day; Temperature", 365, 1, 366);

    WeatherDataVec data = rdata.get_between(Gregorian(yeara, 1, 1), Gregorian(yearb, 12, 31));

    int monthdays[] = { 31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31 };

    std::string periodstring = std::to_string(yeara) + "-" + std::to_string(yearb);

    // histogram for the period
    for(int month = 1; month <= 12; month++){
        WeatherDataVec monthdata = data.get_by_month(month);
        std::cout << "Processing month " << month << " for \"" << name << "\" (" << periodstring << ")" << std::endl;
        for(int day = 1; day <= monthdays[month-1]; day++){
            std::stringstream regexpr;
            regexpr << yeara << "-" << month << "-" << day;
            for(int year = yeara+1; year <= yearb; year++)
                regexpr << "|" << year << "-" << month << "-" << day;
            WeatherDataVec daydata = data.get_by_regex(regexpr.str());
            if(daydata.isempty())
                continue;
            double day_avg = daydata.avgtemp();

            hist->SetBinContent(convert_dm_to_day(day, month), day_avg);
        }
    }
	return hist;
}

void temperature_over_two_periods(Int_t year1a, Int_t year1b, Int_t year2a, Int_t year2b,
                                  WeatherDataVec data) {
	std::cout << "Constructing histogram for the first period..." << std::endl;
    auto period1Hist = temperature_over_period("First period", year1a, year1b, data);
	period1Hist->SetLineColor(kBlue);

	std::cout << "Done.\nConstructing histogram for the second period..." << std::endl;
    auto period2Hist = temperature_over_period("Second period", year2a, year2b, data);
	period2Hist->SetLineColor(kRed);
	std::cout << "Done. Creating canvas and drawing..." << std::endl;

    // calculate average difference in temperature
    double temperature_diff_sum = 0;
	for(int bin = 1; bin <= 365; bin++){
        temperature_diff_sum += period2Hist->GetBinContent(bin) - period1Hist->GetBinContent(bin);
	}
	double avg_temp_diff = temperature_diff_sum/365;
    std::cout << "The average difference in temperature between the given time periods is: " << avg_temp_diff << std::endl;

    auto c = new TCanvas("periodHist", "Average temperatures for two periods", 1000, 800);
    c = c;
	period1Hist->Draw();
	period2Hist->Draw("same");

	// generate legend strings
	std::stringstream period1string;
	period1string << year1a << "-" << year1b;
	std::stringstream period2string;
	period2string << year2a << "-" << year2b;
	std::stringstream diffstring;
	diffstring << "\\text{Avg. } \\Delta{\\!T} = " << avg_temp_diff;

	// create legend
	auto leg = new TLegend(0.2, 0.15);
	leg->SetHeader("Legend", "C");
	leg->AddEntry(period1Hist, period1string.str().c_str(), "l");
	leg->AddEntry(period2Hist, period2string.str().c_str(), "l");
	leg->AddEntry((TObject*)0, diffstring.str().c_str(), "");
	leg->Draw();
}

