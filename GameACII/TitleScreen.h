#pragma once
#ifndef TITLESCREEN_H
#define TITLESCREEN_H

class TitleScreen {
public:
    TitleScreen();
    void display() const;
    int menu();

private:
    int screenMode = 0; // 0 for 720p, 1 for fullscreen
};



#endif // TITLESCREEN_H