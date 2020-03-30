#include <iostream>
#include <sstream>
#include "sorteio.hpp"



using namespace std;

Sorteio jogo;

extern void Opcoes();
void limpa_tela()
{   
     
    #ifdef __unix__
        system("clear");
    #elif WIN32
        system("cls");
    #endif
}

void novaOperacao()
{
    cout << "\n __________________________________________\n";
    string opcao;
    cout << "Deseja realizar uma nova operacao?\n";
    cout << "\t1-SIM\n";
    cout << "\t2-NAO\n";
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
        novaOperacao();
        break;
    case 1:
        limpa_tela();
        Opcoes();
        break;
    case 2:
        limpa_tela();
        exit(0);
        break;
    default:
        limpa_tela();
        novaOperacao();
    }
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

    novaOperacao();
}


int main( int argc, const char** argv )
{
    Opcoes();
    return 0;
}

