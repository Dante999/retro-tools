#include "terminal.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "cmd_files.h"
#include "cmd_help.h"
#include "cmd_show.h"
#include "config.h"
#include "project_defines.h"
#include "util_strings.h"
#include "logger.h"

typedef bool (*cmd_handler)(const char *s);

cmd_handler handler[3] = {cmd_help, cmd_show, cmd_files};

void show_prompt()
{
	char input_buffer[255];

	bool do_loop = true;

	while (do_loop) {
		terminal_printstr("\n\n>");

		if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {

			bool cmd_found = false;

			for (size_t i = 0; i < ARRAY_SIZE(handler); ++i) {
				bool result = handler[i](input_buffer);

				if (result) {
					cmd_found = true;
					break;
				}
			}

			if (!cmd_found) {
				terminal_printstr("Unknown command!\n");
			}
		}
		else {
			terminal_printstr("anything went wrong?!\n");
			do_loop = false;
		}
	}
}





int main(int argc, char *argv[])
{
	char resources_dir[255];

	if ( argc == 2) {
		strncpy(resources_dir, argv[1], sizeof(resources_dir));
		log_debug("custom resource dir given: %s\n", resources_dir);
	}
	else {
		strncpy(resources_dir, "./resources" , sizeof(resources_dir));
	}

	char configfile[255];
	strncpy(configfile, resources_dir, sizeof(configfile));
	strncat(configfile, "/retro-os.conf", sizeof(configfile)-1);


	struct result ret = config_init(configfile);

	if (!ret.success) {
		log_error("unable to load config file '%s' : %s\n", configfile, ret.msg);
		return -1;
	}

// -------------------- SDL starts here ----------------------------------------


// -------------------- SDL ends here -----------------------------------------






#if 0
	terminal_clear();
	terminal_init();

	show_prompt();
#endif
}
