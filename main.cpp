#include <bits/stdc++.h>
#include <filesystem>
#include "grafo.hpp"

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vii;
typedef map<int, int> mpii;
typedef map<string, int> mpsi;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const int MOD = 1e9 + 7;

#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define endl '\n'
#define Lbuffer cin.ignore(numeric_limits<streamsize>::max(), '\n')

int ler_numero() {
    int numero;
    while (true) {
        cin >> numero;
        
        if (!cin.fail()) {
            return numero;
        }
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "[!] ERRO: Entrada invalida! Por favor, digite APENAS numeros: ";
    }
}

int main(){
    vector<Grafo> grafos;
    string ultimo_save = "";

    int sub = -1;
    int a, b;

    while(sub != 0){
        cout<<"--- MENU PRINCIPAL ---"<<endl;
        cout<<"0. Encerrar programa"<<endl;
        cout<<"1. Gerenciar Grafos (Criar, Listar, Adicionar, Remover Arestas)"<<endl;
        cout<<"2. Analisar Grafos (Conexões, Componentes, Caminhos, Ciclos, Bipartido)"<<endl;
        cout<<"3. Saves (Salvar e Carregar)"<<endl;
        cout<<"R.: ";

        sub = ler_numero();

        cout<<endl;

        switch(sub){
            case 0:
                cout<<"Programa finalizado :)"<<endl<<endl;
                break;

            case 1:{
                int sub1 = -1;
                while(sub1 != 0){
                    cout<<"--- GERENCIAR GRAFOS ---"<<endl;
                    cout<<"0. Voltar ao Menu Principal"<<endl;
                    cout<<"1. Criar novo grafo"<<endl;
                    cout<<"2. Listar grafos"<<endl;
                    cout<<"3. Adicionar arestas em um grafo"<<endl;
                    cout<<"4. Remover arestas em um grafo"<<endl;
                    cout<<"R.: ";
                    
                    sub1 = ler_numero();

                    switch(sub1){
                        case 0:
                            break;

                        case 1:{
                            cout<<"Dê um nome ao seu novo grafo: "<<endl<<"R.: ";
                            Lbuffer;
                            
                            string nome; getline(cin, nome);

                            cout<<"Seu grafo tem quantos vértices?"<<endl<<"R.: ";
                            int qtd_vertices = ler_numero();

                            Grafo grafo(qtd_vertices, nome);
                            grafos.push_back(grafo);
                            cout << "Grafo '" << nome << "' criado com sucesso! :D" <<endl;
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        case 2:{
                            if(grafos.empty()){
                                cout << "Nenhum grafo criado ainda! ;-;" << endl;
                            } else {
                                cout << "--- LISTA DE GRAFOS ---" << endl;
                                for (size_t i = 0; i < grafos.size(); i++){
                                    cout << i << ". ";
                                    grafos[i].imprime_nome(); 
                                    cout << endl;
                                }
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        case 3:{
                            if(grafos.empty()){
                                cout << "Nenhum grafo criado ainda! ;-;" << endl;
                            } else {
                                cout<<"Selecione o NUMERO do grafo:"<<endl;
                                for(size_t i = 0; i < grafos.size(); i++){
                                    cout << i << ". "; grafos[i].imprime_nome(); cout<<endl;
                                }
                                
                                cout<<"R.: ";
                                int id = ler_numero();
                                
                                if(id >= 0 && id < grafos.size()){
                                    cout<<"Deseja adicionar quantas arestas?"<<endl<<"R.: ";
                                    int n = ler_numero();
                                    
                                    while(n--){
                                        cout << "Digite os dois vertices (espaco entre eles): ";
                                        a = ler_numero();
                                        b = ler_numero();

                                        if(grafos[id].adicionar_aresta(a, b)){
                                            cout << "Aresta adicionada no grafo "; grafos[id].imprime_nome(); cout << "!" << endl;
                                        }
                                    }
                                } else {
                                    cout << "Grafo invalido! ;-;" << endl;
                                }
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        case 4:{
                            if(grafos.empty()){
                                cout << "Nenhum grafo criado ainda! ;-;" << endl;
                            } else {
                                cout<<"Selecione o NUMERO do grafo:"<<endl;
                                for(size_t i = 0; i < grafos.size(); i++){
                                    cout << i << ". "; grafos[i].imprime_nome(); cout<<endl;
                                }
                                
                                cout<<"R.: ";
                                int id = ler_numero();
                                
                                if(id >= 0 && id < grafos.size()){
                                    cout<<"Deseja remover quantas arestas?"<<endl<<"R.: ";
                                    int n = ler_numero();
                                    
                                    while(n--){
                                        cout << "Digite os dois vertices da aresta a remover (espaco entre eles): ";
                                        a = ler_numero();
                                        b = ler_numero();

                                        if(grafos[id].excluir_aresta(a, b)){
                                            cout << "Aresta removida no grafo "; grafos[id].imprime_nome(); cout << "!" << endl;
                                        }
                                    }
                                } else {
                                    cout << "Grafo invalido! ;-;" << endl;
                                }
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        default:
                            cout<<"Selecione uma opção válida ou escolha 0 para voltar."<<endl<<endl;
                            break;
                    }
                }
                break;
            }

            case 2:{
                int sub2 = -1;
                while(sub2 != 0){
                    cout<<"--- ANALISAR GRAFOS ---"<<endl;
                    cout<<"0. Voltar ao Menu Principal"<<endl;
                    cout<<"1. Mostrar conexões de um grafo"<<endl;
                    cout<<"2. Mostrar componentes de um grafo"<<endl;
                    cout<<"3. Mostrar caminho de um vértice a outro em um grafo"<<endl;
                    cout<<"4. Encontrar ciclos em um grafo"<<endl;
                    cout<<"5. Verificar se um grafo é bipartido"<<endl;
                    cout<<"R.: ";
                    
                    sub2 = ler_numero();

                    switch(sub2){
                        case 0:
                            break;

                        case 1:{
                            if(grafos.empty()){
                                cout << "Nenhum grafo criado ainda! ;-;" << endl;
                            } else {
                                cout<<"Selecione o NUMERO do grafo:"<<endl;
                                for(size_t i = 0; i < grafos.size(); i++){
                                    cout << i << ". "; grafos[i].imprime_nome(); cout<<endl;
                                }
                                
                                cout<<"R.: ";
                                int id = ler_numero();

                                if(id >= 0 && id < grafos.size()){
                                    grafos[id].imprimir_conexoes();
                                } else {
                                    cout << "Grafo invalido! ;-;" << endl;
                                }
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        case 2:{
                            if(grafos.empty()){
                                cout << "Nenhum grafo criado ainda! ;-;" << endl;
                            } else {
                                cout<<"Selecione o NUMERO do grafo:"<<endl;
                                for(size_t i = 0; i < grafos.size(); i++){
                                    cout << i << ". "; grafos[i].imprime_nome(); cout<<endl;
                                }
                                
                                cout<<"R.: ";
                                int id = ler_numero();

                                if(id >= 0 && id < grafos.size()) grafos[id].imprimir_componentes();
                                else cout << "Grafo invalido! ;-;" << endl;
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        case 3:{
                            if(grafos.empty()){
                                cout << "Nenhum grafo criado ainda! ;-;" << endl;
                            } else {
                                cout<<"Selecione o NUMERO do grafo:"<<endl;
                                for(size_t i = 0; i < grafos.size(); i++){
                                    cout << i << ". "; grafos[i].imprime_nome(); cout<<endl;
                                }
                                
                                cout<<"R.: ";
                                int id = ler_numero();

                                if(id >= 0 && id < grafos.size()){
                                    cout << "Digite a origem e o destino: ";
                                    a = ler_numero();
                                    b = ler_numero();
                                    grafos[id].mostrar_caminho(a, b);
                                } else {
                                    cout << "Grafo invalido! ;-;" << endl;
                                }
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        case 4:{
                            if(grafos.empty()){
                                cout << "Nenhum grafo criado ainda! ;-;" << endl;
                            } else {
                                cout<<"Selecione o NUMERO do grafo:"<<endl;
                                for(size_t i = 0; i < grafos.size(); i++){
                                    cout << i << ". "; grafos[i].imprime_nome(); cout<<endl;
                                }
                                
                                cout<<"R.: ";
                                int id = ler_numero();

                                if(id >= 0 && id < grafos.size()) grafos[id].encontra_ciclos_n_arestas();
                                else cout << "Grafo invalido! ;-;" << endl;
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        case 5:{
                            if(grafos.empty()){
                                cout << "Nenhum grafo criado ainda! ;-;" << endl;
                            } else {
                                cout<<"Selecione o NUMERO do grafo:"<<endl;
                                for(size_t i = 0; i < grafos.size(); i++){
                                    cout << i << ". "; grafos[i].imprime_nome(); cout<<endl;
                                }
                                
                                cout<<"R.: ";
                                int id = ler_numero();
                                
                                if(id >= 0 && id < grafos.size()) grafos[id].verifica_bipartido();
                                else cout << "Grafo invalido! ;-;" << endl;
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        default:
                            cout<<"Selecione uma opção válida ou escolha 0 para voltar."<<endl<<endl;
                            break;
                    }
                }
                break;
            }

            case 3:{
                int sub3 = -1;
                while(sub3 != 0){
                    cout<<"--- SAVES ---"<<endl;
                    cout<<"0. Voltar ao Menu Principal"<<endl;
                    cout<<"1. Salvar grafos no PC"<<endl;
                    cout<<"2. Carregar grafos do PC"<<endl;
                    cout<<"R.: ";
                    
                    sub3 = ler_numero();

                    switch(sub3){
                        case 0:
                            break;

                        case 1:{
                            std::filesystem::create_directory("saves");

                            cout<<"Digite um nome para o seu Save (sem o .txt)"<<endl;
                            if(!ultimo_save.empty()){
                                string save_limpo = ultimo_save.substr(6);
                                save_limpo = save_limpo.substr(0, save_limpo.find(".txt"));
                                cout<<"(Ou digite '.' para sobrescrever o arquivo atual: " << save_limpo << ")"<<endl;
                            }
                            cout<<"(Ou digite '0' para cancelar)"<<endl<<"R.: ";
                            Lbuffer;

                            string nome_save; getline(cin, nome_save);
                            string nome_arquivo;

                            if(nome_save == "0"){
                                cout << "Salvamento cancelado." << endl;
                                cout<<"---------------------------"<<endl<<endl;
                                break;
                            }

                            if(nome_save == "."){
                                if(ultimo_save.empty()){
                                    cout << "  [!] ERRO: Nenhum save carregado ou salvo anteriormente para sobrescrever!" << endl;
                                    cout<<"---------------------------"<<endl<<endl;
                                    break;
                                }
                                nome_arquivo = ultimo_save;
                            } else {
                                nome_arquivo = "saves/" + nome_save + ".txt";
                                ultimo_save = nome_arquivo;
                            }

                            ofstream arquivo(nome_arquivo);
                            
                            if(arquivo.is_open()){
                                arquivo << grafos.size() << "\n";

                                for(size_t i = 0; i < grafos.size(); i++){
                                    grafos[i].salvar_grafo(arquivo); 
                                }
                                arquivo.close();
                                
                                string save_limpo = nome_arquivo.substr(6);
                                save_limpo = save_limpo.substr(0, save_limpo.find(".txt"));
                                cout << "Save '" << save_limpo << "' salvo com sucesso! :)" << endl;
                            } else {
                                cout << "  [!] ERRO: Nao foi possivel criar o arquivo!" << endl;
                            }
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        case 2:{
                            std::filesystem::create_directory("saves");

                            cout<<"---Saves disponíveis---"<<endl;
                            bool achou_save = false;

                            for(const auto& it : std::filesystem::directory_iterator("saves")){
                                if(it.path().extension() == ".txt"){
                                    string nome_completo = it.path().filename().string();
                                    string nome_limpo = nome_completo.substr(0, nome_completo.find(".txt"));
                                    cout<< " -> " << nome_limpo <<endl;
                                    achou_save = true;
                                }
                            }

                            if(!achou_save){
                                cout << "  Nenhum save encontrado na pasta 'saves'! ;-;" << endl;
                                cout<<"---------------------------"<<endl<<endl;
                                break;
                            }

                            cout << endl << "Qual o nome do Save que voce deseja carregar? (digite exatamente igual acima)." << endl;
                            cout << "(Ou digite '0' para cancelar)"<<endl<<"R.: ";
                            Lbuffer;

                            string nome_save; getline(cin, nome_save);

                            if(nome_save == "0"){
                                cout << "Carregamento cancelado." << endl;
                                cout<<"---------------------------"<<endl<<endl;
                                break;
                            }

                            string nome_arquivo = "saves/" + nome_save + ".txt";

                            ifstream arquivo(nome_arquivo);
                            if(arquivo.is_open()){
                                int total_grafos;

                                if(arquivo >> total_grafos){
                                    grafos.clear();

                                    for(int i = 0; i < total_grafos; i++){
                                        arquivo.ignore(numeric_limits<streamsize>::max(), '\n');
                                        
                                        string nome;
                                        getline(arquivo, nome);
                                        int v, a;
                                        arquivo >> v >> a;

                                        Grafo g(v, nome);

                                        for(int j = 0; j < a; j++){
                                            int u, vizinho;
                                            arquivo >> u >> vizinho;
                                            g.adicionar_aresta(u, vizinho);
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
                            cout<<"---------------------------"<<endl<<endl;
                            break;
                        }

                        default:
                            cout<<"Selecione uma opção válida ou escolha 0 para voltar."<<endl<<endl;
                            break;
                    }
                }
                break;
            }

            default:
                cout<<"Selecione uma opção válida ou escolha 0 para sair.  >:^("<<endl;
                cout<<"---------------------------"<<endl<<endl;
                break;
        }
    }

    return 0;
}