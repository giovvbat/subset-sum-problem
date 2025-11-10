#ifndef APPROXIMATION_ALGORITHM_HPP
#define APPROXIMATION_ALGORITHM_HPP

#include <tuple>
#include <set>

using namespace std;
using result = tuple<int, set<int>, double>;

result approximation_subset_sum(int restricted_sum, set<int> numbers, double epsilon);

#endif // APPROXIMATION_ALGORITHM_HPP