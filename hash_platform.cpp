#include"hash_platform.h"
#include<cstring>
#include<iostream>


using namespace std;



//Default constructor
hash_platform::hash_platform(int hash_size)
{
	size = hash_size;
	hash_table = new p_node * [size];

	for (int index = 0; index < size; ++index)
	{
		*(hash_table + index) = NULL;
	}
}



//Destructor
hash_platform::~hash_platform()
{
	p_node * temp;

	for (int index = 0; index < size; ++index)
	{	
		while(*(hash_table + index) != NULL)
		{
			temp = *(hash_table + index);
			*(hash_table + index) = (*(hash_table + index))->next;
			delete temp;
		}
	}

	delete [] hash_table;
}				



//Hash function mutliplies the first character in the platform name
//by the sum of the characters in the platform name and mods it by the size
//of the array to produce an index
int hash_platform::hash_this(char * p_name)
{
	int length = strlen(p_name);
	int sum = 0;
	
	for (int index = 0; index < length; ++index)
	{
		sum += *(p_name + index);
	}

	sum = (sum * int(*p_name)) % size;

	return sum;
}	



int hash_platform::insert(char * p_name, game_info * to_add)
{
	int index = hash_this(p_name);
	
	if ( *(hash_table + index) == NULL)
	{
		(*(hash_table + index)) = new p_node;
		(**(hash_table + index)).p_game = to_add;
		(**(hash_table + index)).next = NULL;
		return 1;
	}

	p_node * temp = new p_node;
	temp->p_game = to_add;
	temp->next = (*(hash_table + index));
	(*(hash_table + index)) = temp;
	return 1;
}



//This remove function increments through the array of LLLs checking for entries.
//When an element is not NULL, it traverses the LLL with a previous and current pointer
//to delete entries that match and reconnect the list after deletion
int hash_platform::remove(char * g_name, char * p_name)
{
	int index = hash_this(p_name);
	p_node * current = *(hash_table + index);
	p_node * previous;

	if ( *(hash_table + index) == NULL)
		return 0;

	if ( strcmp(g_name, current->p_game->return_name()) == 0)
	{
		*(hash_table + index) = (*(hash_table + index))->next;
		delete current;
		return 1;
	}

	while (current)
	{
		if (strcmp(g_name, current->p_game->return_name()) == 0)
			current = NULL;	
		else 
		{	
			previous = current;
			current = current->next;
		}
	}

	if (previous->next)
	{
		current = previous->next->next;
		delete previous->next;
		previous->next = current;
	}
	
	return 1;
}

	

//This display function takes the platform name from the user as an argument,
//finds the appropriate index in the table by hashing that platform name,
//then traverses the LLL at the index and calls the print function on each game
int hash_platform::display_platform(char * p_name)
{
	int index = hash_this(p_name);
	p_node * current = *(hash_table + index);

	if (!current)
		return 0;

	while (current)
	{
		if ( strstr(current->p_game->return_platform(), p_name) != NULL)
		{
			current->p_game->display_game();
		}
		current= current->next;
	}

	return 1;
}		
