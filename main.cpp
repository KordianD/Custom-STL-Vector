#include <iostream>
#include <vector>
#include "Vector.h"

int main() {

    Vector<int> first {1,2,3,4,5,6};

    Vector<int>::iterator it = first.begin();


    for (it; it != first.end(); it++)
        std::cout << *it << std::endl;

    std::cout << std::endl;

    for (int x : first)
        std::cout << x << std::endl;


}