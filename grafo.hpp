#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <algorithm>
#include <fstream>

using namespace std;

class Grafo{
    private:

    int n_vertices;
    string nome;
    vector<vector<int>> adj;
    vector<bool> visitados;

    int dfs(int vertice){
        if(visitados[vertice]) return 0;
        visitados[vertice] = true;

        int tamanho_ilha = 1;
        for(int vizinho : adj[vertice]){
            tamanho_ilha += dfs(vizinho);
        }

        return tamanho_ilha;
    }

    int dfs_componente(int vertice, vector<int>& componente_atual){
        if(visitados[vertice]) return 0;
        visitados[vertice] = true;

        componente_atual.push_back(vertice);

        int tamanho_ilha = 1;
        for(int vizinho : adj[vertice]){
            int funcao = dfs_componente(vizinho,componente_atual);
            tamanho_ilha += funcao;
        }

        return tamanho_ilha;
    }

    void dfs_ciclos_n_arestas(int vertice, int& qtd_vertices, int& qtd_arestas){
        visitados[vertice] = true;

        qtd_vertices++;
        qtd_arestas+=adj[vertice].size();

        for(int vizinho:adj[vertice]){
            if(!visitados[vizinho]){
                dfs_ciclos_n_arestas(vizinho, qtd_vertices, qtd_arestas);
            }
        }
    }

    bool dfs_ciclos_percorrendo(int vertice, int pai){
        visitados[vertice] = true;

        for(auto vizinho:adj[vertice]){
            if(!visitados[vizinho]){
                if(dfs_ciclos_percorrendo(vizinho, vertice)){
                    return true;
                }
            }else if(vizinho!=pai){
                return true;
            }
        }

        return false;
    }

    bool dfs_bipartido(int vertice, int cor, vector<int>& coloracao){
        visitados[vertice] = true;
        coloracao[vertice] = cor;
        
        int prox_cor=cor^1;

        for(auto vizinho:adj[vertice]){
            if(!visitados[vizinho]){
                if(!dfs_bipartido(vizinho, prox_cor, coloracao)){
                    return false;
                }
            }else{
                if(coloracao[vizinho]==coloracao[vertice]){
                    return false;
                }
            }
        }

        return true;
    }

    void bfs(int vertice, vector<int>& dist, vector<int>& pai){
        queue<int> fila;
        dist[vertice]=0;
        fila.push(vertice);

        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();

            for(auto vizinho:adj[atual]){
                if(dist[vizinho]==-1){
                    dist[vizinho]=dist[atual]+1;
                    pai[vizinho]=atual;
                    fila.push(vizinho);
                }
            }
        }
    }

    public:

    Grafo(int vertices, string palavra){
        this->n_vertices = vertices;
        this->nome = palavra;
        adj.resize(vertices+1);
        visitados.assign(vertices+1, false);
    }

    void imprime_nome(){
        cout<<nome;
    }

    void imprime_grafo(){
        cout<<"Nome: "<<nome<<" | Vértices: "<<n_vertices<<endl;
        imprimir_conexoes();
    }

    void imprimir_conexoes(){
        cout<<endl<<"---LISTA DE ADJACENCIA---"<<endl;
        for(int i=1; i<=n_vertices; i++){
            cout<<"Vertice "<<i<<" -> ";
            if(adj[i].size()==0){
                cout<< "VAZIO";
            }else{
                for(int vizinho : adj[i]){
                    cout<<"["<<vizinho<<"] ";
                }
            }
            cout<<endl;
        }
    }

    void imprimir_componentes(){
        limpar_visitados();
        int numero_componentes = 0;
        vector<int> tamanhos;
        vector<vector<int>> lista_de_componentes;
        vector<int> componente_atual;

        for(int i=1; i<=n_vertices; i++){
            if(!visitados[i]){
                numero_componentes++;
                tamanhos.push_back(dfs_componente(i,componente_atual));
                sort(componente_atual.begin(), componente_atual.end());
                lista_de_componentes.push_back(componente_atual);
                componente_atual.clear();
            }
        }

        cout<< "Numero de componentes: "<<numero_componentes<<endl<<endl;

        if(numero_componentes>1){
            cout<< "---TAMANHO DE CADA ILHA---"<<endl;
            for(size_t i = 0; i<numero_componentes; i++){
                cout<< "  -> Componente "<<i+1<<": "<<tamanhos[i]<<" vertices"<<endl;
                cout<<"    -> Vertices da componente: ";
                int tam = lista_de_componentes[i].size();
                for(int j=0; j<tam; j++){
                    cout<<lista_de_componentes[i][j];
                    if(j<tam-1){
                        cout<<", ";
                    }
                }
                cout<<endl;
            }
        }
    }

    bool adicionar_aresta(int u, int v, bool direcionado = false){
        if(u < 1 || u > n_vertices || v < 1 || v > n_vertices){
            cout << "  [!] ERRO: Vertices invalidos! O grafo so vai de 1 a " << n_vertices << "." << endl;
            return false;
        }

        if(u == v){
            cout << "  [!] ERRO: Um vertice nao pode criar uma aresta com ele mesmo!" << endl;
            return false;
        }

        auto it = find(adj[u].begin(), adj[u].end(), v);
        if(it != adj[u].end()){
            cout<<"  [!] ERRO: Essa aresta já existe!"<<endl;
            return false;
        }

        adj[u].push_back(v);
        if(!direcionado){
            adj[v].push_back(u);
        }

        return true;
    }

    bool excluir_aresta(int u, int v, bool direcionado = false){
        if(u < 1 || u > n_vertices || v < 1 || v > n_vertices){
            cout << "  [!] ERRO: Vertices invalidos! O grafo so vai de 1 a " << n_vertices << "." << endl;
            return false;
        }

        if(u == v){
            cout << "  [!] ERRO: Um vertice nao possui uma aresta com ele mesmo!" << endl;
            return false;
        }

        auto it = find(adj[u].begin(), adj[u].end(), v);

        if(it == adj[u].end()){
            cout<<"  [!] ERRO: Essa aresta não existe!"<<endl;
            return false;
        }

        adj[u].erase(it);

        if(!direcionado){
            auto itt = find(adj[v].begin(), adj[v].end(), u);
            if(itt != adj[v].end()){
                adj[v].erase(itt);
            }
        }

        return true;
    }

    void limpar_visitados(){
        fill(visitados.begin(), visitados.end(), false);
    }

    void mostrar_tamanhos(int origem){
        if(origem < 1 || origem > n_vertices){
            cout << "Vertice de origem invalido!" << endl;
            return;
        }

        limpar_visitados();
        vector<int> dist(n_vertices+1, -1);
        vector<int> pai(n_vertices+1, -1);
        
        bfs(origem, dist, pai);

        for(int i=1; i<=n_vertices; i++){ 
            if(i == origem) continue;

            if(dist[i] == -1){
                cout<<"  -> Vértice "<<i<<": SEM CONEXÃO"<<endl;
            }else{
                cout<<"  -> Vértice "<<i<<": "<<dist[i]<<" arestas"<<endl;
            }
        }
    }

    void mostrar_caminho(int origem, int destino){
        if(origem < 1 || origem > n_vertices){
            cout << "Vertice de origem invalido!" << endl;
            return;
        }

        if(destino < 1 || destino > n_vertices){
            cout << "Vertice de destino invalido!" << endl;
            return;
        }

        if(origem == destino){
            cout<< "Vértice de origem igual ao vértice de destino"<<endl;
            cout<< "Caminho: "<<origem<<endl;
            return;
        }

        limpar_visitados();
        vector<int> dist(n_vertices+1, -1);
        vector<int> pai(n_vertices+1, -1);

        bfs(origem, dist, pai);

        if(dist[destino]==-1){
            cout<<"Impossível chegar no vértice "<<destino<<" a partir do vertice "<<origem<<endl;
            return;
        }

        vector<int> caminho;
        int temp=destino;
        while(temp!=-1){ 
            caminho.push_back(temp);
            temp=pai[temp];
        }

        cout<<"---CAMINHO DO VERTICE: "<<origem<<" AO VERTICE: "<<destino<<"---"<<endl;
        int tam=caminho.size()-1;
        cout<<origem<<" -> ";
        for(int i=0; i<tam; i++){
            cout<<caminho[tam-i-1];
            if(i<tam-1){
                cout<<" -> ";
            }
        }
        cout<<endl;
    }

    bool encontra_ciclos_percorrendo(){
        limpar_visitados();
        for(int i=1; i<=n_vertices; i++){
            if(!visitados[i]){
                if(dfs_ciclos_percorrendo(i, -1)){
                    cout<<"O grafo possui pelo menos 1 ciclo"<<endl;
                    return true;
                }
            }
        }

        cout<<"O grafo não possui ciclos"<<endl;
        return false;
    }

    bool encontra_ciclos_n_arestas(){
        limpar_visitados();
        for(int i=1; i<=n_vertices; i++){
            if(!visitados[i]){
                int qtd_vertices=0;
                int qtd_arestas=0;
                dfs_ciclos_n_arestas(i, qtd_vertices, qtd_arestas);
                qtd_arestas/=2;

                if(qtd_arestas >= qtd_vertices){
                    cout<<"O grafo possui pelo menos 1 ciclo"<<endl;
                    return true;
                }
            }
        }

        cout<<"O grafo não possui ciclos"<<endl;
        return false;
    }

    bool verifica_bipartido(){
        limpar_visitados();
        int cor=0;
        vector<int> coloracao(n_vertices+1, -1);

        for(int i=1; i<=n_vertices; i++){
            if(!visitados[i]){
                if(!dfs_bipartido(i, cor, coloracao)){
                    cout<<"O grafo não é bipartido"<<endl;
                    return false;
                }
            }
        }

        cout<<"O grafo é bipartido"<<endl;

        return true;
    }

    void salvar_grafo(ofstream& arquivo){
        arquivo << nome << "\n";
        arquivo << n_vertices << "\n";

        int total_arestas = 0;
        vector<pair<int, int>> arestas;
        for(int u = 1; u <= n_vertices; u++){
            for(int v : adj[u]){
                if(u <= v){
                    total_arestas++;
                    arestas.push_back({u, v});
                }
            }
        }

        arquivo << total_arestas << "\n";
        for(auto aresta : arestas){
            arquivo << aresta.first << " " << aresta.second << "\n";
        }
    }
};