#ifndef SORTEIO_H
#define SORTEIO_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "DetectorDeRostos.hpp"

unsigned int microseconds;

#define vermelho 1
#define verde 2
#define azul 3
#define amarelo 4

class Sorteio
{
private:
    DetectorDeRostos faceDetect;
public:

    std::vector<int> numeros;
    
    int sortear(){
        return rand() % 4 + 1;
    }
    void Sequencia(){
    int num,i,pontuacao, opcao;
    std::string pontuacao1;

    numeros.clear();

    srand(time(NULL));
    i = pontuacao = 0;
        while (1)
        {
            num = sortear();
            numeros.push_back(num);

            for (std::vector<int>::iterator it = numeros.begin(); it < numeros.end(); it++)
            {   
                switch (*it)
                {
                case 1:
                    /* codigo da musica (vermelho) */
                    usleep(3000);
                    system("mpg123 vermelho.mp3");
                    std::cout << 1 << " ";
                    break;

                case 2:
                    /* codigo da musica (verde) */
                    usleep(3000);
                    system("mpg123 verde.mp3");
                    std::cout << 2 << " ";
                    break;

                case 3:
                    /* codigo da musica (azul) */
                    usleep(3000);
                    system("mpg123 azul.mp3");
                    std::cout << 3 << " ";
                    break;

                case 4:
                    /* codigo da musica (amarelo) */
                    usleep(3000);
                    system("mpg123 amarelo.mp3");
                    std::cout << 4 << " ";
                    break;
                }

            }

            for (std::vector<int>::iterator it = numeros.begin(); it < numeros.end(); it++)
            {   
                //Colocar o codigo de leitura da posicao do jogador

                std::cout<< "ler" << "\n"; //testando (apagar depois)
                opcao = faceDetect._faceCapture(pontuacao);

                if(*it != opcao /*area que a pessoa vai com a cabeca*/){
                    i = 1;
                    break;
                }
                
                pontuacao1 = std::to_string(++pontuacao);
                std::cout << "PONTUACAO: " << pontuacao1 << std::endl;
                system("mpg123 respostacerta.mp3");

            }
            if(i == 1){ //Perdeu
                std::cout << "PONTUACAO FINAL: " << pontuacao1 << std::endl;
                system("mpg123 Perdeu.mp3");
                salvarArquivo(pontuacao);
                break;
            }

        }
}
    void salvarArquivo(int pontuacao){
    std::ofstream saida("Ranking.txt", std::ios::app);

    if(!saida.is_open()){
        std::cout<<"Nao foi possivel abrir o arquivo de saida"<<std::endl;
    }

    saida<<pontuacao<< std::endl;

    saida.close();
}
    void lerArquivo(){
    std::ifstream entrada("Ranking.txt", std::ios::in);
    std::string pontuacao; 
    int i = 1;
    

    if(!entrada.is_open()){
        std::cout<<"Nao foi possivel abrir entrada"<<std::endl;
    }
    
    std::cout << "PONTUACOES FEITAS: \n"; 
    while(!entrada.eof()){
        getline(entrada,pontuacao);
        std::cout << i++ << ". " << pontuacao << "\n";
    }

    entrada.close();
}
};

#endif
