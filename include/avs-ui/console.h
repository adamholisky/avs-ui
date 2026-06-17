#ifndef AVS_UI_CONSOLE_INCLUDED
#define AVS_UI_CONSOLE_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui/object.h"
#include "avs-list.h"
#include "avs-ui/font.h"

namespace AVS {
    struct ConsoleCell {
        uint32_t char_code;

        uint32_t color_fg;
        uint32_t color_bg;
    };

    class ConsoleLine {
        public:
        uint16_t num_cells;
        ConsoleCell cells[80];
    };
    
	class Console : public Object {
		private:
			char text[255];
            Font *f_main;
            ConsoleLine lines[25];
            uint16_t num_lines;
		public:
			uint16_t font_size;
			char font_name[50];
			uint32_t color_fg;
			uint32_t color_bg;

			Console( uint16_t x_cords, uint16_t y_cords, uint16_t px_width, uint16_t px_height, uint32_t fg, uint32_t bg );
			void output_diagnostic( void );
			void draw( void );

            void update_size( void );
	};
}

#ifdef __cplusplus
}
#endif
#endif