#ifndef CORONA_H
#define CORONA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <tuple>
#include <regex>
#include "csvregex.h"
#include "WeatherDataVec.h"
#include "Gregorian.h"

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TObject.h>


class Analyse_Corona {
	private:
		std::string _filename; //eg: "smhi-opendata_1_53430_20210926_101122_Lund.csv"
		std::string _city; //eg: "Lund"
		//tuple<int, int, int> dateCalculation(int year, int month, int date, int period) const; //determine the date of day+period from year.month.day 
		//Double_t meanOfPeriod (WeatherDataVec data, int frYear, int frMonth, int frDate, int period) const; // determine the mean temp from fY,fM,fD with step length period
		void Plot_Corona() const; //plot the figure of the relation between the temperature and number of people infected with the COVID-19
	public:
		Analyse_Corona(std::string city, std::string filename);
};

#endif /*CORONA_H*/

//eg:
//Analyse_Corona C1 = Analyse_Corona("Lund", "smhi-opendata_1_53430_20210926_101122_Lund.csv");
//Analyse_Corona C2 = Analyse_Corona("Falun","smhi-opendata_1_105370_20210926_100841_Falun.csv");
