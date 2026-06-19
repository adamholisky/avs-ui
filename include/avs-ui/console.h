#ifndef AVS_UI_CONSOLE_INCLUDED
#define AVS_UI_CONSOLE_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui/object.h"
#include "avs-list.h"
#include "avs-ui/font.h"

#define CONSOLE_COLOR_BLACK 0
#define CONSOLE_COLOR_BLUE 1
#define CONSOLE_COLOR_GREEN 2
#define CONSOLE_COLOR_CYAN 3
#define CONSOLE_COLOR_RED 4
#define CONSOLE_COLOR_MAGENTA 5
#define CONSOLE_COLOR_BROWN 6
#define CONSOLE_COLOR_LIGHT_GREY 7
#define CONSOLE_COLOR_DARK_GREY 8
#define CONSOLE_COLOR_LIGHT_BLUE 9
#define CONSOLE_COLOR_LIGHT_GREEN 10
#define CONSOLE_COLOR_LIGHT_CYAN 11
#define CONSOLE_COLOR_LIGHT_RED 12
#define CONSOLE_COLOR_LIGHT_MAGENTA 13
#define CONSOLE_COLOR_YELLOW 14
#define CONSOLE_COLOR_WHITE 15

#define CONSOLE_COLOR_RGB_BLACK 0x001E1E1E
#define CONSOLE_COLOR_RGB_BLUE 0x000000CC
#define CONSOLE_COLOR_RGB_GREEN	0x0000CC00
#define CONSOLE_COLOR_RGB_CYAN 0x0000CCCC
#define CONSOLE_COLOR_RGB_RED 0x00CC0000
#define CONSOLE_COLOR_RGB_MAGENTA 0x00AA00AA
#define CONSOLE_COLOR_RGB_BROWN 0x00AA5500
#define CONSOLE_COLOR_RGB_LIGHT_GREY 0x00AAAAAA
#define CONSOLE_COLOR_RGB_DARK_GREY 0x00555555
#define CONSOLE_COLOR_RGB_LIGHT_BLUE 0x005555FF
#define CONSOLE_COLOR_RGB_LIGHT_GREEN 0x0055FF55
#define CONSOLE_COLOR_RGB_LIGHT_CYAN 0x0055FFFF
#define CONSOLE_COLOR_RGB_LIGHT_RED	0x00FF5555
#define CONSOLE_COLOR_RGB_LIGHT_MAGENTA 0x00FF55FF
#define CONSOLE_COLOR_RGB_YELLOW 0x00FFFF55
#define CONSOLE_COLOR_RGB_WHITE 0x00FFFFFF

#define CONSOLE_DIRECTION_UP 0
#define CONSOLE_DIRECTION_DOWN 1

namespace AVS {
	struct ConsoleCell {
		uint32_t char_code;

		bool has_color;
		uint32_t color_fg;
		uint32_t color_bg;

		bool dirty;
	};

	class ConsoleLine {
	public:
		uint16_t num_cells;
		ConsoleCell *cells;
	};

	class Console : public Object {
	private:
		char text[255];
		Font* f_main;
		ConsoleLine *lines;
		uint16_t num_rows; 
		uint16_t num_cols;
	public:
		uint16_t con_font_size;
		char con_font_name[50];
		uint32_t color_fg;
		uint32_t color_bg;
		uint8_t tab_size;

		uint16_t cursor_row;
		uint16_t cursor_col;

		bool is_color_specified;
		uint32_t current_fg_color;
		uint32_t current_bg_color;

		uint16_t buffer_size;
		ConsoleCell *term_buffer;

		bool is_capturing_esc_code;
		uint8_t esc_capture_num;

		Console( uint16_t x_cords, uint16_t y_cords, uint16_t px_width, uint16_t px_height, uint32_t fg, uint32_t bg );

		void output_diagnostic( void );
		void draw( void );
		
		void put_char( const uint32_t char_code );
		void con_put_char( const uint32_t char_code );
		void con_put_char_at( const uint32_t char_code, uint16_t row, uint16_t col );
		void put_string( const char *s );
		
		void populate_test_data( void );

		void process_escape( const uint32_t char_code );
		void do_tab( void );
		void do_newline( void );
		void do_backspace( void );
		void do_scroll( uint8_t direction, uint16_t num_lines );
	};
}

#ifdef __cplusplus
}
#endif
#endif