#include "Tools.hpp"

bool Tools::IsOpenParenthesis(char ch) {
	if (ch == '(') {
		return true;
	}
	return false;
}

bool Tools::IsCloseParenthesis(char ch) {
	if (ch == ')') {
		return true;
	}
	return false;
}

bool Tools::IsBlankSpace(char ch) {
	if (ch == '\s' || ch == ' ') {
		return true;
	}
	return false;
}

bool Tools::IsSeparator(char ch) {
	if (ch == '.' || ch == ',') {
		return true;
	}
	return false;
}

bool Tools::IsLetter(char ch) {
	return IsLetterLowerCase(ch) || IsLetterUpperCase(ch);
}

bool Tools::IsLetterLowerCase(char ch) {
	int ascii = int(ch);
	if (ascii >= ASCII_a && ascii <= ASCII_z) {
		return true;
	}
	return false;
}

bool Tools::IsLetterUpperCase(char ch) {
	int ascii = int(ch);
	if (ascii >= ASCII_A && ascii <= ASCII_Z) {
		return true;
	}
	return false;
}

bool Tools::IsNumber(char ch) {
	int ascii = int(ch);
	if (ascii >= ASCII_1 && ascii < ASCII_9) {
		return true;
	}
	return false;
}

bool Tools::IsOperator(char ch) {
	if (ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-') {
		return true;
	}
	return false;
}