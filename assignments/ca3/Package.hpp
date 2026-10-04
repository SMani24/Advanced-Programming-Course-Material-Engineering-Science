/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "Installable.hpp"
#include <vector>

class Package : public Installable {
private:
    std::vector<Installable*> children;

public:
    Package(std::string id, std::string title);
    
    bool isPackage() const override;
    void addChild(Installable* child);
    bool hasChild(const std::string& child_id) const;
    
    bool install(TransactionContext& tx) override;
    void uninstall() override;
};

#endif // PACKAGE_HPP