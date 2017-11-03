#include "AlgoPlayer_304824170_318110376.h"

void AlgoPlayer_304824170_318110376::init(const BoardData &board) {
    _bd = &board;
    int e = 0;
    _myLastMove = GameMove(0, 0, 0, 0);

    for (unsigned int i = 0; i < BoardData::rows; i++) {
        for (unsigned int j = 0; j < BoardData::cols; j++) {
            char temp = _bd->charAt(j + 1, i + 1);

            if (temp == '#') {
                _enemyPawns[e++] = PlayerPawn(temp, Point(j, i));
                _board[i][j] = ' ';
            }
            else if (_player == 1 && temp >= '1' && temp <= '3') {
                _myPawns[temp - '1'] = PlayerPawn(temp, Point(j, i));
                _board[i][j] = ' ';
            }
            else if (_player == 2 && temp >= '7' && temp <= '9') {
                _myPawns[temp - '7'] = PlayerPawn(temp, Point(j, i));
                _board[i][j] = ' ';
            }
            else {
                _board[i][j] = temp;

                if (_board[i][j] == 'A') {
                    (_player == 1 ? _myFlag : _enemyFlag) = Point(j, i);
                }
                else if (_board[i][j] == 'B') {
                    (_player == 2 ? _myFlag : _enemyFlag) = Point(j, i);
                }
            }
        }
    }
}

GameMove AlgoPlayer_304824170_318110376::play(const GameMove& opponentsMove) {
    updateGameState(opponentsMove);
    PossibleMove bestMove = getBestMove();

    _myLastMove = GameMove(bestMove.pawn.pos.getX() + 1,
                           bestMove.pawn.pos.getY() + 1,
                           bestMove.destination.getX() + 1,
                           bestMove.destination.getY() + 1);

    return _myLastMove;
}

AlgoPlayer_304824170_318110376::PossibleMove AlgoPlayer_304824170_318110376::getBestMove() {
    vector<PossibleMove> moves = getAllPossibleMoves();

    if (moves.empty()) {
        for (int i = 0; i < 3; i++) {
            if (_myPawns[i].pos.getX() != -1) {
                return PossibleMove(_myPawns[i], _myPawns[i].pos);
            }
        }
    }

    int maxIndex = 0;

    for (int i = 1; i < moves.size(); i++) {
        if (moves[i].score > moves[maxIndex].score) {
            maxIndex = i;
        }
    }

    return moves[maxIndex];
}

void AlgoPlayer_304824170_318110376::calculateMoveScore(PossibleMove &move) const {
    int flagScore = getFlagScore(move);
    int attackScore = getAttackScore(move);

    if (flagScore == 100) {
        move.score = 100;
    }
    else if (attackScore == 0) {
        move.score = 0;
    }
    else {
        move.score = (int)(flagScore * _flagLevel + attackScore * _attackLevel);
        if (Point(_myLastMove, true) == move.destination) {
            move.score *= 0.5;
        }
    }
}

int AlgoPlayer_304824170_318110376::getFlagScore(const PossibleMove &move) const {
    int distance = move.destination.distance(_enemyFlag);
    return (MAX_DISTANCE - distance) * 100 / (double)MAX_DISTANCE;
}

int AlgoPlayer_304824170_318110376::getAttackScore(const PossibleMove &move) const {
    int minDistance = MAX_DISTANCE;
    int pawnIndex;
    for (int i = 0; i < 3; i++) {
        if (_enemyPawns[i].pos.getX() != -1) {
            int dist = move.destination.distance(_enemyPawns[i].pos);
            if (dist < minDistance) {
                pawnIndex = i;
                minDistance = dist;
            }
        }
    }
    int distanceScore = (MAX_DISTANCE - minDistance) * 100 / (double)MAX_DISTANCE;
    int defeatScore = getDefeatScore(_enemyPawns[pawnIndex].pos, move.pawn.key);

    // Bad but not immediate death
    if (distanceScore && !defeatScore) return 1;

    return (int)(distanceScore * defeatScore / 100.0);
}

int AlgoPlayer_304824170_318110376::getDefeatScore(const Point &enemyPos, char key) const {
    int x = enemyPos.getX() + 1;
    int y = enemyPos.getY() + 1;

    if (_player == 1) {
        switch (key) {
            case '1':
                return (x != 4 && (y >= 1 && y <= 9)) * 100;
            case '2':
                // 1/3 of a chance of facing '9' and certain death
                return (int)((x == 11 || (y == 3 || y == 4)) * 2 / 3.0 * 100);
            case '3':
            default:
                return (x == 7 || y == 8) * 100;
        }
    }
    else {
        switch (key) {
            case '7':
            case '8':
                return (
                               (x != 7 && x != 11 && y >= 10 && y <= 13) ||
                               (x == 4 && (y == 1 || y == 2 || (y >= 5 && y <= 13 && y != 8)))
                       ) * 100;
            case '9':
            default:
                // 1/3 of a chance of facing '2' and certain victory
                return (int)((1 / 3.0 + 2 / 3.0 * ((x != 7 && y >= 10 && y <= 13) || (x == 4 && y != 8))) * 100);
        }
    }
}

vector<AlgoPlayer_304824170_318110376::PossibleMove> AlgoPlayer_304824170_318110376::getAllPossibleMoves() {
    vector<PossibleMove> moves;

    for (int i = 0; i < 3; i++) {
        if (_myPawns[i].pos.getX() != -1) {
            addPossibleMoves(moves, _myPawns[i]);
        }
    }

    return moves;
}

void AlgoPlayer_304824170_318110376::addPossibleMoves(vector<PossibleMove> &moves, PlayerPawn &pawn) const {
    Point up(pawn.pos.getX(), pawn.pos.getY() - 1);
    Point down(pawn.pos.getX(), pawn.pos.getY() + 1);
    Point left(pawn.pos.getX() - 1, pawn.pos.getY());
    Point right(pawn.pos.getX() + 1, pawn.pos.getY());

    if (canMove(pawn, up)) {
        moves.push_back(PossibleMove(pawn, up));
        calculateMoveScore(moves.back());
    }
    if (canMove(pawn, down)) {
        moves.push_back(PossibleMove(pawn, down));
        calculateMoveScore(moves.back());
    }
    if (canMove(pawn, left)) {
        moves.push_back(PossibleMove(pawn, left));
        calculateMoveScore(moves.back());
    }
    if (canMove(pawn, right)) {
        moves.push_back(PossibleMove(pawn, right));
        calculateMoveScore(moves.back());
    }
}

void AlgoPlayer_304824170_318110376::updateGameState(const GameMove &opponentsMove) {
    if (_myLastMove.from_x) {
        char from = _bd->charAt(_myLastMove.from_x, _myLastMove.from_y);
        char to = _bd->charAt(_myLastMove.to_x, _myLastMove.to_y);

        PlayerPawn &pawn = _myPawns[findByPosition(_player, Point(_myLastMove, true))];

        if (from != pawn.key) {//if moved
            if (to == pawn.key) {//if arrived
                pawn.pos = Point(_myLastMove, false);

                int enemyIndex = findByPosition(_player % 2 + 1, Point(_myLastMove, false));
                if (enemyIndex != -1) {//if arrived&killed
                    _enemyPawns[enemyIndex].pos = Point();
                }
            }
            else {// not arrived
                pawn.pos = Point();
            }
        }
    }

    if (opponentsMove.from_x) {
        char from = _bd->charAt(opponentsMove.from_x, opponentsMove.from_y);
        char to = _bd->charAt(opponentsMove.to_x, opponentsMove.to_y);

        if (from != '#') {// he moved
            if (to == '#') {// he didn't die
                int pawnIndex = findByPosition(_player, Point(opponentsMove, false));
                if (pawnIndex != -1) {// he killed one of my pawns!
                    _myPawns[pawnIndex].pos = Point();
                }

                _enemyPawns[findByPosition(_player % 2 + 1, Point(opponentsMove, true))].pos = Point(opponentsMove,
                                                                                                     false);
            }
            else {// not arrived
                _enemyPawns[findByPosition(_player % 2 + 1, Point(opponentsMove, true))].pos = Point();
            }
        }
    }
}

bool AlgoPlayer_304824170_318110376::canMove(const PlayerPawn& pawn, const Point &dest) const {
    if (dest.getX() < 0 || dest.getY() < 0 ||
        dest.getX() >= BoardData::cols || dest.getY() >= BoardData::rows) {
        return false;
    }

    char type = _board[dest.getY()][dest.getX()];

    if (type == ' ' || (type == 'S' && canSwim(pawn)) || (type == 'T' && canClimbTrees(pawn))) {
        return findByPosition(_player, dest) == -1;
    }

    return (_player == 1 && type == 'B') || (_player == 2 && type == 'A');
}

int AlgoPlayer_304824170_318110376::findByPosition(int player, const Point &pt) const {
//assuming there ius actually a pawn there
    if (player == _player) {
        for (int i = 0; i < 3; i++) {
            if (_myPawns[i].pos == pt) {
                return i;
            }
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (_enemyPawns[i].pos == pt) {
                return i;
            }
        }
    }

    return -1;
}

bool AlgoPlayer_304824170_318110376::canSwim(const PlayerPawn &pawn) const {
    int pawnIndex = (_player == 1) ? pawn.key - '1' : pawn.key - '7';
    return (_player == 1 && pawnIndex >= 1) ||
           (_player == 2 && pawnIndex == 0);
}

bool AlgoPlayer_304824170_318110376::canClimbTrees(const PlayerPawn &pawn) const {
    int pawnIndex = (_player == 1) ? pawn.key - '1' : pawn.key - '7';
    return (_player == 1 && pawnIndex == 1) ||
           (_player == 2 && pawnIndex <= 1);
}