#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <string>

class Dungeon {
public:
    static std::vector<std::string> generate(int width, int height);
    //void loadNewMap(std::vector<std::string>& map, int& playerX, int& playerY);
};

void loadNewMap(std::vector<std::string>& map, int& playerX, int& playerY, int width, int height);
#endif // DUNGEON_H