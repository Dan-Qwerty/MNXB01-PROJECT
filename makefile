INC_DIR = -Iinclude

FLAGS = -Wall -Werror -Wextra

all:
	g++ main.cpp -o reg $(INC_DIR) $(FLAGS)


