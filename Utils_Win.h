#pragma once

#ifndef __APPLE__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>
#include <time.h>
#include <string>
#include <list>
#include <experimental\filesystem>

using namespace std;

enum class BoxCharacters {
    CORNER_TL = '\xC9',
    CORNER_TR = '\xBB',
    CORNER_BL = '\xC8',
    CORNER_BR = '\xBC',
    HORIZONTAL = '\xCD',
    HORIZONTAL_THIN = '\xC4',
    HORIZONTAL_DOWN = '\xD1',
    HORIZONTAL_UP = '\xCF',
    VERTICAL_RIGHT = '\xC7',
    VERTICAL_LEFT = '\xB6',
    VERTICAL = '\xBA',
    VERTICAL_THIN = '\xB3',
    PLUS_THIN = '\xC5',
};
enum { BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_PURPLE, OLIVE, WHITE, GREY, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW };
enum { SCREEN_START = 0, SCREEN_WIDTH = 53, SCREEN_HEIGHT = 27 };
enum { ESC = 27 };

void setTextColor(int foreground_color, int background_color);
void resetTextColor();
void setTextColor(int foreground_color);
void clearScreen();
void gotoxy(int x, int y);
void hideCursor();
void showCursor();
int getRandom(int start, int end);
void randomSeed();
void setWindowSize(int width, int height);
string getCurrentWorkingDirectory();
string readLine(istream& in);
list<string> listDirectory(string path, string extension, string filename = "");

#endif