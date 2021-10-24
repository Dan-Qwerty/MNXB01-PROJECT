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

  // Tell the compiler where to look for headers. Use the same kinds of flags
  //  that you've seen in the course. Note that paths cannot be relative or use
  //  ~
  gInterpreter->AddIncludePath("-I/home/ql93/git/MNXB01-PROJECT/include");


  //  You can add multiple flags if you have multiple directories to add
  // gSystem->AddIncludePath("-I/home/einarelen/project/include -I/home/einarelen/project/external/include");
  // Or you can keep adding them one by one, which looks neater
  // gSystem->AddIncludePath("-I/home/einarelen/project/external/include");

  // If you want to add flags to the linking process, use the
  // gSystem->AddLinkedLibs() function. Use the same kinds of flags that you are
  // used to from the course
  //
  // Requires that you have a shared library and that it can be found in the
  // LD_LIBRARY_PATH environment variable
  // gSystem->AddLinkedLibs(" -L ~/project/external/lib64 -lfmt " )
  // If you want to skip that, you can link using the Rpath method
  // gSystem->AddLinkedLibs(" -L/home/einarelen/project/external/lib64 -Wl,-rpath=/home/einarelen/project/external/lib64 -lfmt");

  //gROOT->ProcessLine(".L src/tempTrender.cpp+"); //Load the classes that we want to use automatically - Convenient!
	gROOT->ProcessLine(".L csvregex.cpp+");
	gROOT->ProcessLine(".L WeatherDataVec.cpp+");
	//gROOT->ProcessLine(".L ../include/");
	//gROOT->ProcessLine(".L ../include/csvregex.c");
	//gROOT->ProcessLine(".L ..csvregex.cpp");
	//gROOT->ProcessLine(".L ..csvregex.cpp");
 	gROOT->ProcessLine(".L monthly.c"); //The + means to recompile only if it changed sine last time
	//temPerMonth(3);
  //Now you can type project() to invoke the function defined in project
  //You can also create and invoke functions in a temptrender manually by doing e.g. tempTrender t(pathToFile); t.hotCold();
}
