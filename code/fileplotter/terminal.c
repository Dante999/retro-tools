#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define TERM_FG_BLACK "\033[30m"
#define TERM_FG_GREEN "\033[32m"
#define TERM_BG_GREEN "\033[42m"
#define TERM_RESET "\033[m"
#define TERM_BOLD "\033[1m"
#define TERM_REVERSE_ON  "\033[7m"
#define TERM_REVERSE_OFF "\033[27m"
#define TERM_FRAMED "\033[51m"

#define CHAR_DELAY_MSEC 10





void terminal_init() {
	printf(TERM_FG_GREEN);
}

void print_header(const char* s)
{
//	printf("\033[30m \033[42m \033[1m %s \033[m\n", s);
	printf(TERM_FG_BLACK TERM_BG_GREEN TERM_BOLD "%s" TERM_RESET "\n", s);
}

//void print_text(const char* s)
//{
//	printf(TERM_FG_GREEN "%s" TERM_RESET "\n", s);
//}

void terminal_printstr(const char *s)
{
	for( size_t i=0; i < strlen(s); ++i) {
		putchar(s[i]);
		usleep(CHAR_DELAY_MSEC * 1000);
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