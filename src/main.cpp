#include <iostream>
#include <iomanip>
#include <set>
#include "../include/approximation-algorithm.hpp"
#include "../include/exact-algorithm.hpp"
#include "../include/genetic-algorithm.hpp"
#include "../include/instance-generator.hpp"
#include "../include/log-generator.hpp"

using namespace std;
using instance_data = tuple<int, int, set<int>>; // target sum, total sum and set
using result = tuple<int, set<int>, double>; // found sum, found subset, execution time
using regular_result = tuple<int, set<int>>; // sum and subset
using genetic_result = tuple<regular_result, int, double>; // sum, subset, number of iterations and execution time

#define EPSILON 0.99

int main() {
    instance_data instance = generate_instance();

    result exact = exact_subset_sum(get<0>(instance), get<2>(instance));
    result approximation = approximation_subset_sum(get<0>(instance), get<2>(instance), EPSILON);
    genetic_result genetic = genetic_subset_sum(get<0>(instance), get<2>(instance));

    generate_approximation_log(get<2>(instance), get<0>(instance), get<1>(instance), get<0>(approximation), get<1>(approximation), EPSILON, get<2>(approximation));
    generate_exact_log(get<2>(instance), get<0>(instance), get<1>(instance), get<0>(exact), get<1>(exact), get<2>(exact));
    generate_exact_approximation_comparative_log(get<2>(instance), get<0>(instance), get<1>(instance), get<0>(exact), get<0>(approximation), EPSILON, get<2>(exact), get<2>(approximation));
    generate_genetic_log(get<2>(instance), get<0>(instance), get<1>(instance), get<0>(get<0>(genetic)), get<1>(get<0>(genetic)), get<2>(genetic), get<1>(genetic));

    return 0;
}
