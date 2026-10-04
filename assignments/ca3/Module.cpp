/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#include "Module.hpp"

Module::Module(std::string id, std::string title) : Installable(id, title) {
}

bool Module::install(TransactionContext& tx) {
    if (isMockFail()) {
        setState(ComponentState::FAILED);
        return false;
    }
    
    if (getState() != ComponentState::INSTALLED) {
        setState(ComponentState::INSTALLED);
        tx.state_changed_nodes.push_back(this);
    }
    
    return true;
}

void Module::uninstall() {
    setState(ComponentState::PENDING);
}