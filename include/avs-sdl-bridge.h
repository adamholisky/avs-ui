#ifndef AVS_SDL_BRIDGE_INCLUDED
#define AVS_SDL_BRIDGE_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-platform.h"

bool avs_sdl_init( avs_platform *avsp );
void avs_sdl_main_loop( void );
void avs_sdl_update_sdl_window( void );

#ifdef __cplusplus
}
#endif
#endif