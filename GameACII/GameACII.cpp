﻿// GameACII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include "ConsoleUtils.h"
#include "Town.h"
#include "TitleScreen.h"
#include "Dungeon.h"
#include "LineOfSight.h"


const int mapWidth = 50;
const int mapHeight = 25;
const char playerSymbol = '@';

void draw(const std::vector<std::string>& map, int playerX, int playerY, int visibilityRadius, bool inTown) {
    system("cls");

    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);

    int mapHeight = static_cast<int>(map.size());
    int mapWidth = static_cast<int>(map[0].length());

    int paddingTop = (consoleHeight - mapHeight) / 2;
    int paddingLeft = (consoleWidth - mapWidth) / 2;

    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            int distance = (playerX - j) * (playerX - j) + (playerY - i) * (playerY - i);
            setCursorPosition(paddingLeft + j, paddingTop + i);
            if (inTown || distance <= visibilityRadius * visibilityRadius && LineOfSight::hasLineOfSight(playerX, playerY, j, i, map)) {
                std::cout << map[i][j];
            }
            else {
                std::cout << ' ';
            }
        }
    }
}

void loadNewMap(std::vector<std::string>& map, int& playerX, int& playerY) {
    map = Dungeon::generate(mapWidth, mapHeight);

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

bool isPassable(const std::vector<std::string>& map, int x, int y, bool& exitReached, bool& enterDungeon) {
    if (map[y][x] == 'X') {
        exitReached = true;
        return true;
    }

    if (map[y][x] == 'D') {
        enterDungeon = true;
        return true;
    }
    return (map[y][x] == '.' || map[y][x] == playerSymbol);
}

int main() {
    TitleScreen titleScreen;

    int choice = titleScreen.menu();

    if (choice == 2) { // Exit if the choice is "Exit"
        return 0;
    }

    int playerX = 0, playerY = 0;
    int visibilityRadius = 10; // Set the desired visibility radius.

    bool inTown = true;
    int townWidth = 20, townHeight = 10;
    std::vector<std::string> town = generateTown(townWidth, townHeight);

    auto map = town; // Set the initial map to town

    // Find the player's starting position in the town
    for (int i = 0; i < townHeight; ++i) {
        for (int j = 0; j < townWidth; ++j) {
            if (town[i][j] == '.') {
                playerX = j;
                playerY = i;
                break;
            }
        }
    }

    bool exitReached = false;
    bool enterDungeon = false;
    while (true) {
        draw(map, playerX, playerY, visibilityRadius, inTown);
        char input = _getch();
        int newX = playerX, newY = playerY;
        if (input == 'r' || input == 'R') {
            map = Dungeon::generate(mapWidth, mapHeight);
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

        if (isPassable(map, newX, newY, exitReached, enterDungeon)) {
            map[playerY][playerX] = '.';
            playerX = newX;
            playerY = newY;
            map[playerY][playerX] = playerSymbol;

            if (inTown && enterDungeon) {
                inTown = false;
                loadNewMap(map, playerX, playerY);
                enterDungeon = false;
            }
            else if (exitReached) {
                loadNewMap(map, playerX, playerY);
                exitReached = false;
            }
        }
    }
    return 0;
}