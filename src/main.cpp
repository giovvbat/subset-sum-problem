#include <iostream>
#include <set>
#include "../include/approximation-algorithm.hpp"
#include "../include/exact-algorithm.hpp"
#include "../include/instance-generator.hpp"
#include "../include/log-generator.hpp"

using namespace std;
using set_data = tuple<int, int, set<int>>; // target sum, total sum and total set
using resulting_approximation_candidate = tuple<int, set<int>>; // found sum and found subset

#define EPSILON 0.4

int main() { 
    set_data instance = generate_instance();
    int exact_result = exact_subset_sum(get<0>(instance), get<2>(instance));
    resulting_approximation_candidate approximation_result = approximation_subset_sum(get<0>(instance), get<2>(instance), EPSILON);

    // careful: if not comparative, following log printing function must reflect algorithm type of choice!
    generate_exact_log(get<2>(instance), get<0>(instance), get<1>(instance), exact_result);
    
    // generate_comparative_log(get<0>(instance), get<1>(instance), exact_result, get<0>(approximation_result), EPSILON);

    cout << "ALGORITHM CHOICE: EXACT\n" << endl; // --- exclusive to exact algorithm

    // cout << "EPSILON: " << EPSILON << endl; --- information exclusive to approximation algorithm
    cout << "TARGET SUM: " << get<0>(instance) << endl;
    cout << "TOTAL ORIGINAL SET SUM: " << get<1>(instance) << endl;
    cout << "ORIGINAL SET: { ";

    for (int element : get<2>(instance)) {
        cout << element << " ";
    }

    cout << "}" << endl << endl << "GREAT SUM: " << exact_result << endl;

    return 0;
}
