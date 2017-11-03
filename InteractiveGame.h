#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <array>
#include <utility>
#include <algorithm>
#include "BaseGame.h"
#include "Board.h"
#include "Pawn.h"
#include "Utils.h"
#include "Direction.h"
#include "Player.h"
#include "PlayerInput.h"
#include "Move.h"

using namespace std;

class InteractiveGame : BaseGame {
    PlayerInput _inputA, _inputB;
    bool _record;
    ofstream _aRecord, _bRecord;
    Move _aLastMove, _bLastMove;

    bool handleTurn();
    Result gameMenu() const;
    void writeBoardToFile(const string &filename);

public:
    using BaseGame::BaseGame;

    InteractiveGame(Player &playerA, Player &playerB, unsigned int delay, bool record, int round, string path)
            : BaseGame(playerA, playerB, delay),
              _inputA("wxad", "123"),
              _inputB("imjl", "789"),
              _record(record) {
        if (_record) {
            writeBoardToFile(path + "\\random_" + to_string(round) + ".gboard");

            _aRecord.open(path + "\\random_" + to_string(round) + ".moves-a_small", ios_base::trunc);
            _bRecord.open(path + "\\random_" + to_string(round) + ".moves-b_small", ios_base::trunc);
        }
    }

    InteractiveGame(Player &playerA, Player &playerB, unsigned int delay, bool record, const string &filename)
            : BaseGame(playerA, playerB, delay, filename),
              _inputA("wxad", "123"),
              _inputB("imjl", "789"),
              _record(record) {
        if (_record) {
            string aMovesFilename = filename;
            aMovesFilename.replace(filename.find("gboard"), 6, "moves-a_small");
            string bMovesFilename = filename;
            bMovesFilename.replace(filename.find("gboard"), 6, "moves-b_small");

            _aRecord.open(aMovesFilename, ios_base::trunc);
            _bRecord.open(bMovesFilename, ios_base::trunc);
        }
    }

    Result run();
};