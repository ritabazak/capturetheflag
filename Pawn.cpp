#include "Pawn.h"

void Pawn::draw(int backColor) const {
    gotoxy(_pos.getX() * (Board::CELL_SIZE + 1) + 1,
           _pos.getY() * 2 + Board::BOARD_OFFSET + 1);

    setTextColor(_color, backColor);
    cout << " " << _key << " " << flush;
    resetTextColor();
}

void Pawn::duel(Pawn &a, Pawn &b) {
    if (a.whichPlayer() == Player::Side::B) {
        return duel(b, a);
    }

    Player::Side winner = Player::Side::A;

    int x = a._pos.getX(), y = a._pos.getY();

    if (a._key == '1') {
        if (x == 3 || (y >= 9 && y <= 12)) {
            winner = Player::Side::B;
        }
    }
    else if (a._key == '2') {
        if (b._key == '9' || (x != 10 && y != 2 && y != 3)) {
            winner = Player::Side::B;
        }
    }
    else if (a._key == '3') {
        if (x != 6 && y != 7) {
            winner = Player::Side::B;
        }
    }

    a._alive = winner == Player::Side::A;
    b._alive = winner == Player::Side::B;
}