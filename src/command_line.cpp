#include <iostream>
#include <cstdlib>
#include <string>

#include "command_line.h"

std::string filename;

std::string* fetch_command_list(std::string* argv) {
	std::string line;
	getline(std::cin, line);

	while (line.find(" ") <= line.length()) {
		int a = line.find(" ");
		if(line.find("'") == 0) {
			line=line.substr(1, line.length() - 1);
			a = line.find("'");

			*argv++ = line.substr(0, a);

			line = line.substr(a + 1, line.length() - (a + 1));

		}else {
			*argv++ = line.substr(0, a);
			line = line.substr(a + 1, line.length() - (a + 1));
		}

		
		
	}
	*argv++ = line;

	return argv;
}

std::string next_command(std::string*& i) {
	return *i++;
}

void print_command_line_error(int error) {
	std::cout << "Error: " << error << ". Exiting..." << std::endl;
}

int execute_command_list(Command_list command_list) {

	std::string t;
	std::string* it = command_list.begin();

	t = next_command(it);

	if (t == "") {
		return 1;
	}
	else if (t == "exit") {
		return 0;
	}
	else if (t == "clear") {
		system("clear");
		return 1;
	}
	else if (t == "help") {

		return 1;
	}
	else if (t == "filename") {
		t = next_command(it);
		if (t == "") {
			print_command_line_error(error::no_filename);
			return 0;
		}
		filename = t;
		return 1;
	}
	else if (t == "where") {
		std::cout << filename << std::endl;
		return 1;
	}
	return 1;
}



void command_line_loop() {
	while (execute_command_list(Command_list()));
}
