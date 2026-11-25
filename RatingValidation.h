#ifndef RATING_VALIDATION_H
#define RATING_VALIDATION_H

#include <iostream>
#include <sstream>
#include <string>

inline bool validRating(const std::string& input) {
    std::istringstream parser(input);

    int rating;
    char extra;

    if (!(parser >> rating)) {
        return false;
    }

    if (parser >> extra) {
        return false;
    }

    return rating >= 1 && rating <= 5;
}

inline bool readRating(
    std::istream& input,
    std::ostream& output,
    int& rating
) {
    std::string line;

    while (true) {
        output << "Rating (1-5): ";

        if (!std::getline(input, line)) {
            return false;
        }

        if (!validRating(line)) {
            output
                << "Invalid rating! Enter an integer (1-5).\n";
            continue;
        }

        std::istringstream parser(line);
        parser >> rating;
        return true;
    }
}

#endif
