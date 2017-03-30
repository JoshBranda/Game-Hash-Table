#ifndef HASHING_PLATFORMS
#define HASHING_PLATFORMS
#include"games.h"

/*
This data structure represents a hash table of games by platform.
I created a distinct struct for it, p_node, to hold pointers to games
intead of the actual games to save memory.  I also discovered the p_node
struct would work well with the retrieve function, so I used it there too.

*/

struct p_node
{
	game_info * p_game;
	p_node * next;
};

class hash_platform
{
	public:
		hash_platform(int hash_size = 37);
		~hash_platform();

		//Accessor functions
		int display_platform(char * p_name);

		//Mutator functions	
		int insert(char * p_name, game_info * to_add);
		int remove(char * g_name, char * p_name);

	private:
		int hash_this(char * p_name);	

		int size;
		p_node ** hash_table;

};


#endif
