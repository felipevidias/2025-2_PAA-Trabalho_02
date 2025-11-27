// src/dataset.cpp
#include "dataset.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

bool Dataset::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Erro ao abrir arquivo: " << filename << "\n";
        return false;
    }

    ids.clear();
    vectors.clear();

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);

        int id;
        ss >> id;
        ids.push_back(id);

        std::vector<float> v;
        float value;
        while (ss >> value) {
            v.push_back(value);
        }
        if (!v.empty())
            vectors.push_back(v);
    }

    if (vectors.empty()) {
        std::cerr << "Nenhum vetor carregado!\n";
        return false;
    }
    return true;
}
