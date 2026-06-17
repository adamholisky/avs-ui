#include "avs-ui.h"
#include "avs-ui/app.h"

using namespace AVS;

Object::Object( void ) {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	inner_x = 0;
	inner_y = 0;
	inner_width = 0;
	inner_height = 0;
	container_offset_x = 0;
	container_offset_y = 0;

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

void Object::add_child( Object* obj_child ) {
	obj_child->parent = this;

	if ( children != NULL ) {
		children->push( obj_child );
	}
}

void Object::add_child( Object *obj_parent, Object *obj_child ) {
	if( obj_parent == nullptr ) { return; }
	if( obj_child == nullptr ) { return; }

	obj_parent->add_child( obj_child );
}

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

uint16_t Object::get_absolute_x( void ) {
	uint16_t parent_abs_x = this->parent == nullptr ? 0 : parent->get_absolute_x();

	printf( "returning abs_x: %d (%d + %d + %d)\n", this->x + parent_abs_x + container_offset_x, this->x, parent_abs_x, container_offset_x );

	return this->x + parent_abs_x + container_offset_x;
}

uint16_t Object::get_absolute_y( void ) {
	uint16_t parent_abs_y = this->parent == nullptr ? 0 : parent->get_absolute_y();

	printf( "returning abs_y: %d\n", this->x + parent_abs_y + container_offset_y );

	return this->y + parent_abs_y + container_offset_y;
}