// inventory.h
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <unordered_map>

class Inventory {
public:
    // Adds an item to the inventory by its name and quantity
    void addItem(const std::string& itemName, int quantity);

    // Removes an item from the inventory by its name and quantity
    bool removeItem(const std::string& itemName, int quantity);

    // Returns the quantity of an item in the inventory by its name
    int getItemQuantity(const std::string& itemName) const;

private:
    std::unordered_map<std::string, int> items;
};

#endif // INVENTORY_H