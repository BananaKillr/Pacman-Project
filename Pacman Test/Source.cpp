#include <iostream>
#include <windows.h>
#include "Game.h"

using namespace std;

const int width = 20;
const int height = 20;

int pacmanX, pacmanY, score;
int oldPacmanX, oldPacmanY;
bool gameOver; //used in main loop to know when to end loop
bool win; //used to check if win/loss and draw next menu
char map[height][width];

bool leftKeyPressed;
bool rightKeyPressed;
bool upKeyPressed;
bool downKeyPressed;

void Initialize() {
    score = 0;
    gameOver = false;
    pacmanX = 5;
    pacmanY = 5;
    oldPacmanX = pacmanX;
    oldPacmanY = pacmanY;

    leftKeyPressed = false;
    rightKeyPressed = false;
    upKeyPressed = false;
    downKeyPressed = false;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == pacmanX && y == pacmanY)
                map[y][x] = 'C';
            else
                map[y][x] = '.';
        }
    }
}

void Draw() {
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
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << map[y][x] << ' ';
        }
        std::cout << endl;
    }

    // Print score
    std::cout << "Score: " << score << endl;
}

void Input() {
    //Changed to using flags to avoid diagonal movement
    // TODO: implement collision detection
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Check if left arrow key is pressed
        leftKeyPressed = true;
        rightKeyPressed = false;
        upKeyPressed = false;
        downKeyPressed = false;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Check if right arrow key is pressed
        leftKeyPressed = false;
        rightKeyPressed = true;
        upKeyPressed = false;
        downKeyPressed = false;
    }
    else if (GetAsyncKeyState(VK_UP) & 0x8000) { // Check if up arrow key is pressed
        leftKeyPressed = false;
        rightKeyPressed = false;
        upKeyPressed = true;    
        downKeyPressed = false;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Check if down arrow key is pressed
        leftKeyPressed = false;
        rightKeyPressed = false;
        upKeyPressed = false;
        downKeyPressed = true;
    }

    // Move Pacman based on pressed key
    if (leftKeyPressed) {
        pacmanX--;
    }
    else if (rightKeyPressed) {
        pacmanX++;
    }
    else if (upKeyPressed) {
        pacmanY--;
    }
    else if (downKeyPressed) {
        pacmanY++;
    }
}

void Update() {
    // Check game over conditions
    if (pacmanX < 0 || pacmanX >= width || pacmanY < 0 || pacmanY >= height)
        gameOver = true;

    // Clear old position of Pacman
    map[oldPacmanY][oldPacmanX] = ' ';

    // Check if Pacman moved onto a dot
    if (map[pacmanY][pacmanX] == '.' && (oldPacmanX != pacmanX || oldPacmanY != pacmanY)) {
        score++;
    }

    // Update new position of Pacman
    map[pacmanY][pacmanX] = 'C';


    // Update old position
    oldPacmanX = pacmanX;
    oldPacmanY = pacmanY;
}

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <sstream>



class Vave {
public:
    std::string userName;
    std::unordered_map<int, std::priority_queue<int, std::vector<int>, std::less<int>>> highScores;

    Vave(string username) {
        userName = username;
    }

    std::string ToString() {
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
};

std::unordered_map<std::string, Vave*> saves;

void LoadFromFile(string readString) {
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
    int level;
    

    while(!strings.empty()) {
        if (strings.front() == "") {
            strings.pop();
            if (strings.empty()) {
                //TODO create Save object and add to hashmap
                break;
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
        }
    }
}



int main() {
    Game* game = new Game();

    return 0;
}