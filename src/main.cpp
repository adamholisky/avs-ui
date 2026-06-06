#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"

int main( int argc, char* argv[] ) {
	printf( "AVS UI Development Environment Started\n" );

	if( !avs_platform_init() ) {
		printf( "AVS platform init failed. Goodbye.\n" );
		return 1;
	}

	AVS::App *my_app = new AVS::App( "Test App 1" );

	my_app->output_diagnostic();

	return 0;
}

#ifdef AVS_ENV_LINUX

#endif