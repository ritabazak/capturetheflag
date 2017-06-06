#pragma once

#include <iostream>
#include <string>
#include <list>
#include "ProgramArgs.h"
#include "Utils.h"
#include "Player.h"
#include "AlgorithmGame.h"

using namespace std;

class CTFManager {
    enum class Result { EXIT, EXIT_WITH_ERRORS };

    const ProgramArgs &_args;
    list<string> _boardFiles;

    unsigned int _round = 0;
    Player _playerA;
    Player _playerB;

    Result startGame();

    void printSummary() const;
    bool boardFromFile() const { return _args.boardSource() == ProgramArgs::BoardSource::FILE; }

public:
    CTFManager(const ProgramArgs &args);

    void run();
};