#pragma once

#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <list>

using namespace std;

enum { SCREEN_START=0, SCREEN_WIDTH=53, SCREEN_HEIGHT=27 };
enum { ESC = 27 };

int getRandom(int start, int end);
void randomSeed();

void gotoxy(int x, int y);
void hideCursor();
void showCursor();
void clearScreen();
int _kbhit();
void mySleep(int ms);
void setTextColor(int foregroundColor, int backgroundColor, bool bold = false);
void resetTextColor();
string readLine(istream &in);
list<string> listDirectory(string path, string extension, string filename = "");

enum { BLACK=0, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE };
/*

void setTextColor(int foreground_color, int background_color);
void setTextColor(int foreground_color);
void clearScreen();
void gotoxy(int x, int y);
void hideCursor();
 */