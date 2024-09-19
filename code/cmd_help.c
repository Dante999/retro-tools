#include "cmd_help.h"

#include <string.h>

#include "terminal.h"
#include "util_strings.h"

bool cmd_help(const char *s)
{
	if (!utils_strstartswith(s, "help")) {
		return false;
	}

	terminal_printstr("this is a list of all available commands:\n");
	terminal_printstr("-----------------------------------------\n");
	terminal_printstr("help                prints this screen\n");
	terminal_printstr(
	    "files               shows a list of all available files\n");
	terminal_printstr(
	    "show <filename>     prints the content of the given file\n");

	return true;
}