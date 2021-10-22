#ifndef WEATHERDATAVEC_H
#define WEATHERDATAVEC_H
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "csvregex.h"
#include "WeatherDataLine.h"

class WeatherDataVec{
    public:
    std::vector<WeatherDataLine> data;
    
    WeatherDataVec(std::vector<std::string> data_strings){
        std::vector<WeatherDataLine> v;
        for (std::string m : data_strings){
            v.push_back(WeatherDataLine {m});
        }
        data = v;
    }

    WeatherDataVec(std::vector<WeatherDataLine> d) : data(d) {}

    //Now the good stuff

    WeatherDataVec get_by_month(int month);

    WeatherDataVec get_by_year(int year);

    WeatherDataVec get_by_day(int day);

    vector<int> list_years();

    vector<int> list_days();

};

#endif
