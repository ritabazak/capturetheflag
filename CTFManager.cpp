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

    AbstractPlayer *moverA = new AlgoPlayer;
    moverA->setPlayer(1);
    AbstractPlayer *moverB = new AlgoPlayer;
    moverB->setPlayer(2);

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
            gameResult = AlgorithmGame(_playerA, _playerB, *moverA, *moverB, _args.delay(), _args.quiet(), file).run(_round);
        }
        else {
            gameResult = AlgorithmGame(_playerA, _playerB, *moverA, *moverB, _args.delay(), _args.quiet()).run(_round);
        }

        ++_round;

        if (gameResult == AlgorithmGame::Result::EXIT_WITH_ERRORS) {
            return CTFManager::Result::EXIT_WITH_ERRORS;
        }
    } while (gameResult == AlgorithmGame::Result::GAME_FINISHED);

    return CTFManager::Result::EXIT;
}

void CTFManager::run() {
    setWindowSize(SCREEN_WIDTH, Board::BOARD_OFFSET + SCREEN_HEIGHT + 1);

    if (boardFromFile() && !_boardFiles.size()) {
        return;
    }

    Result result = startGame();

    if (result != Result::EXIT_WITH_ERRORS) { printSummary(); };
}

void CTFManager::printSummary() const {
    if (!_args.quiet()) { clearScreen(); }

    cout << "Game Summary" << endl;
    cout << _playerA.getName() << " points: " << _playerA.getScore() << endl;
    cout << _playerB.getName() << " points: " << _playerB.getScore() << endl;
}