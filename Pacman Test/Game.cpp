#include "Game.h"
#include <iostream>
#include <vector>
#include <queue>
#include <Windows.h>
using namespace std;

Game::Game() {
	saves["banana"] = new Save("banana");
	saves["banana"]->highScores[2].push(8000);
	saves["banana"]->highScores[2].push(5000);

	levels[1] = "1. Map 1";
	levels[2] = "2. Map 2";
	levels[3] = "3. Map 3";
	Menu();
};

void Game::CalcEnemyMovement() {


	switch (difficulty)
	{
	case 0: //Uses random movement
	case 1:
		for (int i = 0; i < 4; i++)
		{
			std::vector<int> directions; //0 up, 1 right, 2 down, 3 left 
			int enemy_x;
			int enemy_y;

			directions.clear();
			enemy_x = enemies[i].position.first;
			enemy_y = enemies[i].position.second;

			if (gameBoard[enemy_y + 1][enemy_x] != '#') directions.push_back(0);
			if (gameBoard[enemy_y - 1][enemy_x] != '#') directions.push_back(2);
			if (gameBoard[enemy_y][enemy_x + 1] != '#') directions.push_back(1);
			if (gameBoard[enemy_y][enemy_x - 1] != '#') directions.push_back(3);

			int pickedDirection = rand() % directions.size();

			switch (pickedDirection)
			{
			case 0: //up
				enemies[i].position.first--;
				break;
			case 1: //right
				enemies[i].position.second--;
				break;
			case 2: //down
				enemies[i].position.first++;
				break;
			default: //left
				enemies[i].position.second++;
				break;
			}
		}
		break;
	case 2: //Uses BFS
		for (int i = 0; i < 4; i++)
		{
			enemies[i].position = NextStep(enemies[i].position);
		}
		break;
	}
}

pair<int, int> Game::NextStep(pair<int, int> enemyPosition) {

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
}

void Game::Menu() {
	input = 0;
	while (input < 1 || input > 3) {
		system("cls");
		cout << "Pacman!\n" << endl << "1. New Game" << endl << "2. Continue" << endl << "3. Exit" << endl << "\nSelection: ";
		cin >> input;
	}

	system("cls");



	switch(input) {
	case 1:
		cout << "Enter Username: ";  
		cin >> currentUser;
		if (saves.find(currentUser) != saves.end()) {
			cout << "User Already Exists. Continue Game.";
			Sleep(2000);
			Menu();
			return;
			break;
		}
		saves[currentUser] = new Save(currentUser);
		level = 0;
		while (level < 1 || level > levels.size()) {
			system("cls");
			cout << "Select Map\n\n";
			for (int i = 1; i <= levels.size(); i++) cout << levels[i] << endl;
			cout << "\nInput: ";
			cin >> level;
		}
		difficulty = 0;
		while (difficulty < 1 || difficulty > 3) {
			system("cls");
			cout << "Select Difficulty\n\n1. Easy\n2. Medium\n3. Hard\n\nInput: ";
			std::cin >> difficulty;
		}
		break;
	case 2:

		cout << "Enter Username: "; cin >> currentUser;

		// If user not found
		if (saves.find(currentUser) == saves.end()) 
		{
			cout << "User Does Not Exist. Start New Game.";
			Sleep(2000);
			Menu();
			return;
		}

		// If user found
		input = 0;
		while (input != 1 && input != 2) {
			system("cls");
			cout << "1. Play\n2. See Scores\n\nInput: ";
			cin >> input;
		}

		switch (input) {
		case 1:
			level = 0;
			while (level < 1 || level > levels.size()) {
				system("cls");
				cout << "Select Map\n\n";
				for (int i = 1; i <= levels.size(); i++) cout << levels[i] << endl;
				cout << "\nInput: ";
				cin >> level;
			}

			difficulty = 0;
			while (difficulty < 1 || difficulty > 3) {
				system("cls");
				cout << "Select Difficulty\n\n1. Easy\n2. Medium\n3. Hard\n\nInput: ";
				std::cin >> difficulty;
			}
			break;
		case 2:
			level = 0;
			while (level < 1 || level > levels.size()) {
				system("cls");
				cout << "Select Map\n\n";
				for (int i = 1; i <= levels.size(); i++) cout << levels[i] << endl;
				cout << "\nInput: ";
				cin >> level;
			}

			system("cls");
			priority_queue<int, std::vector<int>, std::less<int>> copyScores = saves[currentUser]->highScores[level];

			if (copyScores.empty()) cout << "No Scores";
			else {
				cout << "Highscores For Map " << level << endl;
				for (int i = 1; i < 4; i++)
				{
					if (!copyScores.empty()) {
						cout << i << ". " << copyScores.top() << endl;
						copyScores.pop();
					}
					else break;
				}
			}
			cin.ignore();
			cin.get();
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
	system("cls");

	switch (level) {
	case 1:
		CopyMap(map1, gameMap);
		break;
	case 2:
		CopyMap(map2, gameMap);
		break;
	case 3:
		CopyMap(map3, gameMap);
		break;
	}


}

void Game::CopyMap(const char source[][height], char dest[][height]) {
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < width; ++j) {
			dest[i][j] = source[i][j];
		}
	}
}

void Game::ExitGame() {
	system("cls");
	cout << "Exitting...";
}

Save::Save(string username) {
	this->userName = username;
}