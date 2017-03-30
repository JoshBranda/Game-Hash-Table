#include"games.h"
#include"hash_name.h"
#include<cstring>
#include<iostream>

using namespace std;



//Default constructor
game_info::game_info()
{
	name = NULL;
	description = NULL;
	type = NULL;
	platform = NULL;
	rating = 0;
	comments = NULL;
}



//This insert function allows the user application to insert data directly into a game object
int game_info::insert_game_info(char * new_name, char * new_description, char * new_type, char * new_platform, int new_rating, char * new_comments)
{
	if (name)
		delete [] name;
	name = new char[strlen(new_name) + 1];
	strcpy(name,new_name);

	if (description)
		delete [] description;
	description = new char[strlen(new_description) + 1];
	strcpy(description,new_description);

	if (type)
		delete [] type;
	type = new char[strlen(new_type) + 1];
	strcpy(type,new_type);

	if (platform)
		delete [] platform;
	platform = new char[strlen(new_platform) + 1];
	strcpy(platform,new_platform);

	rating = new_rating;

	if (comments)
		delete [] comments;
	comments = new char[strlen(new_comments) + 1];
	strcpy(comments,new_comments);

	return 1;
}	


//Destructor
game_info::~game_info()
{
	if (name)
		delete [] name;
		name = NULL;
	if (description)
		delete [] description;
		description = NULL;
	if (type)
		delete [] type;
		type = NULL;
	if (platform)
		delete [] platform;
		platform = NULL;
	if (comments)
		delete [] comments;
		comments = NULL;
}



//This copies the data from the argument game into the current game
int game_info::copy_game(game_info & to_add)
{
	if (!to_add.name)
		return 0;
	
	if (name)
		delete [] name;
	name = new char[strlen(to_add.name) + 1];
	strcpy(name,to_add.name);

	if (description)
		delete [] description;
	description = new char[strlen(to_add.description) + 1];
	strcpy(description,to_add.description);

	if (type)
		delete [] type;
	type = new char[strlen(to_add.type) + 1];
	strcpy(type,to_add.type);

	if (platform)
		delete [] platform;
	platform = new char[strlen(to_add.platform) + 1];
	strcpy(platform,to_add.platform);

	rating = to_add.rating;

	if (comments)
		delete [] comments;
	comments = new char[strlen(to_add.comments) + 1];
	strcpy(comments,to_add.comments);

	return 1;
}



//This appends comments to the end of the current comments on any given game.
int game_info::comment_add(char * new_comments)
{
	char * to_add;
	to_add = new char[strlen(new_comments) + strlen(comments) + 3];
	
	strcpy(to_add, comments);
	strcat(to_add, ". ");
	strcat(to_add, new_comments);

	if (comments)
		delete comments;

	comments = to_add;

	return 1;
}



//This outputs the data inside the current game 
int game_info::display_game(void)
{
	if (!name)
		return 0;
	cout << name << ": " << description << ": " << type << ": " << platform << ": " << rating << " stars: " << comments << endl;
	return 1;
}



//This returns the name of the game back to the user
char * game_info::return_name(void)
{
	return name;
}



//This returns the name of the platform back to the user
char * game_info::return_platform(void)
{
	return platform;
}
