#include "CTFManager.h"

CTFManager::CTFManager(const ProgramArgs &args)
        : _args(args), _playerA("A"), _playerB("B") {

    if (boardFromFile()) {
        _boardFiles = listDirectory(_args.path(), ".gboard");
    }
}

CTFManager::Result CTFManager::startGame() {
    AlgorithmGame::Result gameResult;
    string file;

    auto iter = AlgorithmRegistration::algoFactory.begin();
    _moverA = (*iter).second();
    _moverA->setPlayer(1);
    ++iter;
    _moverB = (*iter).second();
    _moverB->setPlayer(2);

    do {
        if (boardFromFile()) {
            if (_boardFiles.empty()) {
                return CTFManager::Result::EXIT;
            }

            file = (string)_boardFiles.front();
            _boardFiles.pop_front();
        }
        else if (_round == _args.randomBoards()) {
            return CTFManager::Result::EXIT;
        }

        if (boardFromFile()) {
            gameResult = AlgorithmGame(_playerA, _playerB, *_moverA, *_moverB, _args.delay(), _args.quiet(), file).run(_round);
        }
        else {
            gameResult = AlgorithmGame(_playerA, _playerB, *_moverA, *_moverB, _args.delay(), _args.quiet()).run(_round);
        }

        ++_round;

        if (gameResult == AlgorithmGame::Result::EXIT_WITH_ERRORS) {
            return CTFManager::Result::EXIT_WITH_ERRORS;
        }
    } while (gameResult == AlgorithmGame::Result::GAME_FINISHED);


    return CTFManager::Result::EXIT;
}

void CTFManager::run() {
    setWindowSize(SCREEN_WIDTH+2, Board::BOARD_OFFSET + SCREEN_HEIGHT + 1+2);

    if (boardFromFile() && !_boardFiles.size()) {
        return;
    }

    Result result = startGame();

    if (result != Result::EXIT_WITH_ERRORS) { printSummary(); };
}