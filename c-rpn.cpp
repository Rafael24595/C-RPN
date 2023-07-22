#include <iostream>
#include "Rpn.cpp"

int main() {
    try {
        Rpn rpn = Rpn::Transform("1+(2-3+4)");
        rpn.Print();
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
}
