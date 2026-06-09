#include "avs-ui.h"
#include "avs-ui/app.h"

using namespace AVS;

Object::Object( void ) {
	children = new List();
}

void Object::hide( void ) {
	this->is_visible = false;
}

void Object::show( void ) {
	this->is_visible = true;
}

void Object::draw( void ) {
	if( children != NULL ) {
		printf( "Drawing children.\n" );

		children->for_each( []( void *data ) {
			Object *obj = static_cast<Object *>(data);

			if( obj != NULL ) {
				obj->draw();
			}
		});
	}
}

void Object::add_child( Object* obj ) {
	obj->parent = this;

	if ( children != NULL ) {
		children->push( obj );
	}
}

/**
 * @brief Finds the app that the object belongs to
 * 
 * @return Object* pointer to the app, otherwise NULL;
 */
Object* Object::find_app( void ) {
	Object *o = this;
	bool found = false;

	do {
		if( App *a = dynamic_cast<App *>(o) ) {
			found = true;
		} else {
			o = o->parent;
			if( o == nullptr ) {
				return NULL;
			}
		}

	} while( !found );

	return o;
}