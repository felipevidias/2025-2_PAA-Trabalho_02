// src/list_search.cpp
#include "list_search.hpp"

std::vector<int> ListSearch::query(const std::vector<float>& q, int k) const {
    std::vector<std::pair<float,int>> dist; // (distância, id)
    dist.reserve(data.size());

    for (const auto& item : data) {
        float d = euclidean(item.second, q);
        dist.push_back({d, item.first});
    }

    std::sort(dist.begin(), dist.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    if (k > (int)dist.size()) k = (int)dist.size();
    std::vector<int> result;
    for (int i = 0; i < k; ++i) {
        result.push_back(dist[i].second);
    }
    return result;
}
