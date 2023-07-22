#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "NodeLinear.cpp"
#include "CollectionStack.cpp"
#include "CollectionQueue.cpp"
#include "Tools.cpp"

class Rpn {

	private:

		CollectionStack<char> stack;
		CollectionQueue<char> queue;

		void EvalueChar(char ch) {
			if (Tools::IsNumber(ch) || Tools::IsSeparator(ch) || Tools::IsOpenParenthesis(ch) || Tools::IsBlankSpace(ch)) {
				return EvalueDigit(ch);
			}
			if (Tools::IsOperator(ch)) {
				return EvalueOperator(ch);
			}
			if (Tools::IsCloseParenthesis(ch)) {
				return EvalueParenthesis(ch);
			}
		}

		void EvalueDigit(char ch) {
			queue.Insert(ch);
		}

		void EvalueOperator(char ch) {
			return;
		}

		void EvalueParenthesis(char ch) {
			return;
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

