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


//converts vector of strings to vector of ints
std::vector<int> vstr_to_int(std::vector<std::string> str_vec){
    std::string str;
    std::vector<int> int_vec;
    std::transform(str_vec.begin(), str_vec.end(), std::back_inserter(int_vec), [](const std::string& str) { return std::stoi(str); });
    return int_vec;
}

//Get semi-raw data from csv
std::vector<std::string> datavec(std::string filename){
    std::vector<std::string> v;
    std::string line;
    std::ifstream file (filename);
    std::regex re ("[0-9]{4}-[0-9]{2}-[0-9]{2};[0-9]{2}:[0-9]{2}:[0-9]{2};-{0,1}[0-9]{1,}.[0-9];G");
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

std::string datedata_tostr(int year, int month, int day){
    return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
}