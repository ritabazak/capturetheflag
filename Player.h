#pragma once

#include <string>
#include "Direction.h"

using namespace std;

class Player {
    int _score;
    string _name;

    int setScore(int score) { return _score = score; }

public:
    enum {ANY=-1, A, B};

    Player(const string name, int score = 0)
            : _name(name), _score(score) {}

    const int getScore() const { return _score; }
    const string getName() const { return _name; }
    void setName(const string name) { _name = name; }
    int resetScore() { return setScore(0); }
    int increaseScore() { return setScore(_score + 1); }
};