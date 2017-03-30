#ifndef HASHING_NAME
#define HASHING_NAME
#include"games.h"
#include"hash_platform.h"
#include"retrieve_class.h"

/*
This data structure is a hash table organized by game name.
It has three recursive functions inside of it, display_table, display_collisions, and retrieve.
The first two recursive functions have a wrapper and two seperate recursive functions.
That is because the DS is an array of linear linked lists.

Also, my second hash table, organized by platform, has embedded insert, remove, etc functions
inside of the functions here.  That way, the two hash tables are always equivalent in content.

Finally, a seperate retrieve class was created to allow the retrieve function here to pass
multiple objects to the user application.

*/

struct node {
	game_info game;
	node * next;
};

class hash_name
{
	public:
		hash_name(int table_size = 37);
		~hash_name();

		//Accessor functions
		int retrieve(char * name, retrieve_class & gotcha);
		int display_table(void);
		int display_collisions(void);

		//Mutator functions
		int insert(char * name, game_info & to_add, hash_platform & my_hash_platform);
		int destroy(char * name, hash_platform & my_hash_platform);

	private:

		int hash_this(char * name);
		int retrieve(node * current, char * name, retrieve_class & gotcha);
		int display_table(node ** current, node ** index);
		int display_table(node * current);
		int display_collisions(node ** current, node ** index);
		int display_collisions(node * current);
		int destroy_heads(char * name, node *& current, hash_platform & my_hash_platform);
		int destroy(char * name, node *& current, hash_platform & my_hash_platform);

		node ** hash_table;
		int size;
		

};

#endif
