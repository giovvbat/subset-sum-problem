#include <iostream>
#include <iomanip>
#include <set>
#include "../include/approximation-algorithm.hpp"
#include "../include/exact-algorithm.hpp"
#include "../include/instance-generator.hpp"
#include "../include/log-generator.hpp"

using namespace std;
using instance_data = tuple<int, int, set<int>>; // target sum, total sum and total set
// using resulting_approximation_candidate = tuple<int, set<int>>; --- found sum and found subset

#define EPSILON 0.99

int main() { 
    instance_data instance = generate_instance();
    int exact_result = exact_subset_sum(get<0>(instance), get<2>(instance));
    int approximation_result = approximation_subset_sum(get<0>(instance), get<2>(instance), EPSILON);

    // careful: if not comparative, following log printing function calls must reflect algorithm type of choice!
    generate_approximation_log(get<2>(instance), get<0>(instance), get<1>(instance), approximation_result, EPSILON);
    generate_exact_log(get<2>(instance), get<0>(instance), get<1>(instance), exact_result);
    generate_comparative_log(get<2>(instance), get<0>(instance), get<1>(instance), exact_result, approximation_result, EPSILON);

    cout << "TARGET SUM: " << get<0>(instance) << endl;
    cout << "TOTAL ORIGINAL SET SUM: " << get<1>(instance) << endl << "ORIGINAL SET: { ";

    for (int element : get<2>(instance)) {
        cout << element << " ";
    }

    cout << "}" << endl << endl << "GREAT SUM: " << exact_result << endl;
    cout << "APPROXIMATION SUM: " << approximation_result << " (EPSILON: " << EPSILON << ")" << endl << endl;
    cout << "APPROXIMATION SUM/GREAT SUM = " << std::fixed << std::setprecision(4) << static_cast<double>(approximation_result) / exact_result << std::endl;

    return 0;
}
