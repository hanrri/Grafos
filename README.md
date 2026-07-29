# Biblioteca de Grafos em C++ 🕸️

[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)]()

Uma biblioteca de Teoria dos Grafos moderna, robusta e orientada a objetos desenvolvida em **C++17**. Este projeto combina algoritmos clássicos de grafos com uma **Interface Interativa de Terminal (TUI)** limpa, além de um solucionador para o **Problema do Carteiro Chinês (Chinese Postman Problem - CPP)** com múltiplos algoritmos e heurísticas.

---

## 🚀 Funcionalidades da Biblioteca

A classe `Grafo` suporta grafos direcionados, não-direcionados, ponderados e multigrafos (múltiplas arestas entre os mesmos vértices), garantindo total flexibilidade.

### 🔬 Algoritmos e Propriedades
* **Buscas e Percursos:**
  * **BFS (Breadth-First Search):** Cálculo de menor distância em número de arestas e menor caminho curto.
  * **DFS (Depth-First Search):** Navegação profunda, ordenação e verificação de ciclos.
* **Caminhos Mínimos Ponderados:**
  * **Algoritmo de Dijkstra:** Encontra a rota de menor custo total acumulado em grafos com pesos.
* **Componentes e Conexidade:**
  * **Componentes Conexas:** Identificação de ilhas isoladas em grafos não-direcionados.
  * **Algoritmo de Kosaraju:** Identificação de Componentes Fortemente Conexas (SCC) em grafos direcionados.
* **Análise de Estrutura:**
  * **Verificação de Bipartição:** Validação de colorabilidade 2-cor.
  * **Detecção de Ciclos:** Identificação de ciclos em grafos simples e multigrafos.
  * **Vértices Ímpares:** Identificação de vértices com grau ímpar.
* **Problema do Carteiro Chinês (CPP):**
  * **Algoritmo de Hierholzer:** Extração completa do Circuito Euleriano.
  * **Solucionador Exato:** Enumeração por *backtracking* com *bitmask* (Garante a solução ótima global).
  * **Heurística Gulosa:** Pareamento ordenado por distâncias mínimas.
  * **Heurística do Vizinho Mais Próximo:** Pareamento por proximidade local.
* **Utilitários e Persistência:**
  * **Gerador Aleatório:** Geração automática de $M$ arestas aleatórias para testes de estresse.
  * **Sistema de Saves:** Exportação e carregamento completo de grafos em disco (`saves/*.txt`).

---

## 📁 Estrutura do Projeto

```text
Grafos/
├── include/
│   └── grafo.hpp        # Declaração da classe Grafo e tipos do Carteiro Chinês
├── src/
│   ├── grafo.cpp        # Implementação dos algoritmos de teoria dos grafos
│   └── main.cpp         # Interface Interativa de Terminal (CLI/TUI)
├── saves/               # Pasta de persistência (arquivos .txt de grafos salvos)
├── Makefile             # Script de compilação modular em C++17
└── README.md            # Documentação completa do projeto
```

---

## 🛠️ Como Compilar e Executar

### Pré-requisitos
- Compilador C++ com suporte a **C++17** (`g++` 7.0+ ou equivalente).
- Ferramenta `make`.

### Passos de Instalação

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/hanrri/Grafos.git
   cd Grafos
   ```

2. **Compile o projeto:**
   ```bash
   make
   ```

3. **Execute a aplicação:**
   ```bash
   ./programa
   ```

4. **Para limpar arquivos compilados:**
   ```bash
   make clean
   ```

---

## 📖 Tutorial de Uso: Interface Interativa (TUI)

A aplicação conta com um menu de navegação estruturado em **4 categorias principais**, com suporte a **limpeza automática de tela** e **cancelamento (`0`) em qualquer etapa**:

```text
--- MENU PRINCIPAL ---
0. Encerrar programa
1. Gerenciar e Visualizar Grafos
2. Buscas e Caminhos Mínimos (BFS / Dijkstra)
3. Propriedades e Algoritmos Avançados (Kosaraju, Carteiro Chinês, etc.)
4. Saves (Salvar e Carregar)
```

---

### 1️⃣ Gerenciar e Visualizar Grafos
Neste submenu você pode estruturar seus grafos:
- **Criar novo grafo:** Define o nome e o número de vértices.
- **Listar grafos:** Exibe os grafos atualmente carregados na memória.
- **Visualizar conexões:** Exibe a **Lista de Adjacência** detalhada com vértices e pesos.
- **Adicionar / Remover arestas:** Adiciona ou remove arestas indicando a origem e o destino passo a passo.
- **Gerar arestas aleatórias:** Adiciona $M$ arestas com pesos aleatórios de 1 a 10.
- **Excluir grafo:** Remove um grafo específico da memória.

---

### 2️⃣ Buscas e Caminhos Mínimos
Neste submenu você executa buscas de rotas:
- **Distâncias a partir de um vértice (BFS):** Mostra o número de arestas necessárias para atingir todos os outros vértices a partir de uma origem.
- **Caminho mais curto em arestas (BFS):** Informa a sequência exata de vértices para o caminho com menor número de passos entre Origem e Destino.
- **Caminho mínimo com pesos (Dijkstra):** Calcula a rota com o **menor custo acumulado de pesos**, mostrando o custo total e o caminho detalhado.

---

### 3️⃣ Propriedades e Algoritmos Avançados
Neste submenu você realiza análises avançadas:
- **Componentes Conexas:** Conta e exibe quais vértices pertencem a cada ilha desconexa.
- **Componentes Fortemente Conexas (Kosaraju):** Agrupa vértices em componentes fortemente conexas para grafos direcionados.
- **Detecção de Ciclos:** Informa se o grafo contém pelo menos um ciclo.
- **Verificação de Bipartição:** Determina se o grafo pode ser dividido em 2 conjuntos independentes.
- **Resolver Problema do Carteiro Chinês:**
  1. Escolha o grafo desejado.
  2. Escolha o algoritmo (`1. Exato`, `2. Guloso` ou `3. Vizinho Mais Próximo`).
  3. Veja em tempo real o **Tempo de Execução (ms)**, o **Custo Total**, o **Custo Adicional das Arestas Duplicadas** e o **Circuito Euleriano Completo**.

---

### 4️⃣ Saves (Salvar e Carregar)
- **Salvar grafos no PC:** Digite o nome do arquivo para salvar a sessão atual na pasta `saves/` (ou digite `.` para sobrescrever o arquivo atual).
- **Carregar grafos do PC:** Lista os arquivos `.txt` disponíveis na pasta `saves/` e permite restaurar uma sessão anterior.

---

## 💻 Exemplo de Uso como Biblioteca C++

Caso queira utilizar a classe `Grafo` diretamente em seu próprio código C++:

```cpp
#include <iostream>
#include "grafo.hpp"

int main() {
    // 1. Cria um grafo não-direcionado com 5 vértices
    Grafo g(5, "Mapa Urbano");

    // 2. Adiciona arestas com peso (origem, destino, peso)
    g.adicionar_aresta(1, 2, 10);
    g.adicionar_aresta(2, 3, 15);
    g.adicionar_aresta(1, 3, 50);
    g.adicionar_aresta(3, 4, 5);
    g.adicionar_aresta(4, 5, 20);

    // 3. Executa o Algoritmo de Dijkstra a partir do vértice 1
    std::vector<int> dist, pai;
    g.dijkstra(1, dist, pai);

    std::cout << "Menor custo do vertice 1 ao 4: " << dist[4] << std::endl;

    // 4. Resolve o Problema do Carteiro Chinês
    ResultadoCarteiroChines resultado = g.resolver_carteiro_chines(ModoCarteiroChines::EXATO_ENUMERACAO);

    std::cout << "Custo Total do Circuito do Carteiro: " << resultado.custo_total << std::endl;
    std::cout << "Tempo de Execucao: " << resultado.tempo_ms << " ms" << std::endl;

    return 0;
}
```

---

## 📄 Licença

Este projeto está licenciado sob a licença MIT - consulte o arquivo [LICENSE](LICENSE) para mais detalhes.
