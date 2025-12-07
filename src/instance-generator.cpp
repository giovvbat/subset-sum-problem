#include <iostream>
#include <random>
#include <set>

using namespace std;
using instance_data = tuple<int, int, set<int>>; // target sum, total sum and set

#define MINIMUM_ELEMENT_RANGE 2
#define MAXIMUM_ELEMENT_RANGE 1000
#define MINIMUM_CARDINALITY_RANGE 10
#define MAXIMUM_CARDINALITY_RANGE 15

instance_data generate_instance() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> cardinality_distribution(MINIMUM_CARDINALITY_RANGE, MAXIMUM_CARDINALITY_RANGE);
    uniform_int_distribution<int> element_distribution(MINIMUM_ELEMENT_RANGE, MAXIMUM_ELEMENT_RANGE);
    
    set<int> total_set = {};
    int set_cardinality = cardinality_distribution(gen), total_set_sum = 0, current_set_cardinality = 0;

    while (current_set_cardinality != set_cardinality) {
        int current_set_element = element_distribution(gen);

        if (!total_set.insert(current_set_element).second) {
            continue;
        } 

        current_set_cardinality++;
        total_set_sum += current_set_element;
    }

    uniform_int_distribution<int> target_sum_distribution(0, 1.5 * total_set_sum);

    return {target_sum_distribution(gen), total_set_sum, total_set};
}
