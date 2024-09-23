#include "screen.h"

#include "logger.h"

static void screen_render_string(
		SDL_Renderer *renderer,
		int x,
		int y,
		const char *text,
		TTF_Font *font,
		SDL_Rect *rect,
		SDL_Color *color
		) {
	SDL_Surface *surface;
	SDL_Texture *texture;

	surface = TTF_RenderText_Solid(font, text, *color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect->x = x;
	rect->y = y;
	rect->w = surface->w;
	rect->h = surface->h;
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, rect);
	SDL_DestroyTexture(texture);
}

struct result screen_init(struct screen *screen) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return create_result_fmt(false,
				"could not initialize sdl2: %s\n", SDL_GetError());
	}

	screen->window = SDL_CreateWindow(
			"retro-os",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
			);

	if (screen->window == NULL) {
		return create_result_fmt(false, "could not create window: %s\n", SDL_GetError());
	}

	screen->screenSurface = SDL_GetWindowSurface(screen->window);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	screen->renderer = SDL_CreateRenderer(screen->window, -1, render_flags);


	return create_result_success();
}

struct result screen_load_ttf_font(struct screen *screen, const char* font_path, int font_pt_size)
{
	TTF_Init();
	screen->font = TTF_OpenFont(font_path, font_pt_size);

	if (screen->font == NULL) {
		return create_result_fmt(false, "could not initialize font %s: %s\n", font_path, TTF_GetError());
	}

	return create_result_success();
}

void screen_destroy(struct screen *screen) {
	SDL_DestroyWindow(screen->window);
	SDL_Quit();
}




void screen_draw_buffer(struct screen *screen, const char *buffer)
{
	// create a rectangle to update with the size of the rendered text
	SDL_Rect text_rect;
	text_rect.y = 10;
	text_rect.h = 0;

	// The color for the text we will be displaying
//	SDL_Color white = {255, 255, 255, 0};
	SDL_Color white = {0, 255, 0, 0};

	char linebuffer[255];
	size_t linebuffer_idx = 0;

	while (*buffer != '\0') {
		log_debug("linebuffer_idx=%d\n", (int)linebuffer_idx);
		if (*buffer == '\n' || linebuffer_idx >= sizeof(linebuffer)) {
			screen_render_string(
				screen->renderer, 
				10, 
				text_rect.y + text_rect.h, 
				linebuffer, 
				screen->font, 
				&text_rect, 
				&white);

			linebuffer_idx = 0;
			buffer++;
		}

		linebuffer[linebuffer_idx++] = *(buffer++);
	
	}
	// so we can have nice text, two lines one above the next
//	screen_render_string(screen->renderer, 10, 10, "Hello World!", screen->font, &text_rect, &white);
//	screen_render_string(screen->renderer, 10, text_rect.y + text_rect.h, "Conan demo by JFrog", screen->font, &text_rect, &white);
}

