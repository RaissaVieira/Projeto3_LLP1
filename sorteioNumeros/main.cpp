#include <iostream>
#include <sstream>
#include "sorteio.h"

using namespace std;

Sorteio jogo;

void limpa_tela()
{
    #ifdef __unix__
        system("clear");
    #elif WIN32
        system("cls");
    #endif
}

void Opcoes ()
{
    string opcao;
    limpa_tela();
    cout<<"LRY Genius"<<endl;
    cout<<"\t1-Iniciar jogo"<<endl;
    cout<<"\t2-Placar"<<endl;
    cout<<"\t3-Sair"<<endl;


    cout<<"\tDigite a operação que deseja ser realizada: ";
    cin>>opcao;
    cin.ignore();

    stringstream op (opcao);
    int escolha = 0;
    op>>escolha;

    switch (escolha)
    {
    case 0:
        limpa_tela();
        Opcoes();
        break;
    case 1:
        limpa_tela();
        jogo.Sequencia();
        break;
    case 2:
        limpa_tela();
        jogo.lerArquivo();
        break;
    case 3:
        exit(0);
    default:
        Opcoes();
    }
}

int main(){
    Opcoes();

    return 0;
}