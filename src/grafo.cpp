#include "../include/grafo.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// =======================================================
// 2. MÉTODOS AUXILIARES (HELPERS PRIVADOS)
// =======================================================
int Grafo::dfs(int vertice, vector<bool>& visitados) const {
    if (visitados[vertice]) return 0;
    visitados[vertice] = true;

    int tamanho_ilha = 1;
    for (auto [vizinho, peso] : adj[vertice]) {
        tamanho_ilha += dfs(vizinho, visitados);
    }

    return tamanho_ilha;
}

int Grafo::dfs_componente(int vertice, vector<int>& componente_atual, vector<bool>& visitados) const {
    if (visitados[vertice]) return 0;
    visitados[vertice] = true;

    componente_atual.push_back(vertice);

    int tamanho_ilha = 1;
    for (auto [vizinho, peso] : adj[vertice]) {
        int funcao = dfs_componente(vizinho, componente_atual, visitados);
        tamanho_ilha += funcao;
    }

    return tamanho_ilha;
}

void Grafo::dfs_ciclos_n_arestas(int vertice, int& qtd_vertices, int& qtd_arestas, vector<bool>& visitados) const {
    visitados[vertice] = true;

    qtd_vertices++;
    qtd_arestas += adj[vertice].size();

    for (auto [vizinho, peso] : adj[vertice]) {
        if (!visitados[vizinho]) {
            dfs_ciclos_n_arestas(vizinho, qtd_vertices, qtd_arestas, visitados);
        }
    }
}

bool Grafo::dfs_ciclos_percorrendo(int vertice, int pai, vector<bool>& visitados) const {
    visitados[vertice] = true;

    int cont_pai = 0;
    for (auto [vizinho, peso] : adj[vertice]) {
        if (vizinho == pai) cont_pai++;
        if (cont_pai > 1) return true;

        if (!visitados[vizinho]) {
            if (dfs_ciclos_percorrendo(vizinho, vertice, visitados)) {
                return true;
            }
        } else if (vizinho != pai) {
            return true;
        }
    }

    return false;
}

bool Grafo::dfs_bipartido(int vertice, int cor, vector<int>& coloracao, vector<bool>& visitados) const {
    visitados[vertice] = true;
    coloracao[vertice] = cor;

    int prox_cor = cor ^ 1;

    for (auto [vizinho, peso] : adj[vertice]) {
        if (!visitados[vizinho]) {
            if (!dfs_bipartido(vizinho, prox_cor, coloracao, visitados)) {
                return false;
            }
        } else {
            if (coloracao[vizinho] == coloracao[vertice]) {
                return false;
            }
        }
    }

    return true;
}

void Grafo::dfs_kosaraju_1(int vertice, stack<int>& ordem, vector<bool>& visitados) const {
    if (visitados[vertice]) return;
    visitados[vertice] = true;

    for (auto [vizinho, peso] : adj[vertice]) {
        dfs_kosaraju_1(vizinho, ordem, visitados);
    }

    ordem.push(vertice);
}

void Grafo::dfs_kosaraju_2(int vertice, vector<int>& componentes, int n_componentes, vector<bool>& visitados) const {
    if (visitados[vertice]) return;
    visitados[vertice] = true;

    componentes[vertice] = n_componentes;

    for (auto [vizinho, peso] : inv_adj[vertice]) {
        dfs_kosaraju_2(vizinho, componentes, n_componentes, visitados);
    }
}

void Grafo::bfs(int vertice, vector<int>& dist, vector<int>& pai) const {
    queue<int> fila;
    dist[vertice] = 0;
    fila.push(vertice);

    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        for (auto [vizinho, peso] : adj[atual]) {
            if (dist[vizinho] == -1) {
                dist[vizinho] = dist[atual] + 1;
                pai[vizinho] = atual;
                fila.push(vizinho);
            }
        }
    }
}

// =======================================================
// 3. CONSTRUTOR E INFORMAÇÕES BÁSICAS
// =======================================================
Grafo::Grafo(int vertices, string palavra, bool direcionado, bool tem_peso, bool permite_multiplas) {
    this->n_vertices = vertices;
    this->nome = palavra;
    this->direcionado = direcionado;
    this->tem_peso = tem_peso;
    this->permite_multiplas = permite_multiplas;

    adj.resize(vertices + 1);
    inv_adj.resize(vertices + 1);
}

const string& Grafo::get_nome() const { return nome; }

int Grafo::get_n_vertices() const { return n_vertices; }

bool Grafo::is_direcionado() const { return direcionado; }

bool Grafo::is_ponderado() const { return tem_peso; }

bool Grafo::is_multigrafo() const { return permite_multiplas; }

int Grafo::get_grau(int vertice) const {
    if (vertice < 1 || vertice > n_vertices) return -1;
    return adj[vertice].size();
}

int Grafo::get_peso(int u, int v) const {
    if (u < 1 || u > n_vertices || v < 1 || v > n_vertices) return INF;
    for (const auto& [vizinho, peso] : adj[u]) {
        if (vizinho == v) return peso;
    }
    return INF;
}

vector<int> Grafo::get_vertices_impares() const {
    vector<int> impares;
    for (int i = 1; i <= n_vertices; i++) {
        if (adj[i].size() % 2 != 0) {
            impares.push_back(i);
        }
    }
    return impares;
}

const vector<pair<int, int>>& Grafo::get_vizinhos(int vertice) const {
    return adj[vertice];
}

// =======================================================
// 4. MANIPULAÇÃO DA ESTRUTURA
// =======================================================
bool Grafo::adicionar_aresta(int u, int v, int peso) {
    if (u < 1 || u > n_vertices || v < 1 || v > n_vertices) {
        return false;
    }

    if (u == v) {
        return false;
    }

    if (!this->permite_multiplas) {
        auto it = find_if(adj[u].begin(), adj[u].end(), [v](const pair<int, int>& p) { return p.first == v; });
        if (it != adj[u].end()) {
            return false;
        }
    }

    if (peso != 1) {
        this->tem_peso = true;
    }

    adj[u].push_back({v, peso});
    inv_adj[v].push_back({u, peso});

    if (!this->direcionado) {
        adj[v].push_back({u, peso});
        inv_adj[u].push_back({v, peso});
    }

    return true;
}

bool Grafo::excluir_aresta(int u, int v, int peso_alvo) {
    if (u < 1 || u > n_vertices || v < 1 || v > n_vertices) {
        return false;
    }

    if (u == v) {
        return false;
    }

    auto it = find_if(adj[u].begin(), adj[u].end(), [v, peso_alvo](const pair<int, int>& p) {
        return p.first == v && (peso_alvo == -1 || p.second == peso_alvo);
    });

    if (it == adj[u].end()) {
        return false;
    }

    int peso_excluido = it->second;
    adj[u].erase(it);

    auto inv_it = find_if(inv_adj[v].begin(), inv_adj[v].end(), [u, peso_excluido](const pair<int, int>& p) {
        return p.first == u && p.second == peso_excluido;
    });
    if (inv_it != inv_adj[v].end()) {
        inv_adj[v].erase(inv_it);
    }

    if (!this->direcionado) {
        auto itt = find_if(adj[v].begin(), adj[v].end(), [u, peso_excluido](const pair<int, int>& p) {
            return p.first == u && p.second == peso_excluido;
        });
        if (itt != adj[v].end()) {
            adj[v].erase(itt);
        }

        auto itt_inv = find_if(inv_adj[u].begin(), inv_adj[u].end(), [v, peso_excluido](const pair<int, int>& p) {
            return p.first == v && p.second == peso_excluido;
        });
        if (itt_inv != inv_adj[u].end()) {
            inv_adj[u].erase(itt_inv);
        }
    }

    return true;
}

void Grafo::gerar_arestas_aleatorias(int m) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> vert_dist(1, n_vertices);
    uniform_int_distribution<int> weight_dist(1, 10);

    for (int i = 1; i < n_vertices && m > 0; i++) {
        int peso = weight_dist(gen);
        if (adicionar_aresta(i, i + 1, peso)) {
            m--;
        }
    }

    int tentativas = 0;
    while (m > 0 && tentativas < 10000) {
        tentativas++;
        int u = vert_dist(gen);
        int v = vert_dist(gen);
        if (u != v) {
            int peso = weight_dist(gen);
            if (adicionar_aresta(u, v, peso)) {
                m--;
            }
        }
    }
}

// =======================================================
// 5. CAMINHOS E DISTÂNCIAS
// =======================================================
void Grafo::dijkstra(int origem, vector<int>& dist, vector<int>& pai) const {
    dist.assign(n_vertices + 1, INF);
    pai.assign(n_vertices + 1, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[origem] = 0;
    pq.push({0, origem});

    while (!pq.empty()) {
        auto [d, atual] = pq.top();
        pq.pop();

        if (d > dist[atual]) continue;

        for (auto [vizinho, peso] : adj[atual]) {
            if (dist[vizinho] > dist[atual] + peso) {
                dist[vizinho] = dist[atual] + peso;
                pai[vizinho] = atual;
                pq.push({dist[vizinho], vizinho});
            }
        }
    }
}

vector<int> Grafo::obter_distancias(int origem) const {
    vector<int> dist(n_vertices + 1, -1);
    vector<int> pai(n_vertices + 1, -1);

    if (origem >= 1 && origem <= n_vertices) {
        bfs(origem, dist, pai);
    }
    return dist;
}

vector<int> Grafo::obter_caminho(int origem, int destino) const {
    vector<int> caminho;
    if (origem < 1 || origem > n_vertices || destino < 1 || destino > n_vertices) {
        return caminho;
    }

    if (origem == destino) {
        caminho.push_back(origem);
        return caminho;
    }

    vector<int> dist(n_vertices + 1, -1);
    vector<int> pai(n_vertices + 1, -1);

    bfs(origem, dist, pai);

    if (dist[destino] == -1) {
        return caminho;
    }

    int temp = destino;
    while (temp != -1) {
        caminho.push_back(temp);
        temp = pai[temp];
    }
    reverse(caminho.begin(), caminho.end());
    return caminho;
}

// =======================================================
// 6. ANÁLISE DE PROPRIEDADES DO GRAFO
// =======================================================
vector<vector<int>> Grafo::obter_componentes() const {
    vector<bool> visitados(n_vertices + 1, false);
    vector<vector<int>> lista_de_componentes;
    vector<int> componente_atual;

    for (int i = 1; i <= n_vertices; i++) {
        if (!visitados[i]) {
            dfs_componente(i, componente_atual, visitados);
            sort(componente_atual.begin(), componente_atual.end());
            lista_de_componentes.push_back(componente_atual);
            componente_atual.clear();
        }
    }

    return lista_de_componentes;
}

bool Grafo::tem_ciclos_percorrendo() const {
    vector<bool> visitados(n_vertices + 1, false);
    for (int i = 1; i <= n_vertices; i++) {
        if (!visitados[i]) {
            if (dfs_ciclos_percorrendo(i, -1, visitados)) {
                return true;
            }
        }
    }
    return false;
}

bool Grafo::tem_ciclos_n_arestas() const {
    vector<bool> visitados(n_vertices + 1, false);
    for (int i = 1; i <= n_vertices; i++) {
        if (!visitados[i]) {
            int qtd_vertices = 0;
            int qtd_arestas = 0;
            dfs_ciclos_n_arestas(i, qtd_vertices, qtd_arestas, visitados);
            qtd_arestas /= 2;

            if (qtd_arestas >= qtd_vertices) {
                return true;
            }
        }
    }
    return false;
}

vector<int> Grafo::kosaraju() const {
    vector<bool> visitados(n_vertices + 1, false);
    stack<int> ordem;

    for (int i = 1; i <= n_vertices; i++) {
        if (!visitados[i]) {
            dfs_kosaraju_1(i, ordem, visitados);
        }
    }

    fill(visitados.begin(), visitados.end(), false);
    int n_componentes = 1;
    vector<int> componentes(n_vertices + 1);

    while (!ordem.empty()) {
        int atual = ordem.top();
        ordem.pop();

        if (!visitados[atual]) {
            dfs_kosaraju_2(atual, componentes, n_componentes++, visitados);
        }
    }

    return componentes;
}

bool Grafo::verifica_bipartido() const {
    vector<bool> visitados(n_vertices + 1, false);
    int cor = 0;
    vector<int> coloracao(n_vertices + 1, -1);

    for (int i = 1; i <= n_vertices; i++) {
        if (!visitados[i]) {
            if (!dfs_bipartido(i, cor, coloracao, visitados)) {
                return false;
            }
        }
    }

    return true;
}

// =======================================================
// 7. EULERIANO E PROBLEMA DO CARTEIRO CHINÊS
// =======================================================
vector<int> Grafo::extrair_circuito_euleriano(int inicio) const {
    vector<int> circuito;
    if (inicio < 1 || inicio > n_vertices) return circuito;

    auto adj_copia = adj;
    stack<int> pilha;
    pilha.push(inicio);

    while (!pilha.empty()) {
        int u = pilha.top();
        if (!adj_copia[u].empty()) {
            int v = adj_copia[u].back().first;
            int peso = adj_copia[u].back().second;

            for (auto it = adj_copia[u].begin(); it != adj_copia[u].end(); ++it) {
                if (it->first == v && it->second == peso) {
                    adj_copia[u].erase(it);
                    break;
                }
            }
            if (!direcionado) {
                for (auto it = adj_copia[v].begin(); it != adj_copia[v].end(); ++it) {
                    if (it->first == u && it->second == peso) {
                        adj_copia[v].erase(it);
                        break;
                    }
                }
            }
            pilha.push(v);
        } else {
            circuito.push_back(u);
            pilha.pop();
        }
    }
    reverse(circuito.begin(), circuito.end());
    return circuito;
}

static void solve_enum(size_t index, int custo, const vector<int>& impares,
                       const vector<vector<int>>& matriz_dist,
                       int& bitmask, int& melhor_custo, vector<pair<int, int>>& melhor_pareamento,
                       vector<pair<int, int>>& pareamento_atual) {
    size_t n = impares.size();
    if (custo >= melhor_custo) return;

    while (index < n && (bitmask & (1 << index))) {
        index++;
    }

    if (index == n) {
        melhor_custo = custo;
        melhor_pareamento = pareamento_atual;
        return;
    }

    bitmask |= (1 << index);

    for (size_t i = index + 1; i < n; i++) {
        if (!(bitmask & (1 << i))) {
            bitmask |= (1 << i);
            pareamento_atual.push_back({impares[index], impares[i]});

            solve_enum(index + 1, custo + matriz_dist[index][i], impares, matriz_dist, bitmask, melhor_custo, melhor_pareamento, pareamento_atual);

            pareamento_atual.pop_back();
            bitmask &= (~(1 << i));
        }
    }

    bitmask &= (~(1 << index));
}

ResultadoCarteiroChines Grafo::resolver_carteiro_chines(ModoCarteiroChines modo) const {
    auto inicio_tempo = chrono::high_resolution_clock::now();
    ResultadoCarteiroChines res;
    res.custo_total = 0;
    res.custo_adicional = 0;

    Grafo g_duplicado = *this;

    for (int u = 1; u <= n_vertices; u++) {
        for (auto [v, peso] : adj[u]) {
            if (u <= v || direcionado) {
                res.custo_total += peso;
            }
        }
    }

    vector<int> impares = g_duplicado.get_vertices_impares();

    if (!impares.empty()) {
        vector<pair<int, int>> pareamento;

        if (modo == ModoCarteiroChines::EXATO_ENUMERACAO && impares.size() > 16) {
            cout << "  [!] AVISO: Grafo possui " << impares.size() << " vértices ímpares (>16)." << endl;
            cout << "  [!] Alternando para heurística Gulosa para evitar congelamento da CPU." << endl;
            modo = ModoCarteiroChines::GULOSO;
        }

        if (modo == ModoCarteiroChines::EXATO_ENUMERACAO) {
            size_t k = impares.size();
            vector<vector<int>> matriz_dist(k, vector<int>(k, 0));
            vector<int> dist(n_vertices + 1);
            vector<int> pai(n_vertices + 1);

            for (size_t i = 0; i < k; i++) {
                g_duplicado.dijkstra(impares[i], dist, pai);
                for (size_t j = 0; j < k; j++) {
                    matriz_dist[i][j] = dist[impares[j]];
                }
            }

            int bitmask = 0;
            int melhor_custo = INF;
            vector<pair<int, int>> pareamento_atual;
            solve_enum(0, 0, impares, matriz_dist, bitmask, melhor_custo, pareamento, pareamento_atual);
        }
        else if (modo == ModoCarteiroChines::GULOSO) {
            size_t k = impares.size();
            vector<pair<int, pair<int, int>>> arestas_virtuais;
            vector<int> dist(n_vertices + 1);
            vector<int> pai(n_vertices + 1);

            for (size_t i = 0; i < k; i++) {
                g_duplicado.dijkstra(impares[i], dist, pai);
                for (size_t j = i + 1; j < k; j++) {
                    arestas_virtuais.push_back({dist[impares[j]], {impares[i], impares[j]}});
                }
            }
            sort(arestas_virtuais.begin(), arestas_virtuais.end());

            vector<bool> pareados(n_vertices + 1, false);
            for (auto& av : arestas_virtuais) {
                int u = av.second.first;
                int v = av.second.second;
                if (!pareados[u] && !pareados[v]) {
                    pareados[u] = true;
                    pareados[v] = true;
                    pareamento.push_back({u, v});
                }
            }
        }
        else if (modo == ModoCarteiroChines::VIZINHO_MAIS_PROXIMO) {
            vector<bool> pareados(n_vertices + 1, false);
            vector<int> dist(n_vertices + 1);
            vector<int> pai(n_vertices + 1);

            for (int u : impares) {
                if (pareados[u]) continue;
                g_duplicado.dijkstra(u, dist, pai);

                int melhor_v = -1;
                int min_dist = INF;
                for (int v : impares) {
                    if (u != v && !pareados[v] && dist[v] < min_dist) {
                        min_dist = dist[v];
                        melhor_v = v;
                    }
                }
                if (melhor_v != -1) {
                    pareados[u] = true;
                    pareados[melhor_v] = true;
                    pareamento.push_back({u, melhor_v});
                }
            }
        }

        vector<int> dist(n_vertices + 1);
        vector<int> pai(n_vertices + 1);

        for (auto [u, v] : pareamento) {
            g_duplicado.dijkstra(u, dist, pai);
            int atual = v;
            while (atual != u && atual != -1) {
                int anterior = pai[atual];
                if (anterior == -1) break;
                int peso_real = g_duplicado.get_peso(anterior, atual);
                if (peso_real == INF) peso_real = 1;

                res.custo_adicional += peso_real;
                g_duplicado.adicionar_aresta(anterior, atual, peso_real);
                atual = anterior;
            }
        }
    }

    res.custo_total += res.custo_adicional;
    res.circuito = g_duplicado.extrair_circuito_euleriano(1);

    auto fim_tempo = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracao = fim_tempo - inicio_tempo;
    res.tempo_ms = duracao.count();

    return res;
}

// =======================================================
// 8. ENTRADA E SAÍDA DE DADOS (I/O)
// =======================================================
void Grafo::salvar_grafo(ofstream& arquivo) const {
    arquivo << nome << "\n";
    arquivo << n_vertices << "\n";

    int total_arestas = 0;
    vector<pair<pair<int, int>, int>> arestas;
    for (int u = 1; u <= n_vertices; u++) {
        for (auto [v, peso] : adj[u]) {
            if (u <= v) {
                total_arestas++;
                arestas.push_back({{u, v}, peso});
            }
        }
    }

    arquivo << total_arestas << "\n";
    for (auto aresta : arestas) {
        arquivo << aresta.first.first << " " << aresta.first.second << " " << aresta.second << "\n";
    }
}
