#include <set>
#include <tuple> 
#include <set> 
#include <iostream>
#include <algorithm>

using namespace std;
// using candidate = tuple<int, set<int>>; --- sum and subset

int exact_subset_sum(int restricted_sum, set<int> numbers) {
    set<int> unique_fitting_sums;
    int total_max_sum = 0; // sum
    
    unique_fitting_sums.insert(total_max_sum);

    for (int number : numbers) {
        set<int> current_sums = unique_fitting_sums;

        for (int sum : current_sums) {
            if (sum + number <= restricted_sum) {
                int new_sum = sum + number;
                unique_fitting_sums.insert(new_sum);

                if (new_sum == restricted_sum) {
                    return new_sum;
                } else if (new_sum > total_max_sum) {
                    total_max_sum = new_sum;
                }
            }
        }
    }

    return total_max_sum;
}