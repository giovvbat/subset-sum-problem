#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
using candidate = tuple<int, set<int>>; // sum and subset

bool custom_sort(tuple<int, set<int>> first_element, tuple<int, set<int>> second_element) { 
    return get<0>(first_element) < get<0>(second_element); 
}

void trim_all_sums(vector<int>& all_sums, double approximation_factor) {
    int current_earlier_comparison_index = 0;
        int current_later_comparison_index = 1;
        vector<int> indexes_to_be_removed = {};

    while (current_later_comparison_index != all_sums.size()) {
        int first_element = all_sums[current_earlier_comparison_index];
        int second_element = all_sums[current_later_comparison_index];

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
        all_sums.erase(all_sums.begin() + index_to_be_removed);
    }
}

int approximation_subset_sum(int restricted_sum, set<int> numbers, double epsilon) {
    vector<int> all_sums = {0}, current_sums = all_sums;
    double approximation_factor = epsilon / (2 * numbers.size());

    for (int number : numbers) {
        current_sums = all_sums;

        for (int current_sum : current_sums) {
            if (current_sum + number <= restricted_sum) {
                int new_candidate_sum = current_sum + number;
                all_sums.push_back(new_candidate_sum);
            }
        }

        // ordenando as somas
        sort(all_sums.begin(), all_sums.end());

        // fazendo o trim das somas
        trim_all_sums(all_sums, approximation_factor);
    }

    return all_sums[all_sums.size() - 1];
}