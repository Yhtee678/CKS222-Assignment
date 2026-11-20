
#ifndef MENU_INPUT_H
#define MENU_INPUT_H

#include <iostream>

inline bool readMenuChoice(
    std::istream& input,
    std::ostream& output,
    int& choice
) {
    input >> choice;
    return !input.fail();
}

#endif
