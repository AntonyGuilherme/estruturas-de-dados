#ifndef ORDENADOR_H
#define ORDENADOR_H

#include "url.hpp"

class Ordenador
{

public:
    void ordenar(URL **urls, int tamanho);

private:
    int comparar(URL *url, URL *url2);
    void realizarOrdenacao(int Esq, int Dir, URL ** url);
    void particionar(int Esq, int Dir, int *i, int *j, URL ** url);
};

#endif