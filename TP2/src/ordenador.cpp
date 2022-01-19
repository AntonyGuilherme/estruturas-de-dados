#include "ordenador.hpp"
#include <iostream>
void Ordenador::ordenar(URL **urls, int tamanho)
{
    if (tamanho <= 1)
        return;

    realizarOrdenacao(0, tamanho - 1, urls);
}

int Ordenador::comparar(URL *url1, URL *url2)
{
    
    return url1->isSuperiorComparadaCom(url2);
}

void Ordenador::particionar(int Esq, int Dir, int *i, int *j, URL **urls)
{
    URL *x, *w;
    *i = Esq;
    *j = Dir;
    x = urls[(*i + *j) / 2]; /* obtem o pivo x */
    do
    {
        while (this->comparar(x, urls[*i]) > 0)
            (*i)++;
        while (this->comparar(x, urls[*j]) < 0)
            (*j)--;
        if (*i <= *j)
        {
            w = urls[*i];
            urls[*i] = urls[*j];
            urls[*j] = w;
            (*i)++;
            (*j)--;
            
        }
    } while (*i <= *j);

}

void Ordenador::realizarOrdenacao(int Esq, int Dir, URL **urls)
{
    int i, j;
    particionar(Esq, Dir, &i, &j, urls);
    if (Esq < j)
        realizarOrdenacao(Esq, j, urls);
    if (i < Dir)
        realizarOrdenacao(i, Dir, urls);

}