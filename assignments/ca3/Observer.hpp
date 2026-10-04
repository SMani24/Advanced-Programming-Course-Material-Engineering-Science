/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "ComponentState.hpp"

class Installable;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onStateChanged(const Installable* comp, ComponentState old_state, ComponentState new_state) = 0;
};

#endif