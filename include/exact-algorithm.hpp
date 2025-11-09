#ifndef EXACT_ALGORITHM_HPP
#define EXACT_ALGORITHM_HPP

#include <tuple>
#include <set>

using namespace std;
using result = std::tuple<int, set<int>>;

result exact_subset_sum(int restricted_sum, set<int> numbers);

#endif // EXACT_ALGORITHM_HPP