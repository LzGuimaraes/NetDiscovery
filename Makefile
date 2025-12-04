# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Diretórios
SRC_DIR = src
BUILD_DIR = build
OUTPUT_DIR = output

# Arquivos fonte e objetos
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/grafo.cpp
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

# Binário final
EXEC = $(BUILD_DIR)/netdiscovery

# Regra padrão
all: $(EXEC)

# Compilação dos objetos dentro da pasta build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linkagem final
$(EXEC): $(OBJ)
	mkdir -p $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC)

# Executa o programa
run: all
	./$(EXEC)

# Remove objetos e binário
clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_DIR)

