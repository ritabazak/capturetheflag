#pragma once

#include "AbstractPlayer.h"
#include <array>
#include <vector>
#include <stdlib.h>
#include <sstream>

using namespace std;

class AlgoPlayer_304824170_318110376 : public AbstractPlayer {
    enum { MAX_DISTANCE = BoardData::cols + BoardData::rows - 1 };

    class Point {
        int _x, _y;

    public:
        Point(int x = -1, int y = -1) : _x(x), _y(y) {}
        Point(const GameMove &move, bool from)
                : _x((from ? move.from_x : move.to_x) - 1),
                  _y((from ? move.from_y : move.to_y) - 1) {}

        bool operator==(const Point &p) const {
            return _x == p._x && _y == p._y;
        }

        const int &getX() const { return _x; }
        const int &getY() const { return _y; }

        int distance(const Point & destination) const {
            return abs(destination._x - _x) + abs(destination._y - _y);
        }
    };

    struct PlayerPawn {
        char key;
        Point pos;

        PlayerPawn() {};
        PlayerPawn(char _key, Point _pos) : key(_key), pos(_pos) {}
    };

    struct PossibleMove {
        PlayerPawn &pawn;
        Point destination;
        int score = 0;

        PossibleMove(PlayerPawn &_pawn, const Point &_dest) : pawn(_pawn), destination(_dest) {}
    };

    const double _attackLevel;
    const double _flagLevel;
    int _player;
    BoardData const *_bd = nullptr;
    array<PlayerPawn, 3> _myPawns, _enemyPawns;
    Point _myFlag, _enemyFlag;
    char _board[BoardData::rows][BoardData::cols];
    GameMove _myLastMove;

    bool canSwim(const PlayerPawn &pawn) const;
    bool canClimbTrees(const PlayerPawn &pawn) const;
    vector<PossibleMove> getAllPossibleMoves();
    void updateGameState(const GameMove &opponentsMove);
    int findByPosition(int player, const Point &pt) const;
    void addPossibleMoves(vector<PossibleMove> &moves, PlayerPawn &pawn) const;
    PossibleMove getBestMove();
    void calculateMoveScore(PossibleMove &move) const;
    bool canMove(const PlayerPawn &pawn, const Point &dest) const;
    int getFlagScore(const PossibleMove &move) const;
    int getAttackScore(const PossibleMove &move) const;
    int getDefeatScore(const Point &enemyPos, char key) const;

public:
    AlgoPlayer_304824170_318110376(double attackLevel, double flagLevel)
            : _attackLevel(attackLevel),
              _flagLevel(flagLevel),
              _myLastMove(0, 0, 0, 0) {}

    // Player: 1 for A, 2 for B
    void setPlayer(int player) override { _player = player; }
    void init(const BoardData& board) override;
    GameMove play(const GameMove& opponentsMove) override;
    string getName() const override {
        stringstream ss;
        ss << "algo" << _attackLevel << "_" << _flagLevel << "_304824170_318110376";
        return ss.str();
    }
};