#ifndef AVS_UI_INCLUDED
#define AVS_UI_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

/**************************************/
/* Header Config                      */
/**************************************/
#include "avs-platform.h"
#include "avs-ui/object.h"
#include "avs-ui/font.h"

/**************************************/
/* Macros and Defines                 */
/**************************************/
#define AVS_FLAG_DRAW_IMMEDIATE 1
#define AVS_FLAG_DRAW_TRANSPARENT 2

/**************************************/
/* Data Structures                    *
/**************************************/

namespace AVS {
    typedef uint32_t Color;

	enum class NamedColors {
		black =		0x00000000,
		white =		0x00FFFFFF,
		blue =		0x000000FF,
		green =		0x0000FF00,
		red =		0x00FF0000
	};

    typedef struct {
        Color desktop;
        Color border;
        Color window_background;
        Color window_title_bar_background;
        Color window_title_bar_foreground;
        Color button_border;
        Color button_foreground;
        Color button_background;
        Color button_active;
        Color button_hover;
        Color menubar_background;
        Color menubar_foreground;
        Color menubar_select;
        
        uint16_t title_bar_height;
    } Theme;

    class Handle {
        uint32_t id;
        void *data;
    };

    typedef struct {
        uint16_t x;
        uint16_t y;
        uint16_t width;
        uint16_t height;
    } Rect;
}

/**************************************/
/* Functions                          *
/**************************************/

uint16_t avs_draw_string( const char *s, uint16_t x, uint16_t y, uint32_t fg, uint32_t bg, AVS::Font *font, uint16_t size, uint64_t flags );

void avs_draw_char_ttf( uint32_t char_num, uint16_t x, uint16_t y, uint32_t fg, uint32_t bg, AVS::Font *font, uint64_t flags );

#ifdef __cplusplus
}
#endif
#endif