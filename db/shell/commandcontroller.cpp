#include "commandcontroller.h"

#include "command.h"

#include <string>
#include <iostream>

using namespace std;

std::string readLine() {
    std::string line;
    cin >> line;
    return line;
}

Command* parseCommand(std::string line) {
}

void mainLoop() {
    std::string line;
    while (true) {
        line = readLine();
        if (line.compare("exit")) {
            break;
        }
        Command* cmd = parseCommand(line);
    }
}
