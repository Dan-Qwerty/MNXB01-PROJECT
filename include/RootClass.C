#ifndef RootClasses_C
#define RootClasses_C

#include <TObject.h>
#include <iostream>

using namespace std;

class Year : public TObject
{
	public:
		Int_t year;
		Int_t nData;
		Year();
		ClassDef(Year, 1);
};

ClassImp(Year)

Year::Year():TObject(), year(0), nData(0) 
{

}



class TempData : public TObject
{
	public:
		Double_t temp;
		TempData();
		ClassDef(TempData, 1);
};

ClassImp(TempData)

TempData::TempData():TObject(), temp(0.0)
{

}

#endif
