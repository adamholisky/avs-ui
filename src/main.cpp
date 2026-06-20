#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/app.h"
#include "avs-ui/window.h"
#include "avs-ui/font.h"
#include "avs-ui/label.h"
#include "avs-ui/console.h"
#include "avs-ui/button.h"

#include <signal.h>
#include <errno.h>

using namespace AVS;

void sig_handler_sigio( int signo );

class ReferenceApp: public AVS::App {
	private:
		Window *w_main;
		Console *c_main;
		Button *b_do_something;

		int pty_fd;
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

		void handler_sigio( int signo ) {
			char buff[4096];
			ssize_t n;

			printf( "handler inner\n" );

			do {
				n = read( pty_fd, buff, 4096 );

				if( n > 0 ) {
					for( int i = 0; i < n; i++ ) {
						c_main->put_char( 'A' );
						printf( "%c", buff[i] );
					}

					is_dirty = true;
				}
			} while( n > 0 );

			if( is_dirty ) {
				is_dirty = false;

				this->draw();
			}
		}

		void run( void ) {
			printf( "the app is now running?\n" );

			pid_t pid;

			pid = forkpty( &pty_fd, NULL, NULL, NULL );

			if( pid == -1 ) {
				perror( "forkpty" );
				exit(1);
			}

			if( pid == 0 ) {
				execlp( "/bin/bash", "bash", NULL );
				perror( "excelp" );
				exit(1);
			}

			int flags = fcntl( pty_fd, F_GETFL );
			fcntl( pty_fd, F_SETFL, flags | O_NONBLOCK | O_ASYNC );
			struct sigaction sa = {0};
			sa.sa_handler = sig_handler_sigio;
			sigaction( SIGIO, &sa, NULL );

			App::run();
		}

		
};

ReferenceApp *main_app;

void sig_handler_sigio( int signo ) {
	printf( "in handler outer\n" );
	main_app->handler_sigio( signo );
}

int main( int argc, char* argv[] ) {
	printf( "AVS UI Development Environment Started\n" );

	if( !avs_platform_init() ) {
		printf( "AVS platform init failed. Goodbye.\n" );
		return 1;
	}

	initalize_fonts();

	ReferenceApp *my_app = new ReferenceApp();
	main_app = my_app;
	my_app->output_diagnostic();
	my_app->draw();
	my_app->run();

	return 0;
}