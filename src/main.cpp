#include <iostream>
#include "../include/insertion-set.hpp"
#include "approximation-algorithm.cpp"
#include "instance-generator.cpp"

using namespace std;
using set_data = tuple<int, int, insertion_set<int>>; // target sum, total sum and total set
using candidate = tuple<int, insertion_set<int>>; // found sum and found subset

#define EPSILON 0.2

int main() { 
    set_data instance = generate_instance();
    candidate result = subset_sum(get<0>(instance), get<2>(instance), EPSILON);

    cout << "TARGET: " << get<0>(instance) << endl;
    cout << "TOTAL: " << get<1>(instance) << endl;
    cout << "SET: { ";
    
    for (int element : get<2>(instance)) {
        cout << element << " ";
    }
    
    cout << "}" << endl << "FOUND: " << get<0>(result) << endl;

    return 0;
}
