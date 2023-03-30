#ifndef LINEOFSIGHT_H
#define LINEOFSIGHT_H

#include <vector>
#include <string>

class LineOfSight {
public:
    static bool hasLineOfSight(int x0, int y0, int x1, int y1, const std::vector<std::string>& map);
};

#endif // LINEOFSIGHT_H

