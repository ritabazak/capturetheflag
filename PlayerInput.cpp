#include "PlayerInput.h"

Direction PlayerInput::isOwnMove(char ch) const {
    for (int i = 0; i < _moveKeys.length(); i++) {
        if (_moveKeys[i] == ch) {
            return (Direction)i;
        }
    }

    return Direction::STOPPED;
}

int PlayerInput::isOwnPawn(char ch) const {
    for (int i = 0; i < _pawnKeys.length(); i++) {
        if (_pawnKeys[i] == ch) {
            return i;
        }
    }

    return -1;
}