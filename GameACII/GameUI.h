#ifndef GAMEUI_H
#define GAMEUI_H

#include <iostream>
#include "Player.h"

void displayUI(Player& player);
void drawStatusBar(const Player& player, int top);

#endif // GAMEUI_H