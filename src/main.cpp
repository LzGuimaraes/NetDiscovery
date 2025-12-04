#include "../include/grafo.hpp"
#include <iostream>
#include <cstdlib>
#include <thread> // Para sleep
#include <chrono> // Para segundos

int main() {
    int n;
    std::cout << "Digite o número de nós da rede: ";
    std::cin >> n;

    Grafo g(n);
    // Densidade 0.3, Peso max 20
    g.gerarTopologiaAleatoria(0.3, 20); 
    
    // Configuração inicial
    std::cout << "Gerando estado inicial...\n";
    g.imprimirMatriz();
    g.salvarDot("output/grafo.dot");
    
    // Usar 'neato' para respeitar coordenadas
    std::system("neato -Tpng output/grafo.dot -o output/grafo_inicial.png"); 
    std::cout << "Estado inicial salvo em 'output/grafo_inicial.png'\n";

    int origem;
    std::cout << "\nDigite o nó de origem para teste inicial: ";
    std::cin >> origem;
    g.simularMensagens(origem);

    std::cout << "\n--- INICIANDO SIMULAÇÃO DE MOBILIDADE ---\n";
    std::cout << "A rede irá mover-se a cada 10 segundos.\n";
    std::cout << "Serão exibidas as tabelas de rotas completas para todos os nós.\n";
    std::cout << "Pressione Ctrl+C para parar.\n\n";

    int passo = 1;
    while (true) {
        std::cout << "A aguardar 10 segundos...\n";
        std::this_thread::sleep_for(std::chrono::seconds(10));

        std::cout << "\n[Passo " << passo << "] Aplicando mobilidade...\n";
        
        // Move os nós
        g.aplicarMobilidade(50.0);
        
        // ========================================================
        // NOVO: Exibe as rotas de TODOS os nós (Tabela Completa)
        // ========================================================
        std::cout << "\n>>> TABELA DE ROTEAMENTO GERAL (Passo " << passo << ") <<<\n";
        for (int i = 0; i < n; ++i) {
            // Chama a função que gera o formato "Rota A -> B: ..."
            g.simularMensagens(i); 
        }
        std::cout << "=======================================================\n";

        // Salva e Gera Imagem
        g.salvarDot("output/grafo.dot");
        
        // Gera histórico
        std::string comando = "neato -Tpng output/grafo.dot -o output/grafo_passo_" + std::to_string(passo) + ".png";
        std::system(comando.c_str());
        
        // Atualiza imagem principal
        std::system("neato -Tpng output/grafo.dot -o output/grafo.png");

        std::cout << "Grafo visual atualizado: output/grafo.png\n";
        passo++;
    }

    return 0;
}