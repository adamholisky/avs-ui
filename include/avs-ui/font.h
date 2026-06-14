#ifndef AVS_UI_FONT_INCLUDED
#define AVS_UI_FONT_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui/object.h"
#include "avs-list.h"
#include "schrift.h"

#define AVS_FONT_TYPE_TTF 0

namespace AVS {
    typedef struct {
        uint16_t num;
        uint32_t unicode_id;
        uint32_t advance;
        uint32_t y_offset;
        uint32_t x_offset;

        uint16_t width;
        uint16_t height;

        uint8_t *pixel;
    } font_ttf_bitmap;

    typedef struct {
        uint16_t font_size;
        uint16_t bitmap_width;
        uint16_t bitmap_height; 

        uint16_t bitmap_count;
        font_ttf_bitmap *bitmaps;
        
        SFT sft;
    } font_size;

    class Font {
        private:
            uint32_t data_size;
            uint8_t *data;
            List *sizes;
        public:
            char name[50];
            char file_name[255];
            uint8_t type;
            font_ttf_bitmap *bitmaps;
            uint32_t glyph_count;
            uint16_t height;
            uint16_t width;

            Font( const char *font_name, const char *font_file_name );

            font_size* prime_cache( uint16_t size );
            
            font_size *get_size( uint16_t size, bool do_prime_cache = true );

            bool get_glyph( uint32_t code, uint16_t size, font_ttf_bitmap *bitmap );
	};
}

void initalize_fonts( void );
AVS::Font* avs_get_main_font( void );
AVS::Font* avs_get_font( const char *name );

#ifdef __cplusplus
}
#endif
#endif