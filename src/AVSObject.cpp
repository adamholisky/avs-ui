#include "avs-ui.h"

using namespace AVS;

void Object::hide( void ) {
    this->is_visible = false;
}

void Object::show( void ) {
    this->is_visible = true;
}

void Object::draw( void ) {
    
}