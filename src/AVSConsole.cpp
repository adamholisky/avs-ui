#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/console.h"

using namespace AVS;

Console::Console( uint16_t x_cords, uint16_t y_cords, uint16_t px_width, uint16_t px_height, uint32_t fg, uint32_t bg ) : Object() {
    color_fg = fg;
    color_bg = bg;
    strcpy( font_name, "FiraCode" );
    font_size = 13;
    f_main = avs_get_font( font_name );

    x = x_cords;
    y = y_cords;
    width = px_width;
    height = px_height;

    inner_x = x + 2;
    inner_y = x + 2;
    inner_height = px_height - 4;
    inner_width = px_width - 4;

    num_lines = 5;
}

void Console::update_size( void ) {

}

void Console::output_diagnostic( void ) {
    printf( "Console: x=%d  y=%d  w=%d  h=%d\n", x, y, width, height );
}

void Console::draw( void ) {
    this->output_diagnostic();

    uint16_t x_abs = this->get_absolute_x();
    uint16_t y_abs = this->get_absolute_y();

    avs_draw_rect( x_abs, y_abs, width, height, color_bg );

    uint16_t line_x_start = x_abs;
    uint16_t line_y_start = y_abs;

    for( int i = 0; i < num_lines; i++ ){
        //avs_draw_string( "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z 1 2 3 4 5 6 7 8 9 0 ! @ # $.", line_x_start, line_y_start, color_fg, color_bg, f_main, font_size, AVS_FLAG_DRAW_TRANSPARENT );

        line_y_start = line_y_start + 13;
    }
}