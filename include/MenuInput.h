
#ifndef MENU_INPUT_H
#define MENU_INPUT_H

#include <iostream>
#include <sstream>
#include <string>

inline bool readMenuChoice(
    std::istream& input,
    std::ostream& output,
    int& choice
) {
    std::string line;

    while (std::getline(input, line)) {
        std::istringstream parser(line);

        int value;
        char extra;

        if (!(parser >> value)) {
            output << "Invalid input! Enter a number (1-7).\n";
            continue;
        }

        if (parser >> extra) {
            output << "Invalid input! Enter a number (1-7).\n";
            continue;
        }

        if (value < 1 || value > 7) {
            output << "Invalid choice! Enter 1-7.\n";
            continue;
        }

        choice = value;
        return true;
    }

    return false;
}

#endif
