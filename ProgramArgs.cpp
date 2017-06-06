#include "ProgramArgs.h"

ProgramArgs::ProgramArgs()
        : _boardSource(BoardSource::RANDOM),
          _movesSource(MovesSource::ALGORITHM),
          _delay(20),
          _quiet(false),
          _path(getCurrentWorkingDirectory()) { }

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

            if (i + 1 < size && args[i + 1][0] != '-') {
                i++;
                _randomBoards = (unsigned int)stoul(args[i]);
            }
        }
        else if (args[i] == "-moves") {
            i++;
            if (args[i] == "f" || args[i] == "F") {
                _movesSource = MovesSource::FILE;
            }
            else if (args[i] == "a" || args[i] == "A") {
                _movesSource = MovesSource::ALGORITHM;
            }
        }
        else if (args[i] == "-path") {
            _path = args[++i];
        }
        else if (args[i] == "-quiet") {
            _quiet = true;
        }
        else if (args[i] == "-save") {
            _save = true;
        }
        else if (args[i] == "-delay") {
            _delay = (unsigned int)atoi(args[++i].c_str());
        }
    }
}