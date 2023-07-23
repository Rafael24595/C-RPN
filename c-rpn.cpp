#include <iostream>
#include "Rpn.cpp"

int main() {
    try {
        Rpn rpn = Rpn::Transform("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3");
        rpn.Print();
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
}