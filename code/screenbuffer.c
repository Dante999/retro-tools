#include "screenbuffer.h"

#include <string.h>

#include "logger.h"

static struct screenbuffer *g_screenbuffer;

static void append_char(char c)
{
	g_screenbuffer->data[g_screenbuffer->cursor_pos] = c;
	g_screenbuffer->cursor_pos++;
	g_screenbuffer->cursor_pos %= sizeof(g_screenbuffer->data) - 1;
}

void sbuffer_set(struct screenbuffer *sb)
{
	g_screenbuffer = sb;
}

void sbuffer_clear()
{
	memset(g_screenbuffer->data, '\0', sizeof(g_screenbuffer->data));
	g_screenbuffer->cursor_pos = 0;
}

void sbuffer_append(const char *s)
{

	log_debug("start cursor pos: %zu\n", g_screenbuffer->cursor_pos);

	while (*s != '\0') {
		append_char(*(s++));
	}

	log_debug("end cursor pos: %zu\n", g_screenbuffer->cursor_pos);
}
