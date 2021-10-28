#ifndef MONTHLY_H
#define MONTHLY_H
#include <iostream>
#include <fstream>
#include <algorithm>
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



class Analyse_Monthly {
	private:
	Int_t _month;
	void Month_tree(); //TTree building
	public:
	Analyse_Monthly(Int_t month);
	void Temp_PerMonth(); //plot the histo of the average temperature of the month
	void Month_Extreme(); //plot the extreme temperatures & average temperature of the month
};


#endif /*MONTHLY_H*/
