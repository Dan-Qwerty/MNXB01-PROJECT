INC_DIR = -Iinclude

FLAGS = -Wall -Werror -Wextra

FILES = main.cpp src/WeatherDataVec.cpp

EXECUTABLE_NAME = reg

all:
	g++ $(FILES) -o $(EXECUTABLE_NAME) $(INC_DIR) $(FLAGS)


