#include "Utils_Mac.h"

#ifdef __APPLE__

int _getch() {
    return getchar();
}

void randomSeed() {
    srand((unsigned int)time(NULL));
}

int getRandom(int start, int end) {
    return (rand() % (end - start)) + start;
}

void gotoxy(int x, int y) {
    std::cout << "\033[" << y+1 << ";" << x+1 << "H" << std::flush;
}

void hideCursor() {
    std::cout << "\033[?25l" << std::flush;
}

void showCursor() {
    std::cout << "\033[?25h" << std::flush;
}

void clearScreen() {
    std::cout << "\033[2J\033[H" << std::flush;
}

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

void setTextColor(int foregroundColor, int backgroundColor, bool bold) {
    foregroundColor += 30;
    backgroundColor += 40;

    std::cout << "\033[" << foregroundColor << (bold? ";1" : "") << "m";
    std::cout << "\033[" << backgroundColor << "m";
    std::cout << std::flush;
}

void resetTextColor() {
    std::cout << "\033[0m" << std::flush;
}

void Sleep(int ms) {
    usleep(ms * 1000);
}

string readLine(istream &in) {
    string result;
    char c = (char)in.get();

    while (in.gcount() && c != '\n') {
        result += c;
        c = (char)in.get();
    }

    if (result.length() && result.back() == '\r') {
        result.pop_back();
    }

    return result;
}

list<string> listDirectory(string path, string extension, string filename) {
    list<string> files;

    fs::directory_iterator end;

    for(fs::directory_iterator iter(path); iter != end; ++iter) {
        if (iter->status().type() == fs::file_type::regular_file) {
            if (iter->path().extension().string() == extension) {
                files.push_back(iter->path().string());
            }
        }
    }

    files.sort();

    return files;
}

void setWindowSize(int width, int height) { }

string getCurrentWorkingDirectory() {
    char path[255];
    getcwd(path, 255);
    return string(path);
}

void displayMessage(const string &message, int width, int height, int yOffset, unsigned int delay) {
    int len = (int)message.length() + 6;
    int msgHeight = 5;
    int x = width / 2 - len / 2;
    int y = yOffset + height / 2 - msgHeight / 2;

    setTextColor(BLACK, WHITE);
    gotoxy(x, y);
    cout << '\xC9';
    for (int i = 1; i < len - 1; i++) { cout << '\xCD'; }
    cout << '\xBB';

    gotoxy(x, y + 1);
    cout << '\xBA';
    for (int i = 1; i < len - 1; i++) { cout << ' '; }
    cout << '\xBA';

    gotoxy(x, y + 2);
    cout << "\xBA  " << message << "  \xBA";

    gotoxy(x, y + 3);
    cout << '\xBA';
    for (int i = 1; i < len - 1; i++) { cout << ' '; }
    cout << '\xBA';

    gotoxy(x, y + 4);
    cout << '\xC8';
    for (int i = 1; i < len - 1; i++) { cout << '\xCD'; }
    cout << '\xBC';

    cout << flush;
    resetTextColor();
    Sleep(delay);
}


#endif