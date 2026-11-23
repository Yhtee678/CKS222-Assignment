#include <cassert>
#include <iostream>
#include "../RatingValidation.h"

int main() {
    // Valid ratings
    assert(validRating("1"));
    assert(validRating("3"));
    assert(validRating("5"));

    // Invalid ratings
    assert(!validRating("0"));
    assert(!validRating("6"));
    assert(!validRating("abc"));
    assert(!validRating("3.5"));
    assert(!validRating(""));
    assert(!validRating("   "));
    assert(!validRating("2abc"));

    std::cout
        << "All rating validation tests passed!\n";

    return 0;
}
