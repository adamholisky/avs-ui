#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"
#include "avs-platform.h"
#include "avs-sdl-bridge.h"

using namespace AVS;

App::App( const char* disp_name ) : Object() {
	avs_strcpy( this->display_name, disp_name );
	this->is_container = true;
	this->is_drawable = true;

	app_theme.desktop = 0x051022;
	app_theme.border = 0x363636;
	app_theme.window_background = 0x282828;
	app_theme.window_title_bar_background = 0x363636;
	app_theme.window_title_bar_foreground = 0x00EAEAEA;
	app_theme.button_border = 0x183F6C;
	app_theme.button_foreground = 0xD6D6D6;
	app_theme.button_background = 0x0f4d95;	
	app_theme.button_hover = 0x265C9D;
	app_theme.button_active = 0x102B4C;
	app_theme.menubar_background = 0x363636;
	app_theme.menubar_foreground = 0xFFFFFF;
	app_theme.menubar_select = 0x0f4d95; 

	app_theme.title_bar_height = 25;
}

void App::draw( void ) {
	printf( "drawing app\n" );

	//JUST for testing. TODO: remove
	avs_draw_rect( 0, 0, 1024, 768, 0xFF0000 );
	avs_platform_copy_b_to_f();

	Object::draw();
	avs_platform_copy_b_to_f();

	printf( "Done drawing app\n" );
}

void App::output_diagnostic( void ) {
	printf( "display_name: \"%s\"\n", this->display_name );
}

void App::run( void ) {
	// event loop goes here
	avs_sdl_main_loop();
}