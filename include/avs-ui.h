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

    class Display: public Object {
        public:
        Theme *active_theme;
        
        void refresh_all( void );
    };
}

/**************************************/
/* Functions                          *
/**************************************/

#ifdef __cplusplus
}
#endif
#endif