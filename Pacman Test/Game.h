#pragma once
#include <utility>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <Windows.h>
using namespace std;

class Save {
public:
	string userName;
	unordered_map<int, priority_queue<int, std::vector<int>, std::less<int>>> highScores; // Key is level, value is all scores for that level

	Save(string username); //To create new user
	void fromString(string save); //To load user from file
	void newScore(int level, int score); // Add score, check if in top 3
	string toString();
};

class Game
{
private:
	unordered_map<int, string> levels;

	struct gameEntity {
		pair<int, int> position; //Row,col
		pair<int, int> oldPosition;
		char entityChar;
		char old; //used to check if enemy was standding on a dot to restore it after movement
	};

	unordered_map<string, Save*> saves;

	static const int width = 20; //CHANGE THIS TO ACTUAL MAP SIZE, map size should be the same between all the levels
	static const int height = 20;

	char gameBoard[height][width];
	//Create maps and add them here
	const char map1[height][width] = {
		"###################",
		"#........#........#",
		"#.##.###.#.###.##.#",
		"#.................#",
		"#.##.#.#####.#.##.#",
		"#....#...#...#....#",
		"####.###.#.###.####",
		"####.#.......#.####",
		"#......#####......#",
		"####.#.#####.#.####",
		"####.#.......#.####",
		"#....#.#####.#....#",
		"#.##.....#.....##.#",
		"#.##.###.#.###.##.#",
		"#..#...........#..#",
		"##.#.#.#####.#.#.##",
		"#....#...#...#....#",
		"#.######.#.######.#",
		"#.................#",
		"###################", };
	const char map2[height][width] = {
	"###################",
	"#.....#.....#.....#",
	"#.###.#.###.#.###.#",
	"#.................#",
	"##.#.###.#.###.#.##",
	"##.#.###.#.###.#.##",
	"##.#.....#.....#.##",
	"##.###.#####.###.##",
	"#.................#",
	"##.###.#####.###.##",
	"##.#...#...#...#.##",
	"##.#.#...#...#.#.##",
	"##...#########...##",
	"#..#...#...#...#..#",
	"#.####.#.#.#.####.#",
	"#......#.#.#......#",
	"#.###....#....###.#",
	"#.###.#######.###.#",
	"#.................#",
	"###################" };
	const char map3[height][width] = {
	"###################",
	"#........#........#",
	"#.#.####.#.####.#.#",
	"#.#....#.#.#....#.#",
	"#.####.#...#.####.#",
	"#......#.#.#......#",
	"#.####...#...####.#",
	"#.####.#####.####.#",
	"#......#####......#",
	"###.##.#####.##.###",
	"###.##.#...#.##.###",
	"#........#........#",
	"#.##.#.#####.#.##.#",
	"#.##.#.......#.##.#",
	"#....#.#####.#....#",
	"##.#.#...#...#.#.##",
	"#..#...#.#.#...#..#",
	"#.####.#.#.#.####.#",
	"#......#...#......#",
	"###################",
	};
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
	string currentUser;
	char gameMap[height][width];


	int difficulty;
	int level;
	int input = 0;
	int maxLevel = 1;

	void Menu(); //Runs when program first launched, draws menu
	void Initialize(); //Runs once at start, sets initial gameBoard, input flags, and enemy/player positions
	void Draw(); //Draws current map state
	void Input(); //Takes an input from the user, checks if it is valid, if so changes direction
	void CalcEnemyMovement(); //Calculates the next move for the enemy, random if difficulty is 1 or 2, BFS if difficulty is 3, maybe split into seperate functions?
	pair<int, int> NextStep(pair<int, int> enemyPosition); //Returns the next coordinate an enemy needs to move to, used in CalcEnemyMovement
	void Update(); //Changes the coordinates of pacman based on Input(), checks if lose condiiton met
	void saveToFile();
	void LoadFromFile();
	void ExitGame();
	void MainLoop();
	void CopyMap(const char source[][height], char dest[][height]);

	public:
		Game();
};

