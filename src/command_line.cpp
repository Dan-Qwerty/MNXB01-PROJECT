#include <iostream>
#include <cstdlib>
#include <string>

#include "command_line.h"

std::string* fetch_command_list(std::string* argv) {
	std::string line;
	getline(std::cin, line);

	while (line.find(" ") <= line.length()) {
		int a = line.find(" ");
		*argv++ = line.substr(0, a);
		line = line.substr(a + 1, line.length() - (a + 1));
	}
	*argv++ = line;

	return argv;
}

std::string next_command(std::string* i) {
	return *i++;
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
#ifdef __unix__
		system("clear");
#endif
#ifdef _WIN32
		system("cls");
#endif
		return 0;
	}
	return 1;
}

void command_line_loop() {
	while (execute_command_list(Command_list()));
}
