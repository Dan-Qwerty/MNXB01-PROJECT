#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "csvregex.h"
#include "WeatherDataLine.h"
#include "WeatherDataVec.h"

int main(){
    std::string filename {"smhi-opendata_1_53430_20210926_101122_Lund.csv.txt"};
    WeatherDataVec Wdata {datavec(filename)};
    return 0;
}