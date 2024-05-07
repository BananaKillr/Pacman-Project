#include "Game.h"
#include <iostream>
#include <vector>
#include <queue>


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
			pair<int, int> next = nextStep(enemies[i].position, pacman.position);
			enemies[i].position = next;
		}
		break;
	}
}

pair<int, int> Game::nextStep(pair<int, int> pacmanPosition, pair<int, int> enemyPosition) {

	int visited[height][width] = { 0 };
	vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, make_pair(-1, -1)));
	queue<pair<int, int>> q;

	q.push(enemyPosition);
	visited[enemyPosition.second][enemyPosition.first] = 1;

	while (!q.empty()) {
		pair<int, int> current = q.front();
		q.pop();

		if (current == pacmanPosition) {

			while (parent[current.first][current.second] != enemyPosition) { //reconstruct path
				current = parent[current.first][current.second];
			}
			return current; //return next step only
		}

		for (auto direction : directions) {
			int x = current.first + direction.first;
			int y = current.second + direction.second;

			if (gameBoard[x][y] != '#' && visited[x][y] == 0) {
				q.push({ x , y });
				visited[x][y] = 1;
				parent[x][y] = current;
			}
		}
	}
}

