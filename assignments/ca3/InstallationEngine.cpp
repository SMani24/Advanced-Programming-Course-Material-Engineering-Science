/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#include "InstallationEngine.hpp"
#include "Module.hpp"
#include "Package.hpp"
#include "Utils.hpp"
#include <iostream>

InstallationEngine::InstallationEngine() {}

InstallationEngine::~InstallationEngine() {
    for (Installable* comp : all_components) {
        delete comp;
    }
    all_components.clear();
}

Installable* InstallationEngine::getComponent(const std::string& id) {
    for (Installable* comp : all_components) {
        if (comp->getId() == id) return comp;
    }
    return nullptr;
}

void InstallationEngine::processCommand(std::string line) {
    std::string cmd = getNextToken(line);
    if (cmd == "ADD_MODULE") cmdAddModule(line);
    else if (cmd == "ADD_PACKAGE") cmdAddPackage(line);
    else if (cmd == "ATTACH") cmdAttach(line);
    else if (cmd == "MOCK_FAIL") cmdMockFail(line);
    else if (cmd == "RESOLVE_FAIL") cmdResolveFail(line);
    else if (cmd == "INSTALL") cmdInstall(line);
    else if (cmd == "UNINSTALL") cmdUninstall(line);
    else if (cmd != "END" && !cmd.empty()) std::cout << "ERROR: Invalid command\n";
}

void InstallationEngine::cmdAddModule(std::string& line) {
    std::string id = getNextToken(line);
    std::string title = trimLeadingSpaces(line);
    if (id.empty() || title.empty()) { std::cout << "ERROR: Invalid command\n"; return; }
    if (getComponent(id)) { std::cout << "ERROR: Component with ID " << id << " already exists\n"; return; }
    
    Module* mod = new Module(id, title);
    mod->addObserver(&logger);
    all_components.push_back(mod);
}

void InstallationEngine::cmdAddPackage(std::string& line) {
    std::string id = getNextToken(line);
    std::string title = trimLeadingSpaces(line);
    if (id.empty() || title.empty()) { std::cout << "ERROR: Invalid command\n"; return; }
    if (getComponent(id)) { std::cout << "ERROR: Component with ID " << id << " already exists\n"; return; }
    
    Package* pkg = new Package(id, title);
    pkg->addObserver(&logger);
    all_components.push_back(pkg);
}

void InstallationEngine::cmdAttach(std::string& line) {
    std::string p_id = getNextToken(line);
    std::string c_id = getNextToken(line);
    if (p_id.empty() || c_id.empty()) { std::cout << "ERROR: Invalid command\n"; return; }
    
    Installable* parent = getComponent(p_id);
    Installable* child = getComponent(c_id);
    if (!parent) { std::cout << "ERROR: Component " << p_id << " does not exist\n"; return; }
    if (!child) { std::cout << "ERROR: Component " << c_id << " does not exist\n"; return; }
    if (!parent->isPackage()) { std::cout << "ERROR: Cannot attach to a module\n"; return; }
    
    Package* pkg = static_cast<Package*>(parent);
    if (pkg->hasChild(c_id)) { std::cout << "ERROR: Component " << c_id << " is already attached to " << p_id << "\n"; return; }
    if (pkg->getState() == ComponentState::INSTALLED) { std::cout << "ERROR: Cannot attach to an already installed package\n"; return; }
    
    pkg->addChild(child);
}

void InstallationEngine::cmdMockFail(std::string& line) {
    std::string id = getNextToken(line);
    if (id.empty()) { std::cout << "ERROR: Invalid command\n"; return; }
    
    Installable* comp = getComponent(id);
    if (!comp) { std::cout << "ERROR: Component " << id << " does not exist\n"; return; }
    if (comp->getState() == ComponentState::INSTALLED) { std::cout << "ERROR: Component " << id << " is already installed\n"; return; }
    if (comp->isMockFail()) { std::cout << "ERROR: Component " << id << " is already set to fail\n"; return; }
    
    comp->setMockFail(true);
}

void InstallationEngine::cmdResolveFail(std::string& line) {
    std::string id = getNextToken(line);
    if (id.empty()) { std::cout << "ERROR: Invalid command\n"; return; }
    
    Installable* comp = getComponent(id);
    if (!comp) { std::cout << "ERROR: Component " << id << " does not exist\n"; return; }
    if (!comp->isMockFail()) { std::cout << "ERROR: Component " << id << " is not in a mock fail state\n"; return; }
    
    comp->setMockFail(false);
}

void InstallationEngine::cmdInstall(std::string& line) {
    std::string id = getNextToken(line);
    if (id.empty()) { std::cout << "ERROR: Invalid command\n"; return; }
    
    Installable* comp = getComponent(id);
    if (!comp) { std::cout << "ERROR: Component " << id << " does not exist\n"; return; }
    if (comp->getState() == ComponentState::INSTALLED) { std::cout << "ERROR: Component " << id << " is already installed\n"; return; }
    
    comp->setExplicit(true);
    TransactionContext tx;
    if (!comp->install(tx)) {
        for (auto it = tx.state_changed_nodes.rbegin(); it != tx.state_changed_nodes.rend(); ++it) {
            (*it)->forcePending();
        }
        for (auto it = tx.count_increased_nodes.rbegin(); it != tx.count_increased_nodes.rend(); ++it) {
            (*it)->decParents();
        }
    }
}

void InstallationEngine::cmdUninstall(std::string& line) {
    std::string id = getNextToken(line);
    if (id == "-A") {
        uninstallAll();
        return;
    }
    if (id.empty()) { std::cout << "ERROR: Invalid command\n"; return; }
    
    Installable* comp = getComponent(id);
    if (!comp) { std::cout << "ERROR: Component " << id << " does not exist\n"; return; }
    if (comp->getState() != ComponentState::INSTALLED) { std::cout << "ERROR: Component " << id << " is not currently installed\n"; return; }
    if (comp->getInstalledParentsCount() > 0) { std::cout << "ERROR: Component " << id << " is required by another package\n"; return; }
    
    comp->uninstall();
    comp->setExplicit(false);
}

void InstallationEngine::uninstallAll() {
    bool has_installed = false;
    for (Installable* comp : all_components) {
        if (comp->getState() != ComponentState::PENDING) { has_installed = true; break; }
    }
    if (!has_installed) {
        std::cout << "ERROR: No installed components to uninstall\n";
        return;
    }
    for (auto it = all_components.rbegin(); it != all_components.rend(); ++it) {
        if ((*it)->getState() != ComponentState::PENDING) {
            (*it)->forcePending();
            (*it)->setExplicit(false);
            while ((*it)->getInstalledParentsCount() > 0) {
                (*it)->decParents();
            }
        }
    }
}