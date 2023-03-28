#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <vector>
#include <string>

class MapGenerator {
public:
    static std::vector<std::string> generateMap(int width, int height);
};

#endif // MAPGENERATOR_H