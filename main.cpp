#include <iostream>
#include <vector>
#include "Vector.h"

int main() {

    Vector<int> vector {1,2,3,4,5,6,7,8,9};
    std::vector<int> vector2 {1,2,3,4,5,6,7,8,9};

    Vector<int>::iterator it = vector.begin() + 1;
    std::vector<int>::iterator it2 = vector2.begin() + 1;

    Vector<int>::iterator end = vector.begin() + 4;
    std::vector<int>::iterator end1 = vector2.begin() + 4;
    
    vector.erase(it, end);
    vector2.erase(it2, end1);


    for (int x : vector)
        std::cout << x << " ";


    for (int x : vector2)
        std::cout << x << " " ;




}