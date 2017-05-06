#pragma once

#ifdef __APPLE__

#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <list>
//#include <boost/filesystem.hpp>

using namespace std;

enum class BoxCharacters {
    CORNER_TL = '*',
    CORNER_TR = '*',
    CORNER_BL = '*',
    CORNER_BR = '*',
    HORIZONTAL = '-',
    HORIZONTAL_THIN = '-',
    HORIZONTAL_DOWN = '-',
    HORIZONTAL_UP = '-',
    VERTICAL_RIGHT = '|',
    VERTICAL_LEFT = '|',
    VERTICAL = '|',
    VERTICAL_THIN = '|',
    PLUS_THIN = '+',
};
enum { SCREEN_START=0, SCREEN_WIDTH=53, SCREEN_HEIGHT=27 };
enum { ESC = 27 };

int getRandom(int start, int end);
void randomSeed();

int _getch();
void gotoxy(int x, int y);
void hideCursor();
void showCursor();
void clearScreen();
int _kbhit();
void Sleep(int ms);
void setTextColor(int foregroundColor, int backgroundColor, bool bold = false);
void resetTextColor();
string readLine(istream &in);
list<string> listDirectory(string path, string extension, string filename = "");
string getCurrentWorkingDirectory();
void setWindowSize(int width, int height);

//enum { BLACK=0, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
enum { BLACK=0, RED, DARK_GREEN, YELLOW, DARK_BLUE, PURPLE, CYAN, WHITE };

#endif