/*
 * Naming Convention Guideline
 * Class names: PascalCase
 * Function names: camelCase
 * Variable names: lower_snake_case
 * Constant names: UPPER_SNAKE_CASE
 */

#ifndef INSTALLABLE_HPP
#define INSTALLABLE_HPP

#include <string>
#include <vector>
#include "ComponentState.hpp"
#include "Observer.hpp"
#include "TransactionContext.hpp"

class Installable {
protected:
    std::string id;
    std::string title;
    ComponentState state;
    bool mock_fail;
    int installed_parents_count;
    bool is_explicitly_installed;
    std::vector<Observer*> observers;

public:
    Installable(std::string id, std::string title);
    virtual ~Installable();

    void setState(ComponentState new_state);
    
    std::string getId() const;
    std::string getTitle() const;
    ComponentState getState() const;
    
    bool isMockFail() const;
    void setMockFail(bool val);
    
    int getInstalledParentsCount() const;
    void incParents();
    void decParents();
    
    bool getExplicit() const;
    void setExplicit(bool val);
    
    void addObserver(Observer* obs);
    
    virtual bool isPackage() const;
    virtual bool install(TransactionContext& tx) = 0;
    virtual void uninstall() = 0;
    virtual void forcePending();
};

#endif // INSTALLABLE_HPP