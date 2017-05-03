#include "ProgramArgs.h"
#include "CTFManager.h"

int main(int argc, char *argv[]) {
    CTFManager(ProgramArgs(argv + 1, argc - 1)).run();
    return 0;
}