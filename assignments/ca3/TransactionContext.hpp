/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef TRANSACTION_CONTEXT_HPP
#define TRANSACTION_CONTEXT_HPP

#include <vector>


class Installable;

struct TransactionContext {
    std::vector<Installable*> state_changed_nodes;
    std::vector<Installable*> count_increased_nodes;
};

#endif