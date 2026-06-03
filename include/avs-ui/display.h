#ifndef AVS_UI_OBJECT_INCLUDED
#define AVS_UI_OBJECT_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui.h"
#include "avs-ui/object.h"

namespace AVS {
	class Display: public Object {
        public:
        void refresh_all( void );
    };
}

#ifdef __cplusplus
}
#endif
#endif