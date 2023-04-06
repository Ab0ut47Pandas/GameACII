#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include "Player.h"

void draw(const std::vector<std::string>& map, int playerX, int playerY, int visibilityRadius, bool inTown, Player& player, bool lineOfSightEnabled);

#endif // RENDERER_H