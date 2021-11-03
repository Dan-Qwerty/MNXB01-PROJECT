STANDARD = -std=c++11

INC_DIR = -Iinclude

ROOT_LIB = -I/sw/easybuild/software/MPI/GCC/5.4.0-2.26/OpenMPI/1.10.3/ROOT/6.10.02-Python-2.7.12/include -L/sw/easybuild/software/MPI/GCC/5.4.0-2.26/OpenMPI/1.10.3/ROOT/6.10.02-Python-2.7.12/lib -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic

WARNINGS = -Wall -Werror -Wextra

FLAGS = $(STANDARD) $(WARNINGS)

FILES = main.cpp src/csvregex.cpp src/Gregorian.cpp src/WeatherDataVec.cpp src/command_line.cpp

EXECUTABLE_NAME = reg

all:
	g++ $(FLAGS) $(FILES) -o $(EXECUTABLE_NAME) $(INC_DIR) $(ROOT_LIB)
