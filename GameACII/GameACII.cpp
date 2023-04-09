// GameACII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include "GameIncludes.h"




int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "GameACII", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Main game loop
    while (!glfwWindowShouldClose(window)) {
        // TODO: Update game logic and render here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

    ////////////////////////////////////////////////////////////////////////////////////////////////

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

    bool lineOfSightEnabled = true;
    bool displayUIFlag = false;
    bool exitReached = false;
    bool enterDungeon = false;
    while (true) {
        if (!displayUIFlag) {
            draw(map, playerX, playerY, visibilityRadius, inTown, player, lineOfSightEnabled);
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
        else if (GetAsyncKeyState('I') & 0x8000) {
            lineOfSightEnabled = !lineOfSightEnabled;
            Sleep(200); // Add a small delay to prevent the UI from flickering
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
                loadNewMap(map, playerX, playerY, dungeonWidth, dungeonHeight);
                enterDungeon = false;
            }
            else if (exitReached) {
                loadNewMap(map, playerX, playerY, dungeonWidth, dungeonHeight);
                exitReached = false;
            }
        }
    }
    return 0;
}