#include <iostream>
#include "Optional.cpp"
#include "NodeLinear.cpp"

int main() {
    Optional<int> op1 = Optional<int>::Some(new int(2));
    Optional<int> op2 = Optional<int>::Some(new int(3));

    NodeLinear<int> n1 = NodeLinear<int>(new int(0));
    n1.SetElement(new int(1));
    NodeLinear<int> n2 = NodeLinear<int>(new int(0));
    n2.SetElement(new int(2));
    n1.SetReference(&n2);

    NodeLinear<int> reference = *n1.GetReference().Unwrap();

    int sum1 = *op1.Unwrap() + *op2.Unwrap();
    int sum2 = *n1.GetElement() + *reference.GetElement();
    std::cout << "Value of sum1 is: " << sum1;
    std::cout << "\n";
    std::cout << "Value of sum2 is: " << sum2;
}
