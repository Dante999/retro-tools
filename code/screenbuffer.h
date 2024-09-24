#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#define SCREENBUFFER_LINEWIDTH 80
#define SCREENBUFFER_LINES     120

#include <stddef.h>

struct screenbuffer {
	char   data[SCREENBUFFER_LINEWIDTH * SCREENBUFFER_LINES];
	size_t cursor_pos;
};

void sbuffer_set(struct screenbuffer *sb);
void sbuffer_clear();
void sbuffer_append(const char *s);

#endif // SCREENBUFFER_H
