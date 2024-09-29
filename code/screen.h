#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "result.h"
#include "screenbuffer.h"

struct screen {
	struct screen_cfg {
		int  width;
		int  height;
		int  border_width;
		bool fullscreen;
		char font_path[255];
	} cfg;

	SDL_Window   *m_window;
	SDL_Surface  *m_screenSurface;
	SDL_Renderer *m_renderer;
	TTF_Font     *m_font;
};

struct result screen_init(struct screen *screen);

void screen_draw_string(struct screen *screen, const char *s, size_t maxlen);
void screen_draw_buffer(struct screen *screen, struct screenbuffer *buffer);
void screen_destroy(struct screen *screen);

#endif // SCREEN_H
