#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <string>


namespace error {
	enum Error {
		none, space
	};
}


std::string* fetch_command_list(std::string* argv);

struct Command_list {
	Command_list() : last(fetch_command_list(command_list)){}
	std::string* begin() { return command_list; }
	std::string* end() { return last; }

private:
	std::string command_list[16], * last;
};

void command_line_loop();





#endif