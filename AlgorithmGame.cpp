#include "AlgorithmGame.h"

AlgorithmGame::AlgorithmGame(Player &playerA,
                             Player &playerB,
                             AbstractPlayer &moverA,
                             AbstractPlayer &moverB,
                             unsigned int delay,
                             bool quiet,
                             const string &filename)
        : _playerA(playerA),
          _playerB(playerB),
          _moverA(moverA),
          _moverB(moverB),
          _delay(delay),
          _quiet(quiet),
          _board(ProgramArgs::BoardSource::FILE),
          _aData(1, _board, *this),
          _bData(2, _board, *this) {
    list<pair<Point, Board::Type>> boardList;
    list<pair<Point, char>> pawnList;

    ifstream file(filename);

    map<char, unsigned int> charCount;

    for (int row = 0; row < Board::BOARD_SIZE; row++) {
        string line = readLine(file);

        unsigned int lineLength = min<unsigned int>((unsigned int)line.length(), Board::BOARD_SIZE);

        for (unsigned int col = 0; col < lineLength; col++) {
            switch (line[col]) {
                case ' ':
                    break;
                case 'T': case 'S':
                    boardList.push_back(pair<Point, Board::Type>(Point(col, row),
                                                                 (line[col] == 'T')? Board::Type::FR : Board::Type::SEA));
                    break;
                case 'A': case 'B':
                    boardList.push_back(pair<Point, Board::Type>(Point(col, row),
                                                                 (line[col] == 'A')? Board::Type::FLGA : Board::Type::FLGB));
                    break;
                case '1': case '2': case '3': case '7': case '8': case '9':
                    pawnList.push_back(pair<Point, char>(Point(col, row), line[col]));
                    break;
                default:
                    break;
            }

            charCount[line[col]]++;
        }
    }

    _errorFlag = errorCheck(charCount, filename);

    _board.setCells(boardList);
    initPawns(pawnList);

    //TODO: _moverA.init()
    //TODO: _moberB.init()
}

Player::Side AlgorithmGame::checkVictory(const Pawn &pw) {
    if (_board.getCellType(pw.getPosition()) == Board::Type::FLGA) {
        _playerB.increaseScore();
        return Player::Side::B;
    }

    if (_board.getCellType(pw.getPosition()) == Board::Type::FLGB) {
        _playerA.increaseScore();
        return Player::Side::A;
    }

    if (!(_aPawns[0].isAlive() || _aPawns[1].isAlive() || _aPawns[2].isAlive())) {
        _playerB.increaseScore();
        return Player::Side::B;
    }

    if (!(_bPawns[0].isAlive() || _bPawns[1].isAlive() || _bPawns[2].isAlive())) {
        _playerA.increaseScore();
        return Player::Side::A;
    }

    return Player::Side::ANY;
}

void AlgorithmGame::movePawn(Pawn &pawn, Player::Side player, const Point &pt) {
    if (pawn.isAlive()) {
        Board::Type nextCellType = _board.getCellType(pt);

        if (pawn.canMove(nextCellType) && !hasPawn(pt, player)) {
            if (!_quiet) { _board.drawCell(pawn.getPosition()); }

            pawn.move(pt);

            if (!_quiet) { pawn.draw(_board.getCellColor(nextCellType)); }

            // Check for opposite player pawns in the same position
            if (hasPawn(pt, (Player::Side)(((int)player + 1) % 2))) {
                Pawn &enemy = getPawn(pt, (Player::Side)(((int)player + 1) % 2));

                Pawn::duel(pawn, enemy);

                if (!_quiet && enemy.isAlive()) {
                    enemy.draw(_board.getCellColor(nextCellType));
                }
            }
        }
    }
}

void AlgorithmGame::draw() const {
    hideCursor();
    clearScreen();

    drawScores();
    _board.draw();

    for (const Pawn &pw : _aPawns) {
        pw.draw(_board.getCellColor(Board::Type::EMP));
    }
    for (const Pawn &pw : _bPawns) {
        pw.draw(_board.getCellColor(Board::Type::EMP));
    }
}

void AlgorithmGame::drawScores() const {
    int aColor = _board.getCellColor(Board::Type::FLGA);
    int bColor = _board.getCellColor(Board::Type::FLGB);

    gotoxy(SCREEN_START, SCREEN_START);

    setTextColor(aColor, BLACK);
    cout << _playerA.getName() << ": ";
    resetTextColor();
    cout << _playerA.getScore();

    int len = 1, temp = _playerB.getScore();
    while (temp /= 10) len++;
    len += 2 + _playerB.getName().length();

    gotoxy(SCREEN_WIDTH - len, SCREEN_START);

    setTextColor(bColor, BLACK);
    cout << _playerB.getName() << ": ";
    resetTextColor();
    cout << _playerB.getScore();

    cout << flush;
}

bool AlgorithmGame::hasPawn(const Point &pt, Player::Side player) const {
    if (player == Player::Side::A || player == Player::Side::ANY) {
        for (const Pawn &pw : _aPawns) {
            if (pt == pw.getPosition() && pw.isAlive()) {
                return true;
            }
        }
    }

    if (player == Player::Side::B || player == Player::Side::ANY) {
        for (const Pawn &pw : _bPawns) {
            if (pt == pw.getPosition() && pw.isAlive()) {
                return true;
            }
        }
    }

    return false;
}

Pawn &AlgorithmGame::getPawn(const Point &pt, Player::Side player) {
    // Will only get called if we're sure there's a pawn to retrieve
    // hence the warning
    if (player == Player::Side::A) {
        for (Pawn &pw : _aPawns) {
            if (pt == pw.getPosition() && pw.isAlive()) {
                return pw;
            }
        }
    }
    else {
        for (Pawn &pw : _bPawns) {
            if (pt == pw.getPosition() && pw.isAlive()) {
                return pw;
            }
        }
    }
}

Point AlgorithmGame::getValidPawnPosition() const {
    Point p;

    do {
        p = _board.getRandomEmptyPoint();
    } while (hasPawn(p));

    return p;
}

void AlgorithmGame::initPawns() {
    int aColor = _board.getCellColor(Board::Type::FLGA);
    int bColor = _board.getCellColor(Board::Type::FLGB);

    _aPawns[0] = Pawn(getValidPawnPosition(), '1', aColor);
    _aPawns[1] = Pawn(getValidPawnPosition(), '2', aColor, true, true);
    _aPawns[2] = Pawn(getValidPawnPosition(), '3', aColor, true);

    _bPawns[0] = Pawn(getValidPawnPosition(), '7', bColor, true, true);
    _bPawns[1] = Pawn(getValidPawnPosition(), '8', bColor, false, true);
    _bPawns[2] = Pawn(getValidPawnPosition(), '9', bColor);
}

void AlgorithmGame::initPawns(list<pair<Point, char>> pawnList) {
    int aColor = _board.getCellColor(Board::Type::FLGA);
    int bColor = _board.getCellColor(Board::Type::FLGB);

    for (auto p : pawnList) {
        switch (p.second) {
            case '1':
                _aPawns[0] = Pawn(p.first, '1', aColor);
                break;
            case '2':
                _aPawns[1] = Pawn(p.first, '2', aColor, true, true);
                break;
            case '3':
                _aPawns[2] = Pawn(p.first, '3', aColor, true);
                break;
            case '7':
                _bPawns[0] = Pawn(p.first, '7', bColor, true, true);
                break;
            case '8':
                _bPawns[1] = Pawn(p.first, '8', bColor, false, true);
                break;
            case '9':
                _bPawns[2] = Pawn(p.first, '9', bColor);
                break;
            default:
                break;
        }
    }
}

bool AlgorithmGame::errorCheck(map<char, unsigned int> charCount, const string &filename) {
    bool hadErrors = false;

    if (!(charCount['A'] == 1 && charCount['1'] == 1 && charCount['2'] == 1 && charCount['3'] == 1)) {
        clearScreen();
        cout << "Wrong settings for player A tools in file " << filename << endl;
        hadErrors = true;
    }

    if (!(charCount['B'] == 1 && charCount['7'] == 1 && charCount['8'] == 1 && charCount['9'] == 1)) {
        if (!hadErrors) { clearScreen(); }
        cout << "Wrong settings for player B tools in file " << filename << endl;
        hadErrors = true;
    }

    charCount.erase('A');charCount.erase('1');charCount.erase('2');charCount.erase('3');
    charCount.erase('B');charCount.erase('7');charCount.erase('8');charCount.erase('9');
    charCount.erase(' ');charCount.erase('S');charCount.erase('T');

    for (const auto &pair : charCount) {
        if (!hadErrors) { clearScreen(); }
        cout << "Wrong character on board: " << pair.first << " in file " << filename << endl;
        hadErrors = true;
    }

    return hadErrors;
}

Player::Side AlgorithmGame::handleTurn() {
    Player::Side winner = Player::Side::ANY;
    GameMove move;

    if (_turn % 2 == 0) {
        Pawn &pawn = getPawn(Point(move, true), Player::Side::A);
        movePawn(pawn, Player::Side::A, Point(move, false));
        winner = checkVictory(pawn);
    }

    else {
        Pawn &pawn = getPawn(Point(move, true), Player::Side::B);
        movePawn(pawn, Player::Side::B, Point(move, false));
        winner = checkVictory(pawn);
    }

    if (!_quiet) { Sleep(_delay); }

    ++_turn;
    return winner;
}

AlgorithmGame::Result AlgorithmGame::run(int cycle) {
    if (_errorFlag) {
        return Result::EXIT_WITH_ERRORS;
    }

    if (!_quiet) { draw(); }

    Player::Side winner = Player::Side::ANY;

    while (winner == Player::Side::ANY && _turn < ALGORITHM_TIMEOUT) {
        winner = handleTurn();
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