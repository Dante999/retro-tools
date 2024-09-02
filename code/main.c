#include "terminal.h"

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "project_defines.h"
#include "cmd_show.h"
#include "cmd_files.h"
#include "cmd_help.h"

typedef bool (*cmd_handler)(const char *s);


cmd_handler handler[3] = {
	cmd_help,
	cmd_show,
	cmd_files
};

void show_prompt()
{
	char input_buffer[255];


	char do_loop = 1;

	while (do_loop) {
		terminal_printstr("\n\n>");

		if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {

			bool cmd_found = false;
			
			for( size_t i=0; i < ARRAY_SIZE(handler); ++i) {
				bool result = handler[i](input_buffer);

				if( result) {
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
			do_loop = 0;
		}
	}

}



int main(void)
{
	config_init();
	terminal_clear();
	terminal_init();
	
	show_prompt();
}
