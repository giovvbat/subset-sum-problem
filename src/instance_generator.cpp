#include <iostream>
#include <random>
#include "../include/insertion_set.hpp"

using namespace std;
using test_case = tuple<int, insertion_set<int>>; // set and target sum

#define minimum_element_range 0 // fixed
#define maximum_element_range 15 // changeable
#define cardinality_range 1, 10 // fixed, changeable
#define minimum_restricted_sum 1 // fixed

test_case generate_instance() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> cardinality_distribution(cardinality_range);
    std::uniform_int_distribution<int> element_distribution(minimum_element_range, maximum_element_range);
    
    insertion_set<int> total_set = {};
    int set_cardinality = cardinality_distribution(gen), total_set_sum = 0, current_set_cardinality = 0;

    while (current_set_cardinality != set_cardinality) {
        int current_set_element = element_distribution(gen);

        if (!total_set.insert(current_set_element)) {
            continue;
        } 

        current_set_cardinality++;
        total_set_sum += current_set_element;
    }

    std::uniform_int_distribution<int> target_sum_distribution(minimum_restricted_sum, max(minimum_restricted_sum, total_set_sum * 2));

    return {target_sum_distribution(gen), total_set};
}