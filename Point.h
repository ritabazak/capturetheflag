#pragma once

#include "Utils.h"
#include "Direction.h"

class Point {
    int _x, _y;

public:
    Point(int x = -1, int y = -1): _x(x), _y(y) {}

    static Point randomPoint(int start, int end) {
        return Point(getRandom(start, end), getRandom(start, end));
    }

    bool operator==(const Point &p) const {
        return _x == p._x && _y == p._y;
    }

    const int &getX() const { return _x; }
    const int &getY() const { return _y; }
    Point getNext(Direction dir) const {
        switch (dir) {
            case Direction::UP:
                return Point(_x, _y - 1);
            case Direction::DOWN:
                return Point(_x, _y + 1);
            case Direction::LEFT:
                return Point(_x - 1, _y);
            case Direction::RIGHT:
                return Point(_x + 1, _y);
            default:
                return Point(_x, _y);
        }
    }
};