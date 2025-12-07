#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <set>

using namespace std;
using result_data = tuple<int, set<int>>; // sum and subset

int retrieve_candidate_sum_from_binary(set<int> numbers, vector<int> binary_numbers);
set<int> retrieve_candidate_subset_from_binary(set<int> numbers, vector<int> binary_numbers);
result_data retrieve_candidate_from_binary(set<int> numbers, vector<int> binary_numbers);
float retrieve_candidate_fitness_from_binary(set<int> numbers, vector<int> binary_numbers, int target_sum);
vector<int> retrieve_best_generational_candidate(vector<vector<int>> generation, set<int> numbers, int target_sum);
vector<vector<int>> initialize_population(int cardinality_set);
result_data genetic_subset_sum(int target_sum, set<int> numbers);

#endif // GENETIC_ALGORITHM_HPP
