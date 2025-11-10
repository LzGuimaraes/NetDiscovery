<<<<<<< HEAD
# NetDiscovery

## Descrição

NetDiscovery é um simulador de topologia de redes desenvolvido em C++ que permite visualizar e analisar a propagação de mensagens em redes de computadores. O projeto gera grafos aleatórios representando redes, calcula rotas ótimas entre nós usando o algoritmo de Dijkstra e visualiza a topologia através de grafos gerados automaticamente.

## Funcionalidades

- **Geração de Topologia Aleatória**: Cria redes com densidade configurável e garante conectividade entre todos os nós
- **Visualização Gráfica**: Exporta a topologia da rede em formato PNG através do Graphviz
- **Simulação de Mensagens**: Calcula e exibe as rotas mais curtas entre um nó origem e todos os demais
- **Matriz de Adjacência**: Mostra a representação matricial da rede
- **Algoritmo de Dijkstra**: Implementa busca de caminho mais curto com pesos unitários

## Estrutura do Projeto

```
NetDiscovery/
├── include/
│   └── grafo.hpp          # Definição da classe Grafo
├── src/
│   ├── main.cpp           # Programa principal
│   └── grafo.cpp          # Implementação da classe Grafo
├── build/                 # Arquivos objeto e executável (gerado)
├── output/                # Arquivos de saída (grafo.dot e grafo.png)
├── Makefile              # Script de compilação
└── README.md             # Este arquivo
```

## Dependências

### Linux (Ubuntu/Debian)

```bash
# Compilador C++ com suporte a C++17
sudo apt update
sudo apt install g++ make

# Graphviz para visualização de grafos
sudo apt install graphviz

# Visualizador de imagens (opcional, para 'make run')
sudo apt install xdg-utils
```

### Linux (Fedora/RHEL)

```bash
sudo dnf install gcc-c++ make graphviz
```

### Linux (Arch)

```bash
sudo pacman -S gcc make graphviz
```

### macOS

```bash
# Instalar Homebrew (se ainda não tiver)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar dependências
brew install gcc make graphviz
```

### Windows

**Opção 1: WSL (Recomendado)**
1. Instale o WSL2 seguindo a [documentação oficial da Microsoft](https://docs.microsoft.com/windows/wsl/install)
2. Dentro do WSL, siga as instruções para Linux (Ubuntu)

**Opção 2: MinGW/MSYS2**
1. Instale o [MSYS2](https://www.msys2.org/)
2. No terminal MSYS2, execute:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-graphviz make
```
3. Adicione `C:\msys64\mingw64\bin` ao PATH do sistema

**Opção 3: Visual Studio**
1. Instale o Visual Studio com suporte a C++
2. Instale o Graphviz separadamente do [site oficial](https://graphviz.org/download/)
3. Adapte o Makefile ou compile manualmente

## Compilação e Execução

### Compilar e executar

```bash
make
```

Este comando irá:
1. Compilar os arquivos fonte
2. Gerar o executável `build/netdiscovery`
3. Executar o programa automaticamente

### Apenas compilar

```bash
make dot
```

### Executar e abrir a visualização

```bash
make run
```

Abre automaticamente a imagem gerada (Linux com xdg-open)

### Limpar arquivos de compilação

```bash
make clean
```

## Uso do Programa

Ao executar o programa, você será solicitado a:

1. **Número de nós**: Digite quantos computadores/dispositivos a rede terá
2. **Nó de origem**: Digite o número do nó (0 a n-1) que será a origem das mensagens

### Exemplo de execução

```
Digite o número de nós da rede: 5

📡 Matriz de Adjacência:
 0  1  1  0  1 
 1  0  1  1  0 
 1  1  0  0  1 
 0  1  0  0  1 
 1  0  1  1  0 

Digite o nó de origem para simular mensagens: 0

💬 Mensagens enviadas a partir do nó 0:
Rota 0 -> 1: 0->1
Rota 0 -> 2: 0->2
Rota 0 -> 3: 0->1->3
Rota 0 -> 4: 0->4

✅ Grafo salvo em 'output/grafo.png'
```

## 🧮 Como Funciona

### Geração da Topologia

O programa gera uma rede aleatória onde:
- Cada par de nós tem uma probabilidade (densidade = 20% por padrão) de serem conectados
- Um algoritmo de BFS garante que todos os nós estejam conectados
- Se algum nó ficar isolado, ele é conectado automaticamente ao grafo principal

### Algoritmo de Dijkstra

Para encontrar os caminhos mais curtos:
- Utiliza uma fila de prioridade para explorar nós em ordem de distância
- Considera peso unitário (1) para todas as conexões
- Mantém um vetor de predecessores para reconstruir os caminhos

### Visualização

- Exporta o grafo no formato DOT (Graphviz)
- Converte automaticamente para PNG usando o comando `dot`
- A imagem final mostra todos os nós e suas conexões

## 🔍 Detalhes Técnicos

- **Linguagem**: C++17
- **Estrutura de dados**: Lista de adjacência
- **Complexidade do Dijkstra**: O((V + E) log V)
- **Gerador de números aleatórios**: `std::mt19937` (Mersenne Twister)

## 📝 Possíveis Melhorias

- Adicionar pesos variáveis nas arestas
- Implementar outros algoritmos de roteamento (Bellman-Ford, Floyd-Warshall)
- Criar interface gráfica interativa
- Simular falhas de nós/enlaces
- Adicionar métricas de desempenho da rede
- Suportar importação de topologias personalizadas

## 🐛 Solução de Problemas

**Erro: "dot: command not found"**
- Instale o Graphviz conforme as instruções de dependências

**Erro de compilação C++17**
- Verifique se seu compilador suporta C++17
- No GCC: versão 7.0 ou superior

**Imagem não abre automaticamente**
- Execute manualmente: `xdg-open output/grafo.png` (Linux)
- Ou abra o arquivo `output/grafo.png` diretamente

## 📄 Licença

Projeto educacional livre para uso e modificação.

## 👥 Contribuições

=======
# NetDiscovery

## Descrição

NetDiscovery é um simulador de topologia de redes desenvolvido em C++ que permite visualizar e analisar a propagação de mensagens em redes de computadores. O projeto gera grafos aleatórios representando redes, calcula rotas ótimas entre nós usando o algoritmo de Dijkstra e visualiza a topologia através de grafos gerados automaticamente.

## Funcionalidades

- **Geração de Topologia Aleatória**: Cria redes com densidade configurável e garante conectividade entre todos os nós
- **Visualização Gráfica**: Exporta a topologia da rede em formato PNG através do Graphviz
- **Simulação de Mensagens**: Calcula e exibe as rotas mais curtas entre um nó origem e todos os demais
- **Matriz de Adjacência**: Mostra a representação matricial da rede
- **Algoritmo de Dijkstra**: Implementa busca de caminho mais curto com pesos unitários

## Estrutura do Projeto

```
NetDiscovery/
├── include/
│   └── grafo.hpp          # Definição da classe Grafo
├── src/
│   ├── main.cpp           # Programa principal
│   └── grafo.cpp          # Implementação da classe Grafo
├── build/                 # Arquivos objeto e executável (gerado)
├── output/                # Arquivos de saída (grafo.dot e grafo.png)
├── Makefile              # Script de compilação
└── README.md             # Este arquivo
```

## Dependências

### Linux (Ubuntu/Debian)

```bash
# Compilador C++ com suporte a C++17
sudo apt update
sudo apt install g++ make

# Graphviz para visualização de grafos
sudo apt install graphviz

# Visualizador de imagens (opcional, para 'make run')
sudo apt install xdg-utils
```

### Linux (Fedora/RHEL)

```bash
sudo dnf install gcc-c++ make graphviz
```

### Linux (Arch)

```bash
sudo pacman -S gcc make graphviz
```

### macOS

```bash
# Instalar Homebrew (se ainda não tiver)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar dependências
brew install gcc make graphviz
```

### Windows

**Opção 1: WSL (Recomendado)**
1. Instale o WSL2 seguindo a [documentação oficial da Microsoft](https://docs.microsoft.com/windows/wsl/install)
2. Dentro do WSL, siga as instruções para Linux (Ubuntu)

**Opção 2: MinGW/MSYS2**
1. Instale o [MSYS2](https://www.msys2.org/)
2. No terminal MSYS2, execute:
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-graphviz make
```
3. Adicione `C:\msys64\mingw64\bin` ao PATH do sistema

**Opção 3: Visual Studio**
1. Instale o Visual Studio com suporte a C++
2. Instale o Graphviz separadamente do [site oficial](https://graphviz.org/download/)
3. Adapte o Makefile ou compile manualmente

## Compilação e Execução

### Compilar e executar

```bash
make
```

Este comando irá:
1. Compilar os arquivos fonte
2. Gerar o executável `build/netdiscovery`
3. Executar o programa automaticamente

### Apenas compilar

```bash
make dot
```

### Executar e abrir a visualização

```bash
make run
```

Abre automaticamente a imagem gerada (Linux com xdg-open)

### Limpar arquivos de compilação

```bash
make clean
```

## Uso do Programa

Ao executar o programa, você será solicitado a:

1. **Número de nós**: Digite quantos computadores/dispositivos a rede terá
2. **Nó de origem**: Digite o número do nó (0 a n-1) que será a origem das mensagens

### Exemplo de execução

```
Digite o número de nós da rede: 5

📡 Matriz de Adjacência:
 0  1  1  0  1 
 1  0  1  1  0 
 1  1  0  0  1 
 0  1  0  0  1 
 1  0  1  1  0 

Digite o nó de origem para simular mensagens: 0

💬 Mensagens enviadas a partir do nó 0:
Rota 0 -> 1: 0->1
Rota 0 -> 2: 0->2
Rota 0 -> 3: 0->1->3
Rota 0 -> 4: 0->4

✅ Grafo salvo em 'output/grafo.png'
```

## 🧮 Como Funciona

### Geração da Topologia

O programa gera uma rede aleatória onde:
- Cada par de nós tem uma probabilidade (densidade = 20% por padrão) de serem conectados
- Um algoritmo de BFS garante que todos os nós estejam conectados
- Se algum nó ficar isolado, ele é conectado automaticamente ao grafo principal

### Algoritmo de Dijkstra

Para encontrar os caminhos mais curtos:
- Utiliza uma fila de prioridade para explorar nós em ordem de distância
- Considera peso unitário (1) para todas as conexões
- Mantém um vetor de predecessores para reconstruir os caminhos

### Visualização

- Exporta o grafo no formato DOT (Graphviz)
- Converte automaticamente para PNG usando o comando `dot`
- A imagem final mostra todos os nós e suas conexões

## 🔍 Detalhes Técnicos

- **Linguagem**: C++17
- **Estrutura de dados**: Lista de adjacência
- **Complexidade do Dijkstra**: O((V + E) log V)
- **Gerador de números aleatórios**: `std::mt19937` (Mersenne Twister)

## 📝 Possíveis Melhorias

- Adicionar pesos variáveis nas arestas
- Implementar outros algoritmos de roteamento (Bellman-Ford, Floyd-Warshall)
- Criar interface gráfica interativa
- Simular falhas de nós/enlaces
- Adicionar métricas de desempenho da rede
- Suportar importação de topologias personalizadas

## 🐛 Solução de Problemas

**Erro: "dot: command not found"**
- Instale o Graphviz conforme as instruções de dependências

**Erro de compilação C++17**
- Verifique se seu compilador suporta C++17
- No GCC: versão 7.0 ou superior

**Imagem não abre automaticamente**
- Execute manualmente: `xdg-open output/grafo.png` (Linux)
- Ou abra o arquivo `output/grafo.png` diretamente

## 📄 Licença

Projeto educacional livre para uso e modificação.

## 👥 Contribuições


>>>>>>> 2818c17 (Feat: Adiciona Descobrir topologia + Tabelas de Roteamento)
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests.