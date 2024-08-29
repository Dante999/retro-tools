#include "terminal.h"

#include <stdio.h>
#include <string.h>

void show_prompt()
{
	char input_buffer[255];


	char do_loop = 1;

	while (do_loop) {
		terminal_printstr("\n>");

		if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
			char filepath[255];

			strncpy(filepath, "files/", sizeof(filepath));
			strncat(filepath, input_buffer, sizeof(filepath) - strlen(filepath));

			char *newline_pos = strrchr(filepath, '\n');

			if (newline_pos != NULL) {
				*newline_pos = '\0';
			}

			printf("\n\n");
			terminal_printfile(filepath);
		}
		else {
			terminal_printstr("anything went wrong?!\n");
			do_loop = 0;
		}
	}

}



int main(void)
{
	terminal_init();
	
	show_prompt();
	
	
	
	//terminal_printfile("testfiles/protokol-bohrungen.txt");

#if 0
//	printf("hello \033[42m world \033[m\n");
//	printf("this line should be normal\n");
	
	print_header("Hello World");
	print_text("normal text line");
	
	printf(TERM_FG_GREEN "\n");
	printf(TERM_REVERSE TERM_BOLD "this is a test\n" TERM_RESET);
	printf(TERM_FRAMED "hi there!" TERM_RESET "\n");

	terminal_printstr("this may take a while...\n");
//
//
#endif
}
