#pragma once
#include <vector>
#include <string>

class Grafo {
public:
    Grafo(int n);
    void gerarTopologiaAleatoria(double densidade = 0.2);
    void imprimirMatriz() const;
    void salvarDot(const std::string& filename) const;
    void dijkstra(int origem, std::vector<int>& dist, std::vector<int>& prev) const;
    void simularMensagens(int origem) const;
    void descobrirTopologia(int origem) const;
    void gerarTabelasDeRoteamento() const;

private:
    int n;
    std::vector<std::vector<int>> adj;
    void garantirConexao();
};
