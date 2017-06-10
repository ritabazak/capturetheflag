#pragma once

#include <map>
#include "Point.h"
#include "Player.h"
#include "Pawn.h"
#include "GameMove.h"
#include "AbstractPlayer.h"
#include "ExtendedBoardData.h"

class AlgorithmGame {
public:
    enum class Result { GAME_FINISHED, EXIT_WITH_ERRORS };

private:
    enum { ALGORITHM_TIMEOUT=50 };
    Player &_playerA, &_playerB;
    AbstractPlayer &_moverA, &_moverB;
    ExtendedBoardData _aData, _bData;
    Pawn _aPawns[3], _bPawns[3];
    Board _board;
    bool _quiet = false;
    unsigned int _delay;
    unsigned int _turn = 0;
    bool _errorFlag = false;

    Point getValidPawnPosition() const;
    void initPawns();
    void initPawns(list<pair<Point, char>> pawnList);
    void drawScores() const;
    bool errorCheck(map<char, unsigned int> charCount, const string &filename);
    void draw() const;
    void movePawn(Pawn &pawn, Player::Side player, const Point &pt);
    Player::Side checkVictory(const Pawn &pw);
    Player::Side handleTurn();

public:
    // Random board
    AlgorithmGame(Player &playerA,
                  Player &playerB,
                  AbstractPlayer &moverA,
                  AbstractPlayer &moverB,
                  unsigned int delay,
                  bool quiet)
            : _playerA(playerA),
              _playerB(playerB),
              _moverA(moverA),
              _moverB(moverB),
              _aData(1, _board, *this),
              _bData(2, _board, *this),
              _delay(delay),
              _quiet(quiet) {
        initPawns();

        //TODO: _moverA.init()
        //TODO: _moberB.init()
    }

    // Board from file
    AlgorithmGame(Player &playerA,
                  Player &playerB,
                  AbstractPlayer &moverA,
                  AbstractPlayer &moverB,
                  unsigned int delay,
                  bool quiet,
                  const string &filename);

    bool hasPawn(const Point &pt, Player::Side player = Player::Side::ANY) const;
    Pawn &getPawn(const Point &pt, Player::Side player);
    Result run(int cycle);
};