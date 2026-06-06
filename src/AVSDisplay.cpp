#include "avs-platform.h"
#include "avs-ui.h"

#include "avs-ui/display.h"

using namespace AVS;

void Display::refresh_all( void ) {
    avs_platform *avsp = get_avs_platform();
    
    Rect r = {
        x = 0,
        y = 0,
        width = avsp->screen_width,
        height = avsp->screen_height
    };

    refresh_rect( &r );
}

void Display::refresh_rect( Rect *r ) {

}