/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef INSTALLATION_ENGINE_HPP
#define INSTALLATION_ENGINE_HPP

#include <vector>
#include <string>
#include "Installable.hpp"
#include "SystemLogger.hpp"

class InstallationEngine {
private:
    std::vector<Installable*> all_components;
    SystemLogger logger;

    Installable* getComponent(const std::string& id);
    
    void cmdAddModule(std::string& line);
    void cmdAddPackage(std::string& line);
    void cmdAttach(std::string& line);
    void cmdMockFail(std::string& line);
    void cmdResolveFail(std::string& line);
    void cmdInstall(std::string& line);
    void cmdUninstall(std::string& line);
    void uninstallAll();

public:
    InstallationEngine();
    ~InstallationEngine();

    void processCommand(std::string line);
};

#endif // INSTALLATION_ENGINE_HPP