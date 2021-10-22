#ifndef CSVREGEX_H
#define CSVREGEX_H

#include <string>
#include <vector>


//Splits string up by delimiter
//Ex: Hello;World -> [Hello,World] if delim is ;
std::vector<std::string> string_split(std::string s, std::string delim);

//converts vector of strings to vector of ints
std::vector<int> vstr_to_int(std::vector<std::string> str_vec);

//Get semi-raw data from csv
std::vector<std::string> datavec(std::string filename);

#endif