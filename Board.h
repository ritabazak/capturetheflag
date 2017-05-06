#pragma once

#include <iostream>
#include <array>
#include <string>
#include <list>
#include <utility>
#include <fstream>
#include "Utils.h"
#include "Point.h"
#include "ProgramArgs.h"

using namespace std;

class Board {
public:
    enum { BOARD_SIZE = 13, CELL_SIZE = 3, BOARD_OFFSET = 2 };
    enum class Type { EMP, SEA, FR, FLGA, FLGB, _typeCount, OUT_OF_BOUNDS };

private:
    const string _typeNames[(int)Type::_typeCount] = { "   ", " ~ ", " ^ ", " F ", " F " };
    const int _typeColors[(int)Type::_typeCount] = { BLACK, DARK_BLUE, DARK_GREEN, YELLOW, PURPLE };

    Type _board[BOARD_SIZE][BOARD_SIZE] = { {Type::EMP} };

    Type &getCell(const Point &p) { return _board[p.getY()][p.getX()]; }
    Type getCell(const Point &p) const { return _board[p.getY()][p.getX()]; }

public:
    Board(ProgramArgs::BoardSource source = ProgramArgs::BoardSource::RANDOM);

    Point getRandomEmptyPoint() const;

    void draw() const;

    Type getCellType(const Point &p) const {
        if (p.getX() < 0 || p.getX() >= BOARD_SIZE || p.getY() < 0 || p.getY() >= BOARD_SIZE) {
            return Type::OUT_OF_BOUNDS;
        }

        return getCell(p);
    }
    int getCellColor(Type cellType) const { return _typeColors[(int)cellType]; }

    void drawCell(int x, int y) const;
    void drawCell(const Point &p) const { drawCell(p.getX(), p.getY()); }

    void setCells(list <pair<Point, Type>> cellList);

    array<array<char, BOARD_SIZE>, BOARD_SIZE> generateCharArray();
};