#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
using candidate = tuple<int, set<int>>; // sum and subset

bool custom_sort(tuple<int, set<int>> first_element, tuple<int, set<int>> second_element) { 
    return get<0>(first_element) < get<0>(second_element); 
}

void trim_all_candidates(vector<candidate>& all_candidates, double approximation_factor) {
    int current_earlier_comparison_index = 0;
    int current_later_comparison_index = 1;
    vector<int> indexes_to_be_removed = {};

    while (current_later_comparison_index != all_candidates.size()) {
        int first_element = get<0>(all_candidates[current_earlier_comparison_index]);
        int second_element = get<0>(all_candidates[current_later_comparison_index]);

        if (second_element > (first_element * (1 + approximation_factor))) {
            current_earlier_comparison_index = current_later_comparison_index;
            current_later_comparison_index++;
        } else {
            indexes_to_be_removed.push_back(current_later_comparison_index);
            current_later_comparison_index++;
        }
    }

    for (int i = indexes_to_be_removed.size() - 1; i >= 0; i--) {
        int index_to_be_removed = indexes_to_be_removed[i];
        all_candidates.erase(all_candidates.begin() + index_to_be_removed);
    }
}

candidate approximation_subset_sum(int restricted_sum, set<int> numbers, double epsilon) {
    vector<candidate> all_candidates = {{0, set<int>{}}};
    vector<candidate> current_candidates = all_candidates;
    set<int> best_candidate_subset = get<1>(all_candidates[0]);
    double approximation_factor = epsilon / (2 * numbers.size());

    for (int number : numbers) {
        current_candidates = all_candidates;

        for (candidate current_candidate : current_candidates) {
            if (get<0>(current_candidate) + number <= restricted_sum) {
                set<int> new_candidate_subset = get<1>(current_candidate);
                new_candidate_subset.insert(number);
                
                candidate new_candidate = {get<0>(current_candidate) + number, new_candidate_subset};
                all_candidates.push_back(new_candidate);
            }
        }

        // ordenando os candidatos em relação à soma
        sort(all_candidates.begin(), all_candidates.end(), custom_sort);

        // fazendo o trim dos candidatos
        trim_all_candidates(all_candidates, approximation_factor);
    }

    return all_candidates[all_candidates.size() - 1];
}
