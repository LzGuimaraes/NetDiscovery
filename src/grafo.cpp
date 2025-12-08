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
#include <thread> 
#include <chrono>

Grafo::Grafo(int n) : n(n), adj(n), posicoes(n), posicoesAntigas(n), movimentoRealizado(false) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(100.0, 400.0); 

    for(int i=0; i<n; ++i) {
        posicoes[i] = {dist(gen), dist(gen)};
        posicoesAntigas[i] = posicoes[i];
    }
}

void Grafo::gerarTopologiaAleatoria(double densidade) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> pesoDis(0, 20);

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (dis(gen) < densidade) {
                int distFisica = 1; 
                int pesoQoS = pesoDis(gen); 
                adj[i].push_back({j, distFisica, pesoQoS});
                adj[j].push_back({i, distFisica, pesoQoS});
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
                if (!visitado[edge.destino]) {
                    visitado[edge.destino] = true;
                    q.push(edge.destino);
                }
            }
        }
    };
    bfs(0);
    for (int i = 0; i < n; ++i) {
        if (!visitado[i]) {
            for (int j = 0; j < n; ++j) {
                if (visitado[j]) {
                    adj[i].push_back({j, 1, 10});
                    adj[j].push_back({i, 1, 10});
                    break;
                }
            }
            bfs(i);
        }
    }
}

void Grafo::aplicarMobilidade(double maxDeslocamento) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-maxDeslocamento * 0.5, maxDeslocamento * 0.5); 
    std::uniform_int_distribution<> pesoDis(0, 20);

    const double ALCANCE_MAXIMO = 140.0; 
    const double MIN_MAP = 10.0;
    const double MAX_MAP = 490.0;
    // Parâmetros de força física simplificados para brevidade
    
    movimentoRealizado = true;
    std::vector<Coordenada> novasPosicoes = posicoes;

    for (int i = 0; i < n; ++i) {
        posicoesAntigas[i] = posicoes[i];
        novasPosicoes[i].x += dis(gen);
        novasPosicoes[i].y += dis(gen);
        
        // Limites do mapa
        if(novasPosicoes[i].x < MIN_MAP) novasPosicoes[i].x = MIN_MAP;
        if(novasPosicoes[i].x > MAX_MAP) novasPosicoes[i].x = MAX_MAP;
        if(novasPosicoes[i].y < MIN_MAP) novasPosicoes[i].y = MIN_MAP;
        if(novasPosicoes[i].y > MAX_MAP) novasPosicoes[i].y = MAX_MAP;
    }
    posicoes = novasPosicoes;

    for(int i=0; i<n; ++i) adj[i].clear();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = std::sqrt(std::pow(posicoes[i].x - posicoes[j].x, 2) + 
                                    std::pow(posicoes[i].y - posicoes[j].y, 2));

            if (dist <= ALCANCE_MAXIMO) {
                int distFisica = 1 + (int)(dist / 10.0);
                int pesoQoS = pesoDis(gen); // Peso dinâmico

                adj[i].push_back({j, distFisica, pesoQoS});
                adj[j].push_back({i, distFisica, pesoQoS});
            }
        }
    }
}

void Grafo::imprimirMatriz() const {
    std::cout << "\n Matriz de Pesos QoS (0-20):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int p = -1;
            for (auto& edge : adj[i]) {
                if (edge.destino == j) { p = edge.pesoQoS; break; }
            }
            if(p != -1) std::cout << std::setw(3) << p << " ";
            else std::cout << "  . ";
        }
        std::cout << "\n";
    }
}

void Grafo::salvarDot(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) return;
    out.imbue(std::locale::classic());

    out << "graph G {\n";
    out << "  graph [bb=\"0,0,500,500\", inputscale=72, splines=line, bgcolor=\"white\"];\n";
    out << "  node [shape=circle, style=\"filled,setlinewidth(1.5)\", fillcolor=\"#E0F7FA\", color=\"#006064\", fontname=\"Helvetica-Bold\", fontsize=10, fixedsize=true, width=0.4];\n";
    out << "  edge [fontname=\"Helvetica\", fontsize=8];\n";

    for (int i = 0; i < n; ++i) {
        for (auto& edge : adj[i]) {
            int j = edge.destino;
            if (i < j) {
                // Configuração visual baseada no Peso QoS
                std::string cor = "#000000";
                std::string estilo = "solid";
                std::string largura = "1.0";

                // Peso baixo (0-7) = Ótimo (Verde)
                if (edge.pesoQoS <= 7) { 
                    cor = "#2E7D32"; 
                    largura = "2.0";
                } 
                // Peso alto (15-20) = Ruim/Congestionado (Vermelho)
                else if (edge.pesoQoS >= 15) { 
                    cor = "#C62828"; 
                    estilo = "dashed";
                }

                // VOLTANDO PARA A VISUALIZAÇÃO LIMPA (APENAS O NÚMERO DO PESO)
                out << "  " << i << " -- " << j 
                    << " [label=\"" << edge.pesoQoS << "\", " 
                    << "color=\"" << cor << "\", style=\"" << estilo << "\", penwidth=" << largura << "];\n";
            }
        }
    }

    // Posições dos nós
    for (int i = 0; i < n; ++i) {
        out << "  " << i << " [pos=\"" << posicoes[i].x << "," << posicoes[i].y << "!\"];\n";
    }
    out << "}\n";
    out.close();
}

// IMPLEMENTAÇÃO DO DIJKSTRA COM MÉTRICA ADITIVA
// FÓRMULA: d(p) = d(i,j) + d(j,k) + ... + d(l,m)
void Grafo::dijkstraAditivo(int origem, std::vector<int>& dist, std::vector<int>& prev) const {
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
            int v = edge.destino;
            
            if (edge.pesoQoS >= 15) {
                continue; 
            }

            int custoLink = edge.pesoQoS; 
            int novoCustoTotal = dist[u] + custoLink; 
            
            if (novoCustoTotal < dist[v]) {
                dist[v] = novoCustoTotal;
                prev[v] = u;
                pq.push({novoCustoTotal, v});
            }
        }
    }
}

void Grafo::simularRotasQoS(int origem) const {
    std::vector<int> dist, prev;
    
    // Chama a versão puramente aditiva
    dijkstraAditivo(origem, dist, prev); 

    std::cout << ">>> Rotas QoS (Métrica Aditiva) de " << origem << ":\n";
    for (int destino = 0; destino < n; ++destino) {
        if (destino == origem) continue;
        if (prev[destino] == -1) {
            std::cout << "   -> " << destino << ": [DESCONECTADO]\n";
            continue;
        }
        std::vector<int> caminho;
        for (int v = destino; v != -1; v = prev[v]) caminho.push_back(v);
        std::reverse(caminho.begin(), caminho.end());
        
        std::cout << "   -> " << destino << ": ";
        for (size_t i = 0; i < caminho.size(); ++i) {
            std::cout << caminho[i] << (i!=caminho.size()-1 ? "->" : "");
        }
        std::cout << " (CUSTO TOTAL ADITIVO: " << dist[destino] << ")\n";
    }
    std::cout << "-------------------------------------------------------\n";
}

void Grafo::descobrirTopologia(int origem) const {
    std::cout << "\n>>> VIZINHANÇA DIRETA DO NÓ " << origem << " <<<\n";
    if (adj[origem].empty()) {
        std::cout << " [!] Nó Isolado.\n"; 
        return;
    }

    for (auto& edge : adj[origem]) {
        std::string estado = (edge.pesoQoS > 15) ? "CONGESTIONADO" : "LIVRE";
        std::cout << " -> Vizinho: " << edge.destino 
                  << " | Peso QoS: " << std::setw(2) << edge.pesoQoS 
                  << " [" << estado << "]\n";
    }
}