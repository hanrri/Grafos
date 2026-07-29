#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include "../include/grafo.hpp"

using namespace std;

#define Lbuffer cin.ignore(numeric_limits<streamsize>::max(), '\n')

void limpar_tela() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[1;1H" << std::flush;
#endif
}

void pausar() {
    std::cout << "\n[Pressione ENTER para continuar...]";
    if (cin.fail()) {
        cin.clear();
    }
    string dummy;
    getline(cin, dummy);
}

int ler_numero() {
    int numero;
    while (true) {
        if (cin.eof()) {
            cout << "\nEntrada encerrada." << endl;
            exit(0);
        }
        cin >> numero;
        
        if (!cin.fail()) {
            string resto;
            getline(cin, resto);
            return numero;
        }
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "[!] ERRO: Entrada invalida! Por favor, digite APENAS numeros: ";
    }
}

void remover_espacos_finais(string &str) {
    while (!str.empty() && isspace(str.back())) {
        str.pop_back();
    }
}

int selecionar_grafo(const vector<Grafo>& grafos) {
    if (grafos.empty()) {
        cout << "Nenhum grafo criado ainda! ;-;" << endl;
        pausar();
        return -1;
    }

    cout << "Selecione o NÚMERO do grafo:" << endl;
    cout << "0. Voltar / Cancelar" << endl;
    for (size_t i = 0; i < grafos.size(); i++) {
        cout << i + 1 << ". " << grafos[i].get_nome() << " (" << grafos[i].get_n_vertices() << " vértices)" << endl;
    }
    cout << "R.: ";
    
    int escolha = ler_numero();
    if (escolha == 0) {
        cout << "Operação cancelada." << endl;
        return -1;
    }

    if (escolha < 1 || escolha > (int)grafos.size()) {
        cout << "Opção de grafo inválida! ;-;" << endl;
        pausar();
        return -1;
    }

    return escolha - 1;
}

void menu_gerenciar_grafos(vector<Grafo>& grafos) {
    int sub1 = -1;
    while (sub1 != 0) {
        limpar_tela();
        cout << "--- GERENCIAR E VISUALIZAR GRAFOS ---" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "1. Criar novo grafo" << endl;
        cout << "2. Listar grafos" << endl;
        cout << "3. Visualizar conexões (Lista de Adjacência) de um grafo" << endl;
        cout << "4. Adicionar arestas em um grafo" << endl;
        cout << "5. Remover arestas em um grafo" << endl;
        cout << "6. Gerar arestas aleatórias para um grafo" << endl;
        cout << "7. Excluir um grafo da memória" << endl;
        cout << "R.: ";

        sub1 = ler_numero();

        switch (sub1) {
            case 0:
                break;

            case 1: {
                cout << "Dê um nome ao seu novo grafo" << endl;
                cout << "(Ou digite '0' para cancelar)" << endl << "R.: ";

                string nome;
                getline(cin, nome);
                remover_espacos_finais(nome);

                if (nome == "0") {
                    cout << "Criação de grafo cancelada." << endl;
                    pausar();
                    break;
                }

                bool nome_repetido = false;
                for (size_t i = 0; i < grafos.size(); i++) {
                    if (grafos[i].get_nome() == nome) {
                        nome_repetido = true;
                        break;
                    }
                }

                if (nome_repetido) {
                    cout << "  [!] ERRO: Já existe um grafo com o nome '" << nome << "'!" << endl;
                    pausar();
                    break;
                }

                cout << "Seu grafo tem quantos vértices?" << endl << "R.: ";
                int qtd_vertices = ler_numero();

                Grafo grafo(qtd_vertices, nome);
                grafos.push_back(grafo);
                cout << "Grafo '" << nome << "' criado com sucesso! :D" << endl;
                pausar();
                break;
            }

            case 2: {
                if (grafos.empty()) {
                    cout << "Nenhum grafo criado ainda! ;-;" << endl;
                } else {
                    cout << "--- LISTA DE GRAFOS ---" << endl;
                    for (size_t i = 0; i < grafos.size(); i++) {
                        cout << i + 1 << ". " << grafos[i].get_nome() << " (" << grafos[i].get_n_vertices() << " vértices)" << endl;
                    }
                }
                pausar();
                break;
            }

            case 3: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    const auto& g = grafos[id];
                    cout << endl << "--- LISTA DE ADJACÊNCIA (" << g.get_nome() << ") ---" << endl;
                    for (int i = 1; i <= g.get_n_vertices(); i++) {
                        cout << "Vértice " << i << " -> ";
                        const auto& vizinhos = g.get_vizinhos(i);
                        if (vizinhos.empty()) {
                            cout << "VAZIO";
                        } else {
                            for (auto [vizinho, peso] : vizinhos) {
                                cout << "[" << vizinho << "(" << peso << ")] ";
                            }
                        }
                        cout << endl;
                    }
                    pausar();
                }
                break;
            }

            case 4: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    cout << "Deseja adicionar quantas arestas?" << endl << "R.: ";
                    int n = ler_numero();

                    while (n--) {
                        cout << "Digite os dois vértices (origem destino): ";
                        int a = ler_numero();
                        int b = ler_numero();

                        if (grafos[id].adicionar_aresta(a, b)) {
                            cout << "Aresta adicionada no grafo '" << grafos[id].get_nome() << "'!" << endl;
                        }
                    }
                    pausar();
                }
                break;
            }

            case 5: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    cout << "Deseja remover quantas arestas?" << endl << "R.: ";
                    int n = ler_numero();

                    while (n--) {
                        cout << "Digite os dois vértices da aresta a remover: ";
                        int a = ler_numero();
                        int b = ler_numero();

                        if (grafos[id].excluir_aresta(a, b)) {
                            cout << "Aresta removida no grafo '" << grafos[id].get_nome() << "'!" << endl;
                        }
                    }
                    pausar();
                }
                break;
            }

            case 6: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    cout << "Quantas arestas deseja gerar aleatoriamente?" << endl << "R.: ";
                    int m = ler_numero();
                    grafos[id].gerar_arestas_aleatorias(m);
                    cout << "Arestas aleatórias geradas com sucesso!" << endl;
                    pausar();
                }
                break;
            }

            case 7: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    string nome = grafos[id].get_nome();
                    grafos.erase(grafos.begin() + id);
                    cout << "Grafo '" << nome << "' excluído da memória com sucesso!" << endl;
                    pausar();
                }
                break;
            }

            default:
                cout << "Selecione uma opção válida ou escolha 0 para voltar." << endl;
                pausar();
                break;
        }
    }
}

void menu_buscas_caminhos(const vector<Grafo>& grafos) {
    int sub2 = -1;
    while (sub2 != 0) {
        limpar_tela();
        cout << "--- BUSCAS E CAMINHOS MÍNIMOS ---" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "1. Distâncias a partir de um vértice (BFS)" << endl;
        cout << "2. Caminho mais curto em número de arestas (BFS)" << endl;
        cout << "3. Caminho mínimo com pesos (Algoritmo de Dijkstra)" << endl;
        cout << "R.: ";

        sub2 = ler_numero();

        switch (sub2) {
            case 0:
                break;

            case 1: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    cout << "Digite o vértice de origem: ";
                    int orig = ler_numero();
                    if (orig < 1 || orig > grafos[id].get_n_vertices()) {
                        cout << "Vértice de origem inválido!" << endl;
                    } else {
                        vector<int> dist = grafos[id].obter_distancias(orig);
                        cout << endl << "--- DISTÂNCIAS A PARTIR DO VÉRTICE " << orig << " (BFS) ---" << endl;
                        for (int i = 1; i <= grafos[id].get_n_vertices(); i++) {
                            if (i == orig) continue;
                            if (dist[i] == -1) {
                                cout << "  -> Vértice " << i << ": SEM CONEXÃO" << endl;
                            } else {
                                cout << "  -> Vértice " << i << ": " << dist[i] << " aresta(s)" << endl;
                            }
                        }
                    }
                    pausar();
                }
                break;
            }

            case 2: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    int n_v = grafos[id].get_n_vertices();
                    cout << "Digite o vértice de ORIGEM (1 a " << n_v << ", ou 0 para cancelar): ";
                    int a = ler_numero();
                    if (a == 0) {
                        cout << "Operação cancelada." << endl;
                        pausar();
                        break;
                    }

                    cout << "Digite o vértice de DESTINO (1 a " << n_v << ", ou 0 para cancelar): ";
                    int b = ler_numero();
                    if (b == 0) {
                        cout << "Operação cancelada." << endl;
                        pausar();
                        break;
                    }

                    if (a < 1 || a > n_v) {
                        cout << "Vértice de origem inválido!" << endl;
                    } else if (b < 1 || b > n_v) {
                        cout << "Vértice de destino inválido!" << endl;
                    } else if (a == b) {
                        cout << "Vértice de origem igual ao vértice de destino" << endl;
                        cout << "Caminho: " << a << endl;
                    } else {
                        vector<int> caminho = grafos[id].obter_caminho(a, b);
                        if (caminho.empty()) {
                            cout << "Impossível chegar no vértice " << b << " a partir do vértice " << a << endl;
                        } else {
                            cout << endl << "--- CAMINHO MAIS CURTO EM ARESTAS (" << a << " -> " << b << ") ---" << endl;
                            cout << "Total de arestas: " << caminho.size() - 1 << endl;
                            cout << "Caminho: ";
                            for (size_t i = 0; i < caminho.size(); i++) {
                                cout << caminho[i] << (i + 1 < caminho.size() ? " -> " : "");
                            }
                            cout << endl;
                        }
                    }
                    pausar();
                }
                break;
            }

            case 3: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    int n_v = grafos[id].get_n_vertices();
                    cout << "Digite o vértice de ORIGEM (1 a " << n_v << ", ou 0 para cancelar): ";
                    int orig = ler_numero();
                    if (orig == 0) {
                        cout << "Operação cancelada." << endl;
                        pausar();
                        break;
                    }

                    cout << "Digite o vértice de DESTINO (1 a " << n_v << ", ou 0 para cancelar): ";
                    int dest = ler_numero();
                    if (dest == 0) {
                        cout << "Operação cancelada." << endl;
                        pausar();
                        break;
                    }

                    if (orig < 1 || orig > n_v || dest < 1 || dest > n_v) {
                        cout << "Vértices inválidos!" << endl;
                    } else if (orig == dest) {
                        cout << "Vértice de origem igual ao vértice de destino" << endl;
                        cout << "Custo: 0 | Caminho: " << orig << endl;
                    } else {
                        vector<int> dist;
                        vector<int> pai;
                        grafos[id].dijkstra(orig, dist, pai);

                        if (dist[dest] == INF) {
                            cout << "Impossível chegar no vértice " << dest << " a partir do vértice " << orig << endl;
                        } else {
                            vector<int> caminho;
                            int temp = dest;
                            while (temp != -1) {
                                caminho.push_back(temp);
                                temp = pai[temp];
                            }
                            reverse(caminho.begin(), caminho.end());

                            cout << endl << "--- CAMINHO MÍNIMO PONDERADO (DIJKSTRA) ---" << endl;
                            cout << "Custo total do caminho: " << dist[dest] << endl;
                            cout << "Caminho: ";
                            for (size_t i = 0; i < caminho.size(); i++) {
                                cout << caminho[i] << (i + 1 < caminho.size() ? " -> " : "");
                            }
                            cout << endl;
                        }
                    }
                    pausar();
                }
                break;
            }

            default:
                cout << "Selecione uma opção válida ou escolha 0 para voltar." << endl;
                pausar();
                break;
        }
    }
}

void menu_propriedades_avancadas(const vector<Grafo>& grafos) {
    int sub3 = -1;
    while (sub3 != 0) {
        limpar_tela();
        cout << "--- PROPRIEDADES E ALGORITMOS AVANÇADOS ---" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "1. Componentes Conexas (Ilhas)" << endl;
        cout << "2. Componentes Fortemente Conexas (Algoritmo de Kosaraju)" << endl;
        cout << "3. Detecção de Ciclos" << endl;
        cout << "4. Verificação de Grafo Bipartido" << endl;
        cout << "5. Resolver Problema do Carteiro Chinês" << endl;
        cout << "R.: ";

        sub3 = ler_numero();

        switch (sub3) {
            case 0:
                break;

            case 1: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    auto comp = grafos[id].obter_componentes();
                    cout << endl << "Número de componentes conexas: " << comp.size() << endl << endl;

                    if (comp.size() > 1) {
                        cout << "--- TAMANHO DE CADA ILHA ---" << endl;
                        for (size_t i = 0; i < comp.size(); i++) {
                            cout << "  -> Componente " << i + 1 << ": " << comp[i].size() << " vértices" << endl;
                            cout << "    -> Vértices: ";
                            for (size_t j = 0; j < comp[i].size(); j++) {
                                cout << comp[i][j] << (j + 1 < comp[i].size() ? ", " : "");
                            }
                            cout << endl;
                        }
                    }
                    pausar();
                }
                break;
            }

            case 2: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    vector<int> scc = grafos[id].kosaraju();
                    int max_comp = 0;
                    for (int c : scc) max_comp = max(max_comp, c);

                    cout << endl << "--- COMPONENTES FORTEMENTE CONEXAS (KOSARAJU) ---" << endl;
                    cout << "Total de componentes fortemente conexas: " << max_comp << endl;
                    for (int c = 1; c <= max_comp; c++) {
                        cout << "  -> Componente " << c << ": ";
                        bool primeiro = true;
                        for (int i = 1; i <= grafos[id].get_n_vertices(); i++) {
                            if (scc[i] == c) {
                                if (!primeiro) cout << ", ";
                                cout << i;
                                primeiro = false;
                            }
                        }
                        cout << endl;
                    }
                    pausar();
                }
                break;
            }

            case 3: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    if (grafos[id].tem_ciclos_n_arestas()) {
                        cout << "O grafo possui pelo menos 1 ciclo" << endl;
                    } else {
                        cout << "O grafo não possui ciclos" << endl;
                    }
                    pausar();
                }
                break;
            }

            case 4: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    if (grafos[id].verifica_bipartido()) {
                        cout << "O grafo é bipartido" << endl;
                    } else {
                        cout << "O grafo não é bipartido" << endl;
                    }
                    pausar();
                }
                break;
            }

            case 5: {
                int id = selecionar_grafo(grafos);
                if (id != -1) {
                    cout << "Selecione o método de resolução:" << endl;
                    cout << "0. Voltar / Cancelar" << endl;
                    cout << "1. Exato (Enumeração + Bitmask - Menor caminho absoluto)" << endl;
                    cout << "2. Heurística Gulosa (Ordenação por menor distância)" << endl;
                    cout << "3. Heurística Vizinho Mais Próximo" << endl;
                    cout << "R.: ";
                    int met = ler_numero();

                    if (met == 0) {
                        cout << "Operação cancelada." << endl;
                        break;
                    }

                    ModoCarteiroChines modo = ModoCarteiroChines::EXATO_ENUMERACAO;
                    if (met == 2) modo = ModoCarteiroChines::GULOSO;
                    else if (met == 3) modo = ModoCarteiroChines::VIZINHO_MAIS_PROXIMO;

                    auto res = grafos[id].resolver_carteiro_chines(modo);

                    cout << endl << "=== RESULTADO DO CARTEIRO CHINÊS ===" << endl;
                    cout << "Tempo de Execução: " << res.tempo_ms << " ms" << endl;
                    cout << "Custo Total do Circuito: " << res.custo_total << endl;
                    cout << "Custo Adicional (Arestas Duplicadas): " << res.custo_adicional << endl;
                    cout << "Circuito Euleriano Resultante (" << res.circuito.size() << " vértices no percurso):" << endl;

                    for (size_t i = 0; i < res.circuito.size(); i++) {
                        cout << res.circuito[i] << (i + 1 < res.circuito.size() ? " -> " : "");
                    }
                    cout << endl;
                    pausar();
                }
                break;
            }

            default:
                cout << "Selecione uma opção válida ou escolha 0 para voltar." << endl;
                pausar();
                break;
        }
    }
}

void menu_saves(vector<Grafo>& grafos, string& ultimo_save) {
    int sub4 = -1;
    while (sub4 != 0) {
        limpar_tela();
        cout << "--- SAVES ---" << endl;
        cout << "0. Voltar ao Menu Principal" << endl;
        cout << "1. Salvar grafos no PC" << endl;
        cout << "2. Carregar grafos do PC" << endl;
        cout << "R.: ";

        sub4 = ler_numero();

        switch (sub4) {
            case 0:
                break;

            case 1: {
                std::filesystem::create_directory("saves");

                cout << "Digite um nome para o seu Save (sem o .txt)" << endl;
                if (!ultimo_save.empty()) {
                    string save_limpo = ultimo_save.substr(6);
                    save_limpo = save_limpo.substr(0, save_limpo.find(".txt"));
                    cout << "(Ou digite '.' para sobrescrever o arquivo atual: " << save_limpo << ")" << endl;
                }
                cout << "(Ou digite '0' para cancelar)" << endl << "R.: ";

                string nome_save;
                getline(cin, nome_save);
                remover_espacos_finais(nome_save);

                string nome_arquivo;

                if (nome_save == "0") {
                    cout << "Salvamento cancelado." << endl;
                    pausar();
                    break;
                }

                if (nome_save == ".") {
                    if (ultimo_save.empty()) {
                        cout << "  [!] ERRO: Nenhum save carregado ou salvo anteriormente para sobrescrever!" << endl;
                        pausar();
                        break;
                    }
                    nome_arquivo = ultimo_save;
                } else {
                    nome_arquivo = "saves/" + nome_save + ".txt";
                    ultimo_save = nome_arquivo;
                }

                ofstream arquivo(nome_arquivo);

                if (arquivo.is_open()) {
                    arquivo << grafos.size() << "\n";

                    for (size_t i = 0; i < grafos.size(); i++) {
                        grafos[i].salvar_grafo(arquivo);
                    }
                    arquivo.close();

                    string save_limpo = nome_arquivo.substr(6);
                    save_limpo = save_limpo.substr(0, save_limpo.find(".txt"));
                    cout << "Save '" << save_limpo << "' salvo com sucesso! :)" << endl;
                } else {
                    cout << "  [!] ERRO: Nao foi possivel criar o arquivo!" << endl;
                }
                pausar();
                break;
            }

            case 2: {
                std::filesystem::create_directory("saves");

                cout << "--- Saves disponíveis ---" << endl;
                bool achou_save = false;

                for (const auto& it : std::filesystem::directory_iterator("saves")) {
                    if (it.path().extension() == ".txt") {
                        string nome_completo = it.path().filename().string();
                        string nome_limpo = nome_completo.substr(0, nome_completo.find(".txt"));
                        cout << " -> " << nome_limpo << endl;
                        achou_save = true;
                    }
                }

                if (!achou_save) {
                    cout << "  Nenhum save encontrado na pasta 'saves'! ;-;" << endl;
                    pausar();
                    break;
                }

                cout << endl << "Qual o nome do Save que voce deseja carregar? (digite exatamente igual acima)." << endl;
                cout << "(Ou digite '0' para cancelar)" << endl << "R.: ";

                string nome_save;
                getline(cin, nome_save);
                remover_espacos_finais(nome_save);

                if (nome_save == "0") {
                    cout << "Carregamento cancelado." << endl;
                    pausar();
                    break;
                }

                string nome_arquivo = "saves/" + nome_save + ".txt";

                ifstream arquivo(nome_arquivo);
                if (arquivo.is_open()) {
                    int total_grafos;

                    if (arquivo >> total_grafos) {
                        grafos.clear();

                        for (int i = 0; i < total_grafos; i++) {
                            arquivo.ignore(numeric_limits<streamsize>::max(), '\n');

                            string nome;
                            getline(arquivo, nome);
                            int v, a;
                            arquivo >> v >> a;

                            Grafo g(v, nome);

                            for (int j = 0; j < a; j++) {
                                int u, vizinho, peso;
                                arquivo >> u >> vizinho >> peso;
                                g.adicionar_aresta(u, vizinho, peso);
                            }

                            grafos.push_back(g);
                        }
                        ultimo_save = nome_arquivo;
                        cout << "Foram carregados " << total_grafos << " grafos com sucesso! :D" << endl;
                    }
                    arquivo.close();
                } else {
                    cout << "  [!] ERRO: Save '" << nome_save << "' nao encontrado! Verifique se digitou certo." << endl;
                }
                pausar();
                break;
            }

            default:
                cout << "Selecione uma opção válida ou escolha 0 para voltar." << endl;
                pausar();
                break;
        }
    }
}

int main() {
    vector<Grafo> grafos;
    string ultimo_save = "";
    int sub = -1;

    while (sub != 0) {
        limpar_tela();
        cout << "--- MENU PRINCIPAL ---" << endl;
        cout << "0. Encerrar programa" << endl;
        cout << "1. Gerenciar e Visualizar Grafos" << endl;
        cout << "2. Buscas e Caminhos Mínimos (BFS / Dijkstra)" << endl;
        cout << "3. Propriedades e Algoritmos Avançados (Kosaraju, Carteiro Chinês, etc.)" << endl;
        cout << "4. Saves (Salvar e Carregar)" << endl;
        cout << "R.: ";

        sub = ler_numero();
        cout << endl;

        switch (sub) {
            case 0:
                limpar_tela();
                cout << "Programa finalizado :)" << endl << endl;
                break;

            case 1:
                menu_gerenciar_grafos(grafos);
                break;

            case 2:
                menu_buscas_caminhos(grafos);
                break;

            case 3:
                menu_propriedades_avancadas(grafos);
                break;

            case 4:
                menu_saves(grafos, ultimo_save);
                break;

            default:
                cout << "Selecione uma opção válida ou escolha 0 para sair.  >:^(" << endl;
                pausar();
                break;
        }
    }

    return 0;
}