# Comparação de Estruturas de Dados para Busca por Similaridade em Alta Dimensão

Este projeto em C++ implementa e avalia o desempenho de diferentes estruturas de dados para a tarefa de Busca por Similaridade de Vizinhos Mais Próximos (Nearest Neighbor Similarity Search) em um conjunto de dados de alta dimensão.

## Visão Geral

O objetivo é comparar o custo computacional (tempo de construção e tempo de consulta) e a precisão de métodos de busca exatos e aproximados. As estruturas são testadas em um dataset de histogramas de cores de imagens, que são representados como vetores de 32 dimensões.

## Estruturas Implementadas

-   **`ListSearch`**: Uma busca linear (força bruta) que serve como baseline para comparação de tempo e precisão.
-   **`HashSearch`**: Uma tabela de hash tradicional, utilizada para demonstrar sua inadequação para busca por similaridade.
-   **`LSH (Locality-Sensitive Hashing)`**: Um método de busca aproximada projetado para funcionar eficientemente em espaços de alta dimensão.
-   **`M-Tree`**: Uma árvore métrica, que é uma estrutura de dados para indexação e busca exata em espaços métricos.

## Dataset

O arquivo `ColorHistogram.asc` contém o conjunto de dados utilizado.
-   **68.040** vetores de características.
-   Cada vetor possui **32 dimensões**.
-   Cada linha do arquivo representa uma imagem, com o formato: `ID <vetor_de_32_dimensoes>`.

## Pré-requisitos

Para compilar e executar o projeto, você precisará de:
-   Compilador C++ com suporte a C++17 (ex: `g++`)
-   Utilitário `make`

## Compilação

O projeto utiliza um `Makefile` para gerenciar a compilação. Para compilar o programa de benchmark, execute:

```bash
make
```

Isso irá gerar o executável `trabalho2_test`.

Para limpar os arquivos compilados, utilize:
```bash
make clean
```

## Execução

Após a compilação, o programa de benchmark pode ser executado. Ele irá carregar o dataset, construir cada uma das estruturas de dados e executar uma consulta de exemplo, medindo os tempos de construção e de busca.

Para executar, passe o arquivo de dataset como argumento:
```bash
./trabalho2_test ColorHistogram.asc
```

A saída mostrará o desempenho de cada estrutura, como no exemplo abaixo:
```
Dataset carregado: 68040 vetores, dimensão 32

=== ListSearch (baseline) ===
Tempo de construção: 0.0060952 s
Tempo de consulta: 0.00552182 s
Ids retornados: 1 33345 64187 51052 38839 

=== HashSearch ===
Tempo de construção: 0.0135767 s
Tempo de consulta: 1.766e-06 s
Ids retornados: 1 64187 

=== LSH ===
Tempo de construção: 0.0754568 s
Tempo de consulta: 0.000606753 s
Ids retornados: 1 33345 64187 51052 38839 

=== MTree (árvore métrica simples) ===
Tempo de construção: 0.107141 s
Tempo de consulta: 0.00688957 s
Ids retornados: 1 33345 64187 51052 38839 
```

## Estrutura do Projeto

```
.
├── include/         # Arquivos de cabeçalho (.hpp) com as declarações das classes
├── src/             # Arquivos de código-fonte (.cpp) com as implementações
├── experiments/     # Scripts para rodar experimentos
├── Makefile         # Arquivo de build para compilação
├── ColorHistogram.asc # O arquivo do dataset
└── README.md        # Este arquivo
```
