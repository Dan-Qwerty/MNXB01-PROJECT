#include "csvregex.h"
#include "WeatherDataLine.h"
#include "WeatherDataVec.h"
#include <iostream>


int main(){
    std::string filename {"datasets/smhi-opendata_1_53430_20210926_101122_Lund.csv"};
    WeatherDataVec Wdata {datavec(filename)};

    //std::cout << Wdata.data[0].get_temp() << std::endl;

	
	WeatherDataVec datamonth = Wdata.get_by_month(1);
	//WeatherDataVec datayear = datamonth.get_by_year(2010);
	for(unsigned i = 0; i < datamonth.data.size(); i++){
		std::cout << datamonth.data[i].get_year() << " " << datamonth.data[i].get_temp() << std::endl;
	}
	
    return 0;
}

