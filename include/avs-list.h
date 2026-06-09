#ifndef AVS_LIST_CPP_INCLUDED
#define AVS_LIST_CPP_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

namespace AVS {
    class Node {
        public:
        Node *next;
        Node *prev;
        void *data;
    };

	class List {
    protected:
        Node *head;
        Node *tail;
    public:
        int size;

        List();

        void append( void *data );
        void prepend( void *data );
        void insert_before( Node *node, void *data );
        void insert_after( Node *node, void *data );
        void push( void *data );
        void* pop( void );
        void* at_index_data( int index );
        Node* at_index_node( int index );
        void free( Node *node );
        Node* remove( Node *node );
        void empty( void );

        Node* find_data( void *data_to_find, int (*comparison_callback)(void *, void *) );
        void for_each( void ( *for_each_callback )( void *data ) );

        void enqueue( void *data );
        void* dequeue( void );

		void output_diagnostic( void );
	};
}


#ifdef __cplusplus
}
#endif
#endif