#ifndef AVS_UI_LABEL_INCLUDED
#define AVS_UI_LABEL_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui/object.h"
#include "avs-list.h"
#include "avs-ui/font.h"

#define AVS_FONT_TYPE_TTF 0

namespace AVS {
	class Label : public Object {
		private:
			char text[255];
		public:
			uint16_t font_size;
			char font_name[50];
			uint32_t color_fg;
			uint32_t color_bg;

			Label( char *t, uint16_t x_cords, uint16_t y_cords, uint32_t fg, uint32_t bg );
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