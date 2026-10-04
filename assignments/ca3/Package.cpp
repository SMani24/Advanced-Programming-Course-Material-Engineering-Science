/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#include "Package.hpp"

Package::Package(std::string id, std::string title) : Installable(id, title) {
}

bool Package::isPackage() const {
    return true;
}

void Package::addChild(Installable* child) {
    children.push_back(child);
}

bool Package::hasChild(const std::string& child_id) const {
    for (Installable* child : children) {
        if (child->getId() == child_id) {
            return true;
        }
    }
    return false;
}

bool Package::install(TransactionContext& tx) {
    if (isMockFail()) {
        setState(ComponentState::FAILED);
        return false;
    }

    for (Installable* child : children) {
        if (child->getState() != ComponentState::INSTALLED) {
            if (!child->install(tx)) {
                setState(ComponentState::FAILED);
                return false; 
            }
        }
        child->incParents();
        tx.count_increased_nodes.push_back(child);
    }

    if (getState() != ComponentState::INSTALLED) {
        setState(ComponentState::INSTALLED);
        tx.state_changed_nodes.push_back(this);
    }
    
    return true;
}

void Package::uninstall() {
    setState(ComponentState::PENDING);
    
    // Reverse iterators unroll the dependencies in LIFO order
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        Installable* child = *it;
        child->decParents();
        
        if (child->getInstalledParentsCount() == 0 && !child->getExplicit()) {
            if (child->getState() != ComponentState::PENDING) {
                child->uninstall();
            }
        }
    }
}