#include "AlgorithmRegistration.h"

map<string, std::function<AbstractPlayer*(void)>> AlgorithmRegistration::algoFactory;