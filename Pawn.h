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
    char getKey() const { return _key; }
    void draw(int backColor) const;
    bool isAlive() const { return _alive; }
    void move(Direction dir) { _pos = _pos.getNext(dir); }
    Player::Side whichPlayer() const { return (_key <= '3')? Player::Side::A : Player::Side::B; }
    bool canMove(Board::Type cellType) const {
        return cellType == Board::Type::EMP
               || (whichPlayer() == Player::Side::A && cellType == Board::Type::FLGB)
               || (whichPlayer() == Player::Side::B && cellType == Board::Type::FLGA)
               || (_canSwim && cellType == Board::Type::SEA)
               || (_canClimbTrees && cellType == Board::Type::FR);
    }
    static void duel(Pawn &a, Pawn &b);
};