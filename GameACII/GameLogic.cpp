#include "GameLogic.h"
#include <set>

const char playerSymbol = '@';


bool isPassable(const std::vector<std::string>& map, int x, int y, bool& exitReached, bool& enterDungeon) {
    static std::set<char> walkableTiles = { '.', ' ', 'E', 'X', 'D' }; // Add 'D' to the set

    char tile = map[y][x];
    exitReached = (tile == 'X');
    enterDungeon = (tile == 'D'); // Check for 'D' tile

    return walkableTiles.count(tile) > 0;
}