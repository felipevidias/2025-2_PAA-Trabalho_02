// src/hash_search.cpp
#include "hash_search.hpp"
#include <cmath>
#include <algorithm>

long long HashSearch::hashVector(const std::vector<float>& v) const {
    // Hash bem simples: quantiza cada valor e combina
    const float factor = 10.0f; // controla quantização
    long long h = 0;
    for (float x : v) {
        long long q = (long long)std::floor(x * factor);
        h = h * 1315423911LL + q; // mistura
    }
    return h;
}

void HashSearch::insert(const std::vector<float>& vec, int id) {
    long long key = hashVector(vec);
    table[key].push_back({id, vec});
}

std::vector<int> HashSearch::query(const std::vector<float>& q, int k) const {
    long long key = hashVector(q);
    std::vector<int> result;

    auto it = table.find(key);
    if (it == table.end()) {
        // Fallback: retorna vazio
        return result;
    }

    const auto& bucket = it->second;
    std::vector<std::pair<float,int>> dist;
    for (const auto& item : bucket) {
        float d = euclidean(item.second, q);
        dist.push_back({d, item.first});
    }
    std::sort(dist.begin(), dist.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    if (k > (int)dist.size()) k = (int)dist.size();
    for (int i = 0; i < k; ++i) result.push_back(dist[i].second);
    return result;
}
