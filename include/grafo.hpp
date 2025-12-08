#pragma once
#include <vector>
#include <string>

struct Coordenada {
    double x, y;
};

struct Aresta {
    int destino;
    int distanciaFisica; // Mantido apenas para visualização/debug
    int pesoQoS;         // A métrica principal (Custo/Latência)
};

class Grafo {
public:
    Grafo(int n);
    void gerarTopologiaAleatoria(double densidade = 0.2);
    void imprimirMatriz() const;
    
    // Atualizado: Visualização mostra D (Distância) e Q (QoS)
    void salvarDot(const std::string& filename) const; 

    // Única simulação restante: QoS Aditivo
    void simularRotasQoS(int origem) const;

    // Ferramentas
    void descobrirTopologia(int origem) const;
    void aplicarMobilidade(double maxDeslocamento);

private:
    int n;
    std::vector<std::vector<Aresta>> adj; 
    
    std::vector<Coordenada> posicoes;
    std::vector<Coordenada> posicoesAntigas;
    bool movimentoRealizado;

    void garantirConexao();
    
    // Dijkstra específico para métrica aditiva
    void dijkstraAditivo(int origem, std::vector<int>& dist, std::vector<int>& prev) const;
};