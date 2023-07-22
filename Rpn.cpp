#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "NodeLinear.cpp"
#include "CollectionStack.cpp"
#include "CollectionQueue.cpp"
#include "Tools.cpp"
#include "OperatorTable.cpp"

class Rpn {

	private:

		CollectionStack<char> stack;
		CollectionQueue<char> queue;

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
			Optional<NodeLinear<char>> node = stack.Delete();
			if (Tools::IsOpenParenthesis(ch)) {
				return;
			}
			if (node.IsNone()) {
				throw std::runtime_error("Close parenthesis without initialization detected.");
			}
			char* next = node.Unwrap()->GetElement();
			if (!Tools::IsOpenParenthesis(*next)) {
				queue.Insert(*next);
			}
			return EvalueCloseParenthesis(*next);
		}

	public:

		Rpn() {
			stack = CollectionStack<char>();
			queue = CollectionQueue<char>();
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
			Optional<NodeLinear<char>> node = queue.Delete();
			while (node.IsSome()) {
				char element = *node.Unwrap()->GetElement();
				cout << element;
				node = queue.Delete();
			}
		}

};

