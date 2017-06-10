#include "AlgoPlayer.h"

void AlgoPlayer::init(const BoardData &board) {
    _bd = &board;
    int e = 0;

    for (unsigned int i = 0; i < BoardData::rows; i++) {
        for (unsigned int j = 0; j < BoardData::cols; j++) {
            _board[i][j] = _bd->charAt(j + 1, i + 1);

            if (_board[i][j] == '#') {
                _enemyPawns[e++] = Point(j, i);
            }
            else if (_player == 1 && _board[i][j] >= '1' && _board[i][j] <= '3') {
                _myPawns[_board[i][j] - '1'] = Point(j, i);
            }
            else if (_player == 2 && _board[i][j] >= '7' && _board[i][j] <= '9') {
                _myPawns[_board[i][j] - '7'] = Point(j, i);
            }
            else if (_board[i][j] == 'A') {
                (_player == 1? _myFlag : _enemyFlag) = Point(j, i);
            }
            else if (_board[i][j] == 'B') {
                (_player == 2? _myFlag : _enemyFlag) = Point(j, i);
            }
        }
    }
}