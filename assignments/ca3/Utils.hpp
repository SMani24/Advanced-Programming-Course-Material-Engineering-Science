/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "ComponentState.hpp"

std::string trimLeadingSpaces(const std::string& str);
std::string getNextToken(std::string& line);
std::string stateToString(ComponentState state);

#endif