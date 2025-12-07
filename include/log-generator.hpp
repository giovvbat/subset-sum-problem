#ifndef LOG_GENERATOR_HPP
#define LOG_GENERATOR_HPP

#include <set>

using namespace std;

void generate_approximation_log(set<int> original_set, int target_sum, int total_original_set_sum, int found_sum, set<int> found_subset, double epsilon, double execution_time);
void generate_exact_log(set<int> original_set, int target_sum, int total_original_set_sum, int great_sum, set<int> great_subset, double execution_time);
void generate_exact_approximation_comparative_log(set<int> original_set, int target_sum, int total_original_set_sum, int great_sum, int found_sum, double epsilon, double exact_execution_time, double approximation_execution_time);

#endif // LOG_GENERATOR_HPP