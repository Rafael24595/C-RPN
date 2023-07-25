#include <iostream>
#include "Postfix.hpp"
#include "Infix.hpp"

int main() {
    try {
        string p = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
        cout << "Infix expression: \n\t" + p;
        Postfix postfix = Postfix::Transform(p);
        cout << "\nTo postfix:\n\t";
        postfix.Print();

        cout << "\n\n";

        string i = "3 4 2 * 1 5 - 2 3 ^ ^ / +";
        cout << "Postfix expression: \n\t" + i;
        Infix infix = Infix::Transform(i);
        cout << "\nTo infix:\n\t";
        infix.Print();
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
}