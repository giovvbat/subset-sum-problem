#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <vector>
#include <set>
#include <cmath>
#include <random>

using namespace std;
using binary_result = tuple<float, vector<int>>; // fitness and binary subset
using regular_result = tuple<int, set<int>>; // sum and subset
using genetic_result = tuple<regular_result, int, double>; // sum, subset, number of iterations and execution time

static thread_local mt19937 gen(std::random_device{}());

int sum_binary(const set<int>& numbers, const vector<int>& binary_numbers);
regular_result result_binary(const set<int>& numbers, const vector<int>& binary_numbers);
float fitness_binary(const set<int>& numbers, const vector<int>& binary_numbers, int target_sum);
vector<int> best_binary(const vector<binary_result>& generation, const set<int>& numbers, int target_sum);
vector<binary_result> initialize_population(const set<int>& numbers, int population_size, int target_sum, mt19937& gen);
void apply_elitism(vector<binary_result>& descendants, vector<binary_result>& generation, const set<int>& numbers, int target_sum);
vector<binary_result> crossover(binary_result mother, binary_result father, const set<int>& numbers, int target_sum, mt19937& gen);
void mutate(binary_result& individual, mt19937& gen);
genetic_result genetic_subset_sum(int target_sum, set<int> numbers);


#endif // GENETIC_ALGORITHM_HPP
