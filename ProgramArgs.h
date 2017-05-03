#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

using namespace std;

class ProgramArgs {
public:
    enum class BoardSource { RANDOM, FILE };
    enum class MovesSource { KEYBOARD, FILE };

private:
    BoardSource _boardSource;
    MovesSource _movesSource;
    string _path;
    unsigned int _delay;
    bool _quiet;

    ProgramArgs()
            : _boardSource(BoardSource::RANDOM),
              _movesSource(MovesSource::KEYBOARD),
              _delay(20),
              _quiet(false) {
        char path[255];
        getcwd(path, 255);
        _path = path;
    }

public:
    ProgramArgs(char *argv[], int size);

    BoardSource boardSource() const { return _boardSource; }
    MovesSource movesSource() const { return _movesSource; }
    string path() const { return _path; }
    unsigned int delay() const { return _delay; }
    bool quiet() const { return _quiet; }
};