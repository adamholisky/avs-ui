#include "avs-ui.h"

using namespace AVS;

uint16_t avs_draw_string( const char *s, uint16_t x, uint16_t y, uint32_t fg, uint32_t bg, AVS::Font *font, uint16_t size, uint64_t flags ) {
	int len = strlen(s);
	int current_x = x;
	uint16_t pix_len = 0;
	Font *f = ( font == NULL ? avs_get_main_font() : font );

	for( int i = 0; i < len; i++ ) {
		if( f->type == AVS_FONT_TYPE_TTF ) {
			uint32_t char_num = *s;

			avs_draw_char_ttf( char_num, current_x, y, fg, bg, f, flags );

			//vdf( "final width: %d\n", font->ttf_bitmaps[char_num].advance + 1 );

			current_x = current_x + f->bitmaps[char_num].advance + 1;
			pix_len = pix_len + f->bitmaps[char_num].advance + 1;
		}
		
		s++;
	}

	return pix_len;
}


void avs_draw_char_ttf( uint32_t char_num, uint16_t x, uint16_t y, uint32_t fg, uint32_t bg, AVS::Font *font, uint64_t flags ) {
	//vdf( "draw: %X (%c)\n", char_num, (char)char_num );
	avs_platform *avsp = get_avs_platform();

	uint32_t y_offset = (font->size - font->bitmaps[(uint8_t)char_num].y_offset);

	for( int i = 0; i < font->bitmaps[(uint8_t)char_num].height + y_offset; i++ ) {
		uint32_t pix_row = i;
		if( y_offset != 0 && i >= y_offset) {
			pix_row = i - y_offset;
			//vdf( "%c: %d ->  %d ", (char)char_num, y_offset, pix_row );
		}

		uint32_t *loc = (uint *)avsp->back_buffer + ((y+i) * (avsp->screen_pitch / 4)) + x + font->bitmaps[char_num].x_offset;
		uint32_t *loc_imm = (uint *)avsp->front_buffer + ((y+i) * (avsp->screen_pitch / 4)) + x + font->bitmaps[char_num].x_offset;
		
		//vdf( "Row: %d == %X\n", i, font->bitmaps[index].pixel_row[i] );
		//vdf( "\"" );
		//for( int j = 0; j != font->info.width; j++ ) {
		for( int j = 0; j != font->bitmaps[char_num].width; j++ ) {
			// handle the y-offset
			if( i < y_offset ) {
				//vdf( "offset %d (max: %d)\n", i, abs() );

				if( !(flags & AVS_FLAG_DRAW_TRANSPARENT) ) {
					*(loc + j) = bg;
					if( flags & AVS_FLAG_DRAW_IMMEDIATE ) { *(loc_imm + j) = bg; }
				}
				continue;
			}

			// render as normal
			if( font->bitmaps[(uint8_t)char_num].pixel[(pix_row * font->bitmaps[(uint8_t)char_num].width) + j] ) {
				//vdf( "*" );

				float adjust = font->bitmaps[(uint8_t)char_num].pixel[(pix_row * font->bitmaps[(uint8_t)char_num].width) + j];

				uint8_t red_bg = ((bg & 0x00FF0000) >> 16);
				uint8_t red = ((fg & 0x00FF0000) >> 16);
				red = (uint8_t)( (red * (adjust / 0xFF)) + (((1 - (adjust / 0xFF))) * red_bg));

				uint8_t green_bg = (bg & 0x0000FF00) >> 8;
				uint8_t green = (fg & 0x0000FF00) >> 8;
				green = (uint8_t)( (green * (adjust / 0xFF)) + (((1 - (adjust / 0xFF))) * green_bg));
				
				uint8_t blue_bg = (bg & 0x000000FF);
				uint8_t blue = (fg & 0x000000FF);
				blue = (uint8_t)( (blue * (adjust / 0xFF)) + (((1 - (adjust / 0xFF))) * blue_bg));

				uint32_t color = (red << 16) | (green << 8) | (blue);

				*(loc + j) = color;
				if( flags & AVS_FLAG_DRAW_IMMEDIATE ) { *(loc_imm + j) = color; }

				
			} else {
				//vdf( " " );

				if( !(flags & AVS_FLAG_DRAW_TRANSPARENT) ) {
					*(loc + j) = bg;
					if( flags & AVS_FLAG_DRAW_IMMEDIATE ) { *(loc_imm + j) = bg; }
				}
			}
		}
		//vdf( "\"\n" );
	}
}