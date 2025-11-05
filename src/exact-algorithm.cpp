#include <set>
#include <tuple> 
#include <set> 
#include <iostream>
#include <algorithm>

using namespace std;
using candidate = tuple<int, set<int>>; // sum and subset

candidate exact_subset_sum(int restricted_sum, set<int> numbers) {
    set<candidate> unique_fitting_candidates;
    candidate total_max_candidate = {0, set<int>{}}; // sum and set
    
    unique_fitting_candidates.insert(total_max_candidate);

    for (int number : numbers) {
        set<candidate> current_sums_vec = unique_fitting_candidates;

        for (auto [sum, subset] : current_sums_vec) {
            if (sum + number <= restricted_sum) {
                set<int> new_subset = subset;
                new_subset.insert(number);

                candidate new_candidate = {sum + number, new_subset};
                unique_fitting_candidates.insert(new_candidate);

                if (get<0>(new_candidate) == restricted_sum) {
                    return new_candidate;
                } else if (get<0>(new_candidate) > get<0>(total_max_candidate)) {
                    total_max_candidate = new_candidate;
                }
            }
        }
    }

    return total_max_candidate;
}