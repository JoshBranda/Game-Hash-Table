#include"hash_name.h"
#include<cstring>
#include<iostream>

using namespace std;



//Default constructor
hash_name::hash_name(int table_size)
{
	size = table_size;
	hash_table = new node *[size];

	for (int x = 0; x < size; ++x)
	{
		*(hash_table + x) = NULL;
	}
}



//Default destructor
hash_name::~hash_name()
{
	node * temp;

	for (int x = 0; x < size; ++x)
	{
		while (*(hash_table + x) != NULL)
		{
			temp = *(hash_table + x);	
			*(hash_table + x) = (*(hash_table + x))->next;
			delete temp;
		}
				
	}

	delete [] hash_table;

}



//My hash function.  It takes the sum of the name and multiplies it by
//the first character in the word, converted to an integer.  Then,
//it mods the result by the size of the array to produce an index
int hash_name::hash_this(char * name)
{
	int length = strlen(name);
	int sum = 0;

	for (int x = 0; x < length; ++x)
	{
		sum += int(*(name + x));
	}
	

	sum = (sum * int(*name)) % size;

	return sum;
}



//First, it uses the hash function to find the index.  Then,
//if the array is empty at that index, it returns a 0 back to the user.
//Otherwise, it calls the recursive retrieve.
int hash_name::retrieve(char * name, retrieve_class & gotcha)
{
	int index = hash_this(name);
	
	if ( *(hash_table + index) == NULL)
		return 0;

	return retrieve((*(hash_table + index)), name, gotcha);
}



//This recursive retrieve returns 0 to the calling function if the game is not found
//to indicate failure.  Otherwise, it fills a LLL of results matching the search.
int hash_name::retrieve(node * current, char * name, retrieve_class & gotcha)
{
	if (!current)
		return 0;

	if ( strcmp(name, current->game.return_name()) == 0)
	{
		gotcha.insert(&(current->game));
		return 1 + retrieve(current->next, name, gotcha);
	}

	return retrieve(current->next,name,gotcha);
}



//This wrapper function first checks to see if the hash table is NULL
//If not, it calls the recursive function
int hash_name::display_table(void)
{
	node ** index = size + hash_table;
	node ** current = hash_table;

	if (!hash_table)
		return 0;
	
	return display_table(current, index);
}



//This recursive function skips any empty elements in the array
//and calls the third recursive function on any that are non-empty
int hash_name::display_table(node ** current, node ** index)
{
	if (current == index) //The function has reached the end of the array
		return 1;
	
	if (*current == NULL)
	{
		return display_table(++current, index);
	}
	
	display_table(*current);
	return display_table(++current, index);
}



//This recursive display traverses the current linked list and displays
//each node's entry. 
int hash_name::display_table(node * current)
{
	if (current == NULL)
		return 0;

	current->game.display_game();
	return display_table(current->next);
}



//This wrapper and following two recursive functions are for displaying
//the collisions in the table.  I copied the above display functions exactly
//except instead of outputting the entries, I output the number of nodes
//in each linked list and some graphics to make it more visually digestable.
int hash_name::display_collisions(void)
{
	node ** index = size + hash_table;
	node ** current = hash_table;

	if (!hash_table)
		return 0;
	
	cout << endl << "Any # greater than 1 represents a collision: " << endl;
	display_collisions(current, index);
	return 1;
}



//See above description
int hash_name::display_collisions(node ** current, node ** index)
{
	if (current == index)
		return 1;
	
	if (*current == NULL)
	{
		cout << ">0" << endl; //Shows an element with no entries
		return display_collisions(++current, index);
	}
	
	int x = display_collisions(*current);
	cout << x << endl;
	return display_collisions(++current, index);
}



//See above above description 
int hash_name::display_collisions(node * current)
{
	if (current == NULL)
	{
		cout << ">";
		return 0;
	}

	cout << "=";
	return 1 + display_collisions(current->next);
}



//This function uses the hash function to find the index to insert the new game at,
//and it also immediately calls the insert function on the hash table by platform so
//that the two always match. 
int hash_name::insert(char * name, game_info & to_add, hash_platform & my_hash_platform)
{
	int index = hash_this(name);
	game_info * to_p_hash; //Pointer to be assigned the address of the new game in the name hash table
	char * p_name;

	if ( *(hash_table + index) == NULL) //Creates a new "head" if the list is empty
	{
		(*(hash_table + index)) = new node;
		(**(hash_table + index)).game.copy_game(to_add); //New game is copied into name hash table
		(**(hash_table + index)).next = NULL;

		p_name = (**(hash_table + index)).game.return_platform(); //Gets the name of the platform to add to the platform hash table
		to_p_hash = &((**(hash_table + index)).game); //Pointer assigned to the game stored in name hash table
		my_hash_platform.insert(p_name, to_p_hash); //Sends the platform name and game pointer to the platform hash table for entry	
		return 1;
	}

	node * temp = new node;
	temp->game.copy_game(to_add);
	temp->next = (*(hash_table + index));
	(*(hash_table + index)) = temp;

	p_name = (**(hash_table + index)).game.return_platform(); //Invokes the input process described above.
	to_p_hash = &((**(hash_table + index)).game);
	my_hash_platform.insert(p_name, to_p_hash);	

	return 1;
}	



//This wrapper function for deleting all entries with a given name first checks
//to see if the element in the array is NULL, and calls the recursive function if not
int hash_name::destroy(char * name, hash_platform & my_hash_platform)
{
	int index = hash_this(name);
	node * current = *(hash_table + index);

	if ( current == NULL)
		return 0;

	if ( strcmp(name, current->game.return_name()) == 0)
		return destroy_heads(name, *(hash_table + index), my_hash_platform);

	return destroy(name, *(hash_table + index), my_hash_platform);
}



//Since an entry can be in the list more than once, I didn't have a special case where head is checked
//just once to see if it is equal to the selected game.  Because once that head is removed, the next
//head could ALSO be the game to be deleted, requiring multiple head deletions.  That is what this
//recursive call is for.
int hash_name::destroy_heads(char * name, node *& current, hash_platform & my_hash_platform)
{
	node * temp = current;

	if (current == NULL)
		return 0;

	if ( strcmp(name, current->game.return_name()) == 0)
	{
		my_hash_platform.remove(current->game.return_name(), current->game.return_platform());
		current = current->next;
		delete temp;
		return 1 + destroy_heads(name, current, my_hash_platform);
	}	

	return destroy(name, current, my_hash_platform);
}



//The final recursive call assumes head is not the selected game, and deletes and reconnects any
//remaining nodes that match the selected game
int hash_name::destroy(char * name, node *& current, hash_platform & my_hash_platform)
{	

	if (!current->next)
		return 0;

	if ( strcmp(name, current->next->game.return_name()) != 0)
		return destroy(name, current->next, my_hash_platform);

	my_hash_platform.remove(current->game.return_name(), current->game.return_platform());
	node * temp = current->next;
	current->next = current->next->next;
	delete temp;

	return 1 + destroy(name, current, my_hash_platform);

}	
