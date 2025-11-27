# Compilador e flags
CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iinclude

# --- Projeto Principal ---

# Arquivos fonte do projeto principal
SRC = \
    src/dataset.cpp \
    src/list_search.cpp \
    src/hash_search.cpp \
    src/lsh.cpp \
    src/mtree.cpp \
    src/main.cpp

SRC_TEST = \
    src/dataset.cpp \
    src/list_search.cpp \
    src/hash_search.cpp \
    src/lsh.cpp \
    src/mtree.cpp \
    src/main_test.cpp

# Objetos (.o) do projeto principal
OBJ = $(SRC:.cpp=.o)
OBJ_TEST = $(SRC_TEST:.cpp=.o)

# Nome do executável principal
TARGET = trabalho2
TARGET_TEST = trabalho2_test

# --- Regras de Build ---

# Regra padrão: builda apenas o projeto principal
all: test

test: $(TARGET_TEST)

# Linkagem final do projeto principal
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_TEST): $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra genérica para compilar .cpp em .o
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET) $(OBJ_TEST) $(TARGET_TEST)
# Não são arquivos de verdade
.PHONY: all clean test