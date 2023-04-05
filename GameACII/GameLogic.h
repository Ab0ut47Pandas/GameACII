#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <string>


extern const char playerSymbol;

bool isPassable(const std::vector<std::string>& map, int x, int y, bool& exitReached, bool& enterDungeon);

#endif // GAME_LOGIC_H