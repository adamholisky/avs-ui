#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-list.h"

#include "avs-ui/font.h"

using namespace AVS;

List* avs_fonts;

void initalize_fonts( void ) {
	avs_fonts = new List();

	avs_fonts->append( new Font( AVS_FONT_TYPE_TTF, "FiraCode", "fonts/FiraCode.ttf" ) );
}

Font::Font( uint8_t type, const char* font_name, const char* font_file_name ) {
	avs_strcpy( name, font_name );
	avs_strcpy( file_name, font_file_name );

	FILE *f = fopen( file_name, "r" );

	if( f == NULL ) {
		printf( "Cannot open %s, f returned NULL.\n", file_name );
		return;
	}

	struct stat file_meta;
	stat( file_name, &file_meta );

	data_size = file_meta.st_size;

	data = (uint8_t *)avs_malloc( data_size );

	if( fread( data, data_size, 1, f ) != 1 ) {
		printf( "Read failed on %s, fread returned not 1.\n", file_name );
		return;
	}

	switch ( type ) {
		case AVS_FONT_TYPE_TTF:
			load_ttf();
			break;
		default:
			printf( "Unknown font type, halting. Got %d.\n", type );
			while ( 1 ) { ; }
	}
}

void Font::load_ttf( void ) {
	printf( "loading %s\n", name );
}