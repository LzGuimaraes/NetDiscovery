#pragma once
#include <vector>
#include <string>
#include <utility> // Para std::pair

struct Coordenada {
    double x, y;
};

class Grafo {
public:
    Grafo(int n);
    void gerarTopologiaAleatoria(double densidade = 0.2, int pesoMax = 10);
    void imprimirMatriz() const;
    void salvarDot(const std::string& filename) const;
    void dijkstra(int origem, std::vector<int>& dist, std::vector<int>& prev) const;
    void simularMensagens(int origem) const;
    void descobrirTopologia(int origem) const;
    void gerarTabelasDeRoteamento() const;

    // NOVOS MÉTODOS PARA MOBILIDADE
    void aplicarMobilidade(double maxDeslocamento);

private:
    int n;
    std::vector<std::vector<std::pair<int, int>>> adj; 
    
    // NOVOS MEMBROS
    std::vector<Coordenada> posicoes;
    std::vector<Coordenada> posicoesAntigas;
    bool movimentoRealizado; // Flag para controlar se desenhamos o rastro

    void garantirConexao();
};