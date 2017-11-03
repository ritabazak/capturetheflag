#pragma once

#include "AlgorithmGame.h"
#include "BoardData.h"
#include "Board.h"
#include "Pawn.h"
#include "Player.h"
#include "Pawn.h"

class AlgorithmGame;

class ExtendedBoardData : public BoardData {
    int _player;
    Board &_board;
    AlgorithmGame *_game;

public:
    ExtendedBoardData(int player,
                      Board &board,
                      AlgorithmGame *game)
            : _player(player),
              _board(board),
              _game(game) { }

    char charAt(int x, int y) const override;
};