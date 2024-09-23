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
#include "screen.h"

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


char *create_relative_path(char* dst, size_t maxlen, const char* base_path, const char* filename)
{
	strncpy(dst, base_path, maxlen);
	strncat(dst, "/", maxlen);
	strncat(dst, filename, maxlen);

	return dst;
}

int main(int argc, char *argv[])
{
	char resources_dir[255];
	char tmp_filepath[512];
	struct result ret;

	if ( argc == 2) {
		strncpy(resources_dir, argv[1], sizeof(resources_dir));
		log_debug("custom resource dir given: %s\n", resources_dir);
	}
	else {
		strncpy(resources_dir, "./resources" , sizeof(resources_dir));
	}

	create_relative_path(tmp_filepath, sizeof(tmp_filepath), resources_dir, "retro-os.conf");

	ret = config_init(tmp_filepath);
	if (!ret.success) {
		log_error("unable to load config file '%s' : %s\n", tmp_filepath, ret.msg);
		return -1;
	}

	// -------------------- SDL starts here ----------------------------------------

	struct screen screen;

	ret = screen_init(&screen);
	if (!ret.success) {
		log_error("unable to init screen: %s\n", ret.msg);
		return -1;
	}

	create_relative_path(tmp_filepath, sizeof(tmp_filepath), resources_dir, config_gets(CFG_TERMINAL_FONT));

	ret = screen_load_ttf_font(&screen, tmp_filepath, config_geti(CFG_TERMINAL_FONT_SIZE));
	if (!ret.success) {
		log_error("unable to load font: %s\n", ret.msg);
		return -1;
	}

	screen_draw_buffer(&screen, "I guess hello?!\nHopefully this is in a newline :)\n");

	SDL_RenderPresent(screen.renderer);
	SDL_Delay(6000);


	screen_destroy(&screen);

	return 0;
	// -------------------- SDL ends here -----------------------------------------






#if 0
	terminal_clear();
	terminal_init();

	show_prompt();
#endif
}
