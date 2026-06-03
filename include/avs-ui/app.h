#ifndef AVS_UI_APP_INCLUDED
#define AVS_UI_APP_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-ui/object.h"

#define AVS_NAME_MAX 50

namespace AVS {
	class App: public Object {
    private:
        char display_name[AVS_NAME_MAX];
	public:
        App( const char *disp_name );
		void output_diagnostic( void );
        void run( void );
	};
}


#ifdef __cplusplus
}
#endif
#endif