#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"
#include "avs-ui/font.h"

using namespace AVS;
	
class ReferenceApp: public AVS::App {
	private:
		Window *w_main;
	public:
		ReferenceApp( void );
};

ReferenceApp::ReferenceApp( void ) : App( "AVS Reference App" ) {
	w_main = new Window( 10, 10, 1024 - 20, 768 - 20 );
	add_child( w_main );
}

int main( int argc, char* argv[] ) {
	printf( "AVS UI Development Environment Started\n" );

	if( !avs_platform_init() ) {
		printf( "AVS platform init failed. Goodbye.\n" );
		return 1;
	}

	initalize_fonts();

	ReferenceApp *my_app = new ReferenceApp();
	my_app->output_diagnostic();
	my_app->draw();
	my_app->run();

	return 0;
}

#ifdef AVS_ENV_LINUX

#endif