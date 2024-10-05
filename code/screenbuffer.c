#include "screenbuffer.h"

#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "util_defines.h"

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
	memset(g_buffer->data[g_buffer->cursor_line], '\0', SCREENBUFFER_ROWS);


	g_buffer->used_lines = MIN(g_buffer->used_lines++, SCREENBUFFER_LINES);
}

static void move_cursor_to_end_of_previous_line()
{
	if (g_buffer->cursor_line > 0) {
		g_buffer->cursor_line--;
		g_buffer->used_lines--;
	}
	else {
		if (g_buffer->used_lines > 0) {
			g_buffer->cursor_line = SCREENBUFFER_LINES-1;
			g_buffer->used_lines++;
		}
		else {
			// nothing to do, cursor is on "home"
		}
	}

	g_buffer->cursor_column = strlen(g_buffer->data[g_buffer->cursor_line]);
}

static void append_char(char c)
{
	if (c == '\n') {
		write_at_cursor('\0');

		move_cursor_to_next_line();
	}
	else if (c == '\b') {

		if (g_buffer->cursor_column > 0) {
			g_buffer->cursor_column--;
			write_at_cursor('\0');
		}
		else {
			move_cursor_to_end_of_previous_line();
			write_at_cursor('\0');
		}
		// TODO: override current position with space and move cursor
		// one position back with respect to column and line position.
	}
	else {
		if (g_buffer->cursor_column == SCREENBUFFER_ROWS) {
			write_at_cursor('\0');
			move_cursor_to_next_line();
		}

		write_at_cursor(c);
		g_buffer->cursor_column++;
	}
}

void screenbuffer_set(struct screenbuffer *sb)
{
	memset(sb->data, 0, sizeof(sb->data));
	sb->cursor_line   = 0;
	sb->cursor_column = 0;
	sb->used_lines    = 0;

	g_buffer = sb;
}

void screenbuffer_append(const char *s)
{
	assert(g_buffer != NULL);

	while (*s != '\0') {
		append_char(*s++);
	}

}

void screenbuffer_get_view(struct screenview *view)
{

	size_t start_line = 0;
//	size_t end_line   = 0;

	const size_t lines_to_view = MIN(g_buffer->used_lines, SCREENBUFFER_VISIBLE_LINES);

	if (g_buffer->used_lines < SCREENBUFFER_VISIBLE_LINES) {
		start_line = 0;
//		end_line   = g_buffer->used_lines;
	}
	else if (g_buffer->used_lines < SCREENBUFFER_LINES) {
		start_line = g_buffer->cursor_line - SCREENBUFFER_VISIBLE_LINES;
	}
	else {
		// TODO: handle buffer cursor starts from new
	}

	for (size_t i = 0; i < ARRAY_SIZE(view->lines); ++i) {
		if ( i <= lines_to_view) {
			view->lines[i] = g_buffer->data[(i+start_line) % SCREENBUFFER_LINES];
		}
		else {
			view->lines[i] = NULL;
		}
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







