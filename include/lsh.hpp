// include/lsh.hpp
#pragma once
#include "search_structure.hpp"
#include "metrics.hpp"
#include <vector>
#include <unordered_map>
#include <random>

class LSH : public SearchStructure {
private:
    struct HashTable {
        std::unordered_map<long long, std::vector<int>> buckets;
    };

    int L; // número de tabelas
    int K; // número de projeções por tabela
    int dim;

    std::vector<std::vector<std::vector<float>>> randomVectors; // [L][K][dim]
    std::vector<std::vector<float>> storedVectors;              // id -> vetor
    std::vector<HashTable> tables;

    long long hashVector(int tableIndex, const std::vector<float>& v) const;

public:
    LSH(int L_, int K_, int dim_);

    void insert(const std::vector<float>& vec, int id) override;
    void build() override {} // nada especial aqui
    std::vector<int> query(const std::vector<float>& q, int k) const override;
};
