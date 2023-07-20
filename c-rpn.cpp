#include <iostream>
#include "Optional.cpp"
#include "NodeLinear.cpp"
#include "CollectionStack.cpp"

int main() {
    Optional<int> op1 = Optional<int>::Some(new int(2));
    Optional<int> op2 = Optional<int>::Some(new int(3));

    NodeLinear<int> n1 = NodeLinear<int>(new int(0));
    n1.SetElement(new int(1));
    NodeLinear<int> n2 = NodeLinear<int>(new int(0));
    n2.SetElement(new int(2));
    n1.SetReference(&n2);

    NodeLinear<int> reference = *n1.GetReference().Unwrap();

    CollectionStack<int> collection = CollectionStack<int>();

    std::cout << "Conuter: " << collection.Length();
    std::cout << "\n";

    NodeLinear<int> nI = NodeLinear<int>(new int(1));
    collection.Insert(nI);

    std::cout << "Conuter: " << collection.Length();
    std::cout << "\n";

    NodeLinear<int> nII = NodeLinear<int>(new int(2));
    collection.Insert(nII);

    std::cout << "Conuter: " << collection.Length();
    std::cout << "\n";

    NodeLinear<int> nIII = NodeLinear<int>(new int(3));
    collection.Insert(nIII);

    std::cout << "Conuter: " << collection.Length();
    std::cout << "\n";

    collection.Delete();

    std::cout << "Conuter: " << collection.Length();
    std::cout << "\n";

    int sum1 = *op1.Unwrap() + *op2.Unwrap();
    int sum2 = *n1.GetElement() + *reference.GetElement();
    std::cout << "Value of sum1 is: " << sum1;
    std::cout << "\n";
    std::cout << "Value of sum2 is: " << sum2;
}
