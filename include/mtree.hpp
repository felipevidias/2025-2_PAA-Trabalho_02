// include/mtree.hpp
#pragma once
#include "search_structure.hpp"
#include "metrics.hpp"
#include <vector>
#include <limits>

class MTree : public SearchStructure {
private:
    struct Node {
        int id;                     // id do pivô
        std::vector<float> pivot;   // vetor do pivô
        float radius;               // raio de cobertura

        Node* left;
        Node* right;

        std::vector<std::pair<int, std::vector<float>>> bucket; // se folha

        Node() : id(-1), radius(0.0f), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int bucketSize;

    Node* insertRec(Node* node, int id, const std::vector<float>& vec);
    void knnRec(Node* node, const std::vector<float>& q, int k,
                std::vector<std::pair<float,int>>& best) const;

public:
    MTree(int bucketSize_ = 16);
    ~MTree();

    void insert(const std::vector<float>& vec, int id) override;
    void build() override {}
    std::vector<int> query(const std::vector<float>& q, int k) const override;

    void clear(Node* node);
};
