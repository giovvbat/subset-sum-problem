#ifndef LOG_GENERATOR_HPP
#define LOG_GENERATOR_HPP

#include <set>

using namespace std;

void generate_approximation_log(set<int> original_set, int target_sum, int total_original_set_sum, double epsilon, set<int> found_subset, int found_sum);
void generate_exact_log(set<int> original_set, int target_sum, int total_original_set_sum, set<int> found_subset, int found_sum);
void generate_comparative_log(int target_sum, int total_original_set_sum, int great_sum, int found_sum, double epsilon);

#endif // LOG_GENERATOR_HPP