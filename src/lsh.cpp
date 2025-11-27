// src/lsh.cpp
#include "lsh.hpp"
#include <algorithm>
#include <cmath>

LSH::LSH(int L_, int K_, int dim_)
    : L(L_), K(K_), dim(dim_),
      randomVectors(L_, std::vector<std::vector<float>>(K_, std::vector<float>(dim_))),
      tables(L_) {

    std::mt19937 rng(12345);
    std::normal_distribution<float> dist(0.0f, 1.0f);

    // Gera vetores de projeção aleatórios
    for (int l = 0; l < L; ++l) {
        for (int k = 0; k < K; ++k) {
            for (int d = 0; d < dim; ++d) {
                randomVectors[l][k][d] = dist(rng);
            }
        }
    }
}

long long LSH::hashVector(int tableIndex, const std::vector<float>& v) const {
    long long h = 0;
    for (int k = 0; k < K; ++k) {
        const auto& proj = randomVectors[tableIndex][k];
        float dot = 0.0f;
        for (int d = 0; d < dim; ++d)
            dot += proj[d] * v[d];

        int bit = (dot >= 0.0f) ? 1 : 0;
        h = (h << 1) | bit;
    }
    return h;
}

void LSH::insert(const std::vector<float>& vec, int id) {
    if ((int)vec.size() != dim) {
        // em trabalho real: tratar erro
        return;
    }
    if ((int)storedVectors.size() <= id) {
        storedVectors.resize(id + 1);
    }
    storedVectors[id] = vec;

    for (int l = 0; l < L; ++l) {
        long long key = hashVector(l, vec);
        tables[l].buckets[key].push_back(id);
    }
}

std::vector<int> LSH::query(const std::vector<float>& q, int k) const {
    std::vector<int> candidates;
    std::vector<char> used;

    if (storedVectors.empty()) return candidates;
    used.assign(storedVectors.size(), 0);

    for (int l = 0; l < L; ++l) {
        long long key = hashVector(l, q);
        auto it = tables[l].buckets.find(key);
        if (it == tables[l].buckets.end()) continue;

        for (int id : it->second) {
            if (!used[id]) {
                used[id] = 1;
                candidates.push_back(id);
            }
        }
    }

    if (candidates.empty()) {
        // fallback: retorna os k primeiros ids válidos
        for (size_t id = 0; id < storedVectors.size() && (int)id < k; ++id)
            candidates.push_back((int)id);
    }

    std::vector<std::pair<float,int>> dist;
    for (int id : candidates) {
        float d = euclidean(storedVectors[id], q);
        dist.push_back({d, id});
    }

    std::sort(dist.begin(), dist.end(),
              [](const auto& a, const auto& b){ return a.first < b.first; });

    if (k > (int)dist.size()) k = (int)dist.size();
    std::vector<int> result;
    for (int i = 0; i < k; ++i) result.push_back(dist[i].second);
    return result;
}
