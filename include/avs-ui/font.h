#ifndef AVS_UI_FONT_INCLUDED
#define AVS_UI_FONT_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui/object.h"

#define AVS_FONT_TYPE_TTF 0

namespace AVS {
    class Font {
        private:
            void load_ttf( void );
            uint32_t data_size;
            uint8_t *data;
        public:
            char name[50];
            char file_name[255];

            Font( uint8_t type, const char *font_name, const char *font_file_name );
	};
}

void initalize_fonts( void );

#ifdef __cplusplus
}
#endif
#endif