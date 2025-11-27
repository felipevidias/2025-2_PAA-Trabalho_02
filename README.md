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

O projeto utiliza um `Makefile` para gerenciar a compilação.

-   **Para compilar o programa de benchmark principal:**
    ```bash
    make trabalho2
    ```

-   **Para compilar o programa de testes:**
    ```bash
    make
    ```
    (O comando `make` por padrão executa a regra `test`, que compila o `trabalho2_test`)

-   **Para limpar os arquivos compilados:**
    ```bash
    make clean
    ```

## Execução

Após a compilação, dois executáveis serão criados.

1.  **Benchmark Principal (`trabalho2`)**
    Este programa carrega o dataset, constrói cada uma das estruturas de dados e executa uma consulta de exemplo, medindo os tempos de construção e de busca.

    Para executar:
    ```bash
    ./trabalho2
    ```
    A saída mostrará o desempenho de cada estrutura, como no exemplo abaixo:
    ```
    Dataset carregado: 68040 vetores, dimensão 32

    === ListSearch (baseline) ===
    Tempo de construção: 0.0060952 s
    Tempo de consulta: 0.00552182 s
    Ids retornados: 1 33345 64187 51052 38839

    === HashSearch ===
    ...
    ```

2.  **Testes (`trabalho2_test`)**
    Este executável roda um conjunto de testes para validar a corretude das implementações.

    Para executar:
    ```bash
    ./trabalho2_test
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
