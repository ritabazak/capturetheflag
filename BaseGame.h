#pragma once

#include "Board.h"
#include "Pawn.h"
#include "Player.h"
#include <fstream>

class BaseGame {
public:
    enum class Result { GAME_CONTINUED, GAME_RESTARTED, GAME_FINISHED, EXIT_TO_MAIN_MENU, EXIT };

protected:
    Board _board;
    Pawn _aPawns[3], _bPawns[3];
    Player &_playerA, &_playerB;

    bool hasPawn(const Point &pt, int player = Player::ANY) const;
    Pawn &getPawn(const Point &pt, int player);
    Point getValidPawnPosition() const;
    void initPawns();
    void initPawns(list<pair<Point, char>> pawnList);
    void draw() const;
    void drawScores() const;
    void movePawn(Pawn &pawn, int player, Direction dir);
    bool checkVictory(const Pawn &pw);
    void displayMessage(const string &message, int seconds) const;

public:
    BaseGame(Player &playerA, Player &playerB)
            : _playerA(playerA), _playerB(playerB) {
        initPawns();
    }

    BaseGame(Player &playerA, Player &playerB, const string &filename);
};