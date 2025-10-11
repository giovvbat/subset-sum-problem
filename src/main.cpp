#include <iostream>
#include "../include/insertion_set.hpp"
#include "approximation-algorithm.cpp"
#include "instance_generator.cpp"

using namespace std;
using set_data = tuple<int, insertion_set<int>>; // sum and set

int main() { 
    set_data instance = generate_instance();
    set_data result = subset_sum(get<0>(instance), get<1>(instance));

    cout << "total set is = { ";

    for (int element : get<1>(instance)) {
        cout << element << " ";
    }

    cout << "}" << endl << "target sum is " << get<0>(instance) << endl << endl << "subset sum is = { ";

    for (int element : get<1>(result)) {
        cout << element << " ";
    }

    cout << "}" << endl << "found sum is " << get<0>(result);

    return 0;
}