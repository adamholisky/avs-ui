#ifndef AVS_UI_OBJECT_INCLUDED
#define AVS_UI_OBJECT_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include "avs-list.h"

namespace AVS {
	class Object {
	protected:
		// ?
	public:
		Object *parent;
		List *children;
		
		bool is_container;
		bool is_drawable;
		bool is_hover;
		bool is_visible;

		uint16_t x;
		uint16_t y;
		uint16_t width;
		uint16_t height;

		uint16_t inner_x;
		uint16_t inner_y;
		uint16_t inner_width;
		uint16_t inner_height;

		virtual void output_diagnostic( void ) = 0;
		virtual void draw( void );
		virtual void hide( void );
		virtual void show( void );

		virtual ~Object() = default;
	};
}


#ifdef __cplusplus
}
#endif
#endif