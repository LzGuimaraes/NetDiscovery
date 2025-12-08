#include "../include/grafo.hpp"
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

int main() {
    int n;
    std::cout << "Digite o número de nós da rede: ";
    std::cin >> n;

    Grafo g(n);
    g.gerarTopologiaAleatoria(0.2); 
    
    std::cout << "Gerando estado inicial...\n";
    g.salvarDot("output/grafo.dot");
    std::system("neato -Tpng output/grafo.dot -o output/grafo_inicial.png"); 
    std::cout << "Estado inicial salvo.\n";

    int origem;
    std::cout << "\nDigite o nó de origem para monitoramento: ";
    std::cin >> origem;

    std::cout << "\n--- SIMULAÇÃO DE ROTEAMENTO EXCLUSIVO QoS ADITIVO ---\n";
    
    int passo = 1;
    while (true) {
        std::cout << "\nA aguardar 5 segundos...\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));

        std::cout << "\n[Passo " << passo << "] Atualizando pesos e posições...\n";
        
        g.aplicarMobilidade(50.0);
        
        // 1. Scanner de Vizinhos
        g.descobrirTopologia(origem);

        // 2. Roteamento (Apenas QoS Aditivo)
        std::cout << "\n=== MELHORES ROTAS (MÉTRICA DE CUSTO ACUMULADO) ===\n";
        g.simularRotasQoS(origem);
        
        // Gera Imagem
        g.salvarDot("output/grafo.dot");
        std::string comando = "neato -Tpng output/grafo.dot -o output/grafo_passo_" + std::to_string(passo) + ".png";
        std::system(comando.c_str());
        std::system("neato -Tpng output/grafo.dot -o output/grafo.png");

        std::cout << "Mapa atualizado: output/grafo.png\n";
        passo++;
    }

    return 0;
}