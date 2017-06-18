#include "ProgramArgs.h"
#include "Utils.h"
#include "CTFManager.h"
#include "AlgoPlayer.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    AlgorithmRegistration algo_1_304824170_318110376("algo_1_304824170_318110376", [] { return new AlgoPlayer(0.1, 0.9); });
    AlgorithmRegistration algo_2_304824170_318110376("algo_2_304824170_318110376", [] { return new AlgoPlayer(0.6, 0.4); });

    randomSeed();

    CTFManager(ProgramArgs(argv + 1, argc - 1)).run();
    return 0;
}