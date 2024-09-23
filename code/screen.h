#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "result.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080 

struct screen {
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer *renderer;
	TTF_Font *font;
};

struct result screen_init(struct screen *screen);

struct result screen_load_ttf_font(
		struct screen *screen, 
		const char* font_path, 
		int font_pt_size);

void screen_draw_buffer(struct screen *screen, const char *buffer);
void screen_destroy(struct screen *screen);

#endif // SCREEN_H
