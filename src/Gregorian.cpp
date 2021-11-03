#include "Gregorian.h"

/*
To see why this works consult the link: https://en.wikipedia.org/wiki/Julian_day
*/

//initialize from (year,month,day)
Gregorian::Gregorian(int Y,int M, int D){
    year = Y;
    month = M;
    day = D;
    jdn = (1461 * (Y + 4800 + (M - 14)/12))/4 +(367 * (M - 2 - 12 * ((M - 14)/12)))/12 - (3 * ((Y + 4900 + (M - 14)/12)/100))/4 + D - 32075;
}

//initialize from date str "year-month-day"
Gregorian::Gregorian(std::string datestr){
    std::vector<int> v {vstr_to_int(string_split(datestr,"-"))};
    int Y = v[0];
    int M = v[1];
    int D = v[2];
    year = Y;
    month = M;
    day = D;
    jdn = (1461 * (Y + 4800 + (M - 14)/12))/4 +(367 * (M - 2 - 12 * ((M - 14)/12)))/12 - (3 * ((Y + 4900 + (M - 14)/12)/100))/4 + D - 32075;
}

//initialize from WeatherDataLine
Gregorian::Gregorian(WeatherDataLine line){
	year = line.get_year();
	month = line.get_month();
	day = line.get_day();
	jdn = (1461 * (year + 4800 + (month - 14)/12))/4 +(367 * (month - 2 - 12 * ((month - 14)/12)))/12 - (3 * ((year + 4900 + (month - 14)/12)/100))/4 + day - 32075;
}

//initialize from Julian Day Number
Gregorian::Gregorian(int J){
    const int y = 4716;
    const int j = 1401;
    const int m = 2;
    const int n = 12;
    const int r = 4;
    const int p = 1461;
    const int v = 3;
    const int u = 5;
    const int s = 153;
    const int w = 2;
    const int B = 274277;
    const int C = -38;
    
    const int f = J + j + (((4 * J + B) / 146097) * 3) / 4 + C;
    const int e = r * f + v;
    const int g = (e % p) / r;
    const int h = u * g + w;

    int D = ((h % s)) / u + 1;
    int M = ((h / s + m) % n) + 1;
    int Y = (e / p) - y + (n + m - M) / n;

    day = D;
    month = M;
    year = Y;
    jdn = J;
}

int Gregorian::get_year(){
    return year;
}

int Gregorian::get_month(){
    return month;
}

int Gregorian::get_day(){
    return day;
}

int Gregorian::get_julian_day_number(){
    return jdn;
}

std::string Gregorian::get_datestr(){
    return datedata_tostr(year,month,day);
}

//Add dates together
Gregorian Gregorian::operator+(Gregorian Gdate){
    return Gregorian {jdn + Gdate.get_julian_day_number()};
}

//Add days to current date
Gregorian Gregorian::operator+(int days){
    return Gregorian {jdn + days};
}

Gregorian Gregorian::operator+=(Gregorian Gdate){
    return *this + Gdate;
}

Gregorian Gregorian::operator+=(int days){
    return *this + days;
}

Gregorian Gregorian::operator-(int days){
    return *this + (-days);
}

Gregorian Gregorian::operator-=(int days){
    return *this - days;
}

bool Gregorian::operator==(Gregorian GDate){
    return (jdn == GDate.get_julian_day_number());
}

bool Gregorian::operator<=(Gregorian GDate){
    return (jdn <= GDate.get_julian_day_number());
}

bool Gregorian::operator<(Gregorian GDate){
    return (jdn < GDate.get_julian_day_number());
}

bool Gregorian::operator>(Gregorian GDate){
    return (jdn > GDate.get_julian_day_number());
}

bool Gregorian::operator>=(Gregorian GDate){
    return (jdn >= GDate.get_julian_day_number());
}

