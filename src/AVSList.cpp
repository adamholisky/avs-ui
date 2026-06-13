/**
 * @file list.c
 * @author Adam Holisky (adam.holisky@gmail.com)
 * @brief A simple linked list implementation
 * @version 0.1
 * @date 2026-06-03
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "avs-platform.h"
#include "avs-list.h"

using namespace AVS;

 /**
  * @brief Initalize an AVS list
  *
  */
List::List() {
	head = NULL;
	tail = NULL;
	size = 0;
}

/**
 * @brief Adds a new element at the end of the list
 *
 * @param list Pointer ot the avs_list
 * @param data Pointer to the data to add to the list
 * @return avs_list* NULL if failed, otherwise pointer to the avs_list
 */
void List::append( void* data ) {
	insert_after( NULL, data );
}

/**
 * @brief Prepend the data to the front of the list
 *
 * @param list
 * @param data
 * @return avs_list*
 */
void List::prepend( void* data ) {
	insert_before( head, data );
}

/**
 * @brief Inserts the given data before the provided node.
 *
 * @param list
 * @param node
 * @param data
 * @return avs_list*
 */
void List::insert_before( Node* before_node, void* data ) {
	Node *n = new Node();

	n->data = data;
	n->prev = NULL;
	n->next = before_node;

	if ( before_node == NULL ) {
		head = n;
		tail = n;
	}
	else if ( before_node == head ) { // are we inserting at the head of a list already populated?
		head = n;

		// do we need to update tail as well?
		if ( tail == NULL ) {
			tail = n;
		}

		before_node->prev = n;
	}
	else {
		n->prev = before_node->prev;
		before_node->prev = n;
		n->prev->next = n;
	}

	size++;
}

/**
 * @brief Inserts the given data after the provided node.
 *
 * @param list
 * @param node
 * @param data
 * @return avs_list*
 */
void List::insert_after( Node* after_node, void* data ) {
	Node *n = new Node();

	n->data = data;
	n->prev = NULL;
	n->next = NULL;

	// after_node being NULL means add to end of list
	// OR if after_node is set to the list's tail
	if ( after_node == NULL || after_node == tail ) {
		//debugf( "part 1" );
		if ( tail == NULL ) {
			// debugf( "part 2" );
			head = n;
		}
		else {
			//debugf( "part 3" );
			tail->next = n;
			n->prev = tail;
		}

		tail = n;
	}
	else {
		// debugf( "part 4" );
		n->next = after_node->next;
		n->next->prev = n;
		n->prev = after_node;
		after_node->next = n;
		// printf("..");
	}

	size++;
	//  debugf( "part 5" );
}

/**
 * @brief Push data to the top of the list
 *
 * @param list
 * @param data
 * @return avs_list*
 */
void List::push( void* data ) {
	return prepend( data );
}

/**
 * @brief Pop data off the top of the list
 *
 * @param list
 * @return avs_node*
 */
void* List::pop( void ) {
	if ( head == NULL ) {
		return NULL;
	}

	Node *n = remove( head );
	void *data = n->data;

	avs_free( n );

	return data;
}

/**
 * @brief Returns data located at index position of the list. 0 based.s
 *
 * @param list
 * @param index
 * @return void*
 */
void* List::at_index_data( int index ) {
	Node* n = at_index_node( index );

	if ( n == NULL ) {
		return NULL;
	}

	return n->data;
}

/**
 * @brief Returnsa the node located at index position of the list. 0 based.
 *
 * @param list
 * @param index
 * @return avs_node*
 */
Node* List::at_index_node( int index ) {
	if ( index > ( size - 1 ) ) {
		return NULL;
	}
	else if ( index < 0 ) {
		return NULL;
	}
	else {
		Node *n = head;

		for ( int i = 0; i < index; i++ ) {
			n = n->next;
		}

		return n;
	}
}

/**
 * @brief Removes an element from the list, does NOT avs_free memory
 *
 * @param list Pointer to the avs_list
 * @param node Pointer to the node to remove
 * @return avs_list* NULL if failed, otherwise pointer to the avs_list
 */
Node* List::remove( Node* n ) {
	/// TODO: check to ensure the node is in the list

	Node* new_next_node = n->next;

	if ( n->prev == NULL && n->next == NULL ) {
		head = NULL;
		tail = NULL;
	}
	else if ( n->prev == NULL ) {
		// Removing the head of list
		head = new_next_node;

		// If node is not the only element, then carry through prev's null
		if ( new_next_node != NULL ) {
			new_next_node->prev = NULL;
		}
	}
	else if ( n->next == NULL ) {
		// Removing the tail of the list
		tail = n->prev;
		tail->next = NULL;
	}
	else {
		// Removing non-head or tail element
		n->next->prev = n->prev;
		n->prev->next = n->next;
	}

	size--;

	return n;
}

/**
 * @brief Removes an element from the list and avs_frees the memory
 *
 * @param list Pointer to the avs_list
 * @param node Pointer to the node to remove
 * @return avs_list* NULL if failed, otherwise pointer to the avs_list
 */
void List::free( Node* node ) {
	if ( remove( node ) != NULL ) {
		avs_free( node );
	}
}

/**
 * @brief Calls function 'for_each_callback' for every node in the list
 * 
 * []( void *my_obj ) {
 *     Object *obj = static_cast<Object *>(my_obj);
 *     do_stuff();
 * }
 * 
 * @param list Pointer to the avs list
 * @param for_each_callback Pointer to the function to call.
 */
void List::for_each( void ( *for_each_callback )( void *data ) ) {
	Node* n = head;

	for ( int i = 0; i < size; i++ ) {
		for_each_callback( n->data );
		n = n->next;
	}
}

/**
 * @brief Returns a pointer to the node of the list containing the given data, using the comparison function callback
 *
 * @param list Pointer to the avs list
 * @param data_to_find Pointer to the data to find
 * @param comparison_callback Pointer to the function to do the comparison
 * @return avs_node* Pointer to the node containing the data, otherwise NULL
 *
 * Comparison function results:
 *   - number == a is less than b
 *   0 == a equals b
 *   + number = a is greater than b
 */
Node* List::find_data( void* data_to_find, int ( *comparison_callback )( void*, void* ) ) {
	Node* n = head;

	for ( int i = 0; i < size; i++ ) {
		int compare_result = comparison_callback( data_to_find, n->data );
		if ( compare_result == 0 ) {
			return n;
		}

		n = n->next;
	}

	return NULL;
}

/**
 * @brief Empties out the given list
 *
 * @param list pointer to an avs_list
 */
void List::empty( void ) {
	while ( head ) {
		free( head );
	}

	size = 0;
}

/**
 * @brief Enqueues data to the "front" of the list
 *
 * @param list
 * @param data
 * @return avs_list*
 */
void List::enqueue( void* data ) {
	return prepend( data );
}

/**
 * @brief Dequeues data from the "back" of the list
 *
 * @param list
 * @return void*
 */
void* List::dequeue( void ) {
	Node *n = remove( tail );
	void *data = n->data;

	avs_free( n );

	return data;
}