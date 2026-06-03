#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"

using namespace AVS;

App::App( const char *disp_name ) {
    avs_strcpy( this->display_name, disp_name );
}

void App::output_diagnostic( void ) {
    printf( "display_name: \"%s\"\n", this->display_name );
}

void App::run( void ) {
    // event loop goes here
}