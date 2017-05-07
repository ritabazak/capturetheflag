#include "AutomaticGame.h"

AutomaticGame::AutomaticGame(Player &playerA,
                             Player &playerB,
                             unsigned int delay,
                             bool quiet,
                             const string &filename)
        : BaseGame(playerA, playerB, delay, filename) {
    _quiet = quiet;

    string aMovesFilename = filename;
    aMovesFilename.replace(filename.find("gboard"), 6, "moves-a_small");
    string bMovesFilename = filename;
    bMovesFilename.replace(filename.find("gboard"), 6, "moves-b_small");

    _aMoves = readMoves(aMovesFilename);
    _bMoves = readMoves(bMovesFilename);
}

list<Move> AutomaticGame::readMoves(string filename) {
    list<Move> moves;
    ifstream file(filename);

    string line = readLine(file);

    while (file.is_open() && !file.eof()) {
        moves.push_back(Move(line));
        line = readLine(file);
    }

    return moves;
}

bool AutomaticGame::handleTurn() {
    bool result = false;

    if (_turn % 2 == 0) {
        if (_aMoves.size() && _turn == _aMoves.front().turn) {
            _aMove = _aMoves.front();
            _aMoves.pop_front();
        }

        if (_aMove.dir != Direction::STOPPED) {
            movePawn(_aPawns[_aMove.pawn - '1'], Player::A, _aMove.dir);
            result = checkVictory(_aPawns[_aMove.pawn - '1']);
        }
    }

    else {
        if (_bMoves.size() && _turn == _bMoves.front().turn) {
            _bMove = _bMoves.front();
            _bMoves.pop_front();
        }
        if (_bMove.dir != Direction::STOPPED) {
            movePawn(_bPawns[_bMove.pawn - '7'], Player::B, _bMove.dir);
            result = checkVictory(_bPawns[_bMove.pawn - '7']);
        }
    }

    if (!_quiet) { Sleep(_delay); }

    ++_turn;
    return result;
}

BaseGame::Result AutomaticGame::run() {
    if (BaseGame::run() == Result::EXIT_WITH_ERRORS) { return Result::EXIT_WITH_ERRORS; }

    if (!_quiet) { draw(); }

    while (_aMoves.size() || _bMoves.size() ||
           _aMove.dir != Direction::STOPPED ||
           _bMove.dir != Direction::STOPPED) {
        if (handleTurn()) {
            break;
        }
    }

    if (!_quiet) { displayMessage("GAME OVER", SCREEN_WIDTH, SCREEN_HEIGHT, Board::BOARD_OFFSET, _delay * 50); }

    return Result::GAME_FINISHED;
}