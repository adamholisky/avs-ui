#include "avs-sdl-bridge.h"
#include "avs-platform.h"

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
	SDL_FillRect( screen_surface, NULL, 0x00FF0000 );
	SDL_UpdateWindowSurface( sdl_w );

	// Setup the framebuffer
	uint32_t *fb = (uint32_t *)screen_surface->pixels;
	avsp->front_buffer = (void *)fb;

    return true;
}

void avs_sdl_update_sdl_window( void ) {
	SDL_UpdateWindowSurface( sdl_w );
}

void avs_sdl_main_loop( void ) {
	SDL_Event e; 
	bool quit = false; 

	while( quit == false ) {
		while( SDL_PollEvent( &e ) ) { 
			int x, y;

			switch( e.type ) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEMOTION:
					SDL_GetMouseState( &x, &y );

					break;
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					SDL_GetMouseState( &x, &y );

					//vdf( "mb: %d\n", e.button.button );

					bool lmb = (e.button.button == 1 ? true : false );
					bool rmb = (e.button.button == 3 ? true : false );
					
					if( e.type == SDL_MOUSEBUTTONDOWN ) {
						//vui_external_event_handler( VUI_EVENT_MOUSE_DOWN, x, y, lmb, rmb );
					} else {
						//vui_external_event_handler( VUI_EVENT_MOUSE_UP, x, y, lmb, rmb );
					}
					
					break;
			}
		}
	}
}