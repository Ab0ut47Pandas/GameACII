// GameACII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include "ConsoleUtils.h"
#include "MapGenerator.h"
#include "TitleScreen.h"

const int mapWidth = 50;
const int mapHeight = 25;
const char playerSymbol = '@';

bool lineOfSight(int x1, int y1, int x2, int y2, std::vector<std::string>& map) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    bool exitVisible = false;

    while (true) {
        if (x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }

        if (map[y1][x1] == '#') {
            break;
        }

        if (map[y1][x1] == 'X') {
            exitVisible = true;
        }

        map[y1][x1] = '*'; // You can use any symbol to represent visible cells
    }

    return exitVisible;
}

float distance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

void draw(const std::vector<std::string>& map, int playerX, int playerY, int visibilityRadius) {
    system("cls");

    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);

    int mapHeight = static_cast<int>(map.size());
    int mapWidth = static_cast<int>(map[0].length());

    int paddingTop = (consoleHeight - mapHeight) / 2;
    int paddingLeft = (consoleWidth - mapWidth) / 2;

    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            setCursorPosition(paddingLeft + j, paddingTop + i);
            if (map[i][j] == '*') {
                std::cout << map[i][j];
            }
            else if (i == playerY && j == playerX) {
                std::cout << playerSymbol;
            }
            else {
                std::cout << ' ';
            }
        }
    }
}

void loadNewMap(std::vector<std::string>& map, int& playerX, int& playerY) {
    map = MapGenerator::generateMap(mapWidth, mapHeight);

    // Find the entrance for the player
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (map[i][j] == 'E') {
                playerX = j;
                playerY = i;
                break;
            }
        }
    }
}

bool isPassable(const std::vector<std::string>& map, int x, int y, bool& exitReached) {
    if (map[y][x] == 'X') {
        exitReached = true;
        return true;
    }
    return (map[y][x] == '.' || map[y][x] == playerSymbol);
}

int main() {
    TitleScreen titleScreen;

    titleScreen.display();
    int choice = titleScreen.menu();

    if (choice == 2) { // Exit if the choice is "Exit"
        return 0;
    }

    int playerX = 0, playerY = 0;
    int exitX = 0, exitY = 0; // Add exit coordinates
    int visibilityRadius = 1000; // Set the desired visibility radius.

    auto map = MapGenerator::generateMap(mapWidth, mapHeight);

    // Find an open space near the entrance for the player
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (map[i][j] == 'E') {
                playerX = j;
                playerY = i;
            }
            else if (map[i][j] == 'X') {
                exitX = j;
                exitY = i;
            }
        }
    }

    bool exitReached = false;

    
    while (true) {

        draw(map, playerX, playerY, visibilityRadius);
        char input = _getch();
        int newX = playerX, newY = playerY;
        if (input == 'r' || input == 'R') {
            map = MapGenerator::generateMap(mapWidth, mapHeight);
            // Find the entrance for the player
            for (int i = 0; i < mapHeight; ++i) {
                for (int j = 0; j < mapWidth; ++j) {
                    if (map[i][j] == 'E') {
                        playerX = j;
                        playerY = i;
                        break;
                    }
                }
            }
            continue;
        }

        // Clear the visible cells from the previous frame
        for (int i = 0; i < mapHeight; ++i) {
            for (int j = 0; j < mapWidth; ++j) {
                if (map[i][j] == '*') {
                    map[i][j] = '.';
                }
            }
        }
        // Calculate 360-degree visibility
        for (int i = 0; i < mapHeight; ++i) {
            for (int j = 0; j < mapWidth; ++j) {
                if (distance(playerX, playerY, j, i) <= visibilityRadius) {
                    lineOfSight(playerX, playerY, j, i, map);
                }
            }
        }

        lineOfSight(playerX, playerY, exitX, exitY, map);

        switch (input) {
        case 72: // Up
            newY--;
            break;
        case 80: // Down
            newY++;
            break;
        case 75: // Left
            newX--;
            break;
        case 77: // Right
            newX++;
            break;
        default:
            continue;
        }

        //Call LOS after player input 


        if (isPassable(map, newX, newY, exitReached)) {
            map[playerY][playerX] = '.';
            playerX = newX;
            playerY = newY;
            map[playerY][playerX] = playerSymbol;

            //LOS function
            exitReached = lineOfSight(playerX, playerY, exitX, exitY, map);

            if (exitReached) {
                loadNewMap(map, playerX, playerY);
                exitReached = false;
            }
        }

    }
    return 0;
}





