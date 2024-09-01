#include "cmd_files.h"

#include <dirent.h>
#include <stddef.h>

#include "project_defines.h"
#include "terminal.h"

bool cmd_files(const char *s)
{
	if (!utils_strstartswith(s, "files")) {
		return false;
	}

	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir (FILES_SUBDIR)) != NULL) {

		while ((ent = readdir (dir)) != NULL) {
			if (utils_strstartswith(ent->d_name, "..")) {
				terminal_printstr(ent->d_name+2);
			}
			else {
				terminal_printstr(ent->d_name);
			}
		}
		
		closedir (dir);
	
	}
	else {
		terminal_printstr("ERROR: unable to open dir!\n");
	}

	return true;
}