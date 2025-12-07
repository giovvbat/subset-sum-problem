#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <unordered_set>

using namespace std;
using result_data = tuple<int, set<int>>; // sum and subset

set<int> retrieve_candidate_subset_from_binary(set<int> numbers, vector<int> binary_numbers) {
    set<int> candidate_subset = {};
    auto iterator = numbers.begin();

    for (int i = 0; i < binary_numbers.size(); i++) {
        if (binary_numbers[i] == 1) {
            candidate_subset.insert(*iterator);
        }

        iterator++;
    }

    return candidate_subset;
}

result_data retrieve_candidate_from_binary(set<int> numbers, vector<int> binary_numbers) {
    set<int> candidate_subset = {};
    int candidate_sum = 0;
    auto iterator = numbers.begin();

    for (int i = 0; i < binary_numbers.size(); i++) {
        if (binary_numbers[i] == 1) {
            candidate_subset.insert(*iterator);
            candidate_sum += candidate_sum;
        }

        iterator++;
    }

    return {candidate_sum, candidate_subset};
}

int retrieve_candidate_sum_from_binary(set<int> numbers, vector<int> binary_numbers) {
    int candidate_sum = 0;
    auto iterator = numbers.begin();

    for (int i = 0; i < binary_numbers.size(); i++) {
        if (binary_numbers[i] == 1) {
            candidate_sum += *iterator;
        }

        iterator++;
    }

    return candidate_sum;
}

float retrieve_candidate_fitness_from_binary(set<int> numbers, vector<int> binary_numbers, int target_sum) {
    int candidate_sum = retrieve_candidate_sum_from_binary(numbers, binary_numbers);

    if (candidate_sum <= target_sum) {
        return candidate_sum / target_sum;
    } else {
        return 0;
    }
}

vector<int> retrieve_best_generational_candidate(vector<vector<int>> generation, set<int> numbers, int target_sum) {
    vector<int> best = {}; 
    float best_fitness = retrieve_candidate_fitness_from_binary(numbers, best, target_sum);

    for (vector<int> current : generation) {
        float current_fitness = retrieve_candidate_fitness_from_binary(numbers, current, target_sum);

        if (current_fitness > best_fitness) {
            best = current;
            best_fitness = current_fitness;
        }
    }

    return best;
}

vector<vector<int>> initialize_population(int cardinality_set) {
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution bit_value(0.5); // 50% de chance de 1

    vector<vector<int>> population = {};
    population.reserve(80);

    set<vector<int>> seen = {};

    while (population.size() < 80) {
        vector<int> current(cardinality_set);

        for (int i = 0; i < cardinality_set; i++) {
            current[i] = bit_value(gen) ? 1 : 0;
        }

        if (seen.find(current) == seen.end()) {
            seen.insert(current);
            population.push_back(current);
        }
    }

    return population;
}

result_data genetic_subset_sum(int target_sum, set<int> numbers) {
    return {};
}