#pragma once

#include <iostream>
#include <string>
#include <list>
#include "ProgramArgs.h"
#include "Utils.h"
#include "Player.h"
#include "BaseGame.h"
#include "InteractiveGame.h"
#include "AutomaticGame.h"

using namespace std;

class CTFManager {
    enum class Result { SHOW_MENU, EXIT, EXIT_WITH_ERRORS};

    const ProgramArgs &_args;
    list<string> _boardFiles;

    unsigned int _round = 0;
    bool _record = false;
    Player _playerA;
    Player _playerB;

    Result mainMenu();
    void setNames();
    void resetScore();
    Result startGame(bool swapped = false);

    void printSummary() const;

    bool boardFromFile() const { return _args.boardSource() == ProgramArgs::BoardSource::FILE; }
    bool movesFromFile() const { return _args.movesSource() == ProgramArgs::MovesSource::FILE; }

public:
    CTFManager(const ProgramArgs &args);

    void run();
};