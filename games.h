#ifndef GAME_INFORMATION
#define GAME_INFORMATION

/*
This data structur represents the game itself.  It contains all the necessary functions
for storing and editing data within the games themselves
*/


class game_info
{
	public:
		game_info();
		int insert_game_info(char * new_name, char * new_description, char * new_type, char * new_platform, int new_rating, char * new_comments);
		~game_info();

		//Mutator functions
		int copy_game(game_info & to_add);
		int comment_add(char * new_comments);

		//Accessor functions
		int display_game(void);
		char * return_name(void);
		char * return_platform(void);

	private:
		char * name;
		char * description;
		char * type;
		char * platform;
		int rating;
		char * comments;
};

#endif
