#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>
#include "inventory.h"

class Player {
public:
    Player();

    Inventory inventory;

    void gainExperience(int xp);
    void takeDamage(int damage);
    void heal(int amount);

    void addItem(const std::string& item, int quantity);
    bool removeItem(const std::string& item, int quantity);
    void upgradeInventory(int newSize);

    void usePotion(const std::string& potionName);

    int getHealth() const;
    int getExperience() const;
    int getLevel() const;

    void viewInventory() const;
    //addmore

private:
    int level;
    int experience;
    int health;
    int maxHealth;
    int resource;

    int maxInventorySize;

    std::map<std::string, int> potionEffects;
};
#endif //PLAYER_H