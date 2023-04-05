#include "GameLogic.h"


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