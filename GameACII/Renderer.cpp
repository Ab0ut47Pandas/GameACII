#include "Renderer.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#include "ConsoleUtils.h"
#include "lineOfSight.h"
#include "GameUI.h"
#include "GameConfig.h"



void draw(const std::vector<std::string>& map, int playerX, int playerY, int visibilityRadius, bool inTown, Player& player, bool lineOfSightEnabled) {
    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);

    int mapHeight = static_cast<int>(map.size());
    int mapWidth = static_cast<int>(map[0].length());

    int uiPaddingTop = 4;
    int paddingTop = (consoleHeight - mapHeight - 4) / 2;
    int paddingLeft = 20 + (consoleWidth - mapWidth) / 2;

    // Draw the border
    for (int i = paddingTop - 1; i <= paddingTop + mapHeight; ++i) {
        setCursorPosition(paddingLeft - 1, i);
        std::cout << (i == paddingTop - 1 || i == paddingTop + mapHeight ? '+' : '|');
        setCursorPosition(paddingLeft + mapWidth, i);
        std::cout << (i == paddingTop - 1 || i == paddingTop + mapHeight ? '+' : '|');
    }

    for (int j = paddingLeft; j <= paddingLeft + mapWidth; ++j) {
        setCursorPosition(j, paddingTop - 1);
        std::cout << '-';
        setCursorPosition(j, paddingTop + mapHeight);
        std::cout << '-';
    }

    int startY = (playerY - MAX_GAME_AREA_ROWS / 2) > 0 ? playerY - MAX_GAME_AREA_ROWS / 2 : 0;
    int endY = (playerY + MAX_GAME_AREA_ROWS / 2) < mapHeight ? playerY + MAX_GAME_AREA_ROWS / 2 : mapHeight;
    int startX = (playerX - MAX_GAME_AREA_COLS / 2) > 0 ? playerX - MAX_GAME_AREA_COLS / 2 : 0;
    int endX = (playerX + MAX_GAME_AREA_COLS / 2) < mapWidth ? playerX + MAX_GAME_AREA_COLS / 2 : mapWidth;

    for (int i = startY; i < endY; ++i) {
        for (int j = startX; j < endX; ++j) {
            setCursorPosition(paddingLeft + j - startX, paddingTop + i - startY);
            if (inTown) {
                std::cout << map[i][j];
            }
            /*else {
                int distance = (playerX - j) * (playerX - j) + (playerY - i) * (playerY - i);
                if (distance <= visibilityRadius * visibilityRadius && LineOfSight::hasLineOfSight(playerX, playerY, j, i, map)) {
                    std::cout << map[i][j];
                }
                else {
                    std::cout << ' ';
                }
            }*/
            else {
                if (lineOfSightEnabled) {
                    int distance = (playerX - j) * (playerX - j) + (playerY - i) * (playerY - i);
                    if (distance <= visibilityRadius * visibilityRadius && LineOfSight::hasLineOfSight(playerX, playerY, j, i, map)) {
                        std::cout << map[i][j];
                    }
                    else {
                        std::cout << ' ';
                    }
                }
                else {
                    std::cout << map[i][j];
                }
            }

        }
    }

    int statusBarTop = paddingTop + mapHeight;
    drawStatusBar(player, statusBarTop);
    setCursorPosition(0, 0);
}