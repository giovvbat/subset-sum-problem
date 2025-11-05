#ifndef INSTANCE_GENERATOR_HPP
#define INSTANCE_GENERATOR_HPP

#include <tuple>
#include <set>

using namespace std;
using test_case = std::tuple<int, int, set<int>>;

test_case generate_instance();

#endif // INSTANCE_GENERATOR_HPP