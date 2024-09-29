#include "screen.h"

#include <SDL2/SDL_video.h>

#include "logger.h"

static void screen_render_string(SDL_Renderer *renderer, int x, int y,
                                 const char *text, TTF_Font *font,
                                 SDL_Rect *rect, SDL_Color *color)
{
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

static struct result screen_load_ttf_font(struct screen *screen)
{
	TTF_Init();
	screen->m_font = TTF_OpenFont(screen->cfg.font_path, 10);

	if (screen->m_font == NULL) {
		return create_result_fmt(false,
		                         "could not initialize font %s: %s\n",
		                         screen->cfg.font_path, TTF_GetError());
	}

	const int usable_width =
		screen->cfg.width - (2 * screen->cfg.border_width);
	const int max_char_width = usable_width / 80;

	int text_w;
	int text_h;

	TTF_SizeText(screen->m_font, "0", &text_w, &text_h);

	log_info("font with ptsize %d has the dimensions: w=%d h=%d per char\n",
	         10, text_w, text_h);

	int ptsize = (max_char_width * 10) / text_w;

	TTF_SetFontSize(screen->m_font, ptsize);

	return create_result_success();
}

struct result screen_init(struct screen *screen)
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return create_result_fmt(
		    false, "could not initialize sdl2: %s\n", SDL_GetError());
	}

	screen->m_window = SDL_CreateWindow(
	    "retro-os", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	    screen->cfg.width, screen->cfg.height, SDL_WINDOW_SHOWN);

	if (screen->m_window == NULL) {
		return create_result_fmt(false, "could not create window: %s\n",
		                         SDL_GetError());
	}

	if (screen->cfg.fullscreen) {
		SDL_SetWindowFullscreen(screen->m_window,
		                        SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	screen->m_screenSurface = SDL_GetWindowSurface(screen->m_window);

	// triggers the program that controls
	// your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	screen->m_renderer =
	    SDL_CreateRenderer(screen->m_window, -1, render_flags);

	struct result result = screen_load_ttf_font(screen);
	if (!result.success) {
		return result;
	}

	return create_result_success();
}

void screen_destroy(struct screen *screen)
{
	SDL_DestroyWindow(screen->m_window);
	SDL_Quit();
}

void screen_draw_string(struct screen *screen, const char *s, size_t maxlen)
{
	// create a rectangle to update with the size of the rendered text
	SDL_Rect text_rect;
	text_rect.y = screen->cfg.border_width;
	text_rect.h = 0;

	// The color for the text we will be displaying
	//	SDL_Color white = {255, 255, 255, 0};
	SDL_Color white = {0, 255, 0, 0};

	char   linebuffer[255];
	size_t linebuffer_idx = 0;

	size_t i = 0;

	while (s[i] != '\0' && i < maxlen) {

		if (s[i] == '\n' || linebuffer_idx >= sizeof(linebuffer)) {

			linebuffer[linebuffer_idx] = '\0';

			screen_render_string(
			    screen->m_renderer, screen->cfg.border_width,
			    text_rect.y + text_rect.h, linebuffer,
			    screen->m_font, &text_rect, &white);

			linebuffer_idx = 0;
			i++;
		}

		linebuffer[linebuffer_idx++] = s[i++];
	}
	// so we can have nice text, two lines one above the next
	//	screen_render_string(screen->renderer, 10, 10, "Hello World!",
	// screen->font, &text_rect, &white);
	//	screen_render_string(screen->renderer, 10, text_rect.y +
	// text_rect.h, "Conan demo by JFrog", screen->font, &text_rect,
	// &white);
}

void screen_draw_buffer(struct screen *screen, struct screenbuffer *buffer)
{
	screen_draw_string(screen, buffer->data, buffer->cursor_pos);
}
