#ifndef AVS_DISPLAY_INCLUDED
#define AVS_DISPLAY_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui.h"
#include "avs-ui/object.h"

namespace AVS {
	class Display: public Object {
        public:
            void refresh_all( void );
            void refresh_rect( Rect *r );
    };
}

#ifdef __cplusplus
}
#endif
#endif