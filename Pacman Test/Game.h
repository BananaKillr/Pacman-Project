#pragma once
#include <utility>
#include <vector>
#include <unordered_map>
using namespace std;

class Game
{

	struct gameEntity {
		pair<int, int> position; //Row,col
		pair<int, int> oldPosition;
		char entityChar;
		char old; //used to check if enemy was standding on a dot to restore it after movement
	};

	unordered_map<int, Save> saves;

	static const int width = 20; //CHANGE THIS TO ACTUAL MAP SIZE, map size should be the same between all the levels
	static const int height = 20;

	char gameBoard[height][width]; 
	//Create maps and add them here
	const char level1[height][width];
	const char level2[height][width];
	const char level3[height][width];
	const vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

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

	void Menu(); //Runs when program first launched, draws menu
	void Initialize(); //Runs once at start, sets initial gameBoard, input flags, and enemy/player positions
	void Draw(); //Draws current map state
	void Input(); //Takes an input from the user, checks if it is valid, if so changes direction
	void CalcEnemyMovement(); //Calculates the next move for the enemy, random if difficulty is 1 or 2, BFS if difficulty is 3, maybe split into seperate functions?
	void Update(); //Changes the coordinates of pacman based on Input(), checks if lose condiiton met
	pair<int, int> nextStep(pair<int,int> pacmanPosition, pair<int,int> enemyPosition); //Returns the next coordinate an enemy needs to move to, used in CalcEnemyMovement
};

class Save {
	char username[5];
	unordered_map<int, int[3]> highScores;

	Save(char username[5]);
	Save(string save);
	void newScore(int level, int score);
	string toString();
};