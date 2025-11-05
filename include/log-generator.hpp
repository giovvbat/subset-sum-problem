#ifndef LOG_GENERATOR_HPP
#define LOG_GENERATOR_HPP

#include "../include/insertion-set.hpp"

void generate_log(insertion_set<int> original_set, int target_sum, int total_original_set_sum, double epsilon, insertion_set<int> found_subset, int found_sum);

#endif // LOG_GENERATOR_HPP