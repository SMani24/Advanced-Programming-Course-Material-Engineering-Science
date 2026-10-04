/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef MODULE_HPP
#define MODULE_HPP

#include "Installable.hpp"

class Module : public Installable {
public:
    Module(std::string id, std::string title);
    
    bool install(TransactionContext& tx) override;
    void uninstall() override;
};

#endif // MODULE_HPP