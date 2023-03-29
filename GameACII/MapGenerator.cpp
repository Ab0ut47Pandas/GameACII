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

std::vector<std::string> MapGenerator::generateMap(int width, int height) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<std::string> map(height, std::string(width, '#'));

    // Set the entrance and exit positions
    int entranceX = 1, entranceY = 1;
    int exitX = width - 2, exitY = height - 2;

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

    // Add some random walls to make the map more interesting
    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            if (map[i][j] == '.' && std::rand() % 100 < 30) {
                map[i][j] = '#';
            }
        }
    }

    // Set the entrance and exit symbols
    map[entranceY][entranceX] = 'E';
    map[exitY][exitX] = 'X';

    return map;
}