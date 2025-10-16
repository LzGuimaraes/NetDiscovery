#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>

using namespace std;

void mostrarGrafo(const vector<vector<int>>& g) {
    cout << "Grafo lista de Adjacencia" << endl;
    for(int i = 0; i <g.size(); ++i) {
        cout << "Nó " << i << ": ";
        vector<int> vizinhos = g[i];
        sort(vizinhos.begin(), vizinhos.end());
        for (int vizinho : vizinhos) {
            cout << vizinho << " ";
        } 
        cout << endl;
    }
    cout << "----------------------------------" << endl;
}

vector<vector<int>> gerarTopologia(int N, double p) {
    vector<vector<int>> g(N);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j ) {
            if (dis(gen)<p){
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    return g;
}

void bfs(int inicioNo, const vector<vector<int>> & g, vector <bool>& visitado){
    queue<int> q;
    // "u" representa os nós e v representa um vizinho do nó
    // g[1] = {1,2,3,4} g[1] é u e V {1,2,3,4}
    q.push(inicioNo);
    visitado[inicioNo] = true;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g [u]) {
            if (!visitado[v]) {
                visitado[v] = true;
                q.push(v);
            }
        }
    }
}

void garantirConexao(vector<vector<int>>& g){
    int N = g.size();
    if(N==0) return;
    vector<bool> visitado(N, false);
    vector<int> componenteRepresentativo;

    cout << "\nProcuranco por componentes desconectados" << endl;

    for (int i = 0; i < N; i++) {
        if(!visitado[i]) {
            componenteRepresentativo.push_back(i);

            bfs(i,g,visitado);
        }
    }
    if(componenteRepresentativo.size() > 1) {
        cout << "Encontrados " << componenteRepresentativo.size() << " componentes. Conectando-os agora..." << std::endl;

        for(size_t i =0; i < componenteRepresentativo.size() - 1; ++i) {
            int u_no = componenteRepresentativo[i];
            int v_no = componenteRepresentativo[i+1];

            cout << "Criando ponte entre o no " << u_no << " e o no " << v_no << endl;

            g[u_no].push_back(v_no);
            g[v_no].push_back(u_no);
        }
    } else{
        cout << "Grafo ja conectado" << endl;
    }
}

int main() {
    int N = 8;
    double p = 0.2;

    cout << "Gerando topologia com N = " << N << " e P = " << p << endl;
    auto g = gerarTopologia(N,p);
    cout << "\nGrafo gerado inicialmente: " << endl;
    mostrarGrafo(g);
    garantirConexao(g);

    cout << "Grafo final (após garantir conectividade)" << endl;
    mostrarGrafo(g);

    return 0;

}