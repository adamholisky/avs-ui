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

		uint16_t x_abs;
		uint16_t y_abs;

		/**
		 * @brief X position, relative to container that holds the object
		 * 
		 */
		uint16_t x;

		/**
		 * @brief Y position, relative to container that holds the object
		 * 
		 */
		uint16_t y;

		/**
		 * @brief Width of the object
		 * 
		 */
		uint16_t width;

		/**
		 * @brief Height of the object
		 * 
		 */
		uint16_t height;

		/**
		 * @brief X start position, inside the border
		 * 
		 */
		uint16_t inner_x;

		/**
		 * @brief Y position, inside the border
		 * 
		 */
		uint16_t inner_y;

		/**
		 * @brief Object width, inside the border
		 * 
		 */
		uint16_t inner_width;

		/**
		 * @brief Object height, inside the border
		 * 
		 */
		uint16_t inner_height;

		/**
		 * @brief Amount to offset X by for objects inside the container
		 * 
		 */
		uint16_t container_offset_x;

		/**
		 * @brief Amount to offset Y by for objects inside the container
		 * 
		 */
		uint16_t container_offset_y;

		/**
		 * @brief Prints diagnostic info about the object to the console
		 * 
		 */
		virtual void output_diagnostic( void ) = 0;

		/**
		 * @brief Draws the object and all its children
		 * 
		 */
		virtual void draw( void );

		/**
		 * @brief Hides the object on the screen, prevents drawing
		 * 
		 */
		virtual void hide( void );

		/**
		 * @brief Shows the object on the screen
		 * 
		 */
		virtual void show( void );

		Object( void );
		virtual ~Object() = default;

		/**
		 * @brief Adds the given object as a child to the calling object
		 * 
		 * @param obj_child 
		 */
		void add_child( Object *obj_child );

		/**
		 * @brief Adds obs_child as a child to obj_parent
		 * 
		 * @param obj_parent 
		 * @param ojb_child 
		 */
		void add_child( Object *obj_parent, Object *ojb_child );

		/**
		 * @brief Finds the app that the object belongs to
		 * 
		 * @return Object* pointer to the app, otherwise NULL;
		 */
		Object* find_app( void );

		/**
		 * @brief Returns the absolute X coords of the object
		 * 
		 * @return uint16_t 
		 */	
		uint16_t get_absolute_x( void );
		
		/**
		 * @brief Returns the absolute Y coords of the object
		 * 
		 * @return uint16_t 
		 */
		uint16_t get_absolute_y( void );
	};
}


#ifdef __cplusplus
}
#endif
#endif