#ifndef MONTHLY_H
#define MONTHLY_H
#include <iostream>
#include <fstream>
#include <tuple>
#include <algorithm>
#include "csvregex.h"
#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include "RootClass.C"

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TVirtualFitter.h>
#include <TLatex.h>
#include <TLegend.h>


class Analyse_Monthly {
	private:
	Int_t _month;
	std::string _filename;
	void Month_tree(); //TTree building
	public:
	Analyse_Monthly(Int_t month, std::string filename);
	void Temp_PerMonth(); //plot the histo of the average temperature of the month
	void Month_Extreme(); //plot the extreme temperatures & average temperature of the month each year
};


#endif /*MONTHLY_H*/
