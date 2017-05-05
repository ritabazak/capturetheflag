#include "PlayerInput.h"

Direction PlayerInput::isOwnMove(char ch) const {
    for (int i = 0; i < _moveKeys.length(); i++) {
        if (_moveKeys[i] == ch) {
            switch (i) {
                case 0:
                    return Direction::UP;
                case 1:
                    return Direction::DOWN;
                case 2:
                    return Direction::LEFT;
                case 3:
                    return Direction::RIGHT;
            }
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