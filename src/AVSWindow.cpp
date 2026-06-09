#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"

using namespace AVS;

Window::Window() : Object() {
    Window( 10, 10, 100, 100 );
}

Window::Window( uint16_t upper_left_x, uint16_t upper_left_y, uint16_t width, uint16_t height ) : Object() {
    this->x = upper_left_x;
    this->y = upper_left_y;
    this->width = width;
    this->height = height;

    this->inner_x = x + 1;
    this->inner_y = y + 1;
    this->inner_width = width - 2;
    this->inner_height = height - 2;

    this->is_container = true;
    this->is_drawable = true;
    this->is_hover = false;
    this->is_visible = false;
}

void Window::output_diagnostic( void ) {
    printf( "title: \"%s\"\n", this->title );
}

void Window::draw( void ) {
    printf( "Drawing window.\n" );

    App *a = dynamic_cast<App *>(this->find_app());
    Theme *t = &a->app_theme;

    if( has_border ) {
        avs_draw_rect( x, y, width, height, t->border );
    }

    if( has_title_bar ) {
        avs_draw_rect( inner_x, inner_y, inner_width, t->title_bar_height, t->window_title_bar_background );
    }

    avs_draw_rect( inner_x, inner_y + t->title_bar_height, inner_width, inner_height - t->title_bar_height, t->window_background );

/*     vui_theme *theme = vui_get_active_theme();

	if( !(window->flags & VUI_WINDOW_FLAG_NO_BORDER) ) {
		// Border
		vui_draw_rect( window->x, window->y, window->width, window->height, theme->border );
	}

	if( !(window->flags & VUI_WINDOW_FLAG_NO_TITLE_BAR) ) {
		vui_draw_rect( window->inner_x, window->inner_y - VUI_WINDOW_TITLE_BAR_HEIGHT, window->inner_width, VUI_WINDOW_TITLE_BAR_HEIGHT, theme->window_title_bar_background );

		if( !(window->flags & VUI_WINDOW_FLAG_HIDE_TITLE) ) {
			vui_draw_string_ttf( window->title, window->inner_x + 5, window->inner_y - VUI_WINDOW_TITLE_BAR_HEIGHT + 5, theme->window_title_bar_foreground, theme->window_title_bar_background, vui_font_get_font("noto-sans-bold"), 13, VUI_DRAW_FLAGS_NONE );
		}
	}

	// Inner window
	vui_draw_rect( window->inner_x, window->inner_y, window->inner_width, window->inner_height, window->color_background ); */

    Object::draw();
}

void Window::set_title( const char *new_title ) {
    avs_strcpy( title, new_title );
}

const char* Window::get_title( void ) {
    return title;
}