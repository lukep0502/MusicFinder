#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <string>
#include <new>
#include <fstream>
#include "json.hpp"
#include <locale>
#include <windows.h>

using namespace std;
using json = nlohmann::json;

void margem(){
    cout << "--------------------------------------\n";
}

void limpa_tela(){
    system("CLS");
}

string rtrim_copy(const string &s) {
    size_t endpos = s.find_last_not_of(" \t\n\r\f\v");
    if (endpos != string::npos)
        return s.substr(0, endpos + 1);
    else
        return "";
}

string toLowerCase(const string& s) {
    string result = s; // cria uma cópia
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c){ return tolower(c); });
    return result;
}

json inicia_json(){
    ifstream arquivo("exemplo_aleatorio.json");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo JSON!" << endl;
        exit(EXIT_FAILURE);
    }

    json dados;
    arquivo >> dados;
    return dados;
}

int procura_nome(json *dados){

    string campo_nome = "Nome completo";

    string nomeBuscado;
    cout << "Digite o nome da pessoa: ";
    getline(cin, nomeBuscado);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool achou = false;

    for (const auto& usuario : *dados) {
        if (
            usuario.is_object() &&
            usuario.contains(campo_nome) &&
            usuario[campo_nome].is_string() &&
            toLowerCase(rtrim_copy(usuario[campo_nome].get<string>())) == toLowerCase(rtrim_copy(nomeBuscado))
        ) {
            limpa_tela();

            margem();
            cout << "Informações encontradas:\n";

            cout << "Nome: " << nomeBuscado << endl;

            if (usuario.contains("ID"))
                cout << "ID: " << usuario["ID"] << endl;

            if (usuario.contains("Link da música:"))
                cout << "Link da música: " << usuario["Link da música:"].get<string>() << endl;
            else
                cout << "Usuário não tem link da música cadastrado." << endl;

            achou = true;
            margem();
            break;
        }
    }

    if (!achou) {
        limpa_tela();
        margem();
        cout << "Usuário \"" << nomeBuscado << "\" não encontrado." << endl;
        margem();
    }

    int continuar;

    cout << "Deseja continuar procurando?\n";
    cout << "1- Sim\n";
    cout << "2- Nao\n";
    cout << "Precione ENTER para confirmar: ";

    cin >> continuar;

    if(continuar == 1){
        return -1;
    }else{
        return 1;
    }
}

int procura_id(json* dados) {

    string campo_nome  = "Nome completo";

    int idBuscado;
    cout << "Digite o ID da pessoa: ";
    cin >> idBuscado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool achou = false;
 
    for (const auto& usuario : *dados) {
        if (
            usuario.is_object() &&
            usuario.contains("ID") 
        ) {
            bool match = false;
            if (usuario["ID"].is_number_integer()) {
                match = (usuario["ID"].get<int>() == idBuscado);
            } else if (usuario["ID"].is_string()) {
                match = (usuario["ID"].get<string>() == to_string(idBuscado));
            }

            if (match){
                limpa_tela();
                margem();
                cout << "Informações encontradas:\n";

                if (usuario.contains(campo_nome))
                    cout << "Nome: " << usuario[campo_nome].get<string>() << endl;

                cout << "ID: " << idBuscado << endl;

                if (usuario.contains("Link da música:"))
                    cout << "Link da música: " << usuario["Link da música:"].get<string>() << endl;
                else
                    cout << "Usuário não tem link da música cadastrado." << endl;

                achou = true;
                margem();
                break;
            }

        }
    }

    if (!achou) {
        limpa_tela();
        margem();
        cout << "Usuário com ID \"" << idBuscado << "\" não encontrado." << endl;
        margem();
    }

    int continuar;

    cout << "Deseja continuar procurando?\n";
    cout << "1- Sim\n";
    cout << "2- Nao\n";
    cout << "Precione ENTER para confirmar: ";
    cin >> continuar;

    if(continuar == 1){
        return -1;
    }else{
        return 1;
    }

}

void menu(json *dados, int *procurar){
    limpa_tela();
    int escolha;

    cout << "Buscar por:\n";
    cout << "1-nome\n";
    cout << "2-id\n";
    cout << "Precione ENTER para confirmar: ";
    
    cin >> escolha;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (escolha)
    {
    case 1:
        *procurar = procura_nome(dados);
        break;
    
    case 2:
        *procurar = procura_id(dados);
        break;
    };

}

void programa(json *dados){

    int procurar = -1;

    while(procurar != 1){
        menu(dados, &procurar);
    }
}

int main(){

    setlocale(LC_ALL, "Portuguese_Brazil.1252");

    limpa_tela();


    json dados;
    dados = inicia_json();

    programa(&dados);

    return 0;
}