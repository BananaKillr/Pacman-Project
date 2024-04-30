#include "Game.h"
#include <iostream>
#include <vector>
#include <queue>


void Game::CalcEnemyMovement() {


	switch (difficulty)
	{
	case 0:
	case 1:
		for (int i = 0; i < 4; i++)
		{
			std::vector<int> directions; //0 up, 1 right, 2 down, 3 left 
			int enemy_x;
			int enemy_y;

			directions.clear();
			enemy_x = enemies[i].x_coordinate;
			enemy_y = enemies[i].y_coordinate;

			if (gameBoard[enemy_y + 1][enemy_x] != '#') directions.push_back(0);
			if (gameBoard[enemy_y - 1][enemy_x] != '#') directions.push_back(2);
			if (gameBoard[enemy_y][enemy_x + 1] != '#') directions.push_back(1);
			if (gameBoard[enemy_y][enemy_x - 1] != '#') directions.push_back(3);

			int pickedDirection = rand() % directions.size();

			switch (pickedDirection)
			{
			case 0: //up
				enemies[i].y_coordinate++;
				break;
			case 1: //right
				enemies[i].x_coordinate++;
				break;
			case 2: //down
				enemies[i].y_coordinate--;
				break;
			default: //left
				enemies[i].x_coordinate--;
				break;
			}
		}
		break;
	case 2: //implelemnt BFS



		for (int i = 0; i < 4; i++)
		{
			int visited[height][width] = { 0 };
			std::queue<int> x_queue, y_queue;
			std::vector<int> path_x, path_y;

			int enemy_x = enemies[i].x_coordinate;
			int enemy_y = enemies[i].y_coordinate;

			x_queue.push(enemy_x);
			y_queue.push(enemy_y);

			while (!x_queue.empty())
			{
				//Set current node to front of queue, then remove current note from queue
				enemy_x = x_queue.front();
				enemy_y = y_queue.front();
				x_queue.pop();
				y_queue.pop();

				//Check if char found
				if (gameBoard[enemy_y][enemy_x] == pacman.entityChar)
				{
					break;
				}

				//Checks neighbors, adds to queues if valid movement
				if (gameBoard[enemy_y + 1][enemy_x] != '#' && visited[enemy_y + 1][enemy_x] == 0)
				{
					y_queue.push(enemy_y + 1);
					x_queue.push(enemy_x);
					visited[enemy_y][enemy_x] = 1;
				}
				if (gameBoard[enemy_y - 1][enemy_x] != '#' && visited[enemy_y - 1][enemy_x] == 0)
				{
					y_queue.push(enemy_y - 1);
					x_queue.push(enemy_x);
					visited[enemy_y][enemy_x] = 1;
				}
				if (gameBoard[enemy_y][enemy_x + 1] != '#' && visited[enemy_y][enemy_x + 1] == 0) {
					y_queue.push(enemy_y);
					x_queue.push(enemy_x + 1);
					visited[enemy_y][enemy_x] = 1;
				}
				if (gameBoard[enemy_y][enemy_x - 1] != '#' && visited[enemy_y][enemy_x - 1] == 0)
				{
					y_queue.push(enemy_y);
					x_queue.push(enemy_x - 1);
					visited[enemy_y][enemy_x] = 1;
				}
			}
		}
		break;
	}
}