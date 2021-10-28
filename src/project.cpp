#include "monthly.h"
#include "corona.h"

void projectQL(Int_t month) {
	Analyse_Monthly M(month);
	M.Temp_PerMonth();
	M.Month_Extreme();
	Analyse_Corona C;
}


