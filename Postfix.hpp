#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "VectorStack.cpp"
#include "VectorQueue.cpp"
#include "Tools.hpp"
#include "OperatorTable.hpp"

class Postfix {

	private:
		VectorStack<char> stack;
		VectorQueue<char> queue;

		void EvalueChar(char ch);
		void EvalueDigit(char ch);
		void EvalueOperator(char ch);
		bool EvalueOperatorPrecedence(char ch, int actualPrecedence);
		bool EvalueOperatorAssociativity(char ch, int actualPrecedence, int lastPrecedence);
		void EvalueOpenParenthesis(char ch);
		void EvalueCloseParenthesis(char ch);
		void PullStack();

	public:
		Postfix();
		static Postfix Transform(string expression);
		void Print();

};