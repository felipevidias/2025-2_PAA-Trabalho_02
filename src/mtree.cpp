// src/mtree.cpp
#include "mtree.hpp"
#include <algorithm>
#include <cmath>

MTree::MTree(int bucketSize_) : root(nullptr), bucketSize(bucketSize_) {}

MTree::~MTree() {
    clear(root);
}

void MTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

MTree::Node* MTree::insertRec(Node* node, int id,
                              const std::vector<float>& vec) {
    if (!node) {
        node = new Node();
        node->id    = id;
        node->pivot = vec;
        node->radius = 0.0f;
        node->bucket.push_back({id, vec});
        return node;
    }

    // Inserção em folha
    if (!node->left && !node->right && (int)node->bucket.size() < bucketSize) {
        node->bucket.push_back({id, vec});
        float d = euclidean(node->pivot, vec);
        if (d > node->radius) node->radius = d;
        return node;
    }

    // Se é folha mas bucket estourou: faz split
    if (!node->left && !node->right && (int)node->bucket.size() >= bucketSize) {
        node->left  = new Node();
        node->right = new Node();

        // escolhe dois pivôs simples: primeiro e último
        node->left->id    = node->bucket.front().first;
        node->left->pivot = node->bucket.front().second;

        node->right->id    = node->bucket.back().first;
        node->right->pivot = node->bucket.back().second;

        // redistribui elementos
        for (const auto& p : node->bucket) {
            float dl = euclidean(p.second, node->left->pivot);
            float dr = euclidean(p.second, node->right->pivot);
            if (dl <= dr) {
                node->left->bucket.push_back(p);
                if (dl > node->left->radius) node->left->radius = dl;
            } else {
                node->right->bucket.push_back(p);
                if (dr > node->right->radius) node->right->radius = dr;
            }
        }
        node->bucket.clear();
    }

    // Decide se vai para a esquerda ou direita
    float dl = euclidean(vec, node->left->pivot);
    float dr = euclidean(vec, node->right->pivot);

    if (dl <= dr) {
        node->left = insertRec(node->left, id, vec);
        if (dl > node->left->radius) node->left->radius = dl;
    } else {
        node->right = insertRec(node->right, id, vec);
        if (dr > node->right->radius) node->right->radius = dr;
    }

    return node;
}

void MTree::insert(const std::vector<float>& vec, int id) {
    root = insertRec(root, id, vec);
}

void MTree::knnRec(Node* node, const std::vector<float>& q, int k,
                   std::vector<std::pair<float,int>>& best) const {
    if (!node) return;

    // Se folha
    if (!node->left && !node->right) {
        for (const auto& p : node->bucket) {
            float d = euclidean(p.second, q);
            if ((int)best.size() < k) {
                best.push_back({d, p.first});
                std::push_heap(best.begin(), best.end(),
                               [](auto& a, auto& b){ return a.first < b.first; }); // max-heap
            } else if (d < best.front().first) {
                std::pop_heap(best.begin(), best.end(),
                              [](auto& a, auto& b){ return a.first < b.first; });
                best.back() = {d, p.first};
                std::push_heap(best.begin(), best.end(),
                               [](auto& a, auto& b){ return a.first < b.first; });
            }
        }
        return;
    }

    // Distância ao pivô de cada filho
    float dl = node->left  ? euclidean(q, node->left->pivot)  : std::numeric_limits<float>::max();
    float dr = node->right ? euclidean(q, node->right->pivot) : std::numeric_limits<float>::max();

    // Visita filho mais promissor primeiro
    if (dl < dr) {
        if (node->left)  knnRec(node->left,  q, k, best);
        if (node->right) knnRec(node->right, q, k, best);
    } else {
        if (node->right) knnRec(node->right, q, k, best);
        if (node->left)  knnRec(node->left,  q, k, best);
    }
}

std::vector<int> MTree::query(const std::vector<float>& q, int k) const {
    std::vector<std::pair<float,int>> best;
    best.reserve(k+1);
    std::vector<int> result;

    knnRec(root, q, k, best);

    std::sort(best.begin(), best.end(),
              [](const auto& a, const auto& b){ return a.first < b.first; });

    for (auto& p : best) result.push_back(p.second);
    return result;
}
