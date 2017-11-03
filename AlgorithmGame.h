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
    enum { ALGORITHM_TIMEOUT = 1250 };
    Player &_playerA, &_playerB;
    AbstractPlayer &_moverA, &_moverB;
    BoardData &_aData, &_bData;
    Pawn _aPawns[3], _bPawns[3];
    Board _board;
    bool _quiet = false;
    unsigned int _delay;
    unsigned int _turn = 0;
    bool _errorFlag = false;
    GameMove _lastMove;

    void readBoardFile(const string filename);
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
                  bool quiet);

    // Board from file
    AlgorithmGame(Player &playerA,
                  Player &playerB,
                  AbstractPlayer &moverA,
                  AbstractPlayer &moverB,
                  unsigned int delay,
                  bool quiet,
                  const string &filename);

    ~AlgorithmGame() {
        delete &_aData;
        delete &_bData;
    };

    bool hasPawn(const Point &pt, Player::Side player = Player::Side::ANY) const;
    Pawn &getPawn(const Point &pt, Player::Side player);
    Result run(int cycle);
};