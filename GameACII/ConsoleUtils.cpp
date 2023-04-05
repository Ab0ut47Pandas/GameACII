#include "ConsoleUtils.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void getConsoleSize(int& width, int& height) {
#if defined(_WIN32) || defined(_WIN64)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_col;
    height = w.ws_row;
#endif
}

void setCursorPosition(int x, int y) {
#if defined(_WIN32) || defined(_WIN64)
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
        printf("\033[%d;%dH", y + 1, x + 1);
#endif
}

void setConsoleFullScreen() {
    int screenWidth, screenHeight;
    getConsoleSize(screenWidth, screenHeight);

    // Calculate the number of rows and columns based on your monitor's aspect ratio
    int desiredCols = screenWidth * 8 / 10; // Assuming an 8x10 character size
    int desiredRows = screenHeight;

    setConsoleBufferSize(desiredCols, desiredRows);
    setConsoleWindowSize(desiredCols, desiredRows);
}

void setConsoleSize720p() {
    int desiredCols = 128;
    int desiredRows = 40; // Adjust these values based on your preferred console dimensions

    setConsoleBufferSize(desiredCols, desiredRows);
    setConsoleWindowSize(desiredCols, desiredRows);
}

    void setConsoleFontSize(int size) {
#if defined(_WIN32) || defined(_WIN64)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_FONT_INFOEX fontInfo;
        fontInfo.cbSize = sizeof(fontInfo);
        GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
        fontInfo.dwFontSize.X = size;
        fontInfo.dwFontSize.Y = size;
        SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
#else
        // No idea what would happen if this fails or if ran on something other than windows.
        // The user may need to adjust their terminal settings manually.
#endif
    }

    void setConsoleBufferSize(int cols, int rows) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);

        COORD bufferSize;
        bufferSize.X = static_cast<SHORT>(cols);
        bufferSize.Y = static_cast<SHORT>(rows);

        SetConsoleScreenBufferSize(hConsole, bufferSize);
    }

    void setConsoleWindowSize(int cols, int rows) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SMALL_RECT windowSize;
        windowSize.Left = 0;
        windowSize.Top = 0;
        windowSize.Right = static_cast<SHORT>(cols - 1);
        windowSize.Bottom = static_cast<SHORT>(rows - 1);

        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    }

    void hideCursor() {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }

    void clearScreenBuffer(std::ostringstream& buffer, int consoleWidth, int consoleHeight) {
        buffer.str("");
        buffer.clear();

        for (int i = 0; i < consoleHeight; ++i) {
            for (int j = 0; j < consoleWidth; ++j) {
                buffer << ' ';
            }
            buffer << '\n';
        }
    }