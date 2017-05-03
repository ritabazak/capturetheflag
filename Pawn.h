#pragma once

#include <iostream>
#include "Board.h"
#include "Point.h"
#include "Utils.h"
#include "Direction.h"
#include "Player.h"

using namespace std;

class Pawn {
    Point _pos;
    char _key;
    bool _alive = true;
    bool _canSwim;
    bool _canClimbTrees;
    int _color;

public:
    Pawn() {}
    Pawn(const Point &pos, char key, int color, bool canSwim = false, bool canClimbTrees = false)
            : _key(key), _pos(pos), _color(color), _canSwim(canSwim), _canClimbTrees(canClimbTrees) {}

    const Point &getPosition() const { return _pos; }
    void draw(int backColor) const;
    bool isAlive() const { return _alive; }
    void move(Direction dir, int backColor) {
        _pos = _pos.getNext(dir);
        draw(backColor);
    }
    int whichPlayer() const { return (_key <= '3')? Player::A : Player::B; }
    bool canMove(Board::Type cellType) const {
        return cellType == Board::Type::EMP
               || (whichPlayer() == Player::A && cellType == Board::Type::FLGB)
               || (whichPlayer() == Player::B && cellType == Board::Type::FLGA)
               || (_canSwim && cellType == Board::Type::SEA)
               || (_canClimbTrees && cellType == Board::Type::FR);
    }
    static void duel(Pawn &a, Pawn &b, int backColor);
};