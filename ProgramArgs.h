#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Utils.h"

using namespace std;

class ProgramArgs{
public:
    enum class BoardSource { RANDOM, FILE };
    enum class MovesSource { KEYBOARD, FILE};

private:
    BoardSource _boardSource;
    MovesSource _movesSource;
    string _path;
    unsigned int _delay;
    bool _quiet;

    ProgramArgs();

public:
    ProgramArgs(char *argv[], int size);

    BoardSource boardSource() const { return _boardSource; }
    MovesSource movesSource() const { return _movesSource; }
    string path() const { return _path; }
    unsigned int delay() const { return _delay; }
    bool quiet() const { return _quiet; }
};
