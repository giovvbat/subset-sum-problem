#ifndef APPROXIMATION_ALGORITHM_HPP
#define APPROXIMATION_ALGORITHM_HPP

#include "../include/insertion-set.hpp"
#include <tuple>

using candidate = std::tuple<int, insertion_set<int>>; 

candidate subset_sum(int restricted_sum, insertion_set<int> numbers, double epsilon);

#endif // APPROXIMATION_ALGORITHM_HPP