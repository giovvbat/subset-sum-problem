#include <iostream>
#include "../include/insertion-set.hpp"
#include "approximation-algorithm.cpp"
#include "instance-generator.cpp"
#include "log-generator.cpp"

using namespace std;
using set_data = tuple<int, int, insertion_set<int>>; // target sum, total sum and total set
using candidate = tuple<int, insertion_set<int>>; // found sum and found subset

#define EPSILON 0.9

int main() { 
    set_data instance = generate_instance();
    candidate result = subset_sum(get<0>(instance), get<2>(instance), EPSILON);
    generate_log(get<2>(instance), get<0>(instance), get<1>(instance), EPSILON, get<1>(result), get<0>(result));

    cout << "EPSILON: " << EPSILON << endl;
    cout << "TARGET SUM: " << get<0>(instance) << endl;
    cout << "TOTAL ORIGINAL SET SUM: " << get<1>(instance) << endl;
    cout << "ORIGINAL SET: { ";

    for (int element : get<2>(instance)) {
        cout << element << " ";
    }

    cout << "}" << endl << endl << "FOUND SUM: " << get<0>(result) << endl;
    cout << "FOUND SUBSET: { ";

    for (int element : get<1>(result)) {
        cout << element << " ";
    }

    cout << "}";

    return 0;
}
