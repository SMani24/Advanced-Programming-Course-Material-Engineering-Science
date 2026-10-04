// In the name of God
// SMani24

#include <string_view>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

namespace InputStrings {
    constexpr string_view PRINT_ALL = "PRINT_ALL";
    constexpr string_view NEW_LIST = "NEW_LIST";
    constexpr string_view ADD_DEP = "ADD_DEP";
    constexpr string_view PENDING = "PENDING";
    constexpr string_view STATUS = "STATUS";
    constexpr string_view REMOVE = "REMOVE";
    constexpr string_view READY = "READY";
    constexpr string_view DONE = "DONE";
    constexpr string_view EXIT = "EXIT"; 
    constexpr string_view ADD = "ADD";
}
namespace TaskStatus {
    constexpr string_view DONE = "done";
    constexpr string_view PENDING = "pending";
}
namespace TaskError {
    constexpr string_view INVALID_ID = "invalid id";
    constexpr string_view ID_NOT_FOUND = "id not found";
    constexpr string_view NO_ERROR = "no error!";
    constexpr string_view DEPENDENCY_NOT_DONE = "dependency not done!";
}

struct Status {
    int id;
    string title;
    string_view status;
    vector<pair<int, string>> dependencies;
    Status(int id, string title, string_view status, vector<pair<int, string>> dependencies);
    Status() = default;
};

Status::Status(int id, string title, string_view status, vector<pair<int, string>> dependencies) {
    this->id = id;
    this->title = title;
    this->status = status;

    sort(dependencies.begin(), dependencies.end());
    this->dependencies = dependencies;
}


class Task {
private:
    int id;
    vector<Task*> dependencies;
    string title;
    string status;

public:
    Task(int id, const string& title, const vector<Task*>& dependencies) : 
        id(id), title(title), dependencies(dependencies) {status = TaskStatus::PENDING;}

    bool operator<(const Task& other) const;
    string_view getStatus() {return status;}
    string getTitle() {return title;};
    int getId() {return id;}
    string_view doTask();
    Status getFullStatus();
    bool canBeDone();
    bool hasDependency(Task* task);
};

bool Task::operator<(const Task& other) const {
    return id < other.id;
}

string_view Task::doTask() {
    bool isDependenciesDone = true;
    for (Task* dependency : dependencies)
        if (dependency->getStatus() != TaskStatus::DONE)
            isDependenciesDone = false;

    if (!isDependenciesDone)
        return TaskError::DEPENDENCY_NOT_DONE;

    status = TaskStatus::DONE;
    return TaskError::NO_ERROR;
}

Status Task::getFullStatus() {
    vector<pair<int, string>> dependenciesInfo;

    for (Task* dependency : dependencies)
        dependenciesInfo.push_back(pair(dependency->getId(), dependency->getTitle()));

    Status printableStatus = Status(id, title, status, dependenciesInfo);
    return printableStatus;
}

bool Task::canBeDone() {
    for (Task* task : dependencies)
        if (task->getStatus() == TaskStatus::PENDING) 
            return false;

    return true;
}

bool Task::hasDependency(Task* task) {
    for (Task* dependency : dependencies) 
        if (dependency == task)
            return true;

    return false;
}

class ToDoList {
private:
    map<int, Task*> tasks;
    bool isIdAvailable(int id);
    bool sortById(Task* task1, Task* task2);
    bool canRemove(Task* taskToRemove);
public:
    void reset();
    ~ToDoList();
    pair<string_view, vector<int>> addTask(int id, const string& title, const vector<int>& dependencies);
    pair<string_view, vector<int>> addTask(int id, const string& title);
    string_view doTask(int id);
    pair<string_view, Status> getStatus(int id);
    vector<tuple<string_view, int, string>>  getAllTaskStatus();
    vector<Task*> getTasksByStatus(string_view status); 
    vector<Task*> getReadyTasks();
    string_view removeTask(int id);
};

ToDoList::~ToDoList() {
    for (auto const& [id, taskPtr] : tasks) {
        delete taskPtr;
    }
    tasks.clear();
}

void ToDoList::reset() {
    for (auto const& [id, taskPtr] : tasks) {
        delete taskPtr;
    }
    tasks.clear();
}

bool ToDoList::isIdAvailable(int id) {
    if (tasks.find(id) == tasks.end())
        return true;
    return false;
}

pair<string_view, vector<int>> ToDoList::addTask(int id, const string& title, const vector<int>& dependenciesId) {
    vector<int> invalidDependenciesId;

    if (! isIdAvailable(id))
        return pair(TaskError::INVALID_ID, dependenciesId);

    for (int id : dependenciesId)
        if (isIdAvailable(id))
            invalidDependenciesId.push_back(id);
    
    sort(invalidDependenciesId.begin(), invalidDependenciesId.end());
    reverse(invalidDependenciesId.begin(), invalidDependenciesId.end());
    if (invalidDependenciesId.size() > 0)
        return pair(TaskError::ID_NOT_FOUND, invalidDependenciesId);
    
    vector<Task*> dependencies;
    for (int id: dependenciesId)
        dependencies.push_back(tasks[id]);
    
    tasks.insert(pair(id, new Task(id, title, dependencies)));
    return pair(TaskError::NO_ERROR, dependenciesId);
}

pair<string_view, vector<int>> ToDoList::addTask(int id, const string& title) {
    vector<int> dependencies = {};
    return addTask(
        id,
        title,
        dependencies
    );
}

string_view ToDoList::doTask(int id) {
    if (isIdAvailable(id))
        return TaskError::ID_NOT_FOUND;
    
    Task* task = tasks[id];
    return task->doTask();
}

pair<string_view, Status> ToDoList::getStatus(int id) {
    string_view error;
    if (tasks.find(id) == tasks.end()) {
        error = TaskError::ID_NOT_FOUND;
        return pair(error, Status());
    }
    error = TaskError::NO_ERROR;
    Status status = tasks[id]->getFullStatus();
    
    return pair(error, status);
}

vector<tuple<string_view, int, string>> ToDoList::getAllTaskStatus() {
    vector<tuple<string_view, int, string>> allStatus;
    for (auto const& [id, taskPtr] : tasks) {
        Status status = taskPtr->getFullStatus();
        allStatus.push_back(tuple(status.status, status.id, status.title));
    }

    return allStatus;
}

bool ToDoList::sortById(Task* task1, Task* task2) {
    return task1->getId() < task2->getId();
}

vector<Task*> ToDoList::getTasksByStatus(string_view status) {
    vector<Task*> results;
    for (auto const& [id, taskPtr] : tasks)
        if (taskPtr->getStatus() == status)
            results.push_back(taskPtr);

    return results;
}

vector<Task*> ToDoList::getReadyTasks() {
    vector<Task*> pendingTasks = getTasksByStatus(TaskStatus::PENDING);
    vector<Task*> readyTasks;
    for (Task* task : pendingTasks)
        if (task->canBeDone())
            readyTasks.push_back(task);

    return readyTasks;
}

bool ToDoList::canRemove(Task* taskToRemove) {
    for (auto const& [id, task] : tasks)
        if (task->hasDependency(taskToRemove))
            return false;
    return true;
}

string_view ToDoList::removeTask(int id) {
    if (isIdAvailable(id))
        return TaskError::ID_NOT_FOUND;
    
    if (!canRemove(tasks[id]))
        return TaskError::DEPENDENCY_NOT_DONE;

    delete(tasks[id]);
    tasks.erase(id);
    return TaskError::NO_ERROR;
}


class ProgramHandler {
private:
    ToDoList todoList;
    bool isFinished=false;
    void dependencyNotFoundMessage(vector<int> invalidDependencies);

public:
    void makeNewList();
    void addTaskHandler();
    void addDependenciesHandler();
    void doTask();
    void printStatus();
    void printAll();
    void printPending();
    void printReadyTasks();
    void removeTask();
    void finish() {isFinished = true;}
};

void ProgramHandler::makeNewList() {
    if (isFinished)
        return;
    string name;
    cin >> name;
    cout << "List '" << name << "' created." << endl;

    todoList.reset();
}

void ProgramHandler::addTaskHandler() {
    if (isFinished)
        return;
    int id;
    string title;

    cin >> id >> title;

    pair<string_view, vector<int>> error = todoList.addTask(
        id,
        title
    );
    string_view errorMessage = error.first;
    if (errorMessage == TaskError::NO_ERROR)
        cout << "Task " << id << " added." << endl;

    else if (errorMessage == TaskError::INVALID_ID)
        cout << "Error: task " << id << " already exists." << endl;
}

void ProgramHandler::dependencyNotFoundMessage(vector<int> invalidDependencies) {
    if (isFinished)
        return;
    for (int id : invalidDependencies)
        cout << "Error: dependency " << id << " " << "not found." << endl;        
}

void ProgramHandler::addDependenciesHandler() {
    if (isFinished)
        return;
    int id;
    string title;
    vector<int> dependencies;

    cin >> id >> title;

    int dependencyId;
    string restOfLine;
    getline(cin, restOfLine);

    istringstream lineStream(restOfLine);
    while (lineStream >> dependencyId)
        dependencies.push_back(dependencyId);

    pair<string_view, vector<int>> error = todoList.addTask(id, title, dependencies);
    string_view errorMessage = error.first;
    vector<int> invalidDependencies = error.second;

    if (errorMessage == TaskError::INVALID_ID)
        cout << "Error: task " << id << " already exists." << endl;
    
    if (errorMessage == TaskError::ID_NOT_FOUND)
        dependencyNotFoundMessage(invalidDependencies);

    if (errorMessage == TaskError::NO_ERROR)
        cout << "Task " << id << " added with " << dependencies.size() <<" deps." << endl;;
}

void ProgramHandler::doTask() {
    if (isFinished)
        return;
    int id;
    cin >> id;
    string_view error = todoList.doTask(id);

    if (error == TaskError::ID_NOT_FOUND)
        cout << "Error: task " << id << " not found." << endl;


    if (error == TaskError::DEPENDENCY_NOT_DONE) 
        cout << "Cannot complete task "<< id <<": prerequisites not met." << endl;

    if (error == TaskError::NO_ERROR)
        cout << "Task " << id <<" marked as done." << endl;
}

void ProgramHandler::printStatus() {
    if (isFinished)
        return;
    int id;
    cin >> id;
    pair<string_view, Status> statusWithError = todoList.getStatus(id);
    
    string_view error = statusWithError.first;
    Status status = statusWithError.second;

    if (error == TaskError::ID_NOT_FOUND)
        cout << "Error: task " << id <<" not found." << endl;

    else {
        cout << "Task " << id << ": " << status.title << endl;
        cout << "Status: " << status.status << endl;
        
        if (status.dependencies.size() > 0) {
            cout << "Dependencies: ";
            for (int i=0; i < status.dependencies.size() - 1; i++)
                cout << status.dependencies[i].first 
                    << " (" << status.dependencies[i].second << "), ";
            cout << status.dependencies.back().first 
                    << " (" << status.dependencies.back().second << ")" << endl;
        }
        else 
            cout << endl;
    }
}

void ProgramHandler::printAll() {
    if (isFinished)
        return;
    vector<tuple<string_view, int, string>> allStatus = todoList.getAllTaskStatus();
    
    for (auto const& [status, id, title] : allStatus) {
        if (status == TaskStatus::DONE)
            cout << "[done]    ";
        if (status == TaskStatus::PENDING)
            cout << "[pending] ";

        cout << id << ": " << title << endl; 
    }
}

void ProgramHandler::printPending() {
    if (isFinished)
        return;
    string_view status = TaskStatus::PENDING;

    vector<Task*> pendingTasks = todoList.getTasksByStatus(status);

    if (pendingTasks.empty()) {
        cout << endl;
        return;
    }

    cout << "Pending tasks: ";
    for (int i = 0; i < pendingTasks.size() - 1; i ++) {
        cout << pendingTasks[i]->getId() << " (" 
             << pendingTasks[i]->getTitle() << "), ";
    }
    cout << pendingTasks[pendingTasks.size() - 1]->getId() << " (" 
         << pendingTasks[pendingTasks.size() - 1]->getTitle() << ")" << endl;
}

void ProgramHandler::printReadyTasks() {
    vector<Task*> readyTasks = todoList.getReadyTasks();

    if (readyTasks.empty()) {
        cout << endl;
        return;
    }

    cout << "Ready tasks:";
    for (Task* task : readyTasks) 
        cout << " " << task->getId();
    cout << endl;
}

void ProgramHandler::removeTask() {
    int id;
    cin >> id;
    string_view error = todoList.removeTask(id);
    
    if (error == TaskError::ID_NOT_FOUND)
        cout << "Error: task " << id <<" not found." << endl;

    if (error == TaskError::DEPENDENCY_NOT_DONE)
        cout << "Cannot remove task " << id << ": other tasks depend on it." << endl;

    if (error == TaskError::NO_ERROR)
        cout << "Task " << id <<" removed." << endl;
}

int main() {
    string input;
    ProgramHandler program;

    while (cin >> input) {
        if (input == InputStrings::NEW_LIST)
            program.makeNewList();

        else if (input == InputStrings::ADD)
            program.addTaskHandler();

        else if (input == InputStrings::ADD_DEP)
            program.addDependenciesHandler();
        
        else if (input == InputStrings::DONE)
            program.doTask();

        else if (input == InputStrings::STATUS)
            program.printStatus();

        else if (input == InputStrings::PRINT_ALL)
            program.printAll();

        else if (input == InputStrings::PENDING)
            program.printPending();

        else if (input == InputStrings::READY)
            program.printReadyTasks();

        else if (input == InputStrings::REMOVE)
            program.removeTask();

        else if (input == InputStrings::EXIT)
            program.finish();
    }
}