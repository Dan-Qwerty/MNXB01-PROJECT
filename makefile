STANDARD = -std=c++11

INC_DIR = -Iinclude

WARNINGS = -Wall -Werror -Wextra

FLAGS = $(STANDARD) $(WARNINGS)

FILES = main.cpp src/csvregex.cpp src/WeatherDataVec.cpp

EXECUTABLE_NAME = reg

all:
	g++ $(FLAGS) $(FILES) -o $(EXECUTABLE_NAME) $(INC_DIR)


