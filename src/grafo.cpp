#include "grafo.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <fstream>
#include <random>
#include <algorithm>

Grafo::Grafo(int n) : n(n), adj(n) {}

// Gera topologia aleatória e conexa
void Grafo::gerarTopologiaAleatoria(double densidade) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (dis(gen) < densidade) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    garantirConexao();
}

// Garante que todos os nós estejam conectados
void Grafo::garantirConexao() {
    std::vector<bool> visitado(n, false);

    auto bfs = [&](int start){
        std::queue<int> q;
        q.push(start);
        visitado[start] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
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
            // conecta i a algum nó visitado
            for (int j = 0; j < n; ++j) {
                if (visitado[j]) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                    break;
                }
            }
            bfs(i); // marca componente conectado
        }
    }
}

// Mostra matriz de adjacência
void Grafo::imprimirMatriz() const {
    std::cout << "\n📡 Matriz de Adjacência:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int peso = std::find(adj[i].begin(), adj[i].end(), j) != adj[i].end() ? 1 : 0;
            std::cout << " " << peso << " ";
        }
        std::cout << "\n";
    }
}

// Salva grafo em formato DOT
void Grafo::salvarDot(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Erro ao criar arquivo DOT!\n";
        return;
    }
    out << "graph G {\n";
    for (int i = 0; i < n; ++i) {
        for (int j : adj[i]) {
            if (i < j)
                out << "  " << i << " -- " << j << ";\n";
        }
    }
    out << "}\n";
    out.close();
}

// Dijkstra com peso 1
void Grafo::dijkstra(int origem, std::vector<int>& dist, std::vector<int>& prev) const {
    dist.assign(n, 999);
    prev.assign(n, -1);
    dist[origem] = 0;
    using pii = std::pair<int,int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, origem});

    while(!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (int v : adj[u]) {
            int alt = dist[u] + 1; // peso 1
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt,v});
            }
        }
    }
}

// Simula mensagens mostrando cada nó intermediário
void Grafo::simularMensagens(int origem) const {
    std::vector<int> dist, prev;
    dijkstra(origem, dist, prev);
    std::cout << "\n💬 Mensagens enviadas a partir do nó " << origem << ":\n";

    for (int destino = 0; destino < n; ++destino) {
        if (destino == origem) continue;
        if (prev[destino] == -1) {
            std::cout << "Rota " << origem << " -> " << destino << ": inacessível\n";
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
        std::cout << "\n";
    }
}
