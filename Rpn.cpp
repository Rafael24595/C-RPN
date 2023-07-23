#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "NodeLinear.cpp"
#include "VectorStack.cpp"
#include "VectorQueue.cpp"
#include "Tools.cpp"
#include "OperatorTable.h"

class Rpn {

	private:

		VectorStack<char> stack;
		VectorQueue<char> queue;

		void EvalueChar(char ch) {
			if (Tools::IsNumber(ch) || Tools::IsSeparator(ch) || Tools::IsBlankSpace(ch)) {
				return EvalueDigit(ch);
			}
			if (Tools::IsOperator(ch)) {
				return EvalueOperator(ch);
			}
			if (Tools::IsOpenParenthesis(ch)) {
				return EvalueOpenParenthesis(ch);
			}
			if (Tools::IsCloseParenthesis(ch)) {
				return EvalueCloseParenthesis(ch);
			}
		}

		void EvalueDigit(char ch) {
			queue.Insert(ch);
		}

		void EvalueOperator(char ch) {
			stack.Insert(ch);
		}

		void EvalueOpenParenthesis(char ch) {
			stack.Insert(ch);
		}

		void EvalueCloseParenthesis(char ch) {
			Optional<NodeLinear<char>> node = stack.Remove();
			if (Tools::IsOpenParenthesis(ch)) {
				return;
			}
			if (node.IsNone()) {
				throw std::runtime_error("Close parenthesis without initialization detected.");
			}
			char* next = node.Unwrap()->GetValue();
			if (!Tools::IsOpenParenthesis(*next)) {
				queue.Insert(*next);
			}
			return EvalueCloseParenthesis(*next);
		}

	public:

		Rpn() {
			stack = VectorStack<char>();
			queue = VectorQueue<char>();
		}

		static Rpn Transform(string expression) {
			Rpn rpn = Rpn();
			for (int i = 0; i < expression.size(); i++) {
				char ch = expression[i];
				rpn.EvalueChar(ch);
			}
			return rpn;
		}

		void Print() {
			Optional<NodeLinear<char>> node = queue.Remove();
			while (node.IsSome()) {
				char element = *node.Unwrap()->GetValue();
				cout << element;
				node = queue.Remove();
			}
		}

};

