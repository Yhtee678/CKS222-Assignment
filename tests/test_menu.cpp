
#include <cassert>
#include <iostream>
#include <sstream>
#include "MenuInput.h"

void testValidChoices() {
    for (int i = 1; i <= 7; ++i) {
        std::istringstream input(std::to_string(i) + "\n");
        std::ostringstream output;

        int choice = 0;
        bool result = readMenuChoice(input, output, choice);

        assert(result);
        assert(choice == i);
    }
}

void testInvalidInputThenValid() {
    std::istringstream input("abc\n5\n");
    std::ostringstream output;

    int choice = 0;
    bool result = readMenuChoice(input, output, choice);

    assert(result);
    assert(choice == 5);
    assert(output.str().find("Invalid") != std::string::npos);
}

void testMixedInput() {
    std::istringstream input("1abc\n2\n");
    std::ostringstream output;

    int choice = 0;
    bool result = readMenuChoice(input, output, choice);

    assert(result);
    assert(choice == 2);
}

void testOutOfRange() {
    std::istringstream input("0\n8\n3\n");
    std::ostringstream output;

    int choice = 0;
    bool result = readMenuChoice(input, output, choice);

    assert(result);
    assert(choice == 3);
}

void testEmptyInput() {
    std::istringstream input("\n4\n");
    std::ostringstream output;

    int choice = 0;
    bool result = readMenuChoice(input, output, choice);

    assert(result);
    assert(choice == 4);
}

void testEndOfInput() {
    std::istringstream input("");
    std::ostringstream output;

    int choice = 0;
    bool result = readMenuChoice(input, output, choice);

    assert(!result);
}

int main() {
    testValidChoices();
    testInvalidInputThenValid();
    testMixedInput();
    testOutOfRange();
    testEmptyInput();
    testEndOfInput();

    std::cout << "All menu validation tests passed!\n";
    return 0;
}
