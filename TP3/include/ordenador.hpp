#ifndef ORDENADOR_H
#define ORDENADOR_H

#include "HashWD.hpp"

class Ordenador
{

public:
    void ordenar(int * idsDocumentos, int tamanho, HashWD * hashwd);

private:
    int comparar(int documento1, int documento2, HashWD * hashwd);
    void realizarOrdenacao(int Esq, int Dir, int * idsDocumentos, HashWD * hashwd);
    void particionar(int Esq, int Dir, int *i, int *j, int * idsDocumentos, HashWD * hashwd);
};

#endif