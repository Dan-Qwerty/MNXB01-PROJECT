#include "monthly.h"
#include "corona.h"

void projectQL(Int_t month, std::string city, std::string filename) {
	Analyse_Monthly M(month, filename);
	M.Temp_PerMonth();
	M.Month_Extreme();
	Analyse_Corona C(city, filename);
}

//eg
//projectQL(6,"Lund","smhi-opendata_1_53430_20210926_101122_Lund.csv")
//projectQL(8,"Falun","smhi-opendata_1_105370_20210926_100841_Falun.csv")

