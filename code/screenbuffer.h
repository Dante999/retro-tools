#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <stddef.h>


#define SCREENBUFFER_ROWS 80
#define SCREENBUFFER_LINES 20
#define SCREENBUFFER_VISIBLE_LINES 10

struct screenbuffer {
	char data[SCREENBUFFER_LINES][SCREENBUFFER_ROWS];
	size_t cursor_line;
	size_t cursor_column;
	size_t used_lines;
};

struct screenview {
	char *lines[SCREENBUFFER_VISIBLE_LINES];
};;

void screenbuffer_set(struct screenbuffer *sb);
void screenbuffer_append(const char *s);
void screenbuffer_print();
void screenbuffer_get_view(struct screenview *view);

#endif // SCREENBUFFER_H
