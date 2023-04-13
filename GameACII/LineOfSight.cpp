#include "LineOfSight.h"
#include <cmath>

bool LineOfSight::hasLineOfSight(int x0, int y0, int x1, int y1, const std::vector<std::string>& map) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        if (map[y0][x0] == '#') {
            return false;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }

    return true;
}

