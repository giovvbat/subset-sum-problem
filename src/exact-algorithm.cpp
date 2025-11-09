#include <set>
#include <tuple> 
#include <set> 
#include <vector> 
#include <iostream>
#include <algorithm>

using namespace std;
using result = tuple<int, set<int>>; // sum and subset

vector<vector<bool>> retrieve_sum_matrix(int restricted_sum, set<int> numbers) {
    vector<bool> first_matrix_line = {true};

    for (int i = 1; i <= restricted_sum; i++) {
        first_matrix_line.push_back(false);
    }

    vector<vector<bool>> sum_matrix = {first_matrix_line};
    int current_set_row_index = 0;

    for (int number : numbers) {
        vector<bool> current_matrix_line = {true};

        for (int current_sum = 1; current_sum <= restricted_sum; current_sum++) {
            bool flag_to_be_added = sum_matrix[current_set_row_index][current_sum];

            if (flag_to_be_added == false && current_sum >= number) {
                flag_to_be_added = sum_matrix[current_set_row_index][current_sum - number];
            }

            current_matrix_line.push_back(flag_to_be_added);
        }

        sum_matrix.push_back(current_matrix_line);
        current_set_row_index += 1;
    }

    return sum_matrix;
}

result retrieve_great_solution(vector<vector<bool>> sum_matrix, set<int> numbers) {
    int great_sum = 0;
    set<int> great_subset = {};
    vector<bool> last_sum_matrix_line = sum_matrix[sum_matrix.size() - 1];

    for (int great_sum_column = last_sum_matrix_line.size() - 1; great_sum_column >= 0; great_sum_column--) {
        if (last_sum_matrix_line[great_sum_column]) {
            great_sum = great_sum_column;
            break;
        }
    }

    int current_column = great_sum;
    int current_line = sum_matrix.size() - 1;

    while (current_column != 0) {
        current_line -= 1;

        if (sum_matrix[current_line][current_column]) {
            continue;
        } else {
            auto iterator = numbers.begin();
            advance(iterator, current_line);

            great_subset.insert(*iterator);
            current_column -= *iterator;
        }
    }

    return {great_sum, great_subset};
}

result exact_subset_sum(int restricted_sum, set<int> numbers) {
    return retrieve_great_solution(retrieve_sum_matrix(restricted_sum, numbers), numbers);
}