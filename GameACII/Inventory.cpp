// inventory.cpp
#include "inventory.h"

void Inventory::addItem(const std::string& itemName, int quantity) {
    items[itemName] += quantity;
}

bool Inventory::removeItem(const std::string& itemName, int quantity) {
    auto it = items.find(itemName);
    if (it != items.end() && it->second >= quantity) {
        it->second -= quantity;
        if (it->second == 0) {
            items.erase(it);
        }
        return true;
    }
    return false;
}

int Inventory::getItemQuantity(const std::string& itemName) const {
    auto it = items.find(itemName);
    if (it != items.end()) {
        return it->second;
    }
    return 0;
}