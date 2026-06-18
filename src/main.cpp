#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"
#include "avs-ui/font.h"
#include "avs-ui/label.h"
#include "avs-ui/console.h"
#include "avs-ui/button.h"

using namespace AVS;
	
class ReferenceApp: public AVS::App {
	private:
		Window *w_main;
		Console *c_main;
		Button *b_do_something;
	public:
		ReferenceApp( void ) : App( "AVS Reference App" ) {
			w_main = new Window( 10, 10, 1024 - 20, 768 - 20 );
			w_main->set_title( get_name() );

			/* l_mylabel = new Label( "My ReferenceApp Label is a thing", 5, 5, 0xFFFFFF, 0x000000 );
			l_mylabel->is_transparent = true; */

			b_do_something = new Button( "Do Something", 5, 5, 200, 35 );
			c_main = new Console( 0, 100, w_main->inner_width, w_main->inner_height - 100, 0xFFFFFF, 0 );

			add_child( w_main );
			add_child( w_main, b_do_something );
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