#pragma once

#include "BoardData.h"
#include "Board.h"
#include "Pawn.h"
#include "AlgorithmGame.h"

class AlgorithmGame;

class ExtendedBoardData : public BoardData {
    int _player;
    Board &_board;
    AlgorithmGame &_game;

public:
    //TODO: Do this right
    virtual ~ExtendedBoardData() { }

    ExtendedBoardData(int player,
                      Board &board,
                      AlgorithmGame &game)
            : _player(player),
              _board(board),
              _game(game) { }

    char charAt(int x, int y) const override {
        Board::Type type = _game.getPawn
    }
};