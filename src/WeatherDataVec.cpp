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

//averages by day
WeatherDataVec WeatherDataVec::avg_by_day(){
    std::string current_date = data[0].to_str();
    WeatherDataLine line(data[0].get_year(), data[0].get_month(), data[0].get_day(), data[0].get_temp());
    std::vector<WeatherDataLine> avgdata;
    std::vector<double> temps;
    for(auto w : data){
        if(w.to_str() == current_date){
            line.date[0] = w.get_year();
            line.date[1] = w.get_month();
            line.date[2] = w.get_day();
            temps.push_back(w.get_temp());
        } else {
            double avg_temp = std::accumulate(temps.begin(), temps.end(), 0.0)/temps.size();
            line.temperature = avg_temp;
            avgdata.push_back(line);
            current_date = w.to_str();
            temps.clear();
            temps.push_back(w.get_temp());
        }
    }
    return WeatherDataVec{avgdata};
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
    Gregorian gststr{ststr};
    Gregorian gedstr{edstr};
    for (auto w : data){
        if ((gststr <= Gregorian(w.to_str())) && (Gregorian(w.to_str()) <= gedstr)){
            v.push_back(w);
        }
    }
    return WeatherDataVec {v};
}

WeatherDataVec WeatherDataVec::get_between(int year1, int month1, int day1, int year2, int month2, int day2){
    return get_between(datedata_tostr(year1,month1,day1),datedata_tostr(year2,month2,day2));
}

WeatherDataVec WeatherDataVec::get_between(Gregorian stdate, Gregorian eddate){
    return get_between(stdate.get_year(), stdate.get_month(), stdate.get_day(), eddate.get_year(), eddate.get_month(), eddate.get_day());
}

WeatherDataVec WeatherDataVec::get_after(std::string datestr){
    std::vector<WeatherDataLine> v;
    Gregorian gdatestr{datestr};
    for (auto w : data){
        if (gdatestr <= Gregorian(w.to_str())){
            v.push_back(w);
        }
    }
    return WeatherDataVec {v};
}

WeatherDataVec WeatherDataVec::get_after(int year, int month, int day){
    return get_after(datedata_tostr(year,month,day));
}

WeatherDataVec WeatherDataVec::get_after(Gregorian inpdate){
    return get_after(inpdate.get_year(), inpdate.get_month(), inpdate.get_day());
}

WeatherDataVec WeatherDataVec::get_before(std::string datestr){
    std::vector<WeatherDataLine> v;
    Gregorian gdatestr{datestr};
    for (auto w : data){
        if (Gregorian(w.to_str()) <= gdatestr){
            v.push_back(w);
        }
    }
    return WeatherDataVec {v};
}

WeatherDataVec WeatherDataVec::get_before(int year, int month, int day){
    return get_before(datedata_tostr(year,month,day));
}

WeatherDataVec WeatherDataVec::get_before(Gregorian inpdate){
    return get_before(inpdate.get_year(), inpdate.get_month(), inpdate.get_day());
}


double WeatherDataVec::mintemp(){
    std::vector<double> v {list_temperatures()};
    return *std::min_element(v.begin(),v.end());
}

double WeatherDataVec::maxtemp(){
    std::vector<double> v {list_temperatures()};
    return *std::max_element(v.begin(),v.end());
}

double WeatherDataVec::avgtemp(){
    std::vector<double> v {list_temperatures()};
    return std::accumulate( v.begin(), v.end(), 0.0)/v.size();
}

bool WeatherDataVec::isempty(){
    return data.empty();
}
