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
    
    switch( avs_p.platform ) {
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
            while( 1) { ; }
    }
}

/**
 * @brief Platform init for AVSOS user space
 * 
 * @return int 
 */
bool avs_platform_init_avsos( avs_platform *avsp ) {
    return false;
}

/**
 * @brief Platform init for AVSOS Kernel space
 * 
 * @return int 
 */
bool avs_platform_init_avsos_kernel( avs_platform *avsp ) {
    return false;
}

/**
 * @brief Platform init for AVSOS linux
 * 
 * @return int 
 */
bool avs_platform_init_linux( avs_platform *avsp ) {
    avsp->screen_height = 768;
    avsp->screen_width = 1024;

    if( !avs_sdl_init( avsp ) ) {
        printf( "Stopping platform initalization.\n" );
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