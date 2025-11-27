// include/list_search.hpp
#pragma once
#include "search_structure.hpp"
#include "metrics.hpp"
#include <vector>
#include <utility>
#include <algorithm>

class ListSearch : public SearchStructure {
private:
    // (id, vetor)
    std::vector<std::pair<int, std::vector<float>>> data;

public:
    void insert(const std::vector<float>& vec, int id) override {
        data.push_back({id, vec});
    }

    std::vector<int> query(const std::vector<float>& q, int k) const override;
};
