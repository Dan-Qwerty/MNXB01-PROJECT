void rootlogon() {
	gStyle->SetOptStat(0); //Let's make our plots look a bit better. Get rid of the stat box
	gStyle->SetOptTitle(0); //Get rid of the title (good plots use legends instead)
	gStyle->SetTitleSize(0.05, "x"); //Use bigger text on the axes
	gStyle->SetTitleSize(0.05, "y");
	gStyle->SetLabelSize(0.05, "x"); //Use bigger labels too
	gStyle->SetLabelSize(0.05, "y");
	gStyle->SetPadTopMargin(0.05); //Change the margins to fit our new sizes
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.16);

	gInterpreter->AddIncludePath("-I../include");


	//Load the classes that we want to use automatically - Convenient!
	gROOT->ProcessLine(".L csvregex.cpp+");
	gROOT->ProcessLine(".L WeatherDataVec.cpp+");
 	gROOT->ProcessLine(".L monthly.C"); 
}
