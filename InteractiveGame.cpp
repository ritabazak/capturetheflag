#include "InteractiveGame.h"

InteractiveGame::Result InteractiveGame::run() {
    Result menuResult;

    do {
        char input = 0;
        draw();
        gotoxy(SCREEN_START, Board::BOARD_OFFSET + SCREEN_HEIGHT);

        while (input != ESC) {
            if (handleTurn()) {
                displayMessage("GAME OVER", _delay * 50);
                return Result::GAME_FINISHED;
            }

            while (_kbhit()) {
                input = (char)_getch();
                cout << "\b" << flush;

                _inputA.handleKeyInput(input);
                _inputB.handleKeyInput(input);
            }
        }

        menuResult = gameMenu();
    } while (menuResult == Result::GAME_CONTINUED);

    return menuResult;
}

bool InteractiveGame::handleTurn() {
    int player = (_turn % 2)? Player::B : Player::A;

    PlayerInput &input = (player == Player::A)? _inputA : _inputB;
    Pawn *pawns = (player == Player::A)? (Pawn*)_aPawns : (Pawn*)_bPawns;

    bool result = false;

    if (input.hasSelection()) {
        movePawn(pawns[input.getPawn()], player, input.getDirection());

        if (_record) {
            Move &lastMove = (player == Player::A)? _aLastMove : _bLastMove;
            Move newMove(_turn, input);

            if (lastMove != newMove && newMove.dir != Direction::STOPPED) {
                ofstream &movesFile = (player == Player::A)? _aRecord : _bRecord;
                lastMove = newMove;
                lastMove.writeToFile(movesFile);
            }
        }

        result = checkVictory(pawns[input.getPawn()]);
        gotoxy(SCREEN_START, Board::BOARD_OFFSET + SCREEN_HEIGHT);
    }

    ++_turn;
    Sleep(_delay);

    return result;
}

InteractiveGame::Result InteractiveGame::gameMenu() const {
    showCursor();
    clearScreen();

    cout << "1. Continue game" << endl;
    cout << "2. Restart game" << endl;
    cout << "8. Exit to main menu" << endl;
    cout << "9. Exit" << endl;

    int option;

    while (true) {
        cin >> option;

        switch (option) {
            case 1:
                return Result::GAME_CONTINUED;
            case 2:
                return Result::GAME_RESTARTED;
            case 8:
                return Result::EXIT_TO_MAIN_MENU;
            case 9:
                return Result::EXIT;
            default:
                cout << "Please enter a valid option" << endl;
        }
    }
}

void InteractiveGame::writeBoardToFile(const string &filename) {
    array<array<char, Board::BOARD_SIZE>, Board::BOARD_SIZE> boardArray = _board.generateCharArray();

    for (int i = 0; i < 3; i++) {
        const Point &p1 = _aPawns[i].getPosition();
        boardArray[p1.getY()][p1.getX()] = _aPawns[i].getKey();

        const Point &p2 = _bPawns[i].getPosition();
        boardArray[p2.getY()][p2.getX()] = _bPawns[i].getKey();
    }

    ofstream file(filename, ios_base::trunc);

    for (int row = 0; row < Board::BOARD_SIZE; row++) {
        for (int col = 0; col < Board::BOARD_SIZE; col++) {
            file << boardArray[row][col];
        }

        file << endl;
    }
}