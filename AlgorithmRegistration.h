#pragma once
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "AbstractPlayer.h"

using namespace std;

class AlgorithmRegistration {
public:
    AlgorithmRegistration(const string& id, std::function<AbstractPlayer*(void)> func) {
        algoFactory[id] = func;
    }

    static map<string, std::function<AbstractPlayer*(void)>> algoFactory;
};
