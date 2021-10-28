#ifndef CORONA_H
#define CORONA_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include "WeatherDataVec.h"

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TObject.h>


class Analyse_Corona {
	private:
		tuple<int, int, int> dateCalculation(int year, int month, int date, int period); //determine the day+period from y.m.d 
		Double_t meanOfPeriod (WeatherDataVec data, int frYear, int frMonth, int frDate, int period); // determine the mean temp from fY,fM,fD with step length period
		void Plot_Corona(); //plot the figured of the relation between the temperature and number of people infected with the new coronavirus
	public:
		Analyse_Corona();
};

#endif /*CORONA_H*/
