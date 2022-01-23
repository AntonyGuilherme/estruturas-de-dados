#ifndef HEAP_ANTIGO_H
#define HEAP_ANTIGO_H

#include "url.hpp"

class Heap
{

private:
    URL ** heap;
    int tamanhoTotal;
    int tamanhoUsado;
    void Refaz(int Esq, int Dir, URL **url);
    bool RetiraMax(URL ** A, int *n, URL *& url);
    void Constroi(URL ** A, int * n);

public:
    Heap(int tamanhoDoHeap);
    bool pop(URL*&url);
    void inserir(URL * url);
    ~Heap();

};

#endif