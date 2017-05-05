#include "Utils_Win.h"

#ifndef __APPLE__

using namespace std;
namespace fs = std::experimental::filesystem;

void setTextColor(int foreground_color, int background_color) {
    int color = foreground_color | background_color * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor() {
    setTextColor(WHITE, BLACK);
}

void setTextColor(int foreground_color) {
    setTextColor(foreground_color, 0);
}

void clearScreen() {
    system("cls");
}

// function definition -- requires windows.h
void gotoxy(int x, int y) {
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void setWindowSize(int width, int height) {
    HANDLE windowHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT size;
    size.Top = size.Left = 0;
    size.Bottom = height - 1;
    size.Right = width - 1;
    COORD coord;
    coord.X = width;
    coord.Y = height;
    SetConsoleScreenBufferSize(windowHandle, coord);
    SetConsoleWindowInfo(windowHandle, true, &size);
}

int getRandom(int start, int end) {
    return (rand() % (end - start)) + start;
}

void randomSeed() {
    srand((unsigned int)time(NULL));
}

string readLine(istream &in) {
    string result;
    char c = (char)in.get();

    while (in.gcount() && c != '\n') {
        result += c;
        c = (char)in.get();
    }

    if (result.length() && result.back() == '\r') {
        result.pop_back();
    }

    return result;
}

list<string> listDirectory(string path, string extension, string filename) {
    list<string> files;

    for (auto& d : fs::directory_iterator(path)) {
        if (d.status().type() == fs::file_type::regular) {
            if (d.path().extension().string() == extension) {
                files.push_back(d.path().string());
            }
        }
    }




    /*if (extension == "gboard") {
        files.push_back("board_1.gboard");
    }*/

    return files;
}

string getCurrentWorkingDirectory() {
    char path[255];
    _getcwd(path, 255);
    return string(path);
}

#endif