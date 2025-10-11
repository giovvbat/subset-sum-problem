#include <iostream>
#include <random>
#include "../include/insertion-set.hpp"

using namespace std;
using test_case = tuple<int, int, insertion_set<int>>; // set, total sum and target sum

#define MINIMUM_ELEMENT_RANGE 0 // fixed
#define MAXIMUM_ELEMENT_RANGE 1000 // changeable
#define CARDINALITY_RANGE 1, 25 // fixed, changeable
#define MINIMUM_RESTRICTED_SUM 1 // fixed

test_case generate_instance() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> cardinality_distribution(CARDINALITY_RANGE);
    std::uniform_int_distribution<int> element_distribution(MINIMUM_ELEMENT_RANGE, MAXIMUM_ELEMENT_RANGE);
    
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

    std::uniform_int_distribution<int> target_sum_distribution(MINIMUM_RESTRICTED_SUM, max((double) MINIMUM_RESTRICTED_SUM, total_set_sum * 1.5));

    return {target_sum_distribution(gen), total_set_sum, total_set};
}
