#ifndef WEATHERDATALINE_H
#define WEATHERDATALINE_H
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "csvregex.h"

//Datum
//1863-02-13;07:00:00;2.1;G
class WeatherDataLine{
    public:
    std::vector<int> date;
    std::vector<int> time;
    double temperature;

    WeatherDataLine(std::string s){
        //This will look like [1863-02-13,07:00:00,2.1,G]
        std::vector<std::string> first_split {string_split(s,";")};
        date = vstr_to_int(string_split(first_split[0],"-"));
        time = vstr_to_int(string_split(first_split[1],":"));
        temperature = std::stof(first_split[2]);
    }

    double get_temp(){
        return temperature;
    }
    int get_year(){
        return date[0];
    }
    int get_month(){
        return date[1];
    }
    int get_day(){
        return date[2];
    }
    int get_hour(){
        return time[0];
    }
    int get_minute(){
        return time[1];
    }
    int get_second(){
        return time[2];
    }
};

#endif