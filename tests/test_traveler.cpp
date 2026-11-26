#include <cassert>
#include <iostream>
#include <vector>
#include "TravelerValidation.h"

int main() {
    // Name validation
    assert(validTravelerName("Ali Ahmad"));
    assert(!validTravelerName(""));
    assert(!validTravelerName("   "));

    // State validation
    assert(validTravelerState("Johor"));
    assert(!validTravelerState(""));
    assert(!validTravelerState("   "));

    // Email validation
    assert(validTravelerEmail("ali@gmail.com"));
    assert(!validTravelerEmail("abc"));
    assert(!validTravelerEmail("@gmail.com"));
    assert(!validTravelerEmail("ali@"));
    assert(!validTravelerEmail("ali@gmail"));
    assert(!validTravelerEmail("ali @gmail.com"));

    // ID generation
    std::vector<std::string> ids = {
        "U001", "U002", "U004"
    };

    assert(nextTravelerID(ids) == "U003");

    std::vector<std::string> emptyIDs;
    assert(nextTravelerID(emptyIDs) == "U001");

    std::cout
        << "All traveler validation tests passed!\n";

    return 0;
}
