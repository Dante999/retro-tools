#include "cmd_files.h"

#include <dirent.h>
#include <stddef.h>
#include <string.h>

#include "project_defines.h"
#include "terminal.h"
#include "util_strings.h"

bool cmd_files(const char *s)
{
	if (!utils_strstartswith(s, "files")) {
		return false;
	}

	DIR           *dir;
	struct dirent *ent;

	if ((dir = opendir(FILES_SUBDIR)) != NULL) {

		while ((ent = readdir(dir)) != NULL) {

			if (strcmp(ent->d_name, ".") == 0 ||
			    strcmp(ent->d_name, "..") == 0) {
				continue;
			}

			terminal_printstr("    ");
			terminal_printstr(ent->d_name);
			terminal_printstr("\n");
		}

		closedir(dir);
	}
	else {
		terminal_printstr("ERROR: unable to open dir!\n");
	}

	return true;
}
