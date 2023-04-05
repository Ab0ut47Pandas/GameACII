// GameACII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include "GameIncludes.h"


const int mapWidth = 100;
const int mapHeight = 100;
const char playerSymbol = '@';


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

void displayUI(Player& player) {
    // Clear the screen
    system("cls");

    // Display player stats
    std::cout << "Player Stats:\n";
    std::cout << "Health: " << player.getHealth() << "\n";
    std::cout << "Experience: " << player.getExperience() << "\n";
    std::cout << "Level: " << player.getLevel() << "\n";

    // Display UI options
    std::cout << "\nOptions:\n";
    std::cout << "1. Use a health potion\n";
    std::cout << "2. View inventory\n";
    std::cout << "3. Save game\n";
    std::cout << "4. Exit\n";

    // Get user input
    int choice;
    std::cin >> choice;

    // Process user input
    switch (choice) {
    case 1:
        // Use a health potion
        player.usePotion("health");
        break;
    case 2:
        // View inventory
        player.viewInventory();
        break;
    case 3:
        // Save game
        saveGame(player);
        break;
    case 4:
        // Exit
        exit(0);
    }
}

int main() {
    hideCursor();
    TitleScreen titleScreen;

    int choice = titleScreen.menu();

    if (choice == 2) { // Exit if the choice is "Exit"
        return 0;
    }
    system("cls");
    Player player;

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
    bool displayUIFlag = false;
    bool exitReached = false;
    bool enterDungeon = false;
    while (true) {
        if (!displayUIFlag) {
            draw(map, playerX, playerY, visibilityRadius, inTown, player);
        }

        int newX = playerX, newY = playerY;
        bool keyPressed = false;

        // Check arrow keys and U key state
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            newY--;
            keyPressed = true;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            newY++;
            keyPressed = true;
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            newX--;
            keyPressed = true;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            newX++;
            keyPressed = true;
        }
        else if (GetAsyncKeyState('U') & 0x8000) {
            displayUI(player);
            displayUIFlag = true;
            Sleep(200); // Add a small delay to prevent the UI from flickering
        }
        else {
            displayUIFlag = false;
            Sleep(10); // Add a small delay to reduce CPU usage
        }

        if (keyPressed) {
            Sleep(150); // Add a delay after detecting arrow key input to increase movement precision
        }

        if (isPassable(map, newX, newY, exitReached, enterDungeon)) {
            map[playerY][playerX] = '.';
            playerX = newX;
            playerY = newY;
            map[playerY][playerX] = playerSymbol;

            if (inTown && enterDungeon) {
                inTown = false;
                //Dungeon dungeon;
                //dungeon.loadNewMap(map, playerX, playerY);
                loadNewMap(map, playerX, playerY);
                enterDungeon = false;
            }
            else if (exitReached) {
                //Dungeon dungeon;
                //dungeon.loadNewMap(map, playerX, playerY);
                loadNewMap(map, playerX, playerY);
                exitReached = false;
            }
        }
    }
    return 0;
}