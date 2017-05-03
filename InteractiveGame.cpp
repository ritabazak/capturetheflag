#include "InteractiveGame.h"

InteractiveGame::Result InteractiveGame::run() {
    Result menuResult;

    do {
        char input = 0;
        draw();
        gotoxy(SCREEN_START, Board::BOARD_OFFSET + SCREEN_HEIGHT);

        while (input != ESC) {
            if (handleTurn(Player::A) || handleTurn(Player::B)) {
                displayMessage("GAME OVER", 5);
                return Result::GAME_FINISHED;
            }

            while (_kbhit()) {
                input = (char)getchar();
                cout << "\b \b" << flush;

                _inputA.handleKeyInput(input);
                _inputB.handleKeyInput(input);
            }
        }

        menuResult = gameMenu();
    } while (menuResult == Result::GAME_CONTINUED);

    return menuResult;
}

bool InteractiveGame::handleTurn(int player) {
    PlayerInput &input = (player == Player::A)? _inputA : _inputB;
    Pawn *pawns = (player == Player::A)? (Pawn*)_aPawns : (Pawn*)_bPawns;
    bool result = false;

    if (input.hasSelection()) {
        movePawn(pawns[input.getPawn()], player, input.getDirection());
        result = checkVictory(pawns[input.getPawn()]);
        gotoxy(SCREEN_START, Board::BOARD_OFFSET + SCREEN_HEIGHT);
    }
    mySleep(50);

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