#pragma once
class Game
{
	struct gameEntity {
		int x_coordinate;
		int y_coordinate;
		int old_x_coordinate;
		int old_y_coordinate;
		char entityChar;
		char old; //used to check if enemy was standding on a dot to restore it after movement
	};

	static const int width = 20; //CHANGE THIS TO ACTUAL MAP SIZE, map size should be the same between all the levels
	static const int height = 20;

	char gameBoard[height][width]; 
	//Create maps and add them here
	const char level1[height][width];
	const char level2[height][width];
	const char level3[height][width];

	bool gameOver; //used in main loop to know when to end loop
	bool win; //used to check if win/loss and draw next menu

	//Flags for inputs
	bool leftKeyPressed;
	bool rightKeyPressed;
	bool upKeyPressed;
	bool downKeyPressed;

	gameEntity pacman;
	gameEntity enemies[4];

	int difficulty;
	int level;

	void Initialize(); //Runs once at start, sets initial gameBoard, input flags, and enemy/player positions
	void Draw(); //Draws current map state
	void Input(); //Takes an input from the user, checks if it is valid, if so changes direction
	void CalcEnemyMovement(); //Calculates the next move for the enemy, random if difficulty is 1 or 2, BFS if difficulty is 3, maybe split into seperate functions?
	void Update(); //Changes the coordinates of pacman based on Input()
};

