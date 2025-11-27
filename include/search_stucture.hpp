// include/search_structure.hpp
#pragma once
#include <vector>

// Interface genérica para qualquer estrutura de busca
class SearchStructure {
public:
    // Insere um vetor com id associado
    virtual void insert(const std::vector<float>& vec, int id) = 0;

    // Opcional: construir índice depois de inserir tudo
    virtual void build() {}

    // Retorna ids dos k vizinhos mais próximos
    virtual std::vector<int> query(const std::vector<float>& q, int k) const = 0;

    virtual ~SearchStructure() {}
};
