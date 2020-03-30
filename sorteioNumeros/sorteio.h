#ifndef SORTEIO_H
#define SORTEIO_H

#include <vector>

class Sorteio
{
private:

public:
    Sorteio(/* args */);

    std::vector<int> numeros;
    
    int sortear();
    void Sequencia();
    void salvarArquivo(int);
    void lerArquivo();
};

#endif
