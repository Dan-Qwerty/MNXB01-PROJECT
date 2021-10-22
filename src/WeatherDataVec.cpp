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
#include "WeatherDataVec.h"

WeatherDataVec WeatherDataVec::get_by_month(int month){
    vector<WeatherDataLine> v;
    for(auto x : data){
        if (x.get_month() == month){
            v.push_back(x);
        }
    }
    return WeatherDataVec {v};
}

WeatherDataVec WeatherDataVec::get_by_year(int year){
    vector<WeatherDataLine> v;
    for(auto x : data){
        if (x.get_day() == day){
            v.push_back(x);
        }
    }
    return WeatherDataVec {v};
}

WeatherDataVec WeatherDataVec::get_by_day(int day){
    vector<WeatherDataLine> v;
    for(auto x : data){
        if (x.get_day() == day){
            v.push_back(x);
        }
    }
    return WeatherDataVec {v};
}

vector<int> WeatherDataVec::list_years(){
    std::set<int> s;
    for (auto x : data){
        s.insert(x.get_year());
    }
    std::vector<int> v(s.begin(),s.end());
    return v;
}

vector<int> WeatherDataVec::list_days(){
    std::set<int> s;
    for (auto x : data){
        s.insert(x.get_day());
    }
    std::vector<int> v(s.begin(),s.end());
    return v;
}