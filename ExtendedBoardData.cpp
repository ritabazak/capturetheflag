#include "ExtendedBoardData.h"

char ExtendedBoardData::charAt(int x, int y) const {
    //if enemy pawn
    if (_game->hasPawn(Point(x - 1, y - 1), (Player::Side)(_player % 2))) {
        return '#';
    }
    //if my pawn
    if (_game->hasPawn(Point(x - 1, y - 1), (Player::Side)(_player - 1))) {
        return _game->getPawn(Point(x - 1, y - 1), (Player::Side)(_player - 1)).getKey();
    }
    //if no pawns
    switch (_board.getCellType(Point(x - 1, y - 1))) {
    case Board::Type::FLGA:
        return 'A';
    case Board::Type::FLGB:
        return 'B';
    case Board::Type::FR:
        return 'T';
    case Board::Type::SEA:
        return 'S';
        //Board::Type::EMP
    default:
        return ' ';
    }
}