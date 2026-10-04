/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef SYSTEM_LOGGER_HPP
#define SYSTEM_LOGGER_HPP

#include "Observer.hpp"

class SystemLogger : public Observer {
public:
    void onStateChanged(const Installable* comp, ComponentState old_state, ComponentState new_state) override;
};

#endif