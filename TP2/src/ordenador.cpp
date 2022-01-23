#include "ordenador.hpp"
#include <iostream>

int mediana(int index1, int index2, int index3, URL **urls)
{

    if (urls[index1]->isSuperiorComparadaCom(urls[index2]) >= 0)
    {
        if (urls[index1]->isSuperiorComparadaCom(urls[index3]) <= 0)
            return index1;
    }
    else if (urls[index2]->isSuperiorComparadaCom(urls[index3]) <= 0)
        return index2;

    return index3;
}

void Ordenador::ordenar(URL **urls, int tamanho)
{
    // não é necessário ordenar um vetor de um item
    if (tamanho <= 1)
        return;

    // realizando a ordenação
    realizarOrdenacao(0, tamanho - 1, urls);
}

int Ordenador::comparar(URL *url1, URL *url2)
{

    return url1->isSuperiorComparadaCom(url2);
}

/**
 * @param Esq índice inicial
 * @param Dir índice final
 * @param i índice de maiores
 * @param j índice de menores
 * @param urls - vetor
 */
void Ordenador::particionar(int Esq, int Dir, int *i, int *j, URL **urls)
{
    URL *x, *w;
    // inicializa os índices que vão percorrer o vetor
    *i = Esq;
    *j = Dir;

    int indiceDoPivo = mediana(Esq,Dir,(Esq+Dir)/2,urls);

    // inicializa o pivô com elemento central
    x = urls[indiceDoPivo];
    do
    {
        // procura elemento maior que o pivô
        while (this->comparar(x, urls[*i]) > 0)
            (*i)++;
        // procura elemento menor que o pivô
        while (this->comparar(x, urls[*j]) < 0)
            (*j)--;

        // se os índices não se cruzaram
        if (*i <= *j)
        {
            // então troca-se os elementos de índice i e j de lugar
            w = urls[*i];
            urls[*i] = urls[*j];
            urls[*j] = w;

            // i e j passam para a próxima posição
            (*i)++;
            (*j)--;
        }

    } while (*i <= *j); // é executado até que os índices se cruzem
}

/**
 * @param Esq índice inicial
 * @param Dir índice final
 * @param urls vetor
 */
void Ordenador::realizarOrdenacao(int Esq, int Dir, URL **urls)
{

    // índices i e j que vão percorrer o vetor
    int i, j;

    // Particiona com os índices i e j
    particionar(Esq, Dir, &i, &j, urls);

    // se os elementos são <= pivô
    if (Esq < j)
        realizarOrdenacao(Esq, j, urls);

    // se os elementos são maiores ou iguais aos do pivô
    if (i < Dir)
        realizarOrdenacao(i, Dir, urls);
}