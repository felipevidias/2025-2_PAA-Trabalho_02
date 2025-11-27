// include/dataset.hpp
#pragma once
#include <string>
#include <vector>

class Dataset {
public:
    // vector[i] = vetor de características do id i
    std::vector<std::vector<float>> vectors;
    std::vector<int> ids;

    bool loadFromFile(const std::string& filename);

    size_t size() const { return vectors.size(); }
    const std::vector<float>& getVector(size_t i) const { return vectors[i]; }
    int getId(size_t i) const { return ids[i]; }
};
