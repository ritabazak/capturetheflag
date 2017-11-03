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

Player::Side AutomaticGame::handleTurn() {
    Player::Side winner = Player::Side::ANY;

    if (_turn % 2 == 0) {
        if (_aMoves.size() && _turn == _aMoves.front().turn) {
            _aMove = _aMoves.front();
            _aMoves.pop_front();
        }

        if (_aMove.dir != Direction::STOPPED) {
            movePawn(_aPawns[_aMove.pawn - '1'], Player::Side::A, _aMove.dir);
            winner = checkVictory(_aPawns[_aMove.pawn - '1']);
        }
    }

    else {
        if (_bMoves.size() && _turn == _bMoves.front().turn) {
            _bMove = _bMoves.front();
            _bMoves.pop_front();
        }
        if (_bMove.dir != Direction::STOPPED) {
            movePawn(_bPawns[_bMove.pawn - '7'], Player::Side::B, _bMove.dir);
            winner = checkVictory(_bPawns[_bMove.pawn - '7']);
        }
    }

    if (!_quiet) { Sleep(_delay); }

    ++_turn;
    return winner;
}

BaseGame::Result AutomaticGame::run(int cycle) {
    if (BaseGame::run() == Result::EXIT_WITH_ERRORS) { return Result::EXIT_WITH_ERRORS; }

    if (!_quiet) { draw(); }

    Player::Side winner = Player::Side::ANY;

    while (_aMoves.size() || _bMoves.size() ||
           _aMove.dir != Direction::STOPPED ||
           _bMove.dir != Direction::STOPPED) {
        if ((winner = handleTurn()) != Player::Side::ANY) {
            break;
        }
    }

    if (!_quiet) { displayMessage("GAME OVER", SCREEN_WIDTH, SCREEN_HEIGHT, Board::BOARD_OFFSET, _delay * 50); }
    else if (_turn) {
        string winnerStr = "NONE";
        if (winner != Player::Side::ANY) {
            winnerStr = winner == Player::Side::A ? "A" : "B";
        }

        cout << "Game cycle: " << cycle << endl;
        cout << "Num moves: " << _turn << endl;
        cout << "Winner: " << winnerStr << endl << endl;
    }

    return Result::GAME_FINISHED;
}