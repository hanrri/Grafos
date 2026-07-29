#pragma once
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <utility>

const int INF = 0x3f3f3f3f;

enum class ModoCarteiroChines {
    EXATO_ENUMERACAO,
    GULOSO,
    VIZINHO_MAIS_PROXIMO
};

struct ResultadoCarteiroChines {
    int custo_total;
    int custo_adicional;
    std::vector<int> circuito;
    double tempo_ms;
};

class Grafo {
private:
    // =======================================================
    // 1. ATRIBUTOS
    // =======================================================
    int n_vertices;
    std::string nome;
    bool direcionado;
    bool tem_peso;
    bool permite_multiplas;
    std::vector<std::vector<std::pair<int, int>>> adj;
    std::vector<std::vector<std::pair<int, int>>> inv_adj;

    // =======================================================
    // 2. MÉTODOS AUXILIARES (HELPERS PRIVADOS)
    // =======================================================
    int dfs(int vertice, std::vector<bool>& visitados) const;
    int dfs_componente(int vertice, std::vector<int>& componente_atual, std::vector<bool>& visitados) const;
    void dfs_ciclos_n_arestas(int vertice, int& qtd_vertices, int& qtd_arestas, std::vector<bool>& visitados) const;
    bool dfs_ciclos_percorrendo(int vertice, int pai, std::vector<bool>& visitados) const;
    bool dfs_bipartido(int vertice, int cor, std::vector<int>& coloracao, std::vector<bool>& visitados) const;
    void dfs_kosaraju_1(int vertice, std::stack<int>& ordem, std::vector<bool>& visitados) const;
    void dfs_kosaraju_2(int vertice, std::vector<int>& componentes, int n_componentes, std::vector<bool>& visitados) const;
    void bfs(int vertice, std::vector<int>& dist, std::vector<int>& pai) const;

public:
    // =======================================================
    // 3. CONSTRUTOR E INFORMAÇÕES BÁSICAS
    // =======================================================
    Grafo(int vertices, std::string palavra, bool direcionado = false, bool tem_peso = false, bool permite_multiplas = true);

    const std::string& get_nome() const;
    int get_n_vertices() const;
    bool is_direcionado() const;
    bool is_ponderado() const;
    bool is_multigrafo() const;
    int get_grau(int vertice) const;
    int get_peso(int u, int v) const;
    std::vector<int> get_vertices_impares() const;
    const std::vector<std::pair<int, int>>& get_vizinhos(int vertice) const;

    // =======================================================
    // 4. MANIPULAÇÃO DA ESTRUTURA
    // =======================================================
    bool adicionar_aresta(int u, int v, int peso = 1);
    bool excluir_aresta(int u, int v, int peso_alvo = -1);
    void gerar_arestas_aleatorias(int m);

    // =======================================================
    // 5. CAMINHOS E DISTÂNCIAS
    // =======================================================
    void dijkstra(int origem, std::vector<int>& dist, std::vector<int>& pai) const;
    std::vector<int> obter_distancias(int origem) const;
    std::vector<int> obter_caminho(int origem, int destino) const;

    // =======================================================
    // 6. ANÁLISE E ALGORITMOS DE GRAFOS
    // =======================================================
    std::vector<std::vector<int>> obter_componentes() const;
    bool tem_ciclos_percorrendo() const;
    bool tem_ciclos_n_arestas() const;
    std::vector<int> kosaraju() const;
    bool verifica_bipartido() const;

    // =======================================================
    // 7. EULERIANO E PROBLEMA DO CARTEIRO CHINÊS
    // =======================================================
    std::vector<int> extrair_circuito_euleriano(int inicio = 1) const;
    ResultadoCarteiroChines resolver_carteiro_chines(ModoCarteiroChines modo = ModoCarteiroChines::EXATO_ENUMERACAO) const;

    // =======================================================
    // 8. ENTRADA E SAÍDA DE DADOS (I/O)
    // =======================================================
    void salvar_grafo(std::ofstream& arquivo) const;
};