#include "GameUI.h"
#include "SaveLoad.h"
#include "ConsoleUtils.h"

void displayUI(Player& player) {
    // Clear the screen
    system("cls");

    // Display player stats
    std::cout << "Player Stats:\n";
    std::cout << "Health: " << player.getHealth() << "\n";
    std::cout << "Experience: " << player.getExperience() << "\n";
    std::cout << "Level: " << player.getLevel() << "\n";

    // Display UI options
    std::cout << "\nOptions:\n";
    std::cout << "1. Use a health potion\n";
    std::cout << "2. View inventory\n";
    std::cout << "3. Save game\n";
    std::cout << "4. Exit\n";

    // Get user input
    int choice;
    std::cin >> choice;

    // Process user input
    switch (choice) {
    case 1:
        // Use a health potion
        player.usePotion("health");
        break;
    case 2:
        // View inventory
        player.viewInventory();
        break;
    case 3:
        // Save game
        saveGame(player);
        break;
    case 4:
        // Exit
        exit(0);
    }
}

void drawStatusBar(const Player& player) {
    int consoleWidth, consoleHeight;
    getConsoleSize(consoleWidth, consoleHeight);
    // Move the cursor to the lower portion of the screen
    setCursorPosition(0, consoleHeight - 4);

    std::cout << std::string(consoleWidth, '=') << std::endl;
    std::cout << "Health: " << player.getHealth()
        << " | Experience: " << player.getExperience()
        << " | Level: " << player.getLevel() << std::endl;
    std::cout << std::string(consoleWidth, '=') << std::endl;
}