# 🌐 Network Discovery Simulator

Simulador de rede dinâmica com mobilidade inteligente, descoberta de topologia e roteamento adaptativo.

## 📋 Descrição

Este projeto simula uma rede de computadores móveis (MANETs - Mobile Ad-Hoc Networks) onde:
- **Nós se movem** dinamicamente no espaço 2D
- **Conexões são criadas/perdidas** baseadas na distância entre nós
- **Rotas são recalculadas** automaticamente após cada movimento
- **Visualização gráfica** mostra a evolução da rede em tempo real

### Características Principais

✨ **Física de Movimento Realista**
- Movimento browniano (aleatório)
- Repulsão entre nós (evita sobreposição)
- Atração ao centro (mantém rede coesa)

🔗 **Topologia Dinâmica**
- Conexões baseadas em alcance de rádio (140 unidades)
- Pesos das arestas proporcionais à distância
- Reconexão automática após movimento

📊 **Algoritmos de Rede**
- **Dijkstra**: Cálculo de menor caminho
- **BFS**: Descoberta de topologia
- **Tabelas de Roteamento**: Atualizadas a cada passo

🎨 **Visualização com Graphviz**
- Rastro de movimento (nó fantasma + linha pontilhada)
- Cores suaves e design profissional
- Histórico de passos salvos automaticamente

---

## 🛠️ Bibliotecas e Dependências

### Bibliotecas C++ (STL - já incluídas no compilador)
- `<vector>` - estruturas de dados dinâmicas
- `<queue>` - fila de prioridade para Dijkstra
- `<random>` - geração de números aleatórios
- `<thread>` e `<chrono>` - delays entre passos
- `<fstream>` - leitura/escrita de arquivos

### Dependências Externas

#### **Graphviz** (OBRIGATÓRIO)
Ferramenta para gerar gráficos a partir de arquivos `.dot`

**Site oficial:** https://graphviz.org/download/

---

## 📥 Instalação

### 🐧 **Linux (Ubuntu/Debian)**

```bash
# Instalar compilador C++ e Graphviz
sudo apt update
sudo apt install build-essential graphviz

# Clonar/Baixar o projeto
cd netdiscovery

# Compilar
make

# Executar
make run
```

### 🍎 **macOS**

```bash
# Instalar Homebrew (se não tiver)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar dependências
brew install gcc graphviz

# Compilar e executar
make
make run
```

### 🪟 **Windows**

#### **Opção 1: WSL (Recomendado)**
```powershell
# Instalar WSL2 (PowerShell como Admin)
wsl --install

# Reiniciar e abrir Ubuntu WSL
# Seguir instruções do Linux acima
```

#### **Opção 2: MinGW + Graphviz**

1. **Instalar MinGW-w64:**
   - Baixar de: https://www.mingw-w64.org/
   - Adicionar `C:\mingw64\bin` ao PATH do Windows

2. **Instalar Graphviz:**
   - Baixar installer: https://graphviz.org/download/
   - Adicionar `C:\Program Files\Graphviz\bin` ao PATH

3. **Compilar:**
```cmd
mingw32-make
build\netdiscovery.exe
```

#### **Opção 3: MSYS2 (Mais Simples)**
```bash
# Instalar MSYS2: https://www.msys2.org/
# No terminal MSYS2:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-graphviz
make
./build/netdiscovery
```

---

## 🚀 Como Usar

### Execução Básica

```bash
make run
```

### Fluxo de Uso

1. **Defina o número de nós:**
   ```
   Digite o número de nós da rede: 8
   ```

2. **Estado inicial é gerado:**
   - Matriz de adjacência impressa
   - Grafo salvo em `output/grafo_inicial.png`

3. **Escolha nó de origem para teste:**
   ```
   Digite o nó de origem para teste inicial: 0
   ```

4. **Simulação automática inicia:**
   - A cada 10 segundos, os nós se movem
   - Conexões são atualizadas
   - Tabelas de roteamento são exibidas
   - Imagens são salvas em `output/`

5. **Parar a simulação:**
   ```
   Pressione Ctrl+C
   ```

### Visualizar Resultados

```bash
# Abrir imagem principal
xdg-open output/grafo.png  # Linux
open output/grafo.png      # macOS
start output/grafo.png     # Windows

# Ver histórico
ls output/grafo_passo_*.png
```

---

## 📁 Estrutura do Projeto

```
netdiscovery/
├── Makefile              # Automação de compilação
├── README.md             # Este arquivo
├── include/
│   └── grafo.hpp         # Cabeçalho da classe Grafo
├── src/
│   ├── main.cpp          # Programa principal
│   └── grafo.cpp         # Implementação do grafo
├── build/                # Objetos compilados (gerado)
│   └── netdiscovery      # Executável
└── output/               # Resultados (gerado)
    ├── grafo.dot         # Arquivo Graphviz
    ├── grafo_inicial.png # Estado inicial
    ├── grafo.png         # Estado atual
    └── grafo_passo_N.png # Histórico de passos
```

---

## ⚙️ Parâmetros Ajustáveis

### No código `src/grafo.cpp`:

```cpp
// Física de Movimento (linha ~78)
const double DISTANCIA_MINIMA = 90.0;  // Distância mínima entre nós
const double FORCA_REPULSAO = 40.0;    // Força de repulsão
const double ALCANCE_MAXIMO = 140.0;   // Alcance de rádio

// Área de simulação
const double MIN_MAP = 10.0;
const double MAX_MAP = 490.0;
```

### No código `src/main.cpp`:

```cpp
// Densidade e pesos (linha 13)
g.gerarTopologiaAleatoria(0.3, 20); // densidade=0.3, peso_max=20

// Intervalo de movimento (linha 37)
std::this_thread::sleep_for(std::chrono::seconds(10)); // 10 segundos
```

---

## 🧹 Limpeza

```bash
# Remover arquivos compilados e resultados
make clean
```

---

## 🐛 Troubleshooting

### Erro: `neato: command not found`
**Causa:** Graphviz não instalado ou não está no PATH  
**Solução:**
```bash
# Verificar instalação
neato -V

# Se não encontrar, instalar Graphviz
# Linux: sudo apt install graphviz
# macOS: brew install graphviz
# Windows: Adicionar ao PATH
```

### Erro: `No such file or directory: output/`
**Causa:** Pasta output não foi criada  
**Solução:** O Makefile cria automaticamente, mas pode fazer manualmente:
```bash
mkdir -p build output
```

### Imagens não abrem automaticamente
**Solução:** Abrir manualmente com visualizador de imagens:
```bash
# Linux
eog output/grafo.png

# macOS
open output/grafo.png

# Windows
explorer output\grafo.png
```

### Compilação falha no Windows
**Causa:** PATH não configurado corretamente  
**Solução:** Use WSL ou verifique se MinGW/MSYS2 está no PATH do sistema

---

## 📚 Conceitos Implementados

### Algoritmos
- **Dijkstra** - Menor caminho com complexidade O((V+E) log V)
- **BFS** - Busca em largura para descoberta de topologia
- **Union-Find implícito** - Garantia de conectividade do grafo

### Estruturas de Dados
- **Lista de adjacências** - Representação eficiente do grafo
- **Priority Queue** - Heap para Dijkstra
- **Vectors dinâmicos** - Coordenadas e estado dos nós

### Física
- **Movimento Browniano** - Simulação de mobilidade aleatória
- **Forças de repulsão** - Modelo de partículas carregadas
- **Atração ao centro** - Força centrípeta para manter coesão

---

## 📖 Referências

- [Graphviz Documentation](https://graphviz.org/documentation/)
- [Dijkstra's Algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
- [Mobile Ad Hoc Networks (MANETs)](https://en.wikipedia.org/wiki/Mobile_ad_hoc_network)

---

## 👨‍💻 Autor

Luiz Fernando dos Santos Guimarães

Projeto desenvolvido para estudo de **Redes de Computadores** e **Algoritmos de Grafos**.

**Licença:** MIT (uso livre para fins educacionais)
