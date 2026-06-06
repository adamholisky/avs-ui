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

/**************************************/
/* System API Macro Config            */
/**************************************/

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

#ifdef __cplusplus
}
#endif
#endif