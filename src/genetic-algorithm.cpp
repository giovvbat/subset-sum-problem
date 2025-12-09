#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <random>

using namespace std;
using binary_result = tuple<float, vector<int>>; // fitness and binary subset
using regular_result = tuple<int, set<int>>; // sum and subset
using genetic_result = tuple<regular_result, int, double>; // sum, subset, number of iterations and execution time

static thread_local mt19937 gen(random_device{}());

int sum_binary(const set<int>& numbers, const vector<int>& binary_numbers) {
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

regular_result result_binary(const set<int>& numbers, const vector<int>& binary_numbers) {
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

float fitness_binary(const set<int>& numbers, const vector<int>& binary_numbers, int target_sum) {
    int sum = sum_binary(numbers, binary_numbers);

    if (sum > target_sum) {
        return 1.0f / (1.0f + 2 * abs(sum - target_sum)); // 2 é um fator arbitrário de peso
    
    }

    return 1.0f / (1.0f + abs(sum - target_sum));
}

vector<int> best_binary(const vector<binary_result>& generation, const set<int>& numbers, int target_sum) {
    vector<int> best = {}; 
    float best_fitness = 0.0f;

    for (auto current : generation) {
        float current_fitness = get<0>(current);

        if (current_fitness > best_fitness && sum_binary(numbers, get<1>(current)) <= target_sum) {
            best = get<1>(current);
            best_fitness = current_fitness;
        }
    }

    return best;
}

vector<binary_result> initialize_population(const set<int>& numbers, int target_sum, mt19937& gen) {
    bernoulli_distribution bit_value(0.5); // 50% de chance de 1

    vector<binary_result> population = {};
    population.reserve(100);

    while (population.size() < 100) {
        vector<int> current(numbers.size());

        for (int i = 0; i < numbers.size(); i++) {
            current[i] = bit_value(gen) ? 1 : 0;
        }
        
        population.push_back({fitness_binary(numbers, current, target_sum), current});
    
    }

    return population;
}

void apply_elitism(vector<binary_result>& descendants, vector<binary_result>& generation, const set<int>& numbers, int target_sum) {
    int first = -1, second = -1; 
    float first_fitness = -1.0f, second_fitness = -1.0f;

    // finds two best individuals
    for (int i = 0; i < generation.size(); i++) {
        float current_fitness = fitness_binary(numbers, get<1>(generation[i]), target_sum);

        if (current_fitness > first_fitness) {
            second_fitness = first_fitness;
            second = first;

            first_fitness = current_fitness;
            first = i;
        } else if (current_fitness > second_fitness) {
            second_fitness = current_fitness;
            second = i;
        }
    }

    descendants.push_back({first_fitness, get<1>(generation[first])});
    descendants.push_back({second_fitness, get<1>(generation[second])});

    // removes both individuals from original population so they don't take part in selection
    if (first > second) {
        generation.erase(generation.begin() + first);
        generation.erase(generation.begin() + second);
    } else {
        generation.erase(generation.begin() + second);
        generation.erase(generation.begin() + first);
    }
}

binary_result select(const vector<binary_result>& generation, const set<int>& numbers, int target_sum, mt19937& gen) {
    float total_fitness = 0.0f;

    for (auto& individual : generation) {
        total_fitness += fitness_binary(numbers, get<1>(individual), target_sum);
    }

    // fallback: if all fitnesses sum 0, selection is completely random
    if (total_fitness == 0.0f) {
        uniform_int_distribution<int> distribution(0, generation.size() - 1);

        return generation[distribution(gen)];
    }

    // regular roulette selection choice
    uniform_real_distribution<float> pick(0, total_fitness);

    float sorted = pick(gen);
    float cumulative = 0.0f;

    for (binary_result individual : generation) {
        cumulative += fitness_binary(numbers, get<1>(individual), target_sum);

        if (cumulative >= sorted) {
            return individual;
        }
    }

    return generation.back();
}

vector<binary_result> crossover(binary_result mother, binary_result father, set<int>& numbers, int target_sum, mt19937& gen) {
    uniform_int_distribution<int> pick(0, get<1>(mother).size() - 1);
    int point = pick(gen);

    if (point == 0) {
        point++;
    } else if (point == get<1>(mother).size() - 1) {
        point--;
    }

    vector<binary_result> children = {};
    vector<int> first = get<1>(mother);
    vector<int> second = get<1>(father);

    for (int i = point; i < get<1>(father).size(); i++) {
        first[i] = get<1>(father)[i];
    }

    for (int i = point; i < get<1>(mother).size(); i++) {
        second[i] = get<1>(mother)[i];
    }

    children.push_back({fitness_binary(numbers, first, target_sum), first});
    children.push_back({fitness_binary(numbers, second, target_sum), second});

    return children;
}

void mutate(binary_result& individual, mt19937& gen) {
    bernoulli_distribution flip_bit(float (1.0f / get<1>(individual).size()));

    for (int& gene : get<1>(individual)) {
        if (flip_bit(gen)) {
            if (gene == 1) {
                gene = 0;
            } else {
                gene = 1;
            }
        }
    }
}

genetic_result genetic_subset_sum(int target_sum, set<int> numbers) {
    auto start = chrono::steady_clock::now();
    
    vector<binary_result> population = initialize_population(numbers, target_sum, gen);
    vector<binary_result> descendents = {};

    vector<int> best = best_binary(population, numbers, target_sum);
    int imutable = 0, generation = 0;

    while (generation < 500 && imutable < 100) {
        // applying elitism for next generation
        apply_elitism(descendents, population, numbers, target_sum);

        while (descendents.size() < 100) {
            binary_result mother = select(population, numbers, target_sum, gen);
            binary_result father = select(population, numbers, target_sum, gen);

            for (binary_result child : crossover(mother, father, numbers, target_sum, gen)) {
                mutate(child, gen);
                descendents.push_back(child);
            }
        }

        vector<int> current_best = best_binary(descendents, numbers, target_sum);

        if (sum_binary(numbers, current_best) == target_sum) {
            auto end = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;

            return {result_binary(numbers, current_best), generation, elapsed_seconds.count()};
        } else if (best == current_best) {
            imutable++;
        } else {
            imutable = 0;
            best = current_best;
        }

        population = descendents;
        descendents.clear();
        generation++;
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    
    return {result_binary(numbers, best), generation, elapsed_seconds.count()};
}
