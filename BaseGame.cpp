#include "BaseGame.h"

BaseGame::BaseGame(Player &playerA,
                   Player &playerB,
                   unsigned int delay,
                   const string &filename)
        : _playerA(playerA),
          _playerB(playerB),
          _delay(delay),
          _board(ProgramArgs::BoardSource::FILE) {
    list<pair<Point, Board::Type>> boardList;
    list<pair<Point, char>> pawnList;

    ifstream file(filename);

    for (int row = 0; row < Board::BOARD_SIZE; row++) {
        string line = readLine(file);

        unsigned int lineLength = min<unsigned int>((unsigned int)line.length(), Board::BOARD_SIZE);

        for (int col = 0; col < lineLength; col++) {
            switch (line[col]) {
                case 'S':
                    boardList.push_back(pair<Point, Board::Type>(Point(col, row), Board::Type::SEA));
                    break;
                case 'T':
                    boardList.push_back(pair<Point, Board::Type>(Point(col, row), Board::Type::FR));
                    break;
                case ' ':
                    break;
                case 'A':
                    boardList.push_back(pair<Point, Board::Type>(Point(col, row), Board::Type::FLGA));
                    break;
                case 'B':
                    boardList.push_back(pair<Point, Board::Type>(Point(col, row), Board::Type::FLGB));
                    break;
                case '1':
                case '2':
                case '3':
                case '7':
                case '8':
                case '9':
                    pawnList.push_back(pair<Point, char>(Point(col, row), line[col]));
                    break;
                default:
                    //ERROR
                    break;
            }
        }
    }

    _board.setCells(boardList);
    initPawns(pawnList);
}

bool BaseGame::checkVictory(const Pawn &pw) {
    if (_board.getCellType(pw.getPosition()) == Board::Type::FLGA) {
        _playerB.increaseScore();
        return true;
    }

    if (_board.getCellType(pw.getPosition()) == Board::Type::FLGB) {
        _playerA.increaseScore();
        return true;
    }

    if (!(_aPawns[0].isAlive() || _aPawns[1].isAlive() || _aPawns[2].isAlive())) {
        _playerB.increaseScore();
        return true;
    }

    if (!(_bPawns[0].isAlive() || _bPawns[1].isAlive() || _bPawns[2].isAlive())) {
        _playerA.increaseScore();
        return true;
    }

    return false;
}

void BaseGame::movePawn(Pawn &pawn, int player, Direction &dir) {
    if (pawn.isAlive()) {
        Board::Type nextCellType = _board.getCellType(pawn.getPosition().getNext(dir));

        if (pawn.canMove(nextCellType) && !hasPawn(pawn.getPosition().getNext(dir), player)) {
            if (!_quiet) { _board.drawCell(pawn.getPosition()); }

            pawn.move(dir);

            if (!_quiet) { pawn.draw(_board.getCellColor(nextCellType)); }

            if (hasPawn(pawn.getPosition(), (player + 1) % 2)) { // Check for opposite player pawns
                Pawn &enemy = getPawn(pawn.getPosition(), (player + 1) % 2);

                Pawn::duel(pawn, enemy);

                if (!_quiet && enemy.isAlive()) {
                    enemy.draw(_board.getCellColor(nextCellType));
                }
            }
        }
        else {
            dir = Direction::STOPPED;
        }
    }
    else {
        dir = Direction::STOPPED;
    }
}

void BaseGame::draw() const {
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

void BaseGame::drawScores() const {
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

bool BaseGame::hasPawn(const Point &pt, int player) const {
    if (player == Player::A || player == Player::ANY) {
        for (const Pawn &pw : _aPawns) {
            if (pt == pw.getPosition() && pw.isAlive()) {
                return true;
            }
        }
    }

    if (player == Player::B || player == Player::ANY) {
        for (const Pawn &pw : _bPawns) {
            if (pt == pw.getPosition() && pw.isAlive()) {
                return true;
            }
        }
    }

    return false;
}

Pawn &BaseGame::getPawn(const Point &pt, int player) {
    if (player == Player::A) {
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

Point BaseGame::getValidPawnPosition() const {
    Point p;

    do {
        p = _board.getRandomEmptyPoint();
    } while (hasPawn(p));

    return p;
}

void BaseGame::initPawns() {
    int aColor = _board.getCellColor(Board::Type::FLGA);
    int bColor = _board.getCellColor(Board::Type::FLGB);

    _aPawns[0] = Pawn(getValidPawnPosition(), '1', aColor);
    _aPawns[1] = Pawn(getValidPawnPosition(), '2', aColor, true, true);
    _aPawns[2] = Pawn(getValidPawnPosition(), '3', aColor, true);

    _bPawns[0] = Pawn(getValidPawnPosition(), '7', bColor, true, true);
    _bPawns[1] = Pawn(getValidPawnPosition(), '8', bColor, false, true);
    _bPawns[2] = Pawn(getValidPawnPosition(), '9', bColor);
}

void BaseGame::initPawns(list<pair<Point, char>> pawnList) {
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

void BaseGame::displayMessage(const string &message, unsigned int delay) const {
    int len = message.length() + 6;
    int height = 5;
    int x = SCREEN_WIDTH / 2 - len / 2;
    int y = Board::BOARD_OFFSET + SCREEN_HEIGHT / 2 - height / 2;

    setTextColor(BLACK, WHITE);
    gotoxy(x, y);
    cout << '\xC9';
    for (int i = 1; i < len - 1; i++) { cout << '\xCD'; }
    cout << '\xBB';

    gotoxy(x, y + 1);
    cout << '\xBA';
    for (int i = 1; i < len - 1; i++) { cout << ' '; }
    cout << '\xBA';

    gotoxy(x, y + 2);
    cout << "\xBA  " << message << "  \xBA";

    gotoxy(x, y + 3);
    cout << '\xBA';
    for (int i = 1; i < len - 1; i++) { cout << ' '; }
    cout << '\xBA';

    gotoxy(x, y + 4);
    cout << '\xC8';
    for (int i = 1; i < len - 1; i++) { cout << '\xCD'; }
    cout << '\xBC';

    cout << flush;
    resetTextColor();
    Sleep(delay);
}
