#ifndef INSTANCE_GENERATOR_HPP
#define INSTANCE_GENERATOR_HPP

#include "../include/insertion-set.hpp"
#include <tuple>

using test_case = std::tuple<int, int, insertion_set<int>>;

test_case generate_instance();

#endif // INSTANCE_GENERATOR_HPP