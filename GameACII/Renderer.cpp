#include "Renderer.h"
#include <iostream>
#include "ConsoleUtils.h"
#include "lineOfSight.h"

void draw(const std::vector<std::string>& map, int playerX, int playerY, int visibilityRadius, bool inTown, Player& player) {
    //system("cls");



    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);

    int mapHeight = static_cast<int>(map.size());
    int mapWidth = static_cast<int>(map[0].length());

    int paddingTop = (consoleHeight - mapHeight) / 2;
    int paddingLeft = (consoleWidth - mapWidth) / 2;

    //Draw map
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
    setCursorPosition(0, 0);
    std::cout << "Player Stats:\n";
    std::cout << "Health: " << player.getHealth() << "\n";
    std::cout << "Experience: " << player.getExperience() << "\n";
    std::cout << "Level: " << player.getLevel() << "\n";
    std::cout << "\n";
    //system("cls");
}