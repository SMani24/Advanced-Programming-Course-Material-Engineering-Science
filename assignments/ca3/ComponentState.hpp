/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef COMPONENT_STATE_HPP
#define COMPONENT_STATE_HPP

enum class ComponentState {
    PENDING,
    INSTALLED,
    FAILED
};

#endif