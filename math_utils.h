#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <utility>
#include <vector>

using x_y_lists = std::pair<std::vector<double>, std::vector<double>>;

int flp2(int x);

template <typename T>
std::vector<T> arange(T start, T stop, T step = 1)
{
    std::vector<T> values;
    for (T value = start; value < stop; value += step) {
        values.push_back(value);
    }
    return values;
}

template <typename T>
T sum(std::vector<T> target)
{
    T el_sum;
    for (const auto& e : target) {
        el_sum += e;
    }
    return el_sum;
}

#endif // UTILS_H
