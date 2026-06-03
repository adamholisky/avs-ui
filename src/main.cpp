#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"

int main( int argc, char* argv[] ) {
	printf( "AVS UI Development Environment Started\n" );

	AVS::App *my_app = new AVS::App( "Test App 1" );

	my_app->output_diagnostic();

	return 0;
}