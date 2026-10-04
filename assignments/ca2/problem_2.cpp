// In the name of God
// SMani24

/*
 * ========== Naming Convention Guideline ==========
 * Class names    : PascalCase
 * Function names : camelCase
 * Variable names : camelCase
 * Constant names : UPPER_SNAKE_CASE
 * =================================================
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

class Anagram {
private:
    std::set<std::string> vocabulary;
    std::set<std::string> validWords;
    std::map<char, int> availableChars;
    std::string word;
    bool isValid(const std::string& word);
    bool canBeValid(const std::string& word);

public:
    void readVocabulary();
    void solveHelper();
    void solve();
    void printResults();
};
bool Anagram::canBeValid(const std::string& word) {
    auto lowerBoundWordPtr = vocabulary.lower_bound(word);
    if (lowerBoundWordPtr == vocabulary.end() || !(lowerBoundWordPtr->find(word) == 0))
        return false;
    
    return true;
}

void Anagram::printResults() {
    std::cout << validWords.size() << '\n';

    for (const std::string& word : validWords)
        std::cout << word << '\n';
}

bool Anagram::isValid(const std::string& word) {
    if (vocabulary.find(word) == vocabulary.end())
        return false;
    return true;
}
 
void Anagram::solveHelper() {
    for (const auto& [ch, count] : availableChars) {
        if (count <= 0)
            continue;
            
        word += ch;
        if (isValid(word))
            validWords.insert(word);

        if (!canBeValid(word)) {
            word.pop_back();
            continue;
        }

        availableChars[ch] -= 1;

        solveHelper();

        word.pop_back();
        availableChars[ch] += 1;
    }
}

void Anagram::solve() {
    validWords.clear();
    availableChars.clear();
    word.clear();

    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);  
    char ch;
    while (ss >> ch)
        availableChars[ch] += 1;

    solveHelper();
}

void Anagram::readVocabulary() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string word;
        std::cin >> word;
        vocabulary.insert(word);
    }
}

int main() {
    Anagram anagram;
    anagram.readVocabulary();
    
    int q;
    std::cin >> q;
    std::cin.ignore();
    for (int i = 0; i < q; i++) {
        anagram.solve();
        anagram.printResults();
    }
}