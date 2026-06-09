#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-sdl-bridge.h"

avs_platform avs_p;

/**
 * @brief Bring up and configure the AVS Platform
 *
 * @return int
 */
bool avs_platform_init( void ) {
	avs_p.platform = AVS_PLATFORM;

	switch ( avs_p.platform ) {
		case AVS_PFORM_AVSOS:
			return avs_platform_init_avsos( &avs_p );
			break;
		case AVS_PFORM_AVSOS_KERNEL:
			return avs_platform_init_avsos_kernel( &avs_p );
			break;
		case AVS_PFORM_LINUX:
			return avs_platform_init_linux( &avs_p );
			break;
		default:
			printf( "Unrecognized platform! Got %d. Hanging.\n", avs_p.platform );
			while ( 1 ) { ; }
	}
}

/**
 * @brief Platform init for AVSOS user space
 *
 * @return int
 */
bool avs_platform_init_avsos( avs_platform* avsp ) {
	return false;
}

/**
 * @brief Platform init for AVSOS Kernel space
 *
 * @return int
 */
bool avs_platform_init_avsos_kernel( avs_platform* avsp ) {
	return false;
}

/**
 * @brief Platform init for AVSOS linux
 *
 * @return int
 */
bool avs_platform_init_linux( avs_platform* avsp ) {
	avsp->screen_height = 768;
	avsp->screen_width = 1024;
	avsp->screen_pitch = avsp->screen_width * 4;

	if ( !avs_sdl_init( avsp ) ) {
		printf( "Stopping platform initalization.\n" );
		return false;
	}

	avsp->buffer_size = avsp->screen_height * (avsp->screen_width * 4);
	avsp->back_buffer = avs_malloc( avsp->buffer_size );
	avsp->back_buffer32_t = (uint32_t *)avsp->back_buffer;

	if( !avsp->back_buffer ) {
		printf( "Couldn't allocate back buffer.\n" );
		return false;
	}

	return true;
}

/**
 * @brief Get the avs platform object
 *
 * @return avs_platform*
 */
avs_platform* get_avs_platform( void ) {
	return &avs_p;
}

/**
 * @brief Draws a rectangle on the back buffer
 * 
 * @param x 
 * @param y 
 * @param width 
 * @param height 
 * @param color 
 */
void avs_draw_rect( uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color ) {
	uint32_t offset_x = x;
	uint32_t offset_y = y * avs_p.screen_pitch / 4;

	if( x + width > avs_p.screen_width ) { return; }
	if( y + height > avs_p.screen_height ) { return; }

	for ( int i = 0; i < height; i++ ) {
		for ( int j = 0; j < width; j++ ) {
			*( avs_p.back_buffer32_t + offset_y + offset_x + j ) = color;
		}

		offset_y = offset_y + avs_p.screen_pitch / 4;
	}
}

/**
 * @brief Moves the back buffer to the front buffer
 * 
 */
void avs_platform_copy_b_to_f( void ) {
	avs_memcpy( avs_p.front_buffer, avs_p.back_buffer, avs_p.buffer_size );
	avs_sdl_update_sdl_window();
}