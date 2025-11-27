// src/main.cpp
#include "dataset.hpp"
#include "list_search.hpp"
#include "hash_search.hpp"
#include "lsh.hpp"
#include "mtree.hpp"

#include <iostream>
#include <chrono>
#include <memory>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " dataset.txt\n";
        return 1;
    }

    std::string filename = argv[1];
    Dataset D;
    if (!D.loadFromFile(filename)) return 1;

    int dim = (int)D.vectors[0].size();
    int n   = (int)D.size();
    int k   = 5; // k vizinhos

    std::cout << "Dataset carregado: " << n
              << " vetores, dimensão " << dim << "\n";

    // 1) Lista
    {
        std::cout << "\n=== ListSearch (baseline) ===\n";
        ListSearch list;
        auto t0 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            list.insert(D.vectors[i], D.ids[i]);
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Tempo de construção: "
                  << std::chrono::duration<double>(t1 - t0).count() << " s\n";

        auto q = D.vectors[0];
        auto t2 = std::chrono::high_resolution_clock::now();
        auto res = list.query(q, k);
        auto t3 = std::chrono::high_resolution_clock::now();

        std::cout << "Tempo de consulta: "
                  << std::chrono::duration<double>(t3 - t2).count() << " s\n";
        std::cout << "Ids retornados: ";
        for (int id : res) std::cout << id << " ";
        std::cout << "\n";
    }

    // 2) Hash simples
    {
        std::cout << "\n=== HashSearch ===\n";
        HashSearch hs;
        auto t0 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            hs.insert(D.vectors[i], D.ids[i]);
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Tempo de construção: "
                  << std::chrono::duration<double>(t1 - t0).count() << " s\n";

        auto q = D.vectors[0];
        auto t2 = std::chrono::high_resolution_clock::now();
        auto res = hs.query(q, k);
        auto t3 = std::chrono::high_resolution_clock::now();

        std::cout << "Tempo de consulta: "
                  << std::chrono::duration<double>(t3 - t2).count() << " s\n";
        std::cout << "Ids retornados: ";
        for (int id : res) std::cout << id << " ";
        std::cout << "\n";
    }

    // 3) LSH
    {
        std::cout << "\n=== LSH ===\n";
        int L = 5;     // número de tabelas
        int K = 10;    // bits por tabela
        LSH lsh(L, K, dim);

        auto t0 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            lsh.insert(D.vectors[i], D.ids[i]);
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Tempo de construção: "
                  << std::chrono::duration<double>(t1 - t0).count() << " s\n";

        auto q = D.vectors[0];
        auto t2 = std::chrono::high_resolution_clock::now();
        auto res = lsh.query(q, k);
        auto t3 = std::chrono::high_resolution_clock::now();

        std::cout << "Tempo de consulta: "
                  << std::chrono::duration<double>(t3 - t2).count() << " s\n";
        std::cout << "Ids retornados: ";
        for (int id : res) std::cout << id << " ";
        std::cout << "\n";
    }

    // 4) MTree
    {
        std::cout << "\n=== MTree (árvore métrica simples) ===\n";
        MTree mtree(16);

        auto t0 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            mtree.insert(D.vectors[i], D.ids[i]);
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Tempo de construção: "
                  << std::chrono::duration<double>(t1 - t0).count() << " s\n";

        auto q = D.vectors[0];
        auto t2 = std::chrono::high_resolution_clock::now();
        auto res = mtree.query(q, k);
        auto t3 = std::chrono::high_resolution_clock::now();

        std::cout << "Tempo de consulta: "
                  << std::chrono::duration<double>(t3 - t2).count() << " s\n";
        std::cout << "Ids retornados: ";
        for (int id : res) std::cout << id << " ";
        std::cout << "\n";
    }

    return 0;
}
