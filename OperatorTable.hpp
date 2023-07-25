#pragma once

#include "CollectionSimple.cpp"

class OperatorTable {

    private:

        CollectionSimple<std::string, int>* precedence;
        CollectionSimple<std::string, bool>* associativity;

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