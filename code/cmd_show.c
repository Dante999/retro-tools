#include "cmd_show.h"

#include <string.h>
#include <stdio.h>

#include "project_defines.h"
#include "util_strings.h"
#include "terminal.h"



bool cmd_show(const char* s)
{
	if (!utils_strstartswith(s, "show")) {
		return false;
	}

	if (strlen(s) < strlen("show")+1) {
		terminal_printstr("ERROR: no file given!");
		return true;
	}

	char filepath[255];

	strncpy(filepath, FILES_SUBDIR "/", sizeof(filepath));
	strncat(filepath, s+strlen("show")+1, sizeof(filepath) - strlen(filepath));

	char *newline_pos = strrchr(filepath, '\n');

	if (newline_pos != NULL) {
		*newline_pos = '\0';
	}

	printf("\n");
	terminal_printfile(filepath);

	return true;
}