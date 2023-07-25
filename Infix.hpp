#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "Expression.hpp"
#include "OperatorTable.hpp"
#include "Tools.hpp"

#include "VectorStack.cpp"

class Infix {

	private:
		VectorStack<Expression> stack;

		void EvalueChar(char ch);
		void EvalueDigit(char ch);
		void EvalueOperator(char ch);
		VectorQueue<char> EvalueOperatorLeft(Optional<Expression> left, int actualPrecedence, bool actualAssociativity);
		VectorQueue<char> EvalueOperatorRight(Optional<Expression> right, int actualPrecedence, bool actualAssociativity);
		VectorQueue<char> EncapsuleExpression(VectorQueue<char> expression);

	public:
		Infix();
		static Infix Transform(string expression);
		void Print();

};