#pragma once

#include "CollectionHash.cpp" // Include the header file for CollectionHash template

class OperatorTable {

    private:

        CollectionHash<std::string, int>* precedence;
        CollectionHash<std::string, bool>* associativity;

    protected:

        static OperatorTable* instance;

        OperatorTable();
        static OperatorTable* GetInstance();

    public:

        OperatorTable(const OperatorTable&) = delete;
        void operator=(const OperatorTable&) = delete;

        static Optional<int> GetPrecedence(char o);
        static Optional<bool> GetAssociativity(char o);

};