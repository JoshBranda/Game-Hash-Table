/*
Joshua Sander
CS163
Program 3
11/10/2016

This program allows a user to access and edit a list of games and information on those games.

It is represented by an ADT table, sorting the data by value.

There are two menus in the program.  First, the main menu allows the user to print the entire,
unsorted list of games, as well as the list sorted by platform.  They can also add or remove games.
There is a function to see collisions in the hash table.  Obviously, this kind of information about
the data structure would not be in the user application.  However, for myself and any graders, I thought
it would be convenient to have a visual representation of it easily available.

The second menu is accessed through the first.  It allows the user to edit comments (recommendations)
on an individual entry, and also view a single entry.

Aside from the first 8 entries, I created the list of games myself to make sure the format was correct.
*/

#include"games.h"
#include"hash_name.h"
#include"hash_platform.h"
#include"retrieve_class.h"
#include<cstring>
#include<iostream>
#include<fstream>

using namespace std;

const int MAX = 100;
const int COMMENT_MAX = 300;

int load_file(hash_name & my_hash, hash_platform & my_hash_platform);
int add_game(hash_name & my_hash, hash_platform & my_hash_platform);
int remove_game(hash_name & my_hash, hash_platform & my_hash_platform);
int view_game(hash_name & my_hash, hash_platform & my_hash_platform);
int display_platform(hash_platform & my_hash_platform);



int main()
{
	game_info game;
	hash_name my_hash;
	hash_platform my_hash_platform;
	load_file(my_hash, my_hash_platform);
	char choice;
	
	cout << endl << "Welcome to the game archive!" << endl;

	do {

		cout << endl;
		cout << "Please choose from the following options:" << endl;
		cout << "A: Add an entry to the archive" << endl;
		cout << "B: Remove a game from the archive" << endl;
		cout << "C: View or Edit a game" << endl;
		cout << "D: Display games by platform" << endl;
		cout << "E: Display all games" << endl;
		cout << "F: Exit this program" << endl;
		cout << "G: Display collisions (Coders Only!)" << endl;

		cin >> choice;
		cin.ignore();

		switch (choice)
		{
			case 'a':
			case 'A':
				add_game(my_hash, my_hash_platform);
				break;
			case 'b':
			case 'B':
				remove_game(my_hash, my_hash_platform);
				break;
			case 'c':
			case 'C':
				view_game(my_hash, my_hash_platform);
				break;
			case 'd':
			case 'D':
				display_platform(my_hash_platform);
				break;
			case 'e':
			case 'E':
				cout << endl;
				my_hash.display_table();
				break;
			case 'f':
			case 'F':
				break;
			case 'g':
			case 'G':
				cout << endl;
				my_hash.display_collisions();
				break;
			default:
				cout << "This is not a valid choice!  Choose again!" << endl;
				break;	
		}

	}while (choice != 'f' && choice != 'F');

	return 0;

}



//Loads a pre-selected file and reads the data, line by line, from the file.
int load_file(hash_name & my_hash, hash_platform & my_hash_platform)
{
	char name[MAX];
	char desc[MAX];
	char type[MAX];
	char platform[MAX];
	int rating;
	char comments[COMMENT_MAX];
 
	game_info new_game;
	ifstream games_list;
	games_list.open("CS163_games.txt");
	

	games_list.ignore(MAX,'\n');
	games_list.getline(name,MAX,':');
	games_list.getline(desc,MAX,':');
	games_list.getline(type,MAX,':');
	games_list.getline(platform,MAX,':');
	games_list >> rating;
	games_list.ignore(MAX,':');
	games_list.getline(comments,COMMENT_MAX,':');
	games_list.ignore(MAX,'\n');

	while (!games_list.eof())
	{
		new_game.insert_game_info(name, desc, type, platform, rating, comments);
		my_hash.insert(name, new_game, my_hash_platform);
		games_list.getline(name,MAX,':');
		games_list.getline(desc,MAX,':');
		games_list.getline(type,MAX,':');
		games_list.getline(platform,MAX,':');
		games_list >> rating;
		games_list.ignore(MAX,':');
		games_list.getline(comments,COMMENT_MAX,':');
		games_list.ignore(MAX,'\n');
	}

	games_list.close();

	return 1;
}



//Reads user input and places it into table as new entry
int add_game(hash_name & my_hash, hash_platform & my_hash_platform)
{
	char new_name[MAX];
	char new_desc[MAX];
	char new_type[MAX];
	char new_platform[MAX];
	int rating;
	char new_comments[MAX];
	game_info to_add;
	
	cout << endl << "Please enter the name of the game" << endl;
	cin.getline(new_name, MAX, '\n');
	cout << "Please enter the description for the game" << endl;
	cin.getline(new_desc, MAX, '\n');
	cout << "Please enter the type of game" << endl;
	cin.getline(new_type, MAX, '\n');
	cout << "Please enter the platform for the game" << endl;
	cin.getline(new_platform, MAX,'\n');
	cout << "Please enter its star rating" << endl;
	cin >> rating;
	cin.ignore();
	cout << "Please enter comments for the game" << endl;
	cin.getline(new_comments, MAX,'\n');

	to_add.insert_game_info(new_name, new_desc, new_type, new_platform, rating, new_comments);

	my_hash.insert(new_name, to_add, my_hash_platform);

	return 1;
}	



//Reads the name given by a user and removes it from the table
int remove_game(hash_name & my_hash, hash_platform & my_hash_platform)
{
	char remove_name[MAX];

	cout << endl << "Enter the name of the game you would like to remove: " << endl;
	cin.getline(remove_name, MAX, '\n');

	if (my_hash.destroy(remove_name, my_hash_platform) == 0)
	{
		cout << "This game is not in your list!" << endl;
		return 0;
	}

	cout << "Success!" << endl;
	return 1;
}



//Copies an entry from the table into a temporary object which can
//then be maninuplated or viewed by the user.
//This also has the 2nd menu to give the user options with the entry
int view_game(hash_name & my_hash, hash_platform & my_hash_platform)
{
	char choice = 'a';
	char name[MAX];
	char comments[COMMENT_MAX]; 
	retrieve_class gotcha; //Object containing desired table info

	cout << endl << "Please enter the name of the game" << endl;
	cin.getline(name, MAX, '\n');

	if (my_hash.retrieve(name, gotcha) == 0)
	{
		cout << endl << "This item is not in the list!" << endl;
	}

	else
	{
		cout << endl << "This is what we found: " << endl;
		gotcha.display_games();	

		cout << endl << "Which platform do you want?" << endl;
		cin.getline(name, MAX, '\n');
	
		cout << endl << "This is the matching entry: " << endl;		
		gotcha.display_platform(name);
	}	

	do {
		cout << endl;
		cout << "Please choose from the following options:" << endl;
		cout << "A: Add comments to the game" << endl;
		cout << "B: Display the game" << endl;
		cout << "F: Return to main menu" << endl;

		cin >> choice;
		cin.ignore();

		switch (choice)
		{
			case 'a':
			case 'A':
				cout << endl << "Enter the comments to add: " << endl;	
				cin.getline(comments, COMMENT_MAX, '\n');

				gotcha.add_comments(name, comments);

				cout << endl << "The new game entry is: " << endl;
				gotcha.display_platform(name);	
				break;
			case 'b':
			case 'B':
				gotcha.display_platform(name);
				break;
			case 'f':
			case 'F':
				break;
			default:
				cout << "This is not a valid choice!  Choose again!" << endl;
				break;	
		}

	}while (choice != 'f' && choice != 'F');
	
	return 1;
}	



//This displayes all of the games by a chosen platform 
int display_platform(hash_platform & my_hash_platform)
{
	char p_name[MAX];

	cout << endl << "Please enter the platform you would like to display games for: " << endl;	
	cin.getline(p_name,MAX,'\n');
	cout << endl;
	
	if (my_hash_platform.display_platform(p_name) == 0)
		cout << "This platform is not in your list!" << endl;

	return 1;
}
	
