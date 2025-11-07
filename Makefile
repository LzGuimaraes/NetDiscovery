CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
SRC = src/main.cpp src/grafo.cpp
OBJ = $(SRC:.cpp=.o)
BUILD = build
OUTPUT = output

all: dot

$(BUILD)/%.o: src/%.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

dot: $(BUILD)/main.o $(BUILD)/grafo.o
	mkdir -p $(OUTPUT)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD)/netdiscovery
	./$(BUILD)/netdiscovery

run: dot
	xdg-open $(OUTPUT)/grafo.png
