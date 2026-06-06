#include "avs-sdl-bridge.h"
#include "avs-platform.h"
#include "avs-ui.h"

#include <SDL.h>
#include <SDL_render.h>

SDL_Window *sdl_w = NULL;

bool avs_sdl_init( avs_platform *avsp ) {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL_Init failed: %s\n", SDL_GetError() );
		return false;
	}

	sdl_w = SDL_CreateWindow( "VIOS UI Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, avsp->screen_width, avsp->screen_height, SDL_WINDOW_SHOWN );

	if( sdl_w == NULL ) {
		printf( "SDL Window error: %s\n", SDL_GetError() );
		return false;
	}

	SDL_Surface *screen_surface = SDL_GetWindowSurface( sdl_w );
	SDL_FillRect( screen_surface, NULL, 0x00374760 );
	SDL_UpdateWindowSurface( sdl_w );

	// Setup the framebuffer
	uint32_t *fb = (uint32_t *)screen_surface->pixels;

    return true;
}