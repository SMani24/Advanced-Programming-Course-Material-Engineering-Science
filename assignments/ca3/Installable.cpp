/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#include "Installable.hpp"

Installable::Installable(std::string id, std::string title) {
    this->id = id;
    this->title = title;
    this->state = ComponentState::PENDING;
    this->mock_fail = false;
    this->installed_parents_count = 0;
    this->is_explicitly_installed = false;
}

Installable::~Installable() {
}

void Installable::setState(ComponentState new_state) {
    if (this->state != new_state) {
        ComponentState old_state = this->state;
        this->state = new_state;
        for (Observer* obs : observers) {
            obs->onStateChanged(this, old_state, new_state);
        }
    }
}

std::string Installable::getId() const {
    return id;
}

std::string Installable::getTitle() const {
    return title;
}

ComponentState Installable::getState() const {
    return state;
}

bool Installable::isMockFail() const {
    return mock_fail;
}

void Installable::setMockFail(bool val) {
    mock_fail = val;
}

int Installable::getInstalledParentsCount() const {
    return installed_parents_count;
}

void Installable::incParents() {
    installed_parents_count++;
}

void Installable::decParents() {
    if (installed_parents_count > 0) {
        installed_parents_count--;
    }
}

bool Installable::getExplicit() const {
    return is_explicitly_installed;
}

void Installable::setExplicit(bool val) {
    is_explicitly_installed = val;
}

void Installable::addObserver(Observer* obs) {
    observers.push_back(obs);
}

bool Installable::isPackage() const {
    return false;
}

void Installable::forcePending() {
    setState(ComponentState::PENDING);
}