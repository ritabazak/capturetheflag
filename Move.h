#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include "Direction.h"
#include "PlayerInput.h"

using namespace std;

struct Move {
    unsigned int turn;
    char pawn;
    Direction dir;

    Move(): dir(Direction::STOPPED) {}

    Move(unsigned int _turn, const PlayerInput &input)
            : turn(_turn), pawn(input.getPawnKey()), dir(input.getDirection()) { }

    Move(string line) {
        string turnStr = line.substr(0, line.find(","));
        stringstream(turnStr) >> turn;

        line.erase(0, line.find(",") + 1);

        string pawnStr = line.substr(0, line.find(","));
        stringstream(pawnStr) >> pawnStr;
        pawn = pawnStr[0];

        line.erase(0, line.find(",") + 1);

        string dirStr = line;
        stringstream(dirStr) >> dirStr;
        dir = (Direction)dirStr[0];
    }

    bool operator==(const Move &otherMove) {
        return pawn == otherMove.pawn && dir == otherMove.dir;
    }

    bool operator!=(const Move &otherMove) {
        return !(*this == otherMove);
    }

    void writeToFile(ofstream &file) {
        file << turn << ',' << pawn << ',' << (char)dir << endl;
    }
};