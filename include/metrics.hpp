// include/metrics.hpp
#pragma once
#include <vector>
#include <cmath>

inline float euclidean(const std::vector<float>& a,
                       const std::vector<float>& b) {
    float sum = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        float d = a[i] - b[i];
        sum += d * d;
    }
    return std::sqrt(sum);
}
