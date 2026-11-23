#ifndef TRAVELER_VALIDATION_H
#define TRAVELER_VALIDATION_H

#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

inline bool hasVisibleText(const std::string& value) {
    for (unsigned char ch : value) {
        if (!std::isspace(ch)) {
            return true;
        }
    }
    return false;
}

inline bool validTravelerName(const std::string& name) {
    return hasVisibleText(name);
}

inline bool validTravelerState(const std::string& state) {
    return hasVisibleText(state);
}

inline bool validTravelerEmail(const std::string& email) {
    if (email.empty()) return false;

    for (unsigned char ch : email) {
        if (std::isspace(ch)) return false;
    }

    std::size_t at = email.find('@');

    if (at == std::string::npos ||
        at == 0 ||
        at != email.rfind('@')) {
        return false;
    }

    std::size_t dot = email.find('.', at + 1);

    return dot != std::string::npos &&
           dot > at + 1 &&
           dot + 1 < email.size();
}

inline std::string nextTravelerID(
    const std::vector<std::string>& existingIDs
) {
    for (int number = 1; number <= 9999; ++number) {
        std::ostringstream idStream;
        idStream << 'U'
                 << std::setw(3)
                 << std::setfill('0')
                 << number;

        std::string candidate = idStream.str();

        bool exists = false;

        for (const auto& id : existingIDs) {
            if (id == candidate) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            return candidate;
        }
    }

    return "";
}

#endif
