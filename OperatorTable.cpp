#include "OperatorTable.h"
#include "CollectionHash.cpp" // Include the implementation of CollectionHash template
#include <string>

OperatorTable* OperatorTable::instance = nullptr;

OperatorTable::OperatorTable() {
    precedence = new CollectionHash<std::string, int>();
    precedence->Put("+", 2);
    precedence->Put("-", 2);
    precedence->Put("/", 3);
    precedence->Put("*", 3);
    precedence->Put("^", 4);
}

OperatorTable* OperatorTable::GetInstance() {
    if (instance == nullptr) {
        instance = new OperatorTable();
    }
    return instance;
}

Optional<int> OperatorTable::GetPrecedence(char o) {
    std::string key(1, o);
    return precedence->Find(key);
}