#pragma once

class Tools {

	private:
		static const int ASCII_a = 97;
		static const int ASCII_z = 122;
		static const int ASCII_A = 65;
		static const int ASCII_Z = 90;
		static const int ASCII_1 = 48;
		static const int ASCII_9 = 57;

	public:
		static bool IsOpenParenthesis(char ch);
		static bool IsCloseParenthesis(char ch);
		static bool IsBlankSpace(char ch);
		static bool IsSeparator(char ch);
		static bool IsLetter(char ch);
		static bool IsLetterLowerCase(char ch);
		static bool IsLetterUpperCase(char ch);
		static bool IsNumber(char ch);
		static bool IsOperator(char ch);

};