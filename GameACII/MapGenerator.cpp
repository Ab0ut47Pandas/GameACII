#include "MapGenerator.h"
#include <ctime>
#include <cstdlib>

std::vector<std::string> MapGenerator::generateMap(int width, int height) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<std::string> map(height);

    // Generate the initial map
    for (int i = 0; i < height; ++i) {
        std::string row;
        for (int j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                row.push_back('#');
            }
            else {
                row.push_back(std::rand() % 100 < 30 ? '#' : '.');
            }
        }
        map[i] = row;
    }

    // Fill dead-ends
    bool filledDeadEnd;
    do {
        filledDeadEnd = false;

        for (int i = 1; i < height - 1; ++i) {
            for (int j = 1; j < width - 1; ++j) {
                if (map[i][j] == '.') {
                    int surroundingWalls = 0;
                    if (map[i - 1][j] == '#') surroundingWalls++;
                    if (map[i + 1][j] == '#') surroundingWalls++;
                    if (map[i][j - 1] == '#') surroundingWalls++;
                    if (map[i][j + 1] == '#') surroundingWalls++;

                    if (surroundingWalls >= 3) {
                        map[i][j] = '#';
                        filledDeadEnd = true;
                    }
                }
            }
        }
    } while (filledDeadEnd);

    // Set a fixed starting position for the player
    map[1][1] = '@';

    return map;
}