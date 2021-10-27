#include "csvregex.h"
#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include <iostream>


int main(){
    std::string filename {"datasets/smhi-opendata_1_53430_20210926_101122_Lund.csv"};
    WeatherDataVec Wdata {datavec(filename)};

    std::cout << Wdata.data[0].get_temp() << std::endl;

    return 0;
}

