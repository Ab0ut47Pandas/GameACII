#include "MapGenerator.h"
#include <ctime>
#include <cstdlib>
#include <queue>
#include <utility>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void floodFill(std::vector<std::string>& map, int x, int y, char oldChar, char newChar) {
    if (x < 0 || x >= map[0].size() || y < 0 || y >= map.size()) {
        return;
    }

    if (map[y][x] != oldChar) {
        return;
    }

    map[y][x] = newChar;

    floodFill(map, x - 1, y, oldChar, newChar);
    floodFill(map, x + 1, y, oldChar, newChar);
    floodFill(map, x, y - 1, oldChar, newChar);
    floodFill(map, x, y + 1, oldChar, newChar);
}

std::vector<std::string> MapGenerator::generateMap(int width, int height) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<std::string> map(height, std::string(width, '#'));


    // Set the entrance and exit positions
    int entranceX = 5, entranceY = 5;
    int exitX = width - 6, exitY = height - 6;

    int minDistance = (width + height) / 4; // Adjust this value as needed

    do {
        entranceX = std::rand() % (width - 2) + 1;
        entranceY = std::rand() % (height - 2) + 1;
        exitX = std::rand() % (width - 2) + 1;
        exitY = std::rand() % (height - 2) + 1;
    } while (abs(exitX - entranceX) + abs(exitY - entranceY) < minDistance);

    // Create a valid path between entrance and exit
    std::queue<std::pair<int, int>> pathQueue;
    pathQueue.push({ entranceX, entranceY });

    while (!pathQueue.empty()) {
        int x = pathQueue.front().first;
        int y = pathQueue.front().second;
        pathQueue.pop();

        // Check if the current position is the exit
        if (x == exitX && y == exitY) {
            break;
        }

        // Generate a random order of directions
        std::vector<Direction> directions = { UP, DOWN, LEFT, RIGHT };
        std::random_shuffle(directions.begin(), directions.end());

        for (Direction direction : directions) {
            int newX = x;
            int newY = y;

            switch (direction) {
            case UP:
                newY -= 1;
                break;
            case DOWN:
                newY += 1;
                break;
            case LEFT:
                newX -= 1;
                break;
            case RIGHT:
                newX += 1;
                break;
            }

            // Check if the new position is inside the map and not visited
            if (newX >= 1 && newX < width - 1 && newY >= 1 && newY < height - 1 && map[newY][newX] == '#') {
                map[newY][newX] = '.';
                pathQueue.push({ newX, newY });
            }
        }
    }

    // Ensure there is enough open space around the entrance
    map[entranceY - 1][entranceX] = '.';
    map[entranceY + 1][entranceX] = '.';
    map[entranceY][entranceX - 1] = '.';
    map[entranceY][entranceX + 1] = '.';

    // Add some random walls to make the map more interesting
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            if (map[i][j] == '.' && std::rand() % 100 < 30) {
                // Temporarily place a wall
                map[i][j] = '#';

                // Use flood fill to check if the entrance and exit are still connected
                floodFill(map, entranceX, entranceY, '.', 'F');

                // If the exit is not connected, remove the wall
                if (map[exitY][exitX] != 'F') {
                    map[i][j] = '.';
                }

                // Reset flood fill results
                for (int y = 1; y < height - 1; ++y) {
                    for (int x = 1; x < width - 1; ++x) {
                        if (map[y][x] == 'F') {
                            map[y][x] = '.';
                        }
                    }
                }
            }
        }
    }

    // Set the entrance and exit symbols
    map[entranceY][entranceX] = 'E';
    map[exitY][exitX] = 'X';

    return map;
}