#pragma once

#include <string>
#include "Direction.h"
#include "Player.h"

class PlayerInput {
    const string _moveKeys;
    const string _pawnKeys;

    int _pawnSelect = -1;
    int _tempSelect = -1;
    Direction _dirSelect = Direction::STOPPED;

    Direction isOwnMove(char ch) const;
    int isOwnPawn(char ch) const;

public:
    PlayerInput(const string moveKeys, const string pawnKeys)
            : _moveKeys(moveKeys), _pawnKeys(pawnKeys) {}

    void handleKeyInput(char input) {
        int tempPawn;
        Direction tempDir;

        if ((tempPawn = isOwnPawn(input)) != -1) {
            _tempSelect = tempPawn;
        }
        else if (_tempSelect != -1 && (tempDir = isOwnMove(input)) != Direction::STOPPED) {
            _pawnSelect = _tempSelect;
            _dirSelect = tempDir;
        }
    }

    int getPawn() const { return _pawnSelect; }
    Direction &getDirection() { return _dirSelect; }
    bool hasSelection() const { return _pawnSelect != -1 && _dirSelect != Direction::STOPPED; }
};