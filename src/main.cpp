#include <iostream>
#include "../include/insertion_set.hpp"
#include "approximation-algorithm.cpp"

int main() { 
    insertion_set<int> numbers = {25, 22, 20, 18, 16, 14, 12, 10, 8, 7, 5};
    insertion_set<int> result = subset_sum(numbers, 50);

    cout << "{ ";

    for (int element : result) {
        cout << element << " ";
    }

    cout << "}";

    return 0;
}