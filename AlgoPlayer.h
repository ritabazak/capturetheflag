#pragma once

#include "AbstractPlayer.h"
#include "Point.h"
#include <array>

using namespace std;

class AlgoPlayer : public AbstractPlayer {
    int _player;
    BoardData const *_bd;
    array<Point, 3> _myPawns, _enemyPawns;
    Point _myFlag, _enemyFlag;
    char _board[BoardData::rows][BoardData::cols];

public:
    // TODO: Make sure this is right
    virtual ~AlgoPlayer() { }

    // Player: 1 for A, 2 for B
    void setPlayer(int player) override { _player = player; }
    void init(const BoardData& board) override;
    GameMove play(const GameMove& opponentsMove) override {
        GameMove move(_myPawns[0].getX(),
                      _myPawns[0].getY(),
                      _myPawns[0].getX() + 1,
                      _myPawns[0].getY());

        return move;
    }
    string getName() const override {
        return "Genius Algorithm!!!";
    }
};