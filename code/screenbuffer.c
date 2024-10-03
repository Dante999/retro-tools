#include "screenbuffer.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>

static struct screenbuffer *g_buffer = NULL;


static void write_at_cursor(char c)
{
	printf("writing at [%zu][%zu] = %c\n", 
			g_buffer->cursor_line, 
			g_buffer->cursor_column, 
			c);

	g_buffer->data[g_buffer->cursor_line][g_buffer->cursor_column] = c;
}

static void move_cursor_to_next_line()
{
	g_buffer->cursor_column = 0;
	g_buffer->cursor_line++;

	g_buffer->cursor_line %= SCREENBUFFER_LINES;
}


static void append_char(char c)
{
	if (c == '\n') {
		write_at_cursor(c);

		move_cursor_to_next_line();
	}
	else if (c == '\b') {
		// TODO: override current position with space and move cursor
		// one position back with respect to column and line position.
	}
	else {
		if (g_buffer->cursor_column == SCREENBUFFER_ROWS) {
			write_at_cursor('\n');
			move_cursor_to_next_line();
		}

		write_at_cursor(c);
		g_buffer->cursor_column++;
	}
}

void screenbuffer_set(struct screenbuffer *sb)
{
	memset(sb->data, 0, sizeof(sb->data));
	sb->cursor_line = 0;
	sb->cursor_column = 0;

	g_buffer = sb;
}

void screenbuffer_append(const char *s)
{
	assert(g_buffer != NULL);

	while (*s != '\0') {
		append_char(*s++);
	}

}

void screenbuffer_print()
{
	char buffer[255];

	printf("#####|");
	for (size_t i=0; i < SCREENBUFFER_ROWS; ++i) {
		printf("-");
	}
	printf("|\n");

	for (size_t i=0; i < SCREENBUFFER_LINES; ++i) {
	
		memset(buffer, '\0', sizeof(buffer));

		for (size_t j=0; j < SCREENBUFFER_ROWS; ++j) {

			char c = g_buffer->data[i][j];

			if (c == '\n') {
				buffer[j] = '\0';
				break;
			}
			else {
				buffer[j] = c;
			}
		}

		printf("%03zu: |%s|\n", i, buffer);
	}
}







