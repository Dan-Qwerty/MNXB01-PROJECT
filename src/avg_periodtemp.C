#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

// ROOT library objects
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object


int convert_dm_to_day(int day, int month){
    int monthdays[] = { 31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31 };

    int days_prior = 0;
    for(int m = 0; m < month-1; m++)
        days_prior += monthdays[m];
    return days_prior + day;
}

TH1D* temperature_over_period(Int_t year1a, Int_t year1b, WeatherDataVec data){
    auto hist = new TH1D("hist", "Average Temperature; Day; Temperature", 365, 1, 365);

   // histogram for the first period
    for(int day = 1; day <= 31; day++){
        for(int month = 1; month <= 12; month++){
            if(day == 29 && month == 1)
                continue; // skip the leap year problems

            // compute the average over the average.
            std::vector<double> day_sums;
            for(int year = year1a; year <= year1b; year++){
                std::vector<double> daydata = data.get_by_year(year).get_by_day(day).get_by_month(month).list_temperatures();
                double day_avg = std::accumulate(daydata.begin(), daydata.end(), 0.0)/daydata.size();
                day_sums.push_back(day_avg);
            }
            double day_avg = std::accumulate(day_sums.begin(), day_sums.end(), 0.0)/day_sums.size();

            hist->SetBinContent(convert_dm_to_day(day, month), day_avg);
        }
    }
	return hist;
}

void temperature_over_two_periods(Int_t year1a, Int_t year1b, Int_t year2a, Int_t year2b) {
//                                  WeatherDataVec data) {
	WeatherDataVec data(datavec("smhi-opendata_1_53430_20210926_101122_Lund.csv"));
    auto period1Hist = temperature_over_period(year1a, year1b, data);
    auto period2Hist = temperature_over_period(year2a, year2b, data);


    auto c = new TCanvas("periodHist", "Average temperatures for two periods", 800, 800);
	period1Hist->Draw();
	period2Hist->Draw("same");
}

