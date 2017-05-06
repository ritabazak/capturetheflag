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

    cout << (char)(char)BoxCharacters::CORNER_TL;
    for (int col = 1; col < BOARD_SIZE * (CELL_SIZE +1); col++) {
        cout << ((col % 4)? (char)BoxCharacters::HORIZONTAL : (char)BoxCharacters::HORIZONTAL_DOWN);
    }
    cout << (char)BoxCharacters::CORNER_TR << endl;

    for (int row = 0; row < BOARD_SIZE; row++) {
        cout << (char)BoxCharacters::VERTICAL;
        for (int col = 0; col < BOARD_SIZE - 1; col++) {
            cout << "   " << (char)BoxCharacters::VERTICAL_THIN;
        }
        cout << "   " << (char)BoxCharacters::VERTICAL << endl;

        cout << ((row == BOARD_SIZE - 1)? (char)BoxCharacters::CORNER_BL : (char)BoxCharacters::VERTICAL_RIGHT);
        for (int col = 1; col < BOARD_SIZE * (CELL_SIZE + 1); col++) {
            if (row == BOARD_SIZE - 1) {
                cout << ((col % 4) ? (char)BoxCharacters::HORIZONTAL : (char)BoxCharacters::HORIZONTAL_UP);
            }
            else {
                cout << ((col % 4) ? (char)BoxCharacters::HORIZONTAL_THIN : (char)BoxCharacters::PLUS_THIN);
            }
        }
        cout << ((row == BOARD_SIZE - 1)? (char)BoxCharacters::CORNER_BR : (char)BoxCharacters::VERTICAL_LEFT) << endl;
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

array<array<char, Board::BOARD_SIZE>, Board::BOARD_SIZE> Board::generateCharArray() {
    array<array<char, Board::BOARD_SIZE>, Board::BOARD_SIZE> boardArray;

    for (int row = 0; row < Board::BOARD_SIZE; row++) {
        for (int col = 0; col < Board::BOARD_SIZE; col++) {
            switch (_board[row][col]) {
                case Type::FR:
                    boardArray[row][col] = 'T';
                    break;
                case Type::SEA:
                    boardArray[row][col] = 'S';
                    break;
                case Type::FLGA:
                    boardArray[row][col] = 'A';
                    break;
                case Type::FLGB:
                    boardArray[row][col] = 'B';
                    break;
                default:
                    boardArray[row][col] = ' ';
            }
        }
    }

    return boardArray;
}