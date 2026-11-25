#include <sstream>
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

    // Invalid input followed by valid input
    std::istringstream input("abc\n6\n4\n");
    std::ostringstream output;

    int rating = 0;

    bool result = readRating(input, output, rating);

    assert(result);
    assert(rating == 4);
    assert(output.str().find("Invalid") != std::string::npos);

    // End of input
    std::istringstream emptyInput("");
    std::ostringstream emptyOutput;

    int unusedRating = 0;

    assert(!readRating(
        emptyInput,
        emptyOutput,
        unusedRating
    ));

    std::cout
        << "All rating validation tests passed!\n";

    return 0;
}
