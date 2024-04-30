#include "Game.h"
#include <iostream>
#include <vector>


void Game::CalcEnemyMovement() {
	std::vector<int> directions; //0 up, 1 right, 2 down, 3 left 
	int enemy_x;
	int enemy_y;

	switch (difficulty)
	{
	case 0:
	case 1:
		for (size_t i = 0; i < 4; i++)
		{
			directions.clear();
			enemy_x = enemies[i].x_coordinate;
			enemy_y = enemies[i].y_coordinate;

			if (gameBoard[enemy_y + 1] != "#") directions.push_back(0);
			if (gameBoard[enemy_y - 1] != "#") directions.push_back(2);
			if (gameBoard[enemy_x + 1] != "#") directions.push_back(1);
			if (gameBoard[enemy_x - 1] != "#") directions.push_back(3);

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
	case 2: //imprelemnt BFS

		break;
	}
}