#pragma once

#include <iostream>
#include <string>
#include <list>
#include "ProgramArgs.h"
#include "Utils.h"
#include "Player.h"
#include "AlgorithmGame.h"
#include "AbstractPlayer.h"
#include "AlgoPlayer_304824170_318110376.h"
#include "AlgorithmRegistration.h"

using namespace std;

class CTFManager {
    enum class Result { EXIT, EXIT_WITH_ERRORS };

    const ProgramArgs &_args;
    list<string> _boardFiles;

    unsigned int _round = 0;
    Player _playerA;
    Player _playerB;
    AbstractPlayer *_moverA = nullptr, *_moverB = nullptr;

    Result startGame();

    void printSummary() const {
        if (!_args.quiet()) { clearScreen(); }

        cout << "Game Summary" << endl;
        cout << _moverA->getName() << " for A points: " << _playerA.getScore() << endl;
        cout << _moverB->getName() << " for B points: " << _playerB.getScore() << endl;
    }
    bool boardFromFile() const { return _args.boardSource() == ProgramArgs::BoardSource::FILE; }

public:
    CTFManager(const ProgramArgs &args);

    ~CTFManager() {
        delete _moverA;
        delete _moverB;
    }

    void run();
};