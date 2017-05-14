#pragma once

#include <list>
#include <fstream>
#include <sstream>
#include "Utils.h"
#include "BaseGame.h"
#include "Player.h"
#include "Move.h"

class AutomaticGame : public BaseGame {
    list<Move> _aMoves;
    list<Move> _bMoves;
    Move _aMove;
    Move _bMove;

    list<Move> readMoves(string filename);
    Player::Side handleTurn();

public:
    using BaseGame::BaseGame;

    AutomaticGame(Player &playerA,
                  Player &playerB,
                  unsigned int delay,
                  bool quiet,
                  const string &filename);

    Result run(int cycle);
};