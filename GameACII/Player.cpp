#include "Player.h"

Player::Player() :
	level(1),
	experience(0),
	health(100),
	maxHealth(100),
	resource(100),
	maxInventorySize(10) {
}

void Player::gainExperience(int xp) {
	experience += xp;
	//Leveling logic here pls
}

void Player::takeDamage(int damage) {
	health -= damage;
	if (health <= 0) {
		health = 0;
	}
}

void Player::heal(int amount) {
	health += amount;
	if (health > maxHealth) {
		health = maxHealth;
	}
}

void Player::addItem(const std::string& item, int quantity) {
	inventory[item] += quantity;
}

bool Player::removeItem(const std::string& item, int quantity) {
	if (inventory[item] >= quantity) {
		inventory[item] -= quantity;
		return true;
	}
	return false;
}

void Player::upgradeInventory(int newSize) {
	maxInventorySize = newSize;
}

void Player::usePotion(const std::string& potionName) {
	// Implement potion effects and duration logic here
}
