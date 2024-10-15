#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

int getRandom(int a, int b); 

double getRandom(double a, double b); 

inline std::vector<int> operator+(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be of the same size to add.");
    }

    std::vector<int> result(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}