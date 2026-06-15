#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/label.h"
#include "avs-ui/font.h"

using namespace AVS;

Label::Label( char *t, uint16_t x_cords, uint16_t y_cords, uint32_t fg, uint32_t bg ) : Object() {
    x = x_cords;
    y = y_cords;
    color_fg = fg;
    color_bg = bg;

    set_text( t );
}

void Label::output_diagnostic( void ) {
    printf( "text='%s'  x=%d  y=%d  font_name=%s  fg=0x%X bg=0x%X\n", text, x, y, font_name, color_fg, color_bg );
}

void Label::set_text( char *t ) {
    avs_strcpy( text, t );
}

const char *Label::get_text( void ) {
    return text;
}

void Label::draw( void ) {
    Font *f;
    uint16_t size;

    if( font_size == 0 ) { 
        size = 13; 
    } else {
        size = font_size;
    }

    if( font_name[0] == 0 ) {
        f = avs_get_main_font();
    } else {
        f = avs_get_font( font_name );
        
        if( f == nullptr ) { f = avs_get_main_font(); }
    }

    avs_draw_string( text, x, y, color_fg, color_bg, f, size, 0 );
}