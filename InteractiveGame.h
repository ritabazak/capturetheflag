#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <utility>
#include <algorithm>
#include "BaseGame.h"
#include "Board.h"
#include "Pawn.h"
#include "Utils.h"
#include "Direction.h"
#include "Player.h"
#include "PlayerInput.h"

using namespace std;

class InteractiveGame : BaseGame {
    PlayerInput _inputA, _inputB;

    bool handleTurn(int player);
    Result gameMenu() const;

public:
    using BaseGame::BaseGame;

    InteractiveGame(Player &playerA, Player &playerB)
            : BaseGame(playerA, playerB) , _inputA("wxad", "123"), _inputB("imjl", "789") {
    }

    InteractiveGame(Player &playerA, Player &playerB, const string &filename)
            : BaseGame(playerA, playerB, filename),
              _inputA("wxad", "123"),
              _inputB("imjl", "789") { }

    Result run();
};