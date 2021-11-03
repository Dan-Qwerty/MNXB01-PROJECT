#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include "Gregorian.h"
#include <iostream>


// ROOT library objects
#include <TF1.h> // 1d function class
#include <TGraph.h> // graph class
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object


void global_temperature_regression(int year1, int year2, WeatherDataVec rawdata){
    std::cout << "Slicing raw data..." << std::endl;
    WeatherDataVec data = rawdata.get_between(std::to_string(year1) + "-1-1", std::to_string(year2) + "-12-31");
    std::cout << "Averaging by day..." << std::endl;
    data = data.avg_by_day();

	Gregorian earliest_date(data[0]);
    Gregorian last_date(data[data.data.size()-1]);
    int start_day = earliest_date.get_julian_day_number();
    int end_day = last_date.get_julian_day_number();

    int data_size = data.data.size();
    double x[data_size], y[data_size];
    std::cout << "Loading data and doing computations..." << std::endl;
    for(int i = 0; i < data_size; i++){
        Gregorian thisday(data[i]);
        y[i] = data[i].get_temp();
        x[i] = ((double)thisday.get_julian_day_number() - (double)start_day)/365. + (double)earliest_date.get_year();
        if((i % 1000 == 0) || (i % 1000 == 1)){
            std::cout << "Processing " << thisday.get_year() << "-" << thisday.get_month() << "-" << thisday.get_day() << std::endl;
            std::cout << "   with x[i]=" << x[i] << "  &  y[i]=" << y[i] << std::endl;
        }
    }
    std::cout << "Done." << std::endl;

    TCanvas* c1 = new TCanvas("tempreg", (std::string("Temperature Regression from ") + std::to_string(year1) + " to " + std::to_string(year2)).c_str(),
                              1500, 600);

    TGraph* gr = new TGraph(data_size, x, y);
    TF1* increasingsin = new TF1("linearsin","[0]+[1]*x+[2]*sin(6.28318*x-[3])", (double)earliest_date.get_year(), (double)last_date.get_year()+1);
    TFitResultPtr fitptr = gr->Fit(increasingsin, "QNS");
    gr->Draw();

    // draw fit function with good resolution
    double dx = 0.05;
    int arrlen = (int)((last_date.get_year() - earliest_date.get_year() + 1)/dx);
    double xi[arrlen];
    double yo[arrlen];
    double p0 = fitptr->Value(0);
    increasingsin->SetParameter(0, p0);
    double p1 = fitptr->Value(1);
    increasingsin->SetParameter(1, p1);
    double p2 = fitptr->Value(2);
    increasingsin->SetParameter(2, p2);
    double p3 = fitptr->Value(3);
    increasingsin->SetParameter(3, p3);
    for(int i = 0; i < arrlen; i++){
        xi[i] = earliest_date.get_year() + i*dx;
        yo[i] = increasingsin->Eval(xi[i]);
    }
    TGraph* fgr = new TGraph(arrlen, xi, yo);
    fgr->SetLineColor(kRed);
    fgr->Draw("same");
}


