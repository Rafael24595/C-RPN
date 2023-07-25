#pragma once

#include "OperatorTable.hpp"
#include "Tools.hpp"

#include "Optional.cpp"
#include "VectorQueue.cpp"

class Expression {

    private:
        Optional<char> operation;
        VectorQueue<VectorQueue<char>> expression;

    public:
        Expression();
        Expression(VectorQueue<char> e1, VectorQueue<char> e2, char o);
        void Insert(char ch);
        void Insert(VectorQueue<char>& ex);
        VectorQueue<char> GetExpression();
        int Precedence();
        bool IsEmpty();

};