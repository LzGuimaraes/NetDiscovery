#include "../include/grafo.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    int n;
    std::cout << "Digite o número de nós da rede: ";
    std::cin >> n;

    Grafo g(n);
    g.gerarTopologiaAleatoria(0.2);
    g.imprimirMatriz();
    g.salvarDot("output/grafo.dot");

    int origem;
    std::cout << "\nDigite o nó de origem para simular mensagens: ";
    std::cin >> origem;

    g.simularMensagens(origem);

    std::system("dot -Tpng output/grafo.dot -o output/grafo.png");
    std::cout << "\n✅ Grafo salvo em 'output/grafo.png'\n";
    return 0;
}
