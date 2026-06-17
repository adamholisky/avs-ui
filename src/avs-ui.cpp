#include "avs-ui.h"

using namespace AVS;

void avs_render_ttf_bitmap( uint16_t x, uint16_t y, uint32_t fg, uint32_t bg, AVS::font_ttf_bitmap *bitmap ) {
	avs_platform *avsp = get_avs_platform();

	uint32_t y_offset = (bitmap->height - bitmap->y_offset);

	for( int i = 0; i < bitmap->height + y_offset; i++ ) {
		uint32_t pix_row = i;
		if( y_offset != 0 && i >= y_offset) {
			pix_row = i - y_offset;
		}

		uint32_t *loc = (uint *)avsp->back_buffer + ((y+i) * (avsp->screen_pitch / 4)) + x + bitmap->x_offset;
		uint32_t *loc_imm = (uint *)avsp->front_buffer + ((y+i) * (avsp->screen_pitch / 4)) + x + bitmap->x_offset;
		
		//vdf( "Row: %d == %X\n", i, font->bitmaps[index].pixel_row[i] );
		//vdf( "\"" );
		//for( int j = 0; j != font->info.width; j++ ) {
		for( int j = 0; j != bitmap->width; j++ ) {
			// handle the y-offset
			if( i < y_offset ) {
				*(loc + j) = bg;
				continue;
			}

			// render as normal
			if( bitmap->pixel[(pix_row * bitmap->width) + j] ) {
				//vdf( "*" );

				float adjust = bitmap->pixel[(pix_row * bitmap->width) + j];

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
			} else {
				*(loc + j) = bg;
			}
		}
	}
}

uint16_t avs_draw_string( const char *s, uint16_t x, uint16_t y, uint32_t fg, uint32_t bg, AVS::Font *font, uint16_t size, uint64_t flags ) {
	int len = strlen(s);
	int current_x = x;
	uint16_t pix_len = 0;
	Font *f = ( font == NULL ? avs_get_main_font() : font );

	for( int i = 0; i < len; i++ ) {
		if( f->type == AVS_FONT_TYPE_TTF ) {
			uint32_t char_num = *s;

			uint16_t advance_x = avs_draw_char_ttf( char_num, current_x, y, fg, bg, f, size, flags );

			//vdf( "final width: %d\n", font->ttf_bitmaps[char_num].advance + 1 );

			current_x = current_x + advance_x + 1;
			pix_len = pix_len + advance_x + 1;
		}
		
		s++;
	}

	return pix_len;
}

/**
 * @brief Draws the given character
 * 
 * @param char_num 
 * @param x 
 * @param y 
 * @param fg 
 * @param bg 
 * @param font 
 * @param size 
 * @param flags 
 * @return uint16_t the amount to advance x pixels forward to account for the character
 */
uint16_t avs_draw_char_ttf( uint32_t char_num, uint16_t x, uint16_t y, uint32_t fg, uint32_t bg, AVS::Font *font, uint16_t size, uint64_t flags ) {
	avs_platform *avsp = get_avs_platform();

	font_size *fs = font->get_size( size );
	font_ttf_bitmap *bitm = nullptr;

	if( char_num < 256 ) {
		bitm = &fs->bitmaps[char_num];
	} else {
		if( !font->get_glyph(char_num, size, bitm) ) {
			// TODO: Output a ? character or something
			printf( "failed to load bitmap for glyph %d\n", char_num );
			return 0;
		}
	}

	uint32_t y_offset = (bitm->height - bitm->y_offset);

	for( int i = 0; i < bitm->height + y_offset; i++ ) {
		uint32_t pix_row = i;
		if( y_offset != 0 && i >= y_offset) {
			pix_row = i - y_offset;
		}

		uint32_t *loc = (uint *)avsp->back_buffer + ((y+i) * (avsp->screen_pitch / 4)) + x + bitm->x_offset;
		uint32_t *loc_imm = (uint *)avsp->front_buffer + ((y+i) * (avsp->screen_pitch / 4)) + x + bitm->x_offset;
		
		for( int j = 0; j != bitm->width; j++ ) {
			// handle the y-offset
			if( i < y_offset ) {
				if( !(flags & AVS_FLAG_DRAW_TRANSPARENT) ) {
					*(loc + j) = bg;
					if( flags & AVS_FLAG_DRAW_IMMEDIATE ) { *(loc_imm + j) = bg; }
				}
				continue;
			}

			// render as normal
			if( bitm->pixel[(pix_row * bitm->width) + j] ) {
				float adjust = bitm->pixel[(pix_row * bitm->width) + j];

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
				if( !(flags & AVS_FLAG_DRAW_TRANSPARENT) ) {
					*(loc + j) = bg;
					if( flags & AVS_FLAG_DRAW_IMMEDIATE ) { *(loc_imm + j) = bg; }
				}
			}
		}
	}

	return bitm->advance;
}