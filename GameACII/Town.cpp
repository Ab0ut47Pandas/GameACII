#include "Town.h"
#include <ctime>
#include <cstdlib>
#include <queue>
#include <utility>

std::vector<std::string> generateTown(int width, int height) {
    std::vector<std::string> town(height, std::string(width, '#'));

    // Create the room
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            town[i][j] = '.';
        }
    }

    // Add a door to the room
    town[height / 2][width - 1] = 'D';

    return town;
}



