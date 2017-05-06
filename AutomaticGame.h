#pragma once

#include <list>
#include <fstream>
#include <sstream>
#include "Utils.h"
#include "BaseGame.h"
#include "Player.h"

class AutomaticGame : public BaseGame {
    struct Move {
        unsigned int turn;
        char pawn;
        Direction dir;

        Move(): dir(Direction::STOPPED) {}

        Move(string line) {
            string turnStr = line.substr(0, line.find(","));
            stringstream(turnStr) >> turn;

            line.erase(0, line.find(",") + 1);

            string pawnStr = line.substr(0, line.find(","));
            stringstream(pawnStr) >> pawnStr;
            pawn = pawnStr[0];

            line.erase(0, line.find(",") + 1);

            string dirStr = line;
            stringstream(dirStr) >> dirStr;
            dir = (Direction)dirStr[0];
        }
    };

    list<Move> _aMoves;
    list<Move> _bMoves;
    Move _aMove;
    Move _bMove;
    unsigned int _turn = 0;

    list<Move> readMoves(string filename);
    bool handleTurn();

public:
    using BaseGame::BaseGame;

    AutomaticGame(Player &playerA,
                  Player &playerB,
                  unsigned int delay,
                  bool quiet,
                  const string &filename);

    Result run();
};