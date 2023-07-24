#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "VectorStack.cpp"
#include "VectorQueue.cpp"
#include "Tools.cpp"
#include "OperatorTable.h"

class Postfix {

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
			Optional<char> previous = queue.ViewTail();
			if (previous.IsNone() || !(Tools::IsBlankSpace(*previous.Unwrap()) && Tools::IsBlankSpace(ch))) {
				queue.Insert(ch);
			}
		}

		void EvalueOperator(char ch) {
			Optional<int> actualPrecedence = OperatorTable::GetPrecedence(ch);
			if (actualPrecedence.IsNone()) {
				throw std::runtime_error("Unknown operator " + ch);
			}

			bool pushQueue = EvalueOperatorPrecedence(ch, *actualPrecedence.Unwrap());
			if (pushQueue) {
				Optional<char> lastOperator = stack.Remove();
				queue.Insert(lastOperator.Unwrap());
			}

			stack.Insert(ch);
		}

		bool EvalueOperatorPrecedence(char ch, int actualPrecedence) {
			Optional<char> oLastOperator = stack.Get();
			if (oLastOperator.IsSome()) {
				char* lastOperator = oLastOperator.Unwrap();
				Optional<int> oLastPrecedence = OperatorTable::GetPrecedence(*lastOperator);
				if (oLastPrecedence.IsSome()) {
					int lastPrecedence = *oLastPrecedence.Unwrap();
					return EvalueOperatorAssociativity(ch, actualPrecedence, lastPrecedence);
				}
			}

			return false;
		}

		bool EvalueOperatorAssociativity(char ch, int actualPrecedence, int lastPrecedence) {
			Optional<bool> actualAssociativity = OperatorTable::GetAssociativity(ch);
			if (actualAssociativity.IsNone()) {
				throw std::runtime_error("Unknown operator " + ch);
			}

			if (*actualAssociativity.Unwrap() && actualPrecedence <= lastPrecedence) {
				return true;
			}

			if (!*actualAssociativity.Unwrap() && lastPrecedence > actualPrecedence) {
				return true;
			}

			return false;
		}

		void EvalueOpenParenthesis(char ch) {
			stack.Insert(ch);
		}

		void EvalueCloseParenthesis(char ch) {
			Optional<char> element = stack.Remove();
			if (element.IsNone()) {
				throw std::runtime_error("Close parenthesis without initialization detected.");
			}
			if (Tools::IsOpenParenthesis(*element.Unwrap())) {
				return;
			}
			if (!Tools::IsOpenParenthesis(*element.Unwrap())) {
				queue.Insert(*element.Unwrap());
			}
			return EvalueCloseParenthesis(*element.Unwrap());
		}

		void PullStack() {
			Optional<char> node = stack.Remove();
			queue.Insert(' ');
			while (node.IsSome()) {
				queue.Insert(*node.Unwrap());
				node = stack.Remove();
				if (node.IsSome()) {
					queue.Insert(' ');
				}
			}
		}

	public:

		Postfix() {
			stack = VectorStack<char>();
			queue = VectorQueue<char>();
		}

		static Postfix Transform(string expression) {
			Postfix postfix = Postfix();
			for (int i = 0; i < expression.size(); i++) {
				char ch = expression[i];
				postfix.EvalueChar(ch);
			}
			postfix.PullStack();
			return postfix;
		}

		void Print() {
			Optional<char> oActual = queue.Remove();
			while (oActual.IsSome()) {
				char actual = *oActual.Unwrap();
				cout << actual;
				oActual = queue.Remove();
			}
		}

};