#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/button.h"
#include "avs-ui/font.h"

using namespace AVS;

Button::Button( const char* t, uint16_t x_cords, uint16_t y_cords, uint16_t btn_width, uint16_t btn_height ) : Object() {
	x = x_cords;
	y = y_cords;
	height = btn_height;
	width = btn_width;
	font_size = 0;
	font_name[0] = '\0';
	color_fg = 0;
	color_bg = 0;

	set_text( (char*)t );
}

void Button::output_diagnostic( void ) {
	printf( "button text='%s'  x=%d  y=%d  font_name=%s  fg=0x%X bg=0x%X\n", text, x, y, font_name, color_fg, color_bg );
}

void Button::set_text( char* t ) {
	avs_strcpy( text, t );
}

const char* Button::get_text( void ) {
	return text;
}

void Button::draw( void ) {
	avs_platform *avsp = get_avs_platform();

	App *a = dynamic_cast<App *>(this->find_app());
    Theme *t = &a->app_theme;

	Font* f;
	uint16_t size;

	if ( font_size == 0 ) {
		size = 13;
	}
	else {
		size = font_size;
	}

	if ( font_name[0] == 0 ) {
		f = avs_get_main_font();
	}
	else {
		f = avs_get_font( font_name );

		if ( f == nullptr ) { f = avs_get_main_font(); }
	}

	uint16_t abs_x = get_absolute_x();
	uint16_t abs_y = get_absolute_y();

	avs_draw_rect( abs_x, abs_y, width, height, t->button_border );
	printf("1--");
	avs_draw_rect( abs_x + 1, abs_y + 1, width - 2, height - 2, t->button_background );
	printf("2--");

	uint16_t text_w = 0;
	uint16_t text_h = 0;

	avs_string_ttf_get_box( text, f, size, &text_w, &text_h );
	
	uint16_t center_x = abs_x + ((width - 2) / 2);
	uint16_t center_y = abs_y + ((height - 2) / 2);
	uint16_t final_x = center_x - (text_w / 2);
	uint16_t final_y = center_y - (text_h / 2) - 1;

	printf( "text_w=%d  abs_x=%d  abs_y=%d  text_h=%d  center_x=%d  center_y=%d  final_x=%d  final_y=%d\n", abs_x, abs_y, text_w, text_h, center_x, center_y, final_x, final_y );

	avs_draw_string( text, final_x, final_y, t->window_title_bar_foreground, t->button_background , f, size, 0 );
	printf("3--");

	Object::draw();
	printf(".");
}