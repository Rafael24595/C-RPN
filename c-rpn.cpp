#include <iostream>
#include "Optional.cpp"

int main() {
    Optional<int> op1 = Optional<int>::Some(new int(2));
    Optional<int> op2 = Optional<int>::Some(new int(3));
    int sum = op1.Unwrap() + op2.Unwrap();
    std::cout << "Value of sum is: " << sum;
}
