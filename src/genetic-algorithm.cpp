#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <unordered_set>

using namespace std;
using binary_result = tuple<float, vector<int>>; // fitness and binary subset
using regular_result = tuple<int, set<int>>; // sum and subset

int sum_binary(set<int> numbers, vector<int> binary_numbers) {
    int sum = 0;
    auto iterator = numbers.begin();

    for (int i = 0; i < binary_numbers.size(); i++) {
        if (binary_numbers[i] == 1) {
            sum += *iterator;
        }

        iterator++;
    }

    return sum;
}

set<int> subset_binary(set<int> numbers, vector<int> binary_numbers) {
    set<int> subset = {};
    auto iterator = numbers.begin();

    for (int i = 0; i < binary_numbers.size(); i++) {
        if (binary_numbers[i] == 1) {
            subset.insert(*iterator);
        }

        iterator++;
    }

    return subset;
}

regular_result result_binary(set<int> numbers, vector<int> binary_numbers) {
    set<int> subset = {};
    int sum = 0;
    auto iterator = numbers.begin();

    for (int i = 0; i < binary_numbers.size(); i++) {
        if (binary_numbers[i] == 1) {
            subset.insert(*iterator);
            sum += *iterator;
        }

        iterator++;
    }

    return {sum, subset};
}

float fitness_binary(set<int> numbers, vector<int> binary_numbers, int target_sum) {
    int candidate_sum = sum_binary(numbers, binary_numbers);

    if (candidate_sum <= target_sum) {
        return candidate_sum / target_sum;
    } else {
        return 0;
    }
}

vector<int> best_binary(vector<binary_result> generation, set<int> numbers, int target_sum) {
    vector<int> best = {}; 
    float best_fitness = 0;

    for (auto current : generation) {
        float current_fitness = fitness_binary(numbers, get<1>(current), target_sum);

        if (current_fitness > best_fitness) {
            best = get<1>(current);
            best_fitness = current_fitness;
        }
    }

    return best;
}

vector<binary_result> initialize_population(set<int> numbers, int cardinality_set, int target_sum) {
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution bit_value(0.5); // 50% de chance de 1

    vector<binary_result> population = {};
    population.reserve(100);

    set<vector<int>> seen = {};

    while (population.size() < 100) {
        vector<int> current(cardinality_set);

        for (int i = 0; i < cardinality_set; i++) {
            current[i] = bit_value(gen) ? 1 : 0;
        }

        if (seen.find(current) == seen.end()) {
            seen.insert(current);
            population.push_back({fitness_binary(numbers, current, target_sum), current});
        }
    }

    return population;
}

void apply_elitism(vector<binary_result>& descendants, vector<binary_result>& generation, set<int> numbers, int target_sum) {
    vector<int> first = {}, second = {}; 
    float first_fitness = 0, second_fitness = 0;

    // finds two best individuals
    for (auto& current : generation) {
        float current_fitness = fitness_binary(numbers, get<1>(current), target_sum);

        if (current_fitness > first_fitness) {
            second_fitness = first_fitness;
            second = first;

            first_fitness = current_fitness;
            first = get<1>(current);
        } else if (current_fitness > second_fitness) {
            second_fitness = current_fitness;
            second = get<1>(current);
        }
    }

    descendants.push_back({first_fitness, first});
    descendants.push_back({second_fitness, second});
}

regular_result genetic_subset_sum(int target_sum, set<int> numbers) {
    vector<binary_result> population = initialize_population(numbers, numbers.size(), target_sum);
    vector<binary_result> descendents = {};

    vector<int> best = best_binary(population, numbers, target_sum);
    int imutable = 0, generation = 0;

    while (generation < 500 && imutable < 100) {
        // applying elitism for next generation
        apply_elitism(descendents, population, numbers, target_sum);

        vector<int> current_best = best_binary(population, numbers, target_sum);

        if (sum_binary(numbers, current_best) == target_sum) {
            return {result_binary(numbers, current_best)};
        }

        if (best == current_best) {
            imutable++;
        } else {
            best = current_best;
        }

        population = descendents;
        descendents.clear();
        generation++;
    }
    
    return {result_binary(numbers, best)};
}