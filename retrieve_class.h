#ifndef RETRIEVE_NOW
#define RETRIEVE_NOW

#include"hash_platform.h"

/*
This was a class I created to handle the retrieve function.  It allows the user application
to receive multiple game objects stored in one retrieve object for access and maninuplation.
I did not want the user application to deal with nodes directly, violating the ADT wall, so
I made it a class that manages the nodes.
*/

class retrieve_class 
{
	public:
		retrieve_class();
		~retrieve_class();

		//Accessor functions
		int display_games(void);
		int display_platform(char * p_name);

		//Mutator functions
		int insert(game_info * to_add);
		int add_comments(char * p_name, char * to_add);
		int replace_comments(char * to_remove);	


	private:
		p_node * head;

};

#endif
