#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H

void getConsoleSize(int& width, int& height);
void setCursorPosition(int x, int y);
void setConsoleFullScreen();
void setConsoleSize720p();
void setConsoleFontSize(int size);
void setConsoleBufferSize(int cols, int rows);
void setConsoleWindowSize(int cols, int rows);
#endif // CONSOLEUTILS_H