#include "avs-ui.h"
#include "avs-ui/window.h"

using namespace AVS;

Window::Window() {
    Window( 10, 10, 100, 100 );
}

Window::Window( uint16_t upper_left_x, uint16_t upper_left_y, uint16_t width, uint16_t height ) {
    this->x = upper_left_x;
    this->y = upper_left_y;
    this->width = width;
    this->height = height;

    this->is_container = true;
    this->is_drawable = true;
    this->is_hover = false;
    this->is_visible = false;
}

void Window::output_diagnostic( void ) {
    printf( "title: \"%s\"\n", this->title );
}

void Window::draw( void ) {

}

void Window::set_title( const char *new_title ) {
    avs_strcpy( title, new_title );
}

const char* Window::get_title( void ) {
    return title;
}