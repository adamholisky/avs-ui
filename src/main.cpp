#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"
#include "avs-ui/font.h"
#include "avs-ui/label.h"
#include "avs-ui/console.h"

using namespace AVS;
	
class ReferenceApp: public AVS::App {
	private:
		Window *w_main;
		Console *c_main;
	public:
		ReferenceApp( void ) : App( "AVS Reference App" ) {
			w_main = new Window( 10, 10, 1024 - 20, 768 - 20 );
			w_main->set_title( get_name() );

			/* l_mylabel = new Label( "My ReferenceApp Label is a thing", 5, 5, 0xFFFFFF, 0x000000 );
			l_mylabel->is_transparent = true; */

			c_main = new Console( 0, 0, w_main->inner_width, w_main->inner_height, 0xFFFFFF, 0 );

			add_child( w_main );
			add_child( w_main, c_main );
		}
};

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