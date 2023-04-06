#include "TitleScreen.h"
#include <iostream>
#include "ConsoleUtils.h"



const char* GAME_TITLE = R"(
    ___                           _____                           _
   / _ | ___________ ____  ___   / ___/__ __  _____ _______  ___ (_)
  / __ |/ __/ __/ _ `/ _ \/ -_) / /__/ _ `/ |/ / -_) __/ _ \(_-<_
 /_/ |_/_/  \__/\_,_/_//_/\__/  \___/\_,_/|___/\__/_/ /_//_/___(_)
   ____                              ____     __      _ 
  / __/__  ___________ ______ __    /  _/__  / /_____(_)__ ___ _____    
 _\ \/ _ \/ __/ __/ -_) __/ // /   _/ // _ \/ __/ __/ / _ `/ // / -_)  
/___/\___/_/  \__/\__/_/  \_, ( ) /___/_//_/\__/_/ /_/\_, /\_,_/\__( ) 
                         /___/|/                     /___/         |/  
               __  ____                   __       __  _             
 ___ ____  ___/ / /  _/__  _______ ____  / /____ _/ /_(_)__  ___  ___
/ _ `/ _ \/ _  / _/ // _ \/ __/ _ `/ _ \/ __/ _ `/ __/ / _ \/ _ \(_-<
\_,_/_//_/\_,_/ /___/_//_/\__/\_,_/_//_/\__/\_,_/\__/_/\___/_//_/___/
)";

TitleScreen::TitleScreen() {
}

void TitleScreen::display() const {
    std::cout << GAME_TITLE << std::endl;
}

int TitleScreen::menu() {
    //std::cout << GAME_TITLE << std::endl;
    int choice;

    while (true) {
        std::cout << "1. Start New Game" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "3. Set screen to 720p" << (screenMode == 0 ? " (Current)" : "") << std::endl;
        std::cout << "4. Set screen to Fullscreen" << (screenMode == 1 ? " (Current)" : "") << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 3) {
            setConsoleSize720p();
            screenMode = 0;
            system("cls");
        }
        else if (choice == 4) {
            setConsoleFullScreen();
            screenMode = 1;
            system("cls");
        }
        else {
            break;
        }

        std::cout << std::endl; // Add a newline for spacing
    }

    return choice;
}