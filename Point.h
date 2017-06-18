#pragma once

#include "Utils.h"
#include "GameMove.h"

class Point {
    int _x, _y;

public:
    Point(int x = -1, int y = -1) : _x(x), _y(y) {}
    Point(const GameMove &move, bool from)
            : _x((from ? move.from_x : move.to_x) - 1),
              _y((from ? move.from_y : move.to_y) - 1) {}

    static Point randomPoint(int start, int end) {
        return Point(getRandom(start, end), getRandom(start, end));
    }

    bool operator==(const Point &p) const {
        return _x == p._x && _y == p._y;
    }

    const int &getX() const { return _x; }
    const int &getY() const { return _y; }
};