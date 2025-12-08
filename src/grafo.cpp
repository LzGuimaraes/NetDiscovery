#include "../include/grafo.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <fstream>
#include <random>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <cmath> 

// Construtor
Grafo::Grafo(int n) : n(n), adj(n), posicoes(n), posicoesAntigas(n), movimentoRealizado(false) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(100.0, 400.0); 

    for(int i=0; i<n; ++i) {
        posicoes[i] = {dist(gen), dist(gen)};
        posicoesAntigas[i] = posicoes[i];
    }
}

// (Mantenha gerarTopologiaAleatoria e garantirConexao iguais ao anterior...)
void Grafo::gerarTopologiaAleatoria(double densidade, int pesoMax) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> pesoDis(1, pesoMax);

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (dis(gen) < densidade) {
                int peso = pesoDis(gen);
                adj[i].push_back({j, peso});
                adj[j].push_back({i, peso});
            }
        }
    }
    garantirConexao();
}

void Grafo::garantirConexao() {
    std::vector<bool> visitado(n, false);
    auto bfs = [&](int start){
        std::queue<int> q;
        q.push(start);
        visitado[start] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& edge : adj[u]) {
                int v = edge.first;
                if (!visitado[v]) {
                    visitado[v] = true;
                    q.push(v);
                }
            }
        }
    };
    bfs(0);
    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) {
            for (int j = 0; j < n; ++j) {
                if (visitado[j]) {
                    adj[i].push_back({j, 1});
                    adj[j].push_back({i, 1});
                    break;
                }
            }
            bfs(i);
        }
    }
}

// MOBILIDADE COM FÍSICA (REPULSÃO E ATRAÇÃO)
void Grafo::aplicarMobilidade(double maxDeslocamento) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-maxDeslocamento * 0.5, maxDeslocamento * 0.5); 

    // Parâmetros de Física
    const double DISTANCIA_MINIMA = 90.0; 
    const double FORCA_REPULSAO = 40.0;   
    const double CENTRO_MAPA = 250.0;     
    const double FATOR_RETORNO = 0.05;    
    
    // Parâmetros de Conexão
    const double ALCANCE_MAXIMO = 140.0; 
    const double MIN_MAP = 10.0;
    const double MAX_MAP = 490.0;

    movimentoRealizado = true;
    std::cout << "\n=== [RELATÓRIO DE MOBILIDADE INTELIGENTE] ===\n";

    // Vetores temporários para armazenar as novas posições antes de aplicar
    std::vector<Coordenada> novasPosicoes = posicoes;

    for (int i = 0; i < n; ++i) {
        posicoesAntigas[i] = posicoes[i];

        // 1. Movimento Aleatório (Browniano)
        double moveX = dis(gen);
        double moveY = dis(gen);

        // 2. Calcular Forças de Repulsão (Evitar sobreposição)
        double repulsaoX = 0;
        double repulsaoY = 0;

        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            double dx = posicoes[i].x - posicoes[j].x;
            double dy = posicoes[i].y - posicoes[j].y;
            double dist = std::sqrt(dx*dx + dy*dy);

            // Se estiver muito perto (dist < 60), empurra!
            if (dist < DISTANCIA_MINIMA && dist > 0.1) {
                // Vetor normalizado * Força
                repulsaoX += (dx / dist) * FORCA_REPULSAO;
                repulsaoY += (dy / dist) * FORCA_REPULSAO;
            }
        }

        // 3. Atração ao Centro (Se afastar demais, volta)
        double centroX = (CENTRO_MAPA - posicoes[i].x) * FATOR_RETORNO;
        double centroY = (CENTRO_MAPA - posicoes[i].y) * FATOR_RETORNO;

        // Somar todas as forças
        novasPosicoes[i].x += moveX + repulsaoX + centroX;
        novasPosicoes[i].y += moveY + repulsaoY + centroY;

        // Limites do mapa
        if(novasPosicoes[i].x < MIN_MAP) novasPosicoes[i].x = MIN_MAP;
        if(novasPosicoes[i].x > MAX_MAP) novasPosicoes[i].x = MAX_MAP;
        if(novasPosicoes[i].y < MIN_MAP) novasPosicoes[i].y = MIN_MAP;
        if(novasPosicoes[i].y > MAX_MAP) novasPosicoes[i].y = MAX_MAP;
    }

    // Aplica as novas posições
    posicoes = novasPosicoes;

    // Relatório visual
    for(int i=0; i<n; ++i) {
        std::cout << "Nó " << i << ": (" 
                  << std::fixed << std::setprecision(1) << posicoesAntigas[i].x << ", " << posicoesAntigas[i].y 
                  << ") --> (" 
                  << posicoes[i].x << ", " << posicoes[i].y << ")\n";
    }

    // Atualizar Conexões (Lógica de Alcance)
    std::cout << ">>> Atualizando topologia (Alcance: " << ALCANCE_MAXIMO << ")...\n";
    for(int i=0; i<n; ++i) adj[i].clear();

    int novasArestas = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = std::sqrt(std::pow(posicoes[i].x - posicoes[j].x, 2) + 
                                    std::pow(posicoes[i].y - posicoes[j].y, 2));

            if (dist <= ALCANCE_MAXIMO) {
                int peso = 1 + (int)(dist / 10.0); 
                adj[i].push_back({j, peso});
                adj[j].push_back({i, peso});
                novasArestas++;
            }
        }
    }
    std::cout << ">>> Topologia atualizada: " << novasArestas << " conexões ativas.\n";
    std::cout << "=================================\n";
}

// (Mantenha imprimirMatriz igual...)
void Grafo::imprimirMatriz() const {
    std::cout << "\n Matriz de Adjacência (Pesos):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int peso = 0;
            for (auto& edge : adj[i]) {
                if (edge.first == j) {
                    peso = edge.second;
                    break;
                }
            }
            std::cout << std::setw(3) << peso << " ";
        }
        std::cout << "\n";
    }
}

// (Mantenha salvarDot com a correção anterior...)
void Grafo::salvarDot(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Erro ao criar arquivo DOT!\n";
        return;
    }

    out.imbue(std::locale::classic());

    out << "graph G {\n";
    out << "  graph [bb=\"0,0,500,500\", inputscale=72, splines=line, pad=\"0.2\", outputorder=edgesfirst, bgcolor=\"white\"];\n";
    out << "  node [shape=circle, style=\"filled,setlinewidth(1.5)\", fillcolor=\"#E0F7FA\", color=\"#006064\", fontname=\"Helvetica-Bold\", fontsize=10, fixedsize=true, width=0.4];\n";
    out << "  edge [fontname=\"Helvetica\", fontsize=8, fontcolor=\"#555555\", color=\"#455A64\"];\n";

    // Arestas (Conexões)
    for (int i = 0; i < n; ++i) {
        for (auto& edge : adj[i]) {
            int j = edge.first;
            int peso = edge.second;
            if (i < j) {
                out << "  " << i << " -- " << j << " [label=\"" << peso << "\", penwidth=0.8];\n";
            }
        }
    }

    // Nós e Rastro
    for (int i = 0; i < n; ++i) {
        // Nó atual
        out << "  " << i << " [pos=\"" << posicoes[i].x << "," << posicoes[i].y << "!\"];\n";

        if (movimentoRealizado) {
            out << "  \"" << i << "_ghost\" [pos=\"" << posicoesAntigas[i].x << "," << posicoesAntigas[i].y 
                << "!\", label=\"\", shape=circle, width=0.08, style=filled, fillcolor=\"#BDBDBD\", color=\"#9E9E9E\"];\n";
        
            out << "  \"" << i << "_ghost\" -- " << i << " [style=dotted, color=\"#EF5350\", penwidth=0.8, arrowhead=none];\n";
        }
    }

    out << "}\n";
    out.close();
}

// (Mantenha dijkstra, simularMensagens, descobrirTopologia e gerarTabelas igual...)
void Grafo::dijkstra(int origem, std::vector<int>& dist, std::vector<int>& prev) const {
    dist.assign(n, 99999);
    prev.assign(n, -1);
    dist[origem] = 0;
    using pii = std::pair<int,int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, origem});

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int peso = edge.second;
            int alt = dist[u] + peso; 
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }
}

void Grafo::simularMensagens(int origem) const {
    std::vector<int> dist, prev;
    dijkstra(origem, dist, prev);
    for (int destino = 0; destino < n; ++destino) {
        if (destino == origem) continue;
        if (prev[destino] == -1) {
            std::cout << "Rota " << origem << " -> " << destino << ": [SEM ROTA - DESCONECTADO]\n";
            continue;
        }
        std::vector<int> caminho;
        for (int v = destino; v != -1; v = prev[v]) caminho.push_back(v);
        std::reverse(caminho.begin(), caminho.end());
        std::cout << "Rota " << origem << " -> " << destino << ": ";
        for (size_t i = 0; i < caminho.size(); ++i) {
            std::cout << caminho[i];
            if (i != caminho.size()-1) std::cout << "->";
        }
        std::cout << " (Custo: " << dist[destino] << ")\n";
    }
}

void Grafo::descobrirTopologia(int origem) const {
    std::vector<bool> conhecido(n, false);
    std::queue<int> fila;
    fila.push(origem);
    conhecido[origem] = true;
    std::cout << "\n Descoberta de topologia iniciada no nó " << origem << ":\n";
    while (!fila.empty()) {
        int u = fila.front(); fila.pop();
        for (auto& edge : adj[u]) {
            int v = edge.first;
            if (!conhecido[v]) {
                conhecido[v] = true;
                fila.push(v);
            }
        }
    }
    std::cout << "✅ Descoberta concluída.\n";
}

void Grafo::gerarTabelasDeRoteamento() const {
    std::cout << "\n Tabelas de Roteamento:\n";
    for (int origem = 0; origem < n; ++origem) {
        std::vector<int> dist, prev;
        dijkstra(origem, dist, prev);
        std::cout << "\nTabela do nó " << origem << ":\n";
        std::cout << "Destino | Prox. Salto | Custo\n";
        std::cout << "-------------------------------\n";
        for (int destino = 0; destino < n; ++destino) {
            if (destino == origem) continue;
            if (dist[destino] >= 99999) continue;
            int prox = destino;
            while (prev[prox] != origem && prev[prox] != -1) prox = prev[prox];
            std::cout << "   " << std::setw(2) << destino << "   |      " 
                      << std::setw(2) << prox << "     |   " 
                      << std::setw(3) << dist[destino] << "\n";
        }
    }
}