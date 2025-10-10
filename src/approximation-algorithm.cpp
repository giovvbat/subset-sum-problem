#include <iostream>
#include "../include/insertion_set.hpp"

using namespace std;
using candidate = tuple<int, insertion_set<int>>; // sum and subset

#define epsilon 0.2

bool custom_sort(tuple<int, insertion_set<int>> first_element, tuple<int, insertion_set<int>> second_element) { 
    return get<0>(first_element) < get<0>(second_element); 
}

void trim_all_candidates(vector<candidate>& all_candidates) {
    int current_earlier_comparison_index = 0;
    int current_later_comparison_index = 1;
    vector<int> indexes_to_be_removed = {};

    while (current_later_comparison_index != all_candidates.size()) {
        int first_element = get<0>(all_candidates[current_earlier_comparison_index]);
        int second_element = get<0>(all_candidates[current_later_comparison_index]);

        if (second_element <= (1 + epsilon) * first_element) {
            indexes_to_be_removed.push_back(current_later_comparison_index);
            current_later_comparison_index++;
        } else {
            current_earlier_comparison_index = current_later_comparison_index;
            current_later_comparison_index++;
        }
    }

    for (int i = indexes_to_be_removed.size() - 1; i >= 0; i--) {
        int index_to_be_removed = indexes_to_be_removed[i];
        all_candidates.erase(all_candidates.begin() + index_to_be_removed);
    }
}

insertion_set<int> subset_sum(insertion_set<int> numbers, int restricted_sum) {
    vector<candidate> all_candidates = {{0, insertion_set<int>{}}};
    vector<candidate> current_candidates = all_candidates;
    insertion_set<int> new_candidate_subset = insertion_set<int>{};
    insertion_set<int> best_candidate_subset = insertion_set<int>{};

    for (int number : numbers) {
        current_candidates = all_candidates;

        for (candidate current_candidate : current_candidates) {
            if (get<0>(current_candidate) + number <= restricted_sum) {
                new_candidate_subset = get<1>(current_candidate);
                new_candidate_subset.insert(number);

                // otimização: se é igual ao limite de soma, já sabemos que é a solução ótima
                if (get<0>(current_candidate) + number == restricted_sum) {
                    return new_candidate_subset;
                }

                all_candidates.push_back({get<0>(current_candidate) + number, new_candidate_subset});
            }
        }

        // ordenando os candidatos em relação à soma
        sort(all_candidates.begin(), all_candidates.end(), custom_sort);

        // fazendo o trim dos candidatos
        trim_all_candidates(all_candidates);
    }

    return get<1>(all_candidates[all_candidates.size() - 1]);
}
