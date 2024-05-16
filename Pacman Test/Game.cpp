#include "Game.h"
#include <iostream>
#include <vector>
#include <queue>
#include <Windows.h>
#include <sstream>
#include <fstream>	
#include <limits>
using namespace std;

Game::Game() {
	levels[1] = "1. Map 1";
	levels[2] = "2. Map 2";
	levels[3] = "3. Map 3";
	LoadFromFile();
	Menu();
};

void Game::CalcEnemyMovement() {


	switch (difficulty)
	{
	case 1: //Uses random movement
	case 2:
		for (int i = 0; i < 4; i++)
		{
			std::vector<int> directions; //0 up, 1 right, 2 down, 3 left 
			int enemy_x;
			int enemy_y;

			directions.clear();
			enemy_x = enemies[i].position.first;
			enemy_y = enemies[i].position.second;

			if (gameBoard[enemy_y - 1][enemy_x] != '#' && gameBoard[enemy_y - 1][enemy_x] != 'M') directions.push_back(0);
			if (gameBoard[enemy_y][enemy_x + 1] != '#' && gameBoard[enemy_y - 1][enemy_x] != 'M') directions.push_back(1);
			if (gameBoard[enemy_y + 1][enemy_x] != '#' && gameBoard[enemy_y - 1][enemy_x] != 'M') directions.push_back(2);
			if (gameBoard[enemy_y][enemy_x - 1] != '#' && gameBoard[enemy_y - 1][enemy_x] != 'M') directions.push_back(3);

			int pickedDirection = directions[rand() % directions.size()];

			switch (pickedDirection)
			{
			case 0: //up
				enemies[i].position.second--;
				break;
			case 1: //right
				enemies[i].position.first++;
				break;
			case 2: //down
				enemies[i].position.second++;
				break;
			case 3: //left
				enemies[i].position.first--;
				break;
			}
		}
		break;
	case 3: //Uses BFS
		for (int i = 0; i < 4; i++)
		{
			pair<int, int> newPos = NextStep({ enemies[i].position.first, enemies[i].position.second });
			enemies[i].position = newPos;
		}
		break;
	}
}

pair<int, int> Game::NextStep(pair<int, int> enemyPosition) {

	if (enemyPosition == pacman.position) return enemyPosition;

	int visited[height][width] = { 0 };
	vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, make_pair(-1, -1)));
	queue<pair<int, int>> q;

	q.push(enemyPosition);
	visited[enemyPosition.second][enemyPosition.first] = 1;

	while (!q.empty()) {
		pair<int, int> current = q.front();
		q.pop();

		if (current == pacman.position) {

			while (parent[current.first][current.second] != enemyPosition) { //reconstruct path
				current = parent[current.first][current.second];
			}
			return current; //return next step only
		}

		for (auto direction : directions) {
			int x = current.first + direction.first;
			int y = current.second + direction.second;

			if (gameBoard[y][x] != '#' && visited[x][y] == 0) {
				q.push({ x , y });
				visited[x][y] = 1;
				parent[x][y] = current;
			}
		}
	}
	return { 1,1 };
}

void Game::Menu() {
	input = 0;
	while (input < 1 || input > 3) {
		system("cls");
		std::cout << "Pacman!\n" << endl << "1. New Game" << endl << "2. Continue" << endl << "3. Exit" << endl << "\nSelection: ";
		std::cin >> input;
		if (cin.fail()) {
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
	}

	system("cls");



	switch(input) {
	case 1:
		std::cout << "Enter Username: ";  
		std::cin >> currentUser;
		if (saves.find(currentUser) != saves.end()) {
			std::cout << "User Already Exists. Continue Game.";
			std::cin.ignore(255, '\n');
			std::cin.get();
			Menu();
			return;
			break;
		}
		saves[currentUser] = new Save(currentUser);
		level = 0;
		while (level < 1 || level > levels.size()) {
			system("cls");
			std::cout << "Select Map\n\n";
			for (int i = 1; i <= levels.size(); i++) std::cout << levels[i] << endl;
			std::cout << "\nInput: ";
			std::cin >> level;
		}
		difficulty = 0;
		while (difficulty < 1 || difficulty > 3) {
			system("cls");
			std::cout << "Select Difficulty\n\n1. Easy\n2. Medium\n3. Hard\n\nInput: ";
			std::cin >> difficulty;
			if (cin.fail()) {
				std::cin.clear();
				std::cin.ignore(255, '\n');
			}
		}
		break;
	case 2:

		std::cout << "Enter Username: "; std::cin >> currentUser;

		// If user not found
		if (saves.find(currentUser) == saves.end()) 
		{
			std::cout << "User Does Not Exist. Start New Game.";
			std::cin.ignore(255);
			std::cin.get();
			Menu();
			return;
		}

		// If user found
		input = 0;
		while (input != 1 && input != 2) {
			system("cls");
			std::cout << "1. Play\n2. See Scores\n\nInput: ";
			std::cin >> input;
			if (cin.fail()) {
				std::cin.clear();
				std::cin.ignore(255, '\n');
			}
		}

		switch (input) {
		case 1:
			level = 0;
			while (level < 1 || level > levels.size()) {
				system("cls");
				std::cout << "Select Map\n\n";
				for (int i = 1; i <= levels.size(); i++) std::cout << levels[i] << endl;
				std::cout << "\nInput: ";
				std::cin >> level;
				if (cin.fail()) {
					std::cin.clear();
					std::cin.ignore(255, '\n');
				}
			}

			difficulty = 0;
			while (difficulty < 1 || difficulty > 3) {
				system("cls");
				std::cout << "Select Difficulty\n\n1. Easy\n2. Medium\n3. Hard\n\nInput: ";
				std::cin >> difficulty;
				if (cin.fail()) {
					std::cin.clear();
					std::cin.ignore(255, '\n');
				}
			}
			break;
		case 2:
			level = 0;
			while (level < 1 || level > levels.size()) {
				system("cls");
				std::cout << "Select Map\n\n";
				for (int i = 1; i <= levels.size(); i++) std::cout << levels[i] << endl;
				std::cout << "\nInput: ";
				std::cin >> level;
						if (cin.fail()) {
			std::cin.clear();
			std::cin.ignore(255, '\n');
		}
			}

			system("cls");
			priority_queue<int, std::vector<int>, std::less<int>> copyScores = saves[currentUser]->highScores[level];

			if (copyScores.empty()) std::cout << "No Scores";
			else {
				std::cout << "Highscores For Map " << level << endl;
				for (int i = 1; i < 4; i++)
				{
					if (!copyScores.empty()) {
						std::cout << i << ". " << copyScores.top() << endl;
						copyScores.pop();
					}
					else break;
				}
			}
			std::cin.ignore();
			std::cin.get();
			Menu();
			return;
			break;
		}

		break;
	case 3:
		ExitGame();
		return;
		break;
	default:
		break;

	}

	Initialize();
}

void Game::Initialize() {

	switch (level) {
	case 1:
		CopyMap(map1, gameBoard);
		break;
	case 2:
		CopyMap(map2, gameBoard);
		break;
	case 3:
		CopyMap(map3, gameBoard);
		break;
	}

	enemyCooldown = false;
	easyCooldown = false;
	score = 10000;
	gameOver = false;
	win = false;

	leftKeyPressed = false;
	rightKeyPressed = false;
	upKeyPressed = false;
	downKeyPressed = false;

	//Start enemies in corners
	enemies[0].position = { 1, 1 };
	enemies[1].position = { 18, 1 };
	enemies[2].position = { 1, 17 };
	enemies[3].position = { 18, 17 };
	pacman.position = pacman.oldPosition = { 8,1 };

	for (int i = 0; i < 4; i++)
	{
		enemies[i].oldPosition = enemies[i].position;
		enemies[i].old = '.';
	}


	while (!gameOver && !win)
	{
		Draw();
		Input();
		Update();
		Sleep(333);
	}
	
	saves[currentUser]->highScores[level].push(score); // add score  to save

	system("cls");

	if (win) {
		cout << "You Won!\n\nFinal Score: " << score;
	}
	else {
		cout << "You Lost :(\n\nFinal Score: " << score;
	}

	std::cin.ignore();
	std::cin.get();
	Menu();
}

void Game::Draw() {
	// Using windows console API instead to get rid of flickering and hide cursor
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Hide cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	// Move cursor to top-left corner
	COORD topLeft = { 0, 0 };
	SetConsoleCursorPosition(hConsole, topLeft);

	// system("cls");

	// Draw map
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (EnemyInPosition(x, y)) {
				std::cout << 'M' <<  ' ';
			}
			else if ((y == pacman.position.second) && (x == pacman.position.first)) {
				std::cout << 'C' << ' ';
			}
			else {
				std::cout << gameBoard[y][x] << ' ';
			}
		}
		std::cout << endl;
	}

	// Print score
	std::cout << "Score: " << score << endl;
}

void Game::Input() {
	//Changed to using flags to avoid diagonal movement
	// TODO: make sure movement only occurs if it is a valid movement
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && gameBoard[pacman.position.second][pacman.position.first - 1] != '#') { // Check if left arrow key is pressed
		leftKeyPressed = true;
		rightKeyPressed = false;
		upKeyPressed = false;
		downKeyPressed = false;
	}
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && gameBoard[pacman.position.second][pacman.position.first + 1] != '#') { // Check if right arrow key is pressed
		leftKeyPressed = false;
		rightKeyPressed = true;
		upKeyPressed = false;
		downKeyPressed = false;
	}
	else if ((GetAsyncKeyState(VK_UP) & 0x8000) && gameBoard[pacman.position.second - 1][pacman.position.first] != '#') { // Check if up arrow key is pressed
		leftKeyPressed = false;
		rightKeyPressed = false;
		upKeyPressed = true;
		downKeyPressed = false;
	}
	else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && gameBoard[pacman.position.second + 1][pacman.position.first] != '#') { // Check if down arrow key is pressed
		leftKeyPressed = false;
		rightKeyPressed = false;
		upKeyPressed = false;
		downKeyPressed = true;
	}

	int pacmanX = pacman.position.first;
	int pacmanY = pacman.position.second;

	// Move Pacman based on pressed key
	try {
		if (leftKeyPressed && gameBoard[pacmanY][pacmanX - 1] != '#') {
			pacman.position.first--;
		}
		else if (rightKeyPressed && gameBoard[pacmanY][pacmanX + 1] != '#') {
			pacman.position.first++;
		}
		else if (upKeyPressed && gameBoard[pacmanY - 1][pacmanX] != '#') {
			pacman.position.second--;
		}
		else if (downKeyPressed && gameBoard[pacmanY + 1][pacmanX] != '#') {
			pacman.position.second++;
		}
		else {
			leftKeyPressed = false;
			rightKeyPressed = false;
			upKeyPressed = false;
			downKeyPressed = false;
		}
	}
	catch (...) {
		return;
	}
}

void Game::Update(){
	bool foundDot = false;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) 
		{
			if (gameBoard[y][x] == '.') foundDot = true;
		}
	}

	if (!foundDot) {
		win = true;
		score *= difficulty;
		return;
	}
	//Enemies on difficulty 1 move at half speed
	if (!enemyCooldown) {
		if (difficulty == 1) {
			if (!easyCooldown) {
				CalcEnemyMovement();
				easyCooldown = true;
				enemyCooldown = true;
			}
			else {
				easyCooldown = false;
			}
		}
		else {
			CalcEnemyMovement();
			enemyCooldown = true;
		}
	}
	else {
		enemyCooldown = false;
	}

	for (int i = 0; i < 4; i++) {
		if (pacman.position == enemies[i].position || pacman.position == enemies[i].oldPosition)
		{
			gameOver = true;
			score /= 5;
		}
	}

	if (pacman.position != pacman.oldPosition && gameBoard[pacman.position.second][pacman.position.first] == '.') //If pacman moved onto a dot
	{
		score += 25;
	}

	score -= 5;

	gameBoard[pacman.oldPosition.second][pacman.oldPosition.first] = ' '; // Change old pacman position to blank

	//gameBoard[pacman.position.second][pacman.position.first] = 'C';

	pacman.oldPosition = pacman.position;

for (int i = 0; i < 4; i++)
	{
		if (enemies[i].old == 'C') gameBoard[enemies[i].oldPosition.second][enemies[i].oldPosition.first] = ' ';
		else gameBoard[enemies[i].oldPosition.second][enemies[i].oldPosition.first] = enemies[i].old; //Restore char in old position
		enemies[i].old = gameBoard[enemies[i].position.second][enemies[i].position.first]; //Set old to the next step
		//gameBoard[enemies[i].position.second][enemies[i].position.first] = 'M'; //Set next step to M
		enemies[i].oldPosition = enemies[i].position; //Update old position
	}
}

void Game::CopyMap(char source[height][width], char dest[height][width]) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dest[i][j] = source[i][j];
		}
	}
}

void Game::ExitGame() {
	system("cls");
	std::cout << "Exitting...\n";
	std::string saveString;


	for (auto save : saves) {
		saveString += save.second->ToString() + "\n";
	}
	saveString.pop_back();
	std::ofstream output("saves.txt");

	if (output.is_open()) {
		output << saveString;
		output.close();
		cout << "Saved Successfully";
	}
	else {
		cout << "Error Saving!";
		output.close();
	}
}

void Game::LoadFromFile() {
	string readString;
	string fileLine;
	std::ifstream input("saves.txt");

	if (!input.is_open()) {
		cout << "Error Reading File";
		return;
	}

	while (std::getline(input, fileLine)) {
		readString += fileLine;
		readString += '\n';
	}

	std::queue<std::string> strings;
	strings.push("");
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	while ((pos = readString.find("\n", prev)) != std::string::npos)
	{
		strings.push(readString.substr(prev, pos - prev));
		prev = pos + 1;
	}

	std::vector<std::string> line;
	string username;
	unordered_map<int, priority_queue<int, std::vector<int>, std::less<int>>> highScores;
	string currentString;
	Save* save;
	int level;
	bool first = true;


	while (!strings.empty()) {
		if (strings.front() == "") {
			strings.pop();
			if (!strings.empty() && !first)
			{
				save = new Save(username);
				save->highScores = highScores;
				saves[username] = save;
			}
			username = strings.front();
			strings.pop();
			highScores.clear();
		}
		else { // [levelnum]: score1 score2 ..... scoren
			currentString = strings.front();
			pos = 0;
			prev = 0;
			line.clear();

			while ((pos = currentString.find(" ", prev)) != std::string::npos)
			{
				line.push_back(currentString.substr(prev, pos - prev));
				prev = pos + 1;
			} //split level line using " " as delimiter

			level = std::stoi(line[0]);

			for (auto it = line.begin() + 1; it != line.end(); it++) {
				highScores[level].push(std::stoi(*it));
			}

			strings.pop();
			first = false;
		}
	}
	save = new Save(username);
	save->highScores = highScores;
	saves[username] = save;
}

bool Game::EnemyInPosition(int x, int y) {
	for (int i = 0; i < 4; i++)
	{
		if ((x == enemies[i].position.first) && (y == enemies[i].position.second)) {
			return true;
		}
	}
	return false;
}

Save::Save(string username) {
	this->userName = username;
}

std::string Save::ToString() {
	std::string result;

	// Convert userName to string
	result += userName + "\n";

	// Convert highScores to string
	for (auto pair : highScores) {
		result += std::to_string(pair.first) + " ";
		auto scores = pair.second;
		while (!scores.empty()) {
			result += std::to_string(scores.top()) + " ";
			scores.pop();
		}
		result += "\n";
	}

	return result;
}

