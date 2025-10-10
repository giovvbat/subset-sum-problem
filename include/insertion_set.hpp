#ifndef INSERTION_SET_H
#define INSERTION_SET_H

#include <vector>
#include <unordered_set>
#include <initializer_list>

template <typename T>
class insertion_set {
private:
    std::vector<T> data;
    std::unordered_set<T> seen;

public:
    insertion_set() = default;

    insertion_set(std::initializer_list<T> init) {
        for (const auto& val : init) {
            insert(val);
        }
    }

    void insert(const T& value) {
        auto result = seen.insert(value);

        if (result.second) {
            data.push_back(value);
        }
    }

    size_t size() const { return data.size(); }
    bool empty() const { return data.empty(); }

    const std::vector<T>& values() const { return data; }

    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};

#endif // INSERTION_SET_H
