#include <iostream>
#include <vector>
#include "Vector.h"

int main() {

    Vector<int> first {1,2,3};

    std::cout << first.front() << std::endl;
    std::cout << first.back() << std::endl;
    std::cout << first.capacity() << std::endl;
    std::cout << first.size() << std::endl;
    std::cout << (first == first) << std::endl;
    std::cout << (first != first) << std::endl << std::endl;

    Vector<int> second {4,5,6};
    Vector<int> third(second);

    for (int i = 0; i < third.size(); i++)
        std::cout << third.front() << " ";




}