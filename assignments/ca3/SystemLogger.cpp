/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#include "SystemLogger.hpp"
#include "Installable.hpp"
#include "Utils.hpp"
#include <iostream>

void SystemLogger::onStateChanged(const Installable* comp, ComponentState old_state, ComponentState new_state) {
    if (comp) {
        std::cout << "[OBSERVER] Component " << comp->getId() 
                  << " changed from " << stateToString(old_state) 
                  << " to " << stateToString(new_state) << "\n";
    }
}