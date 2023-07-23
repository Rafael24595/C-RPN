#pragma once

#include "CollectionHash.cpp" // Include the header file for CollectionHash template

class OperatorTable {

    private:

        CollectionHash<std::string, int>* precedence;

    protected:

        OperatorTable();

        static OperatorTable* instance;

    public:

        OperatorTable(const OperatorTable&) = delete;
        void operator=(const OperatorTable&) = delete;

        static OperatorTable* GetInstance();

        Optional<int> GetPrecedence(char o);
};