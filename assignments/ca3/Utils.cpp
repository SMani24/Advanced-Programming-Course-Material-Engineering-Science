/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#include "Utils.hpp"

std::string trimLeadingSpaces(const std::string& str) {
    size_t first_non_space = str.find_first_not_of(" \t\r\n");
    if (first_non_space == std::string::npos) {
        return "";
    }
    return str.substr(first_non_space);
}

std::string getNextToken(std::string& line) {
    line = trimLeadingSpaces(line);
    if (line.empty()) {
        return "";
    }

    size_t space_pos = line.find(' ');
    if (space_pos == std::string::npos) {
        std::string token = line;
        line = "";
        return token;
    }

    std::string token = line.substr(0, space_pos);
    line = trimLeadingSpaces(line.substr(space_pos));
    return token;
}

std::string stateToString(ComponentState state) {
    if (state == ComponentState::PENDING) {
        return "PENDING";
    }
    if (state == ComponentState::INSTALLED) {
        return "INSTALLED";
    }
    if (state == ComponentState::FAILED) {
        return "FAILED";
    }
    return "UNKNOWN";
}