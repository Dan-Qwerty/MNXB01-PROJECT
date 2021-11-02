#ifndef WEATHERDATAVEC_H
#define WEATHERDATAVEC_H

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <set>
#include "csvregex.h"
#include "WeatherDataLine.h"


class WeatherDataVec{
    public:
    std::vector<WeatherDataLine> data; 
    
    WeatherDataVec(std::vector<std::string> data_strings); // constructor

    WeatherDataVec(std::vector<WeatherDataLine> d); // constructor

    WeatherDataVec(std::string filename); //constructor

    WeatherDataVec get_by_month(int month);

    WeatherDataVec get_by_year(int year);

    WeatherDataVec get_by_day(int day);

    WeatherDataVec get_by_regex(std::string inpstr);

    WeatherDataVec get_between(std::string ststr, std::string edstr);

    WeatherDataLine operator[](int index);

    WeatherDataLine operator()(int index);

    WeatherDataVec operator()(int startindex, int endindex);

    std::vector<int> list_years();

    std::vector<int> list_days();
    
    std::vector<double> list_temperatures();

    double avgtemp();

    double maxtemp();

    double mintemp();
};

#endif /*WEATHERDATAVEC_H*/
