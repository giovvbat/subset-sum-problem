#ifndef EXACT_ALGORITHM_HPP
#define EXACT_ALGORITHM_HPP

#include <tuple>
#include <set>

using namespace std;
using candidate = std::tuple<int, set<int>>;

int exact_subset_sum(int restricted_sum, set<int> numbers);

#endif // EXACT_ALGORITHM_HPP