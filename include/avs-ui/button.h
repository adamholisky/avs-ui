#ifndef AVS_UI_BUTTON_INCLUDED
#define AVS_UI_BUTTON_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui/object.h"
#include "avs-list.h"
#include "avs-ui/font.h"

namespace AVS {
	class Button : public Object {
		private:
			char text[255];
		public:
			uint16_t font_size;
			char font_name[50];
			uint32_t color_fg;
			uint32_t color_bg;

			Button( const char *t, uint16_t x_cords, uint16_t y_cords, uint16_t btn_width, uint16_t btn_height );
			void output_diagnostic( void );
			void set_text( char *t );
			const char *get_text( void );
			void draw( void );

	};
}

#ifdef __cplusplus
}
#endif
#endif