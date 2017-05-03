#include "ProgramArgs.h"

ProgramArgs::ProgramArgs(char **argv, int size) : ProgramArgs() {
    vector<string> args;

    for (int i = 0; i < size; i++) {
        args.push_back(string(argv[i]));
    }

    for (int i = 0; i < size; i++) {
        if (args[i] == "-board") {
            i++;
            if (args[i] == "f" || args[i] == "F") {
                _boardSource = BoardSource::FILE;
            }
        }
        else if (args[i] == "-moves") {
            i++;
            if (args[i] == "f" || args[i] == "F") {
                _movesSource = MovesSource::FILE;
            }
        }
        else if (args[i] == "-path") {
            _path = args[++i];
        }
        else if (args[i] == "-quiet") {
            _quiet = true;
        }
        else if (args[i] == "-delay") {
            _delay = (unsigned int)atoi(args[++i].c_str());
        }
    }
}