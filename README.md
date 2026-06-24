# Biblioteca de Grafos em C++ 🕸️

Uma implementação robusta e orientada a objetos de teoria dos grafos em C++, desenvolvida para estudos avançados e como base para a resolução do **Problema do Carteiro Chinês**.

## 🚀 Funcionalidades

A classe `Grafo` suporta grafos direcionados, não-direcionados e multigrafos (múltiplas arestas entre os mesmos vértices), garantindo flexibilidade estrutural.

* **Buscas e Percursos:** DFS (Profundidade) e BFS (Largura).
* **Caminho Mínimo:** Algoritmo de Dijkstra para grafos com peso.
* **Componentes Fortemente Conexas:** Algoritmo de Kosaraju otimizado.
* **Detecção de Ciclos:** Verificação baseada em percurso e contagem de arestas.
* **Estruturas Avançadas:** Validação de grafos bipartidos e identificação de vértices de grau ímpar (base para algoritmos Eulerianos).
* **Persistência:** Exportação e salvamento da estrutura do grafo em arquivo de texto.

## 📁 Estrutura do Projeto

* `include/grafo.hpp`: O "motor" principal. Contém toda a classe, atributos e algoritmos.
* `src/main.cpp`: Ponto de entrada do programa e testes práticos.

## 🛠️ Como Executar

Este projeto utiliza um `Makefile` para facilitar a compilação. Certifique-se de ter o `g++` e o `make` instalados.

1. Clone o repositório:
```bash
git clone [https://github.com/hanrri/Grafos.git](https://github.com/hanrri/Grafos.git)
cd Grafos
