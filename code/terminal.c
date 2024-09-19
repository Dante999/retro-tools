#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "config.h"

#define TERM_FG_BLACK "\033[30m"
#define TERM_FG_GREEN "\033[32m"
#define TERM_BG_GREEN "\033[42m"
#define TERM_RESET "\033[m"
#define TERM_BOLD "\033[1m"
#define TERM_REVERSE_ON  "\033[7m"
#define TERM_REVERSE_OFF "\033[27m"
#define TERM_FRAMED "\033[51m"




useconds_t g_char_delay_usec = 50;


void terminal_clear() {
	printf("\e[1;1H\e[2J");
}

void terminal_init() {

///	g_char_delay_usec = config_get()->terminal_print_delay_msec * 1000;
	printf(TERM_FG_GREEN);
}

void terminal_printstr(const char *s)
{
	for( size_t i=0; i < strlen(s); ++i) {
		putchar(s[i]);
		usleep(g_char_delay_usec);
		fflush(stdout);
	}
}

void terminal_printheader(const char *s)
{
	char tmp[255];

	strncpy(tmp, s, sizeof(tmp));

	char *newline_pos = strrchr(tmp, '\n');

	if (newline_pos != NULL) {
		*newline_pos = '\0';
	}

	char buffer[255];

	snprintf(buffer, sizeof(buffer), "%-80s", tmp);

	printf(TERM_REVERSE_ON TERM_BOLD);
	terminal_printstr(buffer);
	printf(TERM_RESET "\n");
	terminal_init();

}

void terminal_printfile(const char *filename)
{
	FILE *f = fopen(filename, "r");

	if (f == NULL) {
		terminal_printstr("file not found!\n");
		return;
	}

	char buffer[255];

	while( fgets(buffer, sizeof(buffer), f) ) {

		if (buffer[0] == '#') {
			terminal_printheader(buffer+2);
		}
		else {
			terminal_printstr(buffer);
		}
	}

}
