#include "WeatherDataVec.h"

//Constructor for input of std::vector<std::string>
WeatherDataVec::WeatherDataVec(std::vector<std::string> data_strings){
	std::vector<WeatherDataLine> v;
    for (std::string m : data_strings){
        v.push_back(WeatherDataLine {m});
    }
    data = v;
}

//Constructor for input of std::string (string should be filename)
WeatherDataVec::WeatherDataVec(std::string filename){
    std::vector<std::string> data_strings {datavec(filename)};
    std::vector<WeatherDataLine> v;
    for (std::string m : data_strings){
        v.push_back(WeatherDataLine {m});
    }
    data = v;
}

//Constructor for input of std::vector<WeatherDataLine>
WeatherDataVec::WeatherDataVec(std::vector<WeatherDataLine> d) : data{d} {}

//Creates new WeatherDataVec from all entries which match the month
WeatherDataVec WeatherDataVec::get_by_month(int month){
    std::vector<WeatherDataLine> v;
    for(auto x : data){
        if (x.get_month() == month){
            v.push_back(x);
        }
    }
    return WeatherDataVec {v};
}

//Creates new WeatherDataVec from all entries which match the year
WeatherDataVec WeatherDataVec::get_by_year(int year){
    std::vector<WeatherDataLine> v;
    for(auto x : data){
        if (x.get_year() == year){
            v.push_back(x);
        }
    }
    return WeatherDataVec {v};
}

//Creates new WeatherDataVec from all entries which match the day
WeatherDataVec WeatherDataVec::get_by_day(int day){
    std::vector<WeatherDataLine> v;
    for(auto x : data){
        if (x.get_day() == day){
            v.push_back(x);
        }
    }
    return WeatherDataVec {v};
}

//Yields list of all years in data (without duplicates)
std::vector<int> WeatherDataVec::list_years(){
    std::set<int> s;
    for (auto x : data){
        s.insert(x.get_year());
    }
    std::vector<int> v(s.begin(),s.end());
    return v;
}

//Yields list of all days in data (without duplicates)
std::vector<int> WeatherDataVec::list_days(){
    std::set<int> s;
    for (auto x : data){
        s.insert(x.get_day());
    }
    std::vector<int> v(s.begin(),s.end());
    return v;
}

//Yields list of all temperatures in data
std::vector<double> WeatherDataVec::list_temperatures(){
    std::vector<double> v;
    for(auto w : data){
        v.push_back(w.get_temp());
    }
    return v;
}

//Provides conventional indexing
WeatherDataLine WeatherDataVec::operator[](int index){
    return data[index];
}

//Provides indexing feature only with () rather than []
WeatherDataLine WeatherDataVec::operator()(int index){
    return data[index];
}

//Provides slicing ranges (a,b) gives the vector with indices from a-b (inclusive)
WeatherDataVec WeatherDataVec::operator()(int startindex, int endindex){
    std::vector<WeatherDataLine> v(data.begin()+startindex,data.end()+endindex+1);
    WeatherDataVec Wdata {v};
    return Wdata;
}

//Provides functionality to get terms which match regex corresponding to string input
WeatherDataVec WeatherDataVec::get_by_regex(std::string inpstr){
    //Some preprocessing in case someone does a silly input
    std::regex wildcard {"\\*+"};
    std::regex mainstr {std::regex_replace(inpstr, wildcard, ".+")};
    std::vector<WeatherDataLine> v;
    for(auto w : data){
        if (std::regex_match(w.to_str(),mainstr)){
            v.push_back(w);
        }
    }
    return WeatherDataVec {v};
}

//This gets all dates between ststr and edstr
WeatherDataVec WeatherDataVec::get_between(std::string ststr, std::string edstr){
    std::vector<WeatherDataLine> v;
    for (auto w : data){
        if ((ststr < w.to_str()) && (w.to_str() < edstr)){
            v.push_back(w);
        }
    }
    return WeatherDataVec {v};
}
