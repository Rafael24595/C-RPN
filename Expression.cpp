#pragma once

#include "VectorQueue.cpp"
#include "OperatorTable.h"
#include "Tools.cpp"
#include "Optional.cpp"

class Expression {

    private:

        Optional<char> operation;
        VectorQueue<VectorQueue<char>> expression;

    public:

        Expression() {
            operation = Optional<char>::None();
            expression = VectorQueue<VectorQueue<char>>();
        }

        Expression(VectorQueue<char> e1, VectorQueue<char> e2, char o) {
            VectorQueue<char> op = VectorQueue<char>();
            op.Insert(o);

            expression = VectorQueue<VectorQueue<char>>();
            expression.Insert(e1);
            expression.Insert(op);
            expression.Insert(e2);
            operation = Optional<char>::Some(o);
        }

        void Insert(char ch) {
            VectorQueue<char>* ex = new VectorQueue<char>();
            ex->Insert(ch);
            expression.Insert(ex);
        }

        void Insert(VectorQueue<char>& ex) {
            expression.Insert(ex);
        }

        VectorQueue<char> GetExpression() {
            VectorQueue<char> ex = VectorQueue<char>();
            Optional<VectorQueue<char>> subExpression = expression.Remove();
            while (subExpression.IsSome()) {
                Optional<char> c = subExpression.Unwrap()->Remove();
                while (c.IsSome()) {
                    ex.Insert(c.Unwrap());
                    c = subExpression.Unwrap()->Remove();
                }
                subExpression = expression.Remove();
            }
            return ex;
        }

        int Precedence() {
            if (operation.IsNone()) {
                return 99;
            }

            Optional<int> actualPrecedence = OperatorTable::GetPrecedence(*operation.Unwrap());
            if (actualPrecedence.IsNone()) {
                throw std::runtime_error("Unknown operator " + *operation.Unwrap());
            }

            return *actualPrecedence.Unwrap();
        }

        bool IsEmpty() {
            if (expression.Length() == 1) {
                VectorQueue<char>* subExpression = expression.Get().Unwrap();
                if (subExpression->Length() == 1 && Tools::IsBlankSpace(*subExpression->Get().Unwrap())) {
                    return true;
                }
            }
            return expression.IsEmpty();
        }

};