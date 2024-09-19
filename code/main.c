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

int main(void)
{
	struct result ret = config_init("resources/retro-os.conf");

	if (!ret.success) {
		printf("ERROR when loading config file: %s\n", ret.msg);
		return -1;
	}

	config_print();

	printf("hello: '%s'\n", config_gets("helloo"));
	printf("my_int_value: '%d'\n", config_geti("my_int_value"));

	return 1;

	// ----------------

	terminal_clear();
	terminal_init();

	show_prompt();
}
