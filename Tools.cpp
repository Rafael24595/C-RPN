#pragma once
class Tools {

	public:

		static bool IsOpenParenthesis(char ch) {
			if (ch == '(') {
				return true;
			}
			return false;
		}

		static bool IsCloseParenthesis(char ch) {
			if (ch == ')') {
				return true;
			}
			return false;
		}

		static bool IsBlankSpace(char ch) {
			if (ch == '\s' || ch == ' ') {
				return true;
			}
			return false;
		}

		static bool IsSeparator(char ch) {
			if (ch == '.' || ch == ',') {
				return true;
			}
			return false;
		}

		static bool IsNumber(char ch) {
			if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '9') {
				return true;
			}
			return false;
		}

		static bool IsOperator(char ch) {
			if (ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-') {
				return true;
			}
			return false;
		}

};