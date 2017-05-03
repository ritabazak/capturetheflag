#include "Board.h"

Board::Board(ProgramArgs::BoardSource source) {
    if (source == ProgramArgs::BoardSource::RANDOM) {
        randomSeed();

        getCell(getRandomEmptyPoint()) = Type::FLGA;
        getCell(getRandomEmptyPoint()) = Type::FLGB;

        for (int i = 0; i < 12; i++) {
            getCell(getRandomEmptyPoint()) = Type::SEA;
            getCell(getRandomEmptyPoint()) = Type::FR;
        }
    }
}

Point Board::getRandomEmptyPoint() const {
    Point p;

    do {
        p = Point::randomPoint(0, BOARD_SIZE - 1);
    } while (getCell(p) != Type::EMP);

    return p;
}

void Board::draw() const {
    gotoxy(SCREEN_START, BOARD_OFFSET);

    cout << '\xC9';
    for (int col = 1; col < BOARD_SIZE * (CELL_SIZE +1); col++) {
        cout << ((col % 4)? '\xCD' : '\xD1');
    }
    cout << '\xBB' << endl;

    for (int row = 0; row < BOARD_SIZE; row++) {
        cout << '\xBA';
        for (int col = 0; col < BOARD_SIZE - 1; col++) {
            cout << "   \xB3";
        }
        cout << "   \xBA" << endl;

        cout << ((row == BOARD_SIZE - 1)? '\xC8' : '\xC7');
        for (int col = 1; col < BOARD_SIZE * (CELL_SIZE + 1); col++) {
            if (row == BOARD_SIZE - 1) {
                cout << ((col % 4) ? '\xCD' : '\xCF');
            }
            else {
                cout << ((col % 4) ? '\xC4' : '\xC5');
            }
        }
        cout << ((row == BOARD_SIZE - 1)? '\xBC' : '\xB6') << endl;
    }

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            drawCell(x, y);
        }
    }
    cout << flush;
}

void Board::drawCell(int x, int y) const {
    gotoxy(SCREEN_START + 1 + x * (CELL_SIZE + 1), BOARD_OFFSET + 1 + y * 2);

    setTextColor(BLACK, getCellColor(_board[y][x]));

    cout << _typeNames[(int)_board[y][x]] << flush;

    resetTextColor();
}

void Board::setCells(list<pair<Point, Board::Type>> cellList) {
    for (auto p : cellList) {
        getCell(p.first) = p.second;
    }
}
