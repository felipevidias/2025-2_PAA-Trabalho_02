// include/hash_search.hpp
#pragma once
#include "search_structure.hpp"
#include "metrics.hpp"
#include <unordered_map>
#include <vector>

class HashSearch : public SearchStructure {
private:
    std::unordered_map<long long, std::vector<std::pair<int, std::vector<float>>>> table;

    long long hashVector(const std::vector<float>& v) const;

public:
    void insert(const std::vector<float>& vec, int id) override;
    std::vector<int> query(const std::vector<float>& q, int k) const override;
};
