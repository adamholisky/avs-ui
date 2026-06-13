#ifndef AVS_UI_WINDOW_INCLUDED
#define AVS_UI_WINDOW_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui/object.h"

#define AVS_UI_MAX_TITLE_LEN 50

	namespace AVS {
		class Window : public Object {
		protected:
			char title[AVS_UI_MAX_TITLE_LEN];
		public:
			bool has_border = true;
			bool has_title_bar = true;

			uint16_t border_size = 1;
			uint16_t title_bar_height = 25;

			uint32_t color_background;

			Window( void );
			Window( uint16_t upper_left_x, uint16_t upper_left_y, uint16_t width, uint16_t height );

			void output_diagnostic( void );
			void draw( void );

			void set_title( const char* new_title );
			const char* get_title( void );
		};
	}


#ifdef __cplusplus
}
#endif
#endif