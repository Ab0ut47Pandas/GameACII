#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <vector>
#include <string>

class MapGenerator {
public:
    static std::vector<std::string> generateMap(int width, int height);

    bool lineOfSight(int x1, int y1, int x2, int y2, const std::vector<std::string>& map);
};

#endif // MAPGENERATOR_H