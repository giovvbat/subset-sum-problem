#include <iostream>
#include <iomanip>
#include <set>
#include "../include/approximation-algorithm.hpp"
#include "../include/exact-algorithm.hpp"
#include "../include/genetic-algorithm.hpp"
#include "../include/instance-generator.hpp"
#include "../include/log-generator.hpp"

using namespace std;
using instance_data = tuple<int, int, set<int>>; // target sum, total sum and total set
using result = tuple<int, set<int>, double>; // found sum, found subset, execution time

#define EPSILON 0.99

int main() {
    instance_data instance = generate_instance();
    
    result exact_result = exact_subset_sum(get<0>(instance), get<2>(instance));
    result approximation_result = approximation_subset_sum(get<0>(instance), get<2>(instance), EPSILON);

    generate_approximation_log(get<2>(instance), get<0>(instance), get<1>(instance), get<0>(approximation_result), get<1>(approximation_result), EPSILON, get<2>(approximation_result));
    generate_exact_log(get<2>(instance), get<0>(instance), get<1>(instance), get<0>(exact_result), get<1>(exact_result), get<2>(exact_result));
    generate_exact_approximation_comparative_log(get<2>(instance), get<0>(instance), get<1>(instance), get<0>(exact_result), get<0>(approximation_result), EPSILON, get<2>(exact_result), get<2>(approximation_result));

    return 0;
}
