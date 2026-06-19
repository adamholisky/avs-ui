#include "avs-platform.h"
#include "avs-ui.h"
#include "avs-ui/console.h"

using namespace AVS;

Console::Console( uint16_t x_cords, uint16_t y_cords, uint16_t px_width, uint16_t px_height, uint32_t fg, uint32_t bg ) : Object() {
	color_fg = fg;
	color_bg = bg;
	is_color_specified = false;
	strcpy( con_font_name, "FiraCode" );
	con_font_size = 13;
	f_main = avs_get_font( con_font_name );

	x = x_cords;
	y = y_cords;
	width = px_width;
	height = px_height;

	inner_x = x + 2;
	inner_y = x + 2;
	inner_height = px_height - 4;
	inner_width = px_width - 4;

	container_offset_x = 2;
	container_offset_y = 2;

	num_rows = 25;
	num_cols = 80;
	cursor_row = 0;
	cursor_col = 0;

	buffer_size = 100 * 80;
	term_buffer = (ConsoleCell*)avs_malloc( sizeof( ConsoleCell ) * buffer_size );

	lines = (ConsoleLine*)avs_malloc( sizeof( ConsoleLine ) * num_rows );
	memset( lines, 0, ( sizeof( ConsoleLine ) * num_rows ) );

	for ( int i = 0; i < num_rows; i++ ) {
		lines[i].num_cells = num_cols;
		lines[i].cells = (ConsoleCell*)avs_malloc( sizeof( ConsoleCell ) * lines[i].num_cells );
		memset( lines[i].cells, 0, sizeof( ConsoleCell ) * lines[i].num_cells );
	}

	is_capturing_esc_code = false;
	esc_capture_num = 0;
	tab_size = 4;

	populate_test_data();
}

void Console::output_diagnostic( void ) {
	printf( "Console: x=%d  y=%d  w=%d  h=%d\n", x, y, width, height );
}

void Console::draw( void ) {
	this->output_diagnostic();

	uint16_t line_x_start = this->get_absolute_x();
	uint16_t line_y_start = this->get_absolute_y();

	font_size* fs = f_main->get_size( this->con_font_size );

	for ( int row = 0; row < num_rows; row++ ) {
		for ( int col = 0; col < num_cols; col++ ) {
			uint32_t fg = lines[row].cells[col].has_color ? lines[row].cells[col].color_fg : color_fg;
			uint32_t bg = lines[row].cells[col].has_color ? lines[row].cells[col].color_bg : color_bg;

			avs_draw_char_ttf_fsize( 
				lines[row].cells[col].char_code, 
				line_x_start + ( 9 * col ), 
				line_y_start, 
				fg, 
				bg, 
				f_main, 
				con_font_size, 
				fs, 
				0
			);
		}

		line_y_start = line_y_start + 13;
	}
}

void Console::put_char( const uint32_t char_code ) {
	con_put_char( char_code );
}

inline void Console::con_put_char( const uint32_t char_code) {
	switch( (char)char_code ) {
		case '\x1b':
			is_capturing_esc_code = true;
			esc_capture_num = 0;
			break;
		case '\t':
			do_tab();
			break;
		case '\n':
			do_newline();
			break;
		case '\b':
			do_backspace();
			break;
		default:
			if( is_capturing_esc_code ) {
				process_escape( char_code );
			} else {
				if( cursor_col == num_cols ) {
					con_put_char( '\n' );
				}

				uint32_t fg = is_color_specified ? current_fg_color : color_fg;
				uint32_t bg = is_color_specified ? current_bg_color : color_bg;

				lines[cursor_row].cells[cursor_col] = {
					.char_code = char_code,
					.has_color = is_color_specified,
					.color_fg = fg,
					.color_bg = bg,
					.dirty = true
				};

				cursor_col++;
			}			
	}
}

void Console::process_escape( const uint32_t char_code ) {

}

inline void Console::con_put_char_at( const uint32_t char_code, uint16_t row, uint16_t col ) {
	lines[row].cells[col] = {
		.char_code = (uint32_t)char_code,
		.has_color = is_color_specified,
		.color_fg = current_fg_color,
		.color_bg = current_bg_color
	};
}

void Console::put_string( const char* s ) {
	for( int i = 0; i < strlen(s); i++ ) {
		con_put_char(s[i]);
	}
}

void Console::populate_test_data( void ) {
	for( int row = 0; row < num_rows; row++ ) {
		put_string( "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.ABCDEF" );
	}
}

void Console::do_tab( void ) {
	if( cursor_col + tab_size  > num_cols ) {
		return;
	}

	uint8_t insert_spaces = 0;

	if( cursor_col == 1 ) {
		insert_spaces = tab_size;
	} else {
		insert_spaces = ( cursor_col - 1 ) % tab_size;
		if( insert_spaces == 0 ) { insert_spaces = tab_size; }
	}

	for( int i = 0; i < insert_spaces; i++ ) {
		con_put_char( ' ' );
	}

}

void Console::do_newline( void ) {
	if( cursor_row + 1 == num_rows ) {
		do_scroll( CONSOLE_DIRECTION_UP, 1 );
		// don't change cursor_row
		cursor_col = 0;
	} else {
		cursor_row++;
		cursor_col = 0;
	}
}

void Console::do_backspace( void ) {
	if( cursor_col == 0 ) {
		return;
	}

	cursor_col--;

	con_put_char_at( ' ', cursor_row, cursor_col + 1 );
}

void Console::do_scroll( uint8_t direction, uint16_t num_lines ) {

}