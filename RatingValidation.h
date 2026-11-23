#ifndef RATING_VALIDATION_H
#define RATING_VALIDATION_H

#include <string>

inline bool validRating(const std::string& input) {
    return !input.empty();
}

#endif
