#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-list.h"

#include "avs-ui/font.h"

using namespace AVS;

List* avs_fonts;

uint16_t dos_code_page[256] = {
    0x0000,0x263A,0x263B,0x2665,0x2666,0x2663,0x2660,0x2022,0x25D8,0x25CB,0x25D9,0x2642,0x2640,0x266A,0x266B,0x263C,
    0x25BA,0x25C4,0x2195,0x203C,0x00B6,0x00A7,0x25AC,0x21A8,0x2191,0x2193,0x2192,0x2190,0x221F,0x2194,0x25B2,0x25BC,
    0x0020,0x0021,0x0022,0x0023,0x0024,0x0025,0x0026,0x0027,0x0028,0x0029,0x002a,0x002b,0x002c,0x002d,0x002e,0x002f,
    0x0030,0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,0x0038,0x0039,0x003a,0x003b,0x003c,0x003d,0x003e,0x003f,
    0x0040,0x0041,0x0042,0x0043,0x0044,0x0045,0x0046,0x0047,0x0048,0x0049,0x004a,0x004b,0x004c,0x004d,0x004e,0x004f,
    0x0050,0x0051,0x0052,0x0053,0x0054,0x0055,0x0056,0x0057,0x0058,0x0059,0x005a,0x005b,0x005c,0x005d,0x005e,0x005f,
    0x0060,0x0061,0x0062,0x0063,0x0064,0x0065,0x0066,0x0067,0x0068,0x0069,0x006a,0x006b,0x006c,0x006d,0x006e,0x006f,
    0x0070,0x0071,0x0072,0x0073,0x0074,0x0075,0x0076,0x0077,0x0078,0x0079,0x007a,0x007b,0x007c,0x007d,0x007e,0x007f,
    0x00c7,0x00fc,0x00e9,0x00e2,0x00e4,0x00e0,0x00e5,0x00e7,0x00ea,0x00eb,0x00e8,0x00ef,0x00ee,0x00ec,0x00c4,0x00c5,
    0x00c9,0x00e6,0x00c6,0x00f4,0x00f6,0x00f2,0x00fb,0x00f9,0x00ff,0x00d6,0x00dc,0x00a2,0x00a3,0x00a5,0x20a7,0x0192,
    0x00e1,0x00ed,0x00f3,0x00fa,0x00f1,0x00d1,0x00aa,0x00ba,0x00bf,0x2310,0x00ac,0x00bd,0x00bc,0x00a1,0x00ab,0x00bb,
    0x2591,0x2592,0x2593,0x2502,0x2524,0x2561,0x2562,0x2556,0x2555,0x2563,0x2551,0x2557,0x255d,0x255c,0x255b,0x2510,
    0x2514,0x2534,0x252c,0x251c,0x2500,0x253c,0x255e,0x255f,0x255a,0x2554,0x2569,0x2566,0x2560,0x2550,0x256c,0x2567,
    0x2568,0x2564,0x2565,0x2559,0x2558,0x2552,0x2553,0x256b,0x256a,0x2518,0x250c,0x2588,0x2584,0x258c,0x2590,0x2580,
    0x03b1,0x00df,0x0393,0x03c0,0x03a3,0x03c3,0x00b5,0x03c4,0x03a6,0x0398,0x03a9,0x03b4,0x221e,0x03c6,0x03b5,0x2229,
    0x2261,0x00b1,0x2265,0x2264,0x2320,0x2321,0x00f7,0x2248,0x00b0,0x2219,0x00b7,0x221a,0x207f,0x00b2,0x25a0,0x00a0
};

void initalize_fonts( void ) {
	avs_fonts = new List();

	avs_fonts->append( new Font( "FiraCode", "fonts/FiraCode.ttf" ) );
	avs_fonts->append( new Font( "DejaVuSans", "fonts/DejaVuSans.ttf" ) );
}

Font* avs_get_main_font( void ) {
	printf( "%s\n", ((Font *)(avs_fonts->at_index_data(0)))->name );

	return (Font *)avs_fonts->at_index_data(0);
}

/**
 * @brief Returns the font <name>.
 * 
 * @param name text string of the font's name 
 * @return Font* Font object that matches name, otherwise NULL.
 */
Font* avs_get_font( const char *name ) {
	Font *result = nullptr;
	char name_to_find[50];
	avs_strcpy( name_to_find, name );

	Node *n = avs_fonts->find_data( (void *)name, []( void *a, void *b ) -> int {
		Font *b_f = (Font *)b;
		return avs_strcmp( (char *)a, b_f->name );
	});

	if( n != nullptr ) {
		result = (Font *)n->data;
	}

	return result;
}

/**
 * @brief Construct a new Font object
 * 
 * @param font_name 
 * @param font_file_name 
 */
Font::Font( const char* font_name, const char* font_file_name ) {
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

	printf( "Read %d from font %s.\n", data_size, file_name );

	type = AVS_FONT_TYPE_TTF;
	sizes = new List();

	switch ( type ) {
		case AVS_FONT_TYPE_TTF:
			prime_cache( 13 );
			break;
		default:
			printf( "Unknown font type, halting. Got %d.\n", type );
			while ( 1 ) { ; }
	}
}

/**
 * @brief Preload the glyphs for the given font size
 * 
 * @param size 
 * @return font_size* 
 */
font_size* Font::prime_cache( uint16_t size ) {
	//printf( "priming cache for font %s at size %d\n", name, size );

	font_size *fs = (font_size *)avs_malloc( sizeof(font_size) );
	fs->bitmap_count = 256;
	fs->bitmaps = (font_ttf_bitmap *)avs_malloc( fs->bitmap_count * sizeof(font_ttf_bitmap) );

	fs->sft.xScale = size;
	fs->sft.yScale = size,
	fs->sft.flags = SFT_DOWNWARD_Y;

	fs->sft.font = sft_loadmem( data, data_size );

	if( fs->sft.font == NULL ) {
		printf( "sft font failed to load\n" );
		return nullptr;
	}

	SFT_LMetrics line_metrics;
	sft_lmetrics( &fs->sft, &line_metrics );

	SFT_Glyph test_glyph;
	sft_lookup( &fs->sft, 'V', &test_glyph );
	SFT_GMetrics glyph_metrics;
	sft_gmetrics( &fs->sft, test_glyph, &glyph_metrics );
	fs->bitmap_width = glyph_metrics.advanceWidth;
	fs->bitmap_height = glyph_metrics.minHeight;

	SFT_Glyph v;

	for( int i = 0; i < 256; i++ ) {
		int lookup_res = sft_lookup( &fs->sft, dos_code_page[i], &v );
		
		SFT_GMetrics glyph_metrics;
		int gmetrics_res = sft_gmetrics( &fs->sft, v, &glyph_metrics );

		fs->bitmaps[i].x_offset = glyph_metrics.leftSideBearing;
		fs->bitmaps[i].y_offset = -glyph_metrics.yOffset;
		fs->bitmaps[i].advance = glyph_metrics.advanceWidth;
		fs->bitmaps[i].width = glyph_metrics.minWidth;
		//fs->bitmaps[i].height = glyph_metrics.minHeight;
		fs->bitmaps[i].height = size;

		uint16_t alloc_height = fs->bitmaps[i].y_offset + fs->bitmaps[i].height;
		uint16_t alloc_width = fs->bitmaps[i].x_offset + fs->bitmaps[i].width;
		
		alloc_height = 100;
		alloc_width = 100;

		//printf( "alloc %d: %d * %d = %d\n", i, alloc_height, alloc_width, alloc_height * alloc_width );
		fs->bitmaps[i].pixel = (uint8_t *)avs_malloc(alloc_height * alloc_width);
		
		memset( fs->bitmaps[i].pixel, 0, alloc_height * alloc_width );

		SFT_Image img = {
			.pixels = fs->bitmaps[i].pixel,
			.width = glyph_metrics.minWidth,
			.height = glyph_metrics.minHeight
		};

		int render_res = sft_render( &fs->sft, v, img );
	}

	return fs;
}

/**
 * @brief Return object with bitmaps of the given size
 * 
 * @param size 
 * @param do_prime_cache 
 * @return font_size* 
 */
font_size* Font::get_size( uint16_t size, bool do_prime_cache ) {
	font_size *fs = (font_size *)sizes->find_data( &size, [](void *a, void *b) -> int {
		int fs_int_a = *(int *)a;
		font_size *fs_b = (font_size *)b;

		return fs_int_a == fs_b->font_size ? 1 : 0; 
	});

	if( fs == nullptr && do_prime_cache ) {
		fs = prime_cache( size );
	}

	return fs;
}

/**
 * @brief Load the requested glyph into bitmap. The caller of this function MUST allocate bitmap 
 * and bitmap.pixel BEFORE calling. Pixel should have enough space to accomidate the size and 
 * platform color usage.
 * 
 * @param code 
 * @param bitmap 
 * @return bool Returns true if successful, false otherwise
 */
bool Font::get_glyph( uint32_t code, uint16_t size, font_ttf_bitmap *bitmap ) {
	if( bitmap == NULL ) {
		return false;
	}

	font_size *fs = get_size( size );

	if( fs == NULL ) {
		return false;
	}

	SFT_Glyph g;

	int lookup_result = sft_lookup( &fs->sft, code, &g );

	if( lookup_result == -1 ) {
		printf( "Glyph lookup failed for 0x%X.\n", code );

		return false;
	}

	SFT_GMetrics glyph_metrics;
	int gmetrics_res = sft_gmetrics( &fs->sft, g, &glyph_metrics );

	bitmap->x_offset = glyph_metrics.leftSideBearing;
	bitmap->y_offset = -glyph_metrics.yOffset;
	bitmap->advance = glyph_metrics.advanceWidth;
	bitmap->width = glyph_metrics.minWidth;
	bitmap->height = glyph_metrics.minHeight;
	//bitmap->pixel = (uint8_t *)avs_malloc( 2 * bitmap->width * bitmaps->height ); 
	bitmap->pixel = (uint8_t *)avs_malloc( 1000 ); 

	SFT_Image img = {
		.pixels = bitmap->pixel,
		.width = glyph_metrics.minWidth,
		.height = glyph_metrics.minHeight
	};

	int render_res = sft_render( &fs->sft, g, img );
	printf( "code: 0x%X, render_res: %d\n", code, render_res );

	return true;
}