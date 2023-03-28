#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>

class Player {
public:
	Player();

	void gainExperience(int xp);
	void takeDamage(int damage);
	void heal(int amount);

	void addItem(const std::string& item, int quantity);
	void removeItem(const std::string& item, int quantity);
	void upgradeInventory(int newSize);

	//addmore

private:
	int level;
	int experience;
	int health;
	int maxHealth;
	int resource;

	std::map<std::string&, int> inventory;
	int maxInventorySize;

	std::map<std::string, int> potionEffects;
};

#endif //PLAYER_H