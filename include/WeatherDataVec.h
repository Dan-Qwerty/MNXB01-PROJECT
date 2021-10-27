#ifndef WEATHERDATAVEC_H
#define WEATHERDATAVEC_H

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include "csvregex.h"
#include "WeatherDataLine.h"


class WeatherDataVec{
    public:
    std::vector<WeatherDataLine> data; 
    
    WeatherDataVec(std::vector<std::string> data_strings); // constructor

    WeatherDataVec(std::vector<WeatherDataLine> d); // constructor

    WeatherDataVec get_by_month(int month);

    WeatherDataVec get_by_year(int year);

    WeatherDataVec get_by_day(int day);

    std::vector<int> list_years();

    std::vector<int> list_days();
    
    std::vector<double> list_temperatures();

};

#endif /*WEATHERDATAVEC_H*/
