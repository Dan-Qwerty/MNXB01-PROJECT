#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

//Splits string up by delimiter
//Ex: Hello;World -> [Hello,World] if delim is ;
std::vector<std::string> string_split(std::string s, std::string delim){
    std::regex re(delim);
    std::sregex_token_iterator it{s.begin(),s.end(),re,-1};
    std::vector<std::string> terms{it,{}};
    return terms;
}

std::vector<int> vstr_to_int(std::vector<std::string> str_vec){
    std::string str;
    std::vector<int> int_vec;
    std::transform(str_vec.begin(), str_vec.end(), std::back_inserter(int_vec), [](const std::string& str) { return std::stoi(str); });
    return int_vec;
}

//Datum
//1863-02-13;07:00:00;2.1;G
class WeatherDataLine{
    public:
    std::vector<int> date;
    std::vector<int> time;
    double temperature;
    //The initialization here is a little messy 
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


//Get semi-raw data from csv
std::vector<std::string> datavec(std::string filename){
    std::vector<std::string> v;
    std::string line;
    std::ifstream file (filename);
    std::regex re ("[0-9]{4}-[0-9]{2}-[0-9]{2};[0-9]{2}:[0-9]{2}:[0-9]{2};[0-9]{1,}.[0-9];G");
    std::smatch m;
    while (std::getline(file,line)){
        std::regex_search(line,m,re);
        for(std::string x : m){
            if (x != ""){
                v.push_back(x);
            }
        }
    }
    file.close();
    return v;
}

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
};

int main(){
    std::string filename {"smhi-opendata_1_53430_20210926_101122_Lund.csv.txt"};
    WeatherDataVec Wdata {datavec(filename)};
    return 0;
}