#ifndef GREGORIAN_H
#define GREGORIAN_H

#include <iostream>
#include <string>
#include <vector>
#include "WeatherDataLine.h"
#include "csvregex.h"

class Gregorian{
    public:
    int year;
    int month;
    int day;
    int jdn;

    //initialize from (year,month,day)
    Gregorian(int Y,int M, int D);

    //initialize from Julian Day Number
    Gregorian(int J);

    //initialize from date string
    Gregorian(std::string datestr);

	//initialize from a WeatherDataLine
	Gregorian(WeatherDataLine line);

    int get_year();

    int get_month();

    int get_day();

    int get_julian_day_number();

    std::string get_datestr();

    //Add dates together
    Gregorian operator+(Gregorian Gdate);

    //Add days to current date
    Gregorian operator+(int days);

    //Add dates together
    Gregorian operator+=(Gregorian Gdate);

    //Add days to current date
    Gregorian operator+=(int days);

    //Subtract days 
    Gregorian operator-(int days);

    //Subctract days
    Gregorian operator-=(int days);

    bool operator==(Gregorian GDate);

    bool operator<=(Gregorian GDate);

    bool operator<(Gregorian GDate);

    bool operator>(Gregorian GDate);

    bool operator>=(Gregorian GDate);
};

#endif /*GREGORIAN_H*/
