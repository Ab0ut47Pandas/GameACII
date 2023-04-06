#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H

#include <sstream>
#include <windows.h>

void getConsoleSize(int& width, int& height);
void setCursorPosition(int x, int y);
void setConsoleFullScreen();
void setConsoleSize720p();
void setConsoleFontSize(int size);
void setConsoleBufferSize(int cols, int rows);
void setConsoleWindowSize(int cols, int rows);
void hideCursor();
void clearScreenBuffer(std::ostringstream& buffer, int consoleWidth, int consoleHeight);
void clearConsole();
LRESULT CALLBACK ConsoleWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SubclassConsoleWindow();

#endif // CONSOLEUTILS_H