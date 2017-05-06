#pragma once

#include "Board.h"
#include "Pawn.h"
#include "Player.h"
#include <fstream>

class BaseGame {
public:
    enum class Result { GAME_CONTINUED, GAME_RESTARTED, GAME_FINISHED, EXIT_TO_MAIN_MENU, EXIT };

private:
    Player &_playerA, &_playerB;

    bool hasPawn(const Point &pt, int player = Player::ANY) const;
    Pawn &getPawn(const Point &pt, int player);
    Point getValidPawnPosition() const;
    void initPawns();
    void initPawns(list<pair<Point, char>> pawnList);
    void drawScores() const;

protected:
    Board _board;
    Pawn _aPawns[3], _bPawns[3];
    unsigned int _delay;
    bool _quiet = false;
    unsigned int _turn = 0;

    void draw() const;
    void displayMessage(const string &message, unsigned int seconds) const;
    void movePawn(Pawn &pawn, int player, Direction &dir);
    bool checkVictory(const Pawn &pw);

public:
    BaseGame(Player &playerA,
             Player &playerB,
             unsigned int delay)
            : _playerA(playerA),
              _playerB(playerB),
              _delay(delay) {
        initPawns();
    }

    BaseGame(Player &playerA,
             Player &playerB,
             unsigned int delay,
             const string &filename);
};