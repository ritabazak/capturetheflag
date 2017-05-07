#include "CTFManager.h"

CTFManager::CTFManager(const ProgramArgs &args)
        : _args(args), _playerA("A"), _playerB("B") {

    if (boardFromFile()) {
        _boardFiles = listDirectory(_args.path(), ".gboard");
    }
}

void CTFManager::setNames() {
    string tempName;

    cout << "Enter player A's name: ";
    cin >> tempName;
    _playerA.setName(tempName);

    cout << "Enter player B's name: ";
    cin >> tempName;
    _playerB.setName(tempName);

    cout << "Names were set." << endl;

    Sleep(_args.delay() * 50);
}

void CTFManager::resetScore() {
    _playerA.resetScore();
    _playerB.resetScore();

    cout << "Scores were reset." << endl;

    Sleep(_args.delay() * 50);
}

CTFManager::Result CTFManager::mainMenu() {
    clearScreen();
    showCursor();

    cout << "1. Set player names" << endl;
    cout << "2. Start game" << endl;
    cout << "3. Start swapped game" << endl;
    cout << "4. Reset score" << endl;
    cout << "5. " << (_record? "Stop" : "Start") << " recording" << endl;
    cout << "9. Exit" << endl;

    int op;

    while (true) {
        cin >> op;

        switch (op) {
            case 1:
                setNames();
                return Result::SHOW_MENU;
            case 2:
            case 3:
                return startGame(op == 3);
            case 4:
                resetScore();
                return Result::SHOW_MENU;
            case 5:
                _record = !_record;
                return Result::SHOW_MENU;
            case 9:
                return Result::EXIT;
            default:
                cout << "Please enter a valid option" << endl;
        }
    }
}

CTFManager::Result CTFManager::startGame(bool swapped) {
    Player &leftPlayer = swapped? _playerB : _playerA;
    Player &rightPlayer = swapped? _playerA : _playerB;

    BaseGame::Result gameResult;
    string file;

    do {
        if (boardFromFile()) {
            file = (string)_boardFiles.front();
            _boardFiles.pop_front();
        }

        do {
            if (movesFromFile()) {
                gameResult = AutomaticGame(leftPlayer, rightPlayer, _args.delay(), _args.quiet(), file).run();
            }
            else if (boardFromFile()) {
                gameResult = InteractiveGame(leftPlayer, rightPlayer, _args.delay(), _record, file).run();
            }
            else {
                gameResult = InteractiveGame(leftPlayer, rightPlayer, _args.delay(), _record, _round, _args.path()).run();
            }
        } while (gameResult == BaseGame::Result::GAME_RESTARTED);

        ++_round;

        if (gameResult == BaseGame::Result::EXIT_WITH_ERRORS) {
            return CTFManager::Result::EXIT_WITH_ERRORS;
        }
        if (gameResult == BaseGame::Result::EXIT || (boardFromFile() && _boardFiles.empty())) {
            return CTFManager::Result::EXIT;
        }
    } while (gameResult == BaseGame::Result::GAME_FINISHED);

    return CTFManager::Result::SHOW_MENU;
}

void CTFManager::run() {
    setWindowSize(SCREEN_WIDTH, Board::BOARD_OFFSET + SCREEN_HEIGHT + 1);

    if (boardFromFile() && !_boardFiles.size()) {
        return;
    }

    Result result;

    if (movesFromFile()) {
        result = startGame();
    }

    else {
        do {
            result = mainMenu();
        } while (result == Result::SHOW_MENU);
    }
    if (result != Result::EXIT_WITH_ERRORS) { printSummary(); };
}

void CTFManager::printSummary() const {
    clearScreen();

    cout << "Game Summary" << endl;
    cout << _playerA.getName() << " points: " << _playerA.getScore() << endl;
    cout << _playerB.getName() << " points: " << _playerB.getScore() << endl;
}